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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_RENDER_IMAGE_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_RENDER_IMAGE_H

#include "ffi_remote_data.h"

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/render/canvas_image.h"
namespace OHOS::Ace::Framework {

class ACE_EXPORT CJRenderImage : public OHOS::FFI::FFIData, public Referenced {
public:
    CJRenderImage();
    explicit CJRenderImage(const int32_t unit);
    ~CJRenderImage() override = default;

    void InitCJRenderImage(const std::string& src);
    void InitCJRenderImage(const RefPtr<OHOS::Ace::PixelMap>& pixmap);
    double GetHeight();
    double GetWidth();
    std::shared_ptr<Ace::ImageData> GetImageData() const
    {
        return imageData_;
    }

    void SetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
    {
        imageData_ = imageData;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    void SetWidth(double width)
    {
        width_ = width;
    }

    void SetHeight(double height)
    {
        height_ = height;
    }

    void SetPixelMapId(int64_t id)
    {
        pixelMapId_ = id;
    }

    int64_t GetPixelMapId()
    {
        return pixelMapId_;
    }

    RefPtr<PixelMap> GetPixelMap() const
    {
        return pixelMap_;
    }

    std::string GetSrc()
    {
        return src_;
    }

    double GetDensity();

private:
    void LoadImage(const std::string& src);
    void LoadImage(const RefPtr<OHOS::Ace::PixelMap>& pixmap);
    void LoadImage(const ImageSourceInfo& src);
    void OnImageDataReady();
    void OnImageLoadSuccess();
    void OnImageLoadFail(const std::string& errorMsg);

    RefPtr<NG::CanvasImage> image_;
    RefPtr<PixelMap> pixelMap_;
    RefPtr<NG::ImageLoadingContext> loadingCtx_;
    std::shared_ptr<Ace::ImageData> imageData_;
    int64_t pixelMapId_;
    ImageSourceInfo sourceInfo_;
    ImageFit imageFit_ = ImageFit::NONE;

    std::string src_;
    double width_ = 0;
    double height_ = 0;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RENDER_IMAGE_H
