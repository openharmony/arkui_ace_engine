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
template<>
Ark_MotionPathOptions ArkValue(const MotionPathOption& src)
{
    Ark_MotionPathOptions dst;
    dst.path = ArkValue<Ark_String>(src.GetPath());
    dst.from = ArkValue<Opt_Number>(src.GetBegin());
    dst.to = ArkValue<Opt_Number>(src.GetEnd());
    dst.rotatable = ArkValue<Opt_Boolean>(src.GetRotate());
    return dst;
}
} // namespace Converter

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
    ASSERT_NE(modifier_->setMotionPath, nullptr);
    using OneTestStep = std::tuple<Ark_MotionPathOptions, std::string>;
    Ark_MotionPathOptions v = {
        .path = Converter::ArkValue<Ark_String>("path"),
        .from = Converter::ArkValue<Opt_Number>(1),
        .to = Converter::ArkValue<Opt_Number>(2),
        .rotatable = Converter::ArkValue<Opt_Boolean>(true),
    };
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_MotionPathOptions>(v), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
}
