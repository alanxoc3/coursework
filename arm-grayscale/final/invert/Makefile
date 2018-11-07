invert: invert.o
	ld -o $@ $+

invert.o: invert.s
	as -o $@ $<

clean:
	rm invert *.o
