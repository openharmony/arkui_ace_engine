/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef CJFFI_DISPLAY_SYNC_IMPL_H
#define CJFFI_DISPLAY_SYNC_IMPL_H

#include <mutex>
#include <string>

#include "core/components_ng/manager/display_sync/ui_display_sync.h"
#include "display_sync_common.h"
#include "ffi_remote_data.h"
#include "interfaces/native/native_animate.h"

namespace OHOS {
namespace DisplaySync {

class DisplaySync {
public:
    DisplaySync() = delete;
    explicit DisplaySync(const Ace::RefPtr<Ace::UIDisplaySync>& uiDisplaySync)
        : uiDisplaySync_(uiDisplaySync) {}

    ~DisplaySync()
    {
        if (uiDisplaySync_) {
            uiDisplaySync_->DelFromPipelineOnContainer();
        }
    }

    Ace::RefPtr<Ace::UIDisplaySync> GetUIDisplaySync() const
    {
        return uiDisplaySync_;
    }

    void RegisterOnFrameCallback(void (*callback)(CIntervalInfo));
    void UnregisterOnFrameCallback(void (*callback)(CIntervalInfo));

private:
    Ace::RefPtr<Ace::UIDisplaySync> uiDisplaySync_;
    std::mutex mutex_;
    std::function<void(CIntervalInfo)> callbackRef_;
};

class DisplaySyncImpl : public OHOS::FFI::FFIData {
public:
    DisplaySyncImpl();
    ~DisplaySyncImpl() = default;

    int32_t SetExpectedFrameRateRange(CFrameRateRange cRateRange);
    int32_t On(char* type, void (*callback)(CIntervalInfo));
    int32_t Off(char* type, void (*callback)(CIntervalInfo));
    int32_t Start();
    int32_t Stop();

private:
    std::shared_ptr<OHOS::DisplaySync::DisplaySync> displaySync_;
};
}
} // namespace OHOS::DisplaySync

#endif // DISPLAY_SYNC_IMPL_H
