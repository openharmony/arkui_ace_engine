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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_VIEW_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperView {
public:
    static RefPtr<SwiperController> Create();
    static void SetDirection(Axis axis);
    static void SetIndex(uint32_t index);
    static void SetAutoPlay(bool autoPlay);
    static void SetAutoPlayInterval(uint32_t interval);
    static void SetDuration(uint32_t duration);
    static void SetCurve(const RefPtr<Curve>& curve);
    static void SetLoop(bool loop);
    static void SetEnabled(bool enabled);
    static void SetDisableSwipe(bool disableSwipe);
    static void SetEdgeEffect(EdgeEffect EdgeEffect);
    static void SetDisplayMode(SwiperDisplayMode displayMode);
    static void SetDisplayCount(int32_t displayCount);
    static void SetShowIndicator(bool showIndicator);
    static void SetItemSpace(const Dimension& itemSpace);
    static void SetCachedCount(int32_t cachedCount);
    static void SetOnChange(ChangeEvent&& onChange);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_VIEW_H
