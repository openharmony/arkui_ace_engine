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

#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "core/interfaces/native/implementation/text_input_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class MockTextInputController : public TextFieldControllerBase {
public:
    MockTextInputController() = default;
    ~MockTextInputController() override = default;
    MOCK_METHOD(void, CaretPosition, (int32_t), (override));
    MOCK_METHOD(void, StopEditing, (), (override));
    MOCK_METHOD(void, SetTextSelection, (int32_t, int32_t, const std::optional<SelectionOptions>&), (override));
};
} // namespace

class TextInputControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUITextInputControllerAccessor,
    &GENERATED_ArkUIAccessors::getTextInputControllerAccessor, TextInputControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockTextInputController_ = new MockTextInputController();
        mockTextInputControllerKeeper_ = AceType::Claim(mockTextInputController_);
        ASSERT_NE(mockTextInputControllerKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->SetController(mockTextInputControllerKeeper_);
        ASSERT_NE(mockTextInputController_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockTextInputControllerKeeper_ = nullptr;
        mockTextInputController_ = nullptr;
    }

    MockTextInputController* mockTextInputController_ = nullptr;
    RefPtr<MockTextInputController> mockTextInputControllerKeeper_ = nullptr;
};

/**
 * @tc.name: caretPositionTest
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(TextInputControllerAccessorTest, caretPositionTest, TestSize.Level1)
{
    constexpr int validValue1 = 10;
    constexpr int validValue2 = 55;
    constexpr int invalidValue = -10;

    auto arkValid1 = ArkValue<Ark_Int32>(validValue1);
    auto arkValid2 = ArkValue<Ark_Int32>(validValue2);
    auto arkInvalid = ArkValue<Ark_Int32>(invalidValue);

    ASSERT_NE(accessor_->caretPosition, nullptr);

    EXPECT_CALL(*mockTextInputController_, CaretPosition(validValue1)).Times(1);
    accessor_->caretPosition(peer_, arkValid1);

    EXPECT_CALL(*mockTextInputController_, CaretPosition(validValue2)).Times(1);

    accessor_->caretPosition(peer_, arkValid2);
    EXPECT_CALL(*mockTextInputController_, CaretPosition(0)).Times(1);
    accessor_->caretPosition(peer_, arkInvalid);
}

/**
 * @tc.name: StopEditingTest
 * @tc.desc: check work of stopEditing method
 * @tc.type: FUNC
 */
HWTEST_F(TextInputControllerAccessorTest, StopEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopEditing, nullptr);

    EXPECT_CALL(*mockTextInputController_, StopEditing()).Times(3);
    accessor_->stopEditing(peer_);
    accessor_->stopEditing(peer_);
    accessor_->stopEditing(peer_);
}

/**
 * @tc.name: SetTextSelectionTest
 * @tc.desc: check work of setTextSelection method
 * @tc.type: FUNC
 */
HWTEST_F(TextInputControllerAccessorTest, SetTextSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTextSelection, nullptr);
    std::optional<SelectionOptions> test = SelectionOptions { MenuPolicy::DEFAULT };

    int32_t valid1 = 10;
    int32_t valid2 = 55;

    auto arkValid1 = ArkValue<Ark_Int32>(valid1);
    auto arkValid2 = ArkValue<Ark_Int32>(valid2);

    const std::vector<MenuPolicy> menuPolicies = {
        MenuPolicy::DEFAULT,
        MenuPolicy::HIDE,
        MenuPolicy::SHOW,
        static_cast<MenuPolicy>(-1)
    };

    EXPECT_CALL(*mockTextInputController_, SetTextSelection(valid1, valid2, _))
        .WillRepeatedly([&test](int32_t arg1, int32_t arg2, std::optional<SelectionOptions> arg3) {
            auto input = test ? std::to_string(std::underlying_type_t<MenuPolicy>(test->menuPolicy)) : "nullopt";
            if (!test) {
                EXPECT_FALSE(arg3) << "Input value was: " << input;
            } else {
                ASSERT_TRUE(arg3);
                EXPECT_EQ(arg3->menuPolicy, test->menuPolicy) << "Input value was: " << input;
            }
        });
    Ark_SelectionOptions menuOptions;
    for (auto& menuPolicy : menuPolicies) {
        test->menuPolicy = (menuPolicy == static_cast<MenuPolicy>(-1)) ? MenuPolicy::DEFAULT : menuPolicy;
        menuOptions.menuPolicy = ArkValue<Opt_MenuPolicy>(menuPolicy);
        auto optMenuOptions = ArkValue<Opt_SelectionOptions>(menuOptions);
        accessor_->setTextSelection(peer_, arkValid1, arkValid2, &optMenuOptions);
    }
    test = std::nullopt;
    accessor_->setTextSelection(peer_, arkValid1, arkValid2, nullptr);
}
} // namespace OHOS::Ace::NG
