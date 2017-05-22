#pragma once
#include <unordered_map>

class KeyboardManager {
public:
	KeyboardManager();
	~KeyboardManager();

	void setKeyDown(std::string k, bool d) { keys[k] = d; }

	bool keyDown(std::string k) { return keys[k]; }

private:
	std::unordered_map<std::string, bool> keys;


};