/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_accessibility_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_event_hub.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_modifier.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class CheckBoxGroupPattern : public Pattern {
    DECLARE_ACE_TYPE(CheckBoxGroupPattern, Pattern);

public:
    CheckBoxGroupPattern() = default;
    ~CheckBoxGroupPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<CheckBoxGroupPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto eventHub = host->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, nullptr);
        auto enabled = eventHub->IsEnabled();
        if (!checkBoxGroupModifier_) {
            CheckBoxGroupModifier::Parameters paintParameters;
            InitializeModifierParam(paintParameters);
            UpdateModifierParam(paintParameters);
            checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(paintParameters);
        }
        auto paintMethod = MakeRefPtr<CheckBoxGroupPaintMethod>(checkBoxGroupModifier_);
        paintMethod->SetEnabled(enabled);
        paintMethod->SetUiStatus(uiStatus_);
        paintMethod->SetTouchHoverAnimationType(touchHoverType_);
        paintMethod->SetHotZoneOffset(hotZoneOffset_);
        paintMethod->SetHotZoneSize(hotZoneSize_);
        return paintMethod;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<CheckBoxGroupAccessibilityProperty>();
    }

    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, bool /*skipMeasure*/, bool /*skipLayout*/) override
    {
        auto geometryNode = dirty->GetGeometryNode();
        auto offset = geometryNode->GetContentOffset();
        auto size = geometryNode->GetContentSize();
        if (!NearEqual(offset, offset_) || !NearEqual(size, size_)) {
            offset_ = offset;
            size_ = size;
            AddHotZoneRect();
        }
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CheckBoxGroupEventHub>();
    }

    const std::optional<std::string>& GetPreGroup()
    {
        return preGroup_;
    }

    void SetPreGroup(const std::string& group)
    {
        preGroup_ = group;
    }

    bool GetIsAddToMap() const
    {
        return isAddToMap_;
    }

    void SetIsAddToMap(bool isAddToMap)
    {
        isAddToMap_ = isAddToMap;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        Pattern::ToJsonValue(json);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto checkBoxEventHub = host->GetEventHub<NG::CheckBoxGroupEventHub>();
        auto group = checkBoxEventHub ? checkBoxEventHub->GetGroupName() : "";
        json->Put("group", group.c_str());
    }

    void ResetUIStatus()
    {
        uiStatus_ = UIStatus::UNSELECTED;
    }

    FocusPattern GetFocusPattern() const override;
    void UpdateUIStatus(bool check);
    void UpdateModifierParam(CheckBoxGroupModifier::Parameters& paintParameters);
    void OnColorConfigurationUpdate() override;

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void InitClickEvent();
    void InitTouchEvent();
    void InitMouseEvent();
    void OnClick();
    void OnTouchDown();
    void OnTouchUp();
    void HandleMouseEvent(bool isHover);
    void UpdateUnSelect();
    void UpdateState();
    void UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool select);
    void UpdateRepeatedGroupStatus(const RefPtr<FrameNode>& frameNode, bool select);
    void UpdateCheckBoxStatus(const RefPtr<FrameNode>& frameNode,
        std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> checkBoxGroupMap, const std::string& group,
        bool select);
    // Init key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void AddHotZoneRect();
    void RemoveLastHotZoneRect() const;
    void InitializeModifierParam(CheckBoxGroupModifier::Parameters& paintParameters);

    std::optional<std::string> preGroup_;
    bool isAddToMap_ = true;
    RefPtr<ClickEvent> clickListener_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<CheckBoxGroupModifier> checkBoxGroupModifier_;
    bool isHover_ = false;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;
    bool isClick_ = false;
    bool isFirstCreated_ = true;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    OffsetF offset_;
    SizeF size_;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxGroupPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_PATTERN_H
