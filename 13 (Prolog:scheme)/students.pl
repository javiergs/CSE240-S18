/* Facts */

status(sam, freshman).
status(jack, sophomore).

topic(sam, bio).
topic(sam, eng).
topic(jack, mat).
topic(jack, cse).

class(mat, calculus).
class(mat, algebra).
class(cse, algorithms).
class(cse, databases).
class(bio, taxonomy).
class(bio, evolution).
class(eng, reading).
class(eng, writing).

/* Rule */

/* Question 3.2 */
info(X,Y):-
    status(X,Y); topic(X,Y).

/* Question 3.3 */
schedule(X,Y):-
    topic(X,Z), class(Z,Y).

