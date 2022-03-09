//------------------------------------------------------------------------------
float interpolateLinear(float* buf, unsigned int index, float frac) {
  float* p = buf + index;

  return (1. - frac) * (*p) + frac * (*(p + 1));
}


//------------------------------------------------------------------------------
float interpolateCubic(float *buf, unsigned int size,
                       unsigned int index, float frac,
                       bool cyclic = true) {
  float* p = buf + index;
  float a, b, c, d, cminusb;

  // if cyclic, wrap around buffer values, otherwise zero-pad

  a = (index <= 0)
    ? (cyclic ? *(buf + size + index - 1) : 0)
    : *(p - 1);

  b = *(p);

  c = (index > size - 2)
    ? (cyclic ? *(buf + index - size + 1) : 0)
    : *(p + 1);

  d = (index > size - 3)
    ? (cyclic ? *(buf + index - size + 2) : 0)
    : *(p + 2);

  cminusb = c - b;

  return b + frac * (
    cminusb - 0.1666667f * (1. - frac) *
    ((d - a - 3.0f * cminusb) * frac + (d + 2.0f * a - 3.0f * b))
  );
}
