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
#include "core/components_ng/image_provider/animated_image_object.h"

#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#else
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#endif
#include "core/components_ng/image_provider/image_loading_context.h"
#include "frameworks/core/components_ng/render/adapter/animated_image.h"

namespace OHOS::Ace::NG {
void AnimatedImageObject::MakeCanvasImage(
    const WeakPtr<ImageLoadingContext>& ctxWp, const SizeF& size, bool forceResize, bool /*syncLoad*/)
{
    auto ctx = ctxWp.Upgrade();
    CHECK_NULL_VOID(ctx);
    AnimatedImage::ResizeParam params { .width = size.Width(),
        .height = size.Height(),
        .forceResize = forceResize,
        .imageQuality = ctx->GetImageQuality() };

#ifndef USE_ROSEN_DRAWING
    auto image = AnimatedImage::Create(DynamicCast<SkiaImageData>(data_), params, src_.GetKey());
#else
    auto image = AnimatedImage::Create(DynamicCast<DrawingImageData>(data_), params, src_.GetKey());
#endif
    CHECK_NULL_VOID(ctx);
    if (!image) {
        ctx->FailCallback("failed to create animated image");
    }
    ctx->SuccessCallback(image);
}

RefPtr<ImageObject> AnimatedImageObject::Clone()
{
    return Claim(this);
}
} // namespace OHOS::Ace::NG
