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
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr size_t SECOND = 2;
constexpr uint32_t SELECTED_INDEX_1 = 1;
constexpr double FONT_SIZE_5 = 5.0;
constexpr double FONT_SIZE_10 = 10.0;
constexpr double FONT_SIZE_20 = 20.0;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
const OffsetF CHILD_OFFSET(0.0f, 10.0f);
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
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

class TextPickerPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerPatternTestNg();
    void DestroyTextPickerPatternTestNgObject();

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

void TextPickerPatternTestNg::DestroyTextPickerPatternTestNgObject()
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

void TextPickerPatternTestNg::InitTextPickerPatternTestNg()
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

void TextPickerPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerPatternTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerPatternTestNg::TearDown()
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
 * @tc.name: TextPickerPatternToJsonValue001
 * @tc.desc: Test TextPickerPattern ToJsonValue(range is not empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternToJsonValue001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    disappearTextStyle.textColor = Color::BLACK;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    textStyle.textColor = Color::BLUE;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    selectedTextStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    textPickerPattern->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerPatternToJsonValue002
 * @tc.desc: Test TextPickerPattern ToJsonValue(range is empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternToJsonValue002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    textPickerPattern->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerPattern ToJsonValue003
 * @tc.desc: Test TextPickerPattern ToJsonValue(isCascade_ is false).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternToJsonValue003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();

    /**
     * @tc.cases: case. cover cascadeOriginptions_ is not empty
     */
    NG::TextCascadePickerOptions option;
    option.rangeResult = { "rangeResult1", "rangeResult2" };
    std::vector<NG::TextCascadePickerOptions> options;
    options.emplace_back(option);

    textPickerPattern->SetCascadeOptions(options, options);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    /**
     * @tc.cases: case. cover isCascade_ == false
     */
    textPickerPattern->SetIsCascade(false);
    textPickerPattern->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);

    /**
     * @tc.cases: case. cover isCascade_ == true
     */
    textPickerPattern->SetIsCascade(true);
    textPickerPattern->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerPatternProcessDepth001
 * @tc.desc: Test TextPickerPattern ProcessCascadeOptionDepth(child is empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternProcessDepth001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    NG::TextCascadePickerOptions option;
    option.rangeResult = { "1", "2", "3" };
    /**
     * @tc.step: step2. create cascade option and call it.
     * @tc.expected: caculate the option depth, the depth is correct.
     */
    auto depth = textPickerPattern->ProcessCascadeOptionDepth(option);
    EXPECT_EQ(1, depth);
}

/**
 * @tc.name: TextPickerPatternProcessDepth002
 * @tc.desc: Test TextPickerPattern ProcessCascadeOptionDepth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternProcessDepth002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    /**
     * @tc.step: step2. create cascade option and call it.
     * @tc.expected: caculate the option depth, the depth is correct.
     */
    NG::TextCascadePickerOptions option;
    option.rangeResult = { "1", "2", "3" };
    NG::TextCascadePickerOptions childoption;
    childoption.rangeResult = { "11", "12", "13" };
    option.children.emplace_back(childoption);
    auto depth = textPickerPattern->ProcessCascadeOptionDepth(option);
    EXPECT_EQ(SECOND, depth);
}

/**
 * @tc.name: TextPickerPatternTest001
 * @tc.desc: test OnKeyEvent when event.action is not DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.cases: case1. up KeyEvent.
     */
    KeyEvent keyEventUp(KeyCode::KEY_DPAD_UP, KeyAction::UP);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventUp));

    /**
     * @tc.cases: case2. down KeyEvent.
     */
    KeyEvent keyEventDown(KeyCode::KEY_DPAD_DOWN, KeyAction::UP);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventDown));
}

