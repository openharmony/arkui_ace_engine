/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public
#include "core/components_ng/base/view_full_update_model.h"
#include "core/components_ng/base/view_full_update_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    std::string TEST;
}; // namespace

class ViewFullUpdateModelNgTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ViewStackProcessorTestNg001
 * @tc.desc: Test the operation of view_full_update_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewFullUpdateModelNgTest, ViewFullUpdateModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewFullUpdateModelNG.
     * @tc.steps: step2. callback CreateNode.push NodeInfo is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewFullUpdateModelNG viewFullUpdateModelNG;
    NodeInfo info;
    RefPtr<AceType> resault = viewFullUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(resault, nullptr);
}

/**
 * @tc.name: ViewStackProcessorTestNg002
 * @tc.desc: Test the operation of view_full_update_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewFullUpdateModelNgTest, ViewFullUpdateModelNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewFullUpdateModelNG.
     * @tc.steps: step2. callback CreateNode.push NodeInfo is not null.
     * @tc.expected: step2. Return expected results..
     */
    std::string viewId = "id";
    ViewFullUpdateModelNG viewFullUpdateModelNG;

    auto callback = []() {
        TEST = "test";
    };
    NodeInfo info = { .viewId = viewId,
        .appearFunc = std::move(callback),
        .isStatic = true };
    RefPtr<AceType> resault = viewFullUpdateModelNG.CreateNode(std::move(info));
    EXPECT_TRUE(resault);
}

/**
 * @tc.name: ViewStackProcessorTestNg003
 * @tc.desc: Test the operation of view_full_update_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewFullUpdateModelNgTest, ViewFullUpdateModelNgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewFullUpdateModelNG.
     * @tc.steps: step2. callback CreateNode.push NodeInfo is not null.
     * @tc.expected: step2. Return expected results..
     */
    std::string viewId = "id";
    WeakPtr<AceType> viewNode;
    ViewFullUpdateModelNG viewFullUpdateModelNG;

    auto callback = []() {
        TEST = "test";
    };

    auto updateViewNodeFunction = [&viewNode](const RefPtr<AceType>& node = nullptr) {
        viewNode = node;
    };

    NodeInfo info = { .viewId = viewId,
        .appearFunc = std::move(callback),
        .updateNodeFunc = std::move(updateViewNodeFunction),
        .isStatic = false };
    RefPtr<AceType> resault = viewFullUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.appearFunc, nullptr);
    EXPECT_TRUE(resault);
}

/**
 * @tc.name: ViewStackProcessorTestNg004
 * @tc.desc: Test the operation of view_full_update_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewFullUpdateModelNgTest, ViewFullUpdateModelNgTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewFullUpdateModelNG.
     * @tc.steps: step2. callback CreateNode.push NodeInfo is not null.
     * @tc.expected: step2. Return expected results..
     */
    std::string viewId = "id";
    WeakPtr<AceType> viewNode;
    RefPtr<AceType> view;
    ViewFullUpdateModelNG viewFullUpdateModelNG;

    auto callback = []() {
        TEST = "test";
    };

    auto renderFunction = [&view]() -> RefPtr<AceType> {
        return nullptr;
    };

    auto updateViewNodeFunction = [&viewNode](const RefPtr<AceType>& node = nullptr) {
        viewNode = node;
    };
    NodeInfo info = { .viewId = viewId,
        .appearFunc = std::move(callback),
        .renderFunc = std::move(renderFunction),
        .updateNodeFunc = std::move(updateViewNodeFunction),
        .isStatic = false };
    RefPtr<AceType> resault = viewFullUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.updateNodeFunc, nullptr);
    EXPECT_TRUE(resault);
}
} // namespace OHOS::Ace::NG