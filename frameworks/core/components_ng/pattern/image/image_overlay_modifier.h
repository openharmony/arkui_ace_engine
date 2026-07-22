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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_OVERLAY_MODIFIER_H

#include <optional>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {

class ImageOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(ImageOverlayModifier, OverlayModifier);

public:
    ImageOverlayModifier(const Color& selectedColor);

    void onDraw(DrawingContext& drawingContext) override;
    
    void SetIsSelected(bool isSelected)
    {
        CHECK_NULL_VOID(isSelected_);
        isSelected_->Set(isSelected);
    }
    
    void SetSize(const SizeF& size)
    {
        CHECK_NULL_VOID(size_);
        size_->Set(size);
    }

    void SetOffset(const OffsetF& offset)
    {
        CHECK_NULL_VOID(offset_);
        offset_->Set(offset);
    }

private:
    RefPtr<PropertyBool> isSelected_;
    RefPtr<PropertySizeF> size_;
    RefPtr<PropertyOffsetF> offset_;
    const Color& selectedColor_;

    ACE_DISALLOW_COPY_AND_MOVE(ImageOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif