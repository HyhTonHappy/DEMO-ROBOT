#include <iostream>
#include <fstream>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <iomanip>
#include <Windows.h>
#include <cctype>
#include <string>
#include <cmath>
#include <queue>
#include <conio.h> // Sử dụng để sử dụng hàm getch() trên Windows
#define ANSI_COLOR_RED "\x1b[31m"// winner
#define ANSI_COLOR_GREEN "\x1b[32m" // menu 1
#define ANSI_COLOR_YELLOW "\x1b[33m" // giao diện màu vàng menu 4,5
#define ANSI_COLOR_RESET "\x1b[0m"//
#define ANSI_COLOR_BLUE "\x1b[34m"// // robot 2
#define ANSI_COLOR_GREY "\x1b[90m"// empty
#define ANSI_COLOR_PINK "\x1b[95m"// menu 2
#define ANSI_COLOR_ORANGE "\x1b[38;5;208m" // robot1
#define ANSI_COLOR_PURPLE "\x1b[35m" // TRÙNG NHAU
#define ANSI_COLOR_CYAN "\x1b[36m" // // MENU 3
#define ANSI_COLOR_BROWN "\x1b[33m" // TRÙNG NHAU Ở VẠCH ĐÍCH
#define ANSI_COLOR_WINE "\x1b[38;2;128;0;32m" // ROBOT MENU3
int a[100][100];
int e[100][100];
int n = 6;
int m = 5;
using namespace std;
struct Coordinate {
    int x;
    int y;
};
struct inputName {
    char* str;
};
int** createArray(int n, int m) {
    int** a = new int* [n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[m];
    }
    return a;
}
int** createArray_e(int n, int m) {
    int** e = new int* [n];
    for (int i = 0; i < n; ++i) {
        e[i] = new int[m];
    }
    return e;
}
void initializeArray_e(int** e) {
    // Khởi tạo giá trị cho ma trận e
    e[0][0] = 2;
    e[0][1] = 1;
    e[0][2] = 14;
    e[0][3] = 12;
    e[0][4] = 17;
    e[1][0] = 3;
    e[1][1] = 16;
    e[1][2] = 22;
    e[1][3] = 91;
    e[1][4] = 23;
    e[2][0] = 4;
    e[2][1] = 56;
    e[2][2] = 87;
    e[2][3] = 31;
    e[2][4] = 65;
    e[3][0] = 27;
    e[3][1] = 43;
    e[3][2] = 90;
    e[3][3] = 100;
    e[3][4] = 101;
    e[4][0] = 76;
    e[4][1] = 54;
    e[4][2] = 32;
    e[4][3] = 99;
    e[4][4] = 66;
    e[5][0] = 178;
    e[5][1] = 154;
    e[5][2] = 150;
    e[5][3] = 200;
    e[5][4] = 543;
}
void deleteArray_e(int** e, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] e[i];
    }
    delete[] e;
}
void initializeArray(int** a) {
    // Khởi tạo giá trị cho ma trận a
    a[0][0] = 2;
    a[0][1] = 1;
    a[0][2] = 14;
    a[0][3] = 12;
    a[0][4] = 17;
    a[1][0] = 3;
    a[1][1] = 16;
    a[1][2] = 22;
    a[1][3] = 91;
    a[1][4] = 23;
    a[2][0] = 4;
    a[2][1] = 56;
    a[2][2] = 87;
    a[2][3] = 31;
    a[2][4] = 65;
    a[3][0] = 27;
    a[3][1] = 43;
    a[3][2] = 90;
    a[3][3] = 100;
    a[3][4] = 101;
    a[4][0] = 76;
    a[4][1] = 54;
    a[4][2] = 32;
    a[4][3] = 99;
    a[4][4] = 66;
    a[5][0] = 178;
    a[5][1] = 154;
    a[5][2] = 150;
    a[5][3] = 200;
    a[5][4] = 543;
}
void deleteArray(int** a, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
}
void printSlowlyColor(const string& sentence, int delay, const string& color) {
    for (char c : sentence) {
        cout << color << c << ANSI_COLOR_RESET;
        cout.flush();

        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
void printSlowly(const string& sentence, int delay) {
    for (char c : sentence) {
        cout << c;
        cout.flush();

        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
void enterName(inputName& input) {
    printSlowlyColor("\n                                                   Moi ban nhap ten: ", 1, ANSI_COLOR_YELLOW);
    char buffer[100];
    cin >> buffer;

    // Cấp phát động cho input.str và sao chép tên từ buffer
    input.str = new char[strlen(buffer) + 1];
    strcpy_s(input.str, strlen(buffer) + 1, buffer);
}
// Hàm đọc ma trận từ file
int** docMaTranTuFile(const string& tenFile, int& n, int& m) {
    ifstream file("input.txt");
    if (file.is_open()) {
        file >> n >> m;

        int** a = createArray(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                file >> a[i][j];
            }
        }

        file.close();
        return a;
    }
    else {
        cout << "Khong the mo file" << endl;
        return nullptr;
    }
}
int findMaxValue(int** a, int x, int y) {
    int rows = 6;
    int cols = 5;
    int maxValue = -1;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (auto& dir : directions) {
        int newX = x + dir.x;
        int newY = y + dir.y;
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && a[newX][newY] > maxValue) {
            maxValue = a[newX][newY];
        }
    }

    return maxValue;
}
int findMaxValue_2(int** a, int x, int y) {
    int rows = 6;
    int cols = 5;
    int maxValue = -1;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (auto& dir : directions) {
        int newX = x + dir.x;
        int newY = y + dir.y;
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && a[newX][newY] > maxValue) {
            maxValue = a[newX][newY];
        }
    }

    return maxValue;
}
int findMaxValue_1(int** e, int x, int y) {
    int rows = 6;
    int cols = 5;
    int maxValue = -1;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (auto& dir : directions) {
        int newX = x + dir.x;
        int newY = y + dir.y;
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && e[newX][newY] > maxValue) {
            maxValue = e[newX][newY];
        }
    }

    return maxValue;
}
int findMaxPath2_2(int** e, Coordinate start2, int e1, int g, int d[100]) {
    d[0] = e[e1][g];
    int dem = 1;
    d[dem];
    int maxPath = 0;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (true) {
        // Kiểm tra các ô xung quanh để tìm ô có giá trị lớn nhất
        int maxValue = findMaxValue_1(e, start2.x, start2.y);

        if (maxValue == -1) {
            printSlowlyColor("\t\tRobot2 Ket thuc", 1, ANSI_COLOR_BLUE);
            d[dem] = maxValue;
            printSlowlyColor("\n\t\tQuang duong di duoc cua robot2: ", 1, ANSI_COLOR_BLUE);
            for (int i = 0; i < dem; i++) {
                cout << d[i] << " ";
            }
            e[start2.x][start2.y] = -2;
            break;
        }

        if (e[e1][g] == e[start2.x][start2.y]) {
            printSlowlyColor("\t\tVi tri bat dau cua robot2 ", 1, ANSI_COLOR_BLUE);
            cout << e[e1][g];
            start2.x = e1;
            start2.y = g;
        }

        // Đánh dấu ô đã đi qua
        e[start2.x][start2.y] = -1;

        // In ra hướng di chuyển của robot
        int directionIndex = -1;
        for (int i = 0; i < 4; i++) {
            int newX = start2.x + directions[i].x;
            int newY = start2.y + directions[i].y;
            if (newX >= 0 && newX < 6 && newY >= 0 && newY < 5 && e[newX][newY] == maxValue) {
                d[dem] = maxValue;
                dem++;
                directionIndex = i;
                break;
            }
        }

        if (directionIndex != -1) {
            switch (directionIndex) {
            case 0:
                cout << ANSI_COLOR_BLUE << "\n\t\tDi chuyen len " << ANSI_COLOR_RESET;
                break;
            case 1:
                cout << ANSI_COLOR_BLUE << "\n\t\tDi chuyen xuong " << ANSI_COLOR_RESET;
                break;
            case 2:
                cout << ANSI_COLOR_BLUE << "\n\t\tDi chuyen trai " << ANSI_COLOR_RESET;
                break;
            case 3:
                cout << ANSI_COLOR_BLUE << "\n\t\tDi chuyen phai " << ANSI_COLOR_RESET;
                break;
            }

            // Tạm dừng chương trình trong 1 giây
            this_thread::sleep_for(chrono::seconds(1));

            // Đi tiếp
            start2.x += directions[directionIndex].x;
            start2.y += directions[directionIndex].y;
            cout << " " << maxValue << "\n";
            maxPath += maxValue;
        }
    }

    return maxPath;
}
int findMaxPath2_1(int** a, Coordinate start1, int e, int g, int c[100]) {
    c[0] = a[e][g];
    int dem = 1;
    c[dem];
    int maxPath = 0;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (true) {
        // Kiểm tra các ô xung quanh để tìm ô có giá trị lớn nhất
        int maxValue = findMaxValue(a, start1.x, start1.y);

        if (maxValue == -1) {
            printSlowlyColor("\t\tRobot1 ket thuc \n ", 1, ANSI_COLOR_ORANGE);
            c[dem] = maxValue;
            printSlowlyColor("\n\t\tQuang duong di duoc cua robot1: ", 1, ANSI_COLOR_ORANGE);
            for (int i = 0; i < dem; i++) {
                cout << c[i] << " ";
            }
            a[start1.x][start1.y] = -2;
            break;
        }

        if (a[e][g] == a[start1.x][start1.y]) {
            printSlowlyColor("\t\tVi tri bat dau cua robot1 ", 1, ANSI_COLOR_ORANGE);
            cout << a[e][g];
            start1.x = e;
            start1.y = g;
        }

        // Đánh dấu ô đã đi qua
        a[start1.x][start1.y] = -1;

        // In ra hướng di chuyển của robot
        int directionIndex = -1;
        for (int i = 0; i < 4; i++) {
            int newX = start1.x + directions[i].x;
            int newY = start1.y + directions[i].y;
            if (newX >= 0 && newX < 6 && newY >= 0 && newY < 5 && a[newX][newY] == maxValue) {
                c[dem] = maxValue;
                dem++;
                directionIndex = i;
                break;
            }
        }

        if (directionIndex != -1) {
            switch (directionIndex) {
            case 0:
                cout << ANSI_COLOR_ORANGE << "\n\t\tDi chuyen len" << ANSI_COLOR_RESET;
                break;
            case 1:
                cout << ANSI_COLOR_ORANGE << "\n\t\tDi chuyen xuong" << ANSI_COLOR_RESET;
                break;
            case 2:
                cout << ANSI_COLOR_ORANGE << "\n\t\tDi chuyen trai" << ANSI_COLOR_RESET;
                break;
            case 3:
                cout << ANSI_COLOR_ORANGE << "\n\t\tDi chuyen phai" << ANSI_COLOR_RESET;
                break;
            }

            // Tạm dừng chương trình trong 1 giây
            this_thread::sleep_for(chrono::seconds(1));

            // Đi tiếp
            start1.x += directions[directionIndex].x;
            start1.y += directions[directionIndex].y;
            cout << " " << maxValue << "\n";
            maxPath += maxValue;
        }
    }

    return maxPath;
}
void visualizePath(int** a, int n, int m, int* b) {
    ofstream outputFile("output.txt");
    int dem = 1;
    cout << "\n\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == -1) {
                cout << ANSI_COLOR_CYAN << "\t" << "* " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô đã đi qua
                dem++;
            }
            else if (a[i][j] == -2) {
                cout << ANSI_COLOR_CYAN << "\t" << "X " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô cuối cùng
            }
            else {
                cout << ANSI_COLOR_GREY << "\t" << ". " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô trống
            }
            this_thread::sleep_for(chrono::milliseconds(200)); // Tạm dừng 200 milliseconds
        }
        cout << "\n";
    }
    this_thread::sleep_for(chrono::seconds(1)); // Tạm dừng 1 giây
    cout << ANSI_COLOR_CYAN << "\n\t\tDo dai di duoc cua robot la: " << ANSI_COLOR_RESET << dem << endl;
    if (outputFile.is_open()) {
        long tong = 0;
        for (int i = 0; i < dem; i++) {
            outputFile << b[i] << " ";
            tong += b[i];
        }
        cout << ANSI_COLOR_CYAN << "\n\t\tDa luu vao output.txt";
        outputFile << endl << "Do dai di duoc: " << dem;
        outputFile << endl << "Tong quang duong di duoc: " << tong;
        outputFile.close();
    }
}
int visualizePath_1(int** a, int n, int m) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == -1) {

                dem++;
            }
            else if (a[i][j] == -2) {
                dem++;
            }
        }
    }
    this_thread::sleep_for(chrono::seconds(1)); // Tạm dừng 1 giây
    cout << ANSI_COLOR_ORANGE << "\n\t\tDo dai duong di cua robot1 la: " << ANSI_COLOR_RESET << dem << endl;
    return dem;
}
int visualizePath_2(int** e, int n, int m) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (e[i][j] == -1) {
                dem++;
            }
            else if (e[i][j] == -2) {
                dem++;
            }
        }
    }
    this_thread::sleep_for(chrono::seconds(1)); // Tạm dừng 1 giây
    cout << ANSI_COLOR_BLUE << "\n\t\tDo dai duong di cua robot2 la: " << ANSI_COLOR_RESET << dem << endl;
    return dem;
}
int tinhTong(int** e, Coordinate start) {
    int rows = 6;
    int cols = 5;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    int maxValue = -1;
    int max2 = -1;
    for (int i = 0; i < 4; i++) {
        int newX = start.x + directions[i].x;
        int newY = start.y + directions[i].y;
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && e[newX][newY] > maxValue) {
            maxValue = e[newX][newY];
            max2 = i;
        }
    }
    if (max2 == -1) {
        return 0;
    }
    e[start.x][start.y] = -1;
    // đi tiếp theo
    int   newX = start.x + directions[max2].x;
    int newY = start.y + directions[max2].y;
    return maxValue + tinhTong(e, { newX,newY });
}
int findMaxPath(int** a, Coordinate start, int e, int g, int* b) {
    b[0] = a[e][g];
    int dem = 1;
    b[dem];
    int maxPath = 0;
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    while (true) {
        // Kiểm tra các ô xung quanh để tìm ô có giá trị lớn nhất
        int maxValue = findMaxValue(a, start.x, start.y);
        if (maxValue == -1) {
            cout << ANSI_COLOR_CYAN << "\t\tKet thuc" << ANSI_COLOR_RESET << endl;
            b[dem] = maxValue;
            printSlowlyColor("\n\t\tQuang duong di duoc: ", 1, ANSI_COLOR_CYAN);
            for (int i = 0; i < dem; i++) {
                cout << b[i] << " ";
            }
            a[start.x][start.y] = -2;
            break;
        }

        if (a[e][g] == a[start.x][start.y]) {
            cout << ANSI_COLOR_CYAN << "\t\tVi tri bat dau " << ANSI_COLOR_RESET << a[e][g] << endl;
            start.x = e;
            start.y = g;
        }

        // Đánh dấu ô đã đi qua
        a[start.x][start.y] = -1;

        // In ra hướng di chuyển của robot
        int directionIndex = -1;
        for (int i = 0; i < 4; i++) {
            int newX = start.x + directions[i].x;
            int newY = start.y + directions[i].y;
            if (newX >= 0 && newX < 6 && newY >= 0 && newY < 5 && a[newX][newY] == maxValue) {
                b[dem] = maxValue;
                dem++;
                directionIndex = i;
                break;
            }
        }

        if (directionIndex != -1) {
            switch (directionIndex) {
            case 0:
                cout << ANSI_COLOR_CYAN << "\n\t\tDi chuyen len " << ANSI_COLOR_RESET;
                break;
            case 1:
                cout << ANSI_COLOR_CYAN << "\n\t\tDi chuyen xuong " << ANSI_COLOR_RESET;
                break;
            case 2:
                cout << ANSI_COLOR_CYAN << "\n\t\tDi chuyen trai " << ANSI_COLOR_RESET;
                break;
            case 3:
                cout << ANSI_COLOR_CYAN << "\n\t\tDi chuyen phai " << ANSI_COLOR_RESET;
                break;
            }

            // Tạm dừng chương trình trong 1 giây
            this_thread::sleep_for(chrono::seconds(1));

            // Đi tiếp
            start.x += directions[directionIndex].x;
            start.y += directions[directionIndex].y;
            cout << maxValue << "\n";
            maxPath += maxValue;
        }
    }

    return maxPath;
}
int findMaxPath_2(int** a, Coordinate start1, Coordinate start2, int e1, int g1, int e2, int g2, int* h, int* k) {
    h[0] = a[e1][g1];
    k[0] = a[e2][g2];
    int dem1 = 1;
    int dem2 = 1;
    long tong1 = 0;
    long tong2 = 0;
    h[dem1];
    int maxPath = 0;
    int maxValue1 = a[e1][g1];
    int maxValue2 = a[e2][g2];
    Coordinate directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    printSlowlyColor("\n\t\tVi tri bat dau cua Robot1: ", 1, ANSI_COLOR_ORANGE);
    cout << maxValue1;
    printSlowlyColor("\n\t\tVi tri bat dau cua Robot2: ", 1, ANSI_COLOR_BLUE);
    cout << maxValue2;

    while (true) {
        // Kiểm tra các ô xung quanh để tìm ô có giá trị lớn nhất cho robot 1
        maxValue1 = findMaxValue(a, start1.x, start1.y);
        if (maxValue1 == maxValue2) {
            a[start2.x][start2.y] = -1;
            maxValue1 = findMaxValue(a, start1.x, start1.y);
        }
        a[start1.x][start1.y] = -1;
        if (maxValue1 == -1) {
            printSlowlyColor("\n\t\tRobot1 da het duong di", 1, ANSI_COLOR_ORANGE);
        }
        else {
            if (maxValue1 != -1) {
                if (a[e1][g1] == a[start1.x][start1.y] && a[start1.x][start1.y] != -1) {
                    //   cout << ANSI_COLOR_ORANGE << "\n\t\tVi tri bat dau cho robot1 " << ANSI_COLOR_RESET;
                     //  cout << a[e1][g1] << "\n";
                    //   cout << ANSI_COLOR_BLUE << "\n\t\tVi tri bat dau cho robot2 " << ANSI_COLOR_RESET;
                    //   cout << maxValue2 << "\n";
                    start1.x = e1;
                    start1.y = g1;
                }
            }
            // Đánh dấu ô đã đi qua cho robot 1
            a[start1.x][start1.y] = -1;
            if (maxValue1 != -1) {
                // In ra hướng di chuyển của robot 1
                int directionIndex1 = -1;
                for (int i = 0; i < 4; i++) {
                    int newX = start1.x + directions[i].x;
                    int newY = start1.y + directions[i].y;
                    if (newX >= 0 && newX < 6 && newY >= 0 && newY < 5 && a[newX][newY] == maxValue1) {
                        h[dem1] = maxValue1;
                        dem1++;
                        directionIndex1 = i;
                        break;
                    }
                }
                if (directionIndex1 != -1) {
                    switch (directionIndex1) {
                    case 0:
                        cout << ANSI_COLOR_ORANGE << "\n\t\tRobot1 di chuyen len " << ANSI_COLOR_RESET;
                        cout << maxValue1 << "\n";
                        break;
                    case 1:
                        cout << ANSI_COLOR_ORANGE << "\n\t\tRobot1 di chuyen xuong " << ANSI_COLOR_RESET;
                        cout << maxValue1 << " \n";
                        break;
                    case 2:
                        cout << ANSI_COLOR_ORANGE << "\n\t\tRobot1 di chuyen trai " << ANSI_COLOR_RESET;
                        cout << maxValue1 << "\n";
                        break;
                    case 3:
                        cout << ANSI_COLOR_ORANGE << "\n\t\tRobot1 di chuyen phai " << ANSI_COLOR_RESET;
                        cout << maxValue1 << "\n";
                        break;
                    }

                    // Tạm dừng chương trình trong 1 giây
                    this_thread::sleep_for(chrono::seconds(1));

                    // Đi tiếp cho robot 1
                    start1.x += directions[directionIndex1].x;
                    start1.y += directions[directionIndex1].y;
                    maxPath += maxValue1;
                }
            }
        }
        // Kiểm tra các ô xung quanh để tìm ô có giá trị lớn nhất cho robot 2
        maxValue2 = findMaxValue(a, start2.x, start2.y);
        if (maxValue2 == -1) {
            printSlowlyColor("\n\t\tRobot2 da het duong di", 1, ANSI_COLOR_BLUE);
        }
        if (maxValue2 != -1) {
            if (a[e2][g2] == a[start2.x][start2.y] && a[start2.x][start2.y] != -1) {
                cout << ANSI_COLOR_BLUE << "\n\t\tVi tri bat dau cho robot2 " << ANSI_COLOR_RESET;
                cout << a[e2][g2] << "\n";
                start2.x = e2;
                start2.y = g2;
            }
        }
        if (maxValue1 == -1 && maxValue2 == -1) {
            h[dem1] = maxValue1;
            printSlowlyColor("\n\t\tDo dai Robot1 di duoc: ", 1, ANSI_COLOR_ORANGE);
            cout << dem1;
            printSlowlyColor("\n\t\tQuang duong di duoc cua robot1: ", 1, ANSI_COLOR_ORANGE);
            for (int i = 0; i < dem1; i++) {
                tong1 += h[i];
                cout << h[i] << " ";
            }
            printSlowlyColor("\n\t\tTong quang duong di duoc cua robot1: ", 1, ANSI_COLOR_ORANGE);
            cout << tong1;
            a[start1.x][start1.y] = -2;
            k[dem2] = maxValue2;
            printSlowlyColor("\n\t\tDo dai ma robot2 di duoc: ", 1, ANSI_COLOR_BLUE);
            cout << dem2;
            printSlowlyColor("\n\t\tQuang duong di duoc cua robot2: ", 1, ANSI_COLOR_BLUE);
            for (int i = 0; i < dem2; i++) {
                tong2 += k[i];
                cout << k[i] << " ";
            }
            printSlowlyColor("\n\t\tTong quang duong di duoc cua robot2: ", 1, ANSI_COLOR_BLUE);
            cout << tong2;
            if (tong1 > tong2) {
                printSlowlyColor("\n\t\tRobot1 win", 1, ANSI_COLOR_RED);
            }
            else if (tong1 == tong2) {
                printSlowlyColor("\n\t\tDRAW", 1, ANSI_COLOR_RED);
            }
            else {
                printSlowlyColor("\n\t\tRobot2 win", 1, ANSI_COLOR_RED);
            }
            ofstream outputFile("output.txt");
            if (outputFile.is_open()) {
                printSlowlyColor("\n\t\tDa luu ket qua vao file output.txt", 1, ANSI_COLOR_GREEN);
                outputFile << endl << "\nDo dai di duoc cua robot1: " << dem1 << endl;
                outputFile << "\nQuang duong robot1 di duoc: " << endl;
                for (int i = 0; i < dem1; i++) {
                    outputFile << h[i] << " ";
                }
                outputFile << endl << "\nTong quang duong ma robot1 di duoc: " << tong1 << endl;
                outputFile << endl << "\nDo dai di duoc cua robot2: " << dem2 << endl;
                outputFile << endl << "\nQuang duong robot2 di duoc: " << endl;
                for (int i = 0; i < dem2; i++) {
                    outputFile << k[i] << " ";
                }
                outputFile << endl << "\nTong quang duong ma robot2 di duoc: " << tong2 << endl;
                if (tong1 > tong2) {
                    outputFile << endl << "\nRobot1 Win " << endl;
                }
                else if (tong1 == tong2) {
                    outputFile << endl << "\nDRAW " << endl;
                }
                else {
                    outputFile << endl << "\nRobot2 Win " << endl;
                }
                outputFile.close();

            }
            a[start2.x][start2.y] = -3;
            break;
        }
        if (maxValue2 == maxValue1) {
            a[start1.x][start1.y] = -1;
            maxValue2 = findMaxValue(a, start2.x, start2.y);
        }
        // Đánh dấu ô đã đi qua cho robot 2
        a[start2.x][start2.y] = -1;
        if (maxValue2 != -1) {
            // In ra hướng di chuyển của robot 2
            int directionIndex2 = -1;
            for (int i = 0; i < 4; i++) {
                int newX = start2.x + directions[i].x;
                int newY = start2.y + directions[i].y;
                if (newX >= 0 && newX < 6 && newY >= 0 && newY < 5 && a[newX][newY] == maxValue2) {
                    k[dem2] = maxValue2;
                    dem2++;
                    directionIndex2 = i;
                    start2.x = newX;
                    start2.y = newY;
                    break;
                }
            }
            if (directionIndex2 != -1) {
                switch (directionIndex2) {
                case 0:
                    cout << ANSI_COLOR_BLUE << "\n\t\tRobot2 di chuyen len " << ANSI_COLOR_RESET;
                    cout << maxValue2 << "\n";
                    break;
                case 1:
                    cout << ANSI_COLOR_BLUE << "\n\t\tRobot2 di chuyen xuong " << ANSI_COLOR_RESET;
                    cout << maxValue2 << "\n";
                    break;
                case 2:
                    cout << ANSI_COLOR_BLUE << "\n\t\tRobot2 di chuyen trai " << ANSI_COLOR_RESET;
                    cout << maxValue2 << "\n";
                    break;
                case 3:
                    cout << ANSI_COLOR_BLUE << "\n\t\tRobot2 di chuyen phai " << ANSI_COLOR_RESET;
                    cout << maxValue2 << "\n";
                    break;
                }
                if (directionIndex2 != -1) {
                    a[start2.x][start2.y] = -1;
                }
                // Tạm dừng chương trình trong 1 giây
                this_thread::sleep_for(chrono::seconds(1));

                // Đi tiếp cho robot 2
                maxPath += maxValue2;
            }
        }
    }

    return maxPath;
}
void visualizePaths(int** a, int** e, int n, int m) {
    cout << "\n\n\n";
    int dem1 = 1;
    int dem2 = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == -1 && e[i][j] != -1) {
                cout << ANSI_COLOR_ORANGE << "\t" << "* " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô đã đi qua của Robot 1
                dem1++;
            }
            else if (a[i][j] == -2 && e[i][j] != -2) {
                cout << ANSI_COLOR_ORANGE << "\t" << "R1 " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô cuối cùng
            }
            else if (e[i][j] == -1 && a[i][j] != -1) {
                cout << ANSI_COLOR_BLUE << "\t" << "+ " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô đã đi qua của Robot 2
                dem2++;
            }
            else if (e[i][j] == -2 && a[i][j] != -2) {
                cout << ANSI_COLOR_BLUE << "\t" << "R2 " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô cuối cùng
            }
            else if (a[i][j] == -1 && e[i][j] == -1) {
                cout << ANSI_COLOR_PURPLE << "\t" << "O " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô trùng nhau
            }
            else if (a[i][j] == -2 && e[i][j] == -2) {
                cout << ANSI_COLOR_BROWN << "\t" << "B " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô trùng nhau
            }
            else {
                cout << ANSI_COLOR_GREY << "\t" << ". " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô trống
            }

        }
        cout << "\n";
    }
    cout << "\n";
}
void visualizePaths_1(int** e, int n, int m, int** a, int* h, int* k) {
    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool isRobot1Path = false;
            bool isRobot2Path = false;
            bool Final1 = false;
            bool Final2 = false;
            for (int l = 0; l < 30; l++) {
                if (a[i][j] == -2) {
                    Final1 = true;
                    break;
                }if (a[i][j] == -3) {
                    Final2 = true;
                    break;
                }
                if (e[i][j] == h[l]) {
                    isRobot1Path = true;
                    break;
                }
                if (e[i][j] == k[l]) {
                    isRobot2Path = true;
                    break;
                }
            }
            if (isRobot1Path) {
                cout << ANSI_COLOR_ORANGE << "\t" << "* " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô đã đi qua của Robot 1
            }
            else if (Final1) {
                cout << ANSI_COLOR_ORANGE << "\t" << "R1 " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô cuối cùng của Robot 1
            }
            else if (isRobot2Path) {
                cout << ANSI_COLOR_BLUE << "\t" << "+ " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô đã đi qua của Robot 2
            }
            else if (Final2) {
                cout << ANSI_COLOR_BLUE << "\t" << "R2 " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô cuối cùng của Robot 2
            }
            else {
                cout << ANSI_COLOR_GREY << "\t" << ". " << "\t" << ANSI_COLOR_RESET; // Ký hiệu cho ô trống
            }
        }
        cout << "\n";
    }
    cout << "\n";
}
void header() {
    printSlowlyColor("___________________________________________________WELCOME TO MY WORLD__________________________________________________", 2, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                     THE ROBOT GAME", 2, ANSI_COLOR_YELLOW);
}
void body1() {
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowlyColor("\n\n\n\n                                                  --------------------------------", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  CHOOSE BETWEEN 1 AND 5", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  1.PLAY WITH COMPUTER", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  2.PLAY WITH FRIEND", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  3.TRY ON IT", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  4.HELP", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  5.ABOUT ME", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  PRESS 0 TO EXIT", 0, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n                                                  --------------------------------", 0, ANSI_COLOR_YELLOW);

}
void body2_item1() {
    int n = 6;
    int m = 5;
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n\n\n", 1);
    printSlowlyColor("\n\n                                                 _____PLAY WITH COMPUTER_____\n\n", 1, ANSI_COLOR_GREEN);
    bool flag = true;
    int choose = 0;
    int start_1 = 0;
    int start_2 = 0;
    long tong = 0;
    long tong1 = 0;
    do {
        do {
            printSlowlyColor("\n                                                  Ban muon chon che do nao ? ", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n                                                  1.Intersection ", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n                                                  2.Normal ", 1, ANSI_COLOR_GREEN);
            cin >> choose;
            if (choose < 1 || choose > 2) {
                printSlowlyColor("\t\tERROR. Vui long chon lai che do: ", 1, ANSI_COLOR_GREEN);
            }
        } while (choose < 1 || choose > 2);
        if (choose == 1) {
            int** a = createArray(n, m);
            int** e = createArray_e(n, m);
            int** maTranDoc = docMaTranTuFile("input.txt", n, m);
            if (maTranDoc != nullptr) {
                // Gán giá trị từ maTranDoc vào a
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        a[i][j] = maTranDoc[i][j];
                    }
                }
            }
            if (maTranDoc != nullptr) {
                // Gán giá trị từ maTranDoc vào a
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        e[i][j] = maTranDoc[i][j];
                    }
                }
            }
            int* c = new int[100];
            int* d = new int[100];
            Coordinate start1;
            Coordinate start2;
            do {
                printSlowlyColor("\nMoi ban nhap toa do cua Robot 1: ", 1, ANSI_COLOR_GREEN);
                cin >> start1.x >> start1.y;
                printSlowlyColor("\nMoi ban nhap toa do cua Robot 2: ", 1, ANSI_COLOR_GREEN);
                cin >> start2.x >> start2.y;
                if ((start1.x < 0 || start2.x < 0 || start2.x > 5 || start1.x >5
                    || start1.y < 0 || start2.y < 0 || start1.y > 4 || start2.y > 4)) {
                    printSlowlyColor("\nERROR. Vui long chon lai toa do: ", 1, ANSI_COLOR_GREEN);
                }
            } while (start1.x < 0 || start2.x < 0 || start2.x > 5 || start1.x >5
                || start1.y < 0 || start2.y < 0 || start1.y > 4 || start2.y > 4);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << "\t" << a[i][j] << "\t";
                    start_1 = a[start1.x][start1.y];
                }
                cout << "\n";
            }
            cout << "\n";
            // robot 1
            long tong = a[start1.x][start1.y];
            long sum = findMaxPath2_1(a, start1, start1.x, start1.y, c);
            tong += sum;
            printSlowlyColor("\n\t\tTong quang duong di duoc của Robot1: ", 1, ANSI_COLOR_ORANGE);
            cout << tong;
            int dem1 = visualizePath_1(a, n, m);
            cout << "\n\n";
            // robot 2
            long tong1 = e[start2.x][start2.y];
            long sum1 = findMaxPath2_2(e, start2, start2.x, start2.y, d);
            tong1 += sum1;
            printSlowlyColor("\n\t\tTong quang duong di duoc của Robot2: ", 1, ANSI_COLOR_BLUE);
            cout << tong1;
            int dem2 = visualizePath_2(e, n, m);
            if (tong1 > tong) {
                printSlowlyColor("\n\t\tRobot2 win\n", 1, ANSI_COLOR_RED);
            }
            else if (tong1 == tong) {
                printSlowlyColor("\n\t\tDRAW\n", 1, ANSI_COLOR_RED);
            }
            else {
                printSlowlyColor("\n\t\tRobot1 win", 1, ANSI_COLOR_RED);
            }
            ofstream outputFile("output.txt");
            if (outputFile.is_open()) {
                printSlowlyColor("\n\t\tDa luu ket qua vao file output.txt", 1, ANSI_COLOR_GREEN);
                outputFile << endl << "\nTong quang duong cua robot1: " << tong << endl;
                outputFile << endl << "\nDo dai di duoc cua robot1: " << dem1 << endl;
                outputFile << endl << "\nQuang duong di duoc cua robot1 " << endl;
                for (int i = 0; i < dem1; i++) {
                    outputFile << c[i] << " ";
                }
                outputFile << endl << "\nTong quang duong cua robot2: " << tong1 << endl;
                outputFile << endl << "\nDo dai di duoc cua robot2: " << dem2 << endl;
                outputFile << endl << "\nQuang duong di duoc cua robot2 " << endl;
                for (int i = 0; i < dem2; i++) {
                    outputFile << d[i] << " ";
                }
                if (tong1 > tong) {
                    outputFile << endl << "\nRobot2 win " << endl;
                }
                else if (tong1 == tong) {
                    outputFile << endl << "\nDRAW " << endl;
                }
                else {
                    outputFile << endl << "\nRobot1 win " << endl;
                }
                outputFile << endl << "\nDoan duong trung nhau: " << endl;
                for (int i = 0; i < dem1; i++) {
                    for (int j = 0; j < dem2; j++) {
                        if (c[i] == d[j]) {
                            outputFile << endl << c[i] << " ";
                        }
                    }
                }
                outputFile.close();
            }
            printSlowlyColor("\n\t\tVisualize cua 2 con Robot: ", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau * la duong di cua Robot1", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau + la duong di cua Robot1", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau O la trung nhau", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau B la trung nhau o ve dich", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau R1 la o cuoi cung cua Robot1", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau R2 la o cuoi cung cua Robot1", 1, ANSI_COLOR_GREEN);
            visualizePaths(a, e, n, m);
            c[dem1];
            d[dem2];
            printSlowlyColor("\n\t\tCac vi tri 2 robot trung nhau: ", 1, ANSI_COLOR_GREEN);
            for (int i = 0; i < dem1; i++) {
                for (int j = 0; j < dem2; j++) {
                    if (c[i] == d[j]) {
                        cout << c[i] << " ";
                    }
                }
            }
            deleteArray(maTranDoc, n);
            deleteArray(a, n);
            deleteArray_e(e, n);
            delete[] c;
            delete[] d;
        }
        else if (choose == 2) {
            Coordinate start1;
            Coordinate start2;
            int** a = createArray(n, m);
            int** e = createArray_e(n, m);
            int** maTranDoc = docMaTranTuFile("input.txt", n, m);
            if (maTranDoc != nullptr) {
                // Gán giá trị từ maTranDoc vào a
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        a[i][j] = maTranDoc[i][j];
                    }
                }
            }
            if (maTranDoc != nullptr) {
                // Gán giá trị từ maTranDoc vào a
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        e[i][j] = maTranDoc[i][j];
                    }
                }
            }
            int* h = new int[100];
            int* k = new int[100];
            do {
                printSlowlyColor("Moi ban nhap toa do cua Robot 1: ", 1, ANSI_COLOR_GREEN);
                cin >> start1.x >> start1.y;
                printSlowlyColor("Moi ban nhap toa do cua Robot 2: ", 1, ANSI_COLOR_GREEN);
                cin >> start2.x >> start2.y;
                if ((start1.x < 0 || start2.x < 0 || start2.x > 5 || start1.x >5
                    || start1.y < 0 || start2.y < 0 || start1.y > 4 || start2.y > 4)) {
                    printSlowlyColor("\t\tERROR. Vui long chon lai toa do: ", 1, ANSI_COLOR_GREEN);
                }
            } while (start1.x < 0 || start2.x < 0 || start2.x > 6 || start1.x >6
                || start1.y < 0 || start2.y < 0 || start1.y > 5 || start2.y > 5);
            long empty = findMaxPath_2(a, start1, start2, start1.x, start1.y, start2.x, start2.y, h, k);
            printSlowlyColor("\n\t\tVisualize cua 2 con Robot: ", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau * la duong di cua Robot1", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau + la duong di cua Robot1", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau R1 la o cuoi cung cua Robot1", 1, ANSI_COLOR_GREEN);
            printSlowlyColor("\n\t\tDau R2 la o cuoi cung cua Robot1", 1, ANSI_COLOR_GREEN);
            visualizePaths_1(e, n, m, a, h, k);
            deleteArray(maTranDoc, n);
            deleteArray(a, n);
            deleteArray_e(e, n);
            delete[] h;
            delete[] k;
        }
        int x = 0;
        printSlowlyColor("\n\n\n                                                  Tiep tuc khong? Nhan 0 de thoat! ", 1, ANSI_COLOR_GREEN);
        cin >> x;
        if (x == 0) {
            flag = false;
            break;
        }
    } while (flag);
}
void body2_item2() {
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowlyColor("\n\n\n                                                _____PLAY WITH FRIEND_____\n\n", 1, ANSI_COLOR_PINK);
    n = 6;
    m = 5;
    do {
        int e1, e2, g1, g2 = 0;
        do {
            printSlowlyColor("\nMoi ban nhap toa do cua robot1 ", 1, ANSI_COLOR_PINK);
            cin >> e1 >> g1;
            printSlowlyColor("\nMoi ban nhap toa do cua robot2 ", 1, ANSI_COLOR_PINK);
            cin >> e2 >> g2;
            if (e1 < 0 || e2 < 0 || g1 > 5 || g2 > 4 || e1 == e2 && g1 == g2) {
                printSlowlyColor("\nERROR! Vui long nhap lai ", 1, ANSI_COLOR_PINK);
            }
        } while (e1 < 0 || e2 < 0 || g1 > 5 || g2 > 4 || e1 == e2 && g1 == g2);
        long a[6][5] = {
          {2, 1, 14, 12, 17},
          {3, 16, 22, 91, 23},
          {4, 56, 87, 31, 65},
          {27, 43, 90, 100, 101},
          {76, 54, 32, 99, 66},
          {178, 154, 150, 200, 543}
        };
        int p1 = e1;
        int p2 = g1;
        int p3 = e2;
        int p4 = g2;
        // xuất màn hình
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == p1 && j == p2) {
                    cout << ANSI_COLOR_ORANGE << "\t" << "S1 " << "\t" << ANSI_COLOR_RESET;
                }
                else if (i == p3 && j == p4) {
                    cout << ANSI_COLOR_BLUE << "\t" << "S2 " << "\t" << ANSI_COLOR_RESET;
                }
                else {
                    cout << "\t" << a[i][j] << "\t";
                }
            }
            cout << "\n";
        }
        int* b1 = new int[n * m]; // Mảng lưu quãng đường đã đi của robot 1
        int* b2 = new int[n * m]; // Mảng lưu quãng đường đã đi của robot 2
        int dem1 = 1; // Số bước đi của robot 1
        int dem2 = 1; // Số bước đi của robot 2
        int tong1 = a[p1][p2]; // Tổng quãng đường đã đi của robot 1
        int tong2 = a[p3][p4]; // Tổng quãng đường đã đi của robot 2
        int trai1 = 0, trai2 = 0, phai1 = 0, phai2 = 0, tren1 = 0, tren2 = 0, duoi1 = 0, duoi2 = 0;
        b1[0] = a[p1][p2];
        b2[0] = a[p3][p4];
        a[p1][p2] = -1;
        a[p3][p4] = -2;
        while (true) {
            bool isValidMove1 = false;
            bool isValidMove2 = false;
            bool checkIT1 = true;
            bool checkIT2 = true;
            while (!isValidMove1) {
                isValidMove1 = true;
                // Người chơi thứ 1 điều khiển robot 1
                cout << ANSI_COLOR_PINK << "\n\t\tNguoi choi 1 - Di chuyen Robot1 :\n" << ANSI_COLOR_RESET;
                cout << ANSI_COLOR_PINK << "\t\tNhap A, S, D, W de di chuyen robot: " << ANSI_COLOR_RESET;
                char move1 = _getch(); // Sử dụng _getch() để đọc ký tự từ người dùng trên Windows
                cout << move1 << endl;
                int newX1 = e1;
                int newY1 = g1;

                // Xử lý các phím di chuyển của người chơi 1
                if (move1 == 'A' || move1 == 'a') {
                    newY1 = g1 - 1; // Di chuyển sang trái
                    newX1 = e1;
                }
                else if (move1 == 'D' || move1 == 'd') {
                    newY1 = g1 + 1; // Di chuyển sang phải
                    newX1 = e1;
                }
                else if (move1 == 'W' || move1 == 'w') {
                    newX1 = e1 - 1; // Di chuyển lên trên
                    newY1 = g1;
                }
                else if (move1 == 'S' || move1 == 's') {
                    newX1 = e1 + 1; // Di chuyển xuống dưới
                    newY1 = g1;
                }
                else {
                    isValidMove1 = false;
                }

                // Kiểm tra nếu vị trí di chuyển của robot 1 nằm ngoài ma trận hoặc đã được đi qua
                if (newX1 < 0 || newX1 >= n || newY1 < 0 || newY1 >= m) {
                    isValidMove1 = false;
                }
                if (move1 == 'a' || move1 == 'A') {
                    trai1 = a[e1][g1 - 1];
                    phai1 = a[e1][g1 + 1];
                    tren1 = a[e1 - 1][g1];
                    duoi1 = a[e1 + 1][g1];
                    if (g1 - 1 < 0) {
                        trai1 = -1;
                    }
                    if (g1 + 1 >= m) {
                        phai1 = -1;
                    }
                    if (e1 - 1 < 0) {
                        tren1 = -1;
                    }
                    if (e1 + 1 >= n) {
                        duoi1 = -1;
                    }
                    if (trai1 < phai1 || trai1 < tren1 || trai1 < duoi1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 'd' || move1 == 'D') {
                    trai1 = a[e1][g1 - 1];
                    phai1 = a[e1][g1 + 1];
                    tren1 = a[e1 - 1][g1];
                    duoi1 = a[e1 + 1][g1];
                    if (g1 - 1 < 0) {
                        trai1 = -1;
                    }
                    if (g1 + 1 >= m) {
                        phai1 = -1;
                    }
                    if (e1 - 1 < 0) {
                        tren1 = -1;
                    }
                    if (e1 + 1 >= n) {
                        duoi1 = -1;
                    }
                    if (phai1 < trai1 || phai1 < tren1 || phai1 < duoi1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 'w' || move1 == 'W') {
                    trai1 = a[e1][g1 - 1];
                    phai1 = a[e1][g1 + 1];
                    tren1 = a[e1 - 1][g1];
                    duoi1 = a[e1 + 1][g1];
                    if (g1 - 1 < 0) {
                        trai1 = -1;
                    }
                    if (g1 + 1 >= m) {
                        phai1 = -1;
                    }
                    if (e1 - 1 < 0) {
                        tren1 = -1;
                    }
                    if (e1 + 1 >= n) {
                        duoi1 = -1;
                    }
                    if (tren1 < phai1 || tren1 < duoi1 || tren1 < trai1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 's' || move1 == 'S') {
                    trai1 = a[e1][g1 - 1];
                    phai1 = a[e1][g1 + 1];
                    tren1 = a[e1 - 1][g1];
                    duoi1 = a[e1 + 1][g1];
                    if (g1 - 1 < 0) {
                        trai1 = -1;
                    }
                    if (g1 + 1 >= m) {
                        phai1 = -1;
                    }
                    if (e1 - 1 < 0) {
                        tren1 = -1;
                    }
                    if (e1 + 1 >= n) {
                        duoi1 = -1;
                    }
                    if (duoi1 < phai1 || duoi1 < tren1 || duoi1 < trai1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 'a' || move1 == 'A') {
                    if (newY1 < 0 || trai1 == -1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 'd' || move1 == 'D') {
                    if (newY1 >= m || phai1 == -1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 'w' || move1 == 'W') {
                    if (newX1 < 0 || tren1 == -1) {
                        isValidMove1 = false;
                    }
                }
                if (move1 == 's' || move1 == 'S') {
                    if (newX1 >= n || duoi1 == -1) {
                        isValidMove1 = false;
                    }
                }
                if (tren1 < 0 && duoi1 < 0 && phai1 < 0 && trai1 < 0) {
                    checkIT1 = false;
                }
                if (!checkIT1) {
                    printSlowlyColor("\t\tRobot1 da het duong di", 1, ANSI_COLOR_ORANGE);
                    isValidMove1 = true;
                    break;
                }
                else {
                    if (isValidMove1) {
                        // Cập nhật vị trí mới của robot 1
                        e1 = newX1;
                        g1 = newY1;
                        b1[dem1] = a[e1][g1]; // Lưu giá trị của ô vào mảng b1
                        tong1 += a[e1][g1]; // Cập nhật tổng quãng đường đã đi của robot 1
                        a[e1][g1] = -1; // Đánh dấu ô đã đi qua
                        cout << ANSI_COLOR_PINK << "Ma tran sau khi di chuyen robot 1:\n" << ANSI_COLOR_RESET;
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                if (i == e1 && j == g1) {
                                    cout << ANSI_COLOR_WINE << "\t" << "*  " << "\t" << ANSI_COLOR_RESET; // In ô hiện tại được đánh dấu *
                                }
                                else if (i == p1 && j == p2) {
                                    cout << ANSI_COLOR_ORANGE << "\t" << "S1 " << "\t" << ANSI_COLOR_RESET; // bắt đầu
                                }
                                else if (a[i][j] == -1) {
                                    cout << ANSI_COLOR_ORANGE << "\t" << "X  " << "\t" << ANSI_COLOR_RESET; // In ô đã đi qua
                                }
                                else if (i == p3 && j == p4) {
                                    cout << ANSI_COLOR_BLUE << "\t" << "S2 " << "\t" << ANSI_COLOR_RESET;

                                }
                                else if (a[i][j] == -2) {
                                    cout << ANSI_COLOR_BLUE << "\t" << "O " << "\t" << ANSI_COLOR_RESET;

                                }
                                else if (i == e2 && j == g2) {
                                    cout << ANSI_COLOR_WINE << "\t" << "+  " << "\t" << ANSI_COLOR_RESET; // In ô hiện tại được đánh dấu +
                                }
                                else {
                                    cout << "\t" << a[i][j] << "\t"; // In giá trị của ô
                                }
                            }
                            cout << "\n";
                        }
                        dem1++; // Tăng số bước đi của robot 1 lên 1
                    }
                    else {
                        cout << ANSI_COLOR_PINK << "\t\tDi chuyen khong hop le cho robot 1!\n" << ANSI_COLOR_RESET;
                        continue;
                    }
                }
            }
            while (!isValidMove2) {
                isValidMove2 = true;
                // Người chơi thứ 2 điều khiển robot 2
                cout << ANSI_COLOR_PINK << "\n\t\tNguoi choi 2 - Di chuyen robot 2:\n";
                cout << "\t\tNhap J, I, L, K de di chuyen robot: " << ANSI_COLOR_RESET;
                char move2 = _getch(); // Sử dụng _getch() để đọc ký tự từ người dùng trên Windows
                cout << move2 << endl;
                int newX2 = e2;
                int newY2 = g2;
                // Xử lý các phím di chuyển của người chơi 2
                if (move2 == 'J' || move2 == 'j') {
                    newY2 = g2 - 1; // Di chuyển sang trái
                    newX2 = e2;
                }
                else if (move2 == 'L' || move2 == 'l') {
                    newY2 = g2 + 1; // Di chuyển sang phải
                    newX2 = e2;
                }
                else if (move2 == 'I' || move2 == 'i') {
                    newX2 = e2 - 1; // Di chuyển lên trên
                    newY2 = g2;
                }
                else if (move2 == 'K' || move2 == 'k') {
                    newX2 = e2 + 1; // Di chuyển xuống dưới
                    newY2 = g2;
                }
                else {
                    isValidMove2 = false;
                }

                // Kiểm tra nếu vị trí di chuyển của robot 2 nằm ngoài ma trận hoặc đã được đi qua
                if (newX2 < 0 || newX2 >= n || newY2 < 0 || newY2 >= m) {
                    isValidMove2 = false;
                }
                if (move2 == 'j' || move2 == 'J') {
                    trai2 = a[e2][g2 - 1];
                    phai2 = a[e2][g2 + 1];
                    tren2 = a[e2 - 1][g2];
                    duoi2 = a[e2 + 1][g2];
                    if (g2 - 1 < 0) {
                        trai2 = -2;
                    }
                    if (g2 + 1 >= m) {
                        phai2 = -2;
                    }
                    if (e2 - 1 < 0) {
                        tren2 = -2;
                    }
                    if (e2 + 1 >= n) {
                        duoi2 = -2;
                    }
                    if (trai2 < phai2 || trai2 < tren2 || trai2 < duoi2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'l' || move2 == 'L') {
                    trai2 = a[e2][g2 - 1];
                    phai2 = a[e2][g2 + 1];
                    tren2 = a[e2 - 1][g2];
                    duoi2 = a[e2 + 1][g2];
                    if (g2 - 1 < 0) {
                        trai2 = -2;
                    }
                    if (g2 + 1 >= m) {
                        phai2 = -2;
                    }
                    if (e2 - 1 < 0) {
                        tren2 = -2;
                    }
                    if (e2 + 1 >= n) {
                        duoi2 = -2;
                    }
                    if (phai2 < trai2 || phai2 < tren2 || phai2 < duoi2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'i' || move2 == 'I') {
                    trai2 = a[e2][g2 - 1];
                    phai2 = a[e2][g2 + 1];
                    tren2 = a[e2 - 1][g2];
                    duoi2 = a[e2 + 1][g2];
                    if (g2 - 1 < 0) {
                        trai2 = -2;
                    }
                    if (g2 + 1 >= m) {
                        phai2 = -2;
                    }
                    if (e2 - 1 < 0) {
                        tren2 = -2;
                    }
                    if (e2 + 1 >= n) {
                        duoi2 = -2;
                    }
                    if (tren2 < phai2 || tren2 < duoi2 || tren2 < trai2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'k' || move2 == 'K') {
                    trai2 = a[e2][g2 - 1];
                    phai2 = a[e2][g2 + 1];
                    tren2 = a[e2 - 1][g2];
                    duoi2 = a[e2 + 1][g2];
                    if (g2 - 1 < 0) {
                        trai2 = -2;
                    }
                    if (g2 + 1 >= m) {
                        phai2 = -2;
                    }
                    if (e2 - 1 < 0) {
                        tren2 = -2;
                    }
                    if (e2 + 1 >= n) {
                        duoi2 = -2;
                    }
                    if (duoi2 < phai2 || duoi2 < tren2 || duoi2 < trai2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'j' || move2 == 'J') {
                    if (newY2 < 0 || trai2 == -2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'l' || move2 == 'L') {
                    if (newY2 >= m || phai2 == -2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'i' || move2 == 'I') {
                    if (newX2 < 0 || tren2 == -2) {
                        isValidMove2 = false;
                    }
                }
                if (move2 == 'k' || move2 == 'K') {
                    if (newX2 >= n || duoi2 == -2) {
                        isValidMove2 = false;
                    }
                }
                if (trai2 < 0 && tren2 < 0 && duoi2 < 0 && phai2 < 0) {
                    checkIT2 = false;
                }
                if (!checkIT2) {
                    printSlowlyColor("\t\tRobot2 da het duong di", 1, ANSI_COLOR_BLUE);
                    isValidMove2 = true;
                    break;
                }
                else {
                    if (isValidMove2) {
                        // Cập nhật vị trí mới của robot 2
                        e2 = newX2;
                        g2 = newY2;
                        b2[dem2] = a[e2][g2]; // Lưu giá trị của ô vào mảng b2
                        tong2 += a[e2][g2]; // Cập nhật tổng quãng đường đã đi của robot 2
                        a[e2][g2] = -2; // Đánh dấu ô đã đi qua
                        cout << ANSI_COLOR_PINK << "\t\tMa tran sau khi di chuyen robot 2:\n" << ANSI_COLOR_RESET;
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                if (i == e2 && j == g2) {
                                    cout << ANSI_COLOR_WINE << "\t" << "+  " << "\t" << ANSI_COLOR_RESET; // In ô hiện tại được đánh dấu +
                                }
                                else if (i == p3 && j == p4) {
                                    cout << ANSI_COLOR_BLUE << "\t" << "S2 " << "\t" << ANSI_COLOR_RESET; // bắt đầu
                                }
                                else if (a[i][j] == -2) {
                                    cout << ANSI_COLOR_BLUE << "\t" << "O  " << "\t" << ANSI_COLOR_RESET; // In ô đã đi qua
                                }
                                else if (i == p1 && j == p2) {
                                    cout << ANSI_COLOR_ORANGE << "\t" << "S1 " << "\t" << ANSI_COLOR_RESET;
                                }
                                else if (a[i][j] == -1) {
                                    cout << ANSI_COLOR_ORANGE << "\t" << "X " << "\t" << ANSI_COLOR_RESET;

                                }
                                else if (i == e1 && j == g1) {
                                    cout << ANSI_COLOR_WINE << "\t" << "*  " << "\t" << ANSI_COLOR_RESET; // In ô hiện tại được đánh dấu *

                                }
                                else {
                                    cout << "\t" << a[i][j] << "\t"; // In giá trị của ô
                                }
                            }
                            cout << "\n";
                        }
                        dem2++; // Tăng số bước đi của robot 2 lên 1
                    }
                    else {
                        cout << ANSI_COLOR_PINK << "\t\tDi chuyen khong hop le cho robot 2!\n" << ANSI_COLOR_RESET;
                    }
                }
            }
            if (!checkIT1 && !checkIT2) {
                break;
            }
        }
        // In quãng đường đã đi của robot 1
        cout << ANSI_COLOR_ORANGE << "\n\t\tQuang duong da di cua robot 1: " << ANSI_COLOR_RESET;
        for (int i = 0; i < dem1; i++) {
            cout << b1[i] << " ";
        }
        cout << ANSI_COLOR_ORANGE << "\n\t\tQuang duong robot1 di duoc: " << dem1 << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_ORANGE << "\n\t\tTong quang duong da di cua robot 1: " << tong1 << ANSI_COLOR_RESET << endl;

        // In quãng đường đã đi của robot 2
        cout << ANSI_COLOR_BLUE << "\n\t\tQuang duong da di cua robot 2: " << ANSI_COLOR_RESET;
        for (int i = 0; i < dem2; i++) {
            cout << b2[i] << " ";
        }
        cout << ANSI_COLOR_BLUE << "\n\t\tQuang duong robot2 di duoc: " << dem2 << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_BLUE << "\n\t\tTong quang duong da di cua robot 2: " << tong2 << ANSI_COLOR_RESET << endl;
        if (tong1 == tong2) {
            printSlowlyColor("\t\tDRAW", 1, ANSI_COLOR_RED);
        }
        else if (tong1 > tong2) {
            printSlowlyColor("\t\tRobot1 Win", 1, ANSI_COLOR_RED);
        }
        else {
            printSlowlyColor("\t\tRobot2 Win", 1, ANSI_COLOR_RED);
        }
        delete[] b1;
        delete[] b2;
        printSlowlyColor("\n\n\n\n                                                 Tiep tuc khong? Nhan 0 de thoat! ", 1, ANSI_COLOR_PINK);
        int choose = 0;
        cin >> choose;
        if (choose == 0) {
            break;
        }
    } while (true);
}
void body2_item3() {
    srand(time(NULL));
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n\n\n", 1);
    printSlowlyColor("\n                                                 __TRY ON IT__", 1, ANSI_COLOR_CYAN);
    printSlowlyColor("\n                                             Hay tap lam quen voi no!\n\n\n", 1, ANSI_COLOR_CYAN);
    n = 6;
    m = 5;
    int e1 = 0, g1 = 0;
    int start1 = 0;
    bool flag = true;
    int choose = 0;
    do {
        do {
            printSlowlyColor("\n                                                  Ban muon chon che do nao ? ", 1, ANSI_COLOR_CYAN);
            printSlowlyColor("\n                                                  1.May tu dieu khien robot ", 1, ANSI_COLOR_CYAN);
            printSlowlyColor("\n                                                  2.Ban tu dieu khien robot ", 1, ANSI_COLOR_CYAN);
            cin >> choose;
            if (choose < 1 || choose > 2) {
                printSlowlyColor("\n\t\tERROR. Vui long chon lai che do: ", 1, ANSI_COLOR_CYAN);
            }
        } while (choose < 1 || choose > 2);
        if (choose == 1) {
            int* b = new int[100];
            Coordinate start;
            do {
                printSlowlyColor("\n\nMoi ban nhap toa do x,y: ", 1, ANSI_COLOR_CYAN);
                cin >> start.x >> start.y;;
                if (start.x < 0 || start.y < 0 || start.x>5 || start.y>4) {
                    printSlowlyColor("\n\nERROR. Vui long nhap lai toa do: ", 1, ANSI_COLOR_CYAN);
                }
            } while (start.x < 0 || start.y < 0 || start.x>5 || start.y>4);
            // Cấp phát động cho ma trận a
            int** a = createArray(n, m);
            int** e = createArray_e(n, m);
            // Khởi tạo giá trị cho ma trận a
            int** maTranDoc = docMaTranTuFile("input.txt", n, m);
            // xuất màn hình
            if (maTranDoc != nullptr) {
                // Xuất ma trận ra màn hình
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        a[i][j] = maTranDoc[i][j];
                        e[i][j] = maTranDoc[i][j];
                        cout << "\t" << a[i][j] << "\t";
                    }
                    cout << "\n";
                }
            }
            long tong = e[start.x][start.y];
            long sum = tinhTong(e, start);
            long sum1 = findMaxPath(a, start, start.x, start.y, b);
            tong += sum;
            printSlowlyColor("\n\t\tTong quang duong di duoc: ", 1, ANSI_COLOR_CYAN);
            cout << tong;
            printSlowlyColor("\n\t\tDuong di cua Robot: ", 1, ANSI_COLOR_CYAN);
            visualizePath(a, n, m, b);
            // Giải phóng bộ nhớ của maTranDoc và a
            deleteArray(maTranDoc, n);
            deleteArray(a, n);
            deleteArray(e, n);
            delete[] b;
        }
        if (choose == 2) {
            do {
                printSlowlyColor("\n\nMoi ban nhap toa do x,y: ", 1, ANSI_COLOR_CYAN);
                cin >> e1 >> g1;
                if (e1 < 0 || g1 < 0 || e1>5 || g1>4) {
                    printSlowlyColor("\nERROR. Vui long nhap lai toa do: ", 1, ANSI_COLOR_CYAN);
                }
            } while (e1 < 0 || g1 < 0 || e1>5 || g1>4);
            // nhập mê cung
            long a[6][5] = {
       {2, 1, 14, 12, 17},
       {3, 16, 22, 91, 23},
       {4, 56, 87, 31, 65},
       {27, 43, 90, 100, 101},
       {76, 54, 32, 99, 66},
       {178, 154, 150, 200, 543}
            };
            cout << "\n\n";
            // xuất màn hình
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i == e1 && j == g1) {
                        cout << ANSI_COLOR_CYAN << "\t" << "S" << ANSI_COLOR_RESET << "\t";
                    }
                    else {
                        cout << "\t" << a[i][j] << "\t";
                    }
                }
                cout << "\n";
            }
            int dem = 1;
            int* b = new int[100];
            long currentX = e1;
            long currentY = g1;
            long newX = currentX;
            long newY = currentY;
            // Thực hiện di chuyển robot
            long trai, phai, tren, duoi = 0;
            char move;
            long tong = a[e1][g1];
            b[0] = a[e1][g1];
            while (true) {
                a[e1][g1] = -1;
                bool isValidMove = true;
                cout << ANSI_COLOR_CYAN << "\t\tNhap A, S, D, W de di chuyen robot (X de thoat): " << ANSI_COLOR_RESET;
                move = _getch(); // Sử dụng _getch() để đọc ký tự từ người dùng trên Windows
                cout << move << endl;

                if (move == 'X' || move == 'x') {
                    break; // Thoát khỏi vòng lặp nếu người dùng nhập X hoặc x
                }
                // Xử lý các phím di chuyển
                if (move == 'A' || move == 'a') {
                    newY = currentY - 1;
                    newX = currentX;
                    // Di chuyển sang trái
                }
                else if (move == 'D' || move == 'd') {
                    newY = currentY + 1; // Di chuyển sang phải
                    newX = currentX;
                }
                else if (move == 'W' || move == 'w') {
                    newX = currentX - 1; // Di chuyển lên trên
                    newY = currentY;
                }
                else if (move == 'S' || move == 's') {
                    newX = currentX + 1; // Di chuyển xuống dưới
                    newY = currentY;
                }
                else {
                    isValidMove = false;
                }
                if (newX < 0 || newX >= n || newY < 0 || newY >= m) {
                    isValidMove = false;
                }
                if (move == 'A' || move == 'a') {
                    trai = a[currentX][currentY - 1];
                    phai = a[currentX][currentY + 1];
                    tren = a[currentX - 1][currentY];
                    duoi = a[currentX + 1][currentY];
                    if (currentX - 1 < 0) {
                        tren = -1;
                    }
                    if (currentX + 1 >= n) {
                        duoi = -1;
                    }
                    if (currentY - 1 < 0) {
                        trai = -1;
                    }
                    if (currentY + 1 >= m) {
                        phai = -1;
                    }
                    if (trai < phai || trai < tren || trai < duoi)
                    {
                        isValidMove = false;
                    }
                }
                else if (move == 'D' || move == 'd') {
                    trai = a[currentX][currentY - 1];
                    phai = a[currentX][currentY + 1];
                    tren = a[currentX - 1][currentY];
                    duoi = a[currentX + 1][currentY];
                    if (currentX - 1 < 0) {
                        tren = -1;
                    }
                    if (currentX + 1 >= n) {
                        duoi = -1;
                    }
                    if (currentY - 1 < 0) {
                        trai = -1;
                    }
                    if (currentY + 1 >= m) {
                        phai = -1;
                    }
                    if (phai < trai || phai < tren || phai < duoi)
                    {
                        isValidMove = false;
                    }
                }
                else if (move == 'W' || move == 'w') {
                    trai = a[currentX][currentY - 1];
                    phai = a[currentX][currentY + 1];
                    tren = a[currentX - 1][currentY];
                    duoi = a[currentX + 1][currentY];
                    if (currentX - 1 < 0) {
                        tren = -1;
                    }
                    if (currentX + 1 >= n) {
                        duoi = -1;
                    }
                    if (currentY - 1 < 0) {
                        trai = -1;
                    }
                    if (currentY + 1 >= m) {
                        phai = -1;
                    } if (tren < trai || tren < phai || tren < duoi)
                    {
                        isValidMove = false;
                    }
                }
                else if (move == 'S' || move == 's') {
                    trai = a[currentX][currentY - 1];
                    phai = a[currentX][currentY + 1];
                    tren = a[currentX - 1][currentY];
                    duoi = a[currentX + 1][currentY];
                    if (currentX - 1 < 0) {
                        tren = -1;
                    }
                    if (currentX + 1 >= n) {
                        duoi = -1;
                    }
                    if (currentY - 1 < 0) {
                        trai = -1;
                    }
                    if (currentY + 1 >= m) {
                        phai = -1;
                    }  if (duoi < trai || duoi < phai || duoi < tren)
                    {
                        isValidMove = false;
                    }
                }
                if (move == 'A' || move == 'a') {
                    if (trai == -1 || newY < 0) {
                        isValidMove = false;
                    }
                }
                if (move == 'D' || move == 'd') {
                    if (phai == -1 || newY >= m) {
                        isValidMove = false;
                    }
                }if (move == 'w' || move == 'W') {
                    if (tren == -1 || newX < 0) {
                        isValidMove = false;
                    }
                }if (move == 'S' || move == 's') {
                    if (duoi == -1 || newX >= n) {
                        isValidMove = false;
                    }
                }
                if (trai < 0 && phai < 0 && tren < 0 && duoi < 0) {
                    printSlowlyColor("\n\t\tQuang duong di duoc: ", 1, ANSI_COLOR_CYAN);
                    for (int i = 0; i < dem; i++) {
                        cout << b[i] << " ";
                    }
                    printSlowlyColor("\n\t\tTong quang duong di duoc: ", 1, ANSI_COLOR_CYAN);
                    cout << tong;
                    printSlowlyColor("\n\t\tDo dai quang duong di duoc: ", 1, ANSI_COLOR_CYAN);
                    cout << dem;
                    delete[] b;
                    break;
                }
                if (isValidMove) {
                    currentX = newX;
                    currentY = newY;
                    b[dem] = a[currentX][currentY];
                    tong += a[currentX][currentY];
                    a[currentX][currentY] = -1; // Đánh dấu ô đã đi qua
                    cout << "\n\n";
                    cout << ANSI_COLOR_CYAN << "\t\tMa tran sau khi di chuyen:\n" << ANSI_COLOR_RESET;
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {
                            if (i == currentX && j == currentY) {
                                cout << ANSI_COLOR_WINE << "\t" << "*  " << "\t" << ANSI_COLOR_RESET; // In ô hiện tại được đánh dấu *
                                dem++;
                            }
                            else if (a[i][j] == -1) {
                                cout << ANSI_COLOR_CYAN << "\t" << "X  " << "\t" << ANSI_COLOR_RESET; // In ô đã đi qua
                            }
                            else {
                                cout << "\t" << a[i][j] << "\t"; // In giá trị của ô
                            }
                        }
                        cout << "\n";
                    }
                }
                else {
                    cout << ANSI_COLOR_CYAN << "\t\tDi chuyen khong hop le!\n" << ANSI_COLOR_RESET;
                }
            }
        }
        printSlowlyColor("\n\n\n\n                                                  Tiep tuc khong? Nhan 0 de thoat!!", 1, ANSI_COLOR_CYAN);
        cin >> choose;
        if (choose == 0) {
            flag = false;
            break;
        }
    } while (flag);
}
void body2_item4() {
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t", 1);
    printSlowlyColor("\n\n\n\n                                                 _____HELP_____", 2, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\n\t\tChao mung ban da den voi Robot World. Day la 1 tro ma tran Robot.", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tSe co 5 muc MENU.", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t1.PLAY WITH COMPUTER. Ban se duoc choi voi may", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t2.PLAY WITH FRIEND. Ban se choi voi ban", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t3.TRY IT ON. Ban se duoc trai nghiem 1 con Robot", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tTro choi se nhu sau:", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t- Robot se di theo 4 huong: Tren, phai, duoi, trai ", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t- Robot se di theo huong co gia tri lon nhat", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t- Voi mode Normal, Robot tu dong di chuyen theo huong ma hai nguoi choi nhap vao ban dau robot khi", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tco diem so lon nhat, khong duoc di nhung o trung nhau", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\t- Voi mode Intersection, Robot se tu dong di theo huong ma hai nguoi choi nhap vao ban dau robot khi", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tco diem so lon nhat, duoc phep di nhung o trung nhau", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tKhong duoc phep di chuyen ra khoi me cung", 1, ANSI_COLOR_YELLOW);
    printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
    printSlowlyColor("\n\t\tCac nut di chuyen: ", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tA/J: Di chuyen ben trai", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tW/I: Di chuyen len tren", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tD/L: Di chuyen ben phai", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tS/K: Di chuyen xuong duoi", 1, ANSI_COLOR_YELLOW);
}
void body2_item5(const inputName& input) {
    printSlowlyColor("\n\n\n\n                                                 _____ABOUT ME_____", 2, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\n\t\tXin chao ", 1, ANSI_COLOR_YELLOW);
    cout << input.str;
    printSlowlyColor("\n\t\tChao mung ban da den voi tro choi Robot.", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tToi la Huynh Tan Phuc, la sinh vien Truong Dai hoc Giao Thong Van Tai TPHCM", 1, ANSI_COLOR_YELLOW);
    printSlowlyColor("\n\t\tMSSV: 2251330030. Chuc ban 1 ngay that vui ve nhe. Cam on ban da ung ho tro choi cua chung toi.", 1, ANSI_COLOR_YELLOW);
}
int main()
{
    srand(time(NULL));
    // Kích thước mê cung
    header();
    inputName input;
    enterName(input);
    int i;
    bool flag = true;

    do {
        body1();
        printSlowly("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n", 1);
        do {
            printSlowlyColor("\n\n                                                  WHICH ITEMS WILL YOU CHOOSE: ", 1, ANSI_COLOR_YELLOW);
            cin >> i;
            if (i == 1) {
                printSlowlyColor("\n\n                                                  YOU CHOOSE PLAY WITH COMPUTER", 1, ANSI_COLOR_YELLOW);
                body2_item1();
            }
            if (i == 2) {
                printSlowlyColor("\n\n                                                  YOU CHOOSE PLAY WITH FRIEND", 1, ANSI_COLOR_YELLOW);
                body2_item2();
            }
            if (i == 3) {
                printSlowlyColor("\n\n                                                  YOU CHOOSE TRY ON IT", 1, ANSI_COLOR_YELLOW);
                body2_item3();

            }
            if (i == 4) {
                printSlowlyColor("\n\n                                                  YOU CHOOSE HELP", 1, ANSI_COLOR_YELLOW);
                body2_item4();
            }
            if (i == 5) {
                printSlowlyColor("\n\n                                                  YOU CHOOSE ABOUT ME", 1, ANSI_COLOR_YELLOW);
                body2_item5(input);
            }if (i == 0) {
                flag = false;
                break;
            }
            if (i < 0 || i >5) {
                printSlowlyColor("\n\n                                                  ERROR. PLEASE CHOOSE AGAIN", 1, ANSI_COLOR_YELLOW);
            }

        } while (i < 0 || i > 5);


    } while (flag);
    // Giải phóng bộ nhớ đã cấp phát
    delete[] input.str;
    return 0;
}

