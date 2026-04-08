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
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
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
const std::string LONG_VALUE = "badge value badge value";
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
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
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
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::RIGHT_TOP);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::RIGHT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::LEFT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(layoutProperty_->GetFontSizeIsDefault());
    EXPECT_FALSE(layoutProperty_->GetBadgeSizeIsDefault());
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Value(), 10);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Unit(), DimensionUnit::VP);

    float fontScale = MockPipelineContext::GetCurrentContext()->GetFontScale();
    MockPipelineContext::GetCurrentContext()->SetFontScale(AGE_FONT_SIZE_SCALE);

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Value(), 10);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension(1)).Unit(), DimensionUnit::VP);

    layoutProperty_->SetIsDefault(true, true);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);
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

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg0011
 * @tc.desc: Test badge layout in the upper right corner.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg011, TestSize.Level1)
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
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::RIGHT_TOP);
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushUITasks(frameNode_);
    EXPECT_EQ(layoutProperty_->GetBadgePositionValue(), BadgePosition::RIGHT_TOP);
    EXPECT_EQ(layoutProperty_->GetLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg012
 * @tc.desc: Test the layout on the right side of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg012, TestSize.Level1)
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
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::RIGHT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushUITasks(frameNode_);
    EXPECT_EQ(layoutProperty_->GetBadgePositionValue(), BadgePosition::RIGHT);
    EXPECT_EQ(layoutProperty_->GetLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg013
 * @tc.desc: Test the layout on the left side of the badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg013, TestSize.Level1)
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
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    layoutProperty_->UpdateBadgePosition(BadgePosition::LEFT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    layoutProperty_->UpdateIsPositionXy(false);
    FlushUITasks(frameNode_);
    EXPECT_EQ(layoutProperty_->GetBadgePositionValue(), BadgePosition::LEFT);
    EXPECT_EQ(layoutProperty_->GetLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg014
 * @tc.desc: Test AdjustTextOffsetForBadge branch when auto avoidance is enabled.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg014, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT_TOP);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetWithAvoidance.GetY() - offsetWithoutAvoidance.GetY(), Dimension(2.0_vp).ConvertToPx());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg015
 * @tc.desc: Test Layout frame size branch for platform version less than ten.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg015, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeBorderWidth = Dimension(3.0, DimensionUnit::VP);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto frameSizeV10 = badgeTextNode->GetGeometryNode()->GetFrameSize();

    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_FIVE));
    FlushUITasks(frameNode_);
    auto frameSizeV5 = badgeTextNode->GetGeometryNode()->GetFrameSize();

    auto borderWidthPx = Dimension(3.0, DimensionUnit::VP).ConvertToPx() * 2;
    EXPECT_EQ(frameSizeV5.Width() - frameSizeV10.Width(), borderWidthPx);
    EXPECT_EQ(frameSizeV5.Height() - frameSizeV10.Height(), borderWidthPx);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg016
 * @tc.desc: Test PerformMeasureSelf with width match and height fix policies.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg016, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    firstChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT));
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
    secondChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT));
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    LayoutConstraintF constraint;
    constraint.parentIdealSize = OptionalSize<float>(200.0f, 160.0f);
    constraint.maxSize = SizeF(500.0f, 500.0f);
    constraint.minSize = SizeF(0.0f, 0.0f);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    auto layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    layoutAlgorithm->PerformMeasureSelf(AccessibilityManager::RawPtr(layoutWrapper));

    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 200.0f);
    EXPECT_EQ(frameSize.Height(), FIRST_ITEM_HEIGHT);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg017
 * @tc.desc: Test PerformMeasureSelf with width fix and height match policies.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg017, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    firstChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT));
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
    secondChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT));
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    LayoutConstraintF constraint;
    constraint.parentIdealSize = OptionalSize<float>(220.0f, 180.0f);
    constraint.maxSize = SizeF(500.0f, 500.0f);
    constraint.minSize = SizeF(0.0f, 0.0f);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    auto layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    layoutAlgorithm->PerformMeasureSelf(AccessibilityManager::RawPtr(layoutWrapper));

    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), FIRST_ITEM_WIDTH);
    EXPECT_EQ(frameSize.Height(), 180.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg018
 * @tc.desc: Test Measure branch when badge font size is not explicitly set.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg018, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto badgeLayoutAlgorithm = AceType::DynamicCast<BadgeLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(badgeLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(secondChildFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(u"1");
    layoutProperty_->ResetBadgeFontSize();

    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_FALSE(badgeLayoutAlgorithm->hasFontSize_);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg019
 * @tc.desc: Test Measure and Layout branches when badge circle size is zero.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg019, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCircleSize = Dimension(0.0, DimensionUnit::VP);
    badge.SetIsDefault(true, false);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_FIVE));
    FlushUITasks(frameNode_);

    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto badgeTextGeometry = badgeTextNode->GetGeometryNode();
    ASSERT_NE(badgeTextGeometry, nullptr);
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Width(), 0.0f);
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Height(), 0.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg020
 * @tc.desc: Test GetTextDataOffset default branch for unsupported badge position.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg020, TestSize.Level1)
{
    auto badgeCircleDiameter = BADGE_CIRCLE_SIZE.ConvertToPx();
    OffsetF frameOffset(12.0f, 24.0f);
    SizeF frameSize(200.0f, 80.0f);
    OffsetF result =
        GetTextDataOffset(BadgePosition(6), TextDirection::LTR, badgeCircleDiameter, frameOffset, frameSize, true);
    EXPECT_EQ(result.GetX(), frameOffset.GetX());
    EXPECT_EQ(result.GetY(), frameOffset.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg021
 * @tc.desc: Test AdjustTextOffsetForBadge branch for RIGHT position in LTR.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg021, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = LONG_VALUE;
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();
    auto textWidth = badgeTextNode->GetGeometryNode()->GetFrameSize().Width();

    EXPECT_EQ(offsetWithAvoidance.GetX() - offsetWithoutAvoidance.GetX(), badgeCircleDiameter - textWidth);
    EXPECT_LE(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg022
 * @tc.desc: Test AdjustTextOffsetForBadge branch for empty badge value.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg022, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "";
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT_TOP);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg023
 * @tc.desc: Test PerformMeasureSelf constrain branch without layout policy.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg023, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    firstChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(600.0f, 620.0f));
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
    secondChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 100.0f));
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(300.0f, 280.0f);
    constraint.minSize = SizeF(50.0f, 40.0f);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    layoutAlgorithm->PerformMeasureSelf(AccessibilityManager::RawPtr(layoutWrapper));

    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 300.0f);
    EXPECT_EQ(frameSize.Height(), 280.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg024
 * @tc.desc: Test AdjustTextOffsetForBadge branch for RIGHT position in LTR with short text.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg024, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "1";
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();
    auto textWidth = badgeTextNode->GetGeometryNode()->GetFrameSize().Width();

    EXPECT_EQ(offsetWithAvoidance.GetX() - offsetWithoutAvoidance.GetX(), badgeCircleDiameter - textWidth);
    EXPECT_GE(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg025
 * @tc.desc: Test AdjustTextOffsetForBadge branch for LEFT position in RTL with long text.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg025, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = LONG_VALUE;
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::LEFT);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();
    auto textWidth = badgeTextNode->GetGeometryNode()->GetFrameSize().Width();

    EXPECT_EQ(offsetWithAvoidance.GetX() - offsetWithoutAvoidance.GetX(), badgeCircleDiameter - textWidth);
    EXPECT_LE(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg026
 * @tc.desc: Test AdjustTextOffsetForBadge branch for LEFT position in RTL with short text.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg026, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "1";
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::LEFT);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();
    auto textWidth = badgeTextNode->GetGeometryNode()->GetFrameSize().Width();

    EXPECT_EQ(offsetWithAvoidance.GetX() - offsetWithoutAvoidance.GetX(), badgeCircleDiameter - textWidth);
    EXPECT_GE(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg027
 * @tc.desc: Test AdjustTextOffsetForBadge keeps X offset unchanged for RIGHT position in RTL.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg027, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg028
 * @tc.desc: Test AdjustTextOffsetForBadge keeps X offset unchanged for LEFT position in LTR.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg028, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::LEFT);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg029
 * @tc.desc: Test AdjustTextOffsetForBadge keeps offsets unchanged for RIGHT_TOP position in RTL with empty text.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg029, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "";
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT_TOP);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetWithAvoidance.GetX(), offsetWithoutAvoidance.GetX());
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg030
 * @tc.desc: Test AdjustTextOffsetForBadge for RIGHT_TOP position in RTL with non-empty text.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg030, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT_TOP);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetWithAvoidance.GetX() - offsetWithoutAvoidance.GetX(), -Dimension(2.0_vp).ConvertToPx());
    EXPECT_EQ(offsetWithAvoidance.GetY() - offsetWithoutAvoidance.GetY(), Dimension(2.0_vp).ConvertToPx());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg031
 * @tc.desc: Test AdjustTextOffsetForBadge for RIGHT_TOP position in LTR with empty text.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg031, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "";
    badgeParameters.badgePosition = static_cast<int>(BadgePosition::RIGHT_TOP);
    badgeParameters.isPositionXy = false;
    badgeParameters.isEnableAutoAvoidance = false;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetWithoutAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    layoutProperty_->UpdateIsEnableAutoAvoidance(true);
    FlushUITasks(frameNode_);
    auto offsetWithAvoidance = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();
    auto textWidth = badgeTextNode->GetGeometryNode()->GetFrameSize().Width();

    EXPECT_EQ(offsetWithAvoidance.GetX() - offsetWithoutAvoidance.GetX(), badgeCircleDiameter - textWidth);
    EXPECT_EQ(offsetWithAvoidance.GetY(), offsetWithoutAvoidance.GetY());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg032
 * @tc.desc: Test LayoutIsPositionXy branch uses badgePositionX and badgePositionY.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg032, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "1";
    badgeParameters.isPositionXy = true;
    badgeParameters.badgePositionX = Dimension(10.0, DimensionUnit::VP);
    badgeParameters.badgePositionY = Dimension(6.0, DimensionUnit::VP);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    FlushUITasks(frameNode_);

    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto badgeTextGeometry = badgeTextNode->GetGeometryNode();
    ASSERT_NE(badgeTextGeometry, nullptr);

    EXPECT_EQ(badgeTextGeometry->GetMarginFrameOffset().GetX(), Dimension(10.0, DimensionUnit::VP).ConvertToPx());
    EXPECT_EQ(badgeTextGeometry->GetMarginFrameOffset().GetY(), Dimension(6.0, DimensionUnit::VP).ConvertToPx());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg033
 * @tc.desc: Test child margin offset is adjusted in RTL layout direction.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg033, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "1";
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);

    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto contentNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    auto hostGeometry = frameNode_->GetGeometryNode();
    ASSERT_NE(hostGeometry, nullptr);
    auto contentGeometry = contentNode->GetGeometryNode();
    ASSERT_NE(contentGeometry, nullptr);

    auto expectedOffsetX = hostGeometry->GetFrameSize().Width() - contentGeometry->GetMarginFrameSize().Width();
    EXPECT_EQ(contentGeometry->GetMarginFrameOffset().GetX(), expectedOffsetX);
    EXPECT_EQ(contentGeometry->GetMarginFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg034
 * @tc.desc: Test child margin offset remains zero in LTR layout direction.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg034, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "1";
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    FlushUITasks(frameNode_);

    auto contentNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    auto contentGeometry = contentNode->GetGeometryNode();
    ASSERT_NE(contentGeometry, nullptr);

    EXPECT_EQ(contentGeometry->GetMarginFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(contentGeometry->GetMarginFrameOffset().GetY(), 0.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg035
 * @tc.desc: Test zero badge circle size keeps badge text frame zero on API version ten and above.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg035, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCircleSize = Dimension(0.0, DimensionUnit::VP);
    badgeParameters.badgeBorderWidth = Dimension(3.0, DimensionUnit::VP);
    badge.SetIsDefault(true, false);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    FlushUITasks(frameNode_);

    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto badgeTextGeometry = badgeTextNode->GetGeometryNode();
    ASSERT_NE(badgeTextGeometry, nullptr);
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Width(), 0.0f);
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Height(), 0.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg036
 * @tc.desc: Test zero badge circle size still applies border offset difference to badge text margin offset.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg036, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCircleSize = Dimension(0.0, DimensionUnit::VP);
    badgeParameters.badgeBorderWidth = Dimension(3.0, DimensionUnit::VP);
    badge.SetIsDefault(true, false);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto borderWidthPx = Dimension(3.0, DimensionUnit::VP).ConvertToPx();

    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    FlushUITasks(frameNode_);
    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto offsetV10 = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_FIVE));
    FlushUITasks(frameNode_);
    auto offsetV5 = badgeTextNode->GetGeometryNode()->GetMarginFrameOffset();

    EXPECT_EQ(offsetV10.GetX() - offsetV5.GetX(), borderWidthPx);
    EXPECT_EQ(offsetV10.GetY() - offsetV5.GetY(), borderWidthPx);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg037
 * @tc.desc: Test single-digit badge count keeps badge text frame width equal to height.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg037, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCount = 5;
    badgeParameters.badgeMaxCount = 9;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    FlushUITasks(frameNode_);

    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto badgeTextGeometry = badgeTextNode->GetGeometryNode();
    ASSERT_NE(badgeTextGeometry, nullptr);
    auto textLayoutProperty = badgeTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();

    EXPECT_EQ(textLayoutProperty->GetContentValue(), u"5");
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Width(), badgeCircleDiameter);
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Height(), badgeCircleDiameter);
    EXPECT_EQ(badgeTextGeometry->GetFrameSize().Width(), badgeTextGeometry->GetFrameSize().Height());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg038
 * @tc.desc: Test badge count greater than max count uses expanded badge text frame width.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg038, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCount = 1000;
    badgeParameters.badgeMaxCount = 99;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create(u"text");
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    GetInstance();

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    FlushUITasks(frameNode_);

    auto badgeTextNode = AceType::DynamicCast<FrameNode>(frameNode_->GetLastChild());
    ASSERT_NE(badgeTextNode, nullptr);
    auto badgeTextGeometry = badgeTextNode->GetGeometryNode();
    ASSERT_NE(badgeTextGeometry, nullptr);
    auto textLayoutProperty = badgeTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto badgeCircleDiameter = pipeline->GetFontScale() >= AGE_FONT_SIZE_SCALE ?
        badgeTheme->GetBadgeAgeCircleSize().ConvertToPx() : badgeTheme->GetBadgeCircleSize().ConvertToPx();

    EXPECT_EQ(textLayoutProperty->GetContentValue(), u"99+");
    EXPECT_GE(badgeTextGeometry->GetFrameSize().Width(), badgeCircleDiameter);
    EXPECT_GE(badgeTextGeometry->GetFrameSize().Width(), badgeTextGeometry->GetFrameSize().Height());
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg039
 * @tc.desc: Test PerformMeasureSelf returns early when selfIdealSize is valid.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg039, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    firstChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(300.0f, 200.0f));
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
    secondChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(120.0f, 80.0f));
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSize<float>(180.0f, 140.0f);
    constraint.maxSize = SizeF(500.0f, 500.0f);
    constraint.minSize = SizeF(0.0f, 0.0f);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    layoutAlgorithm->PerformMeasureSelf(AccessibilityManager::RawPtr(layoutWrapper));

    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 180.0f);
    EXPECT_EQ(frameSize.Height(), 140.0f);
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg040
 * @tc.desc: Test PerformMeasureSelf constrains frame size to min size.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeLayoutAlgorithmTestNg, BadgeLayoutAlgorithmTestNg040, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    firstChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(20.0f, 10.0f));
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
    secondChildLayoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(10.0f, 8.0f));
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(500.0f, 500.0f);
    constraint.minSize = SizeF(60.0f, 40.0f);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    layoutAlgorithm->PerformMeasureSelf(AccessibilityManager::RawPtr(layoutWrapper));

    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 60.0f);
    EXPECT_EQ(frameSize.Height(), 40.0f);
}
} // namespace OHOS::Ace::NG
