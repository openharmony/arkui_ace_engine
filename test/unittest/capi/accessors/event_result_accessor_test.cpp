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

#include "core/interfaces/native/implementation/event_result_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockGestureEventResult : public GestureEventResult {
public:
    MOCK_METHOD(void, SetGestureEventResult, (bool));
    MOCK_METHOD(void, SetGestureEventResult, (bool, bool));
};
} // namespace

class EventResultAccessorTest : public AccessorTestBase<GENERATED_ArkUIEventResultAccessor,
    &GENERATED_ArkUIAccessors::getEventResultAccessor, EventResultPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockGestureEventResult>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockGestureEventResult> mockHandler_ = nullptr;
};

/**
 * @tc.name: setGestureEventResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EventResultAccessorTest, setGestureEventResultTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setGestureEventResult0, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);

    EXPECT_CALL(*mockHandler_, SetGestureEventResult(true)).Times(2);
    accessor_->setGestureEventResult0(peer_, arkTrue);
    accessor_->setGestureEventResult0(peer_, arkTrue);

    EXPECT_CALL(*mockHandler_, SetGestureEventResult(false)).Times(2);
    accessor_->setGestureEventResult0(peer_, arkFalse);
    accessor_->setGestureEventResult0(peer_, arkFalse);
}

} // namespace OHOS::Ace::NG
