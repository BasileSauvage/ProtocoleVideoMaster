#include "centralwidget.h"
#include <QApplication>
#include <QDesktopWidget>

///
/// \file centralwidget.cpp
/// \brief méthodes de la classe CentralWidget
///
/// Gestion du déroulement du test, gestion de l'interface utilisateur
/// \author Pierre Lespingal
///

using namespace std;


CentralWidget::CentralWidget(QWidget *parent)
{
    //Creation et dimensionnement du layout
    m_layout = new QGridLayout;
    setLayout(m_layout);
    m_layout->setVerticalSpacing(0);
    m_layout->setHorizontalSpacing(LAYOUT_SPACE);

    //Mapping des boutons, pour appeler la même méthode avec des arguments différents
    m_signalMapperChoice = new QSignalMapper(this);
    connect(m_signalMapperChoice, SIGNAL(mapped(int)), this, SLOT(saveChoice(int)));

    //Creation des trois widget vidéos
    for(int i=1;i<3;i++)
    {

        QPushButton* button = new QPushButton();
        //Application du style et de la couleur
        setStyleButton(button, i);
        //Placement
        button->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 20);
        m_buttons.append(button);

        //Connection
        m_signalMapperChoice->setMapping(m_buttons[i-1], i);
        connect(m_buttons[i-1], SIGNAL(clicked()), m_signalMapperChoice, SLOT(map()));
    }

    //Creation, placement et connection des differents boutons

    m_reStartTrainingButton = new QPushButton();
    setStyleButton(m_reStartTrainingButton);
    m_reStartTrainingButton->setText("Recommencer l'entrainement");
    connect(m_reStartTrainingButton, SIGNAL(clicked()), this, SLOT(startTraining()));


    m_startTrainingButton = new QPushButton();
    setStyleButton(m_startTrainingButton);
    m_startTrainingButton->setText("Commencer l'entrainement");
    connect(m_startTrainingButton, SIGNAL(clicked()), this, SLOT(nextTest()));


    m_nextButton = new QPushButton();
    setStyleButton(m_nextButton);
    m_nextButton->setText("Comparaison suivante");
    connect(m_nextButton, SIGNAL(clicked()), this, SLOT(nextTest()));


    m_startButton = new QPushButton();
    setStyleButton(m_startButton);
    m_startButton->setText("Passer au test reel");
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startTest()));

    m_startTestButton = new QPushButton();
    setStyleButton(m_startTestButton);
    m_startTestButton->setText("Commencer le test");
    connect(m_startTestButton, SIGNAL(clicked()), this, SLOT(nextTest()));


    m_quitButton = new QPushButton();
    setStyleButton(m_quitButton);
    m_quitButton->setText("Quitter");
    connect(m_quitButton, SIGNAL(clicked()), parent, SLOT(close()));



    //Creation, placement et mise en forme du label d'information
    m_info = new QLabel;
    m_info->setMinimumSize(LAYOUT_WIDTH, 15);
    m_info->setAlignment(Qt::AlignCenter);
    m_info->setStyleSheet("color: white;font-size: 20px");

    //Creation et lancement du timer de temps de comparaison
    m_compareTimer = new QTimer(this);
    m_compareTimer->setSingleShot(true);
    connect(m_compareTimer, SIGNAL(timeout()), this, SLOT(endLoop()));


    //Creation du timer permettant de récuperer les temps de réponse
    m_time = new QTime;

    //Creation et placement de l'espace video
    m_videosWidget = new VideosWidget(this,LAYOUT_VIDEOS_WIDTH, LAYOUT_VIDEOS_HEIGHT);


    //Lancement de la phase d'entrainement
    m_state = Training;
    startTraining();
}

CentralWidget::~CentralWidget()
{

    delete(m_time);

    delete(m_info);

    for(int i = 1;i< 3;i++)
        delete(m_buttons[i-1]);
    delete(m_nextButton);
    delete(m_startButton);
    delete(m_signalMapperChoice);

    m_choices.clear();
    m_buttons.clear();
    m_respondTime.clear();

    delete(m_layout);

}

void CentralWidget::endLoop()
{
    //Arrêt des videos
    m_videosWidget->stop();
    if(m_state == Training) //Affichage de texte pendant la phase d'entrainement
        m_info->setText("<html><div>30 Secondes se sont écoulées,</div><div>les vidéos s'arrêtent,</div><div>vous devez faire votre choix.</div></html>");
}


void CentralWidget::saveChoice(int choice)
{
    //Arrêt de l'affichage des boutons
    cleanButton();

    //Arrêt des vidéos et du timer
    m_videosWidget->stop();
    m_compareTimer->stop();

    //Indication sur la vidéo selectionné
    m_videosWidget->setFocus(choice);

    //Verification de la phase actuelle; entrainement ou test reel
    switch(m_state)
    {

    case Training :

        //Affichage de texte suivant le choix effectué
        if(choice == 1)
            m_info->setText("<html><div>Vous avez choisi l'objet de gauche.</div> <div> Le test se met en pause, vous pouvez reprendre lorsque vous le souhaitez.</div></html>");
        else
            m_info->setText("<html><div>Vous avez choisi l'objet de droite.</div> <div> Le test se met en pause, vous pouvez reprendre lorsque vous le souhaitez.</div></html>");

    break;

    case Test :
        //Prise en compte du choix de l'utilisateur
        m_choices.append(choice);
        //Prise en compte du temps de reponse
        m_respondTime.append(m_time->restart());

    break;

    default :

    break;
    }
    //Affichage des boutons pour la phase suivante
    m_nextButton->show();
}

void CentralWidget::nextTest()
{
    //Arrêt de l'affichage des boutons
    cleanButton();

    //Verification de la phase actuelle; entrainement ou test reel
    switch(m_state)
    {
    case Training :
        if(!m_videosWidget->loadNext())
        {
            //Fin de l'entrainement
            endTraining();
        }
        else
        {
            ////Affichage des boutons pour la phase suivante
            for(int i = 1;i<3;i++)
            {
                m_buttons[i-1]->show();
            }
            m_info->setText("<html><div>Pour choisir une vidéo, cliquez sur le bouton correspondant.</div><div>Rappelez vous la consigne, choisissez l'objet qui ressemble le plus à la vidéo de référence.</div><div><em>Au bout de 30s les videos s'arrétent, vous forcant à faire votre choix.</em></div></html>");

            //Lancement des videos et des timers
            m_videosWidget->runVideos();
            m_videosWidget->play();
            m_videosWidget->showVideos();
            m_compareTimer->start(28800);

        }
        break;
    case Test :
            if(!m_videosWidget->loadNext())
            {
                //Fin du test
                endTest();
            }
            else
            {
            ////Affichage des boutons pour la phase suivante
            for(int i = 1;i<3;i++)
            {
            m_buttons[i-1]->show();
            }

            //Lancement des videos et des timers
            m_videosWidget->runVideos();
            m_videosWidget->play();
            m_compareTimer->start(28800);
            m_videosWidget->showVideos();
            m_time->restart();
            }
        break;
    default :
        break;
    }
}

void CentralWidget::startTraining()
{
    //Arrêt de l'affichage des boutons et des vidéos
    cleanButton();
    m_videosWidget->cleanVideos();

    //Mise en place du layout

    m_info->setText("<html><h4>Phase d'entraînement</h4> <em>Aucun choix ne sera pris en compte.</em><div>Vous allez voir apparaître trois videos d'objets, Une référence</div><div>et deux versions dégradées.</div> <div>La question qui vous est posée est la suivante : lequel des deux objets latéraux ressemble le plus à la référence ? </div> <div>Dit autrement: pour lequel de ces deux objets les dégradations sont elles le moin visibles ? </div> <div><strong>Lorsque vous serez prêts, cliquez sur le bouton pour lancer les vidéos à comparer.</div></html>");
    m_layout->addWidget(m_info, 0, 0, 1, 12, Qt::AlignCenter);

    m_layout->addWidget(m_videosWidget, 1, 0, 5, 12, Qt::AlignCenter);

	m_layout->addWidget(m_buttons[0], 6, 1, 1, 4, Qt::AlignCenter);
	m_buttons[0]->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/3, 40);
	m_layout->addWidget(m_buttons[1], 6, 7, 1, 4, Qt::AlignCenter);
	m_buttons[1]->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/3, 40);


	m_reStartTrainingButton->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 30);
	m_layout->addWidget(m_reStartTrainingButton, 6, 0, 1, 6, Qt::AlignCenter);
	m_startTrainingButton->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 30);
	m_layout->addWidget(m_startTrainingButton, 3, 3, 1, 6, Qt::AlignCenter);
	m_nextButton->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 30);
	m_layout->addWidget(m_nextButton, 6, 3, 1, 6, Qt::AlignCenter);
	m_startButton->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 30);
	m_layout->addWidget(m_startButton, 6, 6, 1, 6, Qt::AlignCenter);
	m_quitButton->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 30);
	m_layout->addWidget(m_quitButton, 6, 4, 1, 4, Qt::AlignCenter);
	m_startTestButton->setFixedSize((LAYOUT_VIDEOS_WIDTH - 3*LAYOUT_SPACE)/2, 30);
	m_layout->addWidget(m_startTestButton, 3, 3, 1, 6, Qt::AlignCenter);


    m_videosWidget->resizeLayout(LAYOUT_VIDEOS_WIDTH, LAYOUT_VIDEOS_HEIGHT);

    //Creation et chargement de la séquence de test d'entrainement
    m_videosWidget->loadSequence("./sequence/training.txt");

    //Affichage des boutons pour la phase suivante
    m_startTrainingButton->show();
}

void CentralWidget::endTraining()
{
    //Arrêt de l'affichage des boutons
    cleanButton();
    //Arrêt des vidéos
    m_videosWidget->stop();

    m_info->setText("<html><div>Entraînement terminé.</div><div> Voulez vous revoir l'entraînement ou passer au test reel ?</div></html>");

    //Affichage des boutons pour la phase suivante
    m_reStartTrainingButton->show();
    m_startButton->show();
}

void CentralWidget::startTest()
{
    //Arrêt de l'affichage des boutons et des vidéos
    cleanButton();
    m_videosWidget->cleanVideos();

    //Agrandissement de l'espace vidéos pour le test reel
    m_videosWidget->resizeLayout(LAYOUT_VIDEOS_WIDTH_T, LAYOUT_VIDEOS_HEIGHT_T);

    //Creation et chargement de la séquence de test
	m_videosWidget->loadSequence("./sequence/sequence.txt");

    //Passage au test reel
    m_state = Test;

    //Supression du texte
    m_info->hide();

    //Affichage des boutons pour la phase suivante
    m_startTestButton->show();

    //Lancement du timer de boucle
    m_time->start();
}

void CentralWidget::endTest()
{
    //Arrêt de l'affichage des boutons et des vidéos
    cleanButton();
    m_videosWidget->cleanVideos();

    //Modification du layout
    m_layout->removeWidget(m_videosWidget);
    m_layout->removeWidget(m_info);
    m_layout->addWidget(m_info, 0, 0, 1, 12);

    //Message de remerciement de fin de test
    m_info->setText("<html><h3>Le test est terminé.</h3> <div> Merci de votre participation !</html>");
    m_info->show();

    //Tentative d'exportation des résultats
    if(!m_videosWidget->exportResult(m_choices, m_respondTime))
    {
        QMessageBox::information(0, "error", "Echec de l'exportation des resultats");
    }


    m_quitButton->show();
    m_state = End;
    m_videosWidget->stop();
    m_compareTimer->stop();
}

void CentralWidget::setStyleButton(QPushButton* button, int i)
{
    switch(i)
    {
    case 1:
        button->setText("L'objet de gauche\n est le plus ressemblant");
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 6px;background-color: qlineargradient(x1: 0,y1 : 0,x2: 0,y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);");
    break;
    case 2:
        button->setText("L'objet de droite \n est le plus ressemblant");
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 6px;background-color: qlineargradient(x1: 0,y1 : 0,x2: 0,y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);");
    break;
    default :
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 6px;background-color: qlineargradient(x1: 0,y1 : 0,x2: 0,y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);");
    break;
    }
}

void CentralWidget::cleanButton()
{
    for(int i =1;i<3;i++)
    {
        m_buttons[i-1]->hide();
    }
    m_nextButton->hide();
    m_startButton->hide();
    m_startTrainingButton->hide();
    m_reStartTrainingButton->hide();
    m_quitButton->hide();
    m_startTestButton->hide();
}
