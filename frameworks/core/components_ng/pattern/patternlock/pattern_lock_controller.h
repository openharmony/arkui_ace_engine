/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERN_LOCK_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERN_LOCK_CONTROLLER_H

#include "core/components_v2/pattern_lock/pattern_lock_controller.h"
#include "frameworks/base/memory/referenced.h"
#include "napi/native_api.h"

namespace OHOS::Ace {
class PatternLockController {
public:
    PatternLockController() = default;
    ~PatternLockController() = default;
    void Reset();
    void SetController(const RefPtr<V2::PatternLockController>& controller);

private:
    RefPtr<V2::PatternLockController> controller_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERN_LOCK_CONTROLLER_H