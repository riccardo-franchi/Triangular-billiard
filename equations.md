# Notes

- Every particle can be described with the following parameters:
$$(x_i, y_i, \theta_i) $$

- We don't have to consider the mass of the particles, as we are consiering no friction


## Equations

1. Equation of the upper edge:
$$y = \frac{r_2 - r_1}{l}\ x + r_1$$

2. Equation of the lower edge:
$$y = \frac{r_1 - r_2}{l}\ x - r_1$$

3. Initial trajectory of the particle:
$$y = \tan\theta\ x + y_0 $$

with $\theta$ the initial angle and $y_0$ initial position of the particle ($x_0 =0$).

4. Trajectory of a particle after a collision at point $(x_i, y_i)$:
$$y = \tan\theta_i\ (x-x_i) + y_i $$

5. Equation for $x_{i+1}$ after a collision:

Upper wall:
$$x_{i+1}=\frac{r_1+\tan\theta_i\ x_i-y_i}{\tan\theta_i+\frac{r_1-r_2}{l}}$$

Lower wall:
$$x_{i+1}=\frac{-r_1+\tan\theta_i\ x_i-y_i}{\tan\theta_i+\frac{r_2-r_1}{l}}$$

6. Equation for $y_{i+1}$ after a collision:

Equation (4):
$$y_{i+1} = \tan\theta_i\ (x_{i+1}-x_i) + y_i $$

7. Theta after a collision

Upper wall:
$$\theta_{i+1} = -\theta_i + 2\alpha$$

Lower wall:
$$\theta_{i+1} = -\theta_i - 2\alpha$$

where $\alpha$ is the angle of the edge, defined as $\arctan(\frac{r_2-r_1}{l})$, and all angles are referred to the $x$ axis.