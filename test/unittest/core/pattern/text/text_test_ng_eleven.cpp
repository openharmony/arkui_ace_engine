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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "test/unittest/core/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/components_ng/pattern/image/image_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class TextTestNgEleven : public TextBases {
public:
};

/**
 * @tc.name: TextModelStaticTest001
 * @tc.desc: test SetFontWeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::FontWeight> validWeight = Ace::FontWeight::W100;
    TextModelStatic::SetFontWeight(frameNode.GetRawPtr(), validWeight);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<Ace::FontWeight> emptyWeight = std::nullopt;
    TextModelStatic::SetFontWeight(frameNode.GetRawPtr(), emptyWeight);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest002
 * @tc.desc: test SetVariableFontWeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest002, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<int32_t> validValue = 1;
    TextModelStatic::SetVariableFontWeight(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    TextModelStatic::SetVariableFontWeight(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest003
 * @tc.desc: test SetEnableVariableFontWeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest003, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<bool> validValue = true;
    TextModelStatic::SetEnableVariableFontWeight(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());

    std::optional<bool> emptyValue = std::nullopt;
    TextModelStatic::SetEnableVariableFontWeight(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest004
 * @tc.desc: test SetMinFontScale func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest004, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<float> validValue = 1.0f;
    TextModelStatic::SetMinFontScale(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());

    std::optional<float> emptyValue = std::nullopt;
    TextModelStatic::SetMinFontScale(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest005
 * @tc.desc: test SetMaxFontScale func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest005, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<float> validValue = 1.0f;
    TextModelStatic::SetMaxFontScale(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<float> emptyValue = std::nullopt;
    TextModelStatic::SetMaxFontScale(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest006
 * @tc.desc: test SetItalicFontStyle func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest006, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::FontStyle> validValue = Ace::FontStyle::NORMAL;
    TextModelStatic::SetItalicFontStyle(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<Ace::FontStyle> emptyValue = std::nullopt;
    TextModelStatic::SetItalicFontStyle(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest007
 * @tc.desc: test SetTextAlign func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest007, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextAlign> validValue = Ace::TextAlign::LEFT;
    TextModelStatic::SetTextAlign(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
    std::optional<Ace::TextAlign> emptyValue = std::nullopt;
    TextModelStatic::SetTextAlign(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
}

/**
 * @tc.name: TextModelStaticTest008
 * @tc.desc: test SetFont func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest008, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto validValue = std::make_optional<Font>();
    TextModelStatic::SetFont(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetFontFamily().has_value());
    TextModelStatic::SetFont(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: TextModelStaticTest009
 * @tc.desc: test SetFontSize func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest009, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetFontSize(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetFontSize(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: TextModelStaticTest010
 * @tc.desc: test SetLineHeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest010, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetLineHeight(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetLineHeight(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest011
 * @tc.desc: test SetLineSpacing func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest011, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetLineSpacing(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetLineSpacing(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest012
 * @tc.desc: test SetTextOverflow func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest012, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextOverflow> validValue = Ace::TextOverflow::CLIP;
    TextModelStatic::SetTextOverflow(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetTextOverflow().has_value());
    std::optional<Ace::TextOverflow> emptyValue = std::nullopt;
    TextModelStatic::SetTextOverflow(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetTextOverflow().has_value());
}

/**
 * @tc.name: TextModelStaticTest013
 * @tc.desc: test SetTextDecoration func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest013, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextDecoration> validValue = Ace::TextDecoration::NONE;
    TextModelStatic::SetTextDecoration(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetTextDecoration().has_value());
    std::optional<Ace::TextDecoration> emptyValue = std::nullopt;
    TextModelStatic::SetTextDecoration(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetTextDecoration().has_value());
}

/**
 * @tc.name: TextModelStaticTest014
 * @tc.desc: test SetLetterSpacing func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest014, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetLetterSpacing(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetLetterSpacing(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: TextModelStaticTest015
 * @tc.desc: test SetTextDecorationStyle func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest015, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextDecorationStyle> validValue = Ace::TextDecorationStyle::SOLID;
    TextModelStatic::SetTextDecorationStyle(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
    std::optional<Ace::TextDecorationStyle> emptyValue = std::nullopt;
    TextModelStatic::SetTextDecorationStyle(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: TextModelStaticTest016
 * @tc.desc: test SetTextCase func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest016, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextCase> validValue = Ace::TextCase::NORMAL;
    TextModelStatic::SetTextCase(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
    std::optional<Ace::TextCase> emptyValue = std::nullopt;
    TextModelStatic::SetTextCase(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: TextModelStaticTest017
 * @tc.desc: test SetMaxLines func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest017, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<uint32_t> validValue = 1;
    TextModelStatic::SetMaxLines(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
    std::optional<uint32_t> emptyValue = std::nullopt;
    TextModelStatic::SetMaxLines(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: TextModelStaticTest018
 * @tc.desc: test SetAdaptMinFontSize func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest018, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetAdaptMinFontSize(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetAdaptMinFontSize().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetAdaptMinFontSize(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest019
 * @tc.desc: test SetAdaptMaxFontSize func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest019, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetAdaptMaxFontSize(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetAdaptMaxFontSize(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest020
 * @tc.desc: test SetFontFamily func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest020, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto validValue = std::make_optional(std::vector<std::string> { "16px" });
    TextModelStatic::SetFontFamily(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetFontFamily().has_value());
    TextModelStatic::SetFontFamily(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: TextModelStaticTest021
 * @tc.desc: test SetTextIndent func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest021, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<CopyOptions> validValue = CopyOptions::None;
    TextModelStatic::SetCopyOption(frameNode.GetRawPtr(), validValue);
    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetTextIndent(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetTextIndent().has_value());

    std::optional<CopyOptions> emptyValue = std::nullopt;
    TextModelStatic::SetCopyOption(frameNode.GetRawPtr(), emptyValue);
    TextModelStatic::SetTextIndent(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
}

/**
 * @tc.name: TextModelStaticTest022
 * @tc.desc: test SetBaselineOffset func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest022, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetBaselineOffset(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetBaselineOffset(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: TextModelStaticTest023
 * @tc.desc: test SetHeightAdaptivePolicy func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest023, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto validValue = TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST;
    TextModelStatic::SetHeightAdaptivePolicy(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetHeightAdaptivePolicy().has_value());
    TextModelStatic::SetHeightAdaptivePolicy(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetHeightAdaptivePolicy().has_value());
}

/**
 * @tc.name: TextModelStaticTest024
 * @tc.desc: test SetTextIndent func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest024, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetTextIndent(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetTextIndent().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetTextIndent(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
}

/**
 * @tc.name: TextModelStaticTest025
 * @tc.desc: test SetWordBreak func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest025, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetWordBreak(frameNode.GetRawPtr(), std::make_optional(WordBreak::BREAK_ALL));
    EXPECT_TRUE(layoutProperty->GetWordBreak().has_value());
    TextModelStatic::SetWordBreak(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest026
 * @tc.desc: test SetTextColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest026, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetTextColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_TRUE(layoutProperty->GetTextColor().has_value());
    TextModelStatic::SetTextColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest027
 * @tc.desc: test SetTextDecorationColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest027, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetTextDecorationColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_TRUE(layoutProperty->GetTextDecorationColor().has_value());
    TextModelStatic::SetTextDecorationColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest028
 * @tc.desc: test SetWordBreak func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest028, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetWordBreak(frameNode.GetRawPtr(), std::make_optional(WordBreak::BREAK_ALL));
    EXPECT_TRUE(layoutProperty->GetWordBreak().has_value());
    TextModelStatic::SetWordBreak(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest029
 * @tc.desc: test SetCaretColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest029, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetCaretColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
    TextModelStatic::SetCaretColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest030
 * @tc.desc: test BindSelectionMenu func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest030, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    SelectMenuParam menuParam;
    TextResponseType textResponseType = TextResponseType::LONG_PRESS;
    TextSpanType textSpanType = TextSpanType::TEXT;
    TextModelStatic::BindSelectionMenu(
        frameNode.GetRawPtr(), textSpanType, textResponseType, nullptr, menuParam);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest031
 * @tc.desc: test SetSelectedBackgroundColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest031, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetSelectedBackgroundColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
    TextModelStatic::SetSelectedBackgroundColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest032
 * @tc.desc: test SetHalfLeading func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest032, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetHalfLeading(frameNode.GetRawPtr(), std::make_optional(true));
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest033
 * @tc.desc: test SetEnableHapticFeedback func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest033, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetEnableHapticFeedback(frameNode.GetRawPtr(), std::make_optional(true));
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest034
 * @tc.desc: test SetSelectionMenuOptions func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest034, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetSelectionMenuOptions(frameNode.GetRawPtr(), nullptr, nullptr);
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest035
 * @tc.desc: test SetLineBreakStrategy func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest035, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetLineBreakStrategy(frameNode.GetRawPtr(), std::make_optional(LineBreakStrategy::BALANCED));
    EXPECT_TRUE(layoutProperty->GetLineBreakStrategy().has_value());
    TextModelStatic::SetLineBreakStrategy(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest036
 * @tc.desc: test SetTextSelectableMode func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest036, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetTextSelectableMode(
        frameNode.GetRawPtr(), std::make_optional(TextSelectableMode::SELECTABLE_FOCUSABLE));
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest037
 * @tc.desc: test SetEllipsisMode func
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEleven, TextModelStaticTest037, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetEllipsisMode(frameNode.GetRawPtr(), std::make_optional(EllipsisMode::HEAD));
    EXPECT_TRUE(layoutProperty->GetEllipsisMode().has_value());
    TextModelStatic::SetEllipsisMode(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetEllipsisMode().has_value());
}

} // namespace OHOS::Ace::NG