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

#include "core/interfaces/native/implementation/full_screen_exit_handler_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class FullScreenExitHandlerAccessorTest : public AccessorTestBase<GENERATED_ArkUIFullScreenExitHandlerAccessor,
    &GENERATED_ArkUIAccessors::getFullScreenExitHandlerAccessor, FullScreenExitHandlerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockFullScreenExitHandler>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockFullScreenExitHandler> mockHandler_ = nullptr;
};

/**
 * @tc.name: exitFullScreenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FullScreenExitHandlerAccessorTest, exitFullScreenTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->exitFullScreen, nullptr);

    EXPECT_CALL(*mockHandler_, ExitFullScreen()).Times(3);
    accessor_->exitFullScreen(peer_);
    accessor_->exitFullScreen(peer_);
    accessor_->exitFullScreen(peer_);
}

} // namespace OHOS::Ace::NG
