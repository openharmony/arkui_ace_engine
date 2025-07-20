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

#include "resource_module.h"

#include <cstdint>

#include "ani.h"
#include "load.h"
#include "log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
} // namespace
bool ResourceModule::ParseAniColor(ani_env* env, ani_object aniValue, uint32_t& color)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }

    auto aniObj = static_cast<ani_object>(aniValue);
    if (AniUtils::IsString(env, aniObj)) {
        auto srcString = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(aniValue));
        return modifier->getColorModifier()->parseColorString(srcString, color);
        return true;
    }

    if (AniUtils::IsNumber(env, aniObj)) {
        ani_status status;
        ani_double doubleSrc;
        if ((status = env->Object_CallMethodByName_Double(aniValue, "unboxed", ":d", &doubleSrc)) != ANI_OK) {
            HILOGW("GetColorValue unboxed double failed. %{public}d", status);
            return false;
        }
        color = ColorAlphaAdapt(static_cast<uint32_t>(doubleSrc));
        return true;
    }

    if (IsResource(env, aniObj)) {
        int32_t resId = -1;
        int32_t resType = -1;
        std::string bundleName;
        std::string moduleName;
        ParseAniResource(env, aniObj, resId, resType, bundleName, moduleName);

        color = modifier->getResourceModifier()->getColorById(resId, resType, bundleName, moduleName);
        return true;
    }
    return false;
}

bool ResourceModule::IsResource(ani_env* env, ani_object obj)
{
    ani_status status;
    ani_class resourceClass;
    if ((status = env->FindClass("Lglobal/resource/Resource;", &resourceClass)) != ANI_OK) {
        HILOGW("IsResource find Resource failed. %{public}d", status);
        return false;
    }
    ani_boolean isResource;
    if ((status = env->Object_InstanceOf(obj, resourceClass, &isResource)) != ANI_OK) {
        HILOGW("IsResource call instanceof Resource failed. %{public}d", status);
        return false;
    }
    return isResource;
}

void ResourceModule::ParseAniResource(ani_env* env, ani_object aniValue, int32_t& resId, int32_t& resType,
    std::string& resBundleName, std::string& resModuleName)
{
    ani_double id;
    env->Object_GetPropertyByName_Double(aniValue, "id", &id);
    resId = static_cast<int32_t>(id);

    ani_double type;
    env->Object_GetPropertyByName_Double(aniValue, "type", &type);
    resType = static_cast<int32_t>(type);

    ani_ref bundleName;
    env->Object_GetPropertyByName_Ref(aniValue, "bundleName", &bundleName);
    resBundleName = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(bundleName));

    ani_ref moduleName;
    env->Object_GetPropertyByName_Ref(aniValue, "moduleName", &moduleName);
    resModuleName = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(moduleName));
}

bool ResourceModule::HandleThemeColorsArg(ani_env* env, ani_array colorsArg, std::vector<uint32_t>& colors)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    auto aniThemeModifier = modifier->getAniThemeModifier();
    int32_t tokenColorsSize = aniThemeModifier->getTokenColorsSize();

    ani_size length;
    env->Array_GetLength(colorsArg, &length);
    if (length < tokenColorsSize) {
        HILOGW("colorArray incorrect in SetDefaultTheme");
    }
    std::vector<uint32_t> basisColors;
    modifier->getAniThemeModifier()->obtainDefaultColors(basisColors);
    if (basisColors.empty()) {
        modifier->getAniThemeModifier()->obtainSystemColors(basisColors);
    }
    if (basisColors.empty()) {
        return false;
    }

    for (int32_t i = 0; i < tokenColorsSize; i++) {
        // type ResourceColor = number | string | Resource
        ani_ref value;
        auto status = env->Array_Get(colorsArg, i, &value);
        if (status != ANI_OK) {
            HILOGW("SetDefaultTheme colorArray get index: %{public}d failed", i);
            continue;
        }
        uint32_t color = 0;
        RefPtr<ResourceObject> resObj;
        bool isColorAvailable = false;
        if (!ResourceModule::ParseAniColor(env, static_cast<ani_object>(value), color)) {
            if (i < basisColors.size()) {
                color = basisColors[i];
                isColorAvailable = true;
            }
        } else {
            isColorAvailable = true;
        }
        colors.push_back(color);
    }
    return true;
}
} // namespace OHOS::Ace::Ani
