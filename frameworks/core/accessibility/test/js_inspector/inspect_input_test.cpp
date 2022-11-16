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

#include "frameworks/core/accessibility/js_inspector/inspect_input.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectInputTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectInputTest001
 * @tc.desc: InspectInput::InspectInput
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    EXPECT_EQ(inspectInput.nodeId_, nodeId);
    EXPECT_EQ(inspectInput.tag_, tag);
}

/**
 * @tc.name: InspectInputTest002
 * @tc.desc: InspectInput::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();
    uint16_t attrsSizeInsert = 6;
    uint16_t stylesSizeInsert = 6;

    inspectInput.PackAttrAndStyle();
    EXPECT_EQ(inspectInput.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectInput.attrs_["type"], "text");
    EXPECT_EQ(inspectInput.attrs_["checked"], "false");
    EXPECT_EQ(inspectInput.attrs_["enterkeytype"], "default");
    EXPECT_EQ(inspectInput.attrs_["showcounter"], "false");
    EXPECT_EQ(inspectInput.attrs_["disabled"], "false");
    EXPECT_EQ(inspectInput.attrs_["focusable"], "true");
    EXPECT_EQ(inspectInput.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectInput.styles_["color"], "#e6000000");
    EXPECT_EQ(inspectInput.styles_["font-size"], "16px");
    EXPECT_EQ(inspectInput.styles_["placeholder-color"], "#99000000");
    EXPECT_EQ(inspectInput.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectInput.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectInput.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework