/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_CONTAINER_WINDOW_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_CONTAINER_WINDOW_MANAGER_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/system_bar/system_bar_style.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {

using WindowCallback = std::function<void(void)>;
using WindowModeCallback = std::function<WindowMode(void)>;
using WindowTypeCallback = std::function<WindowType(void)>;
using WindowSetMaximizeModeCallback = std::function<void(MaximizeMode)>;
using WindowGetMaximizeModeCallback = std::function<MaximizeMode(void)>;
using GetSystemBarStyleCallback = std::function<RefPtr<SystemBarStyle>(void)>;
using SetSystemBarStyleCallback = std::function<void(const RefPtr<SystemBarStyle>&)>;
using WindowGetStartMoveFlagCallback = std::function<uint32_t(void)>;
using GetFreeMultiWindowModeEnabledStateCallback = std::function<bool(void)>;
using WindowCallNativeCallback = std::function<void(const std::string&, const std::string&)>;

class WindowManager : public virtual AceType {
    DECLARE_ACE_TYPE(WindowManager, AceType);

public:
    WindowManager() = default;
    ~WindowManager() override = default;

    void SetAppIconId(int32_t id)
    {
        appIconId_ = id;
    }

    int32_t GetAppIconId() const
    {
        return appIconId_;
    }

    void SetAppLabelId(int32_t id)
    {
        appLabelId_ = id;
    }

    int32_t GetAppLabelId() const
    {
        return appLabelId_;
    }

    void SetWindowMinimizeCallBack(WindowCallback&& callback)
    {
        windowMinimizeCallback_ = std::move(callback);
    }

    void SetWindowMaximizeCallBack(WindowCallback&& callback)
    {
        windowMaximizeCallback_ = std::move(callback);
    }

    void SetWindowMaximizeFloatingCallBack(WindowCallback&& callback)
    {
        windowMaximizeFloatingCallback_ = std::move(callback);
    }

    void SetWindowRecoverCallBack(WindowCallback&& callback)
    {
        windowRecoverCallback_ = std::move(callback);
    }

    void SetWindowCloseCallBack(WindowCallback&& callback)
    {
        windowCloseCallback_ = std::move(callback);
    }

    void SetWindowSplitPrimaryCallBack(WindowCallback&& callback)
    {
        windowSplitPrimaryCallback_ = std::move(callback);
    }

    void SetWindowSplitSecondaryCallBack(WindowCallback&& callback)
    {
        windowSplitSecondaryCallback_ = std::move(callback);
    }

    void SetWindowGetModeCallBack(WindowModeCallback&& callback)
    {
        windowGetModeCallback_ = std::move(callback);
    }

    void SetWindowGetTypeCallBack(WindowTypeCallback&& callback)
    {
        windowGetTypeCallback_ = std::move(callback);
    }

    void SetWindowStartMoveCallBack(WindowCallback&& callback)
    {
        windowStartMoveCallback_ = std::move(callback);
    }

    void SetGetWindowStartMoveFlagCallBack(WindowGetStartMoveFlagCallback&& callback)
    {
        WindowGetStartMoveFlagCallback_ = callback;
    }

    void SetWindowSetMaximizeModeCallBack(WindowSetMaximizeModeCallback&& callback)
    {
        windowSetMaximizeModeCallback_ = std::move(callback);
    }

    void SetWindowGetMaximizeModeCallBack(WindowGetMaximizeModeCallback&& callback)
    {
        windowGetMaximizeModeCallback_ = std::move(callback);
    }

    void SetGetSystemBarStyleCallBack(GetSystemBarStyleCallback&& callback)
    {
        getSystemBarStyleCallback_ = std::move(callback);
    }

    void SetSetSystemBarStyleCallBack(SetSystemBarStyleCallback&& callback)
    {
        setSystemBarStyleCallback_ = std::move(callback);
    }

    void SetGetFreeMultiWindowModeEnabledStateCallback(GetFreeMultiWindowModeEnabledStateCallback&& callback)
    {
        getFreeMultiWindowModeEnabledStateCallback_ = std::move(callback);
    }

    void SetPerformBackCallback(WindowCallback&& callback)
    {
        windowPerformBackCallback_ = callback;
    }

    void SetWindowCallNativeCallback(WindowCallNativeCallback&& callback)
    {
        callNativeCallback_ = std::move(callback);
    }

    void FireWindowCallNativeCallback(const std::string& name, const std::string& value)
    {
        if (callNativeCallback_) {
            callNativeCallback_(name, value);
        }
    }

    void WindowMinimize() const
    {
        if (windowMinimizeCallback_) {
            windowMinimizeCallback_();
        }
    }

    void WindowMaximize(bool supportFloatingMaximize = false)
    {
        if (supportFloatingMaximize && windowMaximizeFloatingCallback_) {
            windowMaximizeFloatingCallback_();
            maximizeMode_ = GetWindowMaximizeMode();
        }
        if (!supportFloatingMaximize && windowMaximizeCallback_) {
            windowMaximizeCallback_();
        }
    }

    void WindowRecover()
    {
        if (windowRecoverCallback_) {
            windowRecoverCallback_();
            maximizeMode_ = MaximizeMode::MODE_RECOVER;
        }
    }

    void FireWindowSplitCallBack(bool isPrimary = true) const
    {
        if (isPrimary && windowSplitPrimaryCallback_) {
            windowSplitPrimaryCallback_();
        }
        if (!isPrimary && windowSplitSecondaryCallback_) {
            windowSplitSecondaryCallback_();
        }
    }

    void WindowClose() const
    {
        if (windowCloseCallback_) {
            windowCloseCallback_();
        }
    }

    void WindowStartMove() const
    {
        if (windowStartMoveCallback_) {
            windowStartMoveCallback_();
        }
    }

    void WindowPerformBack() const
    {
        if (windowPerformBackCallback_) {
            windowPerformBackCallback_();
        }
    }

    bool GetWindowStartMoveFlag() const
    {
        if (WindowGetStartMoveFlagCallback_) {
            return WindowGetStartMoveFlagCallback_();
        }
        return false;
    }

    WindowMode GetWindowMode() const
    {
        if (windowGetModeCallback_) {
            return windowGetModeCallback_();
        }
        return WindowMode::WINDOW_MODE_UNDEFINED;
    }

    WindowType GetWindowType() const
    {
        if (windowGetTypeCallback_) {
            return windowGetTypeCallback_();
        }
        return WindowType::WINDOW_TYPE_UNDEFINED;
    }
     
    void SetWindowMaximizeMode(MaximizeMode mode)
    {
        if (windowSetMaximizeModeCallback_) {
            windowSetMaximizeModeCallback_(mode);
        }
    }

    MaximizeMode GetWindowMaximizeMode() const
    {
        if (windowGetMaximizeModeCallback_) {
            return windowGetMaximizeModeCallback_();
        }
        return MaximizeMode::MODE_RECOVER;
    }

    MaximizeMode GetCurrentWindowMaximizeMode() const
    {
        return maximizeMode_;
    }
    
    void SetCurrentWindowMaximizeMode(MaximizeMode mode)
    {
        maximizeMode_ = mode;
    }

    RefPtr<SystemBarStyle> GetSystemBarStyle()
    {
        if (getSystemBarStyleCallback_) {
            return getSystemBarStyleCallback_();
        }
        return nullptr;
    }

    void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style)
    {
        if (setSystemBarStyleCallback_) {
            setSystemBarStyleCallback_(style);
        }
    }

    bool GetFreeMultiWindowModeEnabledState() const
    {
        if (getFreeMultiWindowModeEnabledStateCallback_) {
            return getFreeMultiWindowModeEnabledStateCallback_();
        }
        return false;
    }

private:
    int32_t appLabelId_ = 0;
    int32_t appIconId_ = 0;
    MaximizeMode maximizeMode_ = MaximizeMode::MODE_RECOVER;
    WindowCallback windowMinimizeCallback_;
    WindowCallback windowRecoverCallback_;
    WindowCallback windowCloseCallback_;
    WindowCallback windowSplitPrimaryCallback_;
    WindowCallback windowSplitSecondaryCallback_;
    WindowCallback windowStartMoveCallback_;
    WindowCallback windowPerformBackCallback_;
    WindowGetStartMoveFlagCallback WindowGetStartMoveFlagCallback_;
    WindowCallback windowMaximizeCallback_;
    WindowCallback windowMaximizeFloatingCallback_;
    WindowSetMaximizeModeCallback windowSetMaximizeModeCallback_;
    WindowGetMaximizeModeCallback windowGetMaximizeModeCallback_;
    WindowModeCallback windowGetModeCallback_;
    WindowTypeCallback windowGetTypeCallback_;
    GetSystemBarStyleCallback getSystemBarStyleCallback_;
    SetSystemBarStyleCallback setSystemBarStyleCallback_;
    GetFreeMultiWindowModeEnabledStateCallback getFreeMultiWindowModeEnabledStateCallback_;
    WindowCallNativeCallback callNativeCallback_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_CONTAINER_WINDOW_MANAGER_H
