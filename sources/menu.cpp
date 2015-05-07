#include "menu.h"

///
/// \file menu.cpp
/// \brief méthodes de la classe Menu
///
/// Gestion du menu de base
/// \author Pierre Lespingal
///

Menu::Menu(QWidget *parent) :
    QMainWindow(parent)
{
    //La taille minimum est fixé
    setMinimumSize(300, 400);

    //Creation du widget central
    m_widget = new QWidget(this);
    setCentralWidget(m_widget);

    //Creation du layout sur le widget central
    m_layout = new QGridLayout(this);
    m_widget->setLayout(m_layout);

    //Creation et placement du texte descriptif
    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setText("<html><h1>Protocole de test subjectif : </h1> <h3> Comparaison visuel d'objet 3D </h3> <div> Vous disposerez d'une phase d'entrainement pour vous familiariser avec votre tache ainsi que l'interface. </div> </html>");
    m_layout->addWidget(m_label, 0, 0);

    //Creation et placement du boutton de lancement de test
    m_startButton = new QPushButton("Commencer le test ( Passage en plein écran )", this);
    m_layout->addWidget(m_startButton, 1, 0);

    //Connection du boutton au lancement du test
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startTest()));
}

Menu::~Menu()
{
    delete(m_startButton);
    delete(m_label);
    delete(m_layout);
    delete(m_widget);
    if(!m_fullWindow)
        delete(m_fullWindow);
}

void Menu::startTest()
{
    //Creation et affichage de l'environnement de test
    m_fullWindow = new FullWindow;
    m_fullWindow->show();
}
