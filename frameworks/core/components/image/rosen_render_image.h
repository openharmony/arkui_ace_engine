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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_ROSEN_RENDER_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_ROSEN_RENDER_IMAGE_H

#ifndef USE_ROSEN_DRAWING
#include "modules/svg/include/SkSVGDOM.h"

#endif

#include "core/components/image/render_image.h"
#include "core/image/image_provider.h"
#include "frameworks/core/components/svg/parse/svg_dom.h"

namespace OHOS::Ace {

class RosenRenderImage final : public RenderImage, public ImageProviderLoader {
    DECLARE_ACE_TYPE(RosenRenderImage, RenderImage);

public:
    RosenRenderImage();
    ~RosenRenderImage() override;

    void Update(const RefPtr<Component>& component) override;
    void Paint(RenderContext& context, const Offset& offset) override;
    void UpdateData(const std::string& uri, const std::vector<uint8_t>& memData) override;

    void OnHiddenChanged(bool hidden) override;

    void UpLoadImageDataForPaint();

    void PaintBgImage(const std::shared_ptr<RSNode>& rsNode);

    void FetchImageObject() override;

    bool SupportOpacity() override
    {
        return true;
    }

    bool IsSourceWideGamut() const override;
    bool RetryLoading() override;
#ifndef USE_ROSEN_DRAWING
    static SkColorType PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap);
    static SkAlphaType AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap);
    static SkImageInfo MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap);
    static sk_sp<SkColorSpace> ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap);
#else
    static RSColorType PixelFormatToRSColorType(const RefPtr<PixelMap>& pixmap);
    static RSAlphaType AlphaTypeToRSAlphaType(const RefPtr<PixelMap>& pixmap);
    static RSBitmapFormat MakeRSBitmapFormatInfoFromPixelMap(const RefPtr<PixelMap>& pixmap);
#endif
    static void UploadImageObjToGpuForRender(const RefPtr<ImageObject>& imageObj,
        const WeakPtr<PipelineContext> context, UploadSuccessCallback uploadSuccessCallback,
        FailedCallback failedCallback, Size resizeTarget, bool forceResize, bool syncMode = false);

    void ImageDataPaintSuccess(const RefPtr<NG::CanvasImage>& image);
    void ImageObjReady(const RefPtr<ImageObject>& imageObj);
    void ImageObjFailed(const std::string& errorMsg);
    bool NeedUploadImageObjToGpu();

    void SetFetchImageObjBackgroundTask(CancelableTask task)
    {
        if (fetchImageObjTask_) {
            fetchImageObjTask_.Cancel(false);
        }
        fetchImageObjTask_ = task;
    }

    void OnAppHide() override;
    void OnAppShow() override;
    void OnVisibleChanged() override;

    void PerformLayoutPixmap() override;
    void PerformLayoutSvgImage() override;

    Size MeasureForPixmap() override;
    Size MeasureForSvgImage() override;
    Size MeasureForNormalImage() override;

protected:
    bool MaybeRelease() override;
    void ClearRenderObject() override;
    void LayoutImageObject() override;
#ifndef USE_ROSEN_DRAWING
    void* GetSkImage() override
    {
        return reinterpret_cast<void*>(&image_);
    }

    RefPtr<PixelMap> GetPixmapFromSkImage() override;
    SkPixmap CloneSkPixmap(SkPixmap& srcPixmap);
#else
    void* GetDrawingImage() override
    {
        return reinterpret_cast<void*>(&image_);
    }
    RefPtr<PixelMap> GetPixmapFromDrawingImage() override;
#endif
private:
    void InitializeCallbacks();
    Size Measure() override;
    void UpdateRenderAltImage(const RefPtr<Component>& component);
#ifndef USE_ROSEN_DRAWING
    void SetSkRadii(const Radius& radius, SkVector& radii);
#else
    void SetRadii(const Radius& radius, RSPoint& radii);
