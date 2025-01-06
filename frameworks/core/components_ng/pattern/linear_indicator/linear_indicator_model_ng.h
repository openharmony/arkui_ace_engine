/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_MODEL_NG_H

#include "core/components_ng/pattern/linear_indicator/linear_indicator_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LinearIndicatorModelNG : public LinearIndicatorModel {
public:
    RefPtr<NG::LinearIndicatorController> Create(std::size_t progressCount) override;
    void SetSpace(const Dimension& value) override;
    void SetStrokeWidth(const Dimension& value) override;
    void SetStrokeRadius(const Dimension& value) override;
    void SetTrackBackgroundColor(const Color& value) override;
    void SetTrackColor(const Color& value) override;
    void Loop(bool value) override;
    void OnChange(std::function<void(int index, float progress)>&& event) override;

    static void SetIndicatorStyleSpace(FrameNode* frameNode, const Dimension& space);
    static void SetIndicatorStyleStrokeWidth(FrameNode* frameNode, const Dimension& strokeWidth);
    static void SetIndicatorStyleStrokeRadius(FrameNode* frameNode, const Dimension& strokeRadius);
    static void SetIndicatorStyleTrackBackgroundColor(FrameNode* frameNode, const Color& trackBackgroundColor);
    static void SetIndicatorStyleTrackColor(FrameNode* frameNode, const Color& trackColor);
    static void SetLoop(FrameNode* frameNode, bool value);
    static void SetOnChange(FrameNode* frameNode, std::function<void(int index, float progress)>&& event);

private:
    void SetProgressCount(OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> frameNode, std::size_t progressCount);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_MODEL_NG_H
