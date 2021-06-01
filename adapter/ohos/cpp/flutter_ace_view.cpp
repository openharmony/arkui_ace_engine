/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "adapter/ohos/cpp/flutter_ace_view.h"
#include <fstream>

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/macros.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/event/mouse_event.h"
#include "core/gestures/touch_event.h"
#include "core/image/image_cache.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/pipeline/layers/flutter_scene_builder.h"

namespace OHOS::Ace::Platform {
namespace {

constexpr int32_t ROTATION_DIVISOR = 64;
constexpr double PERMIT_ANGLE_VALUE = 0.5;

TouchPoint ConvertTouchEvent(OHOS::TouchEvent& touchEvent)
{
    int32_t id = static_cast<int32_t>(touchEvent.GetIndex());
    MmiPoint mmiPoint = touchEvent.GetPointerPosition(id);
    std::chrono::microseconds micros(touchEvent.GetOccurredTime());
    TimeStamp time(micros);
    TouchPoint point { id, mmiPoint.GetX(), mmiPoint.GetY(), TouchType::UNKNOWN, time, touchEvent.GetRadius(id) };
    switch (touchEvent.GetAction()) {
        case OHOS::TouchEvent::CANCEL:
            point.type = TouchType::CANCEL;
            break;
        case OHOS::TouchEvent::HOVER_POINTER_ENTER:
        case OHOS::TouchEvent::HOVER_POINTER_MOVE:
        case OHOS::TouchEvent::HOVER_POINTER_EXIT:
            LOGD("ConvertTouchEvent not implement type:%{public}ld", touchEvent.GetAction());
            break;
        case OHOS::TouchEvent::PRIMARY_POINT_DOWN:
        case OHOS::TouchEvent::OTHER_POINT_DOWN:
            point.type = TouchType::DOWN;
            break;
        case OHOS::TouchEvent::POINT_MOVE:
            point.type = TouchType::MOVE;
            break;
        case OHOS::TouchEvent::PRIMARY_POINT_UP:
        case OHOS::TouchEvent::OTHER_POINT_UP:
            point.type = TouchType::UP;
            break;
        default:
            LOGW("unknown type");
            break;
    }
    return point;
}

void ConvertMouseEvent(OHOS::MouseEvent& mouseEvent, MouseEvent& events)
{
    MmiPoint mmiPoint = mouseEvent.GetCursor();
    events.x = mmiPoint.GetX();
    events.y = mmiPoint.GetY();
    events.z = mmiPoint.GetZ();
    switch (mouseEvent.GetAction()) {
        case OHOS::MouseEvent::PRESS:
            events.action = MouseAction::PRESS;
            break;
        case OHOS::MouseEvent::RELEASE:
            events.action = MouseAction::RELEASE;
            break;
        case OHOS::MouseEvent::MOVE:
            events.action = MouseAction::MOVE;
            break;
        case OHOS::MouseEvent::HOVER_ENTER:
            events.action = MouseAction::HOVER_ENTER;
            break;
        case OHOS::MouseEvent::HOVER_MOVE:
            events.action = MouseAction::HOVER_MOVE;
            break;
        case OHOS::MouseEvent::HOVER_EXIT:
            events.action = MouseAction::HOVER_EXIT;
            break;
        default:
            events.action = MouseAction::NONE;
            break;
    }
    switch (mouseEvent.GetActionButton()) {
        case OHOS::MouseEvent::LEFT_BUTTON:
            events.button = MouseButton::LEFT_BUTTON;
            break;
        case OHOS::MouseEvent::RIGHT_BUTTON:
            events.button = MouseButton::RIGHT_BUTTON;
            break;
        case OHOS::MouseEvent::MIDDLE_BUTTON:
            events.button = MouseButton::MIDDLE_BUTTON;
            break;
        case OHOS::MouseEvent::BACK_BUTTON:
            events.button = MouseButton::BACK_BUTTON;
            break;
        case OHOS::MouseEvent::FORWARD_BUTTON:
            events.button = MouseButton::FORWARD_BUTTON;
            break;
        default:
            events.button = MouseButton::NONE_BUTTON;
            break;
    }
    events.pressedButtons = static_cast<size_t>(mouseEvent.GetPressedButtons());
    std::chrono::microseconds micros(mouseEvent.GetOccurredTime());
    TimeStamp time(micros);
    events.time = time;
}

} // namespace

FlutterAceView* FlutterAceView::CreateView(int32_t instanceId)
{
    FlutterAceView* aceSurface = new Platform::FlutterAceView(instanceId);
    flutter::Settings settings;
    settings.instanceId = instanceId;
    settings.platform = flutter::AcePlatform::ACE_PLATFORM_OHOS;
    settings.enable_software_rendering = true;
    settings.idle_notification_callback = [aceSurface](int64_t deadline) {
        if (aceSurface != nullptr) {
            aceSurface->ProcessIdleEvent(deadline);
        }
    };
    auto shell_holder = std::make_unique<flutter::OhosShellHolder>(settings, false);
    if (aceSurface != nullptr) {
        aceSurface->SetShellHolder(std::move(shell_holder));
    }
    return aceSurface;
}

void FlutterAceView::SurfaceCreated(FlutterAceView* view, OHOS::Window* window)
{
    LOGI(">>> FlutterAceView::SurfaceCreated, pWnd:%{public}p", window);
    if (window == nullptr) {
        LOGE("FlutterAceView::SurfaceCreated, window is nullptr");
        return;
    }

    if (view == nullptr) {
        LOGE("FlutterAceView::SurfaceCreated, view is nullptr");
        return;
    }

    auto platformView = view->GetShellHolder()->GetPlatformView();
    LOGI("FlutterAceView::SurfaceCreated, GetPlatformView");
    if (platformView) {
        LOGI("FlutterAceView::SurfaceCreated, call NotifyCreated");
        platformView->NotifyCreated(window);
    }
    LOGI("<<< FlutterAceView::SurfaceCreated, end");
}

void FlutterAceView::SurfaceChanged(FlutterAceView* view, int32_t width, int32_t height, int32_t orientation)
{
    if (view == nullptr) {
        LOGE("FlutterAceView::SurfaceChanged, view is nullptr");
        return;
    }

    view->NotifySurfaceChanged(width, height);
}

void FlutterAceView::SetViewportMetrics(FlutterAceView* view, const flutter::ViewportMetrics& metrics)
{
    if (view) {
        view->NotifyDensityChanged(metrics.device_pixel_ratio);
        view->NotifySystemBarHeightChanged(metrics.physical_padding_top, metrics.physical_view_inset_bottom);
        auto platformView = view->GetShellHolder()->GetPlatformView();
        if (platformView) {
            platformView->SetViewportMetrics(metrics);
        }
    }
}

bool FlutterAceView::DispatchTouchEvent(FlutterAceView* view, OHOS::TouchEvent& touchEvent)
{
    if (touchEvent.GetAction() == OHOS::TouchEvent::OTHER && touchEvent.GetSourceDevice() == OHOS::TouchEvent::MOUSE) {
        // mouse event
        LOGD("DispatchTouchEvent MouseEvent");
        std::shared_ptr<MultimodalEvent> multimodalEvent = touchEvent.GetMultimodalEvent();
        OHOS::MouseEvent* mouseEvent = (OHOS::MouseEvent*)multimodalEvent.get();
        if (mouseEvent == nullptr) {
            LOGE("mouseEvent is nullptr");
            return false;
        }
        view->ProcessMouseEvent(*mouseEvent);
    } else {
        // touch event
        LOGD("DispatchTouchEvent TouchEvent");
        return view->ProcessTouchEvent(touchEvent);
    }
    return true;
}

bool FlutterAceView::DispatchKeyEvent(FlutterAceView* view, int32_t keyCode, int32_t action, int32_t repeatTime,
    int64_t timeStamp, int64_t timeStampStart)
{
    if (view != nullptr) {
        return view->ProcessKeyEvent(keyCode, action, repeatTime, timeStamp, timeStampStart);
    }
    LOGE("view is null, return false!");
    return false;
}

bool FlutterAceView::DispatchRotationEvent(FlutterAceView* view, float rotationValue)
{
    if (view) {
        return view->ProcessRotationEvent(rotationValue);
    }
    LOGE("view is null, return false!");
    return false;
}

void FlutterAceView::RegisterTouchEventCallback(TouchEventCallback&& callback)
{
    ACE_DCHECK(callback);
    touchEventCallback_ = std::move(callback);
}

void FlutterAceView::RegisterKeyEventCallback(KeyEventCallback&& callback)
{
    ACE_DCHECK(callback);
    keyEventCallback_ = std::move(callback);
}

void FlutterAceView::RegisterMouseEventCallback(MouseEventCallback&& callback)
{
    ACE_DCHECK(callback);
    mouseEventCallback_ = std::move(callback);
}

void FlutterAceView::RegisterRotationEventCallback(RotationEventCallBack&& callback)
{
    ACE_DCHECK(callback);
    rotationEventCallBack_ = std::move(callback);
}

void FlutterAceView::Launch()
{
    LOGD("Launch shell holder.");
    if (!viewLaunched_) {
        flutter::RunConfiguration config;
        shell_holder_->Launch(std::move(config));
        viewLaunched_ = true;
    }
}

void FlutterAceView::SetShellHolder(std::unique_ptr<flutter::OhosShellHolder> holder)
{
    shell_holder_ = std::move(holder);
}

bool FlutterAceView::ProcessTouchEvent(OHOS::TouchEvent& touchEvent)
{
    TouchPoint touchPoint = ConvertTouchEvent(touchEvent);
    bool forbiddenToPlatform = false;
    if (touchPoint.type != TouchType::UNKNOWN) {
        if (touchEventCallback_) {
            touchEventCallback_(touchPoint);
        }
    } else {
        LOGW("Unknown event.");
    }

#ifdef WEARABLE_PRODUCT
    forbiddenToPlatform = forbiddenToPlatform || IsNeedForbidToPlatform(point);
#endif

    // if last page, let os know so that to quit app.
    return forbiddenToPlatform || (!IsLastPage());
}

void FlutterAceView::ProcessMouseEvent(OHOS::MouseEvent& mouseEvent)
{
    MouseEvent event;
    ConvertMouseEvent(mouseEvent, event);
    LOGD("ProcessMouseEvent event");

    if (mouseEventCallback_) {
        mouseEventCallback_(event);
    }
}

bool FlutterAceView::ProcessKeyEvent(
    int32_t keyCode, int32_t keyAction, int32_t repeatTime, int64_t timeStamp, int64_t timeStampStart)
{
    if (!keyEventCallback_) {
        return false;
    }

    auto keyEvents = keyEventRecognizer_.GetKeyEvents(keyCode, keyAction, repeatTime, timeStamp, timeStampStart);
    // First distributes special events.
    // Because the platform receives a raw event, the identified special event processing result is ignored
    if (keyEvents.size() > 1) {
        keyEventCallback_(keyEvents.back());
    }
    return keyEventCallback_(keyEvents.front());
}

void FlutterAceView::ProcessIdleEvent(int64_t deadline)
{
    if (idleCallback_) {
        idleCallback_(deadline);
    }
}

bool FlutterAceView::ProcessRotationEvent(float rotationValue)
{
    if (!rotationEventCallBack_) {
        return false;
    }

    RotationEvent event { .value = rotationValue * ROTATION_DIVISOR };

    return rotationEventCallBack_(event);
}

bool FlutterAceView::Dump(const std::vector<std::string>& params)
{
    if (params.empty() || params[0] != "-drawcmd") {
        LOGE("Unsupported parameters.");
        return false;
    }
#ifdef DUMP_DRAW_CMD
    static int32_t count = 0;
    if (shell_holder_) {
        auto screenShot = shell_holder_->Screenshot(flutter::Rasterizer::ScreenshotType::SkiaPicture, false);
        if (screenShot.data->data() != nullptr) {
            auto byteData = screenShot.data;
            auto path = ImageCache::GetImageCacheFilePath() + "/picture_" + std::to_string(count++) + ".mskp";
            if (DumpLog::GetInstance().GetDumpFile()) {
                DumpLog::GetInstance().AddDesc("Dump draw command to path: " + path);
                DumpLog::GetInstance().Print(0, "Info:", 0);
            }
            std::ofstream outFile(path, std::fstream::out | std::fstream::binary);
            if (!outFile.is_open()) {
                LOGE("Open file %{private}s failed.", path.c_str());
                return false;
            }
            outFile.write(reinterpret_cast<const char*>(byteData->data()), byteData->size());
            outFile.close();
            return true;
        }
    }
#else
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("Dump draw command not support on this version.");
        DumpLog::GetInstance().Print(0, "Info:", 0);
        return true;
    }
#endif
    return false;
}

void FlutterAceView::InitCacheFilePath(const std::string& path)
{
    if (!path.empty()) {
        ImageCache::SetImageCacheFilePath(path);
        ImageCache::SetCacheFileInfo();
    } else {
        LOGW("image cache path empty");
    }
}

bool FlutterAceView::IsLastPage() const
{
    auto container = AceEngine::Get().GetContainer(instanceId_);
    if (!container) {
        return false;
    }

    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }

    return context->IsLastPage();
}

uint32_t FlutterAceView::GetBackgroundColor()
{
    return Color::WHITE.GetValue();
}

// On watch device, it's probable to quit the application unexpectedly when we slide our finger diagonally upward on the
// screen, so we do restrictions here.
bool FlutterAceView::IsNeedForbidToPlatform(TouchPoint point)
{
    if (point.type == TouchType::DOWN) {
        auto result = touchPointInfoMap_.try_emplace(point.id, TouchPointInfo(point.GetOffset()));
        if (!result.second) {
            result.first->second = TouchPointInfo(point.GetOffset());
        }

        return false;
    }

    auto iter = touchPointInfoMap_.find(point.id);
    if (iter == touchPointInfoMap_.end()) {
        return false;
    }
    if (iter->second.eventState_ == EventState::HORIZONTAL_STATE) {
        return false;
    } else if (iter->second.eventState_ == EventState::VERTICAL_STATE) {
        return true;
    }

    Offset offset = point.GetOffset() - iter->second.offset_;
    double deltaX = offset.GetX();
    double deltaY = std::abs(offset.GetY());

    if (point.type == TouchType::MOVE) {
        if (deltaX > 0.0) {
            if (deltaY / deltaX > PERMIT_ANGLE_VALUE) {
                iter->second.eventState_ = EventState::VERTICAL_STATE;
                return true;
            } else {
                iter->second.eventState_ = EventState::HORIZONTAL_STATE;
            }
        }

        return false;
    }

    touchPointInfoMap_.erase(point.id);
    return deltaX > 0.0 && deltaY / deltaX > PERMIT_ANGLE_VALUE;
}

std::unique_ptr<DrawDelegate> FlutterAceView::GetDrawDelegate()
{
    auto darwDelegate = std::make_unique<DrawDelegate>();

    darwDelegate->SetDrawFrameCallback([this](RefPtr<Flutter::Layer>& layer, const Rect& dirty) {
        if (!layer) {
            return;
        }
        RefPtr<Flutter::FlutterSceneBuilder> flutterSceneBuilder = AceType::MakeRefPtr<Flutter::FlutterSceneBuilder>();
        layer->AddToScene(*flutterSceneBuilder, 0.0, 0.0);
        auto scene = flutterSceneBuilder->Build();
        if (!flutter::UIDartState::Current()) {
            LOGE("uiDartState is nullptr");
            return;
        }
        auto window = flutter::UIDartState::Current()->window();
        if (window != nullptr && window->client() != nullptr) {
            window->client()->Render(scene.get());
        }
    });

    return darwDelegate;
}

std::unique_ptr<PlatformWindow> FlutterAceView::GetPlatformWindow()
{
    return nullptr;
}

} // namespace OHOS::Ace::Platform
