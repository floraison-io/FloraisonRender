#include "MRenderCore.h"
#include "MInterface.h"
#include "encapVk.h"
#include "MTracer.h"
#include "iniLoader.h"
#include <iostream>

string consoleString;
extern MRenderCore* renderCore;
extern INI_STRUCT globalConfig;

void consoleInput() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	getline(cin, consoleString);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void executeSingle(string executeString) {
	if (executeString.find("//") == 0) {
		//do nothing
	}
	else if (executeString.find("exit") == 0) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (executeString.find("curse_mode") == 0) {
		int curseMode = stoi(executeString.substr(string("curse_mode").size() + 1));
		if (curseMode == 0) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	else if (executeString.find("speed") == 0) {
		float speed = stof(executeString.substr(string("speed").size() + 1));
		cameraSpeed = speed;
	}
	else if (executeString.find("load_scene") == 0) {
		string scenePath = executeString.substr(string("load_scene").size() + 1);
		if (scenePath.find(";") != string::npos) {
			scenePath = scenePath.substr(0, scenePath.find(";"));
		}
		std::ifstream validation(scenePath, std::ios::in);
		if (validation) {
			string interfacePath = renderCore->interfacePath;
			delete renderCore;
			renderCore = new MRenderCore(scenePath, interfacePath);
		}
		else {
			cout << "ERROR: INVALID SCENE FILE" << endl;
		}
		validation.close();
	}
	else if (executeString.find("load_interface") == 0) {
		string interfacePath = executeString.substr(string("load_interface").size() + 1);
		if (interfacePath.find(";") != string::npos) {
			interfacePath = interfacePath.substr(0, interfacePath.find(";"));
		}
		std::ifstream validation(interfacePath, std::ios::in);
		if (validation) {
			string scenePath = renderCore->scenePath;
			delete renderCore;
			renderCore = new MRenderCore(scenePath, interfacePath);
		}
		else {
			cout << "ERROR: INVALID INTERFACE FILE" << endl;
		}
		validation.close();
	}
	else if (executeString.find("tracer") == 0) {
		string tracerPath = executeString.substr(string("tracer").size() + 1);
		if (tracerPath.find(";") != string::npos) {
			tracerPath = tracerPath.substr(0, tracerPath.find(";"));
		}
		MTracer* tracer = new MTracer();
		tracer->traceDecode(tracerPath);
		tracer->beginExecute();
	}
	else if (executeString.find("gbuffer") == 0) {
		int gID = stoi(executeString.substr(string("gbuffer").size() + 1));
		displayID = gID;
	}
	else if (executeString.find("taau") == 0) {
		int taauState = stoi(executeString.substr(string("taau").size() + 1));
		UIEnable = taauState;
	}
	else if (executeString.find("inf_diffuse") == 0) {
		int inf_diffuseState = stoi(executeString.substr(string("inf_diffuse").size() + 1));
		debugVal = inf_diffuseState;
	}
	else if (executeString.find("interface_page") == 0) {
		int page = stoi(executeString.substr(string("interface_page").size() + 1));
		MInterface::page = page;
	}
	else if (executeString.find("text_disable") == 0) {
		int textID = stoi(executeString.substr(string("textDisable").size() + 1));
		MInterface::textDisableTable[textID] = 1;
	}
	else if (executeString.find("text_enable") == 0) {
		int textID = stoi(executeString.substr(string("text_enable").size() + 1));
		MInterface::textDisableTable[textID] = 0;
	}
	else if (executeString.find("write_interface_state") == 0) {
		renderCore->p_interface->writeStateFile();
	}
	else if (executeString.find("config_full_screen") == 0) {
		int full_screen = stoi(executeString.substr(string("config_full_screen").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "full_screen", to_string(full_screen));
	}
	else if (executeString.find("config_inner_width") == 0) {
		int inner_width = stoi(executeString.substr(string("config_inner_width").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "inner_width", to_string(inner_width));
	}
	else if (executeString.find("config_inner_height") == 0) {
		int inner_height = stoi(executeString.substr(string("config_inner_height").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "inner_height", to_string(inner_height));
	}
	else if (executeString.find("config_outer_width") == 0) {
		int outer_width = stoi(executeString.substr(string("config_outer_width").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "outer_width", to_string(outer_width));
	}
	else if (executeString.find("config_outer_height") == 0) {
		int outer_height = stoi(executeString.substr(string("config_outer_height").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "outer_height", to_string(outer_height));
	}
	else if (executeString.find("config_near_plane") == 0) {
		float near_plane = stof(executeString.substr(string("config_near_plane").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "near_plane", to_string(near_plane));
	}
	else if (executeString.find("config_far_plane") == 0) {
		float far_plane = stof(executeString.substr(string("config_far_plane").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "far_plane", to_string(far_plane));
	}
	else if (executeString.find("config_fov") == 0) {
		float fov = stof(executeString.substr(string("config_fov").size() + 1));
		iniLoader::editKey(&globalConfig, "general", "fov", to_string(fov));
	}
	else if (executeString.find("config_radiance_cache_rad") == 0) {
		int radiance_cache_rad = stoi(executeString.substr(string("config_radiance_cache_rad").size() + 1));
		iniLoader::editKey(&globalConfig, "graphic", "radiance_cache_rad", to_string(radiance_cache_rad));
	}
	else if (executeString.find("config_ssp_1") == 0) {
		int ssp = stoi(executeString.substr(string("config_ssp_1").size() + 1));
		iniLoader::editKey(&globalConfig, "graphic", "ssp_1", to_string(ssp));
	}
	else if (executeString.find("config_ssp_2") == 0) {
		int ssp_2 = stoi(executeString.substr(string("config_ssp_2").size() + 1));
		iniLoader::editKey(&globalConfig, "graphic", "ssp_2", to_string(ssp_2));
	}
	else if (executeString.find("save_config") == 0) {
		iniLoader::writeIni(globalConfig, "res/config/cfg.ini");
	}
	else {
		cout << "unknow execution " << "\"" << (executeString.find(";") == string::npos ? executeString : executeString.substr(0,executeString.find(";"))) << "\"" << endl;
	}
	if (executeString.find(";") != string::npos) {
		executeSingle(executeString.substr(executeString.find(";") + 1));
	}
}

void consoleProcess() {
	if (consoleString != "") {
		executeSingle(consoleString);
		consoleString = "";
	}
}

void executeScript(string scriptPath) {
	std::ifstream file(scriptPath);
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			if (line[0] == '/') {
				continue;
			}

			executeSingle(line);
		}
		file.close();
	}
}

void loadConfig(string iniPath) {
	iniLoader::loadIni(&globalConfig, iniPath);
	FULL_SCREEN = stoi(iniLoader::readKey(globalConfig, "general", "full_screen"));
	OUTER_WIDTH = stoi(iniLoader::readKey(globalConfig, "general", "outer_width"));
	OUTER_HEIGHT = stoi(iniLoader::readKey(globalConfig, "general", "outer_height"));
	INNER_WIDTH = stoi(iniLoader::readKey(globalConfig, "general", "inner_width"));
	INNER_HEIGHT = stoi(iniLoader::readKey(globalConfig, "general", "inner_height"));
	NEAR_PLANE = stof(iniLoader::readKey(globalConfig, "general", "near_plane"));
	FAR_PLANE = stof(iniLoader::readKey(globalConfig, "general", "far_plane"));
	FOV = stof(iniLoader::readKey(globalConfig, "general", "fov"));

	RADIANCE_CACHE_RAD = stoi(iniLoader::readKey(globalConfig, "graphic", "radiance_cache_rad"));
	SSP = stoi(iniLoader::readKey(globalConfig, "graphic", "ssp_1"));
	SSP_2 = stoi(iniLoader::readKey(globalConfig, "graphic", "ssp_2"));
	UIEnable = stoi(iniLoader::readKey(globalConfig, "graphic", "taau"));
	debugVal = stoi(iniLoader::readKey(globalConfig, "graphic", "inf_diffuse"));
}