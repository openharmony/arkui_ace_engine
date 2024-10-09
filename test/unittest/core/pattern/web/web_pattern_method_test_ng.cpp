/*
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
#include "frameworks/core/event/touch_event.h"
#undef private

#define protected public
#include "core/components_ng/gestures/gesture_info.h"
#define private public
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#undef private
#undef protected
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_image_analyzer_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/web/webview/ohos_nweb/include/nweb_handler.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/core/components_ng/event/touch_event.h"
#undef private

#include "test/mock/base/mock_mouse_style.h"
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t RESERVED_DEVICEID = 0xAAAAAAFF;
constexpr int32_t BUFFER_SIZE = 100;
constexpr int32_t WIDTH_VALUE = 10.0;
constexpr int32_t HEIGHT_VALUE = 20.0;
constexpr float EDGE_HEIGHT = 30.0;
} // namespace

namespace OHOS::Ace::NG {
class NWebCursorInfoTestImpl : public OHOS::NWeb::NWebCursorInfo {
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
        return buffer_;
    }

    float GetScale() override
    {
        return 1;
    }

    int32_t GetWidth() override
    {
        return WIDTH_VALUE;
    }

    int32_t GetHeight() override
    {
        return HEIGHT_VALUE;
    }

private:
    uint8_t buffer_[BUFFER_SIZE];
};

class NWebTouchHandleStateTestImpl : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateTestImpl() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return 0.0;
    };
};

class NWebTouchHandleStateEndTestImpl : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateEndTestImpl() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_END_HANDLE;
    };
    bool IsEnable() override
    {
        return true;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight_;
    };

private:
    float edgeHeight_ = EDGE_HEIGHT;
};

class NWebTouchHandleStateBeginTestImpl : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateBeginTestImpl() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight_;
    };

private:
    float edgeHeight_ = EDGE_HEIGHT;
};

class WebPatternMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternMethodTestNg::SetUpTestCase() {}
void WebPatternMethodTestNg::TearDownTestCase() {}
void WebPatternMethodTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void WebPatternMethodTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CloseAutoFillPopup_001
 * @tc.desc: CloseAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, CloseAutoFillPopup_001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    MockPipelineContext::GetCurrent()->SetInstanceId(1);
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    auto result = webPattern->CloseAutoFillPopup();
    MockContainer::TearDown();
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: CloseAutoFillPopup_002
 * @tc.desc: CloseAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, CloseAutoFillPopup_002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    MockContainer::SetUp();
    MockPipelineContext::GetCurrent()->SetInstanceId(1);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    MockContainer::TearDown();
    auto result = webPattern->CloseAutoFillPopup();
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_001
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, UpdateSelectHandleInfo_001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->isCurrentStartHandleDragging_ = true;
    webPattern->UpdateSelectHandleInfo();
    EXPECT_FALSE(webPattern->IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_002
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, UpdateSelectHandleInfo_002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->isCurrentStartHandleDragging_ = false;
    webPattern->UpdateSelectHandleInfo();
    EXPECT_TRUE(webPattern->IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_003
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, UpdateSelectHandleInfo_003, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->isCurrentStartHandleDragging_ = true;
    webPattern->UpdateSelectHandleInfo();
    EXPECT_TRUE(webPattern->IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_001
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTouchSelectionChangedTest_001, TestSize.Level1)
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
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    webPattern->selectTemporarilyHidden_ = true;
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_002
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTouchSelectionChangedTest_002, TestSize.Level1)
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
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    webPattern->selectTemporarilyHidden_ = true;
    webPattern->selectTemporarilyHiddenByScroll_ = false;
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_003
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTouchSelectionChangedTest_003, TestSize.Level1)
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
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    webPattern->selectTemporarilyHidden_ = false;
    webPattern->selectTemporarilyHiddenByScroll_ = true;
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_004
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTouchSelectionChangedTest_004, TestSize.Level1)
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
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    webPattern->selectTemporarilyHidden_ = false;
    webPattern->selectTemporarilyHiddenByScroll_ = false;
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_005
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTouchSelectionChangedTest_005, TestSize.Level1)
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
    auto insertHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    webPattern->selectTemporarilyHidden_ = false;
    webPattern->selectTemporarilyHiddenByScroll_ = false;
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    webPattern->selectOverlayDragging_ = false;
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_006
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTouchSelectionChangedTest_006, TestSize.Level1)
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
    auto insertHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    webPattern->selectTemporarilyHidden_ = false;
    webPattern->selectTemporarilyHiddenByScroll_ = false;
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    webPattern->selectOverlayDragging_ = true;
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_NE(webPattern->insertHandle_, nullptr);
    EXPECT_NE(webPattern->startSelectionHandle_, nullptr);
    EXPECT_NE(webPattern->endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnCursorChange_001
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_001, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    webPattern->mouseEventDeviceId_ = RESERVED_DEVICEID;
    webPattern->isHoverExit_ = true;
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_002
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_002, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    webPattern->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(-1));
    EXPECT_CALL(*mockMouseStyle, SetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(true));
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_003
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_003, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_CONTEXTMENU;
    webPattern->isHoverExit_ = true;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_004
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_004, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_ALIAS;
    webPattern->isHoverExit_ = false;
    ASSERT_FALSE(webPattern->isHoverExit_);
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_005
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_005, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_CUSTOM;
    webPattern->isHoverExit_ = true;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_006
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_006, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_ZOOMIN;
    webPattern->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_007
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnCursorChange_007, TestSize.Level1)
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
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_POINTER;
    webPattern->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = webPattern->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnTooltip_001
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_001, TestSize.Level1)
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
    webPattern->tooltipId_ = 1;
    std::string tooltip = "test";
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_002
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_002, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "";
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_003
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_003, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "";
    webPattern->mouseHoveredX_ = -1;
    webPattern->mouseHoveredY_ = 1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_004
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_004, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "";
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = -1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_005
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_005, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "";
    webPattern->mouseHoveredX_ = -1;
    webPattern->mouseHoveredY_ = -1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_006
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_006, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "test";
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = -1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_007
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_007, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "test";
    webPattern->mouseHoveredX_ = -1;
    webPattern->mouseHoveredY_ = 1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: OnTooltip_008
 * @tc.desc: OnTooltip
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, OnTooltip_008, TestSize.Level1)
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
    webPattern->tooltipId_ = -1;
    std::string tooltip = "test";
    webPattern->mouseHoveredX_ = -1;
    webPattern->mouseHoveredY_ = -1;
    webPattern->OnTooltip(tooltip);
    EXPECT_NE(webPattern->tooltipTimestamp_, -1);
#endif
}

/**
 * @tc.name: InitPanEvent_001
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
    GestureEvent event;
    webPattern->SetIsFixedNestedScrollMode(true);
    webPattern->parent_ = nullptr;
    gestureHub->panEventActuator_->panEvents_.back()->GetActionStartEventFunc()(event);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitPanEvent_002
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_002, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    gestureHub->panEventActuator_->panEvents_.clear();
    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
    GestureEvent event;
    gestureHub->panEventActuator_->panEvents_.back()->GetActionUpdateEventFunc()(event);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitPanEvent_003
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_003, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
    GestureEvent event;
    auto parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->SetNestedScrollParent(parent);
    EXPECT_CALL(*parent, OnScrollDragEndRecursive()).Times(1);
    gestureHub->panEventActuator_->panEvents_.back()->GetActionEndEventFunc()(event);
    webPattern->parent_ = nullptr;
    gestureHub->panEventActuator_->panEvents_.back()->GetActionEndEventFunc()(event);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitPanEvent_004
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_004, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureInfo2 = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo2 = nullptr;
    auto info = std::make_shared<BaseGestureEvent>();
    auto ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo2, info);
    EXPECT_EQ(ret, OHOS::Ace::GestureJudgeResult::CONTINUE);
#endif
}

/**
 * @tc.name: InitPanEvent_005
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_005, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureInfo2 = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo2->SetType(OHOS::Ace::GestureTypeName::UNKNOWN);
    auto info = std::make_shared<BaseGestureEvent>();
    auto ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo2, info);
    EXPECT_EQ(ret, OHOS::Ace::GestureJudgeResult::CONTINUE);
#endif
}

/**
 * @tc.name: InitPanEvent_006
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_006, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureInfo2 = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo2->SetType(OHOS::Ace::GestureTypeName::WEBSCROLL);
    gestureInfo2->SetInputEventType(OHOS::Ace::InputEventType::AXIS);
    auto info = std::make_shared<BaseGestureEvent>();
    auto ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo2, info);
    EXPECT_EQ(ret, OHOS::Ace::GestureJudgeResult::CONTINUE);
#endif
}

/**
 * @tc.name: InitPanEvent_007
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_007, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureInfo2 = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo2->SetType(OHOS::Ace::GestureTypeName::WEBSCROLL);
    gestureInfo2->SetInputEventType(OHOS::Ace::InputEventType::MOUSE_BUTTON);
    auto info = std::make_shared<BaseGestureEvent>();
    auto ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo2, info);
    EXPECT_EQ(ret, OHOS::Ace::GestureJudgeResult::REJECT);
#endif
}

/**
 * @tc.name: InitPanEvent_008
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_008, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureInfo2 = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo2->SetType(OHOS::Ace::GestureTypeName::WEBSCROLL);
    gestureInfo2->SetInputEventType(OHOS::Ace::InputEventType::TOUCH_PAD);
    auto info = std::make_shared<BaseGestureEvent>();
    auto ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo2, info);
    EXPECT_EQ(ret, OHOS::Ace::GestureJudgeResult::CONTINUE);
#endif
}

/**
 * @tc.name: InitPanEvent_009
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_009, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
    GestureEvent event;
    webPattern->SetIsFixedNestedScrollMode(true);
    auto parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->SetNestedScrollParent(parent);
    EXPECT_CALL(*parent, GetAxis()).Times(1);
    gestureHub->panEventActuator_->panEvents_.back()->GetActionStartEventFunc()(event);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitPanEvent_010
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_010, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
    GestureEvent event;
    webPattern->SetIsFixedNestedScrollMode(false);
    auto parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->SetNestedScrollParent(parent);
    gestureHub->panEventActuator_->panEvents_.back()->GetActionStartEventFunc()(event);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitPanEvent_011
 * @tc.desc: InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPanEvent_011, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    RefPtr<GestureEventHub> gestureHub2 = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    PanDirection direction;
    PanDirection direction2;
    direction.type = PanDirection::ALL;
    gestureHub->panEventActuator_ = AceType::MakeRefPtr<PanEventActuator>(gestureHub2, direction, 1, 0.1);
    auto panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction2, 2.0);
    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo = nullptr;
    gestureHub->panEventActuator_->panRecognizer_ = panRecognizer_;
    gestureHub->panEventActuator_->panRecognizer_->SetGestureInfo(gestureInfo);
    webPattern->panEvent_ = nullptr;

    webPattern->InitPanEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
    GestureEvent event;
    webPattern->SetIsFixedNestedScrollMode(false);
    webPattern->parent_ = nullptr;
    gestureHub->panEventActuator_->panEvents_.back()->GetActionStartEventFunc()(event);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitHoverEvent_001
 * @tc.desc: InitHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitHoverEvent_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    auto inputHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    webPattern->hoverEvent_ = nullptr;

    webPattern->InitHoverEvent(inputHub);
    EXPECT_NE(webPattern, nullptr);
    inputHub->hoverEventActuator_->inputEvents_.back()->GetOnHoverEventFunc()(true);
    inputHub->hoverEventActuator_->inputEvents_.back()->GetOnHoverEventFunc()(false);
#endif
}

/**
 * @tc.name: InitEvent_001
 * @tc.desc: InitEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitEvent_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    OHOS::Ace::SetReturnStatus("8");
    webPattern->InitEvent();
    OHOS::Ace::SetReturnStatus("");
    webPattern->InitEvent();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitPinchEvent_001
 * @tc.desc: InitPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPinchEvent_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    webPattern->pinchGesture_ = nullptr;

    webPattern->InitPinchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureEvent = std::make_shared<GestureEvent>();
    gestureEvent->SetSourceTool(SourceTool::TOUCHPAD);
    auto& gestureStartFunc = gestureHub->gestures_.back()->onActionStartId_;
    (*gestureStartFunc)(*gestureEvent);
    EXPECT_NE(gestureEvent, nullptr);

    auto gestureEvent2 = std::make_shared<GestureEvent>();
    gestureEvent2->SetSourceTool(SourceTool::TOUCHPAD);
    auto& gestureUpdateFunc = gestureHub->gestures_.back()->onActionUpdateId_;
    (*gestureUpdateFunc)(*gestureEvent2);
    EXPECT_NE(gestureEvent2, nullptr);
#endif
}

/**
 * @tc.name: InitPinchEvent_002
 * @tc.desc: InitPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitPinchEvent_002, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    webPattern->pinchGesture_ = nullptr;

    webPattern->InitPinchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto gestureEvent = std::make_shared<GestureEvent>();
    gestureEvent->SetSourceTool(SourceTool::UNKNOWN);
    auto& gestureStartFunc = gestureHub->gestures_.back()->onActionStartId_;
    (*gestureStartFunc)(*gestureEvent);
    EXPECT_NE(gestureEvent, nullptr);

    auto gestureEvent2 = std::make_shared<GestureEvent>();
    gestureEvent2->SetSourceTool(SourceTool::UNKNOWN);
    auto& gestureUpdateFunc = gestureHub->gestures_.back()->onActionUpdateId_;
    (*gestureUpdateFunc)(*gestureEvent2);
    EXPECT_NE(gestureEvent2, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_001
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    info->changedTouches_.clear();
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_002
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_002, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    info->changedTouches_.push_back(OHOS::Ace::TouchLocationInfo(1));
    info->SetSourceDevice(OHOS::Ace::SourceType::NONE);
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_003
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_003, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    auto touchInfo = std::make_shared<OHOS::Ace::TouchLocationInfo>(2);
    touchInfo->SetTouchType(TouchType::DOWN);
    info->changedTouches_.push_front(*touchInfo);
    info->SetSourceDevice(OHOS::Ace::SourceType::TOUCH);
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_004
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_004, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    auto touchInfo = std::make_shared<OHOS::Ace::TouchLocationInfo>(2);
    touchInfo->SetTouchType(TouchType::UP);
    info->changedTouches_.push_front(*touchInfo);
    info->SetSourceDevice(OHOS::Ace::SourceType::TOUCH);
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_005
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_005, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    auto touchInfo = std::make_shared<OHOS::Ace::TouchLocationInfo>(2);
    touchInfo->SetTouchType(TouchType::MOVE);
    info->changedTouches_.push_front(*touchInfo);
    info->SetSourceDevice(OHOS::Ace::SourceType::TOUCH);
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_006
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_006, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    auto touchInfo = std::make_shared<OHOS::Ace::TouchLocationInfo>(2);
    touchInfo->SetTouchType(TouchType::CANCEL);
    info->changedTouches_.push_front(*touchInfo);
    info->SetSourceDevice(OHOS::Ace::SourceType::TOUCH);
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_007
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, InitTouchEvent_007, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->touchEvent_ = nullptr;
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    gestureHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);

    auto info = std::make_shared<TouchEventInfo>(".");
    auto touchInfo = std::make_shared<OHOS::Ace::TouchLocationInfo>(2);
    touchInfo->SetTouchType(TouchType::PULL_DOWN);
    info->changedTouches_.push_front(*touchInfo);
    info->SetSourceDevice(OHOS::Ace::SourceType::TOUCH);
    gestureHub->touchEventActuator_->touchEvents_.back()->callback_(*info);
    EXPECT_NE(gestureHub, nullptr);
#endif
}

/**
 * @tc.name: StartVibraFeedback_001
 * @tc.desc: StartVibraFeedback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, StartVibraFeedback_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->isEnabledHapticFeedback_ = true;
    webPattern->StartVibraFeedback("");
    EXPECT_NE(webPattern, nullptr);

    webPattern->isEnabledHapticFeedback_ = false;
    webPattern->StartVibraFeedback("");
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: CloseImageOverlaySelection_001
 * @tc.desc: CloseImageOverlaySelection.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternMethodTestNg, CloseImageOverlaySelection_001, TestSize.Level1)
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
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->imageOverlayIsSelected_ = true;
    auto ret = webPattern->CloseImageOverlaySelection();
    EXPECT_EQ(ret, true);

    webPattern->imageOverlayIsSelected_ = false;
    ret = webPattern->CloseImageOverlaySelection();
    EXPECT_EQ(ret, false);
#endif
}
} // namespace OHOS::Ace::NG
