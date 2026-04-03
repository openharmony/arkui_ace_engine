/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/json/json_util.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace::NG {

class TextFieldModelStaticTestTwo : public TextInputBases {
public:
};

/**
 * @tc.name: SetMinLines001
 * @tc.desc: Test TextFieldModelStatic SetMinLines with valid value greater than 0
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMinLines001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set MinLines with valid value
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMinLines(node, 5u);

    /**
     * @tc.expected: step1. Should set MinLines to the specified value
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasMinLines());
    EXPECT_EQ(textFieldLayoutProperty->GetMinLinesValue(1u), 5u);
}

/**
 * @tc.name: SetMinLines002
 * @tc.desc: Test TextFieldModelStatic SetMinLines with value 0 (should use MIN_LINES)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMinLines002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set MinLines with value 0
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMinLines(node, 0u);

    /**
     * @tc.expected: step1. Should set MinLines to MIN_LINES (1) when value is 0
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasMinLines());
    EXPECT_EQ(textFieldLayoutProperty->GetMinLinesValue(0u), 1u);
}

/**
 * @tc.name: SetMinLines003
 * @tc.desc: Test TextFieldModelStatic SetMinLines with nullopt (should use MIN_LINES)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMinLines003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set MinLines with nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMinLines(node, std::nullopt);

    /**
     * @tc.expected: step1. Should set MinLines to MIN_LINES (1) when value is nullopt
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasMinLines());
    EXPECT_EQ(textFieldLayoutProperty->GetMinLinesValue(0u), 1u);
}

/**
 * @tc.name: SetMinLines004
 * @tc.desc: Test TextFieldModelStatic SetMinLines with different valid values
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMinLines004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and test different MinLines values
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMinLines(node, 3u);
    EXPECT_EQ(textFieldLayoutProperty->GetMinLinesValue(1u), 3u);

    TextFieldModelStatic::SetMinLines(node, 10u);
    EXPECT_EQ(textFieldLayoutProperty->GetMinLinesValue(1u), 10u);

    /**
     * @tc.expected: step1. Should handle different MinLines values correctly
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasMinLines());
}

/**
 * @tc.name: SetOverflowMode001
 * @tc.desc: Test TextFieldModelStatic SetOverflowMode with CLIP mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetOverflowMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set OverflowMode to CLIP
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetOverflowMode(node, OverflowMode::CLIP);

    /**
     * @tc.expected: step1. Should set OverflowMode to CLIP successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
    EXPECT_EQ(textFieldLayoutProperty->GetOverflowModeValue(OverflowMode::SCROLL), OverflowMode::CLIP);
}

/**
 * @tc.name: SetOverflowMode002
 * @tc.desc: Test TextFieldModelStatic SetOverflowMode with SCROLL mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetOverflowMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set OverflowMode to SCROLL
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetOverflowMode(node, OverflowMode::SCROLL);

    /**
     * @tc.expected: step1. Should set OverflowMode to SCROLL successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
    EXPECT_EQ(textFieldLayoutProperty->GetOverflowModeValue(OverflowMode::CLIP), OverflowMode::SCROLL);
}

/**
 * @tc.name: SetOverflowMode003
 * @tc.desc: Test TextFieldModelStatic SetOverflowMode with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetOverflowMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set OverflowMode to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetOverflowMode(node, OverflowMode::CLIP);
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
    TextFieldModelStatic::SetOverflowMode(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset OverflowMode successfully
     */
    EXPECT_FALSE(textFieldLayoutProperty->HasOverflowMode());
}

