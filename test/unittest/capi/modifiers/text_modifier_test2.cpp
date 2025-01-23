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
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"

#include "core/interfaces/native/implementation/text_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "generated/type_helpers.h"

#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_BIND_SELECTION_MENU_NAME = "bindSelectionMenu";
    const auto ATTRIBUTE_BIND_SELECTION_MENU_DEFAULT_VALUE = "[]";

    struct EventsTracker {
        static inline GENERATED_ArkUITextEventsReceiver textEventReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getTextEventsReceiver = [] () -> const GENERATED_ArkUITextEventsReceiver* {
                return &textEventReceiver;
            }
        };
    };
} // namespace

struct SelectionMenuOptions {
    std::optional<MenuOnAppearCallback> onAppear;
    std::optional<Callback_Void> onDisappear;
    std::optional<Ark_MenuType> menuType;
};

namespace Converter {
    void AssignArkValue(Ark_SelectionMenuOptions& dst, const SelectionMenuOptions& src, ConvContext *ctx = nullptr)
    {
        dst.onAppear = Converter::ArkValue<Opt_MenuOnAppearCallback>(src.onAppear);
        dst.onDisappear = Converter::ArkValue<Opt_Callback_Void>(src.onDisappear);
        dst.menuType = Converter::ArkValue<Opt_MenuType>(src.menuType);
    }
}

class TextModifierTest2 : public ModifierTestBase<GENERATED_ArkUITextModifier,
    &GENERATED_ArkUINodeModifiers::getTextModifier, GENERATED_ARKUI_TEXT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }

        // setup the test event handler
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: bindSelectionMenuTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest2, bindSelectionMenuTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BIND_SELECTION_MENU_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BIND_SELECTION_MENU_DEFAULT_VALUE) <<
        "Default value for attribute 'BindSelectionMenu'";
}

/*
 * @tc.name: bindSelectionMenuTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
using OneTestStep = std::tuple<Ark_TextSpanType, CustomNodeBuilder, Ark_TextResponseType>;
static const std::vector<OneTestStep> testPlan = {
    {ARK_TEXT_SPAN_TYPE_TEXT, builder, ARK_TEXT_RESPONSE_TYPE_SELECT},
    {ARK_TEXT_SPAN_TYPE_MIXED, builder, ARK_TEXT_RESPONSE_TYPE_SELECT},
    {ARK_TEXT_SPAN_TYPE_IMAGE, builder, ARK_TEXT_RESPONSE_TYPE_SELECT},
    {ARK_TEXT_SPAN_TYPE_TEXT, builder, ARK_TEXT_RESPONSE_TYPE_LONG_PRESS},
    {ARK_TEXT_SPAN_TYPE_MIXED, builder, ARK_TEXT_RESPONSE_TYPE_LONG_PRESS},
    {ARK_TEXT_SPAN_TYPE_IMAGE, builder, ARK_TEXT_RESPONSE_TYPE_LONG_PRESS},
    {ARK_TEXT_SPAN_TYPE_TEXT, builder, ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK},
    {ARK_TEXT_SPAN_TYPE_MIXED, builder, ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK},
    {ARK_TEXT_SPAN_TYPE_IMAGE, builder, ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK},
};

HWTEST_F(TextModifierTest2, bindSelectionMenuTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSelectionMenu, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int callsCount(0);
    CustomNodeBuilderTestHelper<TextModifierTest2> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();

    std::unique_ptr<JsonValue> fullJson;
    std::string resultValue;
    SelectionMenuOptions selectionMenuOptions1 = {.onAppear = std::nullopt, .onDisappear = std::nullopt,
        .menuType = Ark_MenuType::ARK_MENU_TYPE_SELECTION_MENU};
    auto options1 = Converter::ArkValue<Opt_SelectionMenuOptions>(selectionMenuOptions1);

    SelectionMenuOptions selectionMenuOptions2 = {.onAppear = std::nullopt, .onDisappear = std::nullopt,
        .menuType = Ark_MenuType::ARK_MENU_TYPE_PREVIEW_MENU};
    auto options2 = Converter::ArkValue<Opt_SelectionMenuOptions>(selectionMenuOptions2);

    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectOverlayInfo selectInfo;

    for (auto [spanType, content, responseType]: testPlan) {
        modifier_->setBindSelectionMenu(node_, spanType, &content, responseType, &options1);
        pattern->CopySelectionMenuParams(selectInfo);
        ASSERT_NE(selectInfo.menuInfo.menuBuilder, nullptr);
        selectInfo.menuInfo.menuBuilder();
        EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
        modifier_->setBindSelectionMenu(node_, spanType, &content, responseType, &options2);
        pattern->CopySelectionMenuParams(selectInfo);
        ASSERT_NE(selectInfo.menuInfo.menuBuilder, nullptr);
        selectInfo.menuInfo.menuBuilder();
        EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
        fullJson = GetJsonValue(node_);
        resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BIND_SELECTION_MENU_NAME);
    }

    std::string expectedValue =
        "[{\"spanType\":0,\"responseType\":0,\"menuType\":0},"
        "{\"spanType\":0,\"responseType\":1,\"menuType\":0},"
        "{\"spanType\":0,\"responseType\":2,\"menuType\":0},"
        "{\"spanType\":1,\"responseType\":0,\"menuType\":0},"
        "{\"spanType\":1,\"responseType\":1,\"menuType\":0},"
        "{\"spanType\":1,\"responseType\":2,\"menuType\":0},"
        "{\"spanType\":2,\"responseType\":0,\"menuType\":0},"
        "{\"spanType\":2,\"responseType\":1,\"menuType\":0},"
        "{\"spanType\":2,\"responseType\":2,\"menuType\":0}]";
    EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
}
}