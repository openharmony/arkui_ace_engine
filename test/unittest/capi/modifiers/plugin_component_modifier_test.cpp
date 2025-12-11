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
#include "generated/type_helpers.h"

#include "core/components_ng/pattern/plugin/plugin_event_hub.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TEMPLATE_NAME = "template";
const auto ATTRIBUTE_TEMPLATE_I_SOURCE_NAME = "source";
const auto ATTRIBUTE_TEMPLATE_I_SOURCE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_NAME = "bundleName";
const auto ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEMPLATE_I_DATA_NAME = "data";
const auto ATTRIBUTE_TEMPLATE_I_DATA_DEFAULT_VALUE = "";

enum ResID {
    STRING_RES_0_ID,
    STRING_RES_1_ID,
    STRING_RES_2_ID
};

constexpr auto STRING_RES_0_STR = "STRING_RES_0_STR";
constexpr auto STRING_RES_1_STR = "STRING_RES_1_STR";
constexpr auto STRING_RES_2_STR = "STRING_RES_2_STR";

// Fixture 'String' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
    { "\"\"", Converter::ArkValue<Ark_String>(""), "" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz"), "xyz" },
};

std::vector<std::tuple<ResID, std::string, ResRawValue>> resourceInitTable = {
    { STRING_RES_0_ID, STRING_RES_0_STR, "abc" },
    { STRING_RES_1_ID, STRING_RES_1_STR, "" },
    { STRING_RES_2_ID, STRING_RES_2_STR, "xyz" },
};
} // namespace

class PluginComponentModifierTest
    : public ModifierTestBase<GENERATED_ArkUIPluginComponentModifier,
          &GENERATED_ArkUINodeModifiers::getPluginComponentModifier, GENERATED_ARKUI_PLUGIN_COMPONENT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setPluginComponentOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PluginComponentModifierTest, setPluginComponentOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTemplate =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEMPLATE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_SOURCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEMPLATE_I_SOURCE_DEFAULT_VALUE) <<
        "Default value for attribute 'options.template.source'";

    resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_DEFAULT_VALUE) <<
        "Default value for attribute 'options.template.bundleName'";

    resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_DATA_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEMPLATE_I_DATA_DEFAULT_VALUE) <<
        "Default value for attribute 'options.data'";
}

/*
 * @tc.name: setPluginComponentOptionsTestOptionsTemplateSourceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PluginComponentModifierTest, DISABLED_setPluginComponentOptionsTestOptionsTemplateSourceValidValues,
    TestSize.Level1)
{
    Ark_PluginComponentOptions initValueOptions;

    // Initial setup
    initValueOptions.template_.source = Converter::ArkValue<Opt_String>(std::get<1>(testFixtureStringValidValues[0]));
    initValueOptions.template_.bundleName =
        Converter::ArkValue<Opt_String>(std::get<1>(testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_PluginComponentOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.template_.source = Converter::ArkValue<Opt_String>(value);
        modifier_->setPluginComponentOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultTemplate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEMPLATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_SOURCE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPluginComponentOptions, attribute: options.template.source";
    };

    for (auto& [input, value, expected] : testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPluginComponentOptionsTestOptionsTemplateBundleNameValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    PluginComponentModifierTest, setPluginComponentOptionsTestOptionsTemplateBundleNameValidValues, TestSize.Level1)
{
    Ark_PluginComponentOptions initValueOptions;

    // Initial setup
    initValueOptions.template_.source = Converter::ArkValue<Opt_String>(std::get<1>(testFixtureStringValidValues[0]));
    initValueOptions.template_.bundleName =
        Converter::ArkValue<Opt_String>(std::get<1>(testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_PluginComponentOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.template_.bundleName = Converter::ArkValue<Opt_String>(value);
        modifier_->setPluginComponentOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultTemplate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEMPLATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input <<
            ", method: setPluginComponentOptions, attribute: options.template.bundleName";
    };

    for (auto& [input, value, expected] : testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setOnCompleteTest
 * @tc.desc: check functionality setOnComplete
 * @tc.type: FUNC
 */
HWTEST_F(PluginComponentModifierTest, setOnCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<PluginEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .nodeId = resourceId
        };
    };

    auto callback = Converter::ArkValue<VoidCallback>(checkCallback, contextId);
    auto arkCallback = Converter::ArkValue<Opt_VoidCallback>(callback);

    modifier_->setOnComplete(node_, &arkCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireOnComplete("");
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, contextId);
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc: check functionality setOnError
 * @tc.type: FUNC
 */
HWTEST_F(PluginComponentModifierTest, setOnErrorTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<PluginEventHub>();

    constexpr auto errCode = "404";
    constexpr auto msg = "not found";

    struct CheckEvent {
        int32_t nodeId;
        int errorCode;
        std::string message;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_PluginErrorData info) {
        checkEvent = {
            .nodeId = resourceId,
            .errorCode = Convert<int>(info.errcode),
            .message = Convert<std::string>(info.msg)
        };
    };

    auto callback = ArkValue<PluginErrorCallback>(checkCallback, contextId);
    auto arkCallback = ArkValue<Opt_PluginErrorCallback>(callback);

    modifier_->setOnError(node_, &arkCallback);

    EXPECT_FALSE(checkEvent);
    auto errorJSON = JsonUtil::Create(true);
    errorJSON->Put("errcode", errCode);
    errorJSON->Put("msg", msg);
    eventHub->FireOnError(errorJSON->ToString());
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(std::to_string(checkEvent->errorCode), errCode);
    EXPECT_EQ(checkEvent->message, msg);
}
} // namespace OHOS::Ace::NG
