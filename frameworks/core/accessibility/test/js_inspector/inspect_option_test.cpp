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

#include "frameworks/core/accessibility/js_inspector/inspect_option.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectOptionTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectOptionTest001
 * @tc.desc: InspectOption::InspectOption
 * @tc.type: FUNC
 */
HWTEST_F(InspectOptionTest, InspectOptionTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectOption inspectOption(nodeId, tag);
    EXPECT_EQ(inspectOption.nodeId_, nodeId);
    EXPECT_EQ(inspectOption.tag_, tag);
}

/**
 * @tc.name: InspectOptionTest002
 * @tc.desc: InspectOption::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectOptionTest, InspectOptionTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectOption inspectOption(nodeId, tag);
    auto attrsSize = inspectOption.attrs_.size();
    auto stylesSize = inspectOption.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 6;

    inspectOption.PackAttrAndStyle();
    EXPECT_EQ(inspectOption.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectOption.attrs_["action"], "show");
    EXPECT_EQ(inspectOption.attrs_["focusable"], "true");
    EXPECT_EQ(inspectOption.attrs_["disabled"], "false");
    EXPECT_EQ(inspectOption.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectOption.styles_["color"], "#e6000000");
    EXPECT_EQ(inspectOption.styles_["font-size"], "16px");
    EXPECT_EQ(inspectOption.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectOption.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectOption.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectOption.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
