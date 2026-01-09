/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "list/list_item_group_module.h"

#include <memory>

#include "base/utils/utils.h"
#include "load.h"
#include "base/log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
void ParseStringToDimension(const std::string& str, ArkUIListItemGroupSpace* result)
{
    char* suffixPtr = nullptr;
    float value = std::strtof(str.c_str(), &suffixPtr);

    if (!suffixPtr || suffixPtr == str.c_str()) {
        // not a numeric value
        result->unit = -1;
        return;
    }
    result->value = value;
    if (suffixPtr[0] == '\0' || (suffixPtr[0] == 'v' && suffixPtr[1] == 'p')) {
        // 1: DimensionUnit::VP
        result->unit = 1;
    } else if (suffixPtr[0] == '%') {
        // 3: DimensionUnit::PERCENT
        result->unit = 3;
    } else if (suffixPtr[0] == 'p' && suffixPtr[1] == 'x') {
        // 0: DimensionUnit::PX
        result->unit = 0;
    } else if (suffixPtr[0] == 'l' && suffixPtr[1] == 'p' && suffixPtr[2] == 'x') { // 2: cursor of arr
        // 4: DimensionUnit::LPX
        result->unit = 4;
    } else if (suffixPtr[0] == 'f' && suffixPtr[1] == 'p') {
        // 2: DimensionUnit::FP
        result->unit = 2;
    } else {
        // -1: DimensionUnit::NONE
        result->unit = -1;
    }
}

ArkUIListItemGroupSpace ParseDimension(ani_env *env, ani_object dimensionObj)
{
    ArkUIListItemGroupSpace res;
    ani_class doubleClass;
    if (env->FindClass("std.core.Double", &doubleClass) != ANI_OK) {
        return res;
    }
    ani_class stringClass;
    if (env->FindClass("std.core.String", &stringClass) != ANI_OK) {
        return res;
    }

    ani_boolean isDouble;
    env->Object_InstanceOf(dimensionObj, doubleClass, &isDouble);
    if (isDouble) {
        ani_double dimension;
        env->Object_CallMethodByName_Double(dimensionObj, "toDouble", ":d", &dimension);
        if (dimension < 0) {
            dimension = 0;
        }
        res.value = dimension;
        return res;
    }

    ani_boolean isString;
    env->Object_InstanceOf(dimensionObj, stringClass, &isString);
    if (isString) {
        auto stringDimension = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(dimensionObj));
        ParseStringToDimension(stringDimension, &res);
        if (res.value < 0) {
            res.value = 0.0f;
        }
    }
    return res;
}

void SetListItemGroupFooterContent(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long footerPtr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    auto* footerNode = reinterpret_cast<ArkUINodeHandle>(footerPtr);
    if (!modifier || !arkNode || !footerNode) {
        return;
    }
    modifier->getArkUIAniListItemGroupModifier()->setListItemGroupFooterContent(arkNode, footerNode);
}

void SetListItemGroupFooter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long footerPtr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    auto* footerNode = reinterpret_cast<ArkUINodeHandle>(footerPtr);
    if (!modifier || !arkNode || !footerNode) {
        return;
    }
    modifier->getArkUIAniListItemGroupModifier()->setListItemGroupFooter(arkNode, footerNode);
}

void ResetListItemGroupFooter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    modifier->getArkUIAniListItemGroupModifier()->resetListItemGroupFooter(arkNode);
}

void SetListItemGroupHeaderContent(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long headerPtr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    auto* headerNode = reinterpret_cast<ArkUINodeHandle>(headerPtr);
    if (!modifier || !arkNode || !headerNode) {
        return;
    }
    modifier->getArkUIAniListItemGroupModifier()->setListItemGroupHeaderContent(arkNode, headerNode);
}

void SetListItemGroupHeader(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long headerPtr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    auto* headerNode = reinterpret_cast<ArkUINodeHandle>(headerPtr);
    if (!modifier || !arkNode || !headerNode) {
        return;
    }
    modifier->getArkUIAniListItemGroupModifier()->setListItemGroupHeader(arkNode, headerNode);
}

void ResetListItemGroupHeader(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    modifier->getArkUIAniListItemGroupModifier()->resetListItemGroupHeader(arkNode);
}

void SetListItemGroupStyle(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int style)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    modifier->getArkUIAniListItemGroupModifier()->setListItemGroupStyle(arkNode, static_cast<int32_t>(style));
}

void SetListItemGroupSpace(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object space)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto spaceValue = ParseDimension(env, space);
    modifier->getArkUIAniListItemGroupModifier()->setListItemGroupSpace(arkNode, spaceValue);
}
} // namespace OHOS::Ace::Ani
