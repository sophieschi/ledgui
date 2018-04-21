#ifndef QTMOSQUITTO_DEMO_WINDOW_HPP
#define QTMOSQUITTO_DEMO_WINDOW_HPP

#include <QtWidgets>
#include <QSignalMapper>
#include <QColor>
#include <QSlider>
#include <qtmosquitto.hpp>
#include <QJsonDocument>
#include <QColorDialog>

class Window : public QWidget
{
	Q_OBJECT
	public:
    	Window(QWidget* parent = 0);
		virtual ~Window();
		void doConnect();
    	void doPublish(QString);
		void setColor( const QColor& color );
	    const QColor& getColor();
  
	private slots:
		void composeMessage(QString);
		void updateColor();
		void changeColor();
		void setIterations();

	private:
		QPushButton *buttons[7];
		QPushButton *selectColorButton;
		QSlider *slider; 
    	QtMosquittoClient *mClient;
		QColor color;
		int iterations=1;
		QString message;
};

#endif
