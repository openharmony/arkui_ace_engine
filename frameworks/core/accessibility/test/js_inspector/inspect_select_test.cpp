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

#include "frameworks/core/accessibility/js_inspector/inspect_select.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectSelectTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectSelectTest001
 * @tc.desc: InspectSelect::InspectSelect
 * @tc.type: FUNC
 */
HWTEST_F(InspectSelectTest, InspectSelectTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSelect inspectSelect(nodeId, tag);
    EXPECT_EQ(inspectSelect.nodeId_, nodeId);
    EXPECT_EQ(inspectSelect.tag_, tag);
}

/**
 * @tc.name: InspectSelectTest002
 * @tc.desc: InspectSelect::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectSelectTest, InspectSelectTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSelect inspectSelect(nodeId, tag);
    auto attrsSize = inspectSelect.attrs_.size();
    auto stylesSize = inspectSelect.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 1;

    inspectSelect.PackAttrAndStyle();
    EXPECT_EQ(inspectSelect.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectSelect.attrs_["disabled"], "false");
    EXPECT_EQ(inspectSelect.attrs_["focusable"], "true");
    EXPECT_EQ(inspectSelect.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSelect.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
