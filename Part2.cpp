#include <iostream>
#include <cfloat>
#include <cmath>
#include "Header.h"
using namespace std;

//Using float lliterals in arrays for memory optimization

//Motors Array
int motorCount = 5;
Motor motors[5] = {

motors[0] = { 15.5f, 22.0f, 12100.0f, 20.0f, 1.0f },
motors[1] = { 405.0f, 60.0f, 4300.0f, 25.0f, 1.3f },
motors[2] = { 0.649f, 8.0f, 11700.0f, 30.0f, 1.5f },
motors[3] = { 540.0f, 60.0f, 4300.0f, 35.0f, 1.7f },
motors[4] = { 2.19f, 10.0f, 12000.0f, 40.0f, 2.0f },
};
//Gearboxes Array
int gearCount = 5;
Gearbox gears[5] = {

gears[0] = { 26.0f, 19.0f, 0.7f, 15.0f, 0.5f },
gears[1] = { 150.0f, 14.0f, 0.75f, 20.0f, 0.7f },
gears[2] = { 4.4f, 16.0f, 0.8f, 25.0f, 1.0f },
gears[3] = { 84.0f, 16.0f, 0.85f, 30.0f, 1.3f },
gears[4] = { 734.0f, 12.0f, 0.9f, 35.0f, 1.5f },
};
//Since some parameters (mass, width, efficiency) are not included in the provided dataset,
//approximate values are assumed to allow the optimization process to function correctly.

float calculateCost(Motor m, Gearbox g)
{
    return m.mass + g.mass +
        (m.diameter + g.diameter) / 100 +
        (m.width + g.width) / 100;
}

//Optimization
void solvebestcombination(float T_required, float speed_required)
{
    float bestCost = FLT_MAX;
    int bestMotorIndex = -1;
    int bestGearIndex = -1;

    for (int i = 0; i < motorCount; i++) {
        for (int j = 0; j < gearCount; j++) {

            float T_output = motors[i].torque * gears[j].ratio * gears[j].efficiency;
            float speed_output = motors[i].speed / gears[j].ratio;

            // Check conditions

            if (T_output >= T_required && speed_output >= speed_required) {

                float cost = calculateCost(motors[i], gears[j]);

                if (cost < bestCost) {
                    bestCost = cost;
                    bestMotorIndex = i;
                    bestGearIndex = j;
                }
            }
        }
    }
    // Output
    if (bestMotorIndex == -1) {
        cout << "\nNo suitable combination found.\n";
    }
    else {
        cout << "\nBest Combination Found:\n";

        cout << "\nMotor:\n";
        cout << "Torque: " << motors[bestMotorIndex].torque << "mNm\n";
        cout << "Speed: " << motors[bestMotorIndex].speed << "rpm\n";
        cout << "Mass: " << motors[bestMotorIndex].mass << "kg\n";

        cout << "\nGearbox:\n";
        cout << "Ratio: " << gears[bestGearIndex].ratio << endl;
        cout << "Efficiency: " << gears[bestGearIndex].efficiency << endl;

        cout << "\nTotal Cost: " << bestCost << endl;
    }
}