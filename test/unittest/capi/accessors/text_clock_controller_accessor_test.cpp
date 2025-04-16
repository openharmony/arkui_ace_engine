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

#include "core/interfaces/native/implementation/text_clock_controller_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components/text_clock/text_clock_controller.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class StubTextClockController : public TextClockController {
public:
    StubTextClockController()
    {
        OnStart(std::bind(&StubTextClockController::Start, this));
        OnStop(std::bind(&StubTextClockController::Stop, this));
    }
    ~StubTextClockController() override = default;
    virtual void Start() {}
    virtual void Stop() {}
};
class MockTextClockController : public StubTextClockController {
public:
    MockTextClockController() = default;
    ~MockTextClockController() override = default;
    MOCK_METHOD(void, Start, ());
    MOCK_METHOD(void, Stop, ());
};
} // namespace

class TextClockControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUITextClockControllerAccessor,
    &GENERATED_ArkUIAccessors::getTextClockControllerAccessor, TextClockControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockTextClockController_ = new MockTextClockController();
        mockTextClockControllerKeeper_ = AceType::Claim(mockTextClockController_);
        ASSERT_NE(mockTextClockControllerKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->controller = mockTextClockControllerKeeper_;
        ASSERT_NE(mockTextClockController_, nullptr);
    }

    void TearDown(void) override
    {
        AccessorTestBase::TearDown();
        mockTextClockControllerKeeper_ = nullptr;
        mockTextClockController_ = nullptr;
    }

    MockTextClockController *mockTextClockController_ = nullptr;
    RefPtr<MockTextClockController> mockTextClockControllerKeeper_ = nullptr;
};

/**
 * @tc.name: startTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockControllerAccessorTest, startTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->start, nullptr);

    EXPECT_CALL(*mockTextClockController_, Start()).Times(3);
    accessor_->start(peer_);
    accessor_->start(peer_);
    accessor_->start(peer_);
}

/**
 * @tc.name: stopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockControllerAccessorTest, stopTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stop, nullptr);

    EXPECT_CALL(*mockTextClockController_, Stop()).Times(3);
    accessor_->stop(peer_);
    accessor_->stop(peer_);
    accessor_->stop(peer_);
}
} // namespace OHOS::Ace::NG
