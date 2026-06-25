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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t API_VERSION_BELOW_TWENTY_SIX = 25;
const int32_t API_VERSION_TWENTY_SIX = 26;
const int32_t INVALID_INDEX = -1;
const int32_t VALID_INDEX = 0;
const int32_t VALID_AREA = 1;
const int32_t VALID_INDEX_IN_GROUP = 2;
}

class ListScrollVisibleContentChangeTestNg : public ListTestNg {};

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
    CreateDone();
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 10
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    ScrollTo(10);
    EXPECT_EQ(pattern_->GetTotalOffset(), 10);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 20
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    ScrollTo(20);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 30
     * @tc.cases: endChanged == true and startChanged ==  indexChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 0 };
    ScrollTo(30);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 40
     * @tc.expected: endExpect.index = 1
     */
    ScrollTo(40);
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
    CreateDone();
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 20
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    ScrollTo(20);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 40
     * @tc.cases: startChanged == indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = -1
     */
    ScrollTo(40);
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
    ScrollTo(60);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 80
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(80);
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
    CreateDone();
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 30
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    ScrollTo(30);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    ScrollTo(60);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 90
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(90);
    EXPECT_EQ(pattern_->GetTotalOffset(), 90);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(120);
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
    CreateDone();
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 40
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    ScrollTo(40);
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
    ScrollTo(80);
    EXPECT_EQ(pattern_->GetTotalOffset(), 80);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    ScrollTo(120);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 160
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    ScrollTo(160);
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
    CreateDone();
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
    ScrollTo(50);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 100
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(100);
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 150
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    ScrollTo(150);
    EXPECT_EQ(pattern_->GetTotalOffset(), 150);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 200
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 1, 3, -1 };
    ScrollTo(200);
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
    CreateDone();
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
    ScrollTo(60);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 120
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(120);
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
    ScrollTo(180);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 240
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 2, 2, -1 };
    ScrollTo(240);
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
    CreateDone();
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
    ScrollTo(10);
    EXPECT_EQ(pattern_->GetTotalOffset(), 10);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 20
     * @tc.cases: startChanged == indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = -1
     */
    ScrollTo(20);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 30
     * @tc.cases: startChanged == endChanged == indexChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    ScrollTo(30);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 40
     * @tc.expected: endExpect.index = 1
     */
    ScrollTo(40);
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
    CreateDone();
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
    ScrollTo(20);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 40
     * @tc.cases: startChanged == indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = -1
     */
    ScrollTo(40);
    EXPECT_EQ(pattern_->GetTotalOffset(), 40);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: endExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    ScrollTo(60);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 80
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(80);
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
    CreateDone();
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
    ScrollTo(30);
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    ScrollTo(60);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 90
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(90);
    EXPECT_EQ(pattern_->GetTotalOffset(), 90);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(120);
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
    CreateDone();
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
    ScrollTo(40);
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
    ScrollTo(80);
    EXPECT_EQ(pattern_->GetTotalOffset(), 80);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    ScrollTo(120);
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 160
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    ScrollTo(160);
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
    CreateDone();
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
    ScrollTo(50);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 100
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(100);
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 150
     * @tc.cases: endChanged == indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 1
     */
    ScrollTo(150);
    EXPECT_EQ(pattern_->GetTotalOffset(), 150);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 200
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 1, 3, -1 };
    ScrollTo(200);
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
    CreateDone();
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
    ScrollTo(60);
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 120
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    endExpect = { 1, 1, 1 };
    ScrollTo(120);
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
    ScrollTo(180);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 240
     * @tc.expected: endExpect.index = 1
     */
    endExpect = { 2, 2, -1 };
    ScrollTo(240);
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
    CreateDone();

    paintProperty_->UpdateContentClip({ ContentClipMode::DEFAULT, nullptr });
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetPaddingRect()))).Times(1);
    FlushUITasks();

    paintProperty_->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetFrameRect()))).Times(1);
    FlushUITasks();
}

