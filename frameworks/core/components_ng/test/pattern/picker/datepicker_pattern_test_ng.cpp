/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t START_YEAR_BEFORE = 1899;
constexpr int32_t START_YEAR = 1900;
constexpr int32_t END_YEAR = 2100;
constexpr int32_t END_YEAR_BEHIND = 2101;
constexpr int32_t END_MONTH = 12;
constexpr int32_t END_MONTH_BEHIND = 13;
constexpr int32_t END_DAY = 31;
constexpr int32_t END_DAY_BEHIND = 32;
constexpr int32_t CURRENT_YEAR = 2022;
constexpr int32_t CURRENT_MONTH = 12;
constexpr int32_t CURRENT_DAY = 6;
} // namespace

class PickerPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    };

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void PickerPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
}

void PickerPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void PickerPatternTestNg::SetUp() {}
void PickerPatternTestNg::TearDown() {}

/**
 * @tc.name: DatePickerPatternOnAttachToFrameNode001
 * @tc.desc: Test DatePickerPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnAttachToFrameNode001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    datePickerPattern->OnAttachToFrameNode();
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: DatePickerPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: Test DatePickerPattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    DirtySwapConfig config;
    auto ret = datePickerPattern->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_EQ(ret, false);
    config.frameSizeChange = true;
    ret = datePickerPattern->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_EQ(ret, false);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ret = datePickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: DatePickerPatternOnModifyDone001
 * @tc.desc: Test DatePickerPattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnModifyDone001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->OnModifyDone();

    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        EXPECT_NE(childNode, nullptr);
        auto datePickerColumnPattern = childNode->GetPattern<DatePickerColumnPattern>();
        EXPECT_NE(datePickerColumnPattern, nullptr);
        auto changeCallback = datePickerColumnPattern->GetChangeCallback();
        EXPECT_NE(changeCallback, nullptr);
        changeCallback(frameNode, false, 1, false);

        auto eventCallback = datePickerColumnPattern->GetEventCallback();
        EXPECT_NE(eventCallback, nullptr);
        eventCallback(false);
    }
}

/**
 * @tc.name: DatePickerPatternOnModifyDone002
 * @tc.desc: Test DatePickerPattern OnModifyDone when there is a title node.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnModifyDone002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->titleId_ = std::make_optional(0);
    datePickerPattern->OnModifyDone();

    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        EXPECT_NE(childNode, nullptr);
        auto datePickerColumnPattern = childNode->GetPattern<DatePickerColumnPattern>();
        EXPECT_NE(datePickerColumnPattern, nullptr);
        auto changeCallback = datePickerColumnPattern->GetChangeCallback();
        EXPECT_NE(changeCallback, nullptr);
        changeCallback(frameNode, false, 1, false);

        auto eventCallback = datePickerColumnPattern->GetEventCallback();
        EXPECT_NE(eventCallback, nullptr);
        eventCallback(false);
    }
}

/**
 * @tc.name: DatePickerPatternHandleColumnChange001
 * @tc.desc: Test DatePickerPattern HandleColumnChange when frameNode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleColumnChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleColumnChange(frameNode, false, 1, false);
}

/**
 * @tc.name: DatePickerPatternHandleColumnChange002
 * @tc.desc: Test DatePickerPattern HandleColumnChange when frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleColumnChange002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(nullptr);
    auto host = datePickerPattern->GetHost();
    EXPECT_EQ(host, nullptr);
    datePickerPattern->HandleColumnChange(frameNode, false, 1, false);
}

/**
 * @tc.name: DatePickerPatternOnKeyEvent001
 * @tc.desc: Test DatePickerPattern OnKeyEvent when KeyEvent is KeyAction::DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnKeyEvent001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyEvent event;
    event.action = KeyAction::UP;
    datePickerPattern->OnKeyEvent(event);
}

/**
 * @tc.name: DatePickerPatternOnKeyEvent002
 * @tc.desc: Test DatePickerPattern OnKeyEvent when KeyEvent is KeyAction::UP.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnKeyEvent002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_UP;
    datePickerPattern->OnKeyEvent(event);
}

/**
 * @tc.name: DatePickerPatternOnKeyEvent003
 * @tc.desc: Test DatePickerPattern OnKeyEvent when KeyCode is KeyCode::KEY_DPAD_DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnKeyEvent003, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_DOWN;
    datePickerPattern->OnKeyEvent(event);
}

/**
 * @tc.name: DatePickerPatternOnKeyEvent004
 * @tc.desc: Test DatePickerPattern OnKeyEvent when KeyCode is KeyCode::KEY_BACK.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnKeyEvent004, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_BACK;
    datePickerPattern->OnKeyEvent(event);
}

/**
 * @tc.name: DatePickerPatternHandleDirectionKey001
 * @tc.desc: Test DatePickerPattern HandleDirectionKey when KeyCode is KeyCode::KEY_DPAD_UP.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleDirectionKey001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyCode code = KeyCode::KEY_DPAD_UP;
    datePickerPattern->HandleDirectionKey(code);
}

/**
 * @tc.name: DatePickerPatternHandleDirectionKey002
 * @tc.desc: Test DatePickerPattern HandleDirectionKey when KeyCode is KeyCode::KEY_DPAD_DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleDirectionKey002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyCode code = KeyCode::KEY_DPAD_DOWN;
    datePickerPattern->HandleDirectionKey(code);
}

/**
 * @tc.name: DatePickerPatternHandleDirectionKey003
 * @tc.desc: Test DatePickerPattern HandleDirectionKey when KeyCode is KeyCode::KEY_DPAD_DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleDirectionKey003, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    KeyCode code = KeyCode::KEY_BACK;
    datePickerPattern->HandleDirectionKey(code);
}

/**
 * @tc.name: DatePickerPatternGetAllChildNode001
 * @tc.desc: Test DatePickerPattern GetAllChildNod when child is three nodes.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetAllChildNode001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    auto child = datePickerPattern->GetAllChildNode();
    EXPECT_EQ(child.size(), 3UL);
}

/**
 * @tc.name: DatePickerPatternGetAllChildNode002
 * @tc.desc: Test DatePickerPattern GetAllChildNod when child is not three nodes.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetAllChildNode002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 6UL);
    auto child = datePickerPattern->GetAllChildNode();
    EXPECT_EQ(child.size(), 0UL);
}

/**
 * @tc.name: DatePickerPatternGetAllChildNode003
 * @tc.desc: Test DatePickerPattern GetAllChildNod when child node of year is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetAllChildNode003, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = TestNode::CreateTestNode(1);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    auto child = datePickerPattern->GetAllChildNode();
    EXPECT_EQ(child.size(), 0UL);
}

/**
 * @tc.name: DatePickerPatternGetAllChildNode004
 * @tc.desc: Test DatePickerPattern GetAllChildNod when child node of month is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetAllChildNode004, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = TestNode::CreateTestNode(2);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    auto child = datePickerPattern->GetAllChildNode();
    EXPECT_EQ(child.size(), 0UL);
}

/**
 * @tc.name: DatePickerPatternGetAllChildNode005
 * @tc.desc: Test DatePickerPattern GetAllChildNod when child node of day is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetAllChildNode005, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = TestNode::CreateTestNode(3);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    auto child = datePickerPattern->GetAllChildNode();
    EXPECT_EQ(child.size(), 0UL);
}

/**
 * @tc.name: DatePickerPatternFlushColumn001
 * @tc.desc: Test DatePickerPattern FlushColumn when child is three nodes.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternFlushColumn001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    datePickerPattern->FlushColumn();
}

/**
 * @tc.name: DatePickerPatternFlushColumn002
 * @tc.desc: Test DatePickerPattern FlushColumn when child node of year is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternFlushColumn002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = TestNode::CreateTestNode(1);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    datePickerPattern->FlushColumn();
}

/**
 * @tc.name: DatePickerPatternFlushColumn003
 * @tc.desc: Test DatePickerPattern FlushColumn when child node of month is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternFlushColumn003, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = TestNode::CreateTestNode(2);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    datePickerPattern->FlushColumn();
}

/**
 * @tc.name: DatePickerPatternFlushColumn004
 * @tc.desc: Test DatePickerPattern FlushColumn when child node of day is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternFlushColumn004, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = TestNode::CreateTestNode(3);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    datePickerPattern->FlushColumn();
}

/**
 * @tc.name: DatePickerPatternFlushColumn005
 * @tc.desc: Test DatePickerPattern FlushColumn when Lunar is true.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternFlushColumn005, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    auto property = host->GetLayoutProperty<DataPickerRowLayoutProperty>();
    EXPECT_NE(property, nullptr);
    property->UpdateLunar(true);
    datePickerPattern->FlushColumn();
}

/**
 * @tc.name: DatePickerPatternOnDataLinking001
 * @tc.desc: Test DatePickerPattern OnDataLinking.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternOnDataLinking001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildren().size(), 3UL);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->OnDataLinking(yearFrameNodeChild, false, 1, resultTags);
    datePickerPattern->OnDataLinking(monthFrameNodeChild, false, 2, resultTags);
    datePickerPattern->OnDataLinking(dayFrameNodeChild, false, 3, resultTags);
}

/**
 * @tc.name: DatePickerPatternFireChangeEvent001
 * @tc.desc: Test DatePickerPattern FireChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternFireChangeEvent001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->FireChangeEvent(false);
    datePickerPattern->FireChangeEvent(true);
}

/**
 * @tc.name: DatePickerPatternHandleDayChange001
 * @tc.desc: Test DatePickerPattern HandleDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleDayChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->SetShowLunar(true);
    datePickerPattern->HandleDayChange(false, 1, resultTags);
}

/**
 * @tc.name: DatePickerPatternHandleDayChange002
 * @tc.desc: Test DatePickerPattern HandleDayChange when SetShowLunar is false.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleDayChange002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->SetShowLunar(false);
    datePickerPattern->HandleDayChange(false, 1, resultTags);
}

/**
 * @tc.name: DatePickerPatternHandleSolarDayChange001
 * @tc.desc: Test DatePickerPattern HandleSolarDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleSolarDayChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleSolarDayChange(false, 0);
    datePickerPattern->HandleSolarDayChange(true, 0);
    datePickerPattern->HandleSolarDayChange(false, 1);
    datePickerPattern->HandleSolarDayChange(true, 1);
}

/**
 * @tc.name: DatePickerPatternHandleSolarDayChange002
 * @tc.desc: Test DatePickerPattern HandleSolarDayChange when DatePickerColumnPattern is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleSolarDayChange002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 2, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleSolarDayChange(false, 0);
    datePickerPattern->HandleSolarDayChange(true, 0);
    datePickerPattern->HandleSolarDayChange(false, 1);
    datePickerPattern->HandleSolarDayChange(true, 1);
}

/**
 * @tc.name: DatePickerPatternHandleLunarDayChange001
 * @tc.desc: Test DatePickerPattern HandleLunarDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleLunarDayChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleLunarDayChange(false, 0);
    datePickerPattern->HandleLunarDayChange(true, 0);
    datePickerPattern->HandleLunarDayChange(false, 1);
    datePickerPattern->HandleLunarDayChange(true, 1);
}

/**
 * @tc.name: DatePickerPatternHandleReduceLunarDayChange001
 * @tc.desc: Test DatePickerPattern HandleReduceLunarDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleReduceLunarDayChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleReduceLunarDayChange(0);
    datePickerPattern->HandleReduceLunarDayChange(1);
}

/**
 * @tc.name: DatePickerPatternHandleReduceLunarDayChange002
 * @tc.desc: Test DatePickerPattern HandleReduceLunarDayChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleReduceLunarDayChange002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleReduceLunarDayChange(0);
    datePickerPattern->HandleReduceLunarDayChange(1);
}

/**
 * @tc.name: DatePickerPatternHandleYearChange001
 * @tc.desc: Test DatePickerPattern HandleYearChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleYearChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->SetShowLunar(true);
    datePickerPattern->HandleYearChange(false, 0, resultTags);
    datePickerPattern->HandleYearChange(false, 1, resultTags);
    datePickerPattern->HandleYearChange(true, 0, resultTags);
    datePickerPattern->HandleYearChange(true, 1, resultTags);
}

/**
 * @tc.name: DatePickerPatternHandleYearChange002
 * @tc.desc: Test DatePickerPattern HandleYearChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleYearChange002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->SetShowLunar(false);
    datePickerPattern->HandleYearChange(false, 0, resultTags);
    datePickerPattern->HandleYearChange(false, 1, resultTags);
    datePickerPattern->HandleYearChange(true, 0, resultTags);
    datePickerPattern->HandleYearChange(true, 1, resultTags);
}

/**
 * @tc.name: DatePickerPatternHandleMonthChange001
 * @tc.desc: Test DatePickerPattern HandleMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleMonthChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->SetShowLunar(true);
    datePickerPattern->HandleMonthChange(false, 0, resultTags);
    datePickerPattern->HandleMonthChange(false, 1, resultTags);
    datePickerPattern->HandleMonthChange(true, 0, resultTags);
    datePickerPattern->HandleMonthChange(true, 1, resultTags);
}

/**
 * @tc.name: DatePickerPatternHandleMonthChange002
 * @tc.desc: Test DatePickerPattern HandleMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleMonthChange002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    std::vector<RefPtr<FrameNode>> resultTags;
    datePickerPattern->SetShowLunar(false);
    datePickerPattern->HandleMonthChange(false, 0, resultTags);
    datePickerPattern->HandleMonthChange(false, 1, resultTags);
    datePickerPattern->HandleMonthChange(true, 0, resultTags);
    datePickerPattern->HandleMonthChange(true, 1, resultTags);
}

/**
 * @tc.name: DatePickerPatternHandleSolarMonthChange001
 * @tc.desc: Test DatePickerPattern HandleSolarMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleSolarMonthChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleSolarMonthChange(false, 0);
    datePickerPattern->HandleSolarMonthChange(false, 1);
}

/**
 * @tc.name: DatePickerPatternHandleLunarMonthChange001
 * @tc.desc: Test DatePickerPattern HandleLunarMonthChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleLunarMonthChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleLunarMonthChange(false, 0);
    datePickerPattern->HandleLunarMonthChange(false, 1);
}

/**
 * @tc.name: DatePickerPatternHandleLunarYearChange001
 * @tc.desc: Test DatePickerPattern HandleLunarYearChange.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternHandleLunarYearChange001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    datePickerPattern->HandleLunarYearChange(false, 0);
    datePickerPattern->HandleLunarYearChange(false, 1);
}

/**
 * @tc.name: DatePickerPatternGetCurrentLunarDate001
 * @tc.desc: Test DatePickerPattern GetCurrentLunarDate when year is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetCurrentLunarDate001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = TestNode::CreateTestNode(1);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    LunarDate lunarResult;
    auto ret = datePickerPattern->GetCurrentLunarDate(CURRENT_YEAR);
    EXPECT_NE(ret, lunarResult);
}

/**
 * @tc.name: DatePickerPatternGetCurrentLunarDate002
 * @tc.desc: Test DatePickerPattern GetCurrentLunarDate when month is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetCurrentLunarDate002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = TestNode::CreateTestNode(2);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    LunarDate lunarResult;
    auto ret = datePickerPattern->GetCurrentLunarDate(CURRENT_YEAR);
    EXPECT_NE(ret, lunarResult);
}

/**
 * @tc.name: DatePickerPatternGetCurrentLunarDate003
 * @tc.desc: Test DatePickerPattern GetCurrentLunarDate when day is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetCurrentLunarDate003, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = TestNode::CreateTestNode(3);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    LunarDate lunarResult;
    auto ret = datePickerPattern->GetCurrentLunarDate(CURRENT_YEAR);
    EXPECT_NE(ret, lunarResult);
}

/**
 * @tc.name: DatePickerPatternGetCurrentDate001
 * @tc.desc: Test DatePickerPattern GetCurrentDate when year is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetCurrentDate001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = TestNode::CreateTestNode(1);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    datePickerPattern->SetShowLunar(true);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    PickerDate currentDate;
    auto ret = datePickerPattern->GetCurrentDate();
    EXPECT_EQ(ret.GetYear(), currentDate.GetYear());
    EXPECT_EQ(ret.GetMonth(), currentDate.GetMonth());
    EXPECT_EQ(ret.GetDay(), currentDate.GetDay());
}

/**
 * @tc.name: DatePickerPatternGetCurrentDate002
 * @tc.desc: Test DatePickerPattern GetCurrentDate when month is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetCurrentDate002, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = TestNode::CreateTestNode(2);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 3, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->SetShowLunar(false);
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    PickerDate currentDate;
    auto ret = datePickerPattern->GetCurrentDate();
    EXPECT_EQ(ret.GetYear(), currentDate.GetYear());
    EXPECT_EQ(ret.GetMonth(), currentDate.GetMonth());
    EXPECT_EQ(ret.GetDay(), currentDate.GetDay());
}

/**
 * @tc.name: DatePickerPatternGetCurrentDate003
 * @tc.desc: Test DatePickerPattern GetCurrentDate when day is not FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetCurrentDate003, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 1, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 2, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = TestNode::CreateTestNode(3);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->SetShowLunar(false);
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    PickerDate currentDate;
    auto ret = datePickerPattern->GetCurrentDate();
    EXPECT_EQ(ret.GetYear(), currentDate.GetYear());
    EXPECT_EQ(ret.GetMonth(), currentDate.GetMonth());
    EXPECT_EQ(ret.GetDay(), currentDate.GetDay());
}

/**
 * @tc.name: DatePickerPatternLunarDateCompare001
 * @tc.desc: Test DatePickerPattern LunarDateCompare when left.year > right.year.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternLunarDateCompare001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);

    LunarDate left;
    left.year = CURRENT_YEAR;
    left.month = CURRENT_MONTH;
    left.day = CURRENT_DAY;
    LunarDate right;
    right.year = CURRENT_YEAR - 1;
    right.month = CURRENT_MONTH;
    right.day = CURRENT_DAY;
    auto ret = datePickerPattern->LunarDateCompare(left, right);
    EXPECT_EQ(ret, 1);

    right.year = CURRENT_YEAR + 1;
    ret = datePickerPattern->LunarDateCompare(left, right);
    EXPECT_EQ(ret, -1);

    left.year = CURRENT_YEAR;
    left.month = CURRENT_MONTH - 1;
    right.year = CURRENT_YEAR;
    right.month = CURRENT_MONTH;
    ret = datePickerPattern->LunarDateCompare(left, right);
    EXPECT_EQ(ret, -1);

    left.year = CURRENT_YEAR;
    left.month = CURRENT_MONTH;
    left.day = CURRENT_DAY + 1;
    right.year = CURRENT_YEAR;
    right.month = CURRENT_MONTH;
    right.day = CURRENT_DAY;
    ret = datePickerPattern->LunarDateCompare(left, right);
    EXPECT_EQ(ret, 1);

    left.year = CURRENT_YEAR;
    left.month = CURRENT_MONTH;
    left.day = CURRENT_DAY;
    right.year = CURRENT_YEAR;
    right.month = CURRENT_MONTH;
    right.day = CURRENT_DAY + 1;
    ret = datePickerPattern->LunarDateCompare(left, right);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: DatePickerPatternLunarColumnsBuilding001
 * @tc.desc: Test DatePickerPattern LunarColumnsBuilding.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternLunarColumnsBuilding001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 0, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 1, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 2, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    datePickerPattern->SetColumn(yearFrameNodeChild);
    datePickerPattern->SetColumn(monthFrameNodeChild);
    datePickerPattern->SetColumn(dayFrameNodeChild);
    LunarDate current;
    datePickerPattern->LunarColumnsBuilding(current);
}

/**
 * @tc.name: DatePickerPatternSolarColumnsBuilding001
 * @tc.desc: Test DatePickerPattern SolarColumnsBuilding.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternSolarColumnsBuilding001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->Clean();

    auto patternChild = AceType::MakeRefPtr<DatePickerColumnPattern>();
    auto yearFrameNodeChild = FrameNode::CreateFrameNode("year", 0, patternChild);
    EXPECT_NE(yearFrameNodeChild, nullptr);
    frameNode->AddChild(yearFrameNodeChild);

    auto monthFrameNodeChild = FrameNode::CreateFrameNode("month", 1, patternChild);
    EXPECT_NE(monthFrameNodeChild, nullptr);
    frameNode->AddChild(monthFrameNodeChild);

    auto dayFrameNodeChild = FrameNode::CreateFrameNode("day", 2, patternChild);
    EXPECT_NE(dayFrameNodeChild, nullptr);
    frameNode->AddChild(dayFrameNodeChild);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    datePickerPattern->SetColumn(yearFrameNodeChild);
    datePickerPattern->SetColumn(monthFrameNodeChild);
    datePickerPattern->SetColumn(dayFrameNodeChild);
    PickerDate current;
    datePickerPattern->SolarColumnsBuilding(current);
}

/**
 * @tc.name: DatePickerPatternGetYear001
 * @tc.desc: Test DatePickerPattern GetYear.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetYear001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = datePickerPattern->GetYear(START_YEAR_BEFORE);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetYear(START_YEAR);
    EXPECT_EQ(ret, "08:00:00");
    ret = datePickerPattern->GetYear(END_YEAR);
    EXPECT_EQ(ret, "08:00:00");
    ret = datePickerPattern->GetYear(END_YEAR_BEHIND);
    EXPECT_EQ(ret, "");
}

/**
 * @tc.name: DatePickerPatternGetSolarMonth001
 * @tc.desc: Test DatePickerPattern GetSolarMonth.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetSolarMonth001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = datePickerPattern->GetSolarMonth(0);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetSolarMonth(1);
    EXPECT_EQ(ret, "08:00:00");
    ret = datePickerPattern->GetSolarMonth(END_MONTH);
    EXPECT_EQ(ret, "08:00:00");
    ret = datePickerPattern->GetSolarMonth(END_MONTH_BEHIND);
    EXPECT_EQ(ret, "");
}

/**
 * @tc.name: DatePickerPatternGetSolarDay001
 * @tc.desc: Test DatePickerPattern GetSolarDay.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetSolarDay001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = datePickerPattern->GetSolarDay(0);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetSolarDay(1);
    EXPECT_EQ(ret, "08:00:00");
    ret = datePickerPattern->GetSolarDay(END_DAY);
    EXPECT_EQ(ret, "08:00:00");
    ret = datePickerPattern->GetSolarDay(END_DAY_BEHIND);
    EXPECT_EQ(ret, "");
}

/**
 * @tc.name: DatePickerPatternGetLunarMonth001
 * @tc.desc: Test DatePickerPattern GetLunarMonth.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetLunarMonth001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = datePickerPattern->GetLunarMonth(0, false);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarMonth(1, false);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarMonth(END_MONTH, false);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarMonth(END_MONTH_BEHIND, false);
    EXPECT_EQ(ret, "");

    ret = datePickerPattern->GetLunarMonth(0, true);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarMonth(1, true);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarMonth(END_MONTH, true);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarMonth(END_MONTH_BEHIND, true);
    EXPECT_EQ(ret, "");
}

/**
 * @tc.name: DatePickerPatternGetLunarDay001
 * @tc.desc: Test DatePickerPattern GetLunarDay.
 * @tc.type: FUNC
 */
HWTEST_F(PickerPatternTestNg, DatePickerPatternGetLunarDay001, TestSize.Level1)
{
    DatePickerView::CreateDatePicker();
    PickerDate startDate(START_YEAR, 1, 1);
    DatePickerView::SetStartDate(startDate);
    PickerDate endDate(END_YEAR, END_MONTH, END_DAY);
    DatePickerView::SetEndDate(endDate);
    PickerDate selectedDate(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    DatePickerView::SetSelectedDate(selectedDate);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto datePickerPattern = AceType::MakeRefPtr<DatePickerPattern>();
    datePickerPattern->AttachToFrameNode(frameNode);
    auto host = datePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = datePickerPattern->GetLunarDay(0);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarDay(1);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarDay(END_DAY - 1);
    EXPECT_EQ(ret, "");
    ret = datePickerPattern->GetLunarDay(END_DAY);
    EXPECT_EQ(ret, "");
}
} // namespace OHOS::Ace::NG