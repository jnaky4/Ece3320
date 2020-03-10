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


int main(int argc, char** argv){
	char fileName[50] = "validate/raw-data-valid/raw_data_";
	char appendName[20] = "raw_data_";
	char fileOut[50] = "saved/";
	char fileOut2[50] = "saved/";
	FILE *fp;
	FILE *op;
	
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
	
	int doScale = 0;
	int doOffset = 0;
	
	/*
	 * -n
	 * -s
	 * -a
	 * -h
	 * -d
	 */
	
	try{
		/*
		 * check for enough arguments:
		 * 3 arguments is minimum ./demo -n 1 would create a file
		 * except if -h, 2 arguments ./demo -h, no other arguments should be present
		 */
		if(argc < 3 && strcmp(argv[1], "-h") != 0){
//			printf("%d\n",strcmp(argv[1], "-h"));
			printf("%s\n", argv[1]);
//			printf("not enough arguments:\n");
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
						printf("%s\n", fileName);
	
						
					}
						
				}
				/*
				 * case 2: -a
				 */
				//TODO add check for doScale
				else if(strcmp(argv[i], "-a") == 0){			
					i++;
					if(i >= argc){
						throw user_error("no offset number");
//						printf("no offset number");
//						return 0;
					}
					doOffset = 1;
					strcpy(fileName, argv[1]);	strcat(fileOut, "Offset_data_");
					if(gThanTen != 0){
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
				
				/*
				 * case 3: -s
				 */
				
				//TODO add check for doOffset
				else if(strcmp(argv[i], "-s") == 0){
					i++;
					if(i >= argc){
						throw user_error("no scaler number");
//						printf("no scaler number");
//						return 0;
						}
					doScale = 1;
					
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
				/*
				 * case 4:err -d
				 * if this is used, -n filename will be overwritten,
				 * but the filenumber will be stored for fileOut
				 * 
				 */
				
				//TODO
				else if(strcmp(argv[i], "-d") == 0){
					i++;
					if(i >= argc){
						throw user_error("no new directory listed\n");
					}
					
					strcpy(fileName, argv[i]);
					//strcat(fileName, )
						
					
					
					
					
					
					
					
					
					
					
				}
				else if(strcmp(argv[i], "-h") == 0){
					printf("The program needs at least 3 arguments\n");
					printf("-n followed by the file number\n");
					printf("a file number 1 to 10\n");
					printf("what to do with it, -s scale, -o offset\n");
					printf("how much it sould scale of offset the values in the file\n");
				}
			}
			if(fileCheck != 1){
				throw user_error("no file to load from, nothing will happen\n");
//				printf("no file to load from, nothing will happen\n");
			}
			
		}
	

		/*
		 * opens fileName to read and fileOut to write
		 * 
		 */
		fp = fopen(fileName, "r");
		if (fp == NULL){
			printf("Could not open file wookie %s",fileName);
			return 1;
		}
		fscanf(fp,"%d%d", &numLines, &maxVal);
		printf("%d numlines\n", numLines);
		printf("%d maxval\n", maxVal);
		
		printf("%s\n", fileOut);
		op = fopen(fileOut, "w");
		if (op == NULL){
			printf("Could not open file wookie %s",fileOut);
			return 1;
		}
		
		if(doOffset == 1){
			fprintf(op, "%d %d\n", numLines, offSet);
		}
		
		if(doScale == 1){
			fprintf(op, "%d %lf\n", numLines, scaler);
		}
		
		
		
		for(int i=0; i < numLines; i++){	
			fscanf(fp, "%d", &fileVal);
	//		printf("%d\n", fileVal);
	
			if(doOffset == 1 && doScale == 0){
				
	//			printf("%d offset\n", offSet);
	//			printf("%d fileVal\n", fileVal);
				fileVal = fileVal + offSet;
	//			printf("%d added\n", fileVal);
				fprintf(op, "%d\n", fileVal);
			}
			
			if(doScale == 1 && doOffset == 0){
				if(fileVal != 0){
					scalerOut = ((double)fileVal * scaler);
				}
				else{
					fileVal = 0;
				}
				
				fprintf(op, "%lf\n", scalerOut);	
			}	
			if(doScale == 1 && doOffset == 1){
				printf("Not gonna happen\n");
			}
		}	
		fclose(op);
		fclose(fp);
	}
	catch(user_error &err){
		cerr << err.what() << endl;
	}
	catch(...){
		cerr << "something broke" << endl;
	}

}
