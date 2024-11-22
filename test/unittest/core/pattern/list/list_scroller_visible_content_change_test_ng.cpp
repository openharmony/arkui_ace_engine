/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "list_test_ng.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"

namespace OHOS::Ace::NG {
class ListScrollVisibleContentChangeTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: OnScrollVisibleContentChange001
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 10
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    pattern_->ScrollTo(10);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 10);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 20
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    pattern_->ScrollTo(20);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 30
     * @tc.cases: endChanged == true and startChanged ==  indexChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(30);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 40
     * @tc.expected: endExpect.index = 1
     */
    pattern_->ScrollTo(40);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange002
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 20
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    pattern_->ScrollTo(20);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 40
     * @tc.cases: startChanged == indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = -1
     */
    pattern_->ScrollTo(40);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 60
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(60);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 80
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(80);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 80);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange003
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 30
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    pattern_->ScrollTo(30);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    pattern_->ScrollTo(60);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 90
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(90);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 90);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(120);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange004
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 40
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    pattern_->ScrollTo(40);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 80
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(80);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 80);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    pattern_->ScrollTo(120);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 160
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    pattern_->ScrollTo(160);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 160);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange005
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 50
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    startExpect = { 0, 1, 0 };
    pattern_->ScrollTo(50);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 100
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(100);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 150
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    pattern_->ScrollTo(150);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 150);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 200
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 1, 3, -1 };
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 200);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange006
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    startExpect = { 0, 1, 0 };
    pattern_->ScrollTo(60);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 120
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(120);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 180
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: endExpect.indexInGroup = -1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 1, 3, -1 };
    pattern_->ScrollTo(180);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 240
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 2, 2, -1 };
    pattern_->ScrollTo(240);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 240);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange007
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 10
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: startExpect.index = 0
     */
    startExpect = { 0, 2, -1 };
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(10);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 10);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 20
     * @tc.cases: startChanged == indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = -1
     */
    pattern_->ScrollTo(20);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 30
     * @tc.cases: startChanged == endChanged == indexChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    pattern_->ScrollTo(30);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 40
     * @tc.expected: endExpect.index = 1
     */
    pattern_->ScrollTo(40);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange008
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 20
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: startExpect.index = 0
     */
    startExpect = { 0, 2, -1 };
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(20);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 40
     * @tc.cases: startChanged == indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = -1
     */
    pattern_->ScrollTo(40);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    pattern_->ScrollTo(60);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 80
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(80);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 80);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange009
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 30
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: startExpect.index = 0
     */
    startExpect = { 0, 2, -1 };
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(30);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    pattern_->ScrollTo(60);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 90
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(90);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 90);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(120);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange010
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 40
     * @tc.cases: indexChanged == false startChanged == endChanged == true
     * @tc.expected: startExpect.index = 0
     */
    startExpect = { 0, 2, -1 };
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(40);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 80
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(80);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 80);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    pattern_->ScrollTo(120);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 160
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    pattern_->ScrollTo(160);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 160);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange011
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 50
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.index = 0
     */
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(50);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 100
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(100);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 150
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    pattern_->ScrollTo(150);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 150);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 200
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 1, 3, -1 };
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 200);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: OnScrollVisibleContentChange012
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChange012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    startExpect = { 0, 1, 0 };
    endExpect = { 1, 1, 1 };
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 60
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.index = 0
     */
    endExpect = { 1, 1, 0 };
    pattern_->ScrollTo(60);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 120
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(120);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 180
     * @tc.cases: startChanged == endChanged == true and indexChanged == false
     * @tc.expected: endExpect.indexInGroup = -1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 1, 3, -1 };
    pattern_->ScrollTo(180);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 240
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 2, 2, -1 };
    pattern_->ScrollTo(240);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 240);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: ContentClip001
 * @tc.desc: Test ContentClip
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, ContentClip001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);

    paintProperty_->UpdateContentClip({ ContentClipMode::DEFAULT, nullptr });
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetPaddingRect()))).Times(1);
    FlushLayoutTask(frameNode_);

    paintProperty_->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetFrameRect()))).Times(1);
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG