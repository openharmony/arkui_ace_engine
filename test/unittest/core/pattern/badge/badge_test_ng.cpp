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
constexpr Dimension BADGE_BORDER_WIDTH = 10.0_vp;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
constexpr float AGE_FONT_SIZE_SCALE = 1.75f;
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

class BadgeTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateChild(const LayoutConstraintF& childLayoutConstraint);
    void CreateFrameNodeAndBadgeModelNG(const Dimension badgeCircleSize);

    RefPtr<FrameNode> frameNode_;
    RefPtr<BadgePattern> pattern_;
    RefPtr<BadgeLayoutProperty> layoutProperty_;
    RefPtr<BadgeAccessibilityProperty> accessibilityProperty_;
};

void BadgeTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_BADGE);
    auto badgeTheme = BadgeTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(badgeTheme));
}

void BadgeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void BadgeTestNg::SetUp() {}

void BadgeTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void BadgeTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<BadgePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<BadgeLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<BadgeAccessibilityProperty>();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> BadgeTestNg::CreateChild(
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

void BadgeTestNg::CreateFrameNodeAndBadgeModelNG(const Dimension badgeCircleSize)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCircleSize = badgeCircleSize;
    badge.Create(badgeParameters);
    GetInstance();
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

    GetInstance();
    EXPECT_EQ(accessibilityProperty_->GetText(), "");

    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());

    filter.AddFilterAttr("id");
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
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
    badgeParameters.isPositionXy = true;
    badgeParameters.badgePositionX = Dimension(10);
    badgeParameters.badgePositionY = Dimension(10);
    badge.Create(badgeParameters);

    GetInstance();
    ASSERT_NE(layoutProperty_, nullptr);
    EXPECT_EQ(layoutProperty_->GetBadgeValue(), "test");
    EXPECT_EQ(layoutProperty_->GetBadgeCount(), 1);
    EXPECT_EQ(layoutProperty_->GetBadgeMaxCount(), 99);
    EXPECT_EQ(layoutProperty_->GetBadgeColor(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetBadgeTextColor(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetBadgeFontSize(), BADGE_FONT_SIZE);
    EXPECT_EQ(layoutProperty_->GetBadgeCircleSize(), BADGE_CIRCLE_SIZE);
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
    badgeParameters.badgeFontSize = BADGE_FONT_SIZE;
    badge.Create(badgeParameters);
    GetInstance();

    // test frameNode has not
    pattern_->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    // update badge layoutProperty and go to different branch
    layoutProperty_->UpdateBadgeValue("");
    pattern_->OnModifyDone();

    layoutProperty_->UpdateBadgeValue("test");
    pattern_->OnModifyDone();

    layoutProperty_->UpdateBadgeCount(1);
    pattern_->OnModifyDone();

    layoutProperty_->UpdateBadgeCount(100);
    pattern_->OnModifyDone();

    layoutProperty_->UpdateBadgeCount(-1);
    pattern_->OnModifyDone();

    layoutProperty_->UpdateBadgeCount(-0);
    pattern_->OnModifyDone();
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
    GetInstance();
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    auto badgeLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
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
    firstChildFrameNode->MountToParent(frameNode_);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step4. update layoutWrapper and go to different branch.
     */
    LayoutConstraintF LayoutConstraintVaildWidth;
    LayoutConstraintVaildWidth.selfIdealSize.SetSize(SizeF(1000000, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildWidth);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    layoutProperty_->UpdateBadgeValue("");
    LayoutConstraintF LayoutConstraintVaildHeight;
    LayoutConstraintVaildHeight.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildHeight);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    layoutProperty_->UpdateBadgeValue("test");
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

    layoutProperty_->UpdateBadgeMaxCount(5);
    textLayoutProperty->UpdateContent("hello");
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    for (int32_t i = 0; i < 3; ++i) {
        auto badgePosition = static_cast<BadgePosition>(i);
        layoutProperty_->UpdateBadgePosition(badgePosition);
        badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }

    textLayoutProperty->UpdateContent(" ");
    for (int32_t i = 0; i < 3; ++i) {
        auto badgePosition = static_cast<BadgePosition>(i);
        layoutProperty_->UpdateBadgePosition(badgePosition);
        badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }

    auto secondChild = CreateChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    secondChildFrameNode->MountToParent(frameNode_);
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
    GetInstance();

    // test frameNode has not
    pattern_->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();
    for (auto fontWeight : FontWeights) {
        layoutProperty_->UpdateBadgeFontWeight(fontWeight);
        pattern_->OnModifyDone();
        EXPECT_EQ(layoutProperty_->GetBadgeFontWeight().value(), fontWeight);
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
    GetInstance();

    // test frameNode has not
    pattern_->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    layoutProperty_->UpdateBadgeBorderWidth(BADGE_BORDER_WIDTH);
    pattern_->OnModifyDone();
    EXPECT_EQ(layoutProperty_->GetBadgeBorderWidth().value(), BADGE_BORDER_WIDTH);
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
    GetInstance();

    pattern_->OnModifyDone();

    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(rowNode, nullptr);
    rowNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    // add textNode child
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode_);
    pattern_->OnModifyDone();

    for (auto color : Colors) {
        layoutProperty_->UpdateBadgeBorderColor(color);
        pattern_->OnModifyDone();
        EXPECT_EQ(layoutProperty_->GetBadgeBorderColor().value(), color);
    }
}

/**
 * @tc.name: BadgePatternTest006
 * @tc.desc: test badge measure and layout.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto badgeLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(badgeLayoutAlgorithm));
    layoutProperty_->UpdateBadgeFontSize(BADGE_FONT_SIZE);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(firstChildFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper and go to different branch.
     */
    LayoutConstraintF LayoutConstraintVaildWidth;
    LayoutConstraintVaildWidth.selfIdealSize.SetSize(SizeF(1000000, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildWidth);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. call measure and layout with no child.
     */
    RefPtr<BadgeLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutAlgorithm->hasFontSize_);

    /**
     * @tc.steps: step5. call Measure with layoutWrapper.
     * @tc.expected: layoutAlgorithm->hasFontSize_ is true.
     */
    textLayoutProperty->UpdateContent("1");
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutAlgorithm->hasFontSize_);

    /**
     * @tc.steps: step6. call Layout with layoutWrapper and BadgePosition::default.
     * @tc.expected: layoutAlgorithm->hasFontSize_ is true.
     */
    layoutAlgorithm->hasFontSize_ = true;
    layoutProperty_->UpdateBadgePosition(BadgePosition(6));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutAlgorithm->hasFontSize_);
}

/**
 * @tc.name: BadgePatternTest007
 * @tc.desc: test badge measure and layout.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto badgeLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(badgeLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(firstChildFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(VALUE);

    /**
     * @tc.steps: step3. update layoutWrapper and go to different branch.
     */
    LayoutConstraintF LayoutConstraintVaildWidth;
    LayoutConstraintVaildWidth.selfIdealSize.SetSize(SizeF(1000000, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildWidth);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. call Measure with layoutWrapper.
     * @tc.expected: layoutAlgorithm->hasFontSize_ is true.
     */
    RefPtr<BadgeLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutAlgorithm->hasFontSize_);

    /**
     * @tc.steps: step5. call Layout with layoutWrapper.
     * @tc.expected: layoutAlgorithm->hasFontSize_ is true.
     */
    layoutAlgorithm->hasFontSize_ = true;
    layoutProperty_->UpdateBadgePosition(BadgePosition(6));
    layoutProperty_->UpdateIsPositionXy(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_TEN);
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutAlgorithm->hasFontSize_);
}

/**
 * @tc.name: BadgePatternTest008
 * @tc.desc: test layout different branch
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto badgeLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(badgeLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto firstChild = CreateChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    firstChildFrameNode->MountToParent(frameNode_);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(firstChildFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent("badge value");

    /**
     * @tc.steps: step3. update layoutWrapper and go to different branch.
     */
    LayoutConstraintF LayoutConstraintVaildWidth;
    LayoutConstraintVaildWidth.selfIdealSize.SetSize(SizeF(1000000, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildWidth);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. updated layoutProperty attributes and version information.
     */
    RefPtr<BadgeLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->hasFontSize_ = true;
    layoutProperty_->UpdateBadgePosition(BadgePosition(6));
    layoutProperty_->UpdateIsPositionXy(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_FIVE);

    /**
     * @tc.steps: step5. call Layout with layoutWrapper.
     * @tc.expected: layoutAlgorithm->hasFontSize_ is true.
     */
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutAlgorithm->hasFontSize_);
}

/**
 * @tc.name: BadgePatternTest009
 * @tc.desc: test UpdateSizeWithCheck
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto badgeLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(badgeLayoutAlgorithm));
    layoutWrapper->GetLayoutProperty()->layoutConstraint_->selfIdealSize =
        OptionalSize<float>(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    /**
     * @tc.steps: step3. call PerformMeasureSelf with layoutWrapper.
     * @tc.expected: retFlag is true.
     */
    RefPtr<BadgeLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<BadgeLayoutAlgorithm>();
    ASSERT_NE(badgeLayoutAlgorithm, nullptr);
    layoutAlgorithm->PerformMeasureSelf(AccessibilityManager::RawPtr(layoutWrapper));

    OptionalSizeF frameSize;
    frameSize.UpdateSizeWithCheck(OptionalSize<float>(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    auto retFlag = frameSize.IsValid();
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: BadgePatternTest010
 * @tc.desc: test SetSizeInit
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);

    /**
     * @tc.steps: step2. call SetIsDefault with badgeLayoutProperty.
     */
    layoutProperty_->SetIsDefault(true, true);
    EXPECT_EQ(layoutProperty_->GetFontSizeIsDefault(), true);
    EXPECT_EQ(layoutProperty_->GetBadgeSizeIsDefault(), true);
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
    GetInstance();
    EXPECT_EQ(accessibilityProperty_->GetText(), VALUE);
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
    GetInstance();
    EXPECT_EQ(accessibilityProperty_->GetText(), std::to_string(COUNT));
}

/**
 * @tc.name: BadgeLayoutAlgorithmTestNg001
 * @tc.desc: Test badge layout in the upper right corner.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeLayoutAlgorithmTestNg001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create("text");
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
HWTEST_F(BadgeTestNg, BadgeLayoutAlgorithmTestNg002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create("text");
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
HWTEST_F(BadgeTestNg, BadgeLayoutAlgorithmTestNg003, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create("text");
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
HWTEST_F(BadgeTestNg, BadgeLayoutAlgorithmTestNg004, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeFontSize = BADGE_FONT_SIZE;
    badgeParameters.badgeCircleSize = BADGE_CIRCLE_SIZE;
    badge.SetIsDefault(false, false);
    badge.Create(badgeParameters);
    {
        TextModelNG model;
        model.Create("text");
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
 * @tc.name: BadgeModelNG001
 * @tc.desc: Test badge property.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeModelNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    auto frameNode = BadgeModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Set Value with String.
     */
    auto node = AceType::RawPtr(frameNode);
    BadgeParameters badgeParameters;
    badgeParameters.badgeColor = Color::WHITE;
    badgeParameters.badgeTextColor = Color::WHITE;
    badgeParameters.badgeBorderColor = Color::WHITE;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgePosition = static_cast<int32_t>(BadgePosition::LEFT);
    badgeParameters.isPositionXy = false;
    badgeParameters.badgePositionX = Dimension(1);
    badgeParameters.badgePositionY = Dimension(1);

    BadgeModelNG::SetBadgeParam(node, badgeParameters, false, false);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetBadgeColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty->GetBadgeBorderColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty->GetBadgeTextColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty->GetBadgeValueValue(), VALUE);
    EXPECT_EQ(layoutProperty->GetBadgePosition(), BadgePosition::LEFT);
    /**
     * @tc.steps: step3. Set Value with Number.
     */
    badgeParameters.badgeCount = COUNT;
    badgeParameters.isPositionXy = true;
    BadgeModelNG::SetBadgeParam(node, badgeParameters, false, false);
    EXPECT_EQ(layoutProperty->GetBadgeCountValue(), COUNT);
    EXPECT_EQ(layoutProperty->GetBadgePositionXValue(), Dimension(1));
    EXPECT_EQ(layoutProperty->GetBadgePositionYValue(), Dimension(1));
}
} // namespace OHOS::Ace::NG
