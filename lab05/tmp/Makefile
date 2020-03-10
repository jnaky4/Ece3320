#1/27 Lab introduction to Vim and makefiles

#git init :make empty directory
#git add . : adds all files to commit
#git status : checks status of git directory
#git commit -m "message" : does commit skipping message step
#touch .gitignore : creates files in git directory that git will ignore
#git push : pushes files onto github : requires username and password

#git username jnaky4
#jnalongi2@aol.com



SOURCES := $(wildcard *.c)
#wildcard stores all sources in the current directory with the .cpp inside the sources

CXXFLAGS := -std=c11 -O0 -ggdb
#sets the compiler flag to c++ version 11

#optimization flags
# -O0: optimize with no optimization(0) 

#-ggdb?

PROGRAM := demo




$(PROGRAM) : $(SOURCES)
#source : source.cpp  
	$(CC) $(CFLAGS) $^ -o $@
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


#terminal commands
#chmod +x commands.sh: adds executable to usercontrol
#ls -l
#./commands.sh runs shellscript file
#mv commands.sh temp: moves commands into temp folder
#cd ~ go to root directory
#cd - return to last directory
#make to use make file to build program

#C++
#include <iostream> 
#cin: scanf
#cout: printf
#using namespace std;
# cout << "Key in an integer value:\n";
# << extraction operator
# >> insertion operator
# cin >> value;

