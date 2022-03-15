#include "m_pd.h"

/*
  Exercice :
  
  - Étudiez le code de cet external

  - Compilez-le et installez-le grâce à la commande "make install"
  
  - Ouvrez le fichier Pure Data 1-helloworld.pd pour observer son fonctionnement
*/

static t_class* helloworld_class;

typedef struct _helloworld {
  t_object x_obj;
} t_helloworld;

void helloworld_bang(t_helloworld* x) {
  // post fonctionne de manière similaire à printf et affiche des chaîne de
  // caractères formatées dans la console de Pure Data
  post("Hello, World !");
}

void* helloworld_new() {
  t_helloworld* x = (t_helloworld*) pd_new(helloworld_class);
  return (void*) x;
}

//------------------------------------------------------------------------------
// on évite le name mangling
extern "C" {
// pour un objet nommé <name>, le nom de la fonction d'initialisation doit être
//exactement <name>_setup
void helloworld_setup() {
  helloworld_class = class_new(
    gensym("helloworld"),         // nom de l'objet
    (t_newmethod) helloworld_new, // méthode "new"
    0,                            // méthode "free"(pas nécessaire ici)
    sizeof(t_helloworld),         // taille du data space
    CLASS_DEFAULT,                // flags (ici, objet "normal")
    A_GIMME,                      // type du premier argument (A_GIMME délègue le parsing à la fonction new)
    // ...,                       // types des arguments suivants si A_GIMME n'est pas utilisé
    0                             // 0 signifie "fin des arguments"
  );

  // une fois la classe créée, on lui attache des méthodes
  class_addbang(helloworld_class, helloworld_bang);
}
} /* extern "C" */
//------------------------------------------------------------------------------
