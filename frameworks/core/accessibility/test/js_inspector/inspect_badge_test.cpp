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

#include "frameworks/core/accessibility/js_inspector/inspect_badge.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectBadgeTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectBadgeTest001
 * @tc.desc: InspectBadge::InspectBadge
 * @tc.type: FUNC
 */
HWTEST_F(InspectBadgeTest, InspectBadgeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectBadge inspectBadge(nodeId, tag);
    EXPECT_EQ(inspectBadge.nodeId_, nodeId);
    EXPECT_EQ(inspectBadge.tag_, tag);
}

/**
 * @tc.name: InspectBadgeTest002
 * @tc.desc: InspectBadge::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectBadgeTest, InspectBadgeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectBadge inspectBadge(nodeId, tag);
    auto size = inspectBadge.attrs_.size();
    uint16_t sizeInsert = 7;
    inspectBadge.PackAttrAndStyle();
    EXPECT_EQ(inspectBadge.attrs_.size(), size + sizeInsert);
    EXPECT_EQ(inspectBadge.attrs_["placement"], "rightTop");
    EXPECT_EQ(inspectBadge.attrs_["count"], "0");
    EXPECT_EQ(inspectBadge.attrs_["visible"], "false");
    EXPECT_EQ(inspectBadge.attrs_["maxcount"], "99");
    EXPECT_EQ(inspectBadge.attrs_["config"], "BadgeConfig");
    EXPECT_EQ(inspectBadge.attrs_["disabled"], "false");
    EXPECT_EQ(inspectBadge.attrs_["focusable"], "false");
}
} // namespace OHOS::Ace::Framework
