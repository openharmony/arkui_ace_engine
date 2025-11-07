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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_MODEL_NG_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_MODEL_NG_H

#include "movingphoto_event_hub.h"
#include "movingphoto_controller.h"
#include "movingphoto_utils.h"
#include "movingphoto_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT MovingPhotoModelNG {
public:
    static MovingPhotoModelNG* GetInstance();
    virtual ~MovingPhotoModelNG() = default;

    void Create(const RefPtr<MovingPhotoController>& controller);
    void SetImageSrc(const std::string& src);
    void SetImageSrcByPixelMap(RefPtr<PixelMap>& pixMap);
    void SetMuted(bool muted);
    void SetHdrBrightness(float hdrBrightness);
    void SetObjectFit(ImageFit objectFit);
    void SetOnComplete(MovingPhotoEventFunc&& onComplete);
    void SetOnStart(MovingPhotoEventFunc&& onStart);
    void SetOnStop(MovingPhotoEventFunc&& onStop);
    void SetOnPause(MovingPhotoEventFunc&& onPause);
    void SetOnFinish(MovingPhotoEventFunc&& onFinish);
    void SetOnError(MovingPhotoEventFunc&& onError);
    void SetOnPrepared(MovingPhotoEventFunc&& onPrepared);
    void AutoPlayPeriod(int64_t startTime, int64_t endTime);
    void AutoPlay(bool isAutoPlay);
    void RepeatPlay(bool isRepeatPlay);
    void EnableAnalyzer(bool enabled);
    void SetImageAIOptions(void* options);
    void SetMovingPhotoFormat(MovingPhotoFormat format);
    void SetDynamicRangeMode(DynamicRangeMode rangeMode);
    void SetWaterMask(bool enabled);
    void GetXmageHeight();
    void SetXmagePosition();

    static RefPtr<MovingPhotoNode> CreateMovingPhotoNode(int32_t nodeId, const std::u16string& content);
    static void SetImageSrc(MovingPhotoNode* framenode, const std::string& src);
    static void SetMuted(MovingPhotoNode* framenode, bool muted);
    static void SetHdrBrightness(MovingPhotoNode* framenode, float hdrBrightness);
    static void SetObjectFit(MovingPhotoNode* framenode, ImageFit objectFit);
    static void SetOnComplete(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onComplete);
    static void SetOnStart(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onStart);
    static void SetOnStop(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onStop);
    static void SetOnPause(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onPause);
    static void SetOnFinish(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onFinish);
    static void SetOnError(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onError);
    static void SetOnPrepared(MovingPhotoNode* framenode, MovingPhotoEventFunc&& onPrepared);
    static void AutoPlayPeriod(MovingPhotoNode* framenode, int64_t startTime, int64_t endTime);
    static void AutoPlay(MovingPhotoNode* framenode, bool isAutoPlay);
    static void RepeatPlay(MovingPhotoNode* framenode, bool isRepeatPlay);
    static void EnableAnalyzer(MovingPhotoNode* framenode, bool enabled);
    static void SetImageAIOptions(MovingPhotoNode* framenode, void* options);
    static void SetMovingPhotoFormat(MovingPhotoNode* framenode, MovingPhotoFormat format);
    static void SetDynamicRangeMode(MovingPhotoNode* framenode, DynamicRangeMode rangeMode);
    static void SetWaterMask(MovingPhotoNode* framenode, bool enabled);
    static void GetXmageHeight(MovingPhotoNode* framenode);
    static void SetXmagePosition(MovingPhotoNode* framenode);
    static void SetMovingPhotoController(MovingPhotoNode *framenode, const RefPtr<MovingPhotoController> &controller);
private:
    static std::unique_ptr<MovingPhotoModelNG> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace::NG
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_MODEL_NG_H
