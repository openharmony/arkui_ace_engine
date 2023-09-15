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
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/window_scene/scene/window_event_process.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_BLACK = 0xff000000;
constexpr uint32_t COLOR_WHITE = 0xffffffff;
} // namespace

class LifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit LifecycleListener(const WeakPtr<WindowPattern>& windowPattern) : windowPattern_(windowPattern) {}
    virtual ~LifecycleListener() = default;

    void OnActivation() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnActivation();
    }

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

    void OnExtensionDied() override {}

private:
    WeakPtr<WindowPattern> windowPattern_;
};

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

bool WindowPattern::IsMainWindow() const
{
    CHECK_NULL_RETURN(session_, false);
    return session_->GetWindowType() == Rosen::WindowType::WINDOW_TYPE_APP_MAIN_WINDOW;
}

void WindowPattern::OnAttachToFrameNode()
{
    contentNode_ = FrameNode::CreateFrameNode(
        V2::WINDOW_SCENE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    contentNode_->SetHitTestMode(HitTestMode::HTMNONE);

    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    if (surfaceNode) {
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto state = session_->GetSessionState();
    auto bundleName = session_->GetSessionInfo().bundleName_;
    LOGI("Session state: %{public}u, bundle name: %{public}s", state, bundleName.c_str());
    if (state == Rosen::SessionState::STATE_DISCONNECT) {
        if (!HasStartingPage()) {
            return;
        }
        if (session_->GetShowRecent()) {
            CreateSnapshotNode();
            host->AddChild(snapshotNode_);
            return;
        }
        CreateStartingNode();
        host->AddChild(startingNode_);
        return;
    }

    if (state == Rosen::SessionState::STATE_BACKGROUND && session_->GetBufferAvailable() && session_->GetShowRecent()) {
        CreateSnapshotNode();
        host->AddChild(snapshotNode_);
        return;
    }

    host->AddChild(contentNode_);
    if (!session_->GetBufferAvailable()) {
        CreateStartingNode();
        host->AddChild(startingNode_);
        if (surfaceNode) {
            surfaceNode->SetBufferAvailableCallback(callback_);
        }
    }
}

void WindowPattern::CreateStartingNode()
{
    startingNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = startingNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingNode_->SetHitTestMode(HitTestMode::HTMNONE);

    std::string startupPagePath;
    auto backgroundColor = SystemProperties::GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    const auto& sessionInfo = session_->GetSessionInfo();
    Rosen::SceneSessionManager::GetInstance().GetStartupPage(sessionInfo, startupPagePath, backgroundColor);
    LOGI("startup page path %{public}s, background color %{public}x", startupPagePath.c_str(), backgroundColor);

    startingNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(startupPagePath, sessionInfo.bundleName_, sessionInfo.moduleName_));
    imageLayoutProperty->UpdateImageFit(ImageFit::NONE);
    startingNode_->MarkModifyDone();
}

void WindowPattern::CreateSnapshotNode(std::optional<std::shared_ptr<Media::PixelMap>> snapshot)
{
    snapshotNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = snapshotNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    snapshotNode_->SetHitTestMode(HitTestMode::HTMNONE);

    auto backgroundColor = SystemProperties::GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    if (snapshot) {
        auto pixelMap = PixelMap::CreatePixelMap(&snapshot.value());
        if (!pixelMap) {
            LOGE("pixelMap is null");
            snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));
            return;
        }
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    } else {
        snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));
        CHECK_NULL_VOID(session_);
        CHECK_NULL_VOID(session_->GetScenePersistence());
        ImageSourceInfo sourceInfo("file://" + session_->GetScenePersistence()->GetSnapshotFilePath());
        imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto imageCache = pipelineContext->GetImageCache();
        CHECK_NULL_VOID(imageCache);
        auto snapshotSize = session_->GetScenePersistence()->GetSnapshotSize();
        auto cacheKey = ImageUtils::GenerateImageKey(sourceInfo, SizeF(snapshotSize.first, snapshotSize.second));
        imageCache->ClearCacheImage(cacheKey);
        imageCache->ClearCacheImage(sourceInfo.GetKey());
    }
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    snapshotNode_->MarkModifyDone();
}

void WindowPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(pointerEvent);
    session_->TransferPointerEvent(pointerEvent);
#ifdef ENABLE_DRAG_FRAMEWORK
    if (pointerEvent->GetPointerAction() >= MMI::PointerEvent::POINTER_ACTION_PULL_DOWN &&
        pointerEvent->GetPointerAction() <= MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            auto manager = pipeline->GetDragDropManager();
            CHECK_NULL_VOID(manager);
            manager->SetIsWindowConsumed(true);
        }
    }
#endif // ENABLE_DRAG_FRAMEWORK
}

void WindowPattern::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(keyEvent);
    session_->TransferKeyEvent(keyEvent);
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

