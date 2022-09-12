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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_VIEW_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ListView {
public:
    static void Create();
    static void SetSpace(const Dimension& space);
    static void SetInitialIndex(const int32_t& initialIndex);
    static void SetListDirection(Axis axis);
    static void SetEdgeEffect(EdgeEffect edgeEffect);
    static void SetDivider(const V2::ItemDivider& divider);
    static void SetLanes(int32_t lanes);
    static void SetLaneMinLength(const Dimension& laneMinLength);
    static void SetLaneMaxLength(const Dimension& laneMaxLength);
    static void SetListItemAlign(V2::ListItemAlign listItemAlign);
    static void SetCachedCount(const int32_t& cachedCount);
    static void SetOnScroll(OnScrollEvent&& onScroll);
    static void SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin);
    static void SetOnScrollStop(OnScrollStopEvent&& onScrollStop);
    static void SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex);
    static void SetOnReachStart(OnReachEvent&& onReachStart);
    static void SetOnReachEnd(OnReachEvent&& onReachEnd);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_VIEW_H
