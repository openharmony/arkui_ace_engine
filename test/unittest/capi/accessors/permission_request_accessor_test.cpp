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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/permission_request_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockWebPermissionRequest : public WebPermissionRequest {
public:
    MOCK_METHOD(void, Deny, (), (const));
    MOCK_METHOD(std::string, GetOrigin, (), (const));
    MOCK_METHOD(std::vector<std::string>, GetResources, (), (const));
    MOCK_METHOD(void, Grant, (std::vector<std::string>&), (const));
};
} // namespace

class PermissionRequestAccessorTest : public AccessorTestBase<GENERATED_ArkUIPermissionRequestAccessor,
    &GENERATED_ArkUIAccessors::getPermissionRequestAccessor, PermissionRequestPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockWebPermissionRequest>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockWebPermissionRequest> mockHandler_ = nullptr;
};

/**
 * @tc.name: denyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PermissionRequestAccessorTest, denyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->deny, nullptr);

    EXPECT_CALL(*mockHandler_, Deny()).Times(3);
    accessor_->deny(peer_);
    accessor_->deny(peer_);
    accessor_->deny(peer_);
}

/**
 * @tc.name: DISABLED_getOriginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PermissionRequestAccessorTest, DISABLED_getOriginTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOrigin, nullptr);

    EXPECT_CALL(*mockHandler_, GetOrigin()).Times(1);
    accessor_->getOrigin(peer_);
}

/**
 * @tc.name: DISABLED_getAccessibleResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PermissionRequestAccessorTest, DISABLED_getAccessibleResourceTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAccessibleResource, nullptr);

    EXPECT_CALL(*mockHandler_, GetResources()).Times(1);
    accessor_->getAccessibleResource(peer_);
}

/**
 * @tc.name: grantTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PermissionRequestAccessorTest, grantTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->grant, nullptr);

    std::vector<std::string> vec{ "item1", "item2" };
    Converter::ArkArrayHolder<Array_String> vecHolder(vec);
    Array_String stringArrayResult = vecHolder.ArkValue();

    EXPECT_CALL(*mockHandler_, Grant(vec)).Times(1);
    accessor_->grant(peer_, &stringArrayResult);
}

} // namespace OHOS::Ace::NG
