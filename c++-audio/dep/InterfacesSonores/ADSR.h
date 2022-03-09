//------------------------------------------------------------------------------
class ADSR {
private:
  float sr;
  float a, d, s, r;
  bool running;
  int n;

public:
  ADSR(float sampleRate = 44100) :
  sr(sampleRate),
  a(0.01), d(0.05), s(0.5), r(0.2),
  running(false),
  n(0) {}

  ~ADSR() {}

  void setup(float a, float d, float s, float r);
  void start();
  float getNextValue();
};

//------------------------------------------------------------------------------
void ADSR::setup(float a, float d, float s, float r) {
  this->a = a;
  this->d = d;
  this->s = s;
  this->r = r;
}

void ADSR::start() {
  running = true;
  n = 0;
}

float ADSR::getNextValue() {
  if (!running) return 0;

  float res = 0;

  if (n < (a * sr))
  {
    res = n / (a * sr);
  }
  else if (n < (a + d) * sr)
  {
    float frac = (n - (a * sr)) / (d * sr);
    res = (1 - frac) * (1 - s) + s;
  }
  else if (n < (a + d + r) * sr)
  {
    float frac = (n - ((a + d) * sr)) / (r * sr);
    res = (1 - frac) * s;
  }
  else
  {
    running = false;
  }

  n++;
  return res;
}
