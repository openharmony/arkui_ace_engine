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

#include <optional>
#include <string_view>


#include "base/utils/macros.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text/text_styles.h"


#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_VIEW_H

namespace OHOS::Ace::NG {
    
// pair<value, icon>
using SelectParam = std::pair<std::string, std::string>;

class ACE_EXPORT SelectView {
public:
    static void Create(const std::vector<SelectParam>& params);
    static void SetSelected(int32_t idx);
    static void SetValue(const std::string& value);

    static void SetFontSize(const Dimension& value);
    static void SetItalicFontStyle(const Ace::FontStyle& value);
    static void SetFontWeight(const FontWeight& value);
    static void SetFontFamily(const std::vector<std::string>& value);
    static void SetFontColor(const Color& color);

    static void SetSelectedOptionBgColor(const Color& color);    
    static void SetSelectedOptionFontSize(const Dimension& value);
    static void SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value);
    static void SetSelectedOptionFontWeight(const FontWeight& value);
    static void SetSelectedOptionFontFamily(const std::vector<std::string>& value);
    static void SetSelectedOptionFontColor(const Color& color);

    static void SetOptionBgColor(const Color& color);
    static void SetOptionFontSize(const Dimension& value);
    static void SetOptionItalicFontStyle(const Ace::FontStyle& value);
    static void SetOptionFontWeight(const FontWeight& value);
    static void SetOptionFontFamily(const std::vector<std::string>& value);
    static void SetOptionFontColor(const Color& color);

    static void SetOnSelect(SelectEvent&& onSelect);

};

} // namespace OHOS::Ace::NG

#endif