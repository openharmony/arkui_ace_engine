/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
const InspectorFilter filter;
constexpr int32_t HALF_INDEX_NUM = 5;
constexpr int32_t INDEX_NUM = 10;
constexpr int32_t CURRENT_INDEX = 8;
constexpr int32_t CURRENT_END_INDEX = 3;
constexpr size_t SECOND = 2;
constexpr uint32_t SELECTED_INDEX_1 = 1;
constexpr double FONT_SIZE_5 = 5.0;
constexpr double FONT_SIZE_10 = 10.0;
constexpr double FONT_SIZE_20 = 20.0;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
constexpr double TOSS_DELTA = 20.0;
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const double YOFFSET_START2 = 2000.0;
const double YOFFSET_END2 = 3000.0;
const double TIME_PLUS = 1 * 100.0;
const double TIME_PLUS_LARGE = 10 * 1000.0;
constexpr double DISTANCE = 20.0;
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
constexpr double OVER_SCROLL_OFFSET1 = 40.0;
constexpr double OVER_SCROLL_OFFSET2 = 60.0;
constexpr double OVER_SCROLL_DELTA = 10.0;
constexpr uint32_t OVER_SCROLL_ITEMS = 20;
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
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

class TextPickerExTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerExTestNg();
    void DestroyTextPickerExTestNgObject();

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

void TextPickerExTestNg::DestroyTextPickerExTestNgObject()
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

void TextPickerExTestNg::InitTextPickerExTestNg()
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

void TextPickerExTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerExTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerExTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerExTestNg::TearDown()
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
 * @tc.name: TextPickerLayoutPropertyToJsonValue001
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue001, TestSize.Level1)
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
     * @tc.step: step2. Get json result and compare the result.
     * @tc.expected: the result of ToJsonValue is correct.
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pickerProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerLayoutPropertyClone001
 * @tc.desc: Test TextPickerLayoutProperty Clone.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyClone001, TestSize.Level1)
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
    auto layoutProperty = pickerProperty->Clone();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerLayoutPropertyReset001
 * @tc.desc: Test TextPickerLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyReset001, TestSize.Level1)
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
    pickerProperty->Reset();
    EXPECT_FALSE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyGetText001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetText(), EMPTY_TEXT);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetText(), TEXT_PICKER_CONTENT);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerRowAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of textPickerRowAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerRowAccessibilityPropertyGetText001, TestSize.Level1)
{
    /**
     * @tc.step: step1. Init TextPickerExTestNg.
     */
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), EMPTY_TEXT);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    /**
     * @tc.step: step2. Set Options of Multi Columns.
     */
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPatternNext_->SetOptions(contents);
    /**
     * @tc.step: step3. Get Text result and compare the result.
     * @tc.expected: the result of GetText is correct.
     */
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), TEXT_PICKER_CONTENT + TEXT_PICKER_CONTENT);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerRowAccessibilityPropertyGetText002
 * @tc.desc: Test GetText of textPickerRowAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerRowAccessibilityPropertyGetText002, TestSize.Level1)
{
    /**
     * @tc.step: step1. Init TextPickerExTestNg.
     */
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), EMPTY_TEXT);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    /**
     * @tc.step: step2. Set Options of Single Column.
     */
    textPickerColumnPattern_->SetOptions(contents);
    /**
     * @tc.step: step3. Get Text result and compare the result.
     * @tc.expected: the result of GetText is correct.
     */
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), TEXT_PICKER_CONTENT);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerRowAccessibilityPropertyGetText003
 * @tc.desc: Test GetText of textPickerRowAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerRowAccessibilityPropertyGetText003, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode, nullptr);

    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    stackNode->MountToParent(frameNode);

    auto RowAccessibilityProperty = frameNode->GetAccessibilityProperty<TextPickerRowAccessibilityProperty>();
    ASSERT_NE(RowAccessibilityProperty, nullptr);

    EXPECT_EQ(RowAccessibilityProperty->GetText(), "");
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCurrentIndex(), 0);
    textPickerColumnPattern_->SetCurrentIndex(INDEX_NUM);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCurrentIndex(), INDEX_NUM);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), 0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);

    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(0);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), 0);

    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(INDEX_NUM);
    textPickerColumnPattern_->halfDisplayCounts_ = SECOND;
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), CURRENT_INDEX);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), 0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);

    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(1);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->halfDisplayCounts_ = SECOND;
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), CURRENT_END_INDEX);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    AccessibilityValue result;
    EXPECT_TRUE(textPickerAccessibilityProperty_->HasRange());
    result = textPickerAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 0);
    EXPECT_EQ(result.current, 0);

    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index <= INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(INDEX_NUM);
    result = textPickerAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, INDEX_NUM);
    EXPECT_EQ(result.current, INDEX_NUM);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCollectionItemCounts(), 0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM);
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    EXPECT_FALSE(textPickerAccessibilityProperty_->IsScrollable());
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_TRUE(textPickerAccessibilityProperty_->IsScrollable());
    DestroyTextPickerExTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertySetSpecificSupportAction001
 * @tc.desc: Test SetSpecificSupportAction of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertySetSpecificSupportAction001, TestSize.Level1)
{
    InitTextPickerExTestNg();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index <= HALF_INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(1);
    textPickerAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = textPickerAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    for (int index = 0; index <= INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerAccessibilityProperty_->ResetSupportAction();
    supportAceActions = textPickerAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: TextPickerPaintTest001
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerPaintTest001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    theme->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TextPickerPaintTest002
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerPaintTest002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    /**
     * @tc.cases: case. cover branch GetResizeFlag() is true.
     */
    textPickerPattern->SetResizeFlag(true);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    textPickerPaintMethod->SetEnabled(false);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TextPickerPaintTest003
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerPaintTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrentContext()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);

    /**
     * @tc.steps: step2. execute SetStrokeWidth
     * @tc.expected: the results we get are as expected
     */
    ItemDivider divider;
    DividerInfo info;
    auto result = textPickerPaintMethod->SetStrokeWidth(divider, 0.0, info);
    EXPECT_FALSE(result);

    divider.strokeWidth = 10.0_px;
    result = textPickerPaintMethod->SetStrokeWidth(divider, 0.0, info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextPickerPaintTest004
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerPaintTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    theme->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);

    /**
     * @tc.steps: step2. execute NeedPaintDividerLines
     * @tc.expected: the results we get are as expected
     */
    RectF contentRect;
    ItemDivider divider;
    DividerInfo info;
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, divider, 0.0, info);
    EXPECT_FALSE(result);

    auto thickness = theme->GetDividerThickness();
    auto isShowInDialog = textPickerPattern->GetIsShowInDialog();

    theme->dividerThickness_ = 10.0_px;
    divider.strokeWidth = 10.0_px;
    textPickerPattern->SetIsShowInDialog(true);
    result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, divider, 0.0, info);
    textPickerPattern->SetIsShowInDialog(false);
    result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, divider, 0.0, info);
    EXPECT_FALSE(result);

    contentRect.width_ = 5.0f;
    divider.endMargin = 10.0_px;
    result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, divider, 0.0, info);
    divider.isRtl = !divider.isRtl;
    result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, divider, 0.0, info);
    EXPECT_TRUE(result);

    theme->dividerThickness_ = thickness;
    textPickerPattern->SetIsShowInDialog(isShowInDialog);
}

