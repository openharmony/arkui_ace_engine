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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_method.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction SwiperIndicatorPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    return nullptr;
}

void SwiperIndicatorPaintMethod::PaintMask(
    RSCanvas& canvas, RefPtr<SwiperIndicatorPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset)
{}

void SwiperIndicatorPaintMethod::PaintContent(
    RSCanvas& canvas, const RefPtr<SwiperIndicatorPaintProperty>& paintProperty, SizeF contentSize)
{}
} // namespace OHOS::Ace::NG
