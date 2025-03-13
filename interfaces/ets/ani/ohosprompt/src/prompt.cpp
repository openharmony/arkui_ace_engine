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

#include <ani.h>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/components_ng/pattern/toast/toast_layout_property.h"

std::string ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);
   
    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();

    ani_size bytesWritten = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytesWritten);
    
    utf8Buffer[bytesWritten] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}
bool GetToastMessage(ani_env *env, ani_object options, std::string& messageString)
{
    static const char *className = "L@ohos/prompt/prompt/ShowToastOptions;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }

    ani_ref message_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "message", &message_ref)) {
        return false;
    }

    auto message_str = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(message_ref));
    messageString = message_str;
    return true;
}
bool GetToastDuration(ani_env *env, ani_object options, int32_t& durationInt)
{
    static const char *className = "L@ohos/prompt/prompt/ShowToastOptions;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        std::cerr << "Not found '" << className << "'" << std::endl;
        return false;
    }
    ani_ref duration_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "duration", &duration_ref)) {
        return false;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(duration_ref, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_double duration;
    if (ANI_OK != env->Object_CallMethodByName_Double(
        static_cast<ani_object>(duration_ref), "doubleValue", nullptr, &duration)) {
        return false;
    }
    durationInt = static_cast<int32_t>(duration);
    return true;
}
bool GetToastBottom(ani_env *env, ani_object options, std::string& bottomString)
{
    static const char *className = "L@ohos/prompt/prompt/ShowToastOptions;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_ref bottom_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "bottom", &bottom_ref)) {
        return false;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(bottom_ref, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_class stringClass;
    env->FindClass("Lstd/core/String;", &stringClass);

    ani_class numberClass;
    env->FindClass("Lstd/core/Numeric;", &numberClass);

    ani_boolean isString;
    env->Object_InstanceOf(static_cast<ani_object>(bottom_ref), stringClass, &isString);
    if (isString) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(bottom_ref));
        bottomString = stringContent;
        return true;
    }
    ani_boolean isNumber;
    env->Object_InstanceOf(static_cast<ani_object>(bottom_ref), numberClass, &isNumber);
    if (isNumber) {
        ani_double duration;
        if (ANI_OK !=env->Object_CallMethodByName_Double(
            static_cast<ani_object>(bottom_ref), "doubleValue", nullptr, &duration)) {
            return false;
        }
        double botm = static_cast<double>(duration);
        bottomString = std::to_string(botm);
    }
    return true;
}
static void showToast([[maybe_unused]] ani_env* env, ani_object options)
{
    std::string messageInfo;
    std::string bottomInfo;
    int32_t durationInfo = 0;
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (isUndefined) {
        return;
    }
    GetToastMessage(env, options, messageInfo);
    std::cout << "GetToastMessage :" << messageInfo.c_str() << std::endl;
    GetToastDuration(env, options, durationInfo);
    std::cout << "GetToastDuration :" << durationInfo << std::endl;
    GetToastBottom(env, options, bottomInfo);
    std::cout << "GetToastBottom :" << bottomInfo.c_str() << std::endl;
    auto toastInfo = OHOS::Ace::NG::ToastInfo { .message = messageInfo,
        .duration = durationInfo,
        .bottom = bottomInfo,
        .showMode = OHOS::Ace::NG::ToastShowMode::DEFAULT,
        .alignment = -1,
        .offset = std::nullopt };
    auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->ShowToast(toastInfo, nullptr);
    }
}
ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/prompt/prompt;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"showToast", nullptr, reinterpret_cast<void *>(showToast)},
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
