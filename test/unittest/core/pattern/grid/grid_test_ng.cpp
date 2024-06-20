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

#include "grid_test_ng.h"

#include "test/mock/base/mock_drag_window.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#ifndef TEST_IRREGULAR_GRID
#include "test/mock/base/mock_system_properties.h"
#endif
namespace OHOS::Ace::NG {
void GridTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).WillRepeatedly(Return());

    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    auto gridItemTheme = AceType::MakeRefPtr<GridItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(GridItemTheme::TypeId())).WillRepeatedly(Return(gridItemTheme));

    RefPtr<DragWindow> dragWindow = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragWindow)), DrawFrameNode(_)).Times(AnyNumber());
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragWindow)), MoveTo(_, _)).Times(AnyNumber());
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragWindow)), Destroy()).Times(AnyNumber());

#ifndef TEST_IRREGULAR_GRID
    g_irregularGrid = false;
#endif
}

void GridTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GridTestNg::SetUp() {}

void GridTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes();  // Each testcase will create new list at begin
}

void GridTestNg::GetGrid()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GridPattern>();
    eventHub_ = frameNode_->GetEventHub<GridEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GridLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GridAccessibilityProperty>();
}

GridModelNG GridTestNg::CreateGrid()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(CalcLength(GRID_HEIGHT));
    GetGrid();
    return model;
}

GridItemModelNG GridTestNg::CreateGridItem(float width, float height, GridItemStyle gridItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridItemModelNG itemModel;
    itemModel.Create(gridItemStyle);
    if (width == FILL_VALUE) {
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    } else if (width != NULL_VALUE) {
        ViewAbstract::SetWidth(CalcLength(width));
    }
    if (height == FILL_VALUE) {
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    } else if (height != NULL_VALUE) {
        ViewAbstract::SetHeight(CalcLength(height));
    }
    return itemModel;
}

void GridTestNg::CreateGridItems(int32_t itemNumber, float width, float height, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < itemNumber; i++) {
        CreateGridItem(width, height, gridItemStyle);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void GridTestNg::CreateFocusableGridItems(int32_t itemNumber, float width, float height, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < itemNumber; i++) {
        CreateGridItem(width, height, gridItemStyle);
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void GridTestNg::CreateFixedItems(int32_t itemNumber, GridItemStyle gridItemStyle)
{
    CreateGridItems(itemNumber, ITEM_WIDTH, ITEM_HEIGHT, gridItemStyle);
}

void GridTestNg::CreateFixedHeightItems(int32_t itemNumber, float height, GridItemStyle gridItemStyle)
{
    CreateGridItems(itemNumber, FILL_VALUE, height, gridItemStyle);
}

void GridTestNg::CreateFixedWidthItems(int32_t itemNumber, float width, GridItemStyle gridItemStyle)
{
    CreateGridItems(itemNumber, width, FILL_VALUE, gridItemStyle);
}

void GridTestNg::CreateBigItem(
    int32_t rowStart, int32_t rowEnd, int32_t colStart, int32_t colEnd, float width, float height)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridItemModelNG itemModel;
    itemModel.Create(GridItemStyle::NONE);
    if (rowStart != NULL_VALUE) {
        itemModel.SetRowStart(rowStart);
    }
    if (rowEnd != NULL_VALUE) {
        itemModel.SetRowEnd(rowEnd);
    }
    if (colStart != NULL_VALUE) {
        itemModel.SetColumnStart(colStart);
    }
    if (colEnd != NULL_VALUE) {
        itemModel.SetColumnEnd(colEnd);
    }
    if (width != NULL_VALUE) {
        ViewAbstract::SetWidth(CalcLength(width));
    }
    if (height != NULL_VALUE) {
        ViewAbstract::SetHeight(CalcLength(height));
    }
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

void GridTestNg::CreateBigColItem(int32_t colStart, int32_t colEnd)
{
    CreateBigItem(NULL_VALUE, NULL_VALUE, colStart, colEnd, NULL_VALUE, ITEM_HEIGHT);
}

void GridTestNg::CreateBigRowItem(int32_t rowStart, int32_t rowEnd)
{
    CreateBigItem(rowStart, rowEnd, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
}

void GridTestNg::AddFixedHeightItems(int32_t cnt, float height)
{
    for (int i = 0; i < cnt; ++i) {
        auto child = FrameNode::GetOrCreateFrameNode(
            V2::GRID_ITEM_ETS_TAG, -1, []() { return AceType::MakeRefPtr<GridItemPattern>(nullptr); });
        child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(height))));
        frameNode_->AddChild(child);
    }
}

void GridTestNg::ScrollTo(float position)
{
    pattern_->ScrollTo(position);
    FlushLayoutTask(frameNode_);
}

void GridTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG
