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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextView {
public:
    static void Create(const std::string& content);
    static void SetFontSize(const Dimension& value);
    static void SetTextColor(const Color& value);
    static void SetItalicFontStyle(const ItalicFontStyle& value);
    static void SetFontWeight(const FontWeight& value);
    static void SetFontFamily(const std::vector<std::string>& value);
    static void SetTextAlign(const TextAlign& value);
    static void SetTextOverflow(const TextOverflow& value);
    static void SetMaxLines(const uint32_t& value);
    static void SetLineHeight(const Dimension& value);
    static void SetTextDecoration(const TextDecoration& value);
    static void SetTextDecorationColor(const Color& value);
    static void SetBaselineOffset(const Dimension& value);
    static void SetTextCase(const TextCase& value);
    static void SetLetterSpacing(const Dimension& value);
    static void SetAdaptMinFontSize(const Dimension& value);
    static void SetAdaptMaxFontSize(const Dimension& value);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H
