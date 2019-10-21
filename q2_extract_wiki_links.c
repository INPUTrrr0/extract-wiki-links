#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE* fp;
    fp=fopen(argv[1],"r");
    if (fp==NULL){
        printf("%s\n","the file is not found");
        return 0;
    }
    else{
        //find size of file
        fseek(fp, 0L, SEEK_END);
        int sz = ftell(fp);
        rewind(fp);

        //create a array with all the information
        char fileData[sz+1];
        fread( fileData, 1, sz+1, fp );
        fclose(fp);

        char *ptr1;
        char *ptr2;
        char *ptr3;

        //declare start indicator 
        char start[20]="<a href=\"/wiki/";
        char end[5]="</a>";
        char title[10]="title=\"";
        char quotation[5]="\"";

        ptr1 = fileData;
        ptr2 = ptr1;

        while (ptr1!=NULL){
            //update itself to move down the file 
            ptr1 = strstr(ptr1,start);
            if(ptr1==NULL){
                break;
            }
            ptr2=strstr(ptr1,end);
            ptr3=strstr(ptr1,title);
            //make sure the title indicator is present 
            if (ptr3>ptr2){
               ptr1=ptr2;
                continue;
            }else{ 
                //find page name
                char *ptrA = ptr1+15;//point to start of page name 
                char *ptrB = strstr(ptrA,quotation);//point to end of page name
                size_t stringLength=ptrB-ptrA;
                char buffer1[stringLength];
                buffer1 [stringLength] = '\0';
                strncpy(buffer1,ptrA,stringLength);

                ptrA = strstr(ptrB,title)+7;//point to page name after title
                ptrB = strstr(ptrA,quotation);//point to end of page name after title
                size_t stringLength2=ptrB-ptrA;
                char buffer2[stringLength2];
                buffer2 [stringLength2] = '\0';
                strncpy(buffer2, ptrA, stringLength2);

                for (char* p1 = buffer2; (p1 = strchr(p1, ' ')); ++p1) {
                *p1 = '_'; //sometimes the second part of page name has space instead of _ 
                }
            
                if (strcmp(buffer1, buffer2)==0)
                { //if the first part of the page name doesn't match the one after title
                  //ignore it. we just want to case when the two parts match!
                    printf("%s\n",buffer1);
                }  
            }
            //update pointer 
                ptr1=ptr2;   
        } 
    }
    return 0;
}