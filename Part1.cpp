#include <iostream>
#include <cmath>
#include "M_PI.h"
#include <vector>
#include "Header.h"
using namespace std;

// Constructor
Material::Material(string n, double ys, double d)
    : name(n), yieldStrength(ys), density(d) {
}

vector<Material> materials = {
    Material("Cast Iron", 130.0, 7300.0),
    Material("Copper Nickel", 130.0, 8940.0),
    Material("Brass", 200.0, 8730.0),
    Material("Aluminum", 241.0, 2700.0),
    Material("Steel", 247.0, 7580.0),
    Material("Acrylic", 72.0, 1160.0),
    Material("Copper", 70.0, 8920.0),
    Material("Stainless Steel", 275.0, 7860.0),
    Material("Tungsten", 941.0, 19250.0)
};


double calcLinkMass_Rectangle(double density, double b, double h, double L) {
    return density * (b * h * L);
}

double calcLinkMass_Circle(double density, double r, double L) {
    return density * (M_PI * r * r * L);
}

double calcBendingMoment(double m1, double mp, double L, double amax) {
    double g = 9.81;
    return (m1 * g * (L / 2.0)) +
        (mp * g * L) +
        (m1 * 0.25 * L * L * amax) +
        (mp * L * L * amax);
}

double calcInertia_Rectangle(double b, double h) {
    return (b * pow(h, 3)) / 12.0;
}

double calcInertia_Circle(double r) {
    return 0.25 * M_PI * pow(r, 4);
}

double calcStress_Rectangle(double M, double h, double I) {
    return (M * h) / (2.0 * I);
}

double calcStress_Circle(double M, double r, double I) {
    return (M * r) / I;
}

// Optimization Rectangle
void optRectangle(double& b, double& h, double density, double mp, double L, double amax, double yieldStrength_MPa, double& finalMass) {

    if (b <= 0 || h <= 0) {
        b = 0.01;
        h = 0.01;
    }

    int maxIterations = 10000;

    for (int i = 0; i < maxIterations; i++) {
        double m1 = calcLinkMass_Rectangle(density, b, h, L);
        double M = calcBendingMoment(m1, mp, L, amax);
        double I = calcInertia_Rectangle(b, h);

        double stress = calcStress_Rectangle(M, h, I) / 1e6;

        if (stress > yieldStrength_MPa) {
            b *= 1.01;
            h *= 1.01;
        }
        else if (stress < yieldStrength_MPa * 0.9) {
            b *= 0.99;
            h *= 0.99;
        }
        else {
            finalMass = m1;
            cout << "\nOptimized Rectangle: b = " << b
                << " m, h = " << h << " m\n";
            cout << "Stress = " << stress << " MPa\n";
            cout << "Mass = " << m1 << " kg\n";
            return;
        }
    }

    cout << "Optimization failed.\n";
}

// Optimization Circle
void optCircle(double& r,
    double density, double mp, double L,
    double amax, double yieldStrength_MPa,
    double& finalMass) {

    if (r <= 0) r = 0.01;

    int maxIterations = 10000;

    for (int i = 0; i < maxIterations; i++) {
        double m1 = calcLinkMass_Circle(density, r, L);
        double M = calcBendingMoment(m1, mp, L, amax);
        double I = calcInertia_Circle(r);

        double stress = calcStress_Circle(M, r, I) / 1e6;

        if (stress > yieldStrength_MPa) {
            r *= 1.01;
        }
        else if (stress < yieldStrength_MPa * 0.9) {
            r *= 0.99;
        }
        else {
            finalMass = m1;
            cout << "\nOptimized Circle: r = " << r << " m\n";
            cout << "Stress = " << stress << " MPa\n";
            cout << "Mass = " << m1 << " kg\n";
            return;
        }
    }

    cout << "Optimization failed.\n";
}