### 9/17: 

#### I. Circle by method of triangulation
The first step is to render a circle. The process works as follows. <br>

The intuition: <br>
Say you want to draw a circle on a canvas. The display only recognizes triangles. Say you draw a triangle with vertices: (0, 0), (50, 0), (0, 50). The graphics library can render better approximations of a circle with more pizza slices. <br>

Draw_Circle Function: <br>
The parameter cx, cy, and r is fed into the draw circle function. <br>
Draw triangles using the graphics library functions begin(triangle_fan), vertex(x,y), and end(). <br>
Use the following trigonometric identities cos(angle), sin(angle). <br>

<img src="media/Screenshot%202026-09-17%20at%201.22.08%E2%80%AFAM.png"
    alt="Constructing a Circle" width="400">



### 9/18:
#### II. Moving planets. 
The next step would be to implement movement. Planets accelerate and have velocity on top of their position coordinates. <br>

The intuition: <br>
Say you want to implement an acceleration and velocity feature every time the canvas updates. <br>
For each planet: <br>
Update velocity  = acceleration * dt; <br>
Update position = velocity * dt; <br>
Planet.position = updated position; <br>

<img src="media/Screenshot%202026-09-18%20at%2012.04.46%E2%80%AFAM.png"
     alt="Moving Planets" width="400">

#### III. 2D gravity. 
Planets don’t move linearly, they affect the planets around them given their relative distance and mass. This push and pull phenomenon is described by Newton's Orbital Mechanics. <br>

The intuition: <br>
Say we have the Sun and three other planets. We can describe the planet being moved as p and other planets as other. We can show the position of p after some dt as follows: <br>

set acceleration of x and y directions to 0. <br>
for every other planet p1, p2, p3… pn, not including our planet pi: <br>

first find the distance r <br>
dx = other.x - p.x; <br>
dy = other.y - p.y; <br>
r = sqrt(dx^ 2 + dy^2) <br>

calculate the acceleration (nudge) from every other planet and add it to ax and ay <br>
a = Gm/r^2 <br>
ax += a * (dx / r); <br>
ay += a * (dy / r); <br>

outside the for loop: <br>
nudge the planet's velocity for some delta t, and nudge the planet's position for some delta t to get our new and updated position with respect to a tiny change in time.  <br>

##### Newton's Orbital Mechanics (it’s a video)
<img src="media/2d-gravity-sim.gif"
     alt="2D gravity simulator" width="400">

observations: <br>
*planets fling out once they accelerate too close into the orbit <br>
*planets move faster the closer they get to the Sun <br>
*the Sun wobbles due to the gravitational pull of planets that are closer and have more mass! <br>




