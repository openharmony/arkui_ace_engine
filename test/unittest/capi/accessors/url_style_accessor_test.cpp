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
#include "core/interfaces/native/implementation/url_style_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class UrlStyleAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUIUrlStyleAccessor,
        &GENERATED_ArkUIAccessors::getUrlStyleAccessor, UrlStylePeer> {
public:
    void SetUp() override
    {
        ASSERT_NE(this->accessor_->construct, nullptr);
        AccessorTestBaseParent::SetUp();
    }
    void TearDown() override
    {
    }
};

/**
 * @tc.name: CtorAndGetUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UrlStyleAccessorTest, CtorAndGetUrlTest, TestSize.Level1)
{
    const std::vector<std::string> TEST_PLAN = {
        "http://example.com", "http://url.com", "http://example.com:20000", "https://gitee.com"
    };
    for (auto& str : TEST_PLAN) {
        Ark_String arkStr = Converter::ArkValue<Ark_String>(str);
        peer_ = accessor_->construct(&arkStr);
        ASSERT_NE(peer_, nullptr);
        ASSERT_NE(peer_->span, nullptr);
        EXPECT_EQ(peer_->span->GetUrlSpanAddress(), str);

        auto resultArk = accessor_->getUrl(peer_);
        auto result = Converter::Convert<std::string>(resultArk);
        EXPECT_EQ(str, result);
        finalyzer_(peer_);
    }
}

}