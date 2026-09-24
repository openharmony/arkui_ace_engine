/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#define NAPI_VERSION 8

#include "core/components_ng/pattern/cached_image/cached_image_pattern.h"
#include "core/components_ng/pattern/cached_image/cached_image_paint_method.h"

#include <array>
#include <dlfcn.h>

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/ace_trace.h"
#include "core/common/container.h"
#include "core/components/image/image_theme.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifdef ENABLE_DRAG_FRAMEWORK
#include "core/common/ace_engine_ext.h"
#include "core/common/udmf/udmf_client.h"
#endif

namespace OHOS::Ace::NG {

constexpr uint64_t MAGIC_HASH_NUM = 31;
constexpr int32_t MEMORY_LEVEL_CRITICAL_STATUS = 2;

static void* g_handle = nullptr;

void CachedImagePattern::PrepareAnimation(const RefPtr<CanvasImage>& image)
{
    CHECK_NULL_VOID(image);
    if (image->IsStatic()) {
        return;
    }
    SetRedrawCallback(image);
    RegisterVisibleAreaChange();
    auto layoutProps = GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    // pause animation if prop is initially set to invisible
    if (layoutProps->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        image->ControlAnimation(false);
    }
}

void CachedImagePattern::SetRedrawCallback(const RefPtr<CanvasImage>& image)
{
    CHECK_NULL_VOID(image);
    // set animation flush function for svg / gif
    image->SetRedrawCallback([weak = WeakPtr(GetHost())] {
        auto imageNode = weak.Upgrade();
        CHECK_NULL_VOID(imageNode);
        imageNode->MarkNeedRenderOnly();
    });
}

void CachedImagePattern::RegisterVisibleAreaChange()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto isVisible = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        LOGD("current image visible ratio = %f", ratio);
        self->OnVisibleChange(visible);
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->AddVisibleAreaChangeNode(host, {0.0f}, isVisible, false);
}

RectF CachedImagePattern::CalcImageContentPaintSize(const RefPtr<GeometryNode>& geometryNode)
{
    RectF paintSize;
    auto imageRenderProperty = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(imageRenderProperty, paintSize);
    ImageRepeat repeat = imageRenderProperty->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    bool isImageRepeatX = repeat == ImageRepeat::REPEAT || repeat == ImageRepeat::REPEAT_X;
    bool isImageRepeatY = repeat == ImageRepeat::REPEAT || repeat == ImageRepeat::REPEAT_Y;

    paintSize.SetWidth(isImageRepeatX ? geometryNode->GetContentSize().Width() : dstRect_.Width());
    paintSize.SetHeight(isImageRepeatY ? geometryNode->GetContentSize().Height() : dstRect_.Height());
    paintSize.SetLeft((isImageRepeatX ? 0 : dstRect_.GetX()) + geometryNode->GetContentOffset().GetX());
    paintSize.SetTop((isImageRepeatY ? 0 : dstRect_.GetY()) + geometryNode->GetContentOffset().GetY());
    return paintSize;
}

void CachedImagePattern::SetImagePaintConfig(
    const RefPtr<CanvasImage>& canvasImage, const RectF& srcRect, const RectF& dstRect, bool isSvg)
{
    auto layoutProps = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);

    ImagePaintConfig config {
        .srcRect_ = srcRect,
        .dstRect_ = dstRect,
    };
    config.imageFit_ = layoutProps->GetImageFit().value_or(ImageFit::COVER);
    config.isSvg_ = isSvg;

    canvasImage->SetPaintConfig(config);
}

RefPtr<NodePaintMethod> CachedImagePattern::CreateNodePaintMethod()
{
    if (image_ != nullptr) {
        return MakeRefPtr<CachedImagePaintMethod>(image_);
    }

    if (imageAlt_ != nullptr) {
        return MakeRefPtr<CachedImagePaintMethod>(imageAlt_);
    }

    CreateObscuredImage();
    if (obscuredImage_ != nullptr) {
        return MakeRefPtr<CachedImagePaintMethod>(obscuredImage_);
    }
    return nullptr;
}

bool CachedImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return true;
}

void CachedImagePattern::CreateObscuredImage()
{
    auto props = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto reasons = renderContext->GetObscured().value_or(std::vector<ObscuredReasons>());
    if (reasons.size() != 0 && layoutConstraint->selfIdealSize.IsValid()) {
        if (obscuredImage_ == nullptr) {
            obscuredImage_ = MakeRefPtr<ObscuredImage>();
            SetImagePaintConfig(obscuredImage_, srcRect_, dstRect_, false);
        }
    }
}

void CachedImagePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);

    instanceId_ = ContainerScope::CurrentId();
    LoadImageData(std::string(__FUNCTION__));
}

bool CachedImagePattern::hasLoadImageLoader()
{
    if (g_handle == nullptr) {
        LOGI("start dlopen %{public}s", IMAGE_LOADER_SO_PATH);
        g_handle = dlopen(IMAGE_LOADER_SO_PATH, RTLD_NOW);
        if (g_handle == nullptr) {
            LOGE("dlopen %{public}s, failed:%{public}s", IMAGE_LOADER_SO_PATH, dlerror());
            return false;
        }
    }
    return true;
}

bool CachedImagePattern::NeedToLoadImage()
{
    if (sources_.empty() && (src_.empty() || src_ == imageRequestInfo_.src) && image_ != nullptr) {
        // src_ not changed and image_ loaded, no need to load image.
        LOGD("src_ not changed and image_ loaded, no need to load image.");
        return false;
    }
    return true;
}

void CachedImagePattern::ClearImageRequestInfo()
{
    imageRequestInfo_.identifier = UINT64_MAX;
    imageRequestInfo_.src = "";
    if (!imageRequestInfo_.srcs.empty()) {
        imageRequestInfo_.srcs.clear();
    }
}

bool CachedImagePattern::IsLoadPixelmap()
{
    if (pixmap_ == nullptr) {
        return false;
    }

    SetCachedImageSize(pixmap_, image_);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    host->MarkNeedRenderOnly();
    LOGD("CachedImage pixmap is not null");
    ClearImageRequestInfo();
    return true;
}

uint64_t CachedImagePattern::GetImageRequestIdentifier(ImageRequestInfo reqInfo)
{
    uint64_t identifier = 0;
    uint64_t size = reqInfo.srcs.size();
    if (!reqInfo.src.empty()) {
        identifier = MAGIC_HASH_NUM * identifier + std::hash<std::string>{}(reqInfo.src);
        identifier = MAGIC_HASH_NUM * identifier + std::hash<std::uint32_t>{}(reqInfo.requestOptionsInfo.width);
        identifier = MAGIC_HASH_NUM * identifier + std::hash<std::uint32_t>{}(reqInfo.requestOptionsInfo.height);
    }
    if (!reqInfo.srcs.empty()) {
        if (size == 1) {
            identifier = MAGIC_HASH_NUM * identifier + std::hash<std::string>{}(reqInfo.srcs[0]);
            identifier = MAGIC_HASH_NUM * identifier + size;
        } else {
            identifier = MAGIC_HASH_NUM * identifier + std::hash<std::string>{}(reqInfo.srcs[0]);
            identifier = MAGIC_HASH_NUM * identifier + std::hash<std::string>{}(reqInfo.srcs[size - 1]);
            identifier = MAGIC_HASH_NUM * identifier + size;
        }
        identifier = MAGIC_HASH_NUM * identifier + std::hash<std::uint32_t>{}(reqInfo.requestOptionsInfo.row);
        identifier = MAGIC_HASH_NUM * identifier + std::hash<std::uint32_t>{}(reqInfo.requestOptionsInfo.column);
    }
    auto host = GetHost();
    if (host != nullptr) {
        identifier = MAGIC_HASH_NUM * identifier + std::hash<std::uint32_t>{}(host->GetId());
    }
    return identifier;
}

void CachedImagePattern::LoadImageData(const std::string& type)
{
    LoadImageDataIfNeed(type);
    LoadAltImageDataIfNeed();
}

void CachedImagePattern::InitLoadingData()
{
    if (imageRequestInfo_.target == nullptr) {
        imageRequestInfo_.target = new OHOS::Media::ImageTarget();
        // receive original image width and height callback notification
        OHOS::Media::TargetListener targetListener;
        targetListener.onSourceSizeReady = [weak = WeakClaim(this)](uint64_t requestId, uint64_t identifier,
            int32_t width, int32_t height, bool isFromUiThread) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnTargetSourceSizeReady(requestId, identifier, width, height, isFromUiThread);
        };

        // receive request end callback notification
        targetListener.onRequestComplete = [weak = WeakClaim(this)](uint64_t requestId, uint64_t identifier,
            const std::shared_ptr<OHOS::Media::PixelMap>& pixelMap, const std::string& message, bool isFromUiThread) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pixelMap == nullptr) {
                LOGE("pixelMap is null");
                pattern->OnFail(requestId, identifier, message, isFromUiThread);
                return;
            }
            pattern->OnComplete(requestId, identifier, pixelMap, isFromUiThread);
        };
        imageRequestInfo_.target->RegisterTargetListener(targetListener);
    }

    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID(container);
    imageRequestInfo_.token = container->GetToken();
    imageRequestInfo_.src = src_;
    imageRequestInfo_.srcs = sources_;
    imageRequestInfo_.identifier = GetImageRequestIdentifier(imageRequestInfo_);
    imageRequestInfo_.requestOptionsInfo.isHdr = false;
    imageRequestInfo_.requestOptionsInfo.imageQuality = 0;
    imageRequestInfo_.context = nullptr;
}

void CachedImagePattern::LoadImageDataIfNeed(const std::string& type)
{
    if (IsLoadPixelmap()) {
        return;
    }
    if (!NeedToLoadImage()) {
        return;
    }
    if (!hasLoadImageLoader()) {
        return;
    }

    image_ = nullptr;
    InitLoadingData();

    auto func = reinterpret_cast<RequestImageFunc>(dlsym(g_handle, FUNC_REQUEST_IMAGE));
    if (func == nullptr) {
        LOGE("dlsym %{public}s failed. %{public}s", FUNC_REQUEST_IMAGE, dlerror());
        dlclose(g_handle);
        g_handle = nullptr;
        return;
    }

    ACE_SCOPED_TRACE("CachedImage LoadData, type:%s", type.c_str());
    func(imageRequestInfo_);
}

void CachedImagePattern::LoadAltImageDataIfNeed()
{
    if (pixmap_ != nullptr || image_ != nullptr || pixelmapAlt_ == nullptr) {
        return;
    }
    ACE_SCOPED_TRACE("CachedImage Alt Load %s", src_.c_str());

    SetCachedImageSize(pixelmapAlt_, imageAlt_, true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    if (context && imageAlt_) {
        auto pixelMapOhos = imageAlt_->GetPixelMap();
        if (pixelMapOhos) {
            context->SetColorGamut(pixelMapOhos->GetInnerColorGamut());
        }
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CachedImagePattern::CancelImageRequest()
{
    if (!hasLoadImageLoader()) {
        return;
    }

    auto func = reinterpret_cast<CancelImageRequestFunc>(dlsym(g_handle, FUNC_CANCEL_IMAGE_REQUEST));
    if (func == nullptr) {
        LOGE("dlsym %{public}s failed. %{public}s", FUNC_CANCEL_IMAGE_REQUEST, dlerror());
        dlclose(g_handle);
        g_handle = nullptr;
        return;
    }

    func(imageRequestInfo_);
}

void CachedImagePattern::OnTargetSourceSizeReady(uint64_t requestId, uint64_t identifier,
    int32_t width, int32_t height, bool isFromUiThread)
{
    if (isFromUiThread) {
        OnPatternSourceSizeReady(requestId, identifier, width, height, isFromUiThread);
    } else {
        ContainerScope scope(instanceId_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this), id = Container::CurrentId(),
            requestId, identifier, width, height, isFromUiThread] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnPatternSourceSizeReady(requestId, identifier, width, height, isFromUiThread);
            }, "ArkUICachedImageSourceSizeReady");
    }
}

void CachedImagePattern::SetCachedImageSize(const RefPtr<PixelMap>& pixelMap, RefPtr<CanvasImage>& image, bool isAlt)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    image = CanvasImage::Create(pixelMap);
    CHECK_NULL_VOID(image);
    auto wrapper = DynamicCast<LayoutAlgorithmWrapper>(host->GetLayoutAlgorithm(false));
    CHECK_NULL_VOID(wrapper);
    auto cachedImageLayoutAlgorithm = DynamicCast<CachedImageLayoutAlgorithm>(wrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(cachedImageLayoutAlgorithm);

    srcRect_ = cachedImageLayoutAlgorithm->GetSrcRect();
    dstRect_ = cachedImageLayoutAlgorithm->GetDstRect();

    if (!isAlt) {
        const auto& geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        RectF paintRect = CalcImageContentPaintSize(geometryNode);
        LoadImageSuccessEvent event(pixelMap->GetWidth(), pixelMap->GetHeight(),
            geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), 1, paintRect.Width(),
            paintRect.Height(), paintRect.GetX(), paintRect.GetY());
        auto eventHub = GetEventHub<ImageEventHub>();
        if (eventHub != nullptr) {
            eventHub->FireCompleteEvent(event);
        }
    }

    SetImagePaintConfig(image, srcRect_, dstRect_, false);
    PrepareAnimation(image);
    if (host->IsDraggable()) {
        EnableDrag();
    }
}

