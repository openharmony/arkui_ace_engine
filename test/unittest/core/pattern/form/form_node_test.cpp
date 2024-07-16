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

#include <cstddef>
#include <optional>
#include <memory>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class FormNodeTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTEstSuite() {};
};

/**
 * @tc.name: FormNodeTest_001
 * @tc.desc: TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_001, TestSize.Level1)
{
    PointF globalPoint;
    PointF parentLocalPoint;
    PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    touchRestrict.hitTestType = SourceType::MOUSE;
    TouchTestResult result;
    int32_t touchId = 0;
    TouchTestResult responseLinkResult;
    bool isDispatch = false;
    FormNode formNode;
    auto res = formNode.TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
}
}