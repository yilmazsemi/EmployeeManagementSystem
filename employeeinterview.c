#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_EMPLOYEES 1000

#define FILENAME "employees.txt"
#define TEMPFILE "temp.txt"
#define ADMINFILE "adminaccount.txt"
#define USERFILE "useraccount.txt"
#define ADMINANNUALFILE "annualdayrequest.txt"

struct EmployeeCard {
    char name[50];
    char surname[50];
    char id[10];
};

struct IDCards {
    
    char username[20];
    char password[20];
};

struct Employee{
    
    char name[50];
    char surname[50];
    char age[50];
    char title[50];
    char gender[50];
    char call[3];
    char country[50];
    char city[50];
    char id[20];
    int annual;
    float salary;
    char AnnualRequest[10];
};

struct EmployeeAnnual {
    
    char name[50];
    char surname[50];
    char startDay[10];
    char startMonth[10];
    char startYear[10];
    char finishDay[10];
    char finishMonth[10];
    char finishYear[10];
    char id[20];
    int requestedDay;
    int totalDay;
        
};


int daysInMonth(int month, int year);
int calculateTimeDifference(const char *startDay, const char *startMonth, const char *startYear, const char *finishDay, const char *finishMonth, const char *finishYear);
void removeEmployee();
void loginpage();
void userpage(char username[20]);
void adminpage(char username[20]);
int LineSelector(char username[20], FILE *file);
void Username_to_ID(char username[20],int LineNumber, FILE *file, struct EmployeeCard IDCard[1]);
void ID_to_Username(char ID[10], int LineNumber, FILE *file, struct IDCards IDCard[1]);
void ID_to_EmployeeInformation(char username[20],float updated_salary, int LineNumber);
void SalaryChangeEmployee();
void FileCopier();
void FileCopier_toAnnual();
void FileCopier_toUser();
void ID_to_EmployeeAnnualLeave(char username[20], char decision[10], int annual, int LineNumber);



//--------------------------------------------------------------------------------------------ADMINS-----------------------------------------------------------------------------------------------------

void addEmployee(struct Employee employees[], int *numEmployees) {
    if (*numEmployees < MAX_EMPLOYEES) {
        struct Employee newEmployee;
        struct IDCards ID;

        printf("Enter employee ID: ");
        scanf("%s", newEmployee.id);

        printf("Enter employee name: ");
        scanf("%s", newEmployee.name);
        
        printf("Enter employee surname: ");
        scanf("%s", newEmployee.surname);
        
        bool IsOkey = true;
        int choicefortitle;
        do {
        printf("Enter employee title: \n");
        printf("1. CEO\n");
        printf("2. CFO\n");
        printf("3. Project Manager\n");
        printf("4. Team Leader\n");
        printf("5. Engineer\n");
        printf("6. Intern\n");
        scanf("%d", &choicefortitle);
     

     switch (choicefortitle) {
                case 1:
                    strcpy(newEmployee.title, "CEO");
                    IsOkey = false;
                    break;
                case 2:
                    strcpy(newEmployee.title, "CFO");
                    IsOkey = false;
                    break;
                case 3:
                    strcpy(newEmployee.title, "Project Manager");
                    IsOkey = false;
                    break;
                case 4:
                    strcpy(newEmployee.title, "Team Leader");
                    IsOkey = false;
                    break;
                case 5:
                    strcpy(newEmployee.title, "Engineer");
                    IsOkey = false;
                    break;
                case 6:
                    strcpy(newEmployee.title, "Intern");
                    IsOkey = false;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }

        } while (IsOkey);
        
        printf("Enter employee age: ");
        scanf("%s", newEmployee.age);
        
        bool IsValid = true;
        int choiceforgender;
        do {
        printf("Enter employee gender: \n");
        printf("1. Male\n");
        printf("2. Female\n");
        scanf("%d", &choiceforgender);
     

     switch (choiceforgender) {
                case 1:
                    strcpy(newEmployee.gender, "Male");
                    strcpy(newEmployee.call, "Mr");
                    IsValid = false;
                    break;
                case 2:
                    strcpy(newEmployee.gender, "Female");
                    strcpy(newEmployee.call, "Ms");
                    IsValid = false;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }

        } while (IsValid);
        
        
        printf("Enter employee country: ");
        scanf("%s", newEmployee.country);
        
        printf("Enter employee city: ");
        scanf("%s", newEmployee.city);

        printf("Enter employee monthly salary: ");
        scanf("%f", &newEmployee.salary);
        
        printf("You have to create account for your new employee.\n\n");
        
        printf("Enter employee username: ");
        scanf("%s", ID.username);
        
        printf("Enter employee password: ");
        scanf("%s", ID.password);
        
        strcpy(newEmployee.AnnualRequest, "False");
        
    printf("We have completed entering information about the %s and %s username is %s\n", newEmployee.name, newEmployee.call, ID.username);

        employees[*numEmployees] = newEmployee;
        (*numEmployees)++;

        // Open the file in append mode
        FILE *file = fopen(FILENAME, "a");
        if (file != NULL) {
            // Write the new employee information to the file
            fprintf(file, "%s %s %s %s %s %s %s %s %d %.2f %s\n", newEmployee.id, newEmployee.title, newEmployee.name, newEmployee.surname, newEmployee.age, newEmployee.gender, newEmployee.country, newEmployee.city, 30, newEmployee.salary, newEmployee.AnnualRequest);

            // Close the file
            fclose(file);
        } else {
            printf("Error opening file for writing!\n");
        }
   
    
            // Open the file in append mode
        FILE *userfile = fopen(USERFILE, "a");
        if (userfile != NULL) {
            // Write the new employee information to the file
            fprintf(userfile, "%s %s\n", ID.username, ID.password);

            // Close the file
            fclose(userfile);
        } else {
            printf("Error opening file for writing!\n");
        }
        
            

     printf("Employee added successfully!\n");
    
    
    } else {
        printf("Maximum number of employees reached!\n");
    }
    
    
}

