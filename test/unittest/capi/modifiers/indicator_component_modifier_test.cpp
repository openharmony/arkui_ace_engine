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

#undef UNITEST_FRIEND_CLASS
#define UNITEST_FRIEND_CLASS friend class IndicatorComponentModifierTests

#include <limits>

#include "swiper_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"

#include "core/components/common/layout/constants.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
static const Dimension THEME_SWIPER_INDICATOR_SIZE(9876, DimensionUnit::VP);
static const Dimension THEME_SWIPER_FONT_SIZE(321, DimensionUnit::PX);
static const Color THEME_SWIPER_INDICATOR_COLOR(Color::BLUE);
static const Color THEME_SWIPER_ARROW_COLOR(Color::GREEN);

static const std::vector<std::pair<Opt_Int32, std::string>> TEST_POSITIVE_INTEGER_PLAN {
    {ArkValue<Opt_Int32>(1234), "1234"},
    {ArkValue<Opt_Int32>(5), "5"},
    {ArkValue<Opt_Int32>(INT32_MIN), "0"},
    {ArkValue<Opt_Int32>(-123434), "0"},
};
} // namespace

class IndicatorComponentModifierTests : public ModifierTestBase<GENERATED_ArkUIIndicatorComponentModifier,
    &GENERATED_ArkUINodeModifiers::getIndicatorComponentModifier, GENERATED_ARKUI_INDICATOR_COMPONENT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle("swiper_pattern");
        themeStyle->SetAttr("swiper_indicator_size", { .value = THEME_SWIPER_INDICATOR_SIZE });
        themeStyle->SetAttr("indicator_color", { .value = THEME_SWIPER_INDICATOR_COLOR });
        themeStyle->SetAttr("indicator_color_selected", { .value = THEME_SWIPER_INDICATOR_COLOR });
        themeStyle->SetAttr("indicator_text_font_size", { .value = THEME_SWIPER_FONT_SIZE });
        themeStyle->SetAttr(ARROW_COLOR_PRIMARY, { .value = THEME_SWIPER_ARROW_COLOR });
        themeStyle->SetAttr(ARROW_COLOR_COMPONENT_NORMAL, { .value = THEME_SWIPER_ARROW_COLOR });

        SetupTheme<SwiperIndicatorTheme>();
    }

    void OnModifyDone()
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<IndicatorPattern>();
        ASSERT_NE(pattern, nullptr);
        pattern->OnModifyDone();
    }

    void SetInternalController(const RefPtr<IndicatorController>& controller)
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<IndicatorPattern>();
        ASSERT_NE(pattern, nullptr);
        pattern->indicatorController_ = controller;
    }
};

/**
 * @tc.name: setInitialIndexTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.InitialIndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setInitialIndexTest, TestSize.Level1)
{
    static const std::string propName("initialIndex");
    static const std::string defaultValue("0");
    ASSERT_NE(modifier_->setInitialIndex, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);

    for (auto [input, expected]: TEST_POSITIVE_INTEGER_PLAN) {
        modifier_->setInitialIndex(node_, &input);
        auto checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setCountTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.CountImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setCountTest, TestSize.Level1)
{
    static const std::string propName("count");
    static const std::string defaultValue("0");
    ASSERT_NE(modifier_->setCount, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);

    for (auto [input, expected]: TEST_POSITIVE_INTEGER_PLAN) {
        modifier_->setCount(node_, &input);
        auto checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setLoopTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setLoopTest, TestSize.Level1)
{
    static const std::string propName("loop");
    static const std::string defaultValue("true");
    ASSERT_NE(modifier_->setLoop, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);
    auto optTrue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setLoop(node_, &optTrue);
    auto checkValT = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValT, "true");
    auto optFalse = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setLoop(node_, &optFalse);
    auto checkValF = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValF, "false");
}

/**
 * @tc.name: setVerticalTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.VerticalImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setVerticalTest, TestSize.Level1)
{
    static const std::string propName("vertical");
    static const std::string defaultValue("false");
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);
    auto optTrue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setVertical(node_, &optTrue);
    auto checkValT = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValT, "true");
    auto optFalse = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setVertical(node_, &optFalse);
    auto checkValF = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValF, "false");
}

/**
 * @tc.name: setIndicatorComponentOptionsTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.SetIndicatorComponentOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setIndicatorComponentOptionsTest, TestSize.Level1)
{
    class MockIndicatorController : public IndicatorController {
    public:
        MOCK_METHOD(void, ShowNext, (), (const));
    };
    auto mockIndicatorController = AceType::MakeRefPtr<MockIndicatorController>();
    SetInternalController(mockIndicatorController);

    ASSERT_NE(modifier_->setIndicatorComponentOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setIndicatorComponentOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_IndicatorComponentController>();
    modifier_->setIndicatorComponentOptions(node_, &controllerUndef);

    // create the external IndicatorComponentController peer and attach the modifier to it
    auto peer = PeerUtils::CreatePeer<IndicatorComponentControllerPeer>();
    ASSERT_NE(peer, nullptr);
    auto controller = Converter::ArkValue<Opt_IndicatorComponentController>(peer);
    modifier_->setIndicatorComponentOptions(node_, &controller);

    // assume the internal controller will be affected
    EXPECT_CALL(*mockIndicatorController, ShowNext()).Times(1);

    // during simulating of the action from the external peer
    peer->ShowNext();
}
} // namespace OHOS::Ace::NG