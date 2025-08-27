/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "nweb_accessibility_node_info.h"

#include "frameworks/core/components_ng/pattern/web/transitional_node_info.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::NWeb {
class MockNWebAccessibilityNode : public OHOS::NWeb::NWebAccessibilityNodeInfo {
public:
    MockNWebAccessibilityNode() {}

    MOCK_METHOD1(SetPageId, void(int32_t));
    MOCK_METHOD1(SetParentId, void(int64_t));
    MOCK_METHOD0(GetHint, std::string());
    MOCK_METHOD0(GetError, std::string());
    MOCK_METHOD0(GetRectX, int32_t());
    MOCK_METHOD0(GetRectY, int32_t());
    MOCK_METHOD0(GetPageId, int32_t());
    MOCK_METHOD0(GetActions, std::vector<uint32_t>());
    MOCK_METHOD0(GetContent, std::string());
    MOCK_METHOD0(GetChildIds, std::vector<int64_t>());
    MOCK_METHOD0(GetParentId, int64_t());
    MOCK_METHOD0(GetIsHeading, bool());
    MOCK_METHOD0(GetIsChecked, bool());
    MOCK_METHOD0(GetIsEnabled, bool());
    MOCK_METHOD0(GetIsFocused, bool());
    MOCK_METHOD0(GetRectWidth, int32_t());
    MOCK_METHOD0(GetRectHeight, int32_t());
    MOCK_METHOD0(GetIsVisible, bool());
    MOCK_METHOD0(GetIsHinting, bool());
    MOCK_METHOD0(GetIsEditable, bool());
    MOCK_METHOD0(GetIsSelected, bool());
    MOCK_METHOD0(GetItemCounts, size_t());
    MOCK_METHOD0(GetLiveRegion, int32_t());
    MOCK_METHOD0(GetIsPassword, bool());
    MOCK_METHOD0(GetIsCheckable, bool());
    MOCK_METHOD0(GetIsClickable, bool());
    MOCK_METHOD0(GetIsFocusable, bool());
    MOCK_METHOD0(GetIsScrollable, bool());
    MOCK_METHOD0(GetIsDeletable, bool());
    MOCK_METHOD0(GetAccessibilityId, int64_t());
    MOCK_METHOD0(GetIsPopupSupported, bool());
    MOCK_METHOD0(GetIsContentInvalid, bool());
    MOCK_METHOD0(GetSelectionEnd, int32_t());
    MOCK_METHOD0(GetSelectionStart, int32_t());
    MOCK_METHOD0(GetRangeInfoMin, float());
    MOCK_METHOD0(GetRangeInfoMax, float());
    MOCK_METHOD0(GetRangeInfoCurrent, float());
    MOCK_METHOD0(GetInputType, int32_t());
    MOCK_METHOD0(GetComponentType, std::string());
    MOCK_METHOD0(GetDescriptionInfo, std::string());
    MOCK_METHOD0(GetGridRows, int32_t());
    MOCK_METHOD0(GetGridItemRow, int32_t());
    MOCK_METHOD0(GetGridColumns, int32_t());
    MOCK_METHOD0(GetGridItemColumn, int32_t());
    MOCK_METHOD0(GetGridItemRowSpan, int32_t());
    MOCK_METHOD0(GetGridSelectedMode, int32_t());
    MOCK_METHOD0(GetGridItemColumnSpan, int32_t());
    MOCK_METHOD0(GetIsAccessibilityFocus, bool());
    MOCK_METHOD0(GetIsPluralLineSupported, bool());
    MOCK_METHOD0(GetIsAccessibilityGroup, bool());
    MOCK_METHOD0(GetHtmlElementId, std::string());
    MOCK_METHOD0(GetComponentTypeDescription, std::string());
    MOCK_METHOD0(GetCheckboxGroupSelectedStatus, int32_t());
    MOCK_METHOD0(GetExpandedState, std::string());
};
}  // namespace OHOS::NWeb

namespace OHOS::Ace::NG {

class TransitionalNodeInfoTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void TransitionalNodeInfoTest::SetUpTestCase() {}
void TransitionalNodeInfoTest::TearDownTestCase() {}
void TransitionalNodeInfoTest::SetUp() {}
void TransitionalNodeInfoTest::TearDown() {}

/**
 * @tc.name: Create_001
 * @tc.desc: Test function Create.
 * @tc.type: FUNC
 */
HWTEST_F(TransitionalNodeInfoTest, TransitionalNodeInfo_001, TestSize.Level1)
{
    auto mockNWebAccessibilityNodeInfo = std::make_shared<OHOS::NWeb::MockNWebAccessibilityNode>();
    auto node = std::make_shared<TransitionalNodeInfo>(mockNWebAccessibilityNodeInfo);
    EXPECT_CALL(*mockNWebAccessibilityNodeInfo, GetComponentTypeDescription()).WillOnce(Return("button"));
    EXPECT_CALL(*mockNWebAccessibilityNodeInfo, GetExpandedState()).WillOnce(Return("expanded"));
    EXPECT_CALL(*mockNWebAccessibilityNodeInfo, GetCheckboxGroupSelectedStatus()).WillOnce(Return(2));
    EXPECT_EQ(node->GetComponentTypeDescription(), "button");
    EXPECT_EQ(node->GetExpandedState(), "expanded");
    EXPECT_EQ(node->GetCheckboxGroupSelectedStatus(), 2);
}
}