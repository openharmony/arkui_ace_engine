/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FORCE_SPLIT_FORCE_SPLIT_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FORCE_SPLIT_FORCE_SPLIT_CONSTANTS_H

namespace OHOS::Ace::NG {

/**
 * Two Column Split
 * When LTR: [ Primary | Secondary ]
 * When RTL: [ Secondary | Primary ]
 */
enum class ForceSplitPageColumnType {
    NONE,
    PRIMARY,
    SECONDARY,
};

enum class ForceSplitAdjustConstraintType {
    NONE,
    ADJUST_TO_PRIMARY,
    ADJUST_TO_SECONDARY
};

enum class ForceSplitTransitionType {
    TRANSITION_IN,
    TRANSITION_OUT,
    TRANSITION_MOVE
};

enum class ForceSplitBehaviorMode {
    DISPLACE,
    NAVIGATION,
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FORCE_SPLIT_FORCE_SPLIT_CONSTANTS_H