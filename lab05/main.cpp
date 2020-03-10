#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>

#define MAX
using namespace std;

class user_error : public std::runtime_error{
public: 
	explicit user_error(const char* what_arg) : std::runtime_error(what_arg) {}
	explicit user_error(const std::string &what_arg) : runtime_error(what_arg) {}
	
};

//class file_error : public std::file_error{
//public:
//    explicit file_error(const char* what_arg) : std::file_error(what_arg) {}
//    explicit file_error(const std::string &what_arg) : file_error(what_arg) {}
//
//};


int main(int argc, char** argv){
	char fileName[50] = "validate/raw-data-valid/raw_data_";
	char appendName[20] = "/raw_data_";
	char fileOut[50] = "saved/";
	char fileOut2[50] = "saved/";
	FILE *fp;
	FILE *op;
	FILE *op2;
	
	int offSet = 0;
	double scaler = 1.0;
	double scalerOut = 0.0;
	
	char *strtodPtr;

	
	FILE *fout;
	int filenum;
	char filenumStr[20];
	int fileCheck = 0;
	int gThanTen = 0;
	int fileVal;
	int argument_count = argc;
	char fileCont[255];
	int numLines;
	int maxVal;
	int convert;

	int order = 0;
	/*
	 * order 1: argument -s came before -a
	 * order 2: argument -a came before -s
	 */
	int doScale = 0;
	int doOffset = 0;
	
	try{
		/* Part 1: command line argument checks
		 *      5 cases: -n -a -s -d -h
		 * check for enough arguments:
		 * 3 arguments is minimum ./demo -n 1 would create a file
		 * except if -h, 2 arguments ./demo -h, no other arguments should be present
		 */

		/*
		 * base case: not enough arguments
		 */
		if(argc < 3 && strcmp(argv[1], "-h") != 0){
			printf("%s\n", argv[1]);
			printf("%d argc\n", argc);
			throw user_error("not enough arguments\n");
		}
		
		/*
		 * case 1: -n
		 */
		else{	
			for(int i= 1; i < argc; i++){
				if(strcmp(argv[i], "-n") == 0){
					++i;
					if(i >= argc){
						
						throw user_error("no file number");
//						printf("no file number");
//						return 0;
					}
					else{
						filenum = atoi(argv[i]);
						strcpy(filenumStr, argv[i]);
						if(filenum >= 10){
							gThanTen = 1;
							strcat(fileName, argv[i]);
							strcat(fileName, ".txt");
						}
						else{
							strcat(fileName, "0");
							strcat(fileName, argv[i]);
							strcat(fileName, ".txt");
						}
						
						fileCheck = 1;
						printf("line 97: %s\n", fileName);
	
						
					}
						
				}
				/*
				 * case 2: -a
				 */
				else if(strcmp(argv[i], "-a") == 0){			
					i++;
					if(i >= argc){
						throw user_error("no offset number");
					}
					doOffset = 1;
					/*
					 * if doScale -s arugment has already been passed then
					 * offset data will be put in fileOut2
					 */
					if(doScale == 1){
					    order = 1;
                        strcat(fileOut2, "Offset_data_");

                        if(gThanTen == 1){
                            strcat(fileOut2, filenumStr);
                        }
                        else{
                            strcat(fileOut2, "0");
                            strcat(fileOut2, filenumStr);
                        }
                        strcat(fileOut2, ".txt");

                        offSet = atoi(argv[i]);

                        printf("offset by %d\n", offSet);
                        printf("%s\n", fileOut2);
					}
					else{

                        strcat(fileOut, "Offset_data_");

                        if(gThanTen == 1){
                            strcat(fileOut, filenumStr);
                        }
                        else{
                            strcat(fileOut, "0");
                            strcat(fileOut, filenumStr);
                        }
                        strcat(fileOut, ".txt");

                        offSet = atoi(argv[i]);

                        printf("offset by %d\n", offSet);
                        printf("%s\n", fileOut);
					}

					
				}
				
				/*
				 * case 3: -s
				 */

				else if(strcmp(argv[i], "-s") == 0){
					i++;
					if(i >= argc){
						throw user_error("no scaler number");
						}
					doScale = 1;
                    /*
                     * if doOffset -a arugment has already been passed then
                     * scale data will be put in fileOut2
                     */
					if(doOffset == 1){
					    order = 2;
                        strcat(fileOut2, "Scaled_data_");
                        if(gThanTen != 0){
                            strcat(fileOut2, filenumStr);
                        }
                        else{
                            strcat(fileOut2, "0");
                            strcat(fileOut2, filenumStr);
                        }
                        strcat(fileOut2, ".txt");
                        printf("%s\n", fileOut2);
                        scaler = strtod(argv[i], &strtodPtr);
                        printf("scale by %.4f\n", scaler);
					}
					else{
                        strcat(fileOut, "Scaled_data_");
                        if(gThanTen != 0){
                            strcat(fileOut, filenumStr);
                        }
                        else{
                            strcat(fileOut, "0");
                            strcat(fileOut, filenumStr);
                        }//overwrite string
                        strcat(fileOut, ".txt");
                        printf("%s\n", fileOut);
                        scaler = strtod(argv[i], &strtodPtr);
                        printf("scale by %.4f\n", scaler);
					}

				}
				/*
				 * case 4: -d
				 * if this is used, -n filename will be overwritten,
				 * but the filenumber will be stored for fileOut
				 * 
				 */
				

				else if(strcmp(argv[i], "-d") == 0){
					i++;
					if(i >= argc){
						throw user_error("no new directory listed\n");
					}

					printf("we are here now arent we?\n");
					if(fileCheck == 1){
					    sprintf(filenumStr, "%d", filenum);
                        strcpy(fileName, argv[i]);
                        strcat(fileName, appendName);
                        if(gThanTen == 1){
                            strcat(fileName, filenumStr);
                        }
                        else{
                            strcat(fileName, "0");
                            strcat(fileName, filenumStr);
                        }
                        strcat(fileName, ".txt");
					}

				}
				else if(strcmp(argv[i], "-h") == 0){
				    i = argc;
					printf("The program needs at least 3 arguments to work and 5 to mainipulate the data\n");
                    printf("1: ./hello to compile the makefile\n");
					printf("2: -n followed by the file number\n");
					printf("3: with a file number 1 to 10\n");
					printf("or -d for a specific folder\n");
					printf("4: what to do with it, -s scale, -o offset\n");
					printf("5: how much it should scale or offset the values in the file\n");
				}
			}
			if(fileCheck != 1){
				throw user_error("no file to load from, nothing will happen\n");
			}
			
		}


		/* Part 2: file read and write
		 * opens a fileName to read in and a fileOut to write
		 * if there is a -a and a -s then the program checks order variable
		 * and there will be a fileout2
		 */
		fp = fopen(fileName, "r");
		if (fp == NULL){
		    throw user_error("could not open file");
		}
		fscanf(fp,"%d%d", &numLines, &maxVal);
		printf("%d numlines\n", numLines);
		printf("%d maxval\n", maxVal);


		if(doScale == 1 && doOffset == 1){//order will be assigned
            op = fopen(fileOut, "w");
            op2 = fopen(fileOut2, "w");
            if (op == NULL || op2 == NULL){
                throw user_error("no file to save to one of operations -a or -s, nothing will happen\n");
            }

            if(order == 1){// -s came before -a
                fprintf(op2, "%d %d\n", numLines, offSet);
                fprintf(op, "%d %lf\n", numLines, scaler);
            }
            else{//Order is 2 -a came before -s
                fprintf(op, "%d %d\n", numLines, offSet);
                fprintf(op2, "%d %lf\n", numLines, scaler);
            }

		}
		else{
            printf("%s\n", fileOut);
            op = fopen(fileOut, "w");
            if (op == NULL){
                throw user_error("no file to save to, nothing will happen\n");
            }
            if(doOffset == 1 && doScale == 0){
                fprintf(op, "%d %d\n", numLines, offSet);
            }
            if(doScale == 1 && doOffset == 0){
                fprintf(op, "%d %lf\n", numLines, scaler);
            }
		}
		
		
		
		for(int i=0; i < numLines; i++){	
			fscanf(fp, "%d", &fileVal);
	//		printf("%d\n", fileVal);
	
			if(doOffset == 1){
				
	//			printf("%d offset\n", offSet);
	//			printf("%d fileVal\n", fileVal);
				fileVal = fileVal + offSet;
	//			printf("%d added\n", fileVal);
	            if(order == 1){
                    fprintf(op2, "%d\n", fileVal);
	            }
	            else{
                    fprintf(op, "%d\n", fileVal);
	            }


			}
			
			if(doScale == 1){
				if(fileVal != 0){
					scalerOut = ((double)fileVal * scaler);
				}
				else{
					fileVal = 0;
				}
				if(order == 2){
                    fprintf(op2, "%lf\n", scalerOut);
				}
				else{
                    fprintf(op, "%lf\n", scalerOut);
				}

			}
		}	
		fclose(op);
		fclose(fp);
		fclose(op2);
	}
	catch(user_error &err){
		cerr << err.what() << endl;
	}
//	catch(file_error &err){
//
//	}
	catch(...){
		cerr << "something broke" << endl;
	}

}
