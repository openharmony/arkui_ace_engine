/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"

#include "base/log/dump_log.h"
#include "core/accessibility/accessibility_session_adapter.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"

namespace OHOS::Ace::NG {

namespace {
inline std::string BoolToString(bool value)
{
    return value ? "true" : "false";
}
} // namespace

XComponentPatternV2::XComponentPatternV2(XComponentType type, XComponentNodeType nodeType)
    : XComponentPattern((nodeType == XComponentNodeType::CNODE) ? std::make_optional<std::string>("") : std::nullopt,
          type, (nodeType == XComponentNodeType::CNODE) ? std::make_optional<std::string>("") : std::nullopt, nullptr)
{
    nodeType_ = nodeType;
    if (nodeType == XComponentNodeType::CNODE) {
        isCNode_ = true;
    }
}

void XComponentPatternV2::SetSurfaceHolder(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    surfaceHolder_ = surfaceHolder;
    if (surfaceHolder_) {
        surfaceHolder_->nativeWindow_ = reinterpret_cast<OHNativeWindow*>(nativeWindow_);
        hasGotSurfaceHolder_ = true;
    }
}

OH_ArkUI_SurfaceHolder* XComponentPatternV2::GetSurfaceHolder()
{
    return surfaceHolder_;
}

void XComponentPatternV2::OnAttachToFrameNode()
{
    if (nodeType_ ==  XComponentNodeType::CNODE) {
        XComponentPattern::OnAttachToFrameNode();
        return;
    }
    InitSurface();
    InitNativeWindow(0.0, 0.0);
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EnableSelfRender();
    }
}

void XComponentPatternV2::OnAttachToMainTree()
{
    if (nodeType_ ==  XComponentNodeType::CNODE && !isLifecycleInterfaceCalled_ && !surfaceHolder_) {
        usesSuperMethod_ = true;
        XComponentPattern::OnAttachToMainTree();
        return;
    }
    if (autoInitialize_) {
        HandleSurfaceCreated();
    }
}

void XComponentPatternV2::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    if (usesSuperMethod_) {
        XComponentPattern::BeforeSyncGeometryProperties(config);
        return;
    }
    if (config.skipMeasure) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    drawSize_ = geometryNode->GetContentSize();
    if (!drawSize_.IsPositive()) {
        TAG_LOGW(
            AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s]'s size is not positive", GetId().c_str());
        return;
    }
    localPosition_ = geometryNode->GetContentOffset();
    const auto& [offsetChanged, sizeChanged] = UpdateSurfaceRect();
    HandleSurfaceChangeEvent(offsetChanged, sizeChanged, config.frameOffsetChange);
    AddAfterLayoutTaskForExportTexture();
    host->MarkNeedSyncRenderTree();
}

std::pair<bool, bool> XComponentPatternV2::UpdateSurfaceRect()
{
    if (!drawSize_.IsPositive()) {
        return { false, false };
    }
    auto preSurfaceSize = surfaceSize_;
    auto preSurfaceOffset = surfaceOffset_;

    surfaceSize_ = drawSize_;
    surfaceOffset_ = localPosition_;
    auto offsetChanged = preSurfaceOffset != surfaceOffset_;
    auto sizeChanged = preSurfaceSize != surfaceSize_;
    if (offsetChanged || sizeChanged) {
        paintRect_ = AdjustPaintRect(
            surfaceOffset_.GetX(), surfaceOffset_.GetY(), surfaceSize_.Width(), surfaceSize_.Height(), true);
    }
    return { offsetChanged, sizeChanged };
}

void XComponentPatternV2::HandleSurfaceChangeEvent(bool offsetChanged, bool sizeChanged, bool frameOffsetChange)
{
    if (!drawSize_.IsPositive()) {
        return;
    }
    if (sizeChanged) {
        XComponentSizeChange(paintRect_);
    }
    if (renderContextForSurface_) {
        renderContextForSurface_->SetBounds(
            paintRect_.GetX(), paintRect_.GetY(), paintRect_.Width(), paintRect_.Height());
    }
    if (renderSurface_) {
        renderSurface_->SetSurfaceDefaultSize(
            static_cast<int32_t>(paintRect_.Width()), static_cast<int32_t>(paintRect_.Height()));
    }
}

