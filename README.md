# ai-dotsandboxes

Various approaches for the computer to play the game dots and boxes are implemented. 

# Game Description

The game starts with a grid of dots, and lines are drawn between the dots on successive turns by two players. 
A box formed upon drawing a line adds a point and another consecutive move for that player. 
When the grid is full, the player with the most points wins. 

In this implementation, the first move is random for all players, to avoid repitition.

## Random Player

The Random Player chooses a move by randomly selecting from the list of the valid moves remaining at any turn. 

## Algorithmic Player

The Algorithmic Player chooses a move by using the information of the grid size and whether it is the first or second player 
to move, to create optimal "chains."

## Minimax Player

The Minimax Player chooses a move by employing a minimax algorithm, simulating its and its opponents'
future moves and choosing the optimal move by maximizing its score to a certain depth (implemented as a depth of 3).

## Deep Q Learning Player

The Deep Q Learning Player chooses a move by using a neural network to determine the max quality move
at each state, after being trained with thousands of episodes.

# To Run

```
make all
bin/main
```

# Data

Comparing win rates and move times for every combination of Players.