void removeEmployee() {

    char line[256];
    char line2[256];
    int lineNumber = 0;
    int currentLine = 0;
    int currentLine2 = 0;
    char employee_id[20];
      
        printf("Enter employee ID who you gonna remove: ");
        scanf("%s", employee_id);
    
       FILE *employeefile_r = fopen(FILENAME, "r");
       FILE *tempFile = fopen(TEMPFILE,"w");
       
    lineNumber = LineSelector(employee_id,employeefile_r);
       fclose(employeefile_r);
       FILE *employeefile_r2 = fopen(FILENAME, "r");
       
    while (fgets(line, 256, employeefile_r2) != NULL) {
            
            currentLine++;
            
        if (currentLine != lineNumber) {
        
            fputs(line, tempFile);
        
        }
    }
    
   
    fclose(employeefile_r2);
    fclose(tempFile);
    FileCopier();
    
    FILE *userfile_r = fopen(USERFILE, "r");
    FILE *tempFile_2 = fopen(TEMPFILE,"w");
           
         while (fgets(line2, 256, userfile_r) != NULL) {
               
        currentLine2++;
                    
        if (currentLine2 != lineNumber) {
        
            fputs(line2, tempFile_2);
        
        }
    }
    fclose(userfile_r);
    fclose(tempFile_2);
    FileCopier_toUser();
    
}

void SalaryChangeEmployee() {

    char line[256];
      int lineNumber = 0;
      int currentLine = 0;
      
      char employee_id[20];
      float updated_salary;
      
      char name[20];
      char surname[20];
      char id[10];

        printf("Enter employee ID who you gonna change salary: ");
        scanf("%s", employee_id);
        
        printf("Enter employee`s new salary: ");
        scanf("%f", &updated_salary);
    

        //FILE *tempfile_w = fopen(TEMPFILE, "a");
        FILE *employeefile_r = fopen(FILENAME, "r");
        
    lineNumber = LineSelector(employee_id,employeefile_r);
    
    //printf("ID is in %d \n", LineSelector(employee_id,employeefile_r));
    fclose(employeefile_r);

    ID_to_EmployeeInformation(employee_id , updated_salary,lineNumber);

}


