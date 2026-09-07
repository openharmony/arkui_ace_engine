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

#include "lazy_grid_layout_test.h"

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

class LazyGridPatternVisibleIndexesTest : public LazyGridLayoutTest {
public:
    void SetUp() override
    {
        LazyGridLayoutTest::SetUp();
        pattern_ = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    }
    void TearDown() override
    {
        LazyGridLayoutTest::TearDown();
    }
};

/**
 * @tc.name: GetVisibleIndexesRangeForCallback001
 * @tc.desc: Test when layoutInfo_ is null
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback001, TestSize.Level1)
{
    pattern_->layoutInfo_ = nullptr; // nullptr ： layoutInfo_ 置空
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback002
 * @tc.desc: Test when totalItemCount is 0
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback002, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 0; // 0 ： totalItemCount_ 为0
    pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_
    pattern_->layoutInfo_->visibleEndIndex_ = 5; // 5 ： visibleEndIndex_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback003
 * @tc.desc: Test when totalItemCount is negative
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback003, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = -1; // -1 ： totalItemCount_ 为负数
    pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_
    pattern_->layoutInfo_->visibleEndIndex_ = 5; // 5 ： visibleEndIndex_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback004
 * @tc.desc: Test when visibleStartIndex_ is negative
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback004, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = -1; // -1 ： visibleStartIndex_ 为负数
    pattern_->layoutInfo_->visibleEndIndex_ = 5; // 5 ： visibleEndIndex_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback005
 * @tc.desc: Test when visibleEndIndex_ is negative
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback005, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_
    pattern_->layoutInfo_->visibleEndIndex_ = -1; // -1 ： visibleEndIndex_ 为负数
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback006
 * @tc.desc: Test when both visibleStartIndex_ and visibleEndIndex_ are negative
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback006, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = -1; // -1 ： visibleStartIndex_ 为负数
    pattern_->layoutInfo_->visibleEndIndex_ = -1; // -1 ： visibleEndIndex_ 为负数
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback007
 * @tc.desc: Test when visibleStartIndex_ >= totalItemCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback007, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 10; // 10 ： visibleStartIndex_ 等于totalItemCount_
    pattern_->layoutInfo_->visibleEndIndex_ = 9; // 9 ： visibleEndIndex_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback008
 * @tc.desc: Test when visibleEndIndex_ >= totalItemCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback008, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 5; // 5 ： visibleStartIndex_
    pattern_->layoutInfo_->visibleEndIndex_ = 10; // 10 ： visibleEndIndex_ 等于totalItemCount_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback009
 * @tc.desc: Test when both visibleStartIndex_ and visibleEndIndex_ >= totalItemCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback009, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 15; // 15 ： visibleStartIndex_ 超出totalItemCount_
    pattern_->layoutInfo_->visibleEndIndex_ = 20; // 20 ： visibleEndIndex_ 超出totalItemCount_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback010
 * @tc.desc: Test valid range with visibleStartIndex_ and visibleEndIndex_ within bounds
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback010, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 20; // 20 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_ 从头开始
    pattern_->layoutInfo_->visibleEndIndex_ = 9; // 9 ： visibleEndIndex_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 9);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback011
 * @tc.desc: Test valid range in the middle of items
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback011, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 50; // 50 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 10; // 10 ： visibleStartIndex_ 中间位置
    pattern_->layoutInfo_->visibleEndIndex_ = 25; // 25 ： visibleEndIndex_ 中间位置
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 10);
    EXPECT_EQ(result.second, 25);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback012
 * @tc.desc: Test valid range at the end of items
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback012, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 30; // 30 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 20; // 20 ： visibleStartIndex_ 靠近末尾
    pattern_->layoutInfo_->visibleEndIndex_ = 29; // 29 ： visibleEndIndex_ 末尾项
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 20);
    EXPECT_EQ(result.second, 29);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback013
 * @tc.desc: Test single visible item (start equals end)
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback013, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 5; // 5 ： visibleStartIndex_
    pattern_->layoutInfo_->visibleEndIndex_ = 5; // 5 ： visibleEndIndex_ 等于start，单项可见
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 5);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback014
 * @tc.desc: Test boundary where visibleStartIndex_ equals totalItemCount - 1
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback014, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 9; // 9 ： visibleStartIndex_ 等于totalItemCount_-1
    pattern_->layoutInfo_->visibleEndIndex_ = 9; // 9 ： visibleEndIndex_ 等于totalItemCount_-1
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 9);
    EXPECT_EQ(result.second, 9);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback015
 * @tc.desc: Test boundary where visibleStartIndex_ is 0 and visibleEndIndex_ is totalItemCount - 1
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback015, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 10; // 10 ： totalItemCount_
    pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_ 从头开始
    pattern_->layoutInfo_->visibleEndIndex_ = 9; // 9 ： visibleEndIndex_ 等于totalItemCount_-1
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 9);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback016
 * @tc.desc: Test with totalItemCount of 1 and single visible item
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback016, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 1; // 1 ： totalItemCount_ 仅1项
    pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_
    pattern_->layoutInfo_->visibleEndIndex_ = 0; // 0 ： visibleEndIndex_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback017
 * @tc.desc: Test visibleStartIndex_ at boundary equal to totalItemCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback017, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = 1; // 1 ： totalItemCount_ 仅1项
    pattern_->layoutInfo_->visibleStartIndex_ = 1; // 1 ： visibleStartIndex_ 等于totalItemCount_
    pattern_->layoutInfo_->visibleEndIndex_ = 1; // 1 ： visibleEndIndex_ 等于totalItemCount_
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: GetVisibleIndexesRangeForCallback018
 * @tc.desc: Test negative visibleStartIndex_ takes precedence even with negative totalItemCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback018, TestSize.Level1)
{
    pattern_->layoutInfo_->totalItemCount_ = -5; // -5 ： totalItemCount_ 为负数
    pattern_->layoutInfo_->visibleStartIndex_ = -1; // -1 ： visibleStartIndex_ 为负数
    pattern_->layoutInfo_->visibleEndIndex_ = -1; // -1 ： visibleEndIndex_ 为负数
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

class LazyGridPatternFireVisibleIndexesTest : public LazyGridLayoutTest {
public:
    void SetUp() override
    {
        LazyGridLayoutTest::SetUp();
        pattern_ = AceType::MakeRefPtr<LazyGridLayoutPattern>();
        pattern_->layoutInfo_->totalItemCount_ = 20; // 20 ： totalItemCount_
        pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_
        pattern_->layoutInfo_->visibleEndIndex_ = 9; // 9 ： visibleEndIndex_
    }
    void TearDown() override
    {
        LazyGridLayoutTest::TearDown();
    }
};

/**
 * @tc.name: FireOnVisibleIndexesChange001
 * @tc.desc: Test FireOnVisibleIndexesChange(range) with null callback, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange001, TestSize.Level1)
{
    pattern_->onVisibleIndexesChange_ = nullptr; // nullptr ： onVisibleIndexesChange_ 置空
    auto range = std::make_pair(0, 9); // 0,9 ： range (start=0, end=9)
    pattern_->FireOnVisibleIndexesChange(range);
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, false);
}

/**
 * @tc.name: FireOnVisibleIndexesChange002
 * @tc.desc: Test FireOnVisibleIndexesChange(range) first invocation, callback should fire
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange002, TestSize.Level1)
{
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        capturedStart = start;
        capturedEnd = end;
    });
    auto range = std::make_pair(0, 9); // 0,9 ： range (start=0, end=9)
    pattern_->FireOnVisibleIndexesChange(range);
    EXPECT_EQ(capturedStart, 0);
    EXPECT_EQ(capturedEnd, 9);
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, true);
    EXPECT_EQ(pattern_->lastVisibleIndexesRange_, range);
}

/**
 * @tc.name: FireOnVisibleIndexesChange003
 * @tc.desc: Test FireOnVisibleIndexesChange(range) same range after first fire, should be suppressed
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange003, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
    });
    auto range = std::make_pair(0, 9); // 0,9 ： range (start=0, end=9)
    pattern_->FireOnVisibleIndexesChange(range);
    EXPECT_EQ(callCount, 1);
    pattern_->FireOnVisibleIndexesChange(range);
    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: FireOnVisibleIndexesChange004
 * @tc.desc: Test FireOnVisibleIndexesChange(range) different range after first fire, should fire again
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange004, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange(std::make_pair(0, 9)); // 0,9 ： 第一次range
    EXPECT_EQ(callCount, 1);
    pattern_->FireOnVisibleIndexesChange(std::make_pair(5, 15)); // 5,15 ： 第二次range（不同）
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(capturedStart, 5);
    EXPECT_EQ(capturedEnd, 15);
    EXPECT_EQ(pattern_->lastVisibleIndexesRange_, std::make_pair(5, 15));
}

/**
 * @tc.name: FireOnVisibleIndexesChange005
 * @tc.desc: Test FireOnVisibleIndexesChange(range) with {-1,-1} first, then valid range
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange005, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange(std::make_pair(-1, -1)); // -1,-1 ： 无效range
    EXPECT_EQ(callCount, 1);
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
    pattern_->FireOnVisibleIndexesChange(std::make_pair(0, 9)); // 0,9 ： 有效range（不同）
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(capturedStart, 0);
    EXPECT_EQ(capturedEnd, 9);
}

/**
 * @tc.name: FireOnVisibleIndexesChange006
 * @tc.desc: Test FireOnVisibleIndexesChange(range) with valid range first, then {-1,-1}
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange006, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange(std::make_pair(0, 9)); // 0,9 ： 有效range
    EXPECT_EQ(callCount, 1);
    pattern_->FireOnVisibleIndexesChange(std::make_pair(-1, -1)); // -1,-1 ： 无效range（不同）
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
}

/**
 * @tc.name: FireOnVisibleIndexesChange007
 * @tc.desc: Test FireOnVisibleIndexesChange(range) duplicate {-1,-1} should be suppressed
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange007, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
    });
    pattern_->FireOnVisibleIndexesChange(std::make_pair(-1, -1)); // -1,-1 ： 无效range
    EXPECT_EQ(callCount, 1);
    pattern_->FireOnVisibleIndexesChange(std::make_pair(-1, -1)); // -1,-1 ： 重复无效range
    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: FireOnVisibleIndexesChange008
 * @tc.desc: Test FireOnVisibleIndexesChange() no-arg with null callback, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange008, TestSize.Level1)
{
    pattern_->onVisibleIndexesChange_ = nullptr; // nullptr ： onVisibleIndexesChange_ 置空
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, false);
}

/**
 * @tc.name: FireOnVisibleIndexesChange009
 * @tc.desc: Test FireOnVisibleIndexesChange() no-arg delegates to GetVisibleIndexesRangeForCallback
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange009, TestSize.Level1)
{
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(capturedStart, 0);
    EXPECT_EQ(capturedEnd, 9);
}

/**
 * @tc.name: FireOnVisibleIndexesChange010
 * @tc.desc: Test FireOnVisibleIndexesChange() no-arg with null layoutInfo_, delegates {-1,-1}
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange010, TestSize.Level1)
{
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->layoutInfo_ = nullptr; // nullptr ： layoutInfo_ 置空
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
}

/**
 * @tc.name: FireOnVisibleIndexesChange011
 * @tc.desc: Test FireOnVisibleIndexesChange() no-arg with invalid visible indexes, delegates {-1,-1}
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange011, TestSize.Level1)
{
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->layoutInfo_->visibleStartIndex_ = -1; // -1 ： visibleStartIndex_ 为负数
    pattern_->layoutInfo_->visibleEndIndex_ = -1; // -1 ： visibleEndIndex_ 为负数
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
}

/**
 * @tc.name: FireOnVisibleIndexesChange012
 * @tc.desc: Test FireOnVisibleIndexesChange() no-arg consecutive same range is suppressed
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange012, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
    });
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(callCount, 1);
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: FireOnVisibleIndexesChange013
 * @tc.desc: Test FireOnVisibleIndexesChange() no-arg with changed visible range fires again
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange013, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(callCount, 1);
    pattern_->layoutInfo_->visibleStartIndex_ = 5; // 5 ： visibleStartIndex_ 变更后
    pattern_->layoutInfo_->visibleEndIndex_ = 15; // 15 ： visibleEndIndex_ 变更后
    pattern_->FireOnVisibleIndexesChange();
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(capturedStart, 5);
    EXPECT_EQ(capturedEnd, 15);
}

/**
 * @tc.name: FireOnVisibleIndexesChange014
 * @tc.desc: Test FireOnVisibleIndexesChange(range) multiple range transitions
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange014, TestSize.Level1)
{
    std::vector<std::pair<int32_t, int32_t>> captured;
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        captured.emplace_back(start, end);
    });
    pattern_->FireOnVisibleIndexesChange(std::make_pair(0, 4)); // 0,4 ： 第一个range
    pattern_->FireOnVisibleIndexesChange(std::make_pair(0, 4)); // 0,4 ： 重复range，被抑制
    pattern_->FireOnVisibleIndexesChange(std::make_pair(3, 8)); // 3,8 ： 第二个range（不同）
    pattern_->FireOnVisibleIndexesChange(std::make_pair(3, 8)); // 3,8 ： 重复range，被抑制
    pattern_->FireOnVisibleIndexesChange(std::make_pair(-1, -1)); // -1,-1 ： 第三个range（无效）
    pattern_->FireOnVisibleIndexesChange(std::make_pair(-1, -1)); // -1,-1 ： 重复range，被抑制
    ASSERT_EQ(captured.size(), 3u);
    EXPECT_EQ(captured[0], std::make_pair(0, 4));
    EXPECT_EQ(captured[1], std::make_pair(3, 8));
    EXPECT_EQ(captured[2], std::make_pair(-1, -1));
}

/**
 * @tc.name: FireOnVisibleIndexesChange015
 * @tc.desc: Test lastVisibleIndexesRange_ and hasVisibleIndexesChangeFired_ state after first fire
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange015, TestSize.Level1)
{
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->lastVisibleIndexesRange_ = { -1, -1 }; // -1,-1 ： lastVisibleIndexesRange_ 初始值
    pattern_->SetOnVisibleIndexesChange([](int32_t, int32_t) {});
    auto range = std::make_pair(2, 7); // 2,7 ： range (start=2, end=7)
    pattern_->FireOnVisibleIndexesChange(range);
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, true);
    EXPECT_EQ(pattern_->lastVisibleIndexesRange_, range);
}

/**
 * @tc.name: FireOnVisibleIndexesChange016
 * @tc.desc: Test hasVisibleIndexesChangeFired_=false allows callback even if lastVisibleIndexesRange_ matches
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternFireVisibleIndexesTest, FireOnVisibleIndexesChange016, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    auto range = std::make_pair(0, 9); // 0,9 ： range (start=0, end=9)
    pattern_->lastVisibleIndexesRange_ = range;
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
    });
    pattern_->FireOnVisibleIndexesChange(range);
    EXPECT_EQ(callCount, 1);
}

class LazyGridPatternOnInActiveTest : public LazyGridLayoutTest {
public:
    void SetUp() override
    {
        LazyGridLayoutTest::SetUp();
        pattern_ = AceType::MakeRefPtr<LazyGridLayoutPattern>();
        pattern_->layoutInfo_->totalItemCount_ = 20; // 20 ： totalItemCount_
        pattern_->layoutInfo_->visibleStartIndex_ = 0; // 0 ： visibleStartIndex_
        pattern_->layoutInfo_->visibleEndIndex_ = 9; // 9 ： visibleEndIndex_
    }
    void TearDown() override
    {
        LazyGridLayoutTest::TearDown();
    }
};

/**
 * @tc.name: OnInActive001
 * @tc.desc: Test OnInActive with null callback, should not crash
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive001, TestSize.Level1)
{
    pattern_->onVisibleIndexesChange_ = nullptr; // nullptr ： onVisibleIndexesChange_ 置空
    pattern_->OnInActive();
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, false);
}

/**
 * @tc.name: OnInActive002
 * @tc.desc: Test OnInActive fires callback with {-1,-1}
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive002, TestSize.Level1)
{
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->OnInActive();
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
    EXPECT_EQ(pattern_->lastVisibleIndexesRange_, std::make_pair(-1, -1));
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, true);
}

/**
 * @tc.name: OnInActive003
 * @tc.desc: Test OnInActive after previous FireOnVisibleIndexesChange with valid range
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive003, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->FireOnVisibleIndexesChange(std::make_pair(0, 9)); // 0,9 ： 有效range
    EXPECT_EQ(callCount, 1);
    EXPECT_EQ(capturedStart, 0);
    pattern_->OnInActive();
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
}

/**
 * @tc.name: OnInActive004
 * @tc.desc: Test OnInActive after previous OnInActive (duplicate {-1,-1} suppressed)
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive004, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
    });
    pattern_->OnInActive();
    EXPECT_EQ(callCount, 1);
    pattern_->OnInActive();
    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: OnInActive005
 * @tc.desc: Test OnInActive then FireOnVisibleIndexesChange with valid range fires again
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive005, TestSize.Level1)
{
    int32_t callCount = 0; // 0 ： callCount 初始值
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        callCount++;
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->OnInActive();
    EXPECT_EQ(callCount, 1);
    EXPECT_EQ(capturedStart, -1);
    pattern_->FireOnVisibleIndexesChange(std::make_pair(3, 12)); // 3,12 ： 有效range（不同）
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(capturedStart, 3);
    EXPECT_EQ(capturedEnd, 12);
}

/**
 * @tc.name: OnInActive006
 * @tc.desc: Test OnInActive resets lastVisibleIndexesRange_ to {-1,-1}
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive006, TestSize.Level1)
{
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->SetOnVisibleIndexesChange([](int32_t, int32_t) {});
    pattern_->FireOnVisibleIndexesChange(std::make_pair(5, 10)); // 5,10 ： 有效range
    EXPECT_EQ(pattern_->lastVisibleIndexesRange_, std::make_pair(5, 10));
    pattern_->OnInActive();
    EXPECT_EQ(pattern_->lastVisibleIndexesRange_, std::make_pair(-1, -1));
}

/**
 * @tc.name: OnInActive007
 * @tc.desc: Test OnInActive with callback set but hasVisibleIndexesChangeFired_ already false
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternOnInActiveTest, OnInActive007, TestSize.Level1)
{
    int32_t capturedStart = -2; // -2 ： capturedStart 初始值
    int32_t capturedEnd = -2; // -2 ： capturedEnd 初始值
    pattern_->hasVisibleIndexesChangeFired_ = false; // false ： hasVisibleIndexesChangeFired_ 未触发
    pattern_->lastVisibleIndexesRange_ = { -1, -1 }; // -1,-1 ： lastVisibleIndexesRange_ 初始值
    pattern_->SetOnVisibleIndexesChange([&](int32_t start, int32_t end) {
        capturedStart = start;
        capturedEnd = end;
    });
    pattern_->OnInActive();
    EXPECT_EQ(capturedStart, -1);
    EXPECT_EQ(capturedEnd, -1);
    EXPECT_EQ(pattern_->hasVisibleIndexesChangeFired_, true);
}

} // namespace OHOS::Ace::NG
