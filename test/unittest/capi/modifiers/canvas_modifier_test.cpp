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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_event_hub.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace {
// Attribute names
const auto ATTRIBUTE_CANVAS_NAME = "canvas";
const auto ATTRIBUTE_ENABLE_ANALYZER_NAME = "enableAnalyzer";

// Default values
const auto ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE = false;

// Test plans
typedef std::pair<Ark_Boolean, bool> BoolTest;
const std::vector<BoolTest> BOOL_TEST_PLAN = {
    { false, false },
    { true, true },
    { 0, false },
    { -25, true },
    { 25, true },
};

} // namespace
namespace OHOS::Ace::NG {

class CanvasModifierTest : public ModifierTestBase<GENERATED_ArkUICanvasModifier,
    &GENERATED_ArkUINodeModifiers::getCanvasModifier, GENERATED_ARKUI_CANVAS> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: DISABLED_setOnReadyTest
 * @tc.desc:  Check the functionality of CanvasModifier.OnReadyImpl
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setOnReadyTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnReady, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<CanvasEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const int32_t contextId = 123;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId) {
        checkEvent = {
            .nodeId = resourceId,
        };
    };
    auto func = Converter::ArkValue<VoidCallback>(checkCallback, contextId);
    auto optFunk = Converter::ArkValue<Opt_VoidCallback>(func);
    modifier_->setOnReady(node_, &optFunk);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireReadyEvent();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, contextId);
}

/*
 * @tc.name: setEnableAnalyzerTestValidValues
 * @tc.desc: Check the functionality of CanvasModifier.EnableAnalyzerImpl
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setEnableAnalyzerTestValidValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto canvasObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_CANVAS_NAME);
    auto initialValue = GetAttrValue<bool>(canvasObject, ATTRIBUTE_ENABLE_ANALYZER_NAME);

    EXPECT_EQ(initialValue, ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE);

    for (auto testValue : BOOL_TEST_PLAN) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(testValue.first);
        modifier_->setEnableAnalyzer(node_, &inputValue);

        auto fullJson = GetJsonValue(node_);
        auto canvasObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_CANVAS_NAME);
        auto checkValue = GetAttrValue<bool>(canvasObject, ATTRIBUTE_ENABLE_ANALYZER_NAME);
        EXPECT_EQ(checkValue, testValue.second);
    }
}

} // namespace OHOS::Ace::NG
