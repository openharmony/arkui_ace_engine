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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/resource/resource_object.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_DIVIDER_WIDTH_KEY = "containerPicker.strokeWidth";
const std::string TEST_DIVIDER_COLOR_KEY = "containerPicker.dividerColor";
const std::string TEST_START_MARGIN_KEY = "containerPicker.startMargin";
const std::string TEST_END_MARGIN_KEY = "containerPicker.endMargin";
const std::string TEST_BACKGROUND_COLOR_KEY = "containerPicker.backgroundColor";
const std::string TEST_BORDER_RADIUS_KEY = "containerPicker.borderRadius";
constexpr float TEST_DIVIDER_WIDTH = 3.0f;
constexpr uint32_t TEST_DIVIDER_COLOR = 0xFF000000; // Black
constexpr float TEST_MARGIN = 20.0f;
constexpr uint32_t TEST_BACKGROUND_COLOR = 0xFFFF0000; // Red
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else {
        return nullptr;
    }
}
} // namespace

class ContainerPickerResourceTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateContainerPickerNode();
    RefPtr<FrameNode> CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern);
};

void ContainerPickerResourceTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerResourceTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void ContainerPickerResourceTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void ContainerPickerResourceTest::TearDown() {}

RefPtr<FrameNode> ContainerPickerResourceTest::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->InitDefaultParams();
    pattern->isLoop_ = true;
    return frameNode;
}

RefPtr<FrameNode> ContainerPickerResourceTest::CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    auto frameNode = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

/**
 * @tc.name: ContainerPickerPatternTest001
 * @tc.desc: Test SetIndicatorStyleVal and GetIndicatorStyleVal methods
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create test style
     */
    PickerIndicatorStyle testStyle;
    testStyle.strokeWidth = Dimension(2.0);
    testStyle.dividerColor = Color::RED;
    testStyle.startMargin = Dimension(10.0);
    testStyle.endMargin = Dimension(15.0);
    testStyle.backgroundColor = Color::BLUE;
    testStyle.borderRadius = BorderRadiusProperty(5.0_vp);
    testStyle.isDefaultDividerWidth = false;
    testStyle.isDefaultDividerColor = false;
    testStyle.isDefaultStartMargin = false;
    testStyle.isDefaultEndMargin = false;
    testStyle.isDefaultBackgroundColor = false;
    testStyle.isDefaultBorderRadius = false;

    /**
     * @tc.steps: step2. Test SetIndicatorStyleVal
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIndicatorStyleVal(testStyle);

    /**
     * @tc.steps: step3. Test GetIndicatorStyleVal
     */
    auto retrievedStyle = pattern->GetIndicatorStyleVal();

    // Verify values
    EXPECT_EQ(retrievedStyle.strokeWidth, testStyle.strokeWidth);
    EXPECT_EQ(retrievedStyle.dividerColor, testStyle.dividerColor);
    EXPECT_EQ(retrievedStyle.startMargin, testStyle.startMargin);
    EXPECT_EQ(retrievedStyle.endMargin, testStyle.endMargin);
    EXPECT_EQ(retrievedStyle.backgroundColor, testStyle.backgroundColor);
    EXPECT_EQ(retrievedStyle.borderRadius, testStyle.borderRadius);
    EXPECT_FALSE(retrievedStyle.isDefaultDividerWidth);
    EXPECT_FALSE(retrievedStyle.isDefaultDividerColor);
    EXPECT_FALSE(retrievedStyle.isDefaultStartMargin);
    EXPECT_FALSE(retrievedStyle.isDefaultEndMargin);
    EXPECT_FALSE(retrievedStyle.isDefaultBackgroundColor);
    EXPECT_FALSE(retrievedStyle.isDefaultBorderRadius);
}

