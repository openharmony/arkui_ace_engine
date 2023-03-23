/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/point_t.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_paint_property.h"
#include "core/event/touch_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.example.hello";
const std::string ABILITY_NAME = "MainAbility";
const std::string WANT = R"({bundleName: "com.example.hello", abilityName: "MainAbility"})";
} // namespace

class UIExtensionPatternTestNg : public testing::Test {};

/**
 * @tc.name: UIExtensionCreator001
 * @tc.desc: create UIExtension
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(UIExtensionPatternTestNg, UIExtensionCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create UIExtension Component.
     */
    auto model = UIExtensionModelNG();
    model.Create(BUNDLE_NAME, ABILITY_NAME);
    model.SetWant(WANT);

    /**
     * @tc.steps: step1. Create UIExtension component.
     * @tc.expected: expect paintProperty want
     */
    auto uiExtensionNode =
        AceType::DynamicCast<UIExtensionNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto paintProperty = uiExtensionNode->GetPaintProperty<UIExtensionPaintProperty>();
    EXPECT_EQ(paintProperty->GetWantValue(), WANT);
}

/**
 * @tc.name: UIExtensionCreator002
 * @tc.desc: create UIExtension and get uiExtensionNode to dispatch event
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(UIExtensionPatternTestNg, UIExtensionCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create or create UIExtension component.
     */
    auto model = UIExtensionModelNG();
    model.Create(BUNDLE_NAME, ABILITY_NAME);

    auto uiExtensionNode =
        AceType::DynamicCast<UIExtensionNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    TouchRestrict touchRestrict;
    TouchTestResult testResult;
    auto result = uiExtensionNode->TouchTest(PointF(), PointF(), touchRestrict, testResult, 1);
    EXPECT_EQ(static_cast<int>(HitTestResult::BUBBLING), static_cast<int>(result));
    auto result2 = uiExtensionNode->TouchTest(PointF(), PointF(10, 10), touchRestrict, testResult, 1);
    EXPECT_EQ(static_cast<int>(HitTestResult::OUT_OF_REGION), static_cast<int>(result2));
}
} // namespace OHOS::Ace::NG