void XComponentPatternV2::XComponentSizeChange(const RectF& surfaceRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto viewScale = context->GetViewScale();
    CHECK_NULL_VOID(renderSurface_);
    auto width = surfaceRect.Width();
    auto height = surfaceRect.Height();
    renderSurface_->UpdateSurfaceSizeInUserData(
        static_cast<uint32_t>(width), static_cast<uint32_t>(height));
    renderSurface_->AdjustNativeWindowSize(
        static_cast<uint32_t>(width * viewScale), static_cast<uint32_t>(height * viewScale));
    OnSurfaceChanged(surfaceRect);
}

void XComponentPatternV2::OnSurfaceChanged(const RectF& surfaceRect)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(surfaceHolder_);
    CHECK_EQUAL_VOID(isInitialized_, false);
    ACE_SCOPED_TRACE("XComponent[%s] surfaceHolder OnSurfaceChanged", GetId().c_str());
    auto callbackList = surfaceHolder_->surfaceCallbackList_;
    for (const auto& iter : callbackList) {
        auto callback = iter->OnSurfaceChanged;
        if (callback) {
            callback(surfaceHolder_, surfaceRect.Width(), surfaceRect.Height());
        }
    }
}

void XComponentPatternV2::OnDetachFromMainTree()
{
    if (usesSuperMethod_) {
        XComponentPattern::OnDetachFromMainTree();
        return;
    }
    if (autoInitialize_) {
        HandleSurfaceDestroyed();
    }
}

void XComponentPatternV2::OnDetachFromFrameNode(FrameNode* frameNode)
{
    if (usesSuperMethod_) {
        XComponentPattern::OnDetachFromFrameNode(frameNode);
        return;
    }
    auto id = frameNode->GetId();
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    if (HasTransformHintChangedCallbackId()) {
        pipeline->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
    }
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().DisableSelfRender();
    }
    HandleSurfaceDestroyed();
    
    CHECK_NULL_VOID(surfaceHolder_);
    surfaceHolder_->nativeWindow_ = nullptr;
    surfaceHolder_->node_ = nullptr;
}

void XComponentPatternV2::InitSurface()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderContext->SetClipToFrame(true);
    renderContext->SetClipToBounds(true);
    renderSurface_ = RenderSurface::Create();
    renderSurface_->SetInstanceId(GetHostInstanceId());
    if (type_ == XComponentType::SURFACE) {
        InitializeRenderContext();
        renderSurface_->SetRenderContext(renderContextForSurface_);
    } else if (type_ == XComponentType::TEXTURE) {
        renderSurface_->SetRenderContext(renderContext);
        renderSurface_->SetIsTexture(true);
    }
    renderSurface_->InitSurface();
    renderSurface_->UpdateSurfaceConfig();
    if (type_ == XComponentType::TEXTURE) {
        renderSurface_->RegisterBufferCallback();
    }
    surfaceId_ = renderSurface_->GetUniqueId();

    UpdateTransformHint();
}

