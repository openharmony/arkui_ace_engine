/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_NAPI_KITS_UTILS_H
#define FOUNDATION_ACE_INTERFACES_NAPI_KITS_UTILS_H

#include <chrono>
#include <cmath>
#include <cstdint>
#include <regex>
#include <vector>

#include "native_engine/native_value.h"

#include "base/log/log.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "securec.h"

namespace OHOS::Ace::Napi {

struct ResourceInfo {
    int32_t resId = 0;
    int32_t type = 0;
    std::vector<std::string> params;
    std::optional<std::string> bundleName = std::nullopt;
    std::optional<std::string> moduleName = std::nullopt;
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

enum class ResourceStruct { CONSTANT, DYNAMIC_V1, DYNAMIC_V2 };

size_t GetParamLen(napi_env env, napi_value param);

bool GetNapiString(napi_env env, napi_value value, std::string& retStr, napi_valuetype& valueType);

bool NapiStringToString(napi_env env, napi_value value, std::string& retStr);

void NapiThrow(napi_env env, const std::string& message, int32_t errCode);

napi_value ParseCurve(napi_env env, napi_value value, std::string& curveTypeString, std::vector<float>& curveValue);

napi_value CreateNapiString(napi_env env, const std::string& rawStr);

ResourceStruct CheckResourceStruct(napi_env env, napi_value value);

void CompleteResourceParam(napi_env env, napi_value value);

void CompleteResourceParamV1(napi_env env, napi_value value);

void CompleteResourceParamV2(napi_env env, napi_value value);

void ModifyResourceParam(napi_env env, napi_value value, const ResourceType& resType, const std::string& resName);

bool ConvertResourceType(const std::string& typeName, ResourceType& resType);

void PreFixEmptyBundleName(napi_env env, napi_value value);

bool ParseDollarResource(
    napi_env env, napi_value value, ResourceType& resType, std::string& resName, std::string& moduleName);

void ParseCurveInfo(const std::string& curveString, std::string& curveTypeString, std::vector<float>& curveValue);

bool ParseColor(napi_env env, napi_value value, Color& info);

bool ParseResourceParam(napi_env env, napi_value value, ResourceInfo& info);

bool ParseString(const ResourceInfo& info, std::string& result);

std::string ErrorToMessage(int32_t code);

bool GetSingleParam(napi_env env, napi_callback_info info, napi_value* argv, napi_valuetype& valueType);

std::optional<Color> GetOptionalColor(napi_env env, napi_value argv, napi_valuetype& valueType);

napi_valuetype GetValueType(napi_env env, napi_value value);
RefPtr<ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info);
std::optional<std::string> GetStringFromValueUtf8(napi_env env, napi_value value);
bool ParseIntegerToString(const ResourceInfo& info, std::string& result);
bool ParseColorFromResourceObject(napi_env env, napi_value value, Color& colorResult);

napi_value GetReturnObject(napi_env env, std::string callbackString);
bool HasProperty(napi_env env, napi_value value, const std::string& targetStr);
bool ParseNapiDimension(napi_env env, CalcDimension& result, napi_value napiValue, DimensionUnit defaultUnit);
bool ParseNapiDimensionNG(
    napi_env env, CalcDimension& result, napi_value napiValue, DimensionUnit defaultUnit, bool isSupportPercent);
bool ParseNapiColor(napi_env env, napi_value value, Color& result);
bool ParseStyle(napi_env env, napi_value value, std::optional<BorderStyle>& style);
bool ParseShadowColorStrategy(napi_env env, napi_value value, ShadowColorStrategy& strategy);
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_NAPI_KITS_UTILS_H