int32_t CalculateTranslateDegree(int32_t hostId)
{
    auto& translateCfg = NGGestureRecognizer::GetGlobalTransCfg();
    auto& translateIds = NGGestureRecognizer::GetGlobalTransIds();
    auto translateIter = translateIds.find(hostId);
    int32_t udegree = 0;
    if (translateIter == translateIds.end()) {
        return udegree;
    }
    while (translateIter != translateIds.end()) {
        int32_t translateId = translateIter->second.parentId;
        auto translateCfgIter = translateCfg.find(translateId);
        if (translateCfgIter != translateCfg.end() && translateCfgIter->second.degree != 0) {
            udegree = static_cast<int32_t>(translateCfgIter->second.degree);
            break;
        }
        translateIter = translateIds.find(translateId);
    }
    udegree = udegree % 360;
    return udegree < 0 ? udegree + 360 : udegree;
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
    CHECK_NULL_VOID(host);
    FilterInvalidPointerItem(pointerEvent);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    auto udegree = CalculateTranslateDegree(host->GetId());
    Platform::CalculateWindowCoordinate(selfGlobalOffset, pointerEvent, scale, udegree);
    SetWindowSceneConsumed(pointerEvent->GetPointerAction());
    DispatchPointerEvent(pointerEvent);
    if (SystemProperties::GetDebugEnabled()) {
        int32_t pointerId = pointerEvent->GetPointerId();
        MMI::PointerEvent::PointerItem item;
        bool ret = pointerEvent->GetPointerItem(pointerId, item);
        if (ret) {
            LOGI("WindowPattern AdapterRotation udegree:%{public}d, windowX:%{public}d, windowY:%{public}d", udegree,
                item.GetWindowX(), item.GetWindowY());
        }
    }
}

void WindowPattern::FilterInvalidPointerItem(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ids = pointerEvent->GetPointerIds();
    if (ids.size() <= 1) {
        return;
    }
    for (auto&& id : ids) {
        MMI::PointerEvent::PointerItem item;
        bool ret = pointerEvent->GetPointerItem(id, item);
        if (!ret) {
            LOGE("get pointer:%{public}d item failed", id);
            continue;
        }
        const NG::PointF point { static_cast<float>(item.GetDisplayX()), static_cast<float>(item.GetDisplayY()) };
        if (host->IsOutOfTouchTestRegion(point, MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN)) {
            pointerEvent->RemovePointerItem(id);
        }
    }
}

bool WindowPattern::IsFilterTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    return (pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE &&
        (pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN ||
        pointerEvent->GetButtonId() == MMI::PointerEvent::BUTTON_NONE)) ||
        (pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_PULL_MOVE ||
        pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_PULL_UP);
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
    CHECK_NULL_VOID(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculateWindowCoordinate(selfGlobalOffset, pointerEvent, scale);
    DelayedSingleton<WindowEventProcess>::GetInstance()->ProcessWindowMouseEvent(
        host->GetId(), session_, pointerEvent);
    int32_t action = pointerEvent->GetPointerAction();
    if (action == MMI::PointerEvent::POINTER_ACTION_PULL_MOVE) {
        DelayedSingleton<WindowEventProcess>::GetInstance()->ProcessWindowDragEvent(
            AceType::DynamicCast<WindowNode>(host), pointerEvent);
    }
    if (action == MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
        DelayedSingleton<WindowEventProcess>::GetInstance()->CleanWindowDragEvent();
    }
    SetWindowSceneConsumed(action);
    DispatchPointerEvent(pointerEvent);
}

sptr<Rosen::Session> WindowPattern::GetSession()
{
    return session_;
}

bool WindowPattern::IsFilterMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    int32_t pointerAction = pointerEvent->GetPointerAction();
    if ((pointerEvent->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN) &&
        (pointerAction != MMI::PointerEvent::POINTER_ACTION_PULL_MOVE) &&
        (pointerAction != MMI::PointerEvent::POINTER_ACTION_PULL_UP)) {
        return true;
    }
    return pointerEvent->GetButtonId() == MMI::PointerEvent::MOUSE_BUTTON_LEFT &&
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

void WindowPattern::TransferFocusState(bool focusState)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusStateEvent(focusState);
}

std::vector<Rosen::Rect> WindowPattern::GetHotAreas()
{
    if (session_ == nullptr) {
        return std::vector<Rosen::Rect>();
    }
    return session_->GetTouchHotAreas();
}

void WindowPattern::SetWindowSceneConsumed(int32_t action)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        if (action == MMI::PointerEvent::POINTER_ACTION_DOWN ||
            action == MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN) {
            pipeline->SetWindowSceneConsumed(true);
        }
        if (action == MMI::PointerEvent::POINTER_ACTION_UP ||
            action == MMI::PointerEvent::POINTER_ACTION_BUTTON_UP ||
            action == MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
            pipeline->SetWindowSceneConsumed(false);
        }
    }
}
} // namespace OHOS::Ace::NG
