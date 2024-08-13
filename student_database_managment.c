#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"student_database_managment.h"

static studentDB * helpAddStudentFromFile (queue * q , studentDB * temp);
static studentDB * helpAddStudentManually(queue * q , studentDB * temp);
static void helpPrintStudentsData(studentDB * temp);
static studentDB * helpFindStudentByRollNumber(studentDB * temp , uint32_t roll , uint8_t * flag);
static studentDB * helpFindStudentByFirstName(studentDB * temp , sint8_t fName[50] , uint8_t * flag);
static uint8_t isRollNumberUnique(queue * q , uint32_t roll); 

/**
 * @brief Create a Student object in data base managment
 * 
 * @param q : reference for queue that represent the data base
 * @return pointer to the queue 
 */

queue * createStudentDB(queue* q){
    q->size = 0;
    q->front = NULL;
    q->rear = NULL;
    return q;
}


/**
 * @brief add student data from file text
 * 
 * @param q : reference for queue that represent the data base
 * @return pointer to the queue 
 */

queue * addStudentFromFile(queue * q){
    studentDB * student = (studentDB *) malloc(sizeof(studentDB));
    if(student != NULL){
        student = helpAddStudentFromFile(q , student); //fill student data from the file 
        student->next = NULL;
        /*CHECK IF FIRST NODE*/
        if(q->rear == NULL) q->front = student; //first node
        else q->rear->next = student; //put rear reference for O(1) dequeue 
        q->rear = student; 
        q->size++; 
    }
    else{
        return NULL;
    }
}


/**
 * @brief add student data manually by the user 
 * 
 * @param q : reference for queue that represent the data base 
 * @return pointer to the queue 
 */


queue* addStudentManually(queue *q){
    studentDB * student = (studentDB *) malloc(sizeof(studentDB));
    if(student != NULL){
        student = helpAddStudentManually(q , student); //fill student data manually
        student->next = NULL;
        /*CHECK IF FIRST NODE*/
        if(q->rear == NULL) q->front = student; 
        else q->rear->next = student;
        q->rear = student;
        q->size++;
    }
    else{
        return NULL;
    }
}

/**
 * @brief find a student in the data base system by using his unique roll number
 * 
 * @param q : reference for queue that represent the data base
 * @param roll : the roll number that student want (should be unique)
 */

void findStudentByRollNumber(queue *q , uint32_t roll){
    uint8_t flag = 0;
    if(q->front == NULL){
        printf("\nThe system is Empty\n");
    }
    else if(q != NULL){
        studentDB * temp = q->front;
        temp = helpFindStudentByRollNumber(temp , roll , &flag); 
        if(flag == 1){
            printf("\nThis roll Number is found !\n");
            helpPrintStudentsData(temp);
        }
        else printf("\nThis roll Number isn't found in the system\n");
    }
    else printf("\nThere is not any database for student\n");  
}


/**
 * @brief find a student in the data base system by using his first name
 * 
 * @param q : reference for queue that represent the data base
 * @param fName : the first name that user entered
 */

void findStudentByFirstName(queue *q , sint8_t fName[50]){
    uint8_t flag = 0;
    if(q->front == NULL){
        printf("\nThe system is Empty\n");
    }
    else if(q != NULL){
        studentDB * temp = q->front ;
        temp = helpFindStudentByFirstName(temp , fName ,&flag);
        if(flag == 1){
            printf("\nThis Name is found\n");
            helpPrintStudentsData(temp);
        }
        else printf("\nThis first Name isn't found in the system\n");
    }
    else printf("\nThere is not any database for student\n"); //queue is not found
}


/**
 * @brief each student registered number of courses 
 * this function search for each student is registered certain course
 * @param q : reference for queue that represent the data base
 * @param courseID
 */

