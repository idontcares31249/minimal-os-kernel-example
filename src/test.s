.intel_syntax noprefix
.text
.global _start

_start:
	

helloWorld:
	.ascii "Hello, world!!"
	helloWorld_len = . - helloWorld