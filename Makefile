#1/27 Lab introduction to Vim and makefiles

#git init :make empty directory
#git add . : adds all files to commit
#git status : checks status of git directory
#git commit -m "message" : does commit skipping message step
#touch .gitignore : creates files in git directory that git will ignore

#git username jnaky4
#jnalongi2@aol.com



SOURCES := $(wildcard *.CPP)
#wildcard stores all sources in the current directory with the .cpp inside the sources

CXXFLAGS := -std=c++11 -O0 -ggdb
#sets the compiler flag to c++ version 11

#optimization flags
# -O0: optimize with no optimization(0) 

#-ggdb?

PROGRAM := demo
#



$(PROGRAM) : $(SOURCES)
#source : source.cpp  
	$(CXX) $(CXXFLAGS) $^ -o $@
#	$(CXX) source.cpp -o source
#$(CXX) makes ./a.out and executes the compiler
#$^ fills with prerequisite source.cpp above ie from the right side of the :
#$@ fills with prerequisite PROGRAM above


.PHONY : clean
#

clean : 
	-rm -rf $(PROGRAM)
#defines clean and removes PROGRAM
#-rm doesnt know how to remove more than one file so we -rf recursively removes