void DisplayAnnualDayRequests() {


    int currentLine = 0;
    int lineNumber = 0;
    char lineforemployee[256];
    char line[256];
    char line2[256];
    char line3[256];
    struct EmployeeAnnual employeeAnnual[1];
    struct Employee employee[1];
    FILE *annualfile = fopen(ADMINANNUALFILE, "r");
    FILE *employeefile = fopen(FILENAME, "r");
    
    
    

    
    if (annualfile != NULL) {
    
        printf("\nEmployee List from File:\n");
        printf("ID\t\tName\t\tSurname\t\tStart Date\tFinish Date\tRequested Days\n");
        while (fscanf(annualfile, "%s %s %s %s %s %s %s %s %s %d", employeeAnnual[0].id, employeeAnnual[0].name, employeeAnnual[0].surname,  employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, &employeeAnnual[0].requestedDay) == 10) {
        
            printf("%s\t\t%-15s\t%-15s\t%-2s.%-2s.%-4s\t%-2s.%-2s.%-4s\t%d\n", employeeAnnual[0].id, employeeAnnual[0].name, employeeAnnual[0].surname, employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, employeeAnnual[0].requestedDay);
                   
         }
        
    } else {
        printf("Error opening file for reading!\n");
    }
    
    
    
    
    
    
        fclose(annualfile);
        fclose(employeefile);
    
    FILE *annualfile_G = fopen(ADMINANNUALFILE, "r");

  while (fgets(line, sizeof(line), annualfile_G) != NULL) {

     FILE *employeefile_G = fopen(FILENAME, "r");

      
     sscanf(line, "%s %s %s %s %s %s %s %s %s %d", employeeAnnual[0].id, employeeAnnual[0].name, employeeAnnual[0].surname,  employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, &employeeAnnual[0].requestedDay);

        lineNumber = LineSelector(employeeAnnual[0].id,employeefile_G);


	

	fclose(employeefile_G);
     	FILE *employeefile_G1 = fopen(FILENAME, "r");
        if (employeefile_G1 != NULL) {

        while (fgets(lineforemployee, sizeof(lineforemployee), employeefile_G1) != NULL) {

		currentLine++;
	    	if(currentLine == lineNumber)
	    	{

      		sscanf(lineforemployee,"%s %s %s %s %s %s %s %s %d %f %s", employee[0].id,employee[0].title, employee[0].name, employee[0].surname, employee[0].age, employee[0].gender, employee[0].country, employee[0].city, &employee[0].annual, &employee[0].salary, employee[0].AnnualRequest);
          
         	}         
         }
        
    } else {
        printf("Error opening file for reading!\n");
    }
     currentLine = 0;
     fclose(employeefile_G1);
    
    
        printf("\n---------------------------------------------------------------------------------------------------\n");
        printf(")%s have an annual leave request from %s.%s.%s to %s.%s.%s, when you accept it is going to finish in %d days. \n)Total Days: %d \n", employeeAnnual[0].name, employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, employeeAnnual[0].requestedDay, employee[0].annual);
    
    printf(")This is the ID of the checked holiday leave: %s \n", employeeAnnual[0].id);

  
    
    printf(")The Vacation leave you are currently checking is %d in the Employee List \n",lineNumber);
    
        
        bool IsValid = true;
        int choiceforselect;
        do {
        printf(")Decision \n");
        printf(")1. Accept\n");
        printf(")2. Reject\n");
        printf(")Your Decision: ");
        scanf("%d", &choiceforselect);
     


     switch (choiceforselect) {
                case 1:
                    strcpy(employee[0].AnnualRequest, "True");
                    employee[0].annual -= employeeAnnual[0].requestedDay;
                    IsValid = false;
                    break;
                case 2:
                    strcpy(employee[0].AnnualRequest, "False");
                    IsValid = false;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
            

                    } while (IsValid);
              printf("\n---------------------------------------------------------------------------------------------------\n");


          FILE *tempFile = fopen(TEMPFILE,"w");
       FILE *annualfile_3 = fopen(ADMINANNUALFILE, "r");
    while (fgets(line3, sizeof(line3), annualfile_3) != NULL) {

        if (strstr(line3, employeeAnnual[0].id) == NULL) {
            fputs(line3, tempFile);
        
        }
          }
          fclose(annualfile_3);
          fclose(tempFile);
          FileCopier_toAnnual();
 
          ID_to_EmployeeAnnualLeave(employeeAnnual[0].id , employee[0].AnnualRequest, employee[0].annual, lineNumber);


     
    }
    fclose(annualfile_G);

}

void DisplayEmployeesFromFile() {

    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        printf("\nEmployee List from File:\n");
        printf("ID\tTitle\t\tName\t\tSurname\t\tAge\tGender\t\tCountry\t\tCity\t\tAnnual\tSalary\n");
        printf("--------------------------------------------------------------------------------------------------------------------------\n");

        struct Employee employee;
        
        while (fscanf(file, "%s %s %s %s %s %s %s %s %d %f %s",  employee.id, employee.title, employee.name, employee.surname, employee.age, employee.gender, employee.country, employee.city, &employee.annual, &employee.salary, employee.AnnualRequest) == 11) {
        printf("%s\t%-15s\t%-15s\t%-15s\t%-3s\t%-6s\t\t%-15s\t%-15s\t%d\t%.2f\n\n",
                   employee.id, employee.title, employee.name, employee.surname, employee.age, employee.gender, employee.country, employee.city, employee.annual, employee.salary);
       
        printf("Annual Request: %s\n",employee.AnnualRequest);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
                    }
        } else {
        printf("Error opening file for reading!\n");
        }

        fclose(file);
}

