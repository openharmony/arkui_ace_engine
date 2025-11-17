/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr auto ATTRIBUTE_DIRECTION_NAME = "scrollBarDirection";
constexpr auto ATTRIBUTE_DIRECTION_DEFAULT_VALUE = "ScrollBarDirection.Vertical";
constexpr auto ATTRIBUTE_STATE_NAME = "state";
constexpr auto ATTRIBUTE_STATE_DEFAULT_VALUE = "BarState.Auto";
constexpr auto ATTRIBUTE_VISIBILITY_NAME = "visibility";
constexpr auto ATTRIBUTE_VISIBILITY_DEFAULT_VALUE = "Visibility.Visible";
constexpr auto ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME = "enableNestedScroll";
constexpr auto ATTRIBUTE_ENABLE_NESTED_SCROLL_DEFAULT_VALUE = "false";

struct ScrollBarOptions {
    Ark_ScrollBarOptions value;

    explicit ScrollBarOptions(const GENERATED_ArkUIFullNodeAPI *api,
        const RefPtr<ScrollProxy>& proxy,
        const std::optional<Ark_ScrollBarDirection>& direction = std::nullopt,
        const std::optional<Ark_BarState>& state = std::nullopt) : fullAPI_(api)
    {
        auto peer = fullAPI_->getAccessors()->getScrollerAccessor()->construct();
        auto scrollerPeer = static_cast<ScrollerPeer *>(peer);
        scrollerPeer->SetScrollBarProxy(proxy);
        value = {
            .scroller = scrollerPeer,
            .direction = direction
                ? Converter::ArkValue<Opt_ScrollBarDirection>(direction.value())
                : Converter::ArkValue<Opt_ScrollBarDirection>(Ark_Empty()),
            .state = state
                ? Converter::ArkValue<Opt_BarState>(state.value())
                : Converter::ArkValue<Opt_BarState>(Ark_Empty()),
        };
    }

    ~ScrollBarOptions()
    {
        auto destroy = reinterpret_cast<void (*)(Ark_NativePointer)>(
            fullAPI_->getAccessors()->getScrollerAccessor()->getFinalizer()
        );
        destroy(value.scroller);
    }
    ACE_DISALLOW_COPY_AND_MOVE(ScrollBarOptions);
    const GENERATED_ArkUIFullNodeAPI *fullAPI_;
};

template<class T> using TestCases = std::vector<std::tuple<std::string, T, std::string>>;
} // namespace

class ScrollBarModifierTest : public ModifierTestBase<GENERATED_ArkUIScrollBarModifier,
    &GENERATED_ArkUINodeModifiers::getScrollBarModifier, GENERATED_ARKUI_SCROLL_BAR> {
};

