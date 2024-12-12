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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_MOTION_PATH_NAME = "motionPath";
    const auto ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE = "";
}
namespace Converter {
    // template<>
    // Array_FractionStop ArkValue(const std::vector<std::pair<float, float>>& fractionStopValue)
    // {
    //     Array_FractionStop arr;
    //     arr.length = fractionStopValue.size();
    //     arr.array = new Ark_FractionStop[arr.length];
    //     for (auto i = 0; i < fractionStopValue.size(); ++i) {
    //         arr.array[i].value0 = ArkValue<Ark_Number>(fractionStopValue[i].first);
    //         arr.array[i].value1 = ArkValue<Ark_Number>(fractionStopValue[i].second);
    //     }
    //     return arr;
    // }
    // template<>
    // void AssignArkValue(Opt_BlendApplyType& dst, const BlendApplyType& src)
    // {
    //     Ark_BlendApplyType arkDst;
    //     switch (src) {
    //         case BlendApplyType::FAST: arkDst = ARK_BLEND_APPLY_TYPE_FAST; break;
    //         case BlendApplyType::OFFSCREEN: arkDst = ARK_BLEND_APPLY_TYPE_OFFSCREEN; break;
    //         default:
    //             arkDst = ARK_BLEND_APPLY_TYPE_FAST;
    //     }
    //     dst = ArkValue<Opt_BlendApplyType>(arkDst);
    // }
}

class CommonMethodModifierTest8 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;
};

/*
 * @tc.name: setMotionPathTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setMotionPathTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_MOTION_PATH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE);
}

/*
 * @tc.name: setMotionPathTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setMotionPathTestValidValues, TestSize.Level1)
{
    LOGE("The type `Ark_Union_CircleShape_EllipseShape_PathShape_RectShape` contains "
        "fields of type `Ark_CustomObject`, which are not supported.");
}
}
