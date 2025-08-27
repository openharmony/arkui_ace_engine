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

#include "render_service_client/core/modifier/rs_property.h"
#include "render_service_client/core/ui/rs_node.h"

#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/adapter/focus_modifier.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
using RSPropertyBase = Rosen::RSPropertyBase;

class RS_EXPORT FocusStateModifier : public FocusModifier, public RSOverlayStyleModifier {
public:
    FocusStateModifier() = default;

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
        PaintFocusState(roundRect, rsCanvas);
#else
        CHECK_NULL_VOID(context.canvas);
        PaintFocusState(roundRect, *context.canvas);
#endif
    }

    void SetRoundRect(const RoundRect& rect, float borderWidth) override
    {
        FocusModifier::SetRoundRect(rect, borderWidth);
        if (!rect_) {
            rect_ = std::make_shared<Rosen::RSProperty<RectF>>(rect.GetRect());
        } else {
            rect_->Set(rect.GetRect());
        }
        AttachProperty(rect_);

        if (!animationRect_) {
            animationRect_ = std::make_shared<Rosen::RSAnimatableProperty<RectF>>(rect.GetRect());
        } else {
            animationRect_->Set(rect.GetRect());
        }
    }

    void AttachAnimationRectProperty()
    {
        AttachProperty(animationRect_);
    }
private:
    void PaintFocusState(const RSRoundRect&, RSCanvas&) const;

    std::shared_ptr<Rosen::RSProperty<RectF>> rect_;
    // Animation Properties
    std::shared_ptr<Rosen::RSAnimatableProperty<RectF>> animationRect_;
    ACE_DISALLOW_COPY_AND_MOVE(FocusStateModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_STATE_MODIFIER_H