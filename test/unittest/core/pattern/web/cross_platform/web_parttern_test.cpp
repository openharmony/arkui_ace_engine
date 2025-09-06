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

#include "frameworks/core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace::NG {

class WebPatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

// static
void WebPatternTest::SetUpTestCase() {}
// static
void WebPatternTest::TearDownTestCase() {}

void WebPatternTest::SetUp() {}
void WebPatternTest::TearDown() {}

class MockWebDelegateCross : public WebDelegateCross {
public:
    MOCK_METHOD(void, UpdateWebDebuggingAccess, (bool isWebDebuggingAccessEnabled), (override));
}; // class MockWebDelegateCross


HWTEST(WebPatternTest, WebDebuggingAccessTest001, TestSize.Level1)
{
    RefPtr<MockWebDelegateCross> delegate = MakeRefPtr<MockWebDelegateCross>();

    WebPattern webPattern;
    webPattern.delegate_ = delegate;

    WebPatternProperty::WebDebuggingConfigType enabled_and_port =
        std::make_tuple<bool, int32_t>(true, 8888);

    EXPECT_CALL(delegate, UpdateWebDebuggingAccess(enabled_and_port)).Times(AtLeast(1));

    webPattern.OnWebDebuggingAccessEnabledAndPortUpdate(enabled_and_port);
}

} // namespace OHOS::Ace::NG