/**
 * @tc.name: CanLoopTest001
 * @tc.desc: test CanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, CanLoopTest001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();

    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();

    // canLoop = false,click down, current isn't changed
    param->instance = nullptr;
    param->itemIndex = 3; // down
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->SetCurrentIndex(4);
    pickerNodeLayout->UpdateCanLoop(false);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    uint32_t index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: CanLoopTest002
 * @tc.desc: test CanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, CanLoopTest002, TestSize.Level1)
{
    InitTextPickerExTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();

    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();

    // canLoop = false,click down, current isn't changed
    param->instance = nullptr;
    param->itemIndex = 4; // down
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->SetCurrentIndex(4);
    pickerNodeLayout->UpdateCanLoop(false);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    uint32_t index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: CanLoopTest003
 * @tc.desc: test CanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, CanLoopTest003, TestSize.Level1)
{
    InitTextPickerExTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();

    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();

    // canLoop = false,click up, current isn't changed
    param->instance = nullptr;
    param->itemIndex = 1; // up
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->SetCurrentIndex(0);
    pickerNodeLayout->UpdateCanLoop(false);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    uint32_t index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: CanLoopTest004
 * @tc.desc: test CanLoop
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, CanLoopTest004, TestSize.Level1)
{
    InitTextPickerExTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();

    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();

    // canLoop = false,click up, current isn't changed
    param->instance = nullptr;
    param->itemIndex = 0; // up
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->SetCurrentIndex(0);
    pickerNodeLayout->UpdateCanLoop(false);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    uint32_t index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: TextPickerFireChangeEventTest001
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerFireChangeEventTest001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto onSelectedChange = [](const std::vector<double>& indexs) {
        for (auto index : indexs) {
            EXPECT_EQ(index, 1.0);
        }
    };

    auto onValueChange = [](const std::vector<std::string>& values) {
        for (auto value : values) {
            EXPECT_EQ(value, "currentValue");
        }
    };
    TextPickerModelNG::GetInstance()->SetOnSelectedChangeEvent(std::move(onSelectedChange));
    TextPickerModelNG::GetInstance()->SetOnValueChangeEvent(std::move(onValueChange));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto textPickerEventHub = frameNode->GetOrCreateEventHub<NG::TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    textPickerEventHub->SetOnSelectedChangeEvent(std::move(onSelectedChange));
    textPickerEventHub->SetOnValueChangeEvent(std::move(onValueChange));
    ASSERT_NE(textPickerEventHub->onValueChangeEvent_, nullptr);
    ASSERT_NE(textPickerEventHub->onSelectedChangeEvent_, nullptr);

    std::vector<std::string> values { "currentValue" };
    std::vector<double> indexs { 1.0 };
    textPickerEventHub->FireChangeEvent(values, indexs);
    textPickerEventHub->FireScrollStopEvent(values, indexs);
}

/**
 * @tc.name: TextPickerKeyEvent001
 * @tc.desc: test OnKeyEvent when event.action is not DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerKeyEvent001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->OnModifyDone();

    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    textPickerPattern->InitOnKeyEvent(focusHub);

    /**
     * @tc.cases: case. test OnKeyEvent when event.action is not DOWN.
     */
    KeyEvent event;
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_DPAD_UP;
    bool result = textPickerPattern->OnKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextPickerKeyEvent002
 * @tc.desc: test OnKeyEvent when event.action is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerKeyEvent002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->OnModifyDone();

    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    textPickerPattern->InitOnKeyEvent(focusHub);

    KeyEvent event;
    event.action = KeyAction::DOWN;

    /**
     * @tc.cases: case1. event code is KEY_DPAD_UP.
     */
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(textPickerPattern->OnKeyEvent(event));

    /**
     * @tc.cases: case2. event code is KEY_DPAD_DOWN.
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(textPickerPattern->OnKeyEvent(event));

    /**
     * @tc.cases: case3. event code is KEY_MOVE_HOME.
     */
    event.code = KeyCode::KEY_MOVE_HOME;
    EXPECT_TRUE(textPickerPattern->OnKeyEvent(event));
 
     /**
      * @tc.cases: case4. event code is KEY_MOVE_END.
      */
    event.code = KeyCode::KEY_MOVE_END;
    EXPECT_TRUE(textPickerPattern->OnKeyEvent(event));

    /**
     * @tc.cases: case5. event code is KEY_DPAD_LEFT.
     */
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(textPickerPattern->OnKeyEvent(event));

    /**
     * @tc.cases: case6. event code is KEY_DPAD_RIGHT.
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(textPickerPattern->OnKeyEvent(event));

    /**
     * @tc.cases: case7. event code is KEY_SPACE.
     */
    EXPECT_FALSE(textPickerPattern->HandleDirectionKey(KeyCode::KEY_SPACE));
}