/**
 * @tc.name: ContainerPickerPatternTest002
 * @tc.desc: Test UpdateDividerWidthWithResObj method with valid resource object
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Call the method to test
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateDividerWidthWithResObj(mockResObj);

    /**
     * @tc.steps: step4. Check if the style has been updated.
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultDividerWidth);
    EXPECT_NE(style.strokeWidth.value_or(Dimension()), Dimension(TEST_DIVIDER_WIDTH));
}

/**
 * @tc.name: ContainerPickerPatternTest003
 * @tc.desc: Test UpdateDividerColorWithResObj method with valid resource object
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Call the method to test
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateDividerColorWithResObj(mockResObj);

    /**
     * @tc.steps: step4. Check if the style has been updated.
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultDividerColor);
    EXPECT_NE(style.dividerColor.value_or(Color::TRANSPARENT), Color(TEST_DIVIDER_COLOR));
}

/**
 * @tc.name: ContainerPickerPatternTest004
 * @tc.desc: Test UpdateStartMarginWithResObj method with valid resource object
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Call the method to test
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateStartMarginWithResObj(mockResObj);

    /**
     * @tc.steps: step4. Check if the style has been updated.
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultStartMargin);
    EXPECT_NE(style.startMargin.value_or(Dimension()), Dimension(TEST_MARGIN));
}

/**
 * @tc.name: ContainerPickerPatternTest005
 * @tc.desc: Test UpdateEndMarginWithResObj method with valid resource object
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Call the method to test
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateEndMarginWithResObj(mockResObj);

    /**
     * @tc.steps: step4. Check if the style has been updated.
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultEndMargin);
    EXPECT_NE(style.endMargin.value_or(Dimension()), Dimension(TEST_MARGIN));
}

/**
 * @tc.name: ContainerPickerPatternTest006
 * @tc.desc: Test UpdateBackgroundColorWithResObj method with valid resource object
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Call the method to test
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateBackgroundColorWithResObj(mockResObj);

    /**
     * @tc.steps: step4. Check if the style has been updated.
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultBackgroundColor);
    EXPECT_NE(style.backgroundColor.value_or(Color::TRANSPARENT), Color(TEST_BACKGROUND_COLOR));
}

/**
 * @tc.name: ContainerPickerPatternTest007
 * @tc.desc: Test UpdateBorderRadiusWithResObj method with valid resource object
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Call the method to test
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateBorderRadiusWithResObj(mockResObj);

    /**
     * @tc.steps: step4. Check if the style has been updated.
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    auto property = frameNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetIndicatorBorderRadius().value_or(BorderRadiusProperty(Dimension())),
        BorderRadiusProperty(DEFAULT_RADIUS));
}

/**
 * @tc.name: ContainerPickerModelTest001
 * @tc.desc: Test ProcessResourceObj method with different keys when config change is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Setup pattern resource manager
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    /**
     * @tc.steps: step3. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step4. Test ProcessResourceObj with strokeWidth key
     * @tc.expected: step4. The style will not be updated due to the failure of resource parsing.
     */
    ContainerPickerModel::ProcessResourceObj(TEST_DIVIDER_WIDTH_KEY, mockResObj);
    pattern->resourceMgr_->ReloadResources();
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultDividerWidth);

    /**
     * @tc.steps: step5. Test ProcessResourceObj with dividerColor key
     * @tc.expected: step5. The style will not be updated due to the failure of resource parsing.
     */
    ContainerPickerModel::ProcessResourceObj(TEST_DIVIDER_COLOR_KEY, mockResObj);
    pattern->resourceMgr_->ReloadResources();
    style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultDividerColor);

    /**
     * @tc.steps: step6. Test ProcessResourceObj with startMargin key
     * @tc.expected: step6. The style will not be updated due to the failure of resource parsing.
     */
    ContainerPickerModel::ProcessResourceObj(TEST_START_MARGIN_KEY, mockResObj);
    pattern->resourceMgr_->ReloadResources();
    style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultStartMargin);

    /**
     * @tc.steps: step7. Test ProcessResourceObj with endMargin key
     * @tc.expected: step7. The style will not be updated due to the failure of resource parsing.
     */
    ContainerPickerModel::ProcessResourceObj(TEST_END_MARGIN_KEY, mockResObj);
    pattern->resourceMgr_->ReloadResources();
    style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultEndMargin);

    /**
     * @tc.steps: step8. Test ProcessResourceObj with backgroundColor key
     * @tc.expected: step8. The style will not be updated due to the failure of resource parsing.
     */
    ContainerPickerModel::ProcessResourceObj(TEST_BACKGROUND_COLOR_KEY, mockResObj);
    pattern->resourceMgr_->ReloadResources();
    style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultBackgroundColor);

    /**
     * @tc.steps: step9. Test ProcessResourceObj with borderRadius key
     * @tc.expected: step9. The style will not be updated due to the failure of resource parsing.
     */
    ContainerPickerModel::ProcessResourceObj(TEST_BORDER_RADIUS_KEY, mockResObj);
    pattern->resourceMgr_->ReloadResources();
    style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultBorderRadius);
}

