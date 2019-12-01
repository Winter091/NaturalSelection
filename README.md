# About
This is the really interesting project that allows you to see how the robot can evolve.

There's a grid that consist of cells. Each cell can be empty, or be a food, or be a wall.

Also there's a couple of robots on that grid that all can do some stuff.

Each robot has unique set of commands, its code.

Code is just an array of 64 integers. Each number in the code represent a command.

There are this set of commands:
- Walk in one of 8 directions
- Eat food that is placed around it
- Turn wall around it in a food
- Just get free HP

So, in each iteration each robot execute its commands consequently.

Also, robot lose 1 HP in each iteration, if it has 0 HP - it dies.

In first generation, the code for each robot is generated randomly;

In each next generation, that are starting when there are just a couple of most viable robots left,

robots that are created inherit the code that these remained robots have.

So, after some amount of generations, robots learn how to live longer!
