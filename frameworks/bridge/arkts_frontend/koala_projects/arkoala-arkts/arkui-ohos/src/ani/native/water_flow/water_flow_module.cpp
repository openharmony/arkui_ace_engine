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

#include "water_flow_module.h"

#include <memory>

#include "load.h"
#include "utils/ani_utils.h"
#include "water_flow_module.h"

#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Ani {
void ParseStringToDimension(const std::string& str, ArkUIWaterFlowSectionGap* result)
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
        // DimensionUnit::VP
        result->unit = 1;
    } else if (suffixPtr[0] == '%') {
        // DimensionUnit::PERCENT
        result->unit = 3;
    } else if (suffixPtr[0] == 'p' && suffixPtr[1] == 'x') {
        // DimensionUnit::PX
        result->unit = 0;
    } else if (suffixPtr[0] == 'l' && suffixPtr[1] == 'p' && suffixPtr[2] == 'x') {
        // DimensionUnit::LPX
        result->unit = 4;
    } else if (suffixPtr[0] == 'f' && suffixPtr[1] == 'p') {
        // DimensionUnit::FP
        result->unit = 2;
    } else {
        // DimensionUnit::NONE
        result->unit = -1;
    }
}

ArkUIWaterFlowSectionGap ParseDimension(ani_env *env, ani_ref dimensionRef)
{
    ArkUIWaterFlowSectionGap res;
    ani_class doubleClass;
    if (env->FindClass("std.core.Double", &doubleClass) != ANI_OK) {
        return res;
    }
    ani_class stringClass;
    if (env->FindClass("std.core.String", &stringClass) != ANI_OK) {
        return res;
    }

    ani_boolean isDouble;
    env->Object_InstanceOf(static_cast<ani_object>(dimensionRef), doubleClass, &isDouble);
    if (isDouble) {
        ani_double dimension;
        env->Object_CallMethodByName_Double(static_cast<ani_object>(dimensionRef), "unboxed", ":d", &dimension);
        if (dimension < 0) {
            dimension = 0;
        }
        res.value = dimension;
        return res;
    }

    ani_boolean isString;
    env->Object_InstanceOf(static_cast<ani_object>(dimensionRef), stringClass, &isString);
    if (isString) {
        auto stringDimension = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(dimensionRef));
        ParseStringToDimension(stringDimension, &res);
        if (res.value < 0) {
            res.value = 0.0f;
        }
    }
    return res;
}

ArkUIWaterFlowSectionPadding ParsePadding(ani_env* env, ani_ref paddingRef)
{
    ArkUIWaterFlowSectionPadding res;

    ani_ref leftRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "left", &leftRef);
    res.left = ParseDimension(env, leftRef);

    ani_ref rightRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "right", &rightRef);
    res.right = ParseDimension(env, rightRef);

    ani_ref topRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "top", &topRef);
    res.top = ParseDimension(env, topRef);

    ani_ref bottomRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "bottom", &bottomRef);
    res.bottom = ParseDimension(env, bottomRef);

    return res;
}

ArkUIWaterFlowSectionPadding ParseMargin(ani_env* env, ani_ref marginRef)
{
    ArkUIWaterFlowSectionPadding res;
    ani_class paddingClass;
    if (env->FindClass("arkui.component.units.Padding", &paddingClass) != ANI_OK) {
        return res;
    }

    ani_boolean isPadding;
    env->Object_InstanceOf(static_cast<ani_object>(marginRef), paddingClass, &isPadding);
    if (isPadding) {
        res = ParsePadding(env, marginRef);
    } else {
        ArkUIWaterFlowSectionGap length = ParseDimension(env, marginRef);
        res.left = length;
        res.right = length;
        res.top = length;
        res.bottom = length;
    }
    return res;
}

ArkUIWaterFlowSection ParseSectionOptions(ani_env* env, ani_ref section)
{
    ArkUIWaterFlowSection curSection;
    ani_int itemsCount;
    if (env->Object_GetPropertyByName_Int(static_cast<ani_object>(section), "itemsCount", &itemsCount) != ANI_OK) {
        return curSection;
    }
    curSection.itemsCount = itemsCount;

    ani_ref crossCount;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "crossCount", &crossCount) != ANI_OK) {
        curSection.crossCount = 1;
    }
    ani_boolean isUndefined = false;
    if (env->Reference_IsUndefined(crossCount, &isUndefined) != ANI_OK) {
        curSection.crossCount = 1;
    }
    if (!isUndefined) {
        ani_double crossCnt;
        env->Object_CallMethodByName_Double(static_cast<ani_object>(crossCount), "unboxed", ":d", &crossCnt);
        if (crossCnt <= 0) {
            crossCnt = 1;
        }
        curSection.crossCount = static_cast<int32_t>(crossCnt);
    }

    ani_ref columnsGap;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "columnsGap", &columnsGap);
    isUndefined = false;
    env->Reference_IsUndefined(columnsGap, &isUndefined);
    if (!isUndefined) {
        curSection.columnsGap = ParseDimension(env, columnsGap);
    }

    ani_ref rowsGap;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "rowsGap", &rowsGap);
    isUndefined = false;
    env->Reference_IsUndefined(rowsGap, &isUndefined);
    if (!isUndefined) {
        curSection.rowsGap = ParseDimension(env, rowsGap);
    }

    ani_ref margin;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "margin", &margin);
    isUndefined = false;
    env->Reference_IsUndefined(margin, &isUndefined);
    if (!isUndefined) {
        curSection.margin = ParseMargin(env, margin);
    }

    ani_ref func;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "onGetItemMainSizeByIndex", &func);
    isUndefined = false;
    ani_boolean isGetItemMainSizeByIndex = ANI_FALSE;
    env->Reference_IsUndefined(func, &isUndefined);
    if (!isUndefined) {
        ani_class ClassGetItemMainSizeByIndex;
        env->FindClass("std.core.Function1", &ClassGetItemMainSizeByIndex);
        env->Object_InstanceOf(static_cast<ani_object>(func), ClassGetItemMainSizeByIndex, &isGetItemMainSizeByIndex);
    }

    if (isGetItemMainSizeByIndex) {
        ani_vm* vm = nullptr;
        env->GetVM(&vm);

        ani_ref fnObjGlobalRef = nullptr;
        env->GlobalReference_Create(func, &fnObjGlobalRef);

        auto onGetItemMainSizeByIndex = [fnObjGlobalRef, vm](int32_t index) {
            ani_env* env = nullptr;
            ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
            if (status != ANI_OK || !env) {
                return 0.0f;
            }

            ani_ref aniRes;
            ani_ref aniIndex = AniUtils::CreateInt32(env, index);

            env->FunctionalObject_Call(static_cast<ani_fn_object>(fnObjGlobalRef), 1, &aniIndex, &aniRes);
            ani_double res;
            env->Object_CallMethodByName_Double(static_cast<ani_object>(aniRes), "unboxed", ":d", &res);
            return static_cast<float>(res);
        };
        curSection.onGetItemMainSizeByIndex = std::move(onGetItemMainSizeByIndex);
    }

    return curSection;
}

void SetWaterFlowSection(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object sections)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }

    ani_class waterflowSections;
    if (env->FindClass("arkui.component.waterFlow.WaterFlowSections", &waterflowSections) != ANI_OK) {
        return;
    }
    ani_boolean isSections;
    env->Object_InstanceOf(sections, waterflowSections, &isSections);
    if (!isSections) {
        return;
    }

    ani_ref changeArray;
    if (env->Object_GetPropertyByName_Ref(sections, "changeArray", &changeArray) != ANI_OK) {
        return;
    }
    ani_size changeArrayLength;
    if (env->Array_GetLength(static_cast<ani_array>(changeArray), &changeArrayLength) != ANI_OK) {
        return;
    }

    ani_class sectionChangeInfo;
    if (env->FindClass("arkui.component.waterFlow.SectionChangeInfo", &sectionChangeInfo) != ANI_OK) {
        return;
    }

    ani_class sectionOptions;
    if (env->FindClass("arkui.component.waterFlow.SectionOptions", &sectionOptions) != ANI_OK) {
        return;
    }

    int32_t changeLength = static_cast<int32_t>(changeArrayLength);
    for (int32_t i = 0; i < changeLength; i++) {
        ani_ref change;
        if (env->Array_Get(static_cast<ani_array>(changeArray), i, &change) != ANI_OK) {
            continue;
        }

        ani_boolean isSectionChangeInfo;
        env->Object_InstanceOf(static_cast<ani_object>(change), sectionChangeInfo, &isSectionChangeInfo);
        if (!isSectionChangeInfo) {
            continue;
        }

        ani_int start = 0;
        if (env->Object_GetPropertyByName_Int(static_cast<ani_object>(change), "start", &start) != ANI_OK) {
            continue;
        }
        ani_int deleteCount = 0;
        if (env->Object_GetPropertyByName_Int(static_cast<ani_object>(change), "deleteCount", &deleteCount) !=
            ANI_OK) {
            continue;
        }

        ani_ref sectionOptionsArray;
        env->Object_GetPropertyByName_Ref(static_cast<ani_object>(change), "sections", &sectionOptionsArray);

        ani_size aniLength;
        if (env->Array_GetLength(static_cast<ani_array>(sectionOptionsArray), &aniLength) != ANI_OK) {
            continue;
        }

        int32_t length = static_cast<int32_t>(aniLength);
        std::vector<ArkUIWaterFlowSection> newSections;
        for (int32_t j = 0; j < length; j++) {
            ani_ref section;
            if (env->Array_Get(static_cast<ani_array>(sectionOptionsArray), j, &section) != ANI_OK) {
                continue;
            }
            ani_boolean isSectionOptions;
            env->Object_InstanceOf(static_cast<ani_object>(section), sectionOptions, &isSectionOptions);
            if (!isSectionOptions) {
                continue;
            }
            ArkUIWaterFlowSection curSection = ParseSectionOptions(env, section);
            if (curSection.itemsCount < 0) {
                continue;
            }
            newSections.emplace_back(curSection);
        }
        modifier->getArkUIAniWaterFlowModifier()->setWaterFlowSection(
            arkNode, start, deleteCount, static_cast<void*>(newSections.data()), newSections.size());
    }
}

void SetWaterFlowFooterContent(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long footerPtr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    auto* footerNode = reinterpret_cast<ArkUINodeHandle>(footerPtr);
    if (!modifier || !arkNode || !footerNode) {
        return;
    }
    modifier->getArkUIAniWaterFlowModifier()->setWaterFlowFooterContent(arkNode, footerNode);
}

void SetWaterFlowFooter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long footerPtr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    auto* footerNode = reinterpret_cast<ArkUINodeHandle>(footerPtr);
    if (!modifier || !arkNode || !footerNode) {
        return;
    }
    modifier->getArkUIAniWaterFlowModifier()->setWaterFlowFooter(arkNode, footerNode);
}

void ResetWaterFlowFooter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    modifier->getArkUIAniWaterFlowModifier()->resetWaterFlowFooter(arkNode);
}

void SetWaterFlowScroller(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long scrollerPtr)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(arkNode);
    auto* scroller = reinterpret_cast<void*>(scrollerPtr);
    CHECK_NULL_VOID(scroller);

    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    modifier->getArkUIAniWaterFlowModifier()->setWaterFlowScroller(arkNode, scroller);
}

void SetWaterFlowLayoutMode(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int mode)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(arkNode);

    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    modifier->getArkUIAniWaterFlowModifier()->setWaterFlowLayoutMode(arkNode, static_cast<int32_t>(mode));
}

void UpdateWaterFlowSection(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object changeInfo)
{
    ani_int start = 0;
    if (env->Object_GetPropertyByName_Int(changeInfo, "start", &start) != ANI_OK) {
        return;
    }

    ani_int deleteCount = 0;
    if (env->Object_GetPropertyByName_Int(changeInfo, "deleteCount", &deleteCount) != ANI_OK) {
        return;
    }

    ani_ref sections;
    if (env->Object_GetPropertyByName_Ref(changeInfo, "sections", &sections) != ANI_OK) {
        return;
    }

    ani_size sectionsLength;
    if (env->Array_GetLength(static_cast<ani_array>(sections), &sectionsLength) != ANI_OK) {
        return;
    }

    ani_class sectionOptions;
    if (env->FindClass("arkui.component.waterFlow.SectionOptions", &sectionOptions) != ANI_OK) {
        return;
    }

    int32_t length = static_cast<int32_t>(sectionsLength);
    std::vector<ArkUIWaterFlowSection> newSections;
    for (int32_t j = 0; j < length; j++) {
        ani_ref section;
        if (env->Array_Get(static_cast<ani_array>(sections), j, &section) != ANI_OK) {
            continue;
        }
        ani_boolean isSectionOptions;
        env->Object_InstanceOf(static_cast<ani_object>(section), sectionOptions, &isSectionOptions);
        if (!isSectionOptions) {
            continue;
        }
        ArkUIWaterFlowSection curSection = ParseSectionOptions(env, section);
        if (curSection.itemsCount < 0) {
            continue;
        }
        newSections.emplace_back(curSection);
    }

    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }

    modifier->getArkUIAniWaterFlowModifier()->setWaterFlowSection(
        arkNode, start, deleteCount, static_cast<void*>(newSections.data()), newSections.size());
}
} // namespace OHOS::Ace::Ani
