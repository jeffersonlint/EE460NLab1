.ORIG  x4000

LOAD    add   r1, r1, #1
LOAD        BRzp  LOAD
        AND   r3, r2, r0
        halt
.END
