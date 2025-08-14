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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_PATTERN_H

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/pattern/overlay/group_manager.h"
#include "core/components_ng/pattern/checkbox/checkbox_accessibility_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_layout_algorithm.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_method.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {
class CheckBoxGroupPaintProperty;
class CheckBoxPattern : public Pattern {
    DECLARE_ACE_TYPE(CheckBoxPattern, Pattern);

public:
    CheckBoxPattern() = default;
    ~CheckBoxPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<CheckBoxPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CheckBoxLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, bool /*skipMeasure*/, bool /*skipLayout*/) override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CheckBoxEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<CheckBoxAccessibilityProperty>();
    }

    const std::optional<std::string>& GetPreName()
    {
        return preName_;
    }

    const std::optional<std::string>& GetPreGroup()
    {
        return preGroup_;
    }

    int32_t GetPrePageId() const
    {
        return prePageId_;
    }

    void SetPreName(const std::string& name)
    {
        preName_ = name;
    }

    void SetPreGroup(const std::string& group)
    {
        preGroup_ = group;
    }

    void SetPrePageId(int32_t pageId)
    {
        prePageId_ = pageId;
    }

    void MarkIsSelected(bool isSelected);
    void SetLastSelect(bool select)
    {
        lastSelect_ = select;
    }

    void SetBuilderFunc(CheckBoxMakeCallback&& makeFunc);

    RefPtr<FrameNode> GetContentModifierNode()
    {
        return contentModifierNode_;
    }

    void SetToggleBuilderFunc(SwitchMakeCallback&& toggleMakeFunc);

    bool UseContentModifier()
    {
        return contentModifierNode_ != nullptr;
    }

    void SetCheckBoxSelect(bool value);

    void SetIsUserSetResponseRegion(bool isUserSetResponseRegion)
    {
        isUserSetResponseRegion_ = isUserSetResponseRegion;
    }

    void SetIndicatorBuilder(const std::optional<std::function<void()>>& buildFunc)
    {
        builder_ = buildFunc;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;

    void SetOriginalCheckboxStyle(OriginalCheckBoxStyle style)
    {
        originalStyle_ = style;
    }

    OriginalCheckBoxStyle GetOriginalCheckboxStyle()
    {
        return originalStyle_;
    }

    FocusPattern GetFocusPattern() const override;
    void UpdateUIStatus(bool check);

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    void OnColorConfigurationUpdate() override;
    void OnAttachToMainTree() override;
    void OnAttachToMainTreeMultiThread(const RefPtr<FrameNode>& frameNode);
    void StartCustomNodeAnimation(bool select);
    RefPtr<GroupManager> GetGroupManager();

    void SaveCheckboxSettingData(const CheckboxSettingData& checkboxSettingData)
    {
        checkboxSettingData_ = checkboxSettingData;
    }

    bool OnThemeScopeUpdate(int32_t themeScopeId) override;

    void DumpInfo() override;
    static int32_t ParseCommand(const std::string& command, bool& selectStatus);
    void ReportChangeEvent(bool selectStatus);
    int32_t OnInjectionEvent(const std::string& command) override;
    void SetIsUserSetMargin(bool isUserSetMargin)
    {
        isUserSetMargin_ = isUserSetMargin;
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

private:
    void OnAttachToFrameNode() override;
    void OnAttachToFrameNodeMultiThread(const RefPtr<FrameNode>& frameNode);
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnDetachFromFrameNodeMultiThread();
    void OnDetachFromMainTree() override;
    void OnDetachFromMainTreeMultiThread(const RefPtr<FrameNode>& frameNode);
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void InitClickEvent();
    void InitTouchEvent();
    void InitMouseEvent();
    void InitFocusEvent();
    void OnClick();
    void OnTouchDown();
    void OnTouchUp();
    void HandleMouseEvent(bool isHover);
    void HandleFocusEvent();
    void HandleBlurEvent();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void RegisterVisibleAreaChange();
    void OnIsFocusActiveUpdate(bool isFocusAcitve);
    void CheckPageNode();
    void LoadBuilder();
    void UpdateIndicator();
    void SetBuilderNodeHidden();
    void StartEnterAnimation();
    void StartExitAnimation();
    void UpdateState();
    void UpdateUnSelect();
    void UpdateGroupStatus(FrameNode* frameNode);
    void CheckBoxGroupIsTrue();
    void SetPrePageIdToLastPageId();
    // Init key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool IsSquareStyleBox();
    bool OnKeyEvent(const KeyEvent& event);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void AddHotZoneRect();
    void RemoveLastHotZoneRect() const;
    void SetAccessibilityAction();
    void UpdateSelectStatus(bool isSelected);
    void ChangeSelfStatusAndNotify(const RefPtr<CheckBoxPaintProperty>& paintProperty);
    void ChangeGroupStatusAndNotify(const RefPtr<FrameNode>& checkBoxGroupNode, const std::vector<std::string>& vec,
        bool haveCheckBoxSelected, bool isAllCheckBoxSelected);
    std::string GetGroupNameWithNavId();
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    void InitCheckBoxStatusByGroup(RefPtr<FrameNode> checkBoxGroupNode,
        const RefPtr<CheckBoxGroupPaintProperty>& groupPaintProperty, const std::list<RefPtr<FrameNode>>& list);
    void UpdateCheckBoxGroupStatus(RefPtr<FrameNode> checkBoxGroupNode, const std::list<RefPtr<FrameNode>>& list);
    void UpdatePaintPropertyBySettingData(RefPtr<CheckBoxPaintProperty> paintProp);
    void SetNeedAnimation(bool needAnimation);
    void InitDefaultMargin();
    void ResetDefaultMargin();
    void UpdateNavIdAndState(const RefPtr<FrameNode>& host);

    CheckboxSettingData checkboxSettingData_;

    std::optional<CheckBoxMakeCallback> makeFunc_;
    std::optional<SwitchMakeCallback> toggleMakeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    std::optional<std::string> preName_;
    std::optional<std::string> preGroup_;
    int32_t prePageId_ = 0;
    bool lastSelect_ = false;
    std::optional<std::string> currentNavId_ = std::nullopt;

    RefPtr<ClickEvent> clickListener_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    bool isTouch_ = false;
    bool isHover_ = false;
    bool isFirstCreated_ = true;
    bool isUserSetResponseRegion_ = false;
    bool focusEventInitialized_ = false;
    bool visible_ = true;
    bool isUserSetMargin_ = false;
    bool hasVisibleChangeRegistered_ = false;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    OffsetF offset_;
    SizeF size_;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;
    OriginalCheckBoxStyle originalStyle_ = OriginalCheckBoxStyle::CIRCULAR_STYLE;
    RefPtr<FrameNode> builderNode_;
    std::optional<std::function<void()>> builder_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    RefPtr<CheckBoxPaintMethod> paintMethod_;
    WeakPtr<GroupManager> groupManager_;
    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_PATTERN_H
