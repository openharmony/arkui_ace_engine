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

#include "render_service_client/core/modifier/rs_extended_modifier.h"

#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {
class BackgroundModifier : public Rosen::RSBackgroundStyleModifier {
public:
    BackgroundModifier() = default;
    ~BackgroundModifier() override = default;

    void Draw(Rosen::RSDrawingContext& context) const override
    {
#ifndef USE_ROSEN_DRAWING
#ifdef NEW_SKIA
        CHECK_NULL_VOID(pixelMap_);
        std::shared_ptr<Media::PixelMap> mediaPixelMap = pixelMap_->GetPixelMapSharedPtr();
        std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas* /* unused */) {} };
        auto* recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(skCanvas.get());
        SkSamplingOptions samplingOptions;
        SkPaint paint;

        SizeF desSize(initialNodeWidth_, initialNodeHeight_);
        SizeF srcSize(mediaPixelMap->GetWidth(), mediaPixelMap->GetHeight());
        NG::OffsetF offset1 = Alignment::GetAlignPosition(srcSize, desSize, align_);
        NG::OffsetF offset2 = Alignment::GetAlignPosition(desSize, srcSize, align_);
        SkRect srcSKRect = SkRect::MakeXYWH(offset1.GetX(), offset1.GetY(), srcSize.Width(), srcSize.Height());
        SkRect desSKRect = SkRect::MakeXYWH(offset2.GetX() * context.width / initialNodeWidth_,
            offset2.GetY() * context.height / initialNodeHeight_, srcSize.Width() * context.width / initialNodeWidth_,
            srcSize.Height() * context.height / initialNodeHeight_);
        if (srcSize.Width() > desSize.Width()) {
            srcSKRect.fRight = offset1.GetX() + desSize.Width();
            desSKRect.fRight = context.width;
        }
        if (srcSize.Height() > desSize.Height()) {
            srcSKRect.fBottom = offset1.GetY() + desSize.Height();
            desSKRect.fBottom = context.height;
        }
        recordingCanvas->DrawPixelMapRect(mediaPixelMap, srcSKRect, desSKRect, samplingOptions, &paint);
#endif
#endif
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

private:
    RefPtr<PixelMap> pixelMap_;
    Alignment align_;
    float initialNodeWidth_ = 1.0f;
    float initialNodeHeight_ = 1.0f;
    std::shared_ptr<Rosen::RSProperty<bool>> flag_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BACKGROUND_MODIFIER_H
