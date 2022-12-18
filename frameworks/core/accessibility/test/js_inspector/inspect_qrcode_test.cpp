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

#include "frameworks/core/accessibility/js_inspector/inspect_qrcode.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectQRcodeTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectQRcodeTest001
 * @tc.desc: InspectQRcode::InspectQRcode
 * @tc.type: FUNC
 */
HWTEST_F(InspectQRcodeTest, InspectQRcodeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectQRcode inspectQRcode(nodeId, tag);
    EXPECT_EQ(inspectQRcode.nodeId_, nodeId);
    EXPECT_EQ(inspectQRcode.tag_, tag);
}

/**
 * @tc.name: InspectQRcodeTest002
 * @tc.desc: InspectQRcode::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectQRcodeTest, InspectQRcodeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectQRcode inspectQRcode(nodeId, tag);
    auto attrsSize = inspectQRcode.attrs_.size();
    auto stylesSize = inspectQRcode.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 2;

    inspectQRcode.PackAttrAndStyle();
    EXPECT_EQ(inspectQRcode.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectQRcode.attrs_["type"], "rect");
    EXPECT_EQ(inspectQRcode.attrs_["disabled"], "false");
    EXPECT_EQ(inspectQRcode.attrs_["focusable"], "false");
    EXPECT_EQ(inspectQRcode.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectQRcode.styles_["color"], "#000000");
    EXPECT_EQ(inspectQRcode.styles_["background-color"], "#ffffff");
}
} // namespace OHOS::Ace::Framework
