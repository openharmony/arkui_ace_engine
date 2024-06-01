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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_MODEL_H

#include <functional>
#include <memory>
#include <mutex>

#include "base/utils/macros.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT StepperModel {
public:
    using RoutineCallbackEvent = std::function<void()>;
    using IndexCallbackEvent = std::function<void(int32_t, int32_t)>;
    using IndexChangeEvent = std::function<void(int32_t)>;

    static StepperModel* GetInstance();
    virtual ~StepperModel() = default;

    virtual void Create(uint32_t index) = 0;
    virtual void SetOnFinish(RoutineCallbackEvent&& eventOnFinish) = 0;
    virtual void SetOnSkip(RoutineCallbackEvent&& eventOnSkip) = 0;
    virtual void SetOnChange(IndexCallbackEvent&& eventOnChange) = 0;
    virtual void SetOnNext(IndexCallbackEvent&& eventOnNext) = 0;
    virtual void SetOnPrevious(IndexCallbackEvent&& eventOnPrevious) = 0;
    virtual void SetOnChangeEvent(IndexChangeEvent&& onChangeEvent) = 0;

private:
    static std::unique_ptr<StepperModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_MODEL_H
