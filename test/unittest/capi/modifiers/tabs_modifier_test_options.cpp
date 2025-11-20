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

#include "modifier_test_base.h"
#include "swiper_modifier_test.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/implementation/tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class TabsModifierTestOptions : public ModifierTestBase<GENERATED_ArkUITabsModifier,
    &GENERATED_ArkUINodeModifiers::getTabsModifier, GENERATED_ARKUI_TABS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<TabTheme>();
    }
};


/**
 * @tc.name: setTabsOptionsTestInvalid
 * @tc.desc: Check the functionality of TabsInterfaceModifier.SetTabsOptionsImpl with controller
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTestOptions, setTabsOptionsTestInvalid, TestSize.Level1)
{
    // assume nothing bad with invalid and undefined options
    modifier_->setTabsOptions(node_, nullptr);
    auto optionsUndef = Converter::ArkValue<Opt_TabsOptions>(Ark_Empty());
    modifier_->setTabsOptions(node_, &optionsUndef);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: setTabsOptionsTestBarPos
 * @tc.desc: Check the functionality of TabsInterfaceModifier.SetTabsOptionsImpl with the Bar position
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTestOptions, setTabsOptionsTestBarPos, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabsOptions, nullptr);

    Ark_TabsOptions options = {
        .barPosition = Converter::ArkValue<Opt_BarPosition>(Ark_Empty()),
        .controller = Converter::ArkValue<Opt_TabsController>(Ark_Empty()),
        .index = Converter::ArkValue<Opt_Number>(Ark_Empty())
    };
    auto optionsOpt = Converter::ArkValue<Opt_TabsOptions>(options);

    constexpr auto propName = "barPosition";
    constexpr auto expectedDefaultValue = "BarPosition.Start";
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, expectedDefaultValue);

    using OneTestStep = std::pair<Opt_BarPosition, std::string> ;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_BarPosition>(Ark_BarPosition::ARK_BAR_POSITION_END), "BarPosition.End" },
        { Converter::ArkValue<Opt_BarPosition>(Ark_BarPosition::ARK_BAR_POSITION_START), "BarPosition.Start" },
        { Converter::ArkValue<Opt_BarPosition>(Ark_BarPosition::ARK_BAR_POSITION_END), "BarPosition.End" },
        { Converter::ArkValue<Opt_BarPosition>(static_cast<Ark_BarPosition>(INT_MIN)), expectedDefaultValue },
        { Converter::ArkValue<Opt_BarPosition>(Ark_BarPosition::ARK_BAR_POSITION_END), "BarPosition.End" },
        { Converter::ArkValue<Opt_BarPosition>(Ark_Empty()), expectedDefaultValue },
    };

    for (const auto& [value, expected] : testPlan) {
        optionsOpt.value.barPosition = Converter::ArkValue<Opt_BarPosition>(value);
        modifier_->setTabsOptions(node_, &optionsOpt);
        checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setTabsOptionsTestController
 * @tc.desc: Check the functionality of TabsInterfaceModifier.SetTabsOptionsImpl with controller
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTestOptions, setTabsOptionsTestController, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabsOptions, nullptr);

    Ark_TabsOptions options = {
        .barPosition = Converter::ArkValue<Opt_BarPosition>(Ark_Empty()),
        .controller = Converter::ArkValue<Opt_TabsController>(Ark_Empty()),
        .index = Converter::ArkValue<Opt_Number>(Ark_Empty())
    };
    auto optionsOpt = Converter::ArkValue<Opt_TabsOptions>(options);

    // set the invoke checker INTO the internal controller
    bool checkInvoke = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalSwiperController = TabsModelNG::GetSwiperController(frameNode);
    ASSERT_NE(internalSwiperController, nullptr);
    internalSwiperController->SetSwipeToImpl([&checkInvoke](int32_t, bool) {
        checkInvoke = true;
    });

    // create the external TabsController peer and attach it to modifier
    TabsControllerPeer peer;
    optionsOpt.value.controller = Converter::ArkValue<Opt_TabsController>(&peer);
    modifier_->setTabsOptions(node_, &optionsOpt);

    // check initial state of invoke checker
    EXPECT_FALSE(checkInvoke);

    // simulate the action from the external peer
    peer.TriggerChangeIndex(1);

    // check the expected state of invoke checker
    EXPECT_TRUE(checkInvoke);
}

/**
 * @tc.name: setTabsOptionsTestIndex
 * @tc.desc: Check the functionality of TabsInterfaceModifier.SetTabsOptionsImpl with controller
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTestOptions, setTabsOptionsTestIndex, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabsOptions, nullptr);

    Ark_TabsOptions options = {
        .barPosition = Converter::ArkValue<Opt_BarPosition>(Ark_Empty()),
        .controller = Converter::ArkValue<Opt_TabsController>(Ark_Empty()),
        .index = Converter::ArkValue<Opt_Number>(Ark_Empty())
    };
    auto optionsOpt = Converter::ArkValue<Opt_TabsOptions>(options);

    constexpr auto propName = "index";
    constexpr auto expectedDefaultValue = "0";
    auto checkVal = GetAttrValue<std::string>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, expectedDefaultValue);

    using OneTestStep = std::pair<Opt_Number, std::string> ;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Number>(1), "1" },
        { Converter::ArkValue<Opt_Number>(), expectedDefaultValue },
        { Converter::ArkValue<Opt_Number>(1), "1" },
        { Converter::ArkValue<Opt_Number>(INT_MIN), expectedDefaultValue },
    };

    for (const auto& [value, expected] : testPlan) {
        optionsOpt.value.index = value;
        modifier_->setTabsOptions(node_, &optionsOpt);
        checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}
} // namespace OHOS::Ace::NG