//------------------------------------------------------------------------------------------USERS--------------------------------------------------------------------------------------------------------

void EmployeeAnnualDayRequest(char username[20]) {
    struct EmployeeAnnual employeeAnnual;
    char line[256];
    int lineNumber = 0;
    int currentLine = 0;
    int requestedDays, remainingAnnualLeave;
    int startYear, finishYear;
    int startMonth, finishMonth;
    char empty[10];
    

    FILE *accountfile = fopen(USERFILE, "r");

    if (accountfile == NULL) {
        perror("No Records Found");
        return;
    } else {
        while (fgets(line, 256, accountfile) != NULL) {
            lineNumber++;
            if (strstr(line, username) != NULL) {
                break;
            }
        }
        fclose(accountfile);
    }

    FILE *employeefile = fopen(FILENAME, "r");
    if (employeefile == NULL) {
        perror("No Records Found");
        return;
    }

    while (fgets(line, sizeof(line), employeefile) != NULL) {
        currentLine++;
        if (currentLine == lineNumber) {
            sscanf(line, "%s %s %s %s", employeeAnnual.id, empty, employeeAnnual.name, employeeAnnual.surname);
        }
    }

    fclose(employeefile);

   // Start Year Kontrolü
    do {
        printf("Enter start year (2000 or later): ");
        scanf("%s", employeeAnnual.startYear);

        startYear = atoi(employeeAnnual.startYear);

        if (startYear < 2000 || strlen(employeeAnnual.startYear) != 4) {
            printf("Invalid input. Please enter a valid 4-digit year of 2000 or later.\n");
        }
    } while (startYear < 2000 || strlen(employeeAnnual.startYear) != 4);

    // Finish Year Kontrolü
    do {
        printf("Enter finish year (equal to or greater than start year): ");
        scanf("%s", employeeAnnual.finishYear);

        finishYear = atoi(employeeAnnual.finishYear);

        if (finishYear < startYear || strlen(employeeAnnual.finishYear) != 4 || finishYear <= 0) {
            printf("Invalid input. Please enter a valid 4-digit positive year equal to or greater than start year.\n");
        }
    } while (finishYear < startYear || strlen(employeeAnnual.finishYear) != 4 || finishYear <= 0);
    
    // Start Day Kontrolü
do {
    printf("Enter start day (01-31): ");
    scanf("%s", employeeAnnual.startDay);

    if (!(atoi(employeeAnnual.startDay) >= 1 && atoi(employeeAnnual.startDay) <= 31) || strlen(employeeAnnual.startDay) != 2) {
        printf("Invalid input. Please enter a valid two-digit day between 01 and 31.\n");
    }
} while (!(atoi(employeeAnnual.startDay) >= 1 && atoi(employeeAnnual.startDay) <= 31) || strlen(employeeAnnual.startDay) != 2);

// Finish Day Kontrolü
do {
    printf("Enter finish day (01-31, not included in the annual leave): ");
    scanf("%s", employeeAnnual.finishDay);

    if (!(atoi(employeeAnnual.finishDay) >= 1 && atoi(employeeAnnual.finishDay) <= 31) || strlen(employeeAnnual.finishDay) != 2) {
        printf("Invalid input. Please enter a valid two-digit day between 01 and 31.\n");
    }
} while (!(atoi(employeeAnnual.finishDay) >= 1 && atoi(employeeAnnual.finishDay) <= 31) || strlen(employeeAnnual.finishDay) != 2);

do {
    printf("Enter start month (01-12): ");
    scanf("%s", employeeAnnual.startMonth);

    startMonth = atoi(employeeAnnual.startMonth);

    if (!(startMonth >= 1 && startMonth <= 12) || strlen(employeeAnnual.startMonth) != 2) {
        printf("Invalid input. Please enter a valid two-digit month between 01 and 12.\n");
    }
} while (!(startMonth >= 1 && startMonth <= 12) || strlen(employeeAnnual.startMonth) != 2);

// Finish Month Kontrolü
do {
    printf("Enter finish month (01-12): ");
    scanf("%s", employeeAnnual.finishMonth);

    finishMonth = atoi(employeeAnnual.finishMonth);

    if (!(finishMonth >= 1 && finishMonth <= 12) || strlen(employeeAnnual.finishMonth) != 2) {
        printf("Invalid input. Please enter a valid two-digit month between 01 and 12.\n");
    }
} while (!(finishMonth >= 1 && finishMonth <= 12) || strlen(employeeAnnual.finishMonth) != 2);

   

    FILE *EmpAnnualfile = fopen(ADMINANNUALFILE, "a");

    if (EmpAnnualfile != NULL) {
        // Talep edilen izin gün sayısını hesapla
        requestedDays = calculateTimeDifference(employeeAnnual.startDay, employeeAnnual.startMonth, employeeAnnual.startYear,
                                                employeeAnnual.finishDay, employeeAnnual.finishMonth, employeeAnnual.finishYear);

        // Eğer talep edilen gün sayısı 30'dan fazla ise
        if (requestedDays > 30) {
            printf("Warning: You cannot request more than 30 days of annual leave. Your request has been adjusted to 30 days.\n");
            requestedDays = 30;
        }

        // Toplam izin hakkını güncelle
        remainingAnnualLeave = 30 - requestedDays;

        // Ekrana yazdır
        printf("Requested Annual Leave: %d day%s\n", requestedDays, (requestedDays > 1) ? "s" : "");
        printf("Remaining Annual Leave: %d day%s\n", remainingAnnualLeave, (remainingAnnualLeave > 1) ? "s" : "");

        // Dosyaya yazdır
        fprintf(EmpAnnualfile, "%s %s %s %s %s %s %s %s %s %d %d\n",
            employeeAnnual.id, employeeAnnual.name, employeeAnnual.surname,
            employeeAnnual.startDay, employeeAnnual.startMonth, employeeAnnual.startYear,
            employeeAnnual.finishDay, employeeAnnual.finishMonth, employeeAnnual.finishYear,
            requestedDays, remainingAnnualLeave);

        fclose(EmpAnnualfile);
        printf("Employee annual leave request added successfully!\n");
    } else {
        printf("Error opening file for writing!\n");
    }
}


