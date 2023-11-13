#ifndef _JSON_VALUE_MAP_H_
#define _JSON_VALUE_MAP_H_
#include "includes.h"
#include "CCJSONConverter.h"
class JSONValueMap : public Ref {
private:
	std::string _saveString;
	ValueMap _valueMap;
	bool init();
	bool initWithValueMap(ValueMap valueMap);
	bool initWithSaveString(std::string saveString);
	bool initWithJSONObject(cJSON* json);
	bool initWithFileName(const char* fileName);
public:
	static JSONValueMap* create();
	static JSONValueMap* createWithSaveString(std::string saveString);
	static JSONValueMap* createWithContentOfFile(const char* fileName);

	std::string getSaveString();
	ValueMap getValueMap() { return _valueMap; }

	bool writeToFile(const char* filePath);
};
typedef JSONValueMap CCJSONValueMap, __JsonValueMap;
#endif