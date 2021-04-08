#include "Json/ZyJsonObject.h"

void FZyJsonObject::SetValue(const FString & Key, const FZyJsonValue & Value) const
{
	JsonObject->SetField(Key, Value.JsonValue.IsValid() ? Value.JsonValue : FZyJsonValue().JsonValue);
}

FZyJsonValue FZyJsonObject::GetValue(const FString& Key) const
{
	return FZyJsonValue(JsonObject->GetField<EJson::None>(Key));
}
