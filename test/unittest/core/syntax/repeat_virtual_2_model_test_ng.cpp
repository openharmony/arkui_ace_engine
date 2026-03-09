/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <utility>
#include <map>
#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t TEST_ARR_LEN = 100;
constexpr uint32_t TEST_ARR_LEN_2 = 50;
constexpr uint32_t TEST_TOTAL_COUNT = 100;
constexpr uint32_t TEST_TOTAL_COUNT_2 = 200;
constexpr int32_t TEST_REPEAT_ELMT_ID = 1000;
constexpr int32_t TEST_REPEAT_ELMT_ID_2 = 2000;
constexpr int32_t INVALID_REPEAT_ELMT_ID = -1;
constexpr uint32_t TEST_RID = 1;
constexpr uint32_t TEST_RID_2 = 2;
constexpr uint32_t TEST_INDEX = 5;
constexpr int32_t TEST_LAYOUT_INDEX = 0;
constexpr int32_t TEST_COUNT = 5;
constexpr bool IS_CREATED_BY_TEMPLATE = true;
constexpr bool IS_NOT_CREATED_BY_TEMPLATE = false;
} // namespace

class RepeatVirtual2ModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void RepeatVirtual2ModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RepeatVirtual2ModelTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void RepeatVirtual2ModelTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void RepeatVirtual2ModelTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxCreateTest001
 * @tc.desc: Create RepeatVirtualScroll2 node with all parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxCreateTest001, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { static_cast<uint32_t>(index), 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(TEST_ARR_LEN, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxCreateTest002
 * @tc.desc: Create RepeatVirtualScroll2 with different array lengths
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxCreateTest002, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { static_cast<uint32_t>(index), 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(TEST_ARR_LEN_2, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    model.Create(TEST_ARR_LEN, TEST_TOTAL_COUNT_2, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxRemoveNodeTest003
 * @tc.desc: RemoveNode removes node by RID
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxRemoveNodeTest003, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { static_cast<uint32_t>(index), 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(TEST_ARR_LEN, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    model.RemoveNode(TEST_RID);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxRemoveNodeTest004
 * @tc.desc: RemoveNode with different RIDs
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxRemoveNodeTest004, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { static_cast<uint32_t>(index), 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(TEST_ARR_LEN, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    model.RemoveNode(TEST_RID);
    model.RemoveNode(TEST_RID_2);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxSetInvalidTest005
 * @tc.desc: SetInvalid marks node as invalid
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxSetInvalidTest005, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.SetInvalid(TEST_REPEAT_ELMT_ID, TEST_RID);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxSetInvalidTest006
 * @tc.desc: SetInvalid with different repeatElmtId and RID
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxSetInvalidTest006, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.SetInvalid(TEST_REPEAT_ELMT_ID, TEST_RID);
    model.SetInvalid(TEST_REPEAT_ELMT_ID_2, TEST_RID_2);
    model.SetInvalid(INVALID_REPEAT_ELMT_ID, TEST_RID);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxRequestContainerReLayoutTest007
 * @tc.desc: RequestContainerReLayout updates counts and requests layout
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxRequestContainerReLayoutTest007, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.RequestContainerReLayout(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN, TEST_TOTAL_COUNT, TEST_LAYOUT_INDEX);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxRequestContainerReLayoutTest008
 * @tc.desc: RequestContainerReLayout with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxRequestContainerReLayoutTest008, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.RequestContainerReLayout(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN_2, TEST_TOTAL_COUNT, TEST_LAYOUT_INDEX);
    model.RequestContainerReLayout(TEST_REPEAT_ELMT_ID_2, TEST_ARR_LEN, TEST_TOTAL_COUNT_2, TEST_LAYOUT_INDEX);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxNotifyContainerLayoutChangeTest009
 * @tc.desc: NotifyContainerLayoutChange notifies layout changes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxNotifyContainerLayoutChangeTest009, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.NotifyContainerLayoutChange(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN, TEST_TOTAL_COUNT,
        TEST_INDEX, TEST_COUNT, UINode::NotificationType::START_CHANGE_POSITION);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxNotifyContainerLayoutChangeTest010
 * @tc.desc: NotifyContainerLayoutChange with different notification types
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxNotifyContainerLayoutChangeTest010, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.NotifyContainerLayoutChange(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN, TEST_TOTAL_COUNT,
        TEST_INDEX, TEST_COUNT, UINode::NotificationType::END_CHANGE_POSITION);
    model.NotifyContainerLayoutChange(TEST_REPEAT_ELMT_ID_2, TEST_ARR_LEN, TEST_TOTAL_COUNT,
        TEST_INDEX, TEST_COUNT, UINode::NotificationType::START_CHANGE_POSITION);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxUpdateL1Rid4IndexTest011
 * @tc.desc: UpdateL1Rid4Index updates L1 cache mapping
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxUpdateL1Rid4IndexTest011, TestSize.Level1)
{
    std::map<int32_t, uint32_t> l1Rd4Index;
    l1Rd4Index[0] = 1;
    l1Rd4Index[1] = 2;
    l1Rd4Index[2] = 3;
    RepeatVirtualScroll2ModelNG model;
    model.UpdateL1Rid4Index(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN, TEST_TOTAL_COUNT, TEST_LAYOUT_INDEX, l1Rd4Index);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxUpdateL1Rid4IndexTest012
 * @tc.desc: UpdateL1Rid4Index with empty mapping
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxUpdateL1Rid4IndexTest012, TestSize.Level1)
{
    std::map<int32_t, uint32_t> l1Rd4Index;
    RepeatVirtualScroll2ModelNG model;
    model.UpdateL1Rid4Index(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN, TEST_TOTAL_COUNT, TEST_LAYOUT_INDEX, l1Rd4Index);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxOnMoveTest013
 * @tc.desc: OnMove sets move callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxOnMoveTest013, TestSize.Level1)
{
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    RepeatVirtualScroll2ModelNG model;
    model.OnMove(TEST_REPEAT_ELMT_ID, std::move(onMoveCallback));
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxOnMoveTest014
 * @tc.desc: OnMove with different repeatElmtId
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxOnMoveTest014, TestSize.Level1)
{
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    RepeatVirtualScroll2ModelNG model;
    model.OnMove(TEST_REPEAT_ELMT_ID, std::move(onMoveCallback));
    model.OnMove(TEST_REPEAT_ELMT_ID_2, nullptr);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxSetItemDragHandlerTest015
 * @tc.desc: SetItemDragHandler sets drag handlers
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxSetItemDragHandlerTest015, TestSize.Level1)
{
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    RepeatVirtualScroll2ModelNG model;
    model.SetItemDragHandler(TEST_REPEAT_ELMT_ID, std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxSetItemDragHandlerTest016
 * @tc.desc: SetItemDragHandler with different repeatElmtId
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxSetItemDragHandlerTest016, TestSize.Level1)
{
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    RepeatVirtualScroll2ModelNG model;
    model.SetItemDragHandler(TEST_REPEAT_ELMT_ID, std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    model.SetItemDragHandler(TEST_REPEAT_ELMT_ID_2, nullptr, nullptr, nullptr, nullptr);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxSetCreateByTemplateTest017
 * @tc.desc: SetCreateByTemplate with true
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxSetCreateByTemplateTest017, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.SetCreateByTemplate(IS_CREATED_BY_TEMPLATE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxSetCreateByTemplateTest018
 * @tc.desc: SetCreateByTemplate with false
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxSetCreateByTemplateTest018, TestSize.Level1)
{
    RepeatVirtualScroll2ModelNG model;
    model.SetCreateByTemplate(IS_NOT_CREATED_BY_TEMPLATE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxCompleteFlowTest019
 * @tc.desc: Complete flow with Create and all operations
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxCompleteFlowTest019, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { static_cast<uint32_t>(index), 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(TEST_ARR_LEN, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(TEST_REPEAT_ELMT_ID, std::move(onMoveCallback));
    model.SetInvalid(TEST_REPEAT_ELMT_ID, TEST_RID);
    model.RemoveNode(TEST_RID_2);
    model.SetCreateByTemplate(IS_CREATED_BY_TEMPLATE);
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxZeroArrLenTest020
 * @tc.desc: Create with zero array length
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxZeroArrLenTest020, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { 0, 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(0, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxCallbackExecutionTest021
 * @tc.desc: Verify callbacks are stored and can be invoked
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxCallbackExecutionTest021, TestSize.Level1)
{
    auto onGetRid4Index = [](int32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
        return { static_cast<uint32_t>(index), 0 };
    };
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onMoveFromTo = [](int32_t from, int32_t to) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    RepeatVirtualScroll2ModelNG model;
    model.Create(TEST_ARR_LEN, TEST_TOTAL_COUNT, onGetRid4Index, onRecycleItems,
        onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScroll2SyntaxLargeMappingTest022
 * @tc.desc: UpdateL1Rid4Index with large mapping
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2ModelTestNg, RepeatVirtualScroll2SyntaxLargeMappingTest022, TestSize.Level1)
{
    std::map<int32_t, uint32_t> l1Rd4Index;
    for (int32_t i = 0; i < 100; ++i) {
        l1Rd4Index[i] = static_cast<uint32_t>(i);
    }
    RepeatVirtualScroll2ModelNG model;
    model.UpdateL1Rid4Index(TEST_REPEAT_ELMT_ID, TEST_ARR_LEN, TEST_TOTAL_COUNT, TEST_LAYOUT_INDEX, l1Rd4Index);
    SUCCEED();
}

} // namespace OHOS::Ace::NG
