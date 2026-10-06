# Enemy Weapon Manager

A standalone C++17 console-based gameplay-system demonstration implementing weapon management and enemy management using object-oriented programming principles.

## Overview

This project demonstrates how weapon and enemy systems can be structured for a game using modern C++.

The program contains:

- A polymorphic weapon system
- A weapon manager for equipping and switching weapons
- Multiple weapon types
- A polymorphic enemy system
- An enemy manager for spawning and removing enemies
- Dynamic ownership using `std::unique_ptr`
- A simple combat simulation

The project is designed as a small standalone demonstration of C++ gameplay programming concepts.

---

## Features

### Weapon System

The weapon system contains a base `Weapon` class and specialized weapon types.

Current weapons:

- Pistol
- Shotgun

Each weapon has:

- Name
- Damage
- Ammunition
- Firing functionality
- Reload functionality

The `Weapon` class uses a virtual damage calculation function, allowing derived weapons to implement different damage behaviors.

### Weapon Manager

`WeaponManager` is responsible for:

- Adding weapons
- Switching between weapons
- Firing the currently equipped weapon
- Tracking ammunition
- Displaying weapon status

The manager stores weapons using:

```cpp
std::vector<std::unique_ptr<Weapon>>
```

This allows the manager to own the weapon objects safely.

---

## Enemy System

The enemy system contains an abstract `Enemy` base class and specialized enemy types.

Current enemies:

- Grunt
- Brute

Each enemy has:

- Name
- Health
- Damage handling
- Alive/dead state
- Attack behavior

Different enemy types override their attack behavior using polymorphism.

---

## Enemy Manager

`EnemyManager` is responsible for:

- Spawning enemies
- Tracking active enemies
- Finding the first living enemy
- Removing defeated enemies
- Checking whether all enemies have been defeated
- Displaying enemy status

Enemies are stored using:

```cpp
std::vector<std::unique_ptr<Enemy>>
```

---

## Combat Simulation

The `main()` function demonstrates a simple combat loop.

The program:

1. Creates a weapon manager.
2. Adds a pistol and shotgun.
3. Creates an enemy manager.
4. Spawns a Grunt and a Brute.
5. Selects a weapon based on enemy health.
6. Fires the selected weapon.
7. Applies damage to the enemy.
8. Allows the enemy to attack if it survives.
9. Removes defeated enemies.
10. Continues until all enemies are defeated.

---

## C++ Concepts Demonstrated

This project focuses on practical C++ programming concepts used in gameplay systems.

### Object-Oriented Programming

- Classes and objects
- Inheritance
- Abstraction
- Encapsulation
- Polymorphism
- Virtual functions
- Function overriding

### Modern C++

- `std::unique_ptr`
- `std::make_unique`
- `std::vector`
- `std::string`
- `std::move`
- Range-based loops
- `const` member functions
- Smart-pointer ownership

### Algorithms

The project also uses:

```cpp
std::max
std::remove_if
```

for health management and removing defeated enemies.

---

## Project Structure

Currently the project is implemented as a single C++ source file:

```text
Enemy-Weapon-Manager/
│
├── .gitattributes
├── .gitignore
├── main.cpp
└── README.md
```

---

## Requirements

- C++17 compatible compiler
- GCC / MinGW, Clang, or another C++17 compiler

---

## Build

Using GCC:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o game
```

Run:

### Windows

```bash
game.exe
```

### Linux / macOS

```bash
./game
```

---

## Example Gameplay Flow

```text
Weapons:
> Pistol (ammo: 12)
  Shotgun (ammo: 6)

Enemies:
  Grunt (health: 50)
  Brute (health: 120)

--- Fight ---

Switched to Shotgun
Hit Brute for 30
Brute slams the ground!

Switched to Pistol
Hit Grunt for 10
Grunt swings a club!

...

All enemies defeated!
```

---

## Future Improvements

Possible improvements for the system include:

- Separate `.h` and `.cpp` files
- Weapon reload system
- Weapon cooldown
- Critical-hit system
- Different ammunition types
- Enemy attack damage
- Enemy AI states
- Target selection
- Multiple enemy spawn points
- Weapon inventory slots
- Health component
- Combat statistics
- Unit tests

---

## Purpose

This project is part of my C++ game-programming practice and demonstrates how object-oriented C++ concepts can be applied to gameplay-oriented systems.

The goal is to progressively develop more complex gameplay systems and eventually integrate similar concepts into Unreal Engine projects.

---

## Author

**Akhil Balija**

Computer Science Engineering Student  
Game Development / C++ / Unreal Engine
