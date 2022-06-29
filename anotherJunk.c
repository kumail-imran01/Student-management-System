#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
struct Student
{
    char id[50];
    char name[50];
    float Totalmarks;
    struct Course *EnrollCourse;
    struct Student *next;
    float TotalAttendance;
    char FeesStatus[30];
};
// creating the list of student

// adding the student at the start of the list
struct Student *addStudentAtStart(struct Student *std, char id[], char name[])
{
    struct Student *new_std = (struct Student *)malloc(sizeof(struct Student));
    strcpy(new_std->id, id);
    strcpy(new_std->name, name);
    new_std->next = std;
    std = new_std;
    return std;
}
// add the student at the end of the list
struct Student *addStudentAtEnd(struct Student *std, char id[], char name[])
{
    struct Student *new_std = (struct Student *)malloc(sizeof(struct Student));
    strcpy(new_std->id, id);
    strcpy(new_std->name, name);
    struct Student *std_ptr = std;
    while (std_ptr->next != NULL)
    {
        std_ptr = std->next;
    }
    new_std->next = std_ptr->next;
    std_ptr->next = new_std;
    return std;
}
// now use the above function as the helping function of the add student function
struct Student *addStudent(struct Student *std, char id[], char name[])
{

    if (std == NULL)
    {
        std = addStudentAtStart(std, id, name);
    }
    else
    {
        std = addStudentAtEnd(std, id, name);
    }
    return std;
}
// Remove student using the linklist
struct Student *RemoveStudent(struct Student *std, char id[])
{

    if (strcmp(std->id, id) == 0)
    {
        struct Student *temp = std;
        std = std->next;
        free(temp);
        return std;
    }
    else
    {
        struct Student *std_ptr = std;
        struct Student *std_ptr2 = std->next;
        while (std_ptr2->id != id && std_ptr2->next != NULL)
        {
            std_ptr2 = std_ptr2->next;
            std_ptr = std_ptr->next;
        }
        if (strcmp(std_ptr2->id, id) == 0)
        {
            std_ptr->next = std_ptr2->next;
            free(std_ptr2);
        }
    }
    return std;
}
// display the studnet using simple trversal
void displayStudent(struct Student *std)
{
    while (std != NULL)
    {
        printf("%s\t      %s\n", std->name, std->id);
        std = std->next;
    }
}

struct Course
{
    int id;
    char name[50];
    float credHrs;
    float marks;
    struct Course *next;
};
// create the linklist of the Course

// add the course using function
struct Course *addCourse(struct Course *course, int id, float credHrs, char name[])
{
    struct Course *newCourse = (struct Course *)malloc(sizeof(struct Course));
    newCourse->id = id;
    strcpy(newCourse->name, name);
    newCourse->credHrs = credHrs;
    newCourse->next = NULL;

