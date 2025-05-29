/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
#include "bundlemgr/bundle_mgr_proxy.h"
#include "configuration.h"
#include "event_pass_through_subscriber.h"
#include "if_system_ability_manager.h"
#include "ipc_skeleton.h"
#include "iservice_registry.h"
#include "js_runtime_utils.h"
#include "locale_config.h"
#include "native_reference.h"
#include "ohos/init_data.h"
#ifdef RESOURCE_SCHEDULE_SERVICE_ENABLE
#include "res_sched_client.h"
#include "res_type.h"
#include "resource_manager.h"
#endif // RESOURCE_SCHEDULE_SERVICE_ENABLE
#include "service_extension_context.h"
#include "system_ability_definition.h"
#include "wm_common.h"

#include "base/log/event_report.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/utils.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline/container_window_manager.h"

#if !defined(ACE_UNITTEST)
#include "core/components_ng/base/transparent_node_detector.h"
#endif

#include "core/components_ng/property/safe_area_insets.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "adapter/ohos/entrance/rs_adapter.h"
#include "render_service_client/core/transaction/rs_transaction.h"
#include "render_service_client/core/transaction/rs_sync_transaction_controller.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/cj_utils/cj_utils.h"
#include "adapter/ohos/entrance/dialog_container.h"
#include "adapter/ohos/entrance/dynamic_component/uv_task_wrapper_impl.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "adapter/ohos/entrance/form_utils_impl.h"
#include "adapter/ohos/entrance/global_pipeline_context_manager.h"
#include "adapter/ohos/entrance/aps_monitor_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/ui_event_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "adapter/ohos/osal/navigation_route_ohos.h"
#include "adapter/ohos/osal/page_url_checker_ohos.h"
#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "adapter/ohos/osal/resource_adapter_impl_v2.h"
#include "adapter/ohos/osal/thp_extra_manager_impl.h"
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
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/xcollie/xcollieInterface.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_container_handler.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
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

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "screen_session_manager_client.h"
#include "pointer_event.h"

namespace OHOS::Ace {
namespace {

const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
const std::string START_PARAMS_KEY = "__startParams";
const std::string PARAM_QUERY_KEY = "query";
const std::string ACTION_SEARCH = "ohos.want.action.search";
const std::string ACTION_VIEWDATA = "ohos.want.action.viewData";
const std::string USE_GLOBAL_UICONTENT = "ohos.uec.params.useGlobalUIContent";
constexpr char IS_PREFERRED_LANGUAGE[] = "1";
constexpr uint64_t DISPLAY_ID_INVALID = -1ULL;
static std::atomic<bool> g_isDynamicVsync = false;
static bool g_isDragging = false;

#define UICONTENT_IMPL_HELPER(name) _##name = std::make_shared<UIContentImplHelper>(this)
#define UICONTENT_IMPL_PTR(name) _##name->uiContent_
#define UICONTENT_IMPL_HELPER_GUARD(name, ifInvalid...) \
    std::lock_guard lg(*_##name->mutex_);               \
    if (!*_##name->isValid_) {                          \
        ifInvalid;                                      \
    }

struct UIContentImplHelper {
    explicit UIContentImplHelper(UIContentImpl* uiContent) : uiContent_(uiContent)
    {
        uiContent_->AddDestructCallback(this, [mutex = mutex_, isValid = isValid_] {
            std::lock_guard lg(*mutex);
            *isValid = false;
        });
    }
    ~UIContentImplHelper()
    {
        std::lock_guard lg(*mutex_);
        if (*isValid_) {
            uiContent_->RemoveDestructCallback(this);
        }
    }
    UIContentImpl* uiContent_;
    std::shared_ptr<std::mutex> mutex_ = std::make_shared<std::mutex>();
    std::shared_ptr<bool> isValid_ = std::make_shared<bool>(true);
    UIContentImplHelper(const UIContentImplHelper& rhs) = delete;
    UIContentImplHelper& operator=(const UIContentImplHelper& rhs) = delete;
};

Rosen::Rect ConvertToRSRect(NG::RectF& rect)
{
    Rosen::Rect rsRect;
    rsRect.posX_ = floor(rect.GetX());
    rsRect.posY_ = floor(rect.GetY());
    rsRect.width_ = ceil(rect.Width());
    rsRect.height_ = ceil(rect.Height());
    return rsRect;
}

bool IsNeedAvoidWindowMode(OHOS::Rosen::Window* rsWindow)
{
    // compatibleModeInPc needAvoidWindow
    bool compatibleModeInPc = rsWindow->GetCompatibleModeInPc();
    if (!SystemProperties::GetNeedAvoidWindow() && !compatibleModeInPc) {
        return false;
    }

    auto mode = rsWindow->GetWindowMode();
    return mode == Rosen::WindowMode::WINDOW_MODE_FLOATING || mode == Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            mode == Rosen::WindowMode::WINDOW_MODE_SPLIT_SECONDARY;
}

void AddResConfigInfo(
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context, ResourceConfiguration& aceResCfg)
{
    if (!context || !context->GetResourceManager()) {
        return;
    }
    auto resourceManager = context->GetResourceManager();
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    resourceManager->GetResConfig(*resConfig);
    aceResCfg.SetMcc(resConfig->GetMcc());
    aceResCfg.SetMnc(resConfig->GetMnc());
    aceResCfg.SetAppHasDarkRes(resConfig->GetAppDarkRes());
    auto preferredLocaleInfo = resConfig->GetPreferredLocaleInfo();
    if (preferredLocaleInfo != nullptr) {
        std::string preferredLanguage = preferredLocaleInfo->getLanguage();
        std::string script = preferredLocaleInfo->getScript();
        std::string country = preferredLocaleInfo->getCountry();
        AceApplicationInfo::GetInstance().SetLocale(preferredLanguage.c_str(), country.c_str(), script.c_str(), "");

        std::string preferredLanguageTag = preferredLanguage;
        if (!script.empty()) {
            preferredLanguageTag += "-" + script;
        }
        if (!country.empty()) {
            preferredLanguageTag += "-" + country;
        }
        aceResCfg.SetPreferredLanguage(preferredLanguageTag);
    }
}

void AddSetAppColorModeToResConfig(
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context, ResourceConfiguration& aceResCfg)
{
    CHECK_NULL_VOID(context);
    auto config = context->GetConfiguration();
    CHECK_NULL_VOID(config);
    auto colorModeIsSetByApp = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::COLORMODE_IS_SET_BY_APP);
    if (!colorModeIsSetByApp.empty()) {
        aceResCfg.SetColorModeIsSetByApp(true);
    }
}

std::string StringifyAvoidAreas(const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    std::stringstream ss;
    if (avoidAreas.empty()) {
        return ss.str();
    }
    ss << "updateAvoidAreas size: " << avoidAreas.size() << "[";
    std::for_each(avoidAreas.begin(), avoidAreas.end(), [&ss](const auto& avoidArea) {
        ss << "(" << static_cast<int32_t>(avoidArea.first) << "," << avoidArea.second.ToString() << ")";
    });
    ss << "]";
    return ss.str();
}

bool CloseGlobalModalUIExtension(int32_t instanceId, int32_t sessionId, const std::string& name)
{
    auto globalPipelineManager = GlobalPipelineContextManager::GetInstance();
    auto uecName = name.empty() ? globalPipelineManager->GetUecNameBySessionId(sessionId) : name;
    if (uecName.empty()) {
        return false;
    }

    auto globalPipeline = globalPipelineManager->RemoveGlobalPipelineContext(uecName);
    auto modalPageNode = globalPipelineManager->RemoveModalPageNode(uecName);
    globalPipelineManager->RemoveSessionId(uecName);
    CHECK_NULL_RETURN(globalPipeline, false);
    CHECK_NULL_RETURN(modalPageNode, false);
    auto parentNode = modalPageNode->GetParent();
    if (parentNode) {
        parentNode->RemoveChild(modalPageNode);
        parentNode->RebuildRenderContextTree();
    }
    modalPageNode->MountToParent(globalPipeline->GetRootElement());
    auto globalOverlay = globalPipeline->GetOverlayManager();
    CHECK_NULL_RETURN(globalOverlay, false);
    globalOverlay->CloseModalUIExtension(sessionId);
    globalPipeline->Destroy();
    globalPipeline.Reset();
    return true;
}

bool UpdateModalUIExtensionCallback(std::string uecName, const ModalUIExtensionCallbacks& callbacks)
{
    auto modalPageNode = GlobalPipelineContextManager::GetInstance()->GetModalPageNode(uecName);
    CHECK_NULL_RETURN(modalPageNode, false);
    auto uiExtNode = AceType::DynamicCast<NG::FrameNode>(modalPageNode->GetFirstChild());
    if (!uiExtNode || uiExtNode->GetTag() != V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "GlobalPipelineContext record error ModalUIExtension");
        return false;
    }
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetOnReleaseCallback(std::move(callbacks.onRelease));
    pattern->SetOnErrorCallback(std::move(callbacks.onError));
    pattern->SetModalOnDestroy(std::move(callbacks.onDestroy));
    return true;
}

bool CreateGlobalModalUIExtension(const AAFwk::Want& want, int32_t &sessionId,
    const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config,
    int32_t instanceId, OHOS::Rosen::Window* window)
{
    const std::string uecName = want.GetElement().GetBundleName() + "." + want.GetElement().GetModuleName() +
        "." + want.GetElement().GetAbilityName();
    auto globalPipelineManager = GlobalPipelineContextManager::GetInstance();
    auto globalPipelineContext =
        globalPipelineManager->GetGlobalPipelineContext(uecName);
    if (!globalPipelineContext) {
        globalPipelineContext = globalPipelineManager->CreateGlobalPipelineContext(
            uecName, window, FrontendType::DECLARATIVE_JS, instanceId);
        globalPipelineContext->SetupRootElement();

        auto overlay = globalPipelineContext->GetOverlayManager();
        CHECK_NULL_RETURN(overlay, false);
        sessionId =
            overlay->CreateModalUIExtension(want, callbacks, config); // ModalPage -> UIExtensionComponent
        globalPipelineManager->RegisterSessionId(uecName, sessionId);
        globalPipelineManager->ProcessModalPageNode(uecName, instanceId);
    } else {
        if (!UpdateModalUIExtensionCallback(uecName, callbacks)) {
            CloseGlobalModalUIExtension(instanceId, 0, uecName);
            TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "GlobalPipelineContext with the name %{public}s reuse error", uecName.c_str());
            return false;
        }
        sessionId = globalPipelineManager->GetSessionId(uecName);
        globalPipelineManager->ProcessModalPageNode(uecName, instanceId);
    }
    return true;
}
} // namespace

const std::string SUBWINDOW_PREFIX = "ARK_APP_SUBWINDOW_";
const std::string SUBWINDOW_TOAST_DIALOG_PREFIX = "ARK_APP_SUBWINDOW_TOAST_DIALOG_";
const std::string SUBWINDOW_TOAST_PREFIX = "ARK_APP_SUBWINDOW_TOAST";
const int32_t REQUEST_CODE = -1;
constexpr uint32_t TIMEOUT_LIMIT = 5;
constexpr int32_t COUNT_LIMIT = 3;

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
        LOGI("StatusBarBgColorChanged: %{public}u", color);
    }

private:
    ContentFinishCallback onFinish_;
    ContentStartAbilityCallback onStartAbility_;
};

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateUIContent(void* context, void* runtime)
{
    LOGI("CreateUIContent.");
    Recorder::Init();
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateFormContent(void* context, void* runtime, bool isCard)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "CreateFormUIContent.");
    Recorder::Init();
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime, isCard);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateSubWindowUIContent(void* ability)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Create SubWindowUIContent.");
    Recorder::Init();
    return new UIContentImpl(reinterpret_cast<OHOS::AppExecFwk::Ability*>(ability));
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_GetUIContent(int32_t instanceId)
{
    LOGI("GetUIContent: %{public}d", instanceId);
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
    return tmp.data();
}

void AddAlarmLogFunc()
{
    std::function<void(uint64_t, int, int)> logFunc = [](uint64_t nodeId, int count, int num) {
        auto rsNode = Rosen::RSNodeMap::Instance().GetNode<Rosen::RSNode>(nodeId);
        if (rsNode == nullptr) {
            LOGI("rsNodeId:%{public}" PRId64 "not found, sendCommands:%{public}d, totalNumber:%{public}d",
                nodeId, count, num);
            return;
        }
        auto frameNodeId = rsNode->GetFrameNodeId();
        auto frameNodeTag = rsNode->GetFrameNodeTag();
        auto frameNode = NG::FrameNode::GetFrameNode(frameNodeTag, frameNodeId);
        if (frameNode == nullptr) {
            LOGI("frameNodeId:%{public}d not found, rsNodeId:%{public}" PRId64 " sendCommands:%{public}d, "
                 "totalRsNodeNumber:%{public}d.",
                frameNodeId, nodeId, count, num);
            return;
        }
        LOGI("frameNodeId:%{public}d found, rsNodeId:%{public}" PRId64 " sendCommands:%{public}d, "
             "FrameNodeTag:%{public}s, totalRsNodeNumber:%{public}d",
            frameNodeId, nodeId, count, frameNodeTag.c_str(), num);
    };

    OHOS::Rosen::RSTransactionData::AddAlarmLog(logFunc);
}

bool ParseAvoidAreasUpdate(const RefPtr<NG::PipelineContext>& context,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
    const ViewportConfig& config)
{
    CHECK_NULL_RETURN(context, false);
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    bool safeAreaUpdated = false;
    for (auto& avoidArea : avoidAreas) {
        if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM) {
            safeAreaUpdated |= safeAreaManager->UpdateSystemSafeArea(ConvertAvoidArea(avoidArea.second));
        } else if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
            safeAreaUpdated |= safeAreaManager->UpdateNavSafeArea(ConvertAvoidArea(avoidArea.second));
        } else if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT) {
            safeAreaUpdated |= safeAreaManager->UpdateCutoutSafeArea(ConvertAvoidArea(avoidArea.second),
                NG::OptionalSize<uint32_t>(config.Width(), config.Height()));
        }
    }
    if (safeAreaUpdated) {
        context->SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_AVOID_AREA);
        return true;
    }
    return false;
}

void AvoidAreasUpdateOnUIExtension(const RefPtr<NG::PipelineContext>& context,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    if (avoidAreas.empty()) {
        return;
    }
    CHECK_NULL_VOID(context);
    // for ui extension component
    for (auto& avoidArea : avoidAreas) {
        context->UpdateOriginAvoidArea(avoidArea.second, static_cast<uint32_t>(avoidArea.first));
    }
}

void UpdateSafeArea(const RefPtr<PipelineBase>& pipelineContext,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
    const ViewportConfig& config,
    const RefPtr<Platform::AceContainer>& container)
{
    CHECK_NULL_VOID(container);
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    uint32_t keyboardHeight = safeAreaManager->GetKeyboardInset().Length();
    safeAreaManager->UpdateKeyboardSafeArea(keyboardHeight, config.Height());
    ParseAvoidAreasUpdate(context, avoidAreas, config);
    AvoidAreasUpdateOnUIExtension(context, avoidAreas);
}

class OccupiedAreaChangeListener : public OHOS::Rosen::IOccupiedAreaChangeListener {
public:
    explicit OccupiedAreaChangeListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~OccupiedAreaChangeListener() = default;

    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
    {
        auto rect = info->rect_;
        double positionY = info->textFieldPositionY_;
        double height = info->textFieldHeight_;
        Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        LOGI("OccupiedAreaChange rect:%{public}s type: %{public}d, positionY:%{public}f, height:%{public}f, "
             "instanceId_ %{public}d", keyboardRect.ToString().c_str(), info->type_, positionY, height, instanceId_);
        CHECK_NULL_VOID(info->type_ == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(context);
        if (pipeline) {
            ContainerScope scope(instanceId_);
            auto manager = pipeline->GetSafeAreaManager();
            CHECK_NULL_VOID(manager);
            manager->SetKeyboardInfo(keyboardRect.Height());
            auto uiExtMgr = pipeline->GetUIExtensionManager();
            if (uiExtMgr) {
                SetUIExtensionImeShow(keyboardRect);
            }
            if (uiExtMgr && uiExtMgr->NotifyOccupiedAreaChangeInfo(info)) {
                TAG_LOGI(AceLogTag::ACE_KEYBOARD, "uiExtension consumed");
                taskExecutor->PostTask([id = instanceId_] {
                        ContainerScope scope(id);
                        auto container = Platform::AceContainer::GetContainer(id);
                        CHECK_NULL_VOID(container);
                        auto context = container->GetPipelineContext();
                        CHECK_NULL_VOID(context);
                        context->OnVirtualKeyboardAreaChange(Rect(), 0, 0);
                    }, TaskExecutor::TaskType::UI, "ArkUIVirtualKeyboardAreaChange");
                return;
            }
        }
        if (container->IsSceneBoardWindow()) {
            TAG_LOGD(AceLogTag::ACE_KEYBOARD, "SceneBoard window, no keyboard avoidance");
            return;
        }
        auto curWindow = context->GetCurrentWindowRect();
        positionY -= curWindow.Top();
        ContainerScope scope(instanceId_);
        if (LaterAvoid(keyboardRect, positionY, height)) {
            return;
        }
        taskExecutor->PostSyncTask([context, keyboardRect, rsTransaction, positionY, height] {
                CHECK_NULL_VOID(context);
                context->OnVirtualKeyboardAreaChange(keyboardRect, positionY, height, rsTransaction);
            }, TaskExecutor::TaskType::UI, "ArkUIVirtualKeyboardAreaChange");
    }

private:
    bool LaterAvoid(const Rect& keyboardRect, double positionY, double height)
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_RETURN(container, false);
        auto context = container->GetPipelineContext();
        CHECK_NULL_RETURN(context, false);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(context);
        CHECK_NULL_RETURN(pipeline, false);
        auto textFieldManager = AceType::DynamicCast<NG::TextFieldManagerNG>(pipeline->GetTextFieldManager());
        CHECK_NULL_RETURN(textFieldManager, false);
        auto windowManager = pipeline->GetWindowManager();
        CHECK_NULL_RETURN(windowManager, false);
        auto windowMode = windowManager->GetWindowMode();
        if (windowMode == WindowMode::WINDOW_MODE_FLOATING || windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
            textFieldManager->SetLaterAvoid(false);
            return false;
        }
        bool isRotate = false;
        auto displayInfo = container->GetDisplayInfo();
        if (displayInfo) {
            auto dmRotation = static_cast<int32_t>(displayInfo->GetRotation());
            isRotate = lastRotation != -1 && lastRotation != dmRotation;
            lastRotation = dmRotation;
        } else {
            lastRotation = -1;
        }
        auto triggerAvoidTaskOrientation = textFieldManager->GetContextTriggerAvoidTaskOrientation();
        textFieldManager->SetContextTriggerAvoidTaskOrientation(-1);
        if ((isRotate && lastRotation == triggerAvoidTaskOrientation) ||
            (textFieldManager->GetLaterAvoid() && NearEqual(0.0f, keyboardRect.Height()))) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "no need to later avoid, trigger avoid now");
            textFieldManager->SetLaterAvoid(false);
            return false;
        }
        auto laterRect = textFieldManager->GetLaterAvoidKeyboardRect();
        if (textFieldManager->GetLaterAvoid() && NearEqual(laterRect.Height(), keyboardRect.Height())) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "will trigger avoid later, ignore this notify");
            return true;
        }
        // do not avoid immediately when device is in rotation, trigger it after context trigger root rect update
        if (textFieldManager->GetLaterAvoid() || isRotate) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "rotation change to %{public}d, later avoid %{public}s %{public}f"
                "%{public}f", lastRotation, keyboardRect.ToString().c_str(), positionY, height);
            NG::LaterAvoidInfo laterAvoidInfo = {true, keyboardRect, positionY, height, lastRotation };
            textFieldManager->SetLaterAvoidArgs(laterAvoidInfo);
            return true;
        }
        return false;
    }

    void SetUIExtensionImeShow(const Rect& keyboardRect)
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        if (GreatNotEqual(keyboardRect.Height(), 0.0f)) {
            taskExecutor->PostTask(
                [id = instanceId_] {
                    ContainerScope scope(id);
                    auto pipeline = NG::PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->SetUIExtensionImeShow(true);
                }, TaskExecutor::TaskType::UI, "ArkUISetUIExtensionImeShow");
        } else {
            taskExecutor->PostTask(
                [id = instanceId_] {
                    ContainerScope scope(id);
                    auto pipeline = NG::PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->SetUIExtensionImeShow(false);
                }, TaskExecutor::TaskType::UI, "ArkUISetUIExtensionImeHide");
        }
    }
    int32_t instanceId_ = -1;
    int32_t lastRotation = -1;
};

