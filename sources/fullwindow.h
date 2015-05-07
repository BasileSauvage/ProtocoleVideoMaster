#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#define WIDGET_WIDTH 1000
#define WIDGET_HEIGHT 600

///
/// \file fullwindow.h
/// \brief Fenêtre plein écran
/// \author Pierre Lespingal
///

#include "define.h"
#include <QWidget>
#include <QMainWindow>
#include "centralwidget.h"

/// \class FullWindow
/// \brief La classe FullWindow
///
/// Gère l'affichage en plein écran, pour adapter l'interface de test à l'écran.
///
class FullWindow : public QMainWindow
{
    Q_OBJECT
public:
    ///
    /// \brief Constructeur FullWindow
    ///
    /// Constructeur de la classe FullWindow.
    ///
    /// \param parent : widget parent
    ///
    FullWindow();

    ///
    /// \brief Destructeur FullWindow
    ///
    /// Destructeur de la classe FullWindow.
    ///
    virtual ~FullWindow();

    ///
    /// \brief Récuperation d'un evenement clavier.
    /// \param event : La touche sur laquelle l'utilisateur appuie.
    ///
    /// Reimplementation de la fonction keyPressEvent pour quitter le test si l'utilisateur appuie sur echap. A desactiver ultérieurement ?
    ///
    void keyPressEvent(QKeyEvent* event);

    ///
    /// \brief Detection et gestion d'un redimensionnement.
    ///
    /// Reimplementation de la fonction resizeEvent pour réadapter l'interface en cas de redimensionnement de l'écran.
    ///
    void resizeEvent();

private:
    QWidget* m_mainWidget; ///< Widget principal, qui englobe tout l'écran.
    QGridLayout* m_layout; ///< Layout generale, pour afficher le widget central dans la fenêtre plein écran.
    CentralWidget* m_centralWidget; ///< Widget central, dont les coordonnées et la taille sont fixe.
};

#endif // FULLWINDOW_H
