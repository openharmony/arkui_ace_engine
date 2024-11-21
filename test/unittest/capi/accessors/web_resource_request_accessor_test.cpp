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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "core/interfaces/arkoala/implementation/web_resource_request_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
std::map<std::string, std::string> g_headers = {};
std::string g_method = "method";
std::string g_url = "url";
bool g_hasGesture = true;
bool g_isMainFrame = true;
bool g_isRedirect = true;
} // namespace

class WebResourceRequestAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebResourceRequestAccessor,
    &GENERATED_ArkUIAccessors::getWebResourceRequestAccessor, WebResourceRequestPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        webRequest_ = Referenced::MakeRefPtr<WebRequest>(
            g_headers, g_method, g_url, g_hasGesture, g_isMainFrame, g_isRedirect);
        ASSERT_NE(webRequest_, nullptr);
        peer_->webRequest = webRequest_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        webRequest_ = nullptr;
    }

    RefPtr<WebRequest> webRequest_ = nullptr;
};

/**
 * @tc.name: DISABLED_getRequestHeaderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, DISABLED_getRequestHeaderTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRequestHeader, nullptr);

    // should return value
    accessor_->getRequestHeader(peer_);
}

/**
 * @tc.name: DISABLED_getRequestUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, DISABLED_getRequestUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRequestUrl, nullptr);

    // should return value
    accessor_->getRequestUrl(peer_);
}

/**
 * @tc.name: DISABLED_getRequestMethodTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, DISABLED_getRequestMethodTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRequestMethod, nullptr);

    // should return value
    accessor_->getRequestMethod(peer_);
}

/**
 * @tc.name: isRequestGestureTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, isRequestGestureTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isRequestGesture, nullptr);
    EXPECT_EQ(g_hasGesture, accessor_->isRequestGesture(peer_));
}

/**
 * @tc.name: isRedirectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, isRedirectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isRedirect, nullptr);
    EXPECT_EQ(g_isRedirect, accessor_->isRedirect(peer_));
}

/**
 * @tc.name: isMainFrameTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, isMainFrameTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isMainFrame, nullptr);
    EXPECT_EQ(g_isMainFrame, accessor_->isMainFrame(peer_));
}

} // namespace OHOS::Ace::NG