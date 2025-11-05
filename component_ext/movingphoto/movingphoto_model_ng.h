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

    static RePtr<MovingPhotoNode> MovingPhotoModelNG::CreateMovingPhotoNode(int32_t nodeId, const std::u16string& content);
    static void SetImageSrc(MovingPhotoNode* node, const std::string& src);
    static void SetMuted(MovingPhotoNode* node, bool muted);
    static void SetHdrBrightness(MovingPhotoNode* node, float hdrBrightness);
    static void SetObjectFit(MovingPhotoNode* node, ImageFit objectFit);
    static void SetOnComplete(MovingPhotoNode* node, MovingPhotoEventFunc&& onComplete);
    static void SetOnStart(MovingPhotoNode* node, MovingPhotoEventFunc&& onStart);
    static void SetOnStop(MovingPhotoNode* node, MovingPhotoEventFunc&& onStop);
    static void SetOnPause(MovingPhotoNode* node, MovingPhotoEventFunc&& onPause);
    static void SetOnFinish(MovingPhotoNode* node, MovingPhotoEventFunc&& onFinish);
    static void SetOnError(MovingPhotoNode* node, MovingPhotoEventFunc&& onError);
    static void SetOnPrepared(MovingPhotoNode* node, MovingPhotoEventFunc&& onPrepared);
    static void AutoPlayPeriod(MovingPhotoNode* node, int64_t startTime, int64_t endTime);
    static void AutoPlay(MovingPhotoNode* node, bool isAutoPlay);
    static void RepeatPlay(MovingPhotoNode* node, bool isRepeatPlay);
    static void EnableAnalyzer(MovingPhotoNode* node, bool enabled);
    static void SetImageAIOptions(MovingPhotoNode* node, void* options);
    static void SetMovingPhotoFormat(MovingPhotoNode* node, MovingPhotoFormat format);
    static void SetDynamicRangeMode(MovingPhotoNode* node, DynamicRangeMode rangeMode);
    static void SetWaterMask(MovingPhotoNode* node, bool enabled);
    static void GetXmageHeight(MovingPhotoNode* node);
    static void SetXmagePosition(MovingPhotoNode* node);
    static void MovingPhotoModelNG::SetMovingPhotoController(MovingPhotoNode *frameNode, 
                                                  const RefPtr<MovingPhotoController> &controller);
private:
    static std::unique_ptr<MovingPhotoModelNG> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace::NG
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_MODEL_NG_H
