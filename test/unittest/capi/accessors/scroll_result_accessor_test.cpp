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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/scroll_result_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    constexpr float TEST_VALUE = 10.0f;
    constexpr float TEST_DEFAULT_VALUE = 0.0f;
}

namespace GeneratedModifier {
    const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor();
}

class ScrollResultAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIScrollResultAccessor,
    &GENERATED_ArkUIAccessors::getScrollResultAccessor, ScrollResultPeer> {
public:
    void *CreatePeerInstance() override
    {
        return accessor_->construct();
    }
};

/**
 * @tc.name: setGetOffsetRemain
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollResultAccessorTest, setGetOffsetRemain, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOffsetRemain, nullptr);
    ASSERT_NE(accessor_->setOffsetRemain, nullptr);

    Ark_Number value = accessor_->getOffsetRemain(peer_);
    EXPECT_EQ(Converter::Convert<float>(value), TEST_DEFAULT_VALUE);

    value = Converter::ArkValue<Ark_Number>(TEST_VALUE);
    accessor_->setOffsetRemain(peer_, &value);
    value = accessor_->getOffsetRemain(peer_);
    EXPECT_EQ(Converter::Convert<float>(value), TEST_VALUE);
}

} // namespace OHOS::Ace::NG
