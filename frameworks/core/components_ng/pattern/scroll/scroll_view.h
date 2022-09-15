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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_VIEW_H

#include "base/geometry/axis.h"
#include "core/components/common/properties/color.h"
#include "frameworks/core/event/ace_event_handler.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ScrollView {
public:
    static void Create();
    static void SetAxis(Axis axis);
    static void SetScrollBarColor(const Color& color);
    static void SetScrollBarWidth(const Dimension& width);
    static void SetOnScroll(const EventMarker& onScroll);
    static void SetOnScrollEdge(const EventMarker& onScroll);
    static void SetOnScrollEnd(const EventMarker& onScrollEnd);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_VIEW_H
