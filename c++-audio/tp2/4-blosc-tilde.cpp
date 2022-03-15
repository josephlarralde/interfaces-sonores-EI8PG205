#include "m_pd.h"
#include "Oscillators.h"

/*
  Ce code est très similaire à celui de l'exercice précédent, mais il utilise
  la classe WaveTableOscillator au lieu de la classe SineOscillator, définie
  dans le même fichier que cette dernière.
  La classe WaveTableOscillator est issue de l'exercice 7 du TP précédent.

  Exercice :

  - Étudiez le code de cet external

  - Compilez-le et installez-le avec "make install" après avoir décommenté la
    ligne le concernant dans le makefile, puis testez-le grâce au
    patch 4-blosc-tilde.pd

  - Complétez le code de la méthode blosc_set_shape, sachant que la comparaison
    d'un t_symbol* s se fait de la manière suivante :
    if (s == gensym("un_symbole")) { ... }

  - Compilez et testez à nouveau l'external

  - Complétez le code de la méthode blosc_set_nb_harmonics afin de permettre le
    contrôle du nombre d'harmoniques calculées dans la table d'onde, en
    modifiant éventuellement la classe WaveTableOscillator ou en ajoutant des
    variables au data space de l'external

  - Compilez et testez à nouveau l'external

  - Quelles critiques pourrait-on faire à l'implémentation actuelle ?
    Quelles améliorations pourraient être apportées ?
*/

static t_class* blosc_class;

typedef struct _blosc {
  t_object x_obj;

  WaveTableOscillator* wavetable;

  t_float x_f;
  t_outlet* x_out;

} t_blosc;

void blosc_set_shape(t_blosc* x, t_symbol* s) {
  post("the \"shape\" message is not implemented yet");
  // TODO ...
}

void blosc_set_nb_harmonics(t_blosc* x, t_floatarg f) {
  post("the \"harmonics\" message is not implemented yet");
  // TODO ...
}

//------------------------------------------------------------------------------
t_int* blosc_perform(t_int* w) {
  t_blosc* x    = (t_blosc*)  (w[1]);
  t_sample* in  = (t_sample*) (w[2]);
  t_sample* out = (t_sample*) (w[3]);
  int n         = (int)       (w[4]);

  while (n--) {
    *out++ = x->wavetable->update(*in++);
  }

  return w + 5;
}

void blosc_dsp(t_blosc* x, t_signal** sp) {
  x->wavetable->setSampleRate(sys_getsr());
  dsp_add(blosc_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

//------------------------------------------------------------------------------
void blosc_free(t_blosc* x) {
  delete x->wavetable;
  outlet_free(x->x_out);
}

void* blosc_new(t_symbol* s, int argc, t_atom* argv) {
  t_blosc* x = (t_blosc*) pd_new(blosc_class);

  if (argc > 0) x->x_f = atom_getfloat(argv);

  x->wavetable = new WaveTableOscillator();
  x->wavetable->setSampleRate(sys_getsr());
  x->x_out = outlet_new(&x->x_obj, &s_signal);

  return (void*) x;
}

//------------------------------------------------------------------------------
extern "C" {

void blosc_tilde_setup() {
  blosc_class = class_new(
    gensym("blosc~"),
    (t_newmethod) blosc_new,
    (t_method) blosc_free,
    sizeof(t_blosc),
    CLASS_DEFAULT,
    A_GIMME,
    0
  );

  class_addmethod(blosc_class, (t_method) blosc_dsp, gensym("dsp"), A_CANT, 0);
  class_addmethod(blosc_class, (t_method) blosc_set_shape, gensym("shape"), A_DEFSYMBOL, 0);
  class_addmethod(blosc_class, (t_method) blosc_set_nb_harmonics, gensym("harmonics"), A_DEFFLOAT, 0);

  CLASS_MAINSIGNALIN(blosc_class, t_blosc, x_f);
}

} /* extern "C" */
//------------------------------------------------------------------------------
