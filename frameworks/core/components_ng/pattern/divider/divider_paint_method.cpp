/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/divider/divider_paint_method.h"

#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
RefPtr<Modifier> DividerPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(dividerModifier_, nullptr);
    return dividerModifier_;
}

void DividerPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dividerModifier_);
    auto dividerRenderProperty = DynamicCast<DividerRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(dividerRenderProperty);
    auto host = paintWrapper->GetRenderContext()->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DividerTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    dividerColor_ = dividerRenderProperty->GetDividerColor().value_or(theme->GetColor());
    lineCap_ = dividerRenderProperty->GetLineCap().value_or(LineCap::BUTT);
    offset_ = paintWrapper->GetContentOffset();
    if (lineCap_ == LineCap::SQUARE || lineCap_ == LineCap::ROUND) {
        float boundsRectWidth = 0.0f;
        float boundsRectHeight = 0.0f;
        dividerLength_ += constrainStrokeWidth_;
        if (vertical_) {
            auto offsetY = offset_.GetY();
            offset_.SetY(offsetY - constrainStrokeWidth_ / 2);
            boundsRectWidth = constrainStrokeWidth_;
            boundsRectHeight = dividerLength_;
        } else {
            auto offsetX = offset_.GetX();
            offset_.SetX(offsetX - constrainStrokeWidth_ / 2);
            boundsRectWidth = dividerLength_;
            boundsRectHeight = constrainStrokeWidth_;
        }
        RectF boundsRect(offset_.GetX(), offset_.GetY(), boundsRectWidth, boundsRectHeight);
        dividerModifier_->SetBoundsRect(boundsRect);
        paintWrapper->FlushContentModifier();
    }
    dividerModifier_->SetStrokeWidth(constrainStrokeWidth_);
    dividerModifier_->SetDividerLength(dividerLength_);
    dividerModifier_->SetVertical(vertical_);
    dividerModifier_->SetOffset(offset_);
    dividerModifier_->SetColor(LinearColor(dividerColor_));
    dividerModifier_->SetLineCap(lineCap_);
    dividerModifier_->SetStrokeWidthLimitation(strokeWidthLimitation_);
}
} // namespace OHOS::Ace::NG
