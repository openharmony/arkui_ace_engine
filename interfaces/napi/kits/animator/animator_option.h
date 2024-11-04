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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ANIMATOR_OPTION_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ANIMATOR_OPTION_H

#include <cstdint>
#include <memory>
#include <string>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/memory/referenced.h"
#include "core/animation/animator.h"

namespace OHOS::Ace::Napi {

struct AnimatorOption {
    int32_t duration = 0;
    int32_t delay = 0;
    int32_t iterations = 0;
    double begin = 0.0;
    double end = 0.0;
    std::string easing = "ease";
    std::string fill = "none";
    std::string direction = "normal";

    std::string ToString() const
    {
        return "AnimatorOption:[" + std::to_string(duration) + "," + std::to_string(delay) + "," +
               std::to_string(iterations) + "," + std::to_string(begin) + "," + std::to_string(end) + "," + easing +
               "," + fill + "," + direction + "]";
    }
};

class AnimatorResult final {
public:
    AnimatorResult() = default;
    AnimatorResult(RefPtr<Animator>& animator, std::shared_ptr<AnimatorOption>& option)
        : animator_(animator), option_(option)
    {
        ApplyOption();
    }
    ~AnimatorResult() = default;

    RefPtr<Animator> GetAnimator() const
    {
        return animator_;
    }

    std::shared_ptr<AnimatorOption> GetAnimatorOption() const
    {
        return option_;
    }

    napi_ref GetOnframeRef() const
    {
        return onframe_;
    }

    void SetOnframeRef(const napi_ref& onframe)
    {
        onframe_ = onframe;
    }

    napi_ref GetOnfinishRef() const
    {
        return onfinish_;
    }

    void SetOnfinishRef(const napi_ref& onfinish)
    {
        onfinish_ = onfinish;
    }

    napi_ref GetOncancelRef() const
    {
        return oncancel_;
    }

    void SetOncancelRef(const napi_ref& oncancel)
    {
        oncancel_ = oncancel;
    }

    napi_ref GetOnrepeatRef() const
    {
        return onrepeat_;
    }

    void SetOnrepeatRef(const napi_ref& onrepeat)
    {
        onrepeat_ = onrepeat;
    }

    const RefPtr<Motion>& GetMotion() const
    {
        return motion_;
    }

    void SetMotion(const RefPtr<Motion>& motion)
    {
        motion_ = motion;
    }

    void ApplyOption();

    void Destroy(napi_env env);

private:
    RefPtr<Animator> animator_;
    RefPtr<Motion> motion_;
    std::shared_ptr<AnimatorOption> option_;
    napi_ref onframe_ = nullptr;
    napi_ref onfinish_ = nullptr;
    napi_ref oncancel_ = nullptr;
    napi_ref onrepeat_ = nullptr;
};

} // namespace OHOS::Ace::Napi

#endif // #define FOUNDATION_ACE_INTERFACE_INNERKITS_ANIMATOR_RESULT_H
