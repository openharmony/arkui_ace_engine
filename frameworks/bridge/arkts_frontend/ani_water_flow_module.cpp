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

#include "bridge/arkts_frontend/ani_water_flow_module.h"

#include <ani.h>
#include <optional>
#include <vector>

#include "ani_water_flow_module.h"

#include "base/geometry/calc_dimension.h"
#include "base/utils/string_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"

namespace {
using namespace OHOS::Ace;

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();

    ani_size bytesWritten = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytesWritten);
    utf8Buffer[bytesWritten] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

std::optional<Dimension> ParseDimension(ani_env* env, ani_ref dimensionRef)
{
    std::optional<Dimension> res;
    ani_class doubleClass;
    if (env->FindClass("Lstd/core/Double;", &doubleClass) != ANI_OK) {
        return res;
    }
    ani_class stringClass;
    if (env->FindClass("Lstd/core/String;", &stringClass) != ANI_OK) {
        return res;
    }

    ani_boolean isDouble;
    env->Object_InstanceOf(static_cast<ani_object>(dimensionRef), doubleClass, &isDouble);
    if (isDouble) {
        ani_double dimension;
        env->Object_CallMethodByName_Double(static_cast<ani_object>(dimensionRef), "unboxed", ":D", &dimension);
        res = CalcDimension(dimension, DimensionUnit::VP);
    }

    ani_boolean isString;
    env->Object_InstanceOf(static_cast<ani_object>(dimensionRef), stringClass, &isString);
    if (isString) {
        auto stringDimension = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(dimensionRef));
        res = StringUtils::StringToDimension(stringDimension, true);
    }
    return res;
}

NG::MarginProperty ParsePadding(ani_env* env, ani_ref paddingRef)
{
    NG::MarginProperty res;
    std::optional<CalcDimension> left;
    std::optional<CalcDimension> right;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;

    ani_ref leftRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "left", &leftRef);
    left = ParseDimension(env, leftRef);
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            res.left = NG::CalcLength(left.value().CalcValue());
        } else {
            res.left = NG::CalcLength(left.value());
        }
    }

    ani_ref rightRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "right", &rightRef);
    right = ParseDimension(env, rightRef);
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            res.right = NG::CalcLength(right.value().CalcValue());
        } else {
            res.right = NG::CalcLength(right.value());
        }
    }

    ani_ref topRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "top", &topRef);
    top = ParseDimension(env, topRef);
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            res.top = NG::CalcLength(top.value().CalcValue());
        } else {
            res.top = NG::CalcLength(top.value());
        }
    }

    ani_ref bottomRef;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(paddingRef), "bottom", &bottomRef);
    bottom = ParseDimension(env, bottomRef);
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            res.bottom = NG::CalcLength(bottom.value().CalcValue());
        } else {
            res.bottom = NG::CalcLength(bottom.value());
        }
    }
    return res;
}

std::optional<NG::MarginProperty> ParseMargin(ani_env* env, ani_ref marginRef)
{
    NG::MarginProperty res;
    ani_class paddingClass;
    if (env->FindClass("Larkui/component/units/Padding;", &paddingClass) != ANI_OK) {
        return std::make_optional(res);
    }

    ani_boolean isPadding;
    env->Object_InstanceOf(static_cast<ani_object>(marginRef), paddingClass, &isPadding);
    if (isPadding) {
        res = ParsePadding(env, marginRef);
    } else {
        std::optional<CalcDimension> length = ParseDimension(env, marginRef);
        if (length->Unit() == DimensionUnit::CALC) {
            res.SetEdges(NG::CalcLength(length->CalcValue()));
        } else {
            res.SetEdges(NG::CalcLength(length.value()));
        }
    }
    return std::make_optional(res);
}

} // namespace

namespace OHOS::Ace::Framework {

NG::WaterFlowSections::Section AniWaterFlowModule::ParseSectionOptions(ani_env* env, ani_ref section)
{
    NG::WaterFlowSections::Section curSection;
    ani_double itemsCount;
    if (env->Object_GetPropertyByName_Double(static_cast<ani_object>(section), "itemsCount", &itemsCount) != ANI_OK) {
        return curSection;
    }
    curSection.itemsCount = static_cast<int32_t>(itemsCount);

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
        env->Object_CallMethodByName_Double(static_cast<ani_object>(crossCount), "unboxed", ":D", &crossCnt);
        curSection.crossCount = static_cast<int32_t>(crossCnt);
    }

    ani_ref columnsGap;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "columnsGap", &columnsGap) != ANI_OK) {
    }
    isUndefined = false;
    if (env->Reference_IsUndefined(columnsGap, &isUndefined) != ANI_OK) {
    }
    if (!isUndefined) {
        curSection.columnsGap = ParseDimension(env, columnsGap);
    }

    ani_ref rowsGap;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "rowsGap", &rowsGap) != ANI_OK) {
    }
    isUndefined = false;
    if (env->Reference_IsUndefined(rowsGap, &isUndefined) != ANI_OK) {
    }
    if (!isUndefined) {
        curSection.rowsGap = ParseDimension(env, rowsGap);
    }

    ani_ref margin;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(section), "margin", &margin) != ANI_OK) {
    }
    isUndefined = false;
    if (env->Reference_IsUndefined(margin, &isUndefined) != ANI_OK) {
    }
    if (!isUndefined) {
        curSection.margin = ParseMargin(env, margin);
    }

    return curSection;
}

void AniWaterFlowModule::ParseWaterFlowSections(ani_env* env, ani_ref sections, NG::FrameNode* frameNode)
{
    auto waterFlowSections = NG::WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode);
    CHECK_NULL_VOID(waterFlowSections);

    ani_ref changeArray;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(sections), "changeArray", &changeArray) != ANI_OK) {
        return;
    }
    ani_size changeArrayLength;
    if (env->Array_GetLength(static_cast<ani_array_ref>(changeArray), &changeArrayLength) != ANI_OK) {
    }
    for (int32_t i = 0; i < changeArrayLength; i++) {
        ani_ref change;
        if (env->Array_Get_Ref(static_cast<ani_array_ref>(changeArray), 0, &change) != ANI_OK) {
        }

        ani_class sectionChangeInfo;
        if (env->FindClass("Larkui/component/waterFlow/SectionChangeInfo;", &sectionChangeInfo) != ANI_OK) {
            return;
        }
        ani_boolean isSectionChangeInfo;
        env->Object_InstanceOf(static_cast<ani_object>(change), sectionChangeInfo, &isSectionChangeInfo);
        if (!isSectionChangeInfo) {
            continue;
        }

        ani_double start = 0.0;
        if (env->Object_GetPropertyByName_Double(static_cast<ani_object>(change), "start", &start) != ANI_OK) {
        }
        ani_double deleteCount = 0.0;
        if (env->Object_GetPropertyByName_Double(static_cast<ani_object>(change), "deleteCount", &deleteCount) !=
            ANI_OK) {
        }

        ani_ref sectionOptionsArray;
        if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(change), "sections", &sectionOptionsArray) !=
            ANI_OK) {
        }

        ani_size aniLength;
        if (env->Array_GetLength(static_cast<ani_array_ref>(sectionOptionsArray), &aniLength) != ANI_OK) {
        }

        int32_t length = static_cast<int32_t>(aniLength);
        std::vector<NG::WaterFlowSections::Section> newSections;
        for (int32_t j = 0; j < length; j++) {
            ani_ref section;
            if (env->Array_Get_Ref(static_cast<ani_array_ref>(sectionOptionsArray), j, &section) != ANI_OK) {
                continue;
            }

            ani_class sectionOptions;
            if (env->FindClass("Larkui/component/waterFlow/SectionOptions;", &sectionOptions) != ANI_OK) {
                continue;
            }
            ani_boolean isSectionOptions;
            env->Object_InstanceOf(static_cast<ani_object>(section), sectionOptions, &isSectionOptions);

            if (isSectionOptions) {
                NG::WaterFlowSections::Section curSection = ParseSectionOptions(env, section);
                newSections.emplace_back(curSection);
            }
        }
        waterFlowSections->ChangeData(start, deleteCount, newSections);
    }
}

void AniWaterFlowModule::SetWaterFlowSection(ani_env* env, ani_long ptr, ani_object obj)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode);

    ani_ref sections;
    if (env->Object_GetPropertyByName_Ref(obj, "sections", &sections) != ANI_OK) {
        return;
    }

    ani_class waterflowSections;
    if (env->FindClass("Larkui/component/waterFlow/WaterFlowSections;", &waterflowSections) != ANI_OK) {
        return;
    }

    ani_boolean isNumber;
    env->Object_InstanceOf(static_cast<ani_object>(sections), waterflowSections, &isNumber);
    if (isNumber) {
        ParseWaterFlowSections(env, sections, frameNode);
    }
}
} // namespace OHOS::Ace::Framework