    if (course == NULL)
    {
        newCourse->next = course;
        course = newCourse;
    }
    else
    {
        struct Course *course_ptr = course;
        while (course_ptr->next != NULL)
        {
            course_ptr = course_ptr->next;
        }
        course_ptr->next = newCourse;
        newCourse->next = NULL;
    }
    return course;
}
// display the course
void displayCourse(struct Course *course)
{
    struct Course *course_ptr = course;
    while (course_ptr != NULL)
    {
        printf("%s\t      \t%.2f         \t%d\n", course_ptr->name, course_ptr->credHrs, course_ptr->id);
        course_ptr = course_ptr->next;
    }
}
// this function is used by admin who is entering the marks of the student's course in which he is enrolled
void EnterMarks(struct Course *course)
{
    while (course != NULL)
    {
        printf("Enter the marks of the %s out of 100: ", course->name);
        scanf("%f", &course->marks);
        if (course->marks > 100)
        {
            printf("marks cannot be greater than 100\n");
            continue;
        }
        else
        {
            course = course->next;
        }
    }
}
// Print the result of the students
void viewResult(struct Student *std, struct Course *course)
{
    printf("Name : %s \t Reg : %s\t \n", std->name, std->id);
    while (course != NULL)
    {
        printf(" %d  \t  %s  %.2f \t\n", course->id, course->name, course->marks);
        course = course->next;
    }
    printf("Total Marks : ", std->Totalmarks);
}
// Enter the Attendance of the student
void EnterTheAttendance(struct Student *std)
{
    while (std != NULL)
    {
        printf("Enter the total Attendance Percentage of %s : ", std->name);
        scanf("%f", &std->TotalAttendance);
        std = std->next;
    }
}
// create the function which will update the student fee status
struct Student *SetFeeSubmissionStatus(struct Student *std, char status[])
{
    struct Student *ptr = std;
    while (ptr != NULL)
    {
        strcpy(ptr->FeesStatus, status);
        ptr = ptr->next;
    }
    return std;
}
// using this function student can view his profile
void ViewStudentProfile(struct Student *std)
{
    std->Totalmarks = 0;
    printf("\n====Student Profile======\n");
    printf("\tName : %s\t\n", std->name);
    printf("\tID : %s\t\n", std->id);
    printf("\tFee Status  : %s\t\n", std->FeesStatus);
    printf("\tTotal Attendance : %.2f\t\n", std->TotalAttendance);
    printf("\n==== Course Marks ======\n");
    while (std->EnrollCourse != NULL)
    {
        printf("%s\t%.2f\n", std->EnrollCourse->name, std->EnrollCourse->marks);
        std->Totalmarks = std->EnrollCourse->marks + std->Totalmarks;
        std->EnrollCourse = std->EnrollCourse->next;
    }
    printf("\tTotal Marks : %.2f\t\n", std->Totalmarks);
}
// remove the course used by admin
struct Course *removeCourse(struct Course *course, int id)
{
    struct Course *course_ptr = course;
    struct Course *course_ptr2 = course->next;
    if (course->id == id)
    {
        struct Course *temp = course;
        course = course->next;
        free(temp);
        return course;
    }
    else
    {
        while (course_ptr2->id != id && course_ptr2 != NULL)
        {
            course_ptr = course_ptr->next;
            course_ptr2 = course_ptr2->next;
        }
        if (course_ptr2->id == id)
        {
            course_ptr->next = course_ptr2->next;
        }
    }
    return course;
}
// This function enable students to enroll the course
void SelectCourse(struct Student *std, struct Course *course)
{
    struct Course *course_ptr = course;
    std->EnrollCourse = NULL;
    char name[100];
    for (int i = 0; i < 5; i++)
    {
        course_ptr = course;

        fflush(stdin);
        printf("Enter the name of course %d you want to enroll  : ", i + 1);
        gets(name);
        while (course_ptr != NULL)
        {
            if (strcmp(course_ptr->name, name) == 0)
            {
                std->EnrollCourse = addCourse(std->EnrollCourse, course_ptr->id, course_ptr->credHrs, course_ptr->name);
            }

            course_ptr = course_ptr->next;
        }
    }
}

