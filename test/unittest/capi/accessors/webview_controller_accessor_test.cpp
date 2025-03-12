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

#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/webview_controller_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "test/unittest/capi/stubs/mock_application_context.h"
#include "test/unittest/capi/stubs/mock_nweb_helper.h"

#include "gmock/gmock.h"

namespace OHOS::NWeb {
class MockNWeb : public NWeb {
public:
    MOCK_METHOD(int, Load, (const std::string&, (const std::map<std::string, std::string>&)));
};
}

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class WebviewControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebviewControllerAccessor,
    &GENERATED_ArkUIAccessors::getWebviewControllerAccessor, WebviewControllerPeer> {
public:
    void SetUp() override
    {
        constexpr int nwebid = 100;
        AccessorTestBase::SetUp();
        nweb_ = std::make_shared<NWeb::MockNWeb>();
        ASSERT_NE(nweb_, nullptr);
        NWeb::NWebHelper::Instance().SetNWeb(nwebid, nweb_);
        peer_->nwebId = nwebid;
    }

    std::shared_ptr<NWeb::MockNWeb> nweb_;
};

/**
 * @tc.name: initializeWebEngineTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebviewControllerAccessorTest, initializeWebEngineTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->initializeWebEngine, nullptr);

    EXPECT_FALSE(NWeb::NWebHelper::Instance().IsInited());
    accessor_->initializeWebEngine();
    EXPECT_TRUE(NWeb::NWebHelper::Instance().IsInited());
}

/**
 * @tc.name: loadUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebviewControllerAccessorTest, loadUrlTest, TestSize.Level1)
{
    std::string urlStr = "http://example.com";
    std::string headerKey = "Key";
    std::string headerValue = "Value";
    std::map<std::string, std::string> httpHeaders;
    httpHeaders[headerKey] = headerValue;

    Ark_Union_String_Resource url = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(urlStr);
    Ark_WebHeader header;
    header.headerKey = Converter::ArkValue<Ark_String>(headerKey);
    header.headerValue = Converter::ArkValue<Ark_String>(headerValue);
    std::vector<Ark_WebHeader> vec { header };
    Converter::ArkArrayHolder<Array_WebHeader> vecHolder(vec);
    Opt_Array_WebHeader headers = vecHolder.OptValue<Opt_Array_WebHeader>();

    ASSERT_NE(accessor_->loadUrl, nullptr);

    EXPECT_CALL(*nweb_, Load(urlStr, httpHeaders)).Times(1);
    accessor_->loadUrl(peer_, &url, &headers);
}

} // namespace OHOS::Ace::NG
