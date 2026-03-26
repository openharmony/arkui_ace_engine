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
#include "test/mock/core/common/mock_resource_adapter_v2.h"
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
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float FIRST_ITEM_WIDTH = 100.0f;
constexpr float FIRST_ITEM_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);

RefPtr<ResourceObject> CreateStringResourceObject(int32_t resId = 0)
{
    std::vector<ResourceObjectParams> params;
    return AceType::MakeRefPtr<ResourceObject>(
        resId, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
}
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
    jsonValue->Put("outerBorderColor", layoutProperty_->GetBadgeOuterBorderColor().value().ColorToString().c_str());
    jsonValue->Put("outerBorderWidth", layoutProperty_->GetBadgeOuterBorderWidth().value().ToString().c_str());
    jsonValue->Put("enableAutoAvoidance", layoutProperty_->GetIsEnableAutoAvoidance().value());

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

/**
 * @tc.name: BadgeModelNGCreateWithResourceObj002
 * @tc.desc: Test badge CreateWithResourceObj branch coverage
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGCreateWithResourceObj002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto invalidResourceObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badgeParameters.resourceBadgeValueObject = invalidResourceObject;
    badgeParameters.resourceColorObject = invalidResourceObject;
    badgeParameters.resourceBadgeColorObject = invalidResourceObject;
    badgeParameters.resourceBorderColorObject = invalidResourceObject;
    badgeParameters.resourceOuterBorderColorObject = invalidResourceObject;
    badgeParameters.resourceFontWeightObject = invalidResourceObject;
    badgeParameters.resourceFontSizeObject = invalidResourceObject;
    badgeParameters.resourceBadgeSizeObject = invalidResourceObject;
    badgeParameters.resourceBadgePositionXObject = invalidResourceObject;
    badgeParameters.resourceBadgePositionYObject = invalidResourceObject;
    badgeParameters.resourceBorderWidthObject = invalidResourceObject;
    badgeParameters.resourceOuterBorderWidthObject = invalidResourceObject;
    badge.CreateWithResourceObj(frameNode_, badgeParameters);

    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_EQ(pattern_->resourceMgr_->resMap_.size(), 12);
    EXPECT_EQ(pattern_->resourceMgr_->resKeyArray_.size(), 12);

    badgeParameters.resourceBadgeValueObject = nullptr;
    badgeParameters.resourceColorObject = nullptr;
    badgeParameters.resourceBadgeColorObject = nullptr;
    badgeParameters.resourceBorderColorObject = nullptr;
    badgeParameters.resourceOuterBorderColorObject = nullptr;
    badgeParameters.resourceFontWeightObject = nullptr;
    badgeParameters.resourceFontSizeObject = nullptr;
    badgeParameters.resourceBadgeSizeObject = nullptr;
    badgeParameters.resourceBadgePositionXObject = nullptr;
    badgeParameters.resourceBadgePositionYObject = nullptr;
    badgeParameters.resourceBorderWidthObject = nullptr;
    badgeParameters.resourceOuterBorderWidthObject = nullptr;
    badge.CreateWithResourceObj(frameNode_, badgeParameters);

    EXPECT_EQ(pattern_->resourceMgr_, nullptr);
}

/**
 * @tc.name: BadgeModelNGProcessBadgeTextColorBranchCoverage001
 * @tc.desc: Test badge ProcessBadgeTextColor fallback branch when parse color fails
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgeTextColorBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeTextColor = Color::WHITE;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidColor");
    auto colorResObj = CreateStringResourceObject();
    badge.ProcessBadgeTextColor(pattern_, colorResObj, frameNode);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();

    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    EXPECT_EQ(layoutProperty_->GetBadgeTextColorValue(), badgeTheme->GetBadgeTextColor());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgeTextColorBranchCoverage002
 * @tc.desc: Test badge ProcessBadgeTextColor success branch when parse color succeeds
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgeTextColorBranchCoverage002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeTextColor = Color::WHITE;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);

    ResetMockResourceData();
    AddMockResourceData(0, "#FF0000");
    auto colorResObj = CreateStringResourceObject();
    badge.ProcessBadgeTextColor(pattern_, colorResObj, frameNode);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();

    EXPECT_EQ(layoutProperty_->GetBadgeTextColorValue(), Color::RED);
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessFontSizeBranchCoverage001
 * @tc.desc: Test badge ProcessFontSize success and percent fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessFontSizeBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    ResetMockResourceData();
    AddMockResourceData(0, "20vp");
    auto fontSizeResObj = CreateStringResourceObject();
    badge.ProcessFontSize(pattern_, fontSizeResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeFontSizeValue(), 20.0_vp);
    EXPECT_FALSE(layoutProperty_->GetFontSizeIsDefault());

    ResetMockResourceData();
    AddMockResourceData(0, "30%");
    badge.ProcessFontSize(pattern_, fontSizeResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeFontSizeValue(), badgeTheme->GetBadgeFontSize());
    EXPECT_TRUE(layoutProperty_->GetFontSizeIsDefault());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessFontSizeBranchCoverage002
 * @tc.desc: Test badge ProcessFontSize fallback branch when parse dimension fails
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessFontSizeBranchCoverage002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badge.ProcessFontSize(pattern_, invalidResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeFontSizeValue(), badgeTheme->GetBadgeFontSize());
    EXPECT_TRUE(layoutProperty_->GetFontSizeIsDefault());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessFontSizeBranchCoverage003
 * @tc.desc: Test badge ProcessFontSize state true branch with negative dimension
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessFontSizeBranchCoverage003, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    ResetMockResourceData();
    AddMockResourceData(0, "-12vp");
    auto fontSizeResObj = CreateStringResourceObject();
    badge.ProcessFontSize(pattern_, fontSizeResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeFontSizeValue(), badgeTheme->GetBadgeFontSize());
    EXPECT_TRUE(layoutProperty_->GetFontSizeIsDefault());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgeSizeBranchCoverage001
 * @tc.desc: Test badge ProcessBadgeSize success and percent fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgeSizeBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);

    ResetMockResourceData();
    AddMockResourceData(0, "24vp");
    auto badgeSizeResObj = CreateStringResourceObject();
    badge.ProcessBadgeSize(pattern_, badgeSizeResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeCircleSizeValue(), 24.0_vp);
    EXPECT_FALSE(layoutProperty_->GetBadgeSizeIsDefault());

    ResetMockResourceData();
    AddMockResourceData(0, "18%");
    badge.ProcessBadgeSize(pattern_, badgeSizeResObj);
    pattern_->resourceMgr_->ReloadResources();
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);
    EXPECT_EQ(layoutProperty_->GetBadgeCircleSizeValue(), badgeTheme->GetBadgeCircleSize());
    EXPECT_TRUE(layoutProperty_->GetBadgeSizeIsDefault());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgeSizeBranchCoverage002
 * @tc.desc: Test badge ProcessBadgeSize fallback branch when parse dimension fails
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgeSizeBranchCoverage002, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    badge.ProcessBadgeSize(pattern_, invalidResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeCircleSizeValue(), badgeTheme->GetBadgeCircleSize());
    EXPECT_TRUE(layoutProperty_->GetBadgeSizeIsDefault());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgeSizeBranchCoverage003
 * @tc.desc: Test badge ProcessBadgeSize state true branch with negative dimension
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgeSizeBranchCoverage003, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    ResetMockResourceData();
    AddMockResourceData(0, "-12vp");
    auto badgeSizeResObj = CreateStringResourceObject();
    badge.ProcessBadgeSize(pattern_, badgeSizeResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeCircleSizeValue(), badgeTheme->GetBadgeCircleSize());
    EXPECT_TRUE(layoutProperty_->GetBadgeSizeIsDefault());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgeColorBranchCoverage001
 * @tc.desc: Test badge ProcessBadgeColor success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgeColorBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto colorResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "#00FF00");
    badge.ProcessBadgeColor(pattern_, colorResObj, frameNode);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeColorValue(), Color::GREEN);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidColor");
    badge.ProcessBadgeColor(pattern_, colorResObj, frameNode);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeColorValue(), badgeTheme->GetBadgeColor());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBorderColorBranchCoverage001
 * @tc.desc: Test badge ProcessBorderColor success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBorderColorBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto colorResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "#0000FF");
    badge.ProcessBorderColor(pattern_, colorResObj, frameNode);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeBorderColorValue(), Color::BLUE);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidColor");
    badge.ProcessBorderColor(pattern_, colorResObj, frameNode);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeBorderColorValue(), badgeTheme->GetBadgeBorderColor());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessOuterBorderColorBranchCoverage001
 * @tc.desc: Test badge ProcessOuterBorderColor success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessOuterBorderColorBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto colorResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "#FF0000");
    badge.ProcessOuterBorderColor(pattern_, colorResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeOuterBorderColorValue(), Color::RED);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidColor");
    badge.ProcessOuterBorderColor(pattern_, colorResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeOuterBorderColorValue(), badgeTheme->GetBadgeOuterBorderColor());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessFontWeightBranchCoverage001
 * @tc.desc: Test badge ProcessFontWeight success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessFontWeightBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);

    auto weightResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "bold");
    badge.ProcessFontWeight(pattern_, weightResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeFontWeightValue(), FontWeight::BOLD);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidWeight");
    badge.ProcessFontWeight(pattern_, weightResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeFontWeightValue(), FontWeight::NORMAL);
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgePositionXBranchCoverage001
 * @tc.desc: Test badge ProcessBadgePositionX success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgePositionXBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto positionResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "16vp");
    badge.ProcessBadgePositionX(pattern_, positionResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgePositionXValue(), 16.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidDimension");
    badge.ProcessBadgePositionX(pattern_, positionResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgePositionXValue(), badgeTheme->GetBadgePositionX());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBadgePositionYBranchCoverage001
 * @tc.desc: Test badge ProcessBadgePositionY success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBadgePositionYBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto positionResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "18vp");
    badge.ProcessBadgePositionY(pattern_, positionResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgePositionYValue(), 18.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidDimension");
    badge.ProcessBadgePositionY(pattern_, positionResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgePositionYValue(), badgeTheme->GetBadgePositionY());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessBorderWidthBranchCoverage001
 * @tc.desc: Test badge ProcessBorderWidth success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessBorderWidthBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto widthResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "6vp");
    badge.ProcessBorderWidth(pattern_, widthResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeBorderWidthValue(), 6.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidDimension");
    badge.ProcessBorderWidth(pattern_, widthResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeBorderWidthValue(), badgeTheme->GetBadgeBorderWidth());
    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: BadgeModelNGProcessOuterBorderWidthBranchCoverage001
 * @tc.desc: Test badge ProcessOuterBorderWidth success and fallback branches
 * @tc.type: FUNC
 */
HWTEST_F(BadgeTestToJson, BadgeModelNGProcessOuterBorderWidthBranchCoverage001, TestSize.Level1)
{
    BadgeModelNG badge;
    BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);
    GetInstance();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    ASSERT_NE(badgeTheme, nullptr);

    auto widthResObj = CreateStringResourceObject();
    ResetMockResourceData();
    AddMockResourceData(0, "8vp");
    badge.ProcessOuterBorderWidth(pattern_, widthResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeOuterBorderWidthValue(), 8.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "invalidDimension");
    badge.ProcessOuterBorderWidth(pattern_, widthResObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(layoutProperty_->GetBadgeOuterBorderWidthValue(), badgeTheme->GetBadgeOuterBorderWidth());
    pipeline->SetIsSystemColorChange(false);
}

} // namespace OHOS::Ace::NG