/**
 * @tc.name: TextPickerPatternTest002
 * @tc.desc: test OnKeyEvent when event.action is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.cases: case1. left KeyEvent.
     */
    KeyEvent keyEventLeft(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventLeft));

    /**
     * @tc.cases: case2. right KeyEvent.
     */
    KeyEvent keyEventRight(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventRight));

    /**
     * @tc.cases: case3. up KeyEvent.
     */
    KeyEvent keyEventUp(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventUp));

     /**
      * @tc.cases: case4. down KeyEvent.
      */
    KeyEvent keyEventDwn(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventDwn));

     /**
     * @tc.cases: case5. move home KeyEvent.
     */
    KeyEvent keyEventMoveHome(KeyCode::KEY_MOVE_HOME, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventMoveHome));

     /**
      * @tc.cases: case6. move end KeyEvent.
      */
    KeyEvent keyEventMoveEnd(KeyCode::KEY_MOVE_END, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventMoveEnd));

    /**
     * @tc.cases: case7. KEY_TAB KeyEvent.
     */
    KeyEvent keyEventTab(KeyCode::KEY_TAB, KeyAction::DOWN);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventTab));

    /**
     * @tc.cases: case8. KEY_SPACE KeyEvent.
     */
    KeyEvent keyEventSpace(KeyCode::KEY_SPACE, KeyAction::DOWN);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventSpace));

    /**
     * @tc.cases: case9. KEY_ENTER KeyEvent.
     */
    KeyEvent keyEventEnter(KeyCode::KEY_ENTER, KeyAction::DOWN);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventEnter));
}

/**
 * @tc.name: TextPickerPatternTest003
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    /**
     * @tc.step: step2. call pattern's OnDirtyLayoutWrapperSwap method.
     */
    auto ret = pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TextPickerPatternTest004
 * @tc.desc: Test OnColumnsBuilding.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);

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
    /**
     * @tc.step: step2. Set Multi Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);

    std::vector<uint32_t> selecteds = { 0, 1, 2 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    TextPickerModelNG::GetInstance()->SetCanLoop(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * cover isCascade_ == true
     */
    pickerPattern->OnModifyDone();
    /**
     * cover isCascade_ == false
     */
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    pickerPattern->SetCascadeOptions(options, options);
    pickerPattern->OnModifyDone();
}

/**
 * @tc.name: TextPickerPatternTest005
 * @tc.desc: Test GetSelectedObject
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest005, TestSize.Level1)
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
    pickerPattern->SetCascadeOptions(options, options);
    std::vector<uint32_t> selecteds = { 0, 1, 2 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values = { "0", "1", "2" };
    TextPickerModelNG::GetInstance()->SetValues(values);
    TextPickerModelNG::GetInstance()->SetCanLoop(true);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    /**
     * test method HandleChangeCallback
     */
    columnPattern->HandleChangeCallback(true, true);
}

/**
 * @tc.name: TextPickerPatternTest006
 * @tc.desc: Test TextPickerPattern SetButtonIdeaSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest006, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    auto blendNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    auto geometryNode = stackNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    stackNode->MountToParent(frameNode);
    SizeF frameSize(FONT_SIZE_20, FONT_SIZE_20);
    geometryNode->SetFrameSize(frameSize);
    textPickerPattern->SetButtonIdeaSize();
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->width_.value(), CalcLength(12.0));
}

/**
 * @tc.name: TextPickerPatternTest007
 * @tc.desc: Test TextPickerPattern CalculateHeight().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest007, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    /**
     * @tc.cases: case. cover branch HasDefaultPickerItemHeight() is true and DimensionUnit is PERCENT
     */
    Dimension dimension(10.0f);
    dimension.SetUnit(DimensionUnit::PERCENT);
    textPickerLayoutProperty->UpdateDefaultPickerItemHeight(dimension);
    textPickerPattern->CalculateHeight();
    EXPECT_EQ(textPickerLayoutProperty->GetDefaultPickerItemHeight(), dimension);

    /**
     * @tc.cases: case. cover branch NormalizeToPx(defaultPickerItemHeightValue) less or equals 0.
     */
    Dimension dimension1(-10.0f);
    textPickerLayoutProperty->UpdateDefaultPickerItemHeight(dimension1);
    textPickerPattern->CalculateHeight();
    EXPECT_EQ(textPickerLayoutProperty->GetDefaultPickerItemHeight(), dimension1);

    /**
     * @tc.cases: case. cover branch NormalizeToPx(defaultPickerItemHeightValue) more than 0
     */
    Dimension dimension2(10.0f);
    textPickerLayoutProperty->UpdateDefaultPickerItemHeight(dimension2);
    textPickerPattern->CalculateHeight();
    EXPECT_EQ(textPickerLayoutProperty->GetDefaultPickerItemHeight(), dimension2);
}

