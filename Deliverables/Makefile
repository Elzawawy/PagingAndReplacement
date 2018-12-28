fileSrc = lab4.cc
fileObj = lab4.o
CC =  gcc
FinalTargetName= lab4
$(FinalTargetName) : CFLAG = 
$(fileObj): CFLAG =  -c
$(FinalTargetName) : $(fileObj) 
	$(CC) $(CFLAG) $(fileObj) -o $(FinalTargetName)  
$(fileObj) : $(fileSrc) 
	$(CC) $(CFLAG) $(fileSrc) -o $(fileObj) 
