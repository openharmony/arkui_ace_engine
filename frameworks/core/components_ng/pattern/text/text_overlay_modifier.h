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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_OVERLAY_MODIFIER_H

#include <optional>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
class Pattern;

class TextOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(TextOverlayModifier, OverlayModifier)

public:
    TextOverlayModifier();

    void onDraw(DrawingContext& drawingContext) override;

    void SetPrintOffset(const OffsetF& paintOffset);

    void SetSelectedColor(uint32_t selectedColor);

    void SetSelectedRects(const std::vector<Rect>& selectedRects);

    void SetContentRect(const RectF& contentRect)
    {
        contentRect_ = contentRect;
    }

    void SetIsClip(bool isClip)
    {
        CHECK_NULL_VOID(isClip_);
        isClip_->Set(isClip);
    }

protected:
    std::optional<RectF> contentRect_;

private:
    bool IsSelectedRectsChanged(const std::vector<Rect>& selectedRects);

    RefPtr<PropertyOffsetF> paintOffset_;
    RefPtr<PropertyInt> selectedColor_;
    RefPtr<PropertyBool> changeSelectedRects_;
    RefPtr<PropertyBool> isClip_;;
    std::vector<Rect> selectedRects_;

    ACE_DISALLOW_COPY_AND_MOVE(TextOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif