all:paper.tex
	pdflatex paper.tex
	pdflatex paper.tex
	rm -rf paper.log paper.out paper.snm paper.toc paper.aux paper.nav
clean:
	rm -rf paper.log paper.out paper.snm paper.toc paper.aux paper.nav paper.pdf
