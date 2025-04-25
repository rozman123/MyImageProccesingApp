PROTOTYP !!! Niema jescze zaimplementowanej obsługi błędów!!

Próba stworzenia aplikacji okienkowej do przetwarzania obrazów.

Zrealizowane funkcje:


Load Image - Ładowanie obrazu
Negative - Negatyw
Grey Scale - Zamiana koloru obrazu na GrayScale
Histogram - Generuje Histogram
Stretching - Rozciąganie Histogramu
Wyrównanie - Wyrównanie Histogramu
Brightnes - Jasność Należy podać w polu pod Gamma wartość
Contrast - Jasność Należy podać w polu pod Gamma wartość
Gamma - Jasność Należy podać w polu pod Gamma wartość

Rozmycie Równomierne - w rozmyciu równomiernym należy podać 
po lewej rozmiar maski (liczba nieparzysta) a po prawej liczbe od 0 do 2
(Wypełnienie pixeli dookoła obrazu w celu zapewnienia jakiegoś 
wypełninia dla maski gdy ta skanuje pixele przy krawędziach) 
gdzie:
0 -  cyklicznie
1 -  czarne pixele
2 -  powtórzenie pixeli przykrawędzoiwych

Rozmycie Gausowskie - należy podać wartość maski i wypełnienie przykrawędziowych pixeli
(patrz Rozmycie Równomierne) i pole nad Rozmyciem Gausowskim które oznacza sigme.