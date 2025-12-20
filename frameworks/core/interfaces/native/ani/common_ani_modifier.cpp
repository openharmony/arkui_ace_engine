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

#if !defined(PREVIEW)
#include "canvas_ani/ani_canvas.h"
#endif

#include "core/interfaces/native/implementation/render_node_peer_impl.h"
#include "common_ani_modifier.h"
#include "securec.h"
#include "ui/properties/color.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/event/touch_event.h"
#include "core/interfaces/native/implementation/axis_event_peer.h"
#include "core/interfaces/native/implementation/click_event_peer.h"
#include "core/interfaces/native/implementation/event_target_info_peer.h"
#include "core/interfaces/native/implementation/hover_event_peer.h"
#include "core/interfaces/native/implementation/mouse_event_peer.h"
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/interfaces/native/ani/ani_theme.h"
#include "core/interfaces/native/ani/ani_theme_module.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "core/interfaces/native/node/extension_custom_node.h"
#include "core/interfaces/native/node/theme_modifier.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "bridge/arkts_frontend/ani_context_module.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/interfaces/native/implementation/key_event_peer.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/common/window_free_container.h"
#include "frameworks/core/common/container_scope.h"
#include "frameworks/base/subwindow/subwindow_manager.h"
#include "core/components_ng/token_theme/token_colors.h"
#include "ui/base/geometry/ng/size_t.h"
#include <cstdint>
#include <memory>
#include <vector>
#include "core/common/ace_engine.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;

constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
const int32_t FLAG_DRAW_FRONT = 1;
const int32_t FLAG_DRAW_CONTENT = 1 << 1;
const int32_t FLAG_DRAW_BEHIND = 1 << 2;
const int32_t FLAG_DRAW_FOREGROUND = 1 << 3;
const int32_t FLAG_DRAW_OVERLAY = 1 << 4;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
} // namespace

static thread_local std::vector<int32_t> restoreInstanceIds_;
static const std::unordered_set<std::string> g_clickPreventDefPattern = { "RichEditor", "Hyperlink" };
static const std::unordered_set<std::string> g_touchPreventDefPattern = { "Hyperlink" };

ani_ref* GetHostContext(ArkUI_Int32 key)
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    if (context == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetHostContext-ani can not get current context.");
        return nullptr;
    }
    auto frontend = context->GetFrontend();
    if (frontend == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetHostContext-ani can not get current frontend.");
        return nullptr;
    }
    return frontend->GetHostContext();
}

void SetFrameRateRange(ani_env* env, ani_long peerPtr, ani_object value, ArkUI_Int32 type)
{
    NG::FrameNode* peer = reinterpret_cast<NG::FrameNode*>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto swiperPattern = peer->GetPattern();
    CHECK_NULL_VOID(swiperPattern);
    ani_double min;
    ani_double max;
    ani_double expect;
    if (ANI_OK != env->Object_GetPropertyByName_Double(value, "min", &min)) {
        TAG_LOGE(AceLogTag::ACE_SWIPER, "get expectedFrameRateRange min value failed.");
        return;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Double(value, "max", &max)) {
        TAG_LOGE(AceLogTag::ACE_SWIPER, "get expectedFrameRateRange max value failed.");
        return;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Double(value, "expected", &expect)) {
        TAG_LOGE(AceLogTag::ACE_SWIPER, "get expectedFrameRateRange expect value failed.");
        return;
    }
    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(min, max, expect);
    auto sceneType = static_cast<SwiperDynamicSyncSceneType>(type);
    swiperPattern->SetFrameRateRange(frameRateRange, sceneType);
}

void SyncInstanceId(ArkUI_Int32 instanceId)
{
    restoreInstanceIds_.emplace_back(ContainerScope::CurrentId());
    ContainerScope::UpdateCurrent(instanceId);
}

void RestoreInstanceId()
{
    if (restoreInstanceIds_.empty()) {
        ContainerScope::UpdateCurrent(-1);
        return;
    }
    ContainerScope::UpdateCurrent(restoreInstanceIds_.back());
    restoreInstanceIds_.pop_back();
}

void SetDrawCallback(ani_env* env, ani_long ptr, void* fnDrawCallbackFun)
{
    if (fnDrawCallbackFun == nullptr) {
        LOGE("Draw callback is undefined.");
        return;
    }
    auto* drawCallbackFuncPtr =
        static_cast<std::function<void(NG::DrawingContext& drawingContext)>*>(fnDrawCallbackFun);
    auto* renderNodePeer = reinterpret_cast<RenderNodePeer*>(ptr);
    CHECK_NULL_VOID(renderNodePeer);
    auto renderNode = renderNodePeer->GetFrameNode();
    auto pattern = renderNode->GetPattern<NG::RenderNodePattern>();
    if (pattern) {
        pattern->SetDrawCallback(std::move(*drawCallbackFuncPtr));
    }
}

void SetFrameNodeDrawCallback(ani_env* env, ani_long ptr, void* fnDrawCallbackFun)
{
    if (fnDrawCallbackFun == nullptr) {
        LOGE("Draw callback is undefined.");
        return;
    }
    auto* drawCallbackFuncPtr =
        static_cast<std::function<void(NG::DrawingContext & drawingContext)>*>(fnDrawCallbackFun);

    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NG::CustomFrameNodePattern>();
    if (pattern) {
        pattern->SetDrawCallback(std::move(*drawCallbackFuncPtr));
    }
}

ArkUI_Int32 GetCurrentInstanceId()
{
    return Container::CurrentIdSafely();
}

ArkUI_Int32 GetFocusedInstanceId()
{
    auto currentInstance = ContainerScope::RecentActiveId();
    if (currentInstance == -1) {
        currentInstance = ContainerScope::SingletonId();
    }
    if (currentInstance >= MIN_SUBCONTAINER_ID && currentInstance < MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = SubwindowManager::GetInstance()->GetParentContainerId(currentInstance);
    }
    return currentInstance;
}

ani_long BuilderProxyNodeConstruct(ArkUI_Int32 id)
{
    auto proxyNode = NG::FrameNode::GetOrCreateFrameNode(
        "BuilderProxyNode", id, []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(proxyNode, 0);
    auto stackLayoutAlgorithm = proxyNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(stackLayoutAlgorithm, 0);
    stackLayoutAlgorithm->UpdateAlignment(Alignment::TOP_LEFT);
    proxyNode->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(proxyNode));
}

ani_ref GetSharedLocalStorage()
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    if (context == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetSharedLocalStorage-ani can not get current context.");
        return nullptr;
    }
    auto frontend = context->GetFrontend();
    if (frontend == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetSharedLocalStorage-ani can not get current frontend.");
        return nullptr;
    }
    int32_t currentInstance = Container::CurrentIdSafely();
    auto storage = frontend->GetSharedStorage(currentInstance);
    if (storage) {
        return storage;
    }
    return nullptr;
}

void SetBackgroundImagePixelMap(ani_env* env, ArkUINodeHandle node, ani_ref pixelMapPtr, ArkUI_Int32 repeat)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pixelMapValue = reinterpret_cast<void*>(pixelMapPtr);
    CHECK_NULL_VOID(pixelMapValue);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapValue);
    CHECK_NULL_VOID(pixelMap);
    ViewAbstract::SetBackgroundImage(frameNode, ImageSourceInfo { pixelMap });
#endif
    auto arkRepeat = static_cast<OHOS::Ace::ImageRepeat>(repeat);
    if (arkRepeat >= OHOS::Ace::ImageRepeat::NO_REPEAT && arkRepeat <= OHOS::Ace::ImageRepeat::REPEAT) {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, arkRepeat);
    } else {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
    }
}

void SetCustomCallback(ani_long ptr, void* fnMeasure, void* fnLayout)
{
    auto customFuncExisted = false;
    auto customNode = AceType::MakeRefPtr<NG::ExtensionCustomNode>();
    if (fnMeasure != nullptr) {
        customFuncExisted = true;
        auto* fnMeasurePtr = static_cast<std::function<void(LayoutConstraintF & layoutConstraint)>*>(fnMeasure);
        customNode->SetMeasureCallback(*fnMeasurePtr);
    }
    if (fnLayout != nullptr) {
        customFuncExisted = true;
        auto* fnLayoutPtr = static_cast<std::function<void(OffsetF& position)>*>(fnLayout);
        customNode->SetLayoutCallback(*fnLayoutPtr);
    }
    if (!customFuncExisted) {
        return;
    }
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    frameNode->SetExtensionHandler(customNode);
}

ArkUI_Int32 RequireArkoalaNodeId(ArkUI_Int32 capacity)
{
    auto cursor = ElementRegister::GetInstance()->RequireArkoalaNodeId(capacity);
    return cursor;
}

ani_long GetNodePtrWithPeerPtr(ani_long peerPtr)
{
    RenderNodePeer* peer = reinterpret_cast<RenderNodePeer*>(peerPtr);
    CHECK_NULL_RETURN(peer, -1);
    RefPtr<FrameNode> node = peer->GetFrameNode();
    ani_long ret = reinterpret_cast<ani_long>(node.GetRawPtr());
    return ret;
}

ani_int GetNodeIdWithNodePtr(ani_long nodePtr)
{
    FrameNode* node = reinterpret_cast<FrameNode*>(nodePtr);
    CHECK_NULL_RETURN(node, -1);
    int32_t id = node->GetId();
    return id;
}

ani_int GetNodeIdWithPeerPtr(ani_long ptr)
{
    RenderNodePeer* peer = reinterpret_cast<RenderNodePeer*>(ptr);
    CHECK_NULL_RETURN(peer, -1);
    RefPtr<FrameNode> node = peer->GetFrameNode();
    int32_t id = node->GetId();
    return id;
}
ani_long CreateRenderNodePeerWithNodePtr(ani_long ptr)
{
    FrameNode* node = reinterpret_cast<FrameNode*>(ptr);
    auto nodePtr = AceType::Claim(node);
    auto peerPtr = PeerUtils::CreatePeer<RenderNodePeer>(nodePtr);
    ani_long ret = reinterpret_cast<ani_long>(peerPtr);
    return ret;
}

ani_int CreateWindowFreeContainer(ani_env *env, std::shared_ptr<OHOS::AbilityRuntime::Context> nativeContext)
{
    auto container = Platform::WindowFreeContainer::CreateWindowFreeContainer(env,
        &nativeContext, FrontendType::ARK_TS);
    CHECK_NULL_RETURN(container, -1);
    int32_t instanceId = container->GetInstanceId();
    ContainerScope::Add(instanceId);
    return instanceId;
}

void DestroyWindowFreeContainer(ani_int id)
{
    Platform::WindowFreeContainer::DestroyWindowFreeContainer();
    ContainerScope::RemoveAndCheck(static_cast<int32_t>(id));
}

ani_boolean CheckIsUIThread(ArkUI_Int32 instanceId)
{
    SyncInstanceId(instanceId);
    bool res = CheckThread(TaskExecutor::TaskType::UI);
    RestoreInstanceId();
    return res;
}

ani_boolean IsDebugMode(ArkUI_Int32 instanceId)
{
    SyncInstanceId(instanceId);
    auto& aceApplicationInfo = AceApplicationInfo::GetInstance();
    bool res = aceApplicationInfo.IsDebugForParallel();
    RestoreInstanceId();
    return res;
}

void OnMeasureInnerMeasure(ani_long ptr)
{
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_VOID(frameNode);
    auto layoutAlgorithm = frameNode->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithm);
    auto size = layoutAlgorithm->MeasureContent(frameNode->GetLayoutProperty()->CreateContentConstraint(),
        AceType::RawPtr(frameNode));
    if (size.has_value()) {
        frameNode->GetGeometryNode()->SetContentSize(size.value());
    }
    layoutAlgorithm->Measure(AceType::RawPtr(frameNode));
}

void OnLayoutInnerLayout(ani_long ptr)
{
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_VOID(frameNode);
    auto layoutAlgorithm = frameNode->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithm);
    layoutAlgorithm->Layout(AceType::RawPtr(frameNode));
}

void SetParallelScoped(ani_boolean parallel)
{
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(parallel);
    MultiThreadBuildManager::SetIsParallelizeUI(parallel);
}

static void SetCustomPropertyCallBack(ArkUINodeHandle node, std::function<void()>&& func,
    std::function<std::string(const std::string&)>&& getFunc,
    std::function<std::string()>&& getAllCustomPropertiesFunc)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    ContainerScope scope(id);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("SetCustomPropertyCallBack doesn't run on UI thread");
    }
    auto frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetCustomPropertyCallback(std::move(func), std::move(getFunc), std::move(getAllCustomPropertiesFunc));
}

static std::optional<std::string> GetCustomProperty(ani_env* env, ArkUINodeHandle node, const std::string& key)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    ContainerScope scope(id);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("GetCustomProperty doesn't run on UI thread");
    }
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(node);
    CHECK_NULL_RETURN(frameNodePeer, std::nullopt);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_RETURN(frameNode, std::nullopt);

    std::string capiCustomProperty;
    if (frameNode->GetCapiCustomProperty(key, capiCustomProperty)) {
        return capiCustomProperty;
    } else {
        return std::nullopt;
    }
}

Alignment ParseAlignment(int32_t align)
{
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case NUM_0:
            alignment = Alignment::TOP_LEFT;
            break;
        case NUM_1:
            alignment = Alignment::TOP_CENTER;
            break;
        case NUM_2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case NUM_3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case NUM_4:
            alignment = Alignment::CENTER;
            break;
        case NUM_5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case NUM_6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case NUM_7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case NUM_8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            break;
    }
    return alignment;
}

void SetOverlayComponent(ani_long node, ani_long builderPtr, AniOverlayOptions options)
{
    CHECK_NULL_VOID(node);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(node);
    FrameNodePeer* overlayNodePeer = builderPtr ? reinterpret_cast<FrameNodePeer*>(builderPtr) : nullptr;
    RefPtr<NG::FrameNode> overlayNode = FrameNodePeer::GetFrameNodeByPeer(overlayNodePeer);
    CalcDimension x(options.x, DimensionUnit::VP);
    CalcDimension y(options.y, DimensionUnit::VP);
    Alignment align = ParseAlignment(options.alignment);
    ViewAbstract::SetOverlayBuilder(frameNode, overlayNode, align, x, y);
}

ani_double Vp2px(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    ContainerScope cope(instanceId);
    double density = PipelineBase::GetCurrentDensity();
    return value * density;
}

ani_double Px2vp(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    ContainerScope cope(instanceId);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return 0;
    }
    return value / density;
}

ani_double Fp2px(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    ContainerScope cope(instanceId);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return 0;
    }
    double fontScale = 1.0;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, 0);
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    return  value * density * fontScale;
}

ani_double Px2fp(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    ContainerScope cope(instanceId);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return 0;
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, 0);
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double ratio = density * fontScale;
    double fpValue = value / ratio;
    return fpValue;
}

