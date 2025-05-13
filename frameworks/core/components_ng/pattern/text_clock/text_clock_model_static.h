/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_STATIC_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextClockModelStatic {
public:
    static void SetFormat(FrameNode* frameNode, const std::optional<std::string>& format);
    static void SetHoursWest(FrameNode* frameNode, const std::optional<float>& hoursWest);
    static void SetFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& size);
    static void SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& value);
    static void SetDateTimeOptions(FrameNode* frameNode, const std::optional<ZeroPrefixType>& hourType);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_STATIC_H
