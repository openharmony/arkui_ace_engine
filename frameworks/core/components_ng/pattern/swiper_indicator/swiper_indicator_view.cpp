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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_view.h"

#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void SwiperIndicatorView::SetLeft(const Dimension& left)
{
    ACE_UPDATE_SECOND_CHILD_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Left, left);
}

void SwiperIndicatorView::SetTop(const Dimension& top)
{
    ACE_UPDATE_SECOND_CHILD_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Top, top);
}

void SwiperIndicatorView::SetRight(const Dimension& right)
{
    ACE_UPDATE_SECOND_CHILD_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Right, right);
}

void SwiperIndicatorView::SetBottom(const Dimension& bottom)
{
    ACE_UPDATE_SECOND_CHILD_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Bottom, bottom);
}

void SwiperIndicatorView::SetSize(const Dimension& size)
{
    ACE_UPDATE_SECOND_CHILD_PAINT_PROPERTY(SwiperIndicatorPaintProperty, Size, size);
}

void SwiperIndicatorView::SetIndicatorMask(bool isHasIndicatorMask)
{
    ACE_UPDATE_SECOND_CHILD_PAINT_PROPERTY(SwiperIndicatorPaintProperty, IndicatorMask, isHasIndicatorMask);
}

void SwiperIndicatorView::SetColor(const Color& color)
{
    ACE_UPDATE_SECOND_CHILD_PAINT_PROPERTY(SwiperIndicatorPaintProperty, Color, color);
}

void SwiperIndicatorView::SetSelectedColor(const Color& selectedColor)
{
    ACE_UPDATE_SECOND_CHILD_PAINT_PROPERTY(SwiperIndicatorPaintProperty, SelectedColor, selectedColor);
}

} // namespace OHOS::Ace::NG
