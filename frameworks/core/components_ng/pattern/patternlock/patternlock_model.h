/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_H

#include <mutex>

#include "core/components_ng/pattern/patternlock/patternlock_event_hub.h"
#include "core/components_v2/pattern_lock/pattern_lock_controller.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT PatternLockModel {
public:
    static PatternLockModel* GetInstance();
    virtual ~PatternLockModel() = default;

    virtual RefPtr<V2::PatternLockController> Create() = 0;
    virtual void SetPatternComplete(std::function<void(const BaseEventInfo* info)>&& onComplete) = 0;
    virtual void SetDotConnect(std::function<void(int32_t)>&& onDotConnect) = 0;
    virtual void SetSelectedColor(const Color& selectedColor) = 0;
    virtual void SetAutoReset(bool isAutoReset) = 0;
    virtual void SetPathColor(const Color& pathColor) = 0;
    virtual void SetActiveColor(const Color& activeColor) = 0;
    virtual void SetRegularColor(const Color& regularColor) = 0;
    virtual void SetCircleRadius(const Dimension& radius) = 0;
    virtual void SetSideLength(const Dimension& sideLength) = 0;
    virtual void SetStrokeWidth(const Dimension& lineWidth) = 0;
    virtual void SetActiveCircleColor(const Color& activeCircleColor) = 0;
    virtual void SetActiveCircleRadius(const Dimension& activeCircleRadius) = 0;
    virtual void SetEnableWaveEffect(bool enableWaveEffect) = 0;

private:
    static std::unique_ptr<PatternLockModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_H