class AvoidAreaChangedListener : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit AvoidAreaChangedListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~AvoidAreaChangedListener() = default;

    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type,
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info) override
    {
        Rect keyboardRect = Rect(0, 0, 0, 0);
        double textFieldPositionY = 0.0f;
        double textFieldHeight = 0.0f;

        if (info) {
            auto rect = info->rect_;
            keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
            textFieldPositionY = info->textFieldPositionY_;
            textFieldHeight = info->textFieldHeight_;
            ACE_SCOPED_TRACE("OnAvoidAreaChanged type: %d, value: %s; keyboardRect: %s, textFieldPositionY %f, "
                "textFieldHeight %f; instanceId: %d", type, avoidArea.ToString().c_str(),
                keyboardRect.ToString().c_str(), textFieldPositionY, textFieldHeight, instanceId_);
            TAG_LOGI(ACE_LAYOUT, "OnAvoidAreaChanged type: %{public}d, value: %{public}s; keyboardRect: %{public}s, "
                "textFieldPositionY: %{public}f, textFieldHeight: %{public}f; instanceId: %{public}d",
                type, avoidArea.ToString().c_str(), keyboardRect.ToString().c_str(), textFieldPositionY,
                textFieldHeight, instanceId_);
        } else {
            ACE_SCOPED_TRACE("OnAvoidAreaChanged type: %d, value: %s, instanceId: %d, "
            "keyboardInfo is null", type, avoidArea.ToString().c_str(), instanceId_);
            TAG_LOGI(ACE_LAYOUT, "OnAvoidAreaChanged type: %{public}d, value: %{public}s; instanceId: %{public}d, "
            "keyboardInfo is null", type, avoidArea.ToString().c_str(), instanceId_);
        }
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
        } else if (type == Rosen::AvoidAreaType::TYPE_CUTOUT) {
            cutoutSafeArea_ = ConvertAvoidArea(avoidArea);
        }
        auto safeArea = systemSafeArea_;
        auto navSafeArea = navigationBar_;
        auto cutoutSafeArea = cutoutSafeArea_;
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [pipeline, safeArea, navSafeArea, cutoutSafeArea, type, avoidArea] {
                if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
                    pipeline->UpdateSystemSafeArea(safeArea, true);
                } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
                    pipeline->UpdateNavSafeArea(navSafeArea, true);
                } else if (type == Rosen::AvoidAreaType::TYPE_CUTOUT) {
                    pipeline->UpdateCutoutSafeArea(cutoutSafeArea, true);
                }
                // for ui extension component
                pipeline->UpdateOriginAvoidArea(avoidArea, static_cast<uint32_t>(type));
            },
            TaskExecutor::TaskType::UI, "ArkUIUpdateOriginAvoidArea");

        CHECK_NULL_VOID(info);
        CHECK_NULL_VOID(info->type_ == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT);
        auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
        if (pipelineContext) {
            ContainerScope scope(instanceId_);
            auto manager = pipelineContext->GetSafeAreaManager();
            CHECK_NULL_VOID(manager);
            manager->SetKeyboardInfo(keyboardRect.Height());
            auto uiExtensionManager = pipelineContext->GetUIExtensionManager();
            CHECK_NULL_VOID(uiExtensionManager);
            SetUIExtensionImeShow(keyboardRect);
            if (uiExtensionManager->NotifyOccupiedAreaChangeInfo(info)) {
                TAG_LOGI(AceLogTag::ACE_KEYBOARD, "uiExtension consumed");
                taskExecutor->PostTask([id = instanceId_] {
                        ContainerScope scope(id);
                        auto container = Platform::AceContainer::GetContainer(id);
                        CHECK_NULL_VOID(container);
                        auto context = container->GetPipelineContext();
                        CHECK_NULL_VOID(context);
                        context->OnVirtualKeyboardAreaChange(Rect(), 0, 0);
                    }, TaskExecutor::TaskType::UI, "ArkUIVirtualKeyboardAreaChange");
                return;
            }
        }
    }

private:
    void SetUIExtensionImeShow(const Rect& keyboardRect)
    {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        if (GreatNotEqual(keyboardRect.Height(), 0.0f)) {
            taskExecutor->PostTask(
                [id = instanceId_] {
                    ContainerScope scope(id);
                    auto pipeline = NG::PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->SetUIExtensionImeShow(true);
                }, TaskExecutor::TaskType::UI, "ArkUISetUIExtensionImeShow");
        } else {
            taskExecutor->PostTask(
                [id = instanceId_] {
                    ContainerScope scope(id);
                    auto pipeline = NG::PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->SetUIExtensionImeShow(false);
                }, TaskExecutor::TaskType::UI, "ArkUISetUIExtensionImeHide");
        }
    }
    NG::SafeAreaInsets systemSafeArea_;
    NG::SafeAreaInsets navigationBar_;
    NG::SafeAreaInsets cutoutSafeArea_;
    int32_t instanceId_ = -1;
};

class PretendChangedListener : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit PretendChangedListener(int32_t instanceId) {}
    ~PretendChangedListener() = default;

    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type,
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info) override {}
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
            [pipeline, displayAvailableRect] {
                pipeline->UpdateDisplayAvailableRect(displayAvailableRect);
                TAG_LOGI(AceLogTag::ACE_WINDOW, "UpdateDisplayAvailableRect : %{public}s",
                    displayAvailableRect.ToString().c_str());
            },
            TaskExecutor::TaskType::UI, "ArkUIUpdateDisplayAvailableRect");
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
        auto aceView =
            AceType::DynamicCast<Platform::AceViewOhos>(Platform::AceContainer::GetContainer(instanceId)->GetAceView());
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
        CHECK_NULL_VOID(static_cast<int>(action));
    }

private:
    int32_t instanceId_ = -1;
};

class WaterfallModeChangeListener : public OHOS::Rosen::IWaterfallModeChangeListener {
public:
    explicit WaterfallModeChangeListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~WaterfallModeChangeListener() = default;

    void OnWaterfallModeChange(bool enable) override
    {
        TAG_LOGI(AceLogTag::ACE_WINDOW, "waterfall mode is changed, waterfallMode: %{public}d", enable);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [instanceId = instanceId_, enable] {
                SubwindowManager::GetInstance()->OnWaterfallModeChanged(instanceId, enable);
            },
            TaskExecutor::TaskType::UI, "ArkUIWaterfallModeChanged");
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
        TAG_LOGI(AceLogTag::ACE_WINDOW, "fold status is changed, foldStatus: %{public}d", foldStatus);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        container->SetFoldStatusFromListener(static_cast<FoldStatus>(static_cast<uint32_t>(foldStatus)));
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [instanceId = instanceId_, container, foldStatus] {
                auto context = container->GetPipelineContext();
                CHECK_NULL_VOID(context);
                auto aceFoldStatus = static_cast<FoldStatus>(static_cast<uint32_t>(foldStatus));
                context->OnFoldStatusChanged(aceFoldStatus);
                if (SystemProperties::IsSuperFoldDisplayDevice()) {
                    SubwindowManager::GetInstance()->ClearAllMenuPopup(instanceId);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFoldStatusChanged");
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
        TAG_LOGI(AceLogTag::ACE_WINDOW, "display mode is changed, displayMode: %{public}d", displayMode);
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
                TaskExecutor::TaskType::UI, "ArkUIFoldDisplayModeChanged");
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
            TaskExecutor::TaskType::UI, "ArkUIDialogFoldDisplayModeChanged");
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
        TAG_LOGI(AceLogTag::ACE_MENU, "window is touching outside. instance id is %{public}d", instanceId_);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [instanceId = instanceId_, targetId = targetId_] {
                SubwindowManager::GetInstance()->ClearMenu();
                SubwindowManager::GetInstance()->ClearMenuNG(instanceId, targetId, true, true);
                SubwindowManager::GetInstance()->ClearPopupInSubwindow(instanceId, false);
            },
            TaskExecutor::TaskType::UI, "ArkUITouchOutsideSubwindowClear");
    }

private:
    int32_t instanceId_ = -1;
    int32_t targetId_ = -1;
};

class WindowRectChangeListener : public OHOS::Rosen::IWindowRectChangeListener {
public:
    explicit WindowRectChangeListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~WindowRectChangeListener() = default;

    void OnRectChange(OHOS::Rosen::Rect rect, OHOS::Rosen::WindowSizeChangeReason reason)
    {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "window size is changed. current rect width: %{public}u, "
            "height: %{public}u, left: %{public}d, top: %{public}d, instance id is %{public}d, reason: %{public}d",
            rect.width_, rect.height_, rect.posX_, rect.posY_, instanceId_, reason);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        bool isWindowSizeChanged = !isRectEquel(rect);
        lastRect_ = rect;
        taskExecutor->PostTask(
            [instanceId = instanceId_, isWindowSizeChanged] {
                CHECK_EQUAL_VOID(isWindowSizeChanged, false);
                ContainerScope scope(instanceId);
                auto container = Platform::AceContainer::GetContainer(instanceId);
                CHECK_NULL_VOID(container);
                auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
                CHECK_NULL_VOID(pipeline);
                auto overlay = pipeline->GetOverlayManager();
                CHECK_NULL_VOID(overlay);
                overlay->HideAllMenusWithoutAnimation(false);
                overlay->HideAllPopupsWithoutAnimation();
                SubwindowManager::GetInstance()->ClearAllMenuPopup(instanceId);
            },
            TaskExecutor::TaskType::UI, "ArkUIWindowRectChange");
    }

private:
    bool isRectEquel(OHOS::Rosen::Rect curRect) const
    {
        return curRect.width_ == lastRect_.width_ && curRect.height_ == lastRect_.height_ &&
            curRect.posX_ == lastRect_.posX_ && curRect.posY_ == lastRect_.posY_;
    }
    int32_t instanceId_ = -1;
    OHOS::Rosen::Rect lastRect_;
};

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime) : runtime_(runtime)
{
    MultiThreadBuildManager::InitOnUIThread();
    CHECK_NULL_VOID(context);
    context_ = context->weak_from_this();
    bundleName_ = context->GetBundleName();
    auto hapModuleInfo = context->GetHapModuleInfo();
    CHECK_NULL_VOID(hapModuleInfo);
    moduleName_ = hapModuleInfo->name;
    StoreConfiguration(context->GetConfiguration());
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard)
    : runtime_(runtime), isFormRender_(isCard)
{
    MultiThreadBuildManager::InitOnUIThread();
    CHECK_NULL_VOID(context);
    bundleName_ = context->GetBundleName();
    if (CJUtils::IsCJFrontendContext(context)) {
        LOGD("UIContentImpl cj");
        context_ = context->weak_from_this();
        SetConfiguration(context->GetConfiguration());
    } else {
        auto hapModuleInfo = context->GetHapModuleInfo();
        CHECK_NULL_VOID(hapModuleInfo);
        moduleName_ = hapModuleInfo->name;
        hapPath_ = hapModuleInfo->hapPath;
        isBundle_ = (hapModuleInfo->compileMode == AppExecFwk::CompileMode::JS_BUNDLE);
        SetConfiguration(context->GetConfiguration());
        context_ = context->weak_from_this();
    }
}

UIContentImpl::UIContentImpl(OHOS::AppExecFwk::Ability* ability)
{
    MultiThreadBuildManager::InitOnUIThread();
    CHECK_NULL_VOID(ability);
    context_ = ability->GetAbilityContext();
    auto context = context_.lock();
    CHECK_NULL_VOID(context);
    StoreConfiguration(context->GetConfiguration());
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
    LOGI("[%{public}s][%{public}s][%{public}d]: Destroying old rsUIDirectory", bundleName_.c_str(), moduleName_.c_str(),
        instanceId_);
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
        bool isSceneBoardWindow = window->GetType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD;
        if (isSceneBoardWindow) {
            avoidAreaChangedListener_ = new AvoidAreaChangedListener(instanceId_);
            window->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
        }
    }

    // ArkTSCard need no window : 梳理所有需要window和不需要window的场景
    if (isFormRender_ && !window) {
        LOGI("[%{public}s][%{public}s][%{public}d]: CommonInitializeForm url: %{public}s", bundleName_.c_str(),
            moduleName_.c_str(), instanceId_, contentInfo.c_str());
        errorCode = CommonInitializeForm(window, contentInfo, storage);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }
    if (!intentInfoSerialized_.empty()) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        if (container) {
            TAG_LOGI(AceLogTag::ACE_ROUTER, "intentInfo exist, will distribute intentInfo");
            ContainerScope scope(instanceId_);
            container->DistributeIntentInfo(intentInfoSerialized_, true, std::move(loadPageCallback_));
            intentInfoSerialized_ = "";
            loadPageCallback_ = nullptr;
        }
    }
    LOGI("[%{public}s][%{public}s][%{public}d]: Initialize: %{public}s", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, startUrl_.c_str());
    // run page.
    errorCode = Platform::AceContainer::RunPage(instanceId_, startUrl_, "", isNamedRouter);
    CHECK_ERROR_CODE_RETURN(errorCode);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetUIExtensionSubWindow(isUIExtensionSubWindow_);
    Platform::AceContainer::GetContainer(instanceId_)->SetUIExtensionAbilityProcess(isUIExtensionAbilityProcess_);
    Platform::AceContainer::GetContainer(instanceId_)->SetUIExtensionAbilityHost(isUIExtensionAbilityHost_);
    SubscribeEventsPassThroughMode();
#if !defined(ACE_UNITTEST)
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, errorCode);
    auto rootNode = pipelineContext->GetRootElement();
    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(rootNode, startUrl_);
#endif
    return errorCode;
}

void UIContentImpl::SubscribeEventsPassThroughMode()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [instanceId = instanceId_]() {
            EventPassThroughSubscribeProxy::GetInstance()->SubscribeEvent(instanceId);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIRegisterEventsPassThroughAsync");
}

void UIContentImpl::UnSubscribeEventsPassThroughMode()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [instanceId = instanceId_]() {
            EventPassThroughSubscribeProxy::GetInstance()->UnSubscribeEvent(instanceId);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIUnSubscribeEventsPassThroughAsync");
}

void UIContentImpl::PreInitializeForm(OHOS::Rosen::Window* window, const std::string& url, napi_value storage)
{
    // ArkTSCard need no window
    if (isFormRender_ && !window) {
        LOGI("[%{public}s][%{public}s][%{public}d]: InitializeForm: %{public}s", bundleName_.c_str(),
            moduleName_.c_str(), instanceId_, url.c_str());
        CommonInitializeForm(window, url, storage);
        AddWatchSystemParameter();
    }
}

void UIContentImpl::RunFormPage()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: Initialize startUrl: %{public}s, \
        formData_.size:%{public}zu",
        bundleName_.c_str(), moduleName_.c_str(),
        instanceId_, startUrl_.c_str(),
        formData_.size());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, formData_, false);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SetDistributedUI(distributedUI);
}

UIContentErrorCode UIContentImpl::Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage)
{
    auto errorCode = InitializeInner(window, url, storage, false);
    AddWatchSystemParameter();
    UpdateWindowBlur();
    RegisterLinkJumpCallback();
    return errorCode;
}

UIContentErrorCode UIContentImpl::Initialize(OHOS::Rosen::Window* window,
    const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage)
    {
        std::string contentName = "";
        return Initialize(window, content, storage, contentName);
    }

UIContentErrorCode UIContentImpl::Initialize(OHOS::Rosen::Window* window,
    const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage, const std::string& contentName)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    errorCode = CommonInitialize(window, "", storage);
    CHECK_ERROR_CODE_RETURN(errorCode);
    AddWatchSystemParameter();
    if (content) {
        LOGI("Initialize by buffer, size:%{public}zu", content->size());
        // run page.
        errorCode = Platform::AceContainer::RunPage(instanceId_, content, contentName);
        CHECK_ERROR_CODE_RETURN(errorCode);
    } else {
        LOGE("Initialize failed, buffer is null");
    }
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetUIExtensionSubWindow(isUIExtensionSubWindow_);
    Platform::AceContainer::GetContainer(instanceId_)->SetUIExtensionAbilityProcess(isUIExtensionAbilityProcess_);
    Platform::AceContainer::GetContainer(instanceId_)->SetUIExtensionAbilityHost(isUIExtensionAbilityHost_);
    return errorCode;
}

UIContentErrorCode UIContentImpl::InitializeByName(
    OHOS::Rosen::Window* window, const std::string& name, napi_value storage)
{
    auto errorCode = InitializeInner(window, name, storage, true);
    AddWatchSystemParameter();
    RegisterLinkJumpCallback();
    UpdateWindowBlur();
    return errorCode;
}

void UIContentImpl::InitializeDynamic(const DynamicInitialConfig& config)
{
    isDynamicRender_ = true;
    hapPath_ = config.hapPath;
    hostInstanceId_ = config.hostInstanceId;
    registerComponents_ = config.registerComponents;
    auto env = reinterpret_cast<napi_env>(runtime_);
    auto entryPoint = config.entryPoint;
    hostWindowInfo_ = config.hostWindowInfo;
    CHECK_NULL_VOID(env);
    taskWrapper_ = std::make_shared<NG::UVTaskWrapperImpl>(env);

    CommonInitializeForm(nullptr, config.abcPath, nullptr);
    AddWatchSystemParameter();

    LOGI("[%{public}s][%{public}s][%{public}d]: InitializeDynamic, startUrl"
         ": %{public}s, entryPoint: %{public}s",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, startUrl_.c_str(), entryPoint.c_str());
    Platform::AceContainer::RunDynamicPage(instanceId_, startUrl_, "", entryPoint);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    container->SetDistributedUI(distributedUI);
    ContainerScope scope(instanceId_);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_VOID(stageNode);
    auto renderContext = stageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateWindowBlur();
}

void UIContentImpl::Initialize(
    OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowId)
{
    if (window == nullptr) {
        LOGE("UIExtensionAbility [%{public}s][%{public}s][%{public}d][%{public}s] initialize ui instance failed, the"
             "window is invalid",
            bundleName_.c_str(), moduleName_.c_str(), instanceId_, startUrl_.c_str());
        return;
    }
    auto errorCode = CommonInitialize(window, url, storage, focusWindowId);
    if (errorCode != UIContentErrorCode::NO_ERRORS) {
        return;
    }
    AddWatchSystemParameter();
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SetDrawReadyEventCallback();
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "[%{public}s][%{public}s][%{public}d]: StartUIExtension: %{public}s",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
#if !defined(ACE_UNITTEST)
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(rootNode, startUrl_);
#endif
}

void UIContentImpl::InitializeByName(OHOS::Rosen::Window *window,
    const std::string &name, napi_value storage, uint32_t focusWindowId)
{
    if (window == nullptr) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExtensionAbility [%{public}s][%{public}s][%{public}d][%{public}s]"
            "InitializeByName failed, the window is invalid",
            bundleName_.c_str(), moduleName_.c_str(), instanceId_, startUrl_.c_str());
        return;
    }

    auto errorCode = CommonInitialize(window, name, storage, focusWindowId);
    if (errorCode != UIContentErrorCode::NO_ERRORS) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "CommonInitialize failed when InitializeByName");
        return;
    }

    AddWatchSystemParameter();
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "[%{public}s][%{public}s][%{public}d]: StartUIExtensionByName: %{public}s",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "", true);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SetDistributedUI(distributedUI);
#if !defined(ACE_UNITTEST)
    auto pipelineContext = NG::PipelineContext::GetContextByContainerId(instanceId_);
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(rootNode, startUrl_);
#endif
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
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, ContentInfoType type)
{
    LOGI("Restore with contentInfo size: %{public}d, ContentInfotype: %{public}d",
        static_cast<int32_t>(contentInfo.size()), static_cast<int32_t>(type));
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    errorCode = CommonInitialize(window, contentInfo, storage);
    CHECK_ERROR_CODE_RETURN(errorCode);
    RouterRecoverRecord record;
    std::tie(record, errorCode) = Platform::AceContainer::RestoreRouterStack(instanceId_, contentInfo, type);
    startUrl_ = record.url;
    CHECK_ERROR_CODE_RETURN(errorCode);
    if (startUrl_.empty()) {
        LOGW("Restore start url is empty");
    }
    LOGI("[%{public}s][%{public}s][%{public}d]: Restore startUrl: %{public}s, isNamedRouter: %{public}s",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, startUrl_.c_str(),
        (record.isNamedRouter ? "yes" : "no"));
    return Platform::AceContainer::RunPage(instanceId_, startUrl_, record.params, record.isNamedRouter);
}

std::string UIContentImpl::GetContentInfo(ContentInfoType type) const
{
    LOGI("[%{public}s][%{public}s][%{public}d]: GetContentInfoType: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, type);
    return Platform::AceContainer::GetContentInfo(instanceId_, type);
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
    auto configuration = context->GetConfiguration();
    std::unordered_map<std::string, DeviceType> typeMap = { { "phone", DeviceType::PHONE }, { "tv", DeviceType::TV },
        { "watch", DeviceType::WATCH }, { "car", DeviceType::CAR }, { "tablet", DeviceType::TABLET },
        { "2in1", DeviceType::TWO_IN_ONE }, { "wearable", DeviceType::WEARABLE }, { "UNKNOWN", DeviceType::UNKNOWN } };
    if (configuration) {
        auto type = configuration->GetItem(OHOS::AAFwk::GlobalConfigurationKey::DEVICE_TYPE);
        if (typeMap.find(type) != typeMap.end()) {
            SystemProperties::SetDeviceType(typeMap[type]);
        }
    } else {
        LOGD("configuration is nullptr,use default type");
    }
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
        });
    }

    bool useNewPipe = true;
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        auto displayInfo = defaultDisplay->GetDisplayInfo();
        if (displayInfo) {
            density = displayInfo->GetDensityInCurResolution();
        }
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
        TAG_LOGI(AceLogTag::ACE_FORM,
            "[%{public}s][%{public}s][%{public}d]: CommonInitializeForm virtualPixelRatio: %{public}f, deviceWidth: "
            "%{public}d, deviceHeight: %{public}d",
            bundleName_.c_str(), moduleName_.c_str(), instanceId_, density, deviceWidth, deviceHeight);
    }

    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    ColorMode colorMode = ColorMode::LIGHT;
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
                colorMode = ColorMode::DARK;
                LOGI("Set dark mode");
            } else {
                colorMode = ColorMode::LIGHT;
                LOGI("Set light mode");
            }
            SystemProperties::SetDeviceAccess(
                resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
        } else {
            auto config = context->GetConfiguration();
            if (config) {
                auto configColorMode = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
                colorMode = configColorMode == "dark" ? ColorMode::DARK : ColorMode::LIGHT;
            }
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
    if (isDynamicRender_) {
        ContainerScope::UpdateLocalCurrent(instanceId_);
    }
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
                    LOGI("Start ability: %{private}s", address.c_str());
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
    container->SetUIContentType(uIContentType_);
    container->SetRegisterComponents(registerComponents_);
    container->SetIsFRSCardContainer(isFormRender_);
    container->SetColorMode(colorMode);
    if (window_) {
        container->SetWindowName(window_->GetWindowName());
        container->SetWindowId(window_->GetWindowId());
    }

    if (context) {
        auto token = context->GetToken();
        container->SetToken(token);
    }

    if (appInfo) {
        container->SetApiTargetVersion(appInfo->apiTargetVersion);
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
    aceResCfg.SetColorMode(container->GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    aceResCfg.SetLanguage(AceApplicationInfo::GetInstance().GetLocaleTag());
    AddResConfigInfo(context, aceResCfg);
    if (isDynamicRender_) {
        auto runtimeContext = Platform::AceContainer::GetRuntimeContext(hostInstanceId_);
        if (runtimeContext) {
            AddSetAppColorModeToResConfig(runtimeContext->shared_from_this(), aceResCfg);
        }
    } else {
        AddSetAppColorModeToResConfig(context, aceResCfg);
    }
    if (isDynamicRender_) {
        if (std::regex_match(hapPath_, std::regex(".*\\.hap"))) {
            hapPath = hapPath_;
        } else {
            resPath = hapPath_;
        }
    } else if (isFormRender_) {
        resPath = "/data/bundles/" + bundleName_ + "/" + moduleName_ + "/";
        hapPath = hapPath_;
    }
    TAG_LOGI(AceLogTag::ACE_FORM,
        "[%{public}s][%{public}s][%{public}d]: CommonInitializeForm resPath = %{public}s hapPath = %{public}s",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, resPath.c_str(), hapPath.c_str());
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
        if (!container->IsSceneBoardEnabled()) {
            occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
            window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
        }
    }

    // create ace_view
    RefPtr<Platform::AceViewOhos> aceView = nullptr;
    if (isFormRender_ && !isDynamicRender_) {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, true, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    } else {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    }

    if (isFormRender_) {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, round(formWidth_),
            round(formHeight_), window_);
        CHECK_ERROR_CODE_RETURN(errorCode);
        auto frontend = AceType::DynamicCast<FormFrontendDeclarative>(container->GetFrontend());
        CHECK_NULL_RETURN(frontend, UIContentErrorCode::NULL_POINTER);
        frontend->SetBundleName(bundleName_);
        frontend->SetModuleName(moduleName_);
        // arkTSCard only support "esModule" compile mode
        frontend->SetIsBundle(false);
        container->SetBundleName(bundleName_);
    } else {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }

    if (isDynamicRender_) {
        if (hostWindowInfo_.focusWindowId != 0) {
            container->SetFocusWindowId(hostWindowInfo_.focusWindowId);
        }

        if (hostWindowInfo_.realHostWindowId > 0) {
            container->SetRealHostWindowId(hostWindowInfo_.realHostWindowId);
        }
        LOGI("DynamicRender: focusWindowId: %{public}u, realHostWindowId: %{public}d",
            hostWindowInfo_.focusWindowId, hostWindowInfo_.realHostWindowId);
    }

    // after frontend initialize
    if (window_ && window_->IsFocused()) {
        Focus();
    }

    if (isFormRender_ && !isFormRenderInit_) {
        container->UpdateFormSharedImage(formImageDataMap_);
        container->UpdateFormData(formData_);
        isFormRenderInit_ = true;
        TAG_LOGI(AceLogTag::ACE_FORM, "isFormRenderInit_ true");
    }

    if (isFormRender_) {
        Platform::AceViewOhos::SurfaceChanged(aceView, round(formWidth_), round(formHeight_),
            deviceHeight >= deviceWidth ? 0 : 1);
        container->CheckAndSetFontFamily();
        SetFontScaleAndWeightScale(container, instanceId_);
        // Set sdk version in module json mode for form
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
            pipeline->SetApiTargetVersion(container->GetApiTargetVersion());
        }
    } else {
        Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    }
    // Set sdk version in module json mode
    if (isModelJson) {
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
            pipeline->SetApiTargetVersion(container->GetApiTargetVersion());
        }
    }
    if (runtime_ && !isFormRender_) { // ArkTSCard not support inherit local strorage from context
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context);
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(
                reinterpret_cast<NativeReference*>(ref), context);
        }
    }
    if (context) {
        UpdateFontScale(context->GetConfiguration());
    }
    return UIContentErrorCode::NO_ERRORS;
}

void UIContentImpl::UpdateFontScale(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (isFormRender_ && !fontScaleFollowSystem_) {
        TAG_LOGW(AceLogTag::ACE_FORM, "use form default size");
        return;
    }
    CHECK_NULL_VOID(config);
    auto maxAppFontScale = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::APP_FONT_MAX_SCALE);
    auto followSystem = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::APP_FONT_SIZE_SCALE);
    auto context = NG::PipelineContext::GetContextByContainerId(instanceId_);
    CHECK_NULL_VOID(context);
    auto isFollowSystem = followSystem == "followSystem";
    if (!followSystem.empty()) {
        context->SetFollowSystem(isFollowSystem);
    }
    if (!maxAppFontScale.empty()) {
        context->SetMaxAppFontScale(StringUtils::StringToFloat(maxAppFontScale));
    }
    if (!isFollowSystem) {
        context->SetFontScale(1.0f);
    }

    auto fontScale = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_FONT_SIZE_SCALE);
    if (!fontScale.empty()) {
        context->SetFontScale(StringUtils::StringToFloat(fontScale));
    }
}

void UIContentImpl::SetConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (config == nullptr) {
        UErrorCode status = U_ZERO_ERROR;
        icu::Locale locale = icu::Locale::forLanguageTag(Global::I18n::LocaleConfig::GetSystemLanguage(), status);
        AceApplicationInfo::GetInstance().SetLocale(locale.getLanguage(), locale.getCountry(), locale.getScript(), "");
        return;
    }

    auto deviceAccess = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
    auto languageTag = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);

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
    StoreConfiguration(config);
}

void UIContentImpl::StoreConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (!config) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_WINDOW, "StoreConfiguration %{public}s", config->GetName().c_str());
    auto colorMode = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!colorMode.empty() && container) {
        container->SetColorMode(colorMode == "dark" ? ColorMode::DARK : ColorMode::LIGHT);
    }

    auto string2float = [](const std::string& str) {
        return StringUtils::StringToFloat(str);
    };
    auto fontScale = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_FONT_SIZE_SCALE);
    if (!fontScale.empty()) {
        SystemProperties::SetFontScale(string2float(fontScale));
    }
    auto fontWeightScale = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_FONT_WEIGHT_SCALE);
    if (!fontWeightScale.empty()) {
        SystemProperties::SetFontWeightScale(string2float(fontWeightScale));
    }
    auto deviceType = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::DEVICE_TYPE);
    if (!deviceType.empty()) {
        SystemProperties::SetConfigDeviceType(deviceType);
    }
    auto smartGesture = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_SMART_GESTURE_SWITCH);
    if (!smartGesture.empty()) {
        SystemProperties::SetFocusCanBeActive(smartGesture ==
            OHOS::AppExecFwk::ConfigurationInner::SMART_GESTURE_AUTO);
    }
}

std::shared_ptr<Rosen::RSSurfaceNode> UIContentImpl::GetFormRootNode()
{
    return Platform::AceContainer::GetFormSurfaceNode(instanceId_);
}
// ArkTSCard end

void UIContentImpl::SetFontScaleAndWeightScale(const RefPtr<Platform::AceContainer>& container, int32_t instanceId)
{
    float fontScale = SystemProperties::GetFontScale();
    float fontWeightScale = SystemProperties::GetFontWeightScale();
    if (isFormRender_ && !fontScaleFollowSystem_) {
        TAG_LOGW(AceLogTag::ACE_FORM, "setFontScale form default size");
        fontScale = 1.0f;
        fontWeightScale = 1.0f;
    }
    container->SetFontScale(instanceId, fontScale);
    container->SetFontWeightScale(instanceId, fontWeightScale);
}

void UIContentImpl::SetAceApplicationInfo(std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
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
    XcollieInterface::GetInstance().SetTimerCount("HIT_EMPTY_WARNING", TIMEOUT_LIMIT, COUNT_LIMIT);

    auto task = [] {
        std::unordered_map<std::string, std::string> payload;
        std::unordered_map<std::string, std::string> reply;
        payload["bundleName"] = AceApplicationInfo::GetInstance().GetPackageName();
        payload["targetApiVersion"] = std::to_string(AceApplicationInfo::GetInstance().GetApiTargetVersion());
        g_isDynamicVsync = ResSchedReport::GetInstance().AppWhiteListCheck(payload, reply);
        ACE_SCOPED_TRACE_COMMERCIAL("SetVsyncPolicy(%d)", g_isDynamicVsync.load());
        OHOS::AppExecFwk::EventHandler::SetVsyncPolicy(g_isDynamicVsync);
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
}

void UIContentImpl::SetDeviceProperties()
{
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    float defaultDensity = 1.0f;
    int32_t devicePhysicalWidth = 0;
    int32_t devicePhysicalHeight = 0;

    bool isSceneBoardWindow = window_->GetType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD;
    if (isSceneBoardWindow) {
        auto screenProperties = Rosen::ScreenSessionManagerClient::GetInstance().GetAllScreensProperties();
        if (!screenProperties.empty()) {
            auto iter = screenProperties.begin();
            defaultDensity = iter->second.GetDefaultDensity();
        }
    }

    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDisplayById(window_->GetDisplayId());
    if (!defaultDisplay) {
        defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    }
    sptr<Rosen::DisplayInfo> displayInfo;
    if (defaultDisplay) {
        displayInfo = defaultDisplay->GetDisplayInfoWithCache();
    }
    if (displayInfo) {
        density = displayInfo->GetVirtualPixelRatio();
        if (isSceneBoardWindow && !NearEqual(defaultDensity, 1.0f)) {
            density = defaultDensity;
        }
        deviceWidth = displayInfo->GetWidth();
        deviceHeight = displayInfo->GetHeight();
        devicePhysicalWidth = displayInfo->GetPhysicalWidth();
        devicePhysicalHeight = displayInfo->GetPhysicalHeight();
    }
    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    SystemProperties::SetDevicePhysicalWidth(devicePhysicalWidth);
    SystemProperties::SetDevicePhysicalHeight(devicePhysicalHeight);
}

RefPtr<Platform::AceContainer> UIContentImpl::CreateContainer(
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo>& info, FrontendType frontendType, bool useNewPipe)
{
    auto container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, frontendType, context_, info,
        std::make_unique<ContentEventCallback>(
            [window = window_] {
                CHECK_NULL_VOID(window);
                TAG_LOGI(AceLogTag::ACE_ROUTER, "router back to window");
                window->PerformBack();
            },
            [context = context_](const std::string& address) {
                auto sharedContext = context.lock();
                CHECK_NULL_VOID(sharedContext);
                auto abilityContext =
                    OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                CHECK_NULL_VOID(abilityContext);
                LOGI("startAbility: %{private}s", address.c_str());
                AAFwk::Want want;
                want.AddEntity(Want::ENTITY_BROWSER);
                want.SetUri(address);
                want.SetAction(ACTION_VIEWDATA);
                abilityContext->StartAbility(want, REQUEST_CODE);
            }),
        false, false, useNewPipe);
    return container;
}

UIContentErrorCode UIContentImpl::CommonInitialize(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, uint32_t focusWindowId)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    window_ = window;
    CHECK_NULL_RETURN(window_, UIContentErrorCode::NULL_WINDOW);
    auto windowName = window->GetWindowName();
    ACE_SCOPED_TRACE_COMMERCIAL("UI Initialize:%s", windowName.c_str());
    startUrl_ = contentInfo;
    if (StringUtils::StartWith(windowName, SUBWINDOW_TOAST_DIALOG_PREFIX)) {
        InitializeSubWindow(window_, true);
        return errorCode;
    }
    if (StringUtils::StartWith(windowName, SUBWINDOW_PREFIX)) {
        InitializeSubWindow(window_);
        return errorCode;
    }
    auto context = context_.lock();
    CHECK_NULL_RETURN(context, UIContentErrorCode::NULL_POINTER);
    auto configuration = context->GetConfiguration();
    std::unordered_map<std::string, DeviceType> typeMap = { { "phone", DeviceType::PHONE }, { "tv", DeviceType::TV },
        { "watch", DeviceType::WATCH }, { "car", DeviceType::CAR }, { "tablet", DeviceType::TABLET },
        { "2in1", DeviceType::TWO_IN_ONE }, { "wearable", DeviceType::WEARABLE }, { "UNKNOWN", DeviceType::UNKNOWN } };
    if (configuration) {
        auto type = configuration->GetItem(OHOS::AAFwk::GlobalConfigurationKey::DEVICE_TYPE);
        if (typeMap.find(type) != typeMap.end()) {
            SystemProperties::SetDeviceType(typeMap[type]);
        }
    } else {
        LOGD("configuration is nullptr,use default type");
    }
    static std::once_flag onceFlag;
    std::call_once(onceFlag, std::bind(&UIContentImpl::SetAceApplicationInfo, this, std::ref(context)));
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

    bool reusedNodeSkipMeasure = std::any_of(metaData.begin(), metaData.end(), [](const auto& metaDataItem) {
        return metaDataItem.name == "reusedNodeSkipMeasure" && metaDataItem.value == "true";
    });
    if (reusedNodeSkipMeasure) {
        EventReport::ReportReusedNodeSkipMeasureApp();
    }
    AceApplicationInfo::GetInstance().SetReusedNodeSkipMeasure(reusedNodeSkipMeasure);
    auto useNewPipe =
        AceNewPipeJudgement::QueryAceNewPipeEnabledStage(AceApplicationInfo::GetInstance().GetPackageName(),
            apiCompatibleVersion, apiTargetVersion, apiReleaseType, closeArkTSPartialUpdate);
    AceApplicationInfo::GetInstance().SetIsUseNewPipeline(useNewPipe);
    LOGI("[%{public}s][%{public}s][%{public}d]: UIContent: apiCompatibleVersion: %{public}d, apiTargetVersion: "
         "%{public}d, and apiReleaseType: %{public}s, "
         "useNewPipe: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, apiCompatibleVersion, apiTargetVersion,
        apiReleaseType.c_str(), useNewPipe);
#ifndef NG_BUILD
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    if (SystemProperties::GetRosenBackendEnabled() && !useNewPipe) {
        RsAdapter::RsUIDirectorInit(rsUiDirector, window, context->GetCacheDir());
    }
