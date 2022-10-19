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
 * @tc.name: RenderWaterFlowTest_AnimateTo_001
 * @tc.desc: Verify AnimateTo setting duration.
 * @tc.type: FUNC
 * @tc.require: issueI5TFPO
 */
HWTEST_F(RenderWaterFlowTest, RenderWaterFlowTest_AnimateTo_001, TestSize.Level1)
{
    CreateRenderWaterFlow("1fr 1fr", "1fr 1fr", FlexDirection::COLUMN, CREATE_FLOWITEM_COUNT);
    CHECK_RENDERNODE_NULL_VOID(renderNode_);
    EXPECT_TRUE(renderNode_->animator_ != nullptr);
    float duration = 100.0;
    auto result = renderNode_->AnimateTo(100.0_px, duration, nullptr);
    CHECK_RENDERNODE_NULL_VOID(renderNode_->animator_);
    EXPECT_TRUE(result);
    EXPECT_EQ(renderNode_->animator_->GetDuration(), duration);
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
} // namespace OHOS::Ace
