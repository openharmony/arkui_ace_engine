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

namespace OHOS::Ace::NG {

namespace {
} // namespace

class ListScrollVisibleContentTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: OnScrollVisibleContentChange001
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange001, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 100
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(100);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 1 }));
    EXPECT_TRUE(IsEqual(endInfo, { 4 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange003
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange002, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 200
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 2 }));
    EXPECT_TRUE(IsEqual(endInfo, { 5 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange003
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange003, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 300
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(300);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 3 }));
    EXPECT_TRUE(IsEqual(endInfo, { 6 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange004
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange004, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 400
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(400);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange005
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange005, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 500
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 5 }));
    EXPECT_TRUE(IsEqual(endInfo, { 8 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange006
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange006, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 600
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(600);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 6 }));
    EXPECT_TRUE(IsEqual(endInfo, { 9 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange007
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange007, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 700
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(700);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 7 }));
    EXPECT_TRUE(IsEqual(endInfo, { 10 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange008
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange008, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 800
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(800);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 8 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange009
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange009, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 900
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(900);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 9 }));
    EXPECT_TRUE(IsEqual(endInfo, { 12 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange010
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange010, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 1000
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1000);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 10 }));
    EXPECT_TRUE(IsEqual(endInfo, { 13 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange011
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange011, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to 1100
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1100);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 11 }));
    EXPECT_TRUE(IsEqual(endInfo, { 14 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange012
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange012, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange013
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange013, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 100
     * @tc.expected: startBottom.index = 1
     */
    pattern_->ScrollTo(100);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 1 }));
    EXPECT_TRUE(IsEqual(endInfo, { 4 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange014
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange014, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 200
     * @tc.expected: endTop.index = 5
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 1 }));
    EXPECT_TRUE(IsEqual(endInfo, { 5 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange015
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange015, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 300
     * @tc.expected: startBottom.index = 2
     */
    pattern_->ScrollTo(300);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 2 }));
    EXPECT_TRUE(IsEqual(endInfo, { 6 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange016
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange016, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 400
     * @tc.expected: startBottom.index = 3
     */
    pattern_->ScrollTo(400);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 3 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange017
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange017, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 500
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 8 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange018
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange018, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 600
     * @tc.expected: startBottom.index = 5
     */
    pattern_->ScrollTo(600);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 5 }));
    EXPECT_TRUE(IsEqual(endInfo, { 9 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange019
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange019, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 700
     * @tc.expected: startBottom.index = 6
     */
    pattern_->ScrollTo(700);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 6 }));
    EXPECT_TRUE(IsEqual(endInfo, { 9 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange020
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange020, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 800
     * @tc.expected: startBottom.index = 7
     */
    pattern_->ScrollTo(800);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 7 }));
    EXPECT_TRUE(IsEqual(endInfo, { 10 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange021
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange021, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 900
     * @tc.expected: startBottom.index = 8
     */
    pattern_->ScrollTo(900);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 8 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange022
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange022, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 1000
     * @tc.expected: startBottom.index = 10
     */
    pattern_->ScrollTo(1100);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 10 }));
    EXPECT_TRUE(IsEqual(endInfo, { 13 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange023
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange023, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to 1300
     * @tc.expected: startBottom.index = 11
     */
    pattern_->ScrollTo(1300);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 11 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange024
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollVisibleContentTestNg, OnScrollVisibleContentChange024, TestSize.Level1)
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
    CreateListItems(20);
    CreateDone(frameNode_);

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

     /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

} // namespace OHOS::Ace::NG
