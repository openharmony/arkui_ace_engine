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

#include "core/components_ng/pattern/image/image_overlay_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
ImageOverlayModifier::ImageOverlayModifier(const Color& selectedColor) : selectedColor_(selectedColor)
{
    offset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    AttachProperty(offset_);
    isSelected_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(isSelected_);
    size_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    AttachProperty(size_);
}

void ImageOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(isSelected_->Get());
    auto& canvas = drawingContext.canvas;
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(selectedColor_.GetValue());
    canvas.AttachBrush(brush);

    auto offset = offset_->Get();
    auto size = size_->Get();

    canvas.DrawRect(
        RSRect(offset.GetX(), offset.GetY(), offset.GetX() + size.Width(), offset.GetY() + size.Height()));

    canvas.DetachBrush();
    canvas.Restore();
}

} // namespace OHOS::Ace::NG