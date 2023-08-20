**Initial and final**
Each particles'simulation should be named with progressive numbers, e.g:
- the file containing the initial particles for each simulation is named `initial1.txt`, if you want to use the same particles for more than one simulation the file name should be `initialN1-N2.txt` etc.
- -its histograms are called `cHistoInit1-2.pdf` and `cHistoFin1-2.pdf` etc.
**Billiard's simulation**
Each billiard's simulation should be named with progressive numbers, e.g:
- `simulation1.txt` contains datas of the first simulation
- its graphs are called `cGraphsA1.pdf`, `cGraphsB1.pdf` and `cGraphC1.pdf`
- billiard's conditions are put in the following table (note that r_1 and r_2 values are considered also in the name of the canvas)

| Init. l | r_1 | r_2 | Init. y | Init. theta | Fin. l | Step | N |
| :---: | :---: | :---: | :---: | :---: |:---:| :---: | :---: |
| 13 | 5 | 3 | 1.5 $\pm$ 0.5 | -0.25 $\pm$ 0.5 | N.A. | N.A. | 100'000 |

When you commit changes:
- you should keep .txt file in .gitignore
- exclude .pdf from the .gitignore
