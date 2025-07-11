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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_STATIC_H

#include "core/components_ng/pattern/image_animator/image_animator_model.h"

#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ImageAnimatorModelStatic {
public:
    static void SetDuration(FrameNode* frameNode, const std::optional<int32_t>& duration);
    static void SetState(FrameNode* frameNode, const std::optional<int32_t>& state);
    static void SetFillMode(FrameNode* frameNode, const std::optional<int32_t>& fillMode);
    static void SetIteration(FrameNode* frameNode, const std::optional<int32_t>& iteration);

private:
    static RefPtr<ImageAnimatorPattern> GetImageAnimatorPattern();
    static RefPtr<ImageAnimatorPattern> GetImageAnimatorPattern(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_STATIC_H
