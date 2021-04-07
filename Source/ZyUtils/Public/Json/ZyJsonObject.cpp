#include "Json/ZyJsonObject.h"

void FZyJsonObject::SetValue(const FString & Key, const FZyJsonValue & Value)
{
	JsonObject->SetField(Key, Value.JsonValue.IsValid() ? Value.JsonValue : FZyJsonValue().JsonValue);
}

FZyJsonValue FZyJsonObject::GetValue(const FString Key)
{
	return JsonObject->GetField(Key) || FZyJsonValue();
}
