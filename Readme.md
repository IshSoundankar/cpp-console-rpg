# C++ Console RPG

A turn-based fantasy RPG played in the terminal. The player picks a race, moves around an 8x8 board, picks up equipment and fights enemies of other races. Built in C++17 with an object-oriented design: two class hierarchies, runtime polymorphism and smart-pointer memory management.

## Features

- 8x8 grid board with randomly placed enemies and items
- 5 playable races, each with its own stats and defence behaviour
- Equipment system with weapon, armour, shield and stackable ring slots, limited by carry weight
- Probabilistic combat using attack and defence chance rolls
- Day/night cycle that changes Orc stats every 5 turns

## Build and run

**Qt Creator:** open `untitled.pro` and run.

**Command line (g++):**

```
g++ -std=c++17 -I. board.cpp characters.cpp main.cpp -o rpg
./rpg
```

The screen is cleared with `system("cls")`, so the screen-clearing step is Windows-only. The game itself runs on any platform.

## Controls

| Key | Action |
|-----|--------|
| `w` `a` `s` `d` | Move up, left, down, right |
| `g` | Pick up item on current square |
| `j` | Attack enemy on current square |
| `h` | Drop an equipped item |
| `k` | Look at current square |
| `l` | Show inventory and gold |
| `x` | Exit |

Board symbols: `#` player, `*` enemy, `+` item.

Defeat every enemy to win. Each kill earns 20 gold.

## Races

| Race | Attack | Attack chance | Defence | Defence chance | Health | Strength | On successful defence |
|------|--------|---------------|---------|----------------|--------|----------|-----------------------|
| Human | 30 | 2/3 | 20 | 1/2 | 60 | 100 | No extra effect |
| Elf | 40 | 1 | 10 | 1/4 | 40 | 70 | Gains 1 health |
| Dwarf | 30 | 2/3 | 20 | 2/3 | 50 | 130 | No extra effect |
| Hobbit | 25 | 1/3 | 20 | 2/3 | 70 | 85 | Loses 0 to 5 health |
| Orc (day) | 25 | 1/4 | 10 | 1/4 | 50 | 130 | Takes a quarter of the damage |
| Orc (night) | 45 | 1 | 25 | 1/2 | 50 | 130 | Gains 1 health |

## Class design

```
Item                      Character (abstract)
 ├── Weapon                ├── Human
 ├── Armour                ├── Elf
 │    └── Shield           ├── Dwarf
 └── Ring                  ├── Hobbit
                           └── Orc

Board ── contains ──> Square ── holds ──> Character, Item
```

- **Character** is an abstract base class. `printStats()` is pure virtual, and `successfulDef()` is virtual so each race defines its own defence behaviour.
- **Equipment** is handled in `Character::pickUp()`, which uses `dynamic_pointer_cast` to work out the item type and equip it in the right slot. Total attack, defence, strength and health are calculated from base stats plus equipped items.
- **Board** is a `vector<vector<shared_ptr<Square>>>`. Each Square can hold an enemy, an item and the player.
- **Memory** is managed with `std::shared_ptr` throughout. The combat function takes raw `Character*` pointers, since it only uses the objects and does not own them.

## Post-submission fixes

This version includes fixes made after the original module submission:

- **Virtual dispatch:** `successfulDef()` was not declared `virtual` in the base class. Because combat calls it through a `Character*`, the empty base version always ran, which silently disabled every race-specific defence. Fixed by making it virtual and marking each override with `override`.
- **Shield equipping:** `Shield` inherits from `Armour`, so the `Armour` type check in `pickUp()` matched shields first and put them in the armour slot. Fixed by checking for the more specific type first. Shields are now also placed on the board.
- **Carry limit:** the weight check now uses total strength, so the Ring of Strength raises the limit as intended.
- **Orc defence:** daytime partial damage now uses total attack and defence, including equipment.
- **Input validation and bounds:** race selection rejects invalid input, and movement and the win check use the board dimensions rather than hardcoded values.

## Design trade-offs and known limitations

- `shared_ptr` gives the board and squares shared ownership of characters and items. That keeps lifetimes simple and avoids dangling pointers. A stricter design would keep ownership in one place and give squares non-owning `weak_ptr` or raw pointers.
- Squares are heap-allocated through `shared_ptr`. `vector<vector<Square>>` would work just as well and avoid an allocation per square.
- Because `Shield` inherits from `Armour`, the order of type checks in `pickUp()` matters. Making `Shield` inherit directly from `Item` would remove that dependency.
- Randomness uses `rand()`. `<random>` would give better distribution and seeding.
- Enemies do not move, and `using namespace std;` appears in headers.

## Credits

Developed as a 3-person group project with Steffy Pereppadan Ignatious and Onuchi Kalu for the Advanced Programming module of the MEng in Cybersecurity, University of Limerick (2025). I was the lead developer. This repository is my continued version of the project.