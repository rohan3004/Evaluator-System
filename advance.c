#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 1000
#define MAX_NAME_LENGTH 50
#define FILE_NAME "students_data.dat"
#define TEMP_FILE_NAME "temp.dat"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define DATABASE_FILE "database.dat"

// Structure to hold student record details
struct student
{
    int id;
    char name[MAX_NAME_LENGTH];
    float att;
    float ca;
    float mte;
    float ete;
};

struct user
{
    char id[MAX_USERNAME_LENGTH];
    char name[MAX_USERNAME_LENGTH];
    char pass[MAX_PASSWORD_LENGTH];
};

void eva()
{
    FILE *fp;
    char c;

    // Open the file
    fp = fopen("evaluation.dat", "r");

    // Check if the file exists
    if (fp == NULL) {
        printf("Unable to open file.\n");
    }
    printf("\n\nEvaluation Criteria\n\n");
    // Read and print each character in the file
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    // Close the file
    fclose(fp);
    printf("\n\n\nPress any key to countinue.....");
    getch();
    return;
}

int random_id() {
   int random_num;
   
   // Seed the random number generator
   srand(time(NULL));
   
   // Generate a random number between 1000 and 9999
   random_num = rand() % 9000 + 1000;
   return random_num;
}

// Function to search for a student record by id
void see_detail(char *username) {
    FILE *fp;
    struct user u;
    fp = fopen(DATABASE_FILE, "rb");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    while (fscanf(fp, "%s %s %s\n", u.id, u.name, u.pass) != EOF) {
        if (strcmp(username, u.id) == 0) {
            printf("\n\nID: %s\nName: %s\nPassword: %s\n", u.id, u.name, u.pass);
        }
    }
    fclose(fp);
    printf("\n\nPress any key to countinue.....");
    getch();
    return;
}

void create_record() {
    FILE *fp;
    struct student s;
    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    int id=random_id();
    while (fscanf(fp, "%d %s %f %f %f %f\n", &s.id, s.name, &s.att, &s.ca, &s.mte,&s.ete) != EOF){
        if (s.id == id)
            id=random_id();
    }
    s.id=id;
    printf("Enter student name: ");
    scanf("%s", s.name);
    printf("Enter Attendane marks(out of 100): ");
    scanf("%f", &s.att);
    printf("Enter CA marks(out of 100): ");
    scanf("%f", &s.ca);
    printf("Enter Midterm marks(out of 100): ");
    scanf("%f", &s.mte);
    printf("Enter Endterm marks(out of 100): ");
    scanf("%f", &s.ete);
    fprintf(fp, "%d %s %f %f %f %f\n", s.id, s.name, s.att, s.ca, s.mte,s.ete);
    fclose(fp);
    printf("Record created successfully.\n");
    printf("\n\nPress any key to countinue.....");
    getch();
}

// Function to search for a student record by id
void search_record() {
    FILE *fp;
    struct student s;
    int search_id;
    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    printf("Enter student id to search: ");
    scanf("%d", &search_id);
    while (fscanf(fp, "%d %s %f %f %f %f\n", &s.id, s.name, &s.att, &s.ca, &s.mte,&s.ete) != EOF) {
        if (s.id == search_id) {
            printf("ID: %d\nName: %s\nAttendance Marks: %.2f\nCA Marks: %.2f\nMidterm Marks: %.2f\nEndterm Marks: %.2f", s.id, s.name, s.att,s.ca,s.mte,s.ete);
            fclose(fp);
            printf("\n\nPress any key to countinue.....");
            getch();
            return;
        }
    }
    printf("Record not found.\n");
    fclose(fp);
    printf("\n\nPress any key to countinue.....");
    getch();
}

