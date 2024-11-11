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
#include "modifiers_test_utils.h"

#include "core/components/counter/counter_theme.h"
#include "core/components_ng/pattern/counter/counter_pattern.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ENABLE_DEC_NAME = "enableDec";
    const auto ATTRIBUTE_ENABLE_DEC_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_ENABLE_INC_NAME = "enableInc";
    const auto ATTRIBUTE_ENABLE_INC_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_WIDTH_NAME = "width";
    const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "100.00vp";
    const auto ATTRIBUTE_HEIGHT_NAME = "height";
    const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "32.00vp";

    const Ark_Int32 FAKE_RES_ID(1234);
    const Ark_Length RES_ARK_LENGTH = { .type = ARK_TAG_RESOURCE, .resource = FAKE_RES_ID };

    struct EventsTracker {
        static inline GENERATED_ArkUICounterEventsReceiver counterEventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getCounterEventsReceiver = [] () -> const GENERATED_ArkUICounterEventsReceiver* {
                return &counterEventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class CounterModifierTest : public ModifierTestBase<GENERATED_ArkUICounterModifier,
    &GENERATED_ArkUINodeModifiers::getCounterModifier, GENERATED_ARKUI_COUNTER> {
public:

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<CounterTheme>();

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setEnableDecTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableDecTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_DEC_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ENABLE_DEC_DEFAULT_VALUE);
}

/*
 * @tc.name: setEnableDecTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableDecTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEnableDec(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_DEC_NAME);
    EXPECT_EQ(strResult, "false");

    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEnableDec(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_DEC_NAME);
    EXPECT_EQ(strResult, "true");
}

/*
 * @tc.name: setEnableIncTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableIncTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_INC_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ENABLE_INC_DEFAULT_VALUE);
}

/*
 * @tc.name: setEnableIncTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableIncTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEnableInc(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_INC_NAME);
    EXPECT_EQ(strResult, "false");

    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEnableInc(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_INC_NAME);
    EXPECT_EQ(strResult, "true");
}

/*
 * @tc.name: setOnIncTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setOnIncTest, TestSize.Level1)
{
    VoidCallback func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    auto addId = pattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    auto subGestureHub = addNode->GetOrCreateGestureEventHub();

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::counterEventsReceiver.onInc = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .value = 1
        };
    };

    modifier_->setOnInc(node_, &func);

    EXPECT_EQ(checkEvent.has_value(), false);
    subGestureHub->ActClick();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->value, 1);
}

/*
 * @tc.name: setOnDecTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setOnDecTest, TestSize.Level1)
{
    VoidCallback func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    auto subId = pattern->GetSubId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    auto subGestureHub = addNode->GetOrCreateGestureEventHub();

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::counterEventsReceiver.onDec = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .value = -1
        };
    };

    modifier_->setOnDec(node_, &func);

    EXPECT_EQ(checkEvent.has_value(), false);
    subGestureHub->ActClick();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->value, -1);
}

/*
 * @tc.name: setBackgroundColorTest
 * @tc.desc: Check the functionality of CounterModifierTest.setBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setBackgroundColorTest, TestSize.Level1)
{
    using OneTestStep = std::pair<Ark_ResourceColor, std::string>;
    static const std::string PROP_NAME("backgroundColor");
    static auto resName = NamedResourceId("aa.bb.cc", NodeModifier::ResourceType::COLOR);
    static auto resId = IntResourceId(1234, NodeModifier::ResourceType::COLOR);
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { CreateResourceUnion<Ark_ResourceColor>(resName), EXPECTED_RESOURCE_COLOR },
        { CreateResourceUnion<Ark_ResourceColor>(resId), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(commonModifier_->setBackgroundColor, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::TRANSPARENT.ToString());

    for (const auto &[arkResColor, expected]: testPlan) {
        commonModifier_->setBackgroundColor(node_, &arkResColor);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

/*
 * @tc.name: setWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setWidthTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setWidthTestValidValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        commonModifier_->setWidth(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setWidthTestInvalidValues, TestSize.Level1)
{
    static const std::vector<Ark_Length> testPlan = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
    };

    for (const auto &arkLength : testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        commonModifier_->setWidth(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    }

    commonModifier_->setWidth(node_, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setHeightTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

/*
 * @tc.name: setHeightTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setHeightTestValidValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        commonModifier_->setHeight(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setHeightTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setHeightTestInvalidValues, TestSize.Level1)
{
    static const std::vector<Ark_Length> testPlan = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
    };

    for (const auto &arkLength : testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        commonModifier_->setHeight(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    commonModifier_->setHeight(node_, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

/*
 * @tc.name: setSizeTestValidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setSizeTestValidHeightValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_SizeOptions inputValue;
        inputValue.height = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        commonModifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setSizeTestValidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setSizeTestValidWidthValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_SizeOptions inputValue;
        inputValue.width = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        commonModifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setSizeTestInvalidValues, TestSize.Level1)
{
    Ark_SizeOptions inputValue;

    static const std::vector<Ark_Length> testPlan = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
    };

    for (const auto &arkLength : testPlan) {
        inputValue.width = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        commonModifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &arkLength : testPlan) {
        inputValue.height = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        commonModifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    commonModifier_->setSize(node_, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}
} // namespace OHOS::Ace::NG
