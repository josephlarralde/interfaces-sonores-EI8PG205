#include <cmath>

//------------------------------------------------------------------------------
float getNextPhaseValue(float phase, float sr, float f) {
  float nextPhase = phase + f / sr;

  // keep phase between 0 and 1 :
  if (nextPhase >= 1) {
    nextPhase -= floor(nextPhase);
  } else if (nextPhase < 0) { // this occurs when f < 0
    nextPhase += floor(fabs(phase) + 1);
  }

  return nextPhase;
}

//------------------------------------------------------------------------------
enum WaveShape {
  Sine,
  Saw,
  Square,
  Triangle
};

void fillWaveTable(float* table, int size, WaveShape shape, int harmo = 15) {
  float phase = 0.f;
  float phaseInc = 1.f / size;
  float coeff;
  int i, k;

  switch (shape) {
    //--------------------------------------------------------------------------
    case WaveShape::Sine:
      for (i = 0; i < size; i++) {
        table[i] = sin(2 * M_PI * phase);
        phase += phaseInc;
      }
      break;
    //--------------------------------------------------------------------------
    case WaveShape::Saw:
      coeff = -2 / M_PI;

      for (i = 0; i < size; i++) {
        table[i] = 0;

        for (k = 1; k <= harmo; k++) {
          table[i] += (k % 2 == 0 ? 1 : -1) *
                      sin(2 * M_PI * k * phase) / k;
        }

        table[i] *= coeff;
        phase += phaseInc;
      }
      break;
    //--------------------------------------------------------------------------
    case WaveShape::Square:
      coeff = 4 / M_PI;

      for (i = 0; i < size; i++) {
        table[i] = 0;

        for (k = 1; k <= harmo; k++) {
          table[i] += sin(2 * M_PI * (2 * k - 1) * phase) / (2 * k - 1);
        }

        table[i] *= coeff;
        phase += phaseInc;
      }
      break;
    //--------------------------------------------------------------------------
    case WaveShape::Triangle:
      coeff = -8 / pow(M_PI, 2);

      for (i = 0; i < size; i++) {
        table[i] = 0;

        for (k = 1; k <= harmo; k++) {
          table[i] += (k % 2 == 0 ? 1 : -1) *
                      sin(2 * M_PI * (2 * k - 1) * phase) /
                      pow(2 * k - 1, 2);
        }

        table[i] *= coeff;
        phase += phaseInc;
      }
      break;
    //--------------------------------------------------------------------------
    default:
    break;
  }
}
