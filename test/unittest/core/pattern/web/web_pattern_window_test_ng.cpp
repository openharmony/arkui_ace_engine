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

#include "gtest/gtest.h"
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/web/webview/ohos_nweb/include/nweb_handler.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::NWeb {
class NWebDateTimeChooserCallbackMock : public NWebDateTimeChooserCallback {
public:
    void Continue(bool success, const DateTime& value) override {}
};

class NWebSelectPopupMenuCallbackMock : public NWebSelectPopupMenuCallback {
public:
    void Continue(const std::vector<int32_t>& indices) override {}

    void Cancel() override {}
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
} // namespace OHOS::NWeb

namespace OHOS::Ace::NG {
class WebPatternWindowTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternWindowTestNg::SetUpTestCase() {}
void WebPatternWindowTestNg::TearDownTestCase() {}
void WebPatternWindowTestNg::SetUp() {}
void WebPatternWindowTestNg::TearDown() {}

class NWebDateTimeChooserMock : public NWeb::NWebDateTimeChooser {
public:
    NWebDateTimeChooserMock() = default;
    NWeb::DateTimeChooserType GetType()
    {
        return NWeb::DateTimeChooserType::DTC_DATE;
    }

    double GetStep()
    {
        return 0;
    }

    NWeb::DateTime GetMinimum()
    {
        NWeb::DateTime time = {};
        return time;
    }

    NWeb::DateTime GetMaximum()
    {
        NWeb::DateTime time = {};
        return time;
    }

    NWeb::DateTime GetDialogValue()
    {
        NWeb::DateTime time = {};
        return time;
    }

    MOCK_METHOD0(GetHasSelected, bool());

    size_t GetSuggestionIndex()
    {
        size_t size = 0;
        return size;
    }
};

class WebDelegateMock : public OHOS::Ace::WebDelegate {
public:
    WebDelegateMock(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebDelegate(context, std::move(onError), type, id)
    {}
    MOCK_METHOD0(GetIsSmoothDragResizeEnabled, bool());
    MOCK_METHOD0(GetPendingSizeStatus, bool());
};

class FullScreenEnterEventMock : public FullScreenEnterEvent {
public:
    FullScreenEnterEventMock(
        const RefPtr<FullScreenExitHandler>& handler, int videoNaturalWidth, int videoNaturalHeight)
        : FullScreenEnterEvent(handler, videoNaturalWidth, videoNaturalHeight)
    {}
    ~FullScreenEnterEventMock() = default;
    MOCK_METHOD0(GetHandler, RefPtr<FullScreenExitHandler>());
};

class FullScreenExitHandlerMock : public FullScreenExitHandler {
public:
    FullScreenExitHandlerMock() = default;
    ~FullScreenExitHandlerMock() = default;
    void ExitFullScreen() {};
};

/**
 * @tc.name: ShowTimeDialogTest001
 * @tc.desc: Test ShowTimeDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowTimeDialogTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto chooserMock = std::make_shared<NWebDateTimeChooserMock>();
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    auto callbackMock = std::make_shared<NWeb::NWebDateTimeChooserCallbackMock>();
    bool result = false;

    result = webPattern->ShowTimeDialog(chooserMock, suggestions, callbackMock);
}

/**
 * @tc.name: ShowTimeDialogTest002
 * @tc.desc: Test ShowTimeDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowTimeDialogTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto chooserMock = std::make_shared<NWebDateTimeChooserMock>();
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    auto callbackMock = std::make_shared<NWeb::NWebDateTimeChooserCallbackMock>();
    bool result = false;

    result = webPattern->ShowTimeDialog(chooserMock, suggestions, callbackMock);
}

/**
 * @tc.name: OnDateTimeChooserCloseTest001
 * @tc.desc: Test OnDateTimeChooserClose.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnDateTimeChooserCloseTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->OnDateTimeChooserClose();
}

/**
 * @tc.name: UpdateLocaleTest001
 * @tc.desc: Test UpdateLocale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, UpdateLocaleTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->delegate_ = nullptr;
    EXPECT_EQ(webPattern->delegate_, nullptr);
    webPattern->UpdateLocale();
}

/**
 * @tc.name: UpdateLocaleTest002
 * @tc.desc: Test UpdateLocale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, UpdateLocaleTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->UpdateLocale();
}

/**
 * @tc.name: OnWindowSizeChangedTest001
 * @tc.desc: Test OnWindowSizeChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnWindowSizeChangedTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
}

/**
 * @tc.name: OnResizeNotWorkTest001
 * @tc.desc: Test OnResizeNotWork.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnResizeNotWorkTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->isInWindowDrag_ = false;
    webPattern->OnResizeNotWork();
    EXPECT_EQ(webPattern->isWaiting_, false);
}

/**
 * @tc.name: OnResizeNotWorkTest002
 * @tc.desc: Test OnResizeNotWork.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnResizeNotWorkTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->isInWindowDrag_ = true;
    webPattern->isWaiting_ = true;
    webPattern->OnResizeNotWork();
    EXPECT_EQ(webPattern->isWaiting_, false);
}

/**
 * @tc.name: SetFullScreenExitHandlerTest001
 * @tc.desc: Test SetFullScreenExitHandler.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, SetFullScreenExitHandlerTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    RefPtr<FullScreenExitHandler> handler;
    int videoNaturalWidth = 10;
    int videoNaturalHeight = 10;
    auto fullScreenExitHandler = std::make_shared<FullScreenEnterEvent>(handler, videoNaturalWidth, videoNaturalHeight);
    EXPECT_NE(fullScreenExitHandler, nullptr);
    webPattern->SetFullScreenExitHandler(fullScreenExitHandler);
}

/**
 * @tc.name: OnSmoothDragResizeEnabledUpdateTest001
 * @tc.desc: Test OnSmoothDragResizeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnSmoothDragResizeEnabledUpdateTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->delegate_ = nullptr;
    EXPECT_EQ(webPattern->delegate_, nullptr);
    webPattern->OnSmoothDragResizeEnabledUpdate(true);
}

/**
 * @tc.name: OnSmoothDragResizeEnabledUpdateTest002
 * @tc.desc: Test OnSmoothDragResizeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnSmoothDragResizeEnabledUpdateTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->OnSmoothDragResizeEnabledUpdate(true);
}

/**
 * @tc.name: ShowDateTimeSuggestionDialogTest001
 * @tc.desc: Test ShowDateTimeSuggestionDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowDateTimeSuggestionDialogTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto chooserMock = std::make_shared<NWebDateTimeChooserMock>();
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    auto callbackMock = std::make_shared<NWeb::NWebDateTimeChooserCallbackMock>();
    EXPECT_NE(callbackMock, nullptr);
    bool result = false;

    result = webPattern->ShowDateTimeSuggestionDialog(chooserMock, suggestions, callbackMock);
}

/**
 * @tc.name: ShowDateTimeSuggestionDialogTest002
 * @tc.desc: Test ShowDateTimeSuggestionDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowDateTimeSuggestionDialogTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto chooserMock = std::make_shared<NWebDateTimeChooserMock>();
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    auto callbackMock = std::make_shared<NWeb::NWebDateTimeChooserCallbackMock>();
    bool result = false;

    result = webPattern->ShowDateTimeSuggestionDialog(chooserMock, suggestions, callbackMock);
}

/**
 * @tc.name: InitSelectPopupMenuViewOptionTest001
 * @tc.desc: Test InitSelectPopupMenuViewOption.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, InitSelectPopupMenuViewOptionTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    std::vector<RefPtr<FrameNode>> options;
    auto callback = std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    auto params = std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
    double dipScale = 0;

    webPattern->InitSelectPopupMenuViewOption(options, callback, params, dipScale);
}

/**
 * @tc.name: InitSelectPopupMenuViewTest001
 * @tc.desc: Test InitSelectPopupMenuView.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, InitSelectPopupMenuViewTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    std::string tag = "tag";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    bool isRoot = false;
    bool isLayoutNode = false;

    auto options = AceType::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    auto callback = std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    auto params = std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
    double dipScale = 0;

    webPattern->InitSelectPopupMenuView(options, callback, params, dipScale);
}

/**
 * @tc.name: WindowDragTest001
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = nullptr;
    EXPECT_EQ(webPattern->delegate_, nullptr);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest002
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetIsSmoothDragResizeEnabled()).WillOnce(::testing::Return(false));
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest003
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetIsSmoothDragResizeEnabled()).WillOnce(::testing::Return(true));
    webPattern->WindowDrag(0, 2);
}

/**
 * @tc.name: WindowDragTest004
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetIsSmoothDragResizeEnabled()).WillOnce(::testing::Return(true));
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest005
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetIsSmoothDragResizeEnabled()).WillOnce(::testing::Return(true));
    webPattern->WindowDrag(2, 0);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest006
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest006, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetIsSmoothDragResizeEnabled()).WillOnce(::testing::Return(true));
    webPattern->WindowDrag(2, 2);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest007
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest007, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetPendingSizeStatus()).WillOnce(::testing::Return(false));
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG_START);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest008
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest008, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetPendingSizeStatus()).WillOnce(::testing::Return(true));
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest009
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest009, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetPendingSizeStatus()).WillOnce(::testing::Return(false));
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: WindowDragTest010
 * @tc.desc: Test WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, WindowDragTest010, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    auto delegateMock =
        AceType::MakeRefPtr<WebDelegateMock>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());

    webPattern->delegate_ = delegateMock;
    EXPECT_NE(webPattern->delegate_, nullptr);
    EXPECT_CALL(*delegateMock, GetPendingSizeStatus()).WillOnce(::testing::Return(true));
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG_START);
    webPattern->WindowDrag(0, 0);
}

/**
 * @tc.name: GetSelectPopupPostionTest001
 * @tc.desc: GetSelectPopupPostion.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, GetSelectPopupPostionTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);

    webPattern->GetSelectPopupPostion(params->GetSelectMenuBound());
}

/**
 * @tc.name: GetSelectPopupPostionTest002
 * @tc.desc: GetSelectPopupPostion.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, GetSelectPopupPostionTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);

    webPattern->GetSelectPopupPostion(nullptr);
}

/**
 * @tc.name: UpdateOnFocusTextFieldTest001
 * @tc.desc: UpdateOnFocusTextField.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, UpdateOnFocusTextFieldTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    webPattern->UpdateOnFocusTextField(true);
}

/**
 * @tc.name: UpdateOnFocusTextFieldTest002
 * @tc.desc: UpdateOnFocusTextField.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, UpdateOnFocusTextFieldTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    webPattern->UpdateOnFocusTextField(false);
}

/**
 * @tc.name: OnBackPressedTest001
 * @tc.desc: OnBackPressed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    bool result = false;

    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    webPattern->delegate_ = nullptr;
    result = webPattern->OnBackPressed();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: OnBackPressedTest002
 * @tc.desc: OnBackPressed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    bool result = false;

    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    EXPECT_NE(webPattern->delegate_, nullptr);
    result = webPattern->OnBackPressed();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: OnBackPressedTest003
 * @tc.desc: OnBackPressed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    bool result = false;

    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_HIDE;
    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    EXPECT_NE(webPattern->delegate_, nullptr);
    result = webPattern->OnBackPressed();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnBackPressedForFullScreenTest001
 * @tc.desc: OnBackPressedForFullScreen.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedForFullScreenTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto handler = AceType::MakeRefPtr<FullScreenExitHandlerMock>();
    int videoNaturalWidth = 100;
    int videoNaturalHeight = 100;
    auto handlerMock = std::make_shared<FullScreenEnterEventMock>(handler, videoNaturalWidth, videoNaturalHeight);

    bool result = false;

    webPattern->isFullScreen_ = false;
    result = webPattern->OnBackPressedForFullScreen();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnBackPressedForFullScreenTest002
 * @tc.desc: OnBackPressedForFullScreen.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedForFullScreenTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto handler = AceType::MakeRefPtr<FullScreenExitHandlerMock>();
    int videoNaturalWidth = 100;
    int videoNaturalHeight = 100;
    auto handlerMock = std::make_shared<FullScreenEnterEventMock>(handler, videoNaturalWidth, videoNaturalHeight);

    bool result = false;

    webPattern->isFullScreen_ = true;
    webPattern->fullScreenExitHandler_ = nullptr;
    result = webPattern->OnBackPressedForFullScreen();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnBackPressedForFullScreenTest003
 * @tc.desc: OnBackPressedForFullScreen.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedForFullScreenTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto handler = AceType::MakeRefPtr<FullScreenExitHandlerMock>();
    int videoNaturalWidth = 100;
    int videoNaturalHeight = 100;
    auto handlerMock = std::make_shared<FullScreenEnterEventMock>(handler, videoNaturalWidth, videoNaturalHeight);

    bool result = false;

    webPattern->isFullScreen_ = true;
    webPattern->fullScreenExitHandler_ = handlerMock;
    webPattern->fullScreenExitHandler_->handler_ = nullptr;
    result = webPattern->OnBackPressedForFullScreen();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnBackPressedForFullScreenTest004
 * @tc.desc: OnBackPressedForFullScreen.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnBackPressedForFullScreenTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto handler = AceType::MakeRefPtr<FullScreenExitHandlerMock>();
    int videoNaturalWidth = 100;
    int videoNaturalHeight = 100;
    auto handlerMock = std::make_shared<FullScreenEnterEventMock>(handler, videoNaturalWidth, videoNaturalHeight);

    bool result = false;

    webPattern->isFullScreen_ = true;
    webPattern->fullScreenExitHandler_ = handlerMock;
    webPattern->fullScreenExitHandler_->handler_ = handler;
    result = webPattern->OnBackPressedForFullScreen();
    EXPECT_EQ(result, true);
}
} // namespace OHOS::Ace::NG