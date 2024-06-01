/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_H

#include <mutex>

#include "base/memory/ace_type.h"
#include "core/components/image/image_animator_component.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ImageAnimatorModel {
public:
    static ImageAnimatorModel* GetInstance();
    virtual ~ImageAnimatorModel() = default;

    virtual void Create() = 0;
    virtual void SetImages(const std::vector<ImageProperties>& images) = 0;
    virtual void SetState(int32_t state) = 0;
    virtual void SetDuration(int32_t duration) = 0;
    virtual void SetIteration(int32_t iteration) = 0;
    virtual void SetFillMode(int32_t fillMode) = 0;
    virtual void SetPreDecode(int32_t preDecode) = 0;
    virtual void SetIsReverse(bool isReverse) = 0;
    virtual void SetFixedSize(bool fixedSize) = 0;
    virtual void SetOnStart(std::function<void()>&& OnStart) = 0;
    virtual void SetOnPause(std::function<void()>&& OnPause) = 0;
    virtual void SetOnRepeat(std::function<void()>&& OnRepeat) = 0;
    virtual void SetOnCancel(std::function<void()>&& OnCancel) = 0;
    virtual void SetOnFinish(std::function<void()>&& OnFinish) = 0;

private:
    static std::unique_ptr<ImageAnimatorModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_H
