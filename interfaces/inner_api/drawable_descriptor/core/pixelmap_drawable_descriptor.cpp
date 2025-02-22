/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include "core/pixelmap_drawable_descriptor.h"

#include <cstdint>

#include "loader/image_loader.h"
#include "render_service_base/include/pipeline/rs_recording_canvas.h"
#include "utils/task_pool.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
namespace {
constexpr int32_t BORDER_RADIUS_ARRAY_SIZE = 4;
};

DrawableInfo PixelmapDrawableDescriptor::FetchSync()
{
    if (pixelMap_) {
        return { pixelMap_->GetWidth(), pixelMap_->GetHeight() };
    }
    LoadImageData();
    Decode();
    if (pixelMap_) {
        return { pixelMap_->GetWidth(), pixelMap_->GetHeight() };
    }
    return { 0, 0 };
}

void PixelmapDrawableDescriptor::Fetch()
{
    if (pixelMap_) {
        return;
    }
    // post load and decode task to pool
    TaskPool::GetInstance()->PostTask(
        [this] {
            LoadImageData();
            Decode();
            Validate();
        },
        "PixelMapDrawableDescriptorFetch");
}

void PixelmapDrawableDescriptor::LoadImageData()
{
    auto loader = ImageLoader::CreateImageLoader(src_.GetSrcType());
    data_ = loader->LoadImageData(src_);
}

void PixelmapDrawableDescriptor::Decode()
{
    pixelMap_ = data_->CreatePixelMap({ 0, 0 });
}

void PixelmapDrawableDescriptor::Validate()
{
    // flush component register redraw callback
    for (const auto& callback : redrawCallbacks_) {
        if (callback) {
            callback();
        }
    }
}

int32_t PixelmapDrawableDescriptor::GetOriginalWidth() const
{
    return 0;
}

int32_t PixelmapDrawableDescriptor::GetOriginalHeight() const
{
    return 0;
}

void PixelmapDrawableDescriptor::RegisterRedrawCallback(RedrawCallback&& callback)
{
    redrawCallbacks_.push_back(callback);
}

void PixelmapDrawableDescriptor::Draw(RSCanvas& canvas, PaintConfig config)
{
    if (!pixelMap_) {
        return;
    }

    RSPoint pointRadius[BORDER_RADIUS_ARRAY_SIZE] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };

    RSSamplingOptions options;
    RSAdaptiveImageInfo rsImageInfo;
    rsImageInfo.fitNum = static_cast<int32_t>(config.imageFit);
    rsImageInfo.repeatNum = 0;
    rsImageInfo.scale = 1.0;
    rsImageInfo.dynamicRangeMode = 2;
    rsImageInfo.radius[0] = pointRadius[0];
    rsImageInfo.radius[1] = pointRadius[1];
    rsImageInfo.radius[2] = pointRadius[2];
    rsImageInfo.radius[3] = pointRadius[3];
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    recordingCanvas.DrawPixelMapWithParm(pixelMap_->GetPixelMapSharedPtr(), rsImageInfo, options);
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
