/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#define private public
#define protected public
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef protected
#undef private

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

int32_t g_editStateFlags = 0;
std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> g_insertHandle = nullptr;
std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> g_startSelectionHandle = nullptr;
std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> g_endSelectionHandle = nullptr;

namespace OHOS::NWeb {
class NWebDateTimeChooserCallbackMock : public NWebDateTimeChooserCallback {
public:
    void Continue(bool success, const DateTime& value) override {}
};

class NWebDateTimeChooserMock : public NWebDateTimeChooser {
public:
    MOCK_METHOD0(GetType, DateTimeChooserType());
    MOCK_METHOD0(GetStep, double());
    MOCK_METHOD0(GetMinimum, DateTime());
    MOCK_METHOD0(GetMaximum, DateTime());
    MOCK_METHOD0(GetDialogValue, DateTime());
    MOCK_METHOD0(GetHasSelected, bool());
    MOCK_METHOD0(GetSuggestionIndex, size_t());
};

class NWebSelectPopupMenuCallbackMock : public NWebSelectPopupMenuCallback {
public:
    void Continue(const std::vector<int32_t>& indices) override {}

    void Cancel() override {}
};

class NWebCursorInfoMock : public NWebCursorInfo {
public:
    int32_t GetX() override
    {
        return 0;
    }

    int32_t GetY() override
    {
        return 0;
    }

    uint8_t* GetBuff() override
    {
        return nullptr;
    }

    float GetScale() override
    {
        return 0;
    }

    int32_t GetWidth() override
    {
        return 0;
    }

    int32_t GetHeight() override
    {
        return 0;
    }
};

class NWebSelectPopupMenuParamMock : public NWebSelectPopupMenuParam {
public:
    std::vector<std::shared_ptr<NWebSelectPopupMenuItem>> GetMenuItems() override
    {
        std::vector<std::shared_ptr<NWebSelectPopupMenuItem>> value;
        return value;
    }

    int GetItemHeight() override
    {
        return 0;
    }

    int GetSelectedItem() override
    {
        return 0;
    }

    double GetItemFontSize() override
    {
        return 0;
    }

    bool GetIsRightAligned() override
    {
        return true;
    }

    std::shared_ptr<NWebSelectMenuBound> GetSelectMenuBound() override
    {
        return 0;
    }

    bool GetIsAllowMultipleSelection() override
    {
        return true;
    }
};

class NWebDateTimeSuggestionMock : public NWebDateTimeSuggestion {
public:
    MOCK_METHOD0(GetValue, DateTime());
    MOCK_METHOD0(GetLabel, std::string());
    MOCK_METHOD0(GetLocalizedValue, std::string());
};

class NWebTouchHandleStateMock : public NWebTouchHandleState {
public:
    MOCK_METHOD0(GetTouchHandleId, int32_t());
    MOCK_METHOD0(GetX, int32_t());
    MOCK_METHOD0(GetY, int32_t());
    MOCK_METHOD0(GetViewPortX, int32_t());
    MOCK_METHOD0(GetViewPortY, int32_t());
    MOCK_METHOD0(GetTouchHandleType, TouchHandleType());
    MOCK_METHOD0(IsEnable, bool());
    MOCK_METHOD0(GetAlpha, float());
    MOCK_METHOD0(GetEdgeHeight, float());
};

class NWebTouchHandleStateMockDummy : public NWebTouchHandleState {
public:
    int32_t GetTouchHandleId() override
    {
        return 0;
    }

    int32_t GetX() override
    {
        return 0;
    }

    int32_t GetY() override
    {
        return y_;
    }

    int32_t GetViewPortX() override
    {
        return 0;
    }

    int32_t GetViewPortY() override
    {
        return 0;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::INSERT_HANDLE;
    }

    bool IsEnable() override
    {
        return isEnable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return getEdgeHeight_;
    }

    bool isEnable_ = false;
    TouchHandleType type_ = TouchHandleType::INSERT_HANDLE;
    int32_t alpha_ = 0;
    int32_t y_ = 0;
    float getEdgeHeight_ = 0.0f;
};

class NWebQuickMenuParamsSelectImpl : public NWebQuickMenuParams {
public:
    int32_t GetXCoord() override
    {
        return 0;
    }

    int32_t GetYCoord() override
    {
        return 0;
    }

    int32_t GetWidth() override
    {
        return 0;
    }

    int32_t GetHeight() override
    {
        return 0;
    }

    int32_t GetEditStateFlags() override
    {
        return g_editStateFlags;
    }

    int32_t GetSelectX() override
    {
        return 0;
    }
    int32_t GetSelectY() override
    {
        return 0;
    }

    int32_t GetSelectWidth() override
    {
        return 0;
    }

    int32_t GetSelectXHeight() override
    {
        return 0;
    }

    std::shared_ptr<NWebTouchHandleState> GetTouchHandleState(NWebTouchHandleState::TouchHandleType type) override
    {
        if (type == NWebTouchHandleState::TouchHandleType::INSERT_HANDLE) {
            return g_insertHandle;
        } else if (type == NWebTouchHandleState::TouchHandleType::SELECTION_BEGIN_HANDLE) {
            return g_startSelectionHandle;
        }
        return g_endSelectionHandle;
    }

    bool GetIsLongPressActived() override
    {
        return false;
    }
};

class NWebQuickMenuCallbackMock : public NWebQuickMenuCallback {
public:
    void Continue(int32_t commandId, MenuEventFlags flag) {}

    void Cancel() {}
};

class CustomNWebTouchHandleState : public OHOS::NWeb::NWebTouchHandleState {
public:
    void SetAlpha(float alpha)
    {
        alpha_ = alpha;
    }

    void SetY(int32_t y)
    {
        y_ = y;
    }

    void SetEdgeHeight(float edgeHeight)
    {
        edgeHeight_ = edgeHeight;
    }

    bool IsUnEnable()
    {
        return false;
    }

    int32_t GetTouchHandleId() override
    {
        return 0;
    }

    int32_t GetX() override
    {
        return 0;
    }

    int32_t GetY() override
    {
        return y_;
    }

    int32_t GetViewPortX() override
    {
        return 0;
    }

    int32_t GetViewPortY() override
    {
        return 0;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return INSERT_HANDLE;
    }

    bool IsEnable() override
    {
        return true;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }

private:
    float alpha_ = 0.0;
    int32_t y_ = 0;
    float edgeHeight_ = 0.0;
};
} // namespace OHOS::NWeb

namespace OHOS::Ace::NG {
class WebPatternSelectTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternSelectTestNg::SetUpTestCase() {}
void WebPatternSelectTestNg::TearDownTestCase() {}
void WebPatternSelectTestNg::SetUp() {}
void WebPatternSelectTestNg::TearDown() {}

std::vector<MenuOptionsParam> CreateMenuOptions(const std::vector<NG::MenuItemParam>&)
{
    std::vector<MenuOptionsParam> options {
        { std::nullopt, std::nullopt, std::nullopt, "option1",
            [](const std::string& id) { std::cout << "Option 1 clicked with ID: " << id << std::endl; }, true },
        { std::nullopt, std::nullopt, std::nullopt, "option2",
            [](const std::string& id) { std::cout << "Option 2 clicked with ID: " << id << std::endl; }, false },
        { std::nullopt, std::nullopt, std::nullopt, "option3",
            [](const std::string& id) { std::cout << "Option 3 clicked with ID: " << id << std::endl; }, false }
    };
    return options;
}

bool HandleMenuItemClick(const NG::MenuItemParam& item)
{
    std::cout << "Clicked on menu item: " << item.ToString() << std::endl;
    item.menuOptionsParam.action(item.menuOptionsParam.id);
    return true;
}

/**
 * @tc.name: OnTouchSelectionChanged_001
 * @tc.desc: OnTouchSelectionChanged
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnTouchSelectionChanged_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(endSelectionHandle, nullptr);
    EXPECT_CALL(*insertHandle, IsEnable()).WillRepeatedly(Return(true));
    EXPECT_CALL(*startSelectionHandle, IsEnable()).WillRepeatedly(Return(false));
    EXPECT_CALL(*endSelectionHandle, IsEnable()).WillRepeatedly(Return(true));
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

/**
 * @tc.name: OnTouchSelectionChanged_002
 * @tc.desc: OnTouchSelectionChanged
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnTouchSelectionChanged_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(endSelectionHandle, nullptr);
    EXPECT_CALL(*insertHandle, IsEnable()).WillRepeatedly(Return(true));
    EXPECT_CALL(*startSelectionHandle, IsEnable()).WillRepeatedly(Return(false));
    EXPECT_CALL(*endSelectionHandle, IsEnable()).WillRepeatedly(Return(false));
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

/**
 * @tc.name: OnTouchSelectionChanged_003
 * @tc.desc: OnTouchSelectionChanged
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnTouchSelectionChanged_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(endSelectionHandle, nullptr);
    EXPECT_CALL(*insertHandle, IsEnable()).WillRepeatedly(Return(false));
    EXPECT_CALL(*startSelectionHandle, IsEnable()).WillRepeatedly(Return(true));
    EXPECT_CALL(*endSelectionHandle, IsEnable()).WillRepeatedly(Return(true));
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

/**
 * @tc.name: OnCursorChange_001
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnCursorChange_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    auto info = std::make_shared<NWeb::NWebCursorInfoMock>();
    ASSERT_NE(info, nullptr);
    webPattern->isHoverExit_ = true;
    ASSERT_TRUE(webPattern->isHoverExit_);
    bool ret = webPattern->OnCursorChange(type, info);
    ASSERT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnCursorChange_002
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnCursorChange_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_CONTEXTMENU;
    auto info = std::make_shared<NWeb::NWebCursorInfoMock>();
    ASSERT_NE(info, nullptr);
    webPattern->isHoverExit_ = true;
    ASSERT_TRUE(webPattern->isHoverExit_);
    bool ret = webPattern->OnCursorChange(type, info);
    ASSERT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnCursorChange_003
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnCursorChange_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    auto info = std::make_shared<NWeb::NWebCursorInfoMock>();
    ASSERT_NE(info, nullptr);
    webPattern->isHoverExit_ = false;
    ASSERT_FALSE(webPattern->isHoverExit_);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    bool ret = webPattern->OnCursorChange(type, info);
    ASSERT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnCursorChange_004
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnCursorChange_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_MAX_VALUE;
    auto info = std::make_shared<NWeb::NWebCursorInfoMock>();
    ASSERT_NE(info, nullptr);
    webPattern->isHoverExit_ = false;
    ASSERT_FALSE(webPattern->isHoverExit_);
    bool ret = webPattern->OnCursorChange(type, info);
    ASSERT_FALSE(ret);
#endif
}

/**
 * @tc.name: UpdateLocalCursorStyle_001
 * @tc.desc: UpdateLocalCursorStyle
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateLocalCursorStyle_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = NWeb::CursorType::CT_CONTEXTMENU;
    int32_t windowId = 1;
    webPattern->UpdateLocalCursorStyle(windowId, type);
#endif
}

/**
 * @tc.name: UpdateLocalCursorStyle_002
 * @tc.desc: UpdateLocalCursorStyle
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateLocalCursorStyle_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = NWeb::CursorType::CT_ALIAS;
    int32_t windowId = 1;
    webPattern->UpdateLocalCursorStyle(windowId, type);
#endif
}

/**
 * @tc.name: UpdateLocalCursorStyle_003
 * @tc.desc: UpdateLocalCursorStyle
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateLocalCursorStyle_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::NWeb::CursorType type = NWeb::CursorType::CT_CELL;
    int32_t windowId = 1;
    webPattern->UpdateLocalCursorStyle(windowId, type);
#endif
}

/**
 * @tc.name: UpdateCustomCursor_001
 * @tc.desc: UpdateCustomCursor
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateCustomCursor_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto info = std::make_shared<NWeb::NWebCursorInfoMock>();
    ASSERT_NE(info, nullptr);
    int32_t windowId = 1;
    webPattern->UpdateCustomCursor(windowId, info);
#endif
}

/**
 * @tc.name: UpdateCustomCursor_002
 * @tc.desc: UpdateCustomCursor
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateCustomCursor_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCursorInfoMock> info = nullptr;
    ASSERT_EQ(info, nullptr);
    int32_t windowId = 1;
    webPattern->UpdateCustomCursor(windowId, info);
#endif
}

/**
 * @tc.name: CreatePixelMapFromString_001
 * @tc.desc: CreatePixelMapFromString
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, CreatePixelMapFromString_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::string filePath = "";
    webPattern->CreatePixelMapFromString(filePath);
#endif
}

/**
 * @tc.name: CreatePixelMapFromString_002
 * @tc.desc: CreatePixelMapFromString
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, CreatePixelMapFromString_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::string filePath = "filePath";
    webPattern->CreatePixelMapFromString(filePath);
#endif
}

/**
 * @tc.name: OnTooltip_001
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnTooltip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->tooltipId_ = 0;
    ASSERT_EQ(webPattern->tooltipId_, 0);
    std::string tooltip = "";
    webPattern->OnTooltip(tooltip);
    ASSERT_NE(webPattern->tooltipId_, -1);
#endif
}

/**
 * @tc.name: OnPopupSize_001
 * @tc.desc: OnPopupSize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnPopupSize_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    int32_t x = 1, y = 2, width = 1, height = 1;
    webPattern->renderContextForPopupSurface_ = RenderContext::Create();
    auto surface = AceType::DynamicCast<MockRenderContext>(webPattern->renderContextForPopupSurface_);
    ASSERT_NE(surface, nullptr);
    EXPECT_CALL(
        *AceType::DynamicCast<MockRenderContext>(webPattern->renderContextForPopupSurface_), SetBounds(1, 2, 1, 1))
        .WillOnce(Return());
    ASSERT_NE(webPattern->renderContextForPopupSurface_, nullptr);
    webPattern->OnPopupSize(x, y, width, height);
#endif
}

/**
 * @tc.name: OnPopupSize_002
 * @tc.desc: OnPopupSize
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnPopupSize_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    int32_t x = 1, y = 2, width = 1, height = 1;
    webPattern->renderContextForPopupSurface_ = nullptr;
    ASSERT_EQ(webPattern->renderContextForPopupSurface_, nullptr);
    webPattern->OnPopupSize(x, y, width, height);
#endif
}

/**
 * @tc.name: OnPopupShow_001
 * @tc.desc: OnPopupShow
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnPopupShow_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    bool show = false;
    webPattern->renderContextForPopupSurface_ = RenderContext::Create();
    auto surface = AceType::DynamicCast<MockRenderContext>(webPattern->renderContextForPopupSurface_);
    ASSERT_NE(surface, nullptr);
    EXPECT_CALL(
        *AceType::DynamicCast<MockRenderContext>(webPattern->renderContextForPopupSurface_), SetBounds(0, 0, 0, 0))
        .WillOnce(Return());
    ASSERT_NE(webPattern->renderContextForPopupSurface_, nullptr);
    webPattern->OnPopupShow(show);
#endif
}

/**
 * @tc.name: OnPopupShow_002
 * @tc.desc: OnPopupShow
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnPopupShow_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    bool show = false;
    webPattern->renderContextForPopupSurface_ = nullptr;
    ASSERT_EQ(webPattern->renderContextForPopupSurface_, nullptr);
    webPattern->OnPopupShow(show);
#endif
}

/**
 * @tc.name: OnPopupShow_003
 * @tc.desc: OnPopupShow
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnPopupShow_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    bool show = true;
    webPattern->OnPopupShow(show);
#endif
}

/**
 * @tc.name: AttachCustomKeyboard_001
 * @tc.desc: AttachCustomKeyboard
 * @tc.type: FUNC
 */
void BuildCustomKeyboard()
{
    std::cout << "Building custom keyboard" << std::endl;
}
HWTEST_F(WebPatternSelectTestNg, AttachCustomKeyboard_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->SetCustomKeyboardBuilder(BuildCustomKeyboard);
    ASSERT_NE(webPattern->customKeyboardBuilder_, nullptr);
    webPattern->AttachCustomKeyboard();
#endif
}

/**
 * @tc.name: AttachCustomKeyboard_002
 * @tc.desc: AttachCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, AttachCustomKeyboard_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->SetCustomKeyboardBuilder(nullptr);
    ASSERT_EQ(webPattern->customKeyboardBuilder_, nullptr);
    webPattern->AttachCustomKeyboard();
#endif
}

/**
 * @tc.name: CloseCustomKeyboard_001
 * @tc.desc: CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, CloseCustomKeyboard_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->SetCustomKeyboardBuilder(BuildCustomKeyboard);
    ASSERT_NE(webPattern->customKeyboardBuilder_, nullptr);
    webPattern->CloseCustomKeyboard();
#endif
}

/**
 * @tc.name: CloseCustomKeyboard_002
 * @tc.desc: CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, CloseCustomKeyboard_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->SetCustomKeyboardBuilder(nullptr);
    ASSERT_EQ(webPattern->customKeyboardBuilder_, nullptr);
    webPattern->CloseCustomKeyboard();
#endif
}

/**
 * @tc.name: HandleShowTooltip_001
 * @tc.desc: HandleShowTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HandleShowTooltip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    const std::string& tooltip = "";
    int64_t tooltipTimestamp = 0;
    webPattern->tooltipTimestamp_ = 0;
    webPattern->HandleShowTooltip(tooltip, tooltipTimestamp);
#endif
}

/**
 * @tc.name: HandleShowTooltip_002
 * @tc.desc: HandleShowTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HandleShowTooltip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    const std::string& tooltip = "tooltip";
    int64_t tooltipTimestamp = -1;
    webPattern->tooltipTimestamp_ = -1;
    webPattern->HandleShowTooltip(tooltip, tooltipTimestamp);
#endif
}

/**
 * @tc.name: HandleShowTooltip_003
 * @tc.desc: HandleShowTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HandleShowTooltip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    const std::string& tooltip = "";
    int64_t tooltipTimestamp = -1;
    webPattern->tooltipTimestamp_ = 0;
    webPattern->HandleShowTooltip(tooltip, tooltipTimestamp);
#endif
}

/**
 * @tc.name: ShowTooltip_001
 * @tc.desc: ShowTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, ShowTooltip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    const std::string& tooltip = "tooltip";
    int64_t tooltipTimestamp = -1;
    webPattern->ShowTooltip(tooltip, tooltipTimestamp);
#endif
}

/**
 * @tc.name: CalculateTooltipOffset_001
 * @tc.desc: CalculateTooltipOffset
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, CalculateTooltipOffset_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto tooltipOffset = std::make_shared<OffsetF>();
    ASSERT_NE(tooltipOffset, nullptr);
    RefPtr<FrameNode> tooltipNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(tooltipNode, nullptr);
    tooltipNode->layoutProperty_ = nullptr;
    ASSERT_EQ(tooltipNode->layoutProperty_, nullptr);
    webPattern->CalculateTooltipOffset(tooltipNode, *tooltipOffset);
#endif
}

/**
 * @tc.name: OnSelectPopupMenu_001
 * @tc.desc: OnSelectPopupMenu
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnSelectPopupMenu_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    webPattern->OnSelectPopupMenu(params, callback);
#endif
}

/**
 * @tc.name: OnSelectPopupMenu_002
 * @tc.desc: OnSelectPopupMenu
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnSelectPopupMenu_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params = nullptr;
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    webPattern->OnSelectPopupMenu(params, callback);
#endif
}

/**
 * @tc.name: OnSelectPopupMenu_003
 * @tc.desc: OnSelectPopupMenu
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnSelectPopupMenu_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback = nullptr;
    webPattern->OnSelectPopupMenu(params, callback);
#endif
}

/**
 * @tc.name: NotifyForNextTouchEvent_001
 * @tc.desc: NotifyForNextTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, NotifyForNextTouchEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->NotifyForNextTouchEvent();
#endif
}

/**
 * @tc.name: NotifyForNextTouchEvent_002
 * @tc.desc: NotifyForNextTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, NotifyForNextTouchEvent_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_ = nullptr;
    ASSERT_EQ(webPattern->delegate_, nullptr);
    webPattern->NotifyForNextTouchEvent();
#endif
}

/**
 * @tc.name: InitTouchEventListener_001
 * @tc.desc: InitTouchEventListener
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, InitTouchEventListener_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEventListener_ = nullptr;
    ASSERT_EQ(webPattern->touchEventListener_, nullptr);
    webPattern->InitTouchEventListener();
#endif
}

/**
 * @tc.name: InitTouchEventListener_002
 * @tc.desc: InitTouchEventListener
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, InitTouchEventListener_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEventListener_ = std::make_shared<TouchEventListener>();
    ASSERT_NE(webPattern->touchEventListener_, nullptr);
    webPattern->InitTouchEventListener();
#endif
}

/**
 * @tc.name: UninitTouchEventListener_001
 * @tc.desc: UninitTouchEventListener
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UninitTouchEventListener_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->UninitTouchEventListener();
#endif
}

/**
 * @tc.name: OnDateTimeChooserPopup_001
 * @tc.desc: OnDateTimeChooserPopup
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnDateTimeChooserPopup_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserMock> chooser = nullptr;
    ASSERT_EQ(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestionMock> Suggestion =
        std::make_shared<OHOS::NWeb::NWebDateTimeSuggestionMock>();
    ASSERT_NE(Suggestion, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.push_back(Suggestion);
    ASSERT_FALSE(suggestions.empty());
    webPattern->OnDateTimeChooserPopup(chooser, suggestions, callback);
#endif
}

/**
 * @tc.name: OnDateTimeChooserPopup_002
 * @tc.desc: OnDateTimeChooserPopup
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnDateTimeChooserPopup_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserMock> chooser =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestionMock> Suggestion =
        std::make_shared<OHOS::NWeb::NWebDateTimeSuggestionMock>();
    ASSERT_NE(Suggestion, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.push_back(Suggestion);
    ASSERT_NE(suggestions.size(), 0);
    webPattern->OnDateTimeChooserPopup(chooser, suggestions, callback);
#endif
}

/**
 * @tc.name: OnDateTimeChooserPopup_003
 * @tc.desc: OnDateTimeChooserPopup
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnDateTimeChooserPopup_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserMock> chooser =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.clear();
    ASSERT_EQ(suggestions.size(), 0);
    EXPECT_CALL(*chooser, GetType).WillRepeatedly(Return(NWeb::DTC_TIME));
    webPattern->OnDateTimeChooserPopup(chooser, suggestions, callback);
#endif
}

/**
 * @tc.name: OnDateTimeChooserPopup_004
 * @tc.desc: OnDateTimeChooserPopup
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnDateTimeChooserPopup_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserMock> chooser =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.clear();
    ASSERT_EQ(suggestions.size(), 0);
    EXPECT_CALL(*chooser, GetType).WillRepeatedly(Return(NWeb::DTC_DATETIME_LOCAL));
    webPattern->OnDateTimeChooserPopup(chooser, suggestions, callback);
#endif
}

/**
 * @tc.name: GetDialogProperties_001
 * @tc.desc: GetDialogProperties
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, GetDialogProperties_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme = builder.Build(nullptr);
    EXPECT_NE(theme, nullptr);
    // SystemProperties::InitDeviceType(DeviceType::PHONE);
    webPattern->GetDialogProperties(theme);
#endif
}

/**
 * @tc.name: ShowDateTimeDialog_001
 * @tc.desc: ShowDateTimeDialog
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, ShowDateTimeDialog_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserMock> chooser =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.clear();
    ASSERT_EQ(suggestions.size(), 0);
    EXPECT_CALL(*chooser, GetType).WillRepeatedly(Return(NWeb::DTC_TIME));
    webPattern->ShowDateTimeDialog(chooser, suggestions, callback);
#endif
}

/**
 * @tc.name: StopListenSelectOverlayParentScroll
 * @tc.desc: StopListenSelectOverlayParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, StopListenSelectOverlayParentScroll, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->StopListenSelectOverlayParentScroll(frameNode);
#endif
}

/**
 * @tc.name: RegisterSelectOverlayCallback_001
 * @tc.desc: RegisterSelectOverlayCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RegisterSelectOverlayCallback_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->delegate_ = nullptr;
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    webPattern->RegisterSelectOverlayCallback(selectInfo, params, callback);
#endif
}

/**
 * @tc.name: RegisterSelectOverlayCallback_002
 * @tc.desc: RegisterSelectOverlayCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RegisterSelectOverlayCallback_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::string type_ = "image/png";
    webPattern->OnModifyDone();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    webPattern->RegisterSelectOverlayCallback(selectInfo, params, callback);
#endif
}

/**
 * @tc.name: RegisterSelectOverlayCallback_003
 * @tc.desc: RegisterSelectOverlayCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RegisterSelectOverlayCallback_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::string type_ = "image/png";
    webPattern->OnModifyDone();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    auto flags = g_editStateFlags;
    g_editStateFlags = 0;
    webPattern->RegisterSelectOverlayCallback(selectInfo, params, callback);
    EXPECT_EQ(webPattern->quickMenuCallback_, callback);
    g_editStateFlags = flags;
#endif
}

/**
 * @tc.name: RegisterSelectOverlayEvent
 * @tc.desc: RegisterSelectOverlayEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RegisterSelectOverlayEvent, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    SelectOverlayInfo selectInfo;
    webPattern->RegisterSelectOverlayEvent(selectInfo);
#endif
}

/**
 * @tc.name: ComputeMouseClippedSelectionBounds
 * @tc.desc: ComputeMouseClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, ComputeMouseClippedSelectionBounds, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    int32_t startX = 10;
    int32_t startY = 20;
    int32_t width = 100;
    int32_t height = 50;
    auto ret1 = webPattern->ComputeMouseClippedSelectionBounds(startX, startY, width, height);
    EXPECT_EQ(ret1.GetY(), 0);
    auto ret2 = webPattern->ComputeMouseClippedSelectionBounds(0, -1, 0, 0);
    EXPECT_EQ(ret2.GetY(), 0);
    auto ret3 = webPattern->ComputeMouseClippedSelectionBounds(0, -1, 0, 2);
    EXPECT_EQ(ret3.GetY(), -1);
#endif
}

/**
 * @tc.name: UpdateClippedSelectionBounds_001
 * @tc.desc: UpdateClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateClippedSelectionBounds_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    int32_t startX = 10;
    int32_t startY = 20;
    int32_t width = 100;
    int32_t height = 50;
    webPattern->UpdateClippedSelectionBounds(startX, startY, width, height);
#endif
}

/**
 * @tc.name: UpdateClippedSelectionBounds_002
 * @tc.desc: UpdateClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateClippedSelectionBounds_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    int32_t startX = 10;
    int32_t startY = 20;
    int32_t width = 100;
    int32_t height = 50;
    int32_t selectOverlayId = 1;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(selectOverlayId);
    webPattern->isQuickMenuMouseTrigger_ = true;
    webPattern->UpdateClippedSelectionBounds(startX, startY, width, height);
#endif
}

/**
 * @tc.name: SelectCancel_001
 * @tc.desc: SelectCancel.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, SelectCancel_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    webPattern->quickMenuCallback_ = callback;
    webPattern->SelectCancel();
#endif
}

/**
 * @tc.name: SelectCancel_002
 * @tc.desc: SelectCancel.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, SelectCancel_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->isReceivedArkDrag_ = true;
    webPattern->SelectCancel();
#endif
}

/**
 * @tc.name: GetSelectInfo
 * @tc.desc: GetSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, GetSelectInfo, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    webPattern->GetSelectInfo();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: OnSelectionMenuOptionsUpdate_001
 * @tc.desc: OnSelectionMenuOptionsUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnSelectionMenuOptionsUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    NG::MenuOptionsParam option1;
    std::vector<NG::MenuOptionsParam> options;
    option1.action = [](const std::string&) {};
    options.push_back(option1);
    WebMenuOptionsParam webMenuOption;
    webMenuOption.menuOption = options;
    webPattern->OnSelectionMenuOptionsUpdate(webMenuOption);
    for (auto& menuOption : webPattern->menuOptionParam_) {
        if (menuOption.action) {
            std::string someString = "Example Selection";
            menuOption.action(someString);
        }
    }
    EXPECT_FALSE(webPattern->menuOptionParam_.empty());
#endif
}

/**
 * @tc.name: OnSelectionMenuOptionsUpdate_002
 * @tc.desc: OnSelectionMenuOptionsUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, OnSelectionMenuOptionsUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    NG::MenuOptionsParam option1;
    std::vector<NG::MenuOptionsParam> options;
    options.push_back(option1);
    WebMenuOptionsParam webMenuOption;
    webMenuOption.menuOption = options;
    webPattern->OnSelectionMenuOptionsUpdate(webMenuOption);
    for (auto& menuOption : webPattern->menuOptionParam_) {
        if (menuOption.action) {
            std::string someString = "Example Selection";
            menuOption.action(someString);
        }
    }
    EXPECT_FALSE(webPattern->menuOptionParam_.empty());
#endif
}

/**
 * @tc.name: UpdateEditMenuOptions
 * @tc.desc: UpdateEditMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateEditMenuOptions, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptions;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClick;
    webPattern->UpdateEditMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_001
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateRunQuickMenuSelectInfo_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptions;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClick;
    webPattern->UpdateEditMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
    webPattern->UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(webPattern->isQuickMenuMouseTrigger_);
    int start = 0, end = 0;
    selectInfo.onCreateCallback.textRangeCallback(start, end);
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_002
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateRunQuickMenuSelectInfo_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = true;
    webPattern->UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(webPattern->isQuickMenuMouseTrigger_);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_003
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateRunQuickMenuSelectInfo_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptions;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClick;
    webPattern->onCreateMenuCallback_ = nullptr;
    webPattern->onMenuItemClick_ = nullptr;
    webPattern->UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(webPattern->isQuickMenuMouseTrigger_);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_004
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, UpdateRunQuickMenuSelectInfo_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptions;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClick;
    webPattern->onCreateMenuCallback_ =
        [](const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        std::vector<MenuOptionsParam> menuOptions;
        return menuOptions;
    };
    webPattern->onMenuItemClick_ = [](const NG::MenuItemParam& menuItem) -> bool { return false; };
    webPattern->UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(webPattern->isQuickMenuMouseTrigger_);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_000
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_000, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = true;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);

    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = false;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = false;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(webPattern->selectTemporarilyHidden_, hide);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_001
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(webPattern->selectTemporarilyHidden_, hide);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_002
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    bool hide = false;
    bool isScroll = false;
    webPattern->selectTemporarilyHiddenByScroll_ = false;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_EQ(webPattern->selectTemporarilyHidden_, hide);
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_EQ(webPattern->selectTemporarilyHidden_, hide);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_003
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    webPattern->selectOverlayProxy_ = nullptr;
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_EQ(webPattern->selectOverlayProxy_, nullptr);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_004
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(webPattern->selectOverlayProxy_, nullptr);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_005
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    bool hide = false;
    bool isScroll = true;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->dropParams_ = std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    ASSERT_NE(webPattern->dropParams_, nullptr);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(webPattern->selectOverlayProxy_, nullptr);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_006
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    bool hide = false;
    bool isScroll = true;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->dropParams_ = std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    ASSERT_NE(webPattern->dropParams_, nullptr);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(webPattern->dropParams_, nullptr);
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    auto info = webPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo();
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    info.menuInfo.menuIsShow = true;
    manager->selectOverlayInfo_ = info;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    webPattern->selectOverlayProxy_ = nullptr;
    MockPipelineContext::TearDown();
    EXPECT_NE(webPattern->dropParams_, nullptr);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_007
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, HideHandleAndQuickMenuIfNecessary_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    bool hide = false;
    bool isScroll = true;
    int32_t selectOverlayId = 1;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(selectOverlayId);
    webPattern->dropParams_ = std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    ASSERT_NE(webPattern->dropParams_, nullptr);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    webPattern->insertHandle_ = insertHandle;
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    startSelectionHandle->alpha_ = 1;
    startSelectionHandle->y_ = 0;
    webPattern->startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    endSelectionHandle->alpha_ = 1;
    endSelectionHandle->y_ = 0;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(webPattern->dropParams_, nullptr);
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    auto info = webPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo();
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    info.menuInfo.menuIsShow = false;
    manager->selectOverlayInfo_ = info;
    auto node = manager->GetSelectOverlayNode(current->GetId());
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    webPattern->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_FALSE(pattern->info_->isNewAvoid);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: ChangeVisibilityOfQuickMenu
 * @tc.desc: ChangeVisibilityOfQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, ChangeVisibilityOfQuickMenu, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    int32_t selectOverlayId = 1;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(selectOverlayId);
    webPattern->ChangeVisibilityOfQuickMenu();
#endif
}

/**
 * @tc.name: IsQuickMenuShow
 * @tc.desc: IsQuickMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, IsQuickMenuShow, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    int32_t selectOverlayId = 1;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(selectOverlayId);
    webPattern->IsQuickMenuShow();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: RunQuickMenu_001
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RunQuickMenu_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    webPattern->RunQuickMenu(params, callback);
    EXPECT_TRUE(webPattern);
#endif
}

/**
 * @tc.name: RunQuickMenu_002
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RunQuickMenu_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    webPattern->isQuickMenuMouseTrigger_ = true;
    webPattern->RunQuickMenu(params, callback);
    EXPECT_TRUE(webPattern);
#endif
}

/**
 * @tc.name: RunQuickMenu_003
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternSelectTestNg, RunQuickMenu_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    int32_t selectOverlayId = 1;
    webPattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(selectOverlayId);
    webPattern->RunQuickMenu(params, callback);
    EXPECT_TRUE(webPattern);
#endif
}
} // namespace OHOS::Ace::NG
