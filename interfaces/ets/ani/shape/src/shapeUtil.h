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

#ifndef OHOS_ANI_ACE_SHAPE_UTIL_H
#define OHOS_ANI_ACE_SHAPE_UTIL_H

#include <ani.h>
#include <array>
#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/shadow_theme.h"
#include "frameworks/base/log/log_wrapper.h"

enum RADIUS { TOP_LEFT_RADIUS = 0, TOP_RIGHT_RADIUS = 1, BOTTOM_RIGHT_RADIUS = 2, BOTTOM_LEFT_RADIUS = 3 };
enum ResColor {
    RES_COLOR_WHITE,
    RES_COLOR_BLACK,
    RES_COLOR_BLUE,
    RES_COLOR_BROWN,
    RES_COLOR_GRAY,
    RES_COLOR_GREEN,
    RES_COLOR_GREY,
    RES_COLOR_ORANGE,
    RES_COLOR_PINK,
    RES_COLOR_RED,
    RES_COLOR_YELLOW,
    RES_COLOR_TRANSPARENT
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

bool GetIsStringObject(ani_env* env, ani_ref object_ref);
bool GetIsNumberObject(ani_env* env, ani_ref object_ref);
bool GetIsUndefinedObject(ani_env* env, ani_ref object_ref);
bool GetIsResourceObject(ani_env* env, ani_ref object_ref);
bool GetIsArrayObject(ani_env* env, ani_ref object_ref);
ResourceStruct CheckResourceStruct(ani_env* env, ani_object value);
bool ParseResourceParamId(ani_env* env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamBundleName(ani_env* env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamModuleName(ani_env* env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamType(ani_env* env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamName(ani_env* env, ani_object objects, ResourceInfo& info);
bool ParseResourceParam(ani_env* env, ani_object options, ResourceInfo& info);
bool ParseStringAndNumberOption(ani_env* env, ani_object options,
    OHOS::Ace::CalcDimension& result, const char* property, const char* className);
bool IsInstanceOfCls(ani_env* env, [[maybe_unused]] ani_object object, const char* className);
bool ParseLengthToDimension(
    ani_env* env, ani_ref source_ref, OHOS::Ace::DimensionUnit defaultUnit, OHOS::Ace::CalcDimension& result);
bool ParseLength(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_ref aniOption,
    OHOS::Ace::CalcDimension& lengthInput);
void PreFixEmptyBundleName(ani_env* env, ani_object value);
void processResourceType(ani_env* env, ani_object value, ani_ref params_ref, size_t length);
void ModifyResourceParam(ani_env* env, ani_object value, const ResourceType& resType, const std::string& resName);
void CompleteResourceParamV1(ani_env* env, ani_object value);
void CompleteResourceParamV2(ani_env* env, ani_object value);
bool ParseDollarResource(
    ani_env* env, ani_object params_ref, ResourceType& resType, std::string& resName, std::string& moduleName);
bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
ResourceStruct CheckResourceStruct(ani_env* env, ani_object value);
std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str);
void ReplaceHolder(std::string& originStr, const std::vector<std::string>& params, uint32_t containCount);
bool ParseString(const ResourceInfo& info, std::string& result);
OHOS::Ace::RefPtr<OHOS::Ace::ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info);
OHOS::Ace::RefPtr<OHOS::Ace::ThemeConstants> GetThemeConstants(
    const std::optional<std::string>& bundleName, const std::optional<std::string>& moduleName);
std::string DimensionToString(OHOS::Ace::Dimension dimension);
void ModifyResourceParam(ani_env* env, ani_object value, const ResourceType& resType, const std::string& resName);
void processResourceType(ani_env* env, ani_object value, ani_ref params_ref, size_t length, std::string resName);
bool ParseAniColor(ani_env* env, ani_ref resourceColor_ref, OHOS::Ace::Color& resourceColor);
bool ParseResourceColor(ani_env* env, ani_ref resourceColor_ref, OHOS::Ace::Color& resourceColor);
bool ParseColorMapToColor(ResColor colorenum, OHOS::Ace::Color& Color);
bool GetIsColorEnum(ani_env* env, ani_ref object_ref);
bool ParseOption(
    ani_env* env, ani_object options, OHOS::Ace::CalcDimension& input, const char* property, const char* className);
std::string ParseCommands(ani_env* env, ani_object aniOption);
void ParseArray([[maybe_unused]] ani_env* env,
    const OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect>& shapeRect, ani_object options);
void SetRadiusValue(const OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect>& shapeRect,
    const OHOS::Ace::CalcDimension& radius, int32_t index);
bool ParseStringAndNumberObject(ani_env* env, ani_ref property_ref,
    OHOS::Ace::DimensionUnit defaultUnit, OHOS::Ace::CalcDimension& result);
#endif
