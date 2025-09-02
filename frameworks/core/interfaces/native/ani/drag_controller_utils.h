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
#ifndef INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_CONTROLLER_UTILS_H
#define INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_CONTROLLER_UTILS_H

#include "core/common/resource/resource_wrapper.h"
#include "core/common/resource/resource_manager.h"
#include "base/log/log.h"
#include "bridge/common/utils/utils.h"
namespace OHOS::Ace::Ani {
enum DragForegroundColor {
    DRAG_FOREGROUND_COLOR_WHITE,
    DRAG_FOREGROUND_COLOR_BLACK,
    DRAG_FOREGROUND_COLOR_BLUE,
    DRAG_FOREGROUND_COLOR_BROWN,
    DRAG_FOREGROUND_COLOR_GRAY,
    DRAG_FOREGROUND_COLOR_GREEN,
    DRAG_FOREGROUND_COLOR_GREY,
    DRAG_FOREGROUND_COLOR_ORANGE,
    DRAG_FOREGROUND_COLOR_PINK,
    DRAG_FOREGROUND_COLOR_RED,
    DRAG_FOREGROUND_COLOR_YELLOW,
    DRAG_FOREGROUND_COLOR_TRANSPARENT
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

ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code);
void AniThrow(ani_env* env, const std::string& errMsg, int32_t code);
bool IsUndefinedObject(ani_env* env, ani_ref objectRef);
std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str);
bool IsFunctionObject(ani_env* env, ani_ref obj);
bool IsBigIntObject(ani_env* env, ani_ref obj);
bool IsFunctionObjectWith2Param(ani_env* env, ani_ref obj);
bool IsNumberObject(ani_env* env, ani_ref obj);
bool IsInt32Object(ani_env* env, ani_ref obj);
bool IsStringObject(ani_env* env, ani_ref obj);
bool IsArrayObject(ani_env* env, ani_ref obj);
bool IsBooleanObject(ani_env* env, ani_ref obj);
bool IsColorEnum(ani_env *env, ani_ref objectRef);
bool GetBigIntValue(ani_env* env, ani_object object, int64_t& longValue);
bool GetEnumItem([[maybe_unused]] ani_env* env, ani_size index, const char* enumName, ani_enum_item& enumItem);
bool IsDragPreviewModeEnum(ani_env *env, ani_ref obj);
bool IsResourceObject(ani_env *env, ani_ref object_ref);
bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
bool ParseDollarResource(
    ani_env *env, ani_object params_ref, ResourceType& resType, std::string& resName, std::string& moduleName);
bool ParseResourceParamId(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamBundleName(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamModuleName(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamType(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParamName(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseResourceParam(ani_env *env, ani_object objects, ResourceInfo& info);
bool ParseString(const ResourceInfo& info, std::string& result);
bool ParseAniColor(ani_env *env, ani_ref resourceColorRef, OHOS::Ace::Color& resourceColor);
bool ParseColorMapToColor(DragForegroundColor colorenum, OHOS::Ace::Color& color);
bool ParseResourceColor(ani_env *env, ani_ref resourceColorRef, OHOS::Ace::Color& resourceColor);
void AniThrow(ani_env *env, const std::string &errMsg, int32_t code);
void processResourceType(ani_env *env, ani_object value, ani_ref params_ref, size_t length, std::string resName);
void ModifyResourceParam(ani_env *env, ani_object value, const ResourceType& resType, const std::string& resName);
void CompleteResourceParamV1(ani_env *env, ani_object value);
void CompleteResourceParamV2(ani_env *env, ani_object value);
void CompleteResourceParam(ani_env *env, ani_object value);
void ReplaceHolder(std::string& originStr, const std::vector<std::string>& params, uint32_t containCount);
void PreFixEmptyBundleName(ani_env *env, ani_object value);
void ParseCurveInfo(const std::string& curveString, std::string& curveTypeString, std::vector<float>& curveValue);
void ParseCurve(ani_env* env, ani_object object, std::string& curveTypeString, std::vector<float>& curveValue);
ResourceStruct CheckResourceStruct(ani_env *env, ani_object value);
OHOS::Ace::RefPtr<OHOS::Ace::ThemeConstants> GetThemeConstants(
    const std::optional<std::string>& bundleName, const std::optional<std::string>& moduleName);
OHOS::Ace::RefPtr<OHOS::Ace::ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info);
} // namespace OHOS::Ace::NG
#endif // INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_CONTROLLER_UTILS_H