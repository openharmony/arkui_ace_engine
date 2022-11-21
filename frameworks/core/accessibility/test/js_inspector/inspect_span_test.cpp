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

#include "frameworks/core/accessibility/js_inspector/inspect_span.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectSpanTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectSpanTest001
 * @tc.desc: InspectSpan::InspectSpan
 * @tc.type: FUNC
 */
HWTEST_F(InspectSpanTest, InspectSpanTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSpan inspectSpan(nodeId, tag);
    EXPECT_EQ(inspectSpan.nodeId_, nodeId);
    EXPECT_EQ(inspectSpan.tag_, tag);
}

/**
 * @tc.name: InspectSpanTest002
 * @tc.desc: InspectSpan::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectSpanTest, InspectSpanTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSpan inspectSpan(nodeId, tag);
    auto attrsSize = inspectSpan.attrs_.size();
    auto stylesSize = inspectSpan.styles_.size();
    uint16_t stylesSizeInsert = 6;

    inspectSpan.PackAttrAndStyle();
    EXPECT_EQ(inspectSpan.attrs_.size(), attrsSize);
    EXPECT_EQ(inspectSpan.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSpan.styles_["font-size"], "30px");
    EXPECT_EQ(inspectSpan.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectSpan.styles_["font-style"], "normal");
    EXPECT_EQ(inspectSpan.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectSpan.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectSpan.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
