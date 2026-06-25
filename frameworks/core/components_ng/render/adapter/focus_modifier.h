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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FOCUS_MODIFIER_H

#include "render_service_client/core/modifier/rs_property.h"
#include "render_service_client/core/ui/rs_node.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {
using RSPropertyBase = Rosen::RSPropertyBase;

class FocusModifier {
public:
    FocusModifier() = default;
    ~FocusModifier() = default;
    virtual void SetRoundRect(const RoundRect& rect, float borderWidth)
    {
        CHECK_NULL_VOID(&rect);
        auto cornTopLeft = rect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
        auto cornTopRight = rect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS);
        auto cornBottomLeft = rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS);
        auto cornBottomRight = rect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS);
#ifndef USE_ROSEN_DRAWING
        roundRect_.SetRect(
            RSRect(rect.GetRect().Left(), rect.GetRect().Top(), rect.GetRect().Right(), rect.GetRect().Bottom()));
        InitRoundRect(cornTopLeft, cornTopRight, cornBottomLeft, cornBottomRight);
#else
        roundRect_.SetRect(
            RSRect(rect.GetRect().Left(), rect.GetRect().Top(), rect.GetRect().Right(), rect.GetRect().Bottom()));
        InitRoundRect(cornTopLeft, cornTopRight, cornBottomLeft, cornBottomRight);
#endif
        InitOverlayRect(rect, borderWidth);
    }

    std::shared_ptr<Rosen::RectF> GetOverlayRect()
    {
        return overlayRect_;
    }

    void SetPaintColor(const Color& paintColor)
    {
        paintColor_ = paintColor;
    }

    void SetFrameNode(const RefPtr<FrameNode>& frameNode)
    {
        weakFrameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    }

protected:
    RSRoundRect roundRect_;
    Color paintColor_;
    float paintWidthPx_ = 0.0f;
    WeakPtr<FrameNode> weakFrameNode_;

private:
    void InitOverlayRect(const RoundRect& rect, float borderWidth)
    {
        RSScalar halfDenominator = 2.0f;
        float halfBorder = borderWidth / halfDenominator;
        float newLeft = rect.GetRect().Left() - halfBorder;
        float newTop = rect.GetRect().Top() - halfBorder;
        float newRight = rect.GetRect().Left() + rect.GetRect().Width() + halfBorder;
        float newBottom = rect.GetRect().Top() + rect.GetRect().Height() + halfBorder;
        if (overlayRect_) {
            float oldLeft = overlayRect_->GetLeft();
            float oldTop = overlayRect_->GetTop();
            float oldRight = overlayRect_->GetLeft() + overlayRect_->GetWidth();
            float oldBottom = overlayRect_->GetTop() + overlayRect_->GetHeight();
            newLeft = std::min(newLeft, oldLeft);
            newTop = std::min(newTop, oldTop);
            newRight = std::max(newRight, oldRight);
            newBottom = std::max(newBottom, oldBottom);
        }
        overlayRect_ = std::make_shared<Rosen::RectF>(
            newLeft, newTop, newRight - newLeft, newBottom - newTop);
        paintWidthPx_ = borderWidth;
    }

    void InitRoundRect(EdgeF cornTopLeft, EdgeF cornTopRight, EdgeF cornBottomLeft, EdgeF cornBottomRight)
    {
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::TOP_LEFT_POS, cornTopLeft.x, cornTopLeft.y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::TOP_RIGHT_POS, cornTopRight.x, cornTopRight.y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::BOTTOM_LEFT_POS, cornBottomLeft.x, cornBottomLeft.y);
        roundRect_.SetCornerRadius(RSRoundRect::CornerPos::BOTTOM_RIGHT_POS, cornBottomRight.x, cornBottomRight.y);
    }

    std::shared_ptr<Rosen::RectF> overlayRect_;
};

} // namespace OHOS::Ace::NG

#endif