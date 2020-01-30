.ORIG x3000

      AND   R7, R7, #0
      ADD   R7, R7, #-8
      LSHF  R7, R7, #7
      ADD   R7, R7, #-12
      LSHF  R7, R7, #2  ;R7 contains x3050
LOOP  LDB   R1, R7, #0
      LDB   R2, R7, #1
      STB   R1, R7, #1
      STB   R2, R7, #0
      ADD   R7, R7, #2
      ADD   R0, R0, #-1
      BRnp  LOOP

      HALT

.END
