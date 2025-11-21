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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
std::map<std::string, std::string> g_headers = {
    {"key1", "value1"},
    {"key2", "value2"},
    {"key3", "value3"}
};
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
 * @tc.name: getRequestHeaderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, getRequestHeaderTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRequestHeader, nullptr);
    Array_Header headers = accessor_->getRequestHeader(peer_);
    std::vector<Converter::Header> headerVect = Converter::Convert<std::vector<Converter::Header>>(headers);
    std::vector<Converter::Header> expected;
    for (const auto& pair : g_headers) {
        Converter::Header header {
            .headerKey = pair.first,
            .headerValue = pair.second
        };
        expected.push_back(header);
    }
    EXPECT_EQ(headerVect, expected);
    headers = accessor_->getRequestHeader(nullptr);
    headerVect = Converter::Convert<std::vector<Converter::Header>>(headers);
    std::vector<Converter::Header> empty;
    EXPECT_EQ(headerVect, empty);
}

/**
 * @tc.name: getRequestUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, getRequestUrlTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRequestUrl, nullptr);
    Ark_String url = accessor_->getRequestUrl(peer_);
    EXPECT_EQ(Converter::Convert<std::string>(url), g_url);
    url = accessor_->getRequestUrl(nullptr);
    EXPECT_EQ(Converter::Convert<std::string>(url), "");
}

/**
 * @tc.name: getRequestMethodTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceRequestAccessorTest, getRequestMethodTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRequestMethod, nullptr);
    Ark_String method = accessor_->getRequestMethod(peer_);
    EXPECT_EQ(Converter::Convert<std::string>(method), g_method);
    method = accessor_->getRequestMethod(nullptr);
    EXPECT_EQ(Converter::Convert<std::string>(method), "");
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
