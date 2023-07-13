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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_VIEW_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_VIEW_OHOS_H

#include <memory>

#include "interfaces/inner_api/ace/viewport_config.h"
#include "key_event.h"
#include "wm/window.h"

#include "base/memory/referenced.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/flutter/flutter_thread_model.h"
#include "core/common/platform_res_register.h"
#include "core/event/key_event_recognizer.h"

namespace OHOS::Ace::Platform {

using ReleaseCallback = std::function<void()>;

class ACE_FORCE_EXPORT AceViewOhos : public AceView, public Referenced {
public:
    explicit AceViewOhos(int32_t id, std::unique_ptr<FlutterThreadModel> threadModel);
    ~AceViewOhos() override = default;
    static AceViewOhos* CreateView(
        int32_t instanceId, bool useCurrentEventRunner = false, bool usePlatformThread = false);
    static void SurfaceCreated(AceViewOhos* view, OHOS::sptr<OHOS::Rosen::Window> window);
    static void SurfaceChanged(AceViewOhos* view, int32_t width, int32_t height, int32_t orientation,
        WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    static void SurfacePositionChanged(AceViewOhos* view, int32_t posX, int32_t posY);
    static void SetViewportMetrics(AceViewOhos* view, const ViewportConfig& config);

    static void DispatchTouchEvent(AceViewOhos* view, const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    static bool DispatchKeyEvent(AceViewOhos* view, const std::shared_ptr<MMI::KeyEvent>& keyEvent);
    static bool DispatchRotationEvent(AceViewOhos* view, float rotationValue);
    static void DispatchEventToPerf(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);


    static uint32_t GetBackgroundColor();

    void RegisterTouchEventCallback(TouchEventCallback&& callback) override;
    void RegisterDragEventCallback(DragEventCallBack&& callback) override;
    void RegisterKeyEventCallback(KeyEventCallback&& callback) override;
    void RegisterMouseEventCallback(MouseEventCallback&& callback) override;
    void RegisterAxisEventCallback(AxisEventCallback&& callback) override;
    void RegisterRotationEventCallback(RotationEventCallBack&& callback) override;
    void RegisterCardViewPositionCallback(CardViewPositionCallBack&& callback) override {}
    void RegisterCardViewAccessibilityParamsCallback(CardViewAccessibilityParamsCallback&& callback) override {}

    void Launch() override;

    void ProcessTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

    void ProcessMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

    void ProcessAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

    bool ProcessKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent);

    bool ProcessRotationEvent(float rotationValue);
#ifdef ENABLE_DRAG_FRAMEWORK
    void ProcessDragEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
#endif // ENABLE_DRAG_FRAMEWORK
    void ProcessDragEvent(int32_t x, int32_t y, const DragEventAction& action);

    int32_t GetInstanceId() const override
    {
        return instanceId_;
    }

    void RegisterViewChangeCallback(ViewChangeCallback&& callback) override
    {
        viewChangeCallback_ = std::move(callback);
    }

    void RegisterViewPositionChangeCallback(ViewPositionChangeCallback&& callback) override
    {
        viewPositionChangeCallback_ = std::move(callback);
    }

    void RegisterDensityChangeCallback(DensityChangeCallback&& callback) override
    {
        densityChangeCallback_ = std::move(callback);
    }

    void RegisterSystemBarHeightChangeCallback(SystemBarHeightChangeCallback&& callback) override
    {
        systemBarHeightChangeCallback_ = std::move(callback);
    }

    void RegisterSurfaceDestroyCallback(SurfaceDestroyCallback&& callback) override
    {
        surfaceDestroyCallback_ = std::move(callback);
    }

    void RegisterIdleCallback(IdleCallback&& callback) override {}

    void SetPlatformResRegister(const RefPtr<PlatformResRegister>& resRegister)
    {
        resRegister_ = resRegister;
    }

    const RefPtr<PlatformResRegister>& GetPlatformResRegister() const override
    {
        return resRegister_;
    }

    ViewType GetViewType() const override
    {
        return AceView::ViewType::SURFACE_VIEW;
    }

    std::unique_ptr<DrawDelegate> GetDrawDelegate() override
    {
        return nullptr;
    }

    std::unique_ptr<PlatformWindow> GetPlatformWindow() override
    {
        return nullptr;
    }

    bool Dump(const std::vector<std::string>& params) override;
    const void* GetNativeWindowById(uint64_t textureId) override;

    FlutterThreadModel* GetThreadModel() const
    {
        return threadModel_.get();
    }

private:
    void NotifySurfaceChanged(int width, int height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr)
    {
        if (viewChangeCallback_) {
            viewChangeCallback_(width, height, type, rsTransaction);
        }
        width_ = width;
        height_ = height;
    }

    void NotifySurfacePositionChanged(int32_t posX, int32_t posY)
    {
        if (posX_ == posX && posY_ == posY) {
            LOGD("surface position not changed");
            return;
        }
        if (viewPositionChangeCallback_) {
            viewPositionChangeCallback_(posX, posY);
        }
        posX_ = posX;
        posY_ = posY;
    }

    void NotifyDensityChanged(double density) const
    {
        if (densityChangeCallback_) {
            densityChangeCallback_(density);
        }
    }

    void NotifySystemBarHeightChanged(double statusBar, double navigationBar) const
    {
        if (systemBarHeightChangeCallback_) {
            systemBarHeightChangeCallback_(statusBar, navigationBar);
        }
    }

    void NotifySurfaceDestroyed() const
    {
        if (surfaceDestroyCallback_) {
            surfaceDestroyCallback_();
        }
    }

    TouchEventCallback touchEventCallback_;
    MouseEventCallback mouseEventCallback_;
    AxisEventCallback axisEventCallback_;
    RotationEventCallBack rotationEventCallBack_;
    ViewChangeCallback viewChangeCallback_;
    ViewPositionChangeCallback viewPositionChangeCallback_;
    DensityChangeCallback densityChangeCallback_;
    SystemBarHeightChangeCallback systemBarHeightChangeCallback_;
    SurfaceDestroyCallback surfaceDestroyCallback_;
    DragEventCallBack dragEventCallback_;
    int32_t instanceId_ = -1;
    RefPtr<PlatformResRegister> resRegister_;
    KeyEventCallback keyEventCallback_;
    KeyEventRecognizer keyEventRecognizer_;
    // mark the touch event's state, HORIZONTAL_STATE: the event should send to platform, VERTICAL_STATE: should not
    enum class EventState { INITIAL_STATE, HORIZONTAL_STATE, VERTICAL_STATE };

    struct TouchPointInfo {
        Offset offset_;
        EventState eventState_ = EventState::INITIAL_STATE;

        TouchPointInfo() = default;
        explicit TouchPointInfo(const Offset& offset) : offset_(offset) {}
        ~TouchPointInfo() = default;
    };
    std::unordered_map<int32_t, TouchPointInfo> touchPointInfoMap_;

    // TODO: still using flutter threads
    std::unique_ptr<FlutterThreadModel> threadModel_;

    ACE_DISALLOW_COPY_AND_MOVE(AceViewOhos);
};
} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_VIEW_OHOS_H