/**
 * @tc.name: PatternGetSelectedObject001
 * @tc.desc: Test TextPickerPattern GetSelectedObject()
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, PatternGetSelectedObject001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.step: step. cover branch GetIsDeclarative() is true.
     */
    MockPipelineContext::GetCurrent()->isDeclarative_ = true;

    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<std::string> values = { "0", "1", "2" };
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = AceType::DynamicCast<FrameNode>(frameNode)->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    TextPickerModelNG::GetInstance()->SetSelected(0);
    auto result = textPickerPattern->GetSelectedObject(false, 1);
    ASSERT_NE(result, EMPTY_TEXT);
}

/**
 * @tc.name: PatternGetSelectedObject002
 * @tc.desc: Test TextPickerPattern GetSelectedObject()
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, PatternGetSelectedObject002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.step: step. cover branch GetIsDeclarative() is true.
     */
    MockPipelineContext::GetCurrent()->isDeclarative_ = true;
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);

    std::vector<std::string> values = { "text", "rating", "qrcode" };
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FrameNode>(frameNode)->GetPattern<TextPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto result = pattern->GetSelectedObject(false, 1);
    ASSERT_NE(result, EMPTY_TEXT);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TextPicker accessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create textPicker and initialize related properties.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    auto pickerNodeLayout = pickerFrameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(false);

    /**
     * @tc.steps: step2. Get textPickerColumn frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto textPickerPattern = pickerFrameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->OnModifyDone();
    auto columnNode = textPickerPattern->GetColumnNode();
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->ClearOptions();
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    columnPattern->SetOptions(contents);
    columnPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get blendNode accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto blendNode = AceType::DynamicCast<FrameNode>(columnNode->GetParent());
    ASSERT_NE(blendNode, nullptr);
    auto accessibilityProperty = blendNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When textPickerColumn can not move, call the callback function in accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    columnPattern->SetCurrentIndex(0);
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When textPickerColumn can move, call the callback function in accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    columnPattern->SetOptions(contents);
    columnPattern->SetCurrentIndex(1);
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: TextPickerEventActionsTest001
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextEventActionsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create textPickerColumn.
     */
    InitTextPickerExTestNg();
    auto eventHub = frameNode_->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    textPickerColumnPattern_->InitPanEvent(gestureHub);

    /**
     * @tc.steps: step2. call actionStart_ func.
     * @tc.expected: pressed_ is true.
     */
    GestureEvent gestureEvent;
    auto panEvent = textPickerColumnPattern_->panEvent_;
    ASSERT_NE(panEvent->actionStart_, nullptr);
    panEvent->actionStart_(gestureEvent);
    EXPECT_TRUE(textPickerColumnPattern_->pressed_);

    /**
     * @tc.steps: step3. call actionEnd_ func.
     * @tc.expected: pressed_ is false.
     */
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(false);
    ASSERT_NE(panEvent->actionEnd_, nullptr);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(textPickerColumnPattern_->pressed_);

    /**
     * @tc.steps: step4. call actionEnd_ func in another condition.
     * @tc.expected: pressed_ is false.
     */
    pickerNodeLayout->UpdateCanLoop(true);
    EXPECT_FALSE(textPickerColumnPattern_->NotLoopOptions());
    auto toss = textPickerColumnPattern_->GetToss();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    textPickerColumnPattern_->pressed_ = true;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(textPickerColumnPattern_->pressed_);
}

/**
 * @tc.name: TextPickerTossAnimationControllerTest001
 * @tc.desc: Test TextPickerTossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerTossAnimationControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPickerTossAnimationController instance.
     */
    RefPtr<TextPickerTossAnimationController> toss = AceType::MakeRefPtr<TextPickerTossAnimationController>();
    auto column = AceType::MakeRefPtr<TextPickerColumnPattern>();
    toss->SetColumn(column);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    column->optionProperties_.emplace_back(prop);
    column->optionProperties_.emplace_back(prop);
    column->optionProperties_.emplace_back(prop);
    column->optionProperties_.emplace_back(prop);
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is true.
     */
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
}

