#include "fullwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

///
/// \file fullwindow.cpp
/// \brief méthodes de la classe FullWindow
///
/// Gestion du plein écran, placement de la zone d'interaction avec l'utilisateur
/// \author Pierre Lespingal
///

FullWindow::FullWindow()
{
    //Parametre du plein écran
    setWindowState(Qt::WindowFullScreen);
    setStyleSheet("background-color:rgb(0,0,0)");

    //Creation du widget principal
    m_mainWidget = new QWidget(this);
    setCentralWidget(m_mainWidget);

    //Creation du layout
    m_layout = new QGridLayout(this);
    m_mainWidget->setLayout(m_layout);

    //Creation du widget central, danc lequel se deroulera le test, dimmensionnement et placement
    m_centralWidget = new CentralWidget(this);
    m_layout->addWidget(m_centralWidget, 0, 0);
    m_centralWidget->setFixedSize(LAYOUT_WIDTH, LAYOUT_HEIGHT);
    m_centralWidget->move((QApplication::desktop()->screenGeometry().width())/2 - (LAYOUT_WIDTH)/2, (QApplication::desktop()->screenGeometry().height())/2 - (LAYOUT_HEIGHT)/2);

}

FullWindow::~FullWindow()
{ 
    delete(m_centralWidget);
    delete(m_layout);
    delete(m_mainWidget);
}

void FullWindow::keyPressEvent(QKeyEvent *event)
{
    //Fermeture de la fenetre et fin du test si la touche escape est declenché
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
}

void FullWindow::resizeEvent()
{
    //Si redimensionnement, réadaptation du widget central
    m_centralWidget->move((QApplication::desktop()->screenGeometry().width())/2 - (LAYOUT_WIDTH)/2, (QApplication::desktop()->screenGeometry().height())/2 - (LAYOUT_HEIGHT)/2);
}
