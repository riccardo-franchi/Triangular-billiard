# progetto2023

# Biliardo triangolare

## Descrizione del sistema

Il sistema è delimitato da due segmenti rettilinei, i cui estremi
sono definiti dai punti $[(0, r_1), (\ell, r_2)]$ e 
$[(0, -r_1), (\ell, -r_2)]$ rispettivamente.

Una particella puntiforme inizia a muoversi, con velocità costante,
lungo la direzione descritta dall'angolo $\theta_0$.
Tale particella parte da $(0, y_0)$, $y_0 \in [-r_1, r_1]$, 
e interagisce nel punto $(x_\mathrm{i}, y_\mathrm{i})$ con uno
dei due segmenti di delimitazione (ne caso descritto in figura, 
con quello superiore).
L'interazione consiste in una riflessione (urto elastico), per cui 
$\theta_\mathrm{i} = \theta_\mathrm{r}$, dove $\theta_\mathrm{i}$ e 
$\theta_\mathrm{r}$ rappresentano rispettivamente gli angoli \
incidente e riflettente.

Si noti come la direzione normale al segmento non dipende dalle 
coordinate del punto incidente $(x_\mathrm{i}, y_\mathrm{i})$.
L'equazione della traiettoria, dopo un dato urto, è quindi data 
dalla seguente relazione:

$$
y = \mp \frac{\ell}{(r_2-r_1)} ( x - x_\mathrm{i} ) + y_\mathrm{i}
$$

dove i segni ($\mp$) si riferiscono ad'urti contro al segmento
superiore ($-$) o inferiore ($+$) rispettivamente.

## Obiettivo

Progettare e sviluppare un codice che calcoli la traiettoria di una particella
all'interno del sistema sopradescritto, quando questa parte dalle coordinate
iniziali $(x = 0, y_0)$, e si muove lungo la traiettoria definita dall'angolo
$\theta_0$. 

Il programma deve offrire le seguenti funzionalità:

- date le coordinate iniziali relative alla simulazione di una singola particella,
  il programma deve determinare le coordinate "finali", cioè quelle relative alla
  posizione $(x=\ell, y_\mathrm{f})$, così come l'angolo $\theta_\mathrm{f}$ che
  definisce la direzione del moto della particella in all'uscita del biliardo;
- supponendo che le condizioni iniziali siano caratterizzate da due distribuzioni
  Gaussiane indipendenti, rispettivamente definite dai parametri $(\mu_{y_0}, \sigma_{y_0})$
  e $(\mu_{\theta_0}, \sigma_{\theta_0})$ , il programma deve determinare (generando
  un numero programmabile $N$ di simulazioni del moto di una singola particella)
  le distribuzioni di $y_\mathrm{f}$ e $\theta_\mathrm{f}$ e calcolarne, media,
  deviazione standard, coefficiente di simmetria e di appiattimento.

Infine, studiare (e documentare nella relazione) come variano le distribuzioni al
variare di $\ell$, qualora si mantengano costanti $r_1$ e $r_2$.
