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

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t COLUMN_INDEX_0 = 0;
constexpr int32_t COLUMN_INDEX_2 = 2;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr uint32_t SELECTED_INDEX_2 = 2;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
constexpr double TOSS_DELTA = 20.0;
constexpr double DISTANCE = 20.0;
const OffsetF CHILD_OFFSET(0.0f, 10.0f);
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
const std::vector<std::string> DEFAULT_VALUE = { "1", "2", "3" };
const std::vector<std::string> CUSTOM_VALUE = { "appCustomFont" };
#ifdef SUPPORT_DIGITAL_CROWN
const int COLUMN_INDEX[] = {0, 1, 2, 3, 4};
const int32_t CROWN_SENSITIVITY_ERR = -1;
const int32_t CROWN_SENSITIVITY_ONE = 1;
const int32_t CROWN_SENSITIVITY_THR = 3;
const float OFFSET_FIVE = 5.0f;
#endif
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

class TextPickerColumnTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerColumnTestTwoNg();
    void DestroyTextPickerColumnTestTwoNgObject();

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

void TextPickerColumnTestTwoNg::DestroyTextPickerColumnTestTwoNgObject()
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

void TextPickerColumnTestTwoNg::InitTextPickerColumnTestTwoNg()
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

void TextPickerColumnTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerColumnTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerColumnTestTwoNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerColumnTestTwoNg::TearDown()
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
 * @tc.name: TextPickerColumnPatternTest001
 * @tc.desc: test TextPickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
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
    auto textPickerLayoutAlgorithm = AceType::MakeRefPtr<TextPickerLayoutAlgorithm>();
    textPickerLayoutAlgorithm->halfDisplayCounts_ = 2;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textPickerLayoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    /**
     * @tc.step: step2. call columnpattern's OnDirtyLayoutWrapperSwap method.
     */
    auto ret = pickerColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pickerColumnPattern->GetHalfDisplayCounts(), 2);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TextPickerColumnPatternTest002
 * @tc.desc: test TextPickerColumnPattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest002, TestSize.Level1)
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
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    /**
     * @tc.cases: case1. up KeyEvent.
     */
    KeyEvent keyEventOne(KeyCode::KEY_A, KeyAction::UP);
    auto ret = pickerColumnPattern->OnKeyEvent(keyEventOne);
    EXPECT_FALSE(ret);
    /**
     * @tc.cases: case2. cover branch KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN.
     */
    KeyEvent keyEventFour(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventFour);
    EXPECT_TRUE(ret);

    std::vector<RangeContent> options { { "icon", "text" } };
    pickerColumnPattern->SetOptions(options);
    pickerColumnPattern->columnKind_ = TEXT;
    /**
     * @tc.cases: case3. cover branch KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN.
     */
    KeyEvent keyEventFIve(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventFIve);
    EXPECT_TRUE(ret);
    /**
     * @tc.cases: case4. cover branch KeyCode::KEY_DPAD_UP, KeyAction::DOWN.
     */
    KeyEvent keyEventTwo(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventTwo);
    EXPECT_TRUE(ret);
    /**
     * @tc.cases: case5. cover branch KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN.
     */
    KeyEvent keyEventThr(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventThr);
    EXPECT_TRUE(ret);
    /**
     * @tc.cases: case6. cover branch KeyCode::KEY_1, KeyAction::DOWN.
     */
    KeyEvent keyEventSix(KeyCode::KEY_1, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventSix);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TextPickerColumnPatternTest003
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(true);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    GestureEvent gestureEvent;
    Offset point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetLocalLocation(point);
    panEvent->actionStart_(gestureEvent);
    /**
     * cover actionUpdate_ callback
     */
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    /**
     * cover actionEnd_ callback
     */
    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_EQ(columnPattern->yOffset_, 0.0);
    EXPECT_EQ(columnPattern->yLast_, 0.0);
    EXPECT_EQ(columnPattern->scrollDelta_, 0.0);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->pressed_ = true;
    columnPattern->yOffset_ = OFFSET_Y;
    columnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_EQ(columnPattern->yOffset_, 0.0);
    EXPECT_EQ(columnPattern->yLast_, 0.0);
    EXPECT_FALSE(columnPattern->pressed_);
}

