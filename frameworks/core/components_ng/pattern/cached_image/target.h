/*
 * Copyright (C) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_TARGET_H
#define INTERFACES_KITS_NATIVE_INCLUDE_TARGET_H

#include <pixel_map.h>
#include <refbase.h>

namespace OHOS {
namespace Media {

using OnSizeReadyCallback = std::function<void(int32_t width, int32_t height)>;
using OnSourceSizeReadyCallback = std::function<void(uint64_t requestId, uint64_t identifier,
    int32_t width, int32_t height, bool isFromUiThread)>;
using OnRequestCompleteCallback = std::function<void(uint64_t requestId, uint64_t identifier,
    const std::shared_ptr<OHOS::Media::PixelMap>& pixelMap,
    const std::string& message, bool isFromUiThread)>;

class Target : public RefBase {
public:
    Target() = default;
    virtual ~Target() = default;

    /**
     * Callback on request completed.
     *
     * @param requestId Id of request.
     * @param identifier Identifier for unique identification.
     * @param pixelMap Requested pixelMap, null means request failed.
     * @param message Message representing final request state.
     * @param isFromUiThread True means callbacked from UI thread, otherwise from child thread.
     */
    virtual void OnComplete(uint64_t requestId, uint64_t identifier, const std::shared_ptr<PixelMap>& pixelMap,
        const std::string& message, bool isFromUiThread) = 0;

    /**
     * Callback on request Progressing.
     *
     * @param requestId Id of request.
     * @param identifier Identifier for unique identification.
     * @param curProgress The data size which has downloaded.
     * @param totalProgress The data size of total data.
     * @param isFromUiThread True means callbacked from UI thread, otherwise from child thread.
     */
    virtual void OnProgress(uint64_t requestId, uint64_t identifier, uint32_t curProgress, uint32_t totalProgress,
        bool isFromUiThread) {}

    /**
     * Notify setting source size.
     *
     * @param requestId Id of request.
     * @param identifier Identifier for unique identification.
     * @param width Source width.
     * @param height Source height.
     * @param isFromUiThread True means notify from UI thread, otherwise from child thread.
     */
    virtual void SetSourceSize(uint64_t requestId, uint64_t identifier,
        int32_t width, int32_t height, bool isFromUiThread) {}

    void OnSizeReady(int32_t width, int32_t height)
    {
        if (sizeReadyCallback_ != nullptr) {
            sizeReadyCallback_(width, height);
        }
    }

    void RegisterSizeReadyCallback(OnSizeReadyCallback&& callback)
    {
        sizeReadyCallback_ = std::move(callback);
    }

    // Do not register progress callback by default
    virtual bool CheckProgressCallbackRegister()
    {
        return false;
    }

protected:
    OnSizeReadyCallback sizeReadyCallback_;
};

} // namespace Media
} // namespace OHOS

#endif // INTERFACES_KITS_NATIVE_INCLUDE_TARGET_H