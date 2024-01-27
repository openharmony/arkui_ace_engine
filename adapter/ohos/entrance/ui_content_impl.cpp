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

#include "adapter/ohos/entrance/ui_content_impl.h"

#include <atomic>
#include <cinttypes>

#include "ability_context.h"
#include "ability_info.h"
#include "configuration.h"
#include "ipc_skeleton.h"
#include "js_runtime_utils.h"
#include "locale_config.h"
#include "native_reference.h"
#include "ohos/init_data.h"
#include "service_extension_context.h"
#include "wm_common.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/safe_area_insets.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/transaction/rs_transaction.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/dialog_container.h"
#include "adapter/ohos/entrance/dynamic_component/uv_task_wrapper_impl.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "adapter/ohos/entrance/form_utils_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/ui_event_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "adapter/ohos/osal/page_url_checker_ohos.h"
#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "adapter/ohos/osal/view_data_wrap_ohos.h"
#include "base/geometry/rect.h"
#include "base/i18n/localization.h"
#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "core/common/ace_engine.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/modal_ui_extension.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/resource/resource_manager.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/image/image_file_cache.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifdef FORM_SUPPORTED
#include "core/common/form_manager.h"
#endif
#include "core/common/layout_inspector.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
#ifdef NG_BUILD
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#endif
#include "pipeline/rs_node_map.h"
#include "transaction/rs_transaction_data.h"
#include "ui/rs_node.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
const std::string START_PARAMS_KEY = "__startParams";
const std::string ACTION_VIEWDATA = "ohos.want.action.viewData";

Rosen::Rect ConvertToRSRect(NG::RectF& rect)
{
    Rosen::Rect rsRect;
    rsRect.posX_ = floor(rect.GetX());
    rsRect.posY_ = floor(rect.GetY());
    rsRect.width_ = ceil(rect.Width());
    rsRect.height_ = ceil(rect.Height());
    return rsRect;
}
} // namespace

const std::string SUBWINDOW_PREFIX = "ARK_APP_SUBWINDOW_";
const std::string SUBWINDOW_TOAST_DIALOG_PREFIX = "ARK_APP_SUBWINDOW_TOAST_DIALOG_";
const int32_t REQUEST_CODE = -1;

using ContentFinishCallback = std::function<void()>;
using ContentStartAbilityCallback = std::function<void(const std::string& address)>;
class ContentEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit ContentEventCallback(ContentFinishCallback onFinish) : onFinish_(onFinish) {}
    ContentEventCallback(ContentFinishCallback onFinish, ContentStartAbilityCallback onStartAbility)
        : onFinish_(onFinish), onStartAbility_(onStartAbility)
    {}
    ~ContentEventCallback() override = default;

    void OnFinish() const override
    {
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStartAbility(const std::string& address) override
    {
        CHECK_NULL_VOID(onStartAbility_);
        onStartAbility_(address);
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("StartsBar background color changed.");
    }

private:
    ContentFinishCallback onFinish_;
    ContentStartAbilityCallback onStartAbility_;
};

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateUIContent(void* context, void* runtime)
{
    LOGI("Ace lib loaded, CreateUIContent.");
    Recorder::Init();
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateFormContent(void* context, void* runtime, bool isCard)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "Ace lib loaded, CreateFormUIContent.");
    Recorder::Init();
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime, isCard);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateSubWindowUIContent(void* ability)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Ace lib loaded, Create SubWindowUIContent.");
    Recorder::Init();
    return new UIContentImpl(reinterpret_cast<OHOS::AppExecFwk::Ability*>(ability));
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_GetUIContent(int32_t instanceId)
{
    LOGI("Ace lib loaded, GetUIContent.");
    auto uiWindow = Platform::AceContainer::GetUIWindow(instanceId);
    CHECK_NULL_RETURN(uiWindow, nullptr);
    return uiWindow->GetUIContent();
}

extern "C" ACE_FORCE_EXPORT char* OHOS_ACE_GetCurrentUIStackInfo()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    static auto tmp = pipeline->GetCurrentExtraInfo();
    std::replace(tmp.begin(), tmp.end(), '\\', '/');
    LOGI("UIContentImpl::GetCurrentExtraInfo:%{public}s", tmp.c_str());
    return tmp.data();
}

void AddAlarmLogFunc()
{
    std::function<void(uint64_t, int, int)> logFunc = [](uint64_t nodeId, int count, int num) {
        auto rsNode = Rosen::RSNodeMap::Instance().GetNode<Rosen::RSNode>(nodeId);
        if (rsNode == nullptr) {
            LOGI("rsNodeId = %{public}" PRId64 " send %{public}d commands, total number of rsNode is %{public}d"
                 "But cannot find the rsNode with this rsNodeId",
                nodeId, count, num);
            return;
        }
        auto frameNodeId = rsNode->GetFrameNodeId();
        auto frameNodeTag = rsNode->GetFrameNodeTag();
        auto frameNode = NG::FrameNode::GetFrameNode(frameNodeTag, frameNodeId);
        if (frameNode == nullptr) {
            LOGI("frameNodeId = %{public}d, rsNodeId = %{public}" PRId64 " send %{public}d commands, "
                 "total number of rsNode is %{public}d. But cannot find the frameNode with this frameNodeId.",
                frameNodeId, nodeId, count, num);
            return;
        }
        LOGI("frameNodeId = %{public}d, rsNodeId = %{public}" PRId64 " send %{public}d commands, "
             "the tag of corresponding frame node is %{public}s, total number of rsNode is %{public}d",
            frameNodeId, nodeId, count, frameNodeTag.c_str(), num);
    };

    OHOS::Rosen::RSTransactionData::AddAlarmLog(logFunc);
}

class OccupiedAreaChangeListener : public OHOS::Rosen::IOccupiedAreaChangeListener {
public:
    explicit OccupiedAreaChangeListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~OccupiedAreaChangeListener() = default;

    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
    {
        auto rect = info->rect_;
        auto type = info->type_;
        double positionY = info->textFieldPositionY_;
        double height = info->textFieldHeight_;
        Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        LOGI("UIContent OccupiedAreaChange rect:%{public}s type: %{public}d, positionY:%{public}f, height:%{public}f",
            keyboardRect.ToString().c_str(), type, positionY, height);
        if (type == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT) {
            auto container = Platform::AceContainer::GetContainer(instanceId_);
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            auto context = container->GetPipelineContext();
            CHECK_NULL_VOID(context);
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(context);
            if (pipeline) {
                auto uiExtMgr = pipeline->GetUIExtensionManager();
                if (uiExtMgr && uiExtMgr->NotifyOccupiedAreaChangeInfo(info)) {
                    return;
                }
            }
            auto curWindow = context->GetCurrentWindowRect();
            positionY -= curWindow.Top();
            ContainerScope scope(instanceId_);
            taskExecutor->PostTask(
                [context, keyboardRect, rsTransaction, positionY, height] {
                    CHECK_NULL_VOID(context);
                    context->OnVirtualKeyboardAreaChange(keyboardRect, positionY, height, rsTransaction);
                },
                TaskExecutor::TaskType::UI);
        }
    }

private:
    int32_t instanceId_ = -1;
};

class AvoidAreaChangedListener : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit AvoidAreaChangedListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~AvoidAreaChangedListener() = default;

    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type) override
    {
        LOGD("Avoid area changed, type:%{public}d, topRect: avoidArea:x:%{public}d, y:%{public}d, "
             "width:%{public}d, height%{public}d; bottomRect: avoidArea:x:%{public}d, y:%{public}d, "
             "width:%{public}d, height%{public}d",
            type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
            (int32_t)avoidArea.topRect_.height_, avoidArea.bottomRect_.posX_, avoidArea.bottomRect_.posY_,
            (int32_t)avoidArea.bottomRect_.width_, (int32_t)avoidArea.bottomRect_.height_);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto pipeline = container->GetPipelineContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
            systemSafeArea_ = ConvertAvoidArea(avoidArea);
        } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
            navigationBar_ = ConvertAvoidArea(avoidArea);
        }
        auto safeArea = systemSafeArea_;
        auto navSafeArea = navigationBar_;
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [pipeline, safeArea, navSafeArea, type, avoidArea] {
                if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
                    pipeline->UpdateSystemSafeArea(safeArea);
                } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
                    pipeline->UpdateNavSafeArea(navSafeArea);
                }
                // for ui extension component
                pipeline->UpdateOriginAvoidArea(avoidArea, static_cast<uint32_t>(type));
            },
            TaskExecutor::TaskType::UI);
    }

private:
    NG::SafeAreaInsets systemSafeArea_;
    NG::SafeAreaInsets navigationBar_;
    int32_t instanceId_ = -1;
};

class AvailableAreaChangedListener : public OHOS::Rosen::DisplayManager::IAvailableAreaListener {
public:
    explicit AvailableAreaChangedListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~AvailableAreaChangedListener() = default;

    void OnAvailableAreaChanged(const Rosen::DMRect availableArea) override
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto displayAvailableRect = ConvertDMRect2Rect(availableArea);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [pipeline, displayAvailableRect] { pipeline->UpdateDisplayAvailableRect(displayAvailableRect); },
            TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
};

class DragWindowListener : public OHOS::Rosen::IWindowDragListener {
public:
    explicit DragWindowListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~DragWindowListener() = default;
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event)
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        int32_t instanceId = instanceId_;
        if (container->IsSubContainer()) {
            instanceId = container->GetParentId();
        }
        auto aceView = static_cast<Platform::AceViewOhos*>(Platform::AceContainer::GetContainer(instanceId)->GetView());
        CHECK_NULL_VOID(aceView);
        DragEventAction action;
        switch (event) {
            case OHOS::Rosen::DragEvent::DRAG_EVENT_END:
                action = DragEventAction::DRAG_EVENT_END;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_OUT:
                action = DragEventAction::DRAG_EVENT_OUT;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_MOVE:
                action = DragEventAction::DRAG_EVENT_MOVE;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_IN:
            default:
                action = DragEventAction::DRAG_EVENT_START;
                break;
        }
    }

private:
    int32_t instanceId_ = -1;
};

