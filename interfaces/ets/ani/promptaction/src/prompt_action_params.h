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

#ifndef INTERFACES_ETS_ANI_PROMPTACTION_SRC_PROMPT_ACTION_PARAMS_H
#define INTERFACES_ETS_ANI_PROMPTACTION_SRC_PROMPT_ACTION_PARAMS_H

#include <ani.h>
#include <cmath>
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <optional>

#include "core/common/container.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/shadow_theme.h"
#include "core/common/resource/resource_manager.h"
#include "frameworks/base/log/log_wrapper.h"

struct PromptActionAsyncContext {
    ani_vm* vm = nullptr;
    ani_resolver deferred = nullptr;
    ani_fn_object callback = nullptr;
    int32_t instanceId = -1;
};

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

enum PromptActionBlurStyle {
    THIN = 0,
    REGULAR = 1,
    THICK = 2,
    BACKGROUND_THIN = 3,
    BACKGROUND_REGULAR = 4,
    BACKGROUND_THICK = 5,
    BACKGROUND_ULTRA_THICK = 6,
    NONE = 7,
    COMPONENT_ULTRA_THIN = 8,
    COMPONENT_THIN = 9,
    COMPONENT_REGULAR = 10,
    COMPONENT_THICK = 11,
    COMPONENT_ULTRA_THICK = 12
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
constexpr int32_t PLURAL_HOLDER_INDEX = 2;
constexpr int32_t DOLLAR_TOKENS_SIZE = 3;
constexpr int32_t MAYBE_MODULE_NAME_SIZE = 3;

// Get ANI base params
ani_object CreateANIIntObject(ani_env *env, int32_t intValue);
ani_object CreateANILongObject(ani_env *env, int64_t longValue);
ani_object CreateANIDoubleObject(ani_env *env, double doubleValue);
bool IsUndefinedObject(ani_env *env, ani_ref objectRef);
bool IsClassObject(ani_env *env, ani_object object, const char *class_descriptor);
bool IsArrayObject(ani_env *env, ani_object object);
bool IsArrayObject(ani_env *env, ani_ref ref);
bool IsEnum(ani_env *env, ani_object object, const char *enum_descriptor);
bool GetBoolParam(ani_env* env, ani_ref ref, bool& result);
bool GetBoolParam(ani_env* env, ani_object object, const char *name, bool& result);
bool GetInt32Param(ani_env* env, ani_ref ref, int32_t& result);
bool GetInt32Param(ani_env* env, ani_object object, const char *name, int32_t& result);
bool GetInt64Param(ani_env* env, ani_ref ref, int64_t& result);
bool GetInt64Param(ani_env* env, ani_object object, const char *name, int64_t& result);
bool GetDoubleParam(ani_env* env, ani_ref ref, double& result);
bool GetDoubleParam(ani_env* env, ani_object object, const char *name, double& result);
bool GetDoubleParamOpt(ani_env *env, ani_object object, const char *name, std::optional<double>& result);
std::string ANIStringToStdString(ani_env *env, ani_string ani_str);
bool GetStringParam(ani_env *env, ani_ref ref, std::string& result);
bool GetStringParam(ani_env *env, ani_object object, const char *name, std::string& result);
bool GetStringParamOpt(ani_env *env, ani_object object, const char *name, std::optional<std::string>& result);
bool GetStringArrayParam(ani_env *env, ani_object object, const char *name, std::vector<std::string>& result);
bool GetEnumInt(ani_env* env, ani_object resultObj, const char *enum_descriptor, int32_t& result);
bool GetEnumInt(ani_env* env, ani_object object, const char *name, const char *enum_descriptor, int32_t& result);
bool GetEnumIntOpt(ani_env* env, ani_object object, const char *name, const char *enum_descriptor,
    std::optional<int32_t>& result);
bool GetEnumString(ani_env* env, ani_object resultObj, const char *enum_descriptor, std::string& result);
bool GetEnumString(ani_env* env, ani_object object, const char *name, const char *enum_descriptor,
    std::string& result);
bool GetEnumStringOpt(ani_env* env, ani_object object, const char *name, const char *enum_descriptor,
    std::optional<std::string>& result);
bool GetFunctionParam(ani_env *env, ani_ref ref, std::function<void()>& result);
bool GetFunctionParam(ani_env *env, ani_object object, const char *name, std::function<void()>& result);

// Get promptAction params
void PrefixEmptyBundleName(ani_env *env, ani_object object);
ResourceStruct CheckResourceStruct(ani_env *env, ani_object object);
bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
bool GetDollarResource(ani_env *env, ani_object object, ResourceType& resType, std::string& resName,
    std::string& moduleName);
void ProcessResourceType(ani_env *env, ani_object value, ani_ref paramsRef, size_t length, std::string resName);
void ModifyResourceParam(ani_env *env, ani_object object, const ResourceType& resType, const std::string& resName);
void CompleteResourceParamV1(ani_env *env, ani_object object);
void CompleteResourceParamV2(ani_env *env, ani_object object);
void CompleteResourceParam(ani_env *env, ani_object object);
bool GetResourceParam(ani_env *env, ani_object object, ResourceInfo& result);
OHOS::Ace::RefPtr<OHOS::Ace::ResourceWrapper> CreateResourceWrapper(const ResourceInfo& result);
void ReplaceHolder(std::string& originStr, const std::vector<std::string>& params, uint32_t containCount);
std::string DimensionToString(OHOS::Ace::Dimension dimension);
bool ResourceToString(const ResourceInfo resourceInfo, std::string& result);
bool GetResourceStrParam(ani_env *env, ani_object object, std::string& result);
bool GetResourceStrParam(ani_env *env, ani_object object, const char *name, std::string& result);
bool GetLengthParam(ani_env *env, ani_ref ref, OHOS::Ace::CalcDimension& result);
bool GetLengthParam(ani_env *env, ani_object object, const char *name, OHOS::Ace::CalcDimension& result);
bool GetColorParam(ani_env* env, ani_object object, PromptActionColor& result);
bool GetResourceColorParam(ani_env *env, ani_ref ref, OHOS::Ace::Color& result);
bool GetResourceColorParam(ani_env* env, ani_object object, const char *name, OHOS::Ace::Color& result);
bool GetResourceColorParamOpt(ani_env* env, ani_object object, const char *name,
    std::optional<OHOS::Ace::Color>& result);
bool GetShadowStyleParam(ani_env *env, ani_object object, OHOS::Ace::Shadow& shadow);
bool GetRadiusNumberToDouble(ani_env *env, ani_object object, double& result);
bool ResourceToDimension(const ResourceInfo resource, OHOS::Ace::CalcDimension& result);
bool GetRadiusResourceToDouble(ani_env *env, ani_object object, double& result);
bool GetShadowOptionsRadiusParam(ani_env *env, ani_object object, double& result);
bool GetShadowOptionsType(ani_env *env, ani_object object, int32_t& result);
bool GetShadowColorStrategy(ani_env *env, ani_object object, OHOS::Ace::ShadowColorStrategy& result);
bool GetShadowColorStrategy(ani_env *env, ani_ref ref, OHOS::Ace::ShadowColorStrategy& result);
bool GetShadowOptionsColor(ani_env *env, ani_object object, OHOS::Ace::Shadow& result);
bool GetShadowOptionsOffset(ani_env *env, ani_ref ref, double& result);
bool GetShadowOptionsOffset(ani_env *env, ani_object object, const char *name, double& result);
bool GetShadowOptionsParam(ani_env *env, ani_object object, OHOS::Ace::Shadow& result);
bool GetShadowParam(ani_env *env, ani_object object, OHOS::Ace::Shadow& result);
bool GetShadowParamOpt(ani_env *env, ani_object object, std::optional<OHOS::Ace::Shadow>& result);
bool ResourceIntegerToString(const ResourceInfo& resourceInfo, std::string& result);
bool GetDimensionParam(ani_env* env, ani_ref ref, OHOS::Ace::CalcDimension& result);
bool GetDimensionParam(ani_env* env, ani_object object, const char *name, OHOS::Ace::CalcDimension& result);
bool GetDimensionParamOpt(ani_env* env, ani_object object, const char *name,
    std::optional<OHOS::Ace::CalcDimension>& result);
void CheckDimension(OHOS::Ace::CalcDimension value);
bool GetBackgroundBlurStyleParam(ani_env* env, ani_object object, int32_t& result);
bool GetBackgroundBlurStyleParamOpt(ani_env* env, ani_object object, std::optional<int32_t>& result);
bool GetHoverModeAreaParam(ani_env* env, ani_object object, OHOS::Ace::HoverModeAreaType& result);
bool GetHoverModeAreaParamOpt(ani_env* env, ani_object object, std::optional<OHOS::Ace::HoverModeAreaType>& result);
bool GetOffsetParam(ani_env *env, ani_object object, OHOS::Ace::DimensionOffset& result);
bool GetOffsetParamOpt(ani_env *env, ani_object object, std::optional<OHOS::Ace::DimensionOffset>& result);

#endif // INTERFACES_ETS_ANI_PROMPTACTION_SRC_PROMPT_ACTION_PARAMS_H
