/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_KEYFRAME_ANIMATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_KEYFRAME_ANIMATION_H

#include <list>

#include "core/animation/animation.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/animation/evaluator.h"
#include "core/animation/keyframe.h"

namespace OHOS::Ace {

template<typename T>
class KeyframeAnimation : public Animation<T> {
public:
    KeyframeAnimation() = default;

    ~KeyframeAnimation() override = default;

    void AddKeyframe(const RefPtr<Keyframe<T>>& keyframe)
    {
        if (!keyframe) {
            LOGE("add key frame failed. empty keyframe.");
            return;
        }
        if (!keyframe->IsValid()) {
            LOGE("add key frame failed. invalid keyframe.");
            return;
        }

        keyframes_.emplace_back(keyframe);
        ++keyframeNum_;
    }

    const T& GetValue() const override
    {
        return currentValue_;
    }

    const std::list<RefPtr<Keyframe<T>>>& GetKeyframes() const
    {
        return keyframes_;
    }

    void SetEvaluator(const RefPtr<Evaluator<T>>& evaluator)
    {
        if (!evaluator) {
            LOGE("input evaluator is null, use linear evaluator as default.");
            return;
        }
        evaluator_ = evaluator;
    }

    void SetCurve(const RefPtr<Curve>& curve) override
    {
        if (!curve) {
            LOGE("set curve failed. curve is null.");
            return;
        }
        for (auto& keyframe : keyframes_) {
            keyframe->SetCurve(curve);
        }
    }

    void SetStart(const T& value) override
    {
        auto keyframe = AceType::MakeRefPtr<Keyframe<T>>(0.0f, value);
        if (!keyframe) {
            LOGE("add key frame failed. empty keyframe.");
            return;
        }
        if (!keyframe->IsValid()) {
            LOGE("add key frame failed. invalid keyframe.");
            return;
        }

        keyframes_.emplace_front(keyframe);
        ++keyframeNum_;
    }

    T GetEndValue() override
    {
        return keyframes_.back()->GetKeyValue();
    }

private:
    void Calculate(float keyTime)
    {
        if (keyframes_.empty()) {
            return;
        }
        auto begin = keyframes_.front()->GetKeyValue();
        auto end = keyframes_.back()->GetKeyValue();
        // The initial state is maintained when keyTime < 0.
        if (keyTime < 0.0f) {
            currentValue_ = begin;
            return;
        } else if (keyTime > 1.0f || keyframeNum_ == 1) {
            // The final state is maintained when keyTime > 1 or keyframeNum_ = 1.
            currentValue_ = end;
            return;
        }
        auto preKeyframe = keyframes_.front();
        // Iteratively calculate the value between each keyframe.
        for (const auto& keyframe : keyframes_) {
            if (keyTime < keyframe->GetKeyTime()) {
                float preKeyTime = preKeyframe->GetKeyTime();
                if (NearEqual(keyframe->GetKeyTime(), preKeyTime)) {
                    return;
                }
                float intervalKeyTime = (keyTime - preKeyTime) / (keyframe->GetKeyTime() - preKeyTime);
                auto& curve = keyframe->GetCurve();
                begin = preKeyframe->GetKeyValue();
                end = keyframe->GetKeyValue();
                if (curve) {
                    currentValue_ = evaluator_->Evaluate(begin, end, curve->Move(intervalKeyTime));
                    return;
                } else {
                    currentValue_ = evaluator_->Evaluate(begin, end, Curves::EASE->Move(intervalKeyTime));
                    return;
                }
            }
            preKeyframe = keyframe;
        }
        currentValue_ = end;
    }

    void OnNormalizedTimestampChanged(float normalized, bool reverse) override
    {
        if (normalized < NORMALIZED_DURATION_MIN || normalized > NORMALIZED_DURATION_MAX) {
            LOGE("normalized time check failed. normalized: %{public}f", normalized);
            return;
        }
        Calculate(normalized);
        ValueListenable<T>::NotifyListener(currentValue_);
    }

    T currentValue_ {};
    int32_t keyframeNum_ = 0;
    std::list<RefPtr<Keyframe<T>>> keyframes_;
    RefPtr<Evaluator<T>> evaluator_ = AceType::MakeRefPtr<LinearEvaluator<T>>();
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_KEYFRAME_ANIMATION_H
