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
#include <memory>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/event/touch_event.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef protected
#undef private
#include "test/mock/core/common/mock_udmf.h"

#include "nweb_date_time_chooser.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::NWeb {
class NWebDateTimeChooserCallbackImpl : public NWebDateTimeChooserCallback {
public:
    void Continue(bool success, const DateTime& value) override {}
};

class MockNWebSelectMenuBound : public NWebSelectMenuBound {
    int GetX() override
    {
        return ret;
    }
    int GetY() override
    {
        return ret;
    }
    int GetWidth() override
    {
        return ret;
    }
    int GetHeight() override
    {
        return ret;
    }
    int ret = -1;
};

class TaskExecutorImpl : public Ace::TaskExecutor {
public:
    TaskExecutorImpl() = default;
    explicit TaskExecutorImpl(bool delayRun) : delayRun_(delayRun) {}

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

namespace {
constexpr int32_t DRAG_START_X_POSITION = 10;
constexpr int32_t DRAG_START_Y_POSITION = 20;
constexpr double ROOT_WIDTH_VALUE = 10.0;
constexpr double ROOT_HEIGHT_VALUE = 10.0;
} // namespace

namespace OHOS::Ace::NG {
class UnifiedDataImpl : public Ace::UnifiedData {
public:
    int64_t GetSize() override
    {
        return 0;
    }
};

class PixelMapImpl : public OHOS::Ace::PixelMap {
public:
    int32_t GetWidth() const override
    {
        return 0;
    }
    int32_t GetHeight() const override
    {
        return 0;
    }
    bool GetPixelsVec(std::vector<uint8_t>& data) const override
    {
        return false;
    }
    const uint8_t* GetPixels() const override
    {
        return nullptr;
    }
    PixelFormat GetPixelFormat() const override
    {
        return static_cast<PixelFormat>(0);
    }
    AlphaType GetAlphaType() const override
    {
        return static_cast<AlphaType>(0);
    }
    AllocatorType GetAllocatorType() const override
    {
        return static_cast<AllocatorType>(0);
    }
    bool IsHdr() const override
    {
        return false;
    }
    int32_t GetRowStride() const override
    {
        return 0;
    }
    int32_t GetRowBytes() const override
    {
        return 0;
    }
    int32_t GetByteCount() const override
    {
        return 0;
    }
    void* GetPixelManager() const override
    {
        return nullptr;
    }
    void* GetRawPixelMapPtr() const override
    {
        return nullptr;
    }
    std::string GetId() override
    {
        return "";
    }
    uint32_t GetUniqueId()
    {
        return -1;
    }
    std::string GetModifyId() override
    {
        return "";
    }
    std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() override
    {
        return nullptr;
    }
    void* GetWritablePixels() const override
    {
        return nullptr;
    }
    void Scale(float xAxis, float yAxis) override {}
    void Scale(float xAxis, float yAxis, const AceAntiAliasingOption& option) override {}
    void SavePixelMapToFile(const std::string& dst) const override {}
    RefPtr<PixelMap> GetCropPixelMap(const Rect& srcRect) override
    {
        return nullptr;
    }
    bool EncodeTlv(std::vector<uint8_t>& buff) override
    {
        return false;
    }
    uint32_t WritePixels(const WritePixelsOptions& opts) override
    {
        return 0;
    }
    uint32_t GetInnerColorGamut() const override
    {
        return 0;
    }
    void SetMemoryName(std::string pixelMapName) const override {}
};

class NWebDragDataDummy : public NWeb::NWebDragData {
public:
    std::string GetLinkURL() override
    {
        return "";
    }
    std::string GetFragmentText() override
    {
        return "";
    }
    std::string GetFragmentHtml() override
    {
        return "";
    }
    bool GetPixelMapSetting(const void** data, size_t& len, int& width, int& height) override
    {
        return false;
    }
    bool SetFragmentHtml(const std::string& html) override
    {
        return false;
    }
    bool SetPixelMapSetting(const void* data, size_t len, int width, int height) override
    {
        return false;
    }
    bool SetLinkURL(const std::string& url) override
    {
        return false;
    }
    bool SetFragmentText(const std::string& Text) override
    {
        return false;
    }
    std::string GetLinkTitle() override
    {
        return "";
    }
    bool SetLinkTitle(const std::string& title) override
    {
        return false;
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
        return false;
    }
    std::string GetImageFileName() override
    {
        return "";
    }
    void ClearImageFileNames() override {}
};

class NWebDragDataTrueDummy : public NWeb::NWebDragData {
public:
    std::string GetLinkURL() override
    {
        return "https://example.com";
    }
    std::string GetFragmentText() override
    {
        return "This is some fragment text";
    }
    std::string GetFragmentHtml() override
    {
        return "<p>This is some fragment html</p>";
    }
    bool GetPixelMapSetting(const void** data, size_t& len, int& width, int& height) override
    {
        return true;
    }
    bool SetFragmentHtml(const std::string& html) override
    {
        return true;
    }
    bool SetPixelMapSetting(const void* data, size_t len, int width, int height) override
    {
        return true;
    }
    bool SetLinkURL(const std::string& url) override
    {
        return true;
    }
    bool SetFragmentText(const std::string& Text) override
    {
        return true;
    }
    std::string GetLinkTitle() override
    {
        return "Example Link Title";
    }
    bool SetLinkTitle(const std::string& title) override
    {
        return true;
    }
    void GetDragStartPosition(int& x, int& y) override
    {
        x = DRAG_START_X_POSITION;
        y = DRAG_START_Y_POSITION;
    }
    bool IsSingleImageContent() override
    {
        return true;
    }
    bool SetFileUri(const std::string& uri) override
    {
        return true;
    }
    std::string GetImageFileName() override
    {
        return "example_image.jpg";
    }
    void ClearImageFileNames() override {}
};

class WebPatternAddTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternAddTestNg::SetUpTestCase() {}
void WebPatternAddTestNg::TearDownTestCase() {}
void WebPatternAddTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}
void WebPatternAddTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

class NWebDateTimeChooserTestImpl : public NWeb::NWebDateTimeChooser {
public:
    NWebDateTimeChooserTestImpl() = default;
    NWeb::DateTimeChooserType GetType()
    {
        return ret;
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
    NWeb::DateTimeChooserType ret = NWeb::DateTimeChooserType::DTC_DATE;
};

/**
 * @tc.name: CalculateTooltipOffset
 * @tc.desc: CalculateTooltipOffset
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, CalculateTooltipOffset, TestSize.Level1)
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
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->rootWidth_ = ROOT_WIDTH_VALUE;
    pipeline->rootHeight_ = ROOT_HEIGHT_VALUE;
    webPattern->CalculateTooltipOffset(tooltipNode, *tooltipOffset);
#endif
}

/**
 * @tc.name: ShowDateTimeDialog
 * @tc.desc: ShowDateTimeDialog
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, ShowDateTimeDialog, TestSize.Level1)
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
    std::shared_ptr<NWebDateTimeChooserTestImpl> chooser = std::make_shared<NWebDateTimeChooserTestImpl>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackImpl> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackImpl>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    suggestions.clear();
    EXPECT_EQ(suggestions.size(), 0);
    EXPECT_CALL(*chooser, GetHasSelected).WillRepeatedly(Return(false));
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::TaskExecutorImpl>();
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
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnDateTimeChooserPopup
 * @tc.desc: OnDateTimeChooserPopup
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, OnDateTimeChooserPopup, TestSize.Level1)
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
    std::shared_ptr<NWebDateTimeChooserTestImpl> chooser = std::make_shared<NWebDateTimeChooserTestImpl>();
    ASSERT_NE(chooser, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallbackImpl> callback =
        std::make_shared<OHOS::NWeb::NWebDateTimeChooserCallbackImpl>();
    ASSERT_NE(callback, nullptr);
    std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>> suggestions;
    EXPECT_CALL(*chooser, GetHasSelected).WillRepeatedly(Return(false));
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<NWeb::TaskExecutorImpl>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    MockContainer::Current()->pipelineContext_->SetupRootElement();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    RefPtr<DialogTheme> expectedTheme = AccessibilityManager::MakeRefPtr<DialogTheme>();
    MockPipelineContext::GetCurrent()->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(::testing::_)).WillRepeatedly(Return(expectedTheme));
    webPattern->OnDateTimeChooserPopup(chooser, suggestions, callback);
    EXPECT_EQ(suggestions.size(), 0);
    EXPECT_NE(chooser->ret, NWeb::DTC_TIME);
    MockContainer::TearDown();
#endif
}

/**
 * @tc.name: GetSelectPopupPostion
 * @tc.desc: GetSelectPopupPostion
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, GetSelectPopupPostion, TestSize.Level1)
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
    auto nWebSelect = std::make_shared<NWeb::MockNWebSelectMenuBound>();
    auto ret = webPattern->GetSelectPopupPostion(nWebSelect);
    EXPECT_EQ(ret.GetX(), -1);
#endif
}

/**
 * @tc.name: GetDragPixelMapSize
 * @tc.desc: GetDragPixelMapSize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, GetDragPixelMapSize, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_->pixelMap_ = AccessibilityManager::MakeRefPtr<PixelMapImpl>();
    SizeF pixelMapSize = webPattern->GetDragPixelMapSize();
    EXPECT_EQ(pixelMapSize, SizeF(0, 0));
#endif
}

/**
 * @tc.name: OnDragFileNameStart
 * @tc.desc: OnDragFileNameStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, OnDragFileNameStart, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_->tempDir_ = "abc";
    RefPtr<UnifiedDataImpl> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataImpl>();
    ASSERT_NE(aceUnifiedData, nullptr);
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    ASSERT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, AddFileUriRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData),
                                     ElementsAreArray({ "file:///abc/dragdrop/test.txt" })))
        .WillOnce(Return(false));
    webPattern->OnDragFileNameStart(aceUnifiedData, "test.txt");
    std::string fullName = "abc/dragdrop/test.txt";
    EXPECT_EQ(webPattern->delegate_->tempDir_ + "/dragdrop/test.txt", fullName);
#endif
}

/**
 * @tc.name: HandleDoubleClickEvent_001
 * @tc.desc: HandleDoubleClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleDoubleClickEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MouseInfo info1;
    info1.SetButton(MouseButton::LEFT_BUTTON);
    info1.SetAction(MouseAction::PRESS);
    info1.SetLocalLocation({ 10.0, 10.0 });
    int64_t firstTimeStamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    std::chrono::milliseconds millisec1(firstTimeStamp);
    TimeStamp time1(millisec1);
    info1.SetTimeStamp(time1);
    webPattern->HandleDoubleClickEvent(info1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    MouseInfo info2;
    info2.SetButton(MouseButton::LEFT_BUTTON);
    info2.SetAction(MouseAction::PRESS);
    info2.SetLocalLocation({ 10.0, 10.0 });
    int64_t secondTimeStamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    std::chrono::milliseconds millisec2(secondTimeStamp);
    TimeStamp time2(millisec2);
    info2.SetTimeStamp(time2);
    bool result = webPattern->HandleDoubleClickEvent(info2);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: HandleDoubleClickEvent_002
 * @tc.desc: HandleDoubleClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleDoubleClickEvent_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MouseClickInfo mouseInfo1;
    mouseInfo1.x = 1;
    mouseInfo1.y = 1;
    webPattern->mouseClickQueue_.push(mouseInfo1);
    MouseClickInfo mouseInfo2;
    mouseInfo2.x = 2;
    mouseInfo2.y = 2;
    webPattern->mouseClickQueue_.push(mouseInfo2);
    MouseClickInfo mouseInfo3;
    mouseInfo3.x = 3;
    mouseInfo3.y = 3;
    webPattern->mouseClickQueue_.push(mouseInfo3);

    MouseInfo info4;
    info4.SetButton(MouseButton::LEFT_BUTTON);
    info4.SetAction(MouseAction::PRESS);
    MouseClickInfo mouseInfo4;
    mouseInfo4.x = 10;
    mouseInfo4.y = 10;
    info4.SetLocalLocation(Offset(mouseInfo4.x, mouseInfo4.y));
    bool result = webPattern->HandleDoubleClickEvent(info4);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: GenerateDragDropInfo
 * @tc.desc: GenerateDragDropInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, GenerateDragDropInfo, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    NG::DragDropInfo dragDropInfo;
    auto pixelMapImpl = AceType::MakeRefPtr<PixelMapImpl>();
    dragDropInfo.pixelMap = pixelMapImpl;
    bool result = webpattern.GenerateDragDropInfo(dragDropInfo);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: HandleOnDropMove_001
 * @tc.desc: HandleOnDropMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleOnDropMove_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->isDragging_ = true;
    webPattern->isW3cDragEvent_ = false;
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDropMove(info);
    EXPECT_FALSE(webPattern->isW3cDragEvent_);
#endif
}

/**
 * @tc.name: HandleOnDropMove_002
 * @tc.desc: HandleOnDropMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleOnDropMove_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    webpattern.isDragging_ = true;
    webpattern.isW3cDragEvent_ = true;
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webpattern.HandleOnDropMove(info);
    EXPECT_FALSE(webpattern.isDragStartFromWeb_);
#endif
}

/**
 * @tc.name: HandleOnDropMove_003
 * @tc.desc: HandleOnDropMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleOnDropMove_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->isDragging_ = true;
    webPattern->isW3cDragEvent_ = true;
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDropMove(info);
#endif
}

/**
 * @tc.name: InitWebEventHubDragDropStart
 * @tc.desc: InitWebEventHubDragDropStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, InitWebEventHubDragDropStart, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> eventHub = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragDropStart(eventHub);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "123";
    eventHub->GetOnDragStart()(info, extraParams);
    EXPECT_EQ(webPattern->dropX_, 0);
    EXPECT_EQ(webPattern->dropY_, 0);
#endif
}

/**
 * @tc.name: InitWebEventHubDragMove_001
 * @tc.desc: InitWebEventHubDragMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, InitWebEventHubDragMove_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> eventHub = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragMove(eventHub);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "123";
    webPattern->isDragging_ = false;
    EXPECT_FALSE(webPattern->isDragging_);
    eventHub->onDragMove_(info, extraParams);
    EXPECT_FALSE(webPattern->isDragging_);
#endif
}

/**
 * @tc.name: InitWebEventHubDragMove_002
 * @tc.desc: InitWebEventHubDragMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, InitWebEventHubDragMove_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> eventHub = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragMove(eventHub);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "123";
    webPattern->isDragging_ = true;
    EXPECT_TRUE(webPattern->isDragging_);
    for (uint32_t i = 0; i < 30; ++i) {
        eventHub->onDragMove_(info, extraParams);
    }
    EXPECT_TRUE(webPattern->isDragging_);
#endif
}

/**
 * @tc.name: InitWebEventHubDragDropEnd_001
 * @tc.desc: InitWebEventHubDragDropEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, InitWebEventHubDragDropEnd_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> eventHub = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragDropEnd(eventHub);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "123";
    webPattern->isDragging_ = false;
    EXPECT_FALSE(webPattern->isDragging_);
    eventHub->onDrop_(info, extraParams);
    EXPECT_FALSE(webPattern->isDragging_);
#endif
}

/**
 * @tc.name: InitWebEventHubDragDropEnd_002
 * @tc.desc: InitWebEventHubDragDropEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, InitWebEventHubDragDropEnd_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> eventHub = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragDropEnd(eventHub);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "123";
    webPattern->isDragging_ = true;
    EXPECT_TRUE(webPattern->isDragging_);
    eventHub->onDrop_(info, extraParams);
    EXPECT_EQ(webPattern->dropX_, 0);
    EXPECT_EQ(webPattern->dropY_, 0);
#endif
}

/**
 * @tc.name: HandleOnDragStart_001
 * @tc.desc: HandleOnDragStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleOnDragStart_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_->pixelMap_ = AccessibilityManager::MakeRefPtr<PixelMapImpl>();
    auto mockNWebDragData = std::make_shared<NWebDragDataDummy>();
    webPattern->delegate_->dragData_ = mockNWebDragData;
    RefPtr<UnifiedDataImpl> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataImpl>();
    ASSERT_NE(aceUnifiedData, nullptr);
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    ASSERT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, CreateUnifiedData()).WillOnce(Return(aceUnifiedData));
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDragStart(info);
    EXPECT_FALSE(webPattern->isDragEndMenuShow_);
#endif
}

/**
 * @tc.name: HandleOnDragStart_002
 * @tc.desc: HandleOnDragStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleOnDragStart_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_->pixelMap_ = AccessibilityManager::MakeRefPtr<PixelMapImpl>();
    auto mockNWebDragData = std::make_shared<NWebDragDataTrueDummy>();
    webPattern->delegate_->dragData_ = mockNWebDragData;
    RefPtr<UnifiedDataImpl> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataImpl>();
    ASSERT_NE(aceUnifiedData, nullptr);
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    ASSERT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(*mockUdmfClient, CreateUnifiedData()).WillOnce(Return(aceUnifiedData));
    EXPECT_CALL(*mockUdmfClient,
        AddFileUriRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData),
            ElementsAreArray({ "file:///data/storage/el2/base/haps/entry/temp/dragdrop/example_image.jpg" })))
        .Times(1);
    EXPECT_CALL(*mockUdmfClient,
        AddPlainTextRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData), "This is some fragment text"))
        .Times(1);
    EXPECT_CALL(*mockUdmfClient,
        AddHtmlRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData), "<p>This is some fragment html</p>", ""))
        .Times(1);
    EXPECT_CALL(*mockUdmfClient,
        AddLinkRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData), "https://example.com", "Example Link Title"))
        .Times(1);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDragStart(info);
    EXPECT_FALSE(webPattern->isDragEndMenuShow_);
#endif
}

/**
 * @tc.name: OnDeregister_001
 * @tc.desc: OnDeregister.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, OnDeregister_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto accessibilityChildTreeCallback = std::make_shared<WebAccessibilityChildTreeCallback>(nullptr, 1);
    bool ret = accessibilityChildTreeCallback->OnDeregister();
    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnSetChildTree001
 * @tc.desc: OnSetChildTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, OnSetChildTree_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto accessibilityChildTreeCallback = std::make_shared<WebAccessibilityChildTreeCallback>(nullptr, 1);
    bool ret = accessibilityChildTreeCallback->OnSetChildTree(1, 1);
    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnDumpChildInfo_001
 * @tc.desc: OnDumpChildInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, OnDumpChildInfo_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto accessibilityChildTreeCallback = std::make_shared<WebAccessibilityChildTreeCallback>(nullptr, 1);
    std::vector<std::string> params = { "params1", "params2" };
    std::vector<std::string> info = { "info1", "info2" };
    bool ret = accessibilityChildTreeCallback->OnDumpChildInfo(params, info);
    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnClearRegisterFlag_001
 * @tc.desc: OnClearRegisterFlag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, OnClearRegisterFlag_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto accessibilityChildTreeCallback = std::make_shared<WebAccessibilityChildTreeCallback>(nullptr, 1);
    accessibilityChildTreeCallback->OnClearRegisterFlag();
    EXPECT_FALSE(accessibilityChildTreeCallback->isReg_);
#endif
}

/**
 * @tc.name: GetAccessibilityVisible_001
 * @tc.desc: GetAccessibilityVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, GetAccessibilityVisible_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    bool ret = webpattern.GetAccessibilityVisible(1);
    EXPECT_TRUE(ret);
#endif
}

/**
 * @tc.name: GetAccessibilityVisible_002
 * @tc.desc: GetAccessibilityVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, GetAccessibilityVisible_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    bool ret = webPattern->GetAccessibilityVisible(1);
    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: InitDragEvent006
 * @tc.desc: InitDragEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, NotifyStartDragTask001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_NE(gestureHub, nullptr);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    auto dragDropManager = pipeline->dragDropManager_;
    dragDropManager->dragDropState_ = OHOS::Ace::NG::DragDropMgrState::DRAGGING;
    bool result = webPattern->NotifyStartDragTask(false);
    EXPECT_FALSE(result);
    pipeline->dragDropManager_ = nullptr;
    result = webPattern->NotifyStartDragTask(false);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: HandleOnDragDropFile001
 * @tc.desc: WebPatternAddTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, HandleOnDragDropFile001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);
    RefPtr<UnifiedDataImpl> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataImpl>();
    EXPECT_NE(aceUnifiedData, nullptr);
    webPattern->delegate_->dragData_ = std::make_shared<NWebDragDataTrueDummy>();
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    std::vector<std::string> urlVec = { "abc/dragdrop/test.txt" };
    EXPECT_CALL(*mockUdmfClient, GetFileUriEntry(AceType::DynamicCast<UnifiedData>(aceUnifiedData), _))
        .WillOnce(testing::Invoke([&](const RefPtr<UnifiedData>& data, std::vector<std::string>& outUrlVec) {
            outUrlVec = urlVec;
            EXPECT_FALSE(outUrlVec.empty());
            return true;
        }));
    webPattern->HandleOnDragDropFile(aceUnifiedData);
#endif
}

/**
 * @tc.name: handleDragCancelTask001
 * @tc.desc: WebPatternAddTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, handleDragCancelTask001, TestSize.Level1)
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
    EXPECT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_NE(gestureHub, nullptr);
    webPattern->InitDragEvent(gestureHub);
    EXPECT_NE(webPattern->dragEvent_, nullptr);
    auto drag_cancel_task = webPattern->dragEvent_->GetActionCancelEventFunc();
    EXPECT_NE(drag_cancel_task, nullptr);
    drag_cancel_task();
    EXPECT_FALSE(webPattern->isDragging_);
#endif
}

/**
 * @tc.name: handleDragCancelTask001
 * @tc.desc: handleOnDragEnterId001.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternAddTestNg, handleOnDragEnterId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> eventHub = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragDropStart(eventHub);
    std::string extraParams = "123";
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, nullptr, extraParams);
    EXPECT_FALSE(webPattern->isDragging_);
#endif
}
} // namespace OHOS::Ace::NG
