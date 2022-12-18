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
#define protect public
#include "core/components_ng/pattern/stage/page_pattern.h"
#undef protect
#undef private

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class PagePatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void PagePatternTest::SetUpTestCase() {}
void PagePatternTest::TearDownTestCase() {}
void PagePatternTest::SetUp() {}
void PagePatternTest::TearDown() {}

bool TmpBool()
{
    return true;
}

void TmpVoid()
{
    return;
}

/**
 * @tc.name: PagePatternTestTest001
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest001, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    manager_.OnAttachToFrameNode();
    manager_.ProcessHideState();
    manager_.ProcessShowState();
    manager_.BuildSharedTransitionMap();
}

/**
 * @tc.name: PagePatternTestTest002
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest002, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    manager_.OnShow();
    manager_.OnHide();
}

/**
 * @tc.name: PagePatternTestTest003
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest003, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    manager_.OnHide();
}

/**
 * @tc.name: PagePatternTestTest004
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest004, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    auto ret1 = manager_.IsMeasureBoundary();
    EXPECT_EQ(ret1, true);
    auto ret2 = manager_.IsAtomicNode();
    EXPECT_EQ(ret2, false);
    auto ret3 = manager_.GetPageInfo();
    EXPECT_EQ(ret3, nullptr);
}

/**
 * @tc.name: PagePatternTestTest005
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest005, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    auto ret1 = manager_.OnBackPressed();
    EXPECT_EQ(ret1, false);
}

/**
 * @tc.name: PagePatternTestTest006
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest006, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    std::function<bool()> OnBackPressed = TmpBool;
    auto ret1 = manager_.OnBackPressed();
    EXPECT_EQ(ret1, false);
}

/**
 * @tc.name: PagePatternTestTest007
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest007, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    std::function<void()> onPageShow = TmpVoid;
    std::function<void()> onPageHide = TmpVoid;
    std::function<void()> pageTransitionFunc = TmpVoid;
    manager_.SetOnPageShow(std::move(onPageShow));
    manager_.SetOnPageHide(std::move(onPageShow));
    manager_.SetPageTransitionFunc(std::move(onPageShow));
}

/**
 * @tc.name: PagePatternTestTest008
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest008, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    RefPtr<EventHub> eventHub;
    auto ret = manager_.CreateEventHub();
    EXPECT_NE(ret, eventHub);
}

/**
 * @tc.name: PagePatternTestTest009
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest09, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    auto ret = manager_.GetSharedTransitionMap();
    EXPECT_EQ(ret, manager_.sharedTransitionMap_);
}

/**
 * @tc.name: PagePatternTestTest010
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest010, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    DirtySwapConfig dirtySwapConfig;
    auto ret = manager_.OnDirtyLayoutWrapperSwap(NULL, dirtySwapConfig);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: PagePatternTestTest011
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest011, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    const std::function<void()> onFinish = TmpVoid;
    auto ret = manager_.TriggerPageTransition(PageTransitionType::ENTER, TmpVoid);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: PagePatternTestTest012
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest012, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    const RefPtr<PageTransitionEffect> effect;
    manager_.AddPageTransition(effect);
    manager_.ClearPageTransitionEffect();
}

/**
 * @tc.name: PagePatternTestTest013
 * @tc.desc: Test all the properties of PagePatternTest
 * @tc.type: FUNC
 */
HWTEST_F(PagePatternTest, PagePatternTest013, TestSize.Level1)
{
    const RefPtr<PageInfo> pageInfo;
    PagePattern manager_(pageInfo);
    auto ret = manager_.GetTopTransition();
    EXPECT_EQ(ret, nullptr);
}
} // namespace OHOS::Ace::NG