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

#include <cstddef>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#define protected public
#define private public
#include "foundation/arkui/ace_engine/test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/web/web_pattern.h"
#include "frameworks/core/components_v2/inspector/textinput_composed_element.h"
#undef private
#undef protected
#include "test/mock/core/common/mock_theme_manager.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components/text_overlay/text_overlay_theme.h"
#include "frameworks/core/components_ng/pattern/web/web_model_ng.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NWeb;
using ScriptItems = std::map<std::string, std::vector<std::string>>;
using WeakPtr = std::weak_ptr<OHOS::Ace::PipelineBase>;
using ErrorCallback = std::function<void(const std::string&)>;

namespace OHOS::Ace::NG {

class NWebQuickMenuParamsNeMockFirst : public OHOS::NWeb::NWebQuickMenuParams {
private:
    int32_t xCoord_ = 0;
    int32_t yCoord_ = 0;
    int32_t width_ = 0;
    int32_t height_ = 0;
    int32_t editStateFlags_ = QM_EF_NONE;
    int32_t selectX_ = 100;
    int32_t selectY_ = 200;
    int32_t selectWidth_ = 150;
    int32_t selectHeight_ = 50;

public:
    int32_t GetXCoord() override
    {
        return xCoord_;
    }

    int32_t GetYCoord() override
    {
        return yCoord_;
    }

    int32_t GetWidth() override
    {
        return width_;
    }

    int32_t GetHeight() override
    {
        return height_;
    }

    int32_t GetEditStateFlags() override
    {
        return editStateFlags_;
    }

    int32_t GetSelectX() override
    {
        return selectX_;
    }

    int32_t GetSelectY() override
    {
        return selectY_;
    }

    int32_t GetSelectWidth() override
    {
        return selectWidth_;
    }

    int32_t GetSelectXHeight() override
    {
        return selectHeight_;
    }

    std::shared_ptr<NWebTouchHandleState> GetTouchHandleState(NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
};

class NWebQuickMenuParamsNeMockSecond : public OHOS::NWeb::NWebQuickMenuParams {
private:
    int32_t xCoord_ = 0;
    int32_t yCoord_ = 0;
    int32_t width_ = 0;
    int32_t height_ = 0;
    int32_t editStateFlags_ = QM_EF_NONE;
    int32_t selectX_ = 100;
    int32_t selectY_ = -10;
    int32_t selectWidth_ = 150;
    int32_t selectHeight_ = -10;

public:
    int32_t GetXCoord() override
    {
        return xCoord_;
    }

    int32_t GetYCoord() override
    {
        return yCoord_;
    }

    int32_t GetWidth() override
    {
        return width_;
    }

    int32_t GetHeight() override
    {
        return height_;
    }

    int32_t GetEditStateFlags() override
    {
        return editStateFlags_;
    }

    int32_t GetSelectX() override
    {
        return selectX_;
    }

    int32_t GetSelectY() override
    {
        return selectY_;
    }

    int32_t GetSelectWidth() override
    {
        return selectWidth_;
    }

    int32_t GetSelectXHeight() override
    {
        return selectHeight_;
    }

    std::shared_ptr<NWebTouchHandleState> GetTouchHandleState(NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
};

class NWebQuickMenuParamsNeMockThird : public OHOS::NWeb::NWebQuickMenuParams {
private:
    int32_t xCoord_ = 0;
    int32_t yCoord_ = 0;
    int32_t width_ = 0;
    int32_t height_ = 0;
    int32_t editStateFlags_ = QM_EF_NONE;
    int32_t selectX_ = 100;
    int32_t selectY_ = -10;
    int32_t selectWidth_ = 150;
    int32_t selectHeight_ = 200;

public:
    int32_t GetXCoord() override
    {
        return xCoord_;
    }

    int32_t GetYCoord() override
    {
        return yCoord_;
    }

    int32_t GetWidth() override
    {
        return width_;
    }

    int32_t GetHeight() override
    {
        return height_;
    }

    int32_t GetEditStateFlags() override
    {
        return editStateFlags_;
    }

    int32_t GetSelectX() override
    {
        return selectX_;
    }

    int32_t GetSelectY() override
    {
        return selectY_;
    }

    int32_t GetSelectWidth() override
    {
        return selectWidth_;
    }

    int32_t GetSelectXHeight() override
    {
        return selectHeight_;
    }

    std::shared_ptr<NWebTouchHandleState> GetTouchHandleState(NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
};

class NWebQuickMenuParamsNeMockForth : public OHOS::NWeb::NWebQuickMenuParams {
private:
    int32_t xCoord_ = 0;
    int32_t yCoord_ = 0;
    int32_t width_ = 0;
    int32_t height_ = 0;
    int32_t editStateFlags_ = QM_EF_NONE;
    int32_t selectX_ = 100;
    int32_t selectY_ = 20;
    int32_t selectWidth_ = 150;
    int32_t selectHeight_ = 200;

public:
    int32_t GetXCoord() override
    {
        return xCoord_;
    }

    int32_t GetYCoord() override
    {
        return yCoord_;
    }

