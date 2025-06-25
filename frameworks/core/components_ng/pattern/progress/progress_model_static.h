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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_STATIC_H

#include "core/components_ng/pattern/progress/progress_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ProgressModelStatic {
public:
    static void SetColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetGradientColor(FrameNode* frameNode, const std::optional<Gradient>& value);
    static void SetSmoothEffect(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetLinearSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetRingSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetPaintShadow(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetProgressStatus(FrameNode* frameNode, const std::optional<ProgressStatus>& status);
    static void SetScaleCount(FrameNode* frameNode, const std::optional<int32_t>& value);
    static void SetScaleWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBorderColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetShowText(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetText(FrameNode* frameNode, const std::optional<std::string>& value);
    static void SetFontColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& value);
    static void SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetStrokeRadius(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_STATIC_H