/**
 * @tc.name: TextPickerPatternTest008
 * @tc.desc: Test TextPickerPattern HandleDirectionKey().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest008, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();

    /**
     * @tc.cases: case1. KeyCode : KEY_DPAD_UP.
     */
    bool ret = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_UP);
    EXPECT_FALSE(ret);

    /**
     * @tc.cases: case2. KeyCode : KEY_DPAD_DOWN.
     */
    bool retOne = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN);
    EXPECT_FALSE(retOne);

    /**
     * @tc.cases: case3. KeyCode : KEY_ENTER.
     */
    bool retTwo = textPickerPattern->HandleDirectionKey(KeyCode::KEY_ENTER);
    EXPECT_FALSE(retTwo);

    /**
     * @tc.cases: case4. KeyCode : KEY_DPAD_LEFT.
     */
    bool retThree = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_LEFT);
    EXPECT_FALSE(retThree);

    /**
     * @tc.cases: case5. KeyCode : KEY_DPAD_RIGHT.
     */
    bool retFour = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_RIGHT);
    EXPECT_FALSE(retFour);
}

/**
 * @tc.name: TextPickerPatternTest009
 * @tc.desc: Test TextPickerPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest009, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();

    /**
     * @tc.cases: case. cover branch OnColorConfigurationUpdate isPicker_ == true.
     */
    pickerPattern->OnColorConfigurationUpdate();
}

/**
 * @tc.name: TextPickerPatternTest010
 * @tc.desc: Test TextPickerPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest010, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();

    /**
     * @tc.cases: case. cover branch isPicker_ == false.
     */
    pickerPattern->SetPickerTag(false);
    pickerPattern->OnColorConfigurationUpdate();
}

/**
 * @tc.name: TextPickerPatternTest011
 * @tc.desc: Test TextPickerPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest011, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();

    /**
     * @tc.cases: case. cover branch isPicker_ == false.
     */
    pickerPattern->SetPickerTag(false);

    /**
     * @tc.cases: case. cover branch contentRowNode_ is not null.
     */
    auto columnNode = pickerPattern->GetColumnNode();
    pickerPattern->SetContentRowNode(columnNode);
    pickerPattern->OnColorConfigurationUpdate();
}

/**
 * @tc.name: TextPickerPatternTest012
 * @tc.desc: Test TextPickerPattern SetButtonIdeaSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest012, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    /**
     * @tc.cases: case. cover branch resizeFlag_ == true.
     */
    textPickerPattern->SetResizeFlag(true);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    auto blendNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    auto geometryNode = stackNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    stackNode->MountToParent(frameNode);
    SizeF frameSize(FONT_SIZE_20, FONT_SIZE_20);
    geometryNode->SetFrameSize(frameSize);
    textPickerPattern->SetButtonIdeaSize();
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->width_.value(), CalcLength(12.0));
}

/**
 * @tc.name: TextPickerPatternTest013
 * @tc.desc: Test TextPickerPattern HandleDirectionKey().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest013, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();

    /**
     * @tc.step: step2. ccover branch totalOptionCount == 0.
     * @tc.expected: call HandleDirectionKey() and result is false.
     */
    bool ret = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_UP);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TextPickerPatternTest014
 * @tc.desc: Test TextPickerPattern HandleDirectionKey.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest014, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto blendNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    auto geometryNode = stackNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    stackNode->MountToParent(frameNode);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    auto pickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    std::vector<RangeContent> options { { "icon" } };
    pickerColumnPattern->SetOptions(options);

    /**
     * @tc.cases: case. cover branch childSize more than 0.
     */
    bool ret = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_RIGHT);
    EXPECT_TRUE(ret);

    /**
     * @tc.cases: case. cover branch code default branch.
     */
    bool ret1 = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_CENTER);
    EXPECT_FALSE(ret1);
}

/**
 * @tc.name: TextPickerPatternTest015
 * @tc.desc: Test TextPickerPattern GetSelectedObjectMulti.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest015, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);

    /**
     * @tc.step: step2. Construction parameters and call GetSelectedObjectMulti().
     * @tc.expected: result is expected.
     */
    std::vector<std::string> values = { "111", "123", "134" };
    const std::vector<uint32_t> indexs = { 0, 1, 2 };
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    std::string result = textPickerPattern->GetSelectedObjectMulti(values, indexs, 2);
    std::string expectResult = "{\"value\":[\"111\",\"123\",\"134\"],\"index\":[0,1,2],\"status\":2}";
    EXPECT_EQ(result, expectResult);
}

/**
 * @tc.name: TextPickerPatternTest016
 * @tc.desc: Test ChangeCurrentOptionValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest016, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. Initialize TextCascadePickerOptions、selecteds_ and values.
     */
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions option;
    option.rangeResult = { "111", "123", "134" };
    NG::TextCascadePickerOptions optionsChild1;
    optionsChild1.rangeResult = { "11", "12", "13" };
    options.emplace_back(optionsChild1);
    NG::TextCascadePickerOptions optionsChild2;
    optionsChild2.rangeResult = { "21", "22", "23" };
    options.emplace_back(optionsChild2);
    option.children = options;

    pickerPattern->selecteds_ = { 0, 0 };
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    pickerPattern->SetValues(values);

    /**
     * @tc.step: step3. call ChangeCurrentOptionValue(), cover branch replaceColumn less or equals curColumn.
     * @tc.expected: expect successfully.
     */
    pickerPattern->ChangeCurrentOptionValue(optionsChild1, 16, 1, 0);
    EXPECT_EQ(pickerPattern->selecteds_[1], 16);

    /**
     * @tc.cases: case. cover branch replaceColumn more than curColumn.
     */
    pickerPattern->ChangeCurrentOptionValue(option, 17, 0, 1);
    EXPECT_EQ(pickerPattern->selecteds_[1], 17);
}

/**
 * @tc.name: TextPickerPatternTest017
 * @tc.desc: Test OnLanguageConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest017, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPickerNode->MountToParent(contentColumn);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(buttonConfirmNode);
    CHECK_NULL_VOID(textConfirmNode);
    textConfirmNode->MountToParent(buttonConfirmNode);
    textPickerPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonCancelNode);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(textCancelNode);
    textCancelNode->MountToParent(buttonCancelNode);
    textPickerPattern->SetCancelNode(buttonCancelNode);
    textPickerPattern->OnLanguageConfigurationUpdate();
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);
    std::string nodeInfo = "";
    auto cancel = dialogTheme->GetCancelText();
    EXPECT_EQ(cancel, nodeInfo);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test TextPickerPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    DirtySwapConfig config;
    auto isShowInDialog = textPickerPattern->GetIsShowInDialog();
    textPickerPattern->SetIsShowInDialog(true);
    textPickerPattern->useButtonFocusArea_ = true;
    EXPECT_FALSE(textPickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    textPickerPattern->SetIsShowInDialog(false);
    textPickerPattern->useButtonFocusArea_ = true;
    EXPECT_TRUE(textPickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    textPickerPattern->SetIsShowInDialog(isShowInDialog);
}

/**
 * @tc.name: TextPickerPatternTest018
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest018, TestSize.Level1)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    CrownEvent crownEvent;
    crownEvent.action = OHOS::Ace::CrownAction::BEGIN;
    EXPECT_TRUE(focusHub->ProcessOnCrownEventInternal(crownEvent));
    crownEvent.action = OHOS::Ace::CrownAction::UPDATE;
    EXPECT_TRUE(focusHub->ProcessOnCrownEventInternal(crownEvent));
    crownEvent.action = OHOS::Ace::CrownAction::END;
    EXPECT_TRUE(focusHub->ProcessOnCrownEventInternal(crownEvent));
#endif
}

/**
 * @tc.name: TextPickerPatternTest019
 * @tc.desc: Test GetColumnWidthSumForFirstIndexColumns
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest019, TestSize.Level1)
{
    InitTextPickerPatternTestNg();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(textPickerPattern_, nullptr);

    auto columnNodeGeometryNode = columnNode_->GetGeometryNode();
    ASSERT_NE(columnNodeGeometryNode, nullptr);
    columnNodeGeometryNode->SetFrameSize(SizeF(20.0f, 1.0f));
    auto columnNodeNextGeometryNode = columnNodeNext_->GetGeometryNode();
    ASSERT_NE(columnNodeNextGeometryNode, nullptr);
    columnNodeNextGeometryNode->SetFrameSize(SizeF(30.0f, 1.0f));

    int32_t childCount = static_cast<int32_t>(frameNode_->GetChildren().size());
    EXPECT_EQ(childCount, 2);

    textPickerPattern_->focusKeyID_ = 0;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    float sum = textPickerPattern_->GetColumnWidthSumForFirstIndexColumns(0);
    EXPECT_FLOAT_EQ(sum, 0);

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    sum = textPickerPattern_->GetColumnWidthSumForFirstIndexColumns(0);
    EXPECT_FLOAT_EQ(sum, 30);

    textPickerPattern_->focusKeyID_ = 1;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    sum = textPickerPattern_->GetColumnWidthSumForFirstIndexColumns(1);
    EXPECT_FLOAT_EQ(sum, 20);

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    sum = textPickerPattern_->GetColumnWidthSumForFirstIndexColumns(1);
    EXPECT_FLOAT_EQ(sum, 0);
}

/**
 * @tc.name: TextPickerPatternTest020
 * @tc.desc: Test CalculateColumnSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest020, TestSize.Level1)
{
    InitTextPickerPatternTestNg();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(textPickerPattern_, nullptr);

    int32_t index = 0;
    float childCount = 1.0f;
    SizeF pickerContentSize = SizeF(0.0f, 200.0f);
    auto columnSize = textPickerPattern_->CalculateColumnSize(index, childCount, pickerContentSize);
    EXPECT_FLOAT_EQ(columnSize, 0.0f);

    std::vector<Dimension> width;
    width.emplace_back(Dimension(10.0f, DimensionUnit::PX));
    textPickerPattern_->SetColumnWidths(width);
    index = 1;
    childCount = 2.0f;
    pickerContentSize = SizeF(100.0f, 200.0f);
    columnSize = textPickerPattern_->CalculateColumnSize(index, childCount, pickerContentSize);
    EXPECT_FLOAT_EQ(columnSize, 90.0f);

    textPickerPattern_->SetColumnWidths(width);
    index = 1;
    childCount = 1.0f;
    pickerContentSize = SizeF(100.0f, 200.0f);
    columnSize = textPickerPattern_->CalculateColumnSize(index, childCount, pickerContentSize);
    EXPECT_FLOAT_EQ(columnSize, 0.0f);
}

/**
 * @tc.name: TextPickerPatternTest021
 * @tc.desc: Test GetColumnWidthsStr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerPatternTestNg, TextPickerPatternTest021, TestSize.Level1)
{
    InitTextPickerPatternTestNg();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(textPickerPattern_, nullptr);
    auto columnWidthsStr = textPickerPattern_->GetColumnWidthsStr();
    EXPECT_STREQ(columnWidthsStr.c_str(), "0.00px,0.00px");

    auto host = textPickerPattern_->GetHost();
    auto children = host->GetChildren();
    for (auto iter = children.begin(); iter != children.end(); iter++) {
        ASSERT_NE(*iter, nullptr);
        auto stackNode = AceType::DynamicCast<FrameNode>(*iter);
        host->RemoveChildAndReturnIndex(stackNode);
    }
    columnWidthsStr = textPickerPattern_->GetColumnWidthsStr();
    EXPECT_STREQ(columnWidthsStr.c_str(), "");
}
} // namespace OHOS::Ace::NG
