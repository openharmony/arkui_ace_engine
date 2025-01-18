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

#include "base/log/ace_trace.h"
#include "core/components_ng/base/view_partial_update_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ViewPartialUpdateModelTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ViewPartialUpdateModelTestNg001
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set input is default value.
     * @tc.expected: step1. info is default value and return expect value.
     */
    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;
    NodeInfoPU info;

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_FALSE(info.isStatic);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg002
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.updateViewIdFunc.
     * @tc.expected: step1. info.updateViewIdFunc is not null and return expect value.
     */
    std::string viewIdStr;
    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };

    NodeInfoPU info = {
        .updateViewIdFunc = std::move(updateViewNodeFunction),
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.updateViewIdFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg003
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.hasMeasureOrLayout is true.
     * @tc.expected: step1. info.hasMeasureOrLayout is true and return expect value.
     */
    std::string viewIdStr;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };

    NodeInfoPU info = {
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .hasMeasureOrLayout = true,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_TRUE(info.hasMeasureOrLayout);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg004
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.measureFunc.
     * @tc.expected: step1. info.measureFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testMeasureFun;
    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };

    NodeInfoPU info = {
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .measureFunc = std::move(measureFuncation),
        .hasMeasureOrLayout = true,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.measureFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg005
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.layoutFunc.
     * @tc.expected: step1. info.layoutFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testMeasureFun;
    NG::LayoutWrapper* testLayoutFunc;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };

    NodeInfoPU info = {
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .measureFunc = std::move(measureFuncation),
        .layoutFunc = std::move(layoutFuncation),
        .hasMeasureOrLayout = true,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.layoutFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg006
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.updateNodeFunc.
     * @tc.expected: step1. info.updateNodeFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testMeasureFun;
    NG::LayoutWrapper* testLayoutFunc;
    WeakPtr<AceType> testUpdateNodeFunc;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };
    auto updateNodeFuncation = [&testUpdateNodeFunc](
                                   const RefPtr<AceType>& type = nullptr) { testUpdateNodeFunc = type; };

    NodeInfoPU info = {
        .updateNodeFunc = std::move(updateNodeFuncation),
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .measureFunc = std::move(measureFuncation),
        .layoutFunc = std::move(layoutFuncation),
        .hasMeasureOrLayout = true,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.updateNodeFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg007
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.updateNodeFunc.
     * @tc.expected: step1. info.updateNodeFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testMeasureFun;
    NG::LayoutWrapper* testLayoutFunc;
    WeakPtr<AceType> testUpdateNodeFunc;
    WeakPtr<AceType> testRenderfunc;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };
    auto updateNodeFuncation = [&testUpdateNodeFunc](
                                   const RefPtr<AceType>& type = nullptr) { testUpdateNodeFunc = type; };
    auto renderFunction = [&testRenderfunc]() -> RefPtr<AceType> { return nullptr; };

    NodeInfoPU info = {
        .renderFunc = renderFunction,
        .updateNodeFunc = std::move(updateNodeFuncation),
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .measureFunc = std::move(measureFuncation),
        .layoutFunc = std::move(layoutFuncation),
        .hasMeasureOrLayout = true,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.renderFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg008
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the MarkNeedUpdate function first and set input is null.
     * @tc.expected: step1. the return value is false.
     */
    const WeakPtr<AceType>& nullNode = nullptr;
    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    bool testcustomNode = TestViewPartialUpdateModelNG.MarkNeedUpdate(nullNode);
    EXPECT_FALSE(testcustomNode);

    /**
     * @tc.steps: step2. call the MarkNeedUpdate function again and set input is not null.
     * @tc.expected: step2. the return value is true.
     */
    NodeInfoPU info;
    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));

    testcustomNode = TestViewPartialUpdateModelNG.MarkNeedUpdate(customNode);
    EXPECT_TRUE(testcustomNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg009
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the FinishUpdate function.
     * @tc.expected: step1. the FinishUpdate function is run ok.
     */
    const WeakPtr<AceType>& viewNode = nullptr;
    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    TestViewPartialUpdateModelNG.FinishUpdate(viewNode, 1, [](const UpdateTask& task) {});
    auto stack = NG::ViewStackProcessor::GetInstance()->elementsStack_;
    EXPECT_TRUE(stack.empty());
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg010
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.updateNodeFunc.
     * @tc.expected: step1. info.updateNodeFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testMeasureFun;
    NG::LayoutWrapper* testLayoutFunc;
    WeakPtr<AceType> testUpdateNodeFunc;
    WeakPtr<AceType> testRenderfunc;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto measureFuncation = [&testMeasureFun](
                                NG::LayoutWrapper* layoutWrapper = nullptr) { testMeasureFun = layoutWrapper; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };
    auto updateNodeFuncation = [&testUpdateNodeFunc](
                                   const RefPtr<AceType>& type = nullptr) { testUpdateNodeFunc = type; };
    auto renderFunction = [&testRenderfunc]() -> RefPtr<AceType> { return nullptr; };

    NodeInfoPU info = {
        .renderFunc = renderFunction,
        .updateNodeFunc = std::move(updateNodeFuncation),
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .measureFunc = std::move(measureFuncation),
        .layoutFunc = std::move(layoutFuncation),
        .hasMeasureOrLayout = false,
        .isCustomTitle = true,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.renderFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg011
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.updateNodeFunc.
     * @tc.expected: step1. info.updateNodeFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testLayoutFunc;
    NG::LayoutWrapper* testMeasure;
    WeakPtr<AceType> testUpdateNodeFunc;
    WeakPtr<AceType> testRenderfunc;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };
    auto updateNodeFuncation = [&testUpdateNodeFunc](
                                   const RefPtr<AceType>& type = nullptr) { testUpdateNodeFunc = type; };
    auto renderFunction = [&testRenderfunc]() -> RefPtr<AceType> { return nullptr; };
    auto measureSizeFunction = [&testMeasure](NG::LayoutWrapper* testMeasureWrapper = nullptr) {
        testMeasure = testMeasureWrapper;
    };
    NodeInfoPU info = {
        .renderFunc = renderFunction,
        .updateNodeFunc = std::move(updateNodeFuncation),
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .layoutFunc = std::move(layoutFuncation),
        .measureSizeFunc = std::move(measureSizeFunction),
        .hasMeasureOrLayout = true,
        .isCustomTitle = false,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.renderFunc, nullptr);
    EXPECT_TRUE(customNode);
}

/**
 * @tc.name: ViewPartialUpdateModelTestNg012
 * @tc.desc: Test the operation of view partial update model ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewPartialUpdateModelTestNg, ViewPartialUpdateModelTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the CreateNode function and set info.updateNodeFunc.
     * @tc.expected: step1. info.updateNodeFunc is not null and return expect value.
     */
    std::string viewIdStr;
    NG::LayoutWrapper* testLayoutFunc;
    NG::LayoutWrapper* testPlaceChildrenFunc;
    WeakPtr<AceType> testUpdateNodeFunc;
    WeakPtr<AceType> testRenderfunc;

    ViewPartialUpdateModelNG TestViewPartialUpdateModelNG;

    auto updateViewNodeFunction = [&viewIdStr](std::string viewId = "testViewIdStr") { viewIdStr = viewId; };
    auto layoutFuncation = [&testLayoutFunc](
                               NG::LayoutWrapper* layoutWrapper = nullptr) { testLayoutFunc = layoutWrapper; };
    auto updateNodeFuncation = [&testUpdateNodeFunc](
                                   const RefPtr<AceType>& type = nullptr) { testUpdateNodeFunc = type; };
    auto renderFunction = [&testRenderfunc]() -> RefPtr<AceType> { return nullptr; };
    auto placeChildrenFunction = [&testPlaceChildrenFunc](NG::LayoutWrapper* testPlaceChildrenFuncWrapper = nullptr) {
        testPlaceChildrenFunc = testPlaceChildrenFuncWrapper;
    };
    NodeInfoPU info = {
        .renderFunc = renderFunction,
        .updateNodeFunc = std::move(updateNodeFuncation),
        .updateViewIdFunc = std::move(updateViewNodeFunction),
        .layoutFunc = std::move(layoutFuncation),
        .placeChildrenFunc = std::move(placeChildrenFunction),
        .hasMeasureOrLayout = true,
        .isCustomTitle = false,
    };

    RefPtr<AceType> customNode = TestViewPartialUpdateModelNG.CreateNode(std::move(info));
    EXPECT_NE(info.renderFunc, nullptr);
    EXPECT_TRUE(customNode);
}
} // namespace OHOS::Ace::NG