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

#define private public
#define protected public
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/test/unittest/water_flow/water_flow_test_utils.h"
#include "core/components_v2/water_flow/water_flow_element.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using RenderWaterFlow = OHOS::Ace::V2::RenderWaterFlow;
using RenderWaterFlowItem = OHOS::Ace::V2::RenderWaterFlowItem;
using WaterFlowComponent = OHOS::Ace::V2::WaterFlowComponent;
using WaterFlowItemComponent = OHOS::Ace::V2::WaterFlowItemComponent;
using WaterFlowPositionController = OHOS::Ace::V2::WaterFlowPositionController;

#define CHECK_RENDERNODE_NULL_VOID(ptr)             \
    do {                                            \
        if (!(ptr)) {                               \
            GTEST_LOG_(INFO) << #ptr "is nullptr!"; \
            return;                                 \
        }                                           \
    } while (0)

namespace OHOS::Ace {
constexpr size_t CREATE_FLOWITEM_COUNT = 5;
constexpr size_t CREATE_FLOWITEM_MAX_COUNT = 50;
constexpr size_t START_INDEX = 0;
constexpr double START_POS = 0.0;
constexpr size_t TOTAL_COUNT = 5000;
const Size FLOW_MAX_SIZE(1000, 1000);
const Size FLOW_MIN_SIZE(150, 150);
constexpr Dimension MIN_WIDTH = 300.0_px;
constexpr Dimension MIN_HEIGHT = 300.0_px;
constexpr Dimension MAX_WIDTH = 1000.0_px;
constexpr Dimension MAX_HEIGHT = 1000.0_px;
constexpr int64_t MICROSEC_TO_NANOSEC = 1000;
constexpr int64_t MILLISEC_TO_NANOSEC = 1000000;
constexpr double CENTER_POINT = 2.0;

using ConstraintSize = struct {
    Dimension minWidth;
    Dimension minHeight;
    Dimension maxWidth;
    Dimension maxHeight;
};

class MockWaterFlowElement : public V2::WaterFlowItemGenerator {
public:
    RefPtr<RenderNode> RequestWaterFlowFooter() override;
    inline void SetContext(const RefPtr<PipelineContext>& context)
    {
        mockContext_ = context;
    }
private:
    RefPtr<PipelineContext> mockContext_;
};

RefPtr<RenderNode> MockWaterFlowElement::RequestWaterFlowFooter()
{
    if (mockContext_) {
        auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
        return item;
    }
    return nullptr;
}

class RenderWaterFlowTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    void CreateRenderWaterFlow(std::string columnsArgs, std::string rowsArgs,
        FlexDirection direction = FlexDirection::COLUMN, size_t index = 0);
    void SetItemConstraintSize(RefPtr<Component> component, const ConstraintSize& itemConstraintSize);
    void SetCallback();
    RefPtr<PipelineContext> mockContext_;
    RefPtr<RenderWaterFlow> renderNode_;
    ConstraintSize itemConstraintSize_ = { MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH, MAX_HEIGHT };
};

void RenderWaterFlowTest::SetUpTestCase() {}
void RenderWaterFlowTest::TearDownTestCase() {}

void RenderWaterFlowTest::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    mockContext_->rootWidth_ = 2049.0;
    renderNode_ = AceType::MakeRefPtr<RenderWaterFlow>();
    renderNode_->Attach(mockContext_);
}

void RenderWaterFlowTest::TearDown()
{
    mockContext_ = nullptr;
    renderNode_ = nullptr;
}

void RenderWaterFlowTest::SetItemConstraintSize(RefPtr<Component> component, const ConstraintSize& itemConstraintSize)
{
    auto waterflowComponent = AceType::DynamicCast<WaterFlowComponent>(component);
    if (waterflowComponent) {
        waterflowComponent->SetMinWidth(itemConstraintSize.minWidth);
        waterflowComponent->SetMinHeight(itemConstraintSize.minHeight);
        waterflowComponent->SetMaxWidth(itemConstraintSize.maxWidth);
        waterflowComponent->SetMaxHeight(itemConstraintSize.maxHeight);
    }
}

void RenderWaterFlowTest::CreateRenderWaterFlow(std::string columnsArgs, std::string rowsArgs,
    FlexDirection direction, size_t index)
{
    auto component = WaterFlowTestUtils::CreateComponent(columnsArgs, rowsArgs, direction);
    auto waterflowComponent = AceType::DynamicCast<WaterFlowComponent>(component);
    CHECK_RENDERNODE_NULL_VOID(waterflowComponent);

    RefPtr<WaterFlowPositionController> controller = AceType::MakeRefPtr<WaterFlowPositionController>();
    RefPtr<ScrollBarProxy> scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    waterflowComponent->SetController(controller);
    waterflowComponent->SetScrollBarProxy(scrollBarProxy);
    SetItemConstraintSize(waterflowComponent, itemConstraintSize_);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    SetCallback();
    renderNode_->Update(waterflowComponent);
    LayoutParam layoutParam(FLOW_MAX_SIZE, FLOW_MIN_SIZE);
    renderNode_->SetLayoutParam(layoutParam);
    renderNode_->GetFlowSize();
    for (size_t i = 0; i < index; i++) {
        auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
        auto waterflowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
        CHECK_RENDERNODE_NULL_VOID(waterflowItem);
        renderNode_->AddChildByIndex(i, waterflowItem);
    }
}

void RenderWaterFlowTest::SetCallback()
{
    renderNode_->SetBuildChildByIndex([this](size_t index) {
        auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
        if (!item) {
            GTEST_LOG_(INFO) << "create renderWaterflowItem failed!";
            return false;
        }
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChildByIndex(index, item);
        return true;
    });
    renderNode_->SetDeleteChildByIndex([this](size_t index) {
        if (renderNode_) {
            renderNode_->RemoveChildByIndex(index);
        }
    });
}

