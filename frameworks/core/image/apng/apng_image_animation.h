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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_ANIMATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_ANIMATION_H

#include "core/animation/picture_animation.h"

namespace OHOS::Ace {

class APngImageAnimation : public Animation<int32_t> {
    DECLARE_ACE_TYPE(APngImageAnimation, Animation);
public:
    APngImageAnimation() = default;

    ~APngImageAnimation() override = default;

    // add picture. duration in normalized time.
    bool AddPicture(float duration, const int32_t &pictureInfo);

    void ClearPictures()
    {
        this->duration_ = 0.0f;
        pictures_.clear();
    }

    const int32_t &GetValue() const override
    {
        return currentPicture_->GetPictureInfo();
    }

    // if total normalized duration of all pictures not equals 1.0, scale it to 1.0
    // usually call it after all pictures had been added.
    void AutoScale()
    {
        if (NearZero(this->duration_)) {
            return;
        }
        if (pictures_.empty()) {
            return;
        }

        // already equals to 1.0
        if (NearEqual(this->duration_, NORMALIZED_DURATION_MAX)) {
            return;
        }

        for (const auto &picture : pictures_) {
            picture->UpdateDurationWithScale(this->duration_);
        }

        this->duration_ = NORMALIZED_DURATION_MAX;
    }

    void UpdateAndNotifyPicture(const RefPtr<PictureFrame<int32_t>> &picture);

    /**
     * Use timestamp in order get the true sequence
     * @param normalized
     * @param revserse
     */
    void OnNormalizedTimestampChanged(float normalized, bool revserse) override;

private:
    RefPtr<PictureFrame<int32_t>> currentPicture_ = AceType::MakeRefPtr<PictureFrame<int32_t>>();
    std::vector<RefPtr<PictureFrame<int32_t>>> pictures_;
    int32_t currentIndex_ = -1;
    double totalTime_ = 0;
    double lastFrameTime_ = 0;
};

} // namespace OHOS::Ace


#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_ANIMATION_H
