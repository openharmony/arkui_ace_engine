/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_TYPES_H

#include <cstdint>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "core/components_ng/pattern/date_picker/picker_text_style.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {

// textpicker column kind
const uint32_t ICON = 0x01;
const uint32_t TEXT = 0x02;
const uint32_t MIXTURE = 0x03;

struct RangeContent {
    std::string icon_;
    std::string text_;
    RefPtr<ResourceObject> iconResObj_;
    RefPtr<ResourceObject> textResObj_;
};

struct TextCascadePickerOptions {
    std::vector<std::string> rangeResult;
    std::vector<TextCascadePickerOptions> children;
    RefPtr<ResourceObject> rangeResultResObj;
};

struct TextCascadePickerOptionsAttr {
    bool isCascade = false;
    bool isHasSelectAttr = false;
};

struct TextPickerSettingData {
    std::vector<RangeContent> rangeVector;
    uint32_t selected;
    uint32_t columnKind;
    Dimension height;
    bool canLoop = true;
    int32_t crownSensitivity;
    PickerTextProperties properties;
    PickerBackgroundStyle pickerBgStyle;
    std::vector<uint32_t> selectedValues;
    std::vector<std::string> values;
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptionsAttr attr;
    bool isDisableTextStyleAnimation = false;
    bool isEnableHapticFeedback = true;
    std::vector<Dimension> columnWidths;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_TYPES_H
