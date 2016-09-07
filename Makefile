all:
	R CMD INSTALL .

clean:
	cd src && $(MAKE) clean

