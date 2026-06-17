/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_picker/bridge/textpicker_util.h"

#include <string>

#include "interfaces/inner_api/ace_kit/include/ui/base/geometry/dimension.h"
#include "interfaces/inner_api/ace_kit/include/ui/gestures/gesture_event.h"

#include "core/common/font_manager.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_picker/textpicker_types.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/interfaces/arkoala/arkoala_api.h"
namespace OHOS::Ace::NG::TextPickerUtil {
namespace {
#define MODIFIER_COUNTS 1
} // namespace

#ifndef ARKUI_WEARABLE
RefPtr<FrameNode> SetTextPickerDialogViewShow(const DialogProperties& dialogProps,
    const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto node = TextPickerDialogView::Show(
        dialogProps, settingData, buttonInfos, std::move(dialogEvent), std::move(dialogCancelEvent));
    return node;
}
#endif

const TextPickerCustomModifier* GetTextPickerCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const TextPickerCustomModifier modifier = {
#ifndef ARKUI_WEARABLE
        .setTextPickerDialogViewShow = SetTextPickerDialogViewShow,
#else
        .setTextPickerDialogViewShow = nullptr,
#endif
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, MODIFIER_COUNTS, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
