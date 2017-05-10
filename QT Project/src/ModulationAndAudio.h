/*
 * ModulationAndAudio.h
 *
 */
#ifndef MODULATIONANDAUDIO_H_
#define MODULATIONANDAUDIO_H_

class QGroupBox;
class AMCarrier;
class ModulationAndAudio : public QWidget {

public:
	ModulationAndAudio(QWidget *parent =0);
	AMCarrier *amCarrier;

private:
	QGroupBox *createFirstGroup();// Includes modulation and frequency settings
	QGroupBox *createSecondGroup(); // Includes audio settings
	QGroupBox *createExitButton(); // Includes exit button
public:
	void setAMCarrier(AMCarrier *am);

};

#endif /* MODULATIONANDAUDIO_H_ */
