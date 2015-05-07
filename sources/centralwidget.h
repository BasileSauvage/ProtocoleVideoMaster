#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

///
/// \file centralWidget.h
/// \brief Layout central
/// \author Pierre Lespingal
///

#include "define.h"
#include <QGridLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include "video.h"
#include "videoswidget.h"
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <fstream>
#include <string>
#include <QSignalMapper>
#include <QPushButton>

///
/// \class CentralWidget
/// \brief La classe CentralWidget
///
/// La classe qui commande le deroulement du protocole, l'interaction avec l'utilisateur et la récupération de ses choix.
///
class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief Constructeur CentralWidget
    ///
    /// Constructeur de la classe CentralWidget
    ///
    /// \param parent : widget parent
    ///
    CentralWidget(QWidget *parent = 0);

    ///
    /// \brief Destructeur CentralWidget
    ///
    /// Destructeur de la classe CentralWidget
    ///
    virtual ~CentralWidget();


    ///
    /// \brief Termine la phase d'entraînement
    ///
    /// Est appelé lors de l'achevement de la phase d'entraînement, prépare le lancement du test reel ou si besoin un nouvel entraînement.
    ///
    void endTraining();

    ///
    /// \brief Termine le test
    ///
    /// Est appelé à la fin du test, affiche les remerciements et ne laisse pour evenement possible que la fermeture de l'application de test.
    ///
    void endTest();

    ///
    /// \brief Applique un style predefinit à un bouton
    /// \param button : Un widget bouton
    /// \param i : Indique la video associée au bouton, 1 pour gauche, 2 pour droite, 0 si pas d'association.
    ///
    /// Modifie le style d'un bouton, ainsi que le texte adéquat lorsqu'il s'agit d'un bouton de choix de vidéo.
    ///
    void setStyleButton(QPushButton* button, int i = 0);

    ///
    /// \brief Cache tout les boutons à l'écran
    ///
    /// Tout les boutons à l'écran sont masquéq et l'utilisateur ne peut plus interagir avec eux.
    /// Les boutons necessaires à la phase suivante doivent être alors réafficher pour l'utilisateur.
    ///
    void cleanButton();



public slots:

    ///
    /// \brief Slot appelé lors de la selection d'une vidéo.
    /// \param : choix de l'utilisateur
    ///
    /// Suivant le choix de l'utilisateur, le sauvegarde et met le test en pause.
    ///
    void saveChoice(int choice);

    ///
    /// \brief Slot appelé lors du lancement par l'utilisateur des vidéos pour leur comparaison.
    ///
    /// Met en place la comparaison suivante, lance le test suivant.
    ///
    void nextTest();

    ///
    /// \brief Slot appelé par l'utilisateur pour démarrer la phase d'entraînement.
    ///
    /// Prépare l'interface et lance la phase d'entrainement.
    ///
    void startTraining();

    ///
    /// \brief Slot appelé par l'utilisateur pour démarrer le test reel.
    ///
    /// Prépare l'interface et lance la phase de test reel.
    ///
    void startTest();

    ///
    /// \brief Slot appelé par un timer pour arrêter les vidéos.
    ///
    /// Arrête la lecture des vidéos au bout du timer de 30 sec pour forcer le choix de l'utilisateur.
    ///
    void endLoop();



private:

    QGridLayout* m_layout; ///< Layout général.


    QVector<int> m_choices; ///< Tableau recupérant les choix de l'utilisateur.

    QVector<QPushButton*> m_buttons; ///< Les boutons de choix des videos
    QSignalMapper* m_signalMapperChoice; ///< Pour mapper les bouton de choix.

    VideosWidget* m_videosWidget;///< L'espace dédié au placement des vidéos.

    QTimer* m_compareTimer; ///< Timer de temps donné pour la comparaison.

    QPushButton* m_nextButton; ///< Un bouton pour passer à la comparaison suivante.
    QPushButton* m_startButton; ///< Un bouton pour passer de l'entrainement au test.
    QPushButton* m_startTrainingButton; ///< Un bouton pour commencer l'entrainement.
    QPushButton* m_reStartTrainingButton; ///< Un bouton pour recommencer l'entrainement.
    QPushButton* m_quitButton; ///< Un bouton pour quitter le protocole de test.
    QPushButton* m_startTestButton; ///< Un bouton pour commencer le test reel.

    QTime* m_time; ///< Indique le temps de réponse.
    QVector<int> m_respondTime; ///< Stocke les temps de réponse.

    int m_state; ///< Indicateur de deroulement du test.
    QLabel* m_info; ///< Label d'informations.

    QLabel* m_debug; ///< Label de debug.
};

#endif // MAINLAYOUT_H
