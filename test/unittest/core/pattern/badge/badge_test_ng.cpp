/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components/badge/badge_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/badge/badge_layout_algorithm.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

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
constexpr Dimension BADGE_BORDER_WIDTH = 10.0_vp;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);

const FontWeight FontWeights[] { FontWeight::W100, FontWeight::W200, FontWeight::W300, FontWeight::W400,
    FontWeight::W500, FontWeight::W600, FontWeight::W700, FontWeight::W800, FontWeight::W900, FontWeight::BOLD,
    FontWeight::NORMAL, FontWeight::BOLDER, FontWeight::LIGHTER, FontWeight::MEDIUM, FontWeight::REGULAR };

const Color Colors[] {
    Color::TRANSPARENT,
    Color::WHITE,
    Color::BLACK,
    Color::RED,
    Color::GREEN,
    Color::BLUE,
    Color::GRAY,
};
} // namespace

class BadgeTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapper>> CreateChild(const LayoutConstraintF& childLayoutConstraint);
};
void BadgeTestNg::SetUp()
{
    MockPipelineBase::SetUp();
    // set badgeTheme to themeManager before using themeManager to get badgeTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<BadgeTheme>()));
}
void BadgeTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapper>> BadgeTestNg::CreateChild(
    const LayoutConstraintF& childLayoutConstraint)
{
    // add first child to frameNode
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapper> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textNode, textGeometryNode, textNode->GetLayoutProperty());
    auto textPattern = textNode->GetPattern<TextPattern>();
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    textLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    return { textNode, textLayoutWrapper };
}

/**
 * @tc.name: BadgeFrameNodeCreator001
 * @tc.desc: Test empty property of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeFrameNodeCreator001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeLayoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_NE(badgeLayoutProperty, nullptr);
}

/**
 * @tc.name: BadgeFrameNodeCreator002
 * @tc.desc: Test all the properties of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeFrameNodeCreator002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "test";
    badgeParameters.badgeCount = 1;
    badgeParameters.badgeMaxCount = 99;
    badgeParameters.badgePosition = 1;
    badgeParameters.badgeColor = Color::BLACK;
    badgeParameters.badgeTextColor = Color::GREEN;
    badgeParameters.badgeFontSize = BADGE_FONT_SIZE;
    badgeParameters.badgeCircleSize = BADGE_CIRCLE_SIZE;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeLayoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_EQ(badgeLayoutProperty->GetBadgeValue(), "test");
    EXPECT_EQ(badgeLayoutProperty->GetBadgeCount(), 1);
    EXPECT_EQ(badgeLayoutProperty->GetBadgeMaxCount(), 99);
    EXPECT_EQ(badgeLayoutProperty->GetBadgeColor(), Color::BLACK);
    EXPECT_EQ(badgeLayoutProperty->GetBadgeTextColor(), Color::GREEN);
    EXPECT_EQ(badgeLayoutProperty->GetBadgeFontSize(), BADGE_FONT_SIZE);
    EXPECT_EQ(badgeLayoutProperty->GetBadgeCircleSize(), BADGE_CIRCLE_SIZE);
}
/**
 * @tc.name: BadgePatternTest001
 * @tc.desc: test badge pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeMaxCount = 99;
    badge.Create(badgeParameters);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto badgePattern = AceType::DynamicCast<BadgePattern>(frameNode->GetPattern());
    ASSERT_NE(badgePattern, nullptr);
    auto layoutProperty = AceType::DynamicCast<BadgeLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    // test frameNode has not
    badgePattern->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    // update badge layoutProperty and go to different branch
    layoutProperty->UpdateBadgeValue("");
    badgePattern->OnModifyDone();

    layoutProperty->UpdateBadgeValue("test");
    badgePattern->OnModifyDone();

    layoutProperty->UpdateBadgeCount(1);
    badgePattern->OnModifyDone();

    layoutProperty->UpdateBadgeCount(100);
    badgePattern->OnModifyDone();

    layoutProperty->UpdateBadgeCount(-1);
    badgePattern->OnModifyDone();

    layoutProperty->UpdateBadgeCount(-0);
    badgePattern->OnModifyDone();
}

/**
 * @tc.name: BadgePatternTest002
 * @tc.desc: test badge measure and layout.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto badgePattern = AceType::DynamicCast<BadgePattern>(frameNode->GetPattern());
    ASSERT_NE(badgePattern, nullptr);
    auto badgeLayoutProperty = AceType::DynamicCast<BadgeLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(badgeLayoutProperty, nullptr);
    auto badgeLayoutAlgorithm = badgePattern->CreateLayoutAlgorithm();
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(badgeLayoutAlgorithm));
    /**
     * @tc.steps: step3. call measure and layout with no child.
     */
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step4. update layoutWrapper and go to different branch.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();

    LayoutConstraintF LayoutConstraintVaildWidth;
    LayoutConstraintVaildWidth.selfIdealSize.SetSize(SizeF(1000000, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildWidth);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    layoutProperty->UpdateBadgeValue("");
    LayoutConstraintF LayoutConstraintVaildHeight;
    LayoutConstraintVaildHeight.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildHeight);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    layoutProperty->UpdateBadgeValue("test");
    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(firstChildFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent("");
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    textLayoutProperty->UpdateContent("x");
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    badgeLayoutProperty->UpdateBadgeMaxCount(5);
    textLayoutProperty->UpdateContent("hello");
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    for (int32_t i = 0; i < 3; ++i) {
        auto badgePosition = static_cast<BadgePosition>(i);
        badgeLayoutProperty->UpdateBadgePosition(badgePosition);
        badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }

    textLayoutProperty->UpdateContent(" ");
    for (int32_t i = 0; i < 3; ++i) {
        auto badgePosition = static_cast<BadgePosition>(i);
        badgeLayoutProperty->UpdateBadgePosition(badgePosition);
        badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }

    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode);
    layoutWrapper->AppendChild(secondChildLayoutWrapper);
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: BadgePatternTest003
 * @tc.desc: test badge pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest003, TestSize.Level1)
{
    BadgeModelNG BadgeModelNG;
    BadgeParameters badgeParameters;
    badgeParameters.badgeFontWeight = FontWeight::W100;
    BadgeModelNG.Create(badgeParameters);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto badgePattern = frameNode->GetPattern<BadgePattern>();
    ASSERT_NE(badgePattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    // test frameNode has not
    badgePattern->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();
    for (auto fontWeight : FontWeights) {
        layoutProperty->UpdateBadgeFontWeight(fontWeight);
        badgePattern->OnModifyDone();
        EXPECT_EQ(layoutProperty->GetBadgeFontWeight().value(), fontWeight);
    }
}

/**
 * @tc.name: BadgePatternTest004
 * @tc.desc: test badge pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest004, TestSize.Level1)
{
    BadgeModelNG BadgeModelNG;
    BadgeParameters badgeParameters;
    badgeParameters.badgeMaxCount = 99;
    badgeParameters.badgeBorderWidth = BADGE_BORDER_WIDTH;
    BadgeModelNG.Create(badgeParameters);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto badgePattern = frameNode->GetPattern<BadgePattern>();
    ASSERT_NE(badgePattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    // test frameNode has not
    badgePattern->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    layoutProperty->UpdateBadgeBorderWidth(BADGE_BORDER_WIDTH);
    badgePattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetBadgeBorderWidth().value(), BADGE_BORDER_WIDTH);
}

/**
 * @tc.name: BadgePatternTest005
 * @tc.desc: test badge pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest005, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeMaxCount = 99;
    badgeParameters.badgeBorderColor = Color::BLACK;
    badge.Create(badgeParameters);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto badgePattern = frameNode->GetPattern<BadgePattern>();
    ASSERT_NE(badgePattern, nullptr);
    badgePattern->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode);
    badgePattern->OnModifyDone();

    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    for (auto color : Colors) {
        layoutProperty->UpdateBadgeBorderColor(color);
        badgePattern->OnModifyDone();
        EXPECT_EQ(layoutProperty->GetBadgeBorderColor().value(), color);
    }
}

/**
 * @tc.name: BadgeAccessibilityPropertyTestNg001
 * @tc.desc: Test Text property for BadgeValue of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeAccessibilityPropertyTestNg001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeAccessibilityProperty = frameNode->GetAccessibilityProperty<BadgeAccessibilityProperty>();
    EXPECT_EQ(badgeAccessibilityProperty->GetText(), VALUE);
}

/**
 * @tc.name: BadgeAccessibilityPropertyTestNg002
 * @tc.desc: Test Text property for BadgeCount of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeAccessibilityPropertyTestNg002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeAccessibilityProperty = frameNode->GetAccessibilityProperty<BadgeAccessibilityProperty>();
    EXPECT_EQ(badgeAccessibilityProperty->GetText(), std::to_string(COUNT));
}

/**
 * @tc.name: BadgeAccessibilityPropertyTestNg003
 * @tc.desc: Test Text property of Badge if BadgeValue is empty.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeAccessibilityPropertyTestNg003, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeAccessibilityProperty = frameNode->GetAccessibilityProperty<BadgeAccessibilityProperty>();
    EXPECT_EQ(badgeAccessibilityProperty->GetText(), "");
}
} // namespace OHOS::Ace::NG
