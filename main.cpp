#include <iostream>
#include <vector>
#include <cfloat>
#include "Header.h"
using namespace std;

extern vector<Material> materials;



int main() {

//part1

    int shape;
    while(true)
    {
        cout << "Choose cross-section:\n1 - Rectangle\n2 - Circle\n";
        cin >> shape;
        if(shape==1||shape==2)break;
        cout<<"invalid choice!\n";

    }
    cout << "\nAvailable materials:\n";
    for (int i = 0; i < materials.size(); i++) {
        cout << i << " - " << materials[i].name << endl;
    }

    int matChoice;
    while(true)
    {
        cout << "Select material: ";
        cin >> matChoice;
        if(matChoice>=0 && matChoice < materials.size())
            break;
        cout<<"invalid material choice!\n";
    }
    Material selected = materials[matChoice];

    double L, mp, amax;
    do
    {
        cout << "\nEnter link length (L) in meters: ";
        cin >> L; 
        if (L <= 0) 
           cout << "Invalid! Enter a positive number.\n";
    } while (L <= 0);
        
    do
    {
        cout << "Enter payload mass (mp) in Kg: ";
        cin >> mp;
       if (mp <= 0)
           cout << "Invalid! Enter a positive number.\n";
    } while (mp <= 0);

    do
    {
        cout << "Enter max acceleration (amax) Rad/s^2: ";
        cin >> amax;
        if (amax <= 0)
            cout << "Invalid! Enter a positive number.\n";
    } while (amax <= 0);
    
      
    double finalMass = 0;

    if (shape == 1) {
        double b, h;
        do
        {
             cout << "\nEnter width (b) in meters: ";
            cin >> b;
            if (b <= 0)
                cout << "Invalid! Enter a positive number.\n";
        } while (b <= 0);
        
        do
        {
            cout << "Enter height (h) in meters: ";
            cin >> h;
            if (h <= 0)
                cout << "Invalid! Enter a positive number.\n";
        } while (h <= 0);

        optRectangle(b, h, selected.density, mp, L, amax, selected.yieldStrength, finalMass);

        cout << "\nFinal: b = " << b << " m, h = " << h << " m\n";
    }
    else if (shape == 2) {
        double r;
        do
        {
            cout << "\nEnter radius (r) in meters: ";
            cin >> r;
            if (r <= 0)
                cout << "Invalid! Enter a positive number.\n";
        } while (r <= 0);
        
        optCircle(r, selected.density, mp, L, amax,
                  selected.yieldStrength, finalMass);

        cout << "\nFinal: r = " << r << " m\n";
    }

    cout << "\nFinal Link Mass = " << finalMass << " kg\n";


//PART2

float T_required;
      T_required=(finalMass*9.81*(L/2))+(mp*9.81*L)+(finalMass*(L/2)*(L/2)*amax)+(mp*L*L*amax);
    cout << "\nRequired Torque =" << T_required << "Nm\n";

    float speed_required;

    do
    {
      cout << "Enter required speed (rad/s): ";
      cin >> speed_required; 
      if (speed_required <= 0) 
          cout << "Invalid! Enter a positive number.\n";
    } while (speed_required <= 0);
    
    solvebestcombination(T_required, speed_required);

    return 0;
}
