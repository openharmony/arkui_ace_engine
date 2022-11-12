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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SWIPER_PATTERNS_SWIPER_INDICATOR_INDICATOR_VIEW_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SWIPER_PATTERNS_SWIPER_INDICATOR_INDICATOR_VIEW_NG_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperIndicatorView {
public:
    static void SetLeft(const Dimension& left = Dimension(0.0));
    static void SetTop(const Dimension& top = Dimension(0.0));
    static void SetRight(const Dimension& right = Dimension(0.0));
    static void SetBottom(const Dimension& bottom = Dimension(0.0));
    static void SetSize(const Dimension& size = Dimension(0.0));
    static void SetIndicatorMask(bool isHasIndicatorMask);
    static void SetColor(const Color& color);
    static void SetSelectedColor(const Color& selectedColor);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SWIPER_PATTERNS_SWIPER_INDICATOR_INDICATOR_VIEW_NG_H
