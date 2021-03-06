#include "OpenCVController.h"
#include <chrono>

#include <Server.h>
#include <SocketConnection.h>
#include <Address.h>
#include <NetworkError.h>
int main() {
#ifdef SELF_TEST
	ImageProcessor ip;
	String img_name = "test.jpg";
	chrono::system_clock::time_point start = chrono::system_clock::now();

	if (ip.isFirst()) ip.initialize(img_name);
	else ip.recognizeMovement(img_name);

	chrono::duration<double> sec = chrono::system_clock::now() - start;
	start = chrono::system_clock::now();
	cout << "initial - corner detection and find object" << endl << "elapsed time : " << sec.count() << endl << endl;
#endif


#ifdef VIDEO_TEST
	OpenCVController controller;
	controller.startVideo(1);
#endif


#ifdef NETWORK
	try {
		Network::Server server{ Network::Address("", 33333) };
		cout << "Wait for network connection!" << endl;
		auto connection = server.waitClient();

		OpenCVController controller(connection);
		controller.startVideo(1);
	}
	catch (const std::exception& e) {
		exit(0);
	}
#endif

	return 0;

}