    int32_t GetWidth() override
    {
        return width_;
    }

    int32_t GetHeight() override
    {
        return height_;
    }

    int32_t GetEditStateFlags() override
    {
        return editStateFlags_;
    }

    int32_t GetSelectX() override
    {
        return selectX_;
    }

    int32_t GetSelectY() override
    {
        return selectY_;
    }

    int32_t GetSelectWidth() override
    {
        return selectWidth_;
    }

    int32_t GetSelectXHeight() override
    {
        return selectHeight_;
    }

    std::shared_ptr<NWebTouchHandleState> GetTouchHandleState(NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
};

class NWebTouchHandleStateNeMockFirst : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 0;
    int32_t y_ = 0;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = 10;
    TouchHandleType touchHandleType_ = INVALID_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 0.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockSecond : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 0;
    int32_t y_ = 0;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = -10;
    TouchHandleType touchHandleType_ = INVALID_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 0.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockThird : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 0;
    int32_t y_ = 0;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = -300;
    TouchHandleType touchHandleType_ = INVALID_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 0.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockForth : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 10;
    int32_t y_ = 10;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = -300;
    TouchHandleType touchHandleType_ = INVALID_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 500.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockFifth : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 10;
    int32_t y_ = 10;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = -300;
    TouchHandleType touchHandleType_ = INVALID_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = -500.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockSixth : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 10;
    int32_t y_ = 10;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = 10;
    TouchHandleType touchHandleType_ = INVALID_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 500.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockSeventh : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 10;
    int32_t y_ = 10;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = 10;
    TouchHandleType touchHandleType_ = INSERT_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 0.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockEighth : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 10;
    int32_t y_ = 10;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = 10;
    TouchHandleType touchHandleType_ = INSERT_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = 0.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class NWebTouchHandleStateNeMockNineth : public OHOS::NWeb::NWebTouchHandleState {
private:
    int32_t touchHandleId_ = 0;
    int32_t x_ = 10;
    int32_t y_ = 10;
    int32_t viewPortX_ = 10;
    int32_t viewPortY_ = 10;
    TouchHandleType touchHandleType_ = INSERT_HANDLE;
    bool enable_ = false;
    float alpha_ = 1.0f;
    float edgeHeight_ = -1.0f;

public:
    int32_t GetTouchHandleId() override
    {
        return touchHandleId_;
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
        return viewPortX_;
    }

    int32_t GetViewPortY() override
    {
        return viewPortY_;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return touchHandleType_;
    }

    bool IsEnable() override
    {
        return enable_;
    }

    float GetAlpha() override
    {
        return alpha_;
    }

    float GetEdgeHeight() override
    {
        return edgeHeight_;
    }
};

class WebPatternNewBranchTestUT : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternNewBranchTestUT::SetUpTestCase() {}
void WebPatternNewBranchTestUT::TearDownTestCase() {}
void WebPatternNewBranchTestUT::SetUp()
{
    MockPipelineContext::SetUp();
}
void WebPatternNewBranchTestUT::TearDown()
{
    MockPipelineContext::TearDown();
}

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
 * @tc.name: ComputeClippedSelectionBound_001
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternNewBranchTestUT, ComputeClippedSelectionBound_001, TestSize.Level1)
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
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);

    auto manager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(manager);
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme = builder.Build(nullptr);
    EXPECT_NE(theme, nullptr);
    EXPECT_CALL(*manager, GetTheme(_)).WillRepeatedly(Return(theme));

    auto params = std::make_shared<NWebQuickMenuParamsNeMockFirst>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    params->GetSelectX();
    params->GetSelectY();
    params->GetSelectWidth();
    params->GetSelectXHeight();
    startHandle->GetViewPortX();
    startHandle->GetViewPortY();
    endHandle->GetViewPortX();
    endHandle->GetViewPortY();
    bool isNewAvoid = true;
    webPattern->ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_EQ(isNewAvoid, false);
    auto paramsone = std::make_shared<NWebQuickMenuParamsNeMockSecond>();
    auto startHandleone = std::make_shared<NWebTouchHandleStateNeMockSecond>();
    auto endHandleone = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    paramsone->GetSelectX();
    paramsone->GetSelectY();
    paramsone->GetSelectWidth();
    paramsone->GetSelectXHeight();
    startHandleone->GetViewPortX();
    startHandleone->GetViewPortY();
    endHandleone->GetViewPortX();
    endHandleone->GetViewPortY();
    webPattern->ComputeClippedSelectionBounds(paramsone, startHandleone, endHandleone, isNewAvoid);
    EXPECT_EQ(isNewAvoid, false);
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBound_002
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternNewBranchTestUT, ComputeClippedSelectionBound_002, TestSize.Level1)
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
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);