/**
 * @tc.name: ContentClip002
 * @tc.desc: Test ContentClip
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, ContentClip002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone();

    PaddingProperty padding;
    padding.top = CalcLength(100);
    padding.bottom = CalcLength(100);
    layoutProperty_->UpdatePadding(padding);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(RectF(0, 100, WIDTH, HEIGHT - 200)))).Times(1);
    FlushUITasks();

    PaddingProperty padding0;
    layoutProperty_->UpdatePadding(padding0);
    EXPECT_CALL(*ctx, ResetContentClip()).Times(1);
    FlushUITasks();
}

/**
 * @tc.name: UpdateStartListItemIndex001
 * @tc.desc: Test UpdateStartListItemIndex when list is empty and API version below VERSION_TWENTY_SIX
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, UpdateStartListItemIndex001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_BELOW_TWENTY_SIX);
    ListModelNG model = CreateList();
    CreateDone();
    
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildTrueTotalCount(), 0);
    
    pattern_->startInfo_ = { VALID_INDEX, VALID_AREA, VALID_INDEX_IN_GROUP };
    bool result = pattern_->UpdateStartListItemIndex();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->startInfo_.index, VALID_INDEX);
    EXPECT_EQ(pattern_->startInfo_.area, VALID_AREA);
    EXPECT_EQ(pattern_->startInfo_.indexInGroup, VALID_INDEX_IN_GROUP);
}

/**
 * @tc.name: UpdateStartListItemIndex002
 * @tc.desc: Test UpdateStartListItemIndex when list is empty, API version >= VERSION_TWENTY_SIX and startInfo is -1
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, UpdateStartListItemIndex002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_TWENTY_SIX);
    ListModelNG model = CreateList();
    CreateDone();
    
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildTrueTotalCount(), 0);
    
    pattern_->startInfo_ = { INVALID_INDEX, INVALID_INDEX, INVALID_INDEX };
    bool result = pattern_->UpdateStartListItemIndex();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->startInfo_.index, INVALID_INDEX);
    EXPECT_EQ(pattern_->startInfo_.area, INVALID_INDEX);
    EXPECT_EQ(pattern_->startInfo_.indexInGroup, INVALID_INDEX);
}

/**
 * @tc.name: UpdateStartListItemIndex003
 * @tc.desc: Test UpdateStartListItemIndex when list is empty, API version >= VERSION_TWENTY_SIX and startInfo needs
 * reset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, UpdateStartListItemIndex003, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_TWENTY_SIX);
    ListModelNG model = CreateList();
    CreateDone();
    
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildTrueTotalCount(), 0);
    
    pattern_->startInfo_ = { VALID_INDEX, VALID_AREA, VALID_INDEX_IN_GROUP };
    bool result = pattern_->UpdateStartListItemIndex();
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->startInfo_.index, INVALID_INDEX);
    EXPECT_EQ(pattern_->startInfo_.area, INVALID_INDEX);
    EXPECT_EQ(pattern_->startInfo_.indexInGroup, INVALID_INDEX);
}

/**
 * @tc.name: UpdateEndListItemIndex001
 * @tc.desc: Test UpdateEndListItemIndex when list is empty and API version below VERSION_TWENTY_SIX
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, UpdateEndListItemIndex001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_BELOW_TWENTY_SIX);
    ListModelNG model = CreateList();
    CreateDone();
    
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildTrueTotalCount(), 0);
    
    pattern_->endInfo_ = { VALID_INDEX, VALID_AREA, VALID_INDEX_IN_GROUP };
    bool result = pattern_->UpdateEndListItemIndex();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->endInfo_.index, VALID_INDEX);
    EXPECT_EQ(pattern_->endInfo_.area, VALID_AREA);
    EXPECT_EQ(pattern_->endInfo_.indexInGroup, VALID_INDEX_IN_GROUP);
}

/**
 * @tc.name: UpdateEndListItemIndex002
 * @tc.desc: Test UpdateEndListItemIndex when list is empty, API version >= VERSION_TWENTY_SIX and endInfo is -1
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, UpdateEndListItemIndex002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_TWENTY_SIX);
    ListModelNG model = CreateList();
    CreateDone();
    
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildTrueTotalCount(), 0);
    
    pattern_->endInfo_ = { INVALID_INDEX, INVALID_INDEX, INVALID_INDEX };
    bool result = pattern_->UpdateEndListItemIndex();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->endInfo_.index, INVALID_INDEX);
    EXPECT_EQ(pattern_->endInfo_.area, INVALID_INDEX);
    EXPECT_EQ(pattern_->endInfo_.indexInGroup, INVALID_INDEX);
}

/**
 * @tc.name: UpdateEndListItemIndex003
 * @tc.desc: Test UpdateEndListItemIndex when list is empty, API version >= VERSION_TWENTY_SIX and endInfo needs reset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, UpdateEndListItemIndex003, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_TWENTY_SIX);
    ListModelNG model = CreateList();
    CreateDone();
    
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetChildTrueTotalCount(), 0);
    
    pattern_->endInfo_ = { VALID_INDEX, VALID_AREA, VALID_INDEX_IN_GROUP };
    bool result = pattern_->UpdateEndListItemIndex();
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->endInfo_.index, INVALID_INDEX);
    EXPECT_EQ(pattern_->endInfo_.area, INVALID_INDEX);
    EXPECT_EQ(pattern_->endInfo_.indexInGroup, INVALID_INDEX);
}

/**
 * @tc.name: OnScrollVisibleContentChangeWithEmptyList001
 * @tc.desc: Test OnScrollVisibleContentChange with empty list when API version < VERSION_TWENTY_SIX
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChangeWithEmptyList001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_BELOW_TWENTY_SIX);
    
    ListItemIndex startInfo, endInfo;
    bool callbackTriggered = false;
    auto onVisibleChange = [&startInfo, &endInfo, &callbackTriggered](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
        callbackTriggered = true;
    };
    
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateDone();
    
    EXPECT_FALSE(callbackTriggered);
    EXPECT_EQ(startInfo.index, INVALID_INDEX);
    EXPECT_EQ(endInfo.index, INVALID_INDEX);
}

/**
 * @tc.name: OnScrollVisibleContentChangeWithEmptyList002
 * @tc.desc: Test OnScrollVisibleContentChange with empty list when API version >= VERSION_TWENTY_SIX and info reset
 * needed
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentChangeTestNg, OnScrollVisibleContentChangeWithEmptyList002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_TWENTY_SIX);
    
    ListItemIndex startInfo, endInfo;
    bool callbackTriggered = false;
    auto onVisibleChange = [&startInfo, &endInfo, &callbackTriggered](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
        callbackTriggered = true;
    };
    
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateDone();
    
    EXPECT_FALSE(callbackTriggered);
    EXPECT_EQ(startInfo.index, INVALID_INDEX);
    EXPECT_EQ(endInfo.index, INVALID_INDEX);
    
    pattern_->startInfo_ = { VALID_INDEX, VALID_AREA, VALID_INDEX_IN_GROUP };
    pattern_->endInfo_ = { VALID_INDEX, VALID_AREA, VALID_INDEX_IN_GROUP };
    pattern_->OnScrollVisibleContentChange(eventHub_, false);
    
    EXPECT_TRUE(callbackTriggered);
    EXPECT_EQ(startInfo.index, INVALID_INDEX);
    EXPECT_EQ(startInfo.area, INVALID_INDEX);
    EXPECT_EQ(startInfo.indexInGroup, INVALID_INDEX);
    EXPECT_EQ(endInfo.index, INVALID_INDEX);
    EXPECT_EQ(endInfo.area, INVALID_INDEX);
    EXPECT_EQ(endInfo.indexInGroup, INVALID_INDEX);
}
} // namespace OHOS::Ace::NG