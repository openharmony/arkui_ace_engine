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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "test/mock/base/mock_mouse_style.h"

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
} // namespace OHOS::Ace::NG
