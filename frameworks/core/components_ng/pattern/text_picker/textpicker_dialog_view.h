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
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProperties, uint32_t selected, const Dimension& height,
        const std::vector<std::string>& getRangeVector, std::map<std::string, NG::DailogTextEvent> dialogEvent,
        std::map<std::string, NG::DailogGestureEvent> dialogCancalEvent);
    static void SetSelected(const RefPtr<TextPickerPattern>& textPickerPattern, uint32_t value = 0);
    static void SetRange(const RefPtr<TextPickerPattern>& textPickerPattern, const std::vector<std::string>& value);
    static void SetDailogChange(const RefPtr<FrameNode>& frameNode, DailogTextEvent&& onChange);
    static void SetDefaultPickerItemHeight(const Dimension& value = Dimension(0));
    static void SetDailogAcceptEvent(const RefPtr<FrameNode>& frameNode, DailogTextEvent onChange);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& frameNode,
    std::map<std::string, NG::DailogTextEvent> dialogEvent,
    std::map<std::string, NG::DailogGestureEvent> dialogCancalEvent);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_DIALOG_VIEW_H