class FoldScreenListener : public OHOS::Rosen::DisplayManager::IFoldStatusListener {
public:
    explicit FoldScreenListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~FoldScreenListener() = default;
    void OnFoldStatusChanged(OHOS::Rosen::FoldStatus foldStatus) override
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [container, foldStatus] {
                auto context = container->GetPipelineContext();
                CHECK_NULL_VOID(context);
                auto aceFoldStatus = static_cast<FoldStatus>(static_cast<uint32_t>(foldStatus));
                context->OnFoldStatusChanged(aceFoldStatus);
            },
            TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
};

class FoldDisplayModeListener : public OHOS::Rosen::DisplayManager::IDisplayModeListener {
public:
    explicit FoldDisplayModeListener(int32_t instanceId, bool isDialog = false)
        : instanceId_(instanceId), isDialog_(isDialog)
    {}
    ~FoldDisplayModeListener() = default;
    void OnDisplayModeChanged(OHOS::Rosen::FoldDisplayMode displayMode) override
    {
        if (!isDialog_) {
            auto container = Platform::AceContainer::GetContainer(instanceId_);
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            ContainerScope scope(instanceId_);
            taskExecutor->PostTask(
                [container, displayMode] {
                    auto context = container->GetPipelineContext();
                    CHECK_NULL_VOID(context);
                    auto aceDisplayMode = static_cast<FoldDisplayMode>(static_cast<uint32_t>(displayMode));
                    context->OnFoldDisplayModeChanged(aceDisplayMode);
                },
                TaskExecutor::TaskType::UI);
            return;
        }
        auto container = Platform::DialogContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [container, displayMode] {
                auto context = container->GetPipelineContext();
                CHECK_NULL_VOID(context);
                auto aceDisplayMode = static_cast<FoldDisplayMode>(static_cast<uint32_t>(displayMode));
                context->OnFoldDisplayModeChanged(aceDisplayMode);
            },
            TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
    bool isDialog_ = false;
};

class TouchOutsideListener : public OHOS::Rosen::ITouchOutsideListener {
public:
    explicit TouchOutsideListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~TouchOutsideListener() = default;

    void OnTouchOutside() const
    {
        LOGI("window is touching outside. instance id is %{public}d", instanceId_);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [instanceId = instanceId_] {
                SubwindowManager::GetInstance()->ClearMenu();
                SubwindowManager::GetInstance()->ClearMenuNG(instanceId, true, true);
                SubwindowManager::GetInstance()->ClearPopupInSubwindow(instanceId);
            },
            TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
};

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime) : runtime_(runtime)
{
    CHECK_NULL_VOID(context);
    context_ = context->weak_from_this();
    bundleName_ = context->GetBundleName();
    auto hapModuleInfo = context->GetHapModuleInfo();
    CHECK_NULL_VOID(hapModuleInfo);
    moduleName_ = hapModuleInfo->name;
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard)
    : runtime_(runtime), isFormRender_(isCard)
{
    CHECK_NULL_VOID(context);
    bundleName_ = context->GetBundleName();
    auto hapModuleInfo = context->GetHapModuleInfo();
    CHECK_NULL_VOID(hapModuleInfo);
    moduleName_ = hapModuleInfo->name;
    hapPath_ = hapModuleInfo->hapPath;
    isBundle_ = (hapModuleInfo->compileMode == AppExecFwk::CompileMode::JS_BUNDLE);
    SetConfiguration(context->GetConfiguration());
    context_ = context->weak_from_this();
}

UIContentImpl::UIContentImpl(OHOS::AppExecFwk::Ability* ability)
{
    CHECK_NULL_VOID(ability);
    context_ = ability->GetAbilityContext();
}

void UIContentImpl::DestroyUIDirector()
{
#ifndef NG_BUILD
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
#ifdef ENABLE_ROSEN_BACKEND
    auto rsUIDirector = pipelineContext->GetRSUIDirector();
    CHECK_NULL_VOID(rsUIDirector);
    LOGI("Destroying old rsUIDirectory");
    rsUIDirector->Destroy();
#endif
#endif
}

void UIContentImpl::DestroyCallback() const
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetNextFrameLayoutCallback(nullptr);
}

UIContentErrorCode UIContentImpl::InitializeInner(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, bool isNamedRouter)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    if (window && StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_TOAST_DIALOG_PREFIX)) {
        return CommonInitialize(window, contentInfo, storage);
    }
    if (window) {
        errorCode = CommonInitialize(window, contentInfo, storage);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }

    // ArkTSCard need no window : 梳理所有需要window和不需要window的场景
    if (isFormRender_ && !window) {
        LOGI("CommonInitializeForm url = %{public}s", contentInfo.c_str());
        errorCode = CommonInitializeForm(window, contentInfo, storage);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }
    LOGI("Initialize startUrl = %{public}s", startUrl_.c_str());
    // run page.
    errorCode = Platform::AceContainer::RunPage(instanceId_, startUrl_, "", isNamedRouter);
    CHECK_ERROR_CODE_RETURN(errorCode);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
    return errorCode;
}

void UIContentImpl::PreInitializeForm(OHOS::Rosen::Window* window, const std::string& url, napi_value storage)
{
    // ArkTSCard need no window
    if (isFormRender_ && !window) {
        LOGI("CommonInitializeForm url = %{public}s", url.c_str());
        CommonInitializeForm(window, url, storage);
    }
}

void UIContentImpl::RunFormPage()
{
    LOGI("Initialize startUrl = %{public}s", startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "", false);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
}

UIContentErrorCode UIContentImpl::Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage)
{
    return InitializeInner(window, url, storage, false);
}

UIContentErrorCode UIContentImpl::Initialize(
    OHOS::Rosen::Window* window, const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    errorCode = CommonInitialize(window, "", storage);
    CHECK_ERROR_CODE_RETURN(errorCode);
    if (content) {
        LOGI("Initialize by buffer, size:%{public}zu", content->size());
        // run page.
        errorCode = Platform::AceContainer::RunPage(instanceId_, content, "");
        CHECK_ERROR_CODE_RETURN(errorCode);
    } else {
        LOGE("Initialize failed, buffer is null");
    }
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
    return errorCode;
}

UIContentErrorCode UIContentImpl::InitializeByName(
    OHOS::Rosen::Window* window, const std::string& name, napi_value storage)
{
    return InitializeInner(window, name, storage, true);
}

void UIContentImpl::InitializeDynamic(
    const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint)
{
    isDynamicRender_ = true;
    hapPath_ = hapPath;
    auto env = reinterpret_cast<napi_env>(runtime_);
    CHECK_NULL_VOID(env);
    taskWrapper_ = std::make_shared<NG::UVTaskWrapperImpl>(env);

    CommonInitializeForm(nullptr, abcPath, nullptr);

    LOGI("Initialize DynamicComponent startUrl = %{public}s, entryPoint = %{public}s", startUrl_.c_str(),
        entryPoint.c_str());
    Platform::AceContainer::RunDynamicPage(instanceId_, startUrl_, "", entryPoint);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
}

void UIContentImpl::Initialize(
    OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowId)
{
    if (window) {
        CommonInitialize(window, url, storage);
    }
    if (focusWindowId != 0) {
        LOGI("UIExtension host window id:%{public}u", focusWindowId);
        Platform::AceContainer::GetContainer(instanceId_)->SetFocusWindowId(focusWindowId);
    }

    LOGI("UIExtension startUrl = %{public}s", startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
}

napi_value UIContentImpl::GetUINapiContext()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    ContainerScope scope(instanceId_);
    napi_value result = nullptr;
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, result);
    if (frontend->GetType() == FrontendType::DECLARATIVE_JS) {
#ifdef NG_BUILD
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend);
#else
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend);
#endif
        CHECK_NULL_RETURN(declarativeFrontend, result);
        return declarativeFrontend->GetContextValue();
    }

    return result;
}

UIContentErrorCode UIContentImpl::Restore(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    errorCode = CommonInitialize(window, contentInfo, storage);
    CHECK_ERROR_CODE_RETURN(errorCode);
    std::tie(startUrl_, errorCode) = Platform::AceContainer::RestoreRouterStack(instanceId_, contentInfo);
    CHECK_ERROR_CODE_RETURN(errorCode);
    if (startUrl_.empty()) {
        LOGW("UIContent Restore start url is empty");
    }
    LOGI("Restore startUrl = %{public}s", startUrl_.c_str());
    return Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
}

std::string UIContentImpl::GetContentInfo() const
{
    LOGI("UIContent GetContentInfo");
    return Platform::AceContainer::GetContentInfo(instanceId_);
}

// ArkTSCard start
UIContentErrorCode UIContentImpl::CommonInitializeForm(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    ACE_FUNCTION_TRACE();
    window_ = window;
    startUrl_ = contentInfo;
    auto errorCode = UIContentErrorCode::NO_ERRORS;

    if (window_) {
        if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_TOAST_DIALOG_PREFIX)) {
            InitializeSubWindow(window_, true);
            return errorCode;
        }
        if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_PREFIX)) {
            InitializeSubWindow(window_);
            return errorCode;
        }
    }

    auto context = context_.lock();
    static std::once_flag onceFlag;
    if (!isFormRender_) {
        std::call_once(onceFlag, [&context]() {
            SetHwIcuDirectory();
            Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
            AceApplicationInfo::GetInstance().SetProcessName(context->GetBundleName());
            AceApplicationInfo::GetInstance().SetPackageName(context->GetBundleName());
            AceApplicationInfo::GetInstance().SetDataFileDirPath(context->GetFilesDir());
            AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
            AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingRealPid());
            CapabilityRegistry::Register();
            ImageFileCache::GetInstance().SetImageCacheFilePath(context->GetCacheDir());
            ImageFileCache::GetInstance().SetCacheFileInfo();
        });
    }

    bool useNewPipe = true;
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
    }

    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    if (context) {
        auto resourceManager = context->GetResourceManager();
        if (resourceManager != nullptr) {
            resourceManager->GetResConfig(*resConfig);
            auto localeInfo = resConfig->GetLocaleInfo();
            Platform::AceApplicationInfoImpl::GetInstance().SetResourceManager(resourceManager);
            if (localeInfo != nullptr) {
                auto language = localeInfo->getLanguage();
                auto region = localeInfo->getCountry();
                auto script = localeInfo->getScript();
                AceApplicationInfo::GetInstance().SetLocale((language == nullptr) ? "" : language,
                    (region == nullptr) ? "" : region, (script == nullptr) ? "" : script, "");
            }
            if (resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK) {
                SystemProperties::SetColorMode(ColorMode::DARK);
                LOGI("UIContent set dark mode");
            } else {
                SystemProperties::SetColorMode(ColorMode::LIGHT);
                LOGI("UIContent set light mode");
            }
            SystemProperties::SetDeviceAccess(
                resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
        }
    }

    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
    } else {
        auto extensionContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(context);
        if (extensionContext) {
            info = extensionContext->GetAbilityInfo();
        }
    }
    if (info) {
        AceApplicationInfo::GetInstance().SetAbilityName(info->name);
    }

    RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    std::string moduleName = info != nullptr ? info->moduleName : "";
    auto appInfo = context != nullptr ? context->GetApplicationInfo() : nullptr;
    auto hapModuleInfo = context != nullptr ? context->GetHapModuleInfo() : nullptr;
    auto bundleName = info != nullptr ? info->bundleName : "";
    std::string moduleHapPath = info != nullptr ? info->hapPath : "";
    std::string resPath;
    std::string pageProfile;
    if (isFormRender_) {
        std::vector<std::string> basePaths;
        basePaths.emplace_back("assets/js/" + moduleName_ + "/");
        basePaths.emplace_back("assets/js/share/");
        basePaths.emplace_back("");
        basePaths.emplace_back("js/");
        basePaths.emplace_back("ets/");
        auto assetProvider = CreateAssetProviderImpl(hapPath_, basePaths, false);
        if (assetProvider) {
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    } else {
        if (isModelJson) {
            std::string hapPath = info != nullptr ? info->hapPath : "";
            // first use hap provider
            if (assetManagerImpl && !hapPath.empty()) {
                auto hapAssetProviderImpl = AceType::MakeRefPtr<HapAssetProviderImpl>();
                if (hapAssetProviderImpl->Initialize(hapPath, { "", "ets/", "resources/base/profile/" })) {
                    assetManagerImpl->PushBack(std::move(hapAssetProviderImpl));
                }
            }

            if (appInfo) {
                std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
                for (const auto& module : moduleList) {
                    if (module.moduleName == moduleName) {
                        std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                        auto moduleSourceDir =
                            std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                        resPath = moduleSourceDir + "/";
                        break;
                    }
                }
            }

            // second use file provider, will remove later
            auto assetBasePathStr = { std::string("ets/"), std::string("resources/base/profile/") };
            if (assetManagerImpl && !resPath.empty()) {
                auto assetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
                if (assetProvider->Initialize(resPath, assetBasePathStr)) {
                    assetManagerImpl->PushBack(std::move(assetProvider));
                }
            }

            if (hapModuleInfo) {
                pageProfile = hapModuleInfo->pages;
                const std::string profilePrefix = "$profile:";
                if (pageProfile.compare(0, profilePrefix.size(), profilePrefix) == 0) {
                    pageProfile = pageProfile.substr(profilePrefix.length()).append(".json");
                }
            }
        } else {
            auto packagePathStr = context->GetBundleCodeDir();
            if (hapModuleInfo != nullptr) {
                packagePathStr += "/" + hapModuleInfo->package + "/";
            }
            std::string srcPath = "";
            if (info != nullptr && !info->srcPath.empty()) {
                srcPath = info->srcPath;
            }

            auto assetBasePathStr = { "assets/js/" + (srcPath.empty() ? "default" : srcPath) + "/",
                std::string("assets/js/share/") };
            if (assetManagerImpl && !packagePathStr.empty()) {
                auto fileAssetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
                if (fileAssetProvider->Initialize(packagePathStr, assetBasePathStr)) {
                    assetManagerImpl->PushBack(std::move(fileAssetProvider));
                }
            }
            if (appInfo) {
                std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
                for (const auto& module : moduleList) {
                    if (module.moduleName == moduleName) {
                        std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                        auto moduleSourceDir =
                            std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                        resPath = moduleSourceDir + "/assets/" + module.moduleName + "/";
                        break;
                    }
                }
            }
        }
    }

    std::string hapPath; // hap path in sandbox
    if (!moduleHapPath.empty()) {
        if (moduleHapPath.find(ABS_BUNDLE_CODE_PATH) == std::string::npos) {
            hapPath = moduleHapPath;
        } else {
            auto pos = moduleHapPath.find_last_of('/');
            if (pos != std::string::npos) {
                hapPath = LOCAL_BUNDLE_CODE_PATH + moduleHapPath.substr(pos + 1);
            }
        }
    }

#ifdef PLUGIN_COMPONENT_SUPPORTED
    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(nullptr, pluginUtils);
#endif
    // create container
    if (runtime_) {
        instanceId_ = Container::GenerateId<STAGE_CONTAINER>();
    } else {
        instanceId_ = Container::GenerateId<FA_SUBWINDOW_CONTAINER>();
    }
#ifdef FORM_SUPPORTED
    auto formUtils = std::make_shared<FormUtilsImpl>();
    FormManager::GetInstance().SetFormUtils(formUtils);
#endif
    auto container =
        AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS, context_, info,
            std::make_unique<ContentEventCallback>(
                [window = window_] {
                    CHECK_NULL_VOID(window);
                    window->PerformBack();
                },
                [context = context_](const std::string& address) {
                    auto sharedContext = context.lock();
                    CHECK_NULL_VOID(sharedContext);
                    auto abilityContext =
                        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                    CHECK_NULL_VOID(abilityContext);
                    LOGI("start ability with url = %{private}s", address.c_str());
                    AAFwk::Want want;
                    want.AddEntity(Want::ENTITY_BROWSER);
                    want.SetUri(address);
                    want.SetAction(ACTION_VIEWDATA);
                    abilityContext->StartAbility(want, REQUEST_CODE);
                }),
            taskWrapper_, false, false, useNewPipe);

    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    container->SetIsFormRender(isFormRender_);
    container->SetIsDynamicRender(isDynamicRender_);
    container->SetIsFRSCardContainer(isFormRender_);
    if (window_) {
        container->SetWindowName(window_->GetWindowName());
        container->SetWindowId(window_->GetWindowId());
    }

    if (context) {
        auto token = context->GetToken();
        container->SetToken(token);
    }

    // Mark the relationship between windowId and containerId, it is 1:1
    if (window) {
        SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    }
    AceEngine::Get().AddContainer(instanceId_, container);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    container->SetPageProfile(pageProfile);
    container->Initialize();
    ContainerScope scope(instanceId_);
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(container);
    }
    auto aceResCfg = container->GetResourceConfiguration();
    aceResCfg.SetOrientation(SystemProperties::GetDeviceOrientation());
    aceResCfg.SetDensity(SystemProperties::GetResolution());
    aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
    aceResCfg.SetColorMode(SystemProperties::GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    if (isFormRender_) {
        resPath = "/data/bundles/" + bundleName_ + "/" + moduleName_ + "/";
        hapPath = hapPath_;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "CommonInitializeForm resPath = %{public}s hapPath = %{public}s", resPath.c_str(),
        hapPath.c_str());
    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);
    container->SetHapPath(hapPath);
    container->SetAssetManager(assetManagerImpl);

    if (!isFormRender_) {
        container->SetBundlePath(context->GetBundleCodeDir());
        container->SetFilesDataPath(context->GetFilesDir());
    }

    if (window_) {
        if (window_->IsDecorEnable()) {
            container->SetWindowModal(WindowModal::CONTAINER_MODAL);
        }

        dragWindowListener_ = new DragWindowListener(instanceId_);
        window_->RegisterDragListener(dragWindowListener_);
        occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
        window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
    }

    // create ace_view
    Platform::AceViewOhos* aceView = nullptr;
    if (isFormRender_ && !isDynamicRender_) {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, true, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    } else {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    }

    if (isFormRender_) {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, formWidth_, formHeight_, window_);
        CHECK_ERROR_CODE_RETURN(errorCode);
        auto frontend = AceType::DynamicCast<FormFrontendDeclarative>(container->GetFrontend());
        CHECK_NULL_RETURN(frontend, UIContentErrorCode::NULL_POINTER);
        frontend->SetBundleName(bundleName_);
        frontend->SetModuleName(moduleName_);
        // arkTSCard only support "esModule" compile mode
        frontend->SetIsBundle(false);
    } else {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }

    // after frontend initialize
    if (window_ && window_->IsFocused()) {
        Focus();
    }

    if (isFormRender_ && !isFormRenderInit_) {
        container->UpdateFormSharedImage(formImageDataMap_);
        container->UpdateFormData(formData_);
        isFormRenderInit_ = true;
    }

    if (isFormRender_) {
        Platform::AceViewOhos::SurfaceChanged(aceView, formWidth_, formHeight_, deviceHeight >= deviceWidth ? 0 : 1);
        // Set sdk version in module json mode for form
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    } else {
        Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    }
    // Set sdk version in module json mode
    if (isModelJson) {
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    }
    if (runtime_ && !isFormRender_) { // ArkTSCard not support inherit local strorage from context
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context->GetBindingObject()->Get<NativeReference>());
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(
                reinterpret_cast<NativeReference*>(ref), context->GetBindingObject()->Get<NativeReference>());
        }
    }

    return UIContentErrorCode::NO_ERRORS;
}

void UIContentImpl::SetConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (config == nullptr) {
        UErrorCode status = U_ZERO_ERROR;
        icu::Locale locale = icu::Locale::forLanguageTag(Global::I18n::LocaleConfig::GetSystemLanguage(), status);
        AceApplicationInfo::GetInstance().SetLocale(locale.getLanguage(), locale.getCountry(), locale.getScript(), "");
        SystemProperties::SetColorMode(ColorMode::LIGHT);
        return;
    }

    auto colorMode = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    auto deviceAccess = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
    auto languageTag = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
    if (!colorMode.empty()) {
        if (colorMode == "dark") {
            SystemProperties::SetColorMode(ColorMode::DARK);
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
        }
    }

    if (!deviceAccess.empty()) {
        // Event of accessing mouse or keyboard
        SystemProperties::SetDeviceAccess(deviceAccess == "true");
    }

    if (!languageTag.empty()) {
        std::string language;
        std::string script;
        std::string region;
        Localization::ParseLocaleTag(languageTag, language, script, region, false);
        if (!language.empty() || !script.empty() || !region.empty()) {
            AceApplicationInfo::GetInstance().SetLocale(language, region, script, "");
        }
    }
}

std::shared_ptr<Rosen::RSSurfaceNode> UIContentImpl::GetFormRootNode()
{
    return Platform::AceContainer::GetFormSurfaceNode(instanceId_);
}
// ArkTSCard end

UIContentErrorCode UIContentImpl::CommonInitialize(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    ACE_FUNCTION_TRACE();
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    window_ = window;
    CHECK_NULL_RETURN(window_, UIContentErrorCode::NULL_WINDOW);
    startUrl_ = contentInfo;
    if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_TOAST_DIALOG_PREFIX)) {
        InitializeSubWindow(window_, true);
        return errorCode;
    }
    if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_PREFIX)) {
        InitializeSubWindow(window_);
        return errorCode;
    }
    auto context = context_.lock();
    CHECK_NULL_RETURN(context, UIContentErrorCode::NULL_POINTER);
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&context]() {
        SetHwIcuDirectory();
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
        if (abilityContext) {
            int32_t missionId = -1;
            abilityContext->GetMissionId(missionId);
            AceApplicationInfo::GetInstance().SetMissionId(missionId);
        }
        AceApplicationInfo::GetInstance().SetProcessName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetPackageName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetDataFileDirPath(context->GetFilesDir());
        AceApplicationInfo::GetInstance().SetApiTargetVersion(context->GetApplicationInfo()->apiTargetVersion);
        AceApplicationInfo::GetInstance().SetAppVersionName(context->GetApplicationInfo()->versionName);
        AceApplicationInfo::GetInstance().SetAppVersionCode(context->GetApplicationInfo()->versionCode);
        AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
        AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingRealPid());
        CapabilityRegistry::Register();
        ImageFileCache::GetInstance().SetImageCacheFilePath(context->GetCacheDir());
        ImageFileCache::GetInstance().SetCacheFileInfo();
    });
    AceNewPipeJudgement::InitAceNewPipeConfig();
    auto apiCompatibleVersion = context->GetApplicationInfo()->apiCompatibleVersion;
    auto apiReleaseType = context->GetApplicationInfo()->apiReleaseType;
    auto apiTargetVersion = context->GetApplicationInfo()->apiTargetVersion;
    const auto& hapModuleInfo = context->GetHapModuleInfo();
    std::vector<OHOS::AppExecFwk::Metadata> metaData;
    if (hapModuleInfo) {
        metaData = hapModuleInfo->metadata;
    }
    bool closeArkTSPartialUpdate = std::any_of(metaData.begin(), metaData.end(), [](const auto& metaDataItem) {
        return metaDataItem.name == "ArkTSPartialUpdate" && metaDataItem.value == "false";
    });

    auto useNewPipe =
        AceNewPipeJudgement::QueryAceNewPipeEnabledStage(AceApplicationInfo::GetInstance().GetPackageName(),
            apiCompatibleVersion, apiTargetVersion, apiReleaseType, closeArkTSPartialUpdate);
    LOGI("UIContent: apiCompatibleVersion: %{public}d, apiTargetVersion: %{public}d, and apiReleaseType: %{public}s, "
         "useNewPipe: %{public}d",
        apiCompatibleVersion, apiTargetVersion, apiReleaseType.c_str(), useNewPipe);
#ifndef NG_BUILD
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    if (SystemProperties::GetRosenBackendEnabled() && !useNewPipe) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector) {
            rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());
            rsUiDirector->SetCacheDir(context->GetCacheDir());
            rsUiDirector->Init();
        }
    }
#endif
#endif
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    int32_t devicePhysicalWidth = 0;
    int32_t devicePhysicalHeight = 0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
        devicePhysicalWidth = defaultDisplay->GetPhysicalWidth();
        devicePhysicalHeight = defaultDisplay->GetPhysicalHeight();
    }
    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    SystemProperties::SetDevicePhysicalWidth(devicePhysicalWidth);
    SystemProperties::SetDevicePhysicalHeight(devicePhysicalHeight);
    // Initialize performance check parameters
    AceChecker::InitPerformanceParameters();
    AcePerformanceCheck::Start();
    SystemProperties::SetColorMode(ColorMode::LIGHT);

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    auto resourceManager = context->GetResourceManager();
    if (resourceManager != nullptr) {
        resourceManager->GetResConfig(*resConfig);
        auto localeInfo = resConfig->GetLocaleInfo();
        Platform::AceApplicationInfoImpl::GetInstance().SetResourceManager(resourceManager);
        if (localeInfo != nullptr) {
            auto language = localeInfo->getLanguage();
            auto region = localeInfo->getCountry();
            auto script = localeInfo->getScript();
            AceApplicationInfo::GetInstance().SetLocale((language == nullptr) ? "" : language,
                (region == nullptr) ? "" : region, (script == nullptr) ? "" : script, "");
        }
        if (resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK) {
            SystemProperties::SetColorMode(ColorMode::DARK);
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
        }
        SystemProperties::SetDeviceAccess(
            resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
    }

    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
    } else {
        auto extensionContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(context);
        if (!extensionContext) {
            return UIContentErrorCode::NULL_POINTER;
        }
        info = extensionContext->GetAbilityInfo();
    }
    if (info) {
        AceApplicationInfo::GetInstance().SetAbilityName(info->name);
    }
    RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    std::string moduleName = info != nullptr ? info->moduleName : "";
    auto appInfo = context->GetApplicationInfo();
    auto bundleName = info != nullptr ? info->bundleName : "";
    std::string moduleHapPath = info != nullptr ? info->hapPath : "";
    std::string resPath;
    std::string pageProfile;
    LOGI("Initialize UIContent isModelJson:%{public}s", isModelJson ? "true" : "false");
    if (isModelJson) {
        std::string hapPath = info != nullptr ? info->hapPath : "";
        // first use hap provider
        if (assetManagerImpl && !hapPath.empty()) {
            auto hapAssetProvider = AceType::MakeRefPtr<HapAssetProviderImpl>();
            if (hapAssetProvider->Initialize(hapPath, { "", "ets/", "resources/base/profile/" })) {
                assetManagerImpl->PushBack(std::move(hapAssetProvider));
            }
        }

        if (appInfo) {
            std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
            for (const auto& module : moduleList) {
                if (module.moduleName == moduleName) {
                    std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                    auto moduleSourceDir = std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                    resPath = moduleSourceDir + "/";
                    break;
                }
            }
        }

        // second use file provider, will remove later
        auto assetBasePathStr = { std::string("ets/"), std::string("resources/base/profile/") };
        if (assetManagerImpl && !resPath.empty()) {
            auto fileAssetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
            if (fileAssetProvider->Initialize(resPath, assetBasePathStr)) {
                assetManagerImpl->PushBack(std::move(fileAssetProvider));
            }
        }

        if (hapModuleInfo) {
            pageProfile = hapModuleInfo->pages;
            const std::string profilePrefix = "$profile:";
            if (pageProfile.compare(0, profilePrefix.size(), profilePrefix) == 0) {
                pageProfile = pageProfile.substr(profilePrefix.length()).append(".json");
            }
        }
    } else {
        auto packagePathStr = context->GetBundleCodeDir();
        if (hapModuleInfo != nullptr) {
            packagePathStr += "/" + hapModuleInfo->package + "/";
        }
        std::string srcPath = "";
        if (info != nullptr && !info->srcPath.empty()) {
            srcPath = info->srcPath;
        }

        auto assetBasePathStr = { "assets/js/" + (srcPath.empty() ? "default" : srcPath) + "/",
            std::string("assets/js/share/") };

        if (assetManagerImpl && !packagePathStr.empty()) {
            auto fileAssetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
            if (fileAssetProvider->Initialize(packagePathStr, assetBasePathStr)) {
                assetManagerImpl->PushBack(std::move(fileAssetProvider));
            }
        }
        if (appInfo) {
            std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
            for (const auto& module : moduleList) {
                if (module.moduleName == moduleName) {
                    std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                    auto moduleSourceDir = std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                    resPath = moduleSourceDir + "/assets/" + module.moduleName + "/";
                    break;
                }
            }
        }
    }

    std::string hapPath; // hap path in sandbox
    if (!moduleHapPath.empty()) {
        if (moduleHapPath.find(ABS_BUNDLE_CODE_PATH) == std::string::npos) {
            hapPath = moduleHapPath;
        } else {
            auto pos = moduleHapPath.find_last_of('/');
            if (pos != std::string::npos) {
                hapPath = LOCAL_BUNDLE_CODE_PATH + moduleHapPath.substr(pos + 1);
            }
        }
    }

#ifdef PLUGIN_COMPONENT_SUPPORTED
    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(nullptr, pluginUtils);
#endif
    // create container
    if (runtime_) {
        instanceId_ = Container::GenerateId<STAGE_CONTAINER>();
    } else {
        instanceId_ = Container::GenerateId<FA_SUBWINDOW_CONTAINER>();
    }
#ifdef FORM_SUPPORTED
    auto formUtils = std::make_shared<FormUtilsImpl>();
    FormManager::GetInstance().SetFormUtils(formUtils);
#endif
    auto container =
        AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS, context_, info,
            std::make_unique<ContentEventCallback>(
                [window = window_] {
                    CHECK_NULL_VOID(window);
                    window->PerformBack();
                },
                [context = context_](const std::string& address) {
                    auto sharedContext = context.lock();
                    CHECK_NULL_VOID(sharedContext);
                    auto abilityContext =
                        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                    CHECK_NULL_VOID(abilityContext);
                    LOGI("start ability with url = %{private}s", address.c_str());
                    AAFwk::Want want;
                    want.AddEntity(Want::ENTITY_BROWSER);
                    want.SetUri(address);
                    want.SetAction(ACTION_VIEWDATA);
                    abilityContext->StartAbility(want, REQUEST_CODE);
                }),
            false, false, useNewPipe);
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    container->SetWindowName(window_->GetWindowName());
    container->SetWindowId(window_->GetWindowId());
    auto token = context->GetToken();
    container->SetToken(token);
    container->SetParentToken(parentToken_);
    container->SetPageUrlChecker(AceType::MakeRefPtr<PageUrlCheckerOhos>(context, info));
    // Mark the relationship between windowId and containerId, it is 1:1
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    ContainerScope::Add(instanceId_);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    container->SetPageProfile(pageProfile);
    container->Initialize();
    ContainerScope scope(instanceId_);
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(container);
    }
    auto aceResCfg = container->GetResourceConfiguration();
    aceResCfg.SetOrientation(SystemProperties::GetDeviceOrientation());
    aceResCfg.SetDensity(SystemProperties::GetResolution());
    aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
    aceResCfg.SetColorMode(SystemProperties::GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);
    container->SetHapPath(hapPath);
    container->SetAssetManager(assetManagerImpl);

    container->SetBundlePath(context->GetBundleCodeDir());
    container->SetFilesDataPath(context->GetFilesDir());
    container->SetModuleName(hapModuleInfo->moduleName);
    container->SetIsModule(hapModuleInfo->compileMode == AppExecFwk::CompileMode::ES_MODULE);

    // for atomic service
    container->SetInstallationFree(hapModuleInfo && hapModuleInfo->installationFree);
    if (hapModuleInfo->installationFree) {
        container->SetSharePanelCallback(
            [context = context_](const std::string& bundleName, const std::string& abilityName) {
                auto sharedContext = context.lock();
                CHECK_NULL_VOID(sharedContext);
                auto abilityContext =
                    OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                CHECK_NULL_VOID(abilityContext);
                auto abilityInfo = abilityContext->GetAbilityInfo();
                AAFwk::Want want;
                want.SetParam("abilityName", abilityInfo->name);
                want.SetParam("bundleName", abilityInfo->bundleName);
                want.SetParam("moduleName", abilityInfo->moduleName);
                want.SetParam("hostPkgName", abilityInfo->bundleName);
                want.SetElementName(bundleName, abilityName);
                abilityContext->StartAbility(want, REQUEST_CODE);
            });
    }

    if (window_->IsDecorEnable()) {
        container->SetWindowModal(WindowModal::CONTAINER_MODAL);
    }
    dragWindowListener_ = new DragWindowListener(instanceId_);
    window_->RegisterDragListener(dragWindowListener_);
    occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
    window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
    foldStatusListener_ = new FoldScreenListener(instanceId_);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterFoldStatusListener(foldStatusListener_);
    foldDisplayModeListener_ = new FoldDisplayModeListener(instanceId_);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterDisplayModeListener(foldDisplayModeListener_);

    // create ace_view
    auto aceView =
        Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
    Platform::AceViewOhos::SurfaceCreated(aceView, window_);
#ifndef NG_BUILD
    if (!useNewPipe) {
        Ace::Platform::UIEnvCallback callback = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
        callback = [window, id = instanceId_, container, aceView, rsUiDirector](
                       const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) {
            if (rsUiDirector) {
                ACE_SCOPED_TRACE("OHOS::Rosen::RSUIDirector::Create()");
                rsUiDirector->SetUITaskRunner(
                    [taskExecutor = container->GetTaskExecutor(), id](const std::function<void()>& task) {
                        ContainerScope scope(id);
                        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
                    });
                auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
                if (context != nullptr) {
                    context->SetRSUIDirector(rsUiDirector);
                }
            }
        };
#endif
        // set view
        Platform::AceContainer::SetView(aceView, density, 0, 0, window_, callback);
    } else {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }
#else
    errorCode = Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
    CHECK_ERROR_CODE_RETURN(errorCode);
#endif

    // after frontend initialize
    if (window_->IsFocused()) {
        LOGI("UIContentImpl: focus again");
        Focus();
    }

    Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    auto pipeline = container->GetPipelineContext();
    // Use metadata to control the center-alignment of text at line height.
    bool halfLeading = std::any_of(metaData.begin(), metaData.end(),
        [](const auto& metaDataItem) { return metaDataItem.name == "half_leading" && metaDataItem.value == "true"; });
    pipeline->SetHalfLeading(halfLeading);
    container->CheckAndSetFontFamily();
    if (pipeline) {
        auto rsConfig = window_->GetKeyboardAnimationConfig();
        KeyboardAnimationConfig config = { rsConfig.curveType_, rsConfig.curveParams_, rsConfig.durationIn_,
            rsConfig.durationOut_ };
        pipeline->SetKeyboardAnimationConfig(config);
    }
    // Set sdk version in module json mode
    if (isModelJson) {
        if (pipeline && appInfo) {
            LOGI("SetMinPlatformVersion is %{public}d", appInfo->apiCompatibleVersion);
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    }
    if (runtime_) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context->GetBindingObject()->Get<NativeReference>());
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(
                reinterpret_cast<NativeReference*>(ref), context->GetBindingObject()->Get<NativeReference>());
        }
    }

    InitializeSafeArea(container);
    InitializeDisplayAvailableRect(container);

    // set container temp dir
    if (abilityContext) {
        if (!abilityContext->GetTempDir().empty()) {
            container->SetTempDir(abilityContext->GetTempDir());
        }
    } else {
        LOGI("UIContentImpl::OnStart abilityContext is null");
    }

    LayoutInspector::SetCallback(instanceId_);

    // setLogFunc of current app
    AddAlarmLogFunc();

    return errorCode;
}

void UIContentImpl::InitializeSafeArea(const RefPtr<Platform::AceContainer>& container)
{
    constexpr static int32_t PLATFORM_VERSION_TEN = 10;
    auto pipeline = container->GetPipelineContext();
    if (pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN && pipeline->GetIsAppWindow()) {
        avoidAreaChangedListener_ = new AvoidAreaChangedListener(instanceId_);
        window_->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
        pipeline->UpdateSystemSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_SYSTEM));
        pipeline->UpdateCutoutSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_CUTOUT));
        pipeline->UpdateNavSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR));
    }
}

void UIContentImpl::InitializeDisplayAvailableRect(const RefPtr<Platform::AceContainer>& container)
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    auto& DMManager = Rosen::DisplayManager::GetInstance();
    availableAreaChangedListener_ = new AvailableAreaChangedListener(instanceId_);
    DMManager.RegisterAvailableAreaListener(availableAreaChangedListener_);
    Rosen::DMRect availableArea;
    auto defaultDisplay = DMManager.GetDefaultDisplay();
    if (pipeline && defaultDisplay) {
        Rosen::DMError ret = defaultDisplay->GetAvailableArea(availableArea);
        if (ret == Rosen::DMError::DM_OK) {
            pipeline->UpdateDisplayAvailableRect(ConvertDMRect2Rect(availableArea));
        }
    }
}

void UIContentImpl::Foreground()
{
    LOGI("[%{public}s][%{public}s]: window foreground", bundleName_.c_str(), moduleName_.c_str());
    ContainerScope::UpdateRecentForeground(instanceId_);
    Platform::AceContainer::OnShow(instanceId_);
    // set the flag isForegroundCalled to be true
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetForegroundCalled(true);

    CHECK_NULL_VOID(window_);
    std::string windowName = window_->GetWindowName();
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, instanceId_, true);
}

void UIContentImpl::Background()
{
    LOGI("[%{public}s][%{public}s]: window background", bundleName_.c_str(), moduleName_.c_str());
    Platform::AceContainer::OnHide(instanceId_);

    CHECK_NULL_VOID(window_);
    std::string windowName = window_->GetWindowName();
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, instanceId_, false);
}

void UIContentImpl::ReloadForm(const std::string& url)
{
    startUrl_ = url;
    LOGI("ReloadForm startUrl = %{public}s", startUrl_.c_str());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto assetManager = AceType::DynamicCast<AssetManagerImpl>(container->GetAssetManager());
    assetManager->ReloadProvider();
    container->UpdateResource();
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
}

SerializedGesture UIContentImpl::GetFormSerializedGesture()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, SerializedGesture {});
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, SerializedGesture {});
    return pipelineContext->GetSerializedGesture();
}

void UIContentImpl::Focus()
{
    LOGI("%{public}s window focus", bundleName_.c_str());
    ContainerScope::UpdateRecentActive(instanceId_);
    Platform::AceContainer::OnActive(instanceId_);
    CHECK_NULL_VOID(window_);
    std::string windowName = window_->GetWindowName();
    Recorder::EventRecorder::Get().SetFocusContainerInfo(windowName, instanceId_);
}

void UIContentImpl::UnFocus()
{
    LOGI("%{public}s window unfocus", bundleName_.c_str());
    Platform::AceContainer::OnInactive(instanceId_);
}

void UIContentImpl::Destroy()
{
    LOGI("%{public}s window destroy", bundleName_.c_str());
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    // stop performance check and output json file
    AcePerformanceCheck::Stop();
    if (AceType::InstanceOf<Platform::DialogContainer>(container)) {
        Platform::DialogContainer::DestroyContainer(instanceId_);
    } else {
        Platform::AceContainer::DestroyContainer(instanceId_);
    }
    ContainerScope::RemoveAndCheck(instanceId_);
}

void UIContentImpl::OnNewWant(const OHOS::AAFwk::Want& want)
{
    LOGI("UIContent OnNewWant");
    std::string params = want.GetStringParam(START_PARAMS_KEY);
    Platform::AceContainer::OnNewRequest(instanceId_, params);
}

uint32_t UIContentImpl::GetBackgroundColor()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, 0x000000);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, 0x000000);
    ContainerScope scope(instanceId_);
    uint32_t bgColor = 0x000000;
    taskExecutor->PostSyncTask(
        [&bgColor, container]() {
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            bgColor = pipelineContext->GetAppBgColor().GetValue();
        },
        TaskExecutor::TaskType::UI);

    LOGI("UIContentImpl GetBackgroundColor, value is %{public}u", bgColor);
    return bgColor;
}

void UIContentImpl::SetBackgroundColor(uint32_t color)
{
    LOGI("UIContentImpl: SetBackgroundColor color is %{public}u", color);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, bgColor = color]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetAppBgColor(Color(bgColor));
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::GetAppPaintSize(OHOS::Rosen::Rect& paintrect)
{
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_VOID(stageNode);
    auto renderContext = stageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintRectf = renderContext->GetPaintRectWithoutTransform();
    auto offset = stageNode->GetPaintRectOffset(false);
    paintrect.posX_ = static_cast<int>(offset.GetX());
    paintrect.posY_ = static_cast<int>(offset.GetY());
    paintrect.width_ = static_cast<uint32_t>(paintRectf.Width());
    paintrect.height_ = static_cast<uint32_t>(paintRectf.Height());
}

bool UIContentImpl::ProcessBackPressed()
{
    LOGI("OnBackPressed called");
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (pipeline) {
        auto uiExtMgr = pipeline->GetUIExtensionManager();
        if (uiExtMgr && uiExtMgr->OnBackPressed()) {
            return true;
        }
    }
    bool ret = false;
    taskExecutor->PostSyncTask(
        [container, this, &ret]() {
            if (AceType::InstanceOf<Platform::DialogContainer>(container)) {
                if (Platform::DialogContainer::OnBackPressed(instanceId_)) {
                    LOGI("UIContentImpl ProcessBackPressed DialogContainer return true");
                    ret = true;
                }
            } else {
                LOGI("UIContentImpl ProcessBackPressed AceContainer");
                PerfMonitor::GetPerfMonitor()->RecordInputEvent(LAST_UP, UNKNOWN_SOURCE, 0);
                if (Platform::AceContainer::OnBackPressed(instanceId_)) {
                    LOGI("UIContentImpl ProcessBackPressed AceContainer return true");
                    ret = true;
                }
            }
        },
        TaskExecutor::TaskType::UI);
    return ret;
}

bool UIContentImpl::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(AceEngine::Get().GetContainer(instanceId_));
    CHECK_NULL_RETURN(container, false);
    container->SetCurPointerEvent(pointerEvent);
    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
            "PointerEvent Process to ui_content, eventInfo: id:%{public}d, "
            "WindowName = %{public}s, WindowId = %{public}d, ViewWidth = %{public}d, ViewHeight = %{public}d, "
            "ViewPosX = %{public}d, ViewPosY = %{public}d",
            pointerEvent->GetId(), container->GetWindowName().c_str(), container->GetWindowId(),
            container->GetViewWidth(), container->GetViewHeight(), container->GetViewPosX(), container->GetViewPosY());
    }
    auto* aceView = static_cast<Platform::AceViewOhos*>(container->GetView());
    Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent);
    return true;
}

bool UIContentImpl::ProcessPointerEventWithCallback(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void()>& callback)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(AceEngine::Get().GetContainer(instanceId_));
    CHECK_NULL_RETURN(container, false);
    container->SetCurPointerEvent(pointerEvent);
    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
            "PointerEvent Process to ui_content, eventInfo: id:%{public}d, "
            "WindowName = %{public}s, WindowId = %{public}d, ViewWidth = %{public}d, ViewHeight = %{public}d, "
            "ViewPosX = %{public}d, ViewPosY = %{public}d",
            pointerEvent->GetId(), container->GetWindowName().c_str(), container->GetWindowId(),
            container->GetViewWidth(), container->GetViewHeight(), container->GetViewPosX(), container->GetViewPosY());
    }
    auto* aceView = static_cast<Platform::AceViewOhos*>(container->GetView());
    Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent, nullptr, callback);
    return true;
}

bool UIContentImpl::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& touchEvent)
{
    TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
        "KeyEvent Process to ui_content, eventInfo: id:%{public}d, "
        "keyEvent info: keyCode is %{public}d, "
        "keyAction is %{public}d, keyActionTime is %{public}" PRId64,
        touchEvent->GetId(), touchEvent->GetKeyCode(), touchEvent->GetKeyAction(), touchEvent->GetActionTime());
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto* aceView = static_cast<Platform::AceViewOhos*>(container->GetView());
    return Platform::AceViewOhos::DispatchKeyEvent(aceView, touchEvent);
}

bool UIContentImpl::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}

bool UIContentImpl::ProcessVsyncEvent(uint64_t timeStampNanos)
{
    return false;
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    LOGI("UIContentImpl: UpdateConfiguration called");
    CHECK_NULL_VOID(config);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weakContainer = WeakPtr<Platform::AceContainer>(container), config]() {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_VOID(container);
            Platform::ParsedConfig parsedConfig;
            parsedConfig.colorMode = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
            parsedConfig.deviceAccess = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
            parsedConfig.languageTag = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
            parsedConfig.direction = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DIRECTION);
            parsedConfig.densitydpi = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DENSITYDPI);
            parsedConfig.themeTag = config->GetItem("ohos.application.theme");
            container->UpdateConfiguration(parsedConfig, config->GetName());
            LOGI("UIContentImpl: UpdateConfiguration called End, name:%{public}s", config->GetName().c_str());
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    LOGI("UIContentImpl: UpdateViewportConfig %{public}s", config.ToString().c_str());
    SystemProperties::SetDeviceOrientation(config.Orientation());
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    // The density of sub windows related to dialog needs to be consistent with the main window.
    auto modifyConfig = config;
    if (instanceId_ >= MIN_SUBCONTAINER_ID) {
        auto parentContainer = Platform::AceContainer::GetContainer(container->GetParentId());
        CHECK_NULL_VOID(parentContainer);
        auto parentPipeline = parentContainer->GetPipelineContext();
        CHECK_NULL_VOID(parentPipeline);
        modifyConfig.SetDensity(parentPipeline->GetDensity());
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [config = modifyConfig, container, reason, rsTransaction, rsWindow = window_]() {
        container->SetWindowPos(config.Left(), config.Top());
        auto pipelineContext = container->GetPipelineContext();
        if (pipelineContext) {
            pipelineContext->SetDisplayWindowRectInfo(
                Rect(Offset(config.Left(), config.Top()), Size(config.Width(), config.Height())));
            if (rsWindow) {
                pipelineContext->SetIsLayoutFullScreen(
                    rsWindow->GetMode() == Rosen::WindowMode::WINDOW_MODE_FULLSCREEN);
                auto isNeedAvoidWindowMode =
                    (rsWindow->GetMode() == Rosen::WindowMode::WINDOW_MODE_FLOATING ||
                        rsWindow->GetMode() == Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
                        rsWindow->GetMode() == Rosen::WindowMode::WINDOW_MODE_SPLIT_SECONDARY) &&
                    (SystemProperties::GetDeviceType() == DeviceType::PHONE ||
                        SystemProperties::GetDeviceType() == DeviceType::TABLET);
                pipelineContext->SetIsNeedAvoidWindow(isNeedAvoidWindowMode);
            }
            if (reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION) {
                pipelineContext->FlushBuild();
            }
        }
        auto aceView = static_cast<Platform::AceViewOhos*>(container->GetAceView());
        CHECK_NULL_VOID(aceView);
        Platform::AceViewOhos::SetViewportMetrics(aceView, config); // update density into pipeline
        Platform::AceViewOhos::SurfaceChanged(aceView, config.Width(), config.Height(), config.Orientation(),
            static_cast<WindowSizeChangeReason>(reason), rsTransaction);
        Platform::AceViewOhos::SurfacePositionChanged(aceView, config.Left(), config.Top());
        SubwindowManager::GetInstance()->ClearToastInSubwindow();
    };
    if (container->IsUseStageModel() && reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION) {
        task();
    } else {
        taskExecutor->PostTask(task, TaskExecutor::TaskType::PLATFORM);
    }
}

void UIContentImpl::SetIgnoreViewSafeArea(bool ignoreViewSafeArea)
{
    LOGI("UIContentImpl: SetIgnoreViewSafeArea:%{public}u", ignoreViewSafeArea);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipeline = container->GetPipelineContext();
    const static int32_t PLATFORM_VERSION_TEN = 10;
    CHECK_NULL_VOID(
        pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN && pipeline->GetIsAppWindow());
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, ignoreSafeArea = ignoreViewSafeArea]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetIgnoreViewSafeArea(ignoreSafeArea);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDeco)
{
    LOGI("UIContentImpl: UpdateWindowMode, window mode is %{public}d, hasDeco is %{public}d", mode, hasDeco);
    UpdateDecorVisible(mode == OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING, hasDeco);
}

void UIContentImpl::UpdateDecorVisible(bool visible, bool hasDeco)
{
    LOGI("UIContentImpl: UpdateWindowMode, window visible is %{public}d, hasDeco is %{public}d", visible, hasDeco);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, visible, hasDeco]() {
           auto pipelineContext = container->GetPipelineContext();
           CHECK_NULL_VOID(pipelineContext);
           pipelineContext->ShowContainerTitle(visible, hasDeco);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateMaximizeMode(OHOS::Rosen::MaximizeMode mode)
{
    LOGI("UIContentImpl: UpdateMaximizeMode, maximize mode is %{public}d", mode);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, mode]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto windowManager = pipelineContext->GetWindowManager();
            CHECK_NULL_VOID(windowManager);
            windowManager->SetCurrentWindowMaximizeMode(static_cast<OHOS::Ace::MaximizeMode>(mode));
            pipelineContext->ShowContainerTitle(true, true, true);
        },
        TaskExecutor::TaskType::UI);
}

bool UIContentImpl::NeedSoftKeyboard()
{
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->NeedSoftKeyboard();
}

void UIContentImpl::SetOnWindowFocused(const std::function<void()>& callback)
{
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetOnWindowFocused(callback);
}

void UIContentImpl::HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    LOGI("HideWindowTitleButton hideSplit: %{public}d, hideMaximize: %{public}d, hideMinimize: %{public}d", hideSplit,
        hideMaximize, hideMinimize);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, hideSplit, hideMaximize, hideMinimize]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetContainerButtonHide(hideSplit, hideMaximize, hideMinimize);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateTitleInTargetPos(bool isShow, int32_t height)
{
    LOGI("UIContentImpl: UpdateTitleInTargetPos, isShow %{public}d, height is %{public}d", isShow, height);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, isShow, height]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateTitleInTargetPos(isShow, height);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto ret = taskExecutor->PostSyncTaskTimeout(
        [&]() { container->Dump(params, info); }, TaskExecutor::TaskType::UI, 1500); // timeout 1.5s
    if (!ret) {
        LOGE("DumpInfo failed");
    }
}

void UIContentImpl::InitializeSubWindow(OHOS::Rosen::Window* window, bool isDialog)
{
    window_ = window;
    LOGI("The window name is %{public}s", window->GetWindowName().c_str());
    CHECK_NULL_VOID(window_);
    RefPtr<Container> container;
    instanceId_ = Container::GenerateId<COMPONENT_SUBWINDOW_CONTAINER>();

    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo;
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext;
    if (isDialog) {
        UErrorCode status = U_ZERO_ERROR;
        icu::Locale locale = icu::Locale::forLanguageTag(Global::I18n::LocaleConfig::GetSystemLanguage(), status);
        AceApplicationInfo::GetInstance().SetLocale(locale.getLanguage(), locale.getCountry(), locale.getScript(), "");
        container = AceType::MakeRefPtr<Platform::DialogContainer>(instanceId_, FrontendType::DECLARATIVE_JS);
    } else {
#ifdef NG_BUILD
        container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS,
            runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
                // Sub-window ,just return.
                LOGI("Content event callback");
            }),
            false, true, true);
#else
        if (Container::IsCurrentUseNewPipeline()) {
            container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS,
                runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
                    // Sub-window ,just return.
                    LOGI("Content event callback");
                }),
                false, true, true);
        } else {
            container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS,
                runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
                    // Sub-window ,just return.
                    LOGI("Content event callback");
                }),
                false, true);
        }
#endif
    }
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    touchOutsideListener_ = new TouchOutsideListener(instanceId_);
    window_->RegisterTouchOutsideListener(touchOutsideListener_);
    dragWindowListener_ = new DragWindowListener(instanceId_);
    window_->RegisterDragListener(dragWindowListener_);
    occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
    window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
    foldStatusListener_ = new FoldScreenListener(instanceId_);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterFoldStatusListener(foldStatusListener_);
    foldDisplayModeListener_ = new FoldDisplayModeListener(instanceId_, isDialog);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterDisplayModeListener(foldDisplayModeListener_);
}

void UIContentImpl::SetNextFrameLayoutCallback(std::function<void()>&& callback)
{
    CHECK_NULL_VOID(callback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetNextFrameLayoutCallback(std::move(callback));
}

void UIContentImpl::SetFrameLayoutFinishCallback(std::function<void()>&& callback)
{
    CHECK_NULL_VOID(callback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddPersistAfterLayoutTask(std::move(callback));
    LOGI("SetFrameLayoutFinishCallback SUCCESS");
}

void UIContentImpl::NotifyMemoryLevel(int32_t level)
{
    LOGI("Receive Memory level notification, level: %{public}d", level);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    pipelineContext->NotifyMemoryLevel(level);
}

void UIContentImpl::SetAppWindowTitle(const std::string& title)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    LOGI("set app title");
    pipelineContext->SetAppTitle(title);
}

void UIContentImpl::SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    LOGI("set app icon");
    pipelineContext->SetAppIcon(AceType::MakeRefPtr<PixelMapOhos>(pixelMap));
}

void UIContentImpl::UpdateFormData(const std::string& data)
{
    if (isFormRenderInit_) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        container->UpdateFormData(data);
    } else {
        formData_ = data;
    }
}

void UIContentImpl::UpdateFormSharedImage(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap)
{
    if (isFormRenderInit_) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        container->UpdateFormSharedImage(imageDataMap);
    } else {
        formImageDataMap_ = imageDataMap;
    }
}

void UIContentImpl::SetActionEventHandler(std::function<void(const std::string& action)>&& actionCallback)
{
    CHECK_NULL_VOID(actionCallback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetActionEventHandler(std::move(actionCallback));
}

void UIContentImpl::SetFormLinkInfoUpdateHandler(std::function<void(const std::vector<std::string>&)>&& callback)
{
    CHECK_NULL_VOID(callback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFormLinkInfoUpdateHandler(std::move(callback));
}

void UIContentImpl::SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback)
{
    CHECK_NULL_VOID(errorCallback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    return front->SetErrorEventHandler(std::move(errorCallback));
}

void UIContentImpl::OnFormSurfaceChange(float width, float height)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    auto density = pipelineContext->GetDensity();
    pipelineContext->SetRootSize(density, width, height);
    pipelineContext->OnSurfaceChanged(width, height);
}

void UIContentImpl::SetFormBackgroundColor(const std::string& color)
{
    LOGI("UIContentImpl: SetFormBackgroundColor color is %{public}s", color.c_str());
    if (!Rosen::RSSystemProperties::GetUniRenderEnabled()) {
        // cannot set transparent background effects in not-uniform-render mode
        return;
    }
    Color bgColor;
    if (!Color::ParseColorString(color, bgColor)) {
        return;
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, bgColor]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetAppBgColor(bgColor);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::GetResourcePaths(std::vector<std::string>& resourcesPaths, std::string& assetRootPath,
    std::vector<std::string>& assetBasePaths, std::string& resFolderName)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void UIContentImpl::SetResourcePaths(const std::vector<std::string>& resourcesPaths, const std::string& assetRootPath,
    const std::vector<std::string>& assetBasePaths)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, resourcesPaths, assetRootPath, assetBasePaths]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto assetManager = pipelineContext->GetAssetManager();
            CHECK_NULL_VOID(assetManager);
            auto themeManager = pipelineContext->GetThemeManager();
            CHECK_NULL_VOID(themeManager);

            if (resourcesPaths.empty() && assetRootPath.empty()) {
                return;
            }

            if (!assetRootPath.empty()) {
                auto fileAssetProviderImpl = AceType::MakeRefPtr<FileAssetProviderImpl>();
                if (fileAssetProviderImpl->Initialize(assetRootPath, assetBasePaths)) {
                    assetManager->PushBack(std::move(fileAssetProviderImpl));
                }
                return;
            }
            for (auto iter = resourcesPaths.begin(); iter != resourcesPaths.end(); iter++) {
                auto hapAssetProviderImpl = AceType::MakeRefPtr<HapAssetProviderImpl>();
                if (hapAssetProviderImpl->Initialize(*iter, assetBasePaths)) {
                    assetManager->PushBack(std::move(hapAssetProviderImpl));
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void UIContentImpl::SetIsFocusActive(bool isFocusActive)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, isFocusActive]() {
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetIsFocusActive(isFocusActive);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateResource()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([container]() { container->UpdateResource(); }, TaskExecutor::TaskType::UI);
}

int32_t UIContentImpl::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, 0);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, 0);
    int32_t sessionId = 0;
    taskExecutor->PostSyncTask(
        [container, &sessionId, want, callbacks = callbacks, config = config]() {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            sessionId =
                overlay->CreateModalUIExtension(want, callbacks, config.isProhibitBack, config.isAsyncModalBinding);
        },
        TaskExecutor::TaskType::UI);
    LOGI("UIExtension create modal page end, sessionId=%{public}d", sessionId);
    return sessionId;
}

void UIContentImpl::CloseModalUIExtension(int32_t sessionId)
{
    LOGI("UIExtension close modal page start, sessionId=%{public}d", sessionId);
    if (sessionId == 0) {
        LOGW("UIExtension refuse to close modal page");
        return;
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, sessionId]() {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            overlay->CloseModalUIExtension(sessionId);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::SetParentToken(sptr<IRemoteObject> token)
{
    parentToken_ = token;
}

sptr<IRemoteObject> UIContentImpl::GetParentToken()
{
    return parentToken_;
}

bool UIContentImpl::CheckNeedAutoSave()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    ContainerScope scope(instanceId_);
    bool needAutoSave = false;
    taskExecutor->PostSyncTask(
        [&needAutoSave, container]() {
            CHECK_NULL_VOID(container);
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipelineContext);
            needAutoSave = pipelineContext->CheckNeedAutoSave();
        },
        TaskExecutor::TaskType::UI);

    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UIContentImpl CheckNeedAutoSave, value is %{public}d", needAutoSave);
    return needAutoSave;
}

bool UIContentImpl::DumpViewData(AbilityBase::ViewData& viewData)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    ContainerScope scope(instanceId_);
    bool ret = false;
    taskExecutor->PostSyncTask(
        [this, &ret, &viewData]() {
            auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
            CHECK_NULL_VOID(viewDataWrap);
            ret = DumpViewData(nullptr, viewDataWrap);
            auto viewDataWrapOhos = AceType::DynamicCast<ViewDataWrapOhos>(viewDataWrap);
            CHECK_NULL_VOID(viewDataWrapOhos);
            viewData = viewDataWrapOhos->GetViewData();
        },
        TaskExecutor::TaskType::UI);

    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UIContentImpl DumpViewData, ret is %{public}d", ret);
    return ret;
}

bool UIContentImpl::DumpViewData(const RefPtr<NG::FrameNode>& node, RefPtr<ViewDataWrap> viewDataWrap)
{
    CHECK_NULL_RETURN(viewDataWrap, false);
    auto context = context_.lock();
    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
    } else {
        auto extensionContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(context);
        if (extensionContext) {
            info = extensionContext->GetAbilityInfo();
        } else {
            TAG_LOGE(AceLogTag::ACE_AUTO_FILL, "context is not AbilityContext or ExtensionContext.");
            return false;
        }
    }
    CHECK_NULL_RETURN(info, false);
    viewDataWrap->SetAbilityName(info->name);
    viewDataWrap->SetModuleName(info->moduleName);
    viewDataWrap->SetBundleName(info->bundleName);
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "bundleName=[%{private}s], moduleName=[%{private}s], abilityName=[%{private}s]",
        info->bundleName.c_str(), info->moduleName.c_str(), info->name.c_str());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->DumpPageViewData(node, viewDataWrap);
}