/**
 * @tc.name: ContainerPickerModelTest002
 * @tc.desc: Test ProcessResourceObj method with invalid key when config change is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerModelTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set g_isConfigChangePerform to true
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. Setup pattern resource manager
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto pickerPattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);

    /**
     * @tc.steps: step3. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step4. Test with invalid key
     */
    ContainerPickerModel::ProcessResourceObj("invalid.key", mockResObj);

    /**
     * @tc.steps: step5. Verify no changes were made to default values
     * @tc.expected: step5. The style will not be updated because the key is invalid.
     */
    auto style = pickerPattern->GetIndicatorStyleVal();
    EXPECT_TRUE(style.isDefaultDividerWidth);
    EXPECT_TRUE(style.isDefaultDividerColor);
    EXPECT_TRUE(style.isDefaultStartMargin);
    EXPECT_TRUE(style.isDefaultEndMargin);
    EXPECT_TRUE(style.isDefaultBackgroundColor);
    EXPECT_TRUE(style.isDefaultBorderRadius);
    EXPECT_TRUE(pattern->resourceMgr_->resMap_.empty());
}

/**
 * @tc.name: ContainerPickerModelTest003
 * @tc.desc: Test the ProcessResourceObj function when the value of g_isConfigChangePerform is different.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ContainerPickerModelTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Setup pattern resource manager
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    auto& resMap = pattern->resourceMgr_->resMap_;

    /**
     * @tc.steps: step2. Create mock resource object
     */
    auto mockResObj = AceType::MakeRefPtr<ResourceObject>();

    /**
     * @tc.steps: step3. Test ProcessResourceObj with valid key but g_isConfigChangePerform is false
     * @tc.expected: step3. Resource should not be registered
     */
    g_isConfigChangePerform = false;
    ContainerPickerModel::ProcessResourceObj(TEST_DIVIDER_WIDTH_KEY, mockResObj);
    EXPECT_TRUE(pattern->resourceMgr_->resMap_.empty());

    /**
     * @tc.steps: step4. Test ProcessResourceObj with valid key but g_isConfigChangePerform is true
     * @tc.expected: step4. Resource should be registered
     */
    g_isConfigChangePerform = true;
    ContainerPickerModel::ProcessResourceObj(TEST_DIVIDER_WIDTH_KEY, mockResObj);
    EXPECT_FALSE(resMap.find(TEST_DIVIDER_WIDTH_KEY) == resMap.end());
}

/**
 * @tc.name: ToJsonValueTest001
 * @tc.desc: test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ToJsonValueTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and property.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto property = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(property, nullptr);

    /**
     * @tc.step: step2. call property's ToJsonValue method.
     * @tc.expected: jsonValue->GetValue("type") is a name string.
     */
    const InspectorFilter filter;
    auto jsonValue = JsonUtil::Create(true);
    property->ToJsonValue(jsonValue, filter);
    EXPECT_EQ(jsonValue->GetString("canLoop"), "true");
    auto selectionIndicator = jsonValue->GetObject("selectionIndicator");
    ASSERT_NE(selectionIndicator, nullptr);
    EXPECT_EQ(selectionIndicator->GetString("type"), "PickerIndicatorType.BACKGROUND");
}

/**
 * @tc.name: ToJsonValueTest002
 * @tc.desc: test ToJsonValue with negative IndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ToJsonValueTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and property.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto property = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(property, nullptr);

    /**
     * @tc.step: step2. update property's IndicatorType to -1.
     */
    property->UpdateIndicatorType(-1);

    /**
     * @tc.step: step3. call property's ToJsonValue method.
     * @tc.expected: jsonValue->GetValue("type") is default name string.
     */
    const InspectorFilter filter;
    auto jsonValue = JsonUtil::Create(true);
    property->ToJsonValue(jsonValue, filter);
    auto selectionIndicator = jsonValue->GetObject("selectionIndicator");
    ASSERT_NE(selectionIndicator, nullptr);
    EXPECT_EQ(selectionIndicator->GetString("type"), "PickerIndicatorType.BACKGROUND");
}

/**
 * @tc.name: ToJsonValueTest003
 * @tc.desc: test ToJsonValue with invalid IndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerResourceTest, ToJsonValueTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and property.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto property = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(property, nullptr);

    /**
     * @tc.step: step2. update property's IndicatorType to 2.
     */
    property->UpdateIndicatorType(2);

    /**
     * @tc.step: step3. call property's ToJsonValue method.
     * @tc.expected: jsonValue->GetValue("type") is default name string.
     */
    const InspectorFilter filter;
    auto jsonValue = JsonUtil::Create(true);
    property->ToJsonValue(jsonValue, filter);
    auto selectionIndicator = jsonValue->GetObject("selectionIndicator");
    ASSERT_NE(selectionIndicator, nullptr);
    EXPECT_EQ(selectionIndicator->GetString("type"), "PickerIndicatorType.BACKGROUND");
}

} // namespace OHOS::Ace::NG
