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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H

#include <cstdint>
#include <functional>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/autofill/auto_fill_trigger_state_holder.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/dialog//dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_accessibility_property.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

enum class DialogContentNode {
    TITLE = 0,
    SUBTITLE,
    MESSAGE,
    SHEET,
    BORDERWIDTH,
};
enum class DialogDismissReason {
    DIALOG_PRESS_BACK = 0,
    DIALOG_TOUCH_OUTSIDE,
    DIALOG_CLOSE_BUTTON,
};
class DialogPattern : public PopupBasePattern, public FocusView, public AutoFillTriggerStateHolder {
    DECLARE_ACE_TYPE(DialogPattern, PopupBasePattern, FocusView, AutoFillTriggerStateHolder);

public:
    DialogPattern(const RefPtr<DialogTheme>& dialogTheme, const RefPtr<UINode>& customNode)
        : dialogTheme_(dialogTheme), customNode_(customNode)
    {}
    ~DialogPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetOnWillDismiss(const std::function<void(const int32_t& info, const int32_t& instanceId)>& onWillDismiss)
    {
        onWillDismiss_ = onWillDismiss;
    }

    bool ShouldDismiss() const
    {
        if (onWillDismiss_ && !isDialogDisposed_) {
            return true;
        }
        return false;
    }

    void SetOnWillDismissByNDK(const std::function<bool(const int32_t& info)>& onWillDismissByNDK)
    {
        onWillDismissByNDK_ = onWillDismissByNDK;
    }

    bool CallDismissInNDK(int reason)
    {
        if (onWillDismissByNDK_ && onWillDismissByNDK_(reason)) {
            return true;
        }
        return false;
    }

    void CallOnWillDismiss(const int32_t reason, const int32_t instanceId)
    {
        if (onWillDismiss_ && !isDialogDisposed_) {
            onWillDismiss_(reason, instanceId);
        }
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return AceType::MakeRefPtr<DialogLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<DialogEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<DialogAccessibilityProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        if (dialogProperties_.type == DialogType::ALERT_DIALOG || dialogProperties_.type == DialogType::ACTION_SHEET) {
            return { 0 };
        }
        return { 0, 0 };
    }

    void BuildChild(const DialogProperties& dialogProperties);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    const std::string& GetTitle()
    {
        return title_;
    }

    const std::string& GetSubtitle()
    {
        return subtitle_;
    }

    const std::string& GetMessage()
    {
        return message_;
    }

    RefPtr<UINode> GetCustomNode()
    {
        return customNode_.Upgrade();
    }

    void SetOpenAnimation(const std::optional<AnimationOption>& openAnimation)
    {
        openAnimation_ = openAnimation;
    }
    std::optional<AnimationOption> GetOpenAnimation() const
    {
        return openAnimation_;
    }

    void SetCloseAnimation(const std::optional<AnimationOption>& closeAnimation)
    {
        closeAnimation_ = closeAnimation;
    }
    std::optional<AnimationOption> GetCloseAnimation() const
    {
        return closeAnimation_;
    }

    void SetDialogProperties(const DialogProperties& param)
    {
        dialogProperties_ = param;
        InitHostWindowRect();
    }

    const DialogProperties& GetDialogProperties() const
    {
        return dialogProperties_;
    }

    void OnColorConfigurationUpdate() override;

    void OnLanguageConfigurationUpdate() override;

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override;
    bool AvoidBottom() const override
    {
        return false;
    }

    void RegisterDialogDidAppearCallback(std::function<void()>&& onDidAppear)
    {
        onDidAppearCallback_ = std::move(onDidAppear);
    }

    void RegisterDialogDidDisappearCallback(std::function<void()>&& onDidDisappear)
    {
        onDidDisappearCallback_ = std::move(onDidDisappear);
    }

    void RegisterDialogWillAppearCallback(std::function<void()>&& onWillAppear)
    {
        onWillAppearCallback_ = std::move(onWillAppear);
    }

    void RegisterDialogWillDisappearCallback(std::function<void()>&& onWillDisappear)
    {
        onWillDisappearCallback_ = std::move(onWillDisappear);
    }

    void CallDialogDidAppearCallback()
    {
        if (onDidAppearCallback_) {
            onDidAppearCallback_();
        }
        SetState(PromptActionCommonState::APPEARED);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is APPEARED.");
    }

    void CallDialogDidDisappearCallback()
    {
        if (onDidDisappearCallback_) {
            onDidDisappearCallback_();
        }
        SetState(PromptActionCommonState::DISAPPEARED);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is DISAPPEARED.");
    }

    void CallDialogWillAppearCallback()
    {
        if (onWillAppearCallback_) {
            onWillAppearCallback_();
        }
        SetState(PromptActionCommonState::APPEARING);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is APPEARING.");
    }

    void CallDialogWillDisappearCallback()
    {
        if (onWillDisappearCallback_) {
            onWillDisappearCallback_();
        }
        SetState(PromptActionCommonState::DISAPPEARING);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is DISAPPEARING.");
    }

    bool IsUIExtensionSubWindow() const
    {
        return isUIExtensionSubWindow_;
    }

    RectF GetHostWindowRect() const
    {
        return hostWindowRect_;
    }

    void UpdateFoldDisplayModeChangedCallbackId(std::optional<int32_t> id)
    {
        foldDisplayModeChangedCallbackId_ = id;
    }

    bool HasFoldDisplayModeChangedCallbackId()
    {
        return foldDisplayModeChangedCallbackId_.has_value();
    }

    void UpdateHoverModeChangedCallbackId(std::optional<int32_t> id)
    {
        hoverModeChangedCallbackId_ = id;
    }

    bool HasHoverModeChangedCallbackId()
    {
        return hoverModeChangedCallbackId_.has_value();
    }

    bool GetIsSuitableForAging()
    {
        return isSuitableForElderly_;
    }

    float GetFontScaleForElderly()
    {
        return fontScaleForElderly_;
    }

    void SetIsPickerDialog(bool value)
    {
        isPickerDialog_ = value;
    }

    bool GetIsPickerDialog()
    {
        return isPickerDialog_;
    }

    void UpdateDeviceOrientation(const DeviceOrientation& deviceOrientation);
    void InitHostWindowRect();
    void UpdateHostWindowRect();
    void UpdateFontScale();

    bool GetIsSuitOldMeasure()
    {
        return isSuitOldMeasure_;
    }

    void SetIsScrollHeightNegative(bool isScrollHeightNegative)
    {
        isScrollHeightNegative_ = isScrollHeightNegative;
    }

    bool TriggerAutoSaveWhenInvisible() override
    {
        return true;
    }

    void SetIsDialogDisposed(bool isDialogDisposed)
    {
        isDialogDisposed_ = isDialogDisposed;
    }

    void SetState(PromptActionCommonState value)
    {
        state = value;
    }

    PromptActionCommonState GetState()
    {
        return state;
    }

    bool IsShowInFreeMultiWindow();
    bool IsShowInFloatingWindow();
    void AddExtraMaskNode(const DialogProperties& props);

    int32_t getTransitionNodeCount()
    {
        return transitionNodeCount_;
    }

    void addTransitionNodeCount()
    {
        transitionNodeCount_++;
    }

    void OverlayDismissDialog(const RefPtr<FrameNode>& dialogNode);
    RefPtr<OverlayManager> GetEmbeddedOverlay(const RefPtr<OverlayManager>& context);
    void UpdateDialogColor(const Color& color, const DialogResourceType type);
    void UpdateContentValue(std::string& text, const DialogResourceType type);
    void UpdateLayoutContent(const CalcDimension& value, const DialogResourceType type);
    void UpdateBackShadow(const Shadow& shadow);
    void UpdateEffect(const EffectOption& option);
    void UpdateBlurStyle(const BlurStyleOption& option);
    void UpdateMaskRect(const DimensionRect& rect);
    void UpdateBackGroundColor(std::string& content);
    void UpdateBorderColor(std::string& content);
    void UpdateContent(std::string& text, ActionSheetType type);
    void UpdateContent(const Color& color, ActionSheetType type);
    void UpdateBorderWidth(const NG::BorderWidthProperty& width);
    void UpdateBorderColor(const NG::BorderColorProperty& color);
    void UpdateCornerRadius(const NG::BorderRadiusProperty& radius);
    void UpdateButtonBackgroundColor(const Color& color, int32_t buttonIndex);
    void UpdateButtonFontColor(const std::string colorStr, int32_t buttonIndex);
    void UpdateButtonText(const std::string text, int32_t buttonIndex);

private:
    bool AvoidKeyboard() const override
    {
        return false;
    }
    void OnModifyDone() override;

    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void RegisterHoverModeChangeCallback();
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    RectF GetContentRect(const RefPtr<FrameNode>& contentNode);
    void HandleClick(const GestureEvent& info);
    void RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleBlurEvent();
    void HandleFocusEvent();

    void PopDialog(int32_t buttonIdx);
    bool NeedUpdateHostWindowRect();

