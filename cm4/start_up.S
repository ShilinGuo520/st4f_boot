	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

__Vectros:
	.word	stack_top
	.word	(Reset_Handler + 1)


.word	_sidata
.word	_sdata
.word	_edata
.word	_sbss
.word	_ebss


Reset_Handler:
	ldr r0, =0xE000ED88
	ldr r1,[r0]
	orr	r1,r1,#(0xF << 20)
	str	r1,[r0]

  	movs	r1, #0
 	b	LoopCopyDataInit

CopyDataInit:
				ldr	r3, =_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	adds	r1, r1, #4

LoopCopyDataInit:
	ldr	r0, =_sdata
	ldr	r3, =_edata
	adds	r2, r0, r1
	cmp	r2, r3
	bcc	CopyDataInit
	ldr	r2, =_sbss
	b	LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
	movs	r3, #0
	str	r3, [r2], #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss

	bl	main

