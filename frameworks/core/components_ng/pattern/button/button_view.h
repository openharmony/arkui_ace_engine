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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_VIEW_H

#include <string>

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ButtonView {
public:
    static void CreateLabel(const std::string& label);
    static void CreateChild();
    static void Type(ButtonType buttonType);
    static void StateEffect(bool stateEffect);
    static void FontSize(const Dimension& fontSize);
    static void FontWeight(Ace::FontWeight fontWeight);
    static void ItalicFontStyle(Ace::FontStyle fontStyle);
    static void FontFamily(const std::vector<std::string>& fontFamilies);
    static void TextColor(const Color& textColor);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_VIEW_H