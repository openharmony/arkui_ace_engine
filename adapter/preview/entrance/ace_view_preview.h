
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_ACE_VIEW_OHOS_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_ACE_VIEW_OHOS_H

#include <memory>

#include "adapter/preview/entrance/ace_resource_register.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/event/key_event_recognizer.h"
#include "core/common/thread_model_impl.h"

namespace OHOS::Ace::Platform {
using ReleaseCallback = std::function<void()>;

class AceViewPreview : public AceView {
    DECLARE_ACE_TYPE(AceViewPreview, AceView);

public:
    AceViewPreview(int32_t instanceId, std::unique_ptr<ThreadModelImpl> threadModelImpl);
    ~AceViewPreview() override = default;
    static AceViewPreview* CreateView(
        int32_t instanceId, bool useCurrentEventRunner = false, bool usePlatformThread = false);

    void Launch() override {}
    int32_t GetInstanceId() const override
    {
        return instanceId_;
    }

    void RegisterTouchEventCallback(TouchEventCallback&& callback) override
    {
        ACE_DCHECK(callback);
        touchEventCallback_ = std::move(callback);
    }
    
    void RegisterKeyEventCallback(KeyEventCallback&& callback) override
    {
        ACE_DCHECK(callback);
        keyEventCallback_ = std::move(callback);
    }
    
    void RegisterMouseEventCallback(MouseEventCallback&& callback) override
    {
        ACE_DCHECK(callback);
        mouseEventCallback_ = std::move(callback);
    }

    void RegisterAxisEventCallback(AxisEventCallback&& callback) override
    {
        ACE_DCHECK(callback);
        axisEventCallback_ = std::move(callback);
    }
    
    void RegisterRotationEventCallback(RotationEventCallBack&& callback) override
    {
        ACE_DCHECK(callback);
        rotationEventCallBack_ = std::move(callback);
    }
    
    void RegisterDragEventCallback(DragEventCallBack&& callback) override {}

    void RegisterCardViewPositionCallback(CardViewPositionCallBack&& callback) override
    {
        ACE_DCHECK(callback);
        cardViewPositionCallBack_ = std::move(callback);
    }

    void RegisterCardViewAccessibilityParamsCallback(CardViewAccessibilityParamsCallback&& callback) override
    {
        ACE_DCHECK(callback);
        cardViewAccessibilityParamsCallback_ = std::move(callback);
    }

    void RegisterViewChangeCallback(ViewChangeCallback&& callback) override
    {
        ACE_DCHECK(callback);
        viewChangeCallback_ = std::move(callback);
    }

    void RegisterViewPositionChangeCallback(ViewPositionChangeCallback&& callback) override {}

    void RegisterDensityChangeCallback(DensityChangeCallback&& callback) override
    {
        ACE_DCHECK(callback);
        densityChangeCallback_ = std::move(callback);
    }

    void RegisterTransformHintChangeCallback(TransformHintChangeCallback&& callback) override {}

    void RegisterSystemBarHeightChangeCallback(SystemBarHeightChangeCallback&& callback) override
    {
        ACE_DCHECK(callback);
        systemBarHeightChangeCallback_ = std::move(callback);
    }

    void RegisterSurfaceDestroyCallback(SurfaceDestroyCallback&& callback) override
    {
        ACE_DCHECK(callback);
        surfaceDestroyCallback_ = std::move(callback);
    }

    void RegisterIdleCallback(IdleCallback&& callback) override
    {
        ACE_DCHECK(callback);
        idleCallback_ = std::move(callback);
    }

    void NotifyDensityChanged(double density) const
    {
        CHECK_NULL_VOID(densityChangeCallback_);
        densityChangeCallback_(density);
    }

    void NotifySystemBarHeightChanged(double statusBar, double navigationBar) const
    {
        CHECK_NULL_VOID(systemBarHeightChangeCallback_);
        systemBarHeightChangeCallback_(statusBar, navigationBar);
    }

    void NotifySurfaceDestroyed() const
    {
        CHECK_NULL_VOID(surfaceDestroyCallback_);
        surfaceDestroyCallback_();
    }

    bool HandleKeyEvent(const KeyEvent& keyEvent) override
    {
        return keyEventCallback_ && keyEventCallback_(keyEvent);
    }

    const RefPtr<PlatformResRegister>& GetPlatformResRegister() const override
    {
        return resRegister_;
    }

    bool Dump(const std::vector<std::string>& params) override
    {
        return false;
    }

    void ProcessIdleEvent(int64_t deadline)
    {
        CHECK_NULL_VOID(idleCallback_);
        idleCallback_(deadline);
    }

    ViewType GetViewType() const override
    {
        return AceView::ViewType::SURFACE_VIEW;
    }

    std::unique_ptr<PlatformWindow> GetPlatformWindow() override
    {
        return nullptr;
    }

    const void* GetNativeWindowById(uint64_t textureId) override
    {
        return nullptr;
    }

    ThreadModelImpl* GetThreadModelImpl() const
    {
        return threadModelImpl_.get();
    }

    void NotifySurfaceChanged(
        int32_t width, int32_t height, WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);

    bool HandleMouseEvent(const MouseEvent& mouseEvent);
    bool HandleAxisEvent(const AxisEvent& axisEvent);
    bool HandleTouchEvent(const TouchEvent& touchEvent) override;
    std::unique_ptr<DrawDelegate> GetDrawDelegate() override;

private:
    int32_t instanceId_ = 0;
    RefPtr<PlatformResRegister> resRegister_ = Referenced::MakeRefPtr<AceResourceRegister>();

    TouchEventCallback touchEventCallback_;
    MouseEventCallback mouseEventCallback_;
    AxisEventCallback axisEventCallback_;
    RotationEventCallBack rotationEventCallBack_;
    CardViewPositionCallBack cardViewPositionCallBack_;
    CardViewAccessibilityParamsCallback cardViewAccessibilityParamsCallback_;
    ViewChangeCallback viewChangeCallback_;
    DensityChangeCallback densityChangeCallback_;
    SystemBarHeightChangeCallback systemBarHeightChangeCallback_;
    SurfaceDestroyCallback surfaceDestroyCallback_;
    IdleCallback idleCallback_;
    KeyEventCallback keyEventCallback_;
    KeyEventRecognizer keyEventRecognizer_;
    std::unique_ptr<ThreadModelImpl> threadModelImpl_;

    ACE_DISALLOW_COPY_AND_MOVE(AceViewPreview);
};
} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_ACE_VIEW_OHOS_H
