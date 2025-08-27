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
constexpr Dimension BADGE_FONT_SIZE = 10.0_vp;
constexpr Dimension BADGE_CIRCLE_SIZE = 30.0_vp;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
} // namespace

class BadgeTestToJson : public TestNG {
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

void BadgeTestToJson::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_BADGE);
    auto badgeTheme = BadgeTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(badgeTheme));
}

void BadgeTestToJson::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void BadgeTestToJson::SetUp() {}

void BadgeTestToJson::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void BadgeTestToJson::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<BadgePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<BadgeLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<BadgeAccessibilityProperty>();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> BadgeTestToJson::CreateChild(
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

void BadgeTestToJson::CreateFrameNodeAndBadgeModelNG(const Dimension badgeCircleSize)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCircleSize = badgeCircleSize;
    badge.Create(badgeParameters);
    GetInstance();
}

/**
 * @tc.name: BadgeLayoutPropertyToJsonMaxCount
 * @tc.desc: Test BadgeLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeLayoutPropertyToJsonMaxCount, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and init property value.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeMaxCount = 99;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the value we set.
     */
    EXPECT_EQ(json->GetString("maxCount"), "99");
}

/**
 * @tc.name: BadgeLayoutPropertyToJsonCount
 * @tc.desc: Test BadgeLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeLayoutPropertyToJsonCount, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and init property value.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeCount = 1;
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the value we set.
     */
    EXPECT_EQ(json->GetString("count"), "1");
}

/**
 * @tc.name: BadgeLayoutPropertyToJsonValue
 * @tc.desc: Test BadgeLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeLayoutPropertyToJsonValue, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and init property value.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "test";
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the value we set.
     */
    EXPECT_EQ(json->GetString("value"), "test");
}

/**
 * @tc.name: BadgeLayoutPropertyToJsonPosition
 * @tc.desc: Test BadgeLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeLayoutPropertyToJsonPosition, TestSize.Level1)
{
    /**
     * @tc.step:step1. creat instance and init property value.
     */
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgePosition = 1;
    badgeParameters.isPositionXy = true;
    badgeParameters.badgePositionX = Dimension(10);
    badgeParameters.badgePositionY = Dimension(10);
    badge.Create(badgeParameters);
    GetInstance();
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be BadgePosition.Right".
     */
    EXPECT_EQ(json->GetString("position"), "BadgePosition.Right");
}

/**
 * @tc.name: BadgeLayoutPropertyToJsonStyle
 * @tc.desc: Test BadgeLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeLayoutPropertyToJsonStyle, TestSize.Level1)
{
    /**
     * @tc.step: step1.creat instance and init property value.
     */
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
    badgeParameters.badgeFontWeight = FontWeight::BOLD;
    badgeParameters.badgeBorderWidth = Dimension(13);
    ;
    badge.Create(badgeParameters);
    GetInstance();

    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("x", layoutProperty_->GetBadgePositionX().value().ToString().c_str());
    jsonValue->Put("y", layoutProperty_->GetBadgePositionY().value().ToString().c_str());

    jsonValue->Put("color", layoutProperty_->GetBadgeTextColor().value().ColorToString().c_str());
    jsonValue->Put("fontSize", layoutProperty_->GetBadgeFontSize().value().ToString().c_str());
    jsonValue->Put("badgeColor", layoutProperty_->GetBadgeColor().value().ColorToString().c_str());
    jsonValue->Put("badgeSize", layoutProperty_->GetBadgeCircleSize().value().ToString().c_str());
    jsonValue->Put("borderColor", layoutProperty_->GetBadgeBorderColor().value().ColorToString().c_str());
    jsonValue->Put("borderWidth", layoutProperty_->GetBadgeBorderWidth().value().ToString().c_str());
    jsonValue->Put(
        "fontWeight", V2::ConvertWrapFontWeightToStirng(layoutProperty_->GetBadgeFontWeight().value()).c_str());

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the value we set.
     */
    EXPECT_EQ(json->GetString("style"), jsonValue->ToString().c_str());
}

} // namespace OHOS::Ace::NG
