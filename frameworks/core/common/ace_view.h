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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_VIEW_H

#include "flutter/lib/ui/window/pointer_data_packet.h"

#include <chrono>

#include "base/resource/asset_manager.h"
#include "base/utils/noncopyable.h"
#include "core/common/container.h"
#include "core/common/draw_delegate.h"
#include "core/common/platform_res_register.h"
#include "core/common/platform_window.h"

namespace OHOS::Ace {

class AceView {
public:
    enum class ViewType : int32_t {
        SURFACE_VIEW = 0,
        NATIVE_VIEW,
        AGP_COMPONENT,
    };

    AceView() = default;
    virtual ~AceView() = default;

    virtual bool QueryIfWindowInScreen()
    {
        return true;
    }
    virtual void RegisterScreenBroadcast() {}
    virtual void RegisterTouchEventCallback(TouchEventCallback&& callback) = 0;
    virtual void RegisterKeyEventCallback(KeyEventCallback&& callback) = 0;
    virtual void RegisterMouseEventCallback(MouseEventCallback&& callback) = 0;
    virtual void RegisterRotationEventCallback(RotationEventCallBack&& callback) = 0;
    virtual void RegisterCardViewPositionCallback(CardViewPositionCallBack&& callback) = 0;
    virtual void Launch() = 0;
    virtual int32_t GetInstanceId() const = 0;
    virtual const RefPtr<PlatformResRegister>& GetPlatformResRegister() const = 0;

    using CardViewAccessibilityParamsCallback = std::function<void(const std::string& key, bool focus)>;
    virtual void RegisterCardViewAccessibilityParamsCallback(CardViewAccessibilityParamsCallback&& callback) = 0;

    using ViewChangeCallback = std::function<void(int32_t width, int32_t height)>;
    virtual void RegisterViewChangeCallback(ViewChangeCallback&& callback) = 0;

    using DensityChangeCallback = std::function<void(double density)>;
    virtual void RegisterDensityChangeCallback(DensityChangeCallback&& callback) = 0;

    using SystemBarHeightChangeCallbak = std::function<void(double statusBar, double navigationBar)>;
    virtual void RegisterSystemBarHeightChangeCallback(SystemBarHeightChangeCallbak&& callback) = 0;

    using SurfaceDestroyCallback = std::function<void()>;
    virtual void RegisterSurfaceDestroyCallback(SurfaceDestroyCallback&& callback) = 0;

    using IdleCallback = std::function<void(int64_t)>;
    virtual void RegisterIdleCallback(IdleCallback&& callback) = 0;

    using PreDrawCallback = std::function<void()>;
    virtual void RegisterPreDrawCallback(PreDrawCallback&& callback) {}

    using ViewReleaseCallback = std::function<void()>;
    using ViewDestoryCallback = std::function<void(ViewReleaseCallback&&)>;
    virtual void RegisterViewDestroyCallback(ViewDestoryCallback&& callback) = 0;

    virtual bool Dump(const std::vector<std::string>& params) = 0;

    // Use to receive event from glfw window
    virtual bool HandleTouchEvent(std::unique_ptr<flutter::PointerDataPacket> packet)
    {
        return false;
    }
    // Use to receive event from pc previewer
    virtual bool HandleTouchEvent(const TouchPoint& touchEvent)
    {
        return false;
    }

    virtual ViewType GetViewType() const = 0;
    virtual std::unique_ptr<DrawDelegate> GetDrawDelegate() = 0;
    virtual std::unique_ptr<PlatformWindow> GetPlatformWindow() = 0;
    virtual void UpdateWindowBlurRegion(const std::vector<std::vector<float>>& blurRRects) {}
    virtual void UpdateWindowblurDrawOp() {}
    virtual bool GetScale(float& scaleX, float& scaleY)
    {
        return false;
    }

    void SetBackgroundColor(const Color& color)
    {
        std::lock_guard<std::mutex> lock(backgroundColorMutex_);
        backgroundColor_ = color;
    }

    const Color& GetBackgroundColor()
    {
        std::lock_guard<std::mutex> lock(backgroundColorMutex_);
        return backgroundColor_;
    }

    void SetCachePath(const std::string& cachePath)
    {
        cachePath_ = cachePath;
    }

    const std::string& GetCachePath()
    {
        return cachePath_;
    }

    void SetCreateTime(std::chrono::time_point<std::chrono::high_resolution_clock> time)
    {
        createTime_ = time;
    }

    void SetFirstUpDating(std::chrono::time_point<std::chrono::high_resolution_clock> time)
    {
        firstUpdating_ = true;
        firstUpdateBegin_ = time;
    }

    void SetSessionID(const std::string& sessionID)
    {
        sessionID_ = sessionID;
    }

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> createTime_;
    std::chrono::time_point<std::chrono::high_resolution_clock> firstUpdateBegin_;
    std::string sessionID_;
    bool firstUpdating_ = false;

private:
    std::mutex backgroundColorMutex_;
    Color backgroundColor_;
    std::string cachePath_;

    ACE_DISALLOW_COPY_AND_MOVE(AceView);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_VIEW_H