/**
 * @tc.name: RenderWaterFlowTest_Create_001
 * @tc.desc: Verify that the rendered object was created successfully.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_Create_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto createRenderNode = renderNode_->Create();
    EXPECT_TRUE(createRenderNode != nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_Update_001
 * @tc.desc: Verify that the update function is tested normally.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_Update_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_TRUE(renderNode_->updateFlag_);
    EXPECT_TRUE(renderNode_->scrollBarProxy_ != nullptr);
    EXPECT_EQ(renderNode_->direction_, FlexDirection::COLUMN_REVERSE);
    EXPECT_EQ(renderNode_->userColGap_.Value(), 100.0);
    EXPECT_EQ(renderNode_->userRowGap_.Value(), 100.0);
    EXPECT_EQ(renderNode_->colsArgs_, "1fr 1fr");
    EXPECT_EQ(renderNode_->rowsArgs_, "1fr 1fr");
}

/**
 * @tc.name: RenderWaterFlowTest_Update_002
 * @tc.desc: Verifying exceptions Testing the update function.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_Update_002, TestSize.Level2)
{
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->Update(nullptr);
    EXPECT_TRUE(!(renderNode_->updateFlag_));
    EXPECT_TRUE(renderNode_->scrollBarProxy_ == nullptr);
    EXPECT_EQ(renderNode_->userColGap_.Value(), 0.0);
    EXPECT_EQ(renderNode_->userRowGap_.Value(), 0.0);
}

/**
 * @tc.name: RenderWaterFlowTest_SetBuildChildByIndex_001
 * @tc.desc: Verify that the rendernode of the item is created through the SetBuildChildByIndex function.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetBuildChildByIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_TRUE(renderNode_->buildChildByIndex_ != nullptr);
    EXPECT_TRUE(renderNode_->buildChildByIndex_(START_INDEX));
    EXPECT_TRUE(!renderNode_->items_.empty());
    if (renderNode_->deleteChildByIndex_) {
        renderNode_->deleteChildByIndex_(START_INDEX);
        EXPECT_TRUE(renderNode_->items_.empty());
    }
}

/**
 * @tc.name: RenderWaterFlowTest_SetDeleteChildByIndex_001
 * @tc.desc: Verify that when calling the SetDeleteChildByIndex function, deleteChildByIndex_ is not empty.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetDeleteChildByIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_TRUE(renderNode_->deleteChildByIndex_ != nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTotalCount_001
 * @tc.desc: Verify GetTotalCount function.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTotalCount_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([]() {
        return TOTAL_COUNT;
    });
    EXPECT_TRUE(renderNode_->getTotalCount_ != nullptr);
    auto totalCount = renderNode_->getTotalCount_();
    EXPECT_EQ(totalCount, TOTAL_COUNT);
}

/**
 * @tc.name: RenderWaterFlowTest_AddChildByIndex_001
 * @tc.desc: Verify that AddChildByIndex function creates rendernode.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_AddChildByIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_EQ(renderNode_->items_.size(), CREATE_FLOWITEM_COUNT);
    EXPECT_EQ(renderNode_->RenderNode::GetChildren().size(), CREATE_FLOWITEM_COUNT);
}

/**
 * @tc.name: RenderWaterFlowTest_RemoveChildByIndex_001
 * @tc.desc: Verify that the RemoveChildByIndex function deletes rendernode.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_RemoveChildByIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_EQ(renderNode_->items_.size(), CREATE_FLOWITEM_COUNT);
    renderNode_->RemoveChildByIndex(CREATE_FLOWITEM_COUNT);
    EXPECT_EQ(renderNode_->items_.size(), CREATE_FLOWITEM_COUNT);
    renderNode_->RemoveChildByIndex(CREATE_FLOWITEM_COUNT - 1);
    EXPECT_EQ(renderNode_->items_.size(), CREATE_FLOWITEM_COUNT - 1);
}

/**
 * @tc.name: RenderWaterFlowTest_ClearLayout_001
 * @tc.desc: Fill in items and call clearlayout to clear items.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearLayout_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->mainSideEndPos_.push_back(START_POS);
    renderNode_->mainSideEndPos_.push_back(START_POS);
    renderNode_->crossSideSize_.push_back(450.0);
    renderNode_->crossSideSize_.push_back(450.0);
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->CallItemConstraintSize();
    renderNode_->CallGap();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->ClearLayout(renderNode_->flowMatrix_.size(), true);
    EXPECT_TRUE(renderNode_->flowMatrix_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_ClearLayout_002
 * @tc.desc: Fill in items and call clearlayout to clear items of the specified index.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearLayout_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);

    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->ClearLayout(CREATE_FLOWITEM_COUNT - 1);
    EXPECT_EQ(renderNode_->flowMatrix_.size(), CREATE_FLOWITEM_COUNT - 1);
}

/**
 * @tc.name: RenderWaterFlowTest_ClearLayout_003
 * @tc.desc: Call the ClearLayout function to reset the index data of the layout.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearLayout_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->crossCount_ = CREATE_FLOWITEM_COUNT;
    renderNode_->ClearLayout(CREATE_FLOWITEM_COUNT, true);
    EXPECT_EQ(renderNode_->itemsByCrossIndex_.size(), CREATE_FLOWITEM_COUNT);
}

/**
 * @tc.name: RenderWaterFlowTest_ClearItems_001
 * @tc.desc: Verify that the ClearItems function clears the specified items and deletes all items.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearItems_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_EQ(renderNode_->items_.size(), CREATE_FLOWITEM_COUNT);
    renderNode_->ClearItems(CREATE_FLOWITEM_COUNT);
    EXPECT_EQ(renderNode_->items_.size(), CREATE_FLOWITEM_COUNT);
    renderNode_->ClearItems();
    EXPECT_TRUE(renderNode_->items_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_OnDataSourceUpdated_001
 * @tc.desc: Verify that the OnDataSourceUpdated function updates all items.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnDataSourceUpdated_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([]() {
        return TOTAL_COUNT;
    });
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->InitialFlowProp();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->OnDataSourceUpdated(START_INDEX);
    EXPECT_TRUE(renderNode_->items_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_OnDataSourceUpdated_002
 * @tc.desc: Verify that the OnDataSourceUpdated function updates the items after the specified items.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnDataSourceUpdated_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([]() {
        return TOTAL_COUNT;
    });
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->InitialFlowProp();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->OnDataSourceUpdated(1);
    EXPECT_EQ(renderNode_->items_.size(), 1);
}

/**
 * @tc.name: RenderWaterFlowTest_SetTotalCount_001
 * @tc.desc: Verify that the SetTotalCount function is set to total count.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetTotalCount_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_EQ(renderNode_->totalCount_, 0);
    renderNode_->SetTotalCount(0);
    EXPECT_EQ(renderNode_->totalCount_, 0);
    renderNode_->SetTotalCount(TOTAL_COUNT);
    EXPECT_EQ(renderNode_->totalCount_, TOTAL_COUNT);
}

/**
 * @tc.name: RenderWaterFlowTest_GetEstimatedHeight_001
 * @tc.desc: Verify that GetEstimatedHeight gets the height of the item layout position in the window.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetEstimatedHeight_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->mainSideEndPos_.push_back(300.0);
    renderNode_->mainSideEndPos_.push_back(200.0);
    renderNode_->crossSideSize_.push_back(450);
    renderNode_->crossSideSize_.push_back(450);
    auto estimatedHeight = renderNode_->GetEstimatedHeight();
    EXPECT_EQ(estimatedHeight, 300);
}

/**
 * @tc.name: RenderWaterFlowTest_GetEstimatedHeight_002
 * @tc.desc: Verify that GetEstimatedHeight gets the height of the item layout position outside the viewing window.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetEstimatedHeight_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->mainSize_ = 10;
    renderNode_->mainSideEndPos_.push_back(300.0);
    renderNode_->mainSideEndPos_.push_back(200.0);
    renderNode_->crossSideSize_.push_back(450);
    renderNode_->crossSideSize_.push_back(450);
    auto estimatedHeight = renderNode_->GetEstimatedHeight();
    EXPECT_EQ(estimatedHeight, 10);
}

/**
 * @tc.name: RenderWaterFlowTest_ScrollToIndex_001
 * @tc.desc: Fill in items, and verify that ScrollToIndex finds the specified items outside the window and gets pos.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ScrollToIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    int32_t index = 3;
    int32_t source = 3;
    renderNode_->SetGetTotalCount([]() {
        return TOTAL_COUNT;
    });
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->InitialFlowProp();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->viewportStartPos_ = 1100.0;
    renderNode_->ScrollToIndex(index, source);
    auto iter = renderNode_->flowMatrix_.find(index);
    EXPECT_TRUE(iter != renderNode_->flowMatrix_.end());
    if (iter != renderNode_->flowMatrix_.end()) {
        EXPECT_EQ(iter->second.mainPos, 400);
    }
}

/**
 * @tc.name: RenderWaterFlowTest_ScrollToIndex_002
 * @tc.desc: Verify that ScrollToIndex does not find the specified item trigger fill matrix in the layout matrix.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ScrollToIndex_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    int32_t index = 3;
    int32_t source = 3;
    renderNode_->InitialFlowProp();
    renderNode_->viewportStartPos_ = 1100.0;
    renderNode_->ScrollToIndex(index, source);
    auto iter = renderNode_->flowMatrix_.find(index);
    EXPECT_TRUE(iter != renderNode_->flowMatrix_.end());
    if (iter != renderNode_->flowMatrix_.end()) {
        EXPECT_EQ(iter->second.mainPos, 400);
    }
}

/**
 * @tc.name: RenderWaterFlowTest_ScrollToIndex_002
 * @tc.desc: Verify that ScrollToIndex does not find the specified item trigger fill matrix in the layout matrix.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ScrollToIndex_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN_REVERSE, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    int32_t index = 3;
    int32_t source = 3;
    renderNode_->InitialFlowProp();
    renderNode_->viewportStartPos_ = 1100.0;
    renderNode_->ScrollToIndex(index, source);
    auto iter = renderNode_->flowMatrix_.find(index);
    EXPECT_TRUE(iter != renderNode_->flowMatrix_.end());
    if (iter != renderNode_->flowMatrix_.end()) {
        EXPECT_EQ(iter->second.mainPos, 400);
    }
}

/**
 * @tc.name: RenderWaterFlowTest_GetAxis_001
 * @tc.desc: Verify GetAxis gets the axis direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetAxis_001, TestSize.Level1)
{
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    Axis axis = renderNode_->GetAxis();
    EXPECT_TRUE(axis == Axis::HORIZONTAL);
    renderNode_->useScrollable_ = V2::SCROLLABLE::VERTICAL;
    axis = renderNode_->GetAxis();
    EXPECT_TRUE(axis == Axis::VERTICAL);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastOffset_001
 * @tc.desc: Verify GetLastOffset gets the last offset.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastOffset_001, TestSize.Level1)
{
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->lastOffset_ = 100.0;
    EXPECT_TRUE(renderNode_->GetLastOffset().GetX() == 100.0);
    renderNode_->useScrollable_ = V2::SCROLLABLE::VERTICAL;
    EXPECT_TRUE(renderNode_->GetLastOffset().GetY() == 100.0);
}

/**
 * @tc.name: RenderWaterFlowTest_IsAxisScrollable_001
 * @tc.desc: Verify IsAxisScrollable to determine whether it is scrollable.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_IsAxisScrollable_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto direction = AxisDirection::UP;
    renderNode_->reachHead_ = true;
    EXPECT_FALSE(renderNode_->IsAxisScrollable(direction));
}

/**
 * @tc.name: RenderWaterFlowTest_IsAxisScrollable_002
 * @tc.desc: Verify IsAxisScrollable to determine whether it is scrollable.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_IsAxisScrollable_002, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto direction = AxisDirection::LEFT;
    renderNode_->reachHead_ = true;
    EXPECT_FALSE(renderNode_->IsAxisScrollable(direction));
}

/**
 * @tc.name: RenderWaterFlowTest_IsAxisScrollable_003
 * @tc.desc: Verify IsAxisScrollable to determine whether it is scrollable.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_IsAxisScrollable_003, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto direction = AxisDirection::DOWN;
    renderNode_->reachHead_ = true;
    EXPECT_FALSE(renderNode_->IsAxisScrollable(direction));
}

/**
 * @tc.name: RenderWaterFlowTest_IsAxisScrollable_004
 * @tc.desc: Verify IsAxisScrollable to determine whether it is scrollable.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_IsAxisScrollable_004, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto direction = AxisDirection::RIGHT;
    renderNode_->reachHead_ = true;
    EXPECT_FALSE(renderNode_->IsAxisScrollable(direction));
}

/**
 * @tc.name: RenderWaterFlowTest_IsAxisScrollable_005
 * @tc.desc: Verify IsAxisScrollable to determine whether it is scrollable.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_IsAxisScrollable_005, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto direction = AxisDirection::NONE;
    EXPECT_FALSE(renderNode_->IsAxisScrollable(direction));
}

/**
 * @tc.name: RenderWaterFlowTest_CheckAxisNode_001
 * @tc.desc: Verify that the CheckAxisNode is converted to a weak pointer.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CheckAxisNode_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_TRUE(renderNode_->CheckAxisNode().Upgrade() != nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_OnChildAdded_001
 * @tc.desc: Verify that OnChildAdded sets the location coordinates of the item.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnChildAdded_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
    CHECK_RENDERNODE_NULL_VOID(item);
    renderNode_->cacheSize_ = 200.0;
    renderNode_->OnChildAdded(item);
    EXPECT_EQ(item->GetPosition().GetX(), renderNode_->crossSize_ / CENTER_POINT);
    EXPECT_EQ(item->GetPosition().GetY(), renderNode_->cacheSize_ + renderNode_->mainSize_);
}

/**
 * @tc.name: RenderWaterFlowTest_OnChildAdded_002
 * @tc.desc: Verify that OnChildAdded sets the location coordinates of the item.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnChildAdded_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
    CHECK_RENDERNODE_NULL_VOID(item);
    renderNode_->cacheSize_ = 200.0;
    renderNode_->OnChildAdded(item);
    EXPECT_EQ(item->GetPosition().GetX(), renderNode_->cacheSize_ + renderNode_->mainSize_);
    EXPECT_EQ(item->GetPosition().GetY(), renderNode_->crossSize_ / CENTER_POINT);
}

/**
 * @tc.name: RenderWaterFlowTest_OnChildAdded_003
 * @tc.desc: Verify that OnChildAdded sets the location coordinates of the item.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnChildAdded_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
    CHECK_RENDERNODE_NULL_VOID(item);
    renderNode_->cacheSize_ = 200.0;
    renderNode_->OnChildAdded(item);
    EXPECT_EQ(item->GetPosition().GetX(), renderNode_->crossSize_ / CENTER_POINT);
    EXPECT_EQ(item->GetPosition().GetY(), START_POS - renderNode_->cacheSize_);
}

/**
 * @tc.name: RenderWaterFlowTest_OnChildAdded_004
 * @tc.desc: Verify that OnChildAdded sets the location coordinates of the item.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnChildAdded_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto item = WaterFlowTestUtils::CreateRenderItem(mockContext_);
    CHECK_RENDERNODE_NULL_VOID(item);
    renderNode_->cacheSize_ = 200.0;
    renderNode_->OnChildAdded(item);
    EXPECT_EQ(item->GetPosition().GetX(), START_POS - renderNode_->cacheSize_);
    EXPECT_EQ(item->GetPosition().GetY(), renderNode_->crossSize_ / CENTER_POINT);
}

/**
 * @tc.name: RenderWaterFlowTest_HandleAxisEvent_001
 * @tc.desc: Verify the position offset information of the HandleAxisEvent setting scroll.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_HandleAxisEvent_001, TestSize.Level1)
{
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->viewportStartPos_ = START_POS;
    AxisEvent axisEvent;
    axisEvent.verticalAxis = 0.0;
    renderNode_->HandleAxisEvent(axisEvent);
    EXPECT_EQ(renderNode_->viewportStartPos_, 0.0);
    axisEvent.horizontalAxis = 0.0;
    renderNode_->HandleAxisEvent(axisEvent);
    EXPECT_EQ(renderNode_->viewportStartPos_, 0.0);
}

/**
 * @tc.name: RenderWaterFlowTest_OnPredictLayout_001
 * @tc.desc: Verify that the OnPredictLayout function fills the item matrix.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnPredictLayout_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([]() {
        return TOTAL_COUNT;
    });
    renderNode_->InitialFlowProp();
    renderNode_->OnPredictLayout(4 * MILLISEC_TO_NANOSEC / MICROSEC_TO_NANOSEC);
    EXPECT_TRUE(!renderNode_->cacheItems_.empty());
    EXPECT_EQ(renderNode_->dVPStartPosBackup_, renderNode_->viewportStartPos_);
    EXPECT_EQ(renderNode_->totalCountBack_, TOTAL_COUNT);
}

/**
 * @tc.name: RenderWaterFlowTest_OnPredictLayout_002
 * @tc.desc: Verify that the OnPredictLayout function does not fill the item matrix.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnPredictLayout_002, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([]() {
        return TOTAL_COUNT;
    });
    int64_t deadline = 1;
    renderNode_->InitialFlowProp();
    renderNode_->OnPredictLayout(deadline);
    EXPECT_TRUE(renderNode_->cacheItems_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_RequestWaterFlowFooter_001
 * @tc.desc: Verify that the RequestWaterFlowFooter function requests to create a rendernode node on the element.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_RequestWaterFlowFooter_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto waterflowElement = AceType::MakeRefPtr<MockWaterFlowElement>();
    CHECK_RENDERNODE_NULL_VOID(waterflowElement);
    waterflowElement->SetContext(mockContext_);
    WeakPtr<V2::WaterFlowItemGenerator> waterFlowItemGenerator(waterflowElement);
    renderNode_->RegisterItemGenerator(std::move(waterFlowItemGenerator));
    renderNode_->RequestWaterFlowFooter();
    EXPECT_TRUE(renderNode_->footer_ != nullptr);
    EXPECT_EQ(renderNode_->GetChildren().size(), 1);
    EXPECT_EQ(renderNode_->footerMaxSize_.Width(), ITEM_WIDTH);
    EXPECT_EQ(renderNode_->footerMaxSize_.Height(), ITEM_HEIGHT);
}

/**
 * @tc.name: RenderWaterFlowTest_RequestWaterFlowFooter_002
 * @tc.desc: Verify that the RequestWaterFlowFooter function requests to create an illegal rendernode node
 *           on the element.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_RequestWaterFlowFooter_002, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto waterflowElement = AceType::MakeRefPtr<MockWaterFlowElement>();
    CHECK_RENDERNODE_NULL_VOID(waterflowElement);
    WeakPtr<V2::WaterFlowItemGenerator> waterFlowItemGenerator(waterflowElement);
    renderNode_->RegisterItemGenerator(std::move(waterFlowItemGenerator));
    renderNode_->RequestWaterFlowFooter();
    EXPECT_TRUE(renderNode_->footer_ == nullptr);
    EXPECT_TRUE(renderNode_->GetChildren().empty());
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_001
 * @tc.desc: Verify the layout information of each item in the column direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr", "1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 1);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        EXPECT_TRUE(item->GetPosition() == Offset(START_POS, index * 400));
        EXPECT_TRUE(item->GetLayoutSize() == Size(renderNode_->crossSize_,
            renderNode_->itemConstraintSize_.minMainSize));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_002
 * @tc.desc: Verify the layout information of each item in the column direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 2);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 550, index / 2 * 400));
        EXPECT_TRUE(item->GetLayoutSize() == Size((renderNode_->crossSize_ - renderNode_->crossGap_) / CENTER_POINT,
            renderNode_->itemConstraintSize_.minMainSize));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_003
 * @tc.desc: Verify the layout information of each item in the row direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr", "1fr", FlexDirection::ROW);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 1);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        EXPECT_TRUE(item->GetPosition() == Offset(index * 400, START_POS));
        EXPECT_TRUE(item->GetLayoutSize() == Size(renderNode_->itemConstraintSize_.minMainSize,
            renderNode_->crossSize_));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_004
 * @tc.desc: Verify the layout information of each item in the row direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 2);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        EXPECT_TRUE(item->GetPosition() == Offset(index / 2 * 400, index % 2 * 550));
        EXPECT_TRUE(item->GetLayoutSize() == Size(renderNode_->itemConstraintSize_.minMainSize,
            (renderNode_->crossSize_ - renderNode_->crossGap_) / CENTER_POINT));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_005
 * @tc.desc: Verify the layout information of each item in the column_reverse direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_005, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr", "1fr", FlexDirection::COLUMN_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 1);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        if (index < renderNode_->crossSideSize_.size()) {
            EXPECT_TRUE(item->GetPosition() == Offset(START_POS, (renderNode_->mainSize_) -
                (renderNode_->itemConstraintSize_.minMainSize)));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset(START_POS, (renderNode_->mainSize_) -
                (renderNode_->itemConstraintSize_.minMainSize) - index * 400));
        }
        EXPECT_TRUE(item->GetLayoutSize() == Size(renderNode_->crossSize_,
            renderNode_->itemConstraintSize_.minMainSize));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_006
 * @tc.desc: Verify the layout information of each item in the column_reverse direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_006, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 2);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        if (index < renderNode_->crossSideSize_.size()) {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 550, renderNode_->mainSize_ -
                renderNode_->itemConstraintSize_.minMainSize));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset(index % 2 * 550, (renderNode_->mainSize_) -
            (renderNode_->itemConstraintSize_.minMainSize) - (index / renderNode_->crossSideSize_.size() * 400)));
        }
        EXPECT_TRUE(item->GetLayoutSize() == Size((renderNode_->crossSize_ - renderNode_->crossGap_) / CENTER_POINT,
            renderNode_->itemConstraintSize_.minMainSize));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_007
 * @tc.desc: Verify the layout information of each item in the row_reverse direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_007, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr", "1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 1);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        if (index < renderNode_->crossSideSize_.size()) {
            EXPECT_TRUE(item->GetPosition() == Offset((renderNode_->mainSize_) -
                (renderNode_->itemConstraintSize_.minMainSize), START_POS));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset((renderNode_->mainSize_) -
                (renderNode_->itemConstraintSize_.minMainSize) - index * 400, START_POS));
        }
        EXPECT_TRUE(item->GetLayoutSize() == Size(renderNode_->itemConstraintSize_.minMainSize,
            renderNode_->crossSize_));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_PerformLayout_008
 * @tc.desc: Verify the layout information of each item in the row_reverse direction.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_PerformLayout_008, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::ROW_REVERSE);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->PerformLayout();
    EXPECT_EQ(renderNode_->crossSideSize_.size(), 2);
    size_t index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        if (index < renderNode_->crossSideSize_.size()) {
            EXPECT_TRUE(item->GetPosition() == Offset(renderNode_->mainSize_ -
                renderNode_->itemConstraintSize_.minMainSize, index % 2 * 550));
        } else {
            EXPECT_TRUE(item->GetPosition() == Offset((renderNode_->mainSize_) -
                (renderNode_->itemConstraintSize_.minMainSize) - index / renderNode_->crossSideSize_.size() * 400,
                index % 2 * 550));
        }
        EXPECT_TRUE(item->GetLayoutSize() == Size(renderNode_->itemConstraintSize_.minMainSize,
            (renderNode_->crossSize_ - renderNode_->crossGap_) / CENTER_POINT));
        index++;
    }
}

/**
 * @tc.name: RenderWaterFlowTest_DoJump_001
 * @tc.desc: Verify the function that jump the position to be set by parameters.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DoJump_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);

    EXPECT_TRUE(renderNode_ != nullptr);
    double mainSizeOffset = 20.0;
    renderNode_->reachHead_ = false;
    renderNode_->reachTail_ = false;
    renderNode_->DoJump(mainSizeOffset, SCROLL_FROM_UPDATE);
    EXPECT_EQ(renderNode_->viewportStartPos_, mainSizeOffset);
}

/**
 * @tc.name: RenderWaterFlowTest_SetScrollBarCallback_001
 * @tc.desc: Verify the function that set the callbacks of scroll bar.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetScrollBarCallback_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr", "1fr", FlexDirection::COLUMN);

    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBar_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBar_->barController_ != nullptr);
    renderNode_->SetScrollBarCallback();
    EXPECT_TRUE(renderNode_->scrollBar_->barController_->callback_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBar_->barController_->barEndCallback_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBar_->barController_->scrollEndCallback_ != nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_InitScrollBarProxy_001
 * @tc.desc: Verify the function that initialize the callbacks of scroll bar proxy.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitScrollBarProxy_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);

    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBarProxy_ != nullptr);
    renderNode_->InitScrollBarProxy();
    EXPECT_TRUE(!renderNode_->scrollBarProxy_->scrollableNodes_.empty());
    EXPECT_EQ(renderNode_->scrollBarProxy_->scrollableNodes_.size(), 1);
}

/**
 * @tc.name: RenderWaterFlowTest_InitScrollBarProxy_002
 * @tc.desc: Verify the function that initialize the callbacks of scroll bar proxy.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitScrollBarProxy_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);

    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->scrollBarProxy_ = nullptr;
    renderNode_->InitScrollBarProxy();
    EXPECT_TRUE(renderNode_->scrollBarProxy_ == nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_InitScrollBar_001
 * @tc.desc: Verify the function that initialize the scroll bar of waterflow.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitScrollBar_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);

    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->component_ != nullptr);
    renderNode_->component_->SetController(nullptr);
    renderNode_->InitScrollBar();
    EXPECT_TRUE(renderNode_->component_->displayMode_ == DisplayMode::OFF);
}

/**
 * @tc.name: RenderWaterFlowTest_InitScrollBar_003
 * @tc.desc: Verify the function that initialize the scroll bar of waterflow.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitScrollBar_002, TestSize.Level1)
{
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->component_ = nullptr;
    renderNode_->InitScrollBar();
    EXPECT_TRUE(renderNode_->scrollBar_ == nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_InitScrollBar_004
 * @tc.desc: Verify the function that initialize the scroll bar of waterflow.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitScrollBar_003, TestSize.Level1)
{
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->Attach(nullptr);
    renderNode_->InitScrollBar();
    EXPECT_TRUE(renderNode_->scrollBar_ == nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_InitScrollBar_005
 * @tc.desc: Verify the function that initialize the scroll bar of waterflow.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitScrollBar_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);

    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->InitScrollBar();
    EXPECT_TRUE(renderNode_->scrollBar_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBar_->GetPositionMode() == PositionMode::RIGHT);

    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->InitScrollBar();
    EXPECT_TRUE(renderNode_->scrollBar_ != nullptr);
    EXPECT_TRUE(renderNode_->scrollBar_->GetPositionMode() == PositionMode::BOTTOM);
}

/**
 * @tc.name: RenderWaterFlowTest_DeleteItems_001
 * @tc.desc: Verify the function that delete items by index
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DeleteItems_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);

    int size = renderNode_->items_.size();
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});
    renderNode_->DeleteItems(START_INDEX);
    EXPECT_EQ(renderNode_->items_.size(), (size - 1));
}

/**
 * @tc.name: RenderWaterFlowTest_DeleteItems_002
 * @tc.desc: Verify the function that delete items by index
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DeleteItems_002, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->deleteChildByIndex_ = nullptr;
    EXPECT_TRUE(renderNode_->items_.empty());
    renderNode_->DeleteItems(START_INDEX);
    EXPECT_TRUE(renderNode_->items_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_DeleteItems_003
 * @tc.desc: Verify the function that delete items by index
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DeleteItems_003, TestSize.Level2)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->SetDeleteChildByIndex([](int32_t index) {});
    EXPECT_TRUE(renderNode_->items_.empty());
    renderNode_->DeleteItems(START_INDEX);
    EXPECT_TRUE(renderNode_->items_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_DealCache_001
 * @tc.desc: Verify the function that delete items which be out of cache area.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DealCache_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 0;
    renderNode_->cacheSize_ = 0;
    renderNode_->mainSize_ = 0;
    auto size = renderNode_->items_.size();
    EXPECT_TRUE(size == CREATE_FLOWITEM_MAX_COUNT);
    renderNode_->DealCache();
    EXPECT_EQ(renderNode_->items_.size(), size);
}

/**
 * @tc.name: RenderWaterFlowTest_DealCache_002
 * @tc.desc: Verify the function that delete items which be out of cache area.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DealCache_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 0;
    renderNode_->cacheSize_ = 0;
    renderNode_->mainSize_ = 0;
    auto size = renderNode_->items_.size();
    EXPECT_EQ(CREATE_FLOWITEM_MAX_COUNT, size);
    renderNode_->DealCache();
    EXPECT_EQ(renderNode_->items_.size(), size);
}

/**
 * @tc.name: RenderWaterFlowTest_DealCache_003
 * @tc.desc: Verify the function that delete items which be out of cache area.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DealCache_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 0;
    renderNode_->cacheSize_ = 0;
    renderNode_->mainSize_ = 0;
    auto size = renderNode_->items_.size();
    EXPECT_EQ(CREATE_FLOWITEM_MAX_COUNT, size);
    renderNode_->DealCache();
    EXPECT_EQ(renderNode_->items_.size(), size);
}

/**
 * @tc.name: RenderWaterFlowTest_DealCache_004
 * @tc.desc: Verify the function that delete items which be out of cache area.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_DealCache_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 0;
    renderNode_->cacheSize_ = 0;
    renderNode_->mainSize_ = 0;
    auto size = renderNode_->items_.size();
    EXPECT_EQ(CREATE_FLOWITEM_MAX_COUNT, size);
    renderNode_->DealCache();
    EXPECT_EQ(renderNode_->items_.size(), size);
}

/**
 * @tc.name: RenderWaterFlowTest_GetCacheTargetPos_001
 * @tc.desc: Verify the function that calculate the size (viewport position, cache size, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetCacheTargetPos_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    renderNode_->cacheSize_ = 100;
    renderNode_->mainSize_ = 100;
    EXPECT_EQ(renderNode_->GetCacheTargetPos(), 200);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTargetPos_001
 * @tc.desc: Verify the function that calculate the size (viewport position, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTargetPos_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    renderNode_->targetIndex_ = -1;
    renderNode_->mainSize_ = 100;
    EXPECT_EQ(renderNode_->GetTargetPos(), 100);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTargetPos_002
 * @tc.desc: Verify the function that calculate the size (viewport position, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTargetPos_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    renderNode_->targetIndex_ = -1;
    renderNode_->mainSize_ = 100;
    EXPECT_EQ(renderNode_->GetTargetPos(), 100);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTargetPos_003
 * @tc.desc: Verify the function that calculate the size (viewport position, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTargetPos_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 100.0;
    renderNode_->targetIndex_ = -1;
    renderNode_->mainSize_ = 100.0;
    EXPECT_TRUE(renderNode_->GetTargetPos() == 0);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTargetPos_004
 * @tc.desc: Verify the function that calculate the size (viewport position, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTargetPos_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 100;
    renderNode_->targetIndex_ = -1;
    renderNode_->mainSize_ = 100;
    EXPECT_TRUE(renderNode_->GetTargetPos() == 0);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTargetPos_005
 * @tc.desc: Verify the function that calculate the size (viewport position, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTargetPos_005, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 0;
    renderNode_->targetIndex_ = 0;
    renderNode_->mainSize_ = 100;
    EXPECT_TRUE(renderNode_->GetTargetPos() == DBL_MAX);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTargetPos_006
 * @tc.desc: Verify the function that calculate the size (viewport position, main size)
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTargetPos_006, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = 5005;
    renderNode_->targetIndex_ = 0;
    renderNode_->mainSize_ = 100;
    EXPECT_TRUE(renderNode_->GetTargetPos() == DBL_MAX);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTailPos_001
 * @tc.desc: Verify the function that calculate the position of last item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTailPos_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetTailPos() == START_POS);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTailPos_002
 * @tc.desc: Verify the function that calculate the position of last item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTailPos_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetTailPos() == START_POS);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTailPos_003
 * @tc.desc: Verify the function that calculate the position of last item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTailPos_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN_REVERSE);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetTailPos() == START_POS);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTailPos_004
 * @tc.desc: Verify the function that calculate the position of last item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTailPos_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW_REVERSE);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetTailPos() == START_POS);
}

/**
 * @tc.name: RenderWaterFlowTest_GetTailPos_005
 * @tc.desc: Verify the function that calculate the position of last item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetTailPos_005, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->SetGetTotalCount([this]() {
        return renderNode_->flowMatrix_.size() - 1;
    });
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    EXPECT_GT(renderNode_->GetTailPos(), START_POS);
}

/**
 * @tc.name: RenderWaterFlowTest_CheckReachHead_001
 * @tc.desc: Verify the function that check the viewport is on the head.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CheckReachHead_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    EXPECT_TRUE(renderNode_->CheckReachHead());
}

/**
 * @tc.name: RenderWaterFlowTest_CheckReachHead_002
 * @tc.desc: Verify the function that check the viewport is on the head.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CheckReachHead_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    EXPECT_TRUE(renderNode_->CheckReachHead());
}

/**
 * @tc.name: RenderWaterFlowTest_CheckReachHead_003
 * @tc.desc: Verify the function that check the viewport is on the head.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CheckReachHead_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    EXPECT_TRUE(renderNode_->CheckReachHead());
}

/**
 * @tc.name: RenderWaterFlowTest_CheckReachHead_004
 * @tc.desc: Verify the function that check the viewport is on the head.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CheckReachHead_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->viewportStartPos_ = START_POS;
    EXPECT_TRUE(renderNode_->CheckReachHead());
}

/**
 * @tc.name: RenderWaterFlowTest_GetCrossSize_001
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetCrossSize_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_EQ(renderNode_->GetCrossSize(nullptr), 0.0);
    for (const auto& item : renderNode_->items_) {
        EXPECT_EQ(renderNode_->GetCrossSize(item.second), item.second->GetLayoutSize().Width());
    }
}

/**
 * @tc.name: RenderWaterFlowTest_GetCrossSize_002
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetCrossSize_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    for (const auto& item : renderNode_->items_) {
        EXPECT_EQ(renderNode_->GetCrossSize(item.second), item.second->GetLayoutSize().Height());
    }
}

/**
 * @tc.name: RenderWaterFlowTest_GetCrossSize_003
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetCrossSize_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetCrossSize(nullptr) == 0);
    for (const auto& item : renderNode_->items_) {
        EXPECT_EQ(renderNode_->GetCrossSize(item.second), item.second->GetLayoutSize().Width());
    }
}

/**
 * @tc.name: RenderWaterFlowTest_GetCrossSize_004
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetCrossSize_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    for (const auto& item : renderNode_->items_) {
        EXPECT_EQ(renderNode_->GetCrossSize(item.second), item.second->GetLayoutSize().Height());
    }
}

/**
 * @tc.name: RenderWaterFlowTest_GetMainSize_001
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetMainSize_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    auto item = renderNode_->items_[START_INDEX];
    EXPECT_TRUE(renderNode_->GetMainSize(nullptr) == 0);
    EXPECT_TRUE(renderNode_->GetMainSize(item) == item->GetLayoutSize().Height());
}

/**
 * @tc.name: RenderWaterFlowTest_GetMainSize_002
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetMainSize_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    auto item = renderNode_->items_[START_INDEX];
    EXPECT_TRUE(renderNode_->GetMainSize(item) == item->GetLayoutSize().Width());
}

/**
 * @tc.name: RenderWaterFlowTest_GetMainSize_003
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetMainSize_003, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    auto item = renderNode_->items_[START_INDEX];
    EXPECT_TRUE(renderNode_->GetMainSize(nullptr) == 0);
    EXPECT_TRUE(renderNode_->GetMainSize(item) == item->GetLayoutSize().Height());
}

/**
 * @tc.name: RenderWaterFlowTest_GetMainSize_004
 * @tc.desc: Verify the function that get the cross size of the selected item
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetMainSize_004, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::ROW_REVERSE, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    auto item = renderNode_->items_[START_INDEX];
    EXPECT_TRUE(renderNode_->GetMainSize(item) == item->GetLayoutSize().Width());
}

/**
 * @tc.name: RenderWaterFlowTest_GetFlowItemByChild_001
 * @tc.desc: Verify the function that get the flow item with child.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetFlowItemByChild_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetFlowItemByChild(nullptr) == nullptr);
    auto item = renderNode_->items_[START_INDEX];
    EXPECT_TRUE(renderNode_->GetFlowItemByChild(renderNode_) == item);
}

/**
 * @tc.name: RenderWaterFlowTest_GetFlowItemByChild_002
 * @tc.desc: Verify the function that get the flow item with child.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetFlowItemByChild_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN);
    EXPECT_TRUE(renderNode_ != nullptr);
    EXPECT_TRUE(renderNode_->GetFlowItemByChild(renderNode_) == nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_ConstraintItemSize_001
 * @tc.desc: Verify the function that get constrain size of the flow item.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ConstraintItemSize_001, TestSize.Level1)
{
    V2::FlowStyle flowStyleTest = {0, 0, 30, 50};
    CreateRenderWaterFlow("1fr 1fr 1fr", "1fr 1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->itemConstraintSize_ = V2::ItemConstraintSize{300, 400, 500, 600};
    EXPECT_TRUE(renderNode_->ConstraintItemSize(flowStyleTest, START_INDEX).mainSize == 500);
    V2::FlowStyle flowStyleTestMax = {3000, 4000, 5000, 6000};
    EXPECT_TRUE(renderNode_->ConstraintItemSize(flowStyleTestMax, START_INDEX).mainSize == 600);
}

/**
 * @tc.name: RenderWaterFlowTest_GetCrossEndPos_001
 * @tc.desc: Verify the function that get the end position of the selected cross index.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetCrossEndPos_001, TestSize.Level1)
{
    CreateRenderWaterFlow("50px 60px 70px 80px", "", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    renderNode_->InitialFlowProp();
    renderNode_->crossGap_ = 0;
    EXPECT_TRUE(renderNode_->GetCrossEndPos(4) == 0);
    EXPECT_TRUE(renderNode_->GetCrossEndPos(3) == 180);
    renderNode_->crossGap_ = 10;
    EXPECT_TRUE(renderNode_->GetCrossEndPos(2) == 130);
}

/**
 * @tc.name: RenderWaterFlowTest_UpdateMainSideEndPos_001
 * @tc.desc: Verify the function that get the end position of the selected cross index.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_UpdateMainSideEndPos_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr", "", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->InitialFlowProp();
    renderNode_->SupplyItems(itemIndex, targetPos);
    EXPECT_EQ(renderNode_->mainSideEndPos_.size(), renderNode_->itemsByCrossIndex_.size());
    renderNode_->UpdateMainSideEndPos();
    EXPECT_FALSE(renderNode_->mainSideEndPos_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_ClearFlowMatrix_001
 * @tc.desc: Verify the function that clear the selected item if index > -1, else clear all.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearFlowMatrix_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr 1fr", "", FlexDirection::COLUMN);
    EXPECT_TRUE(renderNode_ != nullptr);
    auto targetIndex = 1;
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->InitialFlowProp();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->ClearFlowMatrix(START_INDEX + 1);
    EXPECT_EQ(renderNode_->flowMatrix_.size(), targetIndex);
    renderNode_->ClearFlowMatrix(START_INDEX, true);
    EXPECT_TRUE(renderNode_->flowMatrix_.empty());
}

/**
 * @tc.name: RenderWaterFlowTest_ClearItemsByCrossIndex_001
 * @tc.desc: Verify the function that clear the selected item if cross index > -1, else clear all.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_ClearItemsByCrossIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr 1fr 1fr", "", FlexDirection::COLUMN, CREATE_FLOWITEM_MAX_COUNT);
    EXPECT_TRUE(renderNode_ != nullptr);
    int index = 4;
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->InitialFlowProp();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->ClearItemsByCrossIndex(index);
    auto cross = renderNode_->itemsByCrossIndex_.begin();
    while (cross != renderNode_->itemsByCrossIndex_.end()) {
        EXPECT_EQ((*cross).size(), 1);
        cross++;
    }
    renderNode_->ClearItemsByCrossIndex(START_INDEX, true);
    EXPECT_EQ(renderNode_->itemsByCrossIndex_.size(), renderNode_->crossCount_);
    EXPECT_TRUE(!renderNode_->itemsByCrossIndex_.empty());
    for (const auto& itemIndex : renderNode_->itemsByCrossIndex_) {
        EXPECT_TRUE(itemIndex.empty());    
    }
}

/**
 * @tc.name: RenderWaterFlowTest_RegisterItemGenerator_001
 * @tc.desc: Verify the function that judge itemGenerator_.Upgrade.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_RegisterItemGenerator_001, TestSize.Level1)
{
    RefPtr<V2::WaterFlowItemGenerator> itemgenerator = AceType::MakeRefPtr<V2::WaterFlowItemGenerator>();
    renderNode_->RegisterItemGenerator(itemgenerator);
    EXPECT_TRUE(renderNode_->itemGenerator_.Upgrade());
}

/**
 * @tc.name: RenderWaterFlowTest_HandleScrollEvent_001
 * @tc.desc: Verify the function that get the value of map.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_HandleScrollEvent_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->HandleScrollEvent();
    for (auto event : renderNode_->waterflowEventFlags_) {
        EXPECT_FALSE(event.second);
    }
}

/**
 * @tc.name: RenderWaterFlowTest_MakeInnerLayoutParam_001
 * @tc.desc: Verify the function that get the value of minsize.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_MakeInnerLayoutParam_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->InitialFlowProp();
    Size size(450, 300);
    size_t index = 0;
    size_t itemIndex = renderNode_->GetNextSupplyedIndex();
    double targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    LayoutParam innerLayout;
    innerLayout = renderNode_->MakeInnerLayoutParam(index);
    auto result = innerLayout.GetMaxSize();
    EXPECT_EQ(result, size);
}

/**
 * @tc.name: RenderWaterFlowTest_SetChildPosition_001
 * @tc.desc: Verify the function that value of GetChildPosition after using SetChildPosition.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetChildPosition_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    renderNode_->InitialFlowProp();
    size_t itemIndex = renderNode_->GetNextSupplyedIndex();
    double targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    size_t index = 0;
    for (auto& item : renderNode_->items_) {
        item.second->SetLayoutSize(Size(160, 160));
        renderNode_->SetChildPosition(item.second, index);
        EXPECT_TRUE(renderNode_->GetPosition() == Offset(index % 5 * 210, index / 5 * 210));
    }
}

/**
 * @tc.name: RenderWaterFlowTest_CreateScrollable_001
 * @tc.desc: Verify the function that Check whether scrollable_ is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CreateScrollable_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->CreateScrollable();
    EXPECT_TRUE(renderNode_->scrollable_ != nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_OnTouchTestHit_001
 * @tc.desc: Verify the function that Check whether scrollable_ is nullptr.
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_OnTouchTestHit_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    TouchRestrict touchRestrict;
    TouchTestResult result;
    touchRestrict.UpdateForbiddenType(1);
    Offset offset(START_POS, START_POS);
    renderNode_->OnTouchTestHit(offset, touchRestrict, result);
    EXPECT_FALSE(renderNode_->scrollable_ == nullptr);
}

/**
 * @tc.name: RenderWaterFlowTest_UpdateScrollPosition_001
 * @tc.desc: Verify the function that return value of UpdateScrollPosition.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_UpdateScrollPosition_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    double offset = 1.0;
    int32_t source = 10;
    auto result = renderNode_->UpdateScrollPosition(offset, source);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RenderWaterFlowTest_CallGap_001
 * @tc.desc: Verify the function that find the value of mainGap_.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CallGap_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->CallGap();
    EXPECT_EQ(renderNode_->mainGap_, 100.0);
}

/**
 * @tc.name: RenderWaterFlowTest_CallGap_001
 * @tc.desc: Verify the function that find the value of maxCrossSize,maxMainSize,minCrossSize and minMainSize.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_CallItemConstraintSize_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN);
    renderNode_->InitialFlowProp();
    renderNode_->CallItemConstraintSize();
    EXPECT_EQ(renderNode_->itemConstraintSize_.maxCrossSize, 1000.0);
    EXPECT_EQ(renderNode_->itemConstraintSize_.maxMainSize, 1000.0);
    EXPECT_EQ(renderNode_->itemConstraintSize_.minCrossSize, 300.0);
    EXPECT_EQ(renderNode_->itemConstraintSize_.minMainSize, 300.0);
}

/**
 * @tc.name: RenderWaterFlowTest_InitialFlowProp_001
 * @tc.desc: Verify the function that value of cacheSize after using InitialFlowProp.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_InitialFlowProp_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->InitialFlowProp();
    EXPECT_EQ(renderNode_->cacheSize_, 1000.0);
}

/**
 * @tc.name: RenderWaterFlowTest_ GetFlowSize_001
 * @tc.desc: Verify the function that find the value of mainSize_ and crossSize_.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetFlowSize_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_EQ(renderNode_->mainSize_, 1000.0);
    EXPECT_EQ(renderNode_->crossSize_, 1000.0);
    EXPECT_EQ(renderNode_->cacheSize_, renderNode_->mainSize_);
}

/**
 * @tc.name: RenderWaterFlowTest_ GetFlowSize_001
 * @tc.desc: Verify the function that value of targetIndex_ after using SuppltItems.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SupplyItems_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->InitialFlowProp();
    size_t itemIndex = renderNode_->GetNextSupplyedIndex();
    double targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    for (auto itemMessage : renderNode_->flowMatrix_) {
        EXPECT_EQ(itemMessage.second.crossSize, (renderNode_->crossSize_ - renderNode_->crossGap_) / CENTER_POINT);
        EXPECT_EQ(itemMessage.second.mainSize, renderNode_->itemConstraintSize_.minMainSize);
    }
}

/**
 * @tc.name: RenderWaterFlowTest_LayoutItems_001
 * @tc.desc: Verify the function that value of GetPosition after using LayoutItems.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_LayoutItems_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    for (size_t index = 0; index < renderNode_->items_.size(); index++) {
        renderNode_->cacheItems_.emplace(index);
    }
    renderNode_->LayoutItems(renderNode_->cacheItems_);
    for (auto itemMessage : renderNode_->items_) {
        EXPECT_EQ(itemMessage.second->GetLayoutSize(), Size(450.0, 300.0));
    }
}

/**
 * @tc.name: RenderWaterFlowTest_GetFooterSize_001
 * @tc.desc: Verify the function that value to width and height.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetFooterSize_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto waterflowElement = AceType::MakeRefPtr<MockWaterFlowElement>();
    CHECK_RENDERNODE_NULL_VOID(waterflowElement);
    waterflowElement->SetContext(mockContext_);
    WeakPtr<V2::WaterFlowItemGenerator> waterFlowItemGenerator(waterflowElement);
    renderNode_->RegisterItemGenerator(std::move(waterFlowItemGenerator));
    renderNode_->RequestWaterFlowFooter();
    double mainSize = 10.0;
    double crossSize = 100.0;
    renderNode_->GetFooterSize(mainSize, crossSize);
    EXPECT_EQ(renderNode_->footerMaxSize_.Width(), crossSize);
    EXPECT_EQ(renderNode_->footerMaxSize_.Height(), mainSize);
}

/**
 * @tc.name: RenderWaterFlowTest_SetFooterPosition_001
 * @tc.desc: Verify the function that value of GetPosition after using SetFooterPosition.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetFooterPosition_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([this]() {
        return renderNode_->flowMatrix_.size() - 1;
    });
    auto waterflowElement = AceType::MakeRefPtr<MockWaterFlowElement>();
    CHECK_RENDERNODE_NULL_VOID(waterflowElement);
    waterflowElement->SetContext(mockContext_);
    WeakPtr<V2::WaterFlowItemGenerator> waterFlowItemGenerator(waterflowElement);
    renderNode_->RegisterItemGenerator(std::move(waterFlowItemGenerator));
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->footerMaxSize_ = Size(150.0, 10.0);
    renderNode_->viewportStartPos_ = 110.0;
    renderNode_->SetFooterPosition();
    EXPECT_TRUE(renderNode_->footer_->GetPosition() == Offset(
        (renderNode_->crossSize_ - renderNode_->footerMaxSize_.Width()) / CENTER_POINT,
        renderNode_->mainSize_ - renderNode_->footerMaxSize_.Height()));
}

/**
 * @tc.name: RenderWaterFlowTest_SetFooterPosition_002
 * @tc.desc: Verify the function that value of GetPosition after using SetFooterPosition.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_SetFooterPosition_002, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto waterflowElement = AceType::MakeRefPtr<MockWaterFlowElement>();
    CHECK_RENDERNODE_NULL_VOID(waterflowElement);
    waterflowElement->SetContext(mockContext_);
    WeakPtr<V2::WaterFlowItemGenerator> waterFlowItemGenerator(waterflowElement);
    renderNode_->RegisterItemGenerator(std::move(waterFlowItemGenerator));
    renderNode_->RequestWaterFlowFooter();
    renderNode_->footerMaxSize_ = Size(150.0, 10.0);
    renderNode_->SetFooterPosition();
    EXPECT_TRUE(renderNode_->footer_->GetPosition() == Offset((renderNode_->crossSize_ - 150) / CENTER_POINT,
        START_POS));
}

/**
 * @tc.name: RenderWaterFlowTest_LayoutFooter_001
 * @tc.desc: Verify the function that value of GetPosition after using LayoutFooter.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_LayoutFooter_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    renderNode_->SetGetTotalCount([this]() {
        return renderNode_->flowMatrix_.size() - 1;
    });
    auto waterflowElement = AceType::MakeRefPtr<MockWaterFlowElement>();
    CHECK_RENDERNODE_NULL_VOID(waterflowElement);
    waterflowElement->SetContext(mockContext_);
    WeakPtr<V2::WaterFlowItemGenerator> waterFlowItemGenerator(waterflowElement);
    renderNode_->RegisterItemGenerator(std::move(waterFlowItemGenerator));
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    renderNode_->viewportStartPos_ = 250.0;
    renderNode_->LayoutFooter();
    EXPECT_TRUE(renderNode_->footer_->GetPosition() == Offset(
        (renderNode_->crossSize_ - renderNode_->footerMaxSize_.Width()) / CENTER_POINT,
        renderNode_->mainSize_ - renderNode_->footerMaxSize_.Height()));
    EXPECT_TRUE(renderNode_->footer_->GetLayoutSize() == Size(renderNode_->footerMaxSize_.Width(),
        renderNode_->footerMaxSize_.Height()));
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastSupplyedIndex_001
 * @tc.desc: Verify the function that return value of GetLastSupplyedIndex.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastSupplyedIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto result = renderNode_->GetLastSupplyedIndex();
    EXPECT_EQ(result, 0);
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    result = renderNode_->GetLastSupplyedIndex();
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: RenderWaterFlowTest_GetNextSupplyedIndex_001
 * @tc.desc: Verify the function that return value of GetNextSupplyedIndex.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetNextSupplyedIndex_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto result = renderNode_->GetNextSupplyedIndex();
    EXPECT_EQ(result, 0);
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    result = renderNode_->GetNextSupplyedIndex();
    EXPECT_EQ(result, 6);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastSupplyedMainSize_001
 * @tc.desc: Verify the function that return value of GetLastSupplyedMainSize.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastSupplyedMainSize_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr");
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    auto result = renderNode_->GetLastSupplyedMainSize();
    EXPECT_EQ(result, 0);
    renderNode_->InitialFlowProp();
    auto itemIndex = renderNode_->GetNextSupplyedIndex();
    auto targetPos = renderNode_->GetTargetPos();
    renderNode_->SupplyItems(itemIndex, targetPos);
    result = renderNode_->GetLastSupplyedMainSize();
    EXPECT_EQ(result, 1100.0);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastMainBlankPos_001
 * @tc.desc: Verify the function that change the return value of the parameter GetLastMainBlankPos.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastMainBlankPos_001, TestSize.Level1)
{
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->mainSideEndPos_.emplace_back(START_POS + i);
    }
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->crossSideSize_.emplace_back(START_POS + i);
    }
    auto result = renderNode_->GetLastMainBlankPos();
    EXPECT_EQ(result.GetY(), START_POS);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastMainBlankPos_002
 * @tc.desc: Verify the function that return value of GetLastMainBlankPos.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastMainBlankPos_002, TestSize.Level1)
{
    const double pos = 100.0;
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->mainSideEndPos_.emplace_back(pos - i);
    }
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->crossSideSize_.emplace_back(pos + i);
    }
    auto result = renderNode_->GetLastMainBlankPos();
    EXPECT_EQ(result.GetY(), pos - CREATE_FLOWITEM_COUNT + 1);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastMainBlankCross_001
 * @tc.desc: Verify the function that return value of GetLastMainBlankCross.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastMainBlankCross_001, TestSize.Level1)
{
    const double pos = 4.0;
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->mainSideEndPos_.emplace_back(pos - i);
    }
    auto result = renderNode_->GetLastMainBlankCross();
    EXPECT_EQ(result, pos);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastMainBlankCross_002
 * @tc.desc: Verify the function that return value of GetLastMainBlankCross.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastMainBlankCross_002, TestSize.Level2)
{
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_TRUE(renderNode_->mainSideEndPos_.empty());
    auto result = renderNode_->GetLastMainBlankCross();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastMainBlankPos_001
 * @tc.desc: Verify the function that change the return value of the parameter GetLastMainPos.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastMainPos_001, TestSize.Level1)
{
    const double pos = 100.0;
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->mainSideEndPos_.emplace_back(pos + i);
    }
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->crossSideSize_.emplace_back(pos + i);
    }
    auto result = renderNode_->GetLastMainPos();
    EXPECT_EQ(result.GetY(), pos + CREATE_FLOWITEM_COUNT - 1);
}

/**
 * @tc.name: RenderWaterFlowTest_GetLastMainBlankPos_002
 * @tc.desc: Verify the function that change the return value of the parameter GetLastMainPos.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_GetLastMainPos_002, TestSize.Level1)
{
    const double pos = 100.0;
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->mainSideEndPos_.emplace_back(pos - i);
    }
    for (size_t i = 0; i < CREATE_FLOWITEM_COUNT; i++) {
        renderNode_->crossSideSize_.emplace_back(pos + i);
    }
    auto result = renderNode_->GetLastMainPos();
    EXPECT_EQ(result.GetY(), pos);
}
} // namespace OHOS::Ace

