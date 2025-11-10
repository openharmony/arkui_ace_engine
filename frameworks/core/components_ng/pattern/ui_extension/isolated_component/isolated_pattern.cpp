/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/log/log_wrapper.h"
#include "base/log/dump_log.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "display_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char RESOURCE_PATH[] = "resourcePath";
constexpr char ABC_PATH[] = "abcPath";
constexpr char ENTRY_POINT[] = "entryPoint";
constexpr char REGISTER_COMPONENTS[] = "registerComponents";
constexpr int32_t PARAM_ERR_CODE = 10001;
constexpr char PARAM_NAME[] = "paramError";
constexpr char PARAM_MSG[] = "The param is empty";
constexpr int32_t WORKER_ERROR = 10002;
constexpr char PARAM_NAME_RESTRICTED_WORKER_ERROR[] = "restrictedWorkerError";
constexpr char PARAM_MSG_RESTRICTED_WORKER_ERROR[] = "Run not in restricted worker thread";
}

int32_t IsolatedPattern::isolatedIdGenerator_ = 0;

IsolatedPattern::IsolatedPattern()
    : PlatformPattern(AceLogTag::ACE_ISOLATED_COMPONENT, ++isolatedIdGenerator_)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionId_ = uiExtensionManager->ApplyExtensionId();
    PLATFORM_LOGI("The IsolatedPattern is created.");
}

IsolatedPattern::~IsolatedPattern()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionManager->RecycleExtensionId(uiExtensionId_);
    PLATFORM_LOGI("The IsolatedPattern is destroyed.");
}

int32_t IsolatedPattern::GetUiExtensionId()
{
    return uiExtensionId_;
}

int64_t IsolatedPattern::WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId)
{
    return uiExtensionId_ * extensionOffset + abilityId;
}

RefPtr<AccessibilitySessionAdapter> IsolatedPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void IsolatedPattern::InitializeIsolatedComponent(const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime)
{
    auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
    auto resourcePath = want.GetStringParam(RESOURCE_PATH);
    auto abcPath = want.GetStringParam(ABC_PATH);
    auto entryPoint = want.GetStringParam(ENTRY_POINT);
    auto registerComponents = want.GetStringArrayParam(REGISTER_COMPONENTS);
    if (resourcePath.empty() || abcPath.empty() || entryPoint.empty() || runtime == nullptr) {
        PLATFORM_LOGE("The param empty.");
        FireOnErrorCallback(PARAM_ERR_CODE, PARAM_NAME, PARAM_MSG);
        return;
    }

    curIsolatedInfo_.abcPath = abcPath;
    curIsolatedInfo_.resourcePath = resourcePath;
    curIsolatedInfo_.entryPoint = entryPoint;
    curIsolatedInfo_.registerComponents = registerComponents;
    InitializeRender(runtime);
}

bool IsolatedPattern::CheckConstraint()
{
    auto instanceId = GetHostInstanceId();
    PLATFORM_LOGI("CheckConstraint instanceId: %{public}d.", instanceId);
    auto container = Platform::AceContainer::GetContainer(instanceId);
    if (!container) {
        PLATFORM_LOGE("container is null.");
        return false;
    }

    UIContentType uIContentType = container->GetUIContentType();
    static std::set<UIContentType> isolatedNotSupportUIContentType = {
        UIContentType::ISOLATED_COMPONENT,
        UIContentType::DYNAMIC_COMPONENT
    };

    if (isolatedNotSupportUIContentType.find(uIContentType) !=
        isolatedNotSupportUIContentType.end()) {
        PLATFORM_LOGE("Not support isolatedComponent in uIContentType: %{public}d.",
            static_cast<int32_t>(uIContentType));
        return false;
    }

    return true;
}

