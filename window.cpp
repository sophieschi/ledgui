#include "window.hpp"

Window::Window(QWidget* par) :
	QWidget(par),
	mClient(new QtMosquittoClient(QString(), true, this))
{
	setWindowTitle(tr("LED Control"));
	resize(200, 400);

	mClient->setAutoReconnect(true);

	QSignalMapper *signalMapper = new QSignalMapper(this);

//Buttons
	QString names[9];
	names[0] = "color";
	names[1] = "wipe";
	names[2] = "round";
	names[3] = "chase";
	names[4] = "strobe";
	names[5] = "pulse";
	names[6] = "rand";
	names[7] = "gauge";
	names[8] = "off";

	QVBoxLayout *layout = new QVBoxLayout();

	for(int i = 0; i < 9; i++)
	{
		buttons[i] = new QPushButton(names[i]);
		buttons[i]->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

		layout->addWidget(buttons[i]);
		connect(buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(buttons[i], names[i]);
	}
	connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(composeMessage(QString)));

	selectColorButton = new QPushButton("select color");
	layout->addWidget(selectColorButton);
	connect(selectColorButton, SIGNAL(clicked()), this, SLOT(changeColor()) );

	slider = new QSlider(Qt::Horizontal);
	slider->setMinimum(1);
	slider->setMaximum(100);
	slider->setValue(10);
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setIterations()) );
	layout->addWidget(slider);

	setLayout(layout);

}

Window::~Window()
{
}


void Window::setIterations()
{
	iterations = slider->value();
}

void Window::updateColor()
{
	selectColorButton->setStyleSheet( "background-color: " + color.name() );
}

void Window::changeColor()
{
	QColor newColor = QColorDialog::getColor(color, parentWidget());
	if ( newColor != color )
	{
		setColor( newColor );
	}
}

void Window::setColor( const QColor& color )
{
	this->color = color;
	updateColor();
}

const QColor& Window::getColor()
{
	return color;
}

void Window::doConnect()
{
	const QString server = "172.16.30.42";
	const QString uname = "rpi1";
	const QString pword = "reallysecure";
	mClient->setUsernamePassword(uname, pword);
	mClient->doConnect(server);
}

void Window::composeMessage(QString type)
{
	QJsonObject obj;
	obj["type"]=type;
	obj["r"]=color.red();
	obj["g"]=color.green();
	obj["b"]=color.blue();
	obj["iterations"]=iterations;
	
	doPublish(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

void Window::doPublish(QString json)
{
	const QString topic = "signal/led";
	
	if (mClient->publish(topic, json) < 0)
	{
		QMessageBox::warning(this, tr("Publish"), tr("Publish failed"));
	}
}
