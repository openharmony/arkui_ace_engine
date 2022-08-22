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

#include <string>
#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/test/json/component_factory.h"
#include "core/components/web/web_component.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class WebComponentTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

protected:
};

void WebComponentTest::SetUpTestCase() {}

void WebComponentTest::TearDownTestCase() {}

void WebComponentTest::SetUp() {}

void WebComponentTest::TearDown() {}

/**
 * @tc.name: WebComponentTest_001
 * @tc.desc: Test create message port.
 * @tc.type: FUNC
 * @tc.require: I5KYNK
 */
HWTEST_F(WebComponentTest, WebComponentTest_001, TestSize.Level1)
{
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    EXPECT_NE(webController, nullptr);
    webController->SetCreateMsgPortsImpl([](std::vector<RefPtr<WebMessagePort>>& ports) {});
    EXPECT_NE(webController->createMsgPortsImpl_, nullptr);
}

/**
 * @tc.name: WebComponentTest_002
 * @tc.desc: Test save store web archive.
 * @tc.type: FUNC
 * @tc.require: I5J1GW
 */
HWTEST_F(WebComponentTest, WebComponentTest_002, TestSize.Level1)
{
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    EXPECT_NE(webController, nullptr);
    webController->SetClearMatchesImpl([]() {});
    EXPECT_NE(webController->clearMatchesImpl_, nullptr);
}

/**
 * @tc.name: WebComponentTest_003
 * @tc.desc: Test find api in web.
 * @tc.type: FUNC
 * @tc.require: I5K4NJ
 */
HWTEST_F(WebComponentTest, WebComponentTest_003, TestSize.Level1)
{
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    EXPECT_NE(webController, nullptr);
    webController->SetSearchAllAsyncImpl([](const std::string& searchStr) {});
    EXPECT_NE(webController->searchAllAsyncImpl_, nullptr);
}
} // namespace OHOS::Ace