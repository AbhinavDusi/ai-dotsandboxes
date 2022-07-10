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

The Algorithmic Player chooses a move by following a specific strategy at each game state.

### Chains

#### Unopened Chain 

Strings of boxes in which any move results in the opponent scoring (Has boxes enclosed by two lines). 

#### Opened Chain

Strings of boxes in which a move is available to take a box (Has a box(es) enclosed by three lines connected to ones enclosed by two or three lines).

#### Unchained Boxes

Boxes that have not been taken by either player and are not art of unopened or opened chains. 

#### Double Cross Strategy

When taking a chain of opened boxes, the last two boxes may be left for the opponent. The opponent may greedily take those two boxes, but is forced to open, or draw a line in, an unopened chain on the next forced move, allowing the first player using this strategy to get even more boxes.

#### Overall Strategy

The game is considered to be in these eight possible states and moves accordingly (* = terminal state).

```
├── There are no Unchained Boxes
|   ├── There are no Open Chains 
|   |   └── Move in the smallest Half-Open Chain *
|   └── There are Open Chains
|       ├── There are no Half-Open Chains
|       |   └── Take an Open Chain *
|       └── There are Half-Open Chains
|           ├── There is one Open Chain
|           |   ├── Open Chain's Length is 2
|           |   |   ├── Smallest Half-Open Chain's Length is <= 2
|           |   |   |   └── Take the Open Chain *
|           |   |   └── Smallest Half-Open Chain's Length is > 2
|           |   |       └── Double Cross Strategy in the Open Chain *
|           |   └── Open Chain's Length is not 2
|           |       └── Take the Open Chain *
|           └── There are mutliple Open Chains
|               └── Take the smallest Open Chain * 
└── There are Unchained Boxes
    ├── There are no Open Chains 
    |   └── Move in an Unchained Box * 
    └── There are Open Chains
        └── Take an Open Chain * 
```

## Minimax Player

The Minimax Player chooses a move by employing a minimax algorithm, simulating its and its opponents' future moves and choosing the optimal move by maximizing its score to a certain depth (implemented as a depth of 3). Alpha beta pruning is for optimization. 

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
- Number of Deep Q Learning Players in each Ensemble: 25

#### Topology

- Four layer neural network
- Input layer size corresponding to game board size
- Two hidden layers with 2 times input size
- Output layer size corresponding to game board size

# To Run

```
make
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
Total Games Played: 1000
Random Player 1 average time per move: 0.250731 microseconds.
Random Player 2 average time per move: 0.166459 microseconds.
```

## Random vs Algorithmic

```
Random Player 1 wins: 1
Algorithmic Player 2 wins: 999
Total Games Played: 1000
Random Player 1 average time per move: 0.119062 microseconds.
Algorithmic Player 2 average time per move: 8.84918 microseconds.
```

## Random vs Minimax

```
Random Player 1 wins: 21
Minimax (depth=3) Player 2 wins: 979
Total Games Played: 1000
Random Player 1 average time per move: 0.111012 microseconds.
Minimax (depth=3) Player 2 average time per move: 5356.56 microseconds.
```

## Random vs Deep Q Learning Ensemble

```
Deep Q Learning Ensemble 2 training time: 53 minutes.
Random Player 1 wins: 181
Deep Q Learning Ensemble Player 2 wins: 819
Total Games Played: 1000
Random Player 1 average time per move: 0.0220504 microseconds.
Deep Q Learning Ensemble Player 2 average time per move: 4182.78 microseconds.
```

## Algorithmic vs Algorithmic

```
Algorithmic Player 1 wins: 508
Algorithmic Player 2 wins: 492
Total Games Played: 1000
Algorithmic Player 1 average time per move: 9.3138 microseconds.
Algorithmic Player 2 average time per move: 10.1969 microseconds.
```

## Algorithmic vs Minimax

```
Algorithmic Player 1 wins: 935
Minimax (depth=3) Player 2 wins: 65
Total Games Played: 1000
Algorithmic Player 1 average time per move: 11.4154 microseconds.
Minimax (depth=3) Player 2 average time per move: 5599.99 microseconds.
```

## Algorithmic vs Deep Q Learning Ensemble

```
Deep Q Learning Ensemble 2 training time: 44 minutes.
Algorithmic Player 1 wins: 1000
Deep Q Learning Ensemble Player 2 wins: 0
Total Games Played: 1000
Algorithmic Player 1 average time per move: 13.7564 microseconds.
Deep Q Learning Ensemble Player 2 average time per move: 4004.14 microseconds.
```

## Minimax vs Minimax

```
Minimax (depth=3) Player 1 wins: 502
Minimax (depth=3) Player 2 wins: 498
Total Games Played: 1000
Minimax (depth=3) Player 1 average time per move: 4375.64 microseconds.
Minimax (depth=3) Player 2 average time per move: 4380.78 microseconds.
```

## Minimax vs Deep Q Learning Ensemble

```
Deep Q Learning Ensemble 2 training time: 44 minutes.
Minimax (depth=3) Player 1 wins: 801
Deep Q Learning Ensemble Player 2 wins: 199
Total Games Played: 1000
Minimax (depth=3) Player 1 average time per move: 4858.96 microseconds.
Deep Q Learning Ensemble Player 2 average time per move: 4006.28 microseconds.
```

## Deep Q Learning Ensemble vs Deep Q Learning Ensemble

```
Deep Q Learning Ensemble 1 training time: 40 minutes.
Deep Q Learning Ensemble 2 training time: 40 minutes.
Deep Q Learning Ensemble Player 1 wins: 554
Deep Q Learning Ensemble Player 2 wins: 446
Total Games Played: 1000
Deep Q Learning Ensemble Player 1 average time per move: 3394.2 microseconds.
Deep Q Learning Ensemble Player 2 average time per move: 3374.62 microseconds.
```

# Future Improvements

- Minimax Player could have better optimization, by taking into account symmetry and previously explored game states. 

- Deep Q Learning Ensemble could be trained with better hyperparameters or learning model to achieve higher win rates. 

- Algorithmic Player could employ many other strategies, such as making sacrifices, to ensure optimal play on larger boards. 