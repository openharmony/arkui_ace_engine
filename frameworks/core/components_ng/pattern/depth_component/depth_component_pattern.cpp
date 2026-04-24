/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/depth_component/depth_component_pattern.h"

#include <algorithm>

#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/depth_component/depth_component_paint_method.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
#include <surface_utils.h>
#include <window.h>
#include "core/common/container.h"
#endif

namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t PERCENT_100 = 100;
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
constexpr uint32_t DEPTH_COMPONENT_NATIVE_WINDOW_COUNT = 2;
constexpr uint32_t SURFACE_QUEUE_SIZE = 5;
constexpr uint32_t DEFAULT_DEPTH_BACKGROUND_COLOR = 0x00000000;
constexpr uint32_t SURFACE_STRIDE_ALIGNMENT = 8;
constexpr float DEFAULT_SCALE = 1.0f;
constexpr float DEFAULT_WIDTH_SCALE = 1.0f;
constexpr float DEFAULT_HEIGHT_SCALE = 1.0f;
constexpr uint32_t ROTATE_90 = 90;
constexpr uint32_t ROTATE_180 = 180;
constexpr uint32_t ROTATE_270 = 270;
constexpr uint32_t ROTATE_0 = 0;

GraphicTransformType RotationToTransform(uint32_t rotation)
{
    switch (rotation) {
        case ROTATE_90:
            return GraphicTransformType::GRAPHIC_ROTATE_90;
        case ROTATE_180:
            return GraphicTransformType::GRAPHIC_ROTATE_180;
        case ROTATE_270:
            return GraphicTransformType::GRAPHIC_ROTATE_270;
        case ROTATE_0:
        default:
            return GraphicTransformType::GRAPHIC_ROTATE_NONE;
    }
}
#endif
} // namespace

RefPtr<NodePaintMethod> DepthComponentPattern::CreateNodePaintMethod()
{
    return MakeRefPtr<DepthComponentPaintMethod>(WeakClaim(this));
}

void DepthComponentPattern::OnAttachToFrameNode()
{
    ACE_SCOPED_TRACE("DepthComponent::OnAttachToFrameNode id=%d gltf=%d", GetHost() ? GetHost()->GetId() : -1,
        IsGltfBackground());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetUsingContentRectForRenderFrame(true);
#ifdef ENABLE_ROSEN_BACKEND
    renderContext->SetFrameGravity(Rosen::Gravity::RESIZE);
#endif
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    rotation_ = pipeline->GetTransformHint();
    auto callbackId = pipeline->RegisterTransformHintChangeCallback([weak = WeakClaim(this)](uint32_t rotation) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->rotation_ = rotation;
    });
    UpdateTransformHintChangedCallbackId(callbackId);
#endif
}

void DepthComponentPattern::OnDetachFromFrameNode(FrameNode* node)
{
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    if (node) {
        auto pipeline = node->GetContextRefPtr();
        if (pipeline) {
            pipeline->RemoveWindowStateChangedCallback(node->GetId());
            if (HasTransformHintChangedCallbackId()) {
                pipeline->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
            }
        }
    }
#else
    (void)node;
#endif
}

void DepthComponentPattern::OnModifyDone()
{
    ACE_SCOPED_TRACE("DepthComponent::OnModifyDone id=%d type=%d", GetHost() ? GetHost()->GetId() : -1,
        static_cast<int32_t>(GetBackgroundSource().type));
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (IsGltfBackground()) {
        RemoveBackgroundImageNode();
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
        InitGltfAdapter();
        if (!gltfWindowsInitialized_) {
            CreateCustomNativeWindows(width3d_, height3d_);
        }
        UpdateGltfScene();
        Update3DScale();
        UpdateWindowChangeSize(true);
        UpdateWindowInfo();
        MarkRender3D();
#endif
    } else {
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
        CleanupGltfResources(true);
#endif
        SetupBackgroundImageNode();
    }

#ifdef ENABLE_ROSEN_BACKEND
    LoadDepthMap();
    TransferDataToRosen();
#endif
}

bool DepthComponentPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    ACE_SCOPED_TRACE("DepthComponent::OnDirtyLayoutWrapperSwap skipMeasure=%d skipLayout=%d sizeChange=%d gltf=%d",
        config.skipMeasure, config.skipLayout, config.contentSizeChange, IsGltfBackground());
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, !(config.skipMeasure || dirty->SkipMeasureContent()));
    auto frameRect = geometryNode->GetFrameRect();
    width3d_ = frameRect.Width();
    height3d_ = frameRect.Height();
    if (IsGltfBackground()) {
        UpdateGltfWindowChange(dirty, config);
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        host->MarkNeedSyncRenderTree();
    }
#else
    (void)dirty;
    (void)config;
#endif
    return !(config.skipMeasure || dirty->SkipMeasureContent());
}

#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
void DepthComponentPattern::OnRebuildFrame()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    for (size_t i = 0; i < surfaceRenderContext_.size(); ++i) {
        renderContext->AddChild(surfaceRenderContext_[i], i);
    }
}
#endif

void DepthComponentPattern::SetBackgroundSource(const OHOS::Ace::DepthBackgroundSource& background)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    CHECK_NULL_VOID(depthLayoutProperty);
    depthLayoutProperty->UpdateBackgroundSource(background);
}

void DepthComponentPattern::SetupBackgroundImageNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto backgroundImage = GetBackgroundImageSource();
    if (!backgroundImage.IsValid()) {
        RemoveBackgroundImageNode();
        return;
    }

    if (backgroundImage.IsSvg()) {
        RemoveBackgroundImageNode();
        return;
    }

    if (!HasBackgroundImageNode()) {
        auto backgroundImageId = GetBackgroundImageId();
        auto backgroundImageNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, backgroundImageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(backgroundImageNode);
        backgroundImageNode->SetHitTestMode(HitTestMode::HTMNONE);
        host->AddChild(backgroundImageNode, 0);
    }

    auto backgroundImageNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, GetBackgroundImageId());
    CHECK_NULL_VOID(backgroundImageNode);
    auto imagePattern = AceType::DynamicCast<ImagePattern>(backgroundImageNode->GetPattern());
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetIsBackground(true);
    auto imageLayoutProperty = backgroundImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);

    imageLayoutProperty->UpdateImageSourceInfo(backgroundImage);
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(PERCENT_100, DimensionUnit::PERCENT), CalcLength(PERCENT_100, DimensionUnit::PERCENT)));
    ApplyBackgroundOffset(backgroundImageNode);
    ApplyBackgroundScale(backgroundImageNode);
    backgroundImageNode->MarkModifyDone();
    backgroundImageNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void DepthComponentPattern::ApplyBackgroundOffset(const RefPtr<FrameNode>& backgroundImageNode)
{
    CHECK_NULL_VOID(backgroundImageNode);
    auto imagePattern = backgroundImageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    if (imagePattern->GetIsAnimation()) {
        return;
    }

    auto layoutProperty = backgroundImageNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    layoutProperty->UpdateNeedOffsetLocalizedEdges(false);
    auto renderContext = backgroundImageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto bgOffset = GetBackgroundOffset();
    if (bgOffset.offsetEdges.has_value()) {
        layoutProperty->UpdateNeedOffsetLocalizedEdges(bgOffset.useLocalizedOffset);
        renderContext->ResetOffset();
        renderContext->UpdateOffsetEdges(bgOffset.offsetEdges.value());
    } else if (bgOffset.offset.has_value()) {
        renderContext->ResetOffsetEdges();
        renderContext->UpdateOffset(bgOffset.offset.value());
    } else {
        renderContext->ResetOffset();
        renderContext->ResetOffsetEdges();
    }
}

void DepthComponentPattern::ApplyBackgroundScale(const RefPtr<FrameNode>& backgroundImageNode)
{
    CHECK_NULL_VOID(backgroundImageNode);
    auto renderContext = backgroundImageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto bgScale = GetBackgroundScale();
    if (bgScale.has_value()) {
        renderContext->UpdateTransformScale(bgScale.value());
    } else {
        renderContext->UpdateTransformScale(NG::VectorF(1.0f, 1.0f));
    }
}

void DepthComponentPattern::RemoveBackgroundImageNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!HasBackgroundImageNode()) {
        return;
    }

    auto backgroundImageNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, GetBackgroundImageId());
    if (!backgroundImageNode) {
        return;
    }

    auto index = host->GetChildIndex(backgroundImageNode);
    if (index >= 0) {
        host->RemoveChildAtIndex(index);
    }

    backgroundImageId_.reset();
}

void DepthComponentPattern::OnPaint3D()
{
    ACE_FUNCTION_TRACE();
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    if (IsGltfBackground() && mrtDepthAdapter_) {
        mrtDepthAdapter_->RenderFrame();
    }
#endif
}

