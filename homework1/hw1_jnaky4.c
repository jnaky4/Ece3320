#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>



Student *head = NULL;



int main() {
    setbuf(stdout, 0);
    bool running = true;
    char input[20];
    char name1[20];
    char name2[20];
    while(running){
        printf("press q to quit\npress i to insert\npress x to swap\npress s to search\npress d to delete\npress f to empty list\npress p to print the list\n");
        scanf("%s",input);
        if(strlen(input)>1){
            printf("not a valid input\n");
        }
        else{
            switch(input[0]){
                case 'q':
                    running = false;
                    break;
                case 'i' :
                    printf("give me a name to insert\n");
                    scanf("%s", name1);

                    if(!isEmpty()){
                        printf("would you like to insert at front type 1\n");
                        scanf("%s", name2);
                        if(strcmp(name2, "1") == 0){
                            Student *temp = create_Student(name1);
                            temp->next = head;
                            head->prev = temp;
                            head = NULL;
                            head = temp;
                            break;
                        }
                        else{
                            printf("give me a second name to insert after\n");
                            scanf("%s", name2);

                        }

                    }
                    head = insert_student(head, name1, name2);
                    break;
                case 's' :
                    printf("give me a name\n");
                    scanf("%s", name1);
                    search_list(head, name1);
                    break;
                case 'd' :
                    printf("give me a name\n");
                    scanf("%s", name1);
                    delete_student(head, name1);
                    break;
                case 'x' :
                    printf("give me a name\n");
                    scanf("%s", name1);
                    printf("give me a second name\n");
                    scanf("%s", name2);
                    swap(create_Student(name1), create_Student(name2));
                    break;
                case 'f' :
                        free_list(head);
                        head = NULL;
                        break;
                case 'p' :
                    print_list(head);
                    break;
                default :
                    printf("not a valid input\n");
                    break;
            }
        }
    }
    return 0;
}

bool isEmpty(){
    return head == NULL;
}

Student *create_Student(char *name){
    Student* new_Student = malloc(sizeof(struct Student));
    strcpy(new_Student->name, name);
    new_Student->next = NULL;
    new_Student->prev = NULL;
    return new_Student;
}

Student *insert_student(Student *head, char *name, char *prev_name){
    Student *insert = create_Student(name);
    Student *prev;// = create_Student(prev_name);

    if(isEmpty(head)){
        printf("new Linked List, %s is the head\n", insert->name);
        return insert;
    }

    prev = search_list(head, prev_name);
    if(prev == NULL){
        printf("no node inserted\n");
        return head;
    }

    if(prev->next == NULL){
        prev->next = insert;
        insert->prev = prev;
        return head;
    }

    else{
        insert->next = prev->next;
        insert->prev = prev;
        insert->next->prev = insert;
        prev->next = insert;
        return head;
    }
}

void print_list(Student *head){
    Student *current = head;
    while(current != NULL){
        printf("%s\n", current->name);
        current = current->next;
    }
    printf("end of list\n");

}

Student *search_list(Student *node, char *name){
    Student* current = node;
    if (isEmpty()) {
        printf("List is empty\n");
        return NULL;
    }

    while(current != NULL){
        if((strcmp(name, current->name)) == 0){
            printf("%s is in the list\n", name);
            return current;
        }

        current = current->next;


    }
    printf("%s not found\n", name);
    return NULL;

}

void swap(Student *node1, Student *node2){
    Student *temp;
    bool node1_head = false;
    bool node1_tail = false;
    bool node2_head = false;
    bool node2_tail = false;


    //Check if nodes are the same
    if(strcmp(node1->name, node2->name) == 0){
        printf("nodes are the same\n");
        return;
    }

    //Check if both nodes are in the list
    node1 = search_list(head, node1->name);
    node2 = search_list(head, node2->name);
    if(node1 == NULL || node2 == NULL){
        printf("one node is not in the list\n");
        return;
    }

    //Check if nodes are adjacent
	if (node2->next->name != NULL) {
		if (strcmp(node2->next->name, node1->name) == 0) {
			printf("swapping\n");
			temp = node1;
			node1 = node2;
			node2 = temp;
			//temp(free);
			//temp = NULL;
		}
	}
    if(node1->next->name != NULL) {
        if (strcmp(node1->next->name, node2->name) == 0) {
            printf("Nodes are adjacent\n");

            node1->next = node2->next;
            node2->next = node1;
            if (node1->prev != NULL) {
                node1->prev->next = node2;
                head = node2;
            }
            //node 1 and 2 next nodes already swapped
            if (node1->next != NULL) {
                node1->next->prev = node1;
            }
            node2->prev = node1->prev;
            node1->prev = node2;
            return;
        }
    }

    if(node1->prev == NULL){
        node1_head = true;
    }
    if(node2->prev == NULL) {
        node2_head = true;
    }
    if(node1->next == NULL){
        node1_tail = true;
    }
    if(node2->next == NULL){
        node2_tail = true;
    }
    //swap head and tail if parameters out of order
    if(node2_head || node1_tail){
        temp = node1;
        node1 = node2;
        node2 = temp;

        if(node2_head)node1_head = true;
        else {
            node2_tail = true;
        }
    }
    temp = create_Student("temp");
    if(node1_head){
        if(node2_tail){
            printf("nodes are head and tail\n");
            temp->next = node1->next;
            temp->prev = node2->prev;
            node1->next = NULL;
            node2->next = temp->next;
            node2->prev = NULL;
            node1->prev = temp->prev;
            node2->next->prev = node2;
            node1->prev->next = node1;
            head = node2;
            free(temp);
            temp = NULL;
            return;
        }
        else{

        temp->next = node2->next;
        temp->prev = node2->prev;
        temp->next->prev = node1;
        temp->prev->next = node1;
        node2->next = node1->next;
        node1->next->prev = node2;
        node2->prev = NULL;
        node1->next = temp->next;
        node1->prev = temp->prev;
        head = node2;
        free(temp);
        temp = NULL;
        return;
        }
    }
    else if(node2_tail){
        temp->next = node1->next;
        temp->prev = node1->prev;
        temp->next->prev = node2;
        temp->prev->next = node2;
        node1->prev = node2->prev;
        node2->prev->next = node1;
        node1->next = NULL;
        node2->next = temp->next;
        node2->prev = temp->prev;
        free(temp);
        temp = NULL;
        return;
    }

    else{
        temp->next = node1->next;
        temp->prev = node1->prev;
        node1->next->prev = node2;
        node1->prev->next = node2;
        node2->next->prev = node1;
        node2->prev->next = node1;
        node1->next = node2->next;
        node1->prev = node2->prev;
        node2->next = temp->next;
        node2->prev = temp->prev;
        free(temp);
        temp = NULL;
        return;


    }

}

int delete_student(Student *node, char *name) {
    Student *delete = search_list(node, name);
    if (delete != NULL) {

        if (strcmp(delete->name, node->name) == 0) {
            head = node->next;
            if (head != NULL) {
                head->prev = NULL;
            }
            printf("head is deleted\n");
            return 1;
        }

        if (delete->next != NULL) {
            delete->prev->next = delete->next;
            delete->next->prev = delete->prev;
        }
        else{
            delete->prev->next = NULL;
        }

        free(delete);

        printf("node is deleted\n");
        return 1;

    }
    else {
        printf("node not deleted\n");
        return 0;
    }
}

void free_list(Student *node){
    Student *current = node;
    Student *next;
    while(current!= NULL) {
        next = current->next;
        free(current);
        current = next;
    }


}