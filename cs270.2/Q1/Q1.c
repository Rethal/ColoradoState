// Q1 Programming Quiz - Source file
// Author: ?????
// Date:   ?????
// Class:  CS270
// Email:  ?????

// Include files
#include "Q1.h"

// Global variables
Student *head = NULL;
Student *tail = NULL;
Student *thisStudent = NULL;

void readFile(char *filename){

  FILE* fp = fopen(filename,"r");
  char n[80];
  int i = 0;
  float g = 0;
  if(fp!=NULL){
  printf("File read \n");
  }
  while(fscanf(fp,"%s %d %f", n, &i, &g)==3){
  insertStudent(n,i,g);
  printf("GOOD \n");
  }
}

            void insertStudent(char *name, int id, float gpa){
	      printf("%s \n %d \n %.2f \n",name,id,gpa);
	      Student *newKid;
	      newKid = calloc(1,sizeof(*newKid));
	      newKid -> name = malloc(sizeof(name));
	      newKid-> name = strdup(name);

	      newKid -> id = id;
	      newKid -> gpa = gpa;
	      thisStudent = head;

	      if(head == NULL){
		head = newKid;

	      }
	      else if(strcmp(newKid->name,head->name)<0){
		printf("newhead \n");
		newKid->next = head;
		head = newKid;
	      }
	      else{
		printf("head: %s \n", head->name);
	      while(thisStudent!=NULL){
		Student *nextStudent = thisStudent->next;
		if(nextStudent!=NULL){
		  printf("next: %s \n",nextStudent->name);
//		  if(newKid->name < nextStudent->name){
//		    printf("reverse \n");
//		    newKid->next = nextStudent;
//		    thisStudent->next = newKid;
//		    }
		 }
		else{
		  thisStudent->next = newKid;
		  thisStudent = thisStudent->next;
		}
	    thisStudent = thisStudent->next;

	      }
	    }
	    }

            void removeStudent(char *name){
	      *thisStudent = *head;
	      if(strcmp(head->name,name)==0){
		thisStudent = head->next;
		free(head->name);
		free(head);
		head = thisStudent;
	      }
	      else{
		while(thisStudent != NULL){
		  Student *nextStudent = thisStudent->next;
		  if(strcmp(nextStudent->name,name)==0){
		    thisStudent->next = nextStudent->next;
		    free(nextStudent->name);
		    free(nextStudent);
		  }
		  thisStudent = thisStudent->next;
		}
	      }
	    }

            void iterate(iterate_function func){
	      if(head != NULL){
		*thisStudent = *head;
		while(thisStudent!=NULL){
		  thisStudent = thisStudent->next;
		}
	      }
	    }

            void terminate(){
	    thisStudent = head->next;
	      while(thisStudent!=NULL){
		free(head->name);
		free(head);
		head = thisStudent;
		thisStudent = head->next;
	      }
	      free(head->name);
	      free(head);
	    }

// ***** Implement four functions in header file




