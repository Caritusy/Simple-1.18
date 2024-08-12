#include "Loader.h"
#include "Module/Modules/SimpleUser.h"
#define ELPP_THREAD_SAFE

SlimUtils::SlimMem mem;
const SlimUtils::SlimModule* gameModule;
bool Loader::isRunning = true;
#pragma comment(lib, "libMinHook.x86.lib")
/* {
Level	描述
Global	Generic level that represents all levels. Useful when setting global configuration for all levels.
Trace	Information that can be useful to back-trace certain events - mostly useful than debug logs.
Debug	Informational events most useful for developers to debug application. Only applicable if NDEBUG is not defined (for non-VC++) or _DEBUG is defined (for VC++).
Fatal	Very severe error event that will presumably lead the application to abort.
Error	Error information but will continue application to keep running.
Warning	Information representing errors in application but application will keep running.
Info	Mainly useful to represent current progress of application.
Verbose	Information that can be highly useful and vary with verbose logging level. Verbose logging is not applicable to hierarchical logging.
Unknown	Only applicable to hierarchical logging and is used to turn off logging completely.
}*/
INITIALIZE_EASYLOGGINGPP
DWORD WINAPI ejectThread(LPVOID lpParam) {
	while (Loader::isRunning) {
		if ((GameData::isKeyDown(VK_CONTROL) && GameData::isKeyDown('L')) || GameData::shouldTerminate()) {
			Loader::isRunning = false;  // Uninject
			break;
		}
		Sleep(20);
	}
	LOG(INFO) << "Stopping Threads...";
	Sleep(50);
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);
}
DWORD WINAPI start(LPVOID lpParam) {
	{
		FreeConsole();
		OPEN_COONSOLE();

		el::Configurations conf;
		conf.setToDefault();
		conf.set(el::Level::Info, el::ConfigurationType::Filename, "logs.log");
#ifdef _DEBUG
		conf.set(el::Level::Debug, el::ConfigurationType::Filename, "logs.log");
		conf.set(el::Level::Error, el::ConfigurationType::Filename, "logs.log");
#else
		conf.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
		conf.set(el::Level::Error, el::ConfigurationType::Enabled, "false");
#endif // _DEBUG
		el::Loggers::reconfigureAllLoggers(conf);
	}

	user.DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1717987481307/fusion-pixel-10px-monospaced-zh_hant.ttf"
		, "Downloaded/fusion-pixel-10px-monospaced-zh_hant.ttf");
	user.DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1718024505474/hacker.jpg"
		, "Downloaded/hacker.jpg");	
	user.DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1719141324942/obj_w5rDlsOJwrLDjj7CmsOj_31598684973_143e_133b_3e2e_65c7ac409cdbbca8795ad15ef29831df.m4a"
		, "Downloaded/弃子pt.2.m4a");
	user.DownloadFile("https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1719142802568/obj_w5rDlsOJwrLDjj7CmsOj_35013079457_54da_45af_8773_9f224a0abd9b0c7177f0a7f6f5ee28be.m4a"
		, "Downloaded/渐行渐远\\Drift Away.m4a");


	LOG(INFO) << "Starting up...";
	init();
	user.SimpleUserinit("爱发电userID", "爱发电Token");  //user封装的太臭了
	DWORD procId = GetCurrentProcessId();
	if (!mem.Open(procId, SlimUtils::ProcessAccess::Full)) {
		LOG(FATAL) << "Failed to open process, error-code: " << GetLastError();
		return 1;
	}
	gameModule = mem.GetModule(L"Minecraft.Windows.exe");
	MH_Initialize();
	GameData::initGameData(gameModule, &mem, (HMODULE)lpParam);
	Target::init(Game.getPtrLocalPlayer());

	Hooks::Init();
	DWORD ejectThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ejectThread, lpParam, NULL, &ejectThreadId);  // Checking Keypresses
	LOG(INFO) << "EjectThread:" << ejectThreadId;
	cmdMgr->initCommands();
	LOG(INFO) << "Initialized command manager (1/3)";
	moduleMgr->initModules();
	LOG(INFO) << "Initialized module manager (2/3)";
	configMgr->init();
	LOG(INFO) << "Initialized config manager (3/3)";

	std::thread countThread([lpParam]() {
		while (Loader::isRunning) {
			Sleep(1000);
		}});
	countThread.detach();

	Hooks::Enable();
	ExitThread(0);
}
////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                              //
//                      ____/`---'\____                           //
//                    .'  \\|     |//  `.                         //
//                   /  \\|||  :  |||//  \                        //
//                  /  _||||| -:- |||||-  \                       //
//                  |   | \\\  -  /// |   |                       //
//                  | \_|  ''\---/''  |   |                       //
//                  \  .-\__  `-`  ___/-. /                       //
//                ___`. .'  /--.--\  `. . ___                     //
//              ."" '<  `.___\_<|>_/___.'  >'"".                  //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //
//      ========`-.____`-.___\_____/___.-`____.-'========         //
//                           `=---='                              //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//         佛祖保佑       永无BUG     永不断言                    //
////////////////////////////////////////////////////////////////////
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
		break;

	case DLL_PROCESS_DETACH:
		Loader::isRunning = false;
		configMgr->saveConfig();
		moduleMgr->disable();
		cmdMgr->disable();
		Hooks::Restore();
	//	opengl::disable();
		delete moduleMgr;
		delete cmdMgr;
		delete configMgr;
		if (Game.getLocalPlayer() != nullptr) {
			GuiData* guiData = Game.getClientInstance()->getGuiData();
			if (guiData != nullptr) {
				guiData->displayClientMessageF("%s%s%sEjected!", RED, BOLD, STRIKETHROUGH);
			}
			LOG(INFO) << "Ejected!";
		}
		//D3D11::disable();

		break;
	}
	return TRUE;
}