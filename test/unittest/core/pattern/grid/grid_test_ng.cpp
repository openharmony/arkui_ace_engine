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

namespace OHOS::Ace::NG {
void GridTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    auto gridItemTheme = AceType::MakeRefPtr<GridItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(GridItemTheme::TypeId())).WillRepeatedly(Return(gridItemTheme));
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
}

void GridTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GridPattern>();
    eventHub_ = frameNode_->GetEventHub<GridEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GridLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GridAccessibilityProperty>();
}

void GridTestNg::Create(const std::function<void(GridModelNG)>& callback)
{
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(CalcLength(GRID_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void GridTestNg::CreateItem(
    int32_t count, float width, float height, bool focusable, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < count; i++) {
        GridItemModelNG itemModel;
        itemModel.Create(gridItemStyle);
        if (width != NULL_VALUE) {
            ViewAbstract::SetWidth(CalcLength(Dimension(width)));
        }
        if (height != NULL_VALUE) {
            ViewAbstract::SetHeight(CalcLength(Dimension(height)));
        }
        if (focusable) {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void GridTestNg::CreateColItem(
    int32_t count, bool focusable, GridItemStyle gridItemStyle)
{
    CreateItem(count, NULL_VALUE, ITEM_HEIGHT, focusable, gridItemStyle);
}

void GridTestNg::CreateRowItem(
    int32_t count, bool focusable, GridItemStyle gridItemStyle)
{
    CreateItem(count, ITEM_WIDTH, NULL_VALUE, focusable, gridItemStyle);
}

void GridTestNg::CreateBigItem(
    int32_t rowStart, int32_t rowEnd, int32_t colStart, int32_t colEnd, float width, float height)
{
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
            ViewAbstract::SetWidth(CalcLength(Dimension(width)));
        }
        if (height != NULL_VALUE) {
            ViewAbstract::SetHeight(CalcLength(Dimension(height)));
        }
        ViewStackProcessor::GetInstance()->Pop();
}

void GridTestNg::CreateBigColItem(int32_t colStart, int32_t colEnd)
{
    CreateBigItem(NULL_VALUE, NULL_VALUE, colStart, colEnd, NULL_VALUE, ITEM_HEIGHT);
}

void GridTestNg::CreateBigRowItem(int32_t rowStart, int32_t rowEnd)
{
    CreateBigItem(rowStart, rowEnd, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
}

void GridTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}

AssertionResult GridTestNg::IsEqualCurrentOffset(float expectOffset)
{
    float currentOffset = pattern_->GetGridLayoutInfo().currentOffset_;
    return IsEqual(currentOffset, expectOffset);
}
} // namespace OHOS::Ace::NG