ani_double Lpx2px(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    ContainerScope cope(instanceId);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return 0;
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, 0);
    auto pipelineContext = container->GetPipelineContext();
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, 0);
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, 0);
    auto windowConfig = frontend->GetWindowConfig();
    if (pipelineContext && pipelineContext->IsContainerModalVisible()) {
        int32_t multiplier = 2;
        width -= multiplier * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
    }
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }
    return value * windowConfig.designWidthScale;
}

ani_double Px2lpx(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    ContainerScope cope(instanceId);
    CHECK_NULL_RETURN(value, 0);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, 0);
    auto pipelineContext = container->GetPipelineContext();
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, 0);
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, 0);
    auto windowConfig = frontend->GetWindowConfig();
    if (pipelineContext && pipelineContext->IsContainerModalVisible()) {
        int32_t multiplier = 2;
        width -= multiplier * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
    }
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }
    return value / windowConfig.designWidthScale;
}

std::optional<std::string> GetWindowName(ani_int instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    ContainerScope scope(instanceId);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, std::nullopt);
    auto window = context->GetWindow();
    CHECK_NULL_RETURN(window, std::nullopt);
    std::string windowName = window->GetWindowName();
    return windowName;
}

std::optional<uint32_t> GetWindowId(ani_int instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, std::nullopt);
    ContainerScope scope(instanceId);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, std::nullopt);
    return context->GetFocusWindowId();
}

ani_int GetWindowWidthBreakpoint()
{
    return ViewAbstract::GetWindowWidthBreakpoint();
}

ani_int GetWindowHeightBreakpoint()
{
    return ViewAbstract::GetWindowHeightBreakpoint();
}

void* TransferKeyEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto accessor = reinterpret_cast<Ark_KeyEvent>(nativePtr);
    CHECK_NULL_RETURN(accessor, nullptr);
    auto nativePointer = reinterpret_cast<void*>(accessor->GetEventInfo());
    return reinterpret_cast<void*>(nativePointer);
}

void* CreateKeyEventAccessorWithPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = KeyEventPeer::Create(reinterpret_cast<void*>(nativePtr));
    return reinterpret_cast<void*>(peer);
}

void* CreateEventTargetInfoAccessor()
{
    auto peer = EventTargetInfoPeer::Create();
    return reinterpret_cast<void*>(peer);
}

void EventTargetInfoAccessorWithId(ani_env* env, ani_long input, const std::string& id)
{
    CHECK_NULL_VOID(input);
    auto accessor = reinterpret_cast<Ark_EventTargetInfo>(input);
    CHECK_NULL_VOID(accessor);
    accessor->id = id;
}

void* CreateScrollableTargetInfoAccessor()
{
    auto peer = ScrollableTargetInfoPeer::Create();
    return reinterpret_cast<void*>(peer);
}

void ScrollableTargetInfoAccessorWithId(ani_env* env, ani_long input, const std::string& id)
{
    CHECK_NULL_VOID(input);
    auto accessor = reinterpret_cast<Ark_EventTargetInfo>(input);
    CHECK_NULL_VOID(accessor);
    accessor->id = id;
}

void ScrollableTargetInfoAccessorWithPointer(ani_long input, ani_long nativePtr)
{
    CHECK_NULL_VOID(input);
    auto accessor = reinterpret_cast<Ark_ScrollableTargetInfo>(input);
    CHECK_NULL_VOID(accessor);
    auto pattern = reinterpret_cast<OHOS::Ace::NG::Pattern*>(nativePtr);
    CHECK_NULL_VOID(pattern);
    accessor->SetPattern(AceType::WeakClaim(pattern));
}

void* TransferScrollableTargetInfoPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto accessor = reinterpret_cast<Ark_ScrollableTargetInfo>(nativePtr);
    CHECK_NULL_RETURN(accessor, nullptr);
    auto pattern = accessor->GetPattern();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto nativePointer = reinterpret_cast<void*>(AceType::RawPtr(pattern));
    return reinterpret_cast<void*>(nativePointer);
}

void* CreateDragEventAccessor(ani_long ptr)
{
    CHECK_NULL_RETURN(ptr, 0);
    auto weak = OHOS::Ace::AceType::WeakClaim(reinterpret_cast<OHOS::Ace::DragEvent*>(ptr));
    auto dragEvent = weak.Upgrade();
    CHECK_NULL_RETURN(dragEvent, 0);
    auto peer = DragEventPeer::Create(dragEvent);
    return reinterpret_cast<void*>(peer);
}

void* GetDragEventPointer(ani_long ptr)
{
    CHECK_NULL_RETURN(ptr, 0);
    auto peer = reinterpret_cast<DragEventPeer*>(ptr);
    CHECK_NULL_RETURN(peer, 0);
    auto dragInfo = peer->dragInfo;
    CHECK_NULL_RETURN(dragInfo, 0);
    return reinterpret_cast<void*>(AceType::RawPtr(dragInfo));
}

void* TransferTouchEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = TouchEventPeer::Create(reinterpret_cast<void*>(nativePtr));
    return reinterpret_cast<void*>(peer);
}

void* TransferMouseEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = MouseEventPeer::Create(reinterpret_cast<void*>(nativePtr));
    return reinterpret_cast<void*>(peer);
}

void* TransferAxisEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = AxisEventPeer::Create(reinterpret_cast<void*>(nativePtr));
    return reinterpret_cast<void*>(peer);
}

void* TransferClickEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = ClickEventPeer::Create(reinterpret_cast<void*>(nativePtr));
    return reinterpret_cast<void*>(peer);
}

void* TransferHoverEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = HoverEventPeer::Create(reinterpret_cast<void*>(nativePtr));
    return reinterpret_cast<void*>(peer);
}

void* GetTouchEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = reinterpret_cast<Ark_TouchEvent>(nativePtr);
    return reinterpret_cast<void*>(peer->GetEventInfo());
}

void* GetMouseEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = reinterpret_cast<Ark_MouseEvent>(nativePtr);
    return reinterpret_cast<void*>(peer->GetEventInfo());
}

void* GetAxisEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = reinterpret_cast<Ark_AxisEvent>(nativePtr);
    return reinterpret_cast<void*>(peer->GetEventInfo());
}

void* GetClickEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = reinterpret_cast<Ark_ClickEvent>(nativePtr);
    return reinterpret_cast<void*>(peer->GetEventInfo());
}

void* GetHoverEventPointer(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto peer = reinterpret_cast<Ark_HoverEvent>(nativePtr);
    return reinterpret_cast<void*>(peer->GetEventInfo());
}

void FrameNodeMarkDirtyNode(ani_env* env, ani_long ptr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_DIFF);
}

ArkUI_Uint32 GetColorValueByString(const std::string& src)
{
    Color color;
    Color::ParseColorString(src, color);
    return color.GetValue();
}

ArkUI_Uint32 GetColorValueByNumber(ArkUI_Uint32 src)
{
    Color color(ColorAlphaAdapt(src));
    return color.GetValue();
}

void SendThemeToNative(ani_env* env, const std::vector<Ark_ResourceColor>& colorArray, ani_int id)
{
    auto colors = AceType::MakeRefPtr<AniThemeColors>();
    colors->SetColors(colorArray);

    auto themeScopeId = static_cast<int32_t>(id);

    AniTheme aniTheme;
    aniTheme.SetColors(colors);
    AniThemeScope::AddAniTheme(themeScopeId, aniTheme);

    // save the current theme when Theme was created by WithTheme container
    if (AniThemeScope::isCurrentThemeDefault || themeScopeId > 0) {
        std::optional<NG::AniTheme> themeOpt = std::make_optional(AniThemeScope::GetAniTheme(themeScopeId));
        AniThemeScope::aniCurrentTheme.swap(themeOpt);
    }
}

void RemoveThemeInNative(ani_env* env, ani_int withThemeId)
{
    auto themeScopeId = static_cast<int32_t>(withThemeId);
    AniThemeScope::RemoveAniTheme(themeScopeId);
}

void SetDefaultTheme(ani_env* env, const std::vector<Ark_ResourceColor>& colorArray, ani_boolean isDark)
{
    auto isDarkValue = static_cast<bool>(isDark);
    std::vector<uint32_t> colors;
    std::vector<RefPtr<ResourceObject>> resObjs;
    AniThemeModule::ConvertToColorArray(colorArray, colors, resObjs);
    NodeModifier::GetThemeModifier()->setDefaultTheme(colors.data(), isDarkValue, static_cast<void*>(&resObjs));
}

void UpdateColorMode(ani_int colorMode)
{
    auto colorModeValue = static_cast<int32_t>(colorMode);
    AniThemeModule::UpdateColorMode(colorModeValue);
}

void RestoreColorMode()
{
    AniThemeModule::RestoreColorMode();
}

void SetThemeScopeId(ani_env* env, ani_int themeScopeId)
{
    auto scopeId = static_cast<int32_t>(themeScopeId);
    AniThemeScope::isCurrentThemeDefault = scopeId == 0;

    std::optional<AniTheme> themeOpt = AniThemeScope::IsAniThemeExists(scopeId)
                                           ? std::make_optional(AniThemeScope::GetAniTheme(scopeId))
                                           : std::nullopt;

    AniThemeScope::aniCurrentTheme.swap(themeOpt);
}

void CreateAndBindTheme(ani_env* env, ani_int themeScopeId, ani_int themeId,
    const std::vector<Ark_ResourceColor>& colorArray, ani_int colorMode, void* func)
{
    int32_t colorModeValue = static_cast<int32_t>(colorMode);

    std::vector<uint32_t> colors;
    std::vector<RefPtr<ResourceObject>> resObjs;
    AniThemeModule::ConvertToColorArray(colorArray, colors, resObjs);

    if (!func) {
        return;
    }
    auto themeModifier = NodeModifier::GetThemeModifier();
    auto theme = themeModifier->createTheme(themeId, colors.data(), colors.data(), colorModeValue,
        static_cast<void*>(&resObjs), static_cast<void*>(&resObjs));
    CHECK_NULL_VOID(theme);
    ArkUINodeHandle node = themeModifier->getWithThemeNode(themeScopeId);
    if (!node) {
        node = AniThemeModule::CreateWithThemeNode(themeScopeId);
    }
    themeModifier->createThemeScope(node, theme);
    themeModifier->setOnThemeScopeDestroy(node, func);
}

