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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FLUTTER_CANVAS_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FLUTTER_CANVAS_IMAGE_H

#include "flutter/flow/skia_gpu_object.h"
#include "third_party/skia/include/core/SkImage.h"

#include "core/components_ng/render/adapter/skia_canvas_image.h"

namespace OHOS::Ace::NG {

class FlutterCanvasImage : public SkiaCanvasImage {
    DECLARE_ACE_TYPE(FlutterCanvasImage, SkiaCanvasImage)
public:
    FlutterCanvasImage() = default;
    ~FlutterCanvasImage() override = default;

    sk_sp<SkImage> GetCanvasImage() const override
    {
        return image_.skia_object();
    }
    void SetImage(flutter::SkiaGPUObject<SkImage> image)
    {
        image_ = std::move(image);
    }

private:
    flutter::SkiaGPUObject<SkImage> image_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_FLUTTER_CANVAS_IMAGE_H
