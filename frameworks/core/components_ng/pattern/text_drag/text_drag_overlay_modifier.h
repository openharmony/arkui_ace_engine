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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class TextDragOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(TextDragOverlayModifier, OverlayModifier);

public:
    explicit TextDragOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~TextDragOverlayModifier() override = default;

    void onDraw(DrawingContext& context) override;
    void StartAnimate();
    void SetBackgroundOffset(float offset);

private:

    WeakPtr<Pattern> pattern_;
    bool isAnimating_ = false;
    RefPtr<AnimatablePropertyFloat> backgroundOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(TextDragOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H