//------------------------------------------------------------------------------------------USEFULL FUNC--------------------------------------------------------------------------------------------------------
int LineSelector(char username[20], FILE *file)
{
    int LineNumber = 0;
    char line[256];
    if (file == NULL) {
        perror("File opening error");
        return -1;

        }
            while (fgets(line, sizeof(line), file) != NULL) {
         
            LineNumber++;
        
            if (strstr(line, username) != NULL) {
                return LineNumber;
            }
            }
        
    return -1;
}


void Username_to_ID(char username[20],int LineNumber, FILE *file, struct EmployeeCard IDCard[1])
{
    char line[256];
    int currentLine = 0;
        if (file == NULL) {
        perror("File opening error");
        return;
        }

        while (fgets(line, sizeof(line), file) != NULL) {
        currentLine++;
        if (currentLine == LineNumber) {
            sscanf(line, "%s %s %s", IDCard[0].id, IDCard[0].name, IDCard[0].surname);
        }
        }
        fclose(file);
}

int daysInMonth(int month, int year) {
    // Ayın gün sayısını döndürür
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // Şubat, artık yıl kontrolü
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                return 29;
            else
                return 28;
        default:
            return -1; // Hata durumu
    }
}

int calculateTimeDifference(const char *startDay, const char *startMonth, const char *startYear,
                             const char *finishDay, const char *finishMonth, const char *finishYear) {
    struct tm tmStart = {0}, tmEnd = {0};

    // Başlangıç tarihini ayarla
    sscanf(startYear, "%d", &tmStart.tm_year);
    sscanf(startMonth, "%d", &tmStart.tm_mon);
    sscanf(startDay, "%d", &tmStart.tm_mday);

    // Bitiş tarihini ayarla
    sscanf(finishYear, "%d", &tmEnd.tm_year);
    sscanf(finishMonth, "%d", &tmEnd.tm_mon);
    sscanf(finishDay, "%d", &tmEnd.tm_mday);

    // Zamanı saniyeye çevir
    time_t timeStart = mktime(&tmStart);
    time_t timeEnd = mktime(&tmEnd);

    // Saniyeler arasındaki farkı gün olarak hesapla
    return (int)difftime(timeEnd, timeStart) / (60 * 60 * 24);
}

