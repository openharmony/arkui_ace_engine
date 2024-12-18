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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/text_clock/text_clock_accessibility_property.h"

#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

namespace OHOS::Ace::NG {
std::string TextClockAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    return UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u""));
}
} // namespace OHOS::Ace::NG