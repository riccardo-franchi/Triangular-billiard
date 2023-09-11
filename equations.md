
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
1. Particle's angle after a collision with elastic collisions:
Upper wall:
$$\theta_{i+1} = -\theta_i + 2\alpha$$
Lower wall:
$$\theta_{i+1} = -\theta_i - 2\alpha$$
where $\alpha$ is the angle of the edge, that varies for each shape of the billiard, and all angles are referred to the $x$ axis.

2. Particle's angle after a collision with partially inelastic collisions:  
Upper wall:
$$\theta_{i+1} = \alpha - \frac{\pi}{2}+\arctan(\frac{1}{e} \tan(\frac{\pi}{2}-\theta_i+\alpha))$$
Lower wall:
$$\theta_{i+1} = -\alpha + \frac{\pi}{2}+\arctan(\frac{1}{e} \tan(\frac{\pi}{2}-\theta_i-\alpha))$$
where $e$ is the coefficient of restitution, $\alpha$ is the angle of the edge, that varies for each shape of the billiard, and all angles are referred to the $x$ axis.

## Straight line billiard
1. Equation of the upper wall:
$$y = \frac{r_2 - r_1}{\ell}\ x + r_1$$

2. Equation of the lower wall:
$$y = \frac{r_1 - r_2}{\ell}\ x - r_1$$

3. Equation for $x_{i+1}$ after a collision:  
Upper wall:
$$x_{i+1}=\frac{r_1+\tan\theta_i\ x_i-y_i}{\tan\theta_i+\frac{r_1-r_2}{\ell}}$$
Lower wall:
$$x_{i+1}=\frac{-r_1+\tan\theta_i\ x_i-y_i}{\tan\theta_i+\frac{r_2-r_1}{\ell}}$$

4. Equation for upper wall angle $\alpha$:
$$\alpha=\arctan{\frac{r_2-r_1}{\ell}}$$

## Parabolic billiard
For simplicity, let 
$$k = \frac{2(r_1-r_2)}{\ell}$$

1. Equation of the upper wall:
$$y=\frac{k}{2\ell} x^2 -kx+r_1$$

2. Equation of the lower wall:
$$y=-\frac{k}{2\ell} x^2 +kx-r_1$$

3. Equation for $x_{i+1}$ after a collision:  
For simplicity, let 
$$m =\tan\theta_i$$
Upper wall:
$$x_{i+1}=\frac{k+m-\sqrt{(k+m)^2-2\frac{k}{\ell}(mx_i+r_1-y_i)}}{\frac{k}{\ell}}$$
Lower wall:
$$x_{i+1}=\frac{k-m-\sqrt{(k-m)^2+2\frac{k}{\ell}(mx_i-r_1-y_i)}}{\frac{k}{\ell}}$$

5. Equation for upper wall angle $\alpha$:
$$\alpha=\arctan(\frac{k}{\ell}(x_{i+1}-\ell))$$

## Semicircular Billiard
For simplicity, let 
$$R = \frac{\ell^2+(r_1-r_2)^2}{2(r_1-r_2)}.$$

1. Equation of the upper wall:
$$y=R+r_2-\sqrt{R^2-x^2-\ell^2+2\ell x}$$

2. Equation of the lower wall:
$$y=-R-r_2+\sqrt{R^2-x^2-\ell^2+2\ell x}$$

3. Equation for $x_{i+1}$ after a collision:  
For simplicity, let 
$$m =\tan\theta_i$$
Upper wall:  
Let
$$k =R+r_2-y_i+mx_i$$
Lower wall:  
Let
$$k =-R-r_2-y_i+mx_i$$
Hence, for both walls:
$$x_{i+1}=\frac{l+mk-\sqrt{(l+mk)^2-(m^2+1)(k^2-R^2+\ell^2)}}{m^2+1}$$

5. Equation for upper wall angle $\alpha$:
$$\alpha=\arctan{\frac{x_{i+1}-\ell}{R+r_2-y_{i+1}}}$$

## Statistics
1. Standard deviation
$$\sigma = \sqrt{\frac{1}{n-1}\sum{(x_i-\mu)^2}}$$

2. Skewness coefficient
$$b_1 = \frac{\frac{1}{n}\sum{(x_i-\mu)^3}}{\sigma^3}$$

3. Kurtosis coefficient
$$b_2 = \frac{\frac{1}{n}\sum{(x_i-\mu)^4}}{\sigma^4}$$  

Note that it can be useful to calculate the excess kurtosis $\gamma_2$, defined as $\gamma_2 = b_2 - 3$.  
