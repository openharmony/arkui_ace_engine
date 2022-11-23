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

#include "frameworks/core/accessibility/js_inspector/inspect_dialog.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectDialogTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectDialogTest001
 * @tc.desc: InspectDialog::InspectDialog
 * @tc.type: FUNC
 */
HWTEST_F(InspectDialogTest, InspectDialogTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDialog inspectDialog(nodeId, tag);
    EXPECT_EQ(inspectDialog.nodeId_, nodeId);
    EXPECT_EQ(inspectDialog.tag_, tag);
}

/**
 * @tc.name: InspectDialogTest002
 * @tc.desc: InspectDialog::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectDialogTest, InspectDialogTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDialog inspectDialog(nodeId, tag);
    auto attrsSize = inspectDialog.attrs_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 4;

    // SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectDialog.PackAttrAndStyle();
    EXPECT_EQ(inspectDialog.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectDialog.styles_.size(), stylesSizeInsert);
    EXPECT_EQ(inspectDialog.attrs_["disabled"], "false");
    EXPECT_EQ(inspectDialog.attrs_["dragable"], "false");
    EXPECT_EQ(inspectDialog.styles_["margin-left"], "0");
    EXPECT_EQ(inspectDialog.styles_["margin-top"], "0");
    EXPECT_EQ(inspectDialog.styles_["margin-right"], "0");
    EXPECT_EQ(inspectDialog.styles_["margin-bottom"], "0");
}
} // namespace OHOS::Ace::Framework
