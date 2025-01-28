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
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "generated/test_fixtures.h"
#include "point_light_test.h"
#include "generated/type_helpers.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::TypeHelper;
using namespace OHOS::Ace::NG::PointLight;

namespace OHOS::Ace::NG {
namespace Converter {
template<>
LoadImageFailEvent Convert(const Ark_ImageError& info)
{
    auto width = Convert<float>(info.componentWidth);
    auto height = Convert<float>(info.componentHeight);
    auto error = Convert<std::string>(info.message);
    LoadImageFailEvent event(width, height, error);
    return event;
}

template<>
LoadImageSuccessEvent Convert(const Ark_Type_ImageAttribute_onComplete_callback_event& event)
{
    LoadImageSuccessEvent info(
        Convert<float>(event.width),
        Convert<float>(event.height),
        Convert<float>(event.componentWidth),
        Convert<float>(event.componentHeight),
        Convert<int>(event.loadingStatus),
        Convert<float>(event.contentOffsetX),
        Convert<float>(event.contentOffsetY),
        Convert<float>(event.contentWidth),
        Convert<float>(event.contentHeight)
    );
    return info;
}
} // OHOS::Ace::NG::Converter

namespace  {
    
    const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
    const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";

    // Valid values for boolean values
    const std::vector<std::tuple<std::string, Ark_Boolean, std::string>> validBoolean = {
        {"true", ArkValue<Ark_Boolean>(true), "true"},
        {"false", ArkValue<Ark_Boolean>(false), "false"},
    };

    struct EventsTracker {
        static inline GENERATED_ArkUIImageEventsReceiver getImageEventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getImageEventsReceiver = [] () -> const GENERATED_ArkUIImageEventsReceiver* {
                return &getImageEventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class ImageModifierTest : public ModifierTestBase<GENERATED_ArkUIImageModifier,
    &GENERATED_ArkUINodeModifiers::getImageModifier,
    GENERATED_ARKUI_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        for (auto&& res : Fixtures::resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
        }

        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};
// /*
//  * @tc.name: setFillColorTestDefaultValues
//  * @tc.desc: Check functionality of ImageModifier.setFillColor
//  * @tc.type: FUNC
//  */
// HWTEST_F(ImageModifierTest, setFillColorTestDefaultValues, TestSize.Level1)
// {
//     std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
//     std::string resultStr;

//     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
//     EXPECT_EQ(resultStr, ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
// }

// /*
//  * @tc.name: setFillColorTestValidValues
//  * @tc.desc: Check functionality of ImageModifier.setFillColor
//  * @tc.type: FUNC
//  */
// HWTEST_F(ImageModifierTest, setFillColorTestValidValues, TestSize.Level1)
// {
//     auto checkValue = [this](const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
//         modifier_->setFillColor(node_, &value);
//         auto jsonValue = GetJsonValue(node_);
//         auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
//         EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
//     };

//     for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
//         checkValue(std::get<0>(value), ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)),
//             std::get<2>(value));
//     }
//     for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
//         checkValue(std::get<0>(value), ArkUnion<Ark_ResourceColor,
//             Ark_String>(std::get<1>(value)), OPACITY_COLOR);
//     }
//     for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
//         checkValue(std::get<0>(value), ArkUnion<Ark_ResourceColor, Ark_Number>(std::get<1>(value)),
//             std::get<2>(value));
//     }
//     for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
//         checkValue(std::get<0>(value), ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
//             std::get<2>(value));
//     }
//     for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
//         checkValue(std::get<0>(value), ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)),
//             std::get<2>(value));
//     }
//     for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
//         checkValue(std::get<0>(value), ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)),
//             ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
//     }
// }

} // namespace OHOS::Ace::NG
