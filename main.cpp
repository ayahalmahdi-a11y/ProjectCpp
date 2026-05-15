#include <iostream>
#include <vector>
#include <cfloat>
#include <limits>
#include "Header.h"
using namespace std;

extern vector<Material> materials;

// ── Input helpers ─────────────────────────────────────────────────────────────

// Read a validated integer in [minVal, maxVal]
int getInt(const string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal)
            return val;
        cout << "Invalid input. Please enter a whole number between "
             << minVal << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a validated double strictly greater than minVal
double getDouble(const string& prompt, double minVal = 0.0) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val && val > minVal)
            return val;
        cout << "Invalid input. Please enter a number greater than "
             << minVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {

    // ── PART 1 ────────────────────────────────────────────────────────────────

    cout << "Choose cross-section:\n1 - Rectangle\n2 - Circle\n";
    int shape = getInt("Enter choice: ", 1, 2);

    cout << "\nAvailable materials:\n";
    for (int i = 0; i < (int)materials.size(); i++)
        cout << i << " - " << materials[i].name << "\n";

    int matChoice = getInt("Select material: ", 0, (int)materials.size() - 1);
    Material selected = materials[matChoice];

    double L    = getDouble("\nEnter link length (L) in meters: ");
    double mp   = getDouble("Enter payload mass (mp) in kg: ");
    double amax = getDouble("Enter max acceleration (amax) in Rad/s^2: ");

    double finalMass = 0.0;

    if (shape == 1) {
        double b = getDouble("\nEnter initial width (b) in meters: ");
        double h = getDouble("Enter initial height (h) in meters: ");

        optRectangle(b, h, selected.density, mp, L, amax, selected.yieldStrength, finalMass);

        cout << "\nFinal: b = " << b << " m, h = " << h << " m\n";
    }
    else {
        double r = getDouble("\nEnter initial radius (r) in meters: ");

        optCircle(r, selected.density, mp, L, amax, selected.yieldStrength, finalMass);

        cout << "\nFinal: r = " << r << " m\n";
    }

    cout << "\nFinal Link Mass = " << finalMass << " kg\n";

    // ── PART 2 ────────────────────────────────────────────────────────────────

    double T_required = (finalMass * 9.81 * (L / 2.0))
                      + (mp       * 9.81 *  L)
                      + (finalMass * (L / 2.0) * (L / 2.0) * amax)
                      + (mp        *  L         *  L        * amax);

    cout << "\nRequired Torque = " << T_required << " Nm\n";

    double speed_required = getDouble("Enter required output speed (RPM): ");

    solvebestcombination((float)T_required, (float)speed_required);

    return 0;
}
