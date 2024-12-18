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
    const auto ATTRIBUTE_GEOMETRY_TRANSITION_NAME = "geometryTransition";
    const auto ATTRIBUTE_GEOMETRY_TRANSITION_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_RESTORE_ID_NAME = "restoreId";
    const auto ATTRIBUTE_RESTORE_ID_DEFAULT_VALUE = "";
}
namespace Converter {

} // namespace Converter

class CommonMethodModifierTest8 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
};

///////// GeometryTransition
/*
 * @tc.name: setGeometryTransitionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setGeometryTransitionTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_GEOMETRY_TRANSITION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_GEOMETRY_TRANSITION_DEFAULT_VALUE);
}

/*
 * @tc.name: setGeometryTransitionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC /data/home/mlobakh/BZ_OHOS/OHOS/interface/sdk-js/api/@internal/component/ets/common.d.ts
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setGeometryTransitionTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGeometryTransition0, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("id1"), "id1"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setGeometryTransition0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GEOMETRY_TRANSITION_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

///////// RestoreId
/*
 * @tc.name: setRestoreIdTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setRestoreIdTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_RESTORE_ID_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_RESTORE_ID_DEFAULT_VALUE);
}

/*
 * @tc.name: setRestoreIdTestValidValues
 * @tc.desc:
 * @tc.type: FUNC /data/home/mlobakh/BZ_OHOS/OHOS/interface/sdk-js/api/@internal/component/ets/common.d.ts
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setRestoreIdTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setRestoreId, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(1), "1"},
        {Converter::ArkValue<Ark_Number>(2), "2"},
        {Converter::ArkValue<Ark_Number>(3), "3"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setRestoreId(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        // std::cout << "\n********* " << fullJson->ToString() << "\n";
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_RESTORE_ID_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
}