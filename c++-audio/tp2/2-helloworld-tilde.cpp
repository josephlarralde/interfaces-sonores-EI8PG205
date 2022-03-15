#include <cmath>
#include "m_pd.h"

/*
  Exercice :
  
  - Étudiez le code de cet external

  - Après avoir décommenté la ligne :
    # helloworld~.class.sources = 2-helloworld-tilde.cpp
    dans le Makefile, compilez-le et installez-le grâce à la commande
    "make install"
  
  - Ouvrez le fichier Pure Data 2-helloworld-tilde.pd pour observer son
    fonctionnement
*/

static t_class* helloworld_class;

typedef struct _helloworld {
  t_object x_obj;
  t_float x_f; // placeholder pour la valeur courante de signal de l'entrée par défaut
  t_outlet* x_out;
} t_helloworld;

//------------------------------------------------------------------------------
t_int* helloworld_perform(t_int* w) {
  t_helloworld* x = (t_helloworld*) (w[1]);
  t_sample* in    = (t_sample*)     (w[2]);
  t_sample* out   = (t_sample*)     (w[3]);
  int n           = (int)           (w[4]);

  // on transmet simplement les échantillons de l'entrée vers la sortie
  while (n--) *out++ = *in++;

  return w + 5;
}

void helloworld_dsp(t_helloworld* x, t_signal** sp) {
  dsp_add(helloworld_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

//------------------------------------------------------------------------------
void helloworld_free(t_helloworld* x) {
  outlet_free(x->x_out);
}

void* helloworld_new(t_symbol *s, int argc, t_atom *argv) {
  t_helloworld* x = (t_helloworld*) pd_new(helloworld_class);
  x->x_out = outlet_new(&x->x_obj, &s_signal);
  post("Hello, World~ !");
  return (void*) x;
}

//------------------------------------------------------------------------------
extern "C" {
// pour un objet manipulant du signal nommé <name>~, le nom de la fonction
// d'initialisation doit être exactement <name>_tilde_setup
void helloworld_tilde_setup() {
  helloworld_class = class_new(
    gensym("helloworld~"),
    (t_newmethod) helloworld_new,
    (t_method) helloworld_free,
    sizeof(t_helloworld),
    CLASS_DEFAULT,
    A_GIMME,
    0
  );

  class_addmethod(helloworld_class, (t_method) helloworld_dsp, gensym("dsp"), A_CANT, 0);

  // cette macro définit l'entrée principale comme pouvant recevoir du signal,
  // et déclare x_f comme étant la variable à utiliser comme valeur courante
  // de signal d'entrée si aucun signal n'est connecté à celle-ci
  CLASS_MAINSIGNALIN(helloworld_class, t_helloworld, x_f);
}

} /* extern "C" */
//------------------------------------------------------------------------------