void findStudentsByCourseID(queue *q , uint32_t courseID){
    uint8_t flag = 0;
    if(q->front == NULL){
        printf("\nThe system is Empty\n");
    }
    else if(q != NULL){
        studentDB * temp = q->front;
        for(uint32_t i = 0 ; i < q->size ;  i++){
            for(uint8_t j = 0 ; j < temp->coursesNumber ; j++){
                if(temp->coursesID[j] == courseID){
                    printf("\n%s is registered in this course (%d)\n",temp->fName , courseID);
                    fflush(stdin);fflush(stdout);
                    helpPrintStudentsData(temp);
                    printf("\n===========================================================\n");
                    flag = 1;
                }
            }
            temp = temp->next;
        }
    }
    else printf("\nThere is not any database for student\n"); 
    if(!flag) printf("There is no student is registered in this course\n");
}


/**
 * @brief printf all students data in the system 
 * 
 * @param q : : reference for queue that represent the data base
 */

void showAllStudent(queue * q){
    studentDB * temp = q->front;
    if(q->front == NULL){
        printf("\nThe system is Empty\n");
    }
    else 
    {
        while (temp != NULL)
        {
            helpPrintStudentsData(temp);
            printf("\n===========================================================\n");
            temp = temp->next;
        }
    }
}

/**
 * @brief function to return number of students if the systems
 * 
 * @param q 
 * @return size of nodes in the queue 
 */

uint32_t studentsCounts(queue * q){
    return q->size;
}

/**
 * @brief function for modification and updating student data
 * 
 * @param q : reference for queue that represent the data base
 * @param roll : the unique roll number for the student
 * @return queue* 
 */

queue *  updateStudentByRollNumber(queue * q , uint32_t roll){
    uint8_t flag = 0;
    if(q->front == NULL){
        printf("\nThe system is Empty\n");
    }
    else if(q != NULL){
        studentDB * temp = q->front;
        temp = helpFindStudentByRollNumber(temp , roll , &flag);
        if(flag == 1){
            printf("\nThis roll Number is found !\n");
            temp = helpAddStudentManually(q , temp);
        }
        else printf("\nThis roll Number isn't found in the system\n");
    }
    else printf("\nThere is not any database for student\n");  
    return q;
}


/**
 * @brief delete a student from the system 
 * 
 * @param q : reference for queue that represent the data base
 * @param roll : the unique roll number for the student
 * @return queue* 
 */

queue * deleteStudentByRollNumber(queue * q , uint32_t roll){
    studentDB * temp = q->front;
    studentDB * prev = q->front;
    uint8_t flag = 0;
    if(q->front == NULL){
        printf("\nThe system is Empty\n");
    }
    else if(temp->roll == roll){
        /*delete the front node*/
        q->front = temp->next;
        prev->next = temp;
        free(temp);
        printf("\nThe student with unique roll number %d is deleted from the system\n",roll);
        q->size--;
    }
    else{
        temp = temp->next;
        while(temp != NULL){
            if(temp->roll == roll){
                flag = 1;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        if(!flag){
            printf("\nthis roll number %d doesn't exist in the system\n",roll);
        }
        else{
            prev->next = temp->next;
            free(temp);
            printf("\nThe student with unique roll number %d is deleted from the system\n",roll);
            q->size--;
        }
    }
    return q;
}




/*========================================= HELP FUNCTIONS ============================================*/

static studentDB * helpAddStudentFromFile (queue * q , studentDB * temp){
    uint32_t size = 0;
    FILE * studentFile = fopen("student.txt","r");
    uint8_t flag = 0;
    if(studentFile == NULL){
        printf("\nfile is not found\n");
        printf("\nfailed to add new student\n");
        return NULL;
    }
    /*read all file until the end*/
    while(!feof(studentFile)){
        fscanf(studentFile , "%d" , &temp->roll);
        fflush(stdin);fflush(stdout);
        flag = isRollNumberUnique(q , temp->roll);
        while (flag == 1) //check if the roll number unique
        {
            printf("\nthis roll number in the file you entered is already exist\n");
            printf("Enter your unique roll number : ");
            scanf("%d",&temp->roll);
            fflush(stdin); fflush(stdout);
            flag = isRollNumberUnique(q , temp->roll);
        }
        fscanf(studentFile, "%s", &temp->fName);
        fflush(stdin);fflush(stdout);
		fscanf(studentFile, "%s", &temp->lName);
        fflush(stdin);fflush(stdout);
		fscanf(studentFile, "%f", &temp->gpa);
        fflush(stdin);fflush(stdout);
        fscanf(studentFile , "%d" , &temp->coursesNumber);
        fflush(stdin);fflush(stdout);
        for(uint8_t i = 0 ; i < temp->coursesNumber ; i++){
            fscanf(studentFile , "%d" , &temp->coursesID[i]);
        }
        size++;
    }
    fclose(studentFile);
    q->size += (size - 1); //for multiple students in the file 
    return temp ;
}

static studentDB * helpAddStudentManually(queue * q , studentDB * temp){
    uint8_t flag ;
    printf("Enter your unique roll number : ");
    scanf("%d",&temp->roll);
    fflush(stdin); fflush(stdout);
    flag = isRollNumberUnique(q , temp->roll);
    while (flag == 1) //check if the roll number unique
    {
        printf("\nthis roll number is already exist\n");
        printf("Enter your unique roll number : ");
        scanf("%d",&temp->roll);
        fflush(stdin); fflush(stdout);
        flag = isRollNumberUnique(q , temp->roll);
    }
    
    printf("Enter your first name : ");
    fflush(stdin); fflush(stdout);
    gets(temp->fName);
    fflush(stdin); fflush(stdout);
    printf("Enter your last name : ");
    fflush(stdin); fflush(stdout);
    gets(temp->lName);
    fflush(stdin); fflush(stdout);
    printf("Enter your GPA : ");
    fflush(stdin); fflush(stdout);
    scanf("%f",&temp->gpa);
    fflush(stdin); fflush(stdout);
    printf("Enter number of courses you want to register (from 1 to 10) : ");
    scanf("%d",&temp->coursesNumber);
    fflush(stdin); fflush(stdout);
    while(temp->coursesNumber > 10){
      printf("Wrong Input \n");
      printf("Enter number of courses you want to register (from 1 to 10) : ");
      scanf("%d",&temp->coursesNumber);
    }
    for(uint8_t i = 0 ; i < temp->coursesNumber ; i++){
        printf("The course ID number %d is : ",i+1);
        scanf("%d",&temp->coursesID[i]);
    }
    return temp;

}



static void helpPrintStudentsData(studentDB * temp){
    printf("\nStudent first name is : %s\n",temp->fName);
    fflush(stdin); fflush(stdout);
    printf("\nStudent last name is : %s\n",temp->lName);
    fflush(stdin); fflush(stdout);
    printf("\n%s's roll number is : %d\n", temp->fName , temp->roll);
    fflush(stdin); fflush(stdout);
    printf("\n%s's GPA is : %0.2f\n", temp->fName , temp->gpa);
    fflush(stdin); fflush(stdout);
    for(uint8_t i = 0 ; i < temp->coursesNumber ; i++){
        printf("\nCourse number %d ID is : %d\n",i+1 , temp->coursesID[i]);
    }
}


static studentDB * helpFindStudentByRollNumber(studentDB * temp , uint32_t roll , uint8_t * flag){
    if(temp != NULL){
          *flag = 0;
        while(temp != NULL){
            if(temp->roll == roll){
                *flag = 1;
                break;
            }
            temp = temp->next;
        }
    }
    return temp;
}



static studentDB * helpFindStudentByFirstName(studentDB * temp , sint8_t fName[50] , uint8_t * flag){
    if(temp != NULL){
         *flag = 0;
        while(temp != NULL){
            if(!strcmp(temp->fName , fName)){
                *flag = 1;
                break;
            }
            temp = temp->next;           
        }
        
    }
    return temp;
}



static uint8_t isRollNumberUnique(queue * q , uint32_t roll){
    uint8_t flag = 0;
    studentDB * temp = q->front;
    if(temp != NULL){
        while (temp != NULL)
        {
            if(temp->roll == roll){
                flag = 1;
                break;
            }
            temp = temp->next;
        }
    }
    else{
        /*this student is the first
          since q-> front is null*/
    }
    return flag;
}