int main()
{
    printf("  \t\t*************************************\n");
    printf("\t\t\t STUDENT MANAGEMENT SYSTEM\n");
    printf("  \t\t*************************************\n");
    struct Student *std = NULL;
    struct Course *course = NULL;
    // course menu
    course = addCourse(course, 90, 4.0, "DSA");
    course = addCourse(course, 12, 4.0, "ISE");
    course = addCourse(course, 11, 3.0, "RWS");
    course = addCourse(course, 88, 3.0, "LA");
    course = addCourse(course, 44, 3.0, "FA");
    course = addCourse(course, 8, 3.0, "ICT");
    course = addCourse(course, 4, 4.0, "PF");
    int choice;
    while (1)
    {
    Start:
        printf("\n\n\t\t>>>>>>>>>Main Menu<<<<<<<<<<<\n");
        printf("\n \t\tAre you Student ?\n \t\tAre you Admin ? \n");
        printf("\n \t\tPress 1 For  Student\n \t\tPress 2 For Admin \n");
        printf("\n \t\t<--Press -1 For  Exit\n ");
        scanf("%d", &choice);
        if (choice == -1)
        {
            break;
        }
        if (choice == 1)
        {
            printf("\tPress 1 for Login\n\tPress 2 For SignUp\n");
            int opt;
            scanf("%d", &opt);
            if (opt == 2)
            {
                char name[20], reg[50];
                printf("Enter your name : ");
                fflush(stdin);
                gets(name);
                printf("Enter your registration (FA20-BSE-000)  : ");
                gets(reg);
                std = addStudent(std, reg, name);
                std = SetFeeSubmissionStatus(std, "Pending");
                printf("\nAccount created Successfully");
            }

            if (opt == 1)
            {
                char name[20], reg[50];
                printf("Enter your name : ");
                fflush(stdin);
                gets(name);
                printf("Enter your registration (FA20-BSE-000)  : ");
                gets(reg);
                int flag = 0;
                while (std != NULL)
                {
                    if (strcmp(std->name, name) == 0 && strcmp(std->id, reg) == 0)
                    {
                        flag = 1;
                        break;
                    }

                    std = std->next;
                }
                if (flag == 0)
                {
                    printf("Wrong Credidential");
                }

                if (flag == 1)
                {
                StudentMenu:
                    // Student module
                    printf("\n\t\t*****************************");
                    printf("\n\t\tWELCOME TO STUDENT PAGE\n");
                    printf("\t\t*****************************\n");
                    printf("\nPress 1 to View Profile \nPress 2 to View Courses\nPress 3 to Select the Courses \nPress 4 to  Fee Submission  \n <--Press -1 to exit\n");
                    int stdOpt;
                    scanf("%d", &stdOpt);
                    if (stdOpt == -1)
                    {
                        goto Start;
                    }
                    if (stdOpt == 1)
                    {
                        ViewStudentProfile(std);
                        goto StudentMenu;
                        getch();
                    }
                    if (stdOpt == 2)
                    {

                        displayCourse(std->EnrollCourse);
                        goto StudentMenu;
                    }
                    if (stdOpt == 3)
                    {
                        displayCourse(course);
                        SelectCourse(std, course);
                        goto StudentMenu;
                    }

                    if (stdOpt == 4)
                    {
                        printf("Fee Submission :  %s\n", std->FeesStatus);
                        if (strcmp(std->FeesStatus, "Completed") == 0)
                        {
                            printf("\nYou submitted your fees of this semster\n");
                            goto StudentMenu;
                        }

                        printf("Do you want to pay the fees (Press 1 for Y / Press 2 for N) : ");
                        int feeOpt;
                        scanf("%d", &feeOpt);
                        if (feeOpt == 1)
                        {
                            printf("\nFee submited\n");
                            strcpy(std->FeesStatus, "Completed");
                            goto StudentMenu;
                        }
                        else
                        {
                            printf("\nSubmit your fees before due date\n ");
                            goto StudentMenu;
                        }
                    }
                }
            }
        }
        // Admin module
        if (choice == 2)
        {
        admin:
            printf("\nEnter the admin password : \n");
            int pass;
            scanf("%d", &pass);
            if (pass == 1234)
            {
                printf("\t\t*************************");
                printf("\n\t\tWELCOME TO ADMIN PAGE\n");
                printf("\t\t*************************\n");
            menu:
                printf("\nPress 1 to Enter Marks\nPress 2 to View Students \nPress 3 to Add Course \nPress 4 to Delete Course\nPress 5 to Mark Attendance\nPress 6 to Remove Student \nPress 7 to View Fee Analytics\nPress 8 to View Courses\n<--Press -1 to Exit\n");
                int adminOpt;
                scanf("%d", &adminOpt);
                if (adminOpt == 8)
                {
                    displayCourse(course);
                    goto menu;
                }

                if (adminOpt == 1)
                {
                    char name[50];
                    displayStudent(std);
                enterMarks:
                    printf("Enter the name of student of you want to enter the marks : ");
                    gets(name);
                    gets(name);
                    while (std != NULL)
                    {
                        if (strcmp(std->name, name) == 0)
                        {
                            break;
                        }
                        std = std->next;
                    }
                    EnterMarks(std->EnrollCourse);
                    printf("\n Want to enter the marks of more students (1-Y /  2-N):\n");
                    int more;
                    scanf("%d", &more);
                    if (more == 1)
                    {
                        goto enterMarks;
                    }
                    else
                    {
                        goto menu;
                    }
                }
                if (adminOpt == 2)
                {
                    displayStudent(std);
                    goto menu;
                }
                if (adminOpt == 3)
                {
                    char name[50];
                    int id;
                    float cred;
                    printf("Enter the name of course : ");
                    fflush(stdin);
                    gets(name);
                    printf("Enter the id of the course : ");
                    scanf("%d", &id);
                    printf("Enter the cred hrs of the course : ");
                    scanf("%f", &cred);
                    course = addCourse(course, id, cred, name);
                    goto menu;
                }
                if (adminOpt == 4)
                {
                    // remove Course function
                    displayCourse(course);
                    int id;
                    printf("Enter the id of the course : ");
                    scanf("%d", &id);
                    course = removeCourse(course, id);
                    goto menu;
                }
                if (adminOpt == 5)
                {
                    EnterTheAttendance(std);
                    goto menu;
                }
                if (adminOpt == 6)
                {
                    displayStudent(std);
                    printf("Enter the reg of the student you want to remove");
                    char reg[40];
                    fflush(stdin);
                    gets(reg);
                    RemoveStudent(std, reg);
                    goto menu;
                }
                if (adminOpt == 7)
                {
                    struct Student *std_ptr = std;
                    while (std_ptr != NULL)
                    {
                        printf("Name ; %s \t Fee Submission : %s \n", std_ptr->name, std_ptr->FeesStatus);
                        std_ptr = std_ptr->next;
                    }
                    std_ptr = std;
                    goto menu;
                }
                if (adminOpt == -1)
                {
                    goto Start;
                }
            }
            else
            {
                printf("Wrong password\n");
                goto admin;
            }
        }
    }
    getch();
    return 0;
}
