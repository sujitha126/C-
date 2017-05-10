/*
 * ModulationAndAudio.cpp
 *
 */
#include <QApplication>
#include<QLabel>
#include<QRadioButton>
#include<QSlider>
#include<QHBoxLayout>
#include<QGroupBox>
#include<QLCDNumber>
#include<QSpinBox>
#include<QDial>
#include<QFormLayout>
#include<QPushButton>
#include<QtGui>
#include "ModulationAndAudio.h"
#include "AMCarrier.h"


ModulationAndAudio::ModulationAndAudio(QWidget *parent)
:QWidget(parent) {
	
}

void ModulationAndAudio::setAMCarrier(AMCarrier *am) {
	amCarrier = am;
	QGridLayout *grid = new QGridLayout;
	grid->addWidget(createFirstGroup(), 0, 0);
	grid->addWidget(createSecondGroup(), 1, 0);
	grid->addWidget(createExitButton(), 2, 0, Qt::AlignCenter);
	setLayout(grid);
}

QGroupBox* ModulationAndAudio::createFirstGroup()
{
	QGroupBox *modulation = new QGroupBox(tr("Modulation"));
	QRadioButton *am = new QRadioButton(tr("AM"));
	QRadioButton *fm = new QRadioButton(tr("FM"));
	QLabel *frequencyLabel = new QLabel(tr("Frequency"));
	QSlider *freqSlider = new QSlider(Qt::Horizontal);
	QLCDNumber *lcdFrequency = new QLCDNumber(10);
	QGridLayout *modLayout = new QGridLayout;

	//Set properties to the widgets
	lcdFrequency->setFrameShape(QFrame::StyledPanel);
	lcdFrequency->setPalette(Qt::blue);
	lcdFrequency->setProperty("value", QVariant(1));
	lcdFrequency->setFrameShape(QFrame::StyledPanel);
	freqSlider->setRange(1, 100);
	freqSlider->setValue(1);
	freqSlider->setSingleStep(1);
	freqSlider->setPageStep(1);
	freqSlider->setFocusPolicy(Qt::StrongFocus);
	freqSlider->setTickPosition(QSlider::TicksBothSides);
	freqSlider->setTickInterval(100);
	freqSlider->setMinimumSize(QSize(250, 0));

	fm->setChecked(true);

	//connect lcdFrequency to the frequency slider
	connect(freqSlider, SIGNAL(valueChanged(int)), lcdFrequency,
			SLOT(display(int)));
	// Connect frequency slider to setFrequency slot of amCarrier
	connect(freqSlider, SIGNAL(valueChanged(int)),amCarrier,SLOT(setFrequency(int)));

	//Add widgets to the layout
	modLayout->addWidget(am, 0, 0);
	modLayout->addWidget(fm, 0, 1);
	modLayout->addWidget(frequencyLabel, 1, 0);
	modLayout->addWidget(freqSlider, 1, 1);
	modLayout->addWidget(lcdFrequency, 1, 2);
	modLayout->addWidget(amCarrier,1,3);
	modulation->setLayout(modLayout);

	return modulation;
}

QGroupBox* ModulationAndAudio::createSecondGroup()
{
	QGroupBox *audioSettings = new QGroupBox(tr("Audio Settings"));
	QLabel *bassLabel = new QLabel(tr("Bass:"));
	QLabel *trebleLabel = new QLabel(tr("Treble:"));
	QLabel *volumeLabel = new QLabel(tr("Volume:"));
	QLCDNumber *bassLCD = new QLCDNumber();
	QLCDNumber *trebleLCD = new QLCDNumber;
	QLCDNumber *volumeLCD = new QLCDNumber;
	QRadioButton *mono = new QRadioButton(tr("Mono"));
	QRadioButton *stereo = new QRadioButton(tr("Stereo"));
	QSpinBox *bassSpinBox = new QSpinBox;
	QSpinBox *trebleSpinBox = new QSpinBox;
	QDial *dialKnobVolume = new QDial();
	QGridLayout *audioSettingsLayout = new QGridLayout;

	//Set the properties for the widgets
	mono->setChecked(true);
	bassSpinBox->setRange(-12, 12);
	bassSpinBox->setSingleStep(1);
	trebleSpinBox->setRange(-12, 12);
	trebleSpinBox->setSingleStep(1);
	dialKnobVolume->setNotchesVisible(true);
	dialKnobVolume->setMaximum(5);
	dialKnobVolume->setValue(1);
	volumeLCD->setPalette(Qt::blue);
	volumeLCD->setProperty("value", QVariant(1));
	bassLCD->setPalette(Qt::blue);
	volumeLCD->setFrameShape(QFrame::StyledPanel);
	bassLCD->setFrameShape(QFrame::StyledPanel);
	trebleLCD->setFrameShape(QFrame::StyledPanel);
	trebleLCD->setPalette(Qt::blue);

	//Connect dial knob to the volume LCD slot
	connect(dialKnobVolume, SIGNAL(sliderMoved(int)), volumeLCD,
			SLOT(display(int)));
	// Connect dial knob to setAmplitude slot of amCarrier
	connect(dialKnobVolume, SIGNAL(sliderMoved(int)),amCarrier,SLOT(setAmplitude(int)));
	//Connect bass Spin box to the bass LCD display
	connect(bassSpinBox, SIGNAL(valueChanged(int)), bassLCD,
			SLOT(display(int)));
	//Connect treble Spin box to treble LCD display
	connect(trebleSpinBox, SIGNAL(valueChanged(int)), trebleLCD,
			SLOT(display(int)));

	//Add widgets to the layout
	audioSettingsLayout->addWidget(bassLabel, 0, 0);
	audioSettingsLayout->addWidget(bassSpinBox, 0, 1);
	audioSettingsLayout->addWidget(bassLCD, 0, 2);
	audioSettingsLayout->addWidget(trebleLabel, 1, 0);
	audioSettingsLayout->addWidget(trebleSpinBox, 1, 1);
	audioSettingsLayout->addWidget(trebleLCD, 1, 2);
	audioSettingsLayout->addWidget(mono, 2, 0);
	audioSettingsLayout->addWidget(stereo, 2, 1);
	audioSettingsLayout->addWidget(volumeLabel, 3, 0);
	audioSettingsLayout->addWidget(dialKnobVolume, 3, 1, 2, 1);
	audioSettingsLayout->addWidget(volumeLCD, 3, 2);
	audioSettings->setLayout(audioSettingsLayout);

	return audioSettings;
}

QGroupBox* ModulationAndAudio::createExitButton()
{
	QGroupBox *exit = new QGroupBox;
	QPushButton *exitButton = new QPushButton(tr("Exit"));
	QHBoxLayout *layout = new QHBoxLayout;

	//Connect the exit button to the QApplication. QApp should be closed when the exit button is clicked
	connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	layout->addWidget(exitButton, Qt::AlignHCenter);
	exit->setLayout(layout);
	return exit;
}


