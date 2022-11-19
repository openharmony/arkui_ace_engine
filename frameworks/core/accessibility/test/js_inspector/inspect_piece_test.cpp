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

#include "frameworks/core/accessibility/js_inspector/inspect_piece.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectPieceTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectPieceTest001
 * @tc.desc: InspectPiece::InspectPiece
 * @tc.type: FUNC
 */
HWTEST_F(InspectPieceTest, InspectPieceTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPiece inspectPiece(nodeId, tag);
    EXPECT_EQ(inspectPiece.nodeId_, nodeId);
    EXPECT_EQ(inspectPiece.tag_, tag);
}

/**
 * @tc.name: InspectPieceTest002
 * @tc.desc: InspectPiece::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectPieceTest, InspectPieceTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPiece inspectPiece(nodeId, tag);
    auto attrsSize = inspectPiece.attrs_.size();
    auto stylesSize = inspectPiece.styles_.size();
    uint16_t attrsSizeInsert = 3;

    inspectPiece.PackAttrAndStyle();
    EXPECT_EQ(inspectPiece.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPiece.attrs_["closable"], "false");
    EXPECT_EQ(inspectPiece.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPiece.attrs_["focusable"], "false");
    EXPECT_EQ(inspectPiece.styles_.size(), stylesSize);
}
} // namespace OHOS::Ace::Framework
