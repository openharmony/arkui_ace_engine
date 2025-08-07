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

#include <functional>
#include <memory>

#include "interfaces/inner_api/ace/viewport_config.h"
#include "key_event.h"
#include "wm/window.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/platform_res_register.h"
#include "core/common/thread_model_impl.h"
#include "core/components_ng/base/frame_node.h"
#include "core/event/key_event_recognizer.h"
#include "core/event/non_pointer_event.h"

namespace OHOS::Ace::Platform {

using ReleaseCallback = std::function<void()>;

class ACE_FORCE_EXPORT AceViewOhos : public AceView {
    DECLARE_ACE_TYPE(AceViewOhos, AceView);
public:
    explicit AceViewOhos(int32_t id, std::unique_ptr<ThreadModelImpl> threadModelImpl);
    ~AceViewOhos() override = default;
    static RefPtr<AceViewOhos> CreateView(
        int32_t instanceId, bool useCurrentEventRunner = false, bool usePlatformThread = false);
    static void SurfaceCreated(const RefPtr<AceViewOhos>& view, OHOS::sptr<OHOS::Rosen::Window> window);
    static void ChangeViewSize(const RefPtr<AceViewOhos>& view, int32_t width, int32_t height);
    static void SurfaceChanged(const RefPtr<AceViewOhos>& view, int32_t width, int32_t height, int32_t orientation,
        WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    static void SurfacePositionChanged(const RefPtr<AceViewOhos>& view, int32_t posX, int32_t posY);
    static void SetViewportMetrics(const RefPtr<AceViewOhos>& view, const ViewportConfig& config);
    static void TransformHintChanged(const RefPtr<AceViewOhos>& view, uint32_t transform);
    static void HandleMouseEvent(const RefPtr<AceViewOhos>& view,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const RefPtr<OHOS::Ace::NG::FrameNode>& node,
        int32_t pointerAction, bool isInjected, int32_t toolType);
    static void DispatchTouchEvent(const RefPtr<AceViewOhos>& view,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr,
        const std::function<void()>& callback = nullptr, bool isInjected = false);
    static bool DispatchKeyEvent(
        const RefPtr<AceViewOhos>& view, const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool isPreIme = false);
    static bool DispatchRotationEvent(const RefPtr<AceViewOhos>& view, float rotationValue);
    static void DispatchEventToPerf(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    static void DispatchEventToPerf(const std::shared_ptr<MMI::KeyEvent>& keyEvent);

    static uint32_t GetBackgroundColor();

    void RegisterTouchEventCallback(TouchEventCallback&& callback) override;
    void RegisterDragEventCallback(DragEventCallBack&& callback) override;
    void RegisterKeyEventCallback(KeyEventCallback&& callback) override;
    void RegisterNonPointerEventCallback(NonPointerEventCallback&& callback) override;
    void RegisterMouseEventCallback(MouseEventCallback&& callback) override;
    void RegisterAxisEventCallback(AxisEventCallback&& callback) override;
    void RegisterRotationEventCallback(RotationEventCallBack&& callback) override;
    void RegisterCardViewPositionCallback(CardViewPositionCallBack&& callback) override {}
    void RegisterCardViewAccessibilityParamsCallback(CardViewAccessibilityParamsCallback&& callback) override {}
    void RegisterCrownEventCallback(CrownEventCallback&& callback) override;
    void Launch() override;

    void ProcessTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr, const std::function<void()>& callback = nullptr,
        bool isInjected = false);

    void ProcessMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr, bool isInjected = false);

    void ProcessAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr, bool isInjected = false);

    bool ProcessKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool isPreIme);

    bool ProcessFocusAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

    void ProcessDigitalCrownEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        bool isInjected = false);

    bool ProcessRotationEvent(float rotationValue);

    void ProcessDragEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr);

    void ProcessDragEvent(int32_t x, int32_t y, const DragEventAction& action,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr);

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

    void RegisterTransformHintChangeCallback(TransformHintChangeCallback&& callback) override
    {
        transformHintChangeCallback_ = std::move(callback);
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

    ThreadModelImpl* GetThreadModelImpl() const
    {
        return threadModelImpl_.get();
    }

private:
    void NotifySurfaceChanged(int width, int height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr)
    {
        width_ = width;
        height_ = height;
        if (viewChangeCallback_) {
            viewChangeCallback_(width, height, type, rsTransaction);
        }
    }

    void ChangeSize(int width, int height)
    {
        width_ = width;
        height_ = height;
    }

    void NotifySurfacePositionChanged(int32_t posX, int32_t posY)
    {
        if (posX_ == posX && posY_ == posY) {
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

    void NotifyTransformHintChanged(uint32_t transform)
    {
        if (transform_ == transform) {
            return;
        }
        if (transformHintChangeCallback_) {
            transformHintChangeCallback_(transform);
        }
        transform_ = transform;
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

    bool ProcessMouseEventWithTouch(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, const MouseEvent& event,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node, const std::function<void()>& markProcess);
    bool ProcessAxisEventWithTouch(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node, bool isInjected);

    TouchEventCallback touchEventCallback_;
    MouseEventCallback mouseEventCallback_;
    AxisEventCallback axisEventCallback_;
    RotationEventCallBack rotationEventCallBack_;
    ViewChangeCallback viewChangeCallback_;
    ViewPositionChangeCallback viewPositionChangeCallback_;
    DensityChangeCallback densityChangeCallback_;
    TransformHintChangeCallback transformHintChangeCallback_;
    SystemBarHeightChangeCallback systemBarHeightChangeCallback_;
    SurfaceDestroyCallback surfaceDestroyCallback_;
    DragEventCallBack dragEventCallback_;
    int32_t instanceId_ = -1;
    RefPtr<PlatformResRegister> resRegister_;
    KeyEventCallback keyEventCallback_;
    NonPointerEventCallback nonPointerEventCallback_;
    CrownEventCallback crownEventCallback_;
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

    std::unique_ptr<ThreadModelImpl> threadModelImpl_;

    OHOS::Ace::PointerEvent axisFakePntEvt_;

    ACE_DISALLOW_COPY_AND_MOVE(AceViewOhos);
};
} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_VIEW_OHOS_H
