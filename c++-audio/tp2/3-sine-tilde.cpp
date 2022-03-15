#include "m_pd.h"
#include "Oscillators.h"

/*
  Ce code décrit un external générant à sa sortie un signal sinusoidal, dont la
  fréquence varie en fonction des valeurs du signal d'entrée (en Hz)

  Notez l'utilisation de l'appel à la fonction sys_getsr() permettant d'obtenir
  la fréquence d'échantillonnage courante de Pure Data, nécessaire au calcul des
  échantillons de sortie

  Notez également que l'on utilise la classe SineOscillator définie dans le
  fichier c++-audio/dep/InterfacesSonores/Oscillators.h, issue de l'exercice 3
  du TP précédent.

  Exercice :

  - Étudiez le code de cet external

  - Après avoir décommenté la ligne :
    # sine~.class.sources = 3-sine-tilde.cpp
    dans le Makefile, compilez-le et installez-le grâce à la commande
    "make install"
  
  - Ouvrez le fichier Pure Data 3-sine-tilde.pd pour observer son
    fonctionnement
*/

static t_class* sine_class;

typedef struct _sine {
  t_object x_obj;

  SineOscillator* sine;

  t_float x_f;
  t_outlet* x_out;

} t_sine;

//------------------------------------------------------------------------------
t_int* sine_perform(t_int* w) {
  t_sine* x     = (t_sine*)   (w[1]);
  t_sample* in  = (t_sample*) (w[2]);
  t_sample* out = (t_sample*) (w[3]);
  int n         = (int)       (w[4]);

  while (n--) {
    *out++ = x->sine->update(*in++);
  }

  return w + 5;
}

void sine_dsp(t_sine* x, t_signal** sp) {
  x->sine->setSampleRate(sys_getsr());
  dsp_add(sine_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

//------------------------------------------------------------------------------
void sine_free(t_sine* x) {
  delete x->sine;
  outlet_free(x->x_out);
}

void* sine_new(t_symbol *s, int argc, t_atom *argv) {
  t_sine* x = (t_sine*) pd_new(sine_class);

  // si on a un argument, on le parse comme un t_float qui représentera
  // la fréquence par défaut
  if (argc > 0) x->x_f = atom_getfloat(argv);

  x->sine = new SineOscillator();
  x->sine->setSampleRate(sys_getsr());
  x->didPost = false;
  x->x_out = outlet_new(&x->x_obj, &s_signal);
  
  return (void*) x;
}

//------------------------------------------------------------------------------
extern "C" {

void sine_tilde_setup() {
  sine_class = class_new(
    gensym("sine~"),
    (t_newmethod) sine_new,
    (t_method) sine_free,
    sizeof(t_sine),
    CLASS_DEFAULT,
    A_GIMME,
    0
  );

  class_addmethod(sine_class, (t_method) sine_dsp, gensym("dsp"), A_CANT, 0);
  CLASS_MAINSIGNALIN(sine_class, t_sine, x_f);
}

} /* extern "C" */
//------------------------------------------------------------------------------
