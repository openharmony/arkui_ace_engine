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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXTPICKER_BRIDGE_TEXT_PICKER_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXTPICKER_BRIDGE_TEXT_PICKER_UTIL_H

#include <map>
#include <string>
#include <functional>


#include "ui/base/referenced.h"

#include "core/components_ng/pattern/date_picker/picker_data.h"

struct Ark_Union_TextPickerDialogOptions_TextPickerDialogOptionsExt;
namespace OHOS::Ace {
enum class VisibleType;
class Dimension;
class GestureEvent;
class PickerTheme;
struct ButtonInfo;
struct DialogProperties;

namespace NG {
class FrameNode;
struct DatePickerSettingData;
struct PickerTextProperties;
struct TextPickerSettingData;
using DialogTextEvent = std::function<void(const std::string&)>;
using DialogGestureEvent = std::function<void(const GestureEvent& info)>;

namespace TextPickerUtil {
const char COLUMN_ETS_TAG[] = "Column";
const char TEXT_PICKER_ETS_TAG[] = "TextPicker";
const char ROW_ETS_TAG[] = "Row";
const char IMAGE_ETS_TAG[] = "Image";
const char TEXT_ETS_TAG[] = "Text";
const char STACK_ETS_TAG[] = "Stack";
const char DIVIDER_ETS_TAG[] = "Divider";
const char BUTTON_ETS_TAG[] = "Button";

struct TextPickerCustomModifier {
    RefPtr<FrameNode> (*setTextPickerDialogViewShow)(const DialogProperties& dialogProperties,
        const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, DialogTextEvent> dialogEvent,
        std::map<std::string, DialogGestureEvent> dialogCancelEvent);
};

struct ArkUITextPickerDialogModifier {
    void (*showTextPickerDialog)(const Ark_Union_TextPickerDialogOptions_TextPickerDialogOptionsExt* options);
};

} // namespace TextPickerUtil
} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXTPICKER_BRIDGE_TEXT_PICKER_UTIL_H