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
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

    struct EventsTracker {
        static inline GENERATED_ArkUITextEventsReceiver textEventReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getTextEventsReceiver = [] () -> const GENERATED_ArkUITextEventsReceiver* {
                return &textEventReceiver;
            }
        };
    };
} // namespace

class TextModifierTest : public ModifierTestBase<GENERATED_ArkUITextModifier,
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

        // AddResource(FLOAT_RES_0_ID, FLOAT_RES_0_VALUE);
        // AddResource(FLOAT_RES_1_ID, FLOAT_RES_1_VALUE);
        // AddResource(FLOAT_RES_2_ID, FLOAT_RES_2_STORED_VALUE);

        // setup the test event handler
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setTextOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, bindSelectionMenuTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    std::cout << std::endl << jsonValue->ToString() << std::endl;

    // resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    // EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";
}

/*
 * @tc.name: setTextOptionsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, bindSelectionMenuTestValidValues, TestSize.Level1)
{
    // auto checkValue = [this](const std::string& input, const std::string& expectedStr,
    //                       const Opt_Union_String_Resource& value) {
    //     auto textOptions = Converter::ArkValue<Opt_TextOptions>(Ark_Empty());

    //     modifier_->setTextOptions(node_, &value, &textOptions);
    //     auto jsonValue = GetJsonValue(node_);
    //     auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    //     EXPECT_EQ(resultStr, expectedStr) <<
    //         "Input value is: " << input << ", method: setTextOptions, attribute: content";
    // };

    // for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
    //     checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    // }
    // for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
    //     checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    // }
}

