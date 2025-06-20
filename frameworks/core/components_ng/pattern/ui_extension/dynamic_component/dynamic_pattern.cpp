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

#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/log/log_wrapper.h"
#include "base/log/dump_log.h"
#include "core/components_ng/pattern/ui_extension/platform_utils.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "display_manager.h"
#include "parameters.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char DC_DEPTH_PREFIX[] = "dcDepth_";
constexpr char PARAM_NAME_DC_EXCEED_MAX_NUM[] = "dcExceedMaxNumInWorker";
constexpr char PARAM_MSG_DC_EXCEED_MAX_NUM[] = "Dc exceed max num in the worker";
constexpr char PARAM_NAME_DC_ONLY_ON_SCB[] = "onlyRunOnSCB";
constexpr char PARAM_MSG_DC_ONLY_ON_SCB[] = "DC only run on SCB";
constexpr char PARAM_NAME_INTERNAL_ERROR[] = "internalError";
constexpr char PARAM_MSG_INTERNAL_ERROR[] = "Internal error";
constexpr char PARAM_NAME_PARAM_ERROR[] = "paramError";
constexpr char PARAM_MSG_PARAM_ERROR[] = "Param error";
constexpr char PARAM_NAME_NOT_SUPPORT_UI_CONTENT_TYPE[] = "notSupportUIContentType";
constexpr char PARAM_MSG_NOT_SUPPORT_UI_CONTENT_TYPE[] = "Not support uIContent type";
constexpr char PARAM_NAME_EXCEED_MAX_NUM[] = "exceedMaxNum";
constexpr char PARAM_MSG_EXCEED_MAX_NUM[] = "Workers exceed Max Num";
const char ENABLE_DEBUG_DC_KEY[] = "persist.ace.debug.dc.enabled";
constexpr double SHOW_START = 0.0;
constexpr double SHOW_FULL = 1.0;

bool IsDebugDCEnabled()
{
    return OHOS::system::GetParameter(ENABLE_DEBUG_DC_KEY, "false") == "true";
}
}

int32_t DynamicPattern::dynamicGenerator_ = 0;

class DCAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    DCAccessibilitySAObserverCallback(
        const WeakPtr<DynamicPattern>& weakPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakUECPattern_(weakPattern) {}
    ~DCAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override
    {
        auto pattern = weakUECPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (state) {
            // first time turn on Accessibility, add TransferAccessibilityRectInfo
            pattern->TransferAccessibilityRectInfo(true);
        }

        return true;
    }

private:
    WeakPtr<DynamicPattern> weakUECPattern_;
};

DynamicPattern::DynamicPattern()
    : PlatformPattern(AceLogTag::ACE_DYNAMIC_COMPONENT, ++dynamicGenerator_)
{
    uiExtensionId_ = UIExtensionIdUtility::GetInstance().ApplyExtensionId();
    instanceId_ = -1;
    PLATFORM_LOGI("The DynamicPattern is created.");
}

DynamicPattern::~DynamicPattern()
{
    UIExtensionIdUtility::GetInstance().RecycleExtensionId(uiExtensionId_);
    PLATFORM_LOGI("The DynamicPattern is destroyed.");
}

int64_t DynamicPattern::WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId)
{
    return uiExtensionId_ * extensionOffset + abilityId;
}

RefPtr<AccessibilitySessionAdapter> DynamicPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void DynamicPattern::InitializeDynamicComponent(
    const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint, void* runtime)
{
    if (entryPoint.empty() || runtime == nullptr) {
        PLATFORM_LOGE("The param empty.");
        HandleErrorCallback(DCResultCode::DC_PARAM_ERROE);
        return;
    }

    curDynamicInfo_.entryPoint = entryPoint;
    InitializeRender(runtime);
    RegisterVisibleAreaChange();
}

void DynamicPattern::HandleErrorCallback(DCResultCode resultCode)
{
    switch (resultCode) {
        case DCResultCode::DC_EXCEED_MAX_NUM_IN_WORKER:
            FireOnErrorCallbackOnUI(
                resultCode, PARAM_NAME_DC_EXCEED_MAX_NUM, PARAM_MSG_DC_EXCEED_MAX_NUM);
            break;
        case DCResultCode::DC_ONLY_RUN_ON_SCB:
            FireOnErrorCallbackOnUI(
                resultCode, PARAM_NAME_DC_ONLY_ON_SCB, PARAM_MSG_DC_ONLY_ON_SCB);
            break;
        case DCResultCode::DC_INTERNAL_ERROR:
            FireOnErrorCallbackOnUI(
                resultCode, PARAM_NAME_INTERNAL_ERROR, PARAM_MSG_INTERNAL_ERROR);
            break;
        case DCResultCode::DC_PARAM_ERROE:
            FireOnErrorCallbackOnUI(
                resultCode, PARAM_NAME_PARAM_ERROR, PARAM_MSG_PARAM_ERROR);
            break;
        case DCResultCode::DC_NOT_SUPPORT_UI_CONTENT_TYPE:
            FireOnErrorCallbackOnUI(
                resultCode, PARAM_NAME_NOT_SUPPORT_UI_CONTENT_TYPE, PARAM_MSG_NOT_SUPPORT_UI_CONTENT_TYPE);
            break;
        case DCResultCode::DC_WORKER_EXCEED_MAX_NUM:
            FireOnErrorCallbackOnUI(
                resultCode, PARAM_NAME_EXCEED_MAX_NUM, PARAM_MSG_EXCEED_MAX_NUM);
            break;
        default:
            PLATFORM_LOGI("HandleErrorCallback code: %{public}d is invalid.", resultCode);
    }
}

DCResultCode DynamicPattern::CheckConstraint()
{
    auto instanceId = GetHostInstanceId();
    PLATFORM_LOGI("CheckConstraint instanceId: %{public}d.", instanceId);
    auto container = Platform::AceContainer::GetContainer(instanceId);
    if (!container) {
        PLATFORM_LOGE("container is null.");
        return DCResultCode::DC_INTERNAL_ERROR;
    }

    UIContentType uIContentType = container->GetUIContentType();
    static std::set<UIContentType> dcNotSupportUIContentType = {
        UIContentType::ISOLATED_COMPONENT,
        UIContentType::DYNAMIC_COMPONENT
    };

    if (dcNotSupportUIContentType.find(uIContentType) != dcNotSupportUIContentType.end()) {
        PLATFORM_LOGE("Not support dc in uIContentType: %{public}d.",
            static_cast<int32_t>(uIContentType));
        return DCResultCode::DC_NOT_SUPPORT_UI_CONTENT_TYPE;
    }

    if (container->IsSceneBoardWindow()) {
        return DCResultCode::DC_NO_ERRORS;
    }

    return IsDebugDCEnabled() ? DCResultCode::DC_NO_ERRORS : DCResultCode::DC_ONLY_RUN_ON_SCB;
}

bool DynamicPattern::CheckDynamicRendererConstraint(void* runtime)
{
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    if (!dynamicComponentRenderer_->CheckDCMaxConstraintInWorker(runtime)) {
        HandleErrorCallback(DCResultCode::DC_EXCEED_MAX_NUM_IN_WORKER);
        return false;
    }

    if (!dynamicComponentRenderer_->CheckWorkerMaxConstraint(runtime)) {
        HandleErrorCallback(DCResultCode::DC_WORKER_EXCEED_MAX_NUM);
        return false;
    }

    return true;
}

void DynamicPattern::InitializeRender(void* runtime)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    dynamicDumpInfo_.createLimitedWorkerTime = GetCurrentTimestamp();
#if !defined(PREVIEW)
    DCResultCode code = CheckConstraint();
    if (code != DCResultCode::DC_NO_ERRORS) {
        HandleErrorCallback(code);
        PLATFORM_LOGE("CheckConstraint failed, code: %{public}d.", code);
        return;
    }

    if (!dynamicComponentRenderer_) {
        ContainerScope scope(instanceId_);
        SetHostNode(host);
        dynamicComponentRenderer_ =
            DynamicComponentRenderer::Create(GetHost(), runtime, curDynamicInfo_);
        if (!CheckDynamicRendererConstraint(runtime)) {
            return;
        }

        dynamicComponentRenderer_->SetUIContentType(UIContentType::DYNAMIC_COMPONENT);
        dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
        dynamicComponentRenderer_->SetBackgroundTransparent(backgroundTransparent_);
        dynamicComponentRenderer_->CreateContent();
        accessibilitySessionAdapter_ =
            AceType::MakeRefPtr<AccessibilitySessionAdapterIsolatedComponent>(dynamicComponentRenderer_);
        SetContainerHostPattern(WeakClaim(this));
        auto eventHub = host->GetOrCreateEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        OnAreaChangedFunc onAreaChangedFunc = [renderer = dynamicComponentRenderer_](
            const RectF& oldRect,
            const OffsetF& oldOrigin,
            const RectF& rect,
            const OffsetF& origin) {
                CHECK_NULL_VOID(renderer);
                renderer->UpdateParentOffsetToWindow(origin + rect.GetOffset());
        };
        eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));
    }
