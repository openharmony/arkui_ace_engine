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
} // namespace OHOS::Ace::NG
