(define encrypt
  (lambda(str) ( let ((key (read))) (define character-encryption
       (lambda (ch)
         (if (or (char-alphabetic? ch) (char-numeric? ch)) (character-rotation ch)
             ch   )))
    (define character-rotation
      (lambda (ch) (integer->char (+ (char->integer ch) key) ))) ;this is where each char is being encrypted by incremented (ASCII) by the value given
      (list->string(map character-encryption (string->list str)))))) ; mapping

(define decrypt
  (lambda(str) ( let ((key (read))) (define character-encryption
       (lambda (ch)
         (if (or (char-alphabetic? ch) (char-numeric? ch)) (character-rotation ch)
             ch   )))
    (define character-rotation
      (lambda (ch) (integer->char (- (char->integer ch) key) ))) ;this is where each char is being encrypted by incremented (ASCII) by the value given
      (list->string(map character-encryption (string->list str)))))) ; mapping

;Test Cases
(encrypt "Hello CSE240!")
(decrypt "Khoor FVH573!")
