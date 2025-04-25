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

#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_model.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string PARAMS_VALUE = R"({"text":{"name":"news"}})";
const std::string PARAMS_VALUE2 = R"({"text":{"A":"B", "osos": "ohhsh"}})";
const std::string URL_VALUE = "pages/next";
const std::string URL_VALUE2 = "pages/back";
} // namespace

struct TestProperty {
    std::optional<NavigatorType> typeValue = std::nullopt;
    std::optional<std::string> params = std::nullopt;
    std::optional<std::string> url = std::nullopt;
    std::optional<bool> active = std::nullopt;
};

class NavigatorPatternTestNg : public testing::Test {
public:
protected:
    RefPtr<FrameNode> CreateNavigator(const TestProperty& testProperty);
};

RefPtr<FrameNode> NavigatorPatternTestNg::CreateNavigator(const TestProperty& testProperty)
{
    NavigatorModelNG navigator;
    navigator.Create();
    if (testProperty.typeValue.has_value()) {
        navigator.SetType(testProperty.typeValue.value());
        navigator.SetUri(testProperty.url.value());
        navigator.SetActive(testProperty.active.value());
        navigator.SetParams(testProperty.params.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: NavigatorFrameNodeCreator001
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator with properties
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::REPLACE);
    testProperty.params = std::make_optional(PARAMS_VALUE);
    testProperty.url = std::make_optional(URL_VALUE);
    testProperty.active = std::make_optional(false);

    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    EXPECT_EQ(eventHub->GetUrl(), URL_VALUE);
    EXPECT_FALSE(eventHub->GetActive());
    EXPECT_EQ(eventHub->GetParams(), PARAMS_VALUE);
    EXPECT_EQ(eventHub->GetType(), NavigatorType::REPLACE);
    eventHub->NavigatePage();
}

/**
 * @tc.name: NavigatorFrameNodeCreator002
 * @tc.desc: Test BACK navigator.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator with properties
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::BACK);
    testProperty.params = std::make_optional(PARAMS_VALUE2);
    testProperty.url = std::make_optional(URL_VALUE2);
    testProperty.active = std::make_optional(false);

    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    EXPECT_EQ(eventHub->GetUrl(), URL_VALUE2);
    EXPECT_FALSE(eventHub->GetActive());
    EXPECT_EQ(eventHub->GetType(), NavigatorType::BACK);
    EXPECT_EQ(eventHub->GetParams(), PARAMS_VALUE2);
    /**
     * @tc.steps: step3. BACK navigate
     */
    eventHub->NavigatePage();
}

/**
 * @tc.name: NavigatorFrameNodeCreator003
 * @tc.desc: Test PUSH navigator.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeCreator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator with properties
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::PUSH);
    testProperty.params = std::make_optional(PARAMS_VALUE);
    testProperty.url = std::make_optional(URL_VALUE);
    testProperty.active = std::make_optional(false);

    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    EXPECT_EQ(eventHub->GetUrl(), URL_VALUE);
    EXPECT_FALSE(eventHub->GetActive());
    EXPECT_EQ(eventHub->GetParams(), PARAMS_VALUE);
    EXPECT_EQ(eventHub->GetType(), NavigatorType::PUSH);
    eventHub->NavigatePage();
}

/**
 * @tc.name: NavigatorFrameNodeCreator004
 * @tc.desc: Test invalid navigator type.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeCreator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator with DEFAULT NavigatorType
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::DEFAULT);
    testProperty.params = std::make_optional(PARAMS_VALUE2);
    testProperty.url = std::make_optional(URL_VALUE2);
    testProperty.active = std::make_optional(false);

    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    EXPECT_EQ(eventHub->GetUrl(), URL_VALUE2);
    EXPECT_FALSE(eventHub->GetActive());
    EXPECT_EQ(eventHub->GetParams(), PARAMS_VALUE2);
    EXPECT_EQ(eventHub->GetType(), NavigatorType::DEFAULT);
    // Navigator Type is invalid
    eventHub->NavigatePage();
}

/**
 * @tc.name: NavigatorFrameNodeCreator005
 * @tc.desc: Test create with no properties.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeCreator005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator with no properties
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    EXPECT_EQ(eventHub->GetUrl(), "");
    EXPECT_FALSE(eventHub->GetActive());
    EXPECT_EQ(eventHub->GetParams(), "");
    EXPECT_EQ(eventHub->GetType(), NavigatorType::PUSH);
    eventHub->NavigatePage();
}

/**
 * @tc.name: NavigatorFrameNodeSetFuncs
 * @tc.desc: Test SetActive.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeSetFuncs, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::PUSH);
    testProperty.params = std::make_optional(PARAMS_VALUE);
    testProperty.url = std::make_optional(URL_VALUE);
    testProperty.active = std::make_optional(false);

    /**
     * @tc.steps: step2. check current properties
     */
    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    EXPECT_TRUE(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    EXPECT_EQ(eventHub->GetUrl(), URL_VALUE);
    EXPECT_FALSE(eventHub->GetActive());
    EXPECT_EQ(eventHub->GetParams(), PARAMS_VALUE);
    EXPECT_EQ(eventHub->GetType(), NavigatorType::PUSH);

    /**
     * @tc.steps: step3. change properties and recheck
     */
    eventHub->SetParams(PARAMS_VALUE2);
    eventHub->SetUrl(URL_VALUE2);
    eventHub->SetType(NavigatorType::BACK);
    EXPECT_EQ(eventHub->GetUrl(), URL_VALUE2);
    EXPECT_EQ(eventHub->GetParams(), PARAMS_VALUE2);
    EXPECT_EQ(eventHub->GetType(), NavigatorType::BACK);
}

/**
 * @tc.name: NavigatorFrameNodeActive
 * @tc.desc: Test active initialized to true.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorFrameNodeActive, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialze navigator with active_ set to true
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::PUSH);
    testProperty.params = std::make_optional(PARAMS_VALUE);
    testProperty.url = std::make_optional(URL_VALUE);
    testProperty.active = std::make_optional(true);

    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    EXPECT_TRUE(frameNode);
    // should navigate immediately
}

/**
 * @tc.name: NavigatorModifyDone
 * @tc.desc: Test OnModifyDone.
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(NavigatorPatternTestNg, NavigatorModifyDone, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigator
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(NavigatorType::PUSH);
    testProperty.params = std::make_optional(PARAMS_VALUE);
    testProperty.url = std::make_optional(URL_VALUE);
    testProperty.active = std::make_optional(false);

    RefPtr<FrameNode> frameNode = CreateNavigator(testProperty);
    EXPECT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<NavigatorPattern>();
    EXPECT_TRUE(pattern);

    // mark modify done multiple times
    frameNode->MarkModifyDone();
    frameNode->MarkModifyDone();
    // assert only one click event is created
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto events = gestureHub->clickEventActuator_->clickEvents_;
    EXPECT_EQ(events.size(), 1);
}
} // namespace OHOS::Ace::NG
