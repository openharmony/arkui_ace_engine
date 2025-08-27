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
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/core/components/common/properties/shadow.h"
#include "promptActionUtils.h"

std::unordered_map<std::string, int> alignmentMap = {
    {"TopStart", 0},
    {"Top", 1},
    {"TopEnd", 2},
    {"Start", 3},
    {"Center", 4},
    {"End", 5},
    {"BottomStart", 6},
    {"Bottom", 7},
    {"BottomEnd", 8}
};

bool GetToastMessage(ani_env *env, ani_object options, std::string& messageString)
{
    ani_ref message_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "message", &message_ref)) {
        return false;
    }
    if (GetIsStringObject(env, message_ref)) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(message_ref));
        messageString = stringContent;
        return true;
    }
    if (GetIsResourceObject(env, message_ref)) {
        ResourceInfo resourceInfo;
        std::string messageStr;
        if (!ParseResourceParam(env, static_cast<ani_object>(message_ref), resourceInfo)) {
            return false;
        }
        if (!ParseString(resourceInfo, messageStr)) {
            return false;
        }
        if (messageStr.size() == 0) {
            return false;
        }
        messageString = messageStr;
    }
    return true;
}
bool GetToastDuration(ani_env *env, ani_object options, int32_t& durationInt)
{
    ani_ref duration_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "duration", &duration_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, duration_ref)) {
        return false;
    }
    ani_double duration;
    if (ANI_OK !=env->Object_CallMethodByName_Double(
        static_cast<ani_object>(duration_ref), "doubleValue", nullptr, &duration)) {
        return false;
    }
    durationInt = static_cast<int32_t>(duration);
    return true;
}
bool GetToastBottom(ani_env *env, ani_object options, std::string& bottomString)
{
    ani_ref bottom_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "bottom", &bottom_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, bottom_ref)) {
        return false;
    }
    if (GetIsStringObject(env, bottom_ref)) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(bottom_ref));
        bottomString = stringContent;
        return true;
    }
    if (GetIsNumberObject(env, bottom_ref)) {
        ani_double bottom;
        if (ANI_OK !=env->Object_CallMethodByName_Double(
            static_cast<ani_object>(bottom_ref), "doubleValue", nullptr, &bottom)) {
            return false;
        }
        double botm = static_cast<double>(bottom);
        bottomString = std::to_string(botm);
    }
    return true;
}
bool GetToastShowMode(ani_env *env, ani_object options, OHOS::Ace::NG::ToastShowMode& showMode)
{
    ani_ref showMode_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "showMode", &showMode_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, showMode_ref)) {
        return false;
    }
    if (!GetIsToastShowModeEnum(env, showMode_ref)) {
        return false;
    }
    ani_int showMode_int;
    if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(showMode_ref), &showMode_int)) {
        return false;
    }
    showMode = static_cast<OHOS::Ace::NG::ToastShowMode>(showMode_int);
    return true;
}
bool GetToastAlignment(ani_env *env, ani_object options, int32_t& alignment)
{
    ani_ref alignment_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "alignment", &alignment_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, alignment_ref)) {
        return false;
    }
    if (!GetIsAlignmentEnum(env, alignment_ref)) {
        return false;
    }
    ani_string stringValue;
    if (ANI_OK != env->EnumItem_GetValue_String(static_cast<ani_enum_item>(alignment_ref), &stringValue)) {
        return false;
    }
    auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(stringValue));
    auto it = alignmentMap.find(stringContent);
    if (it != alignmentMap.end()) {
        alignment = static_cast<int32_t>(it->second);
    } else {
        alignment = -1;
        return false;
    }
    return true;
}
bool GetToastBackgroundBlurStyle(ani_env *env, ani_object options, std::optional<int32_t>& backgroundBlurStyle)
{
    ani_ref blurStyle_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "backgroundBlurStyle", &blurStyle_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, blurStyle_ref)) {
        return false;
    }
    if (!GetIsBlurStyleEnum(env, blurStyle_ref)) {
        return false;
    }
    ani_int blueStyle_int;
    if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(blurStyle_ref), &blueStyle_int)) {
        return false;
    }
    backgroundBlurStyle = static_cast<int32_t>(blueStyle_int);
    std::cerr << "GetToastBackgroundBlurStyle blueStyle " << static_cast<int32_t>(blueStyle_int) << std::endl;
    return true;
}
bool GetToastOffset(ani_env *env, ani_object options, std::optional<OHOS::Ace::DimensionOffset>& offset)
{
    ani_ref offset_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "offset", &offset_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, offset_ref)) {
        return false;
    }
    ani_ref dx_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(static_cast<ani_object>(offset_ref), "dx", &dx_ref)) {
        return false;
    }
    ani_ref dy_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(static_cast<ani_object>(offset_ref), "dy", &dy_ref)) {
        return false;
    }
    OHOS::Ace::CalcDimension dx;
    OHOS::Ace::CalcDimension dy;
    if (!ParseLengthToDimension(env, dx_ref, OHOS::Ace::DimensionUnit::VP, dx)) {
        return false;
    }
    if (!ParseLengthToDimension(env, dy_ref, OHOS::Ace::DimensionUnit::VP, dy)) {
        return false;
    }
    offset = OHOS::Ace::DimensionOffset { dx, dy };
    return true;
}
bool GetToastShadow(ani_env *env, ani_object options, std::optional<OHOS::Ace::Shadow>& shadow,
                    bool& isTypeStyleShadow)
{
    ani_ref shadow_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "shadow", &shadow_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, shadow_ref)) {
        return false;
    }
    OHOS::Ace::Shadow shadowProps;
    if (GetIsShadowStyleEnum(env, shadow_ref)) {
        ani_int shadow_int;
        if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(shadow_ref), &shadow_int)) {
            return false;
        }
        auto style = static_cast<OHOS::Ace::ShadowStyle>(shadow_int);
        GetShadowFromTheme(style, shadowProps);
        shadow = shadowProps;
        return true;
    }
    if (GetIsShadowOptionsObject(env, shadow_ref)) {
        bool ret = GetToastObjectShadow(env, static_cast<ani_object>(shadow_ref), shadowProps);
        isTypeStyleShadow = false;
        return ret;
    }
    return true;
}
bool GetToastBackgroundColor(ani_env* env, ani_object options, std::optional<OHOS::Ace::Color>& backgroundColor)
{
    ani_ref resourceColor_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "backgroundColor", &resourceColor_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, resourceColor_ref)) {
        return false;
    }
    OHOS::Ace::Color resourceColor;
    if (ParseAniColor(env, resourceColor_ref, resourceColor)) {
        backgroundColor = resourceColor;
        return true;
    }
    return false;
}
bool GetToastTextColor(ani_env* env, ani_object options, std::optional<OHOS::Ace::Color>& textColor)
{
    ani_ref resourceColor_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "textColor", &resourceColor_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, resourceColor_ref)) {
        return false;
    }
    OHOS::Ace::Color resourceColor;
    if (ParseAniColor(env, resourceColor_ref, resourceColor)) {
        textColor = resourceColor;
        return true;
    }
    return false;
}
bool GetToastEnableHoverMode(ani_env* env, ani_object options, bool& enableHoverMode)
{
    ani_ref mode_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "enableHoverMode", &mode_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, mode_ref)) {
        return false;
    }
    ani_boolean modeValue;
    if (ANI_OK != env->Object_CallMethodByName_Boolean(
        static_cast<ani_object>(mode_ref), "unboxed", nullptr, &modeValue)) {
        return false;
    }
    enableHoverMode = static_cast<bool>(modeValue);
    return true;
}
bool GetToastHoverModeArea(ani_env* env, ani_object options, OHOS::Ace::HoverModeAreaType& hoverModeArea)
{
    ani_ref area_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "hoverModeArea", &area_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, area_ref)) {
        return false;
    }
    if (!GetIsHoverModeAreaEnum(env, area_ref)) {
        return false;
    }
    ani_int area_int;
    if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(area_ref), &area_int)) {
        return false;
    }
    hoverModeArea = static_cast<OHOS::Ace::HoverModeAreaType>(area_int);
    return true;
}
bool GetToastParams(ani_env* env, ani_object options, OHOS::Ace::NG::ToastInfo toastInfo)
{
    if (GetIsUndefinedObject(env, options)) {
        return false;
    }
    if (!GetIsShowToastOptionsObject(env, options)) {
        return false;
    }
    GetToastMessage(env, options, toastInfo.message);
    std::cout << "GetToastMessage :" << toastInfo.message.c_str() << std::endl;
    GetToastDuration(env, options, toastInfo.duration);
    std::cout << "GetToastDuration :" << toastInfo.duration << std::endl;
    GetToastBottom(env, options, toastInfo.bottom);
    std::cout << "GetToastBottom :" << toastInfo.bottom.c_str() << std::endl;
    GetToastShowMode(env, options, toastInfo.showMode);
    std::cout << "GetToastShowMode :" << static_cast<int32_t>(toastInfo.showMode) << std::endl;
    GetToastAlignment(env, options, toastInfo.alignment);
    std::cout << "GetToastAlignment :" << static_cast<int32_t>(toastInfo.alignment) << std::endl;
    GetToastBackgroundBlurStyle(env, options, toastInfo.backgroundBlurStyle);
    GetToastBackgroundColor(env, options, toastInfo.backgroundColor);
    std::cout << "GetToastBackgroundColor :" << toastInfo.backgroundColor->ToString().c_str() << std::endl;
    GetToastTextColor(env, options, toastInfo.textColor);
    std::cout << "GetToastTextColor :" << toastInfo.textColor->ToString().c_str() << std::endl;
    GetToastOffset(env, options, toastInfo.offset);
    GetToastShadow(env, options, toastInfo.shadow, toastInfo.isTypeStyleShadow);
    GetToastEnableHoverMode(env, options, toastInfo.enableHoverMode);
    std::cout << "GetToastEnableHoverModer :" << toastInfo.enableHoverMode << std::endl;
    GetToastHoverModeArea(env, options, toastInfo.hoverModeArea);
    std::cout << "GetToastHoverModeArea :" << (int)toastInfo.hoverModeArea << std::endl;
    return true;
}
bool HandleShowToast(OHOS::Ace::NG::ToastInfo& toastInfo, std::function<void(int32_t)>& toastCallback)
{
    #ifdef OHOS_STANDARD_SYSTEM
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) && !ContainerIsScenceBoard() &&
        toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            return false;
        }
        delegate->ShowToast(toastInfo, std::move(toastCallback));
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowToast(toastInfo, std::move(toastCallback));
    }
#else
    auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return false;
    }
    // if (toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
    //     delegate->ShowToast(toastInfo, std::move(toastCallback));
    // } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
    //     OHOS::Ace::SubwindowManager::GetInstance()->ShowToast(toastInfo, std::move(toastCallback));
    // }
#endif
    return true;
}
static void showToast([[maybe_unused]] ani_env* env, ani_object options)
{
    std::cout << "ani showToast start" << std::endl;
    auto toastInfo = OHOS::Ace::NG::ToastInfo { .duration = -1,
        .showMode = OHOS::Ace::NG::ToastShowMode::DEFAULT,
        .alignment = -1 };
    if (!GetToastParams(env, options, toastInfo)) {
        return;
    }
    std::function<void(int32_t)> toastCallback = nullptr;
    HandleShowToast(toastInfo, toastCallback);
    std::cerr << "ShowToast end" << std::endl;
}
ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    std::cout << "ani ANI_Constructor start" << std::endl;

    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/promptAction/promptAction;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"showToast", nullptr, reinterpret_cast<void *>(showToast)},
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    std::cout << "ani ANI_Constructor end" << std::endl;
    return ANI_OK;
}
