/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150	0,027s		1	
    200	0,081s		2
    300	0,253s		3
    400	0,634s		4
    800	4,631s		5
   1600	35,793s 	6
   3200	291,454s	7
   6400	2564,883s (uppskattat med kvot 8,8 beräknat utifrån de andra) 8
  12800	24366,390s (uppskattat med kvot 9,5 beräknat utifrån de andra) 9


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n⁴) då vi har 4 st for-loopar som alla kör ungefär N gånger för stora N i värsta fall.

Sortering:
FAST:
    
      N       fast brute       sortering
 ----------------------------------
    150	0,061s		1	
    200	0,062s		2
    300	0,093s		3
    400	0,115s		4
    800	0,342s		5
   1600	1,341s 	6
   3200	5,369s		7
   6400	22,356s 	8
  12800	97,028s	9 

ordo-uttrycket nu är O(n² log n) då vi har två nästlade for-loopar samt en sorteringsalgoritm på O(n log n)

