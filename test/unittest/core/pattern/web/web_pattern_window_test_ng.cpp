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

#include "base/memory/ace_type.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/web/web_pattern.h"
#undef protected
#undef private
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

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

class MockTaskExecutorTest : public Ace::TaskExecutor {
public:
    MockTaskExecutorTest() = default;
    explicit MockTaskExecutorTest(bool delayRun) : delayRun_(delayRun) {}

    bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        Ace::PriorityType priorityType = Ace::PriorityType::LOW) const override
    {
        CHECK_NULL_RETURN(task, false);
        if (delayRun_) {
            return true;
        }
        return true;
    }

    bool WillRunOnCurrentThread(TaskType type) const override
    {
        return true;
    }

    Task WrapTaskWithTraceId(Task&& /*task*/, int32_t /*id*/) const override
    {
        return nullptr;
    }

    void AddTaskObserver(Task&& callback) override {}

    void RemoveTaskObserver() override {}

    void RemoveTask(TaskType type, const std::string& name) override {}

    bool OnPostTaskWithoutTraceId(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        Ace::PriorityType priorityType = Ace::PriorityType::LOW) const override
    {
        CHECK_NULL_RETURN(task, false);
        if (delayRun_) {
            return true;
        }
        task();
        return true;
    }

private:
    bool delayRun_ = false;
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

class WebDelegateDummy : public OHOS::Ace::WebDelegate {
public:
    WebDelegateDummy(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebDelegate(context, std::move(onError), type, id)
    {}
    bool GetIsSmoothDragResizeEnabled()
    {
        return false;
    };
    bool GetPendingSizeStatus()
    {
        return false;
    };
};

class WebDelegateTrueDummy : public OHOS::Ace::WebDelegate {
public:
    WebDelegateTrueDummy(
        const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebDelegate(context, std::move(onError), type, id)
    {}
    bool GetIsSmoothDragResizeEnabled()
    {
        return true;
    };
    bool GetPendingSizeStatus()
    {
        return true;
    };
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
    bool result = true;
    result = webPattern->ShowTimeDialog(chooserMock, suggestions, callbackMock);
    EXPECT_FALSE(result);
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
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>(), nullptr);
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
    webPattern->UpdateLocale();
    EXPECT_NE(webPattern->delegate_, nullptr);
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
    auto type = WindowSizeChangeReason::UNDEFINED;
    webPattern->OnWindowSizeChanged(0, 0, type);
    EXPECT_NE(type, WindowSizeChangeReason::DRAG_START);
    EXPECT_NE(type, WindowSizeChangeReason::DRAG);
    EXPECT_NE(type, WindowSizeChangeReason::DRAG_END);
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
    EXPECT_NE(webPattern->fullScreenExitHandler_, nullptr);
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
    bool result = true;
    result = webPattern->ShowDateTimeSuggestionDialog(chooserMock, suggestions, callbackMock);
    EXPECT_FALSE(result);
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
    EXPECT_TRUE(options.empty());
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
    double dipScale = 0;
    webPattern->InitSelectPopupMenuView(options, callback, params, dipScale);
    EXPECT_NE(params, nullptr);
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
    webPattern->delegate_ = nullptr;
    webPattern->WindowDrag(0, 0);
    EXPECT_EQ(webPattern->delegate_, nullptr);
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
    auto delegateMock = AceType::MakeRefPtr<WebDelegateDummy>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->delegate_ = delegateMock;
    webPattern->WindowDrag(0, 0);
    EXPECT_FALSE(webPattern->delegate_->GetIsSmoothDragResizeEnabled());
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
    auto delegateMock = AceType::MakeRefPtr<WebDelegateTrueDummy>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->delegate_ = delegateMock;
    webPattern->WindowDrag(0, 2);
    EXPECT_NE(webPattern->delegate_, nullptr);
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
    auto delegateMock = AceType::MakeRefPtr<WebDelegateTrueDummy>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    auto type = WindowSizeChangeReason::UNDEFINED;
    webPattern->OnWindowSizeChanged(0, 0, type);
    webPattern->delegate_ = delegateMock;
    webPattern->WindowDrag(2, 2);
    EXPECT_NE(type, WindowSizeChangeReason::DRAG_START);
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

    auto delegateMock = AceType::MakeRefPtr<WebDelegateDummy>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    auto type = WindowSizeChangeReason::DRAG_START;
    webPattern->delegate_ = delegateMock;
    webPattern->OnWindowSizeChanged(0, 0, type);
    webPattern->WindowDrag(0, 0);
    EXPECT_EQ(type, WindowSizeChangeReason::DRAG_START);
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
    EXPECT_EQ(params->GetSelectMenuBound(), nullptr);
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
    bool ret = true;
    webPattern->UpdateOnFocusTextField(ret);
    EXPECT_TRUE(ret);
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
    EXPECT_TRUE(result);
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
    EXPECT_TRUE(result);
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
    EXPECT_FALSE(result);
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
    EXPECT_FALSE(result);
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
    EXPECT_FALSE(result);
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
    EXPECT_FALSE(result);
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
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InitTouchEventListener_001
 * @tc.desc: InitTouchEventListener
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, InitTouchEventListener_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    webPattern->InitTouchEventListener();
    MockPipelineContext::TearDown();
    ASSERT_NE(webPattern->touchEventListener_, nullptr);
#endif
}

/**
 * @tc.name: UninitTouchEventListener_001
 * @tc.desc: UninitTouchEventListener
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, UninitTouchEventListener_001, TestSize.Level1)
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
    auto touch = std::make_shared<TouchEventListener>();
    webPattern->touchEventListener_ = touch;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    webPattern->UninitTouchEventListener();
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->touchEventListener_, nullptr);
#endif
}

/**
 * @tc.name: ShowDateTimeDialog_001
 * @tc.desc: ShowDateTimeDialog
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowDateTimeDialog_001, TestSize.Level1)
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
    std::shared_ptr<NWebDateTimeChooserMock> chooser = std::make_shared<NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.clear();
    ASSERT_EQ(suggestions.size(), 0);
    EXPECT_CALL(*chooser, GetHasSelected).WillRepeatedly(Return(true));
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    MockContainer::Current()->pipelineContext_->SetupRootElement();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    RefPtr<DialogTheme> expectedTheme = AccessibilityManager::MakeRefPtr<DialogTheme>();
    MockPipelineContext::GetCurrent()->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(::testing::_)).WillRepeatedly(Return(expectedTheme));
    bool result = false;
    result = webPattern->ShowDateTimeDialog(chooser, suggestions, callback);
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: ShowDateTimeSuggestionDialogTest003
 * @tc.desc: Test ShowDateTimeSuggestionDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowDateTimeSuggestionDialogTest003, TestSize.Level1)
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
    std::shared_ptr<NWebDateTimeChooserMock> chooser = std::make_shared<NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.clear();
    ASSERT_EQ(suggestions.size(), 0);
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    MockContainer::Current()->pipelineContext_->SetupRootElement();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    RefPtr<DialogTheme> expectedTheme = AccessibilityManager::MakeRefPtr<DialogTheme>();
    MockPipelineContext::GetCurrent()->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(::testing::_)).WillRepeatedly(Return(expectedTheme));
    bool result = false;
    result = webPattern->ShowDateTimeSuggestionDialog(chooser, suggestions, callback);
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: ShowDateTimeSuggestionDialogTest004
 * @tc.desc: Test ShowDateTimeSuggestionDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, ShowDateTimeSuggestionDialogTest004, TestSize.Level1)
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
    std::shared_ptr<NWebDateTimeChooserMock> chooser = std::make_shared<NWebDateTimeChooserMock>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackMock>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    MockContainer::Current()->pipelineContext_->SetupRootElement();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    RefPtr<DialogTheme> expectedTheme = AccessibilityManager::MakeRefPtr<DialogTheme>();
    MockPipelineContext::GetCurrent()->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(::testing::_)).WillRepeatedly(Return(expectedTheme));
    bool result = false;
    result = webPattern->ShowDateTimeSuggestionDialog(chooser, suggestions, callback);
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: OnWindowHide
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, OnWindowHide001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->isWindowShow_ = true;
    webPattern->isVisible_ = false;
    webPattern->OnWindowHide();
    EXPECT_FALSE(webPattern->isVisible_);
#endif
}

/**
 * @tc.name: CalculateTooltipOffset_001
 * @tc.desc: CalculateTooltipOffset
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, CalculateTooltipOffset_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->rootWidth_ = 0;
    pipeline->rootHeight_ = 0;
    webPattern->CalculateTooltipOffset(tooltipNode, *tooltipOffset);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: InitRotationEventCallback_001
 * @tc.desc: InitRotationEventCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, InitRotationEventCallback_001, TestSize.Level1)
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
    webPattern->rotationEndCallbackId_ = 0;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    webPattern->InitRotationEventCallback();
    MockPipelineContext::TearDown();
    ASSERT_NE(webPattern->rotationEndCallbackId_, 0);
#endif
}

/**
 * @tc.name: AdjustRotationRenderFitTest001
 * @tc.desc: Test AdjustRotationRenderFit.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, AdjustRotationRenderFitTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto type = WindowSizeChangeReason::UNDEFINED;
    webPattern->AdjustRotationRenderFit(type);
    type = WindowSizeChangeReason::ROTATION;
    webPattern->AdjustRotationRenderFit(type);
    webPattern->isAttachedToMainTree_ = true;
    webPattern->isVisible_ = false;
    webPattern->AdjustRotationRenderFit(type);
    webPattern->isVisible_ = true;
    webPattern->delegate_ = nullptr;
    webPattern->AdjustRotationRenderFit(type);
    EXPECT_EQ(webPattern->rotationEndCallbackId_, 0);
#endif
}

/**
 * @tc.name: UninitRotationEventCallback_001
 * @tc.desc: UninitRotationEventCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWindowTestNg, UninitRotationEventCallback_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    webPattern->UninitRotationEventCallback();
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->rotationEndCallbackId_, 0);
#endif
}
} // namespace OHOS::Ace::NG