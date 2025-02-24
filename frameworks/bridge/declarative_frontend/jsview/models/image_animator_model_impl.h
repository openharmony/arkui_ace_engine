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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_ANIMATOR_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_ANIMATOR_MODEL_IMPL_H

#include "core/components_ng/pattern/image_animator/image_animator_model.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT ImageAnimatorModelImpl : public OHOS::Ace::ImageAnimatorModel {
public:
    void Create() override;
    void SetImages(const std::vector<ImageProperties>& images) override;
    void SetState(int32_t state) override;
    void SetDuration(int32_t duration) override;
    void SetIteration(int32_t iteration) override;
    void SetFillMode(int32_t fillMode) override;
    void SetPreDecode(int32_t preDecode) override;
    void SetIsReverse(bool isReverse) override;
    void SetFixedSize(bool fixedSize) override;
    void SetAutoMonitorInvisibleArea(bool autoMonitorInvisibleArea = false) override {};
    void SetOnStart(std::function<void()>&& OnStart) override;
    void SetOnPause(std::function<void()>&& OnPause) override;
    void SetOnRepeat(std::function<void()>&& OnRepeat) override;
    void SetOnCancel(std::function<void()>&& OnCancel) override;
    void SetOnFinish(std::function<void()>&& OnFinish) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_ANIMATOR_MODEL_IMPL_H
