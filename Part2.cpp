#include <iostream>
#include <cfloat>
#include <cmath>
#include "Header.h"

// Torque in Nm, Speed in RPM, Diameter/Width in mm, Mass in kg

//Motors Array
int motorCount = 5;
Motor motors[5] = {
    { 15.5f,  22.0f, 12100.0f, 20.0f, 1.0f },
    { 405.0f, 60.0f,  4300.0f, 25.0f, 1.3f },
    { 0.649f,  8.0f, 11700.0f, 30.0f, 1.5f },
    { 540.0f, 60.0f,  4300.0f, 35.0f, 1.7f },
    { 2.19f,  10.0f, 12000.0f, 40.0f, 2.0f },
};

//Gearboxes Array
int gearCount = 5;
Gearbox gears[5] = {
    {  26.0f, 19.0f, 0.70f, 15.0f, 0.5f },
    { 150.0f, 14.0f, 0.75f, 20.0f, 0.7f },
    {   4.4f, 16.0f, 0.80f, 25.0f, 1.0f },
    {  84.0f, 16.0f, 0.85f, 30.0f, 1.3f },
    { 734.0f, 12.0f, 0.90f, 35.0f, 1.5f },
};

float calculateCost(Motor m, Gearbox g)
{
    return m.mass + g.mass +
        (m.diameter + g.diameter) / 1000.0f +
        (m.width    + g.width)    / 1000.0f;
}

//Optimization
void solvebestcombination(float T_required, float speed_required)
{
    float bestCost     = FLT_MAX;
    int bestMotorIndex = -1;
    int bestGearIndex  = -1;

    for (int i = 0; i < motorCount; i++) {
        for (int j = 0; j < gearCount; j++) {

            float T_output     = motors[i].torque * gears[j].ratio * gears[j].efficiency;
            float speed_output = motors[i].speed  / gears[j].ratio;

            // Check conditions
            if (T_output >= T_required && speed_output >= speed_required) {

                float cost = calculateCost(motors[i], gears[j]);

                if (cost < bestCost) {
                    bestCost       = cost;
                    bestMotorIndex = i;
                    bestGearIndex  = j;
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
        cout << "Torque: " << motors[bestMotorIndex].torque << " Nm\n";
        cout << "Speed: "  << motors[bestMotorIndex].speed  << " RPM\n";
        cout << "Mass: "   << motors[bestMotorIndex].mass   << " kg\n";

        cout << "\nGearbox:\n";
        cout << "Ratio: "      << gears[bestGearIndex].ratio               << "\n";
        cout << "Efficiency: " << gears[bestGearIndex].efficiency * 100.0f << " %\n";

        float T_out     = motors[bestMotorIndex].torque * gears[bestGearIndex].ratio * gears[bestGearIndex].efficiency;
        float speed_out = motors[bestMotorIndex].speed  / gears[bestGearIndex].ratio;

        cout << "\nOutput Torque: " << T_out << " Nm (required: " << T_required << " Nm)\n";
        cout << "Output Speed: "   << speed_out << " RPM (required: " << speed_required  << " RPM)\n";
        cout << "\nTotal Cost: "   << bestCost  << "\n";
    }
}
