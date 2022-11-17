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

#include "frameworks/core/accessibility/js_inspector/inspect_search.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectSearchTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectSearchTest001
 * @tc.desc: InspectSearch::InspectSearch
 * @tc.type: FUNC
 */
HWTEST_F(InspectSearchTest, InspectSearchTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSearch inspectSearch(nodeId, tag);
    EXPECT_EQ(inspectSearch.nodeId_, nodeId);
    EXPECT_EQ(inspectSearch.tag_, tag);
}

/**
 * @tc.name: InspectSearchTest002
 * @tc.desc: InspectSearch::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectSearchTest, InspectSearchTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSearch inspectSearch(nodeId, tag);
    auto attrsSize = inspectSearch.attrs_.size();
    auto stylesSize = inspectSearch.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 3;

    inspectSearch.PackAttrAndStyle();
    EXPECT_EQ(inspectSearch.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectSearch.attrs_["disabled"], "false");
    EXPECT_EQ(inspectSearch.attrs_["focusable"], "true");
    EXPECT_EQ(inspectSearch.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSearch.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectSearch.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectSearch.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