/**
 * @tc.name: TextPickerTossAnimationControllerTest002
 * @tc.desc: Test TextPickerTossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerTossAnimationControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPickerTossAnimationController instance.
     */
    RefPtr<TextPickerTossAnimationController> toss = AceType::MakeRefPtr<TextPickerTossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is true.
     */
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    toss->SetStart(YOFFSET_START2);
    toss->SetEnd(YOFFSET_END2);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    EXPECT_EQ(toss->yStart_, 0);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END2);
}

/**
 * @tc.name: TextPickerTossAnimationControllerTest003
 * @tc.desc: Test TextPickerTossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerTossAnimationControllerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPickerTossAnimationController instance.
     */
    RefPtr<TextPickerTossAnimationController> toss = AceType::MakeRefPtr<TextPickerTossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() - TIME_PLUS;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is false.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TextPickerTossAnimationControllerTest004
 * @tc.desc: Test TextPickerTossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerTossAnimationControllerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPickerTossAnimationController instance.
     */
    RefPtr<TextPickerTossAnimationController> toss = AceType::MakeRefPtr<TextPickerTossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_START1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is false.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_START1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TextPickerTossAnimationControllerTest005
 * @tc.desc: Test TextPickerTossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerTossAnimationControllerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextPickerTossAnimationController instance.
     */
    RefPtr<TextPickerTossAnimationController> toss = AceType::MakeRefPtr<TextPickerTossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS_LARGE;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is false.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TextPickerAccessibilityPropertyTest001
 * @tc.desc: Test TextPickerAccessibilityProperty GetBeginIndex and GetEndIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get TextPickerColumnPattern and TextPickerLayoutProperty.
     * @tc.expected: Get successfully.
     */
    InitTextPickerExTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto layout = textPickerColumnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);

    /**
     * @tc.steps: step2. Call GetBeginIndex and GetEndIndex method while layout can't loop.
     * @tc.expected: The return value is base on the size of optionCount.
     */
    RangeContent rangeContent;
    rangeContent.icon_ = "ICON";
    rangeContent.text_ = "TEXT";
    std::vector<NG::RangeContent> value;
    value.emplace_back(rangeContent);
    value.emplace_back(rangeContent);
    textPickerColumnPattern->SetOptions(value);
    layout->UpdateCanLoop(false);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), 1);
}

/**
 * @tc.name: TextPickerAccessibilityPropertyTest002
 * @tc.desc: Test TextPickerAccessibilityProperty SetSpecificSupportAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerAccessibilityPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get TextPickerColumnPattern.
     * @tc.expected: Get successfully.
     */
    InitTextPickerExTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto layout = textPickerColumnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    textPickerAccessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction method with different currentIndex.
     * @tc.expected: The supportActions of TextPickerAccessibilityProperty changes.
     */
    RangeContent rangeContent;
    rangeContent.icon_ = "ICON";
    rangeContent.text_ = "TEXT";
    std::vector<NG::RangeContent> value;
    value.emplace_back(rangeContent);
    value.emplace_back(rangeContent);
    value.emplace_back(rangeContent);
    textPickerColumnPattern->SetOptions(value);
    textPickerColumnPattern->SetCurrentIndex(1);
    layout->UpdateCanLoop(false);
    auto preActions = textPickerAccessibilityProperty_->supportActions_;
    textPickerAccessibilityProperty_->SetSpecificSupportAction();
    EXPECT_NE(preActions, textPickerAccessibilityProperty_->supportActions_);
    textPickerColumnPattern->SetCurrentIndex(0);
    textPickerAccessibilityProperty_->SetSpecificSupportAction();
    EXPECT_NE(preActions, textPickerAccessibilityProperty_->supportActions_);
    textPickerColumnPattern->SetCurrentIndex(2);
    textPickerAccessibilityProperty_->SetSpecificSupportAction();
    EXPECT_NE(preActions, textPickerAccessibilityProperty_->supportActions_);
}