void ID_to_EmployeeInformation(char username[20], float updated_salary, int LineNumber)
{
        char line[256];
        int currentLine = 0;
        struct Employee Temp[1];
        FILE *infofile = fopen(FILENAME, "r");
        FILE *tempfile = fopen(TEMPFILE, "a");
        if (infofile == NULL) {
        perror("File opening error");
        return;
    }
    if (tempfile == NULL) {
        perror("File opening error");
           return;
    }
    while (fgets(line, sizeof(line), infofile) != NULL) {
        currentLine++;
        if (currentLine == LineNumber) {
                         sscanf(line, "%s %s %s %s %s %s %s %s %d %f %s", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname,  Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, &Temp[0].annual, &Temp[0].salary, Temp[0].AnnualRequest);
      
                   fprintf(tempfile,"%s %s %s %s %s %s %s %s %d %f %s\n", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname, Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, Temp[0].annual, updated_salary, Temp[0].AnnualRequest);
                    

        } else {

        fputs(line, tempfile);
        }
    }
        fclose(tempfile);
    fclose(infofile);
    FileCopier();
}
    

void ID_to_EmployeeAnnualLeave(char username[20], char decision[10], int annual, int LineNumber)
{
    char line[256];
    int currentLine = 0;
    struct Employee Temp[1];

        FILE *infofile = fopen(FILENAME, "r");
        FILE *tempfile = fopen(TEMPFILE, "a");
        if (infofile == NULL) {
        perror("File opening error");
        return;
    }
    if (tempfile == NULL) {
        perror("File opening error");
           return;
    }

    while (fgets(line, sizeof(line), infofile) != NULL) {
        
        currentLine++;
    
        if (currentLine == LineNumber) {
            
                         sscanf(line, "%s %s %s %s %s %s %s %s %d %f %s", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname,  Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, &Temp[0].annual, &Temp[0].salary, Temp[0].AnnualRequest);
      
                   fprintf(tempfile,"%s %s %s %s %s %s %s %s %d %f %s\n", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname, Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, annual, Temp[0].salary, decision);
                    
        } else {
        fputs(line, tempfile);
        }
    }
        fclose(tempfile);
    fclose(infofile);
    FileCopier();
}


