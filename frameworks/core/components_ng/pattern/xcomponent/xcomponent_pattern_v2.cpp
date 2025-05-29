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
#include "base/utils/utils.h"
#include "core/accessibility/accessibility_session_adapter.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_session_adapter.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "transaction/rs_transaction_proxy.h"
#endif

namespace OHOS::Ace::NG {

namespace {
const std::string BUFFER_USAGE_XCOMPONENT = "xcomponent";

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
    if (isCNode_) {
        XComponentPattern::OnAttachToFrameNode();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderContext->SetClipToFrame(true);
    renderContext->SetClipToBounds(true);
    InitSurface();
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EnableSelfRender();
    }
    UpdateTransformHint();
}

void XComponentPatternV2::OnAttachToMainTree()
{
    UpdateUsesSuperMethod();
    if (usesSuperMethod_) {
        XComponentPattern::OnAttachToMainTree();
        return;
    }
    isOnTree_ = true;
    if (autoInitialize_) {
        HandleSurfaceCreated();
    }
    if (needRecoverDisplaySync_ && displaySync_ && !displaySync_->IsOnPipeline()) {
        TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "OnAttachToMainTree:recover displaySync: "
            "%{public}s(%{public}" PRIu64 ")", GetId().c_str(), displaySync_->GetId());
        displaySync_->AddToPipelineOnContainer();
        needRecoverDisplaySync_ = false;
    }
}

void XComponentPatternV2::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    UpdateUsesSuperMethod();
    if (usesSuperMethod_) {
        XComponentPattern::BeforeSyncGeometryProperties(config);
        return;
    }
    CHECK_EQUAL_VOID(config.skipMeasure, true);
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
    if (IsSupportImageAnalyzerFeature()) {
        UpdateAnalyzerUIConfig(geometryNode);
    }
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
    needNotifySizeChanged_ = true;
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
    needNotifySizeChanged_ = false;
}

void XComponentPatternV2::OnDetachFromMainTree()
{
    if (usesSuperMethod_) {
        XComponentPattern::OnDetachFromMainTree();
        return;
    }
    isOnTree_ = false;
    if (autoInitialize_) {
        HandleSurfaceDestroyed();
    }
    if (displaySync_ && displaySync_->IsOnPipeline()) {
        TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "OnDetachFromMainTree:remove displaySync: "
            "%{public}s(%{public}" PRIu64 ")", GetId().c_str(), displaySync_->GetId());
        displaySync_->DelFromPipelineOnContainer();
        needRecoverDisplaySync_ = true;
    }
}

