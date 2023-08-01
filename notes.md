# Notes

## Project structure

We want to have a class `Billiard` that handles the main functionality of the simulation:
1. Storing the coordinates of the two walls
2. Storing all the particles
3. Calculating the trajectory of the particle (calculation every collision for every particle)

We than have a class that handles the calculation the stats of the simulation.

### 1. Storing the coordinates of the two walls

The simplest approach is to store the three parameters $r_1, r_2, l$ as members of the class (we will eventually consider in a second moment whether to use a specific class for the walls or not).


### 2. Storing all the particles

The first approach is to handle a single particle (`Particle m_particle`) as a member of class `Billiard`, and then proceeding to point 3. To do that, we must define a header-only class `Particle`. 

After that we have set that up working correctly we can proceed to the next step, which is to handle multiple particles (`std::vector<Particle> m_particles`).


### 3. Calculating the trajectory of the particles 

To calculate the final trajectory of the particle we need to calculate the trajectory of the particle after every collision. We first use a private method `bool willCollide()`. This method will return `true` if the particle collides with the wall, `false` if the particle doesn't collide with any wall: now we can determine its final position and angle with the private method `void calcTrajectory()`.

We may use a public method `void runSimulation()`, that calls `willCollide()` and `calcTrajectory()` for every particle until it eventually returns `false`, at that point we determine its final angle and position.