#endif
#endif
    SetDeviceProperties();
    // Initialize performance check parameters
    AceChecker::InitPerformanceParameters();
    AcePerformanceCheck::Start();
    ColorMode colorMode = ColorMode::LIGHT;

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
        colorMode =
            resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK ? ColorMode::DARK : ColorMode::LIGHT;
        SystemProperties::SetDeviceAccess(
            resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
        LOGI("[%{public}s][%{public}s][%{public}d]: SetLanguage: %{public}s, colorMode: %{public}s, "
             "deviceAccess: %{public}d",
            bundleName_.c_str(), moduleName_.c_str(), instanceId_,
            AceApplicationInfo::GetInstance().GetLanguage().c_str(), colorMode == ColorMode::DARK ? "dark" : "light",
            SystemProperties::GetDeviceAccess());
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
    auto abilityName = info != nullptr ? info->name : "";
    std::string moduleHapPath = info != nullptr ? info->hapPath : "";
    std::string resPath;
    std::string pageProfile;
    LOGI("[%{public}s][%{public}s][%{public}d]: Initialize UIContent isModelJson:%{public}s", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, isModelJson ? "true" : "false");
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
    auto isCJFrontend = CJUtils::IsCJFrontendContext(context.get());
    if (runtime_ || isCJFrontend) {
        instanceId_ = Container::GenerateId<STAGE_CONTAINER>();
    } else {
        instanceId_ = Container::GenerateId<FA_SUBWINDOW_CONTAINER>();
    }
#ifdef FORM_SUPPORTED
    auto formUtils = std::make_shared<FormUtilsImpl>();
    FormManager::GetInstance().SetFormUtils(formUtils);
#endif
#ifdef APS_ENABLE
    auto apsMonitor = std::make_shared<ApsMonitorImpl>();
    PerfMonitor::GetPerfMonitor()->SetApsMonitor(apsMonitor);
#endif
    auto frontendType =  isCJFrontend? FrontendType::DECLARATIVE_CJ : FrontendType::DECLARATIVE_JS;
    auto container = CreateContainer(info, frontendType, useNewPipe);
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    container->SetUIContentType(uIContentType_);
    container->SetWindowName(window_->GetWindowName());
    container->SetWindowId(window_->GetWindowId());
    auto token = context->GetToken();
    container->SetToken(token);
    container->SetParentToken(parentToken_);
    container->SetColorMode(colorMode);
    if (!isCJFrontend) {
        container->SetPageUrlChecker(AceType::MakeRefPtr<PageUrlCheckerOhos>(context, info));
    }
    container->SetNavigationRoute(AceType::MakeRefPtr<NavigationRouteOhos>(context->GetBundleName()));
    // Mark the relationship between windowId and containerId, it is 1:1
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    ContainerScope::Add(instanceId_);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else if (isCJFrontend) {
        container->GetSettings().SetUsingSharedRuntime(true);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    container->SetPageProfile(pageProfile);
    container->Initialize();
     // wjh create and init container end
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
    aceResCfg.SetColorMode(container->GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    aceResCfg.SetLanguage(AceApplicationInfo::GetInstance().GetLocaleTag());
    AddResConfigInfo(context, aceResCfg);
    AddSetAppColorModeToResConfig(context, aceResCfg);
    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);
    container->SetHapPath(hapPath);
    container->SetAssetManager(assetManagerImpl);

    container->SetBundlePath(context->GetBundleCodeDir());
    container->SetFilesDataPath(context->GetFilesDir());
    container->SetBundleName(hapModuleInfo->bundleName);
    container->SetModuleName(hapModuleInfo->moduleName);
    container->SetIsModule(hapModuleInfo->compileMode == AppExecFwk::CompileMode::ES_MODULE);
    container->SetApiTargetVersion(apiTargetVersion);

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

    container->SetAbilityOnSearch([context = context_](const std::string& queryWord) {
        auto sharedContext = context.lock();
        CHECK_NULL_VOID(sharedContext);
        auto abilityContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
        CHECK_NULL_VOID(abilityContext);
        AAFwk::Want want;
        want.AddEntity(Want::ENTITY_BROWSER);
        want.SetAction(ACTION_SEARCH);
        want.SetParam(PARAM_QUERY_KEY, queryWord);
        abilityContext->StartAbility(want, REQUEST_CODE);
    });

    if (window_->IsDecorEnable()) {
        container->SetWindowModal(WindowModal::CONTAINER_MODAL);
    }
    container->InitFoldStatusFromListener();
       // wjh set container rest info end
    dragWindowListener_ = new DragWindowListener(instanceId_);
    window_->RegisterDragListener(dragWindowListener_);
    if (!container->IsSceneBoardEnabled()) {
        occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
        window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
    }
    waterfallModeChangeListener_ = new WaterfallModeChangeListener(instanceId_);
    window_->RegisterWaterfallModeChangeListener(waterfallModeChangeListener_);
    foldStatusListener_ = new FoldScreenListener(instanceId_);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterFoldStatusListener(foldStatusListener_);
    foldDisplayModeListener_ = new FoldDisplayModeListener(instanceId_);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterDisplayModeListener(foldDisplayModeListener_);
    if (window_->GetType() == Rosen::WindowType::WINDOW_TYPE_UI_EXTENSION) {
        windowRectChangeListener_ = new WindowRectChangeListener(instanceId_);
        window_->RegisterHostWindowRectChangeListener(windowRectChangeListener_);
    } else {
        windowRectChangeListener_ = new WindowRectChangeListener(instanceId_);
        window_->RegisterWindowRectChangeListener(windowRectChangeListener_);
    }

    // create ace_view
    auto aceView =
        Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
    Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    int32_t deviceWidth = SystemProperties::GetDeviceWidth();
    int32_t deviceHeight = SystemProperties::GetDeviceHeight();
    double density = SystemProperties::GetResolution();
#ifndef NG_BUILD
    if (!useNewPipe) {
        Ace::Platform::UIEnvCallback callback = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
        callback = [id = instanceId_, container, rsUiDirector](
                       const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) {
            if (rsUiDirector) {
                ACE_SCOPED_TRACE("OHOS::Rosen::RSUIDirector::Create()");
                if (!SystemProperties::GetMultiInstanceEnabled()) {
                    rsUiDirector->SetUITaskRunner(
                        [taskExecutor = container->GetTaskExecutor(), id](
                            const std::function<void()>& task, uint32_t delay) {
                            ContainerScope scope(id);
                            taskExecutor->PostDelayedTask(
                                task, TaskExecutor::TaskType::UI, delay, "ArkUIRenderServiceTask", PriorityType::HIGH);
                        }, id);
                } else {
                    rsUiDirector->SetUITaskRunner(
                        [taskExecutor = container->GetTaskExecutor(), id](
                            const std::function<void()>& task, uint32_t delay) {
                            ContainerScope scope(id);
                            taskExecutor->PostDelayedTask(
                                task, TaskExecutor::TaskType::UI, delay, "ArkUIRenderServiceTask", PriorityType::HIGH);
                        }, 0, true);
                }
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
    // set focus window id for ui extension after pipeline context created.
    if (focusWindowId != 0) {
        container->SetFocusWindowId(focusWindowId);
        auto uIExtensionContainerHandler = AceType::MakeRefPtr<NG::UIExtensionContainerHandler>();
        uIExtensionContainerHandler->SetHostParams(hostWindowInfo_.hostWantParams);
        container->RegisterContainerHandler(uIExtensionContainerHandler);
    }

    auto realHostWindowId = window_->GetRealParentId();
    if (realHostWindowId != 0) {
        container->SetRealHostWindowId(static_cast<uint32_t>(realHostWindowId));
    }
    LOGI("focusWindowId: %{public}u, realHostWindowId: %{public}d",
        focusWindowId, realHostWindowId);

    // after frontend initialize
    if (window_->IsFocused()) {
        Focus();
    }

    Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    auto pipeline = container->GetPipelineContext();
    // Use metadata to control the center-alignment of text at line height.
    bool halfLeading = std::any_of(metaData.begin(), metaData.end(),
        [](const auto& metaDataItem) { return metaDataItem.name == "half_leading" && metaDataItem.value == "true"; });
    bool visibleAreaRealTime =
        std::any_of(metaData.begin(), metaData.end(), [](const auto& metaDataItem) {
            return metaDataItem.name == "ArkTSVisibleAreaRealTime" && metaDataItem.value == "true";
        });
    pipeline->SetHalfLeading(halfLeading);
    pipeline->SetVisibleAreaRealTime(visibleAreaRealTime);
    bool hasPreviewTextOption = std::any_of(metaData.begin(), metaData.end(),
        [pipelineWeak = AceType::WeakClaim(AceType::RawPtr(pipeline))](const auto& metaDataItem) {
                if (metaDataItem.name == "can_preview_text") {
                    auto pipeline = pipelineWeak.Upgrade();
                    CHECK_NULL_RETURN(pipeline, false);
                    pipeline->SetSupportPreviewText(metaDataItem.value == "false");
                    return true;
                }
                return false;
            });
    pipeline->SetHasPreviewTextOption(hasPreviewTextOption);
    // Use metadata to control whether the cutout safeArea takes effect.
    bool useCutout = std::any_of(metaData.begin(), metaData.end(),
        [](const auto& metaDataItem) { return metaDataItem.name == "avoid_cutout" && metaDataItem.value == "true"; });
    if (pipeline) {
        auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
        if (pipelineContext) {
            auto safeAreaManager = pipelineContext->GetSafeAreaManager();
            if (safeAreaManager) {
                safeAreaManager->SetUseCutout(useCutout);
            }
        }
    }
    pipeline->SetApiTargetVersion(container->GetApiTargetVersion());
    container->CheckAndSetFontFamily();
    SetFontScaleAndWeightScale(container, instanceId_);
    if (pipeline) {
        auto rsConfig = window_->GetKeyboardAnimationConfig();
        KeyboardAnimationCurve curveIn = {
            rsConfig.curveIn.curveType_, rsConfig.curveIn.curveParams_, rsConfig.curveIn.duration_};
        KeyboardAnimationCurve curveOut = {
            rsConfig.curveOut.curveType_, rsConfig.curveOut.curveParams_, rsConfig.curveOut.duration_};
        KeyboardAnimationConfig config = {curveIn, curveOut};
        pipeline->SetKeyboardAnimationConfig(config);
    }
    // Use metadata to control whether dirty mark is blocked.
    bool isOpenInvisibleFreeze = std::any_of(metaData.begin(), metaData.end(), [](const auto& metaDataItem) {
        return metaDataItem.name == "ArkUIInvisibleFreeze" && metaDataItem.value == "true";
    });
    LOGI("ArkUIInvisibleFreeze: %{public}d", isOpenInvisibleFreeze);
    pipeline->SetOpenInvisibleFreeze(isOpenInvisibleFreeze);
    // Set sdk version in module json mode
    if (isModelJson) {
        if (pipeline && appInfo) {
            LOGI("[%{public}s][%{public}s][%{public}d]: SetMinPlatformVersion is %{public}d", bundleName_.c_str(),
                moduleName_.c_str(), instanceId_, appInfo->apiCompatibleVersion);
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    }
    if (runtime_) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context);
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(reinterpret_cast<NativeReference*>(ref), context);
        }
    }

    InitializeSafeArea(container);

    InitializeDisplayAvailableRect(container);

    // set container temp dir
    if (abilityContext) {
        if (!abilityContext->GetTempDir().empty()) {
            container->SetTempDir(abilityContext->GetTempDir());
        }
    }

    LayoutInspector::SetCallback(instanceId_);

    // setLogFunc of current app
    AddAlarmLogFunc();
    InitUISessionManagerCallbacks(pipeline);
    UiSessionManager::GetInstance()->SaveBaseInfo(std::string("bundleName:")
                                                     .append(bundleName)
                                                     .append(",moduleName:")
                                                     .append(moduleName)
                                                     .append(",abilityName:")
                                                     .append(abilityName));
    UpdateFontScale(context->GetConfiguration());
    auto thpExtraManager = AceType::MakeRefPtr<NG::THPExtraManagerImpl>();
    if (thpExtraManager->Init()) {
        pipeline->SetTHPExtraManager(thpExtraManager);
    }
    return errorCode;
}

bool GetIsSystemWindow(const RefPtr<Platform::AceContainer>& container)
{
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, false);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    return safeAreaManager->GetWindowTypeConfig().isSystemWindow;
}

void UIContentImpl::InitializeSafeArea(const RefPtr<Platform::AceContainer>& container)
{
    constexpr static int32_t PLATFORM_VERSION_TEN = 10;
    auto pipeline = container->GetPipelineContext();
    bool isSystemWindow =
        GetIsSystemWindow(container) && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN);
    if (pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        if (pipeline->GetIsAppWindow() || container->IsUIExtensionWindow() || isSystemWindow) {
            avoidAreaChangedListener_ = new PretendChangedListener(instanceId_);
            window_->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
            auto systemInsets = container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_SYSTEM);
            auto cutoutInsets = container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_CUTOUT);
            auto navInsets = container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR);
            pipeline->UpdateSystemSafeAreaWithoutAnimation(systemInsets);
            pipeline->UpdateCutoutSafeAreaWithoutAnimation(cutoutInsets);
            pipeline->UpdateNavSafeAreaWithoutAnimation(navInsets);
            TAG_LOGI(ACE_LAYOUT,
                "InitializeSafeArea systemInsets:%{public}s, cutoutInsets:%{public}s, navInsets:%{public}s",
                systemInsets.ToString().c_str(), cutoutInsets.ToString().c_str(), navInsets.ToString().c_str());
        }
    }
}

void UIContentImpl::InitializeDisplayAvailableRect(const RefPtr<Platform::AceContainer>& container)
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    auto& DMManager = Rosen::DisplayManager::GetInstance();
    auto window = container->GetUIWindow(instanceId_);
    uint64_t displayId = 0;
    if (window && window->GetDisplayId() != DISPLAY_ID_INVALID) {
        displayId = window->GetDisplayId();
        listenedDisplayId_ = displayId;
    } else if (window) {
        TAG_LOGW(AceLogTag::ACE_WINDOW, "initialize display available rect invalid. window name is %{public}s",
            window->GetWindowName().c_str());
    }
    availableAreaChangedListener_ = new AvailableAreaChangedListener(instanceId_);
    DMManager.RegisterAvailableAreaListener(availableAreaChangedListener_, displayId);
    Rosen::DMRect availableArea;
    auto defaultDisplay = DMManager.GetDisplayById(displayId);
    if (pipeline && defaultDisplay) {
        Rosen::DMError ret = defaultDisplay->GetAvailableArea(availableArea);
        if (ret == Rosen::DMError::DM_OK) {
            pipeline->UpdateDisplayAvailableRect(ConvertDMRect2Rect(availableArea));
            TAG_LOGI(AceLogTag::ACE_WINDOW,
                "Initialize displayId: %{public}u, availableRect: [%{public}d, %{public}d, %{public}d, %{public}d]",
                (uint32_t)displayId, availableArea.posX_, availableArea.posY_, availableArea.width_,
                availableArea.height_);
        } else {
            TAG_LOGE(AceLogTag::ACE_WINDOW, "Display failed to get availableArea, displayId: %{public}u",
                (uint32_t)displayId);
        }
    }

    if (!defaultDisplay) {
        TAG_LOGE(AceLogTag::ACE_WINDOW, "DisplayManager failed to get display by id: %{public}u", (uint32_t)displayId);
    }
}

void UIContentImpl::Foreground()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: window foreground", bundleName_.c_str(), moduleName_.c_str(),
        instanceId_);
    if (window_ != nullptr && window_->GetType() == Rosen::WindowType::WINDOW_TYPE_APP_MAIN_WINDOW) {
        PerfMonitor::GetPerfMonitor()->SetAppStartStatus();
        PerfMonitor::GetPerfMonitor()->NotifyAppJankStatsBegin();
    }
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
    LOGI("[%{public}s][%{public}s][%{public}d]: window background", bundleName_.c_str(), moduleName_.c_str(),
        instanceId_);
    PerfMonitor::GetPerfMonitor()->NotifyAppJankStatsEnd();
    Platform::AceContainer::OnHide(instanceId_);

    CHECK_NULL_VOID(window_);
    std::string windowName = window_->GetWindowName();
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, instanceId_, false);
}

void UIContentImpl::ReloadForm(const std::string& url)
{
    startUrl_ = url;
    LOGI("[%{public}s][%{public}s][%{public}d]: ReloadForm startUrl = %{public}s", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, startUrl_.c_str());
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
    LOGI("[%{public}s][%{public}s][%{public}d]: window focus", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    ContainerScope::UpdateRecentActive(instanceId_);
    Platform::AceContainer::OnActive(instanceId_);
    CHECK_NULL_VOID(window_);
    std::string windowName = window_->GetWindowName();
    Recorder::EventRecorder::Get().SetFocusContainerInfo(windowName, instanceId_);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
}

void UIContentImpl::UnFocus()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: window unfocus", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    Platform::AceContainer::OnInactive(instanceId_);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
}

void UIContentImpl::ActiveWindow()
{
    LOGI("[%{public}s][%{public}s][%{public}d]:window active", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    Platform::AceContainer::ActiveWindow(instanceId_);
}

void UIContentImpl::UnActiveWindow()
{
    LOGI("[%{public}s][%{public}s][%{public}d]:window unactive", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    Platform::AceContainer::UnActiveWindow(instanceId_);
}

void UIContentImpl::Destroy()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: window destroy", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
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
    UnregisterDisplayManagerCallback();
    SubwindowManager::GetInstance()->OnDestroyContainer(instanceId_);

    if (window_) {
        window_->UnregisterWaterfallModeChangeListener(waterfallModeChangeListener_);
        if (windowRectChangeListener_) {
            if (window_->GetType() == Rosen::WindowType::WINDOW_TYPE_UI_EXTENSION) {
                window_->UnregisterHostWindowRectChangeListener(windowRectChangeListener_);
            } else {
                window_->UnregisterWindowRectChangeListener(windowRectChangeListener_);
            }
            windowRectChangeListener_ = nullptr;
        }
    }
}

void UIContentImpl::UnregisterDisplayManagerCallback()
{
    auto& manager = Rosen::DisplayManager::GetInstance();
    if (foldStatusListener_) {
        manager.UnregisterFoldStatusListener(foldStatusListener_);
        foldStatusListener_ = nullptr;
    }
    if (foldDisplayModeListener_) {
        manager.UnregisterDisplayModeListener(foldDisplayModeListener_);
        foldDisplayModeListener_ = nullptr;
    }
    if (availableAreaChangedListener_) {
        manager.UnregisterAvailableAreaListener(availableAreaChangedListener_, listenedDisplayId_);
        availableAreaChangedListener_ = nullptr;
    }
}

void UIContentImpl::RegisterLinkJumpCallback()
{
#ifdef RESOURCE_SCHEDULE_SERVICE_ENABLE
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    auto pipeLineContext = AceType::DynamicCast<NG::PipelineContext>(pipelineContextBase);
    CHECK_NULL_VOID(pipeLineContext);
    auto bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    TAG_LOGI(AceLogTag::ACE_TEXT, "[%{public}s]: UIContentImpl::RegisterLinkJumpCallback", bundleName.c_str());
    // check 1 : for efficiency, if not in whiteList, no need to call RSS interface and go IPC
    bool isAllowedLinkJump = false;
    // call RSS's inner api
    auto errorNo = OHOS::ResourceSchedule::ResSchedClient::GetInstance().IsAllowedLinkJump(isAllowedLinkJump);
    if (errorNo != NO_ERROR) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "UIContentImpl::RegisterLinkJumpCallback, errorNo: %{public}i", errorNo);
        return;
    }
    if (!isAllowedLinkJump) { // check 1
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT, "UIContentImpl::RegisterLinkJumpCallback, LinkJump is Open");
    pipeLineContext->SetLinkJumpCallback([context = context_] (const std::string& link) {
        auto sharedContext = context.lock();
        CHECK_NULL_VOID(sharedContext);
        auto abilityContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
        CHECK_NULL_VOID(abilityContext);
        AAFwk::Want want;
        want.AddEntity(Want::ENTITY_BROWSER);
        want.SetUri(link);
        want.SetAction(ACTION_VIEWDATA);
        abilityContext->StartAbility(want, REQUEST_CODE);
    });
#endif // RESOURCE_SCHEDULE_SERVICE_ENABLE
}

void UIContentImpl::OnNewWant(const OHOS::AAFwk::Want& want)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: UIContent OnNewWant", bundleName_.c_str(), moduleName_.c_str(),
        instanceId_);
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
        TaskExecutor::TaskType::UI, "ArkUIGetAppBackgroundColor");

    LOGD("[%{public}s][%{public}s][%{public}d]: GetBackgroundColor:%{public}u",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, bgColor);
    return bgColor;
}

void UIContentImpl::SetBackgroundColor(uint32_t color)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: SetBackgroundColor:%{public}u",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, color);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    if (aceContainer) {
        aceContainer->SetIsUseCustomBg(true);
    }
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, bgColor = color]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetAppBgColor(Color(bgColor));
            pipelineContext->ChangeDarkModeBrightness();
        },
        TaskExecutor::TaskType::UI, "ArkUISetAppBackgroundColor");
}

void UIContentImpl::SetWindowContainerColor(uint32_t activeColor, uint32_t inactiveColor)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR,
        "[%{public}s][%{public}s][%{public}d]: SetWindowContainerColor:"
        "active color %{public}u, inactive color %{public}u",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, activeColor, inactiveColor);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [container, activeColor, inactiveColor]() {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->SetWindowContainerColor(Color(activeColor), Color(inactiveColor));
    };
    ExecuteUITask(std::move(task), "ArkUISetWindowContainerColor");
}

void UIContentImpl::GetAppPaintSize(OHOS::Rosen::Rect& paintRect)
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
    auto rect = renderContext->GetPaintRectWithoutTransform();
    auto offset = stageNode->GetPaintRectOffset(false, true);
    paintRect.posX_ = static_cast<int32_t>(offset.GetX());
    paintRect.posY_ = static_cast<int32_t>(offset.GetY());
    paintRect.width_ = static_cast<uint32_t>(rect.Width());
    paintRect.height_ = static_cast<uint32_t>(rect.Height());
}

void UIContentImpl::GetWindowPaintSize(OHOS::Rosen::Rect& paintRect)
{
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    CHECK_NULL_VOID(window_);
    auto windowRect = window_->GetRect();
    NG::RectInt rect;
    rect.SetRect(0, 0, windowRect.width_, windowRect.height_);
    pipelineContext->GetWindowPaintRectWithoutMeasureAndLayout(rect);
    paintRect.posX_ = static_cast<int32_t>(rect.GetX());
    paintRect.posY_ = static_cast<int32_t>(rect.GetY());
    paintRect.width_ = static_cast<uint32_t>(rect.Width());
    paintRect.height_ = static_cast<uint32_t>(rect.Height());
}

bool UIContentImpl::ProcessBackPressed()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: OnBackPressed called", bundleName_.c_str(), moduleName_.c_str(),
        instanceId_);
    Recorder::EventParamsBuilder builder;
    builder.SetEventType(Recorder::EventType::BACK_PRESSED);
    Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    if (container->IsUIExtensionWindow() && !container->WindowIsShow()) {
        return false;
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (pipeline) {
        auto uiExtMgr = pipeline->GetUIExtensionManager();
        if (uiExtMgr && uiExtMgr->OnBackPressed()) {
            LOGI("UIExtension consumed backpressed event");
            return true;
        }
    }
    bool ret = false;
    taskExecutor->PostSyncTask(
        [container, this, &ret]() {
            if (AceType::InstanceOf<Platform::DialogContainer>(container)) {
                if (Platform::DialogContainer::OnBackPressed(instanceId_)) {
                    ret = true;
                }
            } else {
                PerfMonitor::GetPerfMonitor()->RecordInputEvent(LAST_UP, UNKNOWN_SOURCE, 0);
                if (Platform::AceContainer::OnBackPressed(instanceId_)) {
                    ret = true;
                }
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIProcessBackPressed");
    return ret;
}

bool UIContentImpl::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(AceEngine::Get().GetContainer(instanceId_));
    CHECK_NULL_RETURN(container, false);
    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
            "PointerEvent Process to ui_content, eventInfo: id:%{public}d, "
            "WindowName = " SEC_PLD(%{public}s) ", "
            "WindowId = %{public}d, ViewWidth = %{public}d, ViewHeight = %{public}d, "
            "ViewPosX = %{public}d, ViewPosY = %{public}d",
            pointerEvent->GetId(), SEC_PARAM(container->GetWindowName().c_str()), container->GetWindowId(),
            container->GetViewWidth(), container->GetViewHeight(), container->GetViewPosX(), container->GetViewPosY());
    }
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
    Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent);
    return true;
}

bool UIContentImpl::ProcessPointerEvent(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void(bool)>& callback)
{
    if (!ProcessPointerEvent(pointerEvent)) {
        return false;
    }
    if (pointerEvent->GetButtonId() == MMI::PointerEvent::MOUSE_BUTTON_LEFT &&
        pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_RETURN(container, false);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
        CHECK_NULL_RETURN(context, false);
        auto task = [context, finallyCallback = callback]() {
            CHECK_NULL_VOID(context);
            CHECK_NULL_VOID(finallyCallback);
            ContainerScope scope(context->GetInstanceId());
            auto dragDropManager = context->GetDragDropManager();
            CHECK_NULL_VOID(dragDropManager);
            auto isAnyDraggableHit = dragDropManager->IsAnyDraggableHit(context, MOUSE_PRESS_LEFT + MOUSE_BASE_ID);
            TAG_LOGI(AceLogTag::ACE_DRAG, "is any draggable node hit: %{public}d", isAnyDraggableHit);
            dragDropManager->SetIsAnyDraggableHit(false);
            finallyCallback(isAnyDraggableHit);
        };

        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_RETURN(taskExecutor, false);
        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            task();
        } else {
            taskExecutor->PostTask(
                std::move(task), TaskExecutor::TaskType::UI, "ArkUIProcessPointerEvent", PriorityType::VIP);
        }
    } else {
        CHECK_NULL_RETURN(callback, false);
        callback(false);
    }
    return true;
}

bool UIContentImpl::ProcessPointerEventWithCallback(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void()>& callback)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(AceEngine::Get().GetContainer(instanceId_));
    CHECK_NULL_RETURN(container, false);
    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
            "PointerEvent Process to ui_content, eventInfo: id:%{public}d, "
            "WindowName = " SEC_PLD(%{public}s) ", "
            "WindowId = %{public}d, ViewWidth = %{public}d, ViewHeight = %{public}d, "
            "ViewPosX = %{public}d, ViewPosY = %{public}d",
            pointerEvent->GetId(), SEC_PARAM(container->GetWindowName().c_str()), container->GetWindowId(),
            container->GetViewWidth(), container->GetViewHeight(), container->GetViewPosX(), container->GetViewPosY());
    }
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
    Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent, nullptr, callback);
    return true;
}

bool UIContentImpl::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& touchEvent, bool isPreIme)
{
    TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
        "KeyEvent Process to ui_content, eventInfo: id:%{public}d, "
        "keyEvent info: keyCode is " SEC_PLD(%{private}d) ", "
        "keyAction is " SEC_PLD(%{public}d) ", keyActionTime is %{public}" PRId64,
        touchEvent->GetId(), SEC_PARAM(touchEvent->GetKeyCode()), SEC_PARAM(touchEvent->GetKeyAction()),
        touchEvent->GetActionTime());
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
    return Platform::AceViewOhos::DispatchKeyEvent(aceView, touchEvent, isPreIme);
}

bool UIContentImpl::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}

bool UIContentImpl::ProcessVsyncEvent(uint64_t timeStampNanos)
{
    return false;
}

void BuildParsedConfig(Platform::ParsedConfig& parsedConfig,
    const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config, const bool formFontUseDefault)
{
    parsedConfig.colorMode = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    parsedConfig.deviceAccess = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
    parsedConfig.direction = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DIRECTION);
    parsedConfig.densitydpi = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DENSITYDPI);
    parsedConfig.fontFamily = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_FONT);
    parsedConfig.themeTag = config->GetItem("ohos.application.theme");
    parsedConfig.colorModeIsSetByApp = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::COLORMODE_IS_SET_BY_APP);
    parsedConfig.mcc = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_MCC);
    parsedConfig.mnc = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_MNC);
    parsedConfig.fontId = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_FONT_ID);
    // Process system language and preferred language
    auto isPreferredLanguage = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::IS_PREFERRED_LANGUAGE);
    if (isPreferredLanguage == IS_PREFERRED_LANGUAGE) {
        parsedConfig.preferredLanguage = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
    } else {
        parsedConfig.languageTag = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
    }
    // EtsCard Font followSytem disable
    if (formFontUseDefault) {
        parsedConfig.fontScale = "1.0";
        parsedConfig.fontWeightScale = "1.0";
    } else {
        parsedConfig.fontScale = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_FONT_SIZE_SCALE);
        parsedConfig.fontWeightScale = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_FONT_WEIGHT_SCALE);
    }
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    CHECK_NULL_VOID(config);
    StoreConfiguration(config);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    bool formFontUseDefault = isFormRender_ && !fontScaleFollowSystem_;
    taskExecutor->PostTask(
        [weakContainer = WeakPtr<Platform::AceContainer>(container), config, instanceId = instanceId_,
            bundleName = bundleName_, moduleName = moduleName_, formFontUseDefault]() {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_VOID(container);
            Platform::ParsedConfig parsedConfig;
            BuildParsedConfig(parsedConfig, config, formFontUseDefault);
            container->UpdateConfiguration(parsedConfig, config->GetName());
            LOGI("[%{public}d][%{public}s][%{public}s] UpdateConfiguration, name:%{public}s",
                instanceId, bundleName.c_str(), moduleName.c_str(), config->GetName().c_str());
        },
        TaskExecutor::TaskType::UI, "ArkUIUIContentUpdateConfiguration");
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config,
    const std::shared_ptr<Global::Resource::ResourceManager>& resourceManager)
{
    CHECK_NULL_VOID(config);

    RefPtr<ResourceAdapter> adapter = AceType::MakeRefPtr<ResourceAdapterImplV2>(resourceManager, instanceId_);
    ResourceManager::GetInstance().UpdateMainResourceAdapter(bundleName_, moduleName_, instanceId_, adapter);

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->UpdateThemeManager(adapter);

    StoreConfiguration(config);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    bool formFontUseDefault = isFormRender_ && !fontScaleFollowSystem_;
    taskExecutor->PostTask(
        [weakContainer = WeakPtr<Platform::AceContainer>(container), config, instanceId = instanceId_,
            bundleName = bundleName_, moduleName = moduleName_, formFontUseDefault]() {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_VOID(container);
            Platform::ParsedConfig parsedConfig;
            BuildParsedConfig(parsedConfig, config, formFontUseDefault);
            container->UpdateConfiguration(parsedConfig, config->GetName(), true);
            LOGI("[%{public}d][%{public}s][%{public}s] UpdateConfiguration, name:%{public}s", instanceId,
                bundleName.c_str(), moduleName.c_str(), config->GetName().c_str());
        },
        TaskExecutor::TaskType::UI, "ArkUIUIContentUpdateConfigurationWithResMgr");
}

void UIContentImpl::UpdateConfigurationSyncForAll(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    CHECK_NULL_VOID(config);

    auto dialogContainer = Platform::DialogContainer::GetContainer(instanceId_);
    if (dialogContainer) {
        return;
    }
    if (isDynamicRender_ || isFormRender_) {
        return;
    }

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    bool formFontUseDefault = isFormRender_ && !fontScaleFollowSystem_;
    Platform::ParsedConfig parsedConfig;
    BuildParsedConfig(parsedConfig, config, formFontUseDefault);
    container->UpdateConfigurationSyncForAll(parsedConfig, config->GetName());
    LOGI("[%{public}d][%{public}s][%{public}s] UpdateConfigurationSyncForAll, name:%{public}s",
        instanceId_, bundleName_.c_str(), moduleName_.c_str(), config->GetName().c_str());
}

void UIContentImpl::AddKeyFrameAnimateEndCallback(const std::function<void()>& callback)
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    TAG_LOGD(AceLogTag::ACE_WINDOW, "AddKeyFrameAnimateEndCallback");
    auto rootElement = context->GetRootElement();
    CHECK_NULL_VOID(rootElement);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(rootElement->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    rosenRenderContext->AddKeyFrameAnimateEndCallback(callback);
}

void UIContentImpl::AddKeyFrameCanvasNodeCallback(const std::function<
    void(std::shared_ptr<Rosen::RSCanvasNode>& canvasNode,
        std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)>& callback)
{
    TAG_LOGD(AceLogTag::ACE_WINDOW, "AddKeyFrameCanvasNodeCallback");
    addNodeCallback_ = callback;
}

void UIContentImpl::LinkKeyFrameCanvasNode(std::shared_ptr<OHOS::Rosen::RSCanvasNode>& canvasNode)
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
#ifndef NG_BUILD
#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled()) {
        CHECK_NULL_VOID(window_);
        auto surfaceNode = window_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);
        CHECK_NULL_VOID(canvasNode);
        TAG_LOGD(AceLogTag::ACE_WINDOW, "AddChild surfaceNode %{public}" PRIu64 "canvasNode %{public}" PRIu64 "",
            surfaceNode->GetId(), canvasNode->GetId());
        surfaceNode->AddChild(canvasNode, -1);
    }
#endif
#endif
    TAG_LOGD(AceLogTag::ACE_WINDOW, "LinkKeyFrameCanvasNode.");
    auto rootElement = context->GetRootElement();
    CHECK_NULL_VOID(rootElement);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(rootElement->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    rosenRenderContext->LinkCanvasNodeToRootNode(context->GetRootElement());
}

void UIContentImpl::CacheAnimateInfo(const ViewportConfig& config,
    OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    TAG_LOGD(AceLogTag::ACE_WINDOW, "CacheAnimateInfo.");
    cachedAnimateFlag_.store(true);
    cachedConfig_ = config;
    cachedReason_ = reason;
    cachedRsTransaction_ = rsTransaction;
    cachedAvoidAreas_ = avoidAreas;
}

void UIContentImpl::ExecKeyFrameCachedAnimateAction()
{
    TAG_LOGD(AceLogTag::ACE_WINDOW, "exec keyframe cache in");
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    if (cachedAnimateFlag_.load()) {
        const uint32_t delay = 50;
        auto task = [cachedConfig = cachedConfig_, cachedReason = cachedReason_,
            cachedRsTransaction = cachedRsTransaction_, cachedAvoidAreas = cachedAvoidAreas_,
            UICONTENT_IMPL_HELPER(content)] () {
            UICONTENT_IMPL_HELPER_GUARD(content, return);
            TAG_LOGD(AceLogTag::ACE_WINDOW, "exec keyframe cache");
            UICONTENT_IMPL_PTR(content)->UpdateViewportConfig(cachedConfig, cachedReason,
                cachedRsTransaction, cachedAvoidAreas);
        };
        taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, delay,
            "ArkUIExecKeyFrameCachedAnimateTask", PriorityType::HIGH);
    }
    cachedAnimateFlag_.store(false);
}

void UIContentImpl::KeyFrameDragStartPolicy(RefPtr<NG::PipelineContext> context)
{
    if (!context) {
        TAG_LOGE(AceLogTag::ACE_WINDOW, "context is null.");
        return;
    }

    auto transactionController =  Rosen::RSSyncTransactionController::GetInstance();
    CHECK_NULL_VOID(transactionController);
    transactionController->OpenSyncTransaction();
    auto rsTransaction = transactionController->GetRSTransaction();
    auto rootElement = context->GetRootElement();
    if (!rootElement) {
        transactionController->CloseSyncTransaction();
        return;
    }
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(rootElement->GetRenderContext());
    if (!rosenRenderContext) {
        transactionController->CloseSyncTransaction();
        return;
    }
    rosenRenderContext->CreateCanvasNode();
    canvasNode_ = rosenRenderContext->GetCanvasNode();
    if (addNodeCallback_ && canvasNode_) {
        TAG_LOGI(AceLogTag::ACE_WINDOW, "rsTransaction addNodeCallback_.");
        addNodeCallback_(canvasNode_, rsTransaction);
    }
    transactionController->CloseSyncTransaction();

    std::function<void()> callbackCachedAnimation = std::bind(&UIContentImpl::ExecKeyFrameCachedAnimateAction, this);
    CHECK_NULL_VOID(callbackCachedAnimation);
    rosenRenderContext->AddKeyFrameCachedAnimateActionCallback(callbackCachedAnimation);
}

bool UIContentImpl::KeyFrameActionPolicy(const ViewportConfig& config,
    OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    if (!config.GetKeyFrameConfig().enableKeyFrame_) {
        return false;
    }

    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, true);
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(context, true);

    bool animateRes = true;
    auto rootElement = context->GetRootElement();
    CHECK_NULL_RETURN(rootElement, true);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(rootElement->GetRenderContext());
    CHECK_NULL_RETURN(rosenRenderContext, true);
    switch (reason) {
        case OHOS::Rosen::WindowSizeChangeReason::DRAG_START:
            if (!rosenRenderContext->GetIsDraggingFlag()) {
                if (rosenRenderContext->GetCanvasNode()) {
                    rosenRenderContext->SetReDraggingFlag(true);
                }
                rosenRenderContext->SetIsDraggingFlag(true);
                KeyFrameDragStartPolicy(context);
            }
            return true;
        case OHOS::Rosen::WindowSizeChangeReason::DRAG_END:
            rosenRenderContext->SetIsDraggingFlag(false);
            [[fallthrough]];
        case OHOS::Rosen::WindowSizeChangeReason::DRAG:
            animateRes = rosenRenderContext->SetCanvasNodeOpacityAnimation(
                config.GetKeyFrameConfig().animationDuration_,
                config.GetKeyFrameConfig().animationDelay_,
                reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_END);
            if (!animateRes) {
                CacheAnimateInfo(config, reason, rsTransaction, avoidAreas);
                return true;
            }
            return false;
        default:
            return true;
    }
    return false;
}

void UIContentImpl::SetUIExtensionImeShow(const Rect& keyboardRect, int32_t instanceId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (GreatNotEqual(keyboardRect.Height(), 0.0f)) {
        taskExecutor->PostTask(
            [id = instanceId] {
                ContainerScope scope(id);
                auto pipeline = NG::PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                pipeline->SetUIExtensionImeShow(true);
            }, TaskExecutor::TaskType::UI, "ArkUISetUIExtensionImeShow");
    } else {
        taskExecutor->PostTask(
            [id = instanceId] {
                ContainerScope scope(id);
                auto pipeline = NG::PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                pipeline->SetUIExtensionImeShow(false);
            }, TaskExecutor::TaskType::UI, "ArkUISetUIExtensionImeHide");
    }
}

bool UIContentImpl::UIExtensionKeyboardAvoid(const RefPtr<PipelineBase>& pipelineContext,
    int32_t instanceId, const Rect keyboardRect, const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(pipeline, false);
    ContainerScope scope(instanceId);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_RETURN(uiExtensionManager, false);
    SetUIExtensionImeShow(keyboardRect, instanceId);

    if (uiExtensionManager->NotifyOccupiedAreaChangeInfo(info)) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "uiExtension consumed");
        ContainerScope scope(instanceId);
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_RETURN(container, false);
        auto context = container->GetPipelineContext();
        CHECK_NULL_RETURN(context, false);
        context->OnVirtualKeyboardAreaChange(Rect(), 0, 0);
        return true;
    }
    return false;
}

bool UIContentImpl::LaterAvoid(const Rect& keyboardRect, double positionY, double height)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, false);
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(pipeline, false);
    auto textFieldManager = AceType::DynamicCast<NG::TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_RETURN(textFieldManager, false);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, false);
    auto windowMode = windowManager->GetWindowMode();
    if (windowMode == WindowMode::WINDOW_MODE_FLOATING || windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        textFieldManager->SetLaterAvoid(false);
        return false;
    }
    bool isRotate = false;
    auto displayInfo = container->GetDisplayInfo();
    if (displayInfo) {
        auto dmRotation = static_cast<int32_t>(displayInfo->GetRotation());
        isRotate = lastRotation != -1 && lastRotation != dmRotation;
        lastRotation = dmRotation;
    } else {
        lastRotation = -1;
    }
    auto triggerAvoidTaskOrientation = textFieldManager->GetContextTriggerAvoidTaskOrientation();
    textFieldManager->SetContextTriggerAvoidTaskOrientation(-1);
    if ((isRotate && lastRotation == triggerAvoidTaskOrientation) ||
        (textFieldManager->GetLaterAvoid() && NearEqual(0.0f, keyboardRect.Height()))) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "no need to later avoid, trigger avoid now");
        textFieldManager->SetLaterAvoid(false);
        return false;
    }
    auto laterRect = textFieldManager->GetLaterAvoidKeyboardRect();
    if (textFieldManager->GetLaterAvoid() && NearEqual(laterRect.Height(), keyboardRect.Height())) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "will trigger avoid later, ignore this notify");
        return true;
    }
    // do not avoid immediately when device is in rotation, trigger it after context trigger root rect update
    if (textFieldManager->GetLaterAvoid() || isRotate) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "rotation change to %{public}d, later avoid %{public}s %{public}f"
            "%{public}f", lastRotation, keyboardRect.ToString().c_str(), positionY, height);
        NG::LaterAvoidInfo laterAvoidInfo = {true, keyboardRect, positionY, height, lastRotation };
        textFieldManager->SetLaterAvoidArgs(laterAvoidInfo);
        return true;
    }
    return false;
}

void UIContentImpl::SetKeyboardInfo(const RefPtr<PipelineBase>& pipelineContext, float height)
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    safeAreaManager->SetKeyboardInfo(height);
}

void UIContentImpl::KeyboardAvoid(OHOS::Rosen::WindowSizeChangeReason reason, int32_t instanceId,
    const RefPtr<PipelineBase>& pipelineContext, const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
    const RefPtr<Platform::AceContainer>& container, const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(info);
    if (reason != OHOS::Rosen::WindowSizeChangeReason::OCCUPIED_AREA_CHANGE) {
        return;
    }
    auto rect = info->rect_;
    Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
    SetKeyboardInfo(pipelineContext, keyboardRect.Height());
    if (UIExtensionKeyboardAvoid(pipelineContext, instanceId, keyboardRect, info)) {
        return;
    }
    if (container->IsSceneBoardWindow()) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "SceneBoard window, no keyboard avoidance");
        return;
    }
    ACE_LAYOUT_SCOPED_TRACE("KeyboardAvoid keyboardRect %s", keyboardRect.ToString().c_str());
    auto curWindow = pipelineContext->GetCurrentWindowRect();
    double textFieldPositionY = info->textFieldPositionY_;
    double textFieldHeight = info->textFieldHeight_;
    textFieldPositionY -= curWindow.Top();
    ContainerScope scope(instanceId);
    if (LaterAvoid(keyboardRect, textFieldPositionY, textFieldHeight)) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Keyboard later avoid and return");
        ACE_LAYOUT_SCOPED_TRACE("Keyboard later avoid and return");
        return;
    }
    pipelineContext->OnVirtualKeyboardAreaChange(keyboardRect, textFieldPositionY, textFieldHeight, rsTransaction);
}

void UIContentImpl::UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
    const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    if (KeyFrameActionPolicy(config, reason, rsTransaction, avoidAreas)) {
        return;
    }

    if (SystemProperties::GetWindowRectResizeEnabled()) {
        PerfMonitor::GetPerfMonitor()->RecordWindowRectResize(static_cast<OHOS::Ace::WindowSizeChangeReason>(reason),
            bundleName_);
    }
    UpdateViewportConfigWithAnimation(config, reason, {}, rsTransaction, avoidAreas, info);
}