#endif
    void SetClipRadius();
#ifndef USE_ROSEN_DRAWING
    void CanvasDrawImageRect(SkPaint& paint, const Offset& offset, SkCanvas* canvas, const Rect& paintRect);
    void DrawImageOnCanvas(const Rect& srcRect, const Rect& dstRect, const SkPaint& paint, SkCanvas* canvas) const;
    void PaintSVGImage(const sk_sp<SkData>& skData, bool onlyLayoutSelf = false);
    void DrawSVGImage(const Offset& offset, SkCanvas* canvas);
#else
    void CanvasDrawImageRect(RSBrush& brush, const Offset& offset, RSCanvas* canvas, const Rect& paintRect);
    void DrawImageOnCanvas(const Rect& srcRect, const Rect& dstRect, const RSBrush& brush, RSCanvas* canvas) const;
    void PaintSVGImage(const std::shared_ptr<RSData>& drawingData, bool onlyLayoutSelf = false);
    void DrawSVGImage(const Offset& offset, RSCanvas* canvas);
#endif
    void DrawSVGImageCustom(RenderContext& context, const Offset& offset);
    void UpdateLoadSuccessState();
    Rect RecalculateSrcRect(const Size& realImageSize);
#ifndef USE_ROSEN_DRAWING
    void ApplyColorFilter(SkPaint& paint);
    void ApplyInterpolation(SkPaint& paint);
    void ApplyBorderRadius(const Offset& offset, const Rect& paintRect, SkCanvas* canvas);
#else
    void ApplyColorFilter(RSBrush& brush);
    void ApplyInterpolation(RSBrush& brush);
    void ApplyBorderRadius(const Offset& offset, const Rect& paintRect, RSCanvas* canvas);
#endif
    void AddSvgChild();
    void CreateAnimatedPlayer(const RefPtr<ImageProvider>& provider, SkCodec* codecPtr, bool forceResize);
#ifndef USE_ROSEN_DRAWING
    bool VerifySkImageDataFromPixmap(const RefPtr<PixelMap>& pixmap) const;
#else
    bool VerifyRSImageDataFromPixmap(const RefPtr<PixelMap>& pixmap) const;
#endif
    void CreateSvgNodes();
    void SyncCreateSvgNodes(bool isReady = false);
    void RebuildSvgRenderTree(const SvgRenderTree& svgRenderTree, const RefPtr<SvgDom>& svgDom);
    void CancelBackgroundTasks();
    void CacheImageObject();
    void CacheSvgImageObject();
    RefPtr<ImageObject> QueryCacheSvgImageObject();
    void UpdatePixmap(const RefPtr<PixelMap>& pixmap);
    void UpdateSharedMemoryImage(const RefPtr<PipelineContext>& context);
    void ProcessPixmapForPaint();
    std::function<void()> GenerateThumbnailLoadTask();

    RefPtr<ImageObject> imageObj_;
#ifndef USE_ROSEN_DRAWING
    SkSamplingOptions options_;
#else
    RSSamplingOptions options_;
#endif
    sk_sp<SkSVGDOM> skiaDom_;
    RefPtr<SvgDom> svgDom_;
    RefPtr<NG::CanvasImage> image_;
#ifndef USE_ROSEN_DRAWING
    SkVector radii_[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
#else
    std::vector<RSPoint> radii_ = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
#endif
    Size formerRawImageSize_;
    bool imageDataNotReady_ = false;

    ImageSourceInfo curSourceInfo_;
    ImageObjSuccessCallback imageObjSuccessCallback_;
    UploadSuccessCallback uploadSuccessCallback_;
    FailedCallback failedCallback_;
    OnPostBackgroundTask onPostBackgroundTask_;

    SvgRenderTree svgRenderTree_;

    CancelableTask fetchImageObjTask_;
    bool backgroundTaskCanceled_ = false;

    bool contentChanged_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_ROSEN_RENDER_IMAGE_H
