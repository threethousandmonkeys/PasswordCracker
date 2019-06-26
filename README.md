# Password cracker

* If crack is run with no arguments, it should generate guesses, and test them against the SHA256 hashes. When it 􏰖nds one, it should print one line, consisting of the plaintext password, a space, and an integer 1-30 indicating which hash it matches. For example:

  abcd 3 

  Oops 5 

  adam 1 

  passwd 15 

This model is use for 􏰖finding passwords.  

- If crack is run with one integer argument, the argument speci􏰖es how many guesses it produce. In this mode, password guesses are printed to stdout, separated by newline characters (`\n'). 
- If crack is run with two argument, it treat the 􏰖rst as the 􏰖lename of a list of passwords (one per line), and the second as the 􏰖lename of a list of SHA256 hashes (in groups of 32 bytes, with no newline characters). It then test each of the passwords given in the 􏰖rst 􏰖le against each of the hashes given in the second 􏰖file, and produce output as for the case of no arguments. It print nothing else to stdout. 



My good guess approach:

1. First run common-word list (dictionary attack): this dictionary is filtered from common_list shared by Junhao Gan.
        -> very fast
        -> get 4 passwords
        -> total 4 pwds

2. Then use smart brute force. From the observation of the pwd4sha256 
decryption, togetther with counting character's frequency of 
"commom_password.txt", it's easy to found the way of smart brute force:

        -- smart brute force: 
        step 1: all generate by lower case abt
                    -> get 11 passwords, include 3 from common list
                    -> takes 190s, total 12 pwds
                    -> reach the requirment!!
        
        step 2: number together with lower case:
                    -> get extra 3 passwords, include 2 from comlist
                    -> takes 1000s, total 13 pwds
        
        step 3: use whole frequency list (generate by count_freq.py)
                    -> get 3 more
                    -> takes 5500s, total 16 pwds