void ApplyParentThemeScopeId(ani_env* env, ani_long self, ani_long parent)
{
    auto* selfPtr = reinterpret_cast<UINode*>(self);
    auto* parentPtr = reinterpret_cast<UINode*>(parent);
    if (!selfPtr || !parentPtr) {
        return;
    }
    int32_t elementThemeScopeId = selfPtr->GetThemeScopeId();
    if (parentPtr && elementThemeScopeId == 0) {
        int32_t themeScopeId = parentPtr->GetThemeScopeId();
        if (elementThemeScopeId != themeScopeId) {
            selfPtr->SetThemeScopeId(themeScopeId);
        }
    }
}

float GetPx2VpWithCurrentDensity(float px)
{
    return PipelineBase::Px2VpWithCurrentDensity(px);
}

void SetImageCacheCount(ani_int value, ani_int instanceId)
{
    int32_t count = static_cast<int32_t>(value);
    if (count < 0) {
        return;
    }
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto imageCache = pipelineContext->GetImageCache();
    imageCache->SetCapacity(count);
}

void SetImageRawDataCacheSize(ani_int value, ani_int instanceId)
{
    int32_t cacheSize = static_cast<int32_t>(value);
    if (cacheSize < 0) {
        return;
    }
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto imageCache = pipelineContext->GetImageCache();
    imageCache->SetDataCacheLimit(cacheSize);
}

void ApplyThemeScopeId(ani_env* env, ani_long ptr, ani_int themeScopeId)
{
    auto* selfPtr = reinterpret_cast<UINode*>(ptr);
    if (selfPtr) {
        selfPtr->SetThemeScopeId(themeScopeId);
    }
}

template<typename T>
void GetPressedModifierKey(ani_long nativePtr, char*** keys, ani_int* length)
{
    CHECK_NULL_VOID(nativePtr);
    auto accessor = reinterpret_cast<T>(nativePtr);
    CHECK_NULL_VOID(accessor && accessor->GetBaseInfo());
    CHECK_NULL_VOID(keys && length);
    auto eventKeys = accessor->GetBaseInfo()->GetPressedKeyCodes();
    auto size = static_cast<int32_t>(eventKeys.size());
    if (size <= 0) {
        return;
    }
    *length = size;
    *keys = new char* [size];
    for (auto index = 0; index < size; index++) {
        std::string keyStr;
        switch (eventKeys[index]) {
            case KeyCode::KEY_CTRL_LEFT:
            case KeyCode::KEY_CTRL_RIGHT:
                keyStr = "ctrl";
                break;
            case KeyCode::KEY_SHIFT_LEFT:
            case KeyCode::KEY_SHIFT_RIGHT:
                keyStr = "shift";
                break;
            case KeyCode::KEY_ALT_LEFT:
            case KeyCode::KEY_ALT_RIGHT:
                keyStr = "alt";
                break;
            case KeyCode::KEY_FN:
                keyStr = "fn";
                break;
            default:
                keyStr = "";
                break;
        }
        (*keys)[index] = new char[keyStr.length() + 1];
        auto result = strcpy_s((*keys)[index], keyStr.length() + 1, keyStr.c_str());
        if (result != 0) {
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "GetPressedModifierKey error: strcpy_s with error code: %d", result);
            for (auto i = 0; i <= index; i++) {
                delete[](*keys)[i];
            }
            delete[] * keys;
            *keys = nullptr;
            *length = 0;
            return;
        }
    }
}

void GetBaseEventPressedModifierKey(ani_long nativePtr, char*** keys, ani_int* length)
{
    GetPressedModifierKey<Ark_BaseEvent>(nativePtr, keys, length);
}

void GetKeyEventPressedModifierKey(ani_long nativePtr, char*** keys, ani_int* length)
{
    GetPressedModifierKey<Ark_KeyEvent>(nativePtr, keys, length);
}

ani_boolean SetClickEventPreventDefault(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, true);
    auto accessor = reinterpret_cast<Ark_ClickEvent>(nativePtr);
    CHECK_NULL_RETURN(accessor && accessor->GetBaseInfo(), true);
    auto eventInfo = accessor->GetBaseInfo();
    CHECK_NULL_RETURN(eventInfo, true);
    auto patternName = eventInfo->GetPatternName();
    if (g_clickPreventDefPattern.find(patternName.c_str()) == g_clickPreventDefPattern.end()) {
        return false;
    }
    eventInfo->SetPreventDefault(true);
    return true;
}

ani_boolean SetTouchEventPreventDefault(ani_long nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, true);
    auto accessor = reinterpret_cast<Ark_TouchEvent>(nativePtr);
    CHECK_NULL_RETURN(accessor && accessor->GetBaseInfo(), true);
    auto eventInfo = accessor->GetBaseInfo();
    CHECK_NULL_RETURN(eventInfo, true);
    auto patternName = eventInfo->GetPatternName();
    if (g_touchPreventDefPattern.find(patternName.c_str()) == g_touchPreventDefPattern.end()) {
        return false;
    }
    eventInfo->SetPreventDefault(true);
    return true;
}

