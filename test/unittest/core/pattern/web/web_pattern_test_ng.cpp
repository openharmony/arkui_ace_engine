/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#define private public
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "nweb_handler.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "oh_window_pip.h"

using namespace testing;
using namespace testing::ext;
enum PictureInPictureState {
    PIP_STATE_ENTER = 0,
    PIP_STATE_EXIT,
    PIP_STATE_PLAY,
    PIP_STATE_PAUSE,
    PIP_STATE_FAST_FORWARD,
    PIP_STATE_FAST_BACKWARD,
    PIP_STATE_RESTORE,
    PIP_STATE_HLS_ENTER,
    PIP_STATE_HLS_EXIT,
    PIP_STATE_RESIZE,
    PIP_STATE_NONE,
};

enum PictureInPictureCallback {
    PIP_CALLBACK_START = 1,
    PIP_CALLBACK_LIFECYCLE,
    PIP_CALLBACK_CONTROLEVENT,
    PIP_CALLBACK_RESIZE,
    PIP_CALLBACK_NONE,
};

#define PIP_WIDTH        100
#define PIP_HEIGHT       100
#define PIP_ID_OK_0      0
#define PIP_ID_OK_1      100
#define PIP_ID_OK_2      101
#define PIP_SURFACE_OK_0 0
#define PIP_SURFACE_OK_1 100
#define PIP_SURFACE_N_0  1

int32_t OH_PictureInPicture_CreatePip(
    PictureInPicture_PipConfig pipConfig, uint32_t* controllerId)
{
    if (*controllerId == PIP_ID_OK_0 || *controllerId == PIP_ID_OK_1 ||
        *controllerId == PIP_ID_OK_2) {
        return 0;
    }
    return 1;
}
int32_t OH_PictureInPicture_DeletePip(uint32_t controllerId)
{
    return static_cast<int32_t>(controllerId);
}
int32_t OH_PictureInPicture_StartPip(uint32_t controllerId)
{
    if (controllerId == PIP_ID_OK_0 || controllerId == PIP_ID_OK_1 ||
        controllerId == PIP_ID_OK_2) {
        return 0;
    }
    return 1;
}
int32_t OH_PictureInPicture_StopPip(uint32_t controllerId)
{
    return static_cast<int32_t>(controllerId);
}
int32_t OH_PictureInPicture_UpdatePipControlStatus(
    uint32_t controllerId, PictureInPicture_PipControlType controlType,
    PictureInPicture_PipControlStatus status)
{
    return static_cast<int32_t>(controllerId);
}
int32_t OH_PictureInPicture_SetPipControlEnabled(
    uint32_t controllerId, PictureInPicture_PipControlType controlType,
    bool enabled)
{
    return static_cast<int32_t>(controllerId);
}
int32_t OH_PictureInPicture_RegisterStartPipCallback(
    uint32_t controllerId, WebPipStartPipCallback callback)
{
    return controllerId == PIP_CALLBACK_START ? 1 : 0;
}
int32_t OH_PictureInPicture_RegisterLifecycleListener(
    uint32_t controllerId, WebPipLifecycleCallback callback)
{
    return controllerId == PIP_CALLBACK_LIFECYCLE ? 1 : 0;
}
int32_t OH_PictureInPicture_RegisterControlEventListener(
    uint32_t controllerId, WebPipControlEventCallback callback)
{
    return controllerId == PIP_CALLBACK_CONTROLEVENT ? 1 : 0;
}
int32_t OH_PictureInPicture_RegisterResizeListener(
    uint32_t controllerId, WebPipResizeCallback callback)
{
    return controllerId == PIP_CALLBACK_RESIZE ? 1 : 0;
}
int32_t OH_PictureInPicture_UnregisterAllResizeListeners(
    uint32_t controllerId)
{
    return static_cast<int32_t>(controllerId);
}
int32_t OH_PictureInPicture_SetPipMainWindowId(
    PictureInPicture_PipConfig pipConfig, uint32_t mainWindowId)
{
    return 0;
}
int32_t OH_PictureInPicture_SetPipTemplateType(
    PictureInPicture_PipConfig pipConfig, PictureInPicture_PipTemplateType pipTemplateType)
{
    return 0;
}
int32_t OH_PictureInPicture_SetPipRect(
    PictureInPicture_PipConfig pipConfig, uint32_t width, uint32_t height)
{
    return 0;
}
int32_t OH_PictureInPicture_SetPipControlGroup(
    PictureInPicture_PipConfig pipConfig,
    PictureInPicture_PipControlGroup* controlGroup,
    uint8_t controlGroupLength)
{
    return 0;
}
int32_t OH_PictureInPicture_SetPipNapiEnv(
    PictureInPicture_PipConfig pipConfig, void* env)
{
    return 0;
}
int32_t OH_PictureInPicture_CreatePipConfig(PictureInPicture_PipConfig* pipConfig)
{
    return 0;
}
int32_t OH_PictureInPicture_DestroyPipConfig(PictureInPicture_PipConfig* pipConfig)
{
    return 0;
}

int32_t OH_NativeWindow_CreateNativeWindowFromSurfaceId(uint64_t surfaceId, OHNativeWindow **window)
{
    if (surfaceId == PIP_SURFACE_N_0) {
        return OHOS::GSERROR_OK + 1;
    }
    if (surfaceId == PIP_SURFACE_OK_0) {
        *window = nullptr;
        return OHOS::GSERROR_OK;
    }
    if (surfaceId == PIP_SURFACE_OK_1) {
        *window = reinterpret_cast<OHNativeWindow*>(&surfaceId);
        return OHOS::GSERROR_OK;
    }
    return OHOS::GSERROR_OK;
}

namespace OHOS::Ace {
void DialogTheme::Builder::ParseNewPattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const {};
void DialogTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const {};
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
class WebDelegateMock : public WebDelegate {
public:
    WebDelegateMock(
        const WeakPtr<Ace::PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebDelegate(context, std::move(onError), type, id)
    {}
    MOCK_METHOD(void, OnPip,
        (int status, int delegate_id, int child_id, int frame_routing_id, int width, int height), ());
    MOCK_METHOD(void, SetPipNativeWindow,
        (int status, int delegate_id, int child_id, int frame_routing_id,  void* window), ());
    MOCK_METHOD(void, SendPipEvent,
        (int status, int delegate_id, int child_id, int frame_routing_id, int event), ());
};
}
}

namespace OHOS::NWeb {
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
bool IsSnapshotPathValid(const std::string& snapshotPath)
{
    return true;
}
} // namespace OHOS::NWeb

namespace OHOS::Ace::NG {
class MockNWebDragData : public NWeb::NWebDragData {
public:
    MOCK_METHOD(std::string, GetLinkURL, (), (override));
    MOCK_METHOD(std::string, GetFragmentText, (), (override));
    MOCK_METHOD(std::string, GetFragmentHtml, (), (override));
    MOCK_METHOD(bool, GetPixelMapSetting, (const void** data, size_t& len, int& width, int& height), (override));
    MOCK_METHOD(bool, SetFragmentHtml, (const std::string& html), (override));
    MOCK_METHOD(bool, SetPixelMapSetting, (const void* data, size_t len, int width, int height), (override));
    MOCK_METHOD(bool, SetLinkURL, (const std::string& url), (override));
    MOCK_METHOD(bool, SetFragmentText, (const std::string& Text), (override));
    MOCK_METHOD(std::string, GetLinkTitle, (), (override));
    MOCK_METHOD(bool, SetLinkTitle, (const std::string& title), (override));
    void GetDragStartPosition(int& x, int& y)
    {
        x = kDefaultDragStartX;
        y = kDefaultDragStartY;
    }
    MOCK_METHOD(bool, IsSingleImageContent, (), (override));
    MOCK_METHOD(bool, SetFileUri, (const std::string& uri), (override));
    MOCK_METHOD(std::string, GetImageFileName, (), (override));
    MOCK_METHOD(void, ClearImageFileNames, (), (override));
    int kDefaultDragStartX = 10;
    int kDefaultDragStartY = 20;
};
extern void PipStartPipCallback(uint32_t controllerId, uint8_t requestId, uint64_t surfaceId);
extern void PipLifecycleCallback(uint32_t controllerId, PictureInPicture_PipState state, int32_t errorCode);
extern void PipResizeCallback(uint32_t controllerId, uint32_t width, uint32_t height, double scale);
extern void PipControlEventCallback(
    uint32_t controllerId, PictureInPicture_PipControlType actionType, PictureInPicture_PipControlStatus status);

class WebPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTestNg::SetUpTestCase() {}
void WebPatternTestNg::TearDownTestCase() {}
void WebPatternTestNg::SetUp() {}
void WebPatternTestNg::TearDown() {}

/**
 * @tc.name: WebPatternTestNg_001
 * @tc.desc: Test webPattern.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    webpattern.HandleFocusEvent();
    webpattern.OnWebSrcUpdate();
    webpattern.OnWebDataUpdate();
    webpattern.OnJsEnabledUpdate(true);
    webpattern.OnMediaPlayGestureAccessUpdate(true);
    webpattern.OnFileAccessEnabledUpdate(true);
    webpattern.OnOnLineImageAccessEnabledUpdate(true);
    webpattern.OnDomStorageAccessEnabledUpdate(true);
    webpattern.OnImageAccessEnabledUpdate(true);
    webpattern.OnMixedModeUpdate(MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW);
    webpattern.OnZoomAccessEnabledUpdate(true);
    webpattern.OnGeolocationAccessEnabledUpdate(true);
    webpattern.OnUserAgentUpdate("chrome");
    webpattern.OnCacheModeUpdate(WebCacheMode::DEFAULT);
    webpattern.OnWebCursiveFontUpdate("test");
    webpattern.OnWebFantasyFontUpdate("test");
    webpattern.OnWebSansSerifFontUpdate("test");
    webpattern.OnWebSerifFontUpdate("test");
    webpattern.OnWebStandardFontUpdate("test");
    webpattern.OnDefaultFixedFontSizeUpdate(0);
    webpattern.OnDefaultFontSizeUpdate(0);
    webpattern.OnMinFontSizeUpdate(0);
    webpattern.OnMinLogicalFontSizeUpdate(0);
    webpattern.OnWebFixedFontUpdate("test");
    webpattern.OnBlockNetworkUpdate(true);
    webpattern.OnDarkModeUpdate(WebDarkMode::On);
    webpattern.OnForceDarkAccessUpdate(true);
    webpattern.OnAllowWindowOpenMethodUpdate(true);
    webpattern.OnHorizontalScrollBarAccessEnabledUpdate(true);
    webpattern.OnVerticalScrollBarAccessEnabledUpdate(true);
    webpattern.OnAudioResumeIntervalUpdate(0);
    webpattern.OnAudioExclusiveUpdate(true);
    webpattern.OnAudioSessionTypeUpdate(WebAudioSessionType::AUTO);
    webpattern.OnOptimizeParserBudgetEnabledUpdate(true);
    webpattern.OnBlurOnKeyboardHideModeUpdate(0);
#endif
}

/**
 * @tc.name: WebPatternTestNg_002
 * @tc.desc: Test webPattern.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->HandleFocusEvent();
    webPattern->OnWebSrcUpdate();
    webPattern->OnWebDataUpdate();
    webPattern->isUrlLoaded_ = true;
    webPattern->OnWebSrcUpdate();
    webPattern->OnWebDataUpdate();
    webPattern->OnJsEnabledUpdate(true);
    webPattern->OnMediaPlayGestureAccessUpdate(true);
    webPattern->OnFileAccessEnabledUpdate(true);
    webPattern->OnOnLineImageAccessEnabledUpdate(true);
    webPattern->OnDomStorageAccessEnabledUpdate(true);
    webPattern->OnImageAccessEnabledUpdate(true);
    webPattern->OnMixedModeUpdate(MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW);
    webPattern->OnZoomAccessEnabledUpdate(true);
    webPattern->OnGeolocationAccessEnabledUpdate(true);
    webPattern->OnUserAgentUpdate("chrome");
    webPattern->OnCacheModeUpdate(WebCacheMode::DEFAULT);
    webPattern->OnWebCursiveFontUpdate("test");
    webPattern->OnWebFantasyFontUpdate("test");
    webPattern->OnWebSansSerifFontUpdate("test");
    webPattern->OnWebSerifFontUpdate("test");
    webPattern->OnWebStandardFontUpdate("test");
    webPattern->OnDefaultFixedFontSizeUpdate(0);
    webPattern->OnDefaultFontSizeUpdate(0);
    webPattern->OnMinFontSizeUpdate(0);
    webPattern->OnMinLogicalFontSizeUpdate(0);
    webPattern->OnWebFixedFontUpdate("test");
    webPattern->OnBlockNetworkUpdate(true);
    webPattern->OnAllowWindowOpenMethodUpdate(true);
    webPattern->OnHorizontalScrollBarAccessEnabledUpdate(true);
    webPattern->OnVerticalScrollBarAccessEnabledUpdate(true);
    webPattern->OnOptimizeParserBudgetEnabledUpdate(true);
    webPattern->OnWebMediaAVSessionEnabledUpdate(true);
#endif
}

/**
 * @tc.name: WebPatternTestNg_003
 * @tc.desc: Test webPattern.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::TOUCH_SCREEN);
    webPattern->HandleDragMove(event);
    event.SetInputEventType(InputEventType::AXIS);
    webPattern->HandleDragMove(event);
    webPattern->OnDarkModeUpdate(WebDarkMode::On);
    webPattern->OnForceDarkAccessUpdate(true);
    webPattern->OnAudioResumeIntervalUpdate(0);
    webPattern->OnAudioExclusiveUpdate(true);
    webPattern->OnAudioSessionTypeUpdate(WebAudioSessionType::AUTO);
    webPattern->isEnhanceSurface_ = true;
    webPattern->delegate_ = nullptr;
    webPattern->OnModifyDone();
    webPattern->GetCurrentLanguage();
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate005
 * @tc.desc: OnScrollBarColorUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollBarColorUpdate005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    const std::string value;
    webpattern.OnScrollBarColorUpdate(value);
    SystemProperties::SetExtSurfaceEnabled(true);
    webpattern.InitEnhanceSurfaceFlag();
    SystemProperties::SetExtSurfaceEnabled(false);
    webpattern.InitEnhanceSurfaceFlag();
#endif
}

/**
 * @tc.name: InitDragEvent006
 * @tc.desc: InitDragEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitDragEvent006, TestSize.Level1)
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
    bool rerult = webPattern->NotifyStartDragTask();
    EXPECT_TRUE(rerult);
    webPattern->isDisableDrag_ = true;
    rerult = webPattern->NotifyStartDragTask();
    EXPECT_FALSE(rerult);
    webPattern->InitDragEvent(gestureHub);
    webPattern->InitDragEvent(gestureHub);
    EXPECT_NE(webPattern->dragEvent_, nullptr);
    rerult = webPattern->OnCursorChange(OHOS::NWeb::CursorType::CT_CROSS, nullptr);
    EXPECT_FALSE(rerult);
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
 * @tc.name: GetDragAcceptableStatus001
 * @tc.desc: GetDragAcceptableStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragAcceptableStatus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_->UpdateDragCursor(NWeb::NWebDragData::DragOperation::DRAG_OPERATION_COPY);
    webPattern->GetDragAcceptableStatus();
    webPattern->GetDragAcceptableStatus();
    webPattern->delegate_->UpdateDragCursor(NWeb::NWebDragData::DragOperation::DRAG_OPERATION_LINK);
    webPattern->GetDragAcceptableStatus();
    webPattern->delegate_->UpdateDragCursor(NWeb::NWebDragData::DragOperation::DRAG_OPERATION_MOVE);
    webPattern->GetDragAcceptableStatus();
    webPattern->delegate_ = nullptr;
#endif
}

/**
 * @tc.name: ShowDateTimeDialog007
 * @tc.desc: ShowDateTimeDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ShowDateTimeDialog007, TestSize.Level1)
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
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme = builder.Build(nullptr);
    EXPECT_NE(theme, nullptr);
    // SystemProperties::InitDeviceType(DeviceType::PHONE);
    webPattern->GetDialogProperties(theme);
    // SystemProperties::InitDeviceType(DeviceType::TV);
    webPattern->GetDialogProperties(theme);
#endif
}

/**
 * @tc.name: GetSelectPopupPostion008
 * @tc.desc: GetSelectPopupPostion.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetSelectPopupPostion008, TestSize.Level1)
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
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
#endif
}

/**
 * @tc.name: WebPatternTestNg_004.
 * @tc.desc: Test WebPattern  OnCursorChange when CursorType = context-menu.
 * @tc.type: FUNC.
 * @tc.require:I5OZZ8
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_004, TestSize.Level1)
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
    NWeb::NWebCursorInfoMock info;
    bool rerult = webPattern->OnCursorChange(OHOS::NWeb::CursorType::CT_CONTEXTMENU, nullptr);
    EXPECT_FALSE(rerult);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStart009
 * @tc.desc: JavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnDocumentStart009, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStart(scriptItems);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentStart010
 * @tc.desc: UpdateJavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnDocumentStart010, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStart(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentStart();
    EXPECT_FALSE(webPattern->onDocumentStartScriptItems_);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStartByOrder005
 * @tc.desc: JavaScriptOnDocumentStartByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnDocumentStartByOrder005, TestSize.Level1)
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

    webPattern->delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStartByOrder(scriptItems, scriptItemsByOrder);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEndByOrder005
 * @tc.desc: JavaScriptOnDocumentEndByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnDocumentEndByOrder005, TestSize.Level1)
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

    webPattern->delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEndByOrder(scriptItems, scriptItemsByOrder);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentStartByOrder005
 * @tc.desc: UpdateJavaScriptOnDocumentStartByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnDocumentStartByOrder005, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentStartScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    EXPECT_FALSE(webPattern->onDocumentStartScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    webPattern->onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentStartScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    EXPECT_TRUE(webPattern->onDocumentStartScriptItems_.has_value());
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentEndByOrder005
 * @tc.desc: UpdateJavaScriptOnDocumentEndByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnDocumentEndByOrder005, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentEndScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    EXPECT_FALSE(webPattern->onDocumentEndScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    webPattern->onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentEndScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    EXPECT_TRUE(webPattern->onDocumentEndScriptItems_.has_value());
#endif
}

/**
 * @tc.name: JavaScriptOnHeadReadyByOrder001
 * @tc.desc: JavaScriptOnHeadReadyByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnHeadReadyByOrder001, TestSize.Level1)
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

    webPattern->delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnHeadReadyByOrder(scriptItems, scriptItemsByOrder);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnHeadReadyByOrder001
 * @tc.desc: UpdateJavaScriptOnHeadReadyByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnHeadReadyByOrder001, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onHeadReadyScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onHeadReadyScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    EXPECT_FALSE(webPattern->onHeadReadyScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    webPattern->onHeadReadyScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onHeadReadyScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    EXPECT_TRUE(webPattern->onHeadReadyScriptItems_.has_value());
#endif
}

/**
 * @tc.name: OnModifyDone011
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnModifyDone011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
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
#endif
}

/**
 * @tc.name: GetFocusedAccessibilityNode012
 * @tc.desc: GetFocusedAccessibilityNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetFocusedAccessibilityNode012, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    bool isAccessibilityFocus = true;
    auto ret = webPattern->GetFocusedAccessibilityNode(accessibilityId, isAccessibilityFocus);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeById013
 * @tc.desc: GetAccessibilityNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetAccessibilityNodeById013, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    auto ret = webPattern->GetAccessibilityNodeById(accessibilityId);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeByFocusMove014
 * @tc.desc: GetAccessibilityNodeByFocusMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetAccessibilityNodeByFocusMove014, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    int32_t direction = 1;
    auto ret = webPattern->GetAccessibilityNodeByFocusMove(accessibilityId, direction);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetTransitionalNodeById001
 * @tc.desc: GetTransitionalNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetTransitionalNodeById001, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    auto ret = webPattern->GetTransitionalNodeById(accessibilityId);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: ExecuteAction015
 * @tc.desc: ExecuteAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ExecuteAction015, TestSize.Level1)
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
#endif
}

/**
 * @tc.name: SetAccessibilityState014
 * @tc.desc: SetAccessibilityState.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetAccessibilityState014, TestSize.Level1)
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
    webPattern->SetAccessibilityState(true);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd015
 * @tc.desc: JavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnDocumentEnd009, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentEnd016
 * @tc.desc: UpdateJavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnDocumentEnd010, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentEnd();
    EXPECT_FALSE(webPattern->onDocumentEndScriptItems_);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_001
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_001, TestSize.Level1)
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
    webPattern->zoomOutSwitch_ = false;
    webPattern->preScale_ = -1;
    double curScale = -3;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomStatus_, 1);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_002
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_002, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 2;
    webPattern->startPinchScale_ = 2;
    double scale = 1;
    webPattern->zoomOutSwitch_ = false;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomStatus_, 2);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_003
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_003, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 2;
    webPattern->startPinchScale_ = 0;
    double scale = 1;
    webPattern->zoomOutSwitch_ = true;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_004
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_004, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 0;
    webPattern->zoomStatus_ = 1;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomOutSwitch_, true);
    EXPECT_EQ(webPattern->zoomStatus_, 2);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_005
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_005, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 0;
    webPattern->zoomStatus_ = 0;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomStatus_, 2);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_006
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_006, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = true;
    webPattern->zoomStatus_ = 2;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomOutSwitch_, false);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_001
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_001, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    GestureEvent event;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_002
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_002, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(0);
    webPattern->preScale_ = 0;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_003
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_003, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(-2);
    webPattern->preScale_ = 0;
    webPattern->zoomErrorCount_ = 1;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_NE(webPattern->zoomErrorCount_, 1);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_004
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_004, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(1);
    webPattern->zoomStatus_ = 2;
    webPattern->zoomErrorCount_ = 1;
    webPattern->preScale_ = 2;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 1);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_005
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_005, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(1);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 1;
    webPattern->preScale_ = 4;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 1);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: GetNewOriginScale_001
 * @tc.desc: GetNewOriginScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewOriginScale_001, TestSize.Level1)
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

    webPattern->zoomStatus_ = 1;
    auto ret = webPattern->GetNewOriginScale(0.1);
    EXPECT_EQ(ret, 0.1);
    webPattern->zoomStatus_ = 2;
    ret = webPattern->GetNewOriginScale(0.1);
    EXPECT_EQ(ret, 5.0);
    webPattern->zoomStatus_ = 3;
    ret = webPattern->GetNewOriginScale(0.1);
    EXPECT_EQ(ret, 0.0);
#endif
}
/**
 * @tc.name: HandleScaleGestureStart_001
 * @tc.desc: HandleScaleGestureStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureStart_001, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(-2);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 0;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = false;

    webPattern->HandleScaleGestureStart(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 0);
#endif
}

/**
 * @tc.name: HandleScaleGestureEnd_001
 * @tc.desc: HandleScaleGestureEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureEnd_001, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(-2);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 0;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = false;

    webPattern->HandleScaleGestureEnd(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 0);
#endif
}

/**
 * @tc.name: HandleScaleGestureCancel_001
 * @tc.desc: HandleScaleGestureCancel.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureCancel_001, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(-2);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 0;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = false;

    webPattern->HandleScaleGestureCancel(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 0);
#endif
}

/**
 * @tc.name: GetNewScale_001
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_001, TestSize.Level1)
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
    webPattern->pageScale_ = 1;
    double scale = 10;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 5);
    EXPECT_EQ(ret, 1);
#endif
}

/**
 * @tc.name: GetNewScale_002
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_002, TestSize.Level1)
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
    webPattern->pageScale_ = 1;
    webPattern->zoomStatus_ = 2;
    double scale = 3;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(ret, scale);
#endif
}

/**
 * @tc.name: GetNewScale_003
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_003, TestSize.Level1)
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
    webPattern->pageScale_ = 0.1;
    webPattern->zoomStatus_ = 1;
    webPattern->startPageScale_ = 1;
    double scale = 3;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 5);
    EXPECT_EQ(ret, 5);
#endif
}

/**
 * @tc.name: GetNewScale_004
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_004, TestSize.Level1)
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
    webPattern->pageScale_ = 0.1;
    webPattern->zoomStatus_ = 1;
    webPattern->startPageScale_ = -1;
    double scale = 3;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 1);
    EXPECT_EQ(ret, 0.1);
#endif
}

/**
 * @tc.name: GetNewScale_005
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_005, TestSize.Level1)
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
    webPattern->pageScale_ = 10;
    webPattern->zoomStatus_ = 1;
    double scale = 0.1;
    webPattern->startPageScale_ = (1 - scale) * 10 * 0.4444 + 0.1;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 1);
    EXPECT_EQ(ret, 0.1);
#endif
}

/**
 * @tc.name: GetNewScale_006
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_006, TestSize.Level1)
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
    webPattern->pageScale_ = 0.1;
    webPattern->zoomStatus_ = 1;
    double scale = 0.1;
    webPattern->startPageScale_ = (1 - scale) * 10 * 0.4444;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 1);
    EXPECT_EQ(ret, 0.1);
#endif
}
/**
 * @tc.name: InitTouchEvent_001
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitTouchEvent_001, TestSize.Level1)
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
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    webPattern->touchEvent_ = nullptr;

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_002
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitTouchEvent_002, TestSize.Level1)
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
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    TouchEventFunc func = [](TouchEventInfo&) {};
    RefPtr<TouchEventImpl> touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(func));
    webPattern->touchEvent_ = touchEvent_;
    EXPECT_NE(webPattern->touchEvent_, nullptr);

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitMouseEvent_001
 * @tc.desc: InitMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitMouseEvent_001, TestSize.Level1)
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
    RefPtr<InputEventHub> inputHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    webPattern->mouseEvent_ = nullptr;
    EXPECT_EQ(webPattern->mouseEvent_, nullptr);

    webPattern->InitMouseEvent(inputHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitHoverEvent_001
 * @tc.desc: InitHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitHoverEvent_001, TestSize.Level1)
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
    RefPtr<InputEventHub> inputHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    webPattern->hoverEvent_ = nullptr;
    EXPECT_EQ(webPattern->hoverEvent_, nullptr);

    webPattern->InitHoverEvent(inputHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleMouseEvent_001
 * @tc.desc: HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleMouseEvent_001, TestSize.Level1)
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
    MouseInfo info;

    webPattern->HandleMouseEvent(info);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_001
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_001, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    MouseInfo info;

    webPattern->WebOnMouseEvent(info);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_002
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_002, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::PRESS);
    info.SetButton(MouseButton::LEFT_BUTTON);

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 1);
    EXPECT_EQ(webPattern->mouseHoveredY_, 2);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_003
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_003, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::RELEASE);
    info.SetButton(MouseButton::LEFT_BUTTON);
    webPattern->isReceivedArkDrag_ = true;

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 1);
    EXPECT_EQ(webPattern->mouseHoveredY_, 2);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_004
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_004, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::HOVER_EXIT);
    info.SetButton(MouseButton::LEFT_BUTTON);
    webPattern->isReceivedArkDrag_ = false;

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 1);
    EXPECT_EQ(webPattern->mouseHoveredY_, 2);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_005
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_005, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::MOVE);
    info.SetButton(MouseButton::LEFT_BUTTON);

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 10);
    EXPECT_EQ(webPattern->mouseHoveredY_, 20);
#endif
}

/**
 * @tc.name: ResetDragAction_001
 * @tc.desc: ResetDragAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ResetDragAction_001, TestSize.Level1)
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
    webPattern->isDragging_ = true;

    webPattern->ResetDragAction();
    EXPECT_EQ(webPattern->isDragging_, false);
#endif
}

/**
 * @tc.name: ResetDragAction_002
 * @tc.desc: ResetDragAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ResetDragAction_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->isDragging_ = true;

    webPattern->ResetDragAction();
    EXPECT_EQ(webPattern->isDragging_, false);
#endif
}

/**
 * @tc.name: ResetDragAction_003
 * @tc.desc: ResetDragAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ResetDragAction_003, TestSize.Level1)
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
    webPattern->isDragging_ = false;

    webPattern->ResetDragAction();
    EXPECT_EQ(webPattern->isDragging_, false);
#endif
}

/**
 * @tc.name: GetDragOffset_001
 * @tc.desc: GetDragOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragOffset_001, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;

    auto ret = webPattern->GetDragOffset();
    EXPECT_EQ(ret.GetX(), 0);
    EXPECT_EQ(ret.GetY(), 0);
#endif
}

/**
 * @tc.name: GetDragOffset_002
 * @tc.desc: GetDragOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragOffset_002, TestSize.Level1)
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
    webPattern->delegate_->dragData_ = nullptr;

    auto ret = webPattern->GetDragOffset();
    EXPECT_EQ(ret.GetX(), 0);
    EXPECT_EQ(ret.GetY(), 0);
#endif
}

/**
 * @tc.name: GetDragOffset_003
 * @tc.desc: GetDragOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragOffset_003, TestSize.Level1)
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
    auto dragData_ = std::make_shared<MockNWebDragData>();
    webPattern->delegate_->dragData_ = dragData_;

    auto ret = webPattern->GetDragOffset();
    EXPECT_EQ(ret.GetX(), 10);
    EXPECT_EQ(ret.GetY(), 20);
#endif
}

/**
 * @tc.name: WebRequestFocus_001
 * @tc.desc: WebRequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebRequestFocus_001, TestSize.Level1)
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
    webPattern->WebRequestFocus();
#endif
}

/**
 * @tc.name: OnGestureFocusModeUpdate_001
 * @tc.desc: OnGestureFocusModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnGestureFocusModeUpdate_001, TestSize.Level1)
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
    webPattern->OnGestureFocusModeUpdate(GestureFocusMode::DEFAULT);
    EXPECT_TRUE(webPattern->IsDefaultGestureFocusMode());
    webPattern->OnGestureFocusModeUpdate(GestureFocusMode::GESTURE_TAP_AND_LONG_PRESS);
    EXPECT_FALSE(webPattern->IsDefaultGestureFocusMode());
#endif
}

/**
 * @tc.name: IsCurrentFocus_001
 * @tc.desc: IsCurrentFocus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsCurrentFocus_001, TestSize.Level1)
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
    webPattern->IsCurrentFocus();
#endif
}

/**
 * @tc.name: UpdateContentOffset_001
 * @tc.desc: UpdateContentOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateContentOffset_001, TestSize.Level1)
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
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true);
    ASSERT_NE(layoutWrapper, nullptr);
    webPattern->UpdateContentOffset(layoutWrapper);
#endif
}

/**
 * @tc.name: HandleFocusEvent_001
 * @tc.desc: HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFocusEvent_001, TestSize.Level1)
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
    webPattern->needOnFocus_ = false;
    webPattern->HandleFocusEvent();
    EXPECT_TRUE(webPattern->needOnFocus_);
#endif
}

/**
 * @tc.name: HandleFocusEvent_002
 * @tc.desc: HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFocusEvent_002, TestSize.Level1)
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
    webPattern->needOnFocus_ = true;
    webPattern->HandleFocusEvent();
    EXPECT_TRUE(webPattern->needOnFocus_);
#endif
}

/**
 * @tc.name: DumpInfo_001
 * @tc.desc: DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, DumpInfo_001, TestSize.Level1)
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
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    webPattern->DumpInfo();
    webPattern->delegate_ = nullptr;
    webPattern->DumpGpuInfo();
    webPattern->renderSurface_ = nullptr;
    webPattern->DumpSurfaceInfo();
#endif
}

/**
 * @tc.name: OnCompleteSwapWithNewSize_001
 * @tc.desc: OnCompleteSwapWithNewSize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnCompleteSwapWithNewSize_001, TestSize.Level1)
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
    webPattern->isInWindowDrag_ = true;
    webPattern->isWaiting_ = true;
    webPattern->OnCompleteSwapWithNewSize();
    EXPECT_FALSE(webPattern->isWaiting_);
    webPattern->isInWindowDrag_ = false;
    webPattern->isWaiting_ = true;
    webPattern->OnCompleteSwapWithNewSize();
    EXPECT_TRUE(webPattern->isWaiting_);
    webPattern->isInWindowDrag_ = true;
    webPattern->isWaiting_ = false;
    webPattern->OnCompleteSwapWithNewSize();
    EXPECT_FALSE(webPattern->isWaiting_);
    webPattern->isInWindowDrag_ = false;
    webPattern->isWaiting_ = false;
    webPattern->OnCompleteSwapWithNewSize();
    EXPECT_FALSE(webPattern->isWaiting_);
#endif
}

/**
 * @tc.name: OnIntrinsicSizeEnabledUpdate_001
 * @tc.desc: OnIntrinsicSizeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnIntrinsicSizeEnabledUpdate_001, TestSize.Level1)
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
    webPattern->OnIntrinsicSizeEnabledUpdate(false);
#endif
}

/**
 * @tc.name: OnIntrinsicSizeEnabledUpdate_002
 * @tc.desc: OnIntrinsicSizeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnIntrinsicSizeEnabledUpdate_002, TestSize.Level1)
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
    webPattern->OnIntrinsicSizeEnabledUpdate(true);
#endif
}

/**
 * @tc.name: OnIntrinsicSizeEnabledUpdate_003
 * @tc.desc: OnIntrinsicSizeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnIntrinsicSizeEnabledUpdate_003, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->OnIntrinsicSizeEnabledUpdate(true);
#endif
}

/**
 * @tc.name: SetSurfaceDensity_001
 * @tc.desc: SetSurfaceDensity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetSurfaceDensity_001, TestSize.Level1)
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
    webPattern->SetSurfaceDensity(1);
    EXPECT_EQ(webPattern->density_, 1);
#endif
}

/**
 * @tc.name: RestoreRenderFit_001
 * @tc.desc: RestoreRenderFit.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RestoreRenderFit_001, TestSize.Level1)
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
    webPattern->renderContextForSurface_ = nullptr;
    webPattern->RestoreRenderFit();
#endif
}

/**
 * @tc.name: RestoreRenderFit_002
 * @tc.desc: RestoreRenderFit.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RestoreRenderFit_002, TestSize.Level1)
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
    webPattern->renderContextForSurface_ = RenderContext::Create();
    webPattern->RestoreRenderFit();
#endif
}

/**
 * @tc.name: WindowDrag_001
 * @tc.desc: WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowDrag_001, TestSize.Level1)
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
    webPattern->dragWindowFlag_ = true;
    webPattern->lastWidth_ = 0;
    webPattern->lastHeight_ = 0;
    webPattern->WindowDrag(1, 2);
    EXPECT_EQ(webPattern->lastWidth_, 1);
    EXPECT_EQ(webPattern->lastHeight_, 2);
#endif
}

/**
 * @tc.name: WindowDrag_002
 * @tc.desc: WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowDrag_002, TestSize.Level1)
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
    webPattern->dragWindowFlag_ = true;
    webPattern->lastWidth_ = 0;
    webPattern->lastHeight_ = 0;
    webPattern->WindowDrag(6, 7);
    EXPECT_EQ(webPattern->lastWidth_, 6);
    EXPECT_EQ(webPattern->lastHeight_, 7);
#endif
}

/**
 * @tc.name: WindowDrag_003
 * @tc.desc: WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowDrag_003, TestSize.Level1)
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
    webPattern->dragWindowFlag_ = true;
    webPattern->lastWidth_ = 1;
    webPattern->lastHeight_ = 2;
    webPattern->WindowDrag(7, 8);
    EXPECT_EQ(webPattern->lastWidth_, 7);
    EXPECT_EQ(webPattern->lastHeight_, 8);
#endif
}

/**
 * @tc.name: WindowDrag_004
 * @tc.desc: WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowDrag_004, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->lastWidth_ = 1;
    webPattern->lastHeight_ = 2;
    webPattern->WindowDrag(3, 4);
    EXPECT_EQ(webPattern->lastWidth_, 1);
    EXPECT_EQ(webPattern->lastHeight_, 2);
#endif
}

/**
 * @tc.name: WindowDrag_005
 * @tc.desc: WindowDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowDrag_005, TestSize.Level1)
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
    webPattern->dragWindowFlag_ = false;
    webPattern->lastWidth_ = 1;
    webPattern->lastHeight_ = 0;
    webPattern->WindowDrag(3, 4);
    EXPECT_EQ(webPattern->lastWidth_, 1);
    EXPECT_EQ(webPattern->lastHeight_, 0);
#endif
}

/**
 * @tc.name: WindowMaximize_001
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_001, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("8");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_2IN1);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    webPattern->isAttachedToMainTree_ = true;
    webPattern->isVisible_ = true;
    webPattern->renderContextForSurface_ = RenderContext::Create();
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: WindowMaximize_002
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_002, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("-1");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_UNKNOWN);
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: WindowMaximize_003
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_003, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("8");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_2IN1);
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: WindowMaximize_004
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_004, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("8");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_2IN1);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: WindowMaximize_005
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_005, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("8");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_2IN1);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    webPattern->isAttachedToMainTree_ = false;
    webPattern->isVisible_ = true;
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: WindowMaximize_006
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_006, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("8");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_2IN1);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    webPattern->isAttachedToMainTree_ = true;
    webPattern->isVisible_ = false;
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: WindowMaximize_007
 * @tc.desc: WindowMaximize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WindowMaximize_007, TestSize.Level1)
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
    OHOS::Ace::SetReturnStatus("8");
    auto webInfoType = webPattern->GetWebInfoType();
    EXPECT_EQ(webInfoType, WebInfoType::TYPE_2IN1);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    webPattern->isAttachedToMainTree_ = true;
    webPattern->isVisible_ = true;
    webPattern->renderContextForSurface_ = nullptr;
    webPattern->WindowMaximize();
#endif
}

/**
 * @tc.name: ChangeVisibilityOfQuickMenuV2_001
 * @tc.desc: ChangeVisibilityOfQuickMenuV2.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ChangeVisibilityOfQuickMenuV2_001, TestSize.Level1)
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
    webPattern->ChangeVisibilityOfQuickMenuV2();
#endif
}

/**
 * @tc.name: InitDataDetector_001
 * @tc.desc: InitDataDetector.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitDataDetector_001, TestSize.Level1)
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
 
    bool ret = webPattern->GetDataDetectorEnable();
    ASSERT_EQ(ret, false);
    webPattern->GetDataDetectorAdapter();
    webPattern->InitDataDetector();
    ASSERT_NE(webPattern->webDataDetectorAdapter_, nullptr);
    ret = webPattern->GetDataDetectorEnable();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CreatePip_001
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CreatePip_002
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_HLS_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CreatePip_003
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CreatePip_004
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);

    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
#endif
}

/**
 * @tc.name: CreatePip_005
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 1;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, false);
    pipController++;
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, false);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, false);
    webPattern.EnablePip(pipController);
#endif
}

/**
 * @tc.name: CreatePip_006
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipInfo info1{1, 1, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info1);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CreatePip_007
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipInfo info1{1, 0, 1, 0, PIP_WIDTH, PIP_HEIGHT};
    ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info1);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CreatePip_008
 * @tc.desc: CreatePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreatePip_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipInfo info1{1, 0, 0, 1, PIP_WIDTH, PIP_HEIGHT};
    ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info1);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: StopPip_001
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    ret = webPattern.StopPip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: StopPip_002
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    info.delegateId = 1;
    ret = webPattern.StopPip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: StopPip_003
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_HLS_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    ret = webPattern.StopPip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: StopPip_004
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_HLS_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StopPip(1, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: StopPip_005
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_HLS_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StopPip(0, 1, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: StopPip_006
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPip_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_HLS_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StopPip(0, 0, 1);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_001
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    ret = webPattern.PlayPip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: PlayPausePip_002
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    info.delegateId = 1;
    ret = webPattern.PlayPip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_003
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    ret = webPattern.PausePip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, true);
#endif
}

/**
 * @tc.name: PlayPausePip_004
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.RegisterPip(pipController);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(pipController);
    ASSERT_EQ(ret, true);
    webPattern.EnablePip(pipController);
    info.delegateId = 1;
    ret = webPattern.PlayPip(info.delegateId, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_005
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.PlayPip(1, info.childId, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_006
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.PlayPip(0, 1, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_007
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.PlayPip(0, 0, 1);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_008
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.PausePip(1, 0, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_009
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.PausePip(0, 1, info.frameRoutingId);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PlayPausePip_010
 * @tc.desc: PlayPausePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PlayPausePip_010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{1, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.PausePip(0, 0, 1);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_001
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(0, ABOUT_TO_START, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_002
 * @tc.desc: CallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    ret = webPattern.StopPip(0, 0, 0);
    ASSERT_EQ(ret, false);
    PipLifecycleCallback(0, ABOUT_TO_START, 0);
#endif
}
 
/**
 * @tc.name: PipLifecycleCallbackPip_003
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(1, ABOUT_TO_START, 0);
#endif
}
 
/**
 * @tc.name: PipLifecycleCallbackPip_004
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    ret = webPattern.StopPip(0, 0, 0);
    ASSERT_EQ(ret, false);
    PipLifecycleCallback(PIP_ID_OK_1, ABOUT_TO_START, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_005
 * @tc.desc: CallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(0, ABOUT_TO_START, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_006
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(0, STOPPED, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_007
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(0, ABOUT_TO_RESTORE, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_008
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(0, ABOUT_TO_RESTORE, 0);
    PipLifecycleCallback(0, STOPPED, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_009
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(PIP_ID_OK_1, ABOUT_TO_RESTORE, 0);
#endif
}

/**
 * @tc.name: PipLifecycleCallbackPip_010
 * @tc.desc: PipLifecycleCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipLifecycleCallbackPip_010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipLifecycleCallback(0, ABOUT_TO_STOP, 0);
    PipLifecycleCallback(0, STOPPED, 0);
#endif
}

/**
 * @tc.name: PipStartPipCallbackPip_001
 * @tc.desc: PipStartPipCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipStartPipCallbackPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipStartPipCallback(0, 0, 1);
#endif
}
 
/**
 * @tc.name: PipStartPipCallbackPip_002
 * @tc.desc: PipStartPipCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipStartPipCallbackPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipStartPipCallback(0, 0, 0);
#endif
}

/**
 * @tc.name: PipStartPipCallbackPip_003
 * @tc.desc: PipStartPipCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipStartPipCallbackPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipStartPipCallback(0, 0, PIP_SURFACE_OK_1);
#endif
}

/**
 * @tc.name: PipStartPipCallbackPip_004
 * @tc.desc: PipStartPipCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipStartPipCallbackPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipStartPipCallback(1, 0, 0);
#endif
}
 
/**
 * @tc.name: PipStartPipCallbackPip_005
 * @tc.desc: PipStartPipCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipStartPipCallbackPip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipStartPipCallback(PIP_ID_OK_1, 0, 0);
#endif
}
 
/**
 * @tc.name: PipControlEventCallbackPip_001
 * @tc.desc: PipControlEventCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(0, VIDEO_PLAY_PAUSE, PictureInPicture_PipControlStatus::PLAY);
#endif
}
 
/**
 * @tc.name: PipControlEventCallbackPip_002
 * @tc.desc: PipControlEventCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(0, VIDEO_PLAY_PAUSE, PictureInPicture_PipControlStatus::PLAY);
#endif
}
 
/**
 * @tc.name: PipControlEventCallbackPip_003
 * @tc.desc: PipControlEventCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(0, VIDEO_PLAY_PAUSE, PictureInPicture_PipControlStatus::PAUSE);
#endif
}
 
/**
 * @tc.name: PipControlEventCallbackPip_004
 * @tc.desc: CallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(0, FAST_FORWARD, PictureInPicture_PipControlStatus::PAUSE);
#endif
}
 
/**
 * @tc.name: PipControlEventCallbackPip_005
 * @tc.desc: PipControlEventCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(0, FAST_BACKWARD, PictureInPicture_PipControlStatus::PAUSE);
#endif
}

/**
 * @tc.name: PipControlEventCallbackPip_006
 * @tc.desc: PipControlEventCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(0, MUTE_SWITCH, PictureInPicture_PipControlStatus::PAUSE);
#endif
}

/**
 * @tc.name: PipControlEventCallbackPip_007
 * @tc.desc: PipControlEventCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipControlEventCallbackPip_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipControlEventCallback(PIP_ID_OK_1, FAST_BACKWARD, PictureInPicture_PipControlStatus::PAUSE);
#endif
}

/**
 * @tc.name: PipResizeCallbackPip_001
 * @tc.desc: PipResizeCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipResizeCallbackPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipResizeCallback(0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: PipResizeCallbackPip_002
 * @tc.desc: PipResizeCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipResizeCallbackPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipResizeCallback(1, 0, 0, 0);
#endif
}

/**
 * @tc.name: PipResizeCallbackPip_003
 * @tc.desc: PipResizeCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipResizeCallbackPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    PipResizeCallback(0, 0, 0, 0);
#endif
}

/**
 * @tc.name: PipResizeCallbackPip_004
 * @tc.desc: PipResizeCallbackPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, PipResizeCallbackPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo info{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, info);
    ASSERT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    ASSERT_EQ(ret, true);
    PipResizeCallback(PIP_ID_OK_1, 0, 0, 0);
#endif
}
/**
 * @tc.name: OnPipPip_001
 * @tc.desc: OnPipPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnPipPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    ASSERT_EQ(ret, true);
    webPattern.OnPip(0, 0, 0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: OnPipPip_002
 * @tc.desc: OnPipPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnPipPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    ASSERT_EQ(ret, true);
    webPattern.OnPip(PIP_STATE_EXIT, 0, 0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: OnPipPip_003
 * @tc.desc: OnPipPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnPipPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    ASSERT_EQ(ret, true);
    webPattern.OnPip(PIP_STATE_PLAY, 0, 0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: OnPipPip_004
 * @tc.desc: OnPipPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnPipPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    ASSERT_EQ(ret, true);
    webPattern.OnPip(PIP_STATE_PAUSE, 0, 0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: OnPipPip_005
 * @tc.desc: OnPipPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnPipPip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    ASSERT_EQ(ret, true);
    webPattern.OnPip(PIP_STATE_NONE, 0, 0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: SetPipNativeWindowPip_001
 * @tc.desc: SetPipNativeWindowPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetPipNativeWindowPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    auto delegateMock = AceType::MakeRefPtr<WebDelegateMock>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern.delegate_ = delegateMock;
    webPattern.SetPipNativeWindow(0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: SetPipNativeWindowPip_002
 * @tc.desc: SetPipNativeWindowPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetPipNativeWindowPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    webPattern.SetPipNativeWindow(0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: SendPipEventPip_001
 * @tc.desc: SendPipEventPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SendPipEventPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    auto delegateMock = AceType::MakeRefPtr<WebDelegateMock>(
        PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern.delegate_ = delegateMock;
    webPattern.SendPipEvent(0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: SendPipEventPip_002
 * @tc.desc: SendPipEventPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SendPipEventPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    webPattern.SendPipEvent(0, 0, 0, 0);
#endif
}
 
/**
 * @tc.name: RegisterPip_001
 * @tc.desc: RegisterPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegisterPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.RegisterPip(0);
    EXPECT_EQ(ret, true);
#endif
}
 
/**
 * @tc.name: RegisterPip_002
 * @tc.desc: RegisterPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegisterPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.RegisterPip(PIP_CALLBACK_START);
    EXPECT_EQ(ret, false);
#endif
}
 
/**
 * @tc.name: RegisterPip_003
 * @tc.desc: RegisterPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegisterPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.RegisterPip(PIP_CALLBACK_LIFECYCLE);
    EXPECT_EQ(ret, false);
#endif
}
 
/**
 * @tc.name: RegisterPip_004
 * @tc.desc: RegisterPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegisterPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.RegisterPip(PIP_CALLBACK_CONTROLEVENT);
    EXPECT_EQ(ret, false);
#endif
}
 
 
/**
 * @tc.name: RegisterPip_005
 * @tc.desc: RegisterPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegisterPip_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.RegisterPip(PIP_CALLBACK_RESIZE);
    EXPECT_EQ(ret, false);
#endif
}
 
/**
 * @tc.name: StartPip_001
 * @tc.desc: StartPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StartPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.StartPip(0);
    EXPECT_EQ(ret, true);
#endif
}
 
/**
 * @tc.name: StartPip_002
 * @tc.desc: StartPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StartPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    auto ret = webPattern.StartPip(1);
    EXPECT_EQ(ret, false);
#endif
}
 
/**
 * @tc.name: EnablePip_001
 * @tc.desc: EnablePip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, EnablePip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    webPattern.EnablePip(0);
#endif
}
 
/**
 * @tc.name: StopPipPip_001
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPipPip_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    ret = webPattern.StopPip(0, 0, 0);
    EXPECT_EQ(ret, true);
#endif
}
 
/**
 * @tc.name: StopPipPip_002
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPipPip_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = 0;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    ret = webPattern.StopPip(1, 0, 0);
    EXPECT_EQ(ret, false);
#endif
}
 
/**
 * @tc.name: StopPipPip_003
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPipPip_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = PIP_ID_OK_1;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_1);
    EXPECT_EQ(ret, true);
    ret = webPattern.StopPip(0, 0, 0);
    EXPECT_EQ(ret, false);
#endif
}
 
/**
 * @tc.name: StopPipPip_004
 * @tc.desc: StopPip.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, StopPipPip_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webPattern;
    webPattern.delegate_ = nullptr;
    EXPECT_EQ(webPattern.delegate_, nullptr);
    bool init = false;
    uint32_t pipController = PIP_ID_OK_1;
    napi_env env = nullptr;
    PipInfo pipInfo{0, 0, 0, 0, PIP_WIDTH, PIP_HEIGHT};
    bool ret = webPattern.CreatePip(PIP_STATE_ENTER, env, init, pipController, pipInfo);
    EXPECT_EQ(ret, true);
    ret = webPattern.StartPip(PIP_ID_OK_2);
    EXPECT_EQ(ret, true);
    ret = webPattern.StopPip(0, 0, 0);
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CreateSnapshotImageFrameNode_001
 * @tc.desc: CreateSnapshotImageFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CreateSnapshotImageFrameNode_001, TestSize.Level1)
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
    EXPECT_EQ(NWeb::IsSnapshotPathValid("/data/storage/el2/base/cache/web/snapshot/web_frame_123456.png"), true);
    std::string snapshotPath = "/data/storage/el2/base/cache/web/snapshot/web_frame_123456.png";
    webPattern->CreateSnapshotImageFrameNode(snapshotPath);
    webPattern->RemoveSnapshotFrameNode();
    webPattern->RemoveSnapshotFrameNode();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnCssDisplayChangeEnabledUpdate_001
 * @tc.desc: OnCssDisplayChangeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnCssDisplayChangeEnabledUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnCssDisplayChangeEnabledUpdate(true);
#endif
}

/**
 * @tc.name: OnCssDisplayChangeEnabledUpdate_002
 * @tc.desc: OnCssDisplayChangeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnCssDisplayChangeEnabledUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnCssDisplayChangeEnabledUpdate(false);
#endif
}

/**
 * @tc.name: OnCssDisplayChangeEnabledUpdate_003
 * @tc.desc: OnCssDisplayChangeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnCssDisplayChangeEnabledUpdate_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnCssDisplayChangeEnabledUpdate(true);
#endif
}

/**
 * @tc.name: OnBypassVsyncConditionUpdate_001
 * @tc.desc: OnBypassVsyncConditionUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnBypassVsyncConditionUpdate_001, TestSize.Level1)
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
    webPattern->OnBypassVsyncConditionUpdate(WebBypassVsyncCondition::SCROLLBY_FROM_ZERO_OFFSET);
    EXPECT_EQ(webPattern->webBypassVsyncCondition_, WebBypassVsyncCondition::SCROLLBY_FROM_ZERO_OFFSET);
#endif
}

/**
 * @tc.name: SetDefaultBackgroundColor001
 * @tc.desc: SetDefaultBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetDefaultBackgroundColor001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(
            V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SetDefaultBackgroundColor();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);

    webPattern->OnBackgroundColorUpdate(Color::RED.GetValue());
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
#endif
}

/**
 * @tc.name: DarkModeBackgroundColor001
 * @tc.desc: Test DarkModeBackgroundColor001.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, DarkModeBackgroundColor001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(
            V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    ASSERT_NE(webPattern->GetHost()->GetRenderContext(), nullptr);
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_FALSE(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor());

    // Test that the default background color is based on darkMode() and forceDarkAccess()
    // when not set backgroundColor().
    webPattern->UpdateDarkMode(WebDarkMode::On);
    webPattern->UpdateForceDarkAccess(true);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLACK);

    webPattern->UpdateForceDarkAccess(false);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::WHITE);

    webPattern->UpdateDarkMode(WebDarkMode::Off);
    webPattern->UpdateForceDarkAccess(true);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::WHITE);

    webPattern->UpdateBackgroundColor(Color::RED.GetValue());
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::RED);

    webPattern->SetDefaultBackgroundColor();
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::WHITE);

    webPattern->UpdateDarkMode(WebDarkMode::On);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLACK);

    webPattern->UpdateBackgroundColor(Color::RED.GetValue());
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::RED);
#endif
}

/**
 * @tc.name: DarkModeBackgroundColor002
 * @tc.desc: Test DarkModeBackgroundColor002.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, DarkModeBackgroundColor002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(
            V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    ASSERT_NE(webPattern->GetHost()->GetRenderContext(), nullptr);
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_FALSE(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor());

    // Tests that when the backgroundColor is set to null or undefined,
    // it resets the backgroundColor to the default color.
    webPattern->SetDefaultBackgroundColor();
    webPattern->UpdateDarkMode(WebDarkMode::On);
    webPattern->UpdateForceDarkAccess(true);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLACK);

    webPattern->UpdateBackgroundColor(Color::RED.GetValue());
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::RED);

    webPattern->UpdateForceDarkAccess(false);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::RED);

    webPattern->SetDefaultBackgroundColor();
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::WHITE);

    webPattern->UpdateForceDarkAccess(true);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLACK);

    webPattern->UpdateBackgroundColor(Color::BLUE.GetValue());
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLUE);
#endif
}

/**
 * @tc.name: DarkModeBackgroundColor003
 * @tc.desc: Test DarkModeBackgroundColor003.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, DarkModeBackgroundColor003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(
            V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    ASSERT_NE(webPattern->GetHost()->GetRenderContext(), nullptr);
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_FALSE(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor());

    // In the case of richText, tests that when renderContext sets the backgroundColor, GetBackgroundColor() is null,
    // the defaultBackgroundColor will not be set.
    webPattern->GetHost()->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    webPattern->UpdateDarkMode(WebDarkMode::Off);
    webPattern->UpdateForceDarkAccess(true);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLUE);

    webPattern->OnBackgroundColorUpdate(Color::RED.GetValue());
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, false);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::RED);

    webPattern->SetDefaultBackgroundColor();
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::WHITE);

    webPattern->UpdateDarkMode(WebDarkMode::On);
    webPattern->OnModifyDone();
    EXPECT_EQ(webPattern->needSetDefaultBackgroundColor_, true);
    EXPECT_EQ(webPattern->GetHost()->GetRenderContext()->GetBackgroundColor(), Color::BLACK);
#endif
}

/**
 * @tc.name: CheckVisible_001
 * @tc.desc: CheckVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckVisible_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::INVISIBLE);

    EXPECT_FALSE(webPattern->CheckVisible());
#endif
}

/**
 * @tc.name: CheckVisible_002
 * @tc.desc: CheckVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckVisible_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    host->isActive_ = false;
    EXPECT_FALSE(webPattern->CheckVisible());
#endif
}

/**
 * @tc.name: CheckVisible_003
 * @tc.desc: CheckVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckVisible_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto *stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    frameNode->SetParent(nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto parent = host->GetParent();
    EXPECT_EQ(parent, nullptr);
    auto layoutProperty = host->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    host->isActive_ = true;

    EXPECT_TRUE(webPattern->CheckVisible());
#endif
}

/**
 * @tc.name: CheckVisible_004
 * @tc.desc: CheckVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckVisible_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto *stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
    host->isActive_ = true;

    auto parentNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(parentNode, nullptr);
    stack->Push(parentNode);
    frameNode->SetParent(parentNode);
    parentNode->SetWindowBoundary(true);

    EXPECT_TRUE(webPattern->CheckVisible());
#endif
}

/**
 * @tc.name: GetVisibleViewportAvoidHeight001
 * @tc.desc: GetVisibleViewportAvoidHeight.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetVisibleViewportAvoidHeight001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(
            V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    int32_t avoidHeight = webPattern->GetVisibleViewportAvoidHeight();
    EXPECT_EQ(avoidHeight, 0);

    webPattern->OnModifyDone();
    avoidHeight = webPattern->GetVisibleViewportAvoidHeight();
    EXPECT_EQ(avoidHeight, 0);
#endif
}
} // namespace OHOS::Ace::NG