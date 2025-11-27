#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100

struct Employee
{
    char empId[20];
    char name[50];
    char position[15];
    double baseSalary;
    int workDay;
};

struct TimeSheet
{
    char logId[20];
    char empId[20];
    char date[20];
    char status[10];
};
//-----------STRUCTURE
struct Employee list[MAX];  // list 
struct TimeSheet sheet[MAX]; // cham cong
//----------------------------------

//void deleteEmployeev2(struct Employee list[], int *n);    // ver 1 khong confirm



//-------------- MAIN FUNCS --------------
void bubblesortafterdisplay(struct Employee list[], int n);
void add_people(struct Employee list[], int *n);                                           // con tro la vung nho
void updateEmployee(struct Employee list[], int *n);                                       // cap nhat
void deleteEmployeev3(struct Employee list[], int *n);                                     // xoa nhan vien V3
void displayEmployeeList(struct Employee list[], int n);                                   // xem bang
void bubblesort(struct Employee list[], int n);                                            // sap xep nhan vien
void FINDEMPLOYEE(struct Employee list[], int n);                                          // tim nhan vien
void Time_Keeping(struct Employee list[], int n, struct TimeSheet sheet[], int *logCount); // cham cong
int isValidDate(char *date);                                                               // check 31 30 , 28 , 29
int EMPTYCHECKER(char *str);                                                               // ky tu space
int isFutureDate(int d, int m, int y);                                                     // check tuong lai
void getToday(int *d, int *m, int *y);                                                      // check hom nay
void timesheetviewer(struct Employee list[], int n,struct TimeSheet sheet[], int logCount);  // check cham cong
//------------------------------
void showBUBBLE_MENU()
{
    printf("\n \n ----------------------------\n");
    printf("1. Sap xep tang dan\n");
    printf("2. Sap xep giam dan\n");
}
void showmenu()
{
    printf("|        QUAN LY NHAN VIEN VA CHAM CONG       |");
    printf("\n| ==========================================  |\n");
    printf("|  1.Them nhan vien moi                       |\n");
    printf("|  2.Cap nhat ho so nhan vien                 |\n");
    printf("|  3.Xoa ho so nhan vien                      |\n");
    printf("|  4.Hien thi danh sach nhan vien             |\n");
    printf("|  5.Tim kiem nhan vien                       |\n");
    printf("|  6.Sap xep nhan vien                        |\n");
    printf("|  7.Cham cong ngay nhan vien                 |\n");
    printf("|  8.Xem bang cong nhan vien                  |\n");
    printf("|  9.Thoat                                    |\n");
    printf(" =============================================\n");
}

//--------------------------------------
int main()
{
    int logCount = 0;
    int n = 0;
    int choice;
    char choicebuffer[20];
    do
    {
        showmenu();
        printf("Moi ban nhap lua chon: ");
        while (1)
        {
            printf("\n chi duoc nhap so ");
            fgets(choicebuffer, sizeof(choicebuffer), stdin);
            choicebuffer[strcspn(choicebuffer, "\n")] = '\0'; // xoa newline

            if (sscanf(choicebuffer, "%d", &choice) == 1) // chuyen dinh char dang sang int
                break;

            printf("SAI DINH DANG , NHAP LAI\n");
        }
        //  scanf("%d", &choice);
        // getchar();

        switch (choice)
        {
        case 1:
            add_people(list, &n);
            fflush(stdin);
            break;
        case 2:
            updateEmployee(list, &n);
            fflush(stdin);
            break;
        case 3:
            //	deleteEmployee(list , &n);
            deleteEmployeev3(list, &n);
            fflush(stdin);
            break;
        case 4:
            displayEmployeeList(list, n);
            fflush(stdin);
            break;
        case 5:
            FINDEMPLOYEE(list, n);
            fflush(stdin);
            // printf("ss");

            break;
        case 6:
            bubblesort(list, n);
            fflush(stdin);
            break;
        case 7:
            Time_Keeping(list, n, sheet, &logCount);
            fflush(stdin);
            break;
        case 8 : 
            timesheetviewer(list, n, sheet, logCount);
            fflush(stdin);
			break;
            
        default:
            printf("\nKhong hop le!\n \n");
        }
    } while (choice != 9);

    return 0;
}
 // CASE 4
void displayEmployeeList(struct Employee list[], int n)
{
    if (n == 0)
    {
        printf("DANH SACH DANG TRONG.\n");
        return;
    }

    int perPage = 3;
    int totalPages = (n + perPage - 1) / perPage;
    int page;
    char input[20];

    while (1)
    {
        printf("SO TRANG MUON XEM 1 - %d: ", totalPages);

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        // --- KHÔNG ĐƯỢC ĐỂ TRỐNG ---
        if (strlen(input) == 0)
        {
            printf("Khong duoc de trong. Vui long nhap so trang.\n");
            continue;
        }

        // --- PHẢI LÀ SỐ ---
        int valid = 1;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))  // check co phai de so
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("SAI DINH DANG / SO TRANG KHONG HOP LE\n");
            continue;
        }

        // --- chuyen so
        page = 0;
        for (int i = 0; i < strlen(input); i++)
        {
            page = page * 10 + (input[i] - '0');
        }

        if (page >= 1 && page <= totalPages)
            break;

        printf("So trang khong hop le. Vui long nhap lai.\n");
    }

    // ======= IN BẢNG =======
    printf("\n===== DANH SACH NHAN VIEN (Trang %d / %d) =====\n", page, totalPages);
    printf("+--------+----------------------+-----------------+---------------+-------------+\n");
    printf("| MA NV  | TEN NV               | CHUC VU         | LUONG CO BAN  | NGAY CONG   |\n");
    printf("+--------+----------------------+-----------------+---------------+-------------+\n");

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > n)
        end = n;

    for (int i = start; i < end; i++)
    {
        printf("| %-6s | %-20s | %-15s | %-13.0lf | %-11d |\n",
               list[i].empId,
               list[i].name,
               list[i].position,
               list[i].baseSalary,
               list[i].workDay);
    }

    printf("+--------+----------------------+-----------------+---------------+-------------+\n");
}

// CASE 2
void updateEmployee(struct Employee list[], int *n)
{
    if (*n == 0)
    {
        printf("\n \n KHONG THE CAP NHAT - DANH SACH TRONG\n");
        return;
    }
    char id[20];
    int pos = -1;

    // ID
    while (1)
    {
        printf("Nhap ID nhan vien can cap nhat: ");
        fgets(id, 20, stdin);
        id[strcspn(id, "\n")] = '\0';

        if (strlen(id) == 0)
        {
            printf("ID khong duoc de trong!\n");
            continue;
        }

        // tim vi tri
        pos = -1;
        for (int i = 0; i < *n; i++)
        {
            if (strcmp(list[i].empId, id) == 0)
            {
                pos = i;
                break;
            }
        }

        if (pos == -1)
        {
            printf("\n \n ID KHONG TON TAI.\n");
            return;
        }

        break;
    }

    printf("\n--- Cap nhat thong tin cho nhan vien %s ---\n", list[pos].name);

    // ===== CHUC VU=====
    while (1)
    {
        printf("Nhap CHUC VU MOI : ");
        fgets(list[pos].position, 15, stdin);
        list[pos].position[strcspn(list[pos].position, "\n")] = '\0';

        if (strlen(list[pos].position) == 0)
        {
            printf("Chuc vu khong duoc de trong!\n");
            continue;
        }

        break;
    }

    // ===== CAP NHAT LUONG =====
    while (1)
    {
        char buffer[20];
        printf("Nhap luong co ban moi: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (strlen(buffer) == 0 || buffer[0] == '\n')
        {
            printf("Luong khong duoc de trong!\n");
            continue;
        }

        double salary;
        if (sscanf(buffer, "%lf", &salary) != 1)
        {
            printf("Nhap sai dinh dang! Hay nhap so.\n");
            continue;
        }

        if (salary <= 0)
        {
            printf("Luong phai lon hon 0!\n");
            continue;
        }

        list[pos].baseSalary = salary;
        break;
    }

    // ===== NGAY CONG =====
    while (1)
    {
        char buffer[20];
        printf("Nhap ngay cong moi: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (strlen(buffer) == 0 || buffer[0] == '\n')
        {
            printf("Ngay cong khong duoc de trong!\n");
            continue;
        }

        int days;
        if (sscanf(buffer, "%d", &days) != 1)
        {
            printf("Nhap sai dinh dang! Hay nhap so.\n");
            continue;
        }

        if (days < 0 || days > 31)
        {
            printf("Ngay cong phai tu 0 den 31!\n");
            continue;
        }

        list[pos].workDay = days;
        break;
    }

    printf("Cap nhat thong tin thanh cong!\n");
}
 
 // CASE 1
void add_people(struct Employee list[], int *n)
{
    if (*n >= MAX)
    { // CHECK MANG
        printf("Danh sach nhan vien da day, khong the them!\n");
        return;
    }

    char buffer[20]; // generic buffer , luu de copy ra cho khac

    // ID ---
    while (1)
    {
        printf("Nhap ma nhan vien: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (EMPTYCHECKER(buffer))
        {
            printf("Ma nhan vien khong duoc trong!\n");
            continue;
        }

        int exists = 0;
        for (int i = 0; i < *n; i++)
        {
            if (strcmp(list[i].empId, buffer) == 0)
            {
                exists = 1;
                break;
            }
        }
        if (exists)
        {
            printf("Ma nhan vien da ton tai! Nhap lai.\n");
            continue;
        }

        strcpy(list[*n].empId, buffer);
        break;
    }

    // --- NHAP TEN ---
    while (1)
    {
        printf("Ten nhan vien: ");
        fgets(list[*n].name, sizeof(list[*n].name), stdin);

        if (EMPTYCHECKER(list[*n].name))
        {
            printf("Ten nhan vien khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // --- CHUC VU ---
    while (1)
    {
        printf("Chuc vu nhan vien: ");
        fgets(list[*n].position, sizeof(list[*n].position), stdin);

        if (EMPTYCHECKER(list[*n].position))
        {
            printf("Chuc vu khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // --- NHAP LUONG ---
    while (1)
    {
        printf("Luong co ban: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (EMPTYCHECKER(buffer))
        {
            printf("Luong khong duoc de trong! Nhap lai.\n");
            continue;
        }

        double salary;
        if (sscanf(buffer, "%lf", &salary) != 1)
        {
            printf("Nhap sai dinh dang! Nhap lai.\n");
            continue;
        }

        if (salary <= 0)
        {
            printf("Luong khong hop le! Nhap lai.\n");
            continue;
        }

        list[*n].baseSalary = salary;
        break;
    }

    // --- NHAP SO NGAY CONG ---
    while (1)
    {
        printf("Nhap ngay cong (de trong = 0): ");
        fgets(buffer, sizeof(buffer), stdin);

        if (EMPTYCHECKER(buffer))
        {
            list[*n].workDay = 0;
            break;
        }

        int days;
        if (sscanf(buffer, "%d", &days) != 1)
        {
            printf("Nhap sai dinh dang! Nhap lai.\n");
            continue;
        }

        if (days < 0 || days > 31)
        {
            printf("Ngay cong phai tu 0 den 31!\n");
            continue;
        }

        list[*n].workDay = days;
        break;
    }

    (*n)++; // them size
    printf("Them nhan vien thanh cong!\n");
}
// CASE 3 V1
void deleteEmployeev2(struct Employee list[], int *n)
{
    char deleteEmpId[20];
    int pos = -1;

    if (*n == 0)
    {
        printf("DANH SACH RONG! KHONG THE XOA!\n");
        return;
    }

    // NHAP NHAN VIEN
    while (1)
    {
        printf("MA NHAN VIEN MUON XOA: ");
        fgets(deleteEmpId, 20, stdin);
        deleteEmpId[strcspn(deleteEmpId, "\n")] = '\0';

        if (strlen(deleteEmpId) == 0)
        {
            printf("Ma nhan vien khong duoc de trong.\n");
            continue;
        }

        pos = -1;
        for (int i = 0; i < *n; i++)
        {
            if (strcmp(list[i].empId, deleteEmpId) == 0)
            {
                pos = i;
                break;
            }
        }

        if (pos == -1)
        {
            printf("KHONG tim thay nhan vien co ma %s\n", deleteEmpId);
            return;
        }

        break;
    }

    for (int i = pos; i < (*n) - 1; i++)
    {
        list[i] = list[i + 1];
    }
    (*n)--; // tru mang

    printf("Xoa nhan vien %s thanh cong.\n", deleteEmpId);
}
 // CASE 3
void deleteEmployeev3(struct Employee list[], int *n)
{
    char deleteEmpId[20];
    int pos = -1;

    if (*n == 0)
    {
        printf("DANH SACH RONG! KHONG THE XOA!\n");
        return;
    }

    // Nhập mã nhân viên cần xoá
    while (1)
    {
        printf("MA NHAN VIEN MUON XOA: ");
        fgets(deleteEmpId, 20, stdin);
        deleteEmpId[strcspn(deleteEmpId, "\n")] = '\0';

        if (strlen(deleteEmpId) == 0)
        {
            printf("Ma nhan vien khong duoc de trong.\n");
            continue;
        }

        pos = -1;
        for (int i = 0; i < *n; i++)
        {
            if (strcmp(list[i].empId, deleteEmpId) == 0)
            {
                pos = i;
                break;
            }
        }

        if (pos == -1)
        {
            printf("KHONG tim thay nhan vien co ma %s\n", deleteEmpId);
            return;
        }

        break;
    }

    // BUFFER DE CHUYEN DINH DANG
    char confirmStr[10];
    int confirm; // tu convert

    while (1)
    {
        printf("BAN CO MUON XOA NHAN VIEN %s KHONG? (1 = XOA, 2 = THOI): ", deleteEmpId);
        fgets(confirmStr, sizeof(confirmStr), stdin);
        confirmStr[strcspn(confirmStr, "\n")] = '\0';

        if (strlen(confirmStr) == 0)
        {
            printf("Khong duoc de trong. Vui long nhap 1 hoac 2.\n");
            continue;
        }

        // Kiểm tra phải là 1 ký tự số duy nhất
        if (strlen(confirmStr) != 1 || !isdigit(confirmStr[0]))
        {
            printf("Chi duoc nhap 1 hoac 2.\n");
            continue;
        }

        // Tự chuyển char -> số
        confirm = confirmStr[0] - '0';

        if (confirm != 1 && confirm != 2)
        {
            printf("Chi duoc nhap 1 hoac 2.\n");
            continue;
        }

        break;
    }

    if (confirm == 2)
    {
        printf("Huy thao tac xoa.\n");
        return;
    }

    // -------- TIẾN HÀNH XÓA --------
    for (int i = pos; i < (*n) - 1; i++)
    {
        list[i] = list[i + 1];
    }
    (*n)--;

    printf("Xoa nhan vien %s thanh cong.\n", deleteEmpId);
}

 // CASE 6
void bubblesort(struct Employee list[], int n)
{

    int bubblechoice; // chon tang dan giam dan

    if (n == 0)
    {
        printf("\n DANH SACH HIEN DANG RONG\n");
        return;
    }
    if (n == 1)
    {
        printf("\nCHUA CO DU NHAN VIEN DE SAP XEP\n");
        return;
    }

    while (1)
    {
        showBUBBLE_MENU();
        printf("Nhap lua chon cua ban: ");

        char buffer[20];
        fgets(buffer, sizeof(buffer), stdin);

        // kiểm tra rỗng
        if (buffer[0] == '\n')
        {
            printf("KHONG HOP LE .... NHAP LAI...\n");
            continue;
        }

        // kiểm tra có phải số hay không
        if (sscanf(buffer, "%d", &bubblechoice) != 1) // sscanf doc du lieu tu bo dem
        {
            printf("KHONG HOP LE..... NHAP LAI...\n");
            continue;
        }

        // kiểm tra số có thuộc 1 hoặc 2 không
        if (bubblechoice != 1 && bubblechoice != 2)
        {
            printf("Lua chon khong hop le! Nhap lai.\n");
            continue;
        }

        break; // HOP LE
    }

    // sorter
    if (bubblechoice == 1)
    {
        printf("Da chon tang dan\n");
        for (int times = 0; times < n - 1; times++)
        {
            for (int indexer = 0; indexer < n - times - 1; indexer++)
            {
                if (list[indexer].baseSalary > list[indexer + 1].baseSalary)
                {
                    struct Employee temp = list[indexer];
                    list[indexer] = list[indexer + 1];
                    list[indexer + 1] = temp;
                }
            }
        }   bubblesortafterdisplay(list, n);  
            return ;
    }
    else if (bubblechoice == 2)
    {
        printf("Da chon giam dan\n");
        for (int times = 0; times < n - 1; times++)
        {
            for (int indexer = 0; indexer < n - times - 1; indexer++)
            {
                if (list[indexer].baseSalary < list[indexer + 1].baseSalary)
                {
                    struct Employee temp = list[indexer];
                    list[indexer] = list[indexer + 1];
                    list[indexer + 1] = temp;
                }
            }
        }
    }   bubblesortafterdisplay(list, n);  
       return ; 
 }
// CASE 5
void FINDEMPLOYEE(struct Employee list[], int n)
{
    if (n == 0)
    {
        printf("DANH SACH HIEN DANG RONG..!\n");
        return;
    }

    char searchName[50];
    printf("NHAP TEN NHAN VIEN CAN TIM: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    if (strlen(searchName) == 0)
    {
        printf("Ten tim kiem KHONG DUOC de trong!\n");
        return;
    }

    // lowercase searchName
    char lowerSearch[50];
    int len = strlen(searchName);
    for (int i = 0; i < len; i++)
        lowerSearch[i] = tolower(searchName[i]);
    lowerSearch[len] = '\0';

    int found = 0;
    printf("\n===== KET QUA TIM KIEM =====\n");
    printf("%-10s | %-20s | %-12s | %-10s | %-5s\n",
           "Ma NV", "Ten NV", "Chuc vu", "Luong", "Cong");

    for (int i = 0; i < n; i++)
    {

        char lowerName[50];
        int len2 = strlen(list[i].name);
        for (int j = 0; j < len2; j++)
            lowerName[j] = tolower(list[i].name[j]);
        lowerName[len2] = '\0';

        if (strstr(lowerName, lowerSearch) != NULL)
        { // neu 0 thay thi tra ve on tro rong , neu thay se tra ve vi tri tim duoc
            printf("%-10s | %-20s | %-12s | %-10.2lf | %-5d\n",
                   list[i].empId,
                   list[i].name,
                   list[i].position,
                   list[i].baseSalary,
                   list[i].workDay);
            found = 1;
        }
    }

    if (!found)
        printf("KHONG TIM THAY NHAN VIEN CO TEN \"%s\"!\n", searchName);
}


// CASE 7
void Time_Keeping(struct Employee list[], int n, struct TimeSheet sheet[], int *logCount)
{
    if (n == 0)
    {
        printf("DANH SACH HIEN TAI DANG RONG!\n");
        return;
    }

    char checkInEmpId[20];
    char checkInDate[20];
    
    
    // MA NHAN VIEN 
    while (1)
    {
        printf("Nhap ma nhan vien can cham cong: ");
        fgets(checkInEmpId, sizeof(checkInEmpId), stdin);
        checkInEmpId[strcspn(checkInEmpId, "\n")] = '\0';

        if (strlen(checkInEmpId) == 0)
        {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // VI TRI NHAN VIEN
    int pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(list[i].empId, checkInEmpId) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay nhan vien co ma %s\n", checkInEmpId);
        return;
    }


    // CHAM CONG
    while (1)
    {
        printf("Nhap ngay cham cong (dd/mm/yyyy): ");
        fgets(checkInDate, sizeof(checkInDate), stdin);
        checkInDate[strcspn(checkInDate, "\n")] = '\0';

        if (strlen(checkInDate) == 0)
        {
            printf("Ngay cham cong khong duoc de trong!\n");
            continue;
        }

        if (!isValidDate(checkInDate))
        {
            printf("Ngay khong hop le! Dinh dang dd/mm/yyyy.\n");
            continue;
        }

        int d, m, y;
        sscanf(checkInDate, "%d/%d/%d", &d, &m, &y);

        if (isFutureDate(d, m, y))
        {
            printf("Khong the cham cong ngay trong tuong lai!\n");
            continue;
        }

        break;
    }


    //--------------- TRUNG LAP
    for (int i = 0; i < *logCount; i++)
    {
        if (strcmp(sheet[i].empId, checkInEmpId) == 0 &&
            strcmp(sheet[i].date, checkInDate) == 0)
        {
            printf("Nhan vien %s da duoc cham cong vao ngay nay roi!\n",
                   checkInEmpId);
            return;
        }
    }


   // SUCCESS
    list[pos].workDay++;

    sprintf(sheet[*logCount].logId, "LOG%03d", *logCount + 1);
    strcpy(sheet[*logCount].empId, checkInEmpId);
    strcpy(sheet[*logCount].date, checkInDate);
    strcpy(sheet[*logCount].status, "Di lam");

    (*logCount)++;

    printf("Cham cong ngay %s cho nhan vien %s thanh cong!\n",
           checkInDate, checkInEmpId);
}

int isValidDate(char *date)
{
    int d, m, y;

    if (sscanf(date, "%d/%d/%d", &d, &m, &y) != 3)
        return 0;

    if (d < 1 || d > 31)
        return 0;
    if (m < 1 || m > 12)
        return 0;
    if (y < 1900 || y > 3000)
        return 0;

    return 1;
}

int EMPTYCHECKER(char *str) // check xem co ki tu rong
{

    str[strcspn(str, "\n")] = '\0';
    /// len = 0 trong
    if (strlen(str) == 0)
        return 1;

    // null
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
            return 0; // hop le khong trong
    }

    return 1; // trong
}


void bubblesortafterdisplay(struct Employee list[], int n)
{
    if (n == 0)
    {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }

    printf("\n====================== DANH SACH NHAN VIEN SAU KHI SAP XEP ======================\n");
    printf("%-10s | %-20s | %-12s | %-10s | %-5s\n",
           "Ma NV", "Ten NV", "Chuc vu", "Luong", "Cong");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%-10s | %-20s | %-12s | %-10.2lf | %-5d\n",
               list[i].empId,
               list[i].name,
               list[i].position,
               list[i].baseSalary,
               list[i].workDay);
    }

    printf("Hien thi danh sach thanh cong!\n");
}
void timesheetviewer(struct Employee list[], int n,struct TimeSheet sheet[], int logCount)
{
    if (n == 0)
    {
        printf("Danh sach nhan vien dang rong, khong the xem bang cong!\n");
        return;
    }

    char viewEmpId[20];

    // ID CHECKER
    while (1)
    {
        printf("Nhap ma nhan vien can xem bang cong: ");
        fgets(viewEmpId, sizeof(viewEmpId), stdin);
        viewEmpId[strcspn(viewEmpId, "\n")] = '\0';

        if (strlen(viewEmpId) == 0)
        {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // CHECKER 2
    int exists = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(list[i].empId, viewEmpId) == 0)
        {
            exists = 1;
            break;
        }
    }

    if (!exists)
    {
        printf("Khong ton tai nhan vien co ma '%s'!\n", viewEmpId);
        return;
    }

    // LOG CHECKER
    printf("\n===== BANG CHAM CONG CUA NHAN VIEN %s =====\n", viewEmpId);
    printf("%-10s | %-12s | %-10s\n", "LogID", "Ngay cham", "Trang thai");
    printf("--------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < logCount; i++)
    {
        if (strcmp(sheet[i].empId, viewEmpId) == 0)
        {
            printf("%-10s | %-12s | %-10s\n",
                   sheet[i].logId,
                   sheet[i].date,
                   sheet[i].status);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Nhan vien nay chua co ban ghi cham cong nao!\n");
        return;
    }

    printf("--------------------------------------------\n");
    printf("Hien thi bang cham cong thanh cong!\n");
}

// HELPERS
void getToday(int *d, int *m, int *y) {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    *d = now.tm_mday;
    *m = now.tm_mon + 1;  // tháng bắt đầu từ 0
    *y = now.tm_year + 1900;
}

int isFutureDate(int d, int m, int y) {
    int td, tm, ty;
    getToday(&td, &tm, &ty);

    if (y > ty) return 1;
    if (y == ty && m > tm) return 1;
    if (y == ty && m == tm && d > td) return 1;

    return 0;
}
