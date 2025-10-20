
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstring>
using namespace std;
#define MAX 100

void splashScreen() {
    cout << "============================================================\n";
    cout << "              SIGNALS AND SYSTEMS TERMINAL LAB              \n";
    cout << "============================================================\n";
}

void inputSignal(float x[], int &n, const char name[]) {
    cout << "\nEnter number of samples for " << name << ": ";
    cin >> n;
    cout << "Enter " << n << " samples:\n";
    for (int i = 0; i < n; i++) {
        cout << name << "[" << i << "] = ";
        cin >> x[i];
    }
}
void displaySignal(float x[], int n, const char name[]) {
    cout << "\n--- " << name << " Signal ---\n";
    for (int i = 0; i < n; i++)
        cout << name << "[" << i << "] = " << x[i] << endl;
}

void plotSignal(float x[], int n, const char name[]) {
    cout << "\n" << name << " (ASCII plot):\n";
    for (int i = 0; i < n; i++) {
        int val = static_cast<int>(round(x[i]));
        cout << setw(3) << i << " | ";
        if (val >= 0)
            cout << string(val, '*') << " (" << x[i] << ")";
        else
            cout << "-" << string(abs(val), '*') << " (" << x[i] << ")";
        cout << endl;
    }
}
void scaling(float x[], int n) {
    float k;
    cout << "\nEnter scaling factor k: ";
    cin >> k;
    for (int i = 0; i < n; i++)
        x[i] *= k;
    cout << "Signal scaled successfully.\n";
}

void addition(float x1[], int n1, float x2[], int n2) {
    int n = max(n1, n2);
    float y[MAX];
    for (int i = 0; i < n; i++) {
        float a = (i < n1) ? x1[i] : 0;
        float b = (i < n2) ? x2[i] : 0;
        y[i] = a + b;
    }
    displaySignal(y, n, "Added");
}

void reversal(float x[], int n) {
    float y[MAX];
    for (int i = 0; i < n; i++)
        y[i] = x[n - 1 - i];
    displaySignal(y, n, "Reversed");
    plotSignal(y, n, "Reversed");
}

void shift(float x[], int n) {
    int k;
    cout << "Enter shift value (positive = delay, negative = advance): ";
    cin >> k;
    float y[MAX] = {0};

    for (int i = 0; i < n; i++) {
        int shiftedIndex = i + k;
        if (shiftedIndex >= 0 && shiftedIndex < MAX)
            y[shiftedIndex] = x[i];
    }
    displaySignal(y, n + abs(k), "Shifted");
}

void convolution(float x[], int n1, float h[], int n2) {
    float y[MAX] = {0};
    int n3 = n1 + n2 - 1;

    for (int n = 0; n < n3; n++) {
        y[n] = 0;
        for (int k = 0; k < n1; k++) {
            if ((n - k) >= 0 && (n - k) < n2)
                y[n] += x[k] * h[n - k];
        }
    }

    displaySignal(y, n3, "Convolution Output");
    plotSignal(y, n3, "Convolution Output");
}

void correlation(float x[], int n1, float h[], int n2, bool autoCorr) {
    float y[MAX] = {0};
    int n3 = n1 + n2 - 1;

    for (int n = 0; n < n3; n++) {
        y[n] = 0;
        for (int k = 0; k < n1; k++) {
            int j = n - k;
            if (j >= 0 && j < n2)
                y[n] += x[k] * h[j];
        }
    }

    if (autoCorr)
        displaySignal(y, n3, "Auto-Correlation");
    else
        displaySignal(y, n3, "Cross-Correlation");

    plotSignal(y, n3, "Correlation Plot");
}

void checkLTI(float x1[], int n1, float x2[], int n2, float h[], int nh) {
    float y1[MAX] = {0}, y2[MAX] = {0}, y_sum[MAX] = {0};
    int n3 = n1 + nh - 1;
    int n4 = n2 + nh - 1;
    int n = max(n3, n4);

    for (int n = 0; n < n3; n++)
        for (int k = 0; k < n1; k++)
            if ((n - k) >= 0 && (n - k) < nh)
                y1[n] += x1[k] * h[n - k];

    for (int n = 0; n < n4; n++)
        for (int k = 0; k < n2; k++)
            if ((n - k) >= 0 && (n - k) < nh)
                y2[n] += x2[k] * h[n - k];

    float x_sum[MAX];
    int n_sum = max(n1, n2);
    for (int i = 0; i < n_sum; i++) {
        float a = (i < n1) ? x1[i] : 0;
        float b = (i < n2) ? x2[i] : 0;
        x_sum[i] = a + b;
    }

    float y_total[MAX] = {0};
    int n_total = n_sum + nh - 1;
    for (int n = 0; n < n_total; n++)
        for (int k = 0; k < n_sum; k++)
            if ((n - k) >= 0 && (n - k) < nh)
                y_total[n] += x_sum[k] * h[n - k];

    for (int i = 0; i < n; i++)
        y_sum[i] = y1[i] + y2[i];

    cout << "\nChecking LTI Property...\n";
    bool isLTI = true;
    for (int i = 0; i < n_total; i++) {
        if (fabs(y_sum[i] - y_total[i]) > 1e-3) {
            isLTI = false;
            break;
        }
    }

    if (isLTI)
        cout << "System is LINEAR and TIME-INVARIANT (LTI)\n";
    else
        cout << "System is NOT LTI\n";
}

void checkStability(float h[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += fabs(h[i]);
    cout << "\nSum of |h[n]| = " << sum << endl;
    if (sum < 1e6)
        cout << "System is STABLE (BIBO)\n";
    else
        cout << "System is UNSTABLE\n";
}

int main() {
    splashScreen();

    float x1[MAX], x2[MAX], h[MAX];
    int n1 = 0, n2 = 0, nh = 0;
    int choice;

    inputSignal(x1, n1, "x1[n]");

    do {
        cout << "\n============== MENU ==============\n";
        cout << "1. Scaling\n";
        cout << "2. Addition\n";
        cout << "3. Reversal\n";
        cout << "4. Time Shifting\n";
        cout << "5. Convolution\n";
        cout << "6. Correlation\n";
        cout << "7. LTI System Check\n";
        cout << "8. Stability Check\n";
        cout << "9. Display Signal\n";
        cout << "0. Exit\n";
        cout << "==================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                scaling(x1, n1);
                break;
            case 2:
                inputSignal(x2, n2, "x2[n]");
                addition(x1, n1, x2, n2);
                break;
            case 3:
                reversal(x1, n1);
                break;
            case 4:
                shift(x1, n1);
                break;
            case 5:
                inputSignal(h, nh, "h[n]");
                convolution(x1, n1, h, nh);
                break;
            case 6:
                inputSignal(x2, n2, "x2[n]");
                correlation(x1, n1, x2, n2, false);
                break;
            case 7:
                inputSignal(x2, n2, "x2[n]");
                inputSignal(h, nh, "h[n]");
                checkLTI(x1, n1, x2, n2, h, nh);
                break;
            case 8:
                inputSignal(h, nh, "h[n]");
                checkStability(h, nh);
                break;
            case 9:
                displaySignal(x1, n1, "x1[n]");
                plotSignal(x1, n1, "x1[n]");
                break;
            case 0:
                cout << "\nExiting Signals Lab...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}







