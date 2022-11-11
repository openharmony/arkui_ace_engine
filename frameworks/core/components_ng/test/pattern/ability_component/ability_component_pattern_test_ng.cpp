/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/ability_component/ability_component_event_hub.h"
#include "core/components_ng/pattern/ability_component/ability_component_model_ng.h"
#include "core/components_ng/pattern/ability_component/ability_component_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class AbilityComponentPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AbilityComponentObjectTest001
 * @tc.desc: Test setting of object.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentObjectTest001, TestSize.Level1)
{
    AbilityComponentModelNG modelNG;
    modelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<AbilityComponentRenderProperty> paintProperty =
        frameNode->GetPaintProperty<AbilityComponentRenderProperty>();
    EXPECT_NE(paintProperty, nullptr);
    RefPtr<AbilityComponentEventHub> eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    EXPECT_NE(eventHub, nullptr);
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: AbilityComponentModelTest001
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentModelTest001, TestSize.Level1)
{
    bool flagConnect = false;
    auto onConnect = [&flagConnect]() { flagConnect = true; };
    bool flagDisConnect = false;
    auto onDisConnect = [&flagDisConnect]() { flagDisConnect = true; };
    AbilityComponentModelNG modelNG;
    modelNG.Create();
    string want = "abilityName:, bundleName:";
    modelNG.SetWant(want);
    modelNG.SetOnConnect(std::move(onConnect));
    modelNG.SetOnDisConnect(std::move(onDisConnect));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<AbilityComponentRenderProperty> paintProperty =
        frameNode->GetPaintProperty<AbilityComponentRenderProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetWantValue(), want);
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->FireConnect();
    EXPECT_EQ(flagConnect, true);
    pattern->FireDisConnect();
    EXPECT_EQ(flagDisConnect, true);
}

/**
 * @tc.name: AbilityComponentEventTest001
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentEventTest001, TestSize.Level1)
{
    bool flagConnect = false;
    auto onConnect = [&flagConnect]() { flagConnect = true; };
    bool flagDisConnect = false;
    auto onDisConnect = [&flagDisConnect]() { flagDisConnect = true; };
    AbilityComponentModelNG modelNG;
    modelNG.Create();
    string want = "abilityName:, bundleName:";
    modelNG.SetWant(want);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<AbilityComponentEventHub> eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->SetOnConnect(std::move(onConnect));
    eventHub->FireOnConnect();
    EXPECT_EQ(flagConnect, true);
    eventHub->SetOnDisConnect(std::move(onDisConnect));
    eventHub->FireOnDisConnect();
    EXPECT_EQ(flagDisConnect, true);
}

/**
 * @tc.name: AbilityComponentEventTest002
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentEventTest002, TestSize.Level1)
{
    bool flagConnect = false;
    auto onConnect = [&flagConnect]() { flagConnect = true; };
    bool flagDisConnect = false;
    auto onDisConnect = [&flagDisConnect]() { flagDisConnect = true; };
    AbilityComponentModelNG modelNG;
    modelNG.Create();
    string want = "abilityName:, bundleName:";
    modelNG.SetWant(want);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<AbilityComponentEventHub> eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->SetOnConnect(std::move(onConnect));
    eventHub->SetOnDisConnect(std::move(onDisConnect));
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->FireConnect();
    EXPECT_EQ(flagConnect, true);
    pattern->FireDisConnect();
    EXPECT_EQ(flagDisConnect, true);
}
} // namespace OHOS::Ace::NG
