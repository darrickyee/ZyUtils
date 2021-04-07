
#include "Json/ZyJsonValue.h"

EZyJsonType FZyJsonValue::GetType() const
{
	if (!JsonValue.IsValid()) return EZyJsonType::None;

	switch (JsonValue->Type)
	{
	case EJson::Null:
		return EZyJsonType::Null;

	case EJson::Boolean:
		return EZyJsonType::Boolean;

	case EJson::Number:
		return EZyJsonType::Number;

	case EJson::String:
		return EZyJsonType::String;

	case EJson::Object:
		return EZyJsonType::Object;

	case EJson::Array:
		return EZyJsonType::Array;

	default:
		return EZyJsonType::None;
	}
}