void ID_to_Username(char ID[10], int LineNumber, FILE *file, struct IDCards IDCard[1])
{
    char line[256];
        if (file == NULL) {
        perror("File opening error");
        return;
        }

        while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, ID) != NULL) {
        
        sscanf(line, "%s %s", IDCard[0].username, IDCard[0].password);
        }
        }
        fclose(file);
}


void FileCopier()
{

    char ch;

    // Open the source file for reading
    FILE *sourceFile = fopen(FILENAME, "w");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing
    FILE *destinationFile = fopen(TEMPFILE, "r");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
      
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, sourceFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");
    
    fclose(fopen(TEMPFILE,"w"));
    return;
 
}

void FileCopier_toAnnual()
{
    char ch;

    // Open the source file for reading
    FILE *sourceFile = fopen(ADMINANNUALFILE, "w");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing
    FILE *destinationFile = fopen(TEMPFILE, "r");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
      
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, sourceFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");
    
    fclose(fopen(TEMPFILE,"w"));
    return;
 
}

void FileCopier_toUser()
{
    char ch;

    // Open the source file for reading
    FILE *sourceFile = fopen(USERFILE, "w");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing
    FILE *destinationFile = fopen(TEMPFILE, "r");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
      
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, sourceFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");
    
    fclose(fopen(TEMPFILE,"w"));
    return;
 
}
//------------------------------------------------------------------------------------------PAGES--------------------------------------------------------------------------------------------------------



void adminpage(char username[20]) {
    
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;
    
   do {
        printf("\n%s Admin Page \n\n", username);
        printf("1. Add Employee\n");
        printf("2. Remove Employee\n");
        printf("3. Display Employees\n");
        printf("4. Annual Day Requests\n");
        printf("5. Employee Salary Change\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &numEmployees);
                break;
            case 2:
                removeEmployee();
                break;
            case 3:
                DisplayEmployeesFromFile();
                break;
            case 4:
                DisplayAnnualDayRequests();
                break;
            case 5:
                SalaryChangeEmployee();
                break;
            case 6:
                loginpage();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

}

void userpage(char username[20]) {


    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;
    

   do {
        printf("\n%s User Page \n\n", username);
        printf("1. Annual Day Request\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                EmployeeAnnualDayRequest(username);
                break;
            case 2:
                loginpage();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 2);
   
}

void loginpage() {
    struct IDCards ID;
    int choice;
    
   do {
        printf("\nEmployee Detect System\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
            char username[20];
            char password[20];

        switch (choice) {
            case 1:
            printf("Enter your username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);
            
            FILE *adminfile = fopen(ADMINFILE, "r");
            if (adminfile != NULL) {
                while (fscanf(adminfile, "%s %s", ID.username, ID.password) == 2) {
                    if (strcmp(username, ID.username) == 0 && strcmp(password, ID.password) == 0) {
                        fclose(adminfile);
                        adminpage(ID.username);
                    }
                }
                printf("Invalid username or password!\n");
                fclose(adminfile);
            } else {
                printf("Error opening file for reading!\n");
            }
            
            break;
                break;
            case 2:

            printf("Enter your username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);
            
            FILE *userfile = fopen(USERFILE, "r");
            if (userfile != NULL) {
                while (fscanf(userfile, "%s %s", ID.username, ID.password) == 2) {
                    if (strcmp(username, ID.username) == 0 && strcmp(password, ID.password) == 0) {
                        fclose(userfile);
                        userpage(ID.username);
                    }
                }

                printf("Invalid username or password!\n");
                fclose(userfile);
            } else {
                printf("Error opening file for reading!\n");
            }
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

}

//------------------------------------------------------------------------------------------------------MAIN------------------------------------------------------------------------------------------
int main() {
    
    loginpage();

return 0;
}