void IsolatedPattern::InitializeRender(void* runtime)
{
    isolatedDumpInfo_.createLimitedWorkerTime = GetCurrentTimestamp();
#if !defined(PREVIEW)
    if (!CheckConstraint()) {
        PLATFORM_LOGE("CheckConstraint failed.");
        return;
    }

    if (!dynamicComponentRenderer_) {
        ContainerScope scope(instanceId_);
        dynamicComponentRenderer_ = DynamicComponentRenderer::Create(GetHost(), runtime, curIsolatedInfo_);
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        if (!dynamicComponentRenderer_->IsRestrictedWorkerThread()) {
            PLATFORM_LOGW("DynamicComponent should run in restricted worker thread");
            FireOnErrorCallbackOnUI(
                WORKER_ERROR, PARAM_NAME_RESTRICTED_WORKER_ERROR, PARAM_MSG_RESTRICTED_WORKER_ERROR);
            return;
        }

        dynamicComponentRenderer_->SetUIContentType(UIContentType::ISOLATED_COMPONENT);
        dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
        dynamicComponentRenderer_->SetBackgroundTransparent(true);
        dynamicComponentRenderer_->CreateContent();
        accessibilitySessionAdapter_ =
            AceType::MakeRefPtr<AccessibilitySessionAdapterIsolatedComponent>(dynamicComponentRenderer_);
        SetContainerHostPattern(WeakClaim(this));
    }
#else
    PLATFORM_LOGE("IsolatedComponent not support preview.");
#endif
}

void IsolatedPattern::FireOnErrorCallbackOnUI(
    int32_t code, const std::string& name, const std::string& msg)
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto uiTaskExecutor = SingleTaskExecutor::Make(
        pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this), code, name, msg] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireOnErrorCallback(code, name, msg);
        }, "FireOnErrorCallback");
}

void IsolatedPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(pointerEvent);
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferPointerEvent(pointerEvent);
}

void IsolatedPattern::DispatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferFocusActiveEvent(isFocusActive);
}

bool IsolatedPattern::HandleKeyEvent(const KeyEvent& event)
{
    CHECK_NULL_RETURN(event.rawKeyEvent, false);
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    return dynamicComponentRenderer_->TransferKeyEvent(event);
}

void IsolatedPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        dynamicComponentRenderer_->TransferFocusActiveEvent(true);
    }
    dynamicComponentRenderer_->TransferFocusState(true);
}

void IsolatedPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferFocusActiveEvent(false);
    dynamicComponentRenderer_->TransferFocusState(false);
}

void IsolatedPattern::OnAttachToFrameNode()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->AddOnAreaChangeNode(host->GetId());
}

void IsolatedPattern::OnAttachContext(PipelineContext* context)
{
    if (isInitedAccessibilityInInitUiContent_) {
        InitializeAccessibilityInner(false);
    }
}

void IsolatedPattern::OnDetachContext(PipelineContext* context)
{
    ResetAccessibilityChildTreeCallback();
}

bool IsolatedPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipLayout || config.skipMeasure) {
        return false;
    }
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    auto& node = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(node, false);
    auto size = node->GetContentSize();
    float density = 1.0f;
    int32_t orientation = 0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        orientation = static_cast<int32_t>(defaultDisplay->GetOrientation());
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto animationOption = pipeline->GetSyncAnimationOption();
    NG::OffsetF offset;
    dynamicComponentRenderer_->UpdateViewportConfig(size, density, orientation, animationOption, offset);
    return false;
}

void IsolatedPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->DestroyContent();
    dynamicComponentRenderer_ = nullptr;
}

void IsolatedPattern::SetAdaptiveWidth(bool state)
{
    adaptiveWidth_ = state;
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
}

void IsolatedPattern::SetAdaptiveHeight(bool state)
{
    adaptiveHeight_ = state;
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
}

void IsolatedPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("isolatedId: ").append(std::to_string(platformId_)));
    DumpLog::GetInstance().AddDesc(std::string("abcPath: ").append(curIsolatedInfo_.abcPath));
    DumpLog::GetInstance().AddDesc(std::string("resourcePath: ").append(curIsolatedInfo_.resourcePath));
    DumpLog::GetInstance().AddDesc(std::string("entryPoint: ").append(curIsolatedInfo_.entryPoint));
    DumpLog::GetInstance().AddDesc(std::string("createLimitedWorkerTime: ")
        .append(std::to_string(isolatedDumpInfo_.createLimitedWorkerTime)));
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    DumpLog::GetInstance().AddDesc(std::string("createUiContenTime: ")
        .append(std::to_string(rendererDumpInfo.createUiContenTime)));
    DumpLog::GetInstance().AddDesc(std::string("limitedWorkerInitTime: ")
        .append(std::to_string(rendererDumpInfo.limitedWorkerInitTime)));
    DumpLog::GetInstance().AddDesc(std::string("loadAbcTime: ")
        .append(std::to_string(rendererDumpInfo.loadAbcTime)));
}

void IsolatedPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("isolatedId", platformId_);
    json->Put("abcPath", curIsolatedInfo_.abcPath.c_str());
    json->Put("resourcePath", curIsolatedInfo_.resourcePath.c_str());
    json->Put("entryPoint", curIsolatedInfo_.resourcePath.c_str());
    json->Put("resourcePath", curIsolatedInfo_.entryPoint.c_str());
    json->Put("createLimitedWorkerTime", std::to_string(isolatedDumpInfo_.createLimitedWorkerTime).c_str());

    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    json->Put("createUiContenTime", std::to_string(rendererDumpInfo.createUiContenTime).c_str());
    json->Put("limitedWorkerInitTime", std::to_string(rendererDumpInfo.limitedWorkerInitTime).c_str());
    json->Put("loadAbcTime", std::to_string(rendererDumpInfo.createUiContenTime).c_str());
}

void IsolatedPattern::InitializeAccessibility()
{
    isInitedAccessibilityInInitUiContent_ = true;
    InitializeAccessibilityInner(true);
}

void IsolatedPattern::InitializeAccessibilityInner(bool forceReinit)
{
    if (forceReinit) {
        ResetAccessibilityChildTreeCallback();
    }
    CHECK_NE_VOID(accessibilityChildTreeCallback_, nullptr);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ngPipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(ngPipeline);
    auto accessibilityManager = ngPipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    int64_t accessibilityId = host->GetAccessibilityId();
    accessibilityChildTreeCallback_ = std::make_shared<PlatformAccessibilityChildTreeCallback>(
        WeakClaim(this), accessibilityId);
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId, accessibilityChildTreeCallback_);
    auto realHostWindowId = ngPipeline->GetRealHostWindowId();
    CHECK_EQUAL_VOID(accessibilityManager->IsRegister(), false);
    accessibilityChildTreeCallback_->OnRegister(realHostWindowId, accessibilityManager->GetTreeId());
    PLATFORM_LOGD("Isolated: %{public}" PRId64 " register child tree, realHostWindowId: %{public}u",
        accessibilityId, realHostWindowId);
}

void IsolatedPattern::OnAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId) const
{
    PLATFORM_LOGD("Isolated treeId: %{public}d, id: %{public}" PRId64, treeId, accessibilityId);
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void IsolatedPattern::OnAccessibilityChildTreeDeregister() const
{
    PLATFORM_LOGD("Isolated deregister accessibility child tree");
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferAccessibilityChildTreeDeregister();
}

void IsolatedPattern::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId)
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetChildWindowId(childWindowId);
    accessibilityProperty->SetChildTreeId(childTreeId);
}

void IsolatedPattern::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info) const
{
}

void IsolatedPattern::ResetAccessibilityChildTreeCallback()
{
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ngPipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(ngPipeline);
    auto accessibilityManager = ngPipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityChildTreeCallback_->OnDeregister();
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(
        accessibilityChildTreeCallback_->GetAccessibilityId());
    accessibilityChildTreeCallback_.reset();
}
} // namespace OHOS::Ace::NG
