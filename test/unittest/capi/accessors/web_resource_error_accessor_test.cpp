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

#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
std::string g_info = "info";
int32_t g_code = 5;
} // namespace

class WebResourceErrorAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebResourceErrorAccessor,
    &GENERATED_ArkUIAccessors::getWebResourceErrorAccessor, WebResourceErrorPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        peer_->handler = Referenced::MakeRefPtr<WebError>(g_info, g_code);
        ASSERT_NE(peer_->handler, nullptr);
    }
};

/**
 * @tc.name: getErrorCodeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceErrorAccessorTest, getErrorCodeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getErrorCode, nullptr);
    EXPECT_EQ(g_code, Converter::Convert<int32_t>(accessor_->getErrorCode(peer_)));
}

/**
 * @tc.name: getErrorInfoTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebResourceErrorAccessorTest, getErrorInfoTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getErrorInfo, nullptr);
    Ark_String info = accessor_->getErrorInfo(peer_);
    EXPECT_EQ(Converter::Convert<std::string>(info), g_info);
    info = accessor_->getErrorInfo(nullptr);
    EXPECT_EQ(Converter::Convert<std::string>(info), "");
}

} // namespace OHOS::Ace::NG
