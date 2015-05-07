#ifndef MENU_H
#define MENU_H

///
/// \file menu.h
/// \brief Menu de base
/// \author Pierre Lespingal
///

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "fullwindow.h"


///
/// \class Menu
/// \brief La classe Menu
///
/// La classe gère l'affichage du menu et l'accés au test.
///
class Menu : public QMainWindow
{
    Q_OBJECT
public:
    ///
    /// \brief Constructeur Menu
    ///
    /// Constructeur de la classe Menu
    ///
    /// \param parent : widget parent
    ///
    Menu(QWidget *parent = 0);

    ///
    /// \brief Destructeur Menu
    ///
    /// Destructeur de la classe Menu
    ///
    virtual ~Menu();

signals:

public slots:
    ///
    /// \brief Lancement du test.
    ///
    /// Instancie la classe FullWindow, pour placer l'utilisateur dans les conditions du test.
    ///
    void startTest();

private:


    QWidget* m_widget; ///< widget central
    QGridLayout* m_layout; ///< layout central
    QLabel* m_label; ///< text descriptif
    QPushButton* m_startButton; ///< boutton de lancement
    FullWindow* m_fullWindow; ///< classe d'affichage en plein écran pour le test
};

#endif // MENU_H
