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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/interfaces/inner_api/ui_session/mock_ui_session_manager.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

class SwiperTestCore : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_, _)).Times(AnyNumber());
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }
};

} // namespace

/**
 * @tc.name: ContentChangeSwiperStartTest001
 * @tc.desc: Test Swiper phase end keeps active state and explicit termination reports a normal END.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestCore, ContentChangeSwiperStartTest001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto pattern = AceType::MakeRefPtr<SwiperPattern>();
    auto swiperNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 431, pattern, true);
    ASSERT_NE(swiperNode, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    auto paintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateAutoPlay(true);
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER_START, _)).Times(0);
    manager->OnSwiperScrollStart(swiperNode);
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    manager->OnSwiperScrollEnd(swiperNode);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    paintProperty->UpdateAutoPlay(false);
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER_START, _)).Times(1);
    manager->OnSwiperScrollStart(swiperNode);
    manager->OnSwiperScrollStart(swiperNode);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER, _)).Times(0);
    pattern->ContentChangeOnTransitionEnd(swiperNode);
    EXPECT_FALSE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    AnimationCallbackInfo info;
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER, Truly([](const auto& json) {
        auto value = JsonUtil::ParseJsonString(json);
        return value && value->GetString("endReason").empty();
    }))).Times(1);
    pattern->FireAnimationEndEvent(0, info, true);
    manager->OnVsyncEnd(RectF());
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangeTabsStartTest001
 * @tc.desc: Test a Tabs-contained Swiper reports the outer Tabs identity.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestCore, ContentChangeTabsStartTest001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto tabsNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 441, AceType::MakeRefPtr<Pattern>(), true);
    auto pattern = AceType::MakeRefPtr<SwiperPattern>();
    auto swiperNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 442, pattern, true);
    ASSERT_NE(tabsNode, nullptr);
    ASSERT_NE(swiperNode, nullptr);
    tabsNode->AddChild(swiperNode);
    pattern->hasTabsAncestor_ = true;
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager,
        ReportContentChangeEvent(ChangeType::TABS_START, HasSubstr("\"$ID\":441"))).Times(1);
    manager->OnSwiperScrollStart(swiperNode, true);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    AnimationCallbackInfo info;
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS, Truly([](const auto& json) {
        auto value = JsonUtil::ParseJsonString(json);
        return value && value->GetString("endReason").empty();
    }))).Times(1);
    pattern->FireAnimationEndEvent(0, info, true);
    manager->OnVsyncEnd(RectF());
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangeSwiperStartTest002
 * @tc.desc: Test a Swiper returning to its current index closes the START cycle with CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestCore, ContentChangeSwiperStartTest002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto pattern = AceType::MakeRefPtr<SwiperPattern>();
    auto swiperNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 451, pattern, true);
    ASSERT_NE(swiperNode, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER_START, _)).Times(1);
    manager->OnSwiperScrollStart(swiperNode);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    pattern->targetIndex_ = pattern->currentIndex_;
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER_START_CANCEL,
        HasSubstr("\"$ID\":451"))).Times(1);
    pattern->ContentChangeReport(swiperNode, true);
    manager->OnVsyncEnd(RectF());
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangeTabsStartCancelTest001
 * @tc.desc: Test a Tabs transition returning to its current index reports TABS_START_CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestCore, ContentChangeTabsStartCancelTest001, TestSize.Level1)
{
    auto manager = MockPipelineContext::GetCurrent()->GetContentChangeManager();
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto tabsNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 455, AceType::MakeRefPtr<Pattern>(), true);
    auto pattern = AceType::MakeRefPtr<SwiperPattern>();
    auto swiperNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 456, pattern, true);
    ASSERT_NE(tabsNode, nullptr);
    ASSERT_NE(swiperNode, nullptr);
    swiperNode->MountToParent(tabsNode);
    pattern->SetHasTabsAncestor(true);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS_START,
        HasSubstr("\"$ID\":455"))).Times(1);
    manager->OnSwiperScrollStart(swiperNode, true);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    pattern->targetIndex_ = pattern->currentIndex_;
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS_START_CANCEL,
        HasSubstr("\"$ID\":455"))).Times(1);
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS, _)).Times(0);
    pattern->ContentChangeReport(swiperNode, true);
    manager->OnVsyncEnd(RectF());
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS_START,
        HasSubstr("\"$ID\":455"))).Times(1);
    manager->OnSwiperScrollStart(swiperNode, true);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangeNestedSwiperTest001
 * @tc.desc: A Swiper inside TabContent has its own START/END identity and does not suppress Tabs START.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestCore, ContentChangeNestedSwiperTest001, TestSize.Level1)
{
    auto manager = MockPipelineContext::GetCurrent()->GetContentChangeManager();
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);
    auto tabsNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 461, AceType::MakeRefPtr<Pattern>(), true);
    auto tabsPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto tabsSwiper = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 462, tabsPattern, true);
    tabsPattern->SetHasTabsAncestor(true);
    tabsSwiper->MountToParent(tabsNode);
    auto tabContent =
        FrameNode::CreateFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, 463, AceType::MakeRefPtr<Pattern>(), true);
    tabContent->MountToParent(tabsSwiper);
    auto innerPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto innerSwiper = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 464, innerPattern, true);
    innerSwiper->MountToParent(tabContent);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS_START, _)).Times(0);
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER_START, HasSubstr("\"$ID\":464")))
        .Times(1);
    innerPattern->FireScrollStateEvent(ScrollState::SCROLL);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER, _)).Times(1);
    innerPattern->FireScrollStateEvent(ScrollState::IDLE);
    innerPattern->ContentChangeReport(innerSwiper, true);
    manager->OnVsyncEnd(RectF());
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS_START, HasSubstr("\"$ID\":461")))
        .Times(1);
    tabsPattern->FireScrollStateEvent(ScrollState::FLING);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangeTabsCustomTransitionTest001
 * @tc.desc: Custom Tabs transitions report START before the callback and close through the normal END.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestCore, ContentChangeTabsCustomTransitionTest001, TestSize.Level1)
{
    auto manager = MockPipelineContext::GetCurrent()->GetContentChangeManager();
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    for (bool reportStartEvent : { false, true }) {
        ContentChangeConfig config;
        config.reportStartEvent = reportStartEvent;
        manager->StartContentChangeReport(config);
        auto tabsNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, 471, AceType::MakeRefPtr<Pattern>(), true);
        auto pattern = AceType::MakeRefPtr<SwiperPattern>();
        auto swiperNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 472, pattern, true);
        swiperNode->MountToParent(tabsNode);
        pattern->SetHasTabsAncestor(true);
        RefPtr<TabContentTransitionProxy> proxy;
        pattern->SetTabsCustomContentTransition([&](int32_t, int32_t) {
            EXPECT_EQ(manager->activeContentChanges_.empty(), !reportStartEvent);
            return TabContentAnimatedTransition { .timeout = 1000,
                .transition = [&](const RefPtr<TabContentTransitionProxy>& value) { proxy = value; } };
        });

        EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS_START, HasSubstr("\"$ID\":471")))
            .Times(reportStartEvent ? 1 : 0);
        pattern->OnCustomContentTransition(1);
        ASSERT_NE(proxy, nullptr);
        EXPECT_FALSE(manager->IsSwiperScrolling());
        Mock::VerifyAndClearExpectations(mockUiSessionManager);

        EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS, _)).Times(1);
        proxy->FinishTransition();
        manager->OnVsyncEnd(RectF());
        EXPECT_TRUE(manager->activeContentChanges_.empty());
        EXPECT_FALSE(manager->IsContentChanging());
        Mock::VerifyAndClearExpectations(mockUiSessionManager);
        manager->StopContentChangeReport();
    }
}

} // namespace OHOS::Ace::NG
