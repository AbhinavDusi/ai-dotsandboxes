# ai-dotsandboxes

Various approaches for the computer to play the game dots and boxes are implemented. 

# Game Description

The game starts with a grid of dots, and lines are drawn between the dots on successive turns by two players. 
A box formed upon drawing a line adds a point and another consecutive move for that player. 
When the grid is full, the player with the most points wins. 

## Random Player

The Random Player chooses a move by randomly selecting from the list of the valid moves remaining at any turn. 

## Algorithmic Player

The Algorithmic Player chooses a move by 

## Minimax Player

The Minimax Player chooses a move by employing a minimax algorithm, simulating its and its opponents'
future moves and choosing the optimal move by maximizing its score to a certain depth (implemented as a depth of 3).

## Deep Q Learning Player

The Deep Q Learning Player chooses a move by using a neural network to determine the max quality move
at each state, after being trained with thousands of training examples.

# To Run

```
make all
bin/main
```

# Data

Comparing win rates for every combination of Players.