#ifdef ENABLE_ROSEN_BACKEND
void DepthComponentPattern::LoadDepthMap()
{
    ACE_SCOPED_TRACE("DepthComponent::LoadDepthMap key=%s", depthMap_.GetKey().c_str());
    if (!depthMap_.IsValid() || depthMap_.GetKey() == lastLoadedDepthMapKey_) {
        return;
    }
    lastLoadedDepthMapKey_ = depthMap_.GetKey();

    LoadNotifier loadNotifier(
        [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnDepthMapDataReady();
        },
        [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            CHECK_NULL_VOID(pattern->depthMapLoadingCtx_);
            auto canvasImage = pattern->depthMapLoadingCtx_->MoveCanvasImage();
            CHECK_NULL_VOID(canvasImage);
            pattern->OnDepthMapLoadSuccess(canvasImage);
        },
        nullptr);
    depthMapLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(depthMap_, std::move(loadNotifier), false);
    depthMapLoadingCtx_->LoadImageData();
}

void DepthComponentPattern::OnDepthMapDataReady()
{
    CHECK_NULL_VOID(depthMapLoadingCtx_);
    SizeF dstSize = depthMapLoadingCtx_->GetImageSize();
    if (!dstSize.IsPositive()) {
        auto host = GetHost();
        if (host && host->GetGeometryNode()) {
            dstSize = host->GetGeometryNode()->GetContentSize();
        }
    }

    if (!dstSize.IsPositive()) {
        dstSize = SizeF(512.0f, 512.0f);
    }
    depthMapLoadingCtx_->MakeCanvasImage(dstSize, false, ImageFit::COVER);
}

void DepthComponentPattern::OnDepthMapLoadSuccess(const RefPtr<CanvasImage>& canvasImage)
{
    CHECK_NULL_VOID(canvasImage);
    auto pixelMapImage = DynamicCast<NG::PixelMapImage>(canvasImage);
    CHECK_NULL_VOID(pixelMapImage);
    auto pixelMap = pixelMapImage->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto rosenImage = std::make_shared<Rosen::RSImage>();
    rosenImage->SetPixelMap(pixelMap->GetPixelMapSharedPtr());
    auto rsDepthNode = GetRSDepthNode();
    CHECK_NULL_VOID(rsDepthNode);
    rsDepthNode->SetDepthImage(rosenImage);
}

void DepthComponentPattern::TransferDataToRosen()
{
    auto rsDepthNode = GetRSDepthNode();
    CHECK_NULL_VOID(rsDepthNode);
    TransferDepthSpace(rsDepthNode);
    TransferCameraParams(rsDepthNode);
    TransferLightParams(rsDepthNode);
}

std::shared_ptr<OHOS::Rosen::RSDepthNode> DepthComponentPattern::GetRSDepthNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_RETURN(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, nullptr);
    return std::static_pointer_cast<OHOS::Rosen::RSDepthNode>(rsNode);
}

void DepthComponentPattern::TransferDepthSpace(const std::shared_ptr<OHOS::Rosen::RSDepthNode>& rsDepthNode)
{
    CHECK_NULL_VOID(rsDepthNode);
    rsDepthNode->SetDepthSpaceType(static_cast<OHOS::Rosen::DepthSpaceType>(depthSpace_));
}

void DepthComponentPattern::TransferCameraParams(const std::shared_ptr<OHOS::Rosen::RSDepthNode>& rsDepthNode)
{
    ACE_SCOPED_TRACE("DepthComponent::TransferCameraParams gltf=%d", IsGltfBackground());
    CHECK_NULL_VOID(rsDepthNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    CHECK_NULL_VOID(depthLayoutProperty);
    auto cameraParams = depthLayoutProperty->GetCameraParams();
    if (!cameraParams.has_value()) {
        return;
    }

    const auto& camera = cameraParams.value();
    OHOS::Rosen::DepthCameraPara rosenCamera;
    rosenCamera.position = OHOS::Rosen::Vector3f{ camera.position.x, camera.position.y, camera.position.z };
    rosenCamera.quaternion =
        OHOS::Rosen::Vector4f{ camera.quaternion.x, camera.quaternion.y, camera.quaternion.z, camera.quaternion.w };
    rosenCamera.yFov = camera.yFov;
    rosenCamera.zNear = camera.zNear;
    rosenCamera.zFar = camera.zFar;
    rsDepthNode->SetDepthCameraPara(rosenCamera);
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    if (IsGltfBackground()) {
        UpdateGltfCamera();
    }
#endif
}

void DepthComponentPattern::TransferLightParams(const std::shared_ptr<OHOS::Rosen::RSDepthNode>& rsDepthNode)
{
    CHECK_NULL_VOID(rsDepthNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    CHECK_NULL_VOID(depthLayoutProperty);
    auto lightParams = depthLayoutProperty->GetLightParams();
    if (!lightParams.has_value()) {
        return;
    }

    const auto& light = lightParams.value();
    OHOS::Rosen::DepthLightPara rosenLight;
    rosenLight.direction = OHOS::Rosen::Vector3f{ light.direction.x, light.direction.y, light.direction.z };
    rosenLight.color = OHOS::Rosen::Vector3f{ light.color.red, light.color.green, light.color.blue };
    rosenLight.intensity = light.intensity;
    rsDepthNode->SetDepthLightPara(rosenLight);
}
#endif

#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
void DepthComponentPattern::InitGltfAdapter()
{
    ACE_SCOPED_TRACE("DepthComponent::InitGltfAdapter gltf=%d adapter=%d", IsGltfBackground(),
        mrtDepthAdapter_ != nullptr);
    if (!IsGltfBackground()) {
        return;
    }

    auto backgroundSource = GetBackgroundSource();
    if (gltfSceneLoaded_ && mrtDepthAdapter_ && lastLoadedGltfPath_ != backgroundSource.resolvedPath) {
        mrtDepthAdapter_.reset();
        mrtDepthAdapter_ = Render3D::GetMrtDepthAdapterInstance();
        gltfSceneLoaded_ = false;
        nativeWindowSetUp_ = false;
        return;
    }

    if (!mrtDepthAdapter_) {
        mrtDepthAdapter_ = Render3D::GetMrtDepthAdapterInstance();
    }
}

void DepthComponentPattern::UpdateGltfScene()
{
    auto backgroundSource = GetBackgroundSource();
    ACE_SCOPED_TRACE("DepthComponent::UpdateGltfScene gltf=%d windowsReady=%d loaded=%d path=%s",
        backgroundSource.IsGltf(), gltfWindowsInitialized_, gltfSceneLoaded_, backgroundSource.resolvedPath.c_str());
    if (!backgroundSource.IsGltf()) {
        return;
    }

    CHECK_NULL_VOID(mrtDepthAdapter_);
    if (!gltfWindowsInitialized_) {
        return;
    }
    if (lastLoadedGltfPath_ == backgroundSource.resolvedPath && gltfSceneLoaded_) {
        return;
    }

    lastLoadedGltfPath_ = backgroundSource.resolvedPath;
    mrtDepthAdapter_->CreateSceneByGltfUri(lastLoadedGltfPath_);
    gltfSceneLoaded_ = true;
}

void DepthComponentPattern::UpdateGltfCamera()
{
    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(mrtDepthAdapter_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    CHECK_NULL_VOID(depthLayoutProperty);
    auto cameraParams = depthLayoutProperty->GetCameraParams();
    if (!cameraParams.has_value()) {
        return;
    }
    const auto& camera = cameraParams.value();
    Render3D::CameraConfigs configs;
    configs.position_ = { camera.position.x, camera.position.y, camera.position.z };
    configs.rotation_ = { camera.quaternion.x, camera.quaternion.y, camera.quaternion.z, camera.quaternion.w };
    configs.intrinsics_ = { camera.yFov, camera.zNear, camera.zFar };
    mrtDepthAdapter_->SetCameraConfigs(configs);
}

void DepthComponentPattern::UpdateGltfWindowChange(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    ACE_SCOPED_TRACE("DepthComponent::UpdateGltfWindowChange sizeChange=%d windowsReady=%d",
        config.contentSizeChange, gltfWindowsInitialized_);
    if (NearZero(width3d_) || NearZero(height3d_)) {
        return;
    }
    UpdateWindowChangeSize(true);
    UpdateWindowInfo();
    MarkRender3D();
}

void DepthComponentPattern::CleanupGltfResources(bool clearAdapter)
{
    ACE_SCOPED_TRACE("DepthComponent::CleanupGltfResources clearAdapter=%d windows=%zu surfaces=%zu", clearAdapter,
        nativeWindows_.size(), nativeSurfaces_.size());
    
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    for (size_t i = 0; i < surfaceRenderContext_.size(); ++i) {
        renderContext->RemoveChild(surfaceRenderContext_[i]);
    }
    windowChangeInfos_.clear();
    nativeWindows_.clear();
    nativeSurfaceNodes_.clear();
    nativeSurfaces_.clear();
    surfaceRenderContext_.clear();
    gltfWindowsInitialized_ = false;
    gltfSceneLoaded_ = false;
    nativeWindowSetUp_ = false;
    lastLoadedGltfPath_.clear();
    if (clearAdapter) {
        mrtDepthAdapter_.reset();
    }
}

void DepthComponentPattern::CreateCustomNativeWindows(float width, float height)
{
    ACE_SCOPED_TRACE("DepthComponent::CreateCustomNativeWindows width=%.1f height=%.1f current=%zu", width, height,
        nativeWindows_.size());
    if (nativeWindows_.size() == DEPTH_COMPONENT_NATIVE_WINDOW_COUNT) {
        return;
    }
    nativeWindows_.clear();
    nativeSurfaceNodes_.clear();
    nativeSurfaces_.clear();
    windowChangeInfos_.clear();
    for (uint32_t index = 0; index < DEPTH_COMPONENT_NATIVE_WINDOW_COUNT; ++index) {
        RefPtr<RosenRenderContext> renderContextForSurface = MakeRefPtr<RosenRenderContext>();
        CHECK_NULL_VOID(renderContextForSurface);
        auto hostId = std::to_string(GetHost() ? GetHost()->GetId() : 0);
        RenderContext::ContextParam param = { RenderContext::ContextType::SURFACE,
            std::string("DepthComponent_") + hostId + "_" + std::to_string(index) };
        renderContextForSurface->InitContext(false, param);
        surfaceRenderContext_.emplace_back(renderContextForSurface);
        auto surfaceNode =
            OHOS::Rosen::RSBaseNode::ReinterpretCast<OHOS::Rosen::RSSurfaceNode>(renderContextForSurface->GetRSNode());
        GetRenderContext()->AddChild(renderContextForSurface, index);
        CHECK_NULL_VOID(surfaceNode);
        surfaceNode->SetFrameGravity(Rosen::Gravity::RESIZE);
        surfaceNode->SetHardwareEnabled(true);
        auto surface = surfaceNode->GetSurface();
        CHECK_NULL_VOID(surface);
        surface->SetTransformHint(RotationToTransform(rotation_));
        SurfaceUtils::GetInstance()->Add(surface->GetUniqueId(), surface);
        surface->SetQueueSize(SURFACE_QUEUE_SIZE);
        surface->SetUserData("SURFACE_STRIDE_ALIGNMENT", std::to_string(SURFACE_STRIDE_ALIGNMENT));
        surface->SetUserData("SURFACE_FORMAT", std::to_string(OHOS::GRAPHIC_PIXEL_FMT_RGBA_8888));
        surface->SetUserData("SURFACE_WIDTH", std::to_string(static_cast<uint32_t>(width)));
        surface->SetUserData("SURFACE_HEIGHT", std::to_string(static_cast<uint32_t>(height)));
        auto* nativeWindow = CreateNativeWindowFromSurface(&surface);
        if (index == 0) {
            surfaceNode->SetIsDepthBackground(true);
        } else {
            surfaceNode->SetIsDepthResource(true);
        }
        CHECK_NULL_VOID(nativeWindow);
        nativeSurfaceNodes_.emplace_back(surfaceNode);
        nativeSurfaces_.emplace_back(surface);
        nativeWindows_.emplace_back(reinterpret_cast<void*>(nativeWindow));
        auto info = GetWindowChangeInfos(width, height);
        windowChangeInfos_.emplace_back(info);
    }
    gltfWindowsInitialized_ = true;
}

Render3D::WindowChangeInfo DepthComponentPattern::GetWindowChangeInfos(float width, float height) const
{
    Render3D::WindowChangeInfo info;
    info.width = width;
    info.height = height;
    info.scale = DEFAULT_SCALE;
    info.widthScale = DEFAULT_WIDTH_SCALE;
    info.heightScale = DEFAULT_HEIGHT_SCALE;
    info.surfaceType = Render3D::SurfaceType::SURFACE_WINDOW;
    info.backgroundColor = DEFAULT_DEPTH_BACKGROUND_COLOR;
    info.transformType = rotation_;
    info.customNativeWin = nativeWindows_.back();
    return info;
}

void DepthComponentPattern::UpdateWindowChangeSize(bool recreateWindow)
{
    Update3DOffset();
    ACE_SCOPED_TRACE(
        "DepthComponent::UpdateWindowChangeSize width=%.1f height=%.1f", width3d_, height3d_);
    for (size_t index = 0; index < windowChangeInfos_.size(); ++index) {
        auto& info = windowChangeInfos_[index];
        info.width = width3d_;
        info.height = height3d_;
        info.scale = DEFAULT_SCALE;
        info.widthScale = DEFAULT_WIDTH_SCALE;
        info.heightScale = DEFAULT_HEIGHT_SCALE;
        info.recreateWindow = recreateWindow;
        info.surfaceType = Render3D::SurfaceType::SURFACE_WINDOW;
        info.transformType = rotation_;
        info.backgroundColor = DEFAULT_DEPTH_BACKGROUND_COLOR;
        info.customNativeWin = index < nativeWindows_.size() ? nativeWindows_[index] : nullptr;
        if (index < nativeSurfaces_.size() && nativeSurfaces_[index]) {
            nativeSurfaces_[index]->SetTransformHint(RotationToTransform(rotation_));
            nativeSurfaces_[index]->SetUserData("SURFACE_WIDTH", std::to_string(static_cast<uint32_t>(width3d_)));
            nativeSurfaces_[index]->SetUserData("SURFACE_HEIGHT", std::to_string(static_cast<uint32_t>(height3d_)));
        }
        nativeSurfaceNodes_[index]->SetBounds(offsetX_, offsetY_, width3d_, height3d_);
        nativeSurfaceNodes_[index]->SetFrame(offsetX_, offsetY_, width3d_, height3d_);
    }
}

void DepthComponentPattern::Update3DOffset()
{
    auto bgOffset = GetBackgroundOffset();
    if (bgOffset.offsetEdges.has_value()) {
        auto offsetEdges = bgOffset.offsetEdges.value();
        if (offsetEdges.left.has_value()) {
            offsetX_ = offsetEdges.left->ConvertToPx();
        } else if (offsetEdges.right.has_value()) {
            offsetX_ = -offsetEdges.right->ConvertToPx();
        }

        if (offsetEdges.top.has_value()) {
            offsetY_ = offsetEdges.top->ConvertToPx();
        } else if (offsetEdges.bottom.has_value()) {
            offsetY_ = -offsetEdges.bottom->ConvertToPx();
        }

        bool localized = bgOffset.useLocalizedOffset;
        CHECK_NULL_VOID(localized);
        float flag = AceApplicationInfo::GetInstance().IsRightToLeft() ? -1.0 : 1.0;
        if (offsetEdges.start.has_value()) {
            offsetX_ = offsetEdges.start->ConvertToPx() * flag;
        } else if (offsetEdges.end.has_value()) {
            offsetX_ = -offsetEdges.end->ConvertToPx() * flag;
        }
    } else if (bgOffset.offset.has_value()) {
        offsetX_ = bgOffset.offset->GetX().ConvertToPx();
        offsetY_ = bgOffset.offset->GetY().ConvertToPx();
    } else {
        offsetX_ = 0.0;
        offsetY_ = 0.0;
    }
}

void DepthComponentPattern::Update3DScale()
{
    auto bgScale = GetBackgroundScale();
    if (!bgScale.has_value()) {
        return;
    }
    for (size_t index = 0; index < surfaceRenderContext_.size(); ++index) {
        surfaceRenderContext_[index]->UpdateTransformScale(bgScale.value());
    }
}

bool DepthComponentPattern::NeedUpdateWindowInfo()
{
    return !(nativeWindowSetUp_ && NearEqual(lastWidth3d_, width3d_) && NearEqual(lastHeight3d_, height3d_));
}

void DepthComponentPattern::UpdateWindowInfo()
{
    CHECK_NULL_VOID(mrtDepthAdapter_);
    if (!NeedUpdateWindowInfo()) {
        return;
    }

    mrtDepthAdapter_->OnWindowChange(windowChangeInfos_);
    nativeWindowSetUp_ = true;
    lastWidth3d_ = width3d_;
    lastHeight3d_ = height3d_;
}

void DepthComponentPattern::MarkRender3D()
{
    ACE_FUNCTION_TRACE();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

#endif

} // namespace OHOS::Ace::NG
