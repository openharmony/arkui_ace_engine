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
#include <tuple>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "generated/test_fixtures.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/* 
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
} // OHOS::Ace::NG::Converter

namespace  {
    const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
    const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto OPACITY_COLOR = "#FF000000";
    const auto ATTRIBUTE_AUTO_RESIZE_NAME = "autoResize";
    const auto ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE = "false";

    struct EventsTracker {
        static inline GENERATED_ArkUIImageEventsReceiver getImageEventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getImageEventsReceiver = [] () -> const GENERATED_ArkUIImageEventsReceiver* {
                return &getImageEventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace
 */
class MediaCachedImageModifierTest : public ModifierTestBase<GENERATED_ArkUIMediaCachedImageModifier,
    &GENERATED_ArkUINodeModifiers::getMediaCachedImageModifier,
    GENERATED_ARKUI_MEDIA_CACHED_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        for (auto&& res : Fixtures::resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
        }
        // fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};
/*
 * @tc.name: setMediaCachedImageOptionsTest
 * @tc.desc: Check functionality of MediaCachedImageInterface.setMediaCachedImageOptions
 * @tc.type: FUNC
 */
HWTEST_F(MediaCachedImageModifierTest, setMediaCachedImageOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMediaCachedImageOptions, nullptr);

    const std::string expectedSource = "sourceData";
    const std::string expectedModule = {};

    auto arkValue =
        Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource, Ark_ResourceStr>(
            Converter::ArkUnion<Ark_ResourceStr, Ark_String>(expectedSource)
        );
    modifier_->setMediaCachedImageOptions(node_, &arkValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    EXPECT_EQ(GetAttrValue<std::string>(jsonValue, "rawSrc"), expectedSource);
    EXPECT_EQ(GetAttrValue<std::string>(jsonValue, "moduleName"), expectedModule);
}
} // namespace OHOS::Ace::NG