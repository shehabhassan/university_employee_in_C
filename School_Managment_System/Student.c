#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "Config.h"
#include "Student.h"

// Define the global variables
Student *head = NULL;
Student *tail = NULL;
u32 num_students = 0;


void new_student(void) {
    // Allocate memory for a new student
    Student *new_student = (Student*) malloc(sizeof(Student));

    // Get details of the new student
    printf("\nEnter student details:\n");
    printf("ID: ");
    fflush(stdin);
    scanf("%d", &new_student->id);
    printf("Name: ");
    fflush(stdin);
    gets(new_student->name);
    printf("Date of Birth (DD/MM/YYYY): ");
    fflush(stdin);
    gets(new_student->dob);
    printf("Address: ");
    fflush(stdin);
    gets(new_student->address);
    printf("Phone number: ");
    fflush(stdin);
    gets(new_student->phone);
    printf("Computer Science score: ");
    fflush(stdin);
    scanf("%d", &new_student->cs_score);

    // Set the previous and next pointers of the new student
    new_student->prev = NULL;
    new_student->next = NULL;

    // If the list is empty, set the head and tail pointers to the new student
    if (head == NULL) {
        head = new_student;
        tail = new_student;
    } else {
        // Otherwise, add the new student to the end of the list
        tail->next = new_student;
        new_student->prev = tail;
        tail = new_student;
    }

    // Increment the number of students
    num_students++;

    printf("\nNew student added successfully!\n");
}

void delete_student(void) {
    int id;
    if (num_students == 0) {
        printf("\nThe student list is currently empty.\n");
    } else {
        printf("\nEnter ID of student to be deleted: ");
        scanf("%d", &id);

        // Search for the student with the given ID
        Student *current = head;
        while (current != NULL) {
            if (current->id == id) {
                break;
            }
            current = current->next;
        }

        // If the student is not found, display an error message
        if (current == NULL) {
            printf("\nError: student with ID %d not found.\n", id);
            return;
        }

        // Update the previous and next pointers of adjacent nodes
        if (current == head && current == tail) {
            // Case 1: Only one student in the list
            head = NULL;
            tail = NULL;
        } else if (current == head) {
            // Case 2: Student is the head of the list
            head = current->next;
            head->prev = NULL;
        } else if (current == tail) {
            // Case 3: Student is the tail of the list
            tail = current->prev;
            tail->next = NULL;
        } else {
            // Case 4: Student is in the middle of the list
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        // Free the memory allocated for the deleted student
        free(current);

        // Decrement the number of students
        num_students--;

        printf("\nStudent with ID %d deleted successfully!\n", id);
    }
}

void student_list(void) {
    if (num_students == 0) {
        printf("\nThe student list is currently empty.\n");
    } else {
        // Print the table header
        print_table_header();

        // Traverse the list and sort the students by name using bubble sort
        Student *current = head;
        while (current != NULL) {
            Student *next = current->next;

            while (next != NULL) {
                if (strcmp(current->name, next->name) > 0) {
                    // Swap the positions of the two students in the list
                    if (current->prev != NULL) {
                        current->prev->next = next;
                    } else {
                        head = next;
                    }
                    if (next->next != NULL) {
                        next->next->prev = current;
                    } else {
                        tail = current;
                    }
                    Student *temp = next->next;
                    next->next = current;
                    next->prev = current->prev;
                    current->next = temp;
                    current->prev = next;
                    // Reset the variables to continue sorting
                    next = current->next;
                } else {
                    next = next->next;
                }
            }
            current = current->next;
        }

        // Traverse the sorted list and print the details of eachstudent
        current = head;
        while (current != NULL) {
            print_student(current);
            current = current->next;
        }

        // Print the table footer
        print_table_footer();
    }
}

void print_student(Student *s) {
    printf("| %5d | %-20s | %-11s | %-30s | %-15s | %3d |\n", s->id, s->name, s->dob, s->address, s->phone, s->cs_score);
}

void print_table_header(void) {
    printf("\n+-------+----------------------+-------------+--------------------------------+-----------------+-------+\n");
    printf("|   ID  |         Name         | Date of Birth |            Address             |    Phone Number | Score |\n");
    printf("+-------+----------------------+-------------+--------------------------------+-----------------+-------+\n");
}

void print_table_footer(void) {
    printf("+-------+----------------------+-------------+--------------------------------+-----------------+-------+\n");
}

void main_menu(void) {
    int choice;
    do {
        printf("\t\t\t\t\t[Welcome To The School Management System]\n");
        printf("\t\t\t\t\t=========================================\n");
        printf("Please Select an option from the following: \n");
        printf("===========================================\n");
        printf("1. Add new student data.\n");
        printf("2. Delete existing student using student id.\n");
        printf("3. Display all students.\n");
        printf("4. Exit program.\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                new_student();
                break;
            case 2:
                delete_student();
                break;
            case 3:
                student_list();
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 0);
}
