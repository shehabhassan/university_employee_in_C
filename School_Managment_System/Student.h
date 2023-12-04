#ifndef _STUDENT_H_
#define _STUDENT_H_

// Define the student structure
typedef struct student {
    int id;
    char name[NAME_SIZE];
    char dob[DATE_SIZE];
    char address[ADDRESS_SIZE];
    char phone[NUMBER_SIZE];
    int cs_score;
    struct student *prev;
    struct student *next;
} Student;




void main_menu();
void new_student();
void delete_student();
void student_list();
void print_student(Student *s);
void print_table_header();
void print_table_footer();


#endif // _STUDENT_H_
