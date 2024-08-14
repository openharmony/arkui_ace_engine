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

#include "core/components_ng/pattern/divider/divider_modifier.h"

#include "core/components_ng/render/divider_painter.h"

namespace OHOS::Ace::NG {
DividerModifier::DividerModifier()
{
    color_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLUE);
    strokeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    dividerLength_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    lineCap_ = AceType::MakeRefPtr<PropertyInt>(0);
    vertical_ = AceType::MakeRefPtr<PropertyBool>(false);
    offset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    strokeWidthLimitation_ = AceType::MakeRefPtr<PropertyBool>(true);

    AttachProperty(color_);
    AttachProperty(strokeWidth_);
    AttachProperty(dividerLength_);
    AttachProperty(lineCap_);
    AttachProperty(vertical_);
    AttachProperty(offset_);
    AttachProperty(strokeWidthLimitation_);
}

void DividerModifier::onDraw(DrawingContext& context)
{
    LineCap lineCap = LineCap(lineCap_->Get());
    if (strokeWidthLimitation_->Get()) {
        lineCap = lineCap == LineCap::BUTT ? LineCap::SQUARE : lineCap;
    }
    DividerPainter dividerPainter(
        strokeWidth_->Get(), dividerLength_->Get(), vertical_->Get(), color_->Get().ToColor(), lineCap);
    dividerPainter.DrawLine(context.canvas, offset_->Get());
}
} // namespace OHOS::Ace::NG
