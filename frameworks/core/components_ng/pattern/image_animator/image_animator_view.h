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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/animation/animation_pub.h"
#include "core/animation/animator.h"
#include "core/components/declaration/image/image_animator_declaration.h"
#include "core/components_ng/pattern/image_animator/image_animator_event_hub.h"
#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"

namespace OHOS::Ace::NG {

enum class AnimatorEventType {
    ON_START,
    ON_PAUSE,
    ON_REPEAT,
    ON_CANCEL,
    ON_FINISH,
};

class ACE_EXPORT ImageAnimatorView {
public:
    static void Create();

    static void SetImages(std::vector<ImageProperties>&& images);
    static void SetStatus(Animator::Status status);
    static void SetDuration(int32_t duration);
    static void SetIteration(int32_t iteration);
    static void SetFillMode(FillMode fillMode);
    static void SetPreDecode(int32_t preDecode);
    static void SetIsReverse(bool isReverse);
    static void SetFixedSize(bool fixedSize);
    static void SetImageAnimatorEvent(const AnimatorEvent& imageAnimatorEvent, AnimatorEventType eventType);

private:
    static RefPtr<ImageAnimatorPattern> GetImageAnimatorPattern();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_VIEW_H