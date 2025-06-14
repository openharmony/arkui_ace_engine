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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BACKGROUND_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BACKGROUND_MODIFIER_H

#include <functional>
#include <memory>

#if defined(MODIFIER_NG)
#include "render_service_client/core/modifier_ng/custom/rs_background_style_modifier.h"
#else
#include "render_service_client/core/modifier/rs_extended_modifier.h"
#endif

#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {
#if defined(MODIFIER_NG)
using RSBackgroundStyleModifier = Rosen::ModifierNG::RSBackgroundStyleModifier;
using RSDrawingContext = Rosen::ModifierNG::RSDrawingContext;
#else
using RSBackgroundStyleModifier = Rosen::RSBackgroundStyleModifier;
using RSDrawingContext = Rosen::RSDrawingContext;
#endif

class BackgroundModifier : public RSBackgroundStyleModifier {
public:
    BackgroundModifier() = default;
    ~BackgroundModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        auto host = host_.Upgrade();
        CHECK_NULL_VOID(host);
        auto curSize = host->GetGeometryNode()->GetFrameSize();
        auto curWidth = curSize.Width();
        auto curHeight = curSize.Height();
        CHECK_NULL_VOID(pixelMap_);
        std::shared_ptr<Media::PixelMap> mediaPixelMap = pixelMap_->GetPixelMapSharedPtr();
        CHECK_NULL_VOID(mediaPixelMap);
        CHECK_NULL_VOID(context.canvas);
        auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(*context.canvas);
        RSSamplingOptions samplingOptions;
        RSBrush brush;

        SizeF desSize(initialNodeWidth_, initialNodeHeight_);
        SizeF srcSize(mediaPixelMap->GetWidth(), mediaPixelMap->GetHeight());
        NG::OffsetF offset1 = Alignment::GetAlignPosition(srcSize, desSize, align_);
        NG::OffsetF offset2 = Alignment::GetAlignPosition(desSize, srcSize, align_);
        RSRect srcRSRect =
            RSRect(offset1.GetX(), offset1.GetY(), srcSize.Width() + offset1.GetX(), srcSize.Height() + offset1.GetY());
        RSRect desRSRect =
            RSRect(offset2.GetX() * curWidth / initialNodeWidth_, offset2.GetY() * curHeight / initialNodeHeight_,
                srcSize.Width() * curWidth / initialNodeWidth_ + offset2.GetX() * curWidth / initialNodeWidth_,
                srcSize.Height() * curHeight / initialNodeHeight_ + offset2.GetY() * curHeight / initialNodeHeight_);
        if (srcSize.Width() > desSize.Width()) {
            srcRSRect.SetRight(offset1.GetX() + desSize.Width());
            desRSRect.SetRight(curWidth);
        }
        if (srcSize.Height() > desSize.Height()) {
            srcRSRect.SetBottom(offset1.GetY() + desSize.Height());
            desRSRect.SetBottom(curHeight);
        }
        recordingCanvas.AttachBrush(brush);
        recordingCanvas.DrawPixelMapRect(mediaPixelMap, srcRSRect, desRSRect, samplingOptions);
        recordingCanvas.DetachBrush();
    }

    void SetPixelMap(const RefPtr<PixelMap>& pixelMap)
    {
        CHECK_NULL_VOID(pixelMap);
        pixelMap_ = pixelMap;
    }

    void SetAlign(const Alignment& align)
    {
        align_ = align;
    }

    void SetInitialNodeSize(const float width, const float height)
    {
        initialNodeWidth_ = width;
        initialNodeHeight_ = height;
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

private:
    RefPtr<PixelMap> pixelMap_;
    Alignment align_;
    float initialNodeWidth_ = 1.0f;
    float initialNodeHeight_ = 1.0f;
    std::shared_ptr<Rosen::RSProperty<bool>> flag_;
    WeakPtr<FrameNode> host_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BACKGROUND_MODIFIER_H
