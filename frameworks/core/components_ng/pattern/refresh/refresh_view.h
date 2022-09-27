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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RefreshView {
public:
    static void Create();
    static void Pop();
    static void SetRefreshing(bool isRefreshing);
    static void SetRefreshDistance(const Dimension& refreshDistance);
    static void SetUseOffset(bool isUseOffset);
    static void SetIndicatorOffset(const Dimension& indicatorOffset);
    static void SetFriction(int32_t friction);
    static void IsRefresh(bool isRefresh);

    static void SetLoadingDistance(const Dimension& loadingDistance);
    static void SetProgressDistance(const Dimension& progressDistance);
    static void SetProgressDiameter(const Dimension& progressDiameter);
    static void SetMaxDistance(const Dimension& maxDistance);
    static void SetIsShowLastTime(bool IsShowlastTime);
    static void SetShowTimeDistance(const Dimension& showTimeDistance);

    static void SetTextStyle(const TextStyle& textStyle);
    static void SetProgressColor(const Color& progressColor);
    static void SetProgressBackgroundColor(const Color& backgroundColor);
    static void SetOnStateChange(StateChangeEvent&& stateChange);
    static void SetOnRefreshing(RefreshingEvent&& refreshing);
    static void SetChangeEvent(ChangeEvent&& changeEvent);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H