/**
 * @tc.name: TextPickerColumnPatternTest005
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest005, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(true);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    /**
     * cover actionStart_ callback
     */
    GestureEvent gestureEvent;
    Offset point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetLocalLocation(point);
    panEvent->actionStart_(gestureEvent);
    EXPECT_EQ(columnPattern->GetToss()->yStart_, OFFSET_Y);
    EXPECT_TRUE(columnPattern->pressed_);
    /**
     * cover actionUpdate_ callback
     */
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->pressed_ = true;
    columnPattern->yOffset_ = OFFSET_Y;
    columnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    /**
     * cover actionCancel_ callback
     */
    columnPattern->animationCreated_ = false;
    panEvent->actionCancel_();
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_EQ(columnPattern->scrollDelta_, 0.0);
}

/**
 * @tc.name: TextPickerColumnPatternTest004
 * @tc.desc: Test GetSelectedObject
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);
    /**
     * @tc.step: step2. call method GetSelectedObject.
     */
    columnPattern->GetSelectedObject(false, 0);
    columnPattern->GetSelectedObject(true, 1);
}

/**
 * @tc.name: TextPickerColumnPatternTest007
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistance when dir == UP.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest007, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::UP;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    EXPECT_EQ(textPickerColumnPattern->GetShiftDistance(COLUMN_INDEX_0, dir), -2.0f);
}

/**
 * @tc.name: TextPickerColumnPatternTest008
 * @tc.desc: Test TextPickerColumnPattern CalcAlgorithmOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest008, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 5;
    textPickerColumnPattern->algorithmOffset_.clear();
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 10.0f;
    prop.nextDistance = 10.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->CalcAlgorithmOffset(ScrollDirection::UP, DISTANCE);
    EXPECT_EQ(textPickerColumnPattern->algorithmOffset_.size() - BUFFER_NODE_NUMBER, 5);
}

/**
 * @tc.name: TextPickerColumnPatternTest009
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistanceForLandscape when dir == DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest009, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::DOWN;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->GetShiftDistanceForLandscape(COLUMN_INDEX_2, dir);
    double distance = textPickerColumnPattern->optionProperties_[COLUMN_INDEX_2].height;
    EXPECT_EQ(textPickerColumnPattern_->GetShiftDistanceForLandscape(COLUMN_INDEX_2, dir), distance);
}

/**
 * @tc.name: TextPickerColumnPatternTest010
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistanceForLandscape when dir == UP.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest010, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::UP;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->GetShiftDistanceForLandscape(COLUMN_INDEX_0, dir);
    double distance = 0.0f - textPickerColumnPattern->optionProperties_[COLUMN_INDEX_0].height;
    EXPECT_EQ(textPickerColumnPattern_->GetShiftDistanceForLandscape(COLUMN_INDEX_0, dir), distance);
}

/**
 * @tc.name: TextPickerColumnPatternTest011
 * @tc.desc: Test TextPickerColumnPattern ScrollOption.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest011, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 4;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->ScrollOption(20.0f);
    EXPECT_EQ(textPickerColumnPattern->algorithmOffset_.size() - BUFFER_NODE_NUMBER, 5);
}

/**
 * @tc.name: TextPickerColumnPatternTest012
 * @tc.desc: Test TextPickerColumnPattern ResetAlgorithmOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest012, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    textPickerColumnPattern->algorithmOffset_.clear();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    uint32_t counts = theme->GetShowOptionCount();
    textPickerColumnPattern->ResetAlgorithmOffset();
    for (uint32_t i = 0; i < counts; i++) {
        EXPECT_EQ(textPickerColumnPattern->algorithmOffset_.emplace_back(i), i);
    }
}

/**
 * @tc.name: TextPickerColumnPatternTest013
 * @tc.desc: Test TextPickerColumnPattern ScrollOption and HandleEnterSelectedArea.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest013, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 4;
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern->SetOptions(range);
    textPickerColumnPattern->SetCurrentIndex(SELECTED_INDEX_2);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->ScrollOption(10.0f);
    EXPECT_EQ(textPickerColumnPattern->GetEnterIndex(), 1);
}

/**
 * @tc.name: TextPickerColumnPatternInitTextFontFamily001
 * @tc.desc: Test InitTextFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternInitTextFontFamily001, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    auto textPickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerLayoutProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == false && ALL FontFamily_ == false.
     */
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == false && ALL FontFamily_ == true.
     */
    textPickerPattern->HasUserDefinedDisappearFontFamily(true);
    textPickerPattern->HasUserDefinedNormalFontFamily(true);
    textPickerPattern->HasUserDefinedSelectedFontFamily(true);
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
}

/**
 * @tc.name: TextPickerColumnPatternInitTextFontFamily002
 * @tc.desc: Test InitTextFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternInitTextFontFamily002, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    pipeline->fontManager_->appCustomFont_ = "appCustomFont";
    auto textPickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerLayoutProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == true && ALL FontFamily_ == true.
     */
    textPickerPattern->HasUserDefinedDisappearFontFamily(true);
    textPickerPattern->HasUserDefinedNormalFontFamily(true);
    textPickerPattern->HasUserDefinedSelectedFontFamily(true);
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == true && ALL FontFamily_ == false.
     */
    textPickerPattern->HasUserDefinedDisappearFontFamily(false);
    textPickerPattern->HasUserDefinedNormalFontFamily(false);
    textPickerPattern->HasUserDefinedSelectedFontFamily(false);
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), CUSTOM_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), CUSTOM_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), CUSTOM_VALUE);
}

/**
 * @tc.name: TextPickerColumnPatternSetCanLoop001
 * @tc.desc: Test SetCanLoop.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternSetCanLoop001, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    /**
     * @tc.cases: case. cover isLoop_ == isLoop.
     */
    textPickerColumnPattern_->SetCanLoop(true);
    EXPECT_TRUE(textPickerColumnPattern_->isLoop_);

    textPickerColumnPattern_->SetCanLoop(false);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);
    /**
     * @tc.cases: case. cover isLoop_ != isLoop.
     */
    textPickerColumnPattern_->isLoop_ = false;
    textPickerColumnPattern_->SetCanLoop(true);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);

    textPickerColumnPattern_->isLoop_ = false;
    textPickerColumnPattern_->SetTossStatus(true);
    textPickerColumnPattern_->SetCanLoop(true);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);

    textPickerColumnPattern_->isLoop_ = true;
    textPickerColumnPattern_->SetTossStatus(true);
    textPickerColumnPattern_->SetCanLoop(false);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);
}

#ifdef ARKUI_WEARABLE
/**
 * @tc.name: TextPickerColumnPatternTest014
 * @tc.desc: Test TextPickerColumnPattern GetDigitalCrownSensitivity and SetDigitalCrownSensitivity.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest014, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    EXPECT_NE(textPickerColumnPattern->GetDigitalCrownSensitivity(), INVALID_CROWNSENSITIVITY);
    EXPECT_EQ(textPickerColumnPattern->GetDigitalCrownSensitivity(), DEFAULT_CROWNSENSITIVITY);
    textPickerColumnPattern->SetDigitalCrownSensitivity(2);
    EXPECT_EQ(textPickerColumnPattern->GetDigitalCrownSensitivity(), 2);
}

/**
 * @tc.name: TextPickerColumnPatternTest015
 * @tc.desc: Test TextPickerColumnPattern UpdateSelectedTextColor.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest015, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    auto textPickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    RefPtr<TextLayoutProperty> textLayoutProperty = columnPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_FALSE(textLayoutProperty);
    textPickerColumnPattern->UpdateSelectedTextColor(theme);
    EXPECT_EQ(textPickerColumnPattern->GetEnterIndex(), 0);
    EXPECT_EQ(textPickerColumnPattern->GetSelected(), 0);
    EXPECT_EQ(textPickerColumnPattern->selectorTextFocusColor_, Color::WHITE);
}
#endif

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: TextPickerColumnPatternTest016
 * @tc.desc: Test TextPickerColumnPattern SetSelectedMarkPaint.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest016, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showCircleDial_ = true;
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    textPickerColumnPattern->SetSelectedMarkPaint(true);
    textPickerColumnPattern->SetSelectedMark(true, false);
    EXPECT_TRUE(textPickerColumnPattern->selectedMarkPaint_);
}

/**
 * @tc.name: TextPickerColumnPatternTest017
 * @tc.desc: Test TextPickerColumnPattern SetSelectedMarkListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest017, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::function<void(int& selectedColumnId)> call =  [this](int& selectedColumnId) {
        selectedColumnId = 1;
    };

    textPickerColumnPattern->SetSelectedMarkId(COLUMN_INDEX[0]);
    textPickerColumnPattern->SetSelectedMarkListener(call);
    textPickerColumnPattern->SetSelectedMark(true, false);
    EXPECT_EQ(textPickerColumnPattern->selectedColumnId_, 0);

    textPickerColumnPattern->SetSelectedMarkId(COLUMN_INDEX[1]);
    textPickerColumnPattern->circleUtils_ = new PickerColumnPatternCircleUtils<TextPickerColumnPattern>();
    textPickerColumnPattern->SetSelectedMarkListener(call);
    EXPECT_EQ(textPickerColumnPattern->selectedColumnId_, 1);
    textPickerColumnPattern->circleUtils_ = nullptr;
}

/**
 * @tc.name: TextPickerColumnPatternTest018
 * @tc.desc: Test TextPickerColumnPattern HandleCrownBeginEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest018, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CROWN_SENSITIVITY_ONE);

    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->OnAttachToFrameNode();
    CrownEvent crownEvent;
    crownEvent.action = OHOS::Ace::CrownAction::BEGIN;
    columnPattern->HandleCrownBeginEvent(crownEvent);
    EXPECT_TRUE(columnPattern->pressed_);
    EXPECT_FALSE(columnPattern->isCrownEventEnded_);
    columnPattern->pressed_ = false;
    crownEvent.action = OHOS::Ace::CrownAction::UPDATE;
    columnPattern->HandleCrownMoveEvent(crownEvent);
    EXPECT_FALSE(columnPattern->animationBreak_);
    EXPECT_FALSE(columnPattern->isCrownEventEnded_);
    crownEvent.action = OHOS::Ace::CrownAction::END;
    columnPattern->HandleCrownEndEvent(crownEvent);
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_TRUE(columnPattern->isCrownEventEnded_);
}

/**
 * @tc.name: TextPickerColumnPatternTest019
 * @tc.desc: Test TextPickerColumnPattern HandleCrownMoveEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest019, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showCircleDial_ = true;
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CROWN_SENSITIVITY_ONE);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->OnAttachToFrameNode();
    auto layout = columnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    layout->UpdateCanLoop(false);
    AnimationOption option;
    columnPattern->animation_ =
        AnimationUtils::StartAnimation(option, []() { std::cout << "start animation now ." << std::endl; });
    columnPattern->reboundAnimation_ = nullptr;

    CrownEvent crownEvent;
    crownEvent.action = OHOS::Ace::CrownAction::BEGIN;
    columnPattern->HandleCrownBeginEvent(crownEvent);
    EXPECT_TRUE(columnPattern->pressed_);
    EXPECT_FALSE(columnPattern->isCrownEventEnded_);
    columnPattern->circleUtils_ = nullptr;
    crownEvent.action = OHOS::Ace::CrownAction::UPDATE;
    columnPattern->HandleCrownMoveEvent(crownEvent);
    EXPECT_FALSE(columnPattern->animationBreak_);
    EXPECT_FALSE(columnPattern->isCrownEventEnded_);
    columnPattern->animationCreated_ = true;
    crownEvent.action = OHOS::Ace::CrownAction::END;
    columnPattern->HandleCrownEndEvent(crownEvent);
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_TRUE(columnPattern->isCrownEventEnded_);
}

/**
 * @tc.name: TextPickerColumnPatternTest020
 * @tc.desc: Test TextPickerColumnPattern GetDigitalCrownSensitivity and SetDigitalCrownSensitivity.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest020, TestSize.Level1)
{
    TextPickerModelNG::GetInstance()->SetDigitalCrownSensitivity(CROWN_SENSITIVITY_ERR);
    TextPickerModelNG::SetDigitalCrownSensitivity(nullptr, CROWN_SENSITIVITY_ERR);
    InitTextPickerColumnTestTwoNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    EXPECT_NE(textPickerColumnPattern->GetDigitalCrownSensitivity(), INVALID_CROWNSENSITIVITY);
    EXPECT_EQ(textPickerColumnPattern->GetDigitalCrownSensitivity(), DEFAULT_CROWNSENSITIVITY);

    textPickerColumnPattern->SetDigitalCrownSensitivity(BUFFER_NODE_NUMBER);
    TextPickerModelNG::SetDigitalCrownSensitivity(nullptr, CROWN_SENSITIVITY_ONE);
    EXPECT_EQ(textPickerColumnPattern->GetDigitalCrownSensitivity(), BUFFER_NODE_NUMBER);
}

/**
 * @tc.name: TextPickerColumnPatternTest021
 * @tc.desc: Test TextPickerColumnPattern GetDigitalCrownSensitivity and SetDigitalCrownSensitivity.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest021, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    TextPickerModelNG::GetInstance()->SetDigitalCrownSensitivity(CROWN_SENSITIVITY_THR);
    TextPickerModelNG::SetDigitalCrownSensitivity(nullptr, CROWN_SENSITIVITY_THR);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CROWN_SENSITIVITY_ONE);

    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->OnAttachToFrameNode();
    EXPECT_EQ(columnPattern->GetDigitalCrownSensitivity(), DEFAULT_CROWNSENSITIVITY);
    TextPickerModelNG::GetInstance()->SetDigitalCrownSensitivity(CROWN_SENSITIVITY_ONE);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CROWN_SENSITIVITY_ONE);
    EXPECT_EQ(columnPattern->crownSensitivity_, CROWN_SENSITIVITY_ONE);
}

/**
 * @tc.name: TextPickerColumnPatternTest022
 * @tc.desc: Test TextPickerColumnPattern GetContentDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest022, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->showCircleDial_ = true;
    TextPickerModelNG::GetInstance()->Create(pickerTheme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetContentDrawFunction(paintWrapper);
    ASSERT_NE(canvasDrawFunction, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TextPickerColumnPatternTest023
 * @tc.desc: Test TextPickerColumnPattern SetSelectColor.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest023, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CROWN_SENSITIVITY_ONE);

    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->OnAttachToFrameNode();
    columnPattern->SetSelectedMarkPaint(true);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty);
    columnPattern->SetSelectColor(textLayoutProperty, Color::RED, Color::BLUE, OFFSET_FIVE, true);
    EXPECT_EQ(columnPattern->GetEnterIndex(), 0);
    EXPECT_EQ(columnPattern->pressColor_, Color::RED);

    auto newColumnPattern = AceType::MakeRefPtr<TextPickerColumnPattern>();
    ASSERT_NE(newColumnPattern, nullptr);
    newColumnPattern->UpdateSelectedTextColor(theme);
    EXPECT_EQ(newColumnPattern->selectorTextFocusColor_, Color::WHITE);
}

/**
 * @tc.name: TextPickerColumnPatternTest024
 * @tc.desc: Test TextPickerColumnPattern SetSelectColor.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestTwoNg, TextPickerColumnPatternTest024, TestSize.Level1)
{
    InitTextPickerColumnTestTwoNg();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CROWN_SENSITIVITY_ONE);

    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->OnAttachToFrameNode();
    columnPattern->SetSelectedMarkPaint(true);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty);

    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    textPickerPattern_->SetDefaultFocus();
    columnPattern->SetSelectedMark(true, true);
    columnPattern->SetSelectColor(textLayoutProperty, Color::RED, Color::BLUE, OFFSET_FIVE, true);
    EXPECT_EQ(columnPattern->GetEnterIndex(), 0);
    EXPECT_EQ(columnPattern->selectorTextFocusColor_, Color::WHITE);
}
#endif
} // namespace OHOS::Ace::NG