void UIContentImpl::UpdateViewportConfigWithAnimation(const ViewportConfig& config,
    OHOS::Rosen::WindowSizeChangeReason reason, AnimationOption animationOpt,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
    const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    std::string stringifiedMap = StringifyAvoidAreas(avoidAreas);
    if (info) {
        auto rect = info->rect_;
        Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        if (SystemProperties::GetSyncDebugTraceEnabled()) {
            ACE_LAYOUT_SCOPED_TRACE(
                "[%s][%s][%d]: UpdateViewportConfig %s, windowSizeChangeReason %d, is rsTransaction nullptr %d, %s,"
                " keyboardRect %s", bundleName_.c_str(), moduleName_.c_str(), instanceId_, config.ToString().c_str(),
                static_cast<uint32_t>(reason), rsTransaction == nullptr, stringifiedMap.c_str(),
                keyboardRect.ToString().c_str());
        }
        TAG_LOGI(ACE_LAYOUT,
            "[%{public}s][%{public}s][%{public}d]: UpdateViewportConfig %{public}s, windowSizeChangeReason %{public}d,"
            " is rsTransaction nullptr %{public}d, %{public}s, keyboardRect %{public}s", bundleName_.c_str(),
            moduleName_.c_str(), instanceId_, config.ToString().c_str(), static_cast<uint32_t>(reason),
            rsTransaction == nullptr, stringifiedMap.c_str(), keyboardRect.ToString().c_str());
    } else {
        if (SystemProperties::GetSyncDebugTraceEnabled()) {
            ACE_LAYOUT_SCOPED_TRACE(
                "[%s][%s][%d]: UpdateViewportConfig %s, windowSizeChangeReason %d, is rsTransaction nullptr %d, %s,"
                " keyboardInfo is null",
                bundleName_.c_str(), moduleName_.c_str(), instanceId_, config.ToString().c_str(),
                static_cast<uint32_t>(reason), rsTransaction == nullptr, stringifiedMap.c_str());
        }
        TAG_LOGI(ACE_LAYOUT,
            "[%{public}s][%{public}s][%{public}d]: UpdateViewportConfig %{public}s, windowSizeChangeReason %{public}d,"
            " is rsTransaction nullptr %{public}d, %{public}s, keyboardInfo is null", bundleName_.c_str(),
            moduleName_.c_str(), instanceId_, config.ToString().c_str(), static_cast<uint32_t>(reason),
            rsTransaction == nullptr, stringifiedMap.c_str());
    }

    if (reason == OHOS::Rosen::WindowSizeChangeReason::PAGE_ROTATION) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "save PAGE_ROTATION as ROTATION");
        reason = OHOS::Rosen::WindowSizeChangeReason::ROTATION;
    }
    if (lastReason_ == OHOS::Rosen::WindowSizeChangeReason::UNDEFINED) {
        lastReason_ = reason;
    }
    bool reasonDragFlag = GetWindowSizeChangeReason(lastReason_, reason);
    lastReason_ = reason;

    if (!g_isDragging && !g_isDynamicVsync && (reason == OHOS::Rosen::WindowSizeChangeReason::DRAG ||
        reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_START)) {
        OHOS::AppExecFwk::EventHandler::SetVsyncPolicy(true);
        ACE_SCOPED_TRACE_COMMERCIAL("SetVsyncPolicy(true)");
        g_isDragging = true;
    }

    bool isOrientationChanged = static_cast<int32_t>(SystemProperties::GetDeviceOrientation()) != config.Orientation();
    SystemProperties::SetDeviceOrientation(config.Orientation());
    TAG_LOGD(
        AceLogTag::ACE_WINDOW, "Update orientation to : %{public}d", static_cast<uint32_t>(config.Orientation()));
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SetCurrentDisplayOrientation(static_cast<DisplayOrientation>(config.Orientation()));
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    if (container->IsSubContainer()) {
        auto rect = NG::RectF(config.Left(), config.Top(), config.Width(), config.Height());
        SubwindowManager::GetInstance()->SetRect(rect, instanceId_);
        TAG_LOGI(AceLogTag::ACE_WINDOW, "UpdateViewportConfig for subContainer: %{public}s",
            rect.ToString().c_str());
    }
    // The density of sub windows related to dialog needs to be consistent with the main window.
    auto modifyConfig = config;
    if (instanceId_ >= MIN_SUBCONTAINER_ID) {
        auto parentContainer = Platform::AceContainer::GetContainer(container->GetParentId());
        CHECK_NULL_VOID(parentContainer);
        if (parentContainer->IsSceneBoardWindow()) {
            auto parentPipeline = parentContainer->GetPipelineContext();
            CHECK_NULL_VOID(parentPipeline);
            modifyConfig.SetDensity(parentPipeline->GetDensity());
        }
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto updateDensityTask = [container, modifyConfig]() {
        auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
        CHECK_NULL_VOID(aceView);
        Platform::AceViewOhos::SetViewportMetrics(aceView, modifyConfig); // update density into pipeline
    };
    auto updateDeviceOrientationTask = [container, modifyConfig, reason]() {
        if (reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION) {
            container->UpdateResourceOrientation(modifyConfig.Orientation());
        }
    };
    auto updateDisplayIdAndAreaTask = [container, context, modifyConfig, UICONTENT_IMPL_HELPER(content)]() {
        auto displayId = modifyConfig.DisplayId();
        if (displayId == DISPLAY_ID_INVALID) {
            TAG_LOGE(AceLogTag::ACE_WINDOW, "Invalid display id.");
            return;
        }
        if (container->GetCurrentDisplayId() != displayId) {
            container->SetCurrentDisplayId(displayId);
            auto currentDisplay = Rosen::DisplayManager::GetInstance().GetDisplayById(displayId);
            if (context && currentDisplay) {
                Rosen::DMRect availableArea;
                Rosen::DMError ret = currentDisplay->GetAvailableArea(availableArea);
                if (ret == Rosen::DMError::DM_OK) {
                    context->UpdateDisplayAvailableRect(ConvertDMRect2Rect(availableArea));
                }
            }
        }
        UICONTENT_IMPL_HELPER_GUARD(content, return);
        UICONTENT_IMPL_PTR(content)->ChangeDisplayAvailableAreaListener(displayId);
    };
    if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        updateDensityTask(); // ensure density has been updated before load first page
        updateDeviceOrientationTask();
        updateDisplayIdAndAreaTask();
    } else {
        taskExecutor->PostTask(std::move(updateDensityTask), TaskExecutor::TaskType::UI, "ArkUIUpdateDensity");
        taskExecutor->PostTask(
            std::move(updateDeviceOrientationTask), TaskExecutor::TaskType::UI, "ArkUIDeviceOrientation");
        taskExecutor->PostTask(
            std::move(updateDisplayIdAndAreaTask), TaskExecutor::TaskType::UI, "ArkUIUpdateDisplayIdAndArea");
    }
    RefPtr<NG::SafeAreaManager> safeAreaManager = nullptr;

    std::map<OHOS::Rosen::AvoidAreaType, NG::SafeAreaInsets> updatingInsets;
    if (context) {
        context->FireSizeChangeByRotateCallback(isOrientationChanged, rsTransaction);
        if (reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_START ||
            reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_END) {
            bool isDragging = reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_START;
            if (!g_isDynamicVsync && !isDragging) {
                OHOS::AppExecFwk::EventHandler::SetVsyncPolicy(false);
                ACE_SCOPED_TRACE_COMMERCIAL("SetVsyncPolicy(false)");
                g_isDragging = false;
            }
            taskExecutor->PostTask(
                [weak = AceType::WeakClaim(AceType::RawPtr(context)), isDragging]() {
                    auto pipelineContext = weak.Upgrade();
                    CHECK_NULL_VOID(pipelineContext);
                    pipelineContext->SetIsWindowSizeDragging(isDragging);
                }, TaskExecutor::TaskType::UI, "ArkUIWindowSizeDragStartEnd", PriorityType::VIP);
        }
    }

    if (viewportConfigMgr_->IsConfigsEqual(config) && (rsTransaction == nullptr) && reasonDragFlag) {
        TAG_LOGI(ACE_LAYOUT, "UpdateViewportConfig return in advance");
        taskExecutor->PostTask([this, context, config, avoidAreas, reason, instanceId = instanceId_,
            pipelineContext, info, container, rsTransaction] {
                if (avoidAreas.empty() && !info) {
                    return;
                }
                if (ParseAvoidAreasUpdate(context, avoidAreas, config)) {
                    context->AnimateOnSafeAreaUpdate();
                }
                AvoidAreasUpdateOnUIExtension(context, avoidAreas);
                if (pipelineContext) {
                    TAG_LOGI(ACE_KEYBOARD, "KeyboardAvoid in advance");
                    KeyboardAvoid(reason, instanceId, pipelineContext, info, container, rsTransaction);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIUpdateOriginAvoidAreaAndExecuteKeyboardAvoid");
        return;
    }

    auto taskId = viewportConfigMgr_->MakeTaskId();
    auto task = [this, config = modifyConfig, container, reason, rsTransaction, rsWindow = window_, info,
                    isDynamicRender = isDynamicRender_, animationOpt, avoidAreas, taskId,
                    viewportConfigMgr = viewportConfigMgr_]() mutable {
        container->SetWindowPos(config.Left(), config.Top());
        auto pipelineContext = container->GetPipelineContext();
        if (pipelineContext) {
            UpdateSafeArea(pipelineContext, avoidAreas, config, container);
            pipelineContext->SetDisplayWindowRectInfo(
                Rect(Offset(config.Left(), config.Top()), Size(config.Width(), config.Height())));
            pipelineContext->SetWindowSizeChangeReason(static_cast<OHOS::Ace::WindowSizeChangeReason>(reason));
            TAG_LOGD(AceLogTag::ACE_WINDOW, "Update displayWindowRect in UpdateViewportConfig to : %{public}s",
                pipelineContext->GetDisplayWindowRectInfo().ToString().c_str());
            if (rsWindow) {
                pipelineContext->SetIsLayoutFullScreen(
                    rsWindow->GetWindowMode() == Rosen::WindowMode::WINDOW_MODE_FULLSCREEN);
                auto isNeedAvoidWindowMode = IsNeedAvoidWindowMode(rsWindow);
                pipelineContext->SetIsNeedAvoidWindow(isNeedAvoidWindowMode);
            }
            if (reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION) {
                pipelineContext->FlushBuild();
                pipelineContext->StartWindowAnimation();
                container->NotifyDirectionUpdate();
            }
        }
        auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
        CHECK_NULL_VOID(aceView);
        Platform::AceViewOhos::TransformHintChanged(aceView, config.TransformHint());
        if (isDynamicRender && animationOpt.IsValid()) {
            AnimationUtils::Animate(animationOpt, [pipelineContext, aceView, config, reason, rsTransaction] {
                ContainerScope scope(aceView->GetInstanceId());
                Platform::AceViewOhos::SurfaceChanged(aceView, config.Width(), config.Height(), config.Orientation(),
                    static_cast<WindowSizeChangeReason>(reason), rsTransaction);
                pipelineContext->OnSurfaceChanged(
                    config.Width(), config.Height(), static_cast<WindowSizeChangeReason>(reason), rsTransaction);
                pipelineContext->FlushUITasks(true);
            });
        } else {
            Platform::AceViewOhos::SurfaceChanged(aceView, config.Width(), config.Height(), config.Orientation(),
                static_cast<WindowSizeChangeReason>(reason), rsTransaction);
        }
        Platform::AceViewOhos::SurfacePositionChanged(aceView, config.Left(), config.Top());
        SubwindowManager::GetInstance()->OnWindowSizeChanged(container->GetInstanceId(),
            Rect(Offset(config.Left(), config.Top()), Size(config.Width(), config.Height())),
            static_cast<WindowSizeChangeReason>(reason));
        viewportConfigMgr->UpdateViewConfigTaskDone(taskId);
        if (pipelineContext) {
            TAG_LOGI(ACE_KEYBOARD, "KeyboardAvoid in the UpdateViewportConfig task");
            KeyboardAvoid(reason, instanceId_, pipelineContext, info, container, rsTransaction);
        }
    };
    auto changeBrightnessTask = [container]() {
        auto pipelineContext = container->GetPipelineContext();
        if (pipelineContext) {
            pipelineContext->ChangeDarkModeBrightness();
        }
    };
    taskExecutor->PostTask(std::move(changeBrightnessTask), TaskExecutor::TaskType::UI, "ArkUIUpdateBrightness");
    AceViewportConfig aceViewportConfig(modifyConfig, reason, rsTransaction);
    bool isReasonRotationOrDPI = (reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION ||
        reason == OHOS::Rosen::WindowSizeChangeReason::UPDATE_DPI_SYNC ||
        reason == OHOS::Rosen::WindowSizeChangeReason::RESIZE_WITH_ANIMATION);
    if (container->IsUseStageModel() && isReasonRotationOrDPI) {
        if (container->IsUIExtensionWindow()) {
            pipelineContext->AddUIExtensionCallbackEvent(NG::UIExtCallbackEventId::ON_AREA_CHANGED);
        }
        viewportConfigMgr_->UpdateConfigSync(aceViewportConfig, std::move(task));
        if (rsTransaction != nullptr) {
            viewportConfigMgr_->CancelAllPromiseTaskLocked();
        } else if (reason == OHOS::Rosen::WindowSizeChangeReason::UPDATE_DPI_SYNC) {
            viewportConfigMgr_->CancelUselessTaskLocked();
            viewportConfigMgr_->CancelAllPromiseTaskLocked();
        }
    } else if (rsTransaction != nullptr || !avoidAreas.empty()) {
        // When rsTransaction is not nullptr, the task contains animation. It shouldn't be cancled.
        // When avoidAreas need updating, the task shouldn't be cancelled.
        viewportConfigMgr_->UpdatePromiseConfig(aceViewportConfig, std::move(task), container, taskId,
            "ArkUIPromiseViewportConfig");
    } else {
        if (container->IsUIExtensionWindow()) {
            pipelineContext->AddUIExtensionCallbackEvent(NG::UIExtCallbackEventId::ON_AREA_CHANGED);
        }
        viewportConfigMgr_->UpdateConfig(aceViewportConfig, std::move(task), container, "ArkUIUpdateViewportConfig");
    }
    viewportConfigMgr_->StoreConfig(aceViewportConfig);
    viewportConfigMgr_->StoreInfo(info);
    UIExtensionUpdateViewportConfig(config);
}

void UIContentImpl::UIExtensionUpdateViewportConfig(const ViewportConfig& config)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto updateSessionViewportConfigTask = [id = instanceId_, config]() {
        ContainerScope scope(id);
        auto context = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto uiExtMgr = context->GetUIExtensionManager();
        if (uiExtMgr) {
            uiExtMgr->UpdateSessionViewportConfig(config);
        }
    };
    taskExecutor->PostTask(
        std::move(updateSessionViewportConfigTask), TaskExecutor::TaskType::UI, "ArkUIUpdateSessionViewportConfig");
}

void UIContentImpl::SetIgnoreViewSafeArea(bool ignoreViewSafeArea)
{
    TAG_LOGI(ACE_LAYOUT, "[%{public}s][%{public}s][%{public}d]: SetIgnoreViewSafeArea:%{public}u",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, ignoreViewSafeArea);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipeline = container->GetPipelineContext();
    const static int32_t PLATFORM_VERSION_TEN = 10;
    CHECK_NULL_VOID(pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN &&
                    (pipeline->GetIsAppWindow() || container->IsUIExtensionWindow()));
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, ignoreSafeArea = ignoreViewSafeArea]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetIgnoreViewSafeArea(ignoreSafeArea);
        },
        TaskExecutor::TaskType::UI, "ArkUISetIgnoreViewSafeArea");
}

void UIContentImpl::UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDecor)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: UpdateWindowMode: %{public}d, hasDecor: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, mode, hasDecor);
    UpdateDecorVisible(mode == OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING, hasDecor);
    NotifyWindowMode(mode);
}

void UIContentImpl::NotifyWindowMode(OHOS::Rosen::WindowMode mode)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: NotifyWindowMode mode = %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, mode);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipeline);
    taskExecutor->PostTask(
        [weak = WeakPtr<NG::PipelineContext>(pipeline), mode]() {
            auto pipeline = weak.Upgrade();
            CHECK_NULL_VOID(pipeline);
            auto uiExtMgr = pipeline->GetUIExtensionManager();
            CHECK_NULL_VOID(uiExtMgr);
            uiExtMgr->NotifyWindowMode(mode);
        },
        TaskExecutor::TaskType::UI, "ArkUINotifyWindowMode");
}

void UIContentImpl::UpdateWindowBlur()
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_VOID(stageNode);
    auto renderContext = stageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateWindowBlur();
}

void UIContentImpl::UpdateDecorVisible(bool visible, bool hasDecor)
{
    std::lock_guard<std::mutex> lock(updateDecorVisibleMutex_);
    LOGI("[%{public}s][%{public}s][%{public}d]: UpdateWindowVisible: %{public}d, hasDecor: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, visible, hasDecor);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [instanceId = instanceId_, visible, hasDecor]() {
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_VOID(container);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ShowContainerTitle(visible, hasDecor);
        pipelineContext->ChangeDarkModeBrightness();
    };

    // Cancel the pending task
    updateDecorVisibleTask_.Cancel();
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        updateDecorVisibleTask_ = SingleTaskExecutor::CancelableTask(std::move(task));
        taskExecutor->PostTask(updateDecorVisibleTask_,
            TaskExecutor::TaskType::UI, "ArkUIUpdateDecorVisible");
    }
}

void UIContentImpl::SetUIContentType(UIContentType uIContentType)
{
    uIContentType_ = uIContentType;
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->SetUIContentType(uIContentType);
}

void UIContentImpl::SetHostParams(const OHOS::AAFwk::WantParams& params)
{
    if (hostWindowInfo_.hostWantParams == nullptr) {
        hostWindowInfo_.hostWantParams = std::make_shared<OHOS::AAFwk::Want>();
    }

    hostWindowInfo_.hostWantParams->SetParams(params);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto containerHandler = container->GetContainerHandler();
    CHECK_NULL_VOID(containerHandler);
    auto uIExtensionContainerHandler =
        AceType::DynamicCast<NG::UIExtensionContainerHandler>(containerHandler);
    CHECK_NULL_VOID(uIExtensionContainerHandler);
    uIExtensionContainerHandler->SetHostParams(hostWindowInfo_.hostWantParams);
}

void UIContentImpl::UpdateMaximizeMode(OHOS::Rosen::MaximizeMode mode)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: UpdateMaximizeMode: %{public}d", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, mode);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [container, mode]() {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto windowManager = pipelineContext->GetWindowManager();
        CHECK_NULL_VOID(windowManager);
        windowManager->SetCurrentWindowMaximizeMode(static_cast<OHOS::Ace::MaximizeMode>(mode));
        pipelineContext->ShowContainerTitle(true, true, true);
    };
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, "ArkUIUpdateMaximizeMode");
    }
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

int32_t UIContentImpl::AddFocusActiveChangeCallback(const std::function<void(bool isFocusAvtive)>& callback)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, 0);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, 0);
    auto focusManager = pipelineContext->GetOrCreateFocusManager();
    CHECK_NULL_RETURN(focusManager, 0);
    return focusManager->AddFocusActiveChangeCallback(callback);
}

void UIContentImpl::RemoveFocusActiveChangeCallback(int32_t handler)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto focusManager = pipelineContext->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->RemoveFocusActiveChangeCallback(handler);
}

void UIContentImpl::HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: HideWindowTitleButton hideSplit: %{public}d, hideMaximize: %{public}d, "
         "hideMinimize: %{public}d, hideClose: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, hideSplit, hideMaximize, hideMinimize, hideClose);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [container, hideSplit, hideMaximize, hideMinimize, hideClose]() {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->SetContainerButtonHide(hideSplit, hideMaximize, hideMinimize, hideClose);
    };
    ExecuteUITask(std::move(task), "ArkUIHideWindowTitleButton");
}

void UIContentImpl::UpdateTitleInTargetPos(bool isShow, int32_t height)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: UpdateTitleInTargetPos, isShow: %{public}d, height: "
         "%{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, isShow, height);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [container, isShow, height]() {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateTitleInTargetPos(isShow, height);
    };
    ExecuteUITask(std::move(task), "ArkUIUpdateTitleInTargetPos");
}

