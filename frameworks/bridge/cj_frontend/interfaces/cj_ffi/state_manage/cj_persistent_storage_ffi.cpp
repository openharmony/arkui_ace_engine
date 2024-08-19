/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "cj_persistent_storage_ffi.h"
#include "cj_lambda.h"
#include "core/common/storage/storage_proxy.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

bool GetValueFromStorage(std::string key, std::string& result)
{
    auto container = Container::Current();
    if (!container) {
        return false;
    }
    auto executor = container->GetTaskExecutor();
    std::string valueStr = StorageProxy::GetInstance()->GetStorage()->GetString(key);
    if (valueStr.empty()) {
        return false;
    }
    result = valueStr;
    return true;
}

void SetValueToStorage(std::string key, std::string value)
{
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto executor = container->GetTaskExecutor();
    if (!StorageProxy::GetInstance()->GetStorage()) {
        LOGW("no storage available");
        return;
    }
    StorageProxy::GetInstance()->GetStorage()->SetString(key, value);
}

extern "C" {
NativeOptionCString FfiOHOSAceFrameworkPersistentGetString(const char* key)
{
    NativeOptionCString result {.hasValue = false, .value = Utils::MallocCString("").value};
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return result;
#endif
    std::string tmp;
    if (GetValueFromStorage(key, tmp)) {
        result.hasValue = true;
        result.value = Utils::MallocCString(tmp).value;
    }
    return result;
}

void FfiOHOSAceFrameworkPersistentSetString(const char* key, const char* value, NotifyCallbackString callback)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
    "emulator or a real device instead.");
    return;
#endif
    SetValueToStorage(key, value);
    auto cjCallback = [func = CJLambda::Create(callback), key, value]() {
        func(key, value);
    };
    cjCallback();
}

NativeOptionInt64 FfiOHOSAceFrameworkPersistentGetInt64(const char* key)
{
    NativeOptionInt64 result {.hasValue = false, .value = 0};
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return result;
#endif
    std::string tmp;
    if (GetValueFromStorage(key, tmp)) {
        result.hasValue = true;
        result.value = std::stoll(tmp);
    }
    return result;
}

void FfiOHOSAceFrameworkPersistentSetInt64(const char* key, int64_t value, NotifyCallbackInt64 callback)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
    "emulator or a real device instead.");
    return;
#endif
    std::string tmp = std::to_string(value);
    SetValueToStorage(key, tmp);
    auto cjCallback = [func = CJLambda::Create(callback), key, value]() {
        func(key, value);
    };
    cjCallback();
}

NativeOptionFloat64 FfiOHOSAceFrameworkPersistentGetFloat64(const char* key)
{
    NativeOptionFloat64 result {.hasValue = false, .value = 0.0};
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return result;
#endif
    std::string tmp;
    if (GetValueFromStorage(key, tmp)) {
        result.hasValue = true;
        result.value = std::stod(tmp);
    }
    return result;
}

void FfiOHOSAceFrameworkPersistentSetFloat64(const char* key, double value, NotifyCallbackFloat64 callback)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
    "emulator or a real device instead.");
    return;
#endif
    std::string tmp = std::to_string(value);
    SetValueToStorage(key, tmp);
    auto cjCallback = [func = CJLambda::Create(callback), key, value]() {
        func(key, value);
    };
    cjCallback();
}

NativeOptionBool FfiOHOSAceFrameworkPersistentGetBool(const char* key)
{
    NativeOptionBool result {.hasValue = false, .value = false};
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return result;
#endif
    std::string tmp;
    if (GetValueFromStorage(key, tmp)) {
        result.hasValue = true;
        result.value = tmp == "true";
    }
    return result;
}

void FfiOHOSAceFrameworkPersistentSetBool(const char* key, bool value, NotifyCallbackBool callback)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
    "emulator or a real device instead.");
    return;
#endif
    std::string tmp = value ? "true": "false";
    SetValueToStorage(key, tmp);
    auto cjCallback = [func = CJLambda::Create(callback), key, value]() {
        func(key, value);
    };
    cjCallback();
}

void FfiOHOSAceFrameworkPersistentDelete(const char* key)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto executor = container->GetTaskExecutor();
    StorageProxy::GetInstance()->GetStorage()->Delete(key);
}
void FfiOHOSAceFrameworkPersistentClear()
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto executor = container->GetTaskExecutor();
    StorageProxy::GetInstance()->GetStorage()->Clear();
}
}