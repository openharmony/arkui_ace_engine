/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_PATTERN_H

#include <optional>

#include "base/log/dump_log.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/counter/counter_layout_algorithm.h"
#include "core/components_ng/pattern/counter/counter_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components/counter/counter_theme.h"

namespace OHOS::Ace::NG {

class CounterPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(CounterPattern, LinearLayoutPattern);

public:
    CounterPattern() : LinearLayoutPattern(false) {};
    ~CounterPattern() override = default;

    bool HasSubNode() const
    {
        return subId_.has_value();
    }
    int32_t GetSubId()
    {
        if (!subId_.has_value()) {
            subId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return subId_.value();
    }

    bool HasContentNode() const
    {
        return contentId_.has_value();
    }
    int32_t GetContentId()
    {
        if (!contentId_.has_value()) {
            contentId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return contentId_.value();
    }

    bool HasAddNode() const
    {
        return addId_.has_value();
    }
    int32_t GetAddId()
    {
        if (!addId_.has_value()) {
            addId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return addId_.value();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CounterLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<CounterLayoutProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            return { FocusType::NODE, false, FocusStyleType::OUTER_BORDER };
        }
        return { FocusType::SCOPE, true, FocusStyleType::OUTER_BORDER };
    }

    void UpdateTextColor(const RefPtr<FrameNode>& frameNode, const Color& value)
    {
        CHECK_NULL_VOID(frameNode);
        auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextColor(value);
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        textLayoutProperty->ResetTextColor();
    }

    bool OnThemeScopeUpdate(int32_t themeScopeId) override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto counterRenderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(counterRenderContext, false);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto counterTheme = pipeline->GetTheme<CounterTheme>(host->GetThemeScopeId());
        CHECK_NULL_RETURN(counterTheme, false);
        Color textColor = counterRenderContext->GetForegroundColor().has_value()
                              ? counterRenderContext->GetForegroundColorValue()
                              : counterTheme->GetContentTextStyle().GetTextColor();
        auto subNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(subId_.value())));
        CHECK_NULL_RETURN(subNode, false);
        auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetChildren().front());
        CHECK_NULL_RETURN(subTextNode, false);
        UpdateTextColor(subTextNode, textColor);

        auto addNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(addId_.value())));
        CHECK_NULL_RETURN(addNode, false);
        auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetChildren().front());
        CHECK_NULL_RETURN(addTextNode, false);
        UpdateTextColor(addTextNode, textColor);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return !counterRenderContext->GetForegroundColor().has_value();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        if (filter.IsFastFilter()) {
            return;
        }
        ToJsonValueAttribute(json);
    }

    void ToJsonValueAttribute(std::unique_ptr<JsonValue>& json) const
    {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto addNode = AceType::DynamicCast<FrameNode>(
            frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId_.value())));
        if (addNode) {
            auto eventHub = addNode->GetEventHub<ButtonEventHub>();
            if (eventHub) {
                auto enableInc = eventHub->GetStateEffect();
                json->Put("enableInc", enableInc ? "true" : "false");
            }
        }

        auto subNode = AceType::DynamicCast<FrameNode>(
            frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId_.value())));
        if (subNode) {
            auto eventHub = subNode->GetEventHub<ButtonEventHub>();
            if (eventHub) {
                auto enableDec = eventHub->GetStateEffect();
                json->Put("enableDec", enableDec ? "true" : "false");
            }
        }
    }

private:
    void DumpInfo() override
    {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto addNode = AceType::DynamicCast<FrameNode>(
            frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId_.value())));
        if (addNode) {
            auto eventHub = addNode->GetEventHub<ButtonEventHub>();
            if (eventHub) {
                auto enableInc = eventHub->GetStateEffect();
                DumpLog::GetInstance().AddDesc(std::string("enableInc: ").append(enableInc ? "true" : "false"));
            }
        }

        auto subNode = AceType::DynamicCast<FrameNode>(
            frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId_.value())));
        if (subNode) {
            auto eventHub = subNode->GetEventHub<ButtonEventHub>();
            if (eventHub) {
                auto enableDec = eventHub->GetStateEffect();
                DumpLog::GetInstance().AddDesc(std::string("enableDec: ").append(enableDec ? "true" : "false"));
            }
        }
    }

    void DumpInfo(std::unique_ptr<JsonValue>& json) override
    {
        ToJsonValueAttribute(json);
    }

    std::optional<int32_t> subId_;
    std::optional<int32_t> contentId_;
    std::optional<int32_t> addId_;
    ACE_DISALLOW_COPY_AND_MOVE(CounterPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_PATTERN_H
