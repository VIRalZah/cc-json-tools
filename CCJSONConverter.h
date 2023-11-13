#ifndef _JSON_CONVERTER_H_
#define _JSON_CONVERTER_H
#include "includes.h"
class JSONConverter {
public:
	static cJSON* createJSONObjectFromValueMap(ValueMap valueMap);
	static cJSON* createJSONObjectFromValueVector(ValueVector valueVector);

	static cJSON* createJSONObjectFromValue(Value value);

	static ValueMap createValueMapFromJSONObject(cJSON* jsonObject);
	static ValueVector createValueVectorFromJSONObject(cJSON* jsonObject);

	static Value createValueFromJSONObject(cJSON* jsonObject);
};
typedef JSONConverter CCJSONConverter, __JSONConverter;
#endif