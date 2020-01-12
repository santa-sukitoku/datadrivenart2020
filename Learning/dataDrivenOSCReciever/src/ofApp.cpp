#include "ofMain.h"
#include "ofxOsc.h"

#include "ScreenConsole.h"

class ofApp : public ofBaseApp {
	ofxOscReceiver receiver;
	int x;
	int y;

	ScreenConsole console;
public:
	void setup() {
		receiver.setup(26666);
		ofSetWindowPosition(360, 0);
		ofSetWindowTitle("OscReceiver");
	}
	void update() {
		// OSC���b�Z�[�W����M���Ă�ꍇ receiver.hasWaitingMessages() �� true �ɂȂ�
		// ���b�Z�[�W�������������ė��܂��Ă��郁�b�Z�[�W����ɂȂ����� false �ɂȂ���while�𔲂���
		while (receiver.hasWaitingMessages()) {
			ofxOscMessage m;

			// ��ŏ������� ofxOscMessage �Ɏ�M�������b�Z�[�W�����i�[����
			receiver.getNextMessage(m);

			// OSC���b�Z�[�W�̈��� (/hogehoge) ���擾
			std::string address = m.getAddress();
			console("address") << address << " " << m.getNumArgs();

			if (address == "/double") {
				// �ŏ��̈����̌^���m�F, dobule�^��\�� d �������Ă���
				console(address) << m.getArgTypeName(0);
				// double�^ �̒l���擾
				console(address) << m.getArgAsDouble(0);
			}
			else if (address == "/float") {
				// �ŏ��̈����̌^���m�F, float�^��\�� f �������Ă���
				console(address) << m.getArgTypeName(0);
				// double�^ �̒l���擾
				console(address) << m.getArgAsFloat(0);
			}
			else if (address == "/string") {
				// �ŏ��̈����̌^���m�F, string�^��\�� s �������Ă���
				console(address) << m.getArgTypeName(0);
				// string�^�̒l���擾
				console(address) << m.getArgAsString(0);
				// 2�ڂ̈����̌^���m�F, symbol�^��\�� S �������Ă���
				console(address) << m.getArgTypeName(1);
				// symbol�^ (oF�ł�string�^�ɂȂ�) �̒l���擾
				console(address) << m.getArgAsSymbol(1);
			}
			else if (address == "/t") {
				// �ŏ��̈����̌^���m�F, true �^��\�� T �������Ă���
				console(address) << m.getArgTypeName(0);
				// bool�^�̒l���擾
				console(address) << m.getArgAsBool(0);
			}
			else if (address == "/f") {
				// �ŏ��̈����̌^���m�F, false �^��\�� F �������Ă���
				console(address) << m.getArgTypeName(0);
				// bool�^�̒l���擾
				console(address) << m.getArgAsBool(0);
			}
			else if (address == "/mouseMoved") {
				x = m.getArgAsInt32(0);
				y = m.getArgAsInt32(1);
				console(address) << x << ", " << y;
			}
		}
	}
	virtual void draw() {
		ofSetColor(255);
		ofDrawCircle(x, y, 10);
		console.print(40, 40);
	}
};

int main() {
	ofSetupOpenGL(360, 640, OF_WINDOW);
	ofRunApp(new ofApp());
}

