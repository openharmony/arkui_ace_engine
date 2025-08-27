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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}
} // namespace

class TextPickerToJson : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerToJson();
    void DestroyTextPickerToJsonObject();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPickerPattern> textPickerPattern_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityProperty_;
    RefPtr<TextPickerRowAccessibilityProperty> textPickerRowAccessibilityProperty_;
    RefPtr<FrameNode> stackNode_;
    RefPtr<FrameNode> blendNode_;
    RefPtr<FrameNode> columnNode_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPattern_;
    RefPtr<FrameNode> stackNodeNext_;
    RefPtr<FrameNode> blendNodeNext_;
    RefPtr<FrameNode> columnNodeNext_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPatternNext_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityPropertyNext_;
};

void TextPickerToJson::DestroyTextPickerToJsonObject()
{
    frameNode_ = nullptr;
    textPickerPattern_ = nullptr;
    textPickerAccessibilityProperty_ = nullptr;
    textPickerRowAccessibilityProperty_ = nullptr;
    stackNode_ = nullptr;
    blendNode_ = nullptr;
    columnNode_ = nullptr;
    textPickerColumnPattern_ = nullptr;
    stackNodeNext_ = nullptr;
    blendNodeNext_ = nullptr;
    columnNodeNext_ = nullptr;
    textPickerColumnPatternNext_ = nullptr;
    textPickerAccessibilityPropertyNext_ = nullptr;
}

void TextPickerToJson::InitTextPickerToJson()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    textPickerRowAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextPickerRowAccessibilityProperty>();
    ASSERT_NE(textPickerRowAccessibilityProperty_, nullptr);
    textPickerPattern_ = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern_, nullptr);
    stackNode_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode_, nullptr);
    blendNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode_, nullptr);
    columnNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode_, nullptr);
    textPickerAccessibilityProperty_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityProperty_, nullptr);
    textPickerColumnPattern_ = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->MountToParent(blendNode_);
    blendNode_->MountToParent(stackNode_);
    stackNode_->MountToParent(frameNode_);

    stackNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNodeNext_, nullptr);
    blendNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNodeNext_, nullptr);
    columnNodeNext_ =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNodeNext_, nullptr);
    textPickerAccessibilityPropertyNext_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityPropertyNext_, nullptr);
    textPickerColumnPatternNext_ = columnNodeNext_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPatternNext_, nullptr);
    columnNodeNext_->MountToParent(blendNodeNext_);
    blendNodeNext_->MountToParent(stackNodeNext_);
    stackNodeNext_->MountToParent(frameNode_);
}

void TextPickerToJson::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerToJson::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerToJson::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerToJson::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: TextPickerToJsonHeight
 * @tc.desc: Test TextPicker ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerToJsonHeight, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    GTEST_LOG_(INFO) << json->ToString();
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be -.
     */
    EXPECT_EQ(json->GetString("height"), "-");
}

/**
 * @tc.name: TextPickerToJsonWidth
 * @tc.desc: Test TextPicker ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerToJsonWidth, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    GTEST_LOG_(INFO) << json->ToString();
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be -.
     */
    EXPECT_EQ(json->GetString("width"), "-");
}

/**
 * @tc.name: TextPickerToJsonDefaultPickerItemHeight
 * @tc.desc: Test TextPicker ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerToJsonDefaultPickerItemHeight, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     * @tc.expected: default PickerItemHeight is 0.00px
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    GTEST_LOG_(INFO) << json->ToString();
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be -.
     */
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "0.00px");
}

/**
 * @tc.name: TextPickerToJsonDefaultPickerItemHeight001
 * @tc.desc: Test TextPicker ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerToJsonDefaultPickerItemHeight001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     * @tc.expected: default PickerItemHeight is 0.00px
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    TextPickerModelNG::GetInstance()->SetDefaultPickerItemHeight(Dimension(10.0f, DimensionUnit::VP));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    GTEST_LOG_(INFO) << json->ToString();
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be 10.00vp.
     */
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "10.00vp");
}

/**
 * @tc.name: TextPickerToJsonDefaultPickerItemHeight002
 * @tc.desc: Test TextPicker ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerToJsonDefaultPickerItemHeight002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     * @tc.expected: default PickerItemHeight is 0.00px
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    TextPickerModelNG::GetInstance()->SetDefaultPickerItemHeight(Dimension(50.0f, DimensionUnit::PX));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    GTEST_LOG_(INFO) << json->ToString();
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be 50.00px.
     */
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "50.00px");
}

/**
 * @tc.name: TextPickerPatternToJsonValueRange
 * @tc.desc: Test TextPickerPattern ToJsonValue(range is not empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerPatternToJsonValueRange, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    /**
     * @tc.step: step1. init range and Set range.
     */
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);

    /**
     * @tc.step: step2. call ToJsonValue.
     */
    InspectorFilter filter;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    auto json = JsonUtil::Create(true);
    textPickerPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the range value.
     * @tc.expected: it should be the value set.
     */
    std::string rangeStr = textPickerPattern->GetRangeStr();
    EXPECT_EQ(json->GetString("range"), rangeStr.c_str());
}

/**
 * @tc.name: TextPickerPatternToJsonValueColumnWidths
 * @tc.desc: Test TextPickerPattern ToJsonValue(range is empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerPatternToJsonValueColumnWidths, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step1. init columnWidths.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->columnWidths_ = { 7.0_vp, 8.0_vp, 9.0_vp };

    /**
     * @tc.step: step2. call ToJsonValue.
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    textPickerPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the columnWidths value.
     * @tc.expected: it should be the value set.
     */
    std::string columnWidthsStr = textPickerPattern->GetColumnWidthsStr();
    EXPECT_EQ(json->GetString("columnWidths"), columnWidthsStr.c_str());
}

/**
 * @tc.name: TextPickerPatternToJsonValueEnableHapticFeedback
 * @tc.desc: Test TextPickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerPatternToJsonValueEnableHapticFeedback, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * @tc.cases: case. cover isEnableHapticFeedback == true;
     */
    bool isEnableHapticFeedback = true;
    InspectorFilter filter;
    TextPickerModelNG::GetInstance()->SetEnableHapticFeedback(isEnableHapticFeedback);
    auto json = JsonUtil::Create(true);
    textPickerPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetBool("enableHapticFeedback"), isEnableHapticFeedback);

    /**
     * @tc.cases: case. cover isEnableHapticFeedback == false;
     */
    isEnableHapticFeedback = false;
    TextPickerModelNG::GetInstance()->SetEnableHapticFeedback(isEnableHapticFeedback);
    std::unique_ptr<JsonValue> json2 = JsonUtil::Create(true);
    textPickerPattern->ToJsonValue(json2, filter);
    EXPECT_EQ(json2->GetBool("enableHapticFeedback"), isEnableHapticFeedback);
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueCanLoop
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueCanLoop, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);

    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.step: step2. call ToJsonValue.
     * @tc.expected: the canLoop result is true.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("canLoop"), "true");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueSelecteds
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueSelecteds, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);

    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    std::vector<uint32_t> selecteds;
    int selectedCount = 5;
    for (int i = 1; i < selectedCount; i++) {
        selecteds.emplace_back(i);
    }
    selecteds.emplace_back(66);
    pickerProperty->UpdateSelecteds(selecteds);

    auto selectedRes = pickerProperty->CloneSelecteds().value_or(std::vector<uint32_t>());
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(selectedRes[i], selecteds[i]);
    }

    std::vector<std::string> values;
    values.emplace_back("hellow");
    values.emplace_back("good");
    values.emplace_back("better");
    values.emplace_back("best");
    values.emplace_back("most");
    pickerProperty->UpdateValues(values);

    auto values2 = pickerProperty->CloneValues().value_or(std::vector<std::string>());
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(values2[i], values[i]);
    }
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto jsonArraySelected = json->GetValue("selecteds");
    ASSERT_NE(jsonArraySelected, nullptr);
    EXPECT_EQ(jsonArraySelected->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArraySelected->GetString(std::to_string(i).c_str()), std::to_string(selecteds[i]));
    }
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueValues
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueValues, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);

    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    std::vector<uint32_t> selecteds;
    int selectedCount = 5;
    for (int i = 1; i < selectedCount; i++) {
        selecteds.emplace_back(i);
    }
    selecteds.emplace_back(66);
    pickerProperty->UpdateSelecteds(selecteds);

    std::vector<std::string> values;
    values.emplace_back("hellow");
    values.emplace_back("good");
    values.emplace_back("better");
    values.emplace_back("best");
    values.emplace_back("most");
    pickerProperty->UpdateValues(values);

    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto jsonArrayValues = json->GetValue("values");
    EXPECT_EQ(jsonArrayValues->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArrayValues->GetString(std::to_string(i).c_str()), values[i]);
    }
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueSelectedIndex
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueSelectedIndex, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set selectedIndex.
     */
    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);

    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    std::vector<uint32_t> selectIndex;
    selectIndex.push_back(1);
    selectIndex.push_back(2);
    pickerProperty->UpdateSelectedIndex(selectIndex);

    std::vector<uint32_t> selecteds;
    int selectedCount = 5;
    for (int i = 0; i < selectedCount; i++) {
        selecteds.emplace_back(i);
    }
    InspectorFilter filter;
    pickerProperty->UpdateSelecteds(selecteds);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     * The result is the same as selects
     */
    auto jsonArraySelectIndex = json->GetValue("selectedIndex");
    ASSERT_NE(jsonArraySelectIndex, nullptr);
    EXPECT_EQ(jsonArraySelectIndex->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArraySelectIndex->GetString(std::to_string(i).c_str()), std::to_string(selecteds[i]));
    }
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue006
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    Dimension defaultPickerItemHeight = Dimension(6);
    Dimension gradientHeight = Dimension(7);
    std::string value = "testValue";
    uint32_t selected = 0;
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateSelected(selected);
    pickerProperty->UpdateDefaultPickerItemHeight(defaultPickerItemHeight);
    pickerProperty->UpdateGradientHeight(gradientHeight);
    pickerProperty->UpdateValue(value);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), defaultPickerItemHeight.ToString().c_str());
    EXPECT_EQ(json->GetString("gradientHeight"), gradientHeight.ToString().c_str());
    EXPECT_EQ(json->GetString("selected"), std::to_string(selected));
    EXPECT_EQ(json->GetString("value"), value.c_str());
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueGradientHeight
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueGradientHeight, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step1. Construct property values and set.
     */
    Dimension gradientHeight = Dimension(7);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateGradientHeight(gradientHeight);
    /**
     * @tc.step: step1. call ToJsonValue fun.
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the gradientHeight value.
     * @tc.expected: it should be the value set.
     */
    EXPECT_EQ(json->GetString("gradientHeight"), gradientHeight.ToString().c_str());
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueSelected
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueSelected, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    uint32_t selected = 0;
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateSelected(selected);
    /**
     * @tc.step: step1. call ToJsonValue fun.
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the selected value.
     * @tc.expected: it should be the value set.
     */
    EXPECT_EQ(json->GetString("selected"), std::to_string(selected));
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueValue
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueValue, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    std::string value = "testValue";
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateValue(value);
    /**
     * @tc.step: step1. call ToJsonValue fun.
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the value value.
     * @tc.expected: it should be the value set.
     */
    EXPECT_EQ(json->GetString("value"), value.c_str());
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueSelectedTextStyle
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueSelectedTextStyle, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set selectedTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto selectedTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectedTextStyle, nullptr);
    EXPECT_EQ(selectedTextStyle->GetString("color"), "#FFFF0000");
    auto selectedFont = selectedTextStyle->GetObject("font");
    ASSERT_NE(selectedFont, nullptr);
    EXPECT_EQ(selectedFont->GetString("size"), "10.00px");
    EXPECT_EQ(selectedFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue008
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValue008, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set disappearTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FFFF0000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "10.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueNormalTextStyle
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueNormalTextStyle, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set normalTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto normalTextStyle = json->GetObject("textStyle");
    ASSERT_NE(normalTextStyle, nullptr);
    EXPECT_EQ(normalTextStyle->GetString("color"), "#FFFF0000");
    auto normalFont = normalTextStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "10.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueDefaultTextStyle
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueDefaultTextStyle, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set defaultTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    Dimension minFontSize = Dimension(10);
    Dimension maxFontSize = Dimension(10);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultFontSize(data.fontSize.value());
    pickerProperty->UpdateDefaultColor(data.textColor.value());
    pickerProperty->UpdateDefaultWeight(data.fontWeight.value());
    pickerProperty->UpdateDefaultMinFontSize(minFontSize);
    pickerProperty->UpdateDefaultMaxFontSize(maxFontSize);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto defaultTextStyle = json->GetObject("defaultTextStyle");
    ASSERT_NE(defaultTextStyle, nullptr);
    EXPECT_EQ(defaultTextStyle->GetString("color"), "#FFFF0000");
    EXPECT_EQ(defaultTextStyle->GetString("minFontSize"), "10.00px");
    EXPECT_EQ(defaultTextStyle->GetString("maxFontSize"), "10.00px");
    auto defaultFont = defaultTextStyle->GetObject("font");
    ASSERT_NE(defaultFont, nullptr);
    EXPECT_EQ(defaultFont->GetString("size"), "10.00px");
    EXPECT_EQ(defaultFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValueDivider
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerToJson, TextPickerLayoutPropertyToJsonValueDivider, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct divider property values and call  SetDivider.
     */
    ItemDivider dividerData;
    dividerData.strokeWidth = 6.0_vp;
    dividerData.startMargin = 6.0_vp;
    dividerData.endMargin = 6.0_vp;
    dividerData.color = Color::RED;
    TextPickerModelNG::GetInstance()->SetDivider(dividerData);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    auto divider = json->GetObject("divider");
    ASSERT_NE(divider, nullptr);
    EXPECT_EQ(divider->GetString("color"), "#FFFF0000");
    EXPECT_EQ(divider->GetString("strokeWidth"), "6.00vp");
    EXPECT_EQ(divider->GetString("startMargin"), "6.00vp");
    EXPECT_EQ(divider->GetString("endMargin"), "6.00vp");
}
} // namespace OHOS::Ace::NG
