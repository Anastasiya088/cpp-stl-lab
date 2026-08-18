#define NOMINMAX
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <windows.h>

// 1. Базовий клас Auditor
template <typename K, typename V>
class Auditor {
public:
    virtual ~Auditor() = default;

    virtual bool canRead(const K& key) const { return true; }
    virtual bool canWrite(const K& key) const { return true; }
    virtual bool canErase(const K& key) const { return true; }

    // Трансформація/підміна значення при читанні
    virtual V processRead(const K& key, const V& originalValue) const {
        return originalValue;
    }
};

// 2. Підкласи Auditor з різною логікою доступу

// Аудитор, який дозволяє абсолютно все (без обмежень)
template <typename K, typename V>
class AllowAllAuditor : public Auditor<K, V> {};

// Аудитор тільки для читання (забороняє запис та видалення)
template <typename K, typename V>
class ReadOnlyAuditor : public Auditor<K, V> {
public:
    bool canWrite(const K& key) const override { return false; }
    bool canErase(const K& key) const override { return false; }
};

// Аудитор, що підміняє значення для конкретних ключів
template <typename K, typename V>
class OverrideValueAuditor : public Auditor<K, V> {
private:
    std::map<K, V> override_map;
public:
    OverrideValueAuditor(const std::map<K, V>& overrides) : override_map(overrides) {}

    V processRead(const K& key, const V& originalValue) const override {
        auto it = override_map.find(key);
        if (it != override_map.end()) {
            return it->second; // Підміна значення
        }
        return originalValue;
    }
};

// 3. Клас ProxiedMap
template <typename K, typename V>
class ProxiedMap {
private:
    std::map<K, V> internal_map;
    std::shared_ptr<Auditor<K, V>> auditor;

public:
    ProxiedMap(std::shared_ptr<Auditor<K, V>> aud) : auditor(aud) {
        if (!auditor) {
            auditor = std::make_shared<AllowAllAuditor<K, V>>();
        }
    }

    void setAuditor(std::shared_ptr<Auditor<K, V>> aud) {
        auditor = aud;
    }

    // Запис
    void insert(const K& key, const V& value) {
        if (!auditor->canWrite(key)) {
            throw std::runtime_error("Access Denied: Немає прав на запис ключа!");
        }
        internal_map[key] = value;
    }

    // Читання
    V get(const K& key) const {
        if (!auditor->canRead(key)) {
            throw std::runtime_error("Access Denied: Немає прав на читання ключа!");
        }
        auto it = internal_map.find(key);
        if (it == internal_map.end()) {
            throw std::out_of_range("Error: Ключ не знайдено!");
        }
        return auditor->processRead(key, it->second);
    }

    // Видалення
    void erase(const K& key) {
        if (!auditor->canErase(key)) {
            throw std::runtime_error("Access Denied: Немає прав на видалення ключа!");
        }
        internal_map.erase(key);
    }

    size_t size() const { return internal_map.size(); }
};

// 4. Тестування системи
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "=== Тестування ProxyMap та Auditor ===\n\n";

    // 1. Тест з AllowAllAuditor
    auto allowAll = std::make_shared<AllowAllAuditor<std::string, std::string>>();
    ProxiedMap<std::string, std::string> proxyMap(allowAll);

    proxyMap.insert("user", "Admin");
    proxyMap.insert("secret", "12345");
    std::cout << "[AllowAll] user: " << proxyMap.get("user") << "\n";

    // 2. Тест з ReadOnlyAuditor
    std::cout << "\n--- Переключення на ReadOnlyAuditor ---\n";
    auto readOnly = std::make_shared<ReadOnlyAuditor<std::string, std::string>>();
    proxyMap.setAuditor(readOnly);

    try {
        std::cout << "[ReadOnly] Спроба читання 'secret': " << proxyMap.get("secret") << "\n";
        std::cout << "[ReadOnly] Спроба запису нових даних...\n";
        proxyMap.insert("hack", "data");
    }
    catch (const std::exception& e) {
        std::cout << "Перехоплено виключення: " << e.what() << "\n";
    }

    try {
        std::cout << "[ReadOnly] Спроба видалення 'user'...\n";
        proxyMap.erase("user");
    }
    catch (const std::exception& e) {
        std::cout << "Перехоплено виключення: " << e.what() << "\n";
    }

    // 3. Тест з OverrideValueAuditor (підміна значення)
    std::cout << "\n--- Переключення на OverrideValueAuditor ---\n";
    std::map<std::string, std::string> overrides = { {"secret", "*****"} };
    auto overrideAuditor = std::make_shared<OverrideValueAuditor<std::string, std::string>>(overrides);
    proxyMap.setAuditor(overrideAuditor);

    std::cout << "[Override] user: " << proxyMap.get("user") << "\n";
    std::cout << "[Override] secret (підмінено): " << proxyMap.get("secret") << "\n";

    return 0;
}