(define (foo x y)
(if (<= y 0)
    x
(if (<= x 0)
    y
(if (>= x y)
    (+ x (foo (- x 2) y))
    (+ y (foo x (- y 3)))))))

