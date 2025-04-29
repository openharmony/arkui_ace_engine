/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/common/recorder/event_recorder.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_model.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

class NavigatorEventHubTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

namespace OHOS::Ace::NG {
namespace {
const int32_t NAVIGATOR_TYPE_OUTSIDE_DEFINE = 1001;
} // namespace

/**
 * @tc.name: GetNavigatorType001
 * @tc.desc: Test GetNavigatorType.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, GetNavigatorType001, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::PUSH);
    std::string ret = navigatorEventHub.GetNavigatorType();

    EXPECT_EQ(ret, "NavigationType.Push");
}

/**
 * @tc.name: GetNavigatorType002
 * @tc.desc: Test GetNavigatorType.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, GetNavigatorType002, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::BACK);
    std::string ret = navigatorEventHub.GetNavigatorType();

    EXPECT_EQ(ret, "NavigationType.Back");
}

/**
 * @tc.name: GetNavigatorType003
 * @tc.desc: Test GetNavigatorType.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, GetNavigatorType003, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::DEFAULT);
    std::string ret = navigatorEventHub.GetNavigatorType();

    EXPECT_EQ(ret, "NavigationType.Default");
}

/**
 * @tc.name: GetNavigatorType004
 * @tc.desc: Test GetNavigatorType.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, GetNavigatorType004, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::REPLACE);
    std::string ret = navigatorEventHub.GetNavigatorType();

    EXPECT_EQ(ret, "NavigationType.Replace");
}

/**
 * @tc.name: GetNavigatorType005
 * @tc.desc: Test GetNavigatorType and enter switch default.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, GetNavigatorType005, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType(NAVIGATOR_TYPE_OUTSIDE_DEFINE));
    std::string ret = navigatorEventHub.GetNavigatorType();

    EXPECT_EQ(ret, "NavigationType.Push");
}

/**
 * @tc.name: NavigatePage001
 * @tc.desc: Test NavigatePage.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage001, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::PUSH);
    navigatorEventHub.NavigatePage();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: NavigatePage002
 * @tc.desc: Test NavigatePage.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage002, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::REPLACE);
    navigatorEventHub.NavigatePage();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: NavigatePage003
 * @tc.desc: Test NavigatePage.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage003, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::BACK);
    navigatorEventHub.NavigatePage();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: NavigatePage004
 * @tc.desc: Test NavigatePage.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage004, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::DEFAULT);
    navigatorEventHub.NavigatePage();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: NavigatePage005
 * @tc.desc: Test NavigatePage and don't enter IsComponentRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage005, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::PUSH);
    // Make IsComponentRecordEnable return false.
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    navigatorEventHub.NavigatePage();

    EXPECT_FALSE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
}

/**
 * @tc.name: NavigatePage006
 * @tc.desc: Test NavigatePage, enter IsComponentRecordEnable and don't enter host.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage006, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::PUSH);
    // Make IsComponentRecordEnable return true.
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    // Make host NULL.
    navigatorEventHub.AttachHost(nullptr);
    navigatorEventHub.NavigatePage();

    EXPECT_TRUE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
    EXPECT_EQ(navigatorEventHub.GetFrameNode(), nullptr);
}

/**
 * @tc.name: NavigatePage007
 * @tc.desc: Test NavigatePage, enter IsComponentRecordEnable and enter host.
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorEventHubTestNg, NavigatePage007, TestSize.Level1)
{
    NavigatorEventHub navigatorEventHub;
    navigatorEventHub.SetType(NavigatorType::PUSH);
    // Make IsComponentRecordEnable return true.
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    // Make host not NULL.
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    navigatorEventHub.AttachHost(frameNode);
    navigatorEventHub.NavigatePage();

    EXPECT_TRUE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
    EXPECT_NE(navigatorEventHub.GetFrameNode(), nullptr);
}
} // namespace OHOS::Ace::NG
