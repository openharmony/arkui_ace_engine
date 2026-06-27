/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_TEXT_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_TEXT_STYLE_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components_ng/property/border_property.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {

// update flag of text properties
const uint32_t FLAG_DISAPPEAR_COLOR = 0x0001;
const uint32_t FLAG_COLOR = 0x0002;
const uint32_t FLAG_SELECTED_COLOR = 0x0004;
const uint32_t FLAG_DISAPPEAR_FONTSIZE = 0x0008;
const uint32_t FLAG_FONTSIZE = 0x0010;
const uint32_t FLAG_SELECTED_FONTSIZE = 0x0020;
const uint32_t FLAG_DISAPPEAR_WEIGHT = 0x0040;
const uint32_t FLAG_WEIGHT = 0x0080;
const uint32_t FLAG_SELECTED_WEIGHT = 0x0100;

struct PickerTextStyle {
    std::optional<Color> textColor;
    std::optional<Dimension> fontSize;
    std::optional<FontWeight> fontWeight;
    std::optional<std::vector<std::string>> fontFamily;
    std::optional<Ace::FontStyle> fontStyle;
    std::optional<Dimension> minFontSize;
    std::optional<Dimension> maxFontSize;
    std::optional<Ace::TextOverflow> textOverflow;

    bool textColorSetByUser = false;

    RefPtr<ResourceObject> textColorResObj;
    RefPtr<ResourceObject> fontSizeResObj;
    RefPtr<ResourceObject> fontFamilyResObj;
    RefPtr<ResourceObject> minFontSizeResObj;
    RefPtr<ResourceObject> maxFontSizeResObj;
};

struct PickerTextProperties {
    PickerTextStyle disappearTextStyle_;
    PickerTextStyle normalTextStyle_;
    PickerTextStyle selectedTextStyle_;
    PickerTextStyle defaultTextStyle_;
};

struct PickerBackgroundStyle {
    std::optional<Color> color;
    std::optional<NG::BorderRadiusProperty> borderRadius;
    bool textColorSetByUser = false;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> borderRadiusResObj;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_TEXT_STYLE_H
