/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {
class SwiperUIObserverTestNg : public SwiperTestNg {};

/**
 * GetShownItemInfo Test case design
    | index   | displayCount | totalCount | isLoop | size |
    | ------- | ------------ | ---------- | ------ | ---- |
    | 0       | 1            | 4          | x      | 1    |
    | -1      | 1            | 4          | x      | 0    |
    | 1000000 | 1            | 4          | x      | 0    |
    | 0       | 2            | 4          | x      | 2    |
    | 3       | 2            | 4          | false  | 1    |
    | 3       | 2            | 4          | true   | 2    |
    | 0       | 1000000      | 4          | x      | 4    |
 * @tc.name: GetShownItemInfoTest001
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUIObserverTestNg, GetShownItemInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct swiper from table above and do assert.
     */
    const int32_t totalCount = 4;
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(totalCount);
    CreateSwiperDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(0).size(), 1);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(-1).size(), 0);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(1000000).size(), 0);
}

/**
 * @tc.name: GetShownItemInfoTest002
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUIObserverTestNg, GetShownItemInfoTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct swiper from table above and do assert.
     */
    const int32_t totalCount = 4;
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(totalCount);
    CreateSwiperDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(0).size(), 1);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(-1).size(), 0);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(1000000).size(), 0);
}

/**
 * @tc.name: GetShownItemInfoTest003
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUIObserverTestNg, GetShownItemInfoTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct swiper from table above and do assert.
     */
    const int32_t displayCount = 2;
    const int32_t totalCount = 4;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetSwipeByGroup(false);
    model.SetLoop(false);
    CreateSwiperItems(totalCount);
    CreateSwiperDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(0).size(), displayCount);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(totalCount - 1).size(), 1);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(-1).size(), 0);
}

/**
 * @tc.name: GetShownItemInfoTest004
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUIObserverTestNg, GetShownItemInfoTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct swiper from table above and do assert.
     */
    const int32_t displayCount = 2;
    const int32_t totalCount = 4;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetSwipeByGroup(false);
    model.SetLoop(true);
    CreateSwiperItems(totalCount);
    CreateSwiperDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(0).size(), displayCount);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(totalCount - 1).size(), displayCount);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(-1).size(), 0);
}

/**
 * @tc.name: GetShownItemInfoTest005
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUIObserverTestNg, GetShownItemInfoTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct swiper from table above and do assert.
     */
    const int32_t displayCount = 1000000;
    const int32_t totalCount = 4;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetSwipeByGroup(false);
    model.SetLoop(false);
    CreateSwiperItems(totalCount);
    CreateSwiperDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(0).size(), totalCount);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(totalCount - 1).size(), 1);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(-1).size(), 0);
}

/**
 * @tc.name: GetShownItemInfoTest006
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUIObserverTestNg, GetShownItemInfoTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct swiper from table above and do assert.
     */
    const int32_t displayCount = 1000000;
    const int32_t totalCount = 4;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetSwipeByGroup(false);
    model.SetLoop(true);
    CreateSwiperItems(totalCount);
    CreateSwiperDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(0).size(), totalCount);
    ASSERT_EQ(pattern_->GetShownItemInfoFromIndex(-1).size(), 0);
}
}