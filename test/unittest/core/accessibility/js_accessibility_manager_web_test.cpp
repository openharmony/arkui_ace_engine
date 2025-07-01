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

#define private public
#define protected public
#include "core/components_ng/pattern/web/transitional_node_info.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#ifdef WEB_SUPPORTED
#include "nweb_accessibility_node_info.h"
#endif

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class JsAccessibilityManagerWebTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityManagerWebTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void JsAccessibilityManagerWebTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

#ifdef WEB_SUPPORTED
class MockNWebAccessibilityNodeInfo : public NWeb::NWebAccessibilityNodeInfo {
    public:
    std::string GetHint() override
    {
        return "";
    }
    std::string GetError() override
    {
        return "";
    }
    int32_t GetRectX()
    {
        return 0;
    }
    int32_t GetRectY()
    {
        return 0;
    }
    void SetPageId(int32_t pageId) override {}
    int32_t GetPageId() override
    {
        return 0;
    }
    std::vector<uint32_t> GetActions() override
    {
        return {};
    }
    std::string GetContent() override
    {
        return "";
    }
    std::vector<int64_t> GetChildIds() override
    {
        return {};
    }
    void SetParentId(int64_t parentId) override {}
    int64_t GetParentId() override
    {
        return 0;
    }
    bool GetIsHeading() override
    {
        return false;
    }
    bool GetIsChecked() override
    {
        return false;
    }
    bool GetIsEnabled() override
    {
        return false;
    }
    bool GetIsFocused() override
    {
        return false;
    }
    int32_t GetRectWidth()
    {
        return 0;
    }
    int32_t GetRectHeight()
    {
        return 0;
    }
    bool GetIsVisible() override
    {
        return true;
    }
    bool GetIsHinting() override
    {
        return false;
    }
    bool GetIsEditable() override
    {
        return false;
    }
    bool GetIsSelected() override
    {
        return false;
    }
    size_t GetItemCounts() override
    {
        return 0;
    }
    int32_t GetLiveRegion() override
    {
        return 0;
    }
    bool GetIsPassword() override
    {
        return false;
    }
    bool GetIsCheckable() override
    {
        return false;
    }
    bool GetIsClickable() override
    {
        return false;
    }
    bool GetIsFocusable() override
    {
        return false;
    }
    bool GetIsScrollable() override
    {
        return false;
    }
    bool GetIsDeletable() override
    {
        return false;
    }
    int64_t GetAccessibilityId() override
    {
        return 0;
    }
    bool GetIsPopupSupported() override
    {
        return false;
    }
    bool GetIsContentInvalid() override
    {
        return false;
    }
    int32_t GetSelectionEnd() override
    {
        return 0;
    }
    int32_t GetSelectionStart() override
    {
        return 0;
    }
    float GetRangeInfoMin() override
    {
        return 0.0f;
    }
    float GetRangeInfoMax() override
    {
        return 0.0f;
    }
    float GetRangeInfoCurrent() override
    {
        return 0.0f;
    }
    int32_t GetInputType() override
    {
        return 0;
    }
    std::string GetComponentType() override
    {
        return "";
    }
    std::string GetDescriptionInfo() override
    {
        return "";
    }
    int32_t GetGridRows() override
    {
        return 0;
    }
    int32_t GetGridItemRow() override
    {
        return 0;
    }
    int32_t GetGridColumns() override
    {
        return 0;
    }
    int32_t GetGridItemColumn() override
    {
        return 0;
    }
    int32_t GetGridItemRowSpan() override
    {
        return 0;
    }
    int32_t GetGridSelectedMode() override
    {
        return 0;
    }
    int32_t GetGridItemColumnSpan() override
    {
        return 0;
    }
    bool GetIsAccessibilityFocus() override
    {
        return false;
    }
    bool GetIsPluralLineSupported() override
    {
        return false;
    }
};

/**
 * @tc.name: WebSetScreenRect001
 * @tc.desc: WebSetScreenRect degree = 90 / degree = 0
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerWebTest, WebSetScreenRect001, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Framework::CommonProperty commonProperty;
    commonProperty.rotateTransform.rotateDegree = 90;
    auto nWebAccessibilityNodeInfoPtr = std::make_shared<MockNWebAccessibilityNodeInfo>();
    auto nodePtr = std::make_shared<NG::TransitionalNodeInfo>(nWebAccessibilityNodeInfoPtr);
    AccessibilityElementInfo nodeInfo;

    jsAccessibilityManager->WebSetScreenRect(nodePtr, commonProperty, nodeInfo);
    auto rect = nodeInfo.GetRectInScreen();
    EXPECT_EQ(rect.GetLeftTopXScreenPostion(), 0);
    EXPECT_EQ(rect.GetLeftTopYScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomXScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomYScreenPostion(), 0);

    commonProperty.rotateTransform.rotateDegree = 0;
    jsAccessibilityManager->WebSetScreenRect(nodePtr, commonProperty, nodeInfo);
    rect = nodeInfo.GetRectInScreen();
    EXPECT_EQ(rect.GetLeftTopXScreenPostion(), 0);
    EXPECT_EQ(rect.GetLeftTopYScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomXScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomYScreenPostion(), 0);
}

/**
 * @tc.name: WebSetScreenRect002
 * @tc.desc: WebSetScreenRect degree = 0, scaleX != 1, scaleY = 1
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerWebTest, WebSetScreenRect002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Framework::CommonProperty commonProperty;
    commonProperty.rotateTransform.rotateDegree = 0;
    commonProperty.scaleX = 3.0f;
    commonProperty.scaleY = 1.0f;
    auto nWebAccessibilityNodeInfoPtr = std::make_shared<MockNWebAccessibilityNodeInfo>();
    auto nodePtr = std::make_shared<NG::TransitionalNodeInfo>(nWebAccessibilityNodeInfoPtr);
    AccessibilityElementInfo nodeInfo;

    jsAccessibilityManager->WebSetScreenRect(nodePtr, commonProperty, nodeInfo);
    auto rect = nodeInfo.GetRectInScreen();
    EXPECT_EQ(rect.GetLeftTopXScreenPostion(), 0);
    EXPECT_EQ(rect.GetLeftTopYScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomXScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomYScreenPostion(), 0);
}

/**
 * @tc.name: WebSetScreenRect003
 * @tc.desc: WebSetScreenRect degree = 0, scaleX = 1, scaleY != 1
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerWebTest, WebSetScreenRect003, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Framework::CommonProperty commonProperty;
    commonProperty.rotateTransform.rotateDegree = 0;
    commonProperty.scaleX = 1.0f;
    commonProperty.scaleY = 3.0f;
    auto nWebAccessibilityNodeInfoPtr = std::make_shared<MockNWebAccessibilityNodeInfo>();
    auto nodePtr = std::make_shared<NG::TransitionalNodeInfo>(nWebAccessibilityNodeInfoPtr);
    AccessibilityElementInfo nodeInfo;

    jsAccessibilityManager->WebSetScreenRect(nodePtr, commonProperty, nodeInfo);
    auto rect = nodeInfo.GetRectInScreen();
    EXPECT_EQ(rect.GetLeftTopXScreenPostion(), 0);
    EXPECT_EQ(rect.GetLeftTopYScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomXScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomYScreenPostion(), 0);
}

/**
 * @tc.name: WebSetScreenRect004
 * @tc.desc: WebSetScreenRect degree = 0, scaleX != 1, scaleY != 1
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerWebTest, WebSetScreenRect004, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Framework::CommonProperty commonProperty;
    commonProperty.rotateTransform.rotateDegree = 0;
    commonProperty.scaleX = 3.0f;
    commonProperty.scaleY = 3.0f;
    auto nWebAccessibilityNodeInfoPtr = std::make_shared<MockNWebAccessibilityNodeInfo>();
    auto nodePtr = std::make_shared<NG::TransitionalNodeInfo>(nWebAccessibilityNodeInfoPtr);
    AccessibilityElementInfo nodeInfo;

    jsAccessibilityManager->WebSetScreenRect(nodePtr, commonProperty, nodeInfo);
    auto rect = nodeInfo.GetRectInScreen();
    EXPECT_EQ(rect.GetLeftTopXScreenPostion(), 0);
    EXPECT_EQ(rect.GetLeftTopYScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomXScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomYScreenPostion(), 0);
}

/**
 * @tc.name: WebSetScreenRect005
 * @tc.desc: WebSetScreenRect degree = 0, scaleX = 1, scaleY = 1
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerWebTest, WebSetScreenRect005, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    Framework::CommonProperty commonProperty;
    commonProperty.rotateTransform.rotateDegree = 0;
    commonProperty.scaleX = 1.0f;
    commonProperty.scaleY = 1.0f;
    auto nWebAccessibilityNodeInfoPtr = std::make_shared<MockNWebAccessibilityNodeInfo>();
    auto nodePtr = std::make_shared<NG::TransitionalNodeInfo>(nWebAccessibilityNodeInfoPtr);
    AccessibilityElementInfo nodeInfo;

    jsAccessibilityManager->WebSetScreenRect(nodePtr, commonProperty, nodeInfo);
    auto rect = nodeInfo.GetRectInScreen();
    EXPECT_EQ(rect.GetLeftTopXScreenPostion(), 0);
    EXPECT_EQ(rect.GetLeftTopYScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomXScreenPostion(), 0);
    EXPECT_EQ(rect.GetRightBottomYScreenPostion(), 0);
}
#endif //WEB_SUPPORTED
} // namespace OHOS::Ace::NG