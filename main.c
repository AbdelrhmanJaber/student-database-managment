#include<stdio.h>
#include<stdlib.h>

#include"Platform_Types.h"
#include"student_database_managment.h"


enum choises{
    ADD_STUDENT_DETAILS_FROM_FILE = 1,
    ADD_STUDENT_DETAILS_MANUALLY,
    FIND_STUDENT_BY_ROLL_NUMBER,
    FIND_STUDENT_BY_FNAME,
    FIND_STUDENTS_REGISTERED_COURSE,
    COUNT_STUDENTS,
    DELETE_STUDENT_BY_ROLL_NUMBER,
    UPDATE_STUDENT,
    SHOW_ALL_STUDENT,
    EXIT
}options;

void main(void){
    uint32_t option , rollNumber , courseID;
    uint8_t breakFlag = 0;
    sint8_t fName[50];
    queue * q = (queue*) malloc(sizeof(queue));
    q = createStudentDB(q);
    printf("\n=============================== welcome to student databas ================================ \n");
    while (1)
    {
        printf("\n=============================================================== \n");
        printf("\n1- Add Student Details From File\n");
        printf("2- Add Student Details Manually\n");
        printf("3- Find the student by the given roll number\n");
        printf("4- Find the student by the given first name\n");
        printf("5- Find the student registerd in a course by course ID\n");
        printf("6- Number of students in the system\n");
        printf("7- Delete a student by his unique rol number\n");
        printf("8- Update student data\n");
        printf("9- print all students in the system\n");
        printf("10- Exit\n");
        printf("Enter the option you want : ");
        scanf("%d",&option);
        /*switch for the user option*/
        switch(option){
            case ADD_STUDENT_DETAILS_FROM_FILE :{
                q = addStudentFromFile(q);
                printf("\nStudent/s is added to the file correctly\n");
                break;
            }
            case ADD_STUDENT_DETAILS_MANUALLY:{
                q = addStudentManually(q);
                break;
            }
            case FIND_STUDENT_BY_ROLL_NUMBER:{
                printf("\nEnter the roll Number you want to search for : ");
                scanf("%d",&rollNumber);
                findStudentByRollNumber(q , rollNumber);
                break;
            }
            case FIND_STUDENT_BY_FNAME:{
                printf("\nEnter the first name you want to search for : ");
                fflush(stdin);fflush(stdout);
                gets(fName);
                fflush(stdin);fflush(stdout);
                findStudentByFirstName(q , fName);
                break;
            }
            case FIND_STUDENTS_REGISTERED_COURSE:{
                printf("Enter the Course ID : ");
                scanf("%d",&courseID);
                fflush(stdin);fflush(stdout);
                findStudentsByCourseID(q , courseID);
                break;
            }
            case COUNT_STUDENTS:{
                printf("Number of students in the system is %d\n",studentsCounts(q));
                break;
            }
            case DELETE_STUDENT_BY_ROLL_NUMBER:{
                printf("\nEnter the roll Number for student you want to delete : ");
                scanf("%d",&rollNumber);
                q = deleteStudentByRollNumber(q , rollNumber);
                break;
            }
            case UPDATE_STUDENT:{
                printf("Enter the roll Number for student you want to modify his data : ");
                scanf("%d",&rollNumber);
                q = updateStudentByRollNumber(q , rollNumber);
                break;
            }
            case SHOW_ALL_STUDENT:{
                showAllStudent(q);
                break;
            }
            case EXIT:{
                breakFlag = 1;
                break;
            }
            default : {
                printf("\nWrong option!\nplease Enter another option\n");
                break;
            }
        }
        if(breakFlag) break;
    }
    
}