void ResolveUIContext(std::vector<int32_t>& instnace)
{
    auto currnetId = ContainerScope::CurrentIdWithReason();
    instnace.push_back(currnetId.first);
    instnace.push_back(static_cast<int32_t>(currnetId.second));
}

const ArkUIAniCommonModifier* GetCommonAniModifier()
{
    static const ArkUIAniCommonModifier impl = {
        .getHostContext = OHOS::Ace::NG::GetHostContext,
        .setFrameRateRange = OHOS::Ace::NG::SetFrameRateRange,
        .syncInstanceId = OHOS::Ace::NG::SyncInstanceId,
        .restoreInstanceId = OHOS::Ace::NG::RestoreInstanceId,
        .setDrawCallback = OHOS::Ace::NG::SetDrawCallback,
        .setFrameNodeDrawCallback = OHOS::Ace::NG::SetFrameNodeDrawCallback,
        .getCurrentInstanceId = OHOS::Ace::NG::GetCurrentInstanceId,
        .getFocusedInstanceId = OHOS::Ace::NG::GetFocusedInstanceId,
        .builderProxyNodeConstruct = OHOS::Ace::NG::BuilderProxyNodeConstruct,
        .getSharedLocalStorage = OHOS::Ace::NG::GetSharedLocalStorage,
        .setBackgroundImagePixelMap = OHOS::Ace::NG::SetBackgroundImagePixelMap,
        .setCustomCallback = OHOS::Ace::NG::SetCustomCallback,
        .requireArkoalaNodeId = OHOS::Ace::NG::RequireArkoalaNodeId,
        .getNodePtrWithPeerPtr = OHOS::Ace::NG::GetNodePtrWithPeerPtr,
        .getNodeIdWithNodePtr = OHOS::Ace::NG::GetNodeIdWithNodePtr,
        .getNodeIdWithPeerPtr = OHOS::Ace::NG::GetNodeIdWithPeerPtr,
        .createRenderNodePeerWithNodePtr = OHOS::Ace::NG::CreateRenderNodePeerWithNodePtr,
        .createWindowFreeContainer = OHOS::Ace::NG::CreateWindowFreeContainer,
        .destroyWindowFreeContainer = OHOS::Ace::NG::DestroyWindowFreeContainer,
        .checkIsUIThread = OHOS::Ace::NG::CheckIsUIThread,
        .isDebugMode =  OHOS::Ace::NG::IsDebugMode,
        .onMeasureInnerMeasure = OHOS::Ace::NG::OnMeasureInnerMeasure,
        .onLayoutInnerLayout = OHOS::Ace::NG::OnLayoutInnerLayout,
        .setParallelScoped = OHOS::Ace::NG::SetParallelScoped,
        .setCustomPropertyCallBack = OHOS::Ace::NG::SetCustomPropertyCallBack,
        .getCustomProperty = OHOS::Ace::NG::GetCustomProperty,
        .setOverlayComponent = OHOS::Ace::NG::SetOverlayComponent,
        .vp2px = OHOS::Ace::NG::Vp2px,
        .px2vp = OHOS::Ace::NG::Px2vp,
        .fp2px = OHOS::Ace::NG::Fp2px,
        .px2fp = OHOS::Ace::NG::Px2fp,
        .lpx2px = OHOS::Ace::NG::Lpx2px,
        .px2lpx = OHOS::Ace::NG::Px2lpx,
        .getWindowName = OHOS::Ace::NG::GetWindowName,
        .getWindowId = OHOS::Ace::NG::GetWindowId,
        .getWindowHeightBreakpoint = OHOS::Ace::NG::GetWindowHeightBreakpoint,
        .getWindowWidthBreakpoint = OHOS::Ace::NG::GetWindowWidthBreakpoint,
        .transferKeyEventPointer = OHOS::Ace::NG::TransferKeyEventPointer,
        .createKeyEventAccessorWithPointer = OHOS::Ace::NG::CreateKeyEventAccessorWithPointer,
        .createEventTargetInfoAccessor = OHOS::Ace::NG::CreateEventTargetInfoAccessor,
        .eventTargetInfoAccessorWithId = OHOS::Ace::NG::EventTargetInfoAccessorWithId,
        .createScrollableTargetInfoAccessor = OHOS::Ace::NG::CreateScrollableTargetInfoAccessor,
        .scrollableTargetInfoAccessorWithId = OHOS::Ace::NG::ScrollableTargetInfoAccessorWithId,
        .scrollableTargetInfoAccessorWithPointer = OHOS::Ace::NG::ScrollableTargetInfoAccessorWithPointer,
        .transferScrollableTargetInfoPointer = OHOS::Ace::NG::TransferScrollableTargetInfoPointer,
        .createDragEventAccessor = OHOS::Ace::NG::CreateDragEventAccessor,
        .getDragEventPointer = OHOS::Ace::NG::GetDragEventPointer,
        .transferTouchEventPointer = OHOS::Ace::NG::TransferTouchEventPointer,
        .transferMouseEventPointer = OHOS::Ace::NG::TransferMouseEventPointer,
        .transferAxisEventPointer = OHOS::Ace::NG::TransferAxisEventPointer,
        .transferClickEventPointer = OHOS::Ace::NG::TransferClickEventPointer,
        .transferHoverEventPointer = OHOS::Ace::NG::TransferHoverEventPointer,
        .getTouchEventPointer = OHOS::Ace::NG::GetTouchEventPointer,
        .getMouseEventPointer = OHOS::Ace::NG::GetMouseEventPointer,
        .getAxisEventPointer = OHOS::Ace::NG::GetAxisEventPointer,
        .getClickEventPointer = OHOS::Ace::NG::GetClickEventPointer,
        .getHoverEventPointer = OHOS::Ace::NG::GetHoverEventPointer,
        .frameNodeMarkDirtyNode = OHOS::Ace::NG::FrameNodeMarkDirtyNode,
        .getColorValueByString = OHOS::Ace::NG::GetColorValueByString,
        .getColorValueByNumber = OHOS::Ace::NG::GetColorValueByNumber,
        .sendThemeToNative = OHOS::Ace::NG::SendThemeToNative,
        .removeThemeInNative = OHOS::Ace::NG::RemoveThemeInNative,
        .setDefaultTheme = OHOS::Ace::NG::SetDefaultTheme,
        .updateColorMode = OHOS::Ace::NG::UpdateColorMode,
        .restoreColorMode = OHOS::Ace::NG::RestoreColorMode,
        .setThemeScopeId = OHOS::Ace::NG::SetThemeScopeId,
        .createAndBindTheme = OHOS::Ace::NG::CreateAndBindTheme,
        .applyParentThemeScopeId = OHOS::Ace::NG::ApplyParentThemeScopeId,
        .getPx2VpWithCurrentDensity = OHOS::Ace::NG::GetPx2VpWithCurrentDensity,
        .setImageCacheCount = OHOS::Ace::NG::SetImageCacheCount,
        .setImageRawDataCacheSize = OHOS::Ace::NG::SetImageRawDataCacheSize,
        .applyThemeScopeId = OHOS::Ace::NG::ApplyThemeScopeId,
        .getBaseEventPressedModifierKey = OHOS::Ace::NG::GetBaseEventPressedModifierKey,
        .getKeyEventPressedModifierKey = OHOS::Ace::NG::GetKeyEventPressedModifierKey,
        .setClickEventPreventDefault = OHOS::Ace::NG::SetClickEventPreventDefault,
        .setTouchEventPreventDefault = OHOS::Ace::NG::SetTouchEventPreventDefault,
        .resolveUIContext = OHOS::Ace::NG::ResolveUIContext
    };
    return &impl;
}

