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
     * @tc.expected: it should be -.
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
     * @tc.expected: it should be -.
     */
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "50.00px");
}


} // namespace OHOS::Ace::NG
