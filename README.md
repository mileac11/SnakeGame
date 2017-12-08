Tema Joc Matrice
Milea Carmen 244

Denumire joc: Snake 
Elemente conexe necesare: Joystick, LCD

Structurare

1. Initial, pe matrice apar succesiv litere din cuvantul "snake", iar pe LCD este afisat mesajul "Make any move to play".
Astfel, dupa ce din joystick se face o miscare sus/jos/stanga/dreapta, pe matrice va fi afisa un countdown (3,2,1), dupa care jocul propriuzis va incepe.

2. Initial, lungimea sarpelui va fi egala cu 1 si se va misca intr-o directie random (jos/sus/stanga/dreapta), iar pe matrice va aparea totodata primul "candy". 
   Initial, pe LCD va fi afisat scorul actul(0), precum si highscorul.

3. Scopul jucatorului este de a suprapune primul led al sarpelui cu ledul "candy"-ul. Dupa o astfel de miscare, lungimea sarpelui se va incrementa, scorul curent va creste cu o unitate, iar pe ecran se va afisa un nou "candy" pe o pozitie care sa nu coincida cu niciun led al sarpelui. 

4. De fiecare data cand lungimea sarpelui este divizibila cu 5, viteza cu care acesta se deplaseaza va creste, marind astfel dificultatea jocului. Totodata, pe masura ce lungimea sarpelui creste, dificultatea va creste proportional.

5. Daca scorul curent al jucatorului depaseste highscore-ul curent (ex: scor actual = 5, highscore = 4), highscore-ul se modifica in timp real (si nu dupa ce jocul s-a terminat),

6. Jocul se incheie atunci cand primul led al sarpelui se suprapune cu oricare alt led al sarpelui (diferit de primul).

7. Dupa ce jocul s-a terminat, exista 2 scenarii:
	a) daca jocatorul a depasit highscorul care era la momentul in care jocul a inceput pe matrice se afiseaza un "happy face", iar pe LCD mesajul "new highscore" urmat de scorul obtinut
	b) in caz contrar, pe matrice se afiseaza un "sad face", iar pe LCD mesajul "nice try" urmat de scorul obtinut

8. Dupa 3 secunde, jocul ajunge in starea initiala si userul se poate juca din nou procedand ca in prima instanta.

9. Scorul maxim care poate fi obtinut de un user este 64 (numarul de leduri de pe matrice), scor greu realizabil.
 
