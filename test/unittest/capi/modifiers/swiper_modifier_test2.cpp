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

#undef UNITEST_FRIEND_CLASS
#define UNITEST_FRIEND_CLASS friend class SwiperModifierTest2

#include "swiper_modifier_test.h"
#include "modifier_test_base.h"

#include "core/interfaces/native/implementation/swiper_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    static const auto ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE = 0;
    constexpr int32_t TEST_WILL_SCROLL_CURRENTINDEX = 0;
    constexpr int32_t TEST_WILL_SCROLL_COMINGINDEX = 10;
    constexpr int32_t TEST_WILL_SCROLL_OFFSET = 1;
}

namespace Converter {
template<>
void AssignArkValue(Opt_PageFlipMode& dst, const PageFlipMode& src, ConvContext *ctx)
{
    switch (src) {
        case PageFlipMode::CONTINUOUS:
            dst = Converter::ArkValue<Opt_PageFlipMode>(Ark_PageFlipMode::ARK_PAGE_FLIP_MODE_CONTINUOUS); break;
        case PageFlipMode::SINGLE:
            dst = Converter::ArkValue<Opt_PageFlipMode>(Ark_PageFlipMode::ARK_PAGE_FLIP_MODE_SINGLE); break;
        default:
            dst = {}; break;
    }
}
}

class SwiperModifierTest2 : public ModifierTestBase<GENERATED_ArkUISwiperModifier,
    &GENERATED_ArkUINodeModifiers::getSwiperModifier, GENERATED_ARKUI_SWIPER> {
public:
    std::optional<bool> OnContentWillScroll(FrameNode* node,
        int32_t currentIndex, int32_t comingIndex, float offset) const
    {
        CHECK_NULL_RETURN(node, std::nullopt);
        auto pattern = node->GetPattern<SwiperPattern>();
        CHECK_NULL_RETURN(pattern, std::nullopt);
        return pattern->OnContentWillScroll(currentIndex, comingIndex, offset);
    }
};

/**
 * @tc.name: setSwiperOptionsTest
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.SetSwiperOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setSwiperOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSwiperOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setSwiperOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_SwiperController>();
    modifier_->setSwiperOptions(node_, &controllerUndef);

    // set the invoke checker to the internal controller
    bool checkInvoke = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalSwiperController = SwiperModelNG::GetSwiperController(frameNode);
    ASSERT_NE(internalSwiperController, nullptr);
    internalSwiperController->SetShowNextImpl([&checkInvoke]() {
        checkInvoke = true;
    });

    // create the external SwiperController peer and attach modifier to it
    SwiperControllerPeer peer;
    auto controller = Converter::ArkValue<Opt_SwiperController>(&peer);
    modifier_->setSwiperOptions(node_, &controller);

    // check initial state of invoke checker
    EXPECT_FALSE(checkInvoke);

    // simulate the action from the external peer
    peer.TriggerShowNext();

    // check the expected state of invoke checker
    EXPECT_TRUE(checkInvoke);
}

/**
 * @tc.name: setPageFlipModeTestDefaultValue
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.PageFlipModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setPageFlipModeTestDefaultValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPageFlipMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetPageFlipMode(), ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE);
}

/**
 * @tc.name: setPageFlipModeTestValidValue
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.PageFlipModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setPageFlipModeTestValidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPageFlipMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    using OneTestStep = std::tuple<Opt_PageFlipMode, int32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_PageFlipMode>(PageFlipMode::CONTINUOUS), ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_PageFlipMode>(PageFlipMode::SINGLE), static_cast<int32_t>(PageFlipMode::SINGLE)},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setPageFlipMode(node_, &inputValue);
        EXPECT_EQ(pattern->GetPageFlipMode(), expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setPageFlipModeTestInvalidValue
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.PageFlipModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setPageFlipModeTestInvalidValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPageFlipMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    using OneTestStep = std::tuple<Opt_PageFlipMode, int32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Opt_PageFlipMode{.tag = Ark_Tag::INTEROP_TAG_UNDEFINED}, ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_PageFlipMode>(static_cast<PageFlipMode>(-1)), ATTRIBUTE_PAGE_FLIP_MODE_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setPageFlipMode(node_, &inputValue);
        EXPECT_EQ(pattern->GetPageFlipMode(), expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setOnSelectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setOnSelectedTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnSelected, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Number parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<int32_t>(parameter)
        };
    };

    Callback_Number_Void arkCallback = Converter::ArkValue<Callback_Number_Void>(checkCallback, contextId);

    modifier_->setOnSelected(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireSelectedEvent(1);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 1);
    eventHub->FireSelectedEvent(2);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 2);
}

/*
 * @tc.name: setOnUnselectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setOnUnselectedTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnUnselected, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Number parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<int32_t>(parameter)
        };
    };

    Callback_Number_Void arkCallback = Converter::ArkValue<Callback_Number_Void>(checkCallback, contextId);

    modifier_->setOnUnselected(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireUnselectedEvent(1);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 1);
    eventHub->FireUnselectedEvent(2);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 2);
}

/*
 * @tc.name: setOnContentWillScrollTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setOnContentWillScrollTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnContentWillScroll, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto result0 = OnContentWillScroll(frameNode, 0, 10, 1);
    EXPECT_FALSE(result0.has_value());

    struct CheckEvent {
        int32_t nodeId;
        int32_t currentIndex;
        int32_t comingIndex;
        int32_t offset;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_SwiperContentWillScrollResult result, const Callback_Boolean_Void continuation) {
            checkEvent = {
                .nodeId = resourceId,
                .currentIndex = Converter::Convert<int32_t>(result.currentIndex),
                .comingIndex = Converter::Convert<int32_t>(result.comingIndex),
                .offset = Converter::Convert<int32_t>(result.offset)
            };
            CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };
    auto arkCallback = Converter::ArkValue<ContentWillScrollCallback>(checkCallback, contextId);

    ASSERT_FALSE(checkEvent.has_value());
    modifier_->setOnContentWillScroll(node_, &arkCallback);
    auto result1 = OnContentWillScroll(frameNode,
        TEST_WILL_SCROLL_CURRENTINDEX, TEST_WILL_SCROLL_COMINGINDEX, TEST_WILL_SCROLL_OFFSET);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->currentIndex, TEST_WILL_SCROLL_CURRENTINDEX);
    EXPECT_EQ(checkEvent->comingIndex, TEST_WILL_SCROLL_COMINGINDEX);
    EXPECT_EQ(checkEvent->offset, TEST_WILL_SCROLL_OFFSET);
    ASSERT_TRUE(result1.has_value());
    EXPECT_FALSE(result1.value());
    callResult = true;
    checkEvent.reset();
    modifier_->setOnContentWillScroll(node_, &arkCallback);
    auto result2 = OnContentWillScroll(frameNode,
        TEST_WILL_SCROLL_CURRENTINDEX, TEST_WILL_SCROLL_COMINGINDEX, TEST_WILL_SCROLL_OFFSET);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->currentIndex, TEST_WILL_SCROLL_CURRENTINDEX);
    EXPECT_EQ(checkEvent->comingIndex, TEST_WILL_SCROLL_COMINGINDEX);
    EXPECT_EQ(checkEvent->offset, TEST_WILL_SCROLL_OFFSET);
    ASSERT_TRUE(result2.has_value());
    EXPECT_TRUE(result2.value());
}
} // namespace OHOS::Ace::NG
