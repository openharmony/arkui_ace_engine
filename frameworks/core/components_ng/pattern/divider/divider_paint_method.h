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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_PAINT_METHOD_H

#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/divider/divider_modifier.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DividerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(DividerPaintMethod, NodePaintMethod);
public:
    DividerPaintMethod(float constrainStrokeWidth, float dividerLength, bool vertical, bool strokeWidthLimitation,
        RefPtr<DividerModifier> dividerModifier)
        : constrainStrokeWidth_(constrainStrokeWidth), dividerLength_(dividerLength), vertical_(vertical),
          strokeWidthLimitation_(strokeWidthLimitation), dividerModifier_(dividerModifier)
    {}
    ~DividerPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(dividerModifier_, nullptr);
        return dividerModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
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

private:
    float constrainStrokeWidth_;
    float dividerLength_;
    bool vertical_ = false;
    bool strokeWidthLimitation_ = true;

    OffsetF offset_;
    Color dividerColor_;
    LineCap lineCap_;
    RefPtr<DividerModifier> dividerModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(DividerPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_PAINT_METHOD_H
