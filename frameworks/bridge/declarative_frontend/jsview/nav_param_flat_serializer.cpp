/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nav_param_flat_serializer.h"

#include <cstdlib>
#include "base/base64/base64_util.h"
#include "base/log/log_wrapper.h"
#include "bridge/common/utils/engine_helper.h"
#include "jsnapi_expo.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr char FLAT_SER_PREFIX[] = "__nav_flat_ser__:";
} // namespace

bool NavParamFlatSerializer::IsFlatSerialized(const std::string& param)
{
    static const size_t prefixLen = sizeof(FLAT_SER_PREFIX) - 1;
    if (param.size() <= prefixLen) {
        return false;
    }
    return param.compare(0, prefixLen, FLAT_SER_PREFIX) == 0;
}

std::string NavParamFlatSerializer::Serialize(const JSRef<JSVal>& param)
{
    constexpr char undefinedVal[] = "undefined";
    if (param.IsEmpty() || param->IsUndefined() || param->IsNull()) {
        return undefinedVal;
    }
    const EcmaVM* vm = GetEcmaVm();
    if (vm == nullptr) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer serialize: vm is null");
        return undefinedVal;
    }
    panda::LocalScope scope(vm);
    Local<JSValueRef> value = param->GetLocalHandle();
    if (value->IsUndefined() || value->IsNull()) {
        return undefinedVal;
    }
    size_t outSize = 0;
    uint8_t* buffer = panda::JSNApi::SerializeValue(vm, value, panda::JSValueRef::Undefined(vm),
        panda::JSValueRef::Undefined(vm), false, true, false, outSize);
    if (buffer == nullptr || outSize == 0) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer serialize: serialization failed");
        return undefinedVal;
    }
    std::string encoded = Base64Util::Encode(buffer, outSize);
    free(buffer);
    if (encoded.empty()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer serialize: base64 encode failed");
        return undefinedVal;
    }
    std::string result = FLAT_SER_PREFIX + encoded;
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer serialize success, size: %{public}zu",
        outSize);
    return result;
}

JSRef<JSVal> NavParamFlatSerializer::Deserialize(const std::string& param)
{
    if (!IsFlatSerialized(param)) {
        return JSRef<JSObject>::New()->ToJsonObject(param.c_str());
    }
    static const size_t prefixLen = sizeof(FLAT_SER_PREFIX) - 1;
    std::string base64Data = param.substr(prefixLen);
    std::string decoded;
    if (!Base64Util::Decode(base64Data, decoded)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer deserialize: base64 decode failed");
        return JSRef<JSVal>::Make();
    }
    const EcmaVM* vm = GetEcmaVm();
    if (vm == nullptr) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer deserialize: vm is null");
        return JSRef<JSVal>::Make();
    }
    auto engine = EngineHelper::GetCurrentEngine();
    if (engine == nullptr) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer deserialize: engine is null");
        return JSRef<JSVal>::Make();
    }
    auto nativeEngine = engine->GetNativeEngine();
    if (nativeEngine == nullptr) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer deserialize: nativeEngine is null");
        return JSRef<JSVal>::Make();
    }
    panda::LocalScope scope(vm);
    uint8_t* buffer = reinterpret_cast<uint8_t*>(decoded.data());
    Local<JSValueRef> result = panda::JSNApi::DeserializeValue(vm, buffer,
        reinterpret_cast<void*>(nativeEngine));
    if (result->IsUndefined()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer deserialize: deserialization failed");
        return JSRef<JSVal>::Make();
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "NavParamFlatSerializer deserialize success");
    return JSRef<JSVal>::Make(JsiValue(result));
}
} // namespace OHOS::Ace::Framework