// Function to modify an existing student record by id
void modify_record() {
    display_record_inner();
    FILE *fp, *fp_temp;
    struct student s;
    int modify_id, found = 0;
    fp = fopen(FILE_NAME, "rb");
    fp_temp = fopen(TEMP_FILE_NAME, "wb");
    if (fp == NULL || fp_temp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    printf("\nEnter student id to modify: ");
    scanf("%d", &modify_id);
    while (fscanf(fp, "%d %s %f %f %f %f\n", &s.id, s.name, &s.att, &s.ca, &s.mte,&s.ete) != EOF) {
        if (s.id == modify_id) {
            found = 1;
            printf("Enter new attendance marks(out of 100): ");
            scanf("%f", &s.att);
            printf("Enter new CA marks(out of 100): ");
            scanf("%f", &s.ca);
            printf("Enter new Midterm marks(out of 100): ");
            scanf("%f", &s.mte);
            printf("Enter new Endterm marks(out of 100): ");
            scanf("%f", &s.ete);
            fprintf(fp_temp, "%d %s %f %f %f %f\n", s.id, s.name, s.att, s.ca, s.mte,s.ete);
            // fprintf(fp_temp, "%d %s %f\n", s.id, s.name, s.ca);
            printf("Record modified successfully.\n");
        } else {
            fprintf(fp_temp, "%d %s %f %f %f %f\n", s.id, s.name, s.att, s.ca, s.mte,s.ete);
            //fprintf(fp_temp, "%d %s %f %f %f\n", s.id, s.name, s.ca1, s.ca2,s.ca3);
            // fprintf(fp_temp, "%d %s %f\n", s.id, s.name, s.ca);
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }
    fclose(fp);
    fclose(fp_temp);
    remove(FILE_NAME);
    rename(TEMP_FILE_NAME, FILE_NAME);
    printf("\n\nPress any key to countinue.....");
    getch();
}

// Function to delete an existing student record by id
void delete_record() {
    display_record_inner();
    FILE *fp, *fp_temp;
    struct student s;
    int modify_id, found = 0;
    fp = fopen(FILE_NAME, "rb");
    fp_temp = fopen(TEMP_FILE_NAME, "wb");
    if (fp == NULL || fp_temp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    printf("\nEnter student id to delete: ");
    scanf("%d", &modify_id);
    while (fscanf(fp, "%d %s %f %f %f %f\n", &s.id, s.name, &s.att, &s.ca, &s.mte,&s.ete) != EOF) {
        if (s.id == modify_id) {
            found = 1;
            printf("\nRecord Deleted Successfully\n");
            continue;
        } else {
            fprintf(fp_temp, "%d %s %f %f %f %f\n", s.id, s.name, s.att, s.ca, s.mte,s.ete);
            // fprintf(fp_temp, "%d %s %f\n", s.id, s.name, s.ca);
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }
    fclose(fp);
    fclose(fp_temp);
    remove(FILE_NAME);
    rename(TEMP_FILE_NAME, FILE_NAME);
    printf("\n\nPress any key to countinue.....");
    getch();
}

void display_record_inner() {
    FILE *fp;
    struct student s;
    float t=0.0;
    char g[10];
    char *gk = g;
    fp = fopen(FILE_NAME, "rb");
    if(fp == NULL) {
        printf("Error in opening file\n");
        return;
    }
    
    printf("\nID\t\tName\t\tAttendance Marks\tCA Marks\tMidterm Marks\tEndterm Marks\tGrade\n");
    
    while (fscanf(fp, "%d %s %f %f %f %f\n", &s.id, s.name, &s.att, &s.ca, &s.mte,&s.ete) != EOF) {
        t=(s.att+s.ca+s.ete+s.mte)/(4.0);
        if(t>=97 && t<=100)
            gk="A+";
        else if (t>=93 && t<=96)
            gk="A";
        else if (t>=90 && t<=92)
            gk="A-";
        else if (t>=87 && t<=89)
            gk="B+";
        else if (t>=83 && t<=86)
            gk="B";
        else if (t>=80 && t<=82)
            gk="B-";
        else if (t>=77 && t<=79)
            gk="C+";
        else if (t>=73 && t<=76)
            gk="C";
        else if (t>=70 && t<=72)
            gk="C-";
        else if (t>=67 && t<=69)
            gk="D+";
        else if (t>=65 && t<=66)
            gk="D";
        else if (t>=60 && t<=64)
            gk="E";
        else if (t<60)
            gk="F";
        printf("%d\t\t%s\t\t%.2f\t\t\t%.2f\t\t%.2f\t\t%.2f\t\t%s\n",s.id, s.name, s.att,s.ca,s.mte,s.ete,gk); 
    }
    fclose(fp);
}

// Function to display the record
void display_record() {
    FILE *fp;
    struct student s;
    float t=0.0;
    char g[10];
    char *gk = g;
    fp = fopen(FILE_NAME, "rb");
    if(fp == NULL) {
        printf("Error in opening file\n");
        return;
    }
    
    printf("\nID\t\tName\t\tAttendance Marks\tCA Marks\tMidterm Marks\tEndterm Marks\tGrade\n");
    
    while (fscanf(fp, "%d %s %f %f %f %f\n", &s.id, s.name, &s.att, &s.ca, &s.mte,&s.ete) != EOF) {
        t=(s.att+s.ca+s.ete+s.mte)/(4.0);
        if(t>=97 && t<=100)
            gk="A+";
        else if (t>=93 && t<=96)
            gk="A";
        else if (t>=90 && t<=92)
            gk="A-";
        else if (t>=87 && t<=89)
            gk="B+";
        else if (t>=83 && t<=86)
            gk="B";
        else if (t>=80 && t<=82)
            gk="B-";
        else if (t>=77 && t<=79)
            gk="C+";
        else if (t>=73 && t<=76)
            gk="C";
        else if (t>=70 && t<=72)
            gk="C-";
        else if (t>=67 && t<=69)
            gk="D+";
        else if (t>=65 && t<=66)
            gk="D";
        else if (t>=60 && t<=64)
            gk="E";
        else if (t<60)
            gk="F";
        printf("%d\t\t%s\t\t%.2f\t\t\t%.2f\t\t%.2f\t\t%.2f\t\t%s\n",s.id, s.name, s.att,s.ca,s.mte,s.ete,gk); 
    }
    fclose(fp);
    printf("\n\nPress any key to countinue.....");
    getch();
}

// Function to register a new user
void registerUser() {

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    FILE *file;
    file = fopen(DATABASE_FILE, "ab");
    struct user u;
    int found = 0;
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    // printf("\nEnter Id: ");
    // scanf("%d", &id);
    printf("\nEnter your name (max %d characters): ", MAX_USERNAME_LENGTH);
    scanf("%s", username);
    printf("\nEnter a password (max %d characters): ", MAX_PASSWORD_LENGTH);
    scanf("%s",password);
    int num=random_id();
    char str[MAX_USERNAME_LENGTH];
    sprintf(str, "%d", num);
    strcat(str,"@");
    strcat(str,username);
    fprintf(file,"%s %s %s\n",str,username,password);
    printf("Your Username: %s\n",str);
    printf("\nRegistration successful!\n");
    printf("\n\nPress any key to countinue.....");
    getch();
    fclose(file);
}

// Function to check if a given username and password combination is valid
int checkCredentials(char *id, char *password) {
    struct user u;
    // Open the database file in read mode
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("\nError: could not open database file\n");
        exit(1);
    }
    // Loop through each line of the file
    while (fscanf(file, "%s %s %s\n", u.id, u.name, u.pass) != EOF) {
        // Check if the username and password match
        if (strcmp(id, u.id) == 0 && strcmp(password, u.pass) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to handle the login process
void login() {
    char id[MAX_USERNAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    struct user u;
    printf("\nEnter your id: ");
    scanf("%s",id);
    printf("\nEnter your password: ");
    scanf("%s",password);
    if (checkCredentials(id, password)) {
        printf("\nLogin successful!\n");
        printf("\n\nPress any key to countinue.....");
        getch();
        FILE *file = fopen(DATABASE_FILE, "r");
        if (file == NULL) {
            printf("\nError: could not open database file\n");
            exit(1);
        }
        while (fscanf(file, "%s %s %s\n", u.id, u.name, u.pass) != EOF){
            if (strcmp(id, u.id) == 0)
                mainmenu(u.name,u.id);
        }
    } else {
        printf("\nIncorrect id or username or password\n");
        printf("\n\nPress any key to countinue.....");
        getch();
    }
}

int main() {
    int choice;
    do {
        system("cls");
        printf("\n*** CA Evaluator System ***\n");
        printf("\tBy Rohan Chakravarty\n");
        printf("*** Limitations ***\n");
        printf("1. Maximun Name must be of 50 Characters Total\n");
        printf("2. The System can hold 1000 records of the Student\n");
        printf("3. May be Inconsistent and Redundant\n");
        printf("\n\n*** MENU ***\n");
        printf("1. New User/Register\n");
        printf("2. Existing User/Login\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("\nThank you for Using the System\n");
                printf("\t~Rohan Chakravarty\n");
                printf("\n\nPress any key to countinue.....");
                getch();
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 3);
    return 0;
}

void mainmenu(char str[], char str1[]) {
    int choice;
    while(1) {
        system("cls");
        printf("\nWelcome %s\n",str);
        printf("*** MENU ***\n");
        printf("1. Create Record\n");
        printf("2. Search Record\n");
        printf("3. Display Evaluation Criteria\n");
        printf("4. Modify Record\n");
        printf("5. Delete Record\n");
        printf("6. Display Record\n");
        printf("7. Display Your Detail\n");
        printf("8. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                create_record();
                break;
            case 2:
                search_record();
                break;
            case 3:
                eva();
                break;
            case 4:
                modify_record();
                break;
            case 5:
                delete_record();
                break;
            case 6:
                display_record();
                break;
            case 7:
                see_detail(str1);
                break;
            case 8:
                return;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}