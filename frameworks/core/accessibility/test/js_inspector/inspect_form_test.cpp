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

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "frameworks/core/accessibility/js_inspector/inspect_form.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectFormTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectFormTest001
 * @tc.desc: InspectForm::InspectForm
 * @tc.type: FUNC
 */
HWTEST_F(InspectFormTest, InspectFormTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectForm inspectForm(nodeId, tag);
    EXPECT_EQ(inspectForm.nodeId_, nodeId);
    EXPECT_EQ(inspectForm.tag_, tag);
}

/**
 * @tc.name: InspectFormTest002
 * @tc.desc: InspectForm::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectFormTest, InspectFormTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectForm inspectForm(nodeId, tag);
    auto attrsSize = inspectForm.attrs_.size();
    auto stylesSize = inspectForm.styles_.size();
    inspectForm.PackAttrAndStyle();
    EXPECT_EQ(inspectForm.attrs_.size(), attrsSize);
    EXPECT_EQ(inspectForm.styles_.size(), stylesSize);
}
} // namespace OHOS::Ace::Framework
