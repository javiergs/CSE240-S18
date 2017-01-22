(+ 8 (- 2 10))
(- (* 2 (+ 5 10 5)) 30)
(* 2 (+ (* 2 4) (+ 2 (* 0 5))))
(* 3 (+ 4 (/ (+ (* 6 6) (* 6 6)) (+ 10 2))))
(+ (/ (- (/ (/ (* (+ 4 6) (+ 6 4)) 2) 2) 5) 2) (+ (/ (+ (* 4 5) (* 5 4)) 2) (* 4 5)))

(newline)

(define zero 0)
(define two 2)
(define three 3)
(define four 4)
(define five 5)
(define six 6)
(define eight 8)
(define ten 10)
(define thirty 30)

(+ eight (- two ten))
(- (* two (+ five ten five)) thirty)
(* two (+ (* two four) (+ two (* zero five))))
(* three (+ four (/ (+ (* six six) (* six six)) (+ ten two))))
(+ (/ (- (/ (/ (* (+ four six) (+ six four)) two) two) five) two) (+ (/ (+ (* four five) (* five four)) two) (* four five)))

(newline)

(define (Add firstNum secondNum) (+ firstNum secondNum))

(newline)

(define Helper (lambda (x count)
                 (if (= count 0)
                     0
                 (Add x (Helper x (- count 1))))))

(define Square(lambda (x)
                (Helper (abs x) (abs x))))

(define ReadForSquare (lambda ()
                        (Square (read))))

(newline)


(define DiffSquares (lambda ()
                      (abs (- (Square (read)) (Square (read))))))

(newline)

(define AddLet (lambda (firstNum secondNum)
                (let ((x firstNum) (y secondNum))
                (+ x y))))