void CachedImagePattern::OnPatternSourceSizeReady(uint64_t requestId, uint64_t identifier,
    int32_t width, int32_t height, bool isFromUiThread)
{
    if (identifier != 0 && imageRequestInfo_.identifier != 0 && identifier != imageRequestInfo_.identifier) {
        return;
    }

    if (!isFromUiThread) {
        ACE_SCOPED_TRACE("CachedImage OnSourceSizeReady, id:[%ld], w:%d, h:%d", requestId, width, height);
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto wrapper = DynamicCast<LayoutAlgorithmWrapper>(frameNode->GetLayoutAlgorithm(false));
    CHECK_NULL_VOID(wrapper);
    auto layoutAlgorithm = DynamicCast<CachedImageLayoutAlgorithm>(wrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithm);
    layoutAlgorithm->SetImageSize(SizeF(width, height));

    // if the width and height are not set, wait until the layout is complete and callback targetsize
    if (imageRequestInfo_.requestOptionsInfo.width == 0 || imageRequestInfo_.requestOptionsInfo.height == 0) {
        layoutAlgorithm->RegisterLayoutCallback([weak = WeakClaim(this), requestId](SizeF targetSize) {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            OHOS::sptr<OHOS::Media::ImageTarget> target = self->imageRequestInfo_.target;
            if (target == nullptr) {
                LOGE("OnSizeReady failed, target is null, id:[%{public}ld]", requestId);
                return;
            }
            OHOS::Media::OnSizeReadyCallback onSizeReady = target->GetSizeReadyCallback();
            if (onSizeReady != nullptr) {
                LOGD("target->OnSizeReady, id:[%{public}ld], width:%{public}f, height:%{public}f",
                    requestId, targetSize.Width(), targetSize.Height());
                onSizeReady(targetSize.Width(), targetSize.Height());
            }
        });
    }
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void CachedImagePattern::OnComplete(uint64_t requestId, uint64_t identifier,
    const std::shared_ptr<Media::PixelMap>& pixelMap, bool isFromUiThread)
{
    if (isFromUiThread) {
        OnImageLoadSuccess(requestId, identifier, pixelMap);
    } else {
        ContainerScope scope(instanceId_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this), requestId, identifier, pixelMap] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnImageLoadSuccess(requestId, identifier, pixelMap);
            }, "ArkUICachedImageLoadSuccess");
    }
}

void CachedImagePattern::OnImageLoadSuccess(uint64_t requestId, uint64_t identifier,
    const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    if (identifier != 0 && imageRequestInfo_.identifier != 0 && identifier != imageRequestInfo_.identifier) {
        return;
    }

    // When the CachedImage component is recycled,
    // ignore the callback of the image loading request initiated before the recycling
    if (isRecycled_) {
        return;
    }

    ACE_SCOPED_TRACE("CachedImage OnImageLoadSuccess, id:[%ld]", requestId);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("CachedImage OnImageLoadSuccess, id:[%{public}ld], nodeId:%{public}d", requestId, host->GetId());
    SetCachedImageSize(AceType::MakeRefPtr<PixelMapOhos>(std::shared_ptr<Media::PixelMap>(pixelMap)), image_);
    auto context = host->GetRenderContext();
    if (context && image_) {
        auto pixelMapOhos = image_->GetPixelMap();
        if (pixelMapOhos) {
            context->SetColorGamut(pixelMapOhos->GetInnerColorGamut());
        }
    }
    host->MarkNeedRenderOnly();
}

void CachedImagePattern::OnFail(uint64_t requestId, uint64_t identifier,
    const std::string& message, bool isFromUiThread)
{
    if (isFromUiThread) {
        OnImageLoadFail(requestId, identifier, message);
    } else {
        ContainerScope scope(instanceId_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this), requestId, identifier, message] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnImageLoadFail(requestId, identifier, message);
            }, "ArkUICachedImageLoadFail");
    }
}

void CachedImagePattern::OnImageLoadFail(uint64_t requestId, uint64_t identifier, const std::string& message)
{
    if (identifier != 0 && imageRequestInfo_.identifier != 0 && identifier != imageRequestInfo_.identifier) {
        return;
    }

    // When the CachedImage component is recycled,
    // ignore the callback of the image loading request initiated before the recycling
    if (isRecycled_) {
        return;
    }

    ACE_SCOPED_TRACE("CachedImage OnImageLoadFail, id:[%ld]", requestId);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("CachedImage OnImageLoadFail, id:[%{public}ld], nodeId:%{public}d", requestId, host->GetId());
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto imageEventHub = GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    LoadImageFailEvent loadImageFailEvent_(
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), message);
    imageEventHub->FireErrorEvent(std::move(loadImageFailEvent_));
}