/**
 * @tc.name: SetOverflowMode004
 * @tc.desc: Test TextFieldModelStatic SetOverflowMode with mode switching
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetOverflowMode004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and test mode switching
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetOverflowMode(node, OverflowMode::CLIP);
    EXPECT_EQ(textFieldLayoutProperty->GetOverflowModeValue(OverflowMode::SCROLL), OverflowMode::CLIP);

    TextFieldModelStatic::SetOverflowMode(node, OverflowMode::SCROLL);
    EXPECT_EQ(textFieldLayoutProperty->GetOverflowModeValue(OverflowMode::CLIP), OverflowMode::SCROLL);

    /**
     * @tc.expected: step1. Should handle mode switching correctly
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
}

/**
 * @tc.name: SetSelectDetectEnable001
 * @tc.desc: Test TextFieldModelStatic SetSelectDetectEnable with true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetSelectDetectEnable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set SelectDetectEnable to true
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetSelectDetectEnable(node, true);

    /**
     * @tc.expected: step1. Should set SelectDetectEnable to true successfully
     */
    EXPECT_TRUE(pattern->GetSelectDetectEnable());
}

/**
 * @tc.name: SetSelectDetectEnable002
 * @tc.desc: Test TextFieldModelStatic SetSelectDetectEnable with false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetSelectDetectEnable002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set SelectDetectEnable to false
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetSelectDetectEnable(node, false);

    /**
     * @tc.expected: step1. Should set SelectDetectEnable to false successfully
     */
    EXPECT_FALSE(pattern->GetSelectDetectEnable());
}

/**
 * @tc.name: SetSelectDetectEnable003
 * @tc.desc: Test TextFieldModelStatic SetSelectDetectEnable with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetSelectDetectEnable003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set SelectDetectEnable to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetSelectDetectEnable(node, false);
    EXPECT_FALSE(pattern->GetSelectDetectEnable());
    TextFieldModelStatic::SetSelectDetectEnable(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset SelectDetectEnable to default value (true)
     */
    EXPECT_TRUE(pattern->GetSelectDetectEnable());
}

/**
 * @tc.name: SetSelectDetectEnable004
 * @tc.desc: Test TextFieldModelStatic SetSelectDetectEnable with value switching
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetSelectDetectEnable004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and test value switching
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetSelectDetectEnable(node, true);
    EXPECT_TRUE(pattern->GetSelectDetectEnable());

    TextFieldModelStatic::SetSelectDetectEnable(node, false);
    EXPECT_FALSE(pattern->GetSelectDetectEnable());

    TextFieldModelStatic::SetSelectDetectEnable(node, true);
    EXPECT_TRUE(pattern->GetSelectDetectEnable());

    /**
     * @tc.expected: step1. Should handle value switching correctly
     */
    EXPECT_TRUE(pattern->GetSelectDetectEnable());
}

/**
 * @tc.name: SetScrollBarColor001
 * @tc.desc: Test TextFieldModelStatic SetScrollBarColor with valid color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetScrollBarColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set ScrollBarColor
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    Color scrollBarColor = Color::RED;
    TextFieldModelStatic::SetScrollBarColor(node, scrollBarColor);

    /**
     * @tc.expected: step1. Should set ScrollBarColor successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasScrollBarColor());
    EXPECT_EQ(textFieldLayoutProperty->GetScrollBarColorValue(Color::BLACK), scrollBarColor);
}

/**
 * @tc.name: SetScrollBarColor002
 * @tc.desc: Test TextFieldModelStatic SetScrollBarColor with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetScrollBarColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set ScrollBarColor to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetScrollBarColor(node, Color::BLUE);
    EXPECT_TRUE(textFieldLayoutProperty->HasScrollBarColor());
    TextFieldModelStatic::SetScrollBarColor(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset ScrollBarColor successfully
     */
    EXPECT_FALSE(textFieldLayoutProperty->HasScrollBarColor());
}

/**
 * @tc.name: SetScrollBarColor003
 * @tc.desc: Test TextFieldModelStatic SetScrollBarColor with different colors
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetScrollBarColor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and test different ScrollBarColor values
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetScrollBarColor(node, Color::GREEN);
    EXPECT_EQ(textFieldLayoutProperty->GetScrollBarColorValue(Color::BLACK), Color::GREEN);

    TextFieldModelStatic::SetScrollBarColor(node, Color(0xFF123456));
    EXPECT_EQ(textFieldLayoutProperty->GetScrollBarColorValue(Color::BLACK), Color(0xFF123456));

    TextFieldModelStatic::SetScrollBarColor(node, Color(0xFFABCDEF));
    EXPECT_EQ(textFieldLayoutProperty->GetScrollBarColorValue(Color::BLACK), Color(0xFFABCDEF));

    /**
     * @tc.expected: step1. Should handle different colors correctly
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasScrollBarColor());
}

/**
 * @tc.name: SetIsOnlyBetweenLines001
 * @tc.desc: Test TextFieldModelStatic SetIsOnlyBetweenLines with true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetIsOnlyBetweenLines001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set IsOnlyBetweenLines to true
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetIsOnlyBetweenLines(node, true);

    /**
     * @tc.expected: step1. Should set IsOnlyBetweenLines to true successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasIsOnlyBetweenLines());
    EXPECT_TRUE(textFieldLayoutProperty->GetIsOnlyBetweenLinesValue(false));
}

/**
 * @tc.name: SetIsOnlyBetweenLines002
 * @tc.desc: Test TextFieldModelStatic SetIsOnlyBetweenLines with false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetIsOnlyBetweenLines002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set IsOnlyBetweenLines to false
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetIsOnlyBetweenLines(node, false);

    /**
     * @tc.expected: step1. Should set IsOnlyBetweenLines to false successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasIsOnlyBetweenLines());
    EXPECT_FALSE(textFieldLayoutProperty->GetIsOnlyBetweenLinesValue(true));
}

/**
 * @tc.name: SetIsOnlyBetweenLines003
 * @tc.desc: Test TextFieldModelStatic SetIsOnlyBetweenLines with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetIsOnlyBetweenLines003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set IsOnlyBetweenLines to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetIsOnlyBetweenLines(node, true);
    EXPECT_TRUE(textFieldLayoutProperty->HasIsOnlyBetweenLines());
    TextFieldModelStatic::SetIsOnlyBetweenLines(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset IsOnlyBetweenLines successfully
     */
    EXPECT_FALSE(textFieldLayoutProperty->HasIsOnlyBetweenLines());
}

/**
 * @tc.name: SetMaxLinesMode001
 * @tc.desc: Test TextFieldModelStatic SetMaxLinesMode with CLIP mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMaxLinesMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set MaxLinesMode to CLIP
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMaxLinesMode(node, OverflowMode::CLIP);

    /**
     * @tc.expected: step1. Should set OverflowMode to CLIP via MaxLinesMode
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
    EXPECT_EQ(textFieldLayoutProperty->GetOverflowModeValue(OverflowMode::SCROLL), OverflowMode::CLIP);
}

/**
 * @tc.name: SetMaxLinesMode002
 * @tc.desc: Test TextFieldModelStatic SetMaxLinesMode with SCROLL mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMaxLinesMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set MaxLinesMode to SCROLL
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMaxLinesMode(node, OverflowMode::SCROLL);

    /**
     * @tc.expected: step1. Should set OverflowMode to SCROLL via MaxLinesMode
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
    EXPECT_EQ(textFieldLayoutProperty->GetOverflowModeValue(OverflowMode::CLIP), OverflowMode::SCROLL);
}

/**
 * @tc.name: SetMaxLinesMode003
 * @tc.desc: Test TextFieldModelStatic SetMaxLinesMode with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetMaxLinesMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set MaxLinesMode to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetMaxLinesMode(node, OverflowMode::CLIP);
    EXPECT_TRUE(textFieldLayoutProperty->HasOverflowMode());
    TextFieldModelStatic::SetMaxLinesMode(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset OverflowMode successfully
     */
    EXPECT_FALSE(textFieldLayoutProperty->HasOverflowMode());
}

/**
 * @tc.name: SetCounterTextColor001
 * @tc.desc: Test TextFieldModelStatic SetCounterTextColor with valid color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetCounterTextColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set CounterTextColor
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    Color counterTextColor = Color::RED;
    TextFieldModelStatic::SetCounterTextColor(node, counterTextColor);

    /**
     * @tc.expected: step1. Should set CounterTextColor successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasCounterTextColor());
    EXPECT_EQ(textFieldLayoutProperty->GetCounterTextColorValue(Color::BLACK), counterTextColor);
}

/**
 * @tc.name: SetCounterTextColor002
 * @tc.desc: Test TextFieldModelStatic SetCounterTextColor with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetCounterTextColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set CounterTextColor to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetCounterTextColor(node, Color::BLUE);
    EXPECT_TRUE(textFieldLayoutProperty->HasCounterTextColor());
    TextFieldModelStatic::SetCounterTextColor(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset CounterTextColor successfully
     */
    EXPECT_FALSE(textFieldLayoutProperty->HasCounterTextColor());
}

/**
 * @tc.name: SetCounterTextColor003
 * @tc.desc: Test TextFieldModelStatic SetCounterTextColor with different colors
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetCounterTextColor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and test different CounterTextColor values
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetCounterTextColor(node, Color::GREEN);
    EXPECT_EQ(textFieldLayoutProperty->GetCounterTextColorValue(Color::BLACK), Color::GREEN);

    TextFieldModelStatic::SetCounterTextColor(node, Color(0xFF123456));
    EXPECT_EQ(textFieldLayoutProperty->GetCounterTextColorValue(Color::BLACK), Color(0xFF123456));

    /**
     * @tc.expected: step1. Should handle different colors correctly
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasCounterTextColor());
}

/**
 * @tc.name: SetCounterTextOverflowColor001
 * @tc.desc: Test TextFieldModelStatic SetCounterTextOverflowColor with valid color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetCounterTextOverflowColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set CounterTextOverflowColor
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    Color overflowColor = Color::RED;
    TextFieldModelStatic::SetCounterTextOverflowColor(node, overflowColor);

    /**
     * @tc.expected: step1. Should set CounterTextOverflowColor successfully
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasCounterTextOverflowColor());
    EXPECT_EQ(textFieldLayoutProperty->GetCounterTextOverflowColorValue(Color::BLACK), overflowColor);
}

/**
 * @tc.name: SetCounterTextOverflowColor002
 * @tc.desc: Test TextFieldModelStatic SetCounterTextOverflowColor with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetCounterTextOverflowColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and set CounterTextOverflowColor to nullopt
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetCounterTextOverflowColor(node, Color::BLUE);
    EXPECT_TRUE(textFieldLayoutProperty->HasCounterTextOverflowColor());
    TextFieldModelStatic::SetCounterTextOverflowColor(node, std::nullopt);

    /**
     * @tc.expected: step1. Should reset CounterTextOverflowColor successfully
     */
    EXPECT_FALSE(textFieldLayoutProperty->HasCounterTextOverflowColor());
}

/**
 * @tc.name: SetCounterTextOverflowColor003
 * @tc.desc: Test TextFieldModelStatic SetCounterTextOverflowColor with different colors
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTestTwo, SetCounterTextOverflowColor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node and test different CounterTextOverflowColor values
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto textFieldLayoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto node = Referenced::RawPtr(textFieldNode);

    TextFieldModelStatic::SetCounterTextOverflowColor(node, Color::GREEN);
    EXPECT_EQ(textFieldLayoutProperty->GetCounterTextOverflowColorValue(Color::BLACK), Color::GREEN);

    TextFieldModelStatic::SetCounterTextOverflowColor(node, Color(0xFFABCDEF));
    EXPECT_EQ(textFieldLayoutProperty->GetCounterTextOverflowColorValue(Color::BLACK), Color(0xFFABCDEF));

    /**
     * @tc.expected: step1. Should handle different colors correctly
     */
    EXPECT_TRUE(textFieldLayoutProperty->HasCounterTextOverflowColor());
}

} // namespace OHOS::Ace::NG
