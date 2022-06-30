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

## Deep Q Learning Ensemble

The Deep Q Learning Ensemble takes the vote of a collection of Deep Q Learning Players, with each choosing a move by using a trained neural network to determine the max quality move at each state, after being trained with thousands of episodes. 

### Training Information

#### Hyperparameters

- Replay Memory Capacity: 5000
- Minibatch Size: 8
- Number of Episodes: 1000
- Learning Rate: 0.15
- Initial Exploration Rate: 0.94
- Exploration Rate Decay: 0.001
- Discount Factor: 0.89
- Target Update Frequency: 1
- Hidden Layer Size vs Input Layer Size Factor: 2

#### Topology

- Four layer neural network
- Input layer size corresponding to game board size
- Two hidden layers with 8 times input size
- Output layer size corresponding to game board size

#### Timing

```
DQL Player training time for 1000 episodes: 72 minutes.
```

# To Run

```
make all
bin/main
```

# Data

Comparing win rates and move times for every combination of Players. 
1,000 games are simulated on a 3x3 grid. 
The player who moves first or second is swapped after every game. 

## Random vs Random

```
Random Player 1 wins: 494
Random Player 2 wins: 506
Draws: 0
Total Games Played: 1000
Random Player 1 average time per move: 0.250731 microseconds.
Random Player 2 average time per move: 0.166459 microseconds.
```

## Random vs Algorithmic

```

```

## Random vs Minimax

```
Random Player 1 wins: 21
Minimax (depth=3) Player 2 wins: 979
Draws: 0
Total Games Played: 1000
Random Player 1 average time per move: 0.111012 microseconds.
Minimax (depth=3) Player 2 average time per move: 5356.56 microseconds.
```

## Random vs Deep Q Learning Ensemble

```

```

## Algorithmic vs Algorithmic

```

```

## Algorithmic vs Minimax

```

```

## Algorithmic vs Deep Q Learning Ensemble

```

```

## Minimax vs Minimax

```
Minimax (depth=3) Player 1 wins: 502
Minimax (depth=3) Player 2 wins: 498
Draws: 0
Total Games Played: 1000
Minimax (depth=3) Player 1 average time per move: 4375.64 microseconds.
Minimax (depth=3) Player 2 average time per move: 4380.78 microseconds.
```

## Minimax vs Deep Q Learning Ensemble

```

```

## Deep Q Learning Ensemble vs Deep Q Learning Ensemble

```

```
