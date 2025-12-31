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

#include "ui/view/view.h"

#include "base/geometry/shape.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/referenced.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::Kit {

View::View() = default;

View::View(const RefPtr<FrameNode>& node) : node_(node) {}

View::~View() = default;

const RefPtr<FrameNode>& View::GetNode() const
{
    return node_;
}

void View::SetWidth(const CalcDimension& width)
{
    if (width.Unit() == DimensionUnit::CALC) {
        NG::ViewAbstract::SetWidth(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(width.CalcValue()));
    } else {
        NG::ViewAbstract::SetWidth(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(width));
    }
}

void View::SetHeight(const CalcDimension& height)
{
    if (height.Unit() == DimensionUnit::CALC) {
        NG::ViewAbstract::SetHeight(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(height.CalcValue()));
    } else {
        NG::ViewAbstract::SetHeight(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(height));
    }
}

void View::SetTranslate(const NG::TranslateOptions& options)
{
    NG::ViewAbstract::SetTranslate(reinterpret_cast<AceNode*>(node_->GetHandle()), options);
}

void View::SetPivot(const DimensionOffset& value)
{
    NG::ViewAbstract::SetPivot(reinterpret_cast<AceNode*>(node_->GetHandle()), value);
}

void View::SetScale(float x, float y)
{
    NG::VectorF scaleVector = { x, y };
    NG::ViewAbstract::SetScale(reinterpret_cast<AceNode*>(node_->GetHandle()), scaleVector);
}

void View::SetClipPath(const std::string& svgPath)
{
    auto path = AceType::MakeRefPtr<Path>();
    path->SetValue(svgPath);
    NG::ViewAbstract::SetClipShape(reinterpret_cast<AceNode*>(node_->GetHandle()), path);
}

void View::SetOnTouch(TouchEventFunc&& touchEventFunc)
{
    NG::ViewAbstract::SetOnTouch(reinterpret_cast<AceNode*>(node_->GetHandle()), std::move(touchEventFunc));
}

void View::SetOnClick(GestureEventFunc&& clickEventFunc)
{
    NG::ViewAbstract::SetOnClick(reinterpret_cast<AceNode*>(node_->GetHandle()), std::move(clickEventFunc));
}

void View::SetBorderRadius(const Dimension& radius)
{
    NG::ViewAbstract::SetBorderRadius(reinterpret_cast<AceNode*>(node_->GetHandle()), radius);
}

void View::SetBackgroundColor(const Color& color)
{
    NG::ViewAbstract::SetBackgroundColor(reinterpret_cast<AceNode*>(node_->GetHandle()), color);
}

void View::SetBackgroundFilter(const OHOS::Rosen::Filter* backgroundFilter)
{
    NG::ViewAbstract::SetBackgroundFilter(reinterpret_cast<AceNode*>(node_->GetHandle()), backgroundFilter);
}

void View::SetLinearGradientBlur(const NG::LinearGradientBlurPara& blurPara)
{
    NG::ViewAbstract::SetLinearGradientBlur(reinterpret_cast<AceNode*>(node_->GetHandle()), blurPara);
}

void View::SetOpacity(double opacity)
{
    NG::ViewAbstract::SetOpacity(reinterpret_cast<AceNode*>(node_->GetHandle()), opacity);
}

void View::CreateAnimatablePropertyFloat(const std::string& propertyName, float value,
    const std::function<void(float)>& onCallbackEvent, const Ace::PropertyUnit& propertyType)
{
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_VOID(frameNode);
    frameNode->CreateAnimatablePropertyFloat(propertyName, value, onCallbackEvent, propertyType);
}

void View::UpdateAnimatablePropertyFloat(const std::string& propertyName, float value)
{
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateAnimatablePropertyFloat(propertyName, value);
}

void View::DeleteAnimatablePropertyFloat(const std::string& propertyName)
{
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_VOID(frameNode);
    frameNode->DeleteAnimatablePropertyFloat(propertyName);
}

void View::UpdateSafeAreaExpandOpts(const NG::SafeAreaExpandOpts& opts)
{
    NG::ViewAbstract::UpdateSafeAreaExpandOpts(reinterpret_cast<AceNode*>(node_->GetHandle()), opts);
}

void View::CreateAnimatableArithmeticProperty(const std::string& propertyName,
    RefPtr<OHOS::Ace::NG::CustomAnimatableArithmetic>& value,
    std::function<void(const RefPtr<OHOS::Ace::NG::CustomAnimatableArithmetic>&)>& onCallbackEvent)
{
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_VOID(frameNode);
    frameNode->CreateAnimatableArithmeticProperty(propertyName, value, onCallbackEvent);
}

void View::UpdateAnimatableArithmeticProperty(const std::string& propertyName,
    RefPtr<OHOS::Ace::NG::CustomAnimatableArithmetic>& value)
{
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_VOID(frameNode);
    frameNode->UpdateAnimatableArithmeticProperty(propertyName, value);
}

TextDirection View::GetDirection()
{
    return NG::ViewAbstract::GetDirection(reinterpret_cast<AceNode*>(node_->GetHandle()));
}

TextDirection View::GetNonAutoLayoutDirection()
{
    auto direction = GetDirection();
    if (direction != TextDirection::AUTO) {
        return direction;
    }
    return AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
}

} // namespace OHOS::Ace::Kit
