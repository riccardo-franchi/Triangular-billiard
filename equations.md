
# Equations

## Particle
Every particle, after a collision, is described with the following parameters:
$$(x_i, y_i, \theta_i) $$

1. Initial trajectory of the particle:
$$y = \tan\theta\ x + y_0 $$
with $\theta$ the initial angle and $y_0$ initial position of the particle ($x_0 =0$).

2. Trajectory of a particle after a collision at point $(x_i, y_i)$:
$$y = \tan\theta_i\ (x-x_i) + y_i $$
therefore, after a collision we have:
$$y_{i+1} = \tan\theta_i\ (x_{i+1}-x_i) + y_i $$

## Generic Billiard
1. Particle's angle after a collision:
Upper wall:
$$\theta_{i+1} = -\theta_i + 2\alpha$$
Lower wall:
$$\theta_{i+1} = -\theta_i - 2\alpha$$
where $\alpha$ is the angle of the edge, that varies for each shape of the billiard, and all angles are referred to the $x$ axis.

## Straight line billiard
1. Equation of the upper wall:
$$y = \frac{r_2 - r_1}{l}\ x + r_1$$

2. Equation of the lower wall:
$$y = \frac{r_1 - r_2}{l}\ x - r_1$$

3. Equation for $x_{i+1}$ after a collision:  
Upper wall:
$$x_{i+1}=\frac{r_1+\tan\theta_i\ x_i-y_i}{\tan\theta_i+\frac{r_1-r_2}{l}}$$
Lower wall:
$$x_{i+1}=\frac{-r_1+\tan\theta_i\ x_i-y_i}{\tan\theta_i+\frac{r_2-r_1}{l}}$$

4. Equation for upper wall angle $\alpha$:
$$\arctan(\frac{r_2-r_1}{l})$$

## Statistics
1. Standard deviation
$$\sigma = \sqrt{\frac{1}{n-1}\sum{(x_i-\mu)^2}}$$

2. Skewness coefficient
$$b_1 = \frac{\frac{1}{n}\sum{(x_i-\mu)^3}}{\sigma^3}$$

3. Kurtosis coefficient
$$b_2 = \frac{\frac{1}{n}\sum{(x_i-\mu)^4}}{\sigma^4}$$  

Note that it can be useful to calculate the excess kurtosis $\gamma_2$, defined as $\gamma_2 = b_2 - 3$.  
