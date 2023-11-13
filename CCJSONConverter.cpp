#include "CCJSONConverter.h"
cJSON* JSONConverter::createJSONObjectFromValueMap(ValueMap valueMap) {
    cJSON* object = cJSON_CreateObject();
    for (const auto& pair : valueMap) {
        cJSON_AddItemToObject(object, pair.first.c_str(),
            createJSONObjectFromValue(pair.second));
    }
    return object;
}
cJSON* JSONConverter::createJSONObjectFromValueVector(ValueVector valueVector) {
    cJSON* array = cJSON_CreateArray();
    for (const auto& value : valueVector) {
        cJSON_AddItemToArray(array, createJSONObjectFromValue(value));
    }
    return array;
}
cJSON* JSONConverter::createJSONObjectFromValue(Value value) {
    switch (value.getType()) {
    case Value::Type::INTEGER:
        return cJSON_CreateNumber(value.asInt());
        break;
    case Value::Type::DOUBLE:
        return cJSON_CreateNumber(value.asDouble());
        break;
    case Value::Type::FLOAT:
        return cJSON_CreateNumber(value.asFloat());
        break;
    case Value::Type::BOOLEAN:
        return cJSON_CreateBool(value.asBool());
        break;
    case Value::Type::STRING:
        return cJSON_CreateString(value.asString().c_str());
        break;
    case Value::Type::MAP:
        return createJSONObjectFromValueMap(value.asValueMap());
        break;
    case Value::Type::VECTOR:
        return createJSONObjectFromValueVector(value.asValueVector());
        break;
    }
    return cJSON_CreateNull();
}
ValueMap JSONConverter::createValueMapFromJSONObject(cJSON* jsonObject) {
    ValueMap valueMap;
    cJSON* element;
    cJSON_ArrayForEach(element, jsonObject) {
        valueMap.emplace(element->string,
            createValueFromJSONObject(element));
    }
    return valueMap;
}
ValueVector JSONConverter::createValueVectorFromJSONObject(cJSON* jsonObject)
{
    ValueVector valueVector;
    cJSON* element;
    cJSON_ArrayForEach(element, jsonObject) {
        valueVector.push_back(createValueFromJSONObject(jsonObject));
    }
    return valueVector;
}
Value JSONConverter::createValueFromJSONObject(cJSON* jsonObject) {
    double doubleValue = 0.0;
    int intValue = 0;
    float floatValue = 0.0f;
    switch (jsonObject->type) {
    case cJSON_Number:
        doubleValue = jsonObject->valuedouble;
        intValue = static_cast<int>(doubleValue);
        floatValue = static_cast<float>(doubleValue);

        if (intValue == doubleValue) {
            return Value(intValue);
        }
        else if (floatValue == doubleValue) {
            return Value(floatValue);
        }
        else {
            return Value(doubleValue);
        }
        break;
    case cJSON_False:
        return Value(false);
        break;
    case cJSON_True:
        return Value(true);
        break;
    case cJSON_String:
        return Value(jsonObject->valuestring);
        break;
    case cJSON_Object:
        return Value(createValueMapFromJSONObject(jsonObject));
        break;
    case cJSON_Array:
        return Value(createValueVectorFromJSONObject(jsonObject));
        break;
    }
    return ValueNull;
}