void XComponentPatternV2::OnDetachFromFrameNode(FrameNode* frameNode)
{
    UpdateUsesSuperMethod();
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
    if (renderSurface_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderSurface_ = RenderSurface::Create();
    renderSurface_->SetInstanceId(GetHostInstanceId());
    renderSurface_->SetBufferUsage(BUFFER_USAGE_XCOMPONENT);
    if (type_ == XComponentType::SURFACE) {
        InitializeRenderContext();
        renderSurface_->SetRenderContext(renderContextForSurface_);
    } else if (type_ == XComponentType::TEXTURE) {
        renderSurface_->SetRenderContext(renderContext);
        renderSurface_->SetIsTexture(true);
        renderContext->OnNodeNameUpdate(GetId());
    }
    renderSurface_->InitSurface();
    renderSurface_->UpdateSurfaceConfig();
    if (type_ == XComponentType::TEXTURE) {
        renderSurface_->RegisterBufferCallback();
    }
    auto width = paintRect_.Width();
    auto height = paintRect_.Height();
    if (!paintRect_.IsEmpty()) {
        renderSurface_->UpdateSurfaceSizeInUserData(
            static_cast<uint32_t>(width), static_cast<uint32_t>(height));
        renderSurface_->SetSurfaceDefaultSize(
            static_cast<int32_t>(width), static_cast<int32_t>(height));
    }
    renderSurface_->RegisterSurface();
    InitNativeWindow(width, height);
    if (surfaceHolder_) {
        surfaceHolder_->nativeWindow_ = reinterpret_cast<OHNativeWindow*>(nativeWindow_);
    }
    surfaceId_ = renderSurface_->GetUniqueId();
    if (type_ == XComponentType::SURFACE) {
        XComponentInnerSurfaceController::RegisterSurfaceRenderContext(
            surfaceId_, WeakPtr(renderContextForSurface_));
    }
}

void XComponentPatternV2::DisposeSurface()
{
    if (type_ == XComponentType::SURFACE) {
        XComponentInnerSurfaceController::UnregisterSurfaceRenderContext(
            surfaceId_);
        surfaceId_ = "";
    }
    if (renderSurface_) {
        renderSurface_->ReleaseSurfaceBuffers();
        renderSurface_->UnregisterSurface();
        renderSurface_ = nullptr;
    }
    if (surfaceHolder_) {
        surfaceHolder_->nativeWindow_ = nullptr;
    }
    nativeWindow_ = nullptr;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    // for surface type
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContext->RemoveChild(renderContextForSurface_);
    renderContextForSurface_ = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
#endif
}

int32_t XComponentPatternV2::HandleSurfaceCreated()
{
    CHECK_EQUAL_RETURN(isInitialized_, true, ERROR_CODE_XCOMPONENT_STATE_INVALID);
    InitSurface();
    CHECK_NULL_RETURN(renderSurface_, ERROR_CODE_PARAM_INVALID);
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
    if (needNotifySizeChanged_) {
        OnSurfaceChanged(paintRect_);
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t XComponentPatternV2::HandleSurfaceDestroyed()
{
    CHECK_EQUAL_RETURN(isInitialized_, false, ERROR_CODE_XCOMPONENT_STATE_INVALID);
    isInitialized_ = false;
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
    DisposeSurface();
    return ERROR_CODE_NO_ERROR;
}

int32_t XComponentPatternV2::Initialize()
{
    CHECK_EQUAL_RETURN(usesSuperMethod_, true, ERROR_CODE_PARAM_INVALID);
    isLifecycleInterfaceCalled_ = true;
    return HandleSurfaceCreated();
}

int32_t XComponentPatternV2::Finalize()
{
    CHECK_EQUAL_RETURN(usesSuperMethod_, true, ERROR_CODE_PARAM_INVALID);
    isLifecycleInterfaceCalled_ = true;
    return HandleSurfaceDestroyed();
}

int32_t XComponentPatternV2::SetAutoInitialize(bool autoInitialize)
{
    CHECK_EQUAL_RETURN(usesSuperMethod_, true, ERROR_CODE_PARAM_INVALID);
    isLifecycleInterfaceCalled_ = true;
    autoInitialize_ = autoInitialize;
    return ERROR_CODE_NO_ERROR;
}

int32_t XComponentPatternV2::IsInitialized(bool& isInitialized)
{
    CHECK_EQUAL_RETURN(usesSuperMethod_, true, ERROR_CODE_PARAM_INVALID);
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
    CHECK_EQUAL_VOID(hasReleasedSurface_, true);
    if (renderSurface_) {
        renderSurface_->OnWindowStateChange(false);
    }
    OnSurfaceHide();
    hasReleasedSurface_ = true;
}

void XComponentPatternV2::OnWindowShow()
{
    if (usesSuperMethod_) {
        XComponentPattern::OnWindowShow();
        return;
    }
    CHECK_EQUAL_VOID(hasReleasedSurface_, false);
    if (renderSurface_) {
        renderSurface_->OnWindowStateChange(true);
    }
    OnSurfaceShow();
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
    CHECK_NULL_VOID(renderSurface_);
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
    if (renderContextForSurface_) {
        return;
    }
    renderContextForSurface_ = RenderContext::Create();
    RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, GetId() + "Surface",
        RenderContext::PatternType::XCOM };
    renderContextForSurface_->InitContext(false, param);
    if (!paintRect_.IsEmpty()) {
        renderContextForSurface_->SetBounds(
            paintRect_.GetX(), paintRect_.GetY(), paintRect_.Width(), paintRect_.Height());
    }
    renderContextForSurface_->UpdateBackgroundColor(bkColor_);
    renderContextForSurface_->SetHDRBrightness(hdrBrightness_);
    renderContextForSurface_->SetTransparentLayer(isTransparentLayer_);
    renderContextForSurface_->SetSecurityLayer(isEnableSecure_);
    renderContextForSurface_->SetSurfaceRotation(isSurfaceLock_);
    renderContextForSurface_->SetRenderFit(renderFit_);
}

void XComponentPatternV2::OnModifyDone()
{
    if (usesSuperMethod_) {
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
        bkColor_ = isTransparent ? Color::TRANSPARENT : bkColor.value();
    }
    renderContextForSurface_->UpdateBackgroundColor(bkColor_);
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

void XComponentPatternV2::SetExpectedRateRange(int32_t min, int32_t max, int32_t expected)
{
    if (hasGotNativeXComponent_) {
        return;
    }
    isNativeXComponentDisabled_ = true;
    CHECK_NULL_VOID(displaySync_);
    FrameRateRange frameRateRange;
    frameRateRange.Set(min, max, expected);
    displaySync_->SetExpectedFrameRateRange(frameRateRange);
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "Id: %{public}" PRIu64 " SetExpectedFrameRateRange"
        "{%{public}d, %{public}d, %{public}d}", displaySync_->GetId(), min, max, expected);
}

void XComponentPatternV2::UpdateOnFrameEvent(void(*callback)(void*, uint64_t, uint64_t), void* arkuiNode)
{
    if (hasGotNativeXComponent_) {
        return;
    }
    isNativeXComponentDisabled_ = true;
    CHECK_NULL_VOID(displaySync_);
    displaySync_->RegisterOnFrameWithData([weak = AceType::WeakClaim(this),
        callback, arkuiNode](RefPtr<DisplaySyncData> displaySyncData) {
        auto xComponentPattern = weak.Upgrade();
        CHECK_NULL_VOID(xComponentPattern);
        CHECK_NULL_VOID(callback);
        CHECK_NULL_VOID(arkuiNode);
        CHECK_NULL_VOID(displaySyncData);
        callback(arkuiNode, displaySyncData->GetTimestamp(), displaySyncData->GetTargetTimestamp());
    });
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "Id: %{public}" PRIu64 " RegisterOnFrame",
        displaySync_->GetId());
    displaySync_->AddToPipelineOnContainer();
}

void XComponentPatternV2::UnregisterOnFrameEvent()
{
    if (hasGotNativeXComponent_) {
        return;
    }
    isNativeXComponentDisabled_ = true;
    CHECK_NULL_VOID(displaySync_);
    displaySync_->UnregisterOnFrame();
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "Id: %{public}" PRIu64 " UnregisterOnFrame",
        displaySync_->GetId());
    displaySync_->DelFromPipelineOnContainer();
    needRecoverDisplaySync_ = false;
}

void XComponentPatternV2::SetNeedSoftKeyboard(bool isNeedSoftKeyboard)
{
    if (hasGotNativeXComponent_) {
        return;
    }
    isNativeXComponentDisabled_ = true;
    isNeedSoftKeyboard_ = isNeedSoftKeyboard;
}

void XComponentPatternV2::OnSurfaceShow()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(surfaceHolder_);
    auto callbackList = surfaceHolder_->surfaceCallbackList_;
    for (const auto& iter : callbackList) {
        auto callback = iter->onSurfaceShow;
        if (callback) {
            callback(surfaceHolder_);
        }
    }
}

void XComponentPatternV2::OnSurfaceHide()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(surfaceHolder_);
    auto callbackList = surfaceHolder_->surfaceCallbackList_;
    bool hasCallback = false;
    for (const auto& iter : callbackList) {
        auto callback = iter->onSurfaceHide;
        if (callback) {
            callback(surfaceHolder_);
            hasCallback = true;
        }
    }
    if (hasCallback) {
        CHECK_NULL_VOID(renderSurface_);
        renderSurface_->ReleaseSurfaceBuffers();
    }
}

void XComponentPatternV2::ResetAndInitializeNodeHandleAccessibility()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (accessibilityChildTreeCallback_) {
        accessibilityManager->DeregisterAccessibilityChildTreeCallback(
            accessibilityChildTreeCallback_->GetAccessibilityId()
        );
        accessibilityChildTreeCallback_.reset();
        accessibilityChildTreeCallback_ = nullptr;
    }

    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "InitializeNodeHandleAccessibility");
    CHECK_NULL_VOID(arkuiAccessibilityProvider_);
    arkuiAccessibilityProvider_->SetRegisterCallback(
        [weak = WeakClaim(this)] (bool isRegister) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleRegisterAccessibilityEvent(isRegister);
        });
    int64_t accessibilityId = host->GetAccessibilityId();
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT,
        "InitializeNodeHandleAccessibility accessibilityId: %{public}" PRId64 "", accessibilityId);
    accessibilityChildTreeCallback_ = std::make_shared<XComponentAccessibilityChildTreeCallback>(
        WeakClaim(this), host->GetAccessibilityId());
    accessibilityManager->RegisterAccessibilityChildTreeCallback(
        accessibilityId, accessibilityChildTreeCallback_);
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            pipeline->GetWindowId(), accessibilityManager->GetTreeId());
    }
}

