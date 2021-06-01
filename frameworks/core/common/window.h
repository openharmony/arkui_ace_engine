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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_H

#include <memory>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_page.h"
#include "core/common/platform_window.h"

namespace OHOS::Ace {

class ACE_EXPORT Window {
public:
    explicit Window(std::unique_ptr<PlatformWindow> platformWindow);
    ~Window() = default;

    void RequestFrame();

    void SetRootRenderNode(const RefPtr<RenderNode>& root);

    void OnVsync(uint64_t nanoTimestamp, uint32_t frameCount);

    void SetVsyncCallback(AceVsyncCallback&& callback)
    {
        callback_ = std::move(callback);
    }

private:
    std::unique_ptr<PlatformWindow> platformWindow_;
    AceVsyncCallback callback_;
    bool isRequestVsync_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(Window);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_H
