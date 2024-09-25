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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "core/interfaces/native/node/extension_custom_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ExtensionCustomNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: ExtensionCustomNodeTestNg001
 * @tc.desc: test ExtensionCustomNode SetMeasureCallback, SetLayoutCallback, OnMeasure and OnLayout
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionCustomNodeTestNg, ExtensionCustomNodeTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto customNode = AceType::MakeRefPtr<NG::ExtensionCustomNode>();
    auto param = NG::LayoutConstraintF();
    param.minSize = NG::SizeF(50, 50);
    param.maxSize = NG::SizeF(100, 100);
    param.percentReference = NG::SizeF(100, 100);
    auto extensionLayoutConstraint = NG::ExtensionLayoutConstraint::Create(param);

    /**
     * @tc.steps2: Call the function SetMeasureCallback, SetLayoutCallback, OnMeasure and OnLayout.
     * @tc.expected: The function is run ok.
     */
    customNode->SetMeasureCallback([](NG::LayoutConstraintF& layoutConstraint)->void {});
    customNode->SetLayoutCallback([](NG::OffsetF& position)->void {});
    customNode->OnMeasure(extensionLayoutConstraint);
    customNode->OnLayout(100, 100, 10, 10);
    EXPECT_NE(customNode, nullptr);
}
} // namespace OHOS::Ace