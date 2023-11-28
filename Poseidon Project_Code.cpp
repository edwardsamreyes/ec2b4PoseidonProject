#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_DAYS 7 // Maximum number of days for attendance

struct Date {
    int day;
    int month;
    int year;
};

struct AttendanceRecord {
    char studentName[50];
    struct Date dates[MAX_DAYS];
    int isPresent[MAX_DAYS];
    int totalDays;
};

struct StudentAttendanceSystem {
    struct AttendanceRecord attendanceRecords[MAX_STUDENTS];
    int recordCount;
};

void addAttendanceRecord(struct StudentAttendanceSystem *attendanceSystem, const char *studentName) {
    if (attendanceSystem->recordCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    struct AttendanceRecord *record = &(attendanceSystem->attendanceRecords[attendanceSystem->recordCount]);
    strcpy(record->studentName, studentName);
    memset(record->isPresent, -1, sizeof(record->isPresent));
    record->totalDays = 0;
    attendanceSystem->recordCount++;
}

void markAttendance(struct StudentAttendanceSystem *attendanceSystem, const char *studentName) {
    if (attendanceSystem->recordCount == 0) {
        printf("No students added yet!\n");
        return;
    }

    // Print all stored student names for debugging purposes
    printf("List of Students:\n");
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        printf("%d. %s\n", i + 1, attendanceSystem->attendanceRecords[i].studentName);
    }

    printf("Enter date (DD MM YYYY): ");
    struct Date currentDate;
    scanf("%d %d %d", &currentDate.day, &currentDate.month, &currentDate.year);

    int studentIndex = -1;
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        if (strcmp(attendanceSystem->attendanceRecords[i].studentName, studentName) == 0) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student not found!\n");
        return;
    }

    struct AttendanceRecord *record = &(attendanceSystem->attendanceRecords[studentIndex]);
    record->dates[record->totalDays] = currentDate;
    printf("Mark attendance for %s on %d/%d/%d (1 for present, 0 for absent): ", studentName, currentDate.day, currentDate.month, currentDate.year);
    scanf("%d", &record->isPresent[record->totalDays]);
    record->totalDays++;
}

void displayStudentAttendance(const struct StudentAttendanceSystem *attendanceSystem) {
    printf("List of Students with Attendance:\n");
    printf("---------------------------------\n");
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        printf("Student: %s\n", attendanceSystem->attendanceRecords[i].studentName);
        printf("Attendance:\n");
        for (int j = 0; j < attendanceSystem->attendanceRecords[i].totalDays; ++j) {
            printf("%d/%d/%d - %s\n", attendanceSystem->attendanceRecords[i].dates[j].day,
                   attendanceSystem->attendanceRecords[i].dates[j].month,
                   attendanceSystem->attendanceRecords[i].dates[j].year,
                   attendanceSystem->attendanceRecords[i].isPresent[j] == 1 ? "Present" : "Absent");
        }
        printf("---------------------------------\n");
    }
}

void editAttendanceRecord(struct StudentAttendanceSystem *attendanceSystem, const char *studentName) {
    if (attendanceSystem->recordCount == 0) {
        printf("No students added yet!\n");
        return;
    }

    printf("Enter date (DD MM YYYY) to edit attendance: ");
    struct Date editDate;
    scanf("%d %d %d", &editDate.day, &editDate.month, &editDate.year);

    int studentIndex = -1;
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        if (strcmp(attendanceSystem->attendanceRecords[i].studentName, studentName) == 0) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student not found!\n");
        return;
    }

    struct AttendanceRecord *record = &(attendanceSystem->attendanceRecords[studentIndex]);

    int dayIndex = -1;
    for (int j = 0; j < record->totalDays; ++j) {
        if (record->dates[j].day == editDate.day && record->dates[j].month == editDate.month && record->dates[j].year == editDate.year) {
            dayIndex = j;
            break;
        }
    }

    if (dayIndex == -1) {
        printf("Attendance for specified date not found!\n");
        return;
    }

    printf("Mark attendance for %s on %d/%d/%d (1 for present, 0 for absent): ", studentName, editDate.day, editDate.month, editDate.year);
    scanf("%d", &record->isPresent[dayIndex]);
}

void deleteAttendanceRecord(struct StudentAttendanceSystem *attendanceSystem, const char *studentName) {
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        if (strcmp(attendanceSystem->attendanceRecords[i].studentName, studentName) == 0) {
            for (int j = i; j < attendanceSystem->recordCount - 1; ++j) {
                attendanceSystem->attendanceRecords[j] = attendanceSystem->attendanceRecords[j + 1];
            }
            attendanceSystem->recordCount--;
            printf("Attendance record deleted for: %s\n", studentName);
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteAttendanceForDate(struct StudentAttendanceSystem *attendanceSystem, const char *studentName) {
    if (attendanceSystem->recordCount == 0) {
        printf("No students added yet!\n");
        return;
    }

    printf("Enter date (DD MM YYYY) to delete attendance: ");
    struct Date deleteDate;
    scanf("%d %d %d", &deleteDate.day, &deleteDate.month, &deleteDate.year);

    int studentIndex = -1;
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        if (strcmp(attendanceSystem->attendanceRecords[i].studentName, studentName) == 0) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student not found!\n");
        return;
    }

    struct AttendanceRecord *record = &(attendanceSystem->attendanceRecords[studentIndex]);

    int dayIndex = -1;
    for (int j = 0; j < record->totalDays; ++j) {
        if (record->dates[j].day == deleteDate.day && record->dates[j].month == deleteDate.month && record->dates[j].year == deleteDate.year) {
            dayIndex = j;
            break;
        }
    }

    if (dayIndex == -1) {
        printf("Attendance for specified date not found!\n");
        return;
    }

    // Shift array elements to remove the entry for the specified date
    for (int k = dayIndex; k < record->totalDays - 1; ++k) {
        record->dates[k] = record->dates[k + 1];
        record->isPresent[k] = record->isPresent[k + 1];
    }
    record->totalDays--;
    printf("Attendance for %d/%d/%d deleted for %s\n", deleteDate.day, deleteDate.month, deleteDate.year, studentName);
}

void generateReport(const struct StudentAttendanceSystem *attendanceSystem) {
    printf("Attendance Report:\n");
    printf("-----------------\n");
    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        int daysPresent = 0;
        int daysAbsent = 0;

        for (int j = 0; j < attendanceSystem->attendanceRecords[i].totalDays; ++j) {
            if (attendanceSystem->attendanceRecords[i].isPresent[j] == 1) {
                daysPresent++;
            } else {
                daysAbsent++;
            }
        }

        double percentageAttendance = (double)daysPresent / attendanceSystem->attendanceRecords[i].totalDays * 100;

        printf("Student: %s\n\n", attendanceSystem->attendanceRecords[i].studentName);
        printf("Days Present: %d\n", daysPresent);
        printf("Days Absent: %d\n\n", daysAbsent);
        printf("Percentage of Attendance: %.2f%%\n", percentageAttendance);
        printf("---------------------------------\n");
    }

    int totalDaysPresent = 0;
    int totalDaysAbsent = 0;
    int totalStudents = attendanceSystem->recordCount;

    for (int i = 0; i < attendanceSystem->recordCount; ++i) {
        for (int j = 0; j < attendanceSystem->attendanceRecords[i].totalDays; ++j) {
            if (attendanceSystem->attendanceRecords[i].isPresent[j] == 1) {
                totalDaysPresent++;
            } else {
                totalDaysAbsent++;
            }
        }
    }

    double totalAttendance = (double)totalDaysPresent / (totalDaysPresent + totalDaysAbsent) * 100;

    printf("Total Days Present: %d\n", totalDaysPresent);
    printf("Total Days Absent: %d\n\n", totalDaysAbsent);
    printf("Percentage of All Students' Attendance: %.2f%%\n", totalAttendance);
    printf("-----------------\n");
}

int main() {
    struct StudentAttendanceSystem attendanceSystem;
    attendanceSystem.recordCount = 0;

    printf("Welcome to the Student Attendance System\n");

    while (1) {
        printf("\n1. Add Student\n2. Display Attendance Patterns\n3. Mark Attendance\n4. Edit Attendance\n5. Delete Attendance Record\n6. Delete Attendance for a Date\n7. Generate Report\n8. Exit\n");
        printf("\nEnter your choice: ");
        
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (attendanceSystem.recordCount >= MAX_STUDENTS) {
                    printf("Maximum student limit reached!\n");
                    break;
                }

                printf("Enter student name: ");
                char name[50];
                scanf(" %[^\n]", name);
                addAttendanceRecord(&attendanceSystem, name);
                printf("Student added successfully!\n");
                break;

            case 2:
                displayStudentAttendance(&attendanceSystem);
                break;

            case 3:
                printf("Enter student name to mark attendance: ");
                char markName[50];
                scanf(" %[^\n]", markName);
                markAttendance(&attendanceSystem, markName);
                break;

            case 4:
                printf("Enter student name to edit attendance: ");
                char editName[50];
                scanf(" %[^\n]", editName);
                editAttendanceRecord(&attendanceSystem, editName);
                break;

            case 5:
                printf("Enter student name to delete: ");
                char deleteName[50];
                scanf(" %[^\n]", deleteName);
                deleteAttendanceRecord(&attendanceSystem, deleteName);
                break;

            case 6:
                printf("Enter student name to delete attendance for a date: ");
                char deleteDateName[50];
                scanf(" %[^\n]", deleteDateName);
                deleteAttendanceForDate(&attendanceSystem, deleteDateName);
                break;

            case 7:
                generateReport(&attendanceSystem);
                break;

            case 8:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}
