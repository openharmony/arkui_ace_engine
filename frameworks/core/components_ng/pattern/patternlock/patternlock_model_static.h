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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_STATIC_H

#include "core/components_ng/pattern/patternlock/patternlock_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PatternLockModelStatic {
public:
    static void SetActiveColor(FrameNode* frameNode, const std::optional<Color>& activeColor);
    static void SetCircleRadius(FrameNode* frameNode, const std::optional<Dimension>& radius);
    static void SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor);
    static void SetSideLength(FrameNode* frameNode, const std::optional<Dimension>& sideLength);
    static void SetAutoReset(FrameNode* frameNode, const std::optional<bool>& isAutoReset);
    static void SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& lineWidth);
    static void SetRegularColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPathColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetActiveCircleColor(FrameNode* frameNode, const std::optional<Color>& activeCircleColor);
    static void SetActiveCircleRadius(FrameNode* frameNode, const std::optional<Dimension>& activeCircleRadius);
    static void SetEnableWaveEffect(FrameNode* frameNode, const std::optional<bool>& enableWaveEffect);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_STATIC_H
