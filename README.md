# CLGame
## Overview
CLGame is a command-line game that features turn-based combat in an endless dungeon setting. The player assumes the role of a knight navigating randomly through dungeon rooms, battling mobs, and collecting items to progress.

## Game Mechanics
### Player:
- The player is a knight who is sworn to eliminate all mobs encountered.
- The knight cannot flee from battles due to his oath and must defeat all mobs to proceed.
- The player is blind, which causes movement to be randomized when transitioning between rooms.
- Health is unlimited, but damage mitigation is determined by defense values with the following rules:
- Defense < 100: Damage taken is scaled by (1 - defense / 100).
- Defense >= 100: Damage taken is always reduced to 1% of the incoming damage.
### Mobs:
- Each room contains an array of mobs.
- Mobs have stats like health, attack, and defense.
- Every 5th room is a boss room, featuring a more powerful mob.
- Rooms:
- Rooms are generated dynamically with a room number acting as a difficulty modifier.
- A room’s difficulty scales with its number, making mobs tougher as the game progresses.
- After clearing all mobs in a room, the player moves to a new random room.
### Boss Rooms:
- Appear every 5th room.
- Feature a boss with a random name.
- Reward the player with a random item upon clearing.
### Items:
- Items can be weapons, armor, or consumables such as health potions.
- In boss rooms, a random item is awarded after defeating the boss.
- In regular rooms, the player receives:
- +20 health.
- +2 health potions after clearing the room.

## Save and Load Functionality
- The game allows progress to be saved and loaded via a binary file.
- The save file stores:
  - Current room number.
  - Player’s inventory (items and health potions).
  - Player’s stats (health, attack, defense).
  - Data is serialized in the same order for saving and loading.
  - When loading only room number is loaded and a new random room is created with same difficulty 

## Gameplay Flow
- The game runs on a recursive method called gameLoop.
- For each iteration:
- A new room is created, with the room number determining its difficulty.
- The room’s contents (mobs) are displayed to the player.
- The player engages in turn-based combat with the mobs until they are all defeated.
- If the room is a boss room, the player is rewarded with a random item upon victory.
- In non-boss rooms, the player heals and gains health potions after clearing the room.
- Once the room is cleared, the player moves randomly to another room.

## Installation
**Clone the Repository**  
   Download the project from GitHub:
   ```bash
   git clone https://github.com/FurkanCem/CLGame.git
   cd CLGame
   make
   ```
- For Windows run game.exe
- For Linux run ./game on shell