    MockPipelineContext::SetUp();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);

    auto params = std::make_shared<NWebQuickMenuParamsNeMockThird>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockSecond>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    params->GetSelectX();
    params->GetSelectY();
    params->GetSelectWidth();
    params->GetSelectXHeight();
    startHandle->GetViewPortX();
    startHandle->GetViewPortY();
    endHandle->GetViewPortX();
    endHandle->GetViewPortY();
    bool isNewAvoid = true;
    webPattern->ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();

    MockPipelineContext::SetUp();
    auto pipelineone = PipelineContext::GetCurrentContext();
    auto themeone = AceType::MakeRefPtr<MockThemeManager>();
    pipelineone->SetThemeManager(themeone);
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme1 = builder.Build(nullptr);
    EXPECT_CALL(*themeone, GetTheme(_)).WillRepeatedly(Return(theme1));
    auto paramsone = std::make_shared<NWebQuickMenuParamsNeMockForth>();
    auto startHandleone = std::make_shared<NWebTouchHandleStateNeMockThird>();
    auto endHandleone = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    paramsone->GetSelectX();
    paramsone->GetSelectY();
    paramsone->GetSelectWidth();
    paramsone->GetSelectXHeight();
    startHandleone->GetViewPortX();
    startHandleone->GetViewPortY();
    startHandleone->GetEdgeHeight();
    endHandleone->GetViewPortX();
    endHandleone->GetViewPortY();
    endHandleone->GetEdgeHeight();
    webPattern->ComputeClippedSelectionBounds(paramsone, startHandleone, endHandleone, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();

    MockPipelineContext::SetUp();
    auto pipelinetwo = PipelineContext::GetCurrentContext();
    auto themetwo = AceType::MakeRefPtr<MockThemeManager>();
    pipelinetwo->SetThemeManager(themetwo);
    DialogTheme::Builder builder1;
    RefPtr<DialogTheme> theme2 = builder1.Build(nullptr);
    EXPECT_CALL(*themetwo, GetTheme(_)).WillRepeatedly(Return(theme2));
    auto paramstwo = std::make_shared<NWebQuickMenuParamsNeMockForth>();
    auto startHandletwo = std::make_shared<NWebTouchHandleStateNeMockForth>();
    auto endHandletwo = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    paramstwo->GetSelectX();
    paramstwo->GetSelectY();
    paramstwo->GetSelectWidth();
    paramstwo->GetSelectXHeight();
    startHandletwo->GetViewPortX();
    startHandletwo->GetViewPortY();
    startHandletwo->GetEdgeHeight();
    endHandletwo->GetViewPortX();
    endHandletwo->GetViewPortY();
    startHandletwo->GetX();
    startHandletwo->GetY();
    webPattern->ComputeClippedSelectionBounds(paramstwo, startHandletwo, endHandletwo, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBound_006
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternNewBranchTestUT, ComputeClippedSelectionBound_003, TestSize.Level1)
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
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);

    MockPipelineContext::SetUp();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme1 = builder.Build(nullptr);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(theme1));
    auto params = std::make_shared<NWebQuickMenuParamsNeMockForth>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockFifth>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockSixth>();
    params->GetSelectX();
    params->GetSelectY();
    params->GetSelectWidth();
    params->GetSelectXHeight();
    startHandle->GetViewPortX();
    startHandle->GetViewPortY();
    startHandle->GetEdgeHeight();
    endHandle->GetViewPortX();
    endHandle->GetViewPortY();
    endHandle->GetEdgeHeight();
    endHandle->GetX();
    endHandle->GetY();
    bool isNewAvoid = true;
    webPattern->ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid_001
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternNewBranchTestUT, QuickMenuIsNeedNewAvoid_001, TestSize.Level1)
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
    auto params = std::make_shared<NWebQuickMenuParamsNeMockFirst>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    webPattern->QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    auto ret = webPattern->isQuickMenuMouseTrigger_;
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid_002
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternNewBranchTestUT, QuickMenuIsNeedNewAvoid_002, TestSize.Level1)
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
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    auto params = std::make_shared<NWebQuickMenuParamsNeMockFirst>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockSeventh>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockEighth>();
    startHandle->GetEdgeHeight();
    startHandle->GetTouchHandleId();
    endHandle->GetEdgeHeight();
    endHandle->GetTouchHandleId();
    params->GetSelectX();
    params->GetSelectY();
    params->GetSelectWidth();
    params->GetSelectXHeight();
    startHandle->GetViewPortX();
    startHandle->GetViewPortY();
    endHandle->GetViewPortX();
    endHandle->GetViewPortY();
    webPattern->QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(selectInfo.isNewAvoid, false);
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid_003
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternNewBranchTestUT, QuickMenuIsNeedNewAvoid_003, TestSize.Level1)
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
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    auto params = std::make_shared<NWebQuickMenuParamsNeMockFirst>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockSeventh>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockNineth>();
    startHandle->GetEdgeHeight();
    startHandle->GetTouchHandleId();
    endHandle->GetEdgeHeight();
    params->GetSelectX();
    params->GetSelectY();
    params->GetSelectWidth();
    params->GetSelectXHeight();
    startHandle->GetViewPortX();
    startHandle->GetViewPortY();
    endHandle->GetViewPortX();
    endHandle->GetViewPortY();
    webPattern->QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(selectInfo.isNewAvoid, false);
#endif
}
} // namespace OHOS::Ace::NG