/**
 * @tc.name: GetOptionsMultiStr001
 * @tc.desc: Test TextPickerPattern GetOptionsMultiStr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, GetOptionsMultiStr001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. call GetOptionsMultiStr().
     * @tc.expected: the result of GetOptionsMultiStr is empty.
     */
    std::string result = pickerPattern->GetOptionsMultiStr();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: GetOptionsMultiStr002
 * @tc.desc: Test TextPickerPattern GetOptionsMultiStr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, GetOptionsMultiStr002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. call GetOptionsMultiStr().
     * @tc.expected: the result of GetOptionsMultiStr is [["11"]].
     */
    std::vector<TextCascadePickerOptions> options;
    TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    TextPickerModelNG::GetInstance()->SetColumns(options);
    std::string result = pickerPattern->GetOptionsMultiStr();
    std::string expectResult = "[[\"11\",\"12\",\"13\"]]";
    EXPECT_EQ(result, expectResult);
}

/**
 * @tc.name: GetOptionsCascadeStr001
 * @tc.desc: Test GetOptionsCascadeStr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, GetOptionsCascadeStr001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = { "31", "32", "33" };
    options.emplace_back(options3);

    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. call GetOptionsCascadeStr().
     * @tc.expected: the result of GetOptionsCascadeStr is "[{"text":"11"},{"text":"21"},{"text":"31"}]".
     */
    std::string result = pickerPattern->GetOptionsCascadeStr(options);
    std::string expectResult = "[{\"text\":\"11\"},{\"text\":\"21\"},{\"text\":\"31\"}]";
    EXPECT_EQ(result, expectResult);
}

/**
 * @tc.name: ChangeTextStyle001
 * @tc.desc: Test TextPickerLayoutAlgorithm::ChangeTextStyle().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, ChangeTextStyle001, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->ClearStack();
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    TextPickerModelNG::GetInstance()->Create(pickerTheme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF size(100.0f, 100.0f);
    pickerProperty->UpdateMarginSelfIdealSize(size);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto columnSubNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(columnSubNode, nullptr);

    /**
     * @tc.steps: creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);

    auto node = layoutWrapper.GetHostNode();
    ASSERT_NE(node, nullptr);
    auto layoutProperty_ = node->GetLayoutProperty()->Clone();
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: set layoutWrapper->layoutProperty_ is not null.
     */
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnSubNode, columnSubNode->GetGeometryNode(), layoutProperty_);
    EXPECT_NE(subLayoutWrapper, nullptr);

    auto layoutAlgorithmWrapper = subLayoutWrapper->GetLayoutAlgorithm();
    layoutWrapper.AppendChild(subLayoutWrapper);
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);

    /**
     * @tc.steps: set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto pattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    subLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    uint32_t index = 1;
    uint32_t showOptionCount = 2;
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.ChangeTextStyle(index, showOptionCount, size, subLayoutWrapper, &layoutWrapper);
    auto frameSize = subLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_TEXT_FRAME_SIZE);

    /**
     * @tc.case: cover branch index not equals selectedIndex .
     */
    uint32_t showOptionCount1 = 1;
    textPickerLayoutAlgorithm.ChangeTextStyle(index, showOptionCount1, size, subLayoutWrapper, &layoutWrapper);
    EXPECT_EQ(100.0f, subLayoutWrapper->GetGeometryNode()->GetFrameSize().Width());
}

