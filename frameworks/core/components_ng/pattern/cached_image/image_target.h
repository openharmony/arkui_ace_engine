/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_TARGET_H
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_TARGET_H

#include "core/components_ng/pattern/cached_image/target.h"

namespace OHOS {
namespace Media {

typedef struct {
    OnSourceSizeReadyCallback onSourceSizeReady;
    OnRequestCompleteCallback onRequestComplete;
} TargetListener;

class ImageTarget : public Target {
public:
    ImageTarget() = default;
    ~ImageTarget() = default;

    void OnComplete(uint64_t requestId, uint64_t identifier, const std::shared_ptr<OHOS::Media::PixelMap>& pixelMap,
        const std::string& message, bool isFromUiThread) override
    {
        if (targetListener_.onRequestComplete != nullptr) {
            targetListener_.onRequestComplete(requestId, identifier,
                (pixelMap != nullptr) ? pixelMap : nullptr, message, isFromUiThread);
        }
    }

    void SetSourceSize(uint64_t requestId, uint64_t identifier,
        int32_t width, int32_t height, bool isFromUiThread) override
    {
        if (targetListener_.onSourceSizeReady != nullptr) {
            targetListener_.onSourceSizeReady(requestId, identifier, width, height, isFromUiThread);
        }
    }

    void RegisterTargetListener(const TargetListener& targetListener)
    {
        targetListener_ = targetListener;
    }

    OnSizeReadyCallback GetSizeReadyCallback()
    {
        return [wp = wptr(this)](int32_t width, int32_t height) {
            sptr<Target> target = wp.promote();
            if (target != nullptr) {
                target->OnSizeReady(width, height);
            }
        };
    }

private:
    TargetListener targetListener_;
};

} // namespace Media
} // namespace OHOS

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_TARGET_H