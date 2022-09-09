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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_view.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
const ButtonType BUTTON_TYPE_CAPSULE_VALUE = ButtonType::CAPSULE;
const bool STATE_EFFECT_TRUE_VALUE = true;
} // namespace

struct TestProperty {
    std::optional<ButtonType> typeValue = std::nullopt;
    std::optional<bool> stateEffectValue = std::nullopt;
};

class ButtonPatternTestNg : public testing::Test {
public:
protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateChildButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
};

RefPtr<FrameNode> ButtonPatternTestNg::CreateLabelButtonParagraph(
    const std::string& createValue, const TestProperty& testProperty)
{
    ButtonView::CreateWithLabel(createValue);
    if (testProperty.typeValue.has_value())
        ButtonView::SetType(testProperty.typeValue.value());
    if (testProperty.stateEffectValue.has_value())
        ButtonView::SetStateEffect(testProperty.stateEffectValue.value());

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ButtonFrameNodeCreator001
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: zhangxiao
 */
HWTEST_F(ButtonPatternTestNg, ButtonFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT_TRUE_VALUE);

    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);
}
} // namespace OHOS::Ace::NG
