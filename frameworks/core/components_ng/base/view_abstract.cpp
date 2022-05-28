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

#include "core/components_ng/base/view_abstract.h"

#include <memory>

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/modifier/layout/layout_weight_modifier.h"
#include "core/components_ng/modifier/layout/padding_modifier.h"
#include "core/components_ng/modifier/layout/size_modifier.h"
#include "core/components_ng/modifier/render/bg_color_modifier.h"

namespace OHOS::Ace::NG {

void ViewAbstract::Width(const CalcLength& width)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(WidthModifier(width));
}

void ViewAbstract::Height(const CalcLength& height)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(HeightModifier(height));
}

void ViewAbstract::BackgroundColor(const Color& color)
{
    ViewStackProcessor::GetInstance()->PushRenderContextTask(BgColorModifier(color));
}

void ViewAbstract::LayoutWeight(int32_t value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(LayoutWeightModifier(static_cast<float>(value)));
}

void ViewAbstract::Padding(const CalcLength& value)
{
    PaddingProperty padding;
    padding.SetEdges(value);
    ViewStackProcessor::GetInstance()->PushLayoutTask(PaddingModifier(padding));
}

void ViewAbstract::Padding(const PaddingProperty& value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(PaddingModifier(value));
}

void ViewAbstract::Pop()
{
    ViewStackProcessor::GetInstance()->Pop();
}

} // namespace OHOS::Ace::NG