/*
 * @tc.name: setScrollBarOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, DISABLED_setScrollBarOptionsTestDefaultValues, TestSize.Level1)
{
    const auto jsonLayout = GetJsonValue(node_);

    auto resultStr = GetAttrValue<std::string>(jsonLayout, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonLayout, ATTRIBUTE_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonLayout, ATTRIBUTE_VISIBILITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VISIBILITY_DEFAULT_VALUE);
}

/*
 * @tc.name: setScrollBarOptionsScrollerTestValidValues
 * @tc.desc: Checking that the object is set to the pattern and peer.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, setScrollBarOptionsScrollerTestValidValues, TestSize.Level1)
{
    const auto proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    ScrollBarOptions options(fullAPI_, proxy);

    modifier_->setScrollBarOptions(node_, &options.value);

    auto peer = options.value.scroller;
    ASSERT_NE(peer, nullptr);
    EXPECT_EQ(peer->GetScrollBarProxy(), proxy);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NG::ScrollBarPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto patternProxy = pattern->GetScrollBarProxy();
    EXPECT_EQ(patternProxy, proxy);
}

/*
 * @tc.name: setScrollBarOptionsDirectionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, DISABLED_setScrollBarOptionsDirectionTestValidValues, TestSize.Level1)
{
    ScrollBarOptions optionsVertical(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(),
        ARK_SCROLL_BAR_DIRECTION_VERTICAL);
    ScrollBarOptions optionsHorizontal(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(),
        ARK_SCROLL_BAR_DIRECTION_HORIZONTAL);
    const TestCases<ScrollBarOptions&> optionsList {
        {"ARK_SCROLL_BAR_DIRECTION_VERTICAL", optionsVertical, "ScrollBarDirection.Vertical"},
        {"ARK_SCROLL_BAR_DIRECTION_HORIZONTAL", optionsHorizontal, "ScrollBarDirection.Horizontal"},
    };
    for (auto& [input, options, expected] : optionsList) {
        modifier_->setScrollBarOptions(node_, &options.value);
        auto jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: setScrollBarOptions, attribute: " << ATTRIBUTE_DIRECTION_NAME;
    }
}

/*
 * @tc.name: setScrollBarOptionsDirectionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, DISABLED_setScrollBarOptionsDirectionTestInvalidValues, TestSize.Level1)
{
    ScrollBarOptions optionsValid(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(),
        ARK_SCROLL_BAR_DIRECTION_VERTICAL);
    const auto optionsValidStr = "ScrollBarDirection.Vertical";

    ScrollBarOptions optionsUndefined(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>());
    const TestCases<ScrollBarOptions&> optionsList {
        {"undefined", optionsUndefined, ATTRIBUTE_DIRECTION_DEFAULT_VALUE},
    };

    for (auto& [input, options, expected] : optionsList) {
        modifier_->setScrollBarOptions(node_, &optionsValid.value);
        auto jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(result, optionsValidStr);
        modifier_->setScrollBarOptions(node_, &options.value);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: setScrollBarOptions, attribute: " << ATTRIBUTE_DIRECTION_NAME;
    }
}

/*
 * @tc.name: setScrollBarOptionsStateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, setScrollBarOptionsStateTestValidValues, TestSize.Level1)
{
    ScrollBarOptions optionsOff(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(), std::nullopt, ARK_BAR_STATE_OFF);
    ScrollBarOptions optionsAuto(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(), std::nullopt,
        ARK_BAR_STATE_AUTO);
    ScrollBarOptions optionsOn(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(), std::nullopt, ARK_BAR_STATE_ON);
    const TestCases<ScrollBarOptions&> optionsList {
        {"ARK_BAR_STATE_OFF", optionsOff, "BarState.Off"},
        {"ARK_BAR_STATE_AUTO", optionsAuto, "BarState.Auto"},
        {"ARK_BAR_STATE_ON", optionsOn, "BarState.On"},
    };
    for (auto& [input, options, expected] : optionsList) {
        modifier_->setScrollBarOptions(node_, &options.value);
        auto jsonValue = GetJsonValue(node_);
        auto state = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(state, expected) <<
            "Input value is: " << input << ", method: setScrollBarOptions, attribute: " << ATTRIBUTE_STATE_NAME;
        auto visibility = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        auto expectedVisibility = input == "ARK_BAR_STATE_OFF" ? "Visibility.Hidden" : "Visibility.Visible";
        EXPECT_EQ(visibility, expectedVisibility) <<
            " Method: setScrollBarOptions, attribute: " << ATTRIBUTE_STATE_NAME;
    }
}

/*
 * @tc.name: setScrollBarOptionsStateTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, setScrollBarOptionsStateTestInvalidValues, TestSize.Level1)
{
    ScrollBarOptions optionsValid(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>(), std::nullopt, ARK_BAR_STATE_ON);
    const auto optionsValidStr = "BarState.On";

    ScrollBarOptions optionsUndefined(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>());
    const TestCases<ScrollBarOptions&> optionsList {
        {"undefined", optionsUndefined, ATTRIBUTE_STATE_DEFAULT_VALUE},
    };

    for (auto& [input, options, expected] : optionsList) {
        modifier_->setScrollBarOptions(node_, &optionsValid.value);
        auto jsonValue = GetJsonValue(node_);
        auto state = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(state, optionsValidStr);
        modifier_->setScrollBarOptions(node_, &options.value);
        jsonValue = GetJsonValue(node_);
        state = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(state, expected) <<
            "Input value is: " << input << ", method: setScrollBarOptions, attribute: " << ATTRIBUTE_STATE_NAME;
        auto visibility = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        auto expectedVisibility = input == "ARK_BAR_STATE_OFF" ? "Visibility.Hidden" : "Visibility.Visible";
        EXPECT_EQ(visibility, expectedVisibility) <<
            " Method: setScrollBarOptions, attribute: " << ATTRIBUTE_STATE_NAME;
    }
}

/*
 * @tc.name: setEnableNestedScrollTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, setEnableNestedScrollTestDefaultValues, TestSize.Level1)
{
    ScrollBarOptions options(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>());
    modifier_->setScrollBarOptions(node_, &options.value);
    auto jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME);
    EXPECT_EQ(result, ATTRIBUTE_ENABLE_NESTED_SCROLL_DEFAULT_VALUE) <<
        "Default value for attribute " << ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME;
}

/*
 * @tc.name: setEnableNestedScrollTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, setEnableNestedScrollTestValidValues, TestSize.Level1)
{
    ScrollBarOptions options(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>());
    const TestCases<Opt_Boolean> valueList {
        {
            "true",
            Converter::ArkValue<Opt_Boolean>(true),
            "true"
        },
        {
            "false",
            Converter::ArkValue<Opt_Boolean>(false),
            "false"
        },
    };

    modifier_->setScrollBarOptions(node_, &options.value);
    for (auto& [input, value, expected] : valueList) {
        modifier_->setEnableNestedScroll(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME);
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: setEnableNestedScroll, attribute: "
            << ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME;
    }
}

/*
 * @tc.name: setEnableNestedScrollTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarModifierTest, setEnableNestedScrollTestInvalidValues, TestSize.Level1)
{
    const auto validValue = Converter::ArkValue<Opt_Boolean>(true);
    const auto validStr = "true";

    ScrollBarOptions options(fullAPI_, AceType::MakeRefPtr<NG::ScrollBarProxy>());
    const TestCases<Opt_Boolean> valueList {
        {
            "undefined",
            Converter::ArkValue<Opt_Boolean>(),
            ATTRIBUTE_ENABLE_NESTED_SCROLL_DEFAULT_VALUE
        },
    };

    modifier_->setScrollBarOptions(node_, &options.value);
    for (auto& [input, value, expected] : valueList) {
        modifier_->setEnableNestedScroll(node_, &validValue);
        auto jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME);
        modifier_->setEnableNestedScroll(node_, &value);
        EXPECT_EQ(result, validStr);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME);
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: setEnableNestedScroll, attribute: "
            << ATTRIBUTE_ENABLE_NESTED_SCROLL_NAME;
    }
}

} // namespace OHOS::Ace::NG
