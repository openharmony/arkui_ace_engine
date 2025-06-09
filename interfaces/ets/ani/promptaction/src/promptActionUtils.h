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

#ifndef ARKGEN_UTILS_H
#define ARKGEN_UTILS_H

#include <ani.h>
#include <cmath>
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <array>

#include "core/common/container.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/shadow_theme.h"
#include "core/common/resource/resource_manager.h"
#include "frameworks/base/log/log_wrapper.h"

enum PromptActionColor {
    PROMPT_ACTION_COLOR_WHITE,
    PROMPT_ACTION_COLOR_BLACK,
    PROMPT_ACTION_COLOR_BLUE,
    PROMPT_ACTION_COLOR_BROWN,
    PROMPT_ACTION_COLOR_GRAY,
    PROMPT_ACTION_COLOR_GREEN,
    PROMPT_ACTION_COLOR_GREY,
    PROMPT_ACTION_COLOR_ORANGE,
    PROMPT_ACTION_COLOR_PINK,
    PROMPT_ACTION_COLOR_RED,
    PROMPT_ACTION_COLOR_YELLOW,
    PROMPT_ACTION_COLOR_TRANSPARENT
};

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};
struct ResourceInfo {
    int32_t resId = 0;
    int32_t type = 0;
    std::vector<std::string> params;
    std::optional<std::string> bundleName = std::nullopt;
    std::optional<std::string> moduleName = std::nullopt;
};
enum class ResourceStruct { CONSTANT, DYNAMIC_V1, DYNAMIC_V2 };
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
const std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
const int32_t NUMBER_ZERO = 0;
const int32_t NUMBER_ONE = 1;
const int32_t NUMBER_TWO = 2;
const int32_t NUMBER_THREE = 3;
std::string ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str);
void PreFixEmptyBundleName(ani_env *env, ani_object value);
void processResourceType(ani_env *env, ani_object value, ani_ref params_ref, size_t length);
void ModifyResourceParam(ani_env *env, ani_object value, const ResourceType& resType, const std::string& resName);
void CompleteResourceParamV1(ani_env *env, ani_object value);
void CompleteResourceParamV2(ani_env *env, ani_object value);
bool ParseDollarResource(
    ani_env *env, ani_object params_ref, ResourceType& resType, std::string& resName, std::string& moduleName);
bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
ResourceStruct CheckResourceStruct(ani_env *env, ani_object value);
void CompleteResourceParam(ani_env *env, ani_object value);
bool ParseResourceParamId(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamBundleName(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamModuleName(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamType(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamName(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParam(ani_env *env, ani_object options, ResourceInfo& info);
OHOS::Ace::RefPtr<OHOS::Ace::ThemeConstants> GetThemeConstants(
    const std::optional<std::string>& bundleName = std::nullopt,
    const std::optional<std::string>& moduleName = std::nullopt);
OHOS::Ace::RefPtr<OHOS::Ace::ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info);
void ReplaceHolder(std::string& originStr, const std::vector<std::string>& params, uint32_t containCount);
std::string DimensionToString(OHOS::Ace::Dimension dimension);
bool ParseString(const ResourceInfo& info, std::string& result);
bool ParseAniColor(ani_env *env, ani_ref resourceColor_ref, OHOS::Ace::Color& resourceColor);
bool ParseResourceColor(ani_env *env, ani_ref resourceColor_ref, OHOS::Ace::Color& resourceColor);
bool ParseColorMapToColor(PromptActionColor colorenum, OHOS::Ace::Color& Color);
bool ParseLengthToDimension(ani_env *env, ani_ref dy_ref, OHOS::Ace::DimensionUnit defaultUnit,
                            OHOS::Ace::CalcDimension& result);
bool GetShadowFromTheme(OHOS::Ace::ShadowStyle shadowStyle, OHOS::Ace::Shadow& shadow);
bool GetToastObjectShadow(ani_env *env, ani_object objects, OHOS::Ace::Shadow& shadow);
bool ParseShadowOptionsFill(ani_env *env, ani_object objects, bool& isFilled);
bool ParseShadowOptionsOffsetX(ani_env *env, ani_object objects, double& offset);
bool ParseShadowOptionsOffsetY(ani_env *env, ani_object objects, double& offset);
bool ParseShadowOptionsOffset(ani_env *env, ani_ref offset_ref, double& offset);
bool ParseShadowColorStrategy(ani_env *env, ani_ref resourceColor_ref, OHOS::Ace::ShadowColorStrategy& strategy);
bool ParseShadowOptionsColor(ani_env *env, ani_object objects, OHOS::Ace::Shadow& shadowProps);
bool ParseShadowOptionsType(ani_env *env, ani_object objects, int32_t& shadowType);
bool ParseShadowOptionsRadius(ani_env *env, ani_object object, double& result);
bool ParseRadiusNumberToDouble(ani_env *env, ani_object resource_object, double& result);
bool ParseRadiusResourceToDouble(ani_env *env, ani_object resource_object, double& result);
bool ParseResource(const ResourceInfo resource, OHOS::Ace::CalcDimension& result);
bool GetIsResourceObject(ani_env *env, ani_ref object_ref);
bool GetIsStringObject(ani_env *env, ani_ref object_ref);
bool GetIsNumberObject(ani_env *env, ani_ref object_ref);
bool GetIsArrayObject(ani_env *env, ani_ref object_ref);
bool GetIsShadowOptionsObject(ani_env *env, ani_ref object_ref);
bool GetIsShowToastOptionsObject(ani_env *env, ani_object object);
bool GetIsBlurStyleEnum(ani_env *env, ani_ref object_ref);
bool GetIsToastShowModeEnum(ani_env *env, ani_ref object_ref);
bool GetIsShadowStyleEnum(ani_env *env, ani_ref object_ref);
bool GetIsAlignmentEnum(ani_env *env, ani_ref object_ref);
bool GetIsShadowTypeEnum(ani_env *env, ani_ref object_ref);
bool GetIsColoringStrategyEnum(ani_env *env, ani_ref object_ref);
bool GetIsColorEnum(ani_env *env, ani_ref object_ref);
bool GetIsHoverModeAreaEnum(ani_env *env, ani_ref object_ref);
bool GetIsUndefinedObject(ani_env *env, ani_ref object_ref);
#endif