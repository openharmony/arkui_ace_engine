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

#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class MutableStyledStringAccessorTest : public AccessorTestBase<GENERATED_ArkUIMutableStyledStringAccessor,
    &GENERATED_ArkUIAccessors::getMutableStyledStringAccessor, MutableStyledStringPeer> {
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, ctorTest, TestSize.Level1)
{
    auto peer1 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->ctor());
    auto peer2 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->ctor());
    auto peer3 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->ctor());
    ASSERT_NE(peer1, nullptr);
    ASSERT_NE(peer2, nullptr);
    ASSERT_NE(peer3, nullptr);
    EXPECT_EQ(peer1->spanString, nullptr);
    EXPECT_EQ(peer2->spanString, nullptr);
    EXPECT_EQ(peer3->spanString, nullptr);
    finalyzer_(peer1);
    finalyzer_(peer2);
    finalyzer_(peer3);
}
} // namespace OHOS::Ace::NG
