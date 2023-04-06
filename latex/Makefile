all:
	pdflatex test.tex
	pdflatex test_slides.tex
	clear
	clear

open:
	evince ./test_slides.pdf ./test.pdf&

vim:
	nvim *.tex

clean:
	-rm *.log 
	-rm *.aux 
	-rm *.nav 
	-rm *.snm 
	-rm *.toc
	-rm *.out

clean-all:
	-rm *.log 
	-rm *.aux 
	-rm *.nav 
	-rm *.snm 
	-rm *.toc
	-rm *.out
	-rm *.pdf