int32_t XComponentPatternV2::HandleSurfaceCreated()
{
    if (isInitialized_) {
        return ERROR_CODE_XCOMPONENT_STATE_INVALID;
    }
    CHECK_NULL_RETURN(renderSurface_, ERROR_CODE_PARAM_INVALID);
    renderSurface_->RegisterSurface();
    surfaceId_ = renderSurface_->GetUniqueId();
    isInitialized_ = true;
    if (surfaceHolder_) {
        auto callbackList = surfaceHolder_->surfaceCallbackList_;
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] surfaceHolder OnSurfaceCreated", GetId().c_str());
        ACE_SCOPED_TRACE("XComponent[%s] surfaceHolder OnSurfaceCreated", GetId().c_str());
        for (const auto& iter : callbackList) {
            auto callback = iter->OnSurfaceCreated;
            if (callback) {
                callback(surfaceHolder_);
            }
        }
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t XComponentPatternV2::HandleSurfaceDestroyed()
{
    if (!isInitialized_) {
        return ERROR_CODE_XCOMPONENT_STATE_INVALID;
    }
    isInitialized_ = false;
    CHECK_NULL_RETURN(renderSurface_, ERROR_CODE_PARAM_INVALID);
    renderSurface_->ReleaseSurfaceBuffers();
    renderSurface_->UnregisterSurface();
    if (surfaceHolder_) {
        auto callbackList = surfaceHolder_->surfaceCallbackList_;
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] surfaceHolder OnSurfaceDestroyed", GetId().c_str());
        ACE_SCOPED_TRACE("XComponent[%s] surfaceHolder OnSurfaceDestroyed", GetId().c_str());
        for (const auto& iter : callbackList) {
            auto callback = iter->OnSurfaceDestroyed;
            if (callback) {
                callback(surfaceHolder_);
            }
        }
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t XComponentPatternV2::Initialize()
{
    if (usesSuperMethod_) {
        return ERROR_CODE_PARAM_INVALID;
    }
    isLifecycleInterfaceCalled_ = true;
    return HandleSurfaceCreated();
}

int32_t XComponentPatternV2::Finalize()
{
    if (usesSuperMethod_) {
        return ERROR_CODE_PARAM_INVALID;
    }
    isLifecycleInterfaceCalled_ = true;
    return HandleSurfaceDestroyed();
}

int32_t XComponentPatternV2::SetAutoInitialize(bool autoInitialize)
{
    if (usesSuperMethod_) {
        return ERROR_CODE_PARAM_INVALID;
    }
    isLifecycleInterfaceCalled_ = true;
    autoInitialize_ = autoInitialize;
    return ERROR_CODE_NO_ERROR;
}

int32_t XComponentPatternV2::IsInitialized(bool& isInitialized)
{
    if (usesSuperMethod_) {
        return ERROR_CODE_PARAM_INVALID;
    }
    isLifecycleInterfaceCalled_ = true;
    isInitialized = isInitialized_;
    return ERROR_CODE_NO_ERROR;
}

void XComponentPatternV2::OnWindowHide()
{
    if (usesSuperMethod_) {
        XComponentPattern::OnWindowHide();
        return;
    }
    if (hasReleasedSurface_) {
        return;
    }
    if (renderSurface_) {
        renderSurface_->OnWindowStateChange(false);
    }
    hasReleasedSurface_ = true;
}

void XComponentPatternV2::OnWindowShow()
{
    if (usesSuperMethod_) {
        XComponentPattern::OnWindowShow();
        return;
    }
    if (!hasReleasedSurface_) {
        return;
    }
    if (renderSurface_) {
        renderSurface_->OnWindowStateChange(true);
    }
    hasReleasedSurface_ = false;
}

void XComponentPatternV2::OnRebuildFrame()
{
    if (usesSuperMethod_) {
        XComponentPattern::OnRebuildFrame();
        return;
    }
    if (type_ != XComponentType::SURFACE) {
        return;
    }
    if (!renderSurface_->IsSurfaceValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContext->AddChild(renderContextForSurface_, 0);
}

void XComponentPatternV2::InitializeRenderContext()
{
    renderContextForSurface_ = RenderContext::Create();
    RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE,
                                          GetId() + "Surface", RenderContext::PatternType::XCOM };
    renderContextForSurface_->InitContext(false, param);
    renderContextForSurface_->UpdateBackgroundColor(Color::BLACK);
}

void XComponentPatternV2::OnModifyDone()
{
    if (nodeType_ ==  XComponentNodeType::CNODE) {
        XComponentPattern::OnModifyDone();
        return;
    }
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(renderContextForSurface_);
    auto bkColor = renderContext->GetBackgroundColor();
    if (bkColor.has_value()) {
        bool isTransparent = bkColor.value().GetAlpha() < UINT8_MAX;
        renderContextForSurface_->UpdateBackgroundColor(isTransparent ? Color::TRANSPARENT : bkColor.value());
    } else {
        renderContextForSurface_->UpdateBackgroundColor(Color::BLACK);
    }
}

void XComponentPatternV2::DumpInfo()
{
    if (usesSuperMethod_) {
        XComponentPattern::DumpInfo();
        return;
    }
    DumpLog::GetInstance().AddDesc(std::string("autoInitialize: ").append(BoolToString(autoInitialize_)));
    DumpLog::GetInstance().AddDesc(std::string("isInitialized: ").append(BoolToString(isInitialized_)));
    DumpLog::GetInstance().AddDesc(
        std::string("xcomponentNodeType: ").append(XComponentPattern::XComponentNodeTypeToString(nodeType_)));
    DumpLog::GetInstance().AddDesc(
        std::string("xcomponentType: ").append(XComponentPattern::XComponentTypeToString(type_)));
    DumpLog::GetInstance().AddDesc(std::string("surfaceId: ").append(surfaceId_));
    DumpLog::GetInstance().AddDesc(std::string("surfaceRect: ").append(paintRect_.ToString()));
}
} // namespace OHOS::Ace::NG