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

#include "test/mock/core/render/mock_paragraph.h"

#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string CREATE_VALUE = "Hello World";
const std::u16string CREATE_VALUE_W = u"Hello World";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension LINE_HEIGHT_VALUE = Dimension(10, DimensionUnit::PX);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
} // namespace

class SpanTestNg : public testing::Test {};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    };

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: SpanSetBaselineOffsetTest002
 * @tc.desc: Test baseline offset of span
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(0.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::PX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest003
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(0.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::VP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest004
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(0.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::FP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest005
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(0.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::LPX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest006
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(0.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest007
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::PX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest008
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::VP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest009
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::FP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest010
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest011
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest012
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(-10.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::PX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest013
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(-10.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::VP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest014
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(-10.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::FP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest015
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(-10.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest016
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(-10.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest017
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10000.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::PX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest018
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10000.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::VP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest019
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10000.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::FP));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest020
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10000.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::LPX));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest021
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10000.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest022
 * @tc.desc: Test baseline offset of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::PX));

    /**
     * @tc.steps: step4. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::VP));

    /**
     * @tc.steps: step5. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::FP));

    /**
     * @tc.steps: step6. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::LPX));

    /**
     * @tc.steps: step7. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest023
 * @tc.desc: Test baseline offset of span and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::PX));

    /**
     * @tc.steps: step4. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::VP));

    /**
     * @tc.steps: step5. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::FP));

    /**
     * @tc.steps: step6. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::LPX));

    /**
     * @tc.steps: step7. test baseline offset
     */
    offset = Dimension(10.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest024
 * @tc.desc: Test baseline offset of span and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(0.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::PX));

    /**
     * @tc.steps: step4. test baseline offset
     */
    offset = Dimension(0.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::VP));

    /**
     * @tc.steps: step5. test baseline offset
     */
    offset = Dimension(0.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::FP));

    /**
     * @tc.steps: step6. test baseline offset
     */
    offset = Dimension(0.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::LPX));

    /**
     * @tc.steps: step7. test baseline offset
     */
    offset = Dimension(0.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(0.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest025
 * @tc.desc: Test baseline offset of span and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(-10.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::PX));

    /**
     * @tc.steps: step4. test baseline offset
     */
    offset = Dimension(-10.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::VP));

    /**
     * @tc.steps: step5. test baseline offset
     */
    offset = Dimension(-10.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::FP));

    /**
     * @tc.steps: step6. test baseline offset
     */
    offset = Dimension(-10.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::LPX));

    /**
     * @tc.steps: step7. test baseline offset
     */
    offset = Dimension(-10.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: SpanSetBaselineOffsetTest026
 * @tc.desc: Test baseline offset of span and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanSetBaselineOffsetTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);

    /**
     * @tc.steps: step3. test baseline offset
     */
    Dimension offset = Dimension(10000.0, DimensionUnit::PX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step4. test baseline offset
     */
    offset = Dimension(10000.0, DimensionUnit::VP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::VP));

    /**
     * @tc.steps: step5. test baseline offset
     */
    offset = Dimension(10000.0, DimensionUnit::FP);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::FP));

    /**
     * @tc.steps: step6. test baseline offset
     */
    offset = Dimension(10000.0, DimensionUnit::LPX);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::LPX));

    /**
     * @tc.steps: step7. test baseline offset
     */
    offset = Dimension(10000.0, DimensionUnit::AUTO);
    spanModelNG.SetBaselineOffset(offset);
    EXPECT_EQ(spanNode->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset002
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset002, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(0.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::PX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset003
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset003, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(0.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::VP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset004
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset004, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(0.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::FP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset005
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset005, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(0.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset006
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset006, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(0.0, DimensionUnit::AUTO);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset007
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset007, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::PX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset008
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset008, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::VP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset009
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset009, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::FP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset010
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset010, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset011
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset011, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10.0, DimensionUnit::AUTO);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset012
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset012, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(-10.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::PX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset013
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset013, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(-10.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::VP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset014
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset014, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(-10.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::FP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset015
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset015, TestSize.Level1)
{
    ImageModelNG imageSpan;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = "";
    imageInfoConfig.moduleName = "";
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(-10.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset016
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset016, TestSize.Level1)
{
    ImageModelNG imageSpan;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = "";
    imageInfoConfig.moduleName = "";
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(-10.0, DimensionUnit::AUTO);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset017
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset017, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10000.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::PX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset018
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset018, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10000.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::VP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset019
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset019, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10000.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::FP));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset020
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset020, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10000.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset021
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset021, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10000.0, DimensionUnit::AUTO);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::AUTO));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset022
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset022, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10000.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::PX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset023
 * @tc.desc: Test ImageSpanView set baseline offset
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset023, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension offset = Dimension(10.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::PX));

    offset = Dimension(10.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::VP));

    offset = Dimension(10.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::FP));

    offset = Dimension(10.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset024
 * @tc.desc: Test ImageSpanView set baseline offset and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset024, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateImageFit(ImageFit::FILL);
    layoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);

    Dimension offset = Dimension(10.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::PX));

    offset = Dimension(10.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::VP));

    offset = Dimension(10.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::FP));

    offset = Dimension(10.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset025
 * @tc.desc: Test ImageSpanView set baseline offset and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset025, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateImageFit(ImageFit::FILL);
    layoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);

    Dimension offset = Dimension(0.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::PX));

    offset = Dimension(0.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::VP));

    offset = Dimension(0.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::FP));

    offset = Dimension(0.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(0.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset026
 * @tc.desc: Test ImageSpanView set baseline offset and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset026, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateImageFit(ImageFit::FILL);
    layoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);

    Dimension offset = Dimension(-10.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::PX));

    offset = Dimension(-10.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::VP));

    offset = Dimension(-10.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::FP));

    offset = Dimension(-10.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(-10.0, DimensionUnit::LPX));
}

/**
 * @tc.name: ImageSpanSetBaselineOffset027
 * @tc.desc: Test ImageSpanView set baseline offset and more attribute settings
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, ImageSpanSetBaselineOffset027, TestSize.Level1)
{
    ImageModelNG imageSpan;
    ImageInfoConfig imageInfoConfig;
    RefPtr<PixelMap> pixMap = nullptr;
    imageInfoConfig.pixelMap = pixMap;
    imageSpan.Create(imageInfoConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateImageFit(ImageFit::FILL);
    layoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);

    Dimension offset = Dimension(10000.0, DimensionUnit::PX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::PX));

    offset = Dimension(10000.0, DimensionUnit::VP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::VP));

    offset = Dimension(10000.0, DimensionUnit::FP);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::FP));

    offset = Dimension(10000.0, DimensionUnit::LPX);
    layoutProperty->UpdateBaselineOffset(offset);
    EXPECT_TRUE(layoutProperty->HasBaselineOffset());
    EXPECT_EQ(layoutProperty->GetBaselineOffset(), Dimension(10000.0, DimensionUnit::LPX));
}
} // namespace OHOS::Ace::NG
