//
//  Envelope.cpp
//
//  Created by Nigel Redmon on 12/18/12.
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the adsr envelope generator and code,
//  read the series of articles by the author, starting here:
//  http://www.earlevel.com/main/2013/06/01/envelope-generators/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your own purposes, free or commercial.
//
//  1.01  2016-01-02  njr   added calcCoef to SetTargetRatio functions that were in the adsr widget but missing in this code
//  1.02  2017-01-04  njr   in calcCoef, checked for rate 0, to support non-IEEE compliant compilers
//

#include "Envelope.h"
#include <cmath>

Envelope::Envelope() {
    reset();
    setAttackRate(0.0f);
    setDecayRate(0.0f);
    setReleaseRate(0.0f);
    setSustainLevel(1.0f);
    setTargetRatioA(0.3f);
    setTargetRatioDR(0.0001f);
}

Envelope::~Envelope() = default;

void Envelope::setAttackRate(float rate) {
    attackRate = rate;
    attackCoef = calcCoef(rate, targetRatioA);
    attackBase = (1.0f + targetRatioA) * (1.0f - attackCoef);
}

void Envelope::setDecayRate(float rate) {
    decayRate = rate;
    decayCoef = calcCoef(rate, targetRatioDR);
    decayBase = (sustainLevel - targetRatioDR) * (1.0f - decayCoef);
}

void Envelope::setReleaseRate(float rate) {
    releaseRate = rate;
    releaseCoef = calcCoef(rate, targetRatioDR);
    releaseBase = -targetRatioDR * (1.0f - releaseCoef);
}

float Envelope::calcCoef(float rate, float targetRatio) const {
    return (rate <= 0) ? 0.0f : float(exp(-log((1.0 + targetRatio) / targetRatio) / rate));
}

void Envelope::setSustainLevel(float level) {
    sustainLevel = level;
    decayBase = (sustainLevel - targetRatioDR) * (1.0f - decayCoef);
}

void Envelope::setTargetRatioA(float targetRatio) {
    if (targetRatio < 0.000000001f) {
        targetRatio = 0.000000001f; // -180 dB
    }
    targetRatioA = targetRatio;
    attackCoef = calcCoef(attackRate, targetRatioA);
    attackBase = (1.0f + targetRatioA) * (1.0f - attackCoef);
}

void Envelope::setTargetRatioDR(float targetRatio) {
    if (targetRatio < 0.000000001f) {
        targetRatio = 0.000000001f; // -180 dB
    }
    targetRatioDR = targetRatio;
    decayCoef = calcCoef(decayRate, targetRatioDR);
    releaseCoef = calcCoef(releaseRate, targetRatioDR);
    decayBase = (sustainLevel - targetRatioDR) * (1.0f - decayCoef);
    releaseBase = -targetRatioDR * (1.0f - releaseCoef);
}