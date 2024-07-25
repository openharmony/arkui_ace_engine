/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/image/apng/apng_image_animation.h"
namespace OHOS::Ace {
/**
 * add image to list
 * only key index and duration
 * @param duration : ms
 * @param pictureInfo
 * @return
 */
bool APngImageAnimation::AddPicture(float duration, const int32_t &pictureInfo)
{
    if (pictures_.empty()) {
        this->duration_ = 0.0f;
    }

    pictures_.emplace_back(AceType::MakeRefPtr<Ace::PictureFrame<int32_t>>(duration, pictureInfo));
    this->duration_ += duration;
    return true;
}

/**
 * Send notify to listener
 * @param picture
 */
void APngImageAnimation::UpdateAndNotifyPicture(const RefPtr<PictureFrame<int32_t>> &picture)
{
    if (!picture) {
        LOGE("update picture is null.");
        return;
    }

    if (currentPicture_ != picture) {
        ValueListenable<int32_t>::NotifyListener(picture->GetPictureInfo());
        currentPicture_ = picture;
    }
}

/**
 * Use timestamp in order get the true sequence
 * @param normalized
 * @param revserse
 */
void APngImageAnimation::OnNormalizedTimestampChanged(float normalized, bool revserse)
{
    totalTime_ += normalized;

    if (pictures_.empty()) {
        return;
    }

    if (currentIndex_ == pictures_.size() - 1) {
        currentIndex_ = -1;
    }

    uint32_t index = 0;
    if (currentIndex_ >= 0) {
        index = currentIndex_ + 1;
    }

    if (index >= pictures_.size()) {
        index = 0;
    }

    auto picture = pictures_[index];
    float duration = picture->GetDuration();
    if (totalTime_ - lastFrameTime_ < duration) {
        return;
    }

    UpdateAndNotifyPicture(picture);
    currentIndex_ = index;
    lastFrameTime_ = totalTime_;
}
} // namespace OHOS::Ace