//
// Created by evgen on 28.06.2021.
//

#ifndef E_CALCULATION_H
#define E_CALCULATION_H
#include "some_structs.h"
#include <cmath>
const double c[5] {0, 0, 1.0 / 2, 1.0 / 2, 1};
const double TIMESTEP = 0.005;

namespace Calculation {
    double Fx(double x, double y, double vx, double vy, const Con &cnst) {
        return (cnst.l + x) * vy * vy - cnst.k * x / cnst.m + cnst.g * cos(y);
    }

    double Fy(double x, double y, double vx, double vy, const Con &cnst) {
        return -(cnst.m * cnst.g * sin(y) + 2 * vx * vy) / (cnst.l + x);
    }

    PhaseSpace next_step(PhaseSpace &previous_step, PhaseSpace *k, Con &cnst) {
        for (int j = 1; j < 5; j++) {
            k[j].x = previous_step.vx + k[j - 1].vx * TIMESTEP * c[j];
            k[j].vx = Fx(previous_step.x + k[j - 1].x * TIMESTEP * c[j], previous_step.y + k[j - 1].y * TIMESTEP * c[j],
                         previous_step.vx + k[j - 1].vx * TIMESTEP * c[j],
                         previous_step.vy + k[j - 1].vy * TIMESTEP * c[j], cnst);
            k[j].y = previous_step.vy + k[j - 1].vy * TIMESTEP * c[j];
            k[j].vy = Fy(previous_step.x + k[j - 1].x * TIMESTEP * c[j], previous_step.y + k[j - 1].y * TIMESTEP * c[j],
                         previous_step.vx + k[j - 1].vx * TIMESTEP * c[j],
                         previous_step.vy + k[j - 1].vy * TIMESTEP * c[j], cnst);
        }
        return {previous_step.x + (k[1].x + 2 * k[2].x + 2 * k[3].x + k[4].x) * TIMESTEP / 6,
                previous_step.y + (k[1].y + 2 * k[2].y + 2 * k[3].y + k[4].y) * TIMESTEP / 6,
                previous_step.vx + (k[1].vx + 2 * k[2].vx + 2 * k[3].vx + k[4].vx) * TIMESTEP / 6,
                previous_step.vy + (k[1].vy + 2 * k[2].vy + 2 * k[3].vy + k[4].vy) * TIMESTEP / 6};
    }
}

#endif //E_CALCULATION_H
