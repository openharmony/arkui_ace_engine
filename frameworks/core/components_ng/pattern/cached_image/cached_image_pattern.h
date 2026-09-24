/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CACHED_IMAGE_CACHED_IMAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CACHED_IMAGE_CACHED_IMAGE_PATTERN_H

#include <memory>

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/cached_image/cached_image_layout_algorithm.h"
#include "core/components_ng/pattern/cached_image/image_loader_ext_def.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CachedImagePattern : public ImagePattern {
    DECLARE_ACE_TYPE(CachedImagePattern, ImagePattern);

public:
    CachedImagePattern() = default;
    ~CachedImagePattern() override = default;

    void Create(const std::string& src, RefPtr<PixelMap>& pixmap)
    {
        src_ = src;
        pixmap_ = pixmap;
    }

    void Create(const std::vector<std::string>& sources, int32_t column)
    {
        sources_ = sources;
        imageRequestInfo_.requestOptionsInfo.column = column;
    }

    void SetRequestOptions(const SizeF& sourceSize) {
        imageRequestInfo_.requestOptionsInfo.width = sourceSize.Width();
        imageRequestInfo_.requestOptionsInfo.height = sourceSize.Height();
    }

    void SetAlt(const RefPtr<PixelMap>& pixelmapAlt)
    {
        pixelmapAlt_ = pixelmapAlt;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CachedImageLayoutAlgorithm>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    const RefPtr<CanvasImage>& GetCanvasImage()
    {
        return image_;
    }

    void CreateObscuredImage();
    void OnNotifyMemoryLevel(int32_t level) override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void OnVisibleChange(bool isVisible) override;
    void OnRecycle() override;
    void OnReuse() override;

    void EnableDrag();

    void OnComplete(uint64_t requestId, uint64_t identifier,
        const std::shared_ptr<Media::PixelMap>& pixelMap, bool isFromUiThread);
    void OnFail(uint64_t requestId, uint64_t identifier, const std::string& message, bool isFromUiThread);
    void OnTargetSourceSizeReady(uint64_t requestId, uint64_t identifier,
        int32_t width, int32_t height, bool isFromUiThread);

    uint64_t GetImageRequestIdentifier(ImageRequestInfo imageRequestInfo);

private:
    class ObscuredImage : public CanvasImage {
        void DrawToRSCanvas(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect,
            const BorderRadiusArray& radiusXY) override
        {}
        int32_t GetWidth() const override
        {
            return 0;
        }
        int32_t GetHeight() const override
        {
            return 0;
        }
    };

    bool hasLoadImageLoader();
    bool NeedToLoadImage();
    bool IsLoadPixelmap();
    void InitLoadingData();
    void LoadImageDataIfNeed(const std::string& type);
    void CancelImageRequest();
    void LoadAltImageDataIfNeed();
    void LoadImageData(const std::string& type);
    void ClearImageRequestInfo();

    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void OnModifyDone() override;

    void OnImageLoadSuccess(uint64_t requestId, uint64_t identifier, const std::shared_ptr<Media::PixelMap>& pixelMap);
    void OnImageLoadFail(uint64_t requestId, uint64_t identifier, const std::string& message);
    void OnPatternSourceSizeReady(uint64_t requestId, uint64_t identifier,
        int32_t width, int32_t height, bool isFromUiThread);

    void SetImagePaintConfig(
        const RefPtr<CanvasImage>& canvasImage, const RectF& srcRect, const RectF& dstRect, bool isSvg);
    void UpdateInternalResource(ImageSourceInfo& sourceInfo);

    void PrepareAnimation(const RefPtr<CanvasImage>& image);
    void SetRedrawCallback(const RefPtr<CanvasImage>& image);
    void RegisterVisibleAreaChange();

    void UpdateDragEvent(const RefPtr<OHOS::Ace::DragEvent>& event);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void RegisterSizeReadyCallback();

    RectF CalcImageContentPaintSize(const RefPtr<GeometryNode>& geometryNode);

    void SetCachedImageSize(const RefPtr<PixelMap>& pixelMap, RefPtr<CanvasImage>& image, bool isAlt = false);

    RefPtr<CanvasImage> image_;
    RefPtr<CanvasImage> imageAlt_;
    RefPtr<PixelMap> pixmap_;
    RefPtr<PixelMap> pixelmapAlt_;
    RefPtr<CanvasImage> obscuredImage_;
    RectF dstRect_;
    RectF srcRect_;

    bool isShow_{true};
    bool isRecycled_{false};
    std::string src_;
    std::vector<std::string> sources_;
    int32_t instanceId_{-1};

    ImageRequestInfo imageRequestInfo_;

    ACE_DISALLOW_COPY_AND_MOVE(CachedImagePattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CACHED_IMAGE_CACHED_IMAGE_PATTERN_H