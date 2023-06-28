/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

#include "session_manager/include/scene_session_manager.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/window_scene/scene/window_event_process.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_BLACK = 0xff000000;
constexpr uint32_t COLOR_WHITE = 0xffffffff;
} // namespace

class LifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit LifecycleListener(const WeakPtr<WindowPattern>& windowPattern) : windowPattern_(windowPattern) {}
    virtual ~LifecycleListener() = default;

    void OnConnect() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnConnect();
    }

    void OnForeground() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnForeground();
    }

    void OnBackground() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnBackground();
    }

    void OnDisconnect() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnDisconnect();
    }

private:
    WeakPtr<WindowPattern> windowPattern_;
};

WindowPattern::WindowPattern()
{
    instanceId_ = Container::CurrentId();
}

void WindowPattern::RegisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<LifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
}

void WindowPattern::UnregisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
}

void WindowPattern::InitContent()
{
    contentNode_ = FrameNode::CreateFrameNode(
        V2::WINDOW_SCENE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    if (surfaceNode) {
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);
    }

    auto state = session_->GetSessionState();
    LOGI("Session state is %{public}u.", state);
    switch (state) {
        case Rosen::SessionState::STATE_DISCONNECT: {
            CreateStartingNode();
            break;
        }
        case Rosen::SessionState::STATE_BACKGROUND: {
            CreateSnapshotNode();
            break;
        }
        default: {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->AddChild(contentNode_);
            break;
        }
    }
}

void WindowPattern::CreateStartingNode()
{
    if (!HasStartingPage() || CreatePersistentNode()) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    startingNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = startingNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->AddChild(startingNode_);

    std::string startPagePath;
    auto backgroundColor = SystemProperties::GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    auto sessionInfo = session_->GetSessionInfo();
    Rosen::SceneSessionManager::GetInstance().GetStartPage(sessionInfo, startPagePath, backgroundColor);
    LOGI("start page path %{public}s, background color %{public}x", startPagePath.c_str(), backgroundColor);

    startingNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(startPagePath, sessionInfo.bundleName_, sessionInfo.moduleName_));
    imageLayoutProperty->UpdateImageFit(ImageFit::NONE);
    startingNode_->MarkModifyDone();
}

void WindowPattern::CreateSnapshotNode()
{
    snapshotNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = snapshotNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto backgroundColor = SystemProperties::GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddChild(snapshotNode_);

    CHECK_NULL_VOID(session_);
    auto snapshot = session_->GetSnapshot();
    auto pixelMap = PixelMap::CreatePixelMap(&snapshot);

    CHECK_NULL_VOID(pixelMap);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    snapshotNode_->MarkModifyDone();
}

void WindowPattern::OnConnect()
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    CHECK_NULL_VOID(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    if (!HasStartingPage()) {
        return;
    }
    surfaceNode->SetBufferAvailableCallback([weak = WeakClaim(this)]() {
        LOGI("RSSurfaceNode buffer available callback");
        auto windowPattern = weak.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->BufferAvailableCallback();
    });
}

void WindowPattern::BufferAvailableCallback()
{
    ContainerScope scope(instanceId_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->RemoveChild(startingNode_);
    startingNode_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void WindowPattern::OnAttachToFrameNode()
{
    InitContent();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool WindowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    auto windowRect = geometryNode->GetFrameRect();
    Rosen::WSRect rect = { .posX_ = std::round(windowRect.GetX()),
        .posY_ = std::round(windowRect.GetY()),
        .width_ = std::round(windowRect.Width()),
        .height_ = std::round(windowRect.Height()) };

    CHECK_NULL_RETURN(session_, false);
    session_->UpdateRect(rect, Rosen::SizeChangeReason::UNDEFINED);
    return false;
}

void WindowPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(pointerEvent);
    PrintPointerEvent(pointerEvent);
    session_->TransferPointerEvent(pointerEvent);
}

void WindowPattern::PrintPointerEvent(const std::shared_ptr<MMI::PointerEvent>& event)
{
    CHECK_NULL_VOID(event);
    std::vector<int32_t> pointerIds = event->GetPointerIds();
    std::string str;
    std::vector<uint8_t> buffer = event->GetBuffer();
    for (const auto &buff : buffer) {
        str += std::to_string(buff);
    }
    LOGD("EventType:%{public}d,ActionTime:%{public}" PRId64 ",Action:%{public}d,"
        "ActionStartTime:%{public}" PRId64 ",Flag:%{public}d,PointerAction:%{public}s,"
        "SourceType:%{public}s,ButtonId:%{public}d,VerticalAxisValue:%{public}.2f,"
        "HorizontalAxisValue:%{public}.2f,PinchAxisValue:%{public}.2f,"
        "XAbsValue:%{public}.2f,YAbsValue:%{public}.2f,ZAbsValue:%{public}.2f,"
        "RzAbsValue:%{public}.2f,GasAbsValue:%{public}.2f,BrakeAbsValue:%{public}.2f,"
        "Hat0xAbsValue:%{public}.2f,Hat0yAbsValue:%{public}.2f,ThrottleAbsValue:%{public}.2f,"
        "PointerId:%{public}d,PointerCount:%{public}zu,EventNumber:%{public}d,"
        "BufferCount:%{public}zu,Buffer:%{public}s",
        event->GetEventType(), event->GetActionTime(), event->GetAction(),
        event->GetActionStartTime(), event->GetFlag(), event->DumpPointerAction(), event->DumpSourceType(),
        event->GetButtonId(), event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_SCROLL_VERTICAL),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_SCROLL_HORIZONTAL),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_PINCH),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_X),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_Y),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_Z),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_RZ),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_GAS),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_BRAKE),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_HAT0X),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_HAT0Y),
        event->GetAxisValue(MMI::PointerEvent::AXIS_TYPE_ABS_THROTTLE), event->GetPointerId(), pointerIds.size(),
        event->GetId(), buffer.size(), str.c_str());

    for (const auto &pointerId : pointerIds) {
        MMI::PointerEvent::PointerItem item;
        if (!event->GetPointerItem(pointerId, item)) {
            LOGE("Invalid pointer: %{public}d.", pointerId);
            return;
        }
        LOGD("pointerId:%{public}d,DownTime:%{public}" PRId64 ",IsPressed:%{public}d,DisplayX:%{public}d,"
            "DisplayY:%{public}d,WindowX:%{public}d,WindowY:%{public}d,Width:%{public}d,Height:%{public}d,"
            "TiltX:%{public}.2f,TiltY:%{public}.2f,ToolDisplayX:%{public}d,ToolDisplayY:%{public}d,"
            "ToolWindowX:%{public}d,ToolWindowY:%{public}d,ToolWidth:%{public}d,ToolHeight:%{public}d,"
            "Pressure:%{public}.2f,ToolType:%{public}d,LongAxis:%{public}d,ShortAxis:%{public}d,RawDx:%{public}d,"
            "RawDy:%{public}d",
            pointerId, item.GetDownTime(), item.IsPressed(), item.GetDisplayX(), item.GetDisplayY(),
            item.GetWindowX(), item.GetWindowY(), item.GetWidth(), item.GetHeight(), item.GetTiltX(),
            item.GetTiltY(), item.GetToolDisplayX(), item.GetToolDisplayY(), item.GetToolWindowX(),
            item.GetToolWindowY(), item.GetToolWidth(), item.GetToolHeight(), item.GetPressure(),
            item.GetToolType(), item.GetLongAxis(), item.GetShortAxis(), item.GetRawDx(), item.GetRawDy());
    }
}