void UIContentImpl::NotifyRotationAnimationEnd()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (pipelineContext) {
                pipelineContext->StopWindowAnimation();
            }
        },
        TaskExecutor::TaskType::UI, "ArkUINotifyRotationAnimationEnd");
}

void UIContentImpl::DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    std::string currentPid = std::to_string(getpid());
    for (auto param : params) {
        if (param == currentPid) {
            LOGE("DumpInfo pid has appeared");
            return;
        }
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto ret = taskExecutor->PostSyncTaskTimeout(
        [&]() { container->Dump(params, info); }, TaskExecutor::TaskType::UI, 1500, "ArkUIDumpInfo"); // timeout 1.5s
    if (!ret) {
        LOGE("DumpInfo failed");
    }
}

void UIContentImpl::UpdateDialogResourceConfiguration(RefPtr<Container>& container,
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
    auto dialogContainer = AceType::DynamicCast<Platform::DialogContainer>(container);
    if (dialogContainer) {
        std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
        CHECK_NULL_VOID(context);
        auto resourceManager = context->GetResourceManager();
        if (resourceManager != nullptr) {
            resourceManager->GetResConfig(*resConfig);
            CHECK_NULL_VOID(resConfig);
            if (resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK) {
                dialogContainer->SetColorMode(ColorMode::DARK);
            } else {
                dialogContainer->SetColorMode(ColorMode::LIGHT);
            }
        }
        auto aceResCfg = dialogContainer->GetResourceConfiguration();
        aceResCfg.SetOrientation(SystemProperties::GetDeviceOrientation());
        aceResCfg.SetDensity(SystemProperties::GetResolution());
        aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
        aceResCfg.SetColorMode(dialogContainer->GetColorMode());
        aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
        aceResCfg.SetColorModeIsSetByApp(true);
        aceResCfg.SetLanguage(AceApplicationInfo::GetInstance().GetLocaleTag());
        dialogContainer->SetResourceConfiguration(aceResCfg);
    }
}

bool UIContentImpl::IfNeedTouchOutsideListener(const std::string& windowName)
{
    return !StringUtils::StartWith(windowName, SUBWINDOW_TOAST_PREFIX) ||
        Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY);
}

void UIContentImpl::InitializeSubWindow(OHOS::Rosen::Window* window, bool isDialog)
{
    window_ = window;
    CHECK_NULL_VOID(window_);
    LOGI("InitSubwindow: %{public}s", window->GetWindowName().c_str());
    RefPtr<Container> container;
    instanceId_ = Container::GenerateId<COMPONENT_SUBWINDOW_CONTAINER>();
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    uint64_t displayId = 0;
    if (window && window->GetDisplayId() != DISPLAY_ID_INVALID) {
        displayId = window->GetDisplayId();
    } else if (window) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "initialize subWindow display invalid. window name is %{public}s",
            window->GetWindowName().c_str());
    }
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDisplayById(displayId);
    if (defaultDisplay) {
        auto displayInfo = defaultDisplay->GetDisplayInfo();
        if (displayInfo) {
            density = displayInfo->GetDensityInCurResolution();
        }
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
    }
    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo;
    auto context = context_.lock();
    bool isCJFrontend = CJUtils::IsCJFrontendContext(context.get());
    auto frontendType = isCJFrontend ? FrontendType::DECLARATIVE_CJ : FrontendType::DECLARATIVE_JS;
    if (isDialog) {
        UErrorCode status = U_ZERO_ERROR;
        icu::Locale locale = icu::Locale::forLanguageTag(Global::I18n::LocaleConfig::GetSystemLanguage(), status);
        AceApplicationInfo::GetInstance().SetLocale(locale.getLanguage(), locale.getCountry(), locale.getScript(), "");
        container = AceType::MakeRefPtr<Platform::DialogContainer>(instanceId_, FrontendType::DECLARATIVE_JS);
        UpdateDialogResourceConfiguration(container, context);
    } else {
#ifdef NG_BUILD
        container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, frontendType,
            context, abilityInfo, std::make_unique<ContentEventCallback>([] {
                // Sub-window ,just return.
            }), false, true, true);
#else
        if (Container::IsCurrentUseNewPipeline()) {
            container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, frontendType,
                context, abilityInfo, std::make_unique<ContentEventCallback>([] {
                    // Sub-window ,just return.
                }), false, true, true);
        } else {
            container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, frontendType,
                context, abilityInfo, std::make_unique<ContentEventCallback>([] {
                    // Sub-window ,just return.
                }), false, true);
        }
#endif
    }
    if (context) {
        if (context->GetApplicationInfo()) {
            auto appInfo = context->GetApplicationInfo();
            container->SetApiTargetVersion(appInfo->apiTargetVersion);
        }

        container->SetBundlePath(context->GetBundleCodeDir());
        container->SetFilesDataPath(context->GetFilesDir());
    } else {
        // if window don't have context,like service eject a toast,find target version in bundle.
        auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
        CHECK_NULL_VOID(systemAbilityMgr);
        auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
        CHECK_NULL_VOID(bundleObj);
        auto bundleMgrProxy = iface_cast<AppExecFwk::IBundleMgr>(bundleObj);
        CHECK_NULL_VOID(bundleMgrProxy);
        AppExecFwk::BundleInfo bundleInfo;
        bundleMgrProxy->GetBundleInfoForSelf(
            static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_HAP_MODULE), bundleInfo);
        container->SetApiTargetVersion(bundleInfo.targetVersion % 1000);
    }
    container->InitFoldStatusFromListener();
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    touchOutsideListener_ = new TouchOutsideListener(instanceId_);
    window_->RegisterTouchOutsideListener(touchOutsideListener_);
    dragWindowListener_ = new DragWindowListener(instanceId_);
    window_->RegisterDragListener(dragWindowListener_);
    if (!container->IsSceneBoardEnabled()) {
        occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
        window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
    }
    foldStatusListener_ = new FoldScreenListener(instanceId_);
    waterfallModeChangeListener_ = new WaterfallModeChangeListener(instanceId_);
    window_->RegisterWaterfallModeChangeListener(waterfallModeChangeListener_);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterFoldStatusListener(foldStatusListener_);
    foldDisplayModeListener_ = new FoldDisplayModeListener(instanceId_, isDialog);
    OHOS::Rosen::DisplayManager::GetInstance().RegisterDisplayModeListener(foldDisplayModeListener_);

    auto isAppOrSystemWindow = window_->IsAppWindow() || window_->IsSystemWindow();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) && isAppOrSystemWindow) {
        avoidAreaChangedListener_ = new PretendChangedListener(instanceId_);
        window_->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
    }
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
    LOGI("[%{public}s][%{public}s][%{public}d]: SetFrameLayoutFinishCallback", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_);
}

void UIContentImpl::NotifyMemoryLevel(int32_t level)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: NotifyMemoryLevel: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, level);
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
    LOGI("[%{public}s][%{public}s][%{public}d]: setAppTitle", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    pipelineContext->SetAppTitle(title);
}

void UIContentImpl::SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    std::lock_guard<std::mutex> lock(setAppWindowIconMutex_);
    LOGI("[%{public}s][%{public}s][%{public}d]: setAppIcon", bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [container, pixelMap]() {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->SetAppIcon(AceType::MakeRefPtr<PixelMapOhos>(pixelMap));
    };

    // Cancel the pending task
    setAppWindowIconTask_.Cancel();
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        setAppWindowIconTask_ = SingleTaskExecutor::CancelableTask(std::move(task));
        taskExecutor->PostTask(setAppWindowIconTask_,
            TaskExecutor::TaskType::UI, "ArkUISetAppWindowIcon");
    }
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

void UIContentImpl::RegisterAccessibilityChildTree(
    uint32_t parentWindowId, int32_t parentTreeId, int64_t parentElementId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    auto accessibilityManager = front->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->RegisterInteractionOperationAsChildTree(parentWindowId, parentTreeId, parentElementId);
}

void UIContentImpl::SetAccessibilityGetParentRectHandler(std::function<void(int32_t&, int32_t&)>&& callback)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    auto accessibilityManager = front->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->SetAccessibilityGetParentRectHandler(std::move(callback));
}

void UIContentImpl::SetAccessibilityGetParentRectHandler(
    std::function<void(AccessibilityParentRectInfo&)>&& callback)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    auto accessibilityManager = front->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->SetAccessibilityGetParentRectHandler(std::move(callback));
}

void UIContentImpl::DeregisterAccessibilityChildTree()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    auto accessibilityManager = front->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterInteractionOperationAsChildTree();
}

void UIContentImpl::AccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->Dump(params, info);
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

void UIContentImpl::OnFormSurfaceChange(float width, float height, OHOS::Rosen::WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    int32_t formWidth = round(width);
    int32_t formHeight = round(height);
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
    Platform::AceViewOhos::ChangeViewSize(aceView, formWidth, formHeight);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    auto density = pipelineContext->GetDensity();
    pipelineContext->SetRootSize(density, formWidth, formHeight);
    pipelineContext->OnSurfaceChanged(formWidth, formHeight, static_cast<WindowSizeChangeReason>(type), rsTransaction);
}

void UIContentImpl::SetFormBackgroundColor(const std::string& color)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: SetFormBackgroundColor: %{public}s",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, color.c_str());
    if (!Rosen::RSSystemProperties::GetUniRenderEnabled()) {
        // cannot set transparent background effects in not-uniform-render mode
        return;
    }
    Color bgColor;
    if (!Color::ParseColorString(color, bgColor)) {
        return;
    }
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    if (aceContainer) {
        aceContainer->SetIsUseCustomBg(true);
    }
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, bgColor]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetAppBgColor(bgColor);
        },
        TaskExecutor::TaskType::UI, "ArkUISetFormBackgroundColor");
}

void UIContentImpl::SetFontScaleFollowSystem(const bool fontScaleFollowSystem)
{
    LOGD("SetFontScaleFollowSystem: %{public}d", fontScaleFollowSystem);
    fontScaleFollowSystem_ = fontScaleFollowSystem;
}

void UIContentImpl::SetFormRenderingMode(int8_t renderMode)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFormRenderingMode(renderMode);
}

void UIContentImpl::SetFormEnableBlurBackground(bool enableBlurBackground)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFormEnableBlurBackground(enableBlurBackground);
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIGetResourcePaths");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUISetResourcePaths");
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
            ContainerScope scope(container->GetInstanceId());
            pipelineContext->SetIsFocusActive(isFocusActive);
        },
        TaskExecutor::TaskType::UI, "ArkUISetIsFocusActive");
}

void UIContentImpl::UpdateResource()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([container]() { container->UpdateResource(); },
        TaskExecutor::TaskType::UI, "ArkUIUpdateResource");
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
        [container, &sessionId, want, callbacks = callbacks, config = config, window = window_,
            instanceId = instanceId_]() {
            auto flag = want.GetBoolParam(USE_GLOBAL_UICONTENT, false);
            if (flag && CreateGlobalModalUIExtension(want, sessionId, callbacks, config, instanceId, window)) {
                return;
            }

            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            sessionId = overlay->CreateModalUIExtension(want, callbacks, config);
        },
        TaskExecutor::TaskType::UI, "ArkUICreateModalUIExtension");
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "[%{public}s][%{public}s][%{public}d]: create modal page, "
        "sessionId=%{public}d, isProhibitBack=%{public}d, isAsyncModalBinding=%{public}d, "
        "isAllowedBeCovered=%{public}d, prohibitedRemoveByRouter=%{public}d, "
        "isAllowAddChildBelowModalUec=%{public}d, prohibitedRemoveByNavigation=%{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, sessionId, config.isProhibitBack,
        config.isAsyncModalBinding, config.isAllowedBeCovered, config.prohibitedRemoveByRouter,
        config.isAllowAddChildBelowModalUec, config.prohibitedRemoveByNavigation);
    return sessionId;
}

void UIContentImpl::CloseModalUIExtension(int32_t sessionId)
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "[%{public}s][%{public}s][%{public}d]: close modal page, "
        "sessionId=%{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, sessionId);
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
            if (CloseGlobalModalUIExtension(container->GetInstanceId(), sessionId, "")) {
                return;
            }

            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            overlay->CloseModalUIExtension(sessionId);
        },
        TaskExecutor::TaskType::UI, "ArkUICloseModalUIExtension");
}

void UIContentImpl::UpdateModalUIExtensionConfig(
    int32_t sessionId, const ModalUIExtensionAllowedUpdateConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "[%{public}s][%{public}s][%{public}d]: UpdateModalUIExtensionConfig with "
        "sessionId: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, sessionId);
    if (sessionId == 0) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExtension refuse to UpdateModalUIExtensionConfig");
        return;
    }

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, sessionId, config]() {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            overlay->UpdateModalUIExtensionConfig(sessionId, config);
        },
        TaskExecutor::TaskType::UI, "ArkUIUpdateModalUIExtensionConfig");
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
        TaskExecutor::TaskType::UI, "ArkUICheckNeedAutoSave");

    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UIContentImpl CheckNeedAutoSave, value is %{public}d", needAutoSave);
    return needAutoSave;
}

bool UIContentImpl::DumpViewData(AbilityBase::ViewData& viewData, AbilityBase::AutoFillType& type)
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
        TaskExecutor::TaskType::UI, "ArkUIDumpViewData");
    type = ViewDataWrap::ViewDataToType(viewData);
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UIContentImpl DumpViewData, ret is %{public}d", ret);
    return ret;
}

bool UIContentImpl::DumpViewData(const RefPtr<NG::FrameNode>& node, RefPtr<ViewDataWrap> viewDataWrap,
    bool skipSubAutoFillContainer, bool needsRecordData)
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
    return pipelineContext->DumpPageViewData(node, viewDataWrap, skipSubAutoFillContainer, needsRecordData);
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
            auto mgr = pipeline->GetFormVisibleManager();
            if (mgr) {
                mgr->HandleFormVisibleChangeEvent(isVisible);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionVisibleChange");
}

bool UIContentImpl::NotifyExecuteAction(
    int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    return container->NotifyExecuteAction(elementId, actionArguments, action, offset);
}

void UIContentImpl::HandleAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "HandleAccessibilityHoverEvent Point:[%{public}f, %{public}f] "
        "source:%{public}d type:%{public}d time:%{public}" PRId64,
        pointX, pointY, sourceType, eventType, timeMs);
    container->HandleAccessibilityHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
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

RefPtr<PopupParam> UIContentImpl::CreateCustomPopupParam(bool isShow, const CustomPopupUIExtensionConfig& config)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(isShow);
    popupParam->SetUseCustomComponent(true);
    popupParam->SetShowInSubWindow(config.isShowInSubWindow);
    popupParam->SetShadow(GetPopupShadow());
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

Shadow UIContentImpl::GetPopupShadow()
{
    Shadow shadow;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, shadow);
    auto colorMode = container->GetColorMode();
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, shadow);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, shadow);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, shadow);
    auto popupShadowStyle = popupTheme->GetPopupShadowStyle();
    return shadowTheme->GetShadow(popupShadowStyle, colorMode);
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
    customPopupConfigMap_.erase(nodeId);
    popupUIExtensionRecords_.erase(nodeId);
}

void UIContentImpl::SetCustomPopupConfig(int32_t nodeId, const CustomPopupUIExtensionConfig& config, int32_t popupId)
{
    customPopupConfigMap_[nodeId] = config;
    popupUIExtensionRecords_[nodeId] = popupId;
}

bool UIContentImpl::GetTargetNode(
    int32_t& nodeIdLabel, RefPtr<NG::FrameNode>& targetNode, const CustomPopupUIExtensionConfig& config)
{
    if (config.nodeId > -1) {
        nodeIdLabel = config.nodeId;
        targetNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(nodeIdLabel);
        CHECK_NULL_RETURN(targetNode, false);
    } else if (!config.inspectorId.empty()) {
        targetNode = NG::Inspector::GetFrameNodeByKey(config.inspectorId);
        CHECK_NULL_RETURN(targetNode, false);
        nodeIdLabel = targetNode->GetId();
    } else {
        CHECK_NULL_RETURN(targetNode, false);
    }
    return true;
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
            int32_t nodeIdLabel = -1;
            RefPtr<NG::FrameNode> targetNode = nullptr;
            if (!GetTargetNode(nodeIdLabel, targetNode, config)) {
                return;
            }
            if (customPopupConfigMap_.find(nodeIdLabel) != customPopupConfigMap_.end()) {
                LOGW("Nodeid=%{public}d has unclosed popup, cannot create new", nodeIdLabel);
                return;
            }
            auto popupParam = CreateCustomPopupParam(true, config);
            popupParam->SetBlockEvent(false);
            NG::InnerModalUIExtensionConfig innerModalUIExtensionConfig;
            innerModalUIExtensionConfig.isModal = false;
            auto uiExtNode = ModalUIExtension::Create(want, callbacks, innerModalUIExtensionConfig);
            auto focusHub = uiExtNode->GetFocusHub();
            if (focusHub) {
                focusHub->SetFocusable(config.isFocusable);
            }
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
            nodeId = nodeIdLabel;
            popupParam->SetOnStateChange([config, nodeId, UICONTENT_IMPL_HELPER(content)](const std::string& event) {
                UICONTENT_IMPL_HELPER_GUARD(content, return);
                UICONTENT_IMPL_PTR(content)->OnPopupStateChange(event, config, nodeId);
            });
            NG::ViewAbstract::BindPopup(popupParam, targetNode, AceType::DynamicCast<NG::UINode>(uiExtNode));
            SetCustomPopupConfig(nodeId, config, uiExtNode->GetId());
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionCreateCustomPopup");
    TAG_LOGI(
        AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Create custom popup with UIExtension end, nodeId=%{public}d", nodeId);
    return nodeId;
}

void UIContentImpl::DestroyCustomPopupUIExtension(int32_t nodeId)
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "[%{public}s][%{public}s][%{public}d]: Destroy custom popup start, nodeId=%{public}d", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, nodeId);
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
        [container, nodeId, config, UICONTENT_IMPL_HELPER(content)]() {
            UICONTENT_IMPL_HELPER_GUARD(content, return);
            auto targetNode =
                AceType::DynamicCast<NG::FrameNode>(ElementRegister::GetInstance()->GetUINodeById(nodeId));
            CHECK_NULL_VOID(targetNode);
            auto popupParam = UICONTENT_IMPL_PTR(content)->CreateCustomPopupParam(false, config);
            popupParam->SetBlockEvent(false);
            NG::ViewAbstract::BindPopup(popupParam, targetNode, nullptr);
            UICONTENT_IMPL_PTR(content)->customPopupConfigMap_.erase(nodeId);
            UICONTENT_IMPL_PTR(content)->popupUIExtensionRecords_.erase(nodeId);
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionDestroyCustomPopup");
}

void UIContentImpl::UpdateCustomPopupUIExtension(const CustomPopupUIExtensionConfig& config)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [config, this]() {
            int32_t targetId = config.nodeId;
            auto record = popupUIExtensionRecords_.find(targetId);
            int32_t uiExtNodeId = (record != popupUIExtensionRecords_.end()) ? record->second : 0;
            auto uiExtNode = NG::FrameNode::GetFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtNodeId);
            CHECK_NULL_VOID(uiExtNode);
            if (config.targetSize.has_value()) {
                auto layoutProperty = uiExtNode->GetLayoutProperty();
                CHECK_NULL_VOID(layoutProperty);
                PopupSize targetSize = config.targetSize.value();
                DimensionUnit unit = static_cast<DimensionUnit>(targetSize.unit);
                auto width = NG::CalcLength(targetSize.width, unit);
                auto height = NG::CalcLength(targetSize.height, unit);
                layoutProperty->UpdateUserDefinedIdealSize(NG::CalcSize(width, height));
            }
            auto popupParam = CreateCustomPopupParam(true, config);
            popupParam->SetIsCaretMode(false);
            popupParam->SetBlockEvent(false);
            auto popupConfig = customPopupConfigMap_.find(targetId);
            if (popupConfig != customPopupConfigMap_.end()) {
                auto createConfig = popupConfig->second;
                popupParam->SetShowInSubWindow(createConfig.isShowInSubWindow);
                popupParam->SetOnStateChange(
                    [createConfig, targetId, UICONTENT_IMPL_HELPER(content)](const std::string& event) {
                        UICONTENT_IMPL_HELPER_GUARD(content, return);
                        UICONTENT_IMPL_PTR(content)->OnPopupStateChange(event, createConfig, targetId);
                    });
            }
            auto targetNode =
                AceType::DynamicCast<NG::FrameNode>(ElementRegister::GetInstance()->GetUINodeById(targetId));
            CHECK_NULL_VOID(targetNode);
            NG::ViewAbstract::BindPopup(popupParam, targetNode, nullptr);
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionUpdateCustomPopup");
}

