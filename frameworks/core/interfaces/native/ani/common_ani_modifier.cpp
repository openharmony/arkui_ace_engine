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
#include "common_ani_modifier.h"
#include "ani_utils.h"
#include "ui/properties/color.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
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
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/node/theme_modifier.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/arkts_frontend/ani_graphics_module.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "bridge/arkts_frontend/ani_context_module.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/interfaces/native/implementation/key_event_peer.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "frameworks/base/subwindow/subwindow_manager.h"

#include <cstdint>
#include <memory>
#include <vector>

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
    return frontend->GetHostContext(key);
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

void SetDrawCallback(ani_env* env, ani_long ptr, ani_fn_object fnObj)
{
    Framework::AniGraphicsModule::SetDrawCallback(env, ptr, fnObj);
}

ArkUI_Int32 GetCurrentInstanceId()
{
    return ContainerScope::CurrentId();
}

ArkUI_Int32 GetFocusedInstanceId()
{
    auto container = Container::GetFoucsed();
    CHECK_NULL_RETURN(container, -1);
    auto currentInstance = container->GetInstanceId();
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

void SetCustomCallback(ani_env* env, ani_long ptr, ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout)
{
    Framework::AniGraphicsModule::SetCustomCallback(env, ptr, fnObjMeasure, fnObjLayout);
}

ArkUI_Int32 RequireArkoalaNodeId(ArkUI_Int32 capacity)
{
    auto cursor = ElementRegister::GetInstance()->RequireArkoalaNodeId(capacity);
    return cursor;
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

void OnMeasureInnerMeasure(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::OnMeasureInnerMeasure(env, ptr);
}

void OnLayoutInnerLayout(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::OnLayoutInnerLayout(env, ptr);
}

void SetParallelScoped(ani_boolean parallel)
{
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(parallel);
    MultiThreadBuildManager::SetIsParallelizeUI(parallel);
}

static void SetCustomPropertyCallBack(
    ani_env* env, ArkUINodeHandle node, std::function<void()>&& func,
    std::function<std::string(const std::string&)>&& getFunc)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    ContainerScope scope(id);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("SetCustomPropertyCallBack doesn't run on UI thread");
    }
    auto frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetCustomPropertyCallback(std::move(func), std::move(getFunc));
}

static std::optional<std::string> GetCustomProperty(ani_env* env, ArkUINodeHandle node, const std::string& key)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    ContainerScope scope(id);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("GetCustomProperty doesn't run on UI thread");
    }
    auto frameNode = reinterpret_cast<NG::FrameNode*>(node);
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
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
    ContainerScope cope(instanceId);
    double density = PipelineBase::GetCurrentDensity();
    return value * density;
}

ani_double Px2vp(ani_double value, ani_int instanceId)
{
    if (NearZero(value)) {
        return 0;
    }
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
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
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
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
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
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
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
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
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
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

void EventTargetInfoAccessorWithId(ani_env* env, ani_long input, ani_string id)
{
    CHECK_NULL_VOID(input);
    auto accessor = reinterpret_cast<Ark_EventTargetInfo>(input);
    CHECK_NULL_VOID(accessor);
    auto idValue = AniUtils::ANIStringToStdString(env, id);
    accessor->id = idValue;
}

void* CreateScrollableTargetInfoAccessor()
{
    auto peer = ScrollableTargetInfoPeer::Create();
    return reinterpret_cast<void*>(peer);
}

void ScrollableTargetInfoAccessorWithId(ani_env* env, ani_long input, ani_string id)
{
    CHECK_NULL_VOID(input);
    auto accessor = reinterpret_cast<Ark_EventTargetInfo>(input);
    CHECK_NULL_VOID(accessor);
    auto idValue = AniUtils::ANIStringToStdString(env, id);
    accessor->id = idValue;
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
    auto colors = AniThemeColors();
    colors.SetColors(colorArray);

    auto themeScopeId = static_cast<int32_t>(id);
    AniThemeScope::aniThemes[themeScopeId].SetColors(colors);
    // save the current theme when Theme was created by WithTheme container
    if (AniThemeScope::isCurrentThemeDefault || themeScopeId > 0) {
        std::optional<NG::AniTheme> themeOpt = std::make_optional(AniThemeScope::aniThemes[themeScopeId]);
        AniThemeScope::aniCurrentTheme.swap(themeOpt);
    }
}

void SetDefaultTheme(ani_env* env, const std::vector<Ark_ResourceColor>& colorArray, ani_boolean isDark)
{
    auto isDarkValue = static_cast<bool>(isDark);
    std::vector<uint32_t> colors;
    AniThemeModule::ConvertToColorArray(colorArray, colors);
    NodeModifier::GetThemeModifier()->setDefaultTheme(colors.data(), isDarkValue);
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

const ArkUIAniCommonModifier* GetCommonAniModifier()
{
    static const ArkUIAniCommonModifier impl = {
        .getHostContext = OHOS::Ace::NG::GetHostContext,
        .syncInstanceId = OHOS::Ace::NG::SyncInstanceId,
        .restoreInstanceId = OHOS::Ace::NG::RestoreInstanceId,
        .setDrawCallback = OHOS::Ace::NG::SetDrawCallback,
        .getCurrentInstanceId = OHOS::Ace::NG::GetCurrentInstanceId,
        .getFocusedInstanceId = OHOS::Ace::NG::GetFocusedInstanceId,
        .builderProxyNodeConstruct = OHOS::Ace::NG::BuilderProxyNodeConstruct,
        .getSharedLocalStorage = OHOS::Ace::NG::GetSharedLocalStorage,
        .setBackgroundImagePixelMap = OHOS::Ace::NG::SetBackgroundImagePixelMap,
        .setCustomCallback = OHOS::Ace::NG::SetCustomCallback,
        .requireArkoalaNodeId = OHOS::Ace::NG::RequireArkoalaNodeId,
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
        .getColorValueByNumber = OHOS::Ace::NG::GetColorValueByNumber,
        .sendThemeToNative = OHOS::Ace::NG::SendThemeToNative,
        .setDefaultTheme = OHOS::Ace::NG::SetDefaultTheme,
        .updateColorMode = OHOS::Ace::NG::UpdateColorMode,
        .restoreColorMode = OHOS::Ace::NG::RestoreColorMode
    };
    return &impl;
}

void SetDrawModifier(ani_env* env, ani_long ptr, uint32_t flag, ani_object fnObj)
{
    Framework::AniGraphicsModule::SetDrawModifier(env, ptr, flag, fnObj);
}

void Invalidate(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::Invalidate(env, ptr);
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
