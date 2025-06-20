/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TRANSITION_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TRANSITION_MODIFIER_H

#include <functional>
#include <memory>

#if defined(MODIFIER_NG)
#include "render_service_client/core/modifier_ng/custom/rs_transition_style_modifier.h"
#endif

#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
#if defined(MODIFIER_NG)
using RSTransitionStyleModifier = Rosen::ModifierNG::RSTransitionStyleModifier;
#else
using RSTransitionStyleModifier = Rosen::RSTransitionModifier;
#endif
class TransitionModifier : public RSTransitionStyleModifier {
public:
    TransitionModifier() = default;
    ~TransitionModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        if (isBuilderBackground_) {
            DrawWithPixelMap(context);
        } else {
            DrawWithBackgroundColor(context);
        }
    }

    void SetPixelMap(const RefPtr<PixelMap>& pixelMap)
    {
        pixelMap_ = pixelMap;
    }

    void SetAlign(const Alignment& align)
    {
        align_ = align;
    }

    void Modify()
    {
        if (!flag_) {
            flag_ = std::make_shared<Rosen::RSProperty<bool>>(0);
            AttachProperty(flag_);
        } else {
            flag_->Set(!flag_->Get());
        }
    }

    void SetHostNode(RefPtr<FrameNode> host)
    {
        host_ = host;
    }

    void SetBackgroundColor(const Color& color)
    {
        backgroundColor_ = color;
    }

    void SetDrawRegionUpdateFunc(std::function<void(const std::shared_ptr<Rosen::RectF>& rect)>&& func)
    {
        updateDrawRegionFunc_ = std::move(func);
    }

    void SetIsBuilderBackground(bool isBuilderBackground)
    {
        isBuilderBackground_ = isBuilderBackground;
    }

    void SetInitialBackgroundRegion(const RectF& region)
    {
        initialBackgroundRegion_ = region;
    }

#ifndef MODIFIER_NG
    void Active() override {};
    void Identity() override {};
#endif

private:
    void DrawWithPixelMap(RSDrawingContext& context) const
    {
        CHECK_NULL_VOID(pixelMap_);
        RSRect backgroundRegion = GetBackgroundRegion();
        auto backgroundRegionWidth = backgroundRegion.GetWidth();
        auto backgroundRegionHeight = backgroundRegion.GetHeight();
        std::shared_ptr<Media::PixelMap> mediaPixelMap = pixelMap_->GetPixelMapSharedPtr();
        CHECK_NULL_VOID(mediaPixelMap);
        CHECK_NULL_VOID(context.canvas);
        auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(*context.canvas);
        RSSamplingOptions samplingOptions;
        RSBrush brush;
        SizeF desSize(initialBackgroundRegion_.Width(), initialBackgroundRegion_.Height());
        SizeF srcSize(mediaPixelMap->GetWidth(), mediaPixelMap->GetHeight());
        NG::OffsetF offset1 = Alignment::GetAlignPosition(srcSize, desSize, align_);
        NG::OffsetF offset2 = Alignment::GetAlignPosition(desSize, srcSize, align_);
        RSRect srcRSRect =
            RSRect(offset1.GetX(), offset1.GetY(), srcSize.Width() + offset1.GetX(), srcSize.Height() + offset1.GetY());
        float widthScale = backgroundRegionWidth / initialBackgroundRegion_.Width();
        float heightScale = backgroundRegionHeight / initialBackgroundRegion_.Height();
        RSRect desRSRect = RSRect(backgroundRegion.GetLeft() + offset2.GetX() * widthScale,
                                  backgroundRegion.GetTop() + offset2.GetY() * heightScale,
                                  backgroundRegion.GetLeft() + (srcSize.Width() + offset2.GetX()) * widthScale,
                                  backgroundRegion.GetTop() + (srcSize.Height() + offset2.GetY()) * heightScale);
        if (srcSize.Width() > desSize.Width()) {
            srcRSRect.SetRight(offset1.GetX() + desSize.Width());
            desRSRect.SetRight(backgroundRegion.GetLeft() + backgroundRegionWidth);
        }
        if (srcSize.Height() > desSize.Height()) {
            srcRSRect.SetBottom(offset1.GetY() + desSize.Height());
            desRSRect.SetBottom(backgroundRegion.GetTop() + backgroundRegionHeight);
        }
        std::shared_ptr<Rosen::RectF> drawRegion = std::make_shared<Rosen::RectF>(
            desRSRect.GetLeft(), desRSRect.GetTop(), desRSRect.GetWidth(), desRSRect.GetHeight());
        CHECK_NULL_VOID(updateDrawRegionFunc_);
        updateDrawRegionFunc_(drawRegion);
        recordingCanvas.AttachBrush(brush);
        recordingCanvas.DrawPixelMapRect(mediaPixelMap, srcRSRect, desRSRect, samplingOptions);
        recordingCanvas.DetachBrush();
    }

    void DrawWithBackgroundColor(RSDrawingContext& context) const
    {
        RSRect backgroundRegion = GetBackgroundRegion();
        std::shared_ptr<Rosen::RectF> drawRect = std::make_shared<Rosen::RectF>(backgroundRegion.GetLeft(),
            backgroundRegion.GetTop(), backgroundRegion.GetWidth(), backgroundRegion.GetHeight());
        CHECK_NULL_VOID(updateDrawRegionFunc_);
        updateDrawRegionFunc_(drawRect);
        CHECK_NULL_VOID(context.canvas);
        auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(*context.canvas);
        RSBrush brush;
        brush.SetColor(ToRSColor(backgroundColor_));
        recordingCanvas.AttachBrush(brush);
        recordingCanvas.DrawRect(backgroundRegion);
        recordingCanvas.DetachBrush();
    }

    RSRect GetBackgroundRegion() const
    {
        RSRect rect;
        RefPtr<FrameNode> host = host_.Upgrade();
        CHECK_NULL_RETURN(host, rect);
        rect = ToRSRect(host->GetBackGroundAccumulatedSafeAreaExpand());
        return rect;
    }

    RefPtr<PixelMap> pixelMap_;
    Alignment align_;
    Color backgroundColor_;
    std::shared_ptr<Rosen::RSProperty<bool>> flag_;
    WeakPtr<FrameNode> host_;
    bool isBuilderBackground_ = false;
    RectF initialBackgroundRegion_ = { 0.0f, 0.0f, 1.0f, 1.0f };
    std::function<void(const std::shared_ptr<Rosen::RectF>& rect)> updateDrawRegionFunc_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TRANSITION_MODIFIER_H