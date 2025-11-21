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

#include "core/interfaces/native/implementation/event_target_info_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class EventTargetInfoAccessorTest : public AccessorTestBase<GENERATED_ArkUIEventTargetInfoAccessor,
    &GENERATED_ArkUIAccessors::getEventTargetInfoAccessor, EventTargetInfoPeer> {
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EventTargetInfoAccessorTest, ctorTest, TestSize.Level1)
{
    auto peer1 = reinterpret_cast<EventTargetInfoPeer*>(this->accessor_->construct());
    auto peer2 = reinterpret_cast<EventTargetInfoPeer*>(this->accessor_->construct());
    auto peer3 = reinterpret_cast<EventTargetInfoPeer*>(this->accessor_->construct());
    ASSERT_NE(peer1, nullptr);
    ASSERT_NE(peer2, nullptr);
    ASSERT_NE(peer3, nullptr);
    EXPECT_EQ(peer1->id, "");
    EXPECT_EQ(peer2->id, "");
    EXPECT_EQ(peer3->id, "");
    finalyzer_(peer1);
    finalyzer_(peer2);
    finalyzer_(peer3);
}

/**
 * @tc.name: getIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EventTargetInfoAccessorTest, getIdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getId, nullptr);
    const std::vector<std::string> TEST_PLAN {
        "EventTargetInfo ID", "0", "test", ""
    };
    for (const auto& id : TEST_PLAN) {
        peer_->id = id;
        const auto result = accessor_->getId(peer_);
        EXPECT_EQ(peer_->id, id);
        EXPECT_EQ(Converter::Convert<std::string>(result), id);
    }
    const auto result = accessor_->getId(nullptr);
    EXPECT_EQ(Converter::Convert<std::string>(result), "");
}

} // namespace OHOS::Ace::NG