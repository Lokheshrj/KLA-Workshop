#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

struct Die {
    int x, y;
    double llcX, llcY;

    Die(int x, int y, double llcX, double llcY) : x(x), y(y), llcX(llcX), llcY(llcY) {}
};

pair<double, double> calculateLLC(float dieShiftX, float dieShiftY, float distanceToCOWX, float distanceToCOWY) {
    double llcX = dieShiftX + distanceToCOWX;
    double llcY = dieShiftY + distanceToCOWY;

    return make_pair(llcX, llcY);
}

vector<Die> generateDies(float waferDiameter, float dieSizeX, float dieSizeY, float dieShiftX, float dieShiftY, float distanceToCOWX, float distanceToCOWY, int rows, int columns) {
    vector<Die> dies;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double llcX = float(i) * dieSizeX + calculateLLC(dieShiftX, dieShiftY, distanceToCOWX, 0).first;
            double llcY = float(j) * dieSizeY + calculateLLC(dieShiftX, dieShiftY, 0, distanceToCOWY).second;
            dies.emplace_back(i, j, llcX, llcY);
        }
    }
    return dies;
}

int main() {
    fstream file;
    file.open("./Milestone3/Input/Testcase1.txt", ios::in);

    if (!file) {
        cout << "File not found..!" << endl;
        return 1;
    }

    vector<int> inputs;
    char ch;
    int c = 1;

    while (!file.eof()) {
        ch = file.get();
        if (ch == ':') {
            string str = "";
            do {
                ch = file.get();
                if (isdigit(ch)) {
                    str += ch;
                    c = 1;
                } else if ((!isdigit(ch)) && c == 1) {
                    inputs.push_back(stoi(str));
                    str = "";
                    c = 0;
                }
            } while (isdigit(ch) || ch == 'x' || ch == ',' || ch == '(' || ch == ')');
        }
    }

    file.close();


    float waferDiameter = inputs[0];
    float dieSizeX = inputs[1];
    float dieSizeY = inputs[2];
    float dieShiftX = inputs[3];
    float dieShiftY = inputs[4];
    float distanceToCOWX = inputs[5];
    float distanceToCOWY = inputs[6];

    int rows = waferDiameter / dieSizeX;
    int columns = waferDiameter / dieSizeY;

    vector<Die> dies = generateDies(waferDiameter, dieSizeX, dieSizeY, dieShiftX, dieShiftY, distanceToCOWX, distanceToCOWY, rows, columns);
    fstream resultFile("result3.txt", ios::out);

    if (!resultFile) {
        cout << "Error creating result file." << endl;
        return 1;
    }

    for (const auto &die : dies) {
        resultFile << "(" << die.x << "," << die.y << "):(" << die.llcX << "," << die.llcY << ")\n";
        cout << "(" << die.x << "," << die.y << "):(" << die.llcX << "," << die.llcY << ")\n";
    }

    resultFile.close();

    return 0;
}
