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
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <vector>
#include <utility>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/frame_node.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
float one = 1;
float minus = -1;
std::string TEST = "";
}; // namespace

class ViewAbstractModelTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ViewAbstractModelTestNg001
 * @tc.desc: Test the operation of View Abstract Model
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback BindContextMenu
     * @tc.expected: step1. expect the function is run ok
     */
    auto CreateBuildFunc = []() {
        TEST = "test";
    };

    ViewAbstractModelNG viewAbstractModelNG;
    MenuParam menuParam;
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, CreateBuildFunc, menuParam);
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    /**
     * @tc.expected: step1. expect targetNode is null
     */
    EXPECT_EQ(targetNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg002
 * @tc.desc: Test the operation of View Abstract Model
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback SetPivot
     * @tc.expected: step1. expect the function is run ok
     */
    ViewAbstractModelNG viewAbstractModelNG;

    Dimension dimension;
    viewAbstractModelNG.SetPivot(dimension, dimension, dimension);

    /**
     * @tc.expected: step1. expect the num is same with 1.0
     */
    dimension.SetValue(1.0);
    auto num = dimension.Value();
    viewAbstractModelNG.SetPivot(dimension, dimension, dimension);
    EXPECT_EQ(num, 1.0);
}

/**
 * @tc.name: ViewAbstractModelTestNg003
 * @tc.desc: Test the operation of View Abstract Model
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelNgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback SetScale
     * @tc.expected: step1. expect the function is run ok
     */
    VectorF vectorF(0.0, 0.0);
    ViewAbstractModelNG viewAbstractModelNG;
    viewAbstractModelNG.SetScale(one, one, one);
    EXPECT_EQ(vectorF.x, 0);

    /**
     * @tc.expected: step1. expect vectorF.x is 0
     */
    viewAbstractModelNG.SetScale(minus, minus, minus);
    EXPECT_EQ(vectorF.x, 0);
}

/**
 * @tc.name: ViewAbstractModelTestNg004
 * @tc.desc: Test the operation of View Abstract Model
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelNgTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback BindContentCover
     * @tc.expected: step1. expect the function is run ok
     */
    ViewAbstractModelNG viewAbstractModelNG;
    auto CreateBuildFunc = []() {
        TEST = "test";
    };

    auto CreateCallBack = [](std::string ONE = "null") {
        TEST = ONE;
    };

    bool isShow = false;
    viewAbstractModelNG.BindContentCover(isShow, CreateCallBack, CreateBuildFunc, 1);
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    /**
     * @tc.expected: step1. expect targetNode is null
     */
    EXPECT_EQ(targetNode, nullptr);
}
} // namespace OHOS::Ace::NG