/**
 * @tc.name: FlushAnimationTextProperties001
 * @tc.desc: Test TextPickerColumnPattern FlushAnimationTextProperties
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, FlushAnimationTextProperties001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    /**
     * @tc.step: step2. create textpicker cloumn pattern and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is 0.
     */
    columnPattern->FlushAnimationTextProperties(false);
    EXPECT_EQ(0, columnPattern->animationProperties_.size());

    /**
     * @tc.step: step3. construct columnPattern animationProperties_ and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is 1 and fontSize meet expectation.
     */
    std::vector<TextProperties> animationProperties;
    TextProperties properties1;
    properties1.upFontSize = Dimension(FONT_SIZE_5);
    properties1.fontSize = Dimension(FONT_SIZE_20);
    properties1.downFontSize = Dimension(FONT_SIZE_5);
    properties1.upColor = Color::RED;
    properties1.currentColor = Color::RED;
    properties1.downColor = Color::RED;
    animationProperties.emplace_back(properties1);
    columnPattern->animationProperties_ = animationProperties;

    columnPattern->FlushAnimationTextProperties(false);
    Dimension result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_10), result);
    columnPattern->FlushAnimationTextProperties(true);
    result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_5), result);

    /**
     * @tc.step: step4. add construct columnPattern animationProperties_ and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is more than 1 and fontSize meet expectation.
     */
    TextProperties properties2;
    properties2.upFontSize = Dimension(FONT_SIZE_10);
    properties2.fontSize = Dimension(FONT_SIZE_20);
    properties2.downFontSize = Dimension(FONT_SIZE_10);
    properties2.upColor = Color::RED;
    properties2.currentColor = Color::RED;
    properties2.downColor = Color::RED;
    animationProperties.emplace_back(properties2);
    columnPattern->animationProperties_ = animationProperties;

    columnPattern->FlushAnimationTextProperties(false);
    result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_10), result);
    columnPattern->FlushAnimationTextProperties(true);
    result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_20), result);
}

/**
 * @tc.name: TextPickerOverscroller001
 * @tc.desc: Test TextPickerColumnPattern OverScroller, move down.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerOverscroller001, TestSize.Level1)
{
    InitTextPickerExTestNg();
    ASSERT_NE(frameNode_, nullptr);
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(false);

    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->GetGeometryNode()->SetFrameSize(COLUMN_SIZE);
    textPickerColumnPattern_->SetCurrentIndex(0);
    std::vector<NG::RangeContent> range = { { "", "" } };
    textPickerColumnPattern_->SetOptions(range);

    // init overscroller
    TextPickerOverscroller overscroller;
    overscroller.SetColumn(textPickerColumnPattern_);
    EXPECT_EQ(overscroller.GetOverScroll(), 0);

    // overScroll to OVER_SCROLL_OFFSET1
    overscroller.ApplyCurrentOffset(0.0, OVER_SCROLL_OFFSET1, TOSS_DELTA);
    EXPECT_TRUE(overscroller.IsOverScroll());
    EXPECT_GT(overscroller.GetOverScroll(), DISTANCE);
    EXPECT_FALSE(overscroller.IsBackOverScroll());
    EXPECT_EQ(overscroller.GetBackScroll(), 0);

    // overScroll to max
    overscroller.SetOverScroll(OVER_SCROLL_OFFSET2);
    auto yLast = OVER_SCROLL_OFFSET1;
    auto offsetY = OVER_SCROLL_OFFSET1 + OVER_SCROLL_DELTA;
    for (auto i = 0; i < OVER_SCROLL_ITEMS; i++) {
        overscroller.ApplyCurrentOffset(yLast, offsetY, TOSS_DELTA);
        yLast = offsetY;
        offsetY = yLast + OVER_SCROLL_DELTA;
    }

    EXPECT_TRUE(overscroller.InMaxOverScroll());
    EXPECT_TRUE(overscroller.ShouldStartRebound());

    // reset overscroller
    overscroller.Reset();
    EXPECT_EQ(overscroller.GetOverScroll(), 0);
    EXPECT_FALSE(overscroller.IsOverScroll());
}
/**
 * @tc.name: TextPickerModelNGSetGradientHeight002
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerModelNGSetGradientHeight002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerDialogViewUpdateButtonDefaultFocus001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerDialogViewUpdateButtonDefaultFocus002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerDialogViewUpdateButtonDefaultFocus003, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}
/**
 * @tc.name: TextPickerModelNGSetColumns004
 * @tc.desc: Test SetCascadeColumns.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerModelNGSetColumns004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = { "31", "32", "33" };
    options.emplace_back(options3);

    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.step: step2. call GetCascadeOptionCount.
     * @tc.expected: the result of GetCascadeOptionCount is 1.
     */
    EXPECT_EQ(1, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight001
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerModelNGSetGradientHeight001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerPaintTest005
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerPaintTest005, TestSize.Level1)
{
#ifdef ARKUI_WEARABLE
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    auto renderContext = frameNode->GetRenderContext();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
#endif
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue002
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();

    /**
     * @tc.step: step2. call ToJsonValue.
     * @tc.expected: the default result.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "0.00px");
    EXPECT_EQ(json->GetString("gradientHeight"), "0.00px");
    EXPECT_EQ(json->GetString("canLoop"), "true");
    EXPECT_EQ(json->GetString("selected"), "0");
    EXPECT_EQ(json->GetString("value"), "");

    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FF000000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "14.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Normal");

    auto textStyle = json->GetObject("textStyle");
    ASSERT_NE(textStyle, nullptr);
    ASSERT_EQ(textStyle->GetString("color"), "#FF000000");
    auto normalFont = textStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "14.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Normal");

    auto selectTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectTextStyle, nullptr);
    EXPECT_EQ(selectTextStyle->GetString("color"), "#FF000000");
    auto selectFont = textStyle->GetObject("font");
    ASSERT_NE(selectFont, nullptr);
    EXPECT_EQ(selectFont->GetString("size"), "14.00px");
    EXPECT_EQ(selectFont->GetString("weight"), "FontWeight.Normal");

    auto defaulTextStyle = json->GetObject("defaultTextStyle");
    ASSERT_NE(defaulTextStyle, nullptr);
    EXPECT_EQ(defaulTextStyle->GetString("color"), "#FF000000");
    EXPECT_EQ(defaulTextStyle->GetString("minFontSize"), "0.00px");
    EXPECT_EQ(defaulTextStyle->GetString("maxFontSize"), "0.00px");
    EXPECT_EQ(defaulTextStyle->GetString("overflow"), "TextOverflow.Clip");
    auto defaulFont = textStyle->GetObject("font");
    ASSERT_NE(defaulFont, nullptr);
    EXPECT_EQ(defaulFont->GetString("size"), "14.00px");
    EXPECT_EQ(defaulFont->GetString("weight"), "FontWeight.Normal");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue003
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue003, TestSize.Level1)
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

    /**
     * @tc.step: step2. call ToJsonValue.
     * @tc.expected: the canLoop result is true.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("canLoop"), "true");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue004
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue004, TestSize.Level1)
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

    auto jsonArrayValues = json->GetValue("values");
    EXPECT_EQ(jsonArrayValues->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArrayValues->GetString(std::to_string(i).c_str()), values[i]);
    }
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue005
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue005, TestSize.Level1)
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
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue006, TestSize.Level1)
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

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), defaultPickerItemHeight.ToString().c_str());
    EXPECT_EQ(json->GetString("gradientHeight"), gradientHeight.ToString().c_str());
    EXPECT_EQ(json->GetString("selected"), std::to_string(selected));
    EXPECT_EQ(json->GetString("value"), value.c_str());
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue007
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue007, TestSize.Level1)
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
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue008, TestSize.Level1)
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
 * @tc.name: TextPickerLayoutPropertyToJsonValue009
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue009, TestSize.Level1)
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
 * @tc.name: TextPickerLayoutPropertyToJsonValue0010
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerExTestNg, TextPickerLayoutPropertyToJsonValue010, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto disappearTextStyle = json->GetObject("defaultTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FFFF0000");
    EXPECT_EQ(disappearTextStyle->GetString("minFontSize"), "10.00px");
    EXPECT_EQ(disappearTextStyle->GetString("maxFontSize"), "10.00px");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "10.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Bold");
}
} // namespace OHOS::Ace::NG
