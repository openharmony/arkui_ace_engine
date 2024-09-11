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

#include "core/interfaces/arkoala/implementation/swiper_controller_modifier_peer_impl.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class StubSwiperController : public SwiperController {
public:
    StubSwiperController()
    {
        SetShowNextImpl(std::bind(&StubSwiperController::ShowNext, this));
    }
    ~StubSwiperController() override = default;
    virtual void ShowNext() {}
};

class MockSwiperController : public StubSwiperController {
public:
    MockSwiperController() = default;
    ~MockSwiperController() override = default;
    MOCK_METHOD(void, ShowNext, ());
};
} // namespace

class SwiperControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUISwiperControllerAccessor,
    &GENERATED_ArkUIAccessors::getSwiperControllerAccessor, SwiperControllerPeer> {
public:
    static void SetUpTestCase()
    {
        AccessorTestBase::SetUpTestCase();

        auto controller = new MockSwiperController();
        mockSwiperController_ = AceType::Claim(controller);
        EXPECT_CALL(*controller, ShowNext()).Times(1);
    }

    static void TearDownTestCase()
    {
        mockSwiperController_ = nullptr;

        AccessorTestBase::TearDownTestCase();
    }

    virtual void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        auto peerImpl = reinterpret_cast<GeneratedModifier::SwiperControllerModifier::SwiperControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddListener(mockSwiperController_);
    }

    static inline RefPtr<MockSwiperController> mockSwiperController_ = nullptr;
};

/**
 * @tc.name: showNextTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.showNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, showNextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showNext, nullptr);
    accessor_->showNext(peer_);
}

} // namespace OHOS::Ace::NG
