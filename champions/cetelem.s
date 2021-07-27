
.name		"cetelem"
.comment	"il suffit pas de ressembler à cetelem pour faire du cetelem"

start:
	lfork	%2048
	sti		r1, %:ekip, %1
	sti		r1, %:osirus, %1
	sti		r1, %:osirus, %16
	sti		r1, %:freeze, %1
	sti		r1, %:norsacce, %1
	st		r2, -14
	st		r2, -13

ekip:
	live	%53165
	st		r2, -10
	st		r2, -15
	st		r2, -24
	st		r2, -33
	st		r2, -42
	st		r2, -51
	st		r2, -60
	st		r2, -69
	st		r2, -78
	st		r2, -87
	st		r2, -96
	st		r2, -105
	st		r2, -114
	st		r2, -123
	st		r2, -132
	st		r2, -141
	st		r2, -150
	st		r2, -159
	st		r2, -168
	st		r2, -177
	st		r2, -186
	st		r2, -195
	st		r2, -204
	st		r2, -213
	st		r2, -222
	st		r2, -231
	st		r2, -240
	st		r2, -249
	st		r2, -258
	st		r2, -267
	st		r2, -276
	st		r2, -285
	st		r2, -294
	st		r2, -303
	st		r2, -312
	st		r2, -321
	st		r2, -330
	st		r2, -339
	st		r2, -348
	st		r2, -357
	st		r2, -366
	st		r2, -375
	st		r2, -384
	st		r2, -393
	st		r2, -402
	st		r2, -411
	st		r2, -420
	st		r2, -429
	st		r2, -438
	st		r2, -447
	st		r2, -456
	st		r2, -465
	st		r2, -474
	st		r2, -483
	st		r2, -492
	st		r2, -501
	st		r2, -510
	st		r2, -519
	st		r2,	-528
	st		r2,	-537
	zjmp	%:ekip
	ld		%0, r2

osirus:
	live	%654664
	ld		%0, r2
	fork	%:ekip
	live	%354534
	fork	%:freeze
	zjmp	%:osirus

freeze:
	live	%65468435
	ld		%0, r2
	st		r2, 510
	st		r2, 500
	st		r2, 490
	st		r2, 480
	st		r2, 470
	st		r2, 460
	st		r2, 450
	st		r2, 440
	st		r2, 430
	st		r2, 420
	st		r2, 410
	st		r2, 400
	st		r2, 390
	st		r2, 380
	st		r2, 370
	st		r2, 360
	st		r2, 350
	st		r2, 340
	st		r2, 330
	st		r2, 320
	st		r2, 310
	st		r2, 300
	st		r2, 290
	st		r2, 280
	st		r2, 270
	st		r2, 260
	st		r2, 250
	st		r2, 240
	st		r2, 230
	st		r2, 220
	st		r2, 210
	st		r2, 200
	st		r2, 190
	st		r2, 180
	st		r2, 170
	st		r2, 160
	st		r2, 150
	st		r2, 140
	st		r2, 130
	st		r2, 120
	st		r2, 110
	st		r2, 100
	st		r2, 90
	st		r2, 80
	st		r2, 70
	st		r2, 60
	st		r2, 50
	st		r2, 40
	st		r2, 30
	st		r2, 20
	st		r2, 10
	zjmp	%:freeze

norsacce:
	live 	%667974
	ld		%0, r2
	st		r2, 510
	st		r2, 500
	st		r2, 490
	st		r2, 480
	st		r2, 470
	st		r2, 460
	st		r2, 450
	st		r2, 440
	st		r2, 430
	st		r2, 420
	st		r2, 410
	st		r2, 400
	st		r2, 390
	st		r2, 380
	st		r2, 370
	st		r2, 360
	st		r2, 350
	st		r2, 340
	st		r2, 330
	st		r2, 320
	st		r2, 310
	st		r2, 300
	st		r2, 290
	st		r2, 280
	st		r2, 270
	st		r2, 260
	st		r2, 250
	st		r2, 240
	st		r2, 230
	st		r2, 220
	st		r2, 210
	st		r2, 200
	st		r2, 190
	st		r2, 180
	st		r2, 170
	st		r2, 160
	st		r2, 150
	st		r2, 140
	st		r2, 130
	st		r2, 120
	st		r2, 110
	st		r2, 100
	st		r2, 90
	st		r2, 80
	st		r2, 70
	st		r2, 60
	st		r2, 50
	st		r2, 40
	st		r2, 30
	st		r2, 20
	st		r2, 10
	zjmp	%:norsacce
	ld		%0, r2