void UIContentImpl::SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [customTitleSettedShow, floatingTitleSettedShow]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetContainerModalTitleVisible(customTitleSettedShow, floatingTitleSettedShow);
    };
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, "ArkUISetContainerModalTitleVisible");
    }
}

bool UIContentImpl::GetContainerModalTitleVisible(bool isImmersive)
{
    ContainerScope scope(instanceId_);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return NG::ContainerModalViewEnhance::GetContainerModalTitleVisible(pipeline, isImmersive);
}

void UIContentImpl::SetContainerModalTitleHeight(int32_t height)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [height]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetContainerModalTitleHeight(height);
    };
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, "ArkUISetContainerModalTitleHeight");
    }
}

void UIContentImpl::SetContainerButtonStyle(const Rosen::DecorButtonStyle& buttonStyle)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    Ace::DecorButtonStyle decorButtonStyle;
    ConvertDecorButtonStyle(buttonStyle, decorButtonStyle);
    taskExecutor->PostTask(
        [container, decorButtonStyle]() {
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipelineContext);
            NG::ContainerModalViewEnhance::SetContainerButtonStyle(pipelineContext, decorButtonStyle);
        },
        TaskExecutor::TaskType::UI, "SetContainerButtonStyle");
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

void UIContentImpl::ChangeSensitiveNodes(bool isSensitive)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [pipeline, isSensitive]() { pipeline->ChangeSensitiveNodes(isSensitive); },
        TaskExecutor::TaskType::UI, "ArkUIChangeSensitiveNodes");
}

void UIContentImpl::UpdateTransform(const OHOS::Rosen::Transform& transform)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowScale = transform.scaleX_;
    taskExecutor->PostTask(
        [container, windowScale]() { container->SetWindowScale(windowScale); },
        TaskExecutor::TaskType::UI, "ArkUISetWindowScale");
}

void UIContentImpl::AddWatchSystemParameter()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    container->AddWatchSystemParameter();
}

std::vector<Ace::RectF> UIContentImpl::GetOverlayNodePositions() const
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    ContainerScope scope(instanceId_);
    CHECK_NULL_RETURN(container, {});
    return container->GetOverlayNodePositions();
}

void UIContentImpl::RegisterOverlayNodePositionsUpdateCallback(
    const std::function<void(std::vector<Ace::RectF>)>& callback) const
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(container);
    container->RegisterOverlayNodePositionsUpdateCallback(std::move(callback));
}

void UIContentImpl::SetContentNodeGrayScale(float grayscale)
{
    if (LessNotEqual(grayscale, 0.001f)) {
        grayscale = 0.0f;
    }
    if (GreatNotEqual(grayscale, 1.0)) {
        grayscale = 1.0f;
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto rootElement = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootElement);
    auto renderContext = rootElement->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateFrontGrayScale(Dimension(grayscale));
    pipelineContext->SetDragNodeGrayscale(grayscale);
}

void UIContentImpl::PreLayout()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [instanceId = instanceId_] {
            TAG_LOGI(AceLogTag::ACE_WINDOW, "PreLayoutBegin");
            auto container = Platform::AceContainer::GetContainer(instanceId);
            CHECK_NULL_VOID(container);
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipelineContext);
            auto stageManager = pipelineContext->GetStageManager();
            CHECK_NULL_VOID(stageManager);
            auto stageNode = stageManager->GetStageNode();
            CHECK_NULL_VOID(stageNode);
            auto renderContext = stageNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto paintRectf = renderContext->GetPaintRectWithoutTransform();
            if (LessOrEqual(static_cast<uint32_t>(paintRectf.Width()), 0) ||
                LessOrEqual(static_cast<uint32_t>(paintRectf.Height()), 0)) {
                TAG_LOGW(AceLogTag::ACE_WINDOW, "width:%{public}f, height:%{public}f", paintRectf.Width(),
                    paintRectf.Height());
                return;
            }
            pipelineContext->PreLayout(pipelineContext->GetTimeFromExternalTimer(), 0);
        },
        TaskExecutor::TaskType::UI, "ArkUIPreLayout");
    TAG_LOGI(AceLogTag::ACE_WINDOW, "ArkUIPreLayoutEnd");
}

void UIContentImpl::SetStatusBarItemColor(uint32_t color)
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto appBar = container->GetAppBar();
    CHECK_NULL_VOID(appBar);
    appBar->SetStatusBarItemColor(IsDarkColor(color));
}

void UIContentImpl::SetForceSplitEnable(bool isForceSplit, const std::string& homePage, bool isRouter)
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(context);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto forceSplitTask = [weakContext = WeakPtr(context), isForceSplit, homePage, isRouter]() {
        auto context = weakContext.Upgrade();
        CHECK_NULL_VOID(context);
        if (isRouter) {
            auto stageManager = context->GetStageManager();
            CHECK_NULL_VOID(stageManager);
            stageManager->SetForceSplitEnable(isForceSplit, homePage);
            return;
        }
        auto navManager = context->GetNavigationManager();
        CHECK_NULL_VOID(navManager);
        navManager->SetForceSplitEnable(isForceSplit, homePage);
    };
    if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        forceSplitTask();
        return;
    }
    taskExecutor->PostTask(std::move(forceSplitTask), TaskExecutor::TaskType::UI,
        isRouter ? "ArkUISetForceSplitEnable" : "ArkUISetNavigationForceSplitEnable");
}

void UIContentImpl::ProcessDestructCallbacks()
{
    std::shared_lock<std::shared_mutex> reportLock(destructMutex_);
    for (auto& [_, callback] : destructCallbacks_) {
        callback();
    }
}

void UIContentImpl::EnableContainerModalGesture(bool isEnable)
{
    LOGI("[%{public}s][%{public}s][%{public}d]: EnableContainerModalGesture: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, isEnable);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerWeak = AceType::WeakClaim(AceType::RawPtr(container)), isEnable]() {
            auto container = containerWeak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->EnableContainerModalGesture(isEnable);
        },
        TaskExecutor::TaskType::UI, "ArkUIEnableContainerModalGesture");
}

bool UIContentImpl::GetContainerFloatingTitleVisible()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: GetContainerFloatingTitleVisible",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->GetContainerFloatingTitleVisible();
}

bool UIContentImpl::GetContainerCustomTitleVisible()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: GetContainerCustomTitleVisible",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->GetContainerCustomTitleVisible();
}

bool UIContentImpl::GetContainerControlButtonVisible()
{
    LOGI("[%{public}s][%{public}s][%{public}d]: GetContainerControlButtonVisible",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->GetContainerControlButtonVisible();
}

void UIContentImpl::OnContainerModalEvent(const std::string& name, const std::string& value)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [name, value, instanceId = instanceId_]() {
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_VOID(container);
        auto pipelineBase = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineBase);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineBase);
        CHECK_NULL_VOID(pipeline);
        NG::ContainerModalViewEnhance::OnContainerModalEvent(pipeline, name, value);
    };
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, "ArkUIOnContainerModalEvent");
    }
}

void UIContentImpl::ExecuteUITask(std::function<void()> task, const std::string& name)
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
    if (uiTaskRunner.IsRunOnCurrentThread()) {
        task();
    } else {
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, name);
    }
}

void UIContentImpl::UpdateSingleHandTransform(const OHOS::Rosen::SingleHandTransform& transform)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_VOID(aceContainer);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [id = instanceId_, aceContainer, singleHandTransform = Platform::SingleHandTransform(transform.posX,
            transform.posY, transform.scaleX, transform.scaleY)]() {
            aceContainer->SetSingleHandTransform(singleHandTransform);
            auto context = NG::PipelineContext::GetContextByContainerId(id);
            CHECK_NULL_VOID(context);
            auto uiExtManager = context->GetUIExtensionManager();
            CHECK_NULL_VOID(uiExtManager);
            uiExtManager->TransferAccessibilityRectInfo();
        }, TaskExecutor::TaskType::UI, "ArkUISetSingleHandTransform");
}

bool UIContentImpl::ConfigCustomWindowMask(bool enable)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    return NG::ContainerModalView::ConfigCustomWindowMask(pipelineContext, enable);
}

bool UIContentImpl::GetWindowSizeChangeReason(OHOS::Rosen::WindowSizeChangeReason lastReason,
    OHOS::Rosen::WindowSizeChangeReason reason)
{
    bool reasonDragFlag = true;
    if (lastReason == OHOS::Rosen::WindowSizeChangeReason::DRAG_START &&
            reason == OHOS::Rosen::WindowSizeChangeReason::DRAG) {
        reasonDragFlag = false;
    }
    if (lastReason == OHOS::Rosen::WindowSizeChangeReason::DRAG &&
            reason == OHOS::Rosen::WindowSizeChangeReason::DRAG) {
        reasonDragFlag = false;
    }
    if (lastReason == OHOS::Rosen::WindowSizeChangeReason::DRAG &&
            reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_END) {
        reasonDragFlag = false;
    }
    if (lastReason == OHOS::Rosen::WindowSizeChangeReason::SPLIT_DRAG_START &&
            reason == OHOS::Rosen::WindowSizeChangeReason::SPLIT_DRAG) {
        reasonDragFlag = false;
    }
    if (lastReason == OHOS::Rosen::WindowSizeChangeReason::SPLIT_DRAG &&
            reason == OHOS::Rosen::WindowSizeChangeReason::SPLIT_DRAG) {
        reasonDragFlag = false;
    }
    if (lastReason == OHOS::Rosen::WindowSizeChangeReason::SPLIT_DRAG &&
            reason == OHOS::Rosen::WindowSizeChangeReason::SPLIT_DRAG_END) {
        reasonDragFlag = false;
    }
    return reasonDragFlag;
}

std::shared_ptr<Rosen::RSNode> UIContentImpl::GetRSNodeByStringID(const std::string& stringId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, nullptr);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, nullptr);
    std::shared_ptr<Rosen::RSNode> rsNode;
    taskExecutor->PostSyncTask(
        [id = instanceId_, &rsNode, stringId]() {
            ContainerScope scope(id);
            auto frameNode = NG::Inspector::GetFrameNodeByKey(stringId, true, true);
            CHECK_NULL_VOID(frameNode);
            auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
            CHECK_NULL_VOID(renderContext);
            rsNode = renderContext->GetRSNode();
        },
        TaskExecutor::TaskType::UI, "ArkUIGetRSNodeByStringID");
    if (!rsNode) {
        LOGE("Cannot find RSNode by stringId: %{public}s", stringId.c_str());
    }
    return rsNode;
}

void UIContentImpl::SetTopWindowBoundaryByID(const std::string& stringId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [id = instanceId_, stringId]() {
            ContainerScope scope(id);
            auto frameNode = NG::Inspector::GetFrameNodeByKey(stringId, true, true);
            CHECK_NULL_VOID(frameNode);
            frameNode->SetTopWindowBoundary(true);
        },
        TaskExecutor::TaskType::UI, "ArkUISetTopWindowBoundaryByID");
}

void sendCommandCallbackInner(RefPtr<PipelineBase> pipeline)
{
    auto sendCommandCallback = [weakContext = WeakPtr(pipeline)](int32_t value) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        CHECK_NULL_VOID(pipeline);
        KeyEvent keyEvent;
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = static_cast<KeyCode>(value);
        keyEvent.pressedCodes = { keyEvent.code };

        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weakContext = WeakPtr(pipeline), keyEvent]() {
                auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
                CHECK_NULL_VOID(pipeline);
                pipeline->OnNonPointerEvent(keyEvent);
            },
            TaskExecutor::TaskType::UI, "UiSessionSendCommandKeyCode");
    };
    UiSessionManager::GetInstance()->SaveSendCommandFunction(sendCommandCallback);
}

void UIContentImpl::InitUISessionManagerCallbacks(RefPtr<PipelineBase> pipeline)
{
    // set get inspector tree function for ui session manager
    auto callback = [weakContext = WeakPtr(pipeline)](bool onlyNeedVisible) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        if (pipeline == nullptr) {
            pipeline = NG::PipelineContext::GetCurrentContextSafely();
        }
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weakContext = WeakPtr(pipeline), onlyNeedVisible]() {
                auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
                CHECK_NULL_VOID(pipeline);
                ContainerScope scope(pipeline->GetInstanceId());
                if (onlyNeedVisible) {
                    pipeline->GetInspectorTree(true);
                } else {
                    pipeline->GetInspectorTree(false);
                    UiSessionManager::GetInstance()->WebTaskNumsChange(-1);
                }
            },
            TaskExecutor::TaskType::BACKGROUND, "UiSessionGetInspectorTree",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    };
    UiSessionManager::GetInstance()->SaveInspectorTreeFunction(callback);
    auto webCallback = [weakContext = WeakPtr(pipeline)](bool isRegister) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weakContext = WeakPtr(pipeline), isRegister]() {
                auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
                CHECK_NULL_VOID(pipeline);
                pipeline->NotifyAllWebPattern(isRegister);
            },
            TaskExecutor::TaskType::UI, "UiSessionRegisterWebPattern",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    };
    UiSessionManager::GetInstance()->SaveRegisterForWebFunction(webCallback);
    SetupGetPixelMapCallback(pipeline);
    RegisterGetCurrentPageName(pipeline);
    InitSendCommandFunctionsCallbacks(pipeline);
    sendCommandCallbackInner(pipeline);
    SaveGetCurrentInstanceId();
}

void UIContentImpl::SetupGetPixelMapCallback(RefPtr<PipelineBase> pipeline)
{
    auto getPixelMapCallback = [weakContext = WeakPtr(pipeline)]() {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weakContext = WeakPtr(pipeline)]() {
                auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
                CHECK_NULL_VOID(pipeline);
                pipeline->GetAllPixelMap();
            },
            TaskExecutor::TaskType::UI, "UiSessionGetPixelMap");
    };
    UiSessionManager::GetInstance()->SaveGetPixelMapFunction(getPixelMapCallback);
}

void UIContentImpl::SaveGetCurrentInstanceId()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        auto saveInstanceIdCallback = []() -> int32_t {
            auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_RETURN(pipeline, -1);
            return pipeline->GetInstanceId();
        };
        UiSessionManager::GetInstance()->SaveGetCurrentInstanceIdCallback(saveInstanceIdCallback);
    });
}

void UIContentImpl::RegisterGetCurrentPageName(const RefPtr<PipelineBase>& pipeline)
{
    auto getPageNameCallback = [weakContext = WeakPtr(pipeline)]() -> std::string {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        CHECK_NULL_RETURN(pipeline, "");
        return pipeline->GetCurrentPageNameCallback();
    };
    UiSessionManager::GetInstance()->RegisterPipeLineGetCurrentPageName(getPageNameCallback);
}

void UIContentImpl::InitSendCommandFunctionsCallbacks(RefPtr<PipelineBase> pipeline)
{
    auto sendCommandAsync = [weakContext = WeakPtr(pipeline)](int32_t id, const std::string& command) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        if (!pipeline) {
            LOGI("Pipeline context is null");
            return 10;
        }
        auto taskExecutor = pipeline->GetTaskExecutor();
        if (!taskExecutor) {
            LOGI("Task executor is null");
            return 11;
        }
        int32_t result = 12;
        taskExecutor->PostSyncTask(
            [id, command, &result]() {
                auto node = AceType::DynamicCast<NG::FrameNode>(ElementRegister::GetInstance()->GetUINodeById(id));
                if (!node) {
                    LOGI("UiSessionSendCommandAsyncPattern: Node is null for id: %{public}d", id);
                    result = 13;
                    return;
                }
                result = node->OnRecvCommand(command);
            },
            TaskExecutor::TaskType::UI, "UiSessionSendCommandAsyncPattern");
        return result;
    };
    UiSessionManager::GetInstance()->SaveForSendCommandAsyncFunction(sendCommandAsync);
    auto sendCommand = [weakContext = WeakPtr(pipeline)](int32_t id, const std::string& command) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(weakContext.Upgrade());
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [id, command]() {
                auto node = AceType::DynamicCast<NG::FrameNode>(ElementRegister::GetInstance()->GetUINodeById(id));
                if (!node) {
                    LOGI("UiSessionSendCommandPattern: Node is null for id: %{public}d", id);
                    return;
                }
                node->OnRecvCommand(command);
            },
            TaskExecutor::TaskType::UI, "UiSessionSendCommandPattern");
    };
    UiSessionManager::GetInstance()->SaveForSendCommandFunction(sendCommand);
}

bool UIContentImpl::SendUIExtProprty(uint32_t code, const AAFwk::Want& data, uint8_t subSystemId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, false);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    taskExecutor->PostTask(
        [instanceId = instanceId_, code, data, subSystemId]() {
            auto context = NG::PipelineContext::GetContextByContainerId(instanceId);
            CHECK_NULL_VOID(context);
            auto uiExtManager = context->GetUIExtensionManager();
            CHECK_NULL_VOID(uiExtManager);
            uiExtManager->UpdateWMSUIExtProperty(static_cast<Ace::NG::UIContentBusinessCode>(code),
                data, static_cast<Ace::NG::RSSubsystemId>(subSystemId));
        }, TaskExecutor::TaskType::UI, "ArkUISendUIExtProprty");
    return true;
}

bool UIContentImpl::SendUIExtProprtyByPersistentId(uint32_t code, const AAFwk::Want& data,
        const std::unordered_set<int32_t>& persistentIds, uint8_t subSystemId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    taskExecutor->PostTask(
        [instanceId = instanceId_, code, data, persistentIds, subSystemId]() {
            auto context = NG::PipelineContext::GetContextByContainerId(instanceId);
            CHECK_NULL_VOID(context);
            auto uiExtManager = context->GetUIExtensionManager();
            CHECK_NULL_VOID(uiExtManager);
            uiExtManager->UpdateWMSUIExtPropertyByPersistentId(static_cast<Ace::NG::UIContentBusinessCode>(code),
                data, persistentIds, static_cast<Ace::NG::RSSubsystemId>(subSystemId));
        }, TaskExecutor::TaskType::UI, "ArkUISendUIExtProprtyByPersistentId");
    return true;
}

void UIContentImpl::EnableContainerModalCustomGesture(bool enable)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, enable]() {
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipelineContext);
            NG::ContainerModalPattern::EnableContainerModalCustomGesture(pipelineContext, enable);
        },
        TaskExecutor::TaskType::UI, "EnableContainerModalCustomGesture");
}

void UIContentImpl::ChangeDisplayAvailableAreaListener(uint64_t displayId)
{
    if (listenedDisplayId_ != displayId && availableAreaChangedListener_) {
        auto& manager = Rosen::DisplayManager::GetInstance();
        manager.UnregisterAvailableAreaListener(availableAreaChangedListener_, listenedDisplayId_);
        listenedDisplayId_ = displayId;
        manager.RegisterAvailableAreaListener(availableAreaChangedListener_, listenedDisplayId_);
    }
}

void UIContentImpl::ConvertDecorButtonStyle(const Rosen::DecorButtonStyle& buttonStyle,
    Ace::DecorButtonStyle& decorButtonStyle)
{
    decorButtonStyle.buttonBackgroundCornerRadius = buttonStyle.buttonBackgroundCornerRadius;
    decorButtonStyle.buttonBackgroundSize = buttonStyle.buttonBackgroundSize;
    decorButtonStyle.buttonIconSize = buttonStyle.buttonIconSize;
    decorButtonStyle.closeButtonRightMargin = buttonStyle.closeButtonRightMargin;
    decorButtonStyle.colorMode = buttonStyle.colorMode;
    decorButtonStyle.spacingBetweenButtons = buttonStyle.spacingBetweenButtons;
}

void UIContentImpl::SetIntentParam(const std::string& intentInfoSerialized,
    const std::function<void()>&& loadPageCallback, bool isColdStart)
{
    if (!isColdStart) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId_);
        container->DistributeIntentInfo(intentInfoSerialized, false, std::move(loadPageCallback));
        container->RunIntentPage();
        return;
    }
    intentInfoSerialized_ = intentInfoSerialized;
    loadPageCallback_ = std::move(loadPageCallback);
}
} // namespace OHOS::Ace
