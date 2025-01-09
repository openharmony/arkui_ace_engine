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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_DIALOG_VIEW_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextPickerDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProperties, const TextPickerSettingData& settingData,
        const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static RefPtr<FrameNode> RangeShow(const DialogProperties& dialogProperties,
        const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, NG::DialogTextEvent>& dialogEvent,
        std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent);
    static RefPtr<FrameNode> OptionsShow(const DialogProperties& dialogProperties,
        const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, NG::DialogTextEvent>& dialogEvent,
        std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent);
    static void SetSelected(const RefPtr<TextPickerPattern>& textPickerPattern, uint32_t value = 0);
    static void SetSelectedValues(const RefPtr<TextPickerPattern>& textPickerPattern,
        const std::vector<uint32_t>& values);
    static void SetValues(const RefPtr<TextPickerPattern>& textPickerPattern,
        const std::vector<std::string>& values);
    static void SetRange(const RefPtr<TextPickerPattern>& textPickerPattern,
        const std::vector<NG::RangeContent>& value);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onChange);
    static void SetDialogScrollStop(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onScrollStop);
    static void SetDialogEnterSelectedArea(
        const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onEnterSelectedArea);
    static void SetDefaultPickerItemHeight(const Dimension& value);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onChange);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& frameNode,
        const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent, GestureEventFunc callback);
    static RefPtr<FrameNode> CreateAgingButtonNode(RefPtr<FrameNode>& textPickerNode,
        const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent>dialogCancelEvent,
        std::map<std::string, NG::DialogGestureEvent>dialogMoveForwardEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardEvent,
        GestureEventFunc closeCallback, GestureEventFunc nextCallBack, GestureEventFunc previousCallBack);
    static RefPtr<FrameNode> CreateDividerNode(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos, DialogEvent& acceptEvent);
    static RefPtr<FrameNode> CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
        const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateForwardNode(NG::DialogGestureEvent& moveForwardEvent,
        const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateBackwardNode(NG::DialogGestureEvent& moveBackwardEvent,
        const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos);

private:
    static RefPtr<FrameNode> CreateStackNode(RefPtr<PickerTheme> pickerTheme);
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static RefPtr<FrameNode> CreateColumnNode(uint32_t columnKind,
        uint32_t showCount, RefPtr<PickerTheme> pickerTheme);
    static RefPtr<FrameNode> CreateIconItemNode(RefPtr<PickerTheme> pickerTheme);
    static RefPtr<FrameNode> CreateTextItemNode(RefPtr<PickerTheme> pickerTheme);
    static RefPtr<FrameNode> CreateMixtureItemNode(RefPtr<PickerTheme> pickerTheme);
    static void SetTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const PickerTextProperties& properties);
    static void OptionsCreateNode(const RefPtr<TextPickerPattern>& textPickerPattern,
        const TextPickerSettingData& settingData, const RefPtr<FrameNode>& textPickerNode,
        uint32_t showCount, uint32_t columnCount, RefPtr<PickerTheme> pickerTheme);
    static void OptionsShowInternal(const RefPtr<TextPickerPattern>& textPickerPattern,
        const TextPickerSettingData& settingData, const RefPtr<FrameNode>& textPickerNode,
        uint32_t showCount, RefPtr<PickerTheme> pickerTheme);
    static void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    static bool OnKeyEvent(const KeyEvent& event);
    static void UpdateButtonConfirmLayoutProperty(const RefPtr<FrameNode>& buttonConfirmNode,
        RefPtr<PickerTheme> pickerTheme);
    static void UpdateButtonCancelLayoutProperty(const RefPtr<FrameNode>& buttonCancelNode,
        const RefPtr<PipelineContext>& pipeline);
    static void UpdateButtonForwardLayoutProperty(const RefPtr<FrameNode>& buttonCancelNode,
        const RefPtr<PipelineContext>& pipeline);
    static void UpdateButtonBackwardLayoutProperty(const RefPtr<FrameNode>& buttonCancelNode,
        const RefPtr<PipelineContext>& pipeline);
    static void UpdateConfirmButtonTextLayoutProperty(
        const RefPtr<FrameNode>& textConfirmNode, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateCancelButtonTextLayoutProperty(
        const RefPtr<FrameNode>& textCancelNode, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateForwardButtonTextLayoutProperty(
        const RefPtr<FrameNode>& textCancelNode, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateBackwardButtonTextLayoutProperty(
        const RefPtr<FrameNode>& textCancelNode, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateConfirmButtonMargin(
        const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateCancelButtonMargin(
        const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateForwardButtonMargin(
        const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateBackwardButtonMargin(
        const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext);
    static void UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
        const RefPtr<ButtonTheme>& buttonTheme);
    static void UpdateButtonDefaultFocus(const std::vector<ButtonInfo>& buttonInfos,
        const RefPtr<FrameNode>& buttonNode, bool isConfirm);
    static void SetDialogNodePageActive(RefPtr<FrameNode>& contentRow, RefPtr<FrameNode>& textPickerNode,
        const uint32_t& dialogNodePage, const uint32_t& showCount);
    static RefPtr<FrameNode> SeparatedOptionsShow(RefPtr<FrameNode>& contentColumn, RefPtr<FrameNode>& textPickerNode,
        const std::vector<ButtonInfo>& buttonInfos,
        const TextPickerSettingData& settingData,
        std::map<std::string, NG::DialogTextEvent>& dialogEvent,
        std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
        const float& scale, GestureEventFunc closeCallBack, RefPtr<FrameNode>& dialogNode);
    static void SetDialogButtonActive(RefPtr<FrameNode>& contentColumn,
        const uint32_t& dialogNodePage, const uint32_t& columnCount);
    static void SetFirstDialogButtonActive(RefPtr<UINode>& contentRow);
    static void SetSecondDialogButtonActive(RefPtr<UINode>& contentRow);
    static void SetThirdDialogButtonActive(RefPtr<UINode>& contentRow);
    static std::function<void()> CloseDialogEvent(const RefPtr<TextPickerPattern>& textPickerPattern,
        const RefPtr<FrameNode>& dialogNode);

    static void SetDividerNodeActive(RefPtr<UINode>& contentRow, bool firstDivider,
        bool secondDivider, bool thirdDivider);
    static void SetSingleDividerNodeActive(RefPtr<FrameNode>& dividerNode, bool dividerActive);
    static const Dimension ConvertFontSizeLimit(const Dimension& fontSizeValue,
        const Dimension& fontSizeLimit, bool isUserSetFont = false);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue,
        const Dimension& fontSizeLimit = 0.0_vp, bool isUserSetFont = false);
    static const Dimension AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale);
    static void GetUserSettingLimit();
    static bool NeedAdaptForAging();
    static void SetTextDisappearProperties(const RefPtr<PickerTheme>& pickerTheme,
        const PickerTextProperties& properties);
    static void SetDefaultTextStyle(const NG::PickerTextStyle& value);

    static WeakPtr<FrameNode> dialogNode_;
    static uint32_t dialogNodePage_;
    static Dimension selectedTextStyleFont_;
    static Dimension normalTextStyleFont_;
    static Dimension disappearTextStyleFont_;

};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_DIALOG_VIEW_H
