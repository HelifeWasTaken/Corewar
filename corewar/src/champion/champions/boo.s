.name "Boo"
.comment "defense"

start:
	live %667
    sti r2, %:brute, r9
    ld %46446, r3
    zjmp %:main
  

brute:
	live %6
    live %66
    zjmp %:start
    ld	%12, r3
    ld	%12, r3
    ld	%12, r3
    ld	%12, r3
    ld	%12, r3
    fork %334
    zjmp %:tower

tower:
	live %33
    live %69
	zjmp	%:main
  

main:
	fork %483
    ldi %52, %45, r4
    ld	%12, r4
    ld	%12, r4
    ld	%12, r5
    ld	%1, r5
    ld	%1, r5
    st	r4, 360
    st	r5, 44
    fork %44
    live %99
	zjmp %:ajax

ajax:
	live %667
    fork %55
    live %89
    fork %22
    zjmp %:brute