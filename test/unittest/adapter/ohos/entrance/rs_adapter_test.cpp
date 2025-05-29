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
#define private public
#define protected public
#include "adapter/ohos/entrance/rs_adapter.h"
#include "base/utils/system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RsAdapterTest : public testing::Test {
public:
    static bool multiInstanceEnabledSaved_;

    static void SetUpTestSuite()
    {
        RsAdapterTest::multiInstanceEnabledSaved_ = SystemProperties::GetMultiInstanceEnabled();
    }
    static void TearDownTestSuite()
    {
        SystemProperties::SetMultiInstanceEnabled(RsAdapterTest::multiInstanceEnabledSaved_);
    }
    void SetUp() {};
    void TearDown() {};
};

bool RsAdapterTest::multiInstanceEnabledSaved_ = false;

/**
 * @tc.name: RsUIDirectorInit001
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsUIDirectorInit001, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption);;

    SystemProperties::SetMultiInstanceEnabled(false);
    RsAdapter::RsUIDirectorInit(rsUiDirector, window, "");

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_EQ(rsUiDirector->GetRSUIContext(), nullptr);
#endif
}

/**
 * @tc.name: RsUIDirectorInit002
 * @tc.desc: Test RsAdapterTest
 * @tc.type: FUNC
 */
HWTEST_F(RsAdapterTest, RsUIDirectorInit002, TestSize.Level1)
{
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::Create("test", windowOption);;

    SystemProperties::SetMultiInstanceEnabled(true);
    RsAdapter::RsUIDirectorInit(rsUiDirector, window, "");

    EXPECT_NE(rsUiDirector, nullptr);
    EXPECT_NE(rsUiDirector->GetRSUIContext(), nullptr);
#endif
}

} // namespace OHOS::Ace::NG