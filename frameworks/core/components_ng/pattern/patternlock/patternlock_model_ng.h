/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_NG_H

#include "core/components_ng/pattern/patternlock/patternlock_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PatternLockModelNG : public OHOS::Ace::PatternLockModel {
public:
    RefPtr<V2::PatternLockController> Create() override;
    void SetPatternComplete(NG::PatternLockCompleteEvent&& onComplete) override;
    void SetDotConnect(std::function<void(int32_t)>&& onDotConnect) override;
    void SetSelectedColor(const Color& selectedColor) override;
    void SetAutoReset(bool isAutoReset) override;
    void SetPathColor(const Color& pathColor) override;
    void SetActiveColor(const Color& activeColor) override;
    void SetRegularColor(const Color& regularColor) override;
    void SetCircleRadius(const Dimension& radius) override;
    void SetSideLength(const Dimension& sideLength) override;
    void SetStrokeWidth(const Dimension& lineWidth) override;
    void SetActiveCircleColor(const Color& activeCircleColor) override;
    void SetActiveCircleRadius(const Dimension& activeCircleRadius) override;
    void SetEnableWaveEffect(bool enableWaveEffect) override;
    void SetEnableForeground(bool enableForeground) override;
    void SetSkipUnselectedPoint(bool isSkipUnselectedPoint) override;

    static void SetActiveColor(FrameNode* frameNode, const Color& activeColor);
    static void SetCircleRadius(FrameNode* frameNode, const Dimension& radius);
    static void SetSelectedColor(FrameNode* frameNode, const Color& selectedColor);
    static void SetSideLength(FrameNode* frameNode, const Dimension& sideLength);
    static void SetAutoReset(FrameNode* frameNode, bool isAutoReset);
    static void SetStrokeWidth(FrameNode* frameNode, const Dimension& lineWidth);
    static void SetRegularColor(FrameNode* frameNode, const Color& color);
    static void SetPathColor(FrameNode* frameNode, const Color& color);
    static void SetActiveCircleColor(FrameNode* frameNode, const Color& activeCircleColor);
    static void SetActiveCircleRadius(FrameNode* frameNode, const Dimension& activeCircleRadius);
    static void SetEnableWaveEffect(FrameNode* frameNode, bool enableWaveEffect);
    static void SetEnableForeground(FrameNode* frameNode, bool enableForeground);
    static void SetSkipUnselectedPoint(FrameNode* frameNode, bool isSkipUnselectedPoint);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_NG_H
