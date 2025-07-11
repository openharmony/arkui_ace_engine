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

#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class JsGeolocationAccessorTest : public AccessorTestBase<GENERATED_ArkUIJsGeolocationAccessor,
    &GENERATED_ArkUIAccessors::getJsGeolocationAccessor, JsGeolocationPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockWebGeolocation_ = Referenced::MakeRefPtr<MockWebGeolocation>();
        ASSERT_NE(mockWebGeolocation_, nullptr);
        peer_->webGeolocation = mockWebGeolocation_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockWebGeolocation_ = nullptr;
    }

    RefPtr<MockWebGeolocation> mockWebGeolocation_ = nullptr;
};

/**
 * @tc.name: invokeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(JsGeolocationAccessorTest, invokeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->invoke, nullptr);

    std::string origin = "origin";
    bool allow = true;
    bool retain = false;

    Ark_String arkOrigin = Converter::ArkValue<Ark_String>(origin);
    Ark_Boolean arkAllow = Converter::ArkValue<Ark_Boolean>(allow);
    Ark_Boolean arkRetain = Converter::ArkValue<Ark_Boolean>(retain);

    EXPECT_CALL(*mockWebGeolocation_, Invoke(origin, allow, retain)).Times(1);
    accessor_->invoke(peer_, &arkOrigin, arkAllow, arkRetain);
}

} // namespace OHOS::Ace::NG
