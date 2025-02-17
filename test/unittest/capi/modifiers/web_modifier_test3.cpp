/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/interfaces/native/implementation/web_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_modifier_callbacks.h"
#endif // WEB_SUPPORTED

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {

struct SelectionMenuOptionsExt {
    std::optional<Callback_Void> onAppear;
    std::optional<Callback_Void> onDisappear;
    std::optional<CustomNodeBuilder> preview;
    std::optional<Ark_MenuType> menuType;
};

namespace Converter {
    void AssignArkValue(Ark_SelectionMenuOptionsExt& dst, const SelectionMenuOptionsExt& src,
                        ConvContext *ctx = nullptr)
    {
        dst.onAppear = Converter::ArkValue<Opt_Callback_Void>(src.onAppear);
        dst.onDisappear = Converter::ArkValue<Opt_Callback_Void>(src.onDisappear);
        dst.preview = Converter::ArkValue<Opt_CustomNodeBuilder>(src.preview);
        dst.menuType = Converter::ArkValue<Opt_MenuType>(src.menuType);
    }
}

namespace {
    const auto ATTRIBUTE_BIND_SELECTION_MENU_NAME = "bindSelectionMenu";
    const auto ATTRIBUTE_BIND_SELECTION_MENU_DEFAULT_VALUE = "";
#ifdef WEB_SUPPORTED
    const auto ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME = "defaultTextEncodingFormat";
    const std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues = {
        { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
        { "\"\"", Converter::ArkValue<Ark_String>(""), "UTF-8" },
        { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz"), "xyz" },
    };
#endif // WEB_SUPPORTED
} // namespace

class WebModifierTest3 : public ModifierTestBase<GENERATED_ArkUIWebModifier,
    &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
};

/*
 * @tc.name: bindSelectionMenuTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, bindSelectionMenuTestDefaultValues, TestSize.Level1)
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
HWTEST_F(WebModifierTest3, bindSelectionMenuTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSelectionMenu, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    CustomNodeBuilderTestHelper<WebModifierTest3> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    using OneTestStep = std::tuple<Ark_WebElementType, CustomNodeBuilder, Ark_WebResponseType>;

    static const std::vector<OneTestStep> testPlan = {
        {ARK_WEB_ELEMENT_TYPE_IMAGE, builder, ARK_WEB_RESPONSE_TYPE_LONG_PRESS},
    };

    std::unique_ptr<JsonValue> fullJson;
    std::string resultValue;
    SelectionMenuOptionsExt selectionMenuOptions = {.onAppear = std::nullopt, .onDisappear = std::nullopt,
        .preview = std::nullopt, .menuType = Ark_MenuType::ARK_MENU_TYPE_SELECTION_MENU};
    auto options = Converter::ArkValue<Opt_SelectionMenuOptionsExt>(selectionMenuOptions);

    #ifdef WEB_SUPPORTED
    int callsCount(0);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    ASSERT_NE(webPattern, nullptr);
    #endif // WEB_SUPPORTED

    for (auto [spanType, builder, responseType]: testPlan) {
        modifier_->setBindSelectionMenu(node_, spanType, &builder, responseType, &options);
        #ifdef WEB_SUPPORTED
        WebElementType convType = Converter::OptConvert<WebElementType>(spanType).value();
        ResponseType convResponseType = Converter::OptConvert<ResponseType>(responseType).value();
        std::shared_ptr<WebPreviewSelectionMenuParam> reviewSelectionMenuParams =
            webPattern->GetPreviewSelectionMenuParams(convType, convResponseType);
        ASSERT_NE(reviewSelectionMenuParams, nullptr);
        reviewSelectionMenuParams->menuBuilder();
        EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
        #endif // WEB_SUPPORTED

        fullJson = GetJsonValue(node_);
        resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BIND_SELECTION_MENU_NAME);
    }
    std::string expectedValue = "";
    EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
}

/*
 * @tc.name: setDefaultTextEncodingFormatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setDefaultTextEncodingFormatValidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    Ark_String initValueDefaultTextEncodingFormat;
    // Initial setup
    initValueDefaultTextEncodingFormat = std::get<1>(testFixtureStringValidValues[0]);
    auto checkValue = [this, &initValueDefaultTextEncodingFormat](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueDefaultTextEncodingFormat = initValueDefaultTextEncodingFormat;
        inputValueDefaultTextEncodingFormat = value;
        modifier_->setDefaultTextEncodingFormat(node_, &inputValueDefaultTextEncodingFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr);
    };
    for (auto& [input, value, expected] : testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
#endif
}

} // namespace OHOS::Ace::NG