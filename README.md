# About
This is the really interesting project that allows you to see how the living cell can evolve.

There's a grid that consist of cells. Each cell can be empty, or be a food, or be a wall.

Also there's a couple of living cells (robots henceforth) on that grid that all can do some stuff.

Each robot has unique set of commands, its code.

Code is just an array of 64 integers. Each number in the code represents a command.

There are this set of commands:
- Walk in one of 8 directions
- Eat food that is placed around it
- Turn wall around it in a food
- Just get free HP

So, in each iteration each robot executes its commands consequently.

Also, robot loses some amount of HP each iteration, death occurs at 0 HP.

In first generation, the code for each robot is generated randomly;

In each next generation, that are starting when there are just a couple of most viable robots left,

robots that are created inherit the code that these most viable robots had.

So, after some amount of generations, robots learn how to live longer!

**Sadly, the project haven't gone very far. It lacks variety of commands/objects on the grid/interesting mechanics.**

**I'm too lazy to sit here and develop new ways of robots' interaction.**
