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
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextPickerDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProperties, const TextPickerSettingData& settingData,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static RefPtr<FrameNode> RangeShow(const DialogProperties& dialogProperties,
        const TextPickerSettingData& settingData, std::map<std::string, NG::DialogTextEvent>& dialogEvent,
        std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent);
    static RefPtr<FrameNode> OptionsShow(const DialogProperties& dialogProperties,
        const TextPickerSettingData& settingData, std::map<std::string, NG::DialogTextEvent>& dialogEvent,
        std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent);
    static void SetSelected(const RefPtr<TextPickerPattern>& textPickerPattern, uint32_t value = 0);
    static void SetSelectedValues(const RefPtr<TextPickerPattern>& textPickerPattern,
        const std::vector<uint32_t>& values);
    static void SetValues(const RefPtr<TextPickerPattern>& textPickerPattern,
        const std::vector<std::string>& values);
    static void SetRange(const RefPtr<TextPickerPattern>& textPickerPattern,
        const std::vector<NG::RangeContent>& value);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onChange);
    static void SetDefaultPickerItemHeight(const Dimension& value);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onChange);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& frameNode,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        GestureEventFunc callback);
    static RefPtr<FrameNode> CreateDividerNode(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& textPickerNode,
        DialogEvent& acceptEvent);
    static RefPtr<FrameNode> CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
        const RefPtr<FrameNode>& textPickerNode);

private:
    static RefPtr<FrameNode> CreateStackNode();
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
    static RefPtr<FrameNode> dialogNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_DIALOG_VIEW_H