#else
    PLATFORM_LOGE("DynamicComponent not support preview.");
#endif
}

void DynamicPattern::SetBackgroundTransparent(bool backgroundTransparent)
{
    backgroundTransparent_ = backgroundTransparent;
}

void DynamicPattern::OnAccessibilityParentRectInfoUpdate()
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->OnAccessibilityParentRectInfoUpdate();
}

void DynamicPattern::FireOnErrorCallbackOnUI(
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

void DynamicPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(pointerEvent);
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferPointerEvent(pointerEvent);
}

void DynamicPattern::DispatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferFocusActiveEvent(isFocusActive);
}

bool DynamicPattern::HandleKeyEvent(const KeyEvent& event)
{
    CHECK_NULL_RETURN(event.rawKeyEvent, false);
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    return dynamicComponentRenderer_->TransferKeyEvent(event);
}

void DynamicPattern::HandleFocusEvent()
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

void DynamicPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->TransferFocusActiveEvent(false);
    dynamicComponentRenderer_->TransferFocusState(false);
}

void DynamicPattern::OnAttachToFrameNode()
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddOnAreaChangeNode(host->GetId());
}

bool DynamicPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipLayout || config.skipMeasure) {
        return false;
    }
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    auto& node = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(node, false);
    auto size = node->GetContentSize();

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    float density = pipeline->GetDensity();
    int32_t orientation = 0;
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (container) {
        orientation = static_cast<int32_t>(container->GetOrientation());
    }

    auto animationOption = pipeline->GetSyncAnimationOption();
    auto parentGlobalOffset = dirty->GetParentGlobalOffsetWithSafeArea(true, true) +
        dirty->GetFrameRectWithSafeArea(true).GetOffset();
    dynamicComponentRenderer_->UpdateViewportConfig(size, density, orientation, animationOption, parentGlobalOffset);
    TransferAccessibilityRectInfo(true);
    return false;
}

void DynamicPattern::SetIsReportFrameEvent(bool isReportFrameEvent)
{
    hostConfig_.isReportFrameEvent = isReportFrameEvent;
}

void DynamicPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->DestroyContent();
    dynamicComponentRenderer_ = nullptr;
}

void DynamicPattern::SetAdaptiveWidth(bool state)
{
    adaptiveWidth_ = state;
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
}

void DynamicPattern::SetAdaptiveHeight(bool state)
{
    adaptiveHeight_ = state;
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
}

void DynamicPattern::OnAttachContext(PipelineContext *context)
{
    CHECK_NULL_VOID(context);
    auto newInstanceId = context->GetInstanceId();
    PLATFORM_LOGI("OnAttachContext newInstanceId: %{public}d, oldInstanceId: %{public}d.",
        newInstanceId, instanceId_);
    if (newInstanceId != instanceId_) {
        UnRegisterPipelineEvent(instanceId_);
        RegisterPipelineEvent(newInstanceId);
        instanceId_ = newInstanceId;
    }
    AddToPageEventController();
}

void DynamicPattern::RegisterPipelineEvent(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    context->AddWindowStateChangedCallback(host->GetId());
    surfacePositionCallBackId_ =
        context->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t, int32_t) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->TransferAccessibilityRectInfo();
        });

    RegisterAccessibilitySAObserverCallback(instanceId);
    RegisterSingleHandTransformChangedCallback(instanceId);
}

void DynamicPattern::RegisterAccessibilitySAObserverCallback(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    auto frontend = context->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (accessibilitySAObserverCallback_ == nullptr) {
        accessibilitySAObserverCallback_ = std::make_shared<DCAccessibilitySAObserverCallback>(
            WeakClaim(this), host->GetAccessibilityId());
    }

    accessibilityManager->RegisterAccessibilitySAObserverCallback(host->GetAccessibilityId(),
        accessibilitySAObserverCallback_);
}

void DynamicPattern::UnRegisterAccessibilitySAObserverCallback(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    auto frontend = context->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(
        host->GetAccessibilityId());
}

void DynamicPattern::RegisterSingleHandTransformChangedCallback(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    auto uiExtManager = context->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtManager);
    uiExtManager->RegisterSingleHandTransformChangedCallback(host->GetId(),
        [weak = WeakClaim(this)] () {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->TransferAccessibilityRectInfo();
        });
}

void DynamicPattern::UnRegisterSingleHandTransformChangedCallback(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    auto uiExtManager = context->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtManager);
    uiExtManager->UnregisterSingleHandTransformChangedCallback(host->GetId());
}

AccessibilityParentRectInfo DynamicPattern::GetAccessibilityRectInfo() const
{
    AccessibilityParentRectInfo rectInfo;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, rectInfo);
    auto pipeline = host->GetContextRefPtr();
    if (pipeline) {
        auto accessibilityManager = pipeline->GetAccessibilityManager();
        if (accessibilityManager) {
            return accessibilityManager->GetTransformRectInfoRelativeToWindow(host, pipeline);
        }
    }

    auto rect = host->GetTransformRectRelativeToWindow(true);
    VectorF finalScale = host->GetTransformScaleRelativeToWindow();
    rectInfo.left = static_cast<int32_t>(rect.Left());
    rectInfo.top = static_cast<int32_t>(rect.Top());
    rectInfo.scaleX = finalScale.x;
    rectInfo.scaleY = finalScale.y;
    return rectInfo;
}

void DynamicPattern::TransferAccessibilityRectInfo(bool isForce)
{
    if (!(isForce || AceApplicationInfo::GetInstance().IsAccessibilityEnabled())) {
        return;
    }

    UpdateAccessibilityParentRectInfo(GetAccessibilityRectInfo());
}

void DynamicPattern::OnFrameNodeChanged(FrameNodeChangeInfoFlag flag)
{
    if (!(IsAncestorNodeTransformChange(flag) || IsAncestorNodeGeometryChange(flag))) {
        return;
    }

    TransferAccessibilityRectInfo();
}

bool DynamicPattern::IsAncestorNodeGeometryChange(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_GEOMETRY_CHANGE) == FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
}

bool DynamicPattern::IsAncestorNodeTransformChange(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_TRANSFORM_CHANGE) == FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
}

void DynamicPattern::OnDetachContext(PipelineContext *context)
{
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    PLATFORM_LOGI("OnDetachContext instanceId: %{public}d.", instanceId);
    UnRegisterPipelineEvent(instanceId);
}

void DynamicPattern::UnRegisterPipelineEvent(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    context->RemoveWindowStateChangedCallback(host->GetId());
    context->UnregisterSurfacePositionChangedCallback(surfacePositionCallBackId_);
    UnRegisterAccessibilitySAObserverCallback(instanceId);
    UnRegisterSingleHandTransformChangedCallback(instanceId);
}

void DynamicPattern::DumpDynamicRenderer(int32_t depth, bool hasJson)
{
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    std::string deptParam;
    deptParam.append(DC_DEPTH_PREFIX).append(std::to_string(depth));
    params.push_back(deptParam);
    if (hasJson) {
        params.push_back("-json");
    }
    std::vector<std::string> dumpInfo;
    dynamicComponentRenderer_->NotifyUieDump(params, dumpInfo);
}

void DynamicPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("dynamicId: ").append(std::to_string(platformId_)));
    DumpLog::GetInstance().AddDesc(std::string("entryPoint: ").append(curDynamicInfo_.entryPoint));
    DumpLog::GetInstance().AddDesc(std::string("createLimitedWorkerTime: ")
        .append(std::to_string(dynamicDumpInfo_.createLimitedWorkerTime)));
    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    DumpLog::GetInstance().AddDesc(std::string("createUiContenTime: ")
        .append(std::to_string(rendererDumpInfo.createUiContenTime)));
    DumpLog::GetInstance().AddDesc(std::string("limitedWorkerInitTime: ")
        .append(std::to_string(rendererDumpInfo.limitedWorkerInitTime)));
    DumpLog::GetInstance().AddDesc(std::string("loadAbcTime: ")
        .append(std::to_string(rendererDumpInfo.loadAbcTime)));
    std::string isReportFrameEvent = hostConfig_.isReportFrameEvent ? "true" : "false";
    DumpLog::GetInstance().AddDesc(std::string("isReportFrameEvent: ")
        .append(isReportFrameEvent));
}

void DynamicPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("dynamicId", platformId_);
    json->Put("resourcePath", curDynamicInfo_.resourcePath.c_str());
    json->Put("entryPoint", curDynamicInfo_.entryPoint.c_str());
    json->Put("createLimitedWorkerTime", std::to_string(dynamicDumpInfo_.createLimitedWorkerTime).c_str());

    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    json->Put("createUiContenTime", std::to_string(rendererDumpInfo.createUiContenTime).c_str());
    json->Put("limitedWorkerInitTime", std::to_string(rendererDumpInfo.limitedWorkerInitTime).c_str());
    json->Put("loadAbcTime", std::to_string(rendererDumpInfo.createUiContenTime).c_str());
    std::string isReportFrameEvent = hostConfig_.isReportFrameEvent ? "true" : "false";
    json->Put("isReportFrameEvent", isReportFrameEvent.c_str());
}

void DynamicPattern::InitializeAccessibility()
{
    if (accessibilityChildTreeCallback_ != nullptr) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ngPipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    accessibilityChildTreeCallback_ = std::make_shared<PlatformAccessibilityChildTreeCallback>(
        WeakClaim(this), accessibilityId);
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto realHostWindowId = ngPipeline->GetRealHostWindowId();
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            realHostWindowId, accessibilityManager->GetTreeId());
    }
    PLATFORM_LOGI("DynamicComponent: %{public}" PRId64 " register child tree, realHostWindowId: %{public}u",
        accessibilityId, realHostWindowId);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId, accessibilityChildTreeCallback_);
}

void DynamicPattern::OnAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId) const
{
    PLATFORM_LOGI("treeId: %{public}d, id: %{public}" PRId64, treeId, accessibilityId);
    if (dynamicComponentRenderer_ == nullptr) {
        PLATFORM_LOGI("dynamicComponentRenderer_ is null");
        return;
    }
    dynamicComponentRenderer_->TransferAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void DynamicPattern::OnAccessibilityChildTreeDeregister() const
{
    PLATFORM_LOGI("deregister accessibility child tree");
    if (dynamicComponentRenderer_ == nullptr) {
        PLATFORM_LOGI("dynamicComponentRenderer_ is null");
        return;
    }
    dynamicComponentRenderer_->TransferAccessibilityChildTreeDeregister();
}

void DynamicPattern::AddToPageEventController()
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto frontend = pipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->AddToPageEventController(host);
}

void DynamicPattern::ReleasePageEvent() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto frontend = pipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->ReleasePageEvent(host, true);
}

void DynamicPattern::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId)
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetChildWindowId(childWindowId);
    accessibilityProperty->SetChildTreeId(childTreeId);
    ReleasePageEvent();
    TransferAccessibilityRectInfo(true);
}

void DynamicPattern::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info) const
{
    PLATFORM_LOGI("dump accessibility child info");
    if (dynamicComponentRenderer_ == nullptr) {
        PLATFORM_LOGI("dynamicComponentRenderer_ is null");
        return;
    }
    dynamicComponentRenderer_->TransferAccessibilityDumpChildInfo(params, info);
}

void DynamicPattern::ResetAccessibilityChildTreeCallback()
{
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    ContainerScope scope(instanceId_);
    auto ngPipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(
        accessibilityChildTreeCallback_->GetAccessibilityId());
    accessibilityChildTreeCallback_.reset();
    accessibilityChildTreeCallback_ = nullptr;
}

void DynamicPattern::RegisterVisibleAreaChange()
{
    PLATFORM_LOGI("Register visible area change.");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleVisibleAreaChange(visible, ratio);
    };
    std::vector<double> ratioList = { SHOW_START, SHOW_FULL };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
}

void DynamicPattern::HandleVisibleAreaChange(bool visible, double ratio)
{
    PLATFORM_LOGI("HandleVisibleAreaChange visible: %{public}d, curVisible: %{public}d, "
        "ratio: %{public}f.", visible, isVisible_, ratio);
    bool curVisible = !NearEqual(ratio, SHOW_START);
    if (isVisible_ != curVisible) {
        isVisible_ = curVisible;
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        if (isVisible_) {
            dynamicComponentRenderer_->NotifyForeground();
        } else {
            dynamicComponentRenderer_->NotifyBackground();
        }
    }
    TransferAccessibilityRectInfo();
}

bool DynamicPattern::HandleTouchEvent(
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_RETURN(pointerEvent, false);
    auto originAction = pointerEvent->GetPointerAction();
    if (originAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE ||
        originAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
        return false;
    }
    return PlatformPattern::HandleTouchEvent(pointerEvent);
}

void DynamicPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    if (info.GetPullAction() == MouseAction::PULL_MOVE || info.GetPullAction() == MouseAction::PULL_UP) {
        return;
    }
    PlatformPattern::HandleMouseEvent(info);
}
} // namespace OHOS::Ace::NG
