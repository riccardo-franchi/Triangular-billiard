## Naming convention
Each graph is named with progressive numbers, e.g, for the 1st simulation, its graphs are called `cGraphsA1.pdf`, `cGraphsB1.pdf` and `cGraphC1.pdf`.

Billiard's initial conditions are put in the following table (note that $r_1$ and $r_2$ values are considered also in the name of the canvas)

| Simulation  | $\ell_i$ | $r_1$ | $r_2$ | $y_0$ | $\theta_0$ | $\ell_f$ | Step | N | Comment |
| :---: | :---: | :---: | :---: | :---: | :---: |:---:| :---: | :---: | :---: |
| 1  | 1 | 5 | 3 | 1.5 $\pm$ 0.5 | -0.25 $\pm$ 0.5 | 40 | 1.5 | 100'000 | General with $\alpha$ < 0 |
| 3 | 20 | 4 | 6 | -0.75 $\pm$ 1.5 | 0 $\pm$ 0.25 | - | - | 100'000'000 | - |
| 5 | 10 | 2 | 6 | 1.2 $\pm$ 0.7 | 0.8 $\pm$ 1.1 | 1500 | 0.1 | 100'000| $\alpha$ > 0 & $l_f$ very big |
| 6 | 10 | 7 | 4 | 0.5 $\pm$ 2.1 | 0.4 $\pm$ 1.3 | 1500 | 0.2 | 10'000 | $\alpha$ < 0 & $l_f$ very big |
| 7 | 15 | 4 | 4 | 3.2 $\pm$ 0.2 | -1.1 $\pm$ 0.4 | 45 | 0.1 | 20'000 | $\alpha$ = 0 |
| 8 | 3 | 4 | 0.2 | -1 $\pm$ 0.8| -0.7 $\pm$ 0.5 | 10 | 0.05 | 100'000 | $\alpha$ << 0 |
| 9 | 10 | 5 | 4 | 2.5 $\pm$ 1 | 1 $\pm$ 0.5 | 200 | 0.05 | 50'000 | $\ell_f$ $\simeq$ 150 to study $\sigma$ |
| 10 | 250 | 50 | 2 | 1.5 $\pm$ 2 | 0.2 $\pm$ 0.1 | - | - | 50'000'000 | - |
| 11 | 5'000  | 200 | 15 | 150 $\pm$ 20 | -0.5 $\pm$ 0.4 | - | - | 200'000'000 | - |
| 13 | 1 | 1 | 1 | 1 $\pm$ 1 | 1 $\pm$ 1 | 100 | 1 | 10'000 | $\alpha$ = 0 & $l_f$ very big |

> Note that:
> - Initial and Final $\ell$ are the lenghts used in the simulation
> - We should avoid repeating the same type of simulation
> - The cases studied should be as varied as possible.

---

Considerations (varying $\ell$ ):
- skewness goes to 0, while kurtosis to a fixed value, always (from what we have seen)
- same thing for mean, which goes to 0, and st. dev., which tends to a fixed value.
- correlation between $\sigma_0$ and $\sigma_f$ ????
- st. dev. has a spike for low $\ell$ (less than 100/50), sometimes only $\sigma_{\theta}$, some other times both.
    - confirmed by 3 simulations

Considerations (normal simulation):
- histo of sim. #10 is VERY interesting ($\theta_f$ pseudo-periodicity)
