foo(X,Y,Z):- Y < 1, Z is X.

foo(X,Y,Z):- X < 1, Z is Y.

foo(X,Y,Z):- (X > Y; X =:= Y),
F1 is X-2,
foo(F1, Y, Z2), 
Z is X + Z2.

foo(X,Y,Z):- X < Y,
F2 is Y-3,
foo(X, F2, Z1),
Z is Y + Z1. 
