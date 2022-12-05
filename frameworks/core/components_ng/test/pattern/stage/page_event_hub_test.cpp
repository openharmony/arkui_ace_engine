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
#include "core/components_ng/pattern/stage/page_event_hub.h"
#undef protect
#undef private
#include <string>
#include <map>
#include <memory>

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class PageEventHubTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    PageEventHub manager_;
};

void PageEventHubTest::SetUpTestCase() {}
void PageEventHubTest::TearDownTestCase() {}
void PageEventHubTest::SetUp() {}
void PageEventHubTest::TearDown() {}

/**
 * @tc.name: PageEventHubTest001
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest001, TestSize.Level1)
{
    string group = "123";
    int32_t radioId = 1;
    manager_.AddRadioToGroup(group, radioId);
    manager_.RemoveRadioFromGroup(group, radioId);
}

/**
 * @tc.name: PageEventHubTest002
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest002, TestSize.Level1)
{
    string group = "123";
    int32_t radioId = 1;
    manager_.AddRadioToGroup(group, radioId);
    auto ret = manager_.HasRadioId(group, radioId);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: PageEventHubTest003
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest003, TestSize.Level1)
{
    string group = "123";
    int32_t radioId = 1;
    manager_.AddRadioToGroup(group, radioId);
    manager_.UpdateRadioGroupValue(group, radioId);
}

/**
 * @tc.name: PageEventHubTest004
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest004, TestSize.Level1)
{
    string group = "123";
    int32_t radioId = 1;
    int32_t radioId1 = 2;
    manager_.AddRadioToGroup(group, radioId);
    manager_.UpdateRadioGroupValue(group, radioId1);
}

/**
 * @tc.name: PageEventHubTest005
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest005, TestSize.Level1)
{
    string group = "123";
    int32_t checkboxId = 1;
    manager_.AddCheckBoxToGroup(group, checkboxId);
    manager_.RemoveCheckBoxFromGroup(group, checkboxId);
}

/**
 * @tc.name: PageEventHubTest006
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest006, TestSize.Level1)
{
    string group = "123";
    int32_t checkboxId = 1;
    manager_.AddCheckBoxToGroup(group, checkboxId);
    manager_.AddCheckBoxGroupToGroup(group, checkboxId);
}

/**
 * @tc.name: PageEventHubTest007
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest007, TestSize.Level1)
{
    string group = "123";
    int32_t checkboxId = 1;
    int32_t checkboxId1 = 2;
    manager_.AddCheckBoxToGroup(group, checkboxId);
    manager_.AddCheckBoxGroupToGroup(group, checkboxId1);
}

/**
 * @tc.name: PageEventHubTest008
 * @tc.desc: Test all the properties of PageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(PageEventHubTest, PageEventHubTest008, TestSize.Level1)
{
    string group = "123";
    int32_t checkboxId = 1;
    int32_t checkboxId1 = 2;
    manager_.AddCheckBoxToGroup(group, checkboxId);
    auto ret = manager_.GetCheckBoxGroupMap();
    manager_.AddCheckBoxToGroup(group, checkboxId1);
    auto ret1 = manager_.GetCheckBoxGroupMap();
    EXPECT_NE(ret, ret1);
}
} // namespace OHOS::Ace::NG