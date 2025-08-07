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
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {
enum class PatternLockResourceType {
    SELECTEDCOLOR,
    PATHCOLOR,
    ACTIVECOLOR,
    REGULARCOLOR,
    CIRCLERADIUS,
    SIDELENGTH,
    ACTIVECIRCLECOLOR,
};
class ACE_FORCE_EXPORT PatternLockModel {
public:
    static PatternLockModel* GetInstance();
    virtual ~PatternLockModel() = default;

    virtual RefPtr<V2::PatternLockController> Create();
    virtual void SetPatternComplete(std::function<void(const BaseEventInfo* info)>&& onComplete);
    virtual void SetDotConnect(std::function<void(int32_t)>&& onDotConnect);
    virtual void SetSelectedColor(const Color& selectedColor);
    virtual void SetSelectedColorByUser(bool isByuserSet);
    virtual void SetAutoReset(bool isAutoReset);
    virtual void SetPathColor(const Color& pathColor);
    virtual void SetPathColorByUser(bool isByuserSet);
    virtual void SetActiveColor(const Color& activeColor);
    virtual void SetActiveColorByUser(bool isByuserSet);
    virtual void SetRegularColor(const Color& regularColor);
    virtual void SetRegularColorByUser(bool isByuserSet);
    virtual void SetCircleRadius(const Dimension& radius);
    virtual void SetSideLength(const Dimension& sideLength);
    virtual void SetStrokeWidth(const Dimension& lineWidth);
    virtual void SetActiveCircleColor(const Color& activeCircleColor);
    virtual void SetActiveCircleColorByUser(bool isByuserSet);
    virtual void SetActiveCircleRadius(const Dimension& activeCircleRadius);
    virtual void SetEnableWaveEffect(bool enableWaveEffect);
    virtual void SetEnableForeground(bool enableForeground);
    virtual void SetSkipUnselectedPoint(bool isSkipUnselectedPoint);
    virtual void CreateWithResourceObj(
        PatternLockResourceType PatternLockResourceType, const RefPtr<ResourceObject>& resObj);

private:
    static std::unique_ptr<PatternLockModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_MODEL_H
