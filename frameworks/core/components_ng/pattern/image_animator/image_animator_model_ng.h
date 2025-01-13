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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_NG_H

#include "core/components_ng/pattern/image_animator/image_animator_model.h"
#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ImageAnimatorModelNG : public OHOS::Ace::ImageAnimatorModel {
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
    void SetAutoMonitorInvisibleArea(bool autoMonitorInvisibleArea = false) override;
    void SetOnStart(std::function<void()>&& OnStart) override;
    void SetOnPause(std::function<void()>&& OnPause) override;
    void SetOnRepeat(std::function<void()>&& OnRepeat) override;
    void SetOnCancel(std::function<void()>&& OnCancel) override;
    void SetOnFinish(std::function<void()>&& OnFinish) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetImages(FrameNode* frameNode, const std::vector<ImageProperties>& images);
    static void SetIsReverse(FrameNode* frameNode, bool isReverse);
    static void SetDuration(FrameNode* frameNode, int32_t duration);
    static void SetState(FrameNode* frameNode, int32_t state);
    static void SetFixedSize(FrameNode* frameNode, bool fixedSize);
    static void SetFillMode(FrameNode* frameNode, int32_t fillMode);
    static void SetIteration(FrameNode* frameNode, int32_t iteration);
    static bool IsReverse(FrameNode* frameNode);
    static int32_t GetDuration(FrameNode* frameNode);
    static int32_t GetState(FrameNode* frameNode);
    static bool IsFixedSize(FrameNode* frameNode);
    static int32_t GetFillMode(FrameNode* frameNode);
    static int32_t GetIteration(FrameNode* frameNode);
    static int32_t GetImagesSize(FrameNode* frameNode);
    static void SetAutoMonitorInvisibleArea(FrameNode* frameNode, bool autoMonitorInvisibleArea = false);
    static void SetOnStart(FrameNode* frameNode, std::function<void()>&& onStart);
    static void SetOnPause(FrameNode* frameNode, std::function<void()>&& onPause);
    static void SetOnRepeat(FrameNode* frameNode, std::function<void()>&& onRepeat);
    static void SetOnCancel(FrameNode* frameNode, std::function<void()>&& onCancel);
    static void SetOnFinish(FrameNode* frameNode, std::function<void()>&& onFinish);
private:
    static RefPtr<ImageAnimatorPattern> GetImageAnimatorPattern();
    static RefPtr<ImageAnimatorPattern> GetImageAnimatorPattern(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_ANIMATOR_IMAGE_ANIMATOR_MODEL_NG_H
