/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef OHOS_ROSEN_WINDOW_H
#define OHOS_ROSEN_WINDOW_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include "refbase.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "vsync_receiver.h"

namespace OHOS::Rosen {
enum class WindowType : uint32_t {
    WINDOW_TYPE_TRANSPARENT_VIEW = 0,
};

enum class WMError : int32_t {
    WM_OK = 0,
};

struct VsyncCallback {
    std::function<void(uint64_t, uint64_t)> onCallback;
};

class WindowOption : public RefBase {
public:
    void SetWindowType(WindowType type)
    {
        type_ = type;
    }

private:
    WindowType type_ = WindowType::WINDOW_TYPE_TRANSPARENT_VIEW;
};

class Window : public RefBase {
public:
    static sptr<Window> Create(const std::string& windowName, sptr<WindowOption>& option);

    explicit Window(std::string windowName);
    ~Window() override = default;

    virtual std::shared_ptr<RSSurfaceNode> GetSurfaceNode() const
    {
        return nullptr;
    }

    virtual std::shared_ptr<RSUIDirector> GetRSUIDirector() const
    {
        return director_;
    }

    virtual WMError Destroy(uint32_t reason = 0, bool isFromInnerkits = false)
    {
        return WMError::WM_OK;
    }

    virtual void RequestVsync(const std::shared_ptr<VsyncCallback>& callback)
    {
        vsyncCallback_ = callback;
    }

    virtual int64_t GetVSyncPeriod() const
    {
        return DEFAULT_VSYNC_PERIOD_NANOSECONDS;
    }

    virtual void FlushFrameRate(uint32_t, int32_t, uint32_t) {}
    virtual void FlushLayoutSize(int32_t, int32_t) {}
    virtual WMError SetKeepScreenOn(bool)
    {
        return WMError::WM_OK;
    }
    virtual WMError SetViewKeepScreenOn(bool)
    {
        return WMError::WM_OK;
    }
    virtual void SetUiDvsyncSwitch(bool, OHOS::FromWhom = OHOS::DEFAULT_FROMWHOM) {}
    virtual uint32_t GetStatusBarHeight() const
    {
        return 0;
    }
    virtual void NotifyExtensionTimeout(int32_t) {}
    virtual WMError NotifySnapshotUpdate()
    {
        return WMError::WM_OK;
    }
    virtual void FlushVsync() {}

    virtual const std::string& GetWindowName() const
    {
        return windowName_;
    }

private:
    static constexpr int64_t DEFAULT_VSYNC_PERIOD_NANOSECONDS = 16'666'666;

    std::string windowName_;
    std::shared_ptr<RSUIDirector> director_ = RSUIDirector::Create(nullptr);
    std::shared_ptr<VsyncCallback> vsyncCallback_;
};
} // namespace OHOS::Rosen

#endif // OHOS_ROSEN_WINDOW_H
