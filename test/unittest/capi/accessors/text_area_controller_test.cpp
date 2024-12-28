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

#include "core/interfaces/native/implementation/text_area_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class MockTextAreaController : public TextFieldControllerBase {
public:
    MockTextAreaController() = default;
    ~MockTextAreaController() override = default;
    MOCK_METHOD(void, CaretPosition, (int32_t), (override));
    MOCK_METHOD(void, StopEditing, (), (override));
    MOCK_METHOD(void, SetTextSelection, (int32_t, int32_t, const std::optional<SelectionOptions>&), (override));
};
} // namespace

class TextAreaControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUITextAreaControllerAccessor,
    &GENERATED_ArkUIAccessors::getTextAreaControllerAccessor, TextAreaControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockTextAreaController_ = new MockTextAreaController();
        mockTextAreaControllerKeeper_ = AceType::Claim(mockTextAreaController_);
        ASSERT_NE(mockTextAreaControllerKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->SetController(mockTextAreaControllerKeeper_);
        ASSERT_NE(mockTextAreaController_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockTextAreaControllerKeeper_ = nullptr;
        mockTextAreaController_ = nullptr;
    }

    MockTextAreaController* mockTextAreaController_ = nullptr;
    RefPtr<MockTextAreaController> mockTextAreaControllerKeeper_ = nullptr;
};

/**
 * @tc.name: caretPositionTest
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaControllerAccessorTest, caretPositionTest, TestSize.Level1)
{
    constexpr int validValue1 = 10;
    constexpr int validValue2 = 55;
    constexpr int invalidValue = -10;

    auto arkValid1 = ArkValue<Ark_Number>(validValue1);
    auto arkValid2 = ArkValue<Ark_Number>(validValue2);
    auto arkInvalid = ArkValue<Ark_Number>(invalidValue);

    ASSERT_NE(accessor_->caretPosition, nullptr);

    EXPECT_CALL(*mockTextAreaController_, CaretPosition(validValue1)).Times(1);
    accessor_->caretPosition(peer_, &arkValid1);

    EXPECT_CALL(*mockTextAreaController_, CaretPosition(validValue2)).Times(1);

    accessor_->caretPosition(peer_, &arkValid2);
    EXPECT_CALL(*mockTextAreaController_, CaretPosition(0)).Times(1);
    accessor_->caretPosition(peer_, &arkInvalid);
    accessor_->caretPosition(peer_, nullptr);
}

/**
 * @tc.name: StopEditingTest
 * @tc.desc: check work of stopEditing method
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaControllerAccessorTest, StopEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopEditing, nullptr);

    EXPECT_CALL(*mockTextAreaController_, StopEditing()).Times(3);
    accessor_->stopEditing(peer_);
    accessor_->stopEditing(peer_);
    accessor_->stopEditing(peer_);
}

MATCHER_P(CompareSelectionOptions, selectionOptions, "SelectionOptions compare")
{
    return arg->menuPolicy == selectionOptions->menuPolicy;
}

/**
 * @tc.name: SetTextSelectionTest
 * @tc.desc: check work of setTextSelection method
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaControllerAccessorTest, SetTextSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTextSelection, nullptr);
    constexpr std::optional<SelectionOptions> empty = std::nullopt;
    std::optional<SelectionOptions> test = SelectionOptions { MenuPolicy::DEFAULT };

    int32_t valid1 = 10;
    int32_t valid2 = 55;

    auto arkValid1 = ArkValue<Ark_Number>(valid1);
    auto arkValid2 = ArkValue<Ark_Number>(valid2);

    const std::vector<MenuPolicy> menuPolicies = {
        MenuPolicy::DEFAULT,
        MenuPolicy::HIDE,
        MenuPolicy::SHOW,
        static_cast<MenuPolicy>(-1)
    };

    EXPECT_CALL(*mockTextAreaController_, SetTextSelection(0, 0, CompareSelectionOptions(empty))).Times(0);
    accessor_->setTextSelection(peer_, nullptr, nullptr, nullptr);

    Ark_SelectionOptions menuOptions;
    for (auto& menuPolicy : menuPolicies) {
        test->menuPolicy = menuPolicy;
        if (menuPolicy != static_cast<MenuPolicy>(-1)) {
            EXPECT_CALL(*mockTextAreaController_, SetTextSelection(valid1,
                valid2, CompareSelectionOptions(test))).Times(1);
        } else {
            EXPECT_CALL(*mockTextAreaController_, SetTextSelection(valid1,
                valid2, CompareSelectionOptions(empty))).Times(1);
        }
        menuOptions.menuPolicy = ArkValue<Opt_MenuPolicy>(menuPolicy);
        auto optMenuOptions = ArkValue<Opt_SelectionOptions>(menuOptions);
        accessor_->setTextSelection(peer_, &arkValid1, &arkValid2, &optMenuOptions);
    }
    EXPECT_CALL(*mockTextAreaController_, SetTextSelection(valid1, valid2, CompareSelectionOptions(empty))).Times(1);
    accessor_->setTextSelection(peer_, &arkValid1, &arkValid2, nullptr);
}
} // namespace OHOS::Ace::NG