    // set render context properties of content frame
    void UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode, const DialogProperties& props);
    void BuildCustomChild(const DialogProperties& props, const RefPtr<UINode>& customNode);
    RefPtr<FrameNode> BuildMainTitle(const DialogProperties& dialogProperties);
    RefPtr<FrameNode> BuildSubTitle(const DialogProperties& dialogProperties);
    void ParseButtonFontColorAndBgColor(
        const ButtonInfo& params, std::string& textColor, std::optional<Color>& bgColor);
    void SetButtonEnabled(const RefPtr<FrameNode>& buttonNode, bool enabled);
    // update wrapperNode background style
    void UpdateWrapperBackgroundStyle(const RefPtr<FrameNode>& host, const RefPtr<DialogTheme>& dialogTheme);
    RefPtr<FrameNode> BuildTitle(const DialogProperties& dialogProperties);
    RefPtr<FrameNode> BuildContent(const DialogProperties& dialogProperties);
    RefPtr<FrameNode> CreateDialogScroll(const DialogProperties& dialogProps);

    void UpdateDialogButtonProperty(RefPtr<FrameNode>& buttonNode, int32_t index, bool isVertical, int32_t length);
    RefPtr<FrameNode> BuildButtons(const std::vector<ButtonInfo>& buttons, const DialogButtonDirection& direction);
    void AddButtonAndDivider(
        const std::vector<ButtonInfo>& buttons, const RefPtr<NG::FrameNode>& container, bool isVertical);
    RefPtr<FrameNode> CreateDivider(
        const Dimension& dividerLength, const Dimension& dividerWidth, const Color& color, const Dimension& space);
    RefPtr<FrameNode> CreateButton(
        const ButtonInfo& params, int32_t index, bool isCancel = false, bool isVertical = false, int32_t length = 0);
    RefPtr<FrameNode> CreateButtonText(const std::string& text, const std::string& colorStr);
    // to close dialog when button is clicked
    void BindCloseCallBack(const RefPtr<GestureEventHub>& hub, int32_t buttonIdx);
    // build ActionSheet items
    RefPtr<FrameNode> BuildSheet(const std::vector<ActionSheetInfo>& sheets);
    RefPtr<FrameNode> BuildSheetItem(const ActionSheetInfo& item);
    RefPtr<FrameNode> BuildSheetInfoTitle(const std::string& title);
    RefPtr<FrameNode> BuildSheetInfoIcon(const std::string& icon);
    // build actionMenu
    RefPtr<FrameNode> BuildMenu(const std::vector<ButtonInfo>& buttons, bool hasTitle);
    void RecordEvent(int32_t btnIndex) const;
    void ParseBorderRadius(BorderRadiusProperty& raidus);
    void UpdateSheetIconAndText();
    void UpdateButtonsPropertyForEachButton(RefPtr<FrameNode> buttonFrameNode, int32_t btnindex);
    void UpdateButtonsProperty();
    void UpdateNodeContent(const RefPtr<FrameNode>& node, std::string& text);
    void UpdateTitleAndContentColor();
    void UpdateDialogTextColor(const RefPtr<FrameNode>& textNode, const TextStyle& textStyle);
    void UpdateAlignmentAndOffset();
    void DumpBoolProperty();
    void DumpBoolProperty(std::unique_ptr<JsonValue>& json);
    void DumpObjectProperty();
    void DumpObjectProperty(std::unique_ptr<JsonValue>& json);
    void DumpSimplifyBoolProperty(std::unique_ptr<JsonValue>& json);
    void DumpSimplifyObjectProperty(std::unique_ptr<JsonValue>& json);
    void DumpSimplifyBorderProperty(std::unique_ptr<JsonValue>& json);
    void DumpSimplifySizeProperty(std::unique_ptr<JsonValue>& json);
    void UpdatePropertyForElderly(const std::vector<ButtonInfo>& buttons);
    bool NeedsButtonDirectionChange(const std::vector<ButtonInfo>& buttons);
    void OnFontConfigurationUpdate() override;
    void UpdateTextFontScale();
    void UpdateTitleTextFontScale();
    void CheckScrollHeightIsNegative(const RefPtr<UINode>& contentColumn, const DialogProperties& props);
    RefPtr<OverlayManager> GetOverlayManager(const RefPtr<FrameNode>& host);
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;
    void AddFollowParentWindowLayoutNode();
    void RemoveFollowParentWindowLayoutNode();
    void RegisterButtonOnKeyEvent(const ButtonInfo& params, RefPtr<FrameNode>& buttonNode, int32_t buttonIdx);
    RefPtr<DialogTheme> dialogTheme_;
    WeakPtr<UINode> customNode_;
    RefPtr<ClickEvent> onClick_;

    std::optional<AnimationOption> openAnimation_;
    std::optional<AnimationOption> closeAnimation_;
    std::optional<int32_t> foldDisplayModeChangedCallbackId_;
    std::optional<int32_t> hoverModeChangedCallbackId_;
    bool isFoldStatusChanged_ = false;

    // XTS inspector values
    std::string message_;
    std::string title_;
    std::string subtitle_;
    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss_;
    std::function<bool(const int32_t& info)> onWillDismissByNDK_;

    DialogProperties dialogProperties_;
    WeakPtr<FrameNode> menuNode_;
    bool isFirstDefaultFocus_ = true;
    RefPtr<FrameNode> buttonContainer_;
    RefPtr<FrameNode> contentColumn_;
    RefPtr<RenderContext> contentRenderContext_;
    bool isSuitableForElderly_ = false;
    bool isPickerDialog_ = false;
    bool notAdapationAging_ = false;
    bool isSuitOldMeasure_ = false;
    bool isScrollHeightNegative_ = false;
    float fontScaleForElderly_ = 1.0f;
    PromptActionCommonState state = PromptActionCommonState::UNINITIALIZED;
    DeviceOrientation deviceOrientation_ = DeviceOrientation::PORTRAIT;
    RefPtr<FrameNode> titleContainer_;
    int32_t transitionNodeCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(DialogPattern);

    std::function<void()> onDidAppearCallback_ = nullptr;
    std::function<void()> onDidDisappearCallback_ = nullptr;
    std::function<void()> onWillAppearCallback_ = nullptr;
    std::function<void()> onWillDisappearCallback_ = nullptr;
    std::unordered_map<DialogContentNode, RefPtr<FrameNode>> contentNodeMap_;
    bool isUIExtensionSubWindow_ = false;
    bool isDialogDisposed_ = false;
    RectF hostWindowRect_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H