void WindowPattern::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(session_);
    session_->TransferKeyEvent(keyEvent);
}

bool WindowPattern::CreatePersistentNode()
{
    CHECK_NULL_RETURN(session_, false);
    if (session_->GetScenePersistence() == nullptr || !session_->GetScenePersistence()->IsSnapshotExisted()) {
        return false;
    }
    startingNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = startingNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->AddChild(startingNode_);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(std::string("file:/").append(session_->GetScenePersistence()->GetSnapshotFilePath())));
    imageLayoutProperty->UpdateImageFit(ImageFit::COVER);
    startingNode_->MarkModifyDone();
    return true;
}

void WindowPattern::DispatchKeyEventForConsumed(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool& isConsumed)
{
    CHECK_NULL_VOID(session_);
    session_->TransferKeyEventForConsumed(keyEvent, isConsumed);
}

void WindowPattern::DisPatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusActiveEvent(isFocusActive);
}

void WindowPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }
    auto callback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    gestureHub->AddTouchEvent(touchEvent_);
}

void WindowPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (mouseEvent_) {
        return;
    }
    auto callback = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    if (mouseEvent_) {
        inputHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(callback));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void WindowPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    LOGD("WindowPattern HandleTouchEvent enter");
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    if (IsFilterTouchEvent(pointerEvent)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculateWindowCoordinate(selfGlobalOffset, pointerEvent, scale);
    DispatchPointerEvent(pointerEvent);
}

bool WindowPattern::IsFilterTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    return pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE &&
    (pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN ||
        pointerEvent->GetButtonId() == MMI::PointerEvent::BUTTON_NONE);
}

void WindowPattern::HandleMouseEvent(const MouseInfo& info)
{
    LOGD("WindowPattern HandleMouseEvent enter");
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    if (IsFilterMouseEvent(pointerEvent)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculateWindowCoordinate(selfGlobalOffset, pointerEvent, scale);
    int32_t action = pointerEvent->GetPointerAction();
    if (action == MMI::PointerEvent::POINTER_ACTION_MOVE &&
        pointerEvent->GetButtonId() == MMI::PointerEvent::BUTTON_NONE) {
        WindowEventHandler->ProcessWindowEvent(AceType::DynamicCast<WindowNode>(
            host, pointerEvent, false));
    }
    if (action == MMI::PointerEvent::POINTER_ACTION_PULL_MOVE) {
        WindowEventHandler->ProcessWindowEvent(AceType::DynamicCast<WindowNode>(
            host, pointerEvent, true));
    }
    DispatchPointerEvent(pointerEvent);
}

bool WindowPattern::IsFilterMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    int32_t pointerAction = pointerEvent->GetPointerAction();
    if ((pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN) &&
        (pointerAction != MMI::PointerEvent::POINTER_ACTION_PULL_MOVE) &&
        (pointerAction != MMI::PointerEvent::POINTER_ACTION_PULL_UP)) {
        return true;
    }
    return pointerEvent->GetButtonId() != MMI::PointerEvent::BUTTON_NONE &&
        (pointerAction == MMI::PointerEvent::POINTER_ACTION_MOVE ||
        pointerAction == MMI::PointerEvent::POINTER_ACTION_BUTTON_UP);
}

void WindowPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouchEvent(gestureHub);
    auto inputHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitMouseEvent(inputHub);
}
} // namespace OHOS::Ace::NG
