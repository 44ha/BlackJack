# Blackjack (C++)

Console Blackjack game. Full 52-card deck, betting system, dealer AI, and ASCII card rendering.

## Features

- Full 52-card deck that persists across rounds until depleted / low (not reset every hand)
- Unicode suit symbols (♠ ♥ ♦ ♣) with ASCII card art
- Ace value adjustment (11 to 1 when hand exceeds 21)
- Chip-based betting starting at 1000 chips
- Dealer hits until 17, hides second card until player stands
- Win / lose / bust / tie detection, play multiple rounds

## Build

```bash
g++ -std=c++11 -o blackjack BlackJack.cpp
./blackjack
```

## How to play

You start with 1000 chips. Each round, place a bet, then choose to hit (`h`) or stand (`s`). If you go over 21 you bust. Dealer plays after you stand, must hit until 17+. Highest hand wins.

## Example

```
You have 1000 chips.
Place your bet: 200

Player's Hand:
+-----+ +-----+
|  10  | |  A  |
|  ♠   | |  ♥  |
+-----+ +-----+
Total: 21

Dealer's Hand:
+-----+
|  K  |
|  ♦  |
+-----+
 ??

Do you want to (h)it or (s)tand? s
Player wins!
```
