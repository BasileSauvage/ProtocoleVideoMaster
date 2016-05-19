#ifndef DEFINE_H
#define DEFINE_H

///
/// \file define.h
/// \brief Enumeration pour le déroulement du protocole et grandeurs globales pour le dimensionnement de l'interface.
/// \author Pierre Lespingal
///

///
/// \enum State
/// \brief Enumeration state
///
/// Enumeration permettant de se reperer dans les différentes phases du protocole.
///
enum State
{
    Training, Test, End
};

//#define NB_TEST 100 ///< Nombre de comparaison maximum lors d'un test
//#define LAYOUT_HEIGHT 900 ///< Hauteur de l'espace de travail en temps normal
//#define LAYOUT_VIDEOS_HEIGHT 600 ///< Hauteur de l'espace d'affichage des vidéos en temps normal
//#define LAYOUT_VIDEOS_HEIGHT_T 800 ///< Hauteur de l'espace d'affichage des vidéos pendant la phase d'entraînement
//#define LAYOUT_WIDTH 1066 ///< Largeur de l'espace de travail en temps normal
//#define LAYOUT_VIDEOS_WIDTH 800 ///< Largeur de l'espace d'affichage des vidéos en temps normal
//#define LAYOUT_VIDEOS_WIDTH_T 1066 ///< Largeur de l'espace d'affichage des vidéos pendant la phase d'entraînement
//#define LAYOUT_SPACE 20 ///< espacement horizontal entre deux objets
//#define LAYOUT_LABEL 30 ///< Taille occupé par la mention référence
//#define LAYOUT_V_SPACE 0 ///< espacement vertical entre deux objets
//#define LAYOUT_R LAYOUT_VIDEOS_HEIGHT/LAYOUT_VIDEOS_WIDTH ///< Resolution de l'espace vidéo en temps normal
//#define LAYOUT_R_T LAYOUT_VIDEOS_HEIGHT_T/LAYOUT_VIDEOS_WIDTH_T ///< Resolution de l'espace vidéo pendant la pahse d'entraînement

#define NB_TEST 100 ///< Nombre de comparaison maximum lors d'un test
#define LAYOUT_HEIGHT 1050 ///< Hauteur de l'espace de travail en temps normal
#define LAYOUT_VIDEOS_HEIGHT 720 ///< Hauteur de l'espace d'affichage des vidéos en temps normal [EDIT BASILE: phase d'entrainement]
#define LAYOUT_VIDEOS_HEIGHT_T 900 ///< Hauteur de l'espace d'affichage des vidéos pendant la phase d'entraînement [EDIT BASILE: phase de test]
#define LAYOUT_WIDTH 1200 ///< Largeur de l'espace de travail en temps normal
#define LAYOUT_VIDEOS_WIDTH 1200 ///< Largeur de l'espace d'affichage des vidéos en temps normal [EDIT BASILE: phase d'entrainement]
#define LAYOUT_VIDEOS_WIDTH_T 1200 ///< Largeur de l'espace d'affichage des vidéos pendant la phase d'entraînement [EDIT: phase de test]
#define LAYOUT_SPACE 20 ///< espacement horizontal entre deux objets
#define LAYOUT_LABEL 30 ///< Taille occupé par la mention référence
#define LAYOUT_V_SPACE 0 ///< espacement vertical entre deux objets
#define LAYOUT_R LAYOUT_VIDEOS_HEIGHT/LAYOUT_VIDEOS_WIDTH ///< Resolution de l'espace vidéo en temps normal
#define LAYOUT_R_T LAYOUT_VIDEOS_HEIGHT_T/LAYOUT_VIDEOS_WIDTH_T ///< Resolution de l'espace vidéo pendant la pahse d'entraînement

#endif // DEFINE_H
