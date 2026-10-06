// Enemy Manager and Weapon Manager

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================ Weapons ============================

// Abstract base class: every weapon must define how its damage is calculated.
class Weapon {
public:
    Weapon(std::string name, int damage, int ammo)
        : name_(std::move(name)), damage_(damage), ammo_(ammo) {}
    virtual ~Weapon() = default;

    // Fires once and returns the damage dealt (0 if out of ammo).
    int fire() {
        if (ammo_ <= 0) {
            std::cout << name_ << " is out of ammo!\n";
            return 0;
        }
        --ammo_;
        return calculateDamage();
    }

    void reload(int amount) { ammo_ += amount; }

    const std::string& name() const { return name_; }
    int ammo() const { return ammo_; }

protected:
    virtual int calculateDamage() const = 0;  // abstraction + polymorphism
    int baseDamage() const { return damage_; }

private:
    std::string name_;
    int damage_;
    int ammo_;
};

class Pistol : public Weapon {
public:
    Pistol() : Weapon("Pistol", 10, 12) {}

protected:
    int calculateDamage() const override { return baseDamage(); }
};

class Shotgun : public Weapon {
public:
    Shotgun() : Weapon("Shotgun", 10, 6) {}

protected:
    // Several pellets hit at once.
    int calculateDamage() const override { return baseDamage() * 3; }
};

// Owns the player's weapons and tracks which one is equipped.
class WeaponManager {
public:
    void addWeapon(std::unique_ptr<Weapon> weapon) {
        weapons_.push_back(std::move(weapon));
    }

    bool switchTo(std::size_t index) {
        if (index >= weapons_.size()) {
            std::cout << "No weapon in slot " << index << "\n";
            return false;
        }
        if (index != current_) {
            current_ = index;
            std::cout << "Switched to " << weapons_[current_]->name() << "\n";
        }
        return true;
    }

    // Fires the equipped weapon and returns the damage dealt.
    int fireCurrent() {
        if (weapons_.empty()) {
            std::cout << "No weapons equipped!\n";
            return 0;
        }
        return weapons_[current_]->fire();
    }

    void printStatus() const {
        for (std::size_t i = 0; i < weapons_.size(); ++i) {
            std::cout << (i == current_ ? "> " : "  ") << weapons_[i]->name()
                      << " (ammo: " << weapons_[i]->ammo() << ")\n";
        }
    }

private:
    std::vector<std::unique_ptr<Weapon>> weapons_;
    std::size_t current_ = 0;
};

// ============================ Enemies ============================

class Enemy {
public:
    Enemy(std::string name, int health)
        : name_(std::move(name)), health_(health) {}
    virtual ~Enemy() = default;

    void takeDamage(int amount) { health_ = std::max(0, health_ - amount); }
    bool isAlive() const { return health_ > 0; }

    const std::string& name() const { return name_; }
    int health() const { return health_; }

    virtual void attack() const = 0;  // each enemy type attacks differently

private:
    std::string name_;
    int health_;
};

class Grunt : public Enemy {
public:
    Grunt() : Enemy("Grunt", 50) {}
    void attack() const override { std::cout << "Grunt swings a club!\n"; }
};

class Brute : public Enemy {
public:
    Brute() : Enemy("Brute", 120) {}
    void attack() const override { std::cout << "Brute slams the ground!\n"; }
};

// Owns all enemies in the level.
class EnemyManager {
public:
    void spawn(std::unique_ptr<Enemy> enemy) {
        std::cout << enemy->name() << " spawned\n";
        enemies_.push_back(std::move(enemy));
    }

    // Returns the first living enemy, or nullptr. The manager keeps ownership.
    Enemy* firstAlive() const {
        for (const auto& enemy : enemies_) {
            if (enemy->isAlive()) return enemy.get();
        }
        return nullptr;
    }

    void removeDead() {
        enemies_.erase(
            std::remove_if(enemies_.begin(), enemies_.end(),
                           [](const std::unique_ptr<Enemy>& e) {
                               if (!e->isAlive()) {
                                   std::cout << e->name() << " defeated\n";
                                   return true;
                               }
                               return false;
                           }),
            enemies_.end());
    }

    bool allDefeated() const { return enemies_.empty(); }

    void printStatus() const {
        for (const auto& enemy : enemies_) {
            std::cout << "  " << enemy->name() << " (health: " << enemy->health() << ")\n";
        }
    }

private:
    std::vector<std::unique_ptr<Enemy>> enemies_;
};

// ============================== Demo ==============================

int main() {
    WeaponManager weapons;
    EnemyManager enemies;

    weapons.addWeapon(std::make_unique<Pistol>());
    weapons.addWeapon(std::make_unique<Shotgun>());

    enemies.spawn(std::make_unique<Grunt>());
    enemies.spawn(std::make_unique<Brute>());

    std::cout << "\nWeapons:\n";
    weapons.printStatus();
    std::cout << "Enemies:\n";
    enemies.printStatus();
    std::cout << "\n--- Fight ---\n";

    while (!enemies.allDefeated()) {
        Enemy* target = enemies.firstAlive();

        // Use the shotgun on tough enemies, the pistol on weak ones.
        weapons.switchTo(target->health() > 60 ? 1 : 0);

        int damage = weapons.fireCurrent();
        target->takeDamage(damage);
        std::cout << "Hit " << target->name() << " for " << damage
                  << " (health left: " << target->health() << ")\n";

        if (target->isAlive()) target->attack();
        enemies.removeDead();
    }

    std::cout << "\nAll enemies defeated!\n";
    weapons.printStatus();
    return 0;
}