void SetDrawModifier(ani_long ptr, uint32_t flag, void* fnDrawBehindFun, void* fnDrawContentFun, void* fnDrawFrontFun,
    void* fnDrawForegroundFun, void* fnDrawOverlayFun)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode && frameNode->IsSupportDrawModifier());
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    if (flag & FLAG_DRAW_BEHIND) {
        auto* fnDrawBehindFunPtr =
            static_cast<std::function<void(NG::DrawingContext & drawingContext)>*>(fnDrawBehindFun);
        drawModifier->drawBehindFunc = *fnDrawBehindFunPtr;
    }
    if (flag & FLAG_DRAW_CONTENT) {
        auto* fnDrawContentFunPtr =
            static_cast<std::function<void(NG::DrawingContext & drawingContext)>*>(fnDrawContentFun);
        drawModifier->drawContentFunc = *fnDrawContentFunPtr;
    }
    if (flag & FLAG_DRAW_FRONT) {
        auto* fnDrawFrontFunPtr =
            static_cast<std::function<void(NG::DrawingContext & drawingContext)>*>(fnDrawFrontFun);
        drawModifier->drawFrontFunc = *fnDrawFrontFunPtr;
    }
    if (flag & FLAG_DRAW_FOREGROUND) {
        auto* fnDrawForegroundFunPtr =
            static_cast<std::function<void(NG::DrawingContext & drawingContext)>*>(fnDrawForegroundFun);
        drawModifier->drawForegroundFunc = *fnDrawForegroundFunPtr;
    }
    if (flag & FLAG_DRAW_OVERLAY) {
        auto* fnDrawOverlayFunPtr =
            static_cast<std::function<void(NG::DrawingContext & drawingContext)>*>(fnDrawOverlayFun);
        drawModifier->drawOverlayFunc = *fnDrawOverlayFunPtr;
    }
    frameNode->SetDrawModifier(drawModifier);
    if (frameNode) {
        const auto& extensionHandler = frameNode->GetExtensionHandler();
        if (extensionHandler) {
            extensionHandler->InvalidateRender();
        } else {
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
        }
    }
}

void Invalidate(ani_env* env, ani_long ptr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode);
    const auto& extensionHandler = frameNode->GetExtensionHandler();
    if (extensionHandler) {
        extensionHandler->InvalidateRender();
    } else {
        frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
    }
}

const ArkUIAniDrawModifier* GetArkUIAniDrawModifier()
{
    static const ArkUIAniDrawModifier impl = {
        .setDrawModifier = OHOS::Ace::NG::SetDrawModifier,
        .invalidate = OHOS::Ace::NG::Invalidate,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
