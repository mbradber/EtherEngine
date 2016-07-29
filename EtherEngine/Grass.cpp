#include "EtherApp.h"

class Grass : public Ether::Core::EtherApp
{
protected:
	void Startup() {
		EtherApp::Startup();
	}

	void Render(double currentTime) {
		EtherApp::Render(currentTime);
	}

	void Shutdown() {
		EtherApp::Shutdown();
	}
};

DECLARE_MAIN(Grass)