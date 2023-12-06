/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_OBJECT_H

#include "modules/svg/include/SkSVGDOM.h"

#include "base/image/pixel_map.h"
#include "core/image/animated_image_player.h"
#include "core/image/image_source_info.h"
#include "frameworks/core/components/svg/parse/svg_dom.h"

namespace OHOS::Ace {

class RenderImage;
class ImageObject : public virtual AceType {
    DECLARE_ACE_TYPE(ImageObject, AceType);

public:
#ifndef USE_ROSEN_DRAWING
    static RefPtr<ImageObject> BuildImageObject(
        ImageSourceInfo source, const RefPtr<PipelineBase> context, const sk_sp<SkData>& skData, bool useSkiaSvg);
#else
    static RefPtr<ImageObject> BuildImageObject(ImageSourceInfo source, const RefPtr<PipelineBase> context,
        const std::shared_ptr<RSData>& rsData, bool useSkiaSvg);
#endif

    ImageObject() = default;
    explicit ImageObject(ImageSourceInfo source) : imageSource_(source) {}

    ImageObject(ImageSourceInfo source, const Size& imageSize, int32_t frameCount, bool isSvg = false)
        : imageSource_(source), imageSize_(imageSize), frameCount_(frameCount), isSvg_(isSvg)
    {}
    virtual ~ImageObject() = default;

    static std::string GenerateCacheKey(const ImageSourceInfo& srcInfo, Size targetSize);

    Size GetImageSize()
    {
        return imageSize_;
    }

    void SetImageSize(Size& size)
    {
        imageSize_ = size;
    }

    int32_t GetFrameCount()
    {
        return frameCount_;
    }

    void SetFrameCount(int32_t frameCount)
    {
        frameCount_ = frameCount;
    }

    bool IsSingleFrame() const
    {
        return frameCount_ == 1;
    }

    ImageSourceInfo GetSourceInfo()
    {
        return imageSource_;
    }

    bool IsSvg() const
    {
        return isSvg_;
    }

    bool IsAPng() const
    {
        return isApng_;
    }

    virtual void UploadToGpuForRender(const WeakPtr<PipelineBase>& context,
        const UploadSuccessCallback& successCallback, const FailedCallback& failedCallback, const Size& imageSize,
        bool forceResize, bool syncMode = false)
    {}

    virtual void Pause() {}
    virtual void Resume() {}
    virtual void ClearData() {}

    // this will be called on ui thread when renderImage do perform layout for different image objects.
    virtual void PerformLayoutImageObject(RefPtr<RenderImage> image) {}

    // this will be called on ui thread when renderImage do measure for different image objects.
    virtual Size MeasureForImage(RefPtr<RenderImage> image);

    virtual bool CancelBackgroundTasks()
    {
        return false;
    }

    virtual RefPtr<ImageObject> Clone()
    {
        return MakeRefPtr<ImageObject>(imageSource_, imageSize_, frameCount_, isSvg_);
    }

protected:
    ImageSourceInfo imageSource_;
    Size imageSize_;
    int32_t frameCount_ = 1;
    bool isSvg_ = false;
    bool isApng_ = false;
};

class SvgSkiaImageObject : public ImageObject {
    DECLARE_ACE_TYPE(SvgSkiaImageObject, ImageObject);

public:
    SvgSkiaImageObject(
        ImageSourceInfo source, const Size& imageSize, int32_t frameCount, const sk_sp<SkSVGDOM>& skiaDom)
        : ImageObject(source, imageSize, frameCount, true), skiaDom_(skiaDom)
    {}

    ~SvgSkiaImageObject() override = default;

    const sk_sp<SkSVGDOM>& GetSkiaDom()
    {
        return skiaDom_;
    }

    void PerformLayoutImageObject(RefPtr<RenderImage> image) override;
    Size MeasureForImage(RefPtr<RenderImage> image) override;

    RefPtr<ImageObject> Clone() override
    {
        return MakeRefPtr<SvgSkiaImageObject>(imageSource_, Size(), frameCount_, skiaDom_);
    }

private:
    sk_sp<SkSVGDOM> skiaDom_;
};

class SvgImageObject : public ImageObject {
    DECLARE_ACE_TYPE(SvgImageObject, ImageObject);

public:
    SvgImageObject(ImageSourceInfo source, const Size& imageSize, int32_t frameCount, const RefPtr<SvgDom>& svgDom)
        : ImageObject(source, imageSize, frameCount, true), svgDom_(svgDom)
    {}

    ~SvgImageObject() override = default;

    const RefPtr<SvgDom>& GetSvgDom()
    {
        return svgDom_;
    }

    void PerformLayoutImageObject(RefPtr<RenderImage> image) override;
    Size MeasureForImage(RefPtr<RenderImage> image) override;

    RefPtr<ImageObject> Clone() override
    {
        return MakeRefPtr<SvgImageObject>(imageSource_, Size(), frameCount_, svgDom_);
    }

private:
    RefPtr<SvgDom> svgDom_;
};

class StaticImageObject : public ImageObject {
    DECLARE_ACE_TYPE(StaticImageObject, ImageObject);

public:
    using CancelableTask = CancelableCallback<void()>;
#ifndef USE_ROSEN_DRAWING
    StaticImageObject(ImageSourceInfo source, const Size& imageSize, int32_t frameCount, const sk_sp<SkData>& data)
        : ImageObject(source, imageSize, frameCount), skData_(data)
    {}
#else
    StaticImageObject(
        ImageSourceInfo source, const Size& imageSize, int32_t frameCount, const std::shared_ptr<RSData>& data)
        : ImageObject(source, imageSize, frameCount), data_(data)
    {}
#endif

    ~StaticImageObject() override = default;

    void UploadToGpuForRender(const WeakPtr<PipelineBase>& context, const UploadSuccessCallback& successCallback,
        const FailedCallback& failedCallback, const Size& imageSize, bool forceResize, bool syncMode = false) override;

    void ClearData() override
    {
#ifndef USE_ROSEN_DRAWING
        skData_ = nullptr;
#else
        data_ = nullptr;
#endif
    }

    bool CancelBackgroundTasks() override;

    RefPtr<ImageObject> Clone() override
    {
#ifndef USE_ROSEN_DRAWING
        return MakeRefPtr<StaticImageObject>(imageSource_, imageSize_, frameCount_, skData_);
#else
        return MakeRefPtr<StaticImageObject>(imageSource_, imageSize_, frameCount_, data_);
#endif
    }

private:
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> skData_;
#else
    std::shared_ptr<RSData> data_;
#endif
    CancelableTask uploadForPaintTask_;
};

#ifndef USE_ROSEN_DRAWING
RefPtr<ImageObject> CreateAnimatedImageObject(
    ImageSourceInfo source, const Size& imageSize, int32_t frameCount, const sk_sp<SkData>& data);
#else
RefPtr<ImageObject> CreateAnimatedImageObject(
    ImageSourceInfo source, const Size& imageSize, int32_t frameCount, const std::shared_ptr<RSData>& data);
#endif

class PixelMapImageObject : public ImageObject {
    DECLARE_ACE_TYPE(PixelMapImageObject, ImageObject);

public:
    explicit PixelMapImageObject(const RefPtr<PixelMap>& pixmap) : pixmap_(pixmap)
    {
        imageSize_ = Size(pixmap_->GetWidth(), pixmap_->GetHeight());
    }

    ~PixelMapImageObject() override = default;

    void* GetRawPixelMapPtr()
    {
        return pixmap_->GetRawPixelMapPtr();
    }

    void PerformLayoutImageObject(RefPtr<RenderImage> image) override;
    Size MeasureForImage(RefPtr<RenderImage> image) override;

    void ClearData() override
    {
        pixmap_ = nullptr;
    }

    const RefPtr<PixelMap>& GetPixmap() const
    {
        return pixmap_;
    }

    RefPtr<ImageObject> Clone() override
    {
        return MakeRefPtr<PixelMapImageObject>(pixmap_);
    }

private:
    RefPtr<PixelMap> pixmap_;
};
RefPtr<ImageObject> GetImageSvgDomObj(ImageSourceInfo source, const std::unique_ptr<SkMemoryStream>& svgStream,
    const RefPtr<PipelineBase>& context, std::optional<Color>& color);
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_OBJECT_H
