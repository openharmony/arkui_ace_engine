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
    textLayoutProperty->UpdateContent(u"");
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    textLayoutProperty->UpdateContent(u"x");
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    layoutProperty_->UpdateBadgeMaxCount(5);
    textLayoutProperty->UpdateContent(u"hello");
    badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    for (int32_t i = 0; i < 3; ++i) {
        auto badgePosition = static_cast<BadgePosition>(i);
        layoutProperty_->UpdateBadgePosition(badgePosition);
        badgeLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        badgeLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }

    textLayoutProperty->UpdateContent(u" ");
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
    textLayoutProperty->UpdateContent(u"1");
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
    textLayoutProperty->UpdateContent(u"badge value");

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
    /**
     * @tc.steps: step4. Test updateBadgeStyle method.
     */
    BadgeParameters badgeParameters2;
    badgeParameters2.badgeColor = Color::RED;
    badgeParameters2.badgeTextColor = Color::RED;
    badgeParameters2.badgeBorderColor = Color::RED;
    badgeParameters2.badgeValue = VALUE;
    badgeParameters2.badgeFontWeight = FontWeight::W100;
    badgeParameters2.badgeBorderWidth = BADGE_BORDER_WIDTH;

    BadgeModelNG::UpdateBadgeStyle(badgeParameters2, frameNode);
    EXPECT_EQ(layoutProperty->GetBadgeColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty->GetBadgeBorderColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty->GetBadgeTextColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty->GetBadgeValueValue(), VALUE);
    EXPECT_EQ(layoutProperty->GetBadgeFontWeightValue(), FontWeight::W100);
    EXPECT_EQ(layoutProperty->GetBadgeBorderWidthValue(), BADGE_BORDER_WIDTH);
}

/**
 * @tc.name: BadgeDumpInfoTest001
 * @tc.desc: test badge pattern DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeDumpInfoTest001, TestSize.Level1)
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
    pattern_->DumpInfo();
    EXPECT_EQ(layoutProperty_->GetBadgeValueValue(), "");

    layoutProperty_->UpdateBadgeValue("test");
    pattern_->DumpInfo();
    EXPECT_EQ(layoutProperty_->GetBadgeValueValue(), "test");
}

/**
 * @tc.name: BadgeDumpInfoTest002
 * @tc.desc: test badge pattern DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeDumpInfoTest002, TestSize.Level1)
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
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty_->UpdateBadgeValue("");
    pattern_->DumpInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeValueValue(), "");

    layoutProperty_->UpdateBadgeValue("test");
    pattern_->DumpInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeValueValue(), "test");
}

/**
 * @tc.name: BadgeDumpInfoTest003
 * @tc.desc: test badge pattern DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeDumpInfoTest003, TestSize.Level1)
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
    layoutProperty_->UpdateBadgeCount(1);
    pattern_->DumpInfo();
    EXPECT_EQ(layoutProperty_->GetBadgeCountValue(), 1);

    layoutProperty_->UpdateBadgeCount(100);
    pattern_->DumpInfo();
    EXPECT_EQ(layoutProperty_->GetBadgeCountValue(), 100);
}

/**
 * @tc.name: BadgeDumpInfoTest004
 * @tc.desc: test badge pattern DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeDumpInfoTest004, TestSize.Level1)
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
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty_->UpdateBadgeCount(1);
    pattern_->DumpInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeCountValue(), 1);

    layoutProperty_->UpdateBadgeCount(100);
    pattern_->DumpInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeCountValue(), 100);
}

/**
 * @tc.name: BadgeDumpSimplifyInfoTest001
 * @tc.desc: test badge pattern DumpSimplifyInfo.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeDumpSimplifyInfoTest001, TestSize.Level1)
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

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern_->DumpSimplifyInfo(json);

    // update badge layoutProperty and go to different branch
    layoutProperty_->UpdateBadgeCount(1);
    pattern_->DumpSimplifyInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeCountValue(), 1);

    layoutProperty_->UpdateBadgeCount(0);
    layoutProperty_->UpdateBadgeMaxCount(0);
    pattern_->DumpSimplifyInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeCountValue(), 0);

    layoutProperty_->UpdateBadgeValue("test");
    layoutProperty_->UpdateBadgeTextColor(Color::GREEN);
    layoutProperty_->UpdateBadgeCircleSize(BADGE_CIRCLE_SIZE);
    layoutProperty_->UpdateBadgeFontSize(BADGE_FONT_SIZE);
    pattern_->DumpSimplifyInfo(json);
    EXPECT_EQ(layoutProperty_->GetBadgeValueValue(), "test");
    EXPECT_EQ(layoutProperty_->GetBadgeCircleSizeValue(), BADGE_CIRCLE_SIZE);
    EXPECT_EQ(layoutProperty_->GetBadgeTextColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetBadgeFontSizeValue(), BADGE_FONT_SIZE);
}
} // namespace OHOS::Ace::NG
