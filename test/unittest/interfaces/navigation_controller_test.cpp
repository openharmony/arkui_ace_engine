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

#include "gtest/gtest.h"

#include "interfaces/inner_api/ace/navigation_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t VALUE = 0;
} // namespace

class NavigationControllerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: NavigationController001
 * @tc.desc: Test IsNavDestinationInTopStack function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationControllerTest, NavigationController001, TestSize.Level1)
{
    std::shared_ptr<NavigationController> navigationController = std::make_shared<NavigationController>();
    ASSERT_NE(navigationController, nullptr);
    EXPECT_EQ(navigationController->IsNavDestinationInTopStack(), false);
}

/**
 * @tc.name: NavigationController002
 * @tc.desc: Test GetTopHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationControllerTest, NavigationController002, TestSize.Level1)
{
    std::shared_ptr<NavigationController> navigationController = std::make_shared<NavigationController>();
    ASSERT_NE(navigationController, nullptr);
    EXPECT_EQ(navigationController->GetTopHandle(), VALUE);
}

/**
 * @tc.name: NavigationController003
 * @tc.desc: Test SetInPIPMode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationControllerTest, NavigationController003, TestSize.Level1)
{
    std::shared_ptr<NavigationController> navigationController = std::make_shared<NavigationController>();
    ASSERT_NE(navigationController, nullptr);
    int32_t handle = 1;
    navigationController->SetInPIPMode(handle);
}

/**
 * @tc.name: NavigationController004
 * @tc.desc: Test PopInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationControllerTest, NavigationController004, TestSize.Level1)
{
    std::shared_ptr<NavigationController> navigationController = std::make_shared<NavigationController>();
    ASSERT_NE(navigationController, nullptr);
    bool destroy = true;
    navigationController->PopInPIP(destroy);
}

/**
 * @tc.name: NavigationController005
 * @tc.desc: Test PushInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationControllerTest, NavigationController005, TestSize.Level1)
{
    std::shared_ptr<NavigationController> navigationController = std::make_shared<NavigationController>();
    ASSERT_NE(navigationController, nullptr);
    int32_t handle = 1;
    navigationController->PushInPIP(handle);
}

/**
 * @tc.name: NavigationController006
 * @tc.desc: Test DeletePIPMode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationControllerTest, NavigationController006, TestSize.Level1)
{
    std::shared_ptr<NavigationController> navigationController = std::make_shared<NavigationController>();
    ASSERT_NE(navigationController, nullptr);
    int32_t handle = 1;
    navigationController->DeletePIPMode(handle);
}
} // namespace OHOS::Ace