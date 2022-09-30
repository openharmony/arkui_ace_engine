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

#include "gtest/gtest.h"

#include "core/components/test/unittest/mock/mock_render_common.h"

#define private public
#define protected public
#include "core/components/test/unittest/water_flow/water_flow_test_utils.h"
#include "core/components_v2/water_flow/render_water_flow.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using RenderWaterFlow = OHOS::Ace::V2::RenderWaterFlow;
using RenderWaterFlowItem = OHOS::Ace::V2::RenderWaterFlowItem;
using WaterFlowComponent = OHOS::Ace::V2::WaterFlowComponent;
using WaterFlowItemComponent = OHOS::Ace::V2::WaterFlowItemComponent;
using WaterFlowPositionController = OHOS::Ace::V2::WaterFlowPositionController;

namespace OHOS::Ace {
constexpr int32_t WATER_FLOW_COLUMNS_NUMBERS = 5;
constexpr Dimension height = 160.0_px;
constexpr double view_width = 1000.0;
constexpr double view_height = 1000.0;
constexpr double rowGap = 50.0;
constexpr double colGap = 50.0;
constexpr int32_t rowCount = 5;
constexpr int32_t colCount = 5;

class RenderWaterFlowTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    void CreateWaterFlow(int32_t itemMainSpan, int32_t itemCrossSpan);
    void CreateWaterFlowDefaultHeight();
    void FillItems(
        int32_t index, int32_t MainSpan, int32_t CrossSpan, int32_t callbackMainSpan, int32_t callbackCrossSpan);
    void SetCallback(int32_t itemMainSpan, int32_t itemCrossSpan);

    RefPtr<PipelineContext> mockContext_;
    RefPtr<RenderWaterFlow> renderNode_;
    const int32_t render_component_count = 5;
};

void RenderWaterFlowTest::SetUpTestCase() {}
void RenderWaterFlowTest::TearDownTestCase() {}

void RenderWaterFlowTest::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    renderNode_ = AceType::MakeRefPtr<RenderWaterFlow>();
    renderNode_->Attach(mockContext_);
}

void RenderWaterFlowTest::TearDown()
{
    mockContext_ = nullptr;
    renderNode_ = nullptr;
}

void RenderWaterFlowTest::CreateWaterFlow(int32_t itemMainSpan, int32_t itemCrossSpan)
{
    auto Component = WaterFlowTestUtils::CreateComponent(FlexDirection::COLUMN, WATER_FLOW_COLUMNS_NUMBERS);
    auto waterflowComponent = AceType::DynamicCast<WaterFlowComponent>(Component);
    if (!waterflowComponent) {
        GTEST_LOG_(INFO) << "create WaterFlow component failed!";
        return;
    }
    RefPtr<WaterFlowPositionController> controller = AceType::MakeRefPtr<WaterFlowPositionController>();
    RefPtr<ScrollBarProxy> scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    waterflowComponent->SetController(controller);
    waterflowComponent->SetScrollBarProxy(scrollBarProxy);
    waterflowComponent->SetMainLength(height);
    if (renderNode_ == nullptr) {
        GTEST_LOG_(INFO) << "renderNode_ == nullptr!";
        return;
    }
    renderNode_->mainSize_ = view_height;
    renderNode_->crossSize_ = view_width;
    renderNode_->mainCount_ = rowCount;
    renderNode_->crossCount_ = colCount;
    renderNode_->mainGap_ = rowGap;
    renderNode_->crossGap_ = colGap;
    renderNode_->useScrollable_ = V2::RenderWaterFlow::SCROLLABLE::VERTICAL;
    DisplayMode displayMode = DisplayMode::AUTO;
    renderNode_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(displayMode);
    renderNode_->totalCountFlag_ = true;
    renderNode_->GetChildViewPort().SetWidth(view_width);
    renderNode_->GetChildViewPort().SetHeight(view_height);
    SetCallback(itemMainSpan, itemCrossSpan);
    renderNode_->Update(waterflowComponent);
}

void RenderWaterFlowTest::CreateWaterFlowDefaultHeight()
{
    auto Component = WaterFlowTestUtils::CreateComponent(FlexDirection::ROW, WATER_FLOW_COLUMNS_NUMBERS);
    auto waterflowComponent = AceType::DynamicCast<WaterFlowComponent>(Component);
    if (!waterflowComponent) {
        GTEST_LOG_(INFO) << "create WaterFlow component failed!";
        return;
    }
    RefPtr<WaterFlowPositionController> controller = AceType::MakeRefPtr<WaterFlowPositionController>();
    RefPtr<ScrollBarProxy> scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    waterflowComponent->SetController(controller);
    waterflowComponent->SetScrollBarProxy(scrollBarProxy);
    renderNode_->Update(waterflowComponent);
}

void RenderWaterFlowTest::FillItems(
    int32_t index, int32_t itemMainSpan, int32_t itemCrossSpan, int32_t callbackMainSpan, int32_t callbackCrossSpan)
{
    CreateWaterFlow(callbackMainSpan, callbackCrossSpan);
    auto item = WaterFlowTestUtils::CreateRenderItem(itemMainSpan, itemCrossSpan, index, mockContext_);
    auto flowitem = AceType::DynamicCast<RenderWaterFlowItem>(item);
    if (flowitem == nullptr) {
        GTEST_LOG_(INFO) << "flowitem == nullptr!";
        return;
    }
    renderNode_->AddChildByIndex(index, flowitem);
}

void RenderWaterFlowTest::SetCallback(int32_t callMainSpan, int32_t callCrossSpan)
{
    renderNode_->SetBuildChildByIndex([this, callMainSpan, callCrossSpan](int32_t index) {
        GTEST_LOG_(INFO) << "SetBuildChildByIndex called!";
        auto item = WaterFlowTestUtils::CreateRenderItem(callMainSpan, callCrossSpan, index, mockContext_);
        if (item) {
            item->GetChildren().front()->Attach(mockContext_);
            item->Attach(mockContext_);
            renderNode_->AddChildByIndex(index, item);
            return true;
        } else {
            GTEST_LOG_(INFO) << "create RenderWaterFlowItem component failed!";
            return false;
        }
    });
    renderNode_->SetDeleteChildByIndex([this](int32_t index) {
        for (auto outIt = renderNode_->flowMatrix_.begin(); outIt != renderNode_->flowMatrix_.end(); outIt++) {
            for (auto inIt = outIt->second.begin(); inIt != outIt->second.end(); inIt++) {
                if (inIt->second == index) {
                    GTEST_LOG_(INFO) << "delete: rowIndex:" << outIt->first << "columnIndex:" << inIt->first
                                     << "index:" << inIt->second;
                    return;
                }
            }
        }
    });
    renderNode_->SetGetChildSpanByIndex(
        [](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
            GTEST_LOG_(INFO) << "SetGetChildSpanByIndex called !";

            if (index >= 0) {
                if (isHorizontal) {
                    itemMainSpan = 1;
                    itemCrossSpan = 1;
                } else {
                    itemMainSpan = 1;
                    itemCrossSpan = 1;
                }
                return true;
            }
            return false;
        });
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetItemCalSizeNeeded_001, TestSize.Level1)
{
    RefPtr<V2::RenderWaterFlowItem> renderitem = nullptr;
    auto result = renderNode_->GetItemCalSizeNeeded(renderitem);
    EXPECT_EQ(result, false);
    auto item = WaterFlowTestUtils::CreateRenderItem(1, 1, 1, mockContext_);
    if (item) {
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
    }
    auto expect = renderNode_->GetItemCalSizeNeeded(item);
    EXPECT_EQ(expect, true);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetItemCalSizeNeeded_001, TestSize.Level1)
{
    auto item = WaterFlowTestUtils::CreateRenderItem(1, 1, 1, mockContext_);
    if (item) {
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
    }
    renderNode_->SetItemCalSizeNeeded(item, true);
    EXPECT_TRUE(item->GetCalSizeNeeded());
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_UpdateAccessibilityAttr_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    NodeId nodeId = 1;
    std::string nodeName = "string";
    auto sAbilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, nodeName);
    WeakPtr<AccessibilityNode> wAbilityNode(sAbilityNode);
    auto wref = wAbilityNode.Upgrade();
    if (wref == nullptr) {
        GTEST_LOG_(INFO) << "wref == nullptr!";
        return;
    }

    renderNode_->SetAccessibilityNode(wAbilityNode);
    renderNode_->UpdateAccessibilityAttr();
    auto refPtr = renderNode_->GetAccessibilityNode().Upgrade();
    if (refPtr) {
        EXPECT_EQ(refPtr->GetCollectionInfo().rows, 5);
        EXPECT_EQ(refPtr->GetCollectionInfo().columns, 5);
    } else {
        GTEST_LOG_(INFO) << "the refptr is nullptr";
    }
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetIndexByFlow_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    int32_t row = 1;
    int32_t col = 2;
    int32_t index = 1;
    for (int32_t i = 1; i < 3; i++) {
        for (int32_t j = 1; j < 3; j++) {
            renderNode_->flowMatrix_[i][j] = index;
            index++;
        }
    }
    int32_t result = renderNode_->GetIndexByFlow(row, col);
    EXPECT_EQ(result, 2);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_focusMove_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    int32_t index = 0;
    KeyDirection direction = KeyDirection::DOWN;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrix_[i][j] = index;
            index++;
        }
    }
    renderNode_->focusRow_ = 0;
    renderNode_->focusCol_ = 1;
    renderNode_->focusIndex_ = 1;
    int32_t result = renderNode_->focusMove(direction);
    EXPECT_EQ(result, 5);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetItemSpan_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    auto item = WaterFlowTestUtils::CreateRenderItem(1, 2, 1, mockContext_);
    auto flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
    EXPECT_NE(flowItem, nullptr);
    int32_t rowresult = renderNode_->GetItemSpan(flowItem, true);
    EXPECT_EQ(rowresult, 1);
    int32_t colresult = renderNode_->GetItemSpan(flowItem, false);
    EXPECT_EQ(colresult, 2);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_updatefocusinfo_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    int32_t index = 0;
    int32_t focusIndex = 1;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrixByIndex_[i][j] = index;
            index++;
        }
    }

    renderNode_->UpdateFocusInfo(focusIndex);
    EXPECT_EQ(renderNode_->focusRow_, 0);
    EXPECT_EQ(renderNode_->focusCol_, 4);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_RequestNextFocus_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    int32_t index = 0;
    bool vertical = true;
    bool reverse = false;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrix_[j][i] = index;
            index++;
        }
    }
    renderNode_->focusRow_ = 0;
    renderNode_->focusCol_ = 1;
    renderNode_->focusIndex_ = 1;
    int32_t result = renderNode_->RequestNextFocus(vertical, reverse);
    EXPECT_EQ(result, 5);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ParseCrossLength_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    std::vector<double> rowlens;
    std::vector<double> collens;
    rowlens = renderNode_->ParseCrossLength(renderNode_->mainSize_, renderNode_->mainGap_);
    for (auto& len : rowlens) {
        EXPECT_EQ(len, 160);
    }
    collens = renderNode_->ParseCrossLength(renderNode_->crossSize_, renderNode_->crossGap_);
    for (auto len : collens) {
        EXPECT_EQ(len, 160);
    }
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_UpdateScrollPosition_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    renderNode_->currentOffset_ = 1.0;
    double offset1 = 3.1;
    int32_t source = 10;
    bool result = renderNode_->UpdateScrollPosition(offset1, source);
    EXPECT_TRUE(result);
    EXPECT_EQ(renderNode_->currentOffset_, 1.0);

    double offset = 2.1;
    int32_t source2 = 2;
    renderNode_->reachHead_ = false;
    renderNode_->reachTail_ = true;
    renderNode_->currentOffset_ = 1.0;
    auto expect = renderNode_->UpdateScrollPosition(offset, source2);
    EXPECT_EQ(renderNode_->reachTail_, false);
    EXPECT_TRUE(expect);
    EXPECT_EQ(renderNode_->currentOffset_, 3.0);

    double offset2 = -2.1;
    int32_t source3 = 2;
    renderNode_->reachHead_ = true;
    renderNode_->reachTail_ = false;
    renderNode_->currentOffset_ = 1.0;
    auto expect2 = renderNode_->UpdateScrollPosition(offset2, source3);
    EXPECT_EQ(renderNode_->reachHead_, false);
    EXPECT_TRUE(expect2);
    EXPECT_EQ(renderNode_->currentOffset_, -1.0);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_HandleAxisEvent_001, TestSize.Level1)
{
    AxisEvent event;
    event.horizontalAxis = 1.5;
    event.verticalAxis = 1.5;
    renderNode_->reachHead_ = true;
    renderNode_->reachTail_ = false;
    renderNode_->currentOffset_ = 1.0;
    renderNode_->HandleAxisEvent(event);
    EXPECT_EQ(renderNode_->reachHead_, false);
    EXPECT_EQ(renderNode_->currentOffset_, -11.0);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_isScrollable_001, TestSize.Level1)
{
    AxisDirection direction1 = AxisDirection::UP;
    renderNode_->isVertical_ = true;
    renderNode_->reachHead_ = false;
    renderNode_->reachTail_ = true;
    EXPECT_TRUE(renderNode_->IsAxisScrollable(direction1));

    AxisDirection direction2 = AxisDirection::DOWN;
    renderNode_->reachHead_ = true;
    renderNode_->reachTail_ = false;
    EXPECT_TRUE(renderNode_->IsAxisScrollable(direction2));

    renderNode_->isVertical_ = false;
    AxisDirection direction3 = AxisDirection::LEFT;
    renderNode_->reachHead_ = false;
    renderNode_->reachTail_ = true;
    EXPECT_TRUE(renderNode_->IsAxisScrollable(direction3));

    AxisDirection direction4 = AxisDirection::RIGHT;
    renderNode_->reachHead_ = true;
    renderNode_->reachTail_ = false;
    EXPECT_TRUE(renderNode_->IsAxisScrollable(direction4));
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnPaintFinish_001, TestSize.Level1)
{
    renderNode_->showItem_ = {1.0, 2.0};
    renderNode_->OnPaintFinish();
    EXPECT_EQ(renderNode_->startShowItemIndex_, 1.0);
    EXPECT_EQ(renderNode_->endShowItemIndex_, 2.0);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearItems_001, TestSize.Level1)
{
    FillItems(0, 1, 1, 1, 1);
    renderNode_->ClearItems();
    EXPECT_EQ(renderNode_->items_.size(), 0);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetItemSpanFromCache_001, TestSize.Level1)
{
    int32_t itemMainSpan = 0;
    int32_t itemCrossSpan = 0;
    int32_t index = 2;
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    bool result = renderNode_->GetItemSpanFromCache(index, itemMainSpan, itemCrossSpan);
    auto it = renderNode_->itemSpanCache_.find(2);
    if (it != renderNode_->itemSpanCache_.end()) {
        EXPECT_EQ(it->second.rowSpan, 1);
        EXPECT_EQ(it->second.colSpan, 1);
    }
    EXPECT_TRUE(result);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnDataSourceUpdated_001, TestSize.Level1)
{
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    int32_t index = -1;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrix_[i][j] = index;
        }
    }
    renderNode_->OnDataSourceUpdated(index);
    EXPECT_EQ(renderNode_->items_.size(), 0);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetItemMainIndex_001, TestSize.Level1)
{
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    int32_t index = 0;
    int32_t findindex = 2;
    int32_t mainIndex = 0;
    int32_t crossIndex = 0;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrixByIndex_[i][j] = index;
            index++;
        }
    }
    bool result = renderNode_->GetItemMainCrossIndex(1, mainIndex, crossIndex);
    EXPECT_TRUE(result);
    EXPECT_EQ(mainIndex, 0);
    EXPECT_EQ(crossIndex, 4);
    EXPECT_EQ(renderNode_->GetItemMainIndex(findindex), 0);
    findindex = 6;
    EXPECT_EQ(renderNode_->GetItemMainIndex(findindex), -1);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DeleteItems_001, TestSize.Level1)
{
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    int32_t index = 0;
    for (int32_t i = 0; i < 3; i++) {
        for (int32_t j = 0; j < 3; j++) {
            renderNode_->flowMatrix_[i][j] = index;
            index++;
        }
    }
    EXPECT_EQ(renderNode_->items_.size(), 5);
    renderNode_->DeleteItems(0, false);
    EXPECT_EQ(renderNode_->items_.size(), 2);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_BuildFlow_001, TestSize.Level1)
{
    std::vector<double> cross;
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    renderNode_->BuildFlow(cross);
    if (cross.empty()) {
        GTEST_LOG_(INFO) << "buildflow failed!";
        return;
    }
    EXPECT_EQ(renderNode_->flowCells_.Width(), 160.0);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_NeedUpdate_001, TestSize.Level1)
{
    FlexDirection directionExpect = FlexDirection::COLUMN;
    int32_t cols = 3;
    auto component =  WaterFlowTestUtils::CreateComponent(directionExpect, cols);
    bool update = renderNode_->NeedUpdate(component);
    EXPECT_TRUE(update);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_AddChildByIndex_001, TestSize.Level1)
{
    for (int32_t index = 0; index < render_component_count; index++) {
        auto item = WaterFlowTestUtils::CreateRenderItem(1, 1, index, mockContext_);
        auto flowitem = AceType::DynamicCast<RenderWaterFlowItem>(item);
        renderNode_->AddChildByIndex(index, flowitem);
    }
    EXPECT_EQ(renderNode_->items_.size(), render_component_count);
    EXPECT_EQ(renderNode_->RenderNode::GetChildren().size(), render_component_count);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetChildPosition_001, TestSize.Level1)
{
    int32_t index = 0;
    Size size(160, 160);
    for (int32_t i = 0; i < 6; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    for (int32_t i = 0; i < 3; i++) {
        for (int32_t j = 0; j < 3; j++) {
            renderNode_->flowMatrixByIndex_[i][j] = index;
            index++;
        }
    }
    renderNode_->flowCells_ = size;
    auto item = renderNode_->items_.find(3);
    int32_t itemMainSpan = renderNode_->GetItemSpan(item->second, false);
    int32_t itemCrossSpan = renderNode_->GetItemSpan(item->second, true);
    int32_t itemMain = renderNode_->GetItemMainIndex(1);
    item->second->SetLayoutSize(Size(160, 160));
    renderNode_->SetChildPosition(item->second, itemMain, 1, itemMainSpan, itemCrossSpan);
    EXPECT_TRUE(item->second->GetPosition() == Offset(210.0, 0.0));
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CheckFlowPlaced_001, TestSize.Level1)
{
    int32_t itemMain = 0;
    int32_t itemCross = 2;
    int32_t itemMainSpan = 0;
    int32_t itemCrossSpan = 0;
    int32_t index = 2;
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    EXPECT_TRUE(renderNode_->GetItemSpanFromCache(index, itemMainSpan, itemCrossSpan));
    bool result = renderNode_->CheckFlowPlaced(index, itemMain, itemCross, itemMainSpan, itemCrossSpan);
    EXPECT_TRUE(result);
    EXPECT_TRUE(renderNode_->flowMatrix_.count(0));
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_MakeInnerLayoutParam_001, TestSize.Level1)
{
    int32_t itemMain = 0;
    int32_t itemCross = 2;
    int32_t itemMainSpan = 0;
    int32_t itemCrossSpan = 0;
    int32_t index = 2;
    Size size(160, 160);
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    renderNode_->flowCells_ = size;
    EXPECT_TRUE(renderNode_->GetItemSpanFromCache(index, itemMainSpan, itemCrossSpan));
    const auto& it = renderNode_->MakeInnerLayoutParam(itemMain, itemCross, itemMainSpan, itemCrossSpan);
    EXPECT_EQ(it.GetMaxSize(), size);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_LayoutChild_001, TestSize.Level1)
{
    int32_t itemMain = 0;
    int32_t itemCross = 1;
    int32_t itemMainSpan = 1;
    int32_t itemCrossSpan = 1;

    Size size(160, 160);
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    renderNode_->flowCells_ = size;
    renderNode_->mainSize_ = 160;
    auto item = renderNode_->items_.find(1);
    renderNode_->LayoutChild(item->second, itemMain, itemCross, itemMainSpan, itemCrossSpan);
    EXPECT_EQ(item->second->GetPosition(), Offset(0, 210));
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetFlowSize_001, TestSize.Level1)
{
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    renderNode_->mainSize_ = 0;
    renderNode_->crossSize_ = 0;
    Size sizemax(1000, 1000);
    Size sizemin(160, 160);
    LayoutParam layoutParam(sizemax, sizemin);
    renderNode_->SetLayoutParam(layoutParam);
    EXPECT_TRUE(renderNode_->GetFlowSize());
    EXPECT_EQ(renderNode_->mainSize_, 1000);
    EXPECT_EQ(renderNode_->crossSize_, 1000);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_Rank_001, TestSize.Level1)
{
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    int32_t index = 0;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrix_[i][j] = index;
            index++;
        }
    }
    bool result = renderNode_->Rank(3);
    EXPECT_TRUE(result);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CreateScrollable_001, TestSize.Level1)
{
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    renderNode_->scrollable_ = nullptr;
    renderNode_->CreateScrollable();
    EXPECT_TRUE(renderNode_->scrollable_ != nullptr);
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SupplyItems_001, TestSize.Level1)
{
    std::vector<double> main;

    int32_t mainIndex = 0;
    bool vailSupplyItem = false;
    for (int32_t i = 0; i < 5; i++) {
        FillItems(i, 1, 1, 1, 1);
    }
    int32_t index = 0;
    for (int32_t i = 0; i < 4; i++) {
        for (int32_t j = 0; j < 4; j++) {
            renderNode_->flowMatrix_[i][j] = -1;
            index++;
        }
    }
    renderNode_->BuildFlow(main);
    renderNode_->SupplyItems(vailSupplyItem, mainIndex);

    EXPECT_TRUE(renderNode_->inCache_.count(mainIndex));
}

HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_001, TestSize.Level1)
{
    CreateWaterFlow(1, 1);
    renderNode_->mainSize_ = 0;
    renderNode_->crossSize_ = 0;
    Size sizemax(1000, 1000);
    Size sizemin(160, 160);
    LayoutParam layoutParam(sizemax, sizemin);
    renderNode_->SetLayoutParam(layoutParam);
    renderNode_->PerformLayout();
    const std::list<RefPtr<RenderNode>>& items = renderNode_->RenderNode::GetChildren();
    EXPECT_TRUE(!items.empty());
    int32_t index = 0;
    for (const auto& item : items) {
        EXPECT_TRUE(item->GetPosition() == Offset(index % 5 * 210, index / 5 * 210));
        EXPECT_TRUE(item->GetLayoutSize() == Size(160.0, 160.0));
        index++;
    }
}

HWTEST_F(RenderWaterFlowTest, PerformLayout_002, TestSize.Level1)
{
    CreateWaterFlow(2, 2);
    renderNode_->SetGetChildSpanByIndex(
        [](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
            GTEST_LOG_(INFO) << "SetGetChildSpanByIndex called start!";
            if (index >= 0) {
                itemMainSpan = 2;
                itemCrossSpan = 2;
                return true;
            }
            return false;
        });
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});

    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderNode_->SetLayoutParam(layoutParam);

    renderNode_->PerformLayout();

    auto& items = renderNode_->RenderNode::GetChildren();
    EXPECT_TRUE(!items.empty());
    int32_t index = 0;
    for (const auto& item : items) {
        if ((index + 1) % 3 == 0) {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 3 * 420, index / 3 * 420));
            EXPECT_TRUE(item->GetLayoutSize() == Size(160.0, 2 * 160 + 50));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 3 * 420, index / 3 * 420));
            EXPECT_TRUE(item->GetLayoutSize() == Size(2 * 160 + 50, 2 * 160 + 50));
        }
        index++;
    }
}

HWTEST_F(RenderWaterFlowTest, PerformLayout_003, TestSize.Level1)
{
    CreateWaterFlow(3, 3);
    renderNode_->SetGetChildSpanByIndex(
        [](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
            GTEST_LOG_(INFO) << "SetGetChildSpanByIndex called start!";
            if (index >= 0) {
                itemMainSpan = 3;
                itemCrossSpan = 3;
                return true;
            }
            return false;
        });
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});

    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderNode_->SetLayoutParam(layoutParam);

    renderNode_->PerformLayout();

    auto& items = renderNode_->RenderNode::GetChildren();
    EXPECT_TRUE(!items.empty());
    int32_t index = 0;
    for (const auto& item : items) {
        if ((index + 1) % 2 == 0) {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 630, index / 2 * 630));
            EXPECT_TRUE(item->GetLayoutSize() == Size(2 * 160 + 50, 3 * 160 + 50 * 2));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 630, index / 2 * 630));
            EXPECT_TRUE(item->GetLayoutSize() == Size(3 * 160 + 50 * 2, 3 * 160 + 50 * 2));
        }
        index++;
    }
}

HWTEST_F(RenderWaterFlowTest, PerformLayout_004, TestSize.Level1)
{
    CreateWaterFlow(4, 4);
    renderNode_->SetGetChildSpanByIndex(
        [](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
            GTEST_LOG_(INFO) << "SetGetChildSpanByIndex called start!";
            if (index >= 0) {
                itemMainSpan = 4;
                itemCrossSpan = 4;
                return true;
            }
            return false;
        });
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});

    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderNode_->SetLayoutParam(layoutParam);

    renderNode_->PerformLayout();

    auto& items = renderNode_->RenderNode::GetChildren();
    EXPECT_TRUE(!items.empty());
    int32_t index = 0;
    for (const auto& item : items) {
        if ((index + 1) % 2 == 0) {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 840, index / 2 * 840));
            EXPECT_TRUE(item->GetLayoutSize() == Size(160, 4 * 160 + 50 * 3));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 840, index / 2 * 840));
            EXPECT_TRUE(item->GetLayoutSize() == Size(4 * 160 + 50 * 3, 4 * 160 + 50 * 3));
        }
        index++;
    }
}

HWTEST_F(RenderWaterFlowTest, PerformLayout_005, TestSize.Level1)
{
    CreateWaterFlow(5, 5);
    renderNode_->SetGetChildSpanByIndex(
        [](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
            GTEST_LOG_(INFO) << "SetGetChildSpanByIndex called start!";
            if (index >= 0) {
                itemMainSpan = 5;
                itemCrossSpan = 5;
                return true;
            }
            return false;
        });
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});

    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderNode_->SetLayoutParam(layoutParam);

    renderNode_->PerformLayout();

    auto& items = renderNode_->RenderNode::GetChildren();
    EXPECT_TRUE(items.size() == 1);
    auto it = items.begin();
    EXPECT_TRUE((*it)->GetPosition() == Offset(0, 0));
    EXPECT_TRUE((*it)->GetLayoutSize() == Size(1000, 1000));
}

HWTEST_F(RenderWaterFlowTest, PerformLayout_006, TestSize.Level1)
{
    CreateWaterFlow(6, 6);
    renderNode_->SetGetChildSpanByIndex(
        [](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
            GTEST_LOG_(INFO) << "SetGetChildSpanByIndex called start!";
            if (index >= 0) {
                itemMainSpan = 6;
                itemCrossSpan = 6;
                return true;
            }
            return false;
        });
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});

    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderNode_->SetLayoutParam(layoutParam);

    renderNode_->PerformLayout();

    auto& items = renderNode_->RenderNode::GetChildren();
    EXPECT_TRUE(items.size() == 1);
    auto it = items.begin();
    EXPECT_TRUE((*it)->GetPosition() == Offset(0, 0));
    EXPECT_TRUE((*it)->GetLayoutSize() == Size(1000, 1210));
}
} // namespace OHOS::Ace
