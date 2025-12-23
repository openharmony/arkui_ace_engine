/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_REFRESH_CONSTANT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_REFRESH_CONSTANT_H

namespace OHOS::Ace::NG {

enum class RefreshStatus {
    // The default status.
    INACTIVE = 0,
    // While being dragged but not enough to trig refresh.
    DRAG,
    // Dragging enough to refresh, and less than the max distance.
    OVER_DRAG,
    // While it is refreshing.
    REFRESH,
    // While it will scroll back to the top after refreshing.
    DONE,
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_REFRESH_CONSTANT_H