ArkUI_AccessibilityProvider* XComponentPatternV2::CreateAccessibilityProvider()
{
    if (hasGotNativeXComponent_) {
        return nullptr;
    }
    isNativeXComponentDisabled_ = true;
    useNodeHandleAccessibilityProvider_ = true;
    if (arkuiAccessibilityProvider_) {
        return arkuiAccessibilityProvider_;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    arkuiAccessibilityProvider_ = new ArkUI_AccessibilityProvider();
    XComponentPatternV2::XComponentAccessibilityProviderMap[arkuiAccessibilityProvider_] = WeakPtr(host);
    ResetAndInitializeNodeHandleAccessibility();
    return arkuiAccessibilityProvider_;
}

void XComponentPatternV2::DisposeAccessibilityProvider(ArkUI_AccessibilityProvider* provider)
{
    if (hasGotNativeXComponent_ || (provider != arkuiAccessibilityProvider_)) {
        return;
    }
    CHECK_NULL_VOID(arkuiAccessibilityProvider_);
    isNativeXComponentDisabled_ = true;
    XComponentPatternV2::XComponentAccessibilityProviderMap.erase(arkuiAccessibilityProvider_);
    auto host = GetHost();
    UninitializeAccessibility(AceType::RawPtr(host));
    delete arkuiAccessibilityProvider_;
    arkuiAccessibilityProvider_ = nullptr;
}

std::unordered_map<void*, WeakPtr<FrameNode>> XComponentPatternV2::XComponentAccessibilityProviderMap;

FrameNode* XComponentPatternV2::QueryAccessibilityProviderHost(void* provider, bool& isProviderValied)
{
    auto it = XComponentAccessibilityProviderMap.find(provider);
    if (it == XComponentAccessibilityProviderMap.end()) {
        isProviderValied = false;
        return nullptr;
    }
    isProviderValied = true;
    auto weakHost = it->second;
    auto host = weakHost.Upgrade();
    CHECK_NULL_RETURN(host, nullptr);
    return AceType::RawPtr(host);
}
} // namespace OHOS::Ace::NG