void UIContentImpl::ProcessFormVisibleChange(bool isVisible)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, isVisible]() {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            pipeline->HandleFormVisibleChangeEvent(isVisible);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::SearchElementInfoByAccessibilityId(
    int64_t elementId, int32_t mode, int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SearchElementInfoByAccessibilityIdNG(elementId, mode, baseParent, output);
}

void UIContentImpl::SearchElementInfosByText(int64_t elementId, const std::string& text, int64_t baseParent,
    std::list<Accessibility::AccessibilityElementInfo>& output)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SearchElementInfosByTextNG(elementId, text, baseParent, output);
}

void UIContentImpl::FindFocusedElementInfo(
    int64_t elementId, int32_t focusType, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->FindFocusedElementInfoNG(elementId, focusType, baseParent, output);
}

void UIContentImpl::FocusMoveSearch(
    int64_t elementId, int32_t direction, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->FocusMoveSearchNG(elementId, direction, baseParent, output);
}

bool UIContentImpl::NotifyExecuteAction(
    int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    return container->NotifyExecuteAction(elementId, actionArguments, action, offset);
}

std::string UIContentImpl::RecycleForm()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    std::string statusData;
    CHECK_NULL_RETURN(container, statusData);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, statusData);
    return pipeline->OnFormRecycle();
}

void UIContentImpl::RecoverForm(const std::string& statusData)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    return pipeline->OnFormRecover(statusData);
}

void UIContentImpl::RemoveOldPopInfoIfExsited(bool isShowInSubWindow, int32_t nodeId)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    if (isShowInSubWindow) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId());
        CHECK_NULL_VOID(subwindow);
        overlayManager = subwindow->GetOverlayManager();
    }

    CHECK_NULL_VOID(overlayManager);
    if (overlayManager->HasPopupInfo(nodeId)) {
        LOGD("Target node id=%{public}d has old popup info, erase it", nodeId);
        overlayManager->ErasePopupInfo(nodeId);
    }
}

RefPtr<PopupParam> UIContentImpl::CreateCustomPopupParam(bool isShow, const CustomPopupUIExtensionConfig& config)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(isShow);
    popupParam->SetUseCustomComponent(true);
    popupParam->SetShowInSubWindow(config.isShowInSubWindow);

    if (config.isAutoCancel.has_value()) {
        popupParam->SetHasAction(!config.isAutoCancel.value());
    }

    if (config.isEnableArrow.has_value()) {
        popupParam->SetEnableArrow(config.isEnableArrow.value());
    }

    if (config.targetOffset.has_value()) {
        PopupOffset targetOffset = config.targetOffset.value();
        DimensionUnit unit = static_cast<DimensionUnit>(targetOffset.unit);
        if (unit != DimensionUnit::PERCENT) { // not support percent settings
            CalcDimension dx(targetOffset.deltaX, unit);
            CalcDimension dy(targetOffset.deltaY, unit);
            popupParam->SetTargetOffset(Offset(dx.ConvertToPx(), dy.ConvertToPx()));
        }
    }

    if (config.targetSpace.has_value()) {
        PopupLength targetSpace = config.targetSpace.value();
        DimensionUnit unit = static_cast<DimensionUnit>(targetSpace.unit);
        popupParam->SetTargetSpace(CalcDimension(targetSpace.length, unit));
    }

    if (config.arrowOffset.has_value()) {
        PopupLength arrowOffset = config.arrowOffset.value();
        DimensionUnit unit = static_cast<DimensionUnit>(arrowOffset.unit);
        popupParam->SetArrowOffset(CalcDimension(arrowOffset.length, unit));
    }

    if (config.placement.has_value()) {
        popupParam->SetPlacement(static_cast<Placement>(config.placement.value()));
    }

    if (config.backgroundColor.has_value()) {
        popupParam->SetBackgroundColor(Color(config.backgroundColor.value()));
    }

    if (config.maskColor.has_value()) {
        popupParam->SetMaskColor(Color(config.maskColor.value()));
    }
    return popupParam;
}

void UIContentImpl::OnPopupStateChange(
    const std::string& event, const CustomPopupUIExtensionConfig& config, int32_t nodeId)
{
    if (config.onStateChange) {
        config.onStateChange(event);
    }

    auto visible = JsonUtil::ParseJsonString(event);
    CHECK_NULL_VOID(visible);
    bool isVisible = visible->GetBool("isVisible");
    if (isVisible) {
        return;
    }

    LOGD("Created custom popup is invisible");
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask([config, nodeId]() { RemoveOldPopInfoIfExsited(config.isShowInSubWindow, nodeId); },
        TaskExecutor::TaskType::UI, 100); // delay 100ms
    customPopupConfigMap_.erase(nodeId);
}

int32_t UIContentImpl::CreateCustomPopupUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const CustomPopupUIExtensionConfig& config)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, 0);
    int32_t nodeId = 0;
    taskExecutor->PostSyncTask(
        [want, &nodeId, callbacks = callbacks, config = config, this]() {
            if (config.inspectorId.empty()) {
                return;
            }
            auto targetNode = NG::Inspector::GetFrameNodeByKey(config.inspectorId);
            CHECK_NULL_VOID(targetNode);
            if (customPopupConfigMap_.find(targetNode->GetId()) != customPopupConfigMap_.end()) {
                LOGW("Nodeid=%{public}d has unclosed popup, cannot create new", targetNode->GetId());
                return;
            }

            auto popupParam = CreateCustomPopupParam(true, config);
            auto uiExtNode = ModalUIExtension::Create(want, callbacks);
            if (config.targetSize.has_value()) {
                auto layoutProperty = uiExtNode->GetLayoutProperty();
                CHECK_NULL_VOID(layoutProperty);
                PopupSize targetSize = config.targetSize.value();
                DimensionUnit unit = static_cast<DimensionUnit>(targetSize.unit);
                auto width = NG::CalcLength(targetSize.width, unit);
                auto height = NG::CalcLength(targetSize.height, unit);
                layoutProperty->UpdateUserDefinedIdealSize(NG::CalcSize(width, height));
            }
            uiExtNode->MarkModifyDone();
            nodeId = targetNode->GetId();
            popupParam->SetOnStateChange(
                [config, nodeId, this](const std::string& event) { this->OnPopupStateChange(event, config, nodeId); });

            NG::ViewAbstract::BindPopup(popupParam, targetNode, AceType::DynamicCast<NG::UINode>(uiExtNode));
            customPopupConfigMap_[nodeId] = config;
        },
        TaskExecutor::TaskType::UI);
    LOGI("Create custom popup with UIExtension end, nodeId=%{public}d", nodeId);
    return nodeId;
}

void UIContentImpl::DestroyCustomPopupUIExtension(int32_t nodeId)
{
    LOGI("Destroy custom popup start, nodeId=%{public}d", nodeId);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto popupConfig = customPopupConfigMap_.find(nodeId);
    if (popupConfig == customPopupConfigMap_.end()) {
        LOGW("Node doesn't hava popup or closed already");
        return;
    }
    auto config = popupConfig->second;
    taskExecutor->PostTask(
        [container, nodeId, config, this]() {
            auto targetNode =
                AceType::DynamicCast<NG::FrameNode>(ElementRegister::GetInstance()->GetUINodeById(nodeId));
            CHECK_NULL_VOID(targetNode);
            auto popupParam = CreateCustomPopupParam(false, config);
            NG::ViewAbstract::BindPopup(popupParam, targetNode, nullptr);
            RemoveOldPopInfoIfExsited(config.isShowInSubWindow, nodeId);
            customPopupConfigMap_.erase(nodeId);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [customTitleSettedShow, floatingTitleSettedShow]() {
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->SetContainerModalTitleVisible(customTitleSettedShow, floatingTitleSettedShow);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::SetContainerModalTitleHeight(int32_t height)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [height]() {
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->SetContainerModalTitleHeight(height);
        },
        TaskExecutor::TaskType::UI);
}

int32_t UIContentImpl::GetContainerModalTitleHeight()
{
    ContainerScope scope(instanceId_);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, -1);
    return pipeline->GetContainerModalTitleHeight();
}

bool UIContentImpl::GetContainerModalButtonsRect(Rosen::Rect& containerModal, Rosen::Rect& buttons)
{
    NG::RectF floatContainerModal;
    NG::RectF floatButtons;
    ContainerScope scope(instanceId_);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (!pipeline->GetContainerModalButtonsRect(floatContainerModal, floatButtons)) {
        return false;
    }
    containerModal = ConvertToRSRect(floatContainerModal);
    buttons = ConvertToRSRect(floatButtons);
    return true;
}

void UIContentImpl::SubscribeContainerModalButtonsRectChange(
    std::function<void(Rosen::Rect& containerModal, Rosen::Rect& buttons)>&& callback)
{
    ContainerScope scope(instanceId_);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (callback == nullptr) {
        pipeline->SubscribeContainerModalButtonsRectChange(nullptr);
        return;
    }
    std::function<void(NG::RectF&, NG::RectF&)> wrapFunc = [cb = std::move(callback)](NG::RectF& floatContainerModal,
                                                               NG::RectF& floatButtons) {
        Rosen::Rect containerModal = ConvertToRSRect(floatContainerModal);
        Rosen::Rect buttons = ConvertToRSRect(floatButtons);
        cb(containerModal, buttons);
    };
    pipeline->SubscribeContainerModalButtonsRectChange(std::move(wrapFunc));
}

void UIContentImpl::UpdateTransform(const OHOS::Rosen::Transform& transform)
{
    LOGI("UIContentImpl: UpdateTransform, window scale is %{public}f", transform.scaleX_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowScale = transform.scaleX_;
    taskExecutor->PostTask(
        [container, windowScale]() { container->SetWindowScale(windowScale); }, TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace
