#include "CCJSONValueMap.h"
bool JSONValueMap::init() {
	return true;
}
bool JSONValueMap::initWithValueMap(ValueMap valueMap) {
	_valueMap = valueMap;
	return true;
}
bool JSONValueMap::initWithSaveString(std::string saveString) {
	auto json = cJSON_Parse(saveString.c_str());
	if (!initWithJSONObject(json)) {
		return false;
	}
	_saveString = saveString;
	return true;
}
bool JSONValueMap::initWithJSONObject(cJSON* json) {
	if (!json) {
		return false;
	}
	return initWithValueMap(JSONConverter::createValueMapFromJSONObject(json));
}
bool JSONValueMap::initWithFileName(const char* fileName) {
	return initWithSaveString(FileUtils::getInstance()->getStringFromFile(fileName));
}
JSONValueMap* JSONValueMap::create() {
	JSONValueMap* pRet = new (std::nothrow) JSONValueMap();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}
JSONValueMap* JSONValueMap::createWithSaveString(std::string saveString) {
	JSONValueMap* pRet = new (std::nothrow) JSONValueMap();
	if (pRet && pRet->initWithSaveString(saveString)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}
JSONValueMap* JSONValueMap::createWithContentOfFile(const char* fileName) {
	JSONValueMap* pRet = new (std::nothrow) JSONValueMap();
	if(pRet && pRet->initWithFileName(fileName)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}
std::string JSONValueMap::getSaveString() {
	if (auto json = JSONConverter::createJSONObjectFromValueMap(_valueMap)) {
		_saveString = cJSON_Print(json);
		cJSON_Delete(json);
	}
	return _saveString;
}
bool JSONValueMap::writeToFile(const char* filePath) {
	if (auto saveString = getSaveString(); saveString != std::string()) {
		return FileUtils::getInstance()->writeStringToFile(getSaveString(), filePath);
	}
	return false;
}