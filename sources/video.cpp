#include "video.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <QMessageBox>
#include <QDir>
#include <sstream>
#include <iostream>

///
/// \file video.cpp
/// \brief méthodes de la classe Video
///
/// Gestion d'un flux vidéo
/// \author Pierre Lespingal
///

Video::Video(QWidget *parent) :
    QWidget(parent)
{
    //Creation du layout de base
    m_layout = new QGridLayout;
    setLayout(m_layout);

    //Creation du label affichant les frames de la video
    m_label = new QLabel;
    m_label->setScaledContents(false);//la video s'adapte à l'écran
    m_layout->addWidget(m_label);

    m_capture = NULL;
    m_image = NULL;
}

Video::~Video()
{
    delete(m_image);
    //cvReleaseCapture( &m_capture );
    delete(m_label);
    delete(m_layout);
}

double Video::setVideo(const std::string path)
{
    //if(m_capture) //Remise à zero de la capture si besoin
    //cvReleaseCapture( &m_capture );


    //Chargement de la capture
    //m_capture = cvCaptureFromFile(path);

    /*std::ostringstream oss;
    double f = cvGetCaptureProperty( m_capture, CV_CAP_PROP_FRAME_COUNT);
    oss << f;
    QMessageBox::information(0, "error", QString::fromStdString(oss.str()));*/
    //Recuperation des grandeurs de la vidéo
    //double h = cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_HEIGHT);
    //double w = cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_WIDTH);

    //QMessageBox::information(0, "error", QString::fromStdString(path));
    //if (path.compare("videos/Sphere_Interpolated_Original_compresse.avi") == 0)
    //QMessageBox::information(0, "error", "ok");

//    if(!m_cap.open("videos/0-Gong_28k.avi")) //Si echec, -1, sinon resolution
	if(!m_cap.open(path)) //Si echec, -1, sinon resolution
		return -1;
    else
    {double h = m_cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        double w = m_cap.get(CV_CAP_PROP_FRAME_WIDTH);
        return h/w;
    }
}

int Video::nextFrame()
{
    //recuperation de la frame suivante
    //m_image = cvQueryFrame(m_capture);

    if(m_cap.read(m_im))//si l'image est bien recuperée
    {
        //affichage
        //m_label->setPixmap(QPixmap::fromImage(Ipl2QImage(m_im)));
        m_label->setPixmap(QPixmap::fromImage(Mat2QImage(m_im)));
        return 0;
    }
    else
        return -1;

}


QImage Video::Ipl2QImage(const IplImage *newImage)//Fonction de conversion d'une IplImage vers une QImage
{
    QImage qtemp;
    if (newImage && cvGetSize(newImage).width > 0)
    {
        int x;
        int y;
        char* data = newImage->imageData;

        qtemp= QImage(newImage->width, newImage->height,QImage::Format_RGB32 );
        for( y = 0; y < newImage->height; y++, data +=newImage->widthStep )
            for( x = 0; x < newImage->width; x++)
            {
                uint *p = (uint*)qtemp.scanLine (y) + x;
                *p = qRgb(data[x * newImage->nChannels+2],
                          data[x * newImage->nChannels+1],data[x * newImage->nChannels]);
            }
    }
    return qtemp;
}

QImage Video::Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}
