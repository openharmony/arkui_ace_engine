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
#include "test/mock/core/common/mock_image_analyzer_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/event/touch_event.h"
#undef private
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::NWeb {
class NWebDragDataMock : public NWebDragData {
public:
    std::string GetLinkURL() override
    {
        return "http://example.com";
    }

    std::string GetFragmentText() override
    {
        return "This is some text.";
    }

    std::string GetFragmentHtml() override
    {
        return "<html><body>This is some HTML.</body></html>";
    }

    bool GetPixelMapSetting(const void** data, size_t& len, int& width, int& height) override
    {
        *data = nullptr;
        len = 0;
        width = 0;
        height = 0;
        return false;
    }

    bool SetFragmentHtml(const std::string& html) override
    {
        // Do nothing or implement actual behavior
        return true;
    }

    bool SetPixelMapSetting(const void* data, size_t len, int width, int height) override
    {
        // Do nothing or implement actual behavior
        return true;
    }

    bool SetLinkURL(const std::string& url) override
    {
        // Do nothing or implement actual behavior
        return true;
    }

    bool SetFragmentText(const std::string& text) override
    {
        // Do nothing or implement actual behavior
        return true;
    }

    std::string GetLinkTitle() override
    {
        return "Example Title";
    }

    bool SetLinkTitle(const std::string& title) override
    {
        // Do nothing or implement actual behavior
        return true;
    }

    void GetDragStartPosition(int& x, int& y) override
    {
        x = 0;
        y = 0;
    }

    bool IsSingleImageContent() override
    {
        return false;
    }

    bool SetFileUri(const std::string& uri) override
    {
        // Do nothing or implement actual behavior
        return true;
    }

    std::string GetImageFileName() override
    {
        return "image.png";
    }

    void ClearImageFileNames() override
    {
        // Do nothing or implement actual behavior
    }
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

    void SetX(int32_t x)
    {
        x_ = x;
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
        return x_;
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
    int32_t x_ = 0;
    float edgeHeight_ = 0.0;
};
} // namespace OHOS::NWeb

namespace OHOS::Ace::NG {
class ScrollablePatternDummy : public ScrollablePattern {
public:
    ScrollablePatternDummy() = default;
    ~ScrollablePatternDummy() = default;
    bool IsReverse() const override
    {
        return false;
    }

    bool ShouldDelayChildPressedState() const override
    {
        return true;
    }

    bool UpdateCurrentOffset(float delta, int32_t source)
    {
        return false;
    }
    bool IsScrollable() const override
    {
        return false;
    }
    bool IsAtTop() const override
    {
        return false;
    }
    bool IsAtBottom(bool considerRepeat = false) const override
    {
        return false;
    }
    bool OutBoundaryCallback() override
    {
        return false;
    }

    bool IsOutOfBoundary(bool useCurrentDelta = true) override
    {
        return false;
    }

    void OnTouchDown(const TouchEventInfo& info) override {}

    bool OnScrollCallback(float offset, int32_t source) override
    {
        return false;
    }
    void OnScrollStartCallback() override {}
    void FireOnScrollStart(bool withPerfMonitor) override {}
    void FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart) override {}
    void FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd) override {}

    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override {}

    void UpdateScrollBarOffset() override {}

    OverScrollOffset GetOverScrollOffset(double delta) const override
    {
        return { 0, 0 };
    }

    void StopAnimate() override {}

    double GetTotalOffset() const override
    {
        return 0.0f;
    }
    float GetTotalHeight() const override
    {
        return 0.0f;
    }
    void OnAnimateStop() override {}
    void ScrollTo(float position) override {}
    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll = false,
        bool useTotalOffset = true) override
    {}
    bool CanOverScroll(int32_t source) override
    {
        return false;
    }

    std::optional<float> CalcPredictSnapOffset(
        float delta, float dragDistance, float velocity, SnapDirection snapDirection) override
    {
        std::optional<float> predictSnapPosition;
        return predictSnapPosition;
    }

    bool NeedScrollSnapToSide(float delta) override
    {
        return false;
    }

    float GetMainContentSize() const override
    {
        return 0.0f;
    }

    bool SupportScrollToIndex() const override
    {
        return true;
    }

    ScrollAlign GetDefaultScrollAlign() const override
    {
        return ScrollAlign::START;
    }

    void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::START,
        std::optional<float> extraOffset = std::nullopt) override
    {}

    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth) override {}

    ScrollEdgeType GetScrollEdgeType() const override
    {
        return ScrollEdgeType::SCROLL_NONE;
    }

    Rect GetItemRect(int32_t index) const override
    {
        return Rect();
    };

    int32_t GetItemIndex(double x, double y) const override
    {
        return -1;
    }

    bool IsScrollSnap() override
    {
        return false;
    }

    std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems() override
    {
        std::vector<RefPtr<FrameNode>> children;
        return children;
    }

    void InitScrollBarClickEvent() override {}

    void ScrollPage(bool reverse, bool smooth = false,
        AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL) override
    {}

    ScrollOffsetAbility GetScrollOffsetAbility() override
    {
        return { nullptr, Axis::NONE };
    }

    std::function<bool(int32_t)> GetScrollIndexAbility() override
    {
        return nullptr;
    }

    void SetAccessibilityAction() override {}

    void OnAttachToMainTree() override {}

protected:
    DisplayMode GetDefaultScrollBarDisplayMode() const override
    {
        return DisplayMode::AUTO;
    }

    void FireOnScroll(float finalOffset, OnScrollEvent& onScroll) const override {}

    void OnScrollStop(const OnScrollStopEvent& onScrollStop, const OnScrollStopEvent& onJSFrameNodeScrollStop) override
    {}

private:
    void OnScrollEndCallback() override {};

    void MultiSelectWithoutKeyboard(const RectF& selectedZone) override {}
    void ClearMultiSelect() override {}
    bool IsItemSelected(float xOffset, float yOffset)
    {
        return false;
    }
    float GetOffsetWithLimit(float offset) const override
    {
        return 0.0f;
    }
};

class WebPatternFocusTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternFocusTestNg::SetUpTestCase() {}
void WebPatternFocusTestNg::TearDownTestCase() {}
void WebPatternFocusTestNg::SetUp() {}
void WebPatternFocusTestNg::TearDown() {}

/**
 * @tc.name: OnTextSelected_001
 * @tc.desc: OnTextSelected.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnTextSelected_001, TestSize.Level1)
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
    webPattern->overlayCreating_ = false;
    webPattern->awaitingOnTextSelected_ = true;
    webPattern->OnTextSelected();
    ASSERT_NE(webPattern->delegate_, nullptr);
    EXPECT_TRUE(webPattern->overlayCreating_);
    EXPECT_FALSE(webPattern->awaitingOnTextSelected_);
#endif
}

/**
 * @tc.name: DestroyAnalyzerOverlay_001
 * @tc.desc: DestroyAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, DestroyAnalyzerOverlay_001, TestSize.Level1)
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
    webPattern->DestroyAnalyzerOverlay();
    ASSERT_EQ(webPattern->imageAnalyzerManager_, nullptr);
#endif
}

/**
 * @tc.name: DestroyAnalyzerOverlay_002
 * @tc.desc: DestroyAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, DestroyAnalyzerOverlay_002, TestSize.Level1)
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
    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::WEB);
    webPattern->imageAnalyzerManager_ = imageAnalyzerManager;
    imageAnalyzerManager->SetOverlayCreated(true);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->DestroyAnalyzerOverlay();
    EXPECT_FALSE(webPattern->overlayCreating_);
#endif
}

/**
 * @tc.name: DestroyAnalyzerOverlay_003
 * @tc.desc: DestroyAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, DestroyAnalyzerOverlay_003, TestSize.Level1)
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
    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::WEB);
    webPattern->imageAnalyzerManager_ = imageAnalyzerManager;
    imageAnalyzerManager->SetOverlayCreated(false);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->DestroyAnalyzerOverlay();
    EXPECT_FALSE(webPattern->overlayCreating_);
#endif
}

/**
 * @tc.name: OnAccessibilityHoverEvent1
 * @tc.desc: OnAccessibilityHoverEvent1.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnAccessibilityHoverEvent, TestSize.Level1)
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
    SourceType sourceType = SourceType::NONE;
    AccessibilityHoverEventType eventType = AccessibilityHoverEventType::MOVE;
    TimeStamp time;
    auto result = webPattern->GetWebAccessibilityIdBySurfaceId("hoverSurfaceId");
    ASSERT_EQ(result, -1);

    const NG::PointF point(20, 100);
    webPattern->OnAccessibilityHoverEvent(point, sourceType, eventType, time);
    result = webPattern->GetWebAccessibilityIdBySurfaceId("hoverSurfaceId");
    ASSERT_NE(result, -1);
#endif
}

/**
 * @tc.name: OnAccessibilityHoverEvent2
 * @tc.desc: OnAccessibilityHoverEvent2.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnAccessibilityHoverEvent2, TestSize.Level1)
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
    SourceType sourceType = SourceType::NONE;
    AccessibilityHoverEventType eventType = AccessibilityHoverEventType::MOVE;
    TimeStamp time;
    auto result = webPattern->GetWebAccessibilityIdBySurfaceId("hoverSurfaceId");
    ASSERT_NE(result, -1);

    const NG::PointF point(-1, -1);
    webPattern->OnAccessibilityHoverEvent(point, sourceType, eventType, time);
    result = webPattern->GetWebAccessibilityIdBySurfaceId("hoverSurfaceId");
    ASSERT_EQ(result, -1);
#endif
}

/**
 * @tc.name: GetSurfaceIdByHtmlElementId001
 * @tc.desc: GetSurfaceIdByHtmlElementId delegate_ is null
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, GetSurfaceIdByHtmlElementId001, TestSize.Level1)
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
    ASSERT_EQ(webPattern->delegate_, nullptr);

    std::string htmlElementId = "testElementId";
    std::string result = webPattern->GetSurfaceIdByHtmlElementId(htmlElementId);
    ASSERT_EQ(result, "");
#endif
}

/**
 * @tc.name: GetSurfaceIdByHtmlElementId002
 * @tc.desc: GetSurfaceIdByHtmlElementId delegate_ is not null
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, GetSurfaceIdByHtmlElementId002, TestSize.Level1)
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

    std::string result1 = webPattern->GetSurfaceIdByHtmlElementId("existhtmlElementId");
    ASSERT_EQ(result1, "existSurfaceId");
    std::string result2 = webPattern->GetSurfaceIdByHtmlElementId("existhtmlElementIdOther");
    ASSERT_EQ(result2, "existSurfaceIdOther");
    std::string result3 = webPattern->GetSurfaceIdByHtmlElementId("noExisthtmlElementId");
    ASSERT_EQ(result3, "");
#endif
}

/**
 * @tc.name: GetWebAccessibilityIdBySurfaceId001
 * @tc.desc: GetWebAccessibilityIdBySurfaceId delegate_ is null
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, GetWebAccessibilityIdBySurfaceId001, TestSize.Level1)
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
    ASSERT_EQ(webPattern->delegate_, nullptr);

    std::string surfaceId = "testSurfaceId";
    auto result = webPattern->GetWebAccessibilityIdBySurfaceId(surfaceId);
    ASSERT_EQ(result, -1);
#endif
}

/**
 * @tc.name: GetWebAccessibilityIdBySurfaceId002
 * @tc.desc: GetWebAccessibilityIdBySurfaceId delegate_ is not null
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, GetWebAccessibilityIdBySurfaceId002, TestSize.Level1)
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

    auto result1 = webPattern->GetWebAccessibilityIdBySurfaceId("existSurfaceId");
    ASSERT_EQ(result1, 123);
    auto result2 = webPattern->GetWebAccessibilityIdBySurfaceId("existSurfaceIdOther");
    ASSERT_EQ(result2, 456);
    auto result3 = webPattern->GetWebAccessibilityIdBySurfaceId("noexistSurfaceId");
    ASSERT_EQ(result3, -1);
#endif
}

/**
 * @tc.name: RegisterTextBlurCallback
 * @tc.desc: RegisterTextBlurCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, RegisterTextBlurCallback, TestSize.Level1)
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

    WebPattern::TextBlurCallback callback = [](int64_t id, const std::string& data) {};
    webPattern->RegisterTextBlurCallback(std::move(callback));
    EXPECT_TRUE(webPattern->textBlurAccessibilityEnable_);
#endif
}

/**
 * @tc.name: UnRegisterTextBlurCallback
 * @tc.desc: UnRegisterTextBlurCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, UnRegisterTextBlurCallback, TestSize.Level1)
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
    webPattern->UnRegisterTextBlurCallback();
    EXPECT_FALSE(webPattern->textBlurAccessibilityEnable_);
#endif
}

/**
 * @tc.name: InitializeAccessibility_001
 * @tc.desc: InitializeAccessibility.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, InitializeAccessibility_001, TestSize.Level1)
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
    webPattern->instanceId_ = 1;
    OHOS::Ace::SetBoolStatus(true);
    webPattern->InitializeAccessibility();
    webPattern->InitializeAccessibility();
    webPattern->UninitializeAccessibility();
    OHOS::Ace::SetBoolStatus(false);
    webPattern->InitializeAccessibility();
    webPattern->UninitializeAccessibility();
    ASSERT_EQ(webPattern->accessibilityChildTreeCallback_[webPattern->instanceId_], nullptr);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnSetAccessibilityChildTree_001
 * @tc.desc: OnSetAccessibilityChildTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnSetAccessibilityChildTree_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    frameNode->accessibilityProperty_ = nullptr;
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnSetAccessibilityChildTree(33, 33);
    EXPECT_EQ(frameNode->accessibilityProperty_, nullptr);
#endif
}

/**
 * @tc.name: OnSetAccessibilityChildTree_002
 * @tc.desc: OnSetAccessibilityChildTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnSetAccessibilityChildTree_002, TestSize.Level1)
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
    webPattern->OnSetAccessibilityChildTree(33, 33);
    EXPECT_EQ(frameNode->accessibilityProperty_->GetChildTreeId(), 33);
#endif
}
/**
 * @tc.name: OnAccessibilityChildTreeRegister
 * @tc.desc: OnAccessibilityChildTreeRegister.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnAccessibilityChildTreeRegister, TestSize.Level1)
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
    ASSERT_FALSE(webPattern->OnAccessibilityChildTreeRegister());
#endif
}

/**
 * @tc.name: OnAccessibilityChildTreeDeregister
 * @tc.desc: OnAccessibilityChildTreeDeregister.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, OnAccessibilityChildTreeDeregister, TestSize.Level1)
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
    ASSERT_FALSE(webPattern->OnAccessibilityChildTreeDeregister());
#endif
}

/**
 * @tc.name: ClearDragData_001
 * @tc.desc: ClearDragData.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ClearDragData_001, TestSize.Level1)
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
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    webPattern->ClearDragData();
#endif
}

/**
 * @tc.name: ClearDragData_002
 * @tc.desc: ClearDragData.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ClearDragData_002, TestSize.Level1)
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
    webPattern->ClearDragData();
#endif
}

/**
 * @tc.name: ClearDragData_003
 * @tc.desc: ClearDragData.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ClearDragData_003, TestSize.Level1)
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
    EXPECT_EQ(webPattern->delegate_, nullptr);
    webPattern->ClearDragData();
#endif
}

/**
 * @tc.name: InitFocusEvent_001
 * @tc.desc: InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, InitFocusEvent_001, TestSize.Level1)
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
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    EXPECT_NE(focusHub, nullptr);
#endif
}

/**
 * @tc.name: HandleBlurEvent_001
 * @tc.desc: HandleBlurEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleBlurEvent_001, TestSize.Level1)
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
    webPattern->isReceivedArkDrag_ = true;
    webPattern->HandleBlurEvent(BlurReason::FOCUS_SWITCH);
#endif
}

/**
 * @tc.name: HandleBlurEvent_002
 * @tc.desc: HandleBlurEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleBlurEvent_002, TestSize.Level1)
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
    webPattern->HandleBlurEvent(BlurReason::FOCUS_SWITCH);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: HandleKeyEvent_001
 * @tc.desc: HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleKeyEvent_001, TestSize.Level1)
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
    KeyEvent keyEvent;
    EXPECT_FALSE(webPattern->HandleKeyEvent(keyEvent));
#endif
}

/**
 * @tc.name: ClearKeyEventByKeyCode_001
 * @tc.desc: ClearKeyEventByKeyCode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ClearKeyEventByKeyCode_001, TestSize.Level1)
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
    int32_t keyCode = 1;
    webPattern->ClearKeyEventByKeyCode(keyCode);
#endif
}

/**
 * @tc.name: ClearKeyEventByKeyCode_002
 * @tc.desc: ClearKeyEventByKeyCode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ClearKeyEventByKeyCode_002, TestSize.Level1)
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
    KeyEvent keyEvent;
    for (int i = 0; i <= 1001; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    int32_t keyCode = 1;
    webPattern->ClearKeyEventByKeyCode(keyCode);
#endif
}

/**
 * @tc.name: WebOnKeyEvent_001
 * @tc.desc: WebOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, WebOnKeyEvent_001, TestSize.Level1)
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
    KeyEvent keyEvent;
    webPattern->WebOnKeyEvent(keyEvent);
#endif
}

/**
 * @tc.name: WebOnKeyEvent_002
 * @tc.desc: WebOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, WebOnKeyEvent_002, TestSize.Level1)
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
    KeyEvent keyEvent;
    ASSERT_NE(webPattern->delegate_, nullptr);
    for (int i = 0; i <= 1001; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    webPattern->WebOnKeyEvent(keyEvent);
#endif
}

/**
 * @tc.name: BeforeSyncGeometryProperties_001
 * @tc.desc: BeforeSyncGeometryProperties.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, BeforeSyncGeometryProperties_001, TestSize.Level1)
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
    DirtySwapConfig dirtySwapConfig;
    webPattern->BeforeSyncGeometryProperties(dirtySwapConfig);
#endif
}

/**
 * @tc.name: BeforeSyncGeometryProperties_002
 * @tc.desc: BeforeSyncGeometryProperties.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, BeforeSyncGeometryProperties_002, TestSize.Level1)
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
    webPattern->isInWindowDrag_ = true;
    DirtySwapConfig dirtySwapConfig;
    webPattern->BeforeSyncGeometryProperties(dirtySwapConfig);
#endif
}

/**
 * @tc.name: UpdateLayoutAfterKeyboardShow_001
 * @tc.desc: UpdateLayoutAfterKeyboardShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, UpdateLayoutAfterKeyboardShow_001, TestSize.Level1)
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
    webPattern->UpdateLayoutAfterKeyboardShow(500, 500, 20.2, 250.0);
    ASSERT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: UpdateLayoutAfterKeyboardShow_002
 * @tc.desc: UpdateLayoutAfterKeyboardShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, UpdateLayoutAfterKeyboardShow_002, TestSize.Level1)
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
    webPattern->keyBoardAvoidMode_ = WebKeyboardAvoidMode::RESIZE_VISUAL;
    webPattern->UpdateLayoutAfterKeyboardShow(500, 500, 20.2, 250.0);
    ASSERT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: UpdateLayoutAfterKeyboardShow_003
 * @tc.desc: UpdateLayoutAfterKeyboardShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, UpdateLayoutAfterKeyboardShow_003, TestSize.Level1)
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
    webPattern->keyBoardAvoidMode_ = WebKeyboardAvoidMode::OVERLAYS_CONTENT;
    webPattern->UpdateLayoutAfterKeyboardShow(500, 500, 20.2, 250.0);
    ASSERT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleTouchDownTest001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchDownTest001, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->HandleTouchDown(event, true);
#endif
}

/**
 * @tc.name: HandleTouchDownTest002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchDownTest002, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->overlayCreating_ = true;
    event.AddTouchLocationInfo(std::move(info));
    webPattern->HandleTouchDown(event, true);
#endif
}

/**
 * @tc.name: HandleTouchUpTest001
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchUpTest001, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->HandleTouchUp(event, true);
#endif
}

/**
 * @tc.name: HandleTouchUpTest002
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchUpTest002, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->isReceivedArkDrag_ = true;
    webPattern->overlayCreating_ = true;
    event.AddTouchLocationInfo(std::move(info));
    webPattern->HandleTouchUp(event, true);
#endif
}

/**
 * @tc.name: HandleTouchMoveTest001
 * @tc.desc: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchMoveTest001, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->HandleTouchMove(event, true);
#endif
}

/**
 * @tc.name: HandleTouchMoveTest002
 * @tc.desc: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchMoveTest002, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->isReceivedArkDrag_ = true;
    event.AddTouchLocationInfo(std::move(info));
    webPattern->HandleTouchMove(event, true);
#endif
}

/**
 * @tc.name: HandleTouchMoveTest003
 * @tc.desc: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchMoveTest003, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->isReceivedArkDrag_ = true;
    event.AddTouchLocationInfo(std::move(info));
    webPattern->overlayCreating_ = true;
    webPattern->HandleTouchMove(event, true);
#endif
}

/**
 * @tc.name: HandleTouchMoveTest004
 * @tc.desc: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchMoveTest004, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->isReceivedArkDrag_ = true;
    event.AddTouchLocationInfo(std::move(info));
    webPattern->overlayCreating_ = true;
    webPattern->isDragging_ = true;
    webPattern->HandleTouchMove(event, true);
#endif
}

/**
 * @tc.name: HandleTouchCancelTest001
 * @tc.desc: HandleTouchCancel
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchCancelTest001, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    webPattern->HandleTouchCancel(event);
#endif
}

/**
 * @tc.name: HandleTouchCancelTest002
 * @tc.desc: HandleTouchCancel
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, HandleTouchCancelTest002, TestSize.Level1)
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

    int32_t fingerId = 0;
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    event.AddTouchLocationInfo(std::move(info));
    webPattern->overlayCreating_ = true;
    webPattern->HandleTouchCancel(event);
#endif
}

/**
 * @tc.name: ParseTouchInfoTest001
 * @tc.desc: ParseTouchInfo
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ParseTouchInfoTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    TouchEventInfo info("touch");
    info.changedTouches_.clear();
    std::list<OHOS::Ace::NG::WebPattern::TouchInfo> touchInfos;
    EXPECT_FALSE(g_webPattern->ParseTouchInfo(info, touchInfos));
#endif
}

/**
 * @tc.name: RequestFullScreenTest
 * @tc.desc: RequestFullScreen
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, RequestFullScreenTest, TestSize.Level1)
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
    webPattern->RequestFullScreen();
    EXPECT_EQ(webPattern->isFullScreen_, true);
#endif
}

/**
 * @tc.name: ExitFullScreenTest
 * @tc.desc: ExitFullScreen
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, ExitFullScreenTest, TestSize.Level1)
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
    webPattern->ExitFullScreen();
    EXPECT_EQ(webPattern->isFullScreen_, false);
#endif
}

/**
 * @tc.name: GetCoordinatePointTest001
 * @tc.desc: GetCoordinatePoint
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, GetCoordinatePointTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto coordinatePoint = webPattern->GetCoordinatePoint();
    EXPECT_NE(coordinatePoint, std::nullopt);
#endif
}

/**
 * @tc.name: GetCoordinatePointTest002
 * @tc.desc: GetCoordinatePoint
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, GetCoordinatePointTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    host->GetGeometryNode()->SetFrameOffset(OffsetF(0, 0));

    auto coordinatePoint = webPattern->GetCoordinatePoint();
    EXPECT_NE(coordinatePoint, std::nullopt);
    EXPECT_FLOAT_EQ(coordinatePoint->GetX(), 0);
    EXPECT_FLOAT_EQ(coordinatePoint->GetY(), 0);
#endif
}

/**
 * @tc.name: DelTouchOverlayInfoByTouchIdTest001
 * @tc.desc: DelTouchOverlayInfoByTouchId
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, DelTouchOverlayInfoByTouchIdTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    webPattern->touchOverlayInfo_.push_back(WebPattern::TouchInfo { 1, 10.0, 1 });
    webPattern->touchOverlayInfo_.push_back(WebPattern::TouchInfo { 2, 30.0, 2 });
    webPattern->touchOverlayInfo_.push_back(WebPattern::TouchInfo { 3, 50.0, 3 });

    webPattern->DelTouchOverlayInfoByTouchId(2);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 2);
    webPattern->DelTouchOverlayInfoByTouchId(4);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 2);
#endif
}

/**
 * @tc.name: DelTouchOverlayInfoByTouchIdTest002
 * @tc.desc: DelTouchOverlayInfoByTouchId
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternFocusTestNg, DelTouchOverlayInfoByTouchIdTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    webPattern->touchOverlayInfo_.push_back(WebPattern::TouchInfo { 3, 50.0, 3 });
    webPattern->touchOverlayInfo_.push_back(WebPattern::TouchInfo { 4, 70.0, 4 });
    webPattern->touchOverlayInfo_.push_back(WebPattern::TouchInfo { 5, 90.0, 5 });
    webPattern->DelTouchOverlayInfoByTouchId(3);
    webPattern->DelTouchOverlayInfoByTouchId(4);
    webPattern->DelTouchOverlayInfoByTouchId(5);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 0);
#endif
}
} // namespace OHOS::Ace::NG
