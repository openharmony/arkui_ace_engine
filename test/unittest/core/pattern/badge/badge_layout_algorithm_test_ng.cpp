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

#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components/badge/badge_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/badge/badge_layout_algorithm.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string VALUE = "badge value";
const int COUNT = 10;
constexpr Dimension BADGE_FONT_SIZE = 10.0_vp;
constexpr Dimension BADGE_CIRCLE_SIZE = 30.0_vp;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
constexpr float AGE_FONT_SIZE_SCALE = 1.75f;
constexpr float PERCENT_HALF = 0.5f;
} // namespace

class BadgeLayoutAlgorithmTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    OffsetF GetTextDataOffset(const BadgePosition badgePosition, const TextDirection layoutDirection,
        float badgeCircleDiameter, const OffsetF offset, const SizeF parentSize, bool textIsSpace);
    OffsetF GetTextOffsetByPosition(
        const RefPtr<BadgeLayoutProperty> layoutProperty, const RefPtr<GeometryNode>& geometryNode);

protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateChild(const LayoutConstraintF& childLayoutConstraint);
    void CreateFrameNodeAndBadgeModelNG(const Dimension badgeCircleSize);

    RefPtr<FrameNode> frameNode_;
    RefPtr<BadgePattern> pattern_;
    RefPtr<BadgeLayoutProperty> layoutProperty_;
    RefPtr<BadgeAccessibilityProperty> accessibilityProperty_;
};

void BadgeLayoutAlgorithmTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_BADGE);
    auto badgeTheme = BadgeTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(badgeTheme));
}

void BadgeLayoutAlgorithmTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void BadgeLayoutAlgorithmTestNg::SetUp() {}

void BadgeLayoutAlgorithmTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void BadgeLayoutAlgorithmTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<BadgePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<BadgeLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<BadgeAccessibilityProperty>();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> BadgeLayoutAlgorithmTestNg::CreateChild(
    const LayoutConstraintF& childLayoutConstraint)
{
    // add first child to frameNode
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, textGeometryNode, textNode->GetLayoutProperty());
    auto textPattern = textNode->GetPattern<TextPattern>();
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    textLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    return { textNode, textLayoutWrapper };
}

void BadgeLayoutAlgorithmTestNg::CreateFrameNodeAndBadgeModelNG(const Dimension badgeCircleSize)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCircleSize = badgeCircleSize;
    badge.Create(badgeParameters);
    GetInstance();
}

OffsetF BadgeLayoutAlgorithmTestNg::GetTextDataOffset(const BadgePosition badgePosition,
    const TextDirection layoutDirection, float badgeCircleDiameter, const OffsetF offset, const SizeF parentSize,
    bool textIsSpace)
{
    auto badgeCircleRadius = badgeCircleDiameter / 2;
    auto width = parentSize.Width();
    auto height = parentSize.Height();
    OffsetF textOffset;
    if (badgePosition == BadgePosition::RIGHT_TOP) {
        if (layoutDirection == TextDirection::RTL) {
            textOffset = OffsetF(offset.GetX(), offset.GetY());
        } else {
            textOffset = OffsetF(offset.GetX() + width - badgeCircleDiameter, offset.GetY());
        }
        if (!textIsSpace) {
            textOffset += OffsetF(Dimension(2.0_vp).ConvertToPx(), -Dimension(2.0_vp).ConvertToPx());
        }
    } else if (badgePosition == BadgePosition::RIGHT) {
        if (layoutDirection == TextDirection::RTL) {
            textOffset = OffsetF(offset.GetX(), offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        } else {
            textOffset = OffsetF(
                offset.GetX() + width - badgeCircleDiameter, offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        }
    } else if (badgePosition == BadgePosition::LEFT) {
        if (layoutDirection == TextDirection::RTL) {
            textOffset = OffsetF(
                offset.GetX() + width - badgeCircleDiameter, offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        } else {
            textOffset = OffsetF(offset.GetX(), offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        }
    } else {
        textOffset = OffsetF(offset.GetX(), offset.GetY());
    }
    return textOffset;
}

OffsetF BadgeLayoutAlgorithmTestNg::GetTextOffsetByPosition(
    const RefPtr<BadgeLayoutProperty> layoutProperty, const RefPtr<GeometryNode>& geometryNode)
{
    auto offset = geometryNode->GetFrameOffset();
    auto badgePositionX = layoutProperty->GetBadgePositionX();
    auto badgePositionY = layoutProperty->GetBadgePositionY();
    OffsetF textOffset =
        OffsetF(offset.GetX() + badgePositionX->ConvertToPx(), offset.GetY() + badgePositionY->ConvertToPx());
    return textOffset;
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg001
 * @tc.desc: Test badge layout in the upper right corner.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::RIGHT_TOP);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(layoutProperty_->GetBadgePositionValue(), BadgePosition::RIGHT_TOP);
    EXPECT_EQ(layoutProperty_->GetLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg002
 * @tc.desc: Test the layout on the right side of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::RIGHT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(layoutProperty_->GetBadgePositionValue(), BadgePosition::RIGHT);
    EXPECT_EQ(layoutProperty_->GetLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg003
 * @tc.desc: Test the layout on the left side of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg003, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::LEFT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(layoutProperty_->GetBadgePositionValue(), BadgePosition::LEFT);
    EXPECT_EQ(layoutProperty_->GetLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg004
 * @tc.desc: Test the layout on the left side of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg004, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeFontSize = BADGE_FONT_SIZE;
    badgeParameters.badgeCircleSize = BADGE_CIRCLE_SIZE;
    badge.SetIsDefault(false, false);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(layoutProperty_->GetFontSizeIsDefault());
    EXPECT_FALSE(layoutProperty_->GetBadgeSizeIsDefault());
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Value(), 10);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Unit(), DimensionUnit::VP);

    float fontScale = MockPipelineContext::GetCurrentContext()->GetFontScale();
    MockPipelineContext::GetCurrentContext()->SetFontScale(AGE_FONT_SIZE_SCALE);

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Value(), 10);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Unit(), DimensionUnit::VP);

    layoutProperty_->SetIsDefault(true, true);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Value(), 16);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Unit(), DimensionUnit::VP);
    MockPipelineContext::GetCurrentContext()->SetFontScale(fontScale);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg005
 * @tc.desc: In the scence of BadgeCount, test the text direction of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCount = COUNT;
    badge.SetIsDefault(true, true);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    /**
     * @tc.steps: step2. Set RTL to textLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(layoutProperty_->GetFontSizeIsDefault());
    EXPECT_TRUE(layoutProperty_->GetBadgeSizeIsDefault());
    EXPECT_EQ(layoutProperty_->GetNonAutoLayoutDirection(), TextDirection::LTR);
    EXPECT_EQ(textLayoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps: step3. call layout and check layoutDirection.
     */
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(textLayoutProperty->GetNonAutoLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg006
 * @tc.desc: In the scence of BadgeValue, test the text direction of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.SetIsDefault(true, true);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    /**
     * @tc.steps: step2. Set RTL to textLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(layoutProperty_->GetFontSizeIsDefault());
    EXPECT_TRUE(layoutProperty_->GetBadgeSizeIsDefault());
    EXPECT_EQ(layoutProperty_->GetNonAutoLayoutDirection(), TextDirection::LTR);
    EXPECT_EQ(textLayoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps: step3. call layout and check layoutDirection.
     */
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(textLayoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg007
 * @tc.desc: Test the impact of BadgePosition and TextDirection on the GetTextDataOffset method.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.SetIsDefault(true, true);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    /**
     * @tc.steps: step2. Check the results generated by using different BadgePosition as input parameters for bb.
     */
    auto badgeCircleDiameter = BADGE_CIRCLE_SIZE.ConvertToPx();
    OffsetF frameOffset = OffsetF(0, 0);
    SizeF frameSize(400.0, 400.0);
    OffsetF result = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result.GetX(), 370.0f);
    EXPECT_EQ(result.GetY(), 0.0f);

    OffsetF result2 =
        GetTextDataOffset(BadgePosition::RIGHT, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result2.GetX(), 370.0f);
    EXPECT_EQ(result2.GetY(), 185.0f);

    OffsetF result3 =
        GetTextDataOffset(BadgePosition::LEFT, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result3.GetX(), 0.0f);
    EXPECT_EQ(result3.GetY(), 185.0f);

    /**
     * @tc.steps: step3. Check the results generated by using different TextDirection as input parameters for bb.
     */
    OffsetF result4 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::RTL, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result4.GetX(), 0.0f);
    EXPECT_EQ(result4.GetY(), 0.0f);

    OffsetF result5 =
        GetTextDataOffset(BadgePosition::RIGHT, TextDirection::RTL, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result5.GetX(), 0.0f);
    EXPECT_EQ(result5.GetY(), 185.0f);

    OffsetF result6 =
        GetTextDataOffset(BadgePosition::LEFT, TextDirection::RTL, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result6.GetX(), 370.0f);
    EXPECT_EQ(result6.GetY(), 185.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg008
 * @tc.desc: Test the impact of badgeCircleDiameter and badgeCircleRadius on the GetTextDataOffset method.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.SetIsDefault(true, true);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    /**
     * @tc.steps: step2. Check the results generated by using different badgeCircleDiameter as input parameters for bb.
     */
    auto badgeCircleDiameter = BADGE_CIRCLE_SIZE.ConvertToPx() / 2;
    OffsetF frameOffset = OffsetF(0, 0);
    SizeF frameSize(200.0, 50.0);
    OffsetF result = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result.GetX(), 185.0f);
    EXPECT_EQ(result.GetY(), 0.0f);

    auto badgeCircleDiameter2 = BADGE_CIRCLE_SIZE.ConvertToPx();
    OffsetF result2 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter2, frameOffset, frameSize, true);
    EXPECT_EQ(result2.GetX(), 170.0f);
    EXPECT_EQ(result2.GetY(), 0.0f);

    auto badgeCircleDiameter3 = BADGE_CIRCLE_SIZE.ConvertToPx() * 2;
    OffsetF result3 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter3, frameOffset, frameSize, true);
    EXPECT_EQ(result3.GetX(), 140.0f);
    EXPECT_EQ(result3.GetY(), 0.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg009
 * @tc.desc: Test the impact of badgeCircleDiameter and textIsSpace on the GetTextDataOffset method.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.SetIsDefault(true, true);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    /**
     * @tc.steps: step2. Check the results generated by using different textIsSpace and badgeCircleDiameter as input
     * parameters for bb.
     */
    auto badgeCircleDiameter = BADGE_CIRCLE_SIZE.ConvertToPx() / 2;
    OffsetF frameOffset = OffsetF(0, 0);
    SizeF frameSize(200.0, 50.0);
    OffsetF result4 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, false);
    EXPECT_EQ(result4.GetX(), 187.0f);
    EXPECT_EQ(result4.GetY(), -2.0f);

    auto badgeCircleDiameter2 = BADGE_CIRCLE_SIZE.ConvertToPx();
    OffsetF result5 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter2, frameOffset, frameSize, false);
    EXPECT_EQ(result5.GetX(), 172.0f);
    EXPECT_EQ(result5.GetY(), -2.0f);

    auto badgeCircleDiameter3 = BADGE_CIRCLE_SIZE.ConvertToPx() * 2;
    OffsetF result6 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter3, frameOffset, frameSize, false);
    EXPECT_EQ(result6.GetX(), 142.0f);
    EXPECT_EQ(result6.GetY(), -2.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg010
 * @tc.desc: Test the impact of frameOffset and frameSize on the GetTextDataOffset method.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.SetIsDefault(true, true);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    /**
     * @tc.steps: step2. Check the results generated by using different frameSize as input parameters for bb.
     */
    auto badgeCircleDiameter = BADGE_CIRCLE_SIZE.ConvertToPx();
    OffsetF frameOffset = OffsetF(0, 0);
    SizeF frameSize(200.0, 50.0);
    OffsetF result = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result.GetX(), 170.0f);
    EXPECT_EQ(result.GetY(), 0.0f);

    SizeF frameSize2(100.0, 50.0);
    OffsetF result2 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize2, true);
    EXPECT_EQ(result2.GetX(), 70.0f);
    EXPECT_EQ(result2.GetY(), 0.0f);

    SizeF frameSize3(50.0, 100.0);
    OffsetF result3 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize3, true);
    EXPECT_EQ(result3.GetX(), 20.0f);
    EXPECT_EQ(result3.GetY(), 0.0f);

    /**
     * @tc.steps: step3. Check the results generated by using different frameOffset as input parameters for bb.
     */
    OffsetF frameOffset2 = OffsetF(20, 0);
    OffsetF result4 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset2, frameSize, true);
    EXPECT_EQ(result4.GetX(), 190.0f);
    EXPECT_EQ(result4.GetY(), 0.0f);

    OffsetF frameOffset3 = OffsetF(0, 30);
    OffsetF result5 = GetTextDataOffset(
        BadgePosition::RIGHT_TOP, TextDirection::LTR, badgeCircleDiameter, frameOffset3, frameSize, true);
    EXPECT_EQ(result5.GetX(), 170.0f);
    EXPECT_EQ(result5.GetY(), 30.0f);
}
} // namespace OHOS::Ace::NG
