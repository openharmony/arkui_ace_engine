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

#include <memory>

#include "gtest/gtest.h"
#include "base/memory/referenced.h"
#include "base/test/mock/mock_container.h"
#include "base/test/mock/mock_subwindow_ohos.h"
#include "base/subwindow/subwindow_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

const std::string TEST_STRING = "";
const int32_t TEST_INT_TEAM_ONE = 1;
const int32_t TEST_INT_TEAM_TWO = 2;
const int32_t TEST_INT_TEAM_THREE = 3;
const bool TEST_BOOL = true;

} // namespace

class SubwindowManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SubwindowManagerTest::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "SubwindowManagerTest SetUpTestCase";
}

void SubwindowManagerTest::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "SubwindowManagerTest TearDownTestCase";
}

void SubwindowManagerTest::SetUp()
{
    GTEST_LOG_(INFO) << "SubwindowManagerTest SetUp";
}

void SubwindowManagerTest::TearDown()
{
    GTEST_LOG_(INFO) << "SubwindowManagerTest TearDown";
}

/**
 * @tc.name: Subwindow_Manager_ShowToast_001
 * @tc.desc: Call ShowToast interface when Subwindow is null.
 * @tc.type: FUNC
 * @tc.require: RM017
 * @tc.author: Wutm
 */
HWTEST_F(SubwindowManagerTest, Subwindow_Manager_ShowToast_001, TestSize.Level1)
{
    Container::SetCurrentId(TEST_INT_TEAM_ONE);
    std::shared_ptr<SubwindowManager> subwindowm = SubwindowManager::GetInstance();
    subwindowm->ShowToast(TEST_STRING, TEST_INT_TEAM_ONE, TEST_STRING);
    auto resultPtr = subwindowm->GetSubwindow(TEST_INT_TEAM_ONE);
    ASSERT_TRUE(resultPtr != nullptr);
}

/**
 * @tc.name: Subwindow_Manager_ShowToast_002
 * @tc.desc: Call ShowToast interface when Subwindow is not null.
 * @tc.type: FUNC
 * @tc.require: RM017
 * @tc.author: Wutm
 */
HWTEST_F(SubwindowManagerTest, Subwindow_Manager_ShowToast_002, TestSize.Level1)
{
    std::shared_ptr<SubwindowManager> subwindowm = SubwindowManager::GetInstance();
    subwindowm->ShowToast(TEST_STRING, TEST_INT_TEAM_ONE, TEST_STRING);
    auto resultPtr = subwindowm->GetSubwindow(TEST_INT_TEAM_ONE);
    ASSERT_TRUE(resultPtr != nullptr);
}

/**
 * @tc.name: Subwindow_Manager_ShowDialog_001
 * @tc.desc: Call ShowDialog interface when Subwindow is null.
 * @tc.type: FUNC
 * @tc.require: RM017
 * @tc.author: Wutm
 */
HWTEST_F(SubwindowManagerTest, Subwindow_Manager_ShowDialog_001, TestSize.Level1)
{
    Container::SetCurrentId(TEST_INT_TEAM_TWO);
    std::shared_ptr<SubwindowManager> subwindowm = SubwindowManager::GetInstance();
    std::vector<ButtonInfo> buttons;
    std::set<std::string> callbacks;
    auto callback = [](int32_t callbackType, int32_t successType) {};
    subwindowm->ShowDialog(TEST_STRING, TEST_STRING, buttons, TEST_BOOL, callback, callbacks);
    auto resultPtr = subwindowm->GetSubwindow(TEST_INT_TEAM_TWO);
    ASSERT_TRUE(resultPtr != nullptr);
}

/**
 * @tc.name: Subwindow_Manager_ShowDialog_002
 * @tc.desc: Call ShowDialog interface when Subwindow is not null.
 * @tc.type: FUNC
 * @tc.require: RM017
 * @tc.author: Wutm
 */
HWTEST_F(SubwindowManagerTest, Subwindow_Manager_ShowDialog_002, TestSize.Level1)
{
    std::shared_ptr<SubwindowManager> subwindowm = SubwindowManager::GetInstance();
    std::vector<ButtonInfo> buttons;
    std::set<std::string> callbacks;
    auto callback = [](int32_t callbackType, int32_t successType) {};
    subwindowm->ShowDialog(TEST_STRING, TEST_STRING, buttons, TEST_BOOL, callback, callbacks);
    auto resultPtr = subwindowm->GetSubwindow(TEST_INT_TEAM_TWO);
    ASSERT_TRUE(resultPtr != nullptr);
}

/**
 * @tc.name: Subwindow_Manager_ShowActionMenu_001
 * @tc.desc: Call ShowActionMenu interface when Subwindow is null.
 * @tc.type: FUNC
 * @tc.require: RM017
 * @tc.author: Wutm
 */
HWTEST_F(SubwindowManagerTest, Subwindow_Manager_ShowActionMenu_001, TestSize.Level1)
{
    Container::SetCurrentId(TEST_INT_TEAM_THREE);
    std::shared_ptr<SubwindowManager> subwindowm = SubwindowManager::GetInstance();
    std::vector<ButtonInfo> buttons;
    auto callback = [](int32_t callbackType, int32_t successType) {};
    subwindowm->ShowActionMenu(TEST_STRING, buttons, callback);
    auto resultPtr = subwindowm->GetSubwindow(TEST_INT_TEAM_THREE);
    ASSERT_TRUE(resultPtr != nullptr);
}

/**
 * @tc.name: Subwindow_Manager_ShowActionMenu_002
 * @tc.desc: Call ShowActionMenu interface when Subwindow is null.
 * @tc.type: FUNC
 * @tc.require: RM017
 * @tc.author: Wutm
 */
HWTEST_F(SubwindowManagerTest, Subwindow_Manager_ShowActionMenu_002, TestSize.Level1)
{
    std::shared_ptr<SubwindowManager> subwindowm = SubwindowManager::GetInstance();
    std::vector<ButtonInfo> buttons;
    auto callback = [](int32_t callbackType, int32_t successType) {};
    subwindowm->ShowActionMenu(TEST_STRING, buttons, callback);
    auto resultPtr = subwindowm->GetSubwindow(TEST_INT_TEAM_THREE);
    ASSERT_TRUE(resultPtr != nullptr);
}
} // namespace OHOS::Ace
