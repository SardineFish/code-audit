.data
foo: .word 0x1234
bar: .word 0xAABB

.text
__start:
la t0, foo
#push t