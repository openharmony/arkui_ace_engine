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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_DIRTY_FLAG_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_DIRTY_FLAG_H

#include <cstdint>

namespace OHOS::Ace::NG {

using PropertyChangeFlag = uint32_t;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;
// Mark self, parent, children to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;
// Mark self to reLayout.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_LAYOUT = 1 << 1;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_DIFF = 1 << 2;

// Mark self to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF = 1 << 3;

// Mark self and parent to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT = 1 << 4;

// Mark self remeasure due to child size may change, which may mark parent, self and children to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 5;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_RENDER = 1 << 6;
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST = 1 << 7;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_EVENT = 1 << 8;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD = 1 << 9;

struct DirtySwapConfig {
    bool frameSizeChange = false;
    bool frameOffsetChange = false;
    bool contentSizeChange = false;
    bool contentOffsetChange = false;
    bool skipMeasure = false;
    bool skipLayout = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_DIRTY_FLAG_H
