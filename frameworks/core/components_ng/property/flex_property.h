/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_FLEX_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_FLEX_PROPERTIES_H

#include <map>

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
using AlignRulesItem = std::map<AlignDirection, AlignRule>;
using BiasPair = std::pair<float, float>;
using GuidelineItem = std::vector<GuidelineInfo>;
using BarrierItem = std::vector<BarrierInfo>;

class FlexItemProperty {
public:
    FlexItemProperty() = default;
    ~FlexItemProperty() = default;

    std::string HorizontalAlignToString(HorizontalAlign align)
    {
        switch (align) {
            case HorizontalAlign::CENTER:
                return "HorizontalAlign::Center";
            case HorizontalAlign::START:
                return "HorizontalAlign::Left";
            case HorizontalAlign::END:
                return "HorizontalAlign::End";
            default:
                return "Unknown";
        }
    }

    std::string VerticalAlignToString(VerticalAlign align)
    {
        switch (align) {
            case VerticalAlign::TOP:
                return "VerticalAlign::Top";
            case VerticalAlign::CENTER:
                return "VerticalAlign::Center";
            case VerticalAlign::BOTTOM:
                return "VerticalAlign::Bottom";
            case VerticalAlign::BASELINE:
                return "VerticalAlign::BaseLine";
            default:
                return "Unknown";
        }
    }

    std::string AlignDirectionToString(AlignDirection direction)
    {
        switch (direction) {
            case AlignDirection::MIDDLE:
                return "AlignDirection::Middle";
            case AlignDirection::LEFT:
                return "AlignDirection::Left";
            case AlignDirection::RIGHT:
                return "AlignDirection::RIGHT";
            case AlignDirection::TOP:
                return "AlignDirection::Top";
            case AlignDirection::CENTER:
                return "AlignDirection::Center";
            case AlignDirection::BOTTOM:
                return "AlignDirection::Bottom";
            default:
                return "Unknown";
        }
    }

    std::string SingleAlignRuleToString(AlignDirection direction, AlignRule rule)
    {
        std::string result = AlignDirectionToString(direction) + ": {'" + rule.anchor + "', ";
        if (static_cast<int32_t>(direction) < HORIZONTAL_DIRECTION_RANGE) {
            result += HorizontalAlignToString(rule.horizontal);
        } else if (static_cast<int32_t>(direction) < VERTICAL_DIRECTION_RANGE) {
            result += VerticalAlignToString(rule.vertical);
        } else {
            result += "Unknown";
        }
        result += "}";
        return result;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        static const char* ITEM_ALIGN[] = { "ItemAlign.Auto", "ItemAlign.Start", "ItemAlign.Center", "ItemAlign.End",
            "ItemAlign.Stretch", "ItemAlign.Baseline" };
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr(
            "flexBasis", propFlexBasis.has_value() ? propFlexBasis.value().ToString().c_str() : "auto", filter);
        json->PutExtAttr("flexGrow", round(static_cast<double>(propFlexGrow.value_or(0.0)) * 100) / 100, filter);
        json->PutExtAttr("flexShrink", round(static_cast<double>(propFlexShrink.value_or(1)) * 100) / 100, filter);
        json->PutExtAttr(
            "alignSelf", ITEM_ALIGN[static_cast<int32_t>(propAlignSelf.value_or(FlexAlign::AUTO))], filter);
        json->PutExtAttr("displayPriority", propDisplayIndex.value_or(1), filter);
    }

    std::string AlignRulesToString()
    {
        if (!HasAlignRules()) {
            return "";
        }
        return AlignRulesToString(GetAlignRules().value());
    }

    std::string AlignRulesToString(const AlignRulesItem& alignRules)
    {
        std::string result;
        auto iter = alignRules.begin();
        for (; iter != alignRules.end(); iter++) {
            result.append(SingleAlignRuleToString(iter->first, iter->second));
            result.append(", ");
        }
        return result;
    }

    void ClearAlignValue()
    {
        ResetAlignLeft();
        ResetAlignRight();
        ResetAlignMiddle();
        ResetAlignTop();
        ResetAlignBottom();
        ResetAlignCenter();
    }

    bool GetTwoHorizontalDirectionAligned() const
    {
        return (HasAlignLeft() && HasAlignRight()) || (HasAlignRight() && HasAlignMiddle()) ||
               (HasAlignLeft() && HasAlignMiddle());
    }

    bool GetTwoVerticalDirectionAligned() const
    {
        return (HasAlignTop() && HasAlignCenter()) || (HasAlignBottom() && HasAlignCenter()) ||
               (HasAlignTop() && HasAlignBottom());
    }

    void SetAlignValue(const AlignDirection& alignDirection, float value)
    {
        static const std::unordered_map<AlignDirection, void (*)(float, FlexItemProperty&)> operators = {
            { AlignDirection::LEFT,
                [](float inMapValue, FlexItemProperty& item) { item.UpdateAlignLeft(inMapValue); } },
            { AlignDirection::RIGHT,
                [](float inMapValue, FlexItemProperty& item) { item.UpdateAlignRight(inMapValue); } },
            { AlignDirection::MIDDLE,
                [](float inMapValue, FlexItemProperty& item) { item.UpdateAlignMiddle(inMapValue); } },
            { AlignDirection::TOP, [](float inMapValue, FlexItemProperty& item) { item.UpdateAlignTop(inMapValue); } },
            { AlignDirection::BOTTOM,
                [](float inMapValue, FlexItemProperty& item) { item.UpdateAlignBottom(inMapValue); } },
            { AlignDirection::CENTER,
                [](float inMapValue, FlexItemProperty& item) { item.UpdateAlignCenter(inMapValue); } },
        };
        auto operatorIter = operators.find(alignDirection);
        if (operatorIter != operators.end()) {
            operatorIter->second(value, *this);
            return;
        }
        LOGW("Unknown Align Direction");
    }

    bool GetAligned(const AlignDirection& alignDirection)
    {
        static const std::unordered_map<AlignDirection, bool (*)(FlexItemProperty&)> operators = {
            { AlignDirection::LEFT, [](FlexItemProperty& item) { return item.HasAlignLeft(); } },
            { AlignDirection::RIGHT, [](FlexItemProperty& item) { return item.HasAlignRight(); } },
            { AlignDirection::MIDDLE, [](FlexItemProperty& item) { return item.HasAlignMiddle(); } },
            { AlignDirection::TOP, [](FlexItemProperty& item) { return item.HasAlignTop(); } },
            { AlignDirection::BOTTOM, [](FlexItemProperty& item) { return item.HasAlignBottom(); } },
            { AlignDirection::CENTER, [](FlexItemProperty& item) { return item.HasAlignCenter(); } },
        };
        auto operatorIter = operators.find(alignDirection);
        if (operatorIter != operators.end()) {
            return operatorIter->second(*this);
        }
        LOGW("Unknown Align Direction");
        return false;
    }

    float GetAlignValue(const AlignDirection& alignDirection)
    {
        static const std::unordered_map<AlignDirection, float (*)(FlexItemProperty&)> operators = {
            { AlignDirection::LEFT, [](FlexItemProperty& item) { return item.GetAlignLeft().value_or(0.0f); } },
            { AlignDirection::RIGHT, [](FlexItemProperty& item) { return item.GetAlignRight().value_or(0.0f); } },
            { AlignDirection::MIDDLE, [](FlexItemProperty& item) { return item.GetAlignMiddle().value_or(0.0f); } },
            { AlignDirection::TOP, [](FlexItemProperty& item) { return item.GetAlignTop().value_or(0.0f); } },
            { AlignDirection::BOTTOM, [](FlexItemProperty& item) { return item.GetAlignBottom().value_or(0.0f); } },
            { AlignDirection::CENTER, [](FlexItemProperty& item) { return item.GetAlignCenter().value_or(0.0f); } },
        };
        auto operatorIter = operators.find(alignDirection);
        if (operatorIter != operators.end()) {
            return operatorIter->second(*this);
        }
        LOGW("Unknown Align Direction");
        return 0.0f;
    }

    bool NeedMarkParentMeasure()
    {
        return needMarkParentMeasure_;
    }
    void SetMarkParentMeasure(bool mark)
    {
        needMarkParentMeasure_ = mark;
    }

    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexGrow, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexShrink, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignSelf, FlexAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexBasis, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DisplayIndex, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HorizontalChainStyle, ChainInfo);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(VerticalChainStyle, ChainInfo);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignLeft, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignMiddle, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignRight, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignTop, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignCenter, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignBottom, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Bias, BiasPair);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Barrier, BarrierItem);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Guideline, GuidelineItem);
    ACE_DEFINE_PROPERTY_GROUP_ITEM_WITH_CALLBACK(AlignRules, AlignRulesItem);

private:
    void OnAlignRulesUpdate(const AlignRulesItem& item)
    {
        auto prevValue = propAlignRules_;
        if (TopologicalOrderMightChanged(item)) {
            needMarkParentMeasure_ = true;
        }
    }
    bool TopologicalOrderMightChanged(const AlignRulesItem& newValue)
    {
        // return if has no prev value, then relativeContainer must measure
        if (!propAlignRules_.has_value()) {
            return true;
        }
        auto& prevValue = propAlignRules_.value();
        // target: container can skip redo topological ordering even children might have some changes related to
        // alignRules Rule Ver.1: a. all key of new map must exist in prev map b. values related to the same key should
        // have the same value c. when we have less alignRules than the last time, keeping topo order would be fine Next
        // possible update: allowing new map has more align rules but extra anchor has lower topo order
        //                          meaning a new dependency that will be measured earlier is added
        for (auto iter = newValue.begin(); iter != newValue.end(); iter++) {
            if (prevValue.find(iter->first) != prevValue.end()) {
                if (prevValue[iter->first] != iter->second) {
                    return true;
                }
            } else {
                return true;
            }
        }
        return false;
    }

    bool needMarkParentMeasure_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_FLEX_PROPERTIES_H