void CachedImagePattern::OnNotifyMemoryLevel(int32_t level)
{
    LOGD("Receive Memory level notification, level: %{public}d", level);
    if (isShow_) {
        return;
    }

    if (level != MEMORY_LEVEL_CRITICAL_STATUS) {
        LOGI("Receive Memory level notification, non critical, skip");
        return;
    }

    // clean image data
    image_ = nullptr;
    pixmap_ = nullptr;

    // clean alt image data
    imageAlt_ = nullptr;
    pixelmapAlt_ = nullptr;

    // clean rs node to release the sk_sp<SkImage> held by it
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->ClearDrawCommands();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushMessages();
}

// when recycle image component, release the pixelmap resource
void CachedImagePattern::OnRecycle()
{
    isRecycled_ = true;
    image_ = nullptr;
    pixmap_ = nullptr;
    CancelImageRequest();
    imageAlt_ = nullptr;
    pixelmapAlt_ = nullptr;

    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->ClearDrawCommands();
    UnregisterWindowStateChangedCallback();
}

void CachedImagePattern::OnReuse()
{
    isRecycled_ = false;
    RegisterWindowStateChangedCallback();
    LoadImageData(std::string(__FUNCTION__));
}

void CachedImagePattern::OnWindowHide()
{
    isShow_ = false;
}

void CachedImagePattern::OnWindowShow()
{
    isShow_ = true;
    LoadImageData(std::string(__FUNCTION__));
}

void CachedImagePattern::OnVisibleChange(bool isVisible)
{
    // control svg / gif animation
    if (image_ != nullptr) {
        image_->ControlAnimation(isVisible);
    } else if (imageAlt_ != nullptr) {
        imageAlt_->ControlAnimation(isVisible);
    }

    if (!isVisible) {
        CancelImageRequest();
    } else {
        LoadImageData(std::string(__FUNCTION__));
    }
}

void CachedImagePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderCtx = host->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    renderCtx->SetClipToBounds(false);
    renderCtx->SetUsingContentRectForRenderFrame(true);

    // register image frame node to pipeline context to receive memory level notification
    // and window state change notification
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddNodesToNotifyMemoryLevel(host->GetId());
    pipeline->AddWindowStateChangedCallback(host->GetId());
    // set draggable for framenode
    auto theme = pipeline->GetTheme<ImageTheme>();
    CHECK_NULL_VOID(theme);
    auto isDraggable = theme->GetDraggable();
    if (isDraggable && !host->IsDraggable()) {
        auto gestureHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->InitDragDropEvent();
    }
    host->SetDraggable(isDraggable);
}

void CachedImagePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveNodesToNotifyMemoryLevel(id);

    CancelImageRequest();
}

void CachedImagePattern::EnableDrag()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dragStart = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string&
        /* extraParams */) -> DragDropInfo {
        DragDropInfo info;
        auto cachedImagePattern = weak.Upgrade();
        CHECK_NULL_RETURN(cachedImagePattern, info);

#ifdef ENABLE_DRAG_FRAMEWORK
        AceEngineExt::GetInstance().DragStartExt();
#endif
        cachedImagePattern->UpdateDragEvent(event);
        info.extraInfo = cachedImagePattern->src_;
        return info;
    };
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnDragStart()) {
        eventHub->SetOnDragStart(std::move(dragStart));
    }
}

void CachedImagePattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    json->PutExtAttr("draggable", host->IsDraggable() ? "true" : "false", filter);
}

void CachedImagePattern::UpdateDragEvent(const RefPtr<OHOS::Ace::DragEvent>& event)
{
#ifdef ENABLE_DRAG_FRAMEWORK
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    CHECK_NULL_VOID(image_);
    auto pixelMap = image_->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    const uint8_t* pixels = pixelMap->GetPixels();
    CHECK_NULL_VOID(pixels);
    int32_t length = pixelMap->GetByteCount();
    std::vector<uint8_t> data(pixels, pixels + length);
    PixelMapRecordDetails details = { pixelMap->GetWidth(), pixelMap->GetHeight(), pixelMap->GetPixelFormat(),
        pixelMap->GetAlphaType() };
    UdmfClient::GetInstance()->AddPixelMapRecord(unifiedData, data, details);
    if (event != nullptr) {
        event->SetData(unifiedData);
    }
#endif
}

} // namespace OHOS::Ace::NG