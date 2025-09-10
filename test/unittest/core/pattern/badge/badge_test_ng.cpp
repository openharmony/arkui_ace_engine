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
#include "test/mock/base/mock_system_properties.h"
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
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "core/components_ng/syntax/if_else_node.h"

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
HWTEST_F(BadgeTestNg, BadgeFrameNodeCreator001, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgeFrameNodeCreator002, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgePatternTest001, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgePatternTest003, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgePatternTest004, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgePatternTest005, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgePatternTest009, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgePatternTest010, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgeAccessibilityPropertyTestNg001, TestSize.Level0)
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
HWTEST_F(BadgeTestNg, BadgeAccessibilityPropertyTestNg002, TestSize.Level0)
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

    std::shared_ptr<JsonValue> json = std::make_shared<JsonValue>();
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

/**
 * @tc.name: BadgePatternTest001
 * @tc.desc: Test UpdateBadgeValue
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create badge and get frameNode.
     */
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    /**
     * @tc.steps: step2. call UpdateBadgeValue with different conditions
     */
    pattern_->UpdateBadgeValue(VALUE, true);  // isFirstLoad = true
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeValue(), VALUE);
    
    pattern_->UpdateBadgeValue(VALUE, false); // isFirstLoad = false
    EXPECT_EQ(layoutProperty->GetBadgeValue(), VALUE); // should not update
}

/**
 * @tc.name: BadgePatternTest002
 * @tc.desc: Test UpdateColor
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest002, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    Color testColor = Color::RED;
    pattern_->UpdateColor(testColor, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeTextColor(), testColor);
    
    Color testColor2 = Color::BLUE;
    pattern_->UpdateColor(testColor2, false);
    EXPECT_EQ(layoutProperty->GetBadgeTextColor(), testColor); // should not update
}

/**
 * @tc.name: BadgePatternTest003
 * @tc.desc: Test UpdateBadgeColor
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest003, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    Color testColor = Color::GREEN;
    pattern_->UpdateBadgeColor(testColor, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeColor(), testColor);
    
    Color testColor2 = Color::RED;
    pattern_->UpdateBadgeColor(testColor2, false);
    EXPECT_EQ(layoutProperty->GetBadgeColor(), testColor); // should not update
}

/**
 * @tc.name: BadgePatternTest004
 * @tc.desc: Test UpdateBorderColor
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest004, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    Color testColor = Color::BLACK;
    pattern_->UpdateBorderColor(testColor, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeBorderColor(), testColor);
    
    Color testColor2 = Color::WHITE;
    pattern_->UpdateBorderColor(testColor2, false);
    EXPECT_EQ(layoutProperty->GetBadgeBorderColor(), testColor); // should not update
}

/**
 * @tc.name: BadgePatternTest005
 * @tc.desc: Test UpdateFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest005, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    FontWeight fontWeight = FontWeight::BOLD;
    pattern_->UpdateFontWeight(fontWeight, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeFontWeight(), fontWeight);
    
    FontWeight fontWeight2 = FontWeight::NORMAL;
    pattern_->UpdateFontWeight(fontWeight2, false);
    EXPECT_EQ(layoutProperty->GetBadgeFontWeight(), fontWeight); // should not update
}

/**
 * @tc.name: BadgePatternTest006
 * @tc.desc: Test UpdateFontSize
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest006, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    CalcDimension fontSize(BADGE_FONT_SIZE);
    pattern_->UpdateFontSize(fontSize, false, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeFontSize(), fontSize);
    EXPECT_FALSE(layoutProperty->GetFontSizeIsDefault());
    
    CalcDimension fontSize2(BADGE_FONT_SIZE);
    pattern_->UpdateFontSize(fontSize2, true, false);
    EXPECT_EQ(layoutProperty->GetBadgeFontSize(), fontSize); // should not update
}

/**
 * @tc.name: BadgePatternTest007
 * @tc.desc: Test UpdateBadgeCircleSize
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest007, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    CalcDimension size(BADGE_FONT_SIZE);
    pattern_->UpdateBadgeCircleSize(size, false, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeCircleSize(), size);
    EXPECT_FALSE(layoutProperty->GetBadgeSizeIsDefault());
    
    CalcDimension size2(BADGE_FONT_SIZE);
    pattern_->UpdateBadgeCircleSize(size2, true, false);
    EXPECT_EQ(layoutProperty->GetBadgeCircleSize(), size); // should not update
}

/**
 * @tc.name: BadgePatternTest009
 * @tc.desc: Test UpdateBadgePosition
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest008, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    CalcDimension posX(BADGE_FONT_SIZE);
    pattern_->UpdateBadgePositionX(posX, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgePositionX(), posX);
    
    CalcDimension posY(BADGE_FONT_SIZE);
    pattern_->UpdateBadgePositionY(posY, true);
    EXPECT_EQ(layoutProperty->GetBadgePositionY(), posY);
}

/**
 * @tc.name: BadgePatternTest010
 * @tc.desc: Test UpdateBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, UpdateBadgePatternTest009, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    CalcDimension width(BADGE_FONT_SIZE);
    pattern_->UpdateBorderWidth(width, true);
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeBorderWidth(), width);
    
    CalcDimension width2(BADGE_FONT_SIZE);
    pattern_->UpdateBorderWidth(width2, false);
    EXPECT_EQ(layoutProperty->GetBadgeBorderWidth(), width); // should not update
}

/**
 * @tc.name: BadgePatternTest011
 * @tc.desc: test badge pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternTest011, TestSize.Level0)
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
    auto ifNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto ifNode = IfElseNode::GetOrCreateIfElseNode(ifNodeId);
    ASSERT_NE(ifNode, nullptr);
    ifNode->MountToParent(frameNode_);
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
 * @tc.name: BadgeModelNGSetBadgeParameMaxCount
 * @tc.desc: Test badge SetBadgeParam.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGSetBadgeParameMaxCount, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    auto frameNode = BadgeModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. setvalue badgeMaxCount .
     */
    auto node = AceType::RawPtr(frameNode);
    BadgeParameters badgeParameters;
    badgeParameters.badgeMaxCount = COUNT;

    BadgeModelNG::SetBadgeParam(node, badgeParameters, false, false);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.case: case1. check value badgeMaxCount.
     * @tc.expected: it should be as we set.
     */
    EXPECT_EQ(layoutProperty->GetBadgeMaxCount(), COUNT);
}

/**
 * @tc.name: BadgeModelNGSetBadgeParam
 * @tc.desc: Test badge SetBadgeParam is not init.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGSetBadgeParam, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateFrameNode.
     */
    auto frameNode = BadgeModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. SetBadgeParam.
     */
    auto node = AceType::RawPtr(frameNode);
    BadgeParameters badgeParameters;

    BadgeModelNG::SetBadgeParam(node, badgeParameters, false, false);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.case: case to cover branch has_value() is false.
     * @tc.expected: it should be the theme value.
     */
    const int defaultMaxCount = 99;
    const double defaultPosValue = 0.0;
    EXPECT_EQ(layoutProperty->GetBadgeMaxCount(), defaultMaxCount);
    EXPECT_EQ(layoutProperty->HasBadgeValue(), false);
    EXPECT_EQ(layoutProperty->GetBadgePositionXValue().Value(), defaultPosValue);
    EXPECT_EQ(layoutProperty->GetBadgePositionYValue().Value(), defaultPosValue);
    EXPECT_EQ(layoutProperty->GetIsPositionXyValue(), false);
    EXPECT_EQ(layoutProperty->GetBadgePositionValue(), BadgePosition::RIGHT_TOP);
}

/**
 * @tc.name: BadgeModelNGCreateWithResourceObj001
 * @tc.desc: Test badge CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGCreateWithResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create instance and badgeParameters is not init.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    /**
     * @tc.steps: step2. call to CreateWithResourceObj.
     */
    badge.CreateWithResourceObj(frameNode_, badgeParameters);

    /**
     * @tc.steps: step3. check the key value, .
     * @tc.expected: it should be null.
     */
    EXPECT_EQ(badgeParameters.resourceBadgeValueObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceColorObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceBadgeColorObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceBorderColorObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceFontWeightObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceFontSizeObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceBadgeSizeObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceBadgePositionXObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceBadgePositionYObject, nullptr);
    EXPECT_EQ(badgeParameters.resourceBorderWidthObject, nullptr);
    std::string key = "badge.badgeValue";
    std::string badgeValue = pattern_->GetResCacheMapByKey(key);
    EXPECT_EQ(badgeValue, "");
}

/**
 * @tc.name: BadgeModelNGProcessBadgeValue
 * @tc.desc: Test badge ProcessBadgeValue
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBadgeValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "";
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBadgeValue.
     */
    badgeParameters.resourceBadgeValueObject = AceType::MakeRefPtr<ResourceObject>();
    badge.ProcessBadgeValue(pattern_, badgeParameters.resourceBadgeValueObject);

    /**
     * @tc.steps: step3. check the key value, .
     * @tc.expected: it should be "".
     */
    std::string badgeValue = layoutProperty_->GetBadgeValueValue();
    EXPECT_EQ(badgeValue, "");
}

/**
 * @tc.name: BadgeModelNGProcessBadgeTextColor
 * @tc.desc: Test badge ProcessBadgeTextColor
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBadgeTextColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeTextColor = Color::WHITE;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBadgeValue.
     */
    badgeParameters.resourceColorObject = AceType::MakeRefPtr<ResourceObject>();
    badge.ProcessBadgeValue(pattern_, badgeParameters.resourceColorObject);

    /**
     * @tc.steps: step3. check the key value, .
     * @tc.expected: it should be "Color::WHITE".
     */
    Color textColor = layoutProperty_->GetBadgeTextColorValue();
    EXPECT_EQ(textColor, Color::WHITE);
}

/**
 * @tc.name: BadgeModelNGProcessBadgePositionX
 * @tc.desc: Test badge ProcessBadgePositionX
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBadgePositionX, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgePositionX = Dimension(1, DimensionUnit::VP);
    badgeParameters.badgePositionY = Dimension(1, DimensionUnit::VP);
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBadgePositionX.
     */
    badgeParameters.resourceBadgePositionXObject = AceType::MakeRefPtr<ResourceObject>();
    badge.ProcessBadgePositionX(pattern_, badgeParameters.resourceBadgePositionXObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be Dimension(1).
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    Dimension positionX = layoutProperty_->GetBadgePositionXValue();
    EXPECT_EQ(positionX.Value(), 1);
}

/**
 * @tc.name: BadgeModelNGProcessBadgePositionY
 * @tc.desc: Test badge ProcessBadgePositionY
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBadgePositionY, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgePositionX = Dimension(1);
    badgeParameters.badgePositionY = Dimension(1, DimensionUnit::VP);
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBadgePositionY.
     */
    badgeParameters.resourceBadgePositionYObject = AceType::MakeRefPtr<ResourceObject>();
    badge.ProcessBadgePositionY(pattern_, badgeParameters.resourceBadgePositionYObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be Dimension(1).
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    Dimension positionY = layoutProperty_->GetBadgePositionYValue();
    EXPECT_EQ(positionY.Value(), 1);
}

/**
 * @tc.name: BadgeModelNGProcessBorderWidth
 * @tc.desc: Test badge ProcessBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBorderWidth, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badgeParameters.badgeBorderWidth = BADGE_BORDER_WIDTH;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBorderWidth.
     */
    badgeParameters.resourceBorderWidthObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badge.ProcessBorderWidth(pattern_, badgeParameters.resourceBorderWidthObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be 0.0.
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isSystemColorChange_ = true;
    Dimension borderWidth = layoutProperty_->GetBadgeBorderWidthValue();
    EXPECT_EQ(borderWidth.Value(), BADGE_BORDER_WIDTH.Value());
}

/**
 * @tc.name: BadgeModelNGProcessFontSize
 * @tc.desc: Test badge ProcessFontSize
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessFontSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badgeParameters.badgeFontSize = 1.00_vp;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessFontSize.
     */
    badgeParameters.resourceFontSizeObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badge.ProcessFontSize(pattern_, badgeParameters.resourceFontSizeObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be 0.0f.
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isSystemColorChange_ = true;
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    Dimension FontSize = layoutProperty_->GetBadgeFontSizeValue();
    EXPECT_EQ(FontSize, badgeTheme->GetBadgeFontSize());
}

/**
 * @tc.name: BadgeModelNGProcessFontWeight
 * @tc.desc: Test badge ProcessFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessFontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badgeParameters.badgeFontWeight = FontWeight::NORMAL;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessFontWeight.
     */
    badgeParameters.resourceFontWeightObject = AceType::MakeRefPtr<ResourceObject>();
    badge.ProcessFontWeight(pattern_, badgeParameters.resourceFontWeightObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be NORMAL.
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    auto fontWeight = layoutProperty_->GetBadgeFontWeightValue();
    EXPECT_EQ(fontWeight, FontWeight::NORMAL);
}

/**
 * @tc.name: BadgeModelNGProcessBorderColor
 * @tc.desc: Test badge ProcessBorderColor
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBorderColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badgeParameters.badgeBorderColor = Color::WHITE;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBorderColor.
     */
    badgeParameters.resourceBorderColorObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badge.ProcessBorderColor(pattern_, badgeParameters.resourceBorderColorObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be FF000000.
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    auto pipeline = frameNode_->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isSystemColorChange_ = true;
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    auto borderColor = layoutProperty_->GetBadgeBorderColorValue();
    EXPECT_EQ(borderColor, badgeTheme->GetBadgeBorderColor());
}

/**
 * @tc.name: BadgeModelNGProcessBadgeColor
 * @tc.desc: Test badge ProcessBadgeColor
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGProcessBadgeColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badgeParameters.badgeColor = Color::WHITE;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call to ProcessBadgeColor.
     */
    badgeParameters.resourceBadgeColorObject = AceType::MakeRefPtr<ResourceObject>();
    badge.ProcessBadgeColor(pattern_, badgeParameters.resourceBadgeColorObject);

    /**
     * @tc.steps: step3. check the key value.
     * @tc.expected: it should be FF000000.
     */
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern_->OnColorModeChange(colorMode);
    auto badgeColor = layoutProperty_->GetBadgeBorderColorValue();
    EXPECT_EQ(badgeColor.ColorToString(), "#FF000000");
}

/**
 * @tc.name: BadgeDumpInfo001
 * @tc.desc: Test dump info of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, BadgeDumpInfo001, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    
    CalcDimension width(BADGE_FONT_SIZE);
    pattern_->UpdateBorderWidth(width, true);
    pattern_->DumpInfo();
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeBorderWidth(), width);
    
    CalcDimension width2(BADGE_FONT_SIZE);
    pattern_->UpdateBorderWidth(width2, false);
    pattern_->DumpInfo();
    EXPECT_EQ(layoutProperty->GetBadgeBorderWidth(), width); // should not update
}

/**
 * @tc.name: BadgeModelNGTest001
 * @tc.desc: Test CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgeModelNGTest001, TestSize.Level1)
{
    BadgeModelNG badge1;
    BadgeParameters badgeParameters;
    badgeParameters.badgeMaxCount = 99;
    badgeParameters.badgeFontSize = BADGE_FONT_SIZE;
    g_isConfigChangePerform = false;
    badge1.Create(badgeParameters);
    GetInstance();

    BadgeModelNG badge2;
    g_isConfigChangePerform = true;
    badgeParameters.resourceBadgeValueObject = nullptr;
    badgeParameters.resourceBadgeColorObject = nullptr;
    badgeParameters.resourceBadgeColorObject = nullptr;
    badgeParameters.resourceBorderColorObject = nullptr;
    badgeParameters.resourceFontWeightObject = nullptr;
    badgeParameters.resourceFontSizeObject = nullptr;
    badgeParameters.resourceBadgeSizeObject = nullptr;
    badgeParameters.resourceBadgePositionXObject = nullptr;
    badgeParameters.resourceBadgePositionYObject = nullptr;
    badgeParameters.resourceBorderWidthObject = nullptr;
    badge2.Create(badgeParameters);
    EXPECT_EQ(layoutProperty_->GetBadgeTextColor(), Color::BLACK);

    BadgeModelNG badge3;
    badgeParameters.resourceBadgeValueObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBadgeColorObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBadgeColorObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBorderColorObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceFontWeightObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceFontSizeObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBadgeSizeObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBadgePositionXObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBadgePositionYObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBorderWidthObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badge3.Create(badgeParameters);
    auto pipeline = PipelineBase::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    auto badgeTextColor = badgeTheme->GetBadgeTextColor();
    EXPECT_EQ(layoutProperty_->GetBadgeTextColor(), badgeTextColor);
}

/**
 * @tc.name: BadgePatternOnColorUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestNg, BadgePatternOnColorUpdate001, TestSize.Level1)
{
    CreateFrameNodeAndBadgeModelNG(BADGE_CIRCLE_SIZE);
    g_isConfigChangePerform = false;
    pattern_->OnColorConfigurationUpdate();
    auto layoutProperty = pattern_->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetBadgeTextColor(), Color::BLACK);
    g_isConfigChangePerform = true;
    pattern_->OnColorConfigurationUpdate();
    auto pipeline = PipelineBase::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    auto badgeTextColor = badgeTheme->GetBadgeTextColor();
    EXPECT_EQ(layoutProperty->GetBadgeTextColor(), badgeTextColor);

    layoutProperty->UpdateBadgePositionXByuser(true);
    layoutProperty->UpdateBadgePositionYByuser(true);
    layoutProperty->UpdateBadgeFontSizeByuser(true);
    layoutProperty->UpdateBadgeCircleSizeByuser(true);
    layoutProperty->UpdateBadgeBorderColorByuser(true);
    layoutProperty->UpdateBadgeBorderWidthByuser(true);
    layoutProperty->UpdateBadgeTextColorByuser(true);
    layoutProperty->UpdateBadgeColorByuser(true);
    pattern_->OnColorConfigurationUpdate();
    EXPECT_EQ(layoutProperty->GetBadgeTextColor(), Color::BLACK);
}

/**
 * @tc.name: CreateBadgeFrameNodeTest001
 * @tc.desc: Test to create a badge frame node and return.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, CreateBadgeFrameNodeTest001, TestSize.Level1)
{
    BadgeModelNG badge;
    auto framenode = badge.CreateBadgeFrameNode();
    ASSERT_NE(framenode, nullptr);
}

/**
 * @tc.name: CreateByFrameNodeTest001
 * @tc.desc: Test to create a badge by frame node.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeTestNg, CreateByFrameNodeTest001, TestSize.Level1)
{
    BadgeModelNG badge;
    auto framenode = badge.CreateBadgeFrameNode();
    ASSERT_NE(framenode, nullptr);

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
    badge.CreateByFrameNode(framenode, badgeParameters);

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
} // namespace OHOS::Ace::NG
