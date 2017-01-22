(define Ackermann (lambda (s t) ; Size - n problem
                    (if (= s 0) (+ t 1) ; Stopping condition and return value
                        (if (and (> s 0) (= t 0)) ; Construction size - n solution from size - m definition.
                            (Ackermann (- s 1) 1) ; Size - m problem
                                      (if (and (> s 0) (> t 0)) 
                                          (Ackermann (- s 1) (Ackermann s (- t 1)))))))) ; Size - m problem
(Ackermann 0 0)
(Ackermann 1 1)
(Ackermann 2 3)
(Ackermann 3 4)
(Ackermann 3 7)

(newline)

(define (alternate lst1 lst2 lst3) ; Size - n problem
                    (if (or (null? lst1) (null? lst2) (null? lst3)) '() ; Stopping condition and return value
                        (append (list (car lst1)) (list (car lst2)) (list (car lst3)) (alternate (cdr lst1)(cdr lst2)(cdr lst3))))) ; Construction size - n solution from size - m definition. && Size - m problem

(alternate '(1 2 3) '(a b c) '(m n o))

(newline)

(define (pairs lst1 lst2) ; Size - n problem
                (if (or (null? lst1) (null? lst2)) '() ; Stopping condition and return value
                    (append (list (cons (car lst1) (car lst2))) (pairs (cdr lst1)(cdr lst2))))) ; Construction size - n solution from size - m definition. && Size - m problem

(pairs '(1 2 3) '(a b c))

(newline)

(define (sumOdds lst)
                (if (null? lst) 0
                   (if (= (modulo (car lst) 2) 1)
                       (+ (car lst) (sumOdds (cdr lst)))
                       (sumOdds (cdr lst)))))

(sumOdds '(1 3 4 5 6 -7))

(newline)

((lambda (lst)
  (sumOdds lst)) 
   '(1 3 4 5 6 -7))

(newline)
   
(define (helper lst z)
          (if (null? lst) (display z)
          (if (< z (car lst)) (helper (cdr lst) (car lst)) (helper (cdr lst) z))))

(define (findMax lst)
          (if (null? lst) (display "empty list")
          (helper lst (car lst))))

(findMax '(1 5 20 -2 10))

(newline)