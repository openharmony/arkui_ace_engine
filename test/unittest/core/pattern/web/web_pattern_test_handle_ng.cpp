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
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "frameworks/core/pipeline/pipeline_base.h"
#undef protected
#undef private

#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t COUNTER_NUMBER_ZERO_HANDLE = 0;
constexpr int32_t COUNTER_NUMBER_OTHER_HANDLE = -1;
constexpr float COUNTER_NUMBER_ZERO_FLOAT_HANDLE = 0.0f;
constexpr int32_t COUNTER_NUMBER_TEN_HANDLE = 10;
} // namespace

namespace OHOS::Ace {
class UnifiedDataMock : public Ace::UnifiedData {
public:
    int64_t GetSize() override
    {
        return COUNTER_NUMBER_TEN_HANDLE;
    }
};

class UnifiedDataMockRe : public Ace::UnifiedData {
public:
    int64_t GetSize() override
    {
        return COUNTER_NUMBER_ZERO_HANDLE;
    }
};

class MockPixelMap : public Ace::PixelMap {
public:
    MOCK_METHOD(int32_t, GetWidth, (), (const, override));
    MOCK_METHOD(int32_t, GetHeight, (), (const, override));
    MOCK_METHOD(bool, GetPixelsVec, (std::vector<uint8_t> & data), (const, override));
    MOCK_METHOD(const uint8_t*, GetPixels, (), (const, override));
    MOCK_METHOD(PixelFormat, GetPixelFormat, (), (const, override));
    MOCK_METHOD(AlphaType, GetAlphaType, (), (const, override));
    MOCK_METHOD(int32_t, GetRowStride, (), (const, override));
    MOCK_METHOD(int32_t, GetRowBytes, (), (const, override));
    MOCK_METHOD(int32_t, GetByteCount, (), (const, override));
    MOCK_METHOD(void*, GetPixelManager, (), (const, override));
    MOCK_METHOD(void*, GetRawPixelMapPtr, (), (const, override));
    MOCK_METHOD(std::string, GetId, (), (override));
    MOCK_METHOD(std::string, GetModifyId, (), (override));
    MOCK_METHOD(std::shared_ptr<Media::PixelMap>, GetPixelMapSharedPtr, (), (override));
    MOCK_METHOD(void*, GetWritablePixels, (), (const, override));
    MOCK_METHOD(void, Scale, (float xAxis, float yAxis), (override));
    MOCK_METHOD(void, Scale, (float xAxis, float yAxis, const AceAntiAliasingOption& option), (override));
    MOCK_METHOD(void, SavePixelMapToFile, (const std::string& dst), (const, override));
    MOCK_METHOD(RefPtr<PixelMap>, GetCropPixelMap, (const Rect& srcRect), (override));
    MOCK_METHOD(bool, EncodeTlv, (std::vector<uint8_t> & buff), (override));
    MOCK_METHOD(AllocatorType, GetAllocatorType, (), (const override));
    MOCK_METHOD(bool, IsHdr, (), (const override));
    MOCK_METHOD(uint32_t, WritePixels, (const WritePixelsOptions& opts), (override));
    MOCK_METHOD(bool, GetIsWideColorGamut, (), (const override));
};

class WebDelegateDummy : public WebDelegate {
public:
    WebDelegateDummy(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebDelegate(context, std::move(onError), type, id)
    {}
    RefPtr<PixelMap> GetDragPixelMap()
    {
        auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
        return mockPixelMap;
    }
};
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class MockRecursiveLock : public RecursiveLock {
public:
    void Lock() override {}
    void Unlock() override {}
}; // namespace OHOS::Ace::NG

class MockLayoutWrapper : public LayoutWrapper {
public:
    MockLayoutWrapper(WeakPtr<FrameNode> hostNode) : LayoutWrapper(std::move(hostNode)), lock_() {}

    // Implement pure virtual functions from LayoutWrapper.
    const RefPtr<LayoutAlgorithmWrapper>& GetLayoutAlgorithm(bool needReset = false) override
    {
        static RefPtr<LayoutAlgorithmWrapper> algorithm;
        return algorithm;
    }

    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override {}

    void Layout() override {}

    int32_t GetTotalChildCount() const override
    {
        return COUNTER_NUMBER_ZERO_HANDLE;
    }

    const RefPtr<GeometryNode>& GetGeometryNode() const override
    {
        static RefPtr<GeometryNode> geometryNode;
        return geometryNode;
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const override
    {
        static RefPtr<LayoutProperty> layoutProperty;
        return layoutProperty;
    }

    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(
        uint32_t index, bool addToRenderTree = true, bool isCache = false) override
    {
        return nullptr;
    }

    RefPtr<LayoutWrapper> GetChildByIndex(uint32_t index, bool isCache = false) override
    {
        return nullptr;
    }

    ChildrenListWithGuard GetAllChildrenWithBuild(bool addToRenderTree = true) override
    {
        return ChildrenListWithGuard({}, lock_);
    }

    void RemoveChildInRenderTree(uint32_t index) override {}

    void RemoveAllChildInRenderTree() override {}

    void SetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart = COUNTER_NUMBER_ZERO_HANDLE,
        int32_t cacheEnd = COUNTER_NUMBER_ZERO_HANDLE, bool showCached = false) override
    {}

    void SetActiveChildRange(const std::optional<ActiveChildSets>& activeChildSets,
        const std::optional<ActiveChildRange>& activeChildRange = std::nullopt) override
    {}

    void SetActiveChildRange(const std::set<int32_t>& activeIndexes, const std::set<int32_t>& cachedIndexes) override {}

    void RecycleItemsByIndex(int32_t start, int32_t end) override {}

    void RecycleItemsByIndex(const std::set<int32_t>& indexes) override {}

    const std::string& GetHostTag() const override
    {
        static std::string tag = "";
        return tag;
    }

    bool IsActive() const override
    {
        return false;
    }

    void SetActive(bool active = true, bool needRebuildRenderContext = false) override {}

    bool CheckNeedForceMeasureAndLayout() override
    {
        return false;
    }

    float GetBaselineDistance() const override
    {
        return COUNTER_NUMBER_ZERO_FLOAT_HANDLE;
    }

    void SetCacheCount(int32_t cacheCount = COUNTER_NUMBER_ZERO_HANDLE,
        const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt) override
    {}

    bool SkipMeasureContent() const override
    {
        return false;
    }

    bool CheckShouldRunOnMain() override
    {
        return true;
    }

    bool IsOutOfLayout() const override
    {
        return false;
    }

    void BuildLazyItem() override {}

    void SetLongPredictTask() override {}

private:
    MockRecursiveLock lock_;
};
} // namespace OHOS::Ace::NG

namespace OHOS::NWeb {
class MockNWebKeyEvent : public NWebKeyEvent {
public:
    int32_t GetAction() override
    {
        return COUNTER_NUMBER_OTHER_HANDLE;
    }
    int32_t GetKeyCode() override
    {
        return COUNTER_NUMBER_OTHER_HANDLE;
    }
};

class MockNWebKeyEventFalse : public NWebKeyEvent {
public:
    int32_t GetAction() override
    {
        return COUNTER_NUMBER_TEN_HANDLE;
    }
    int32_t GetKeyCode() override
    {
        return COUNTER_NUMBER_TEN_HANDLE;
    }
};

class MockNWebKeyEventBe : public NWebKeyEvent {
public:
    int32_t GetAction() override
    {
        return COUNTER_NUMBER_OTHER_HANDLE;
    }
    int32_t GetKeyCode() override
    {
        return COUNTER_NUMBER_TEN_HANDLE;
    }
};

class MockNWebKeyEventAf : public NWebKeyEvent {
public:
    int32_t GetAction() override
    {
        return COUNTER_NUMBER_TEN_HANDLE;
    }
    int32_t GetKeyCode() override
    {
        return COUNTER_NUMBER_OTHER_HANDLE;
    }
};

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
        len = COUNTER_NUMBER_ZERO_HANDLE;
        width = COUNTER_NUMBER_ZERO_HANDLE;
        height = COUNTER_NUMBER_ZERO_HANDLE;
        return false;
    }

    bool SetFragmentHtml(const std::string& html) override
    {
        // Do nothing or implement actual behavior
        if (!html.empty()) {
            return true;
        } else {
            return false;
        }
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
        x = COUNTER_NUMBER_ZERO_HANDLE;
        y = COUNTER_NUMBER_ZERO_HANDLE;
    }

    bool IsSingleImageContent() override
    {
        return true;
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

class MockTaskExecutorTest : public Ace::TaskExecutor {
public:
    MockTaskExecutorTest() = default;
    MockTaskExecutorTest(bool delayRun) : delayRun_(delayRun) {}

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
class WebPatternTestHandle : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTestHandle::SetUpTestCase() {}
void WebPatternTestHandle::TearDownTestCase() {}
void WebPatternTestHandle::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
}
void WebPatternTestHandle::TearDown()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

class RenderContextTest : public RenderContext {
public:
    RectF GetPaintRectWithoutTransform() override
    {
        return *retf;
    }
    std::shared_ptr<RectF> retf;
};

/**
 * @tc.name: HandleOnDragEnter
 * @tc.desc: HandleOnDragEnter
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragEnter, TestSize.Level1)
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
    auto delegateMock = AceType::MakeRefPtr<WebDelegateDummy>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->delegate_ = delegateMock;
    auto gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->delegate_ = nullptr;
    webPattern->HandleOnDragEnter(gestureHub);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: HandleOnDragDropLink001
 * @tc.desc: HandleOnDragDropLink
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDropLink001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<UnifiedDataMock> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    EXPECT_NE(aceUnifiedData, nullptr);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    std::string linkUrl = "http://example.com";
    std::string linkTitle = "Example Title";
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData), _, _))
        .WillOnce(
            testing::Invoke([&](const RefPtr<UnifiedData>& data, std::string& outLinkUrl, std::string& outLinkTitle) {
                outLinkUrl = linkUrl;
                outLinkTitle = linkTitle;
                EXPECT_NE(outLinkUrl, "");
            }));
    webPattern->HandleOnDragDropLink(aceUnifiedData);
#endif
}

/**
 * @tc.name: HandleOnDragDropLink002
 * @tc.desc: HandleOnDragDropLink
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDropLink002, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<UnifiedDataMock> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    EXPECT_NE(aceUnifiedData, nullptr);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    std::string linkUrl = "";
    std::string linkTitle = "";
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData), _, _))
        .WillOnce(
            testing::Invoke([&](const RefPtr<UnifiedData>& data, std::string& outLinkUrl, std::string& outLinkTitle) {
                outLinkUrl = linkUrl;
                outLinkTitle = linkTitle;
                EXPECT_EQ(outLinkUrl, "");
            }));
    webPattern->HandleOnDragDropLink(aceUnifiedData);
#endif
}

/**
 * @tc.name: HandleOnDragDrop001
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMock>();
    gestureHub->SetData(nullptr);
    webPattern->HandleOnDragDrop(gestureHub);
    EXPECT_GE(aceData->GetSize(), 1);
#endif
}

/**
 * @tc.name: HandleOnDragDrop002
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop002, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    gestureHub->SetIsGetDataSuccess(false);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMockRe>();
    gestureHub->SetData(aceData);
    webPattern->HandleOnDragDrop(gestureHub);
    EXPECT_LT(aceData->GetSize(), 1);
#endif
}

/**
 * @tc.name: HandleOnDragDrop003
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop003, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    gestureHub->SetIsGetDataSuccess(true);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMock>();
    gestureHub->SetData(aceData);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    std::vector<std::string> plains = { "plains1", "plains2", "plains3" };
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, GetPlainTextRecords(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(plains));
    EXPECT_CALL(*mockUdmfClient, GetHtmlRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke([](const RefPtr<UnifiedData>&, std::string&, std::string&) {}));
    std::vector<uint8_t> spanString;
    EXPECT_CALL(*mockUdmfClient, GetSpanStringRecord(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(spanString));
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke(
            [](const RefPtr<UnifiedData>& aceData, std::string&, std::string&) { EXPECT_NE(aceData, nullptr); }));
    EXPECT_CALL(*mockUdmfClient, GetFileUriRecord(AceType::DynamicCast<UnifiedData>(aceData), _))
        .WillOnce(Return(false));
    webPattern->HandleOnDragDrop(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragDrop004
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop004, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMock>();
    gestureHub->SetData(aceData);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    std::vector<std::string> plains = { "", "", "" };
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, GetPlainTextRecords(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(plains));
    EXPECT_CALL(*mockUdmfClient, GetHtmlRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke([](const RefPtr<UnifiedData>&, std::string&, std::string&) {}));
    std::vector<uint8_t> spanString;
    EXPECT_CALL(*mockUdmfClient, GetSpanStringRecord(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(spanString));
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke(
            [](const RefPtr<UnifiedData>& aceData, std::string&, std::string&) { EXPECT_NE(aceData, nullptr); }));
    EXPECT_CALL(*mockUdmfClient, GetFileUriRecord(AceType::DynamicCast<UnifiedData>(aceData), _))
        .WillOnce(Return(false));
    webPattern->HandleOnDragDrop(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragDrop005
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop005, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMock>();
    gestureHub->SetData(aceData);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    std::vector<std::string> plains = { "", "plains1", "plains2" };
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, GetPlainTextRecords(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(plains));
    std::string htmlContent_ = "This is a sample HTML content.";
    EXPECT_CALL(*mockUdmfClient, GetHtmlRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(
            testing::Invoke([&](const RefPtr<UnifiedData>& data, std::string& htmlContent, std::string& plainContent) {
                htmlContent = htmlContent_;
                plainContent = "plainString";
            }));
    std::vector<uint8_t> spanString;
    EXPECT_CALL(*mockUdmfClient, GetSpanStringRecord(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(spanString));
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke(
            [](const RefPtr<UnifiedData>& aceData, std::string&, std::string&) { EXPECT_NE(aceData, nullptr); }));
    EXPECT_CALL(*mockUdmfClient, GetFileUriRecord(AceType::DynamicCast<UnifiedData>(aceData), _))
        .WillOnce(Return(false));
    webPattern->HandleOnDragDrop(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragDrop006
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop006, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMock>();
    gestureHub->SetData(aceData);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    std::vector<std::string> plains = { "", "plains1", "plains2" };
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, GetPlainTextRecords(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(plains));
    std::string htmlContent_ = "";
    EXPECT_CALL(*mockUdmfClient, GetHtmlRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(
            testing::Invoke([&](const RefPtr<UnifiedData>& data, std::string& htmlContent, std::string& plainContent) {
                htmlContent = htmlContent_;
                plainContent = "";
            }));
    std::vector<uint8_t> spanString;
    EXPECT_CALL(*mockUdmfClient, GetSpanStringRecord(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(spanString));
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke(
            [](const RefPtr<UnifiedData>& aceData, std::string&, std::string&) { EXPECT_NE(aceData, nullptr); }));
    EXPECT_CALL(*mockUdmfClient, GetFileUriRecord(AceType::DynamicCast<UnifiedData>(aceData), _))
        .WillOnce(Return(false));
    webPattern->HandleOnDragDrop(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragDrop007
 * @tc.desc: HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleOnDragDrop007, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(gestureHub, nullptr);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<OHOS::Ace::UnifiedDataMock>();
    gestureHub->SetData(aceData);
    webPattern->delegate_->dragData_ = std::make_shared<OHOS::NWeb::NWebDragDataMock>();
    std::vector<std::string> plains = { "", "plains1", "plains2" };
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, GetPlainTextRecords(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(plains));
    EXPECT_CALL(*mockUdmfClient, GetHtmlRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke([](const RefPtr<UnifiedData>&, std::string&, std::string&) {}));
    std::vector<uint8_t> spanString = { 10, 20, 30 };
    EXPECT_CALL(*mockUdmfClient, GetSpanStringRecord(AceType::DynamicCast<UnifiedData>(aceData)))
        .WillOnce(Return(spanString));
    EXPECT_CALL(*mockUdmfClient, GetLinkRecord(AceType::DynamicCast<UnifiedData>(aceData), _, _))
        .WillOnce(testing::Invoke(
            [](const RefPtr<UnifiedData>& aceData, std::string&, std::string&) { EXPECT_NE(aceData, nullptr); }));
    EXPECT_CALL(*mockUdmfClient, GetFileUriRecord(AceType::DynamicCast<UnifiedData>(aceData), _))
        .WillOnce(Return(false));
    webPattern->HandleOnDragDrop(gestureHub);
#endif
}

/**
 * @tc.name: HandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleDragEnd001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    int32_t x = 0;
    int32_t y = 0;
    webPattern->HandleDragEnd(x, y);
    EXPECT_FALSE(webPattern->isDragging_);
#endif
}

/**
 * @tc.name: HandleDragEnd002
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleDragEnd002, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    int32_t x = 1;
    int32_t y = 1;
    webPattern->HandleDragEnd(x, y);
    EXPECT_FALSE(webPattern->isReceivedArkDrag_);
#endif
}

/**
 * @tc.name: HandleDragEnd003
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleDragEnd003, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    int32_t x = 1;
    int32_t y = 0;
    webPattern->HandleDragEnd(x, y);
    EXPECT_FALSE(webPattern->isW3cDragEvent_);
#endif
}

/**
 * @tc.name: HandleDragEnd004
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleDragEnd004, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    int32_t x = 0;
    int32_t y = 2;
    webPattern->HandleDragEnd(x, y);
    EXPECT_FALSE(webPattern->isW3cDragEvent_);
#endif
}

/**
 * @tc.name: HandleBlurEvent001
 * @tc.desc: HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleBlurEvent001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    webPattern->isReceivedArkDrag_ = false;
    webPattern->selectPopupMenuShowing_ = true;
    webPattern->isVisible_ = false;
    webPattern->isActive_ = true;
    webPattern->HandleBlurEvent(BlurReason::WINDOW_BLUR);
    EXPECT_FALSE(webPattern->IsDialogNested());
#endif
}

/**
 * @tc.name: HandleBlurEvent002
 * @tc.desc: HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleBlurEvent002, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    webPattern->isReceivedArkDrag_ = false;
    webPattern->selectPopupMenuShowing_ = true;
    webPattern->isVisible_ = false;
    webPattern->isActive_ = false;
    webPattern->HandleBlurEvent(BlurReason::WINDOW_BLUR);
    EXPECT_FALSE(webPattern->IsDialogNested());
#endif
}

/**
 * @tc.name: HandleBlurEvent003
 * @tc.desc: HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, HandleBlurEvent003, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    webPattern->isReceivedArkDrag_ = false;
    webPattern->selectPopupMenuShowing_ = true;
    webPattern->isVisible_ = true;
    webPattern->isActive_ = true;
    webPattern->HandleBlurEvent(BlurReason::WINDOW_BLUR);
    EXPECT_FALSE(webPattern->IsDialogNested());
#endif
}

/**
 * @tc.name: KeyboardReDispatch001
 * @tc.desc: KeyboardReDispatch
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, KeyboardReDispatch001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    auto event = std::make_shared<OHOS::NWeb::MockNWebKeyEvent>();
    EXPECT_NE(event, nullptr);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    bool isUsed = true;
    KeyEvent keyEvent;
    for (int i = 0; i <= 10; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    webPattern->KeyboardReDispatch(event, isUsed);
    EXPECT_EQ(webPattern->webKeyEvent_.front().metaKey, 0);
#endif
}

/**
 * @tc.name: KeyboardReDispatch002
 * @tc.desc: KeyboardReDispatch
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, KeyboardReDispatch002, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    auto event = std::make_shared<OHOS::NWeb::MockNWebKeyEvent>();
    EXPECT_NE(event, nullptr);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    bool isUsed = false;
    KeyEvent keyEvent;
    for (int i = 0; i <= 10; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    webPattern->KeyboardReDispatch(event, isUsed);
    EXPECT_EQ(webPattern->webKeyEvent_.front().metaKey, 0);
#endif
}

/**
 * @tc.name: KeyboardReDispatch003
 * @tc.desc: KeyboardReDispatch
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, KeyboardReDispatch003, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    auto event = std::make_shared<OHOS::NWeb::MockNWebKeyEventFalse>();
    EXPECT_NE(event, nullptr);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    bool isUsed = true;
    KeyEvent keyEvent;
    for (int i = 0; i <= 10; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    webPattern->KeyboardReDispatch(event, isUsed);
    EXPECT_EQ(webPattern->webKeyEvent_.front().deviceId, 0);
#endif
}

/**
 * @tc.name: KeyboardReDispatch004
 * @tc.desc: KeyboardReDispatch
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, KeyboardReDispatch004, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    auto event = std::make_shared<OHOS::NWeb::MockNWebKeyEventBe>();
    EXPECT_NE(event, nullptr);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    bool isUsed = true;
    KeyEvent keyEvent;
    for (int i = 0; i <= 10; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    webPattern->KeyboardReDispatch(event, isUsed);
    EXPECT_EQ(webPattern->webKeyEvent_.front().deviceId, 0);
#endif
}

/**
 * @tc.name: KeyboardReDispatch005
 * @tc.desc: KeyboardReDispatch
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, KeyboardReDispatch005, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    auto event = std::make_shared<OHOS::NWeb::MockNWebKeyEventAf>();
    EXPECT_NE(event, nullptr);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::MockTaskExecutorTest>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    bool isUsed = true;
    KeyEvent keyEvent;
    for (int i = 0; i <= 10; ++i) {
        webPattern->webKeyEvent_.push_back(keyEvent);
    }
    webPattern->KeyboardReDispatch(event, isUsed);
    EXPECT_EQ(webPattern->webKeyEvent_.front().deviceId, 0);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = true;
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
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

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 1000000.0, 1000000.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    webPattern->offlineWebInited_ = false;
    webPattern->offlineWebRendered_ = true;
    webPattern->isUrlLoaded_ = true;
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
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

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 10.0, 10.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    EXPECT_FALSE(webPattern->CheckSafeAreaIsExpand());
    webPattern->offlineWebInited_ = false;
    webPattern->offlineWebRendered_ = true;
    webPattern->isUrlLoaded_ = true;
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap004
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap004, TestSize.Level1)
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

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 10.0, 10.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    EXPECT_FALSE(webPattern->CheckSafeAreaIsExpand());
    webPattern->offlineWebInited_ = true;
    webPattern->offlineWebRendered_ = false;
    webPattern->isUrlLoaded_ = true;
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_TRUE(webPattern->offlineWebRendered_);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap005
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap005, TestSize.Level1)
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

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 10.0, 10.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    EXPECT_FALSE(webPattern->CheckSafeAreaIsExpand());
    webPattern->offlineWebInited_ = true;
    webPattern->offlineWebRendered_ = true;
    webPattern->isUrlLoaded_ = true;
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap006
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap006, TestSize.Level1)
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

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 10.0, 10.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    EXPECT_FALSE(webPattern->CheckSafeAreaIsExpand());
    webPattern->offlineWebInited_ = false;
    webPattern->offlineWebRendered_ = false;
    webPattern->isUrlLoaded_ = false;
    webPattern->webSrc_ = "webSrcString";
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap007
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap007, TestSize.Level1)
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

    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 10.0, 10.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    EXPECT_FALSE(webPattern->CheckSafeAreaIsExpand());
    webPattern->offlineWebInited_ = false;
    webPattern->offlineWebRendered_ = false;
    webPattern->isUrlLoaded_ = false;
    webPattern->webSrc_ = "";
    bool result = webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap008
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestHandle, OnDirtyLayoutWrapperSwap008, TestSize.Level1)
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
    auto weakFrameNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dirty = AceType::MakeRefPtr<OHOS::Ace::NG::MockLayoutWrapper>(weakFrameNode);
    DirtySwapConfig config;
    config.contentSizeChange = true;
    webPattern->isInWindowDrag_ = false;
    auto reder = AceType::MakeRefPtr<RenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 10.0, 10.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto expand = std::make_unique<SafeAreaExpandOpts>();
    expand->type = SAFE_AREA_TYPE_SYSTEM;
    expand->edges = SAFE_AREA_EDGE_BOTTOM;
    layoutProperty->safeAreaExpandOpts_ = std::move(expand);
    frameNode->SetLayoutProperty(layoutProperty);
    EXPECT_TRUE(webPattern->CheckSafeAreaIsExpand());
    webPattern->offlineWebInited_ = false;
    webPattern->offlineWebRendered_ = false;
    webPattern->isUrlLoaded_ = true;
    webPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(webPattern->isKeyboardInSafeArea_);
#endif
}
} // namespace OHOS::Ace::NG
