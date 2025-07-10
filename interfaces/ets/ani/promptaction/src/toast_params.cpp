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

#include "toast_params.h"

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

bool GetToastBottom(ani_env *env, ani_object object, std::string& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "bottom", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (GetStringParam(env, resultObj, result)) {
        return true;
    }

    double resultDouble;
    if (GetDoubleParam(env, resultObj, resultDouble)) {
        result = std::to_string(resultDouble);
        return true;
    }
    return false;
}

bool GetToastShowMode(ani_env *env, ani_object object, OHOS::Ace::NG::ToastShowMode& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "showMode", "L@ohos/promptAction/promptAction/ToastShowMode;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::NG::ToastShowMode>(resultInt);
    return true;
}

bool GetToastAlignment(ani_env *env, ani_object object, int32_t& result)
{
    std::string resultStr;
    if (!GetEnumString(env, object, "alignment", "Larkui/component/enums/Alignment;", resultStr)) {
        return false;
    }

    auto iter = alignmentMap.find(resultStr);
    if (iter != alignmentMap.end()) {
        result = static_cast<int32_t>(iter->second);
        return true;
    }
    result = -1;
    return false;
}

bool GetToastShadow(ani_env *env, ani_object object, std::optional<OHOS::Ace::Shadow>& result, bool& isTypeStyleShadow)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "shadow", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::Shadow shadow;
    if (GetShadowStyleParam(env, resultObj, shadow)) {
        result = std::make_optional<OHOS::Ace::Shadow>(shadow);
        isTypeStyleShadow = true;
        return true;
    }

    if (GetShadowOptionsParam(env, resultObj, shadow)) {
        result = std::make_optional<OHOS::Ace::Shadow>(shadow);
        isTypeStyleShadow = false;
        return true;
    }
    return false;
}

bool GetShowToastOptions(ani_env* env, ani_object object, OHOS::Ace::NG::ToastInfo result)
{
    if (IsUndefinedObject(env, object)) {
        return false;
    }

    if (!IsClassObject(env, object, "L@ohos/promptAction/promptAction/ShowToastOptions;")) {
        return false;
    }

    GetResourceStrParam(env, object, "message", result.message);
    GetInt32Param(env, object, "duration", result.duration);
    GetToastBottom(env, object, result.bottom);
    GetToastShowMode(env, object, result.showMode);
    GetToastAlignment(env, object, result.alignment);
    GetOffsetParamOpt(env, object, result.offset);
    GetResourceColorParamOpt(env, object, "backgroundColor", result.backgroundColor);
    GetResourceColorParamOpt(env, object, "textColor", result.textColor);
    GetBackgroundBlurStyleParamOpt(env, object, result.backgroundBlurStyle);
    GetToastShadow(env, object, result.shadow, result.isTypeStyleShadow);
    GetBoolParam(env, object, "enableHoverMode", result.enableHoverMode);
    GetHoverModeAreaParam(env, object, result.hoverModeArea);
    return true;
}