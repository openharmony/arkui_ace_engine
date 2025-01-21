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

#ifndef OHOS_ACE_FRAMEWORK_CJ_ANIMATOR_H
#define OHOS_ACE_FRAMEWORK_CJ_ANIMATOR_H

#include <cstdint>
#include <memory>
#include <string>

#include "ffi_remote_data.h"

#include "base/memory/referenced.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/animation/animator.h"
#include "core/animation/curve.h"
#include "core/animation/curve_animation.h"
#include "core/animation/spring_motion.h"
namespace OHOS::Ace {

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

extern RefPtr<Motion> ParseOptionToMotion(const std::shared_ptr<AnimatorOption>& option);
class AnimatorResultImpl : public OHOS::FFI::FFIData {
    DECL_TYPE(AnimatorResultImpl, OHOS::FFI::FFIData);

public:
    AnimatorResultImpl() = default;
    AnimatorResultImpl(RefPtr<Animator> animator, std::shared_ptr<AnimatorOption> option)
        : animator_(std::move(animator)), option_(std::move(option))
    {
        ApplyOption();
    }
    ~AnimatorResultImpl()
    {
        Destroy();
    }

    RefPtr<Animator> GetAnimator() const
    {
        return animator_;
    }

    std::shared_ptr<AnimatorOption> GetAnimatorOption() const
    {
        return option_;
    }

    const RefPtr<Motion>& GetMotion() const
    {
        return motion_;
    }

    void SetMotion(const RefPtr<Motion>& motion)
    {
        motion_ = motion;
    }

    std::function<void(double)> GetOnframeRef() const
    {
        return onframe_;
    }

    void SetOnframe(int64_t funcId);

    void SetOnFrame(int64_t funcId);

    void SetOnfinish(int64_t funcId);

    void SetOnFinish(int64_t funcId);

    void SetOncancel(int64_t funcId);

    void SetOnCancel(int64_t funcId);

    void SetOnrepeat(int64_t funcId);

    void SetOnRepeat(int64_t funcId);

    void ApplyOption();

    void Destroy();

private:
    RefPtr<Animator> animator_;
    RefPtr<Motion> motion_;
    std::shared_ptr<AnimatorOption> option_;
    std::function<void(double)> onframe_ = nullptr;
    std::function<void(void)> onfinish_ = nullptr;
    std::function<void(void)> oncancel_ = nullptr;
    std::function<void(void)> onrepeat_ = nullptr;
};

} // namespace OHOS::Ace

#endif // #define OHOS_ACE_FRAMEWORK_CJ_ANIMATOR_H
