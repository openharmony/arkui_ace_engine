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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_STATE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_STATE_MODIFIER_H

#include "render_service_client/core/modifier/rs_extended_modifier.h"
#include "render_service_client/core/modifier/rs_property.h"
#include "render_service_client/core/ui/rs_node.h"

#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {

using RSModifierType = Rosen::RSModifierType;
using RSExtendedModifier = Rosen::RSExtendedModifier;
using RSPropertyBase = Rosen::RSPropertyBase;

class RS_EXPORT FocusStateModifier : public RSOverlayStyleModifier {
public:
    FocusStateModifier() = default;

    RSModifierType GetModifierType() const override
    {
        return RSModifierType::OVERLAY_STYLE;
    }

    void Draw(RSDrawingContext& context) const override
    {
        CHECK_NULL_VOID(animationRect_);
        RSRoundRect roundRect = roundRect_;
        auto realRect = animationRect_->Get();
        roundRect.SetRect(
            RSRect(realRect.Left(), realRect.Top(), realRect.Right(), realRect.Bottom()));
#ifndef USE_ROSEN_DRAWING
        std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas* /*unused*/) {} };
        RSCanvas rsCanvas(&skCanvas);
        CHECK_NULL_VOID(&rsCanvas);
        paintTask_(roundRect, rsCanvas);
#else
        CHECK_NULL_VOID(context.canvas);
        CHECK_NULL_VOID(paintTask_);
        paintTask_(roundRect, *context.canvas);
#endif
    }

    std::shared_ptr<Rosen::RectF> GetOverlayRect()
    {
        return overlayRect_;
    }

    void SetRoundRect(const RoundRect& rect, float borderWidth)
    {
#ifndef USE_ROSEN_DRAWING
#ifndef USE_GRAPHIC_TEXT_GINE
        roundRect_.SetRect(
            rosen::Rect(rect.GetRect().Left(), rect.GetRect().Top(), rect.GetRect().Right(), rect.GetRect().Bottom()));
        roundRect_.SetCornerRadius(rosen::RoundRect::CornerPos::TOP_LEFT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y);
        roundRect_.SetCornerRadius(rosen::RoundRect::CornerPos::TOP_RIGHT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y);
        roundRect_.SetCornerRadius(rosen::RoundRect::CornerPos::BOTTOM_LEFT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y);
        roundRect_.SetCornerRadius(rosen::RoundRect::CornerPos::BOTTOM_RIGHT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y);
#else
        roundRect_.SetRect(
            RSRect(rect.GetRect().Left(), rect.GetRect().Top(), rect.GetRect().Right(), rect.GetRect().Bottom()));
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::TOP_LEFT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::TOP_RIGHT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::BOTTOM_LEFT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::BOTTOM_RIGHT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y);
#endif
#else
        roundRect_.SetRect(
            RSRect(rect.GetRect().Left(), rect.GetRect().Top(), rect.GetRect().Right(), rect.GetRect().Bottom()));
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::TOP_LEFT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::TOP_RIGHT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::BOTTOM_LEFT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::BOTTOM_RIGHT_POS,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
            rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y);
#endif
        if (!rect_) {
            rect_ = std::make_shared<Rosen::RSProperty<RectF>>(rect.GetRect());
        } else {
            rect_->Set(rect.GetRect());
        }
        AttachProperty(rect_);

        if (!animationRect_) {
            animationRect_ = std::make_shared<Rosen::RSAnimatableProperty<RectF>>(rect.GetRect());
            AttachProperty(animationRect_);
        } else {
            animationRect_->Set(rect.GetRect());
        }

        overlayRect_ = std::make_shared<Rosen::RectF>(
            rect.GetRect().Left() - borderWidth / 2, rect.GetRect().Top() - borderWidth / 2,
            rect.GetRect().Width() + borderWidth, rect.GetRect().Height() + borderWidth);
    }

    void SetPaintTask(const std::function<void(const RSRoundRect&, RSCanvas&)>& paintTask)
    {
        paintTask_ = paintTask;
    }

private:
    std::shared_ptr<Rosen::RSProperty<RectF>> rect_;
    RSRoundRect roundRect_;
    std::shared_ptr<Rosen::RectF> overlayRect_;
    std::function<void(const RSRoundRect&, RSCanvas&)> paintTask_;

    // Animation Properties
    std::shared_ptr<Rosen::RSAnimatableProperty<RectF>> animationRect_;
    ACE_DISALLOW_COPY_AND_MOVE(FocusStateModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_STATE_MODIFIER_H
