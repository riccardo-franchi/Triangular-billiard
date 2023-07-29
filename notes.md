# Notes
- Every point can be described as a vector $v$ with four components ($v \in \mathbb{R}^4$), two of them describing the position and two the velocity:
$$(x_i, y_i, v_{x_i}, v_{y_i}) $$

- We don't have to consider the mass of the particles, as we are consiering no friction


## Equations

1. Equation of the upper edge:
$$y = \frac{r_2 - r_1}{l}\ x + r_1$$
2. Equation of the lower edge:
$$y = -\frac{r_2 - r_1}{l}\ x - r_1$$

3. Initial trajectory of the particle:
$$ y = \frac{v_y}{v_x}\ x + y_0$$
with $v_x$, $v_y$ components of the initial velocity and $y_0$ initial position of the particle ($x_0 =0$).

5. Position of the first collision of a particle (with $v_y>0$):
\[ x = \frac{r_1-y_0}{\frac{v_y}{v_x}+\frac{r_1-r_2}{l}} \quad y=\frac{v_y}{v_x}\ x + y_0 \]
obtained by considering equations (1) and (3).

6. Trajectory of the particle after the $i$-th collision:
\[ y = \mp \frac{l}{r_2-r_1}\ (x - x_i) + y_i \quad (\bigstar) \]
check this equation! It's odd that the angular coefficient is not influenced by the direction of the particle.
