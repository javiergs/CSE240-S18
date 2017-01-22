/* Facts */
male(kam).
male(rob).
male(dom).
male(dag).
male(jeb).
male(tio).
male(zev).
male(gio).

female(ana).
female(sue).
female(kat).
female(syd).
female(may).
female(pam).
female(fey).
female(liz).

father_of(kam, rob). /* kam is the father of rob */
father_of(kam, syd). /* kam is the father of syd */
father_of(rob, dom). /* rob is the father of dom */
father_of(rob, kat). /* rob is the father of kat */
father_of(jeb, tio). /* jeb is the father of tio */
father_of(jeb, pam). /* jeb is the father of pam */
father_of(tio, dag). /* tio is the father of dag */
father_of(tio, fey). /* tio is the father of fey */
father_of(zev, liz). /* zev is the father of liz */
father_of(zev, gio). /* zev is the father of gio */

mother_of(ana, rob). /* ana is the mother of rob */
mother_of(ana, syd). /* ana is the mother of syd */
mother_of(sue, kat). /* sue is the mother of kat */
mother_of(sue, dom). /* sue is the mother of dom */
mother_of(syd, dag). /* syd is the mother of dag */
mother_of(syd, fey). /* syd is the mother of fey */
mother_of(may, tio). /* may is the mother of tio */
mother_of(may, pam). /* may is the mother of pam */
mother_of(pam, liz). /* pam is the mother of liz */
mother_of(pam, gio). /* pam is the mother of gio */

/* Rules */

/* Question 2.1 */
is_male(X):-
    male(X);
    father_of(X,_).

/* Question 2.2 */
is_female(X):-
    female(X);
    mother_of(X,_).

/* Question 2.3 */
parent_of(X,Y):-
    father_of(X,Y);
     mother_of(X,Y).

/* Question 2.4 */
sibling_of(X, Y):-
    parent_of(Z,X), parent_of(Z,Y).

/* Question 2.5 */    
grandmother_of(X, Z):-
    mother_of(X,Y), (mother_of(Y, Z);
    father_of(Y,Z)).

grandfather_of(X, Z):-
    father_of(X, Y), (mother_of(Y,Z);
    father_of(Y,Z)).

/* Question 2.6 */
descendent_of(X, Y):-
    parent_of(Y, X).
descendent_of(X, Y):-
    parent_of(Z, X), descendent_of(Z, Y).
