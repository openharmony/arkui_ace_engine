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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "foundation/arkui/ace_engine/frameworks/core/common/ai/image_analyzer_manager.h"
#include "foundation/arkui/ace_engine/interfaces/inner_api/ace/ai/image_analyzer.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/pattern/web/web_select_overlay.h"
#undef protected
#undef private
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "nweb.h"
#include "nweb_handler.h"
#include "core/components/web/web_event.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"
#include "core/components_v2/inspector/inspector_constants.h"

#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;
using namespace OHOS::NWeb;
using namespace OHOS::Rosen;

namespace {
constexpr int32_t COORDINATEID_UN = -1;
constexpr int32_t COORDINATEID_FA = 1;
constexpr int32_t POSITION_UN = 10;
constexpr int32_t POSITIONX_FA = 0;
constexpr int32_t POSITIONY_FA = 1;
constexpr int32_t VIEWPORT = 0;
constexpr int32_t DEVICE_HEIGHT = 1280;
constexpr float ALPHA_UN = -0.5;
constexpr float ALPHA_FA = 0.5;
constexpr float EDGEHEIGHT_UN = 0.0;
constexpr float EDGEHEIGHT_FA = 5.0;
constexpr float EDGEHEIGHT_TR = 1.0;
constexpr float EDGE_HEIGHT = 30.0;
constexpr float NEW_EPSILON = 0.001f;
bool g_isEnable = false;
bool g_isLongPress = false;
float g_alpha = 0;
int32_t g_Y = 1;
float g_height = 0;
int32_t g_editStateFlags = 0;
std::shared_ptr<NWebTouchHandleState> g_insertHandle = nullptr;
std::shared_ptr<NWebTouchHandleState> g_startSelectionHandle = nullptr;
std::shared_ptr<NWebTouchHandleState> g_endSelectionHandle = nullptr;
} // namespace

namespace OHOS::NWeb {
class MockNWebTouchHandleStateImpl : public NWebTouchHandleState {
public:
    MockNWebTouchHandleStateImpl() = default;
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
        return g_alpha;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight_;
    };

private:
    float edgeHeight_ = EDGE_HEIGHT;
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
        return g_isLongPress;
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
RefPtr<WebPattern> g_webPattern = nullptr;

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

class NWebQuickMenuParamsMockImpl : public OHOS::NWeb::NWebQuickMenuParams {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (override));
    MOCK_METHOD(int32_t, GetYCoord, (), (override));
    MOCK_METHOD(int32_t, GetWidth, (), (override));
    MOCK_METHOD(int32_t, GetHeight, (), (override));
    MOCK_METHOD(int32_t, GetEditStateFlags, (), (override));
    MOCK_METHOD(int32_t, GetSelectX, (), (override));
    MOCK_METHOD(int32_t, GetSelectY, (), (override));
    MOCK_METHOD(int32_t, GetSelectWidth, (), (override));
    MOCK_METHOD(int32_t, GetSelectXHeight, (), (override));
    MOCK_METHOD(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState>, GetTouchHandleState,
        (OHOS::NWeb::NWebTouchHandleState::TouchHandleType type), (override));
    MOCK_METHOD(bool, GetIsLongPressActived, (), (override));
};

class NWebQuickMenuParamsDummy : public OHOS::NWeb::NWebQuickMenuParams {
public:
    int32_t GetXCoord() override
    {
        return 0;
    };
    int32_t GetYCoord() override
    {
        return 0;
    };
    int32_t GetWidth() override
    {
        return 0;
    };
    int32_t GetHeight() override
    {
        return 0;
    };
    int32_t GetEditStateFlags() override
    {
        return 0;
    };
    int32_t GetSelectX() override
    {
        return selectX;
    };
    int32_t GetSelectY() override
    {
        return selectY;
    };
    int32_t GetSelectWidth() override
    {
        return width;
    };
    int32_t GetSelectXHeight() override
    {
        return height;
    };
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> GetTouchHandleState(
        OHOS::NWeb::NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
    bool GetIsLongPressActived() override
    {
        return isLongPresseActived;
    }

private:
    int32_t selectX = 100;
    int32_t selectY = 200;
    int32_t width = 150;
    int32_t height = 50;
    bool isLongPresseActived = false;
};

class NWebTouchHandleStateMockImpl : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateMockImpl() = default;
    MOCK_METHOD(int32_t, GetTouchHandleId, (), (override));
    MOCK_METHOD(int32_t, GetX, (), (override));
    MOCK_METHOD(int32_t, GetY, (), (override));
    MOCK_METHOD(int32_t, GetViewPortX, (), (override));
    MOCK_METHOD(int32_t, GetViewPortY, (), (override));
    MOCK_METHOD(TouchHandleType, GetTouchHandleType, (), (override));
    MOCK_METHOD(bool, IsEnable, (), (override));
    MOCK_METHOD(float, GetAlpha, (), (override));
    MOCK_METHOD(float, GetEdgeHeight, (), (override));
};

class NWebTouchHandleStateDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateDummy() = default;
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

class NWebTouchHandleStateEndDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateEndDummy() = default;
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
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight;
    };

private:
    float edgeHeight = 10.0;
};

class NWebTouchHandleStateBeginDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateBeginDummy() = default;
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
        return edgeHeight;
    };

private:
    float edgeHeight = 10.0;
};

class WebSelectOverlayTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

#ifdef OHOS_STANDARD_SYSTEM
class NWebTouchHandleStateMock : public NWebTouchHandleState {
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
        return g_Y;
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
        return g_isEnable;
    }

    float GetAlpha() override
    {
        return g_alpha;
    }

    float GetEdgeHeight() override
    {
        return g_height;
    }
};

class NWebQuickMenuParamsMock : public NWebQuickMenuParams {
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

class NWebTouchHandleStateUN : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateUN() = default;
    int32_t GetTouchHandleId() override
    {
        return COORDINATEID_UN;
    };
    int32_t GetX() override
    {
        return POSITION_UN;
    };
    int32_t GetY() override
    {
        return POSITION_UN;
    };
    int32_t GetViewPortX() override
    {
        return VIEWPORT;
    };
    int32_t GetViewPortY() override
    {
        return VIEWPORT;
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
        return ALPHA_UN;
    };
    float GetEdgeHeight() override
    {
        return EDGEHEIGHT_UN;
    };
};

class NWebTouchHandleStateFA : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateFA() = default;
    int32_t GetTouchHandleId() override
    {
        return COORDINATEID_FA;
    };
    int32_t GetX() override
    {
        return POSITIONX_FA;
    };
    int32_t GetY() override
    {
        return POSITIONY_FA;
    };
    int32_t GetViewPortX() override
    {
        return VIEWPORT;
    };
    int32_t GetViewPortY() override
    {
        return VIEWPORT;
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
        return ALPHA_FA;
    };
    float GetEdgeHeight() override
    {
        return EDGEHEIGHT_FA;
    };
};

class NWebTouchHandleStateTR : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateTR() = default;
    int32_t GetTouchHandleId() override
    {
        return COORDINATEID_UN;
    };
    int32_t GetX() override
    {
        return POSITIONX_FA;
    };
    int32_t GetY() override
    {
        return POSITIONY_FA;
    };
    int32_t GetViewPortX() override
    {
        return VIEWPORT;
    };
    int32_t GetViewPortY() override
    {
        return VIEWPORT;
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
        return ALPHA_FA;
    };
    float GetEdgeHeight() override
    {
        return EDGEHEIGHT_TR;
    };
};

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
#endif

void WebSelectOverlayTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    stack->Push(frameNode);

    g_webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_webPattern);
    g_webPattern->SetWebSrc(src);
    g_webPattern->SetWebController(controller);
#endif
}

void WebSelectOverlayTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern = nullptr;
#endif
}
void WebSelectOverlayTest::SetUp() {}
void WebSelectOverlayTest::TearDown() {}

std::vector<MenuOptionsParam> CreateMenuOptionsV2(const std::vector<NG::MenuItemParam>&)
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

bool HandleMenuItemClickV2(const NG::MenuItemParam& item)
{
    std::cout << "Clicked on menu item: " << item.ToString() << std::endl;
    item.menuOptionsParam.action(item.menuOptionsParam.id);
    return true;
}

std::vector<MenuOptionsParam> PrepareMenuOptionsV2(const std::vector<NG::MenuItemParam>&)
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

bool InitSafeAreaManager(RefPtr<PipelineContext>& pipeline)
{
    if (!pipeline) {
        return false;
    }
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = DEVICE_HEIGHT - 1;
    insetBottom.end = DEVICE_HEIGHT;
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreaManager->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    safeAreaManager->systemSafeArea_.bottom_ = SafeAreaInsets::Inset(insetBottom);
    pipeline->safeAreaManager_ = safeAreaManager;
    return true;
}

bool InitLayoutWrapper(RefPtr<LayoutWrapperNode>& layoutWrapper, RefPtr<GeometryNode>& geometryNode,
    std::shared_ptr<SelectOverlayInfo>& infoPtr)
{
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    if (!selectOverlayNode) {
        return false;
    }
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    if (!pattern) {
        return false;
    }
    if (!geometryNode) {
        return false;
    }
    geometryNode->SetFrameSize(SizeF(100.0f, 50.0f));
    geometryNode->SetFrameOffset(OffsetF(0.0f, 0.0f));
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    return true;
}

/**
 * @tc.name: RunQuickMenu_001
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RunQuickMenu_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    bool result = overlay.RunQuickMenu(params, callback);
    MockPipelineContext::TearDown();
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: RunQuickMenu_002
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RunQuickMenu_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    g_isLongPress = true;
    g_isEnable = true;
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    overlay.isQuickMenuMouseTrigger_ = true;
    bool result = overlay.RunQuickMenu(params, callback);
    g_isLongPress = false;
    g_isEnable = false;
    MockPipelineContext::TearDown();
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: RunQuickMenu_003
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RunQuickMenu_003, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    overlay.isQuickMenuMouseTrigger_ = true;
    g_isEnable = true;
    g_insertHandle = std::make_shared<NWebTouchHandleStateMock>();
    bool result = overlay.RunQuickMenu(params, callback);
    g_isEnable = false;
    MockPipelineContext::TearDown();
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_001
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    overlay.selectTemporarilyHidden_ = true;
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.insertHandle_, nullptr);
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_002
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest_002, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    overlay.selectTemporarilyHidden_ = true;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.insertHandle_, nullptr);
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_003
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest_003, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.insertHandle_, nullptr);
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_004
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest_004, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.insertHandle_, nullptr);
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_005
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest_005, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.selectOverlayDragging_ = false;
    overlay.isShowHandle_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.insertHandle_, nullptr);
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest_006
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest_006, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.selectOverlayDragging_ = true;
    overlay.isShowHandle_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.insertHandle_, nullptr);
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
#endif
}

/**
 * @tc.name: OnTouchSelectionChanged_007
 * @tc.desc: OnTouchSelectionChanged
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChanged_007, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(endSelectionHandle, nullptr);
    EXPECT_CALL(*insertHandle, IsEnable()).WillRepeatedly(Return(true));
    EXPECT_CALL(*startSelectionHandle, IsEnable()).WillRepeatedly(Return(false));
    EXPECT_CALL(*endSelectionHandle, IsEnable()).WillRepeatedly(Return(true));
    overlay.isShowHandle_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

/**
 * @tc.name: OnTouchSelectionChanged_008
 * @tc.desc: OnTouchSelectionChanged
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChanged_008, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(endSelectionHandle, nullptr);
    EXPECT_CALL(*insertHandle, IsEnable()).WillRepeatedly(Return(true));
    EXPECT_CALL(*startSelectionHandle, IsEnable()).WillRepeatedly(Return(false));
    EXPECT_CALL(*endSelectionHandle, IsEnable()).WillRepeatedly(Return(false));
    overlay.isShowHandle_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

/**
 * @tc.name: OnTouchSelectionChanged_009
 * @tc.desc: OnTouchSelectionChanged
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChanged_009, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWeb::NWebTouchHandleStateMock>();
    ASSERT_NE(endSelectionHandle, nullptr);
    EXPECT_CALL(*insertHandle, IsEnable()).WillRepeatedly(Return(false));
    EXPECT_CALL(*startSelectionHandle, IsEnable()).WillRepeatedly(Return(true));
    EXPECT_CALL(*endSelectionHandle, IsEnable()).WillRepeatedly(Return(true));
    overlay.isShowHandle_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest010
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebSelectOverlay g_overlay(g_webPattern);
    g_overlay.selectOverlayDragging_ = true;
    g_overlay.OnTouchSelectionChanged(g_insertHandle, g_startSelectionHandle, g_endSelectionHandle);
    g_endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_overlay.OnTouchSelectionChanged(g_insertHandle, g_startSelectionHandle, g_endSelectionHandle);
    EXPECT_EQ(g_overlay.insertHandle_, nullptr);
    g_insertHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_startSelectionHandle.reset();
    g_startSelectionHandle = nullptr;
    g_endSelectionHandle.reset();
    g_endSelectionHandle = nullptr;
    g_overlay.OnTouchSelectionChanged(g_insertHandle, g_startSelectionHandle, g_endSelectionHandle);
    g_overlay.OnTouchSelectionChanged(g_insertHandle, g_startSelectionHandle, g_endSelectionHandle);
    g_insertHandle.reset();
    g_insertHandle = nullptr;
    g_endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_startSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_overlay.OnTouchSelectionChanged(g_insertHandle, g_startSelectionHandle, g_endSelectionHandle);
#endif
}

/**
 * @tc.name: RegisterSelectOverlayEvent
 * @tc.desc: RegisterSelectOverlayEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RegisterSelectOverlayEvent, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectOverlayInfo selectInfo;
    overlay.RegisterSelectOverlayEvent(selectInfo);
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_001
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSelectHandleInfo_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.isCurrentStartHandleDragging_ = true;
    overlay.UpdateSelectHandleInfo();
    EXPECT_FALSE(overlay.IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_002
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSelectHandleInfo_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.isCurrentStartHandleDragging_ = false;
    overlay.UpdateSelectHandleInfo();
    EXPECT_TRUE(overlay.IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_003
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSelectHandleInfo_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateTestImpl>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.isCurrentStartHandleDragging_ = true;
    overlay.UpdateSelectHandleInfo();
    EXPECT_TRUE(overlay.IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo_004
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSelectHandleInfo_004, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.isCurrentStartHandleDragging_ = false;
    overlay.UpdateSelectHandleInfo();
    EXPECT_FALSE(overlay.IsSelectHandleReverse());
#endif
}

/**
 * @tc.name: IsSelectHandleReverse001
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, IsSelectHandleReverse001, TestSize.Level2)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateDummy>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.IsSelectHandleReverse();
    EXPECT_EQ(overlay.IsSelectHandleReverse(), true);
#endif
}

/**
 * @tc.name: IsSelectHandleReverse002
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, IsSelectHandleReverse002, TestSize.Level2)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.IsSelectHandleReverse();
    EXPECT_EQ(overlay.IsSelectHandleReverse(), true);
#endif
}

/**
 * @tc.name: IsSelectHandleReverse003
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, IsSelectHandleReverse003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    overlay.IsSelectHandleReverse();
    EXPECT_EQ(overlay.IsSelectHandleReverse(), false);
#endif
}

/**
 * @tc.name: ChangeHandleHeight001
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ChangeHandleHeight001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    GestureEvent event;
    overlay.ChangeHandleHeight(event, true);
#endif
}

/**
 * @tc.name: IsSelectHandleReverse003
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ChangeHandleHeight002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    GestureEvent event;
    overlay.ChangeHandleHeight(event, false);
#endif
}

/**
 * @tc.name: GetTouchHandleOverlayTypeTest001
 * @tc.desc: Test GetTouchHandleOverlayType.
 * @tc.type: FUNC
 */

HWTEST_F(WebSelectOverlayTest, GetTouchHandleOverlayTypeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebSelectOverlay g_overlay(g_webPattern);
    std::shared_ptr<NWebQuickMenuParams> params = std::make_shared<NWebQuickMenuParamsMock>();
    std::shared_ptr<NWebQuickMenuCallback> callback = std::make_shared<NWebQuickMenuCallbackMock>();
    bool result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);

    g_insertHandle = std::make_shared<NWebTouchHandleStateMock>();
    result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);

    g_endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);

    g_startSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);

    result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);

    g_insertHandle.reset();
    g_insertHandle = nullptr;
    result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);

    g_endSelectionHandle.reset();
    g_endSelectionHandle = nullptr;
    result = g_overlay.RunQuickMenu(params, callback);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: IsTouchHandleValidTest
 * @tc.desc: IsTouchHandleValid
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, IsTouchHandleValidTest, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle = nullptr;
    auto expect = overlay.IsTouchHandleValid(handle);
    EXPECT_EQ(expect, false);
#endif
}

/**
 * @tc.name: IsTouchHandleValid002
 * @tc.desc: Test IsTouchHandleValid.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, IsTouchHandleValid002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebSelectOverlay g_overlay(g_webPattern);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle = nullptr;
    bool result = g_overlay.IsTouchHandleValid(handle);
    EXPECT_FALSE(result);
    handle = std::make_shared<NWebTouchHandleStateMock>();
    result = g_overlay.IsTouchHandleValid(handle);
    EXPECT_FALSE(result);
    g_isEnable = true;
    result = g_overlay.IsTouchHandleValid(handle);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: RegisterSelectOverLayOnClose001
 * @tc.desc: Test RegisterSelectOverLayOnClose.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RegisterSelectOverLayOnClose001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    overlay.RegisterSelectOverLayOnClose(selectInfo);
    selectInfo.onClose(false);
#endif
}

/**
 * @tc.name: RegisterSelectOverLayOnClose002
 * @tc.desc: Test RegisterSelectOverLayOnClose.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RegisterSelectOverLayOnClose002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    overlay.RegisterSelectOverLayOnClose(selectInfo);
    selectInfo.onClose(true);
#endif
}

/**
 * @tc.name: CheckHandles_001
 * @tc.desc: CheckHandles.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, CheckHandles_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectHandleInfo selectHandleInfo;
    auto handle_ = std::make_shared<NWebTouchHandleStateUN>();
    handle_->GetAlpha();
    overlay.CheckHandles(selectHandleInfo, handle_);
    EXPECT_TRUE(selectHandleInfo.isShow);
#endif
}

/**
 * @tc.name: CheckHandles_002
 * @tc.desc: CheckHandles.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, CheckHandles_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectHandleInfo selectHandleInfo;
    auto handle_ = std::make_shared<NWebTouchHandleStateFA>();
    handle_->GetAlpha();
    handle_->GetY();
    handle_->GetEdgeHeight();
    overlay.CheckHandles(selectHandleInfo, handle_);
    EXPECT_TRUE(selectHandleInfo.isShow);
#endif
}

/**
 * @tc.name: CheckHandles_003
 * @tc.desc: CheckHandles.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, CheckHandles_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectHandleInfo selectHandleInfo;
    auto handle_ = std::make_shared<NWebTouchHandleStateTR>();
    handle_->GetAlpha();
    handle_->GetY();
    handle_->GetEdgeHeight();
    overlay.CheckHandles(selectHandleInfo, handle_);
    EXPECT_TRUE(selectHandleInfo.isShow);
#endif
}

/**
 * @tc.name: CheckHandles_004
 * @tc.desc: CheckHandles
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, CheckHandles_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);

    auto handle = std::make_shared<NWeb::CustomNWebTouchHandleState>();
    handle->SetAlpha(0.5);
    handle->SetY(10);
    handle->SetEdgeHeight(5);

    SelectHandleInfo handleInfo;
    overlay.CheckHandles(handleInfo, handle);

    EXPECT_TRUE(handleInfo.isShow);
#endif
}

/**
 * @tc.name: CheckHandles_005
 * @tc.desc: CheckHandles
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, CheckHandles_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);

    auto handle = std::make_shared<NWeb::CustomNWebTouchHandleState>();
    handle->SetAlpha(1.2);
    handle->SetY(10);
    handle->SetEdgeHeight(5);

    SelectHandleInfo handleInfo;
    overlay.CheckHandles(handleInfo, handle);
    handle->SetEdgeHeight(0);
    overlay.CheckHandles(handleInfo, handle);
#endif
}

/**
 * @tc.name: ComputeTouchHandleRectTest
 * @tc.desc: ComputeTouchHandleRect
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeTouchHandleRectTest, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);

    auto touchHandle = std::make_shared<NWeb::CustomNWebTouchHandleState>();
    touchHandle->SetX(10.0);
    touchHandle->SetY(20.0);
    touchHandle->SetEdgeHeight(5.0);

    RectF paintRect = overlay.ComputeTouchHandleRect(touchHandle);

    EXPECT_FLOAT_EQ(paintRect.Width(), SelectHandleInfo::GetDefaultLineWidth().ConvertToPx());
    EXPECT_FLOAT_EQ(paintRect.Height(), 5);
#endif
}

/**
 * @tc.name: OnMenuItemAction_001
 * @tc.desc: OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnMenuItemAction_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    overlay.SetMenuOptions(selectInfo, params, callback);
    overlay.OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
#endif
}

/**
 * @tc.name: OnMenuItemAction_002
 * @tc.desc: OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnMenuItemAction_002, TestSize.Level1)
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
    std::string type_ = "image/png";
    webPattern->OnModifyDone();
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    overlay.SetMenuOptions(selectInfo, params, callback);
    overlay.OnMenuItemAction(OptionMenuActionId::CUT, OptionMenuType::TOUCH_MENU);
#endif
}

/**
 * @tc.name: OnMenuItemAction_003
 * @tc.desc: OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnMenuItemAction_003, TestSize.Level1)
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
    std::string type_ = "image/png";
    webPattern->OnModifyDone();
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    auto flags = g_editStateFlags;
    g_editStateFlags = 0;
    overlay.SetMenuOptions(selectInfo, params, callback);
    overlay.OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(overlay.quickMenuCallback_, callback);
    overlay.OnMenuItemAction(OptionMenuActionId::ASK_CELIA, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(overlay.isShowHandle_, false);
    g_editStateFlags = flags;
#endif
}

/**
 * @tc.name: OnMenuItemActionTest005
 * @tc.desc: Test OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnMenuItemActionTest005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebSelectOverlay g_overlay(g_webPattern);
    g_webPattern->GetCoordinatePoint();
    std::shared_ptr<NWebTouchHandleState> touchHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_overlay.ComputeTouchHandleRect(touchHandle);
    g_Y = -1;
    g_overlay.ComputeTouchHandleRect(touchHandle);

    std::shared_ptr<NWebQuickMenuParams> params = std::make_shared<NWebQuickMenuParamsMock>();
    std::shared_ptr<NWebQuickMenuCallback> callback = std::make_shared<NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    g_overlay.SetMenuOptions(selectInfo, params, callback);
    EXPECT_FALSE(selectInfo.menuInfo.showCut);
    g_editStateFlags = OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_CUT;
    g_overlay.SetMenuOptions(selectInfo, params, callback);
    g_editStateFlags = OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY;
    g_overlay.SetMenuOptions(selectInfo, params, callback);
    g_editStateFlags = OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_PASTE;
    g_overlay.SetMenuOptions(selectInfo, params, callback);
    g_editStateFlags = OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_SELECT_ALL;
    g_overlay.SetMenuOptions(selectInfo, params, callback);
    g_overlay.OnMenuItemAction(OptionMenuActionId::SELECT_ALL, OptionMenuType::TOUCH_MENU);
    g_overlay.OnMenuItemAction(OptionMenuActionId::CAMERA_INPUT, OptionMenuType::TOUCH_MENU);
    g_overlay.OnMenuItemAction(OptionMenuActionId::DISAPPEAR, OptionMenuType::TOUCH_MENU);
#endif
}

/**
 * @tc.name: StartListenSelectOverlayParentScrollTest001
 * @tc.desc: StartListenSelectOverlayParentScroll
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, StartListenSelectOverlayParentScrollTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);

    MockPipelineContext::SetUp();
    overlay.scrollableParentInfo_.hasParent = true;
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_FALSE(overlay.scrollableParentInfo_.hasParent);

    overlay.scrollableParentInfo_.hasParent = false;
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_FALSE(overlay.scrollableParentInfo_.hasParent);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: StartListenSelectOverlayParentScrollTest002
 * @tc.desc: StartListenSelectOverlayParentScroll
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, StartListenSelectOverlayParentScrollTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);
    MockPipelineContext::SetUp();
    overlay.scrollableParentInfo_.parentIds.push_back(1);
    overlay.scrollableParentInfo_.hasParent = true;

    overlay.StartListenSelectOverlayParentScroll(frameNode);
    overlay.scrollableParentInfo_.parentIds.clear();
    EXPECT_TRUE(webPattern->scrollableParentInfo_.hasParent);
    frameNode->tag_ = "parent1";
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_TRUE(webPattern->scrollableParentInfo_.hasParent);
    frameNode->tag_ = "parent";
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_TRUE(webPattern->scrollableParentInfo_.hasParent);
    frameNode->SetParent(nullptr);
    frameNode->tag_ = "parent1";
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_TRUE(webPattern->scrollableParentInfo_.hasParent);
    frameNode->tag_ = "parent";
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_TRUE(webPattern->scrollableParentInfo_.hasParent);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: StartListenSelectOverlayParentScrollTest003
 * @tc.desc: StartListenSelectOverlayParentScroll
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, StartListenSelectOverlayParentScrollTest003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);
    auto parentNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollablePatternDummy>(); });
    ASSERT_NE(parentNode, nullptr);
    stack->Push(parentNode);
    frameNode->SetParent(parentNode);
    MockPipelineContext::SetUp();
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto parent = host->GetParent();
    ASSERT_NE(parent, nullptr);

    overlay.scrollableParentInfo_.parentIds.push_back(1);
    overlay.scrollableParentInfo_.hasParent = true;

    overlay.StartListenSelectOverlayParentScroll(frameNode);
    overlay.scrollableParentInfo_.parentIds.clear();
    EXPECT_TRUE(overlay.scrollableParentInfo_.hasParent);
    parent->tag_ = "parent1";
    frameNode->SetParent(parent);
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_TRUE(overlay.scrollableParentInfo_.hasParent);
    parent->tag_ = "parent";
    frameNode->SetParent(parent);
    overlay.StartListenSelectOverlayParentScroll(frameNode);
    EXPECT_TRUE(overlay.scrollableParentInfo_.hasParent);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: RegisterSelectOverlayParentScrollCallbackTest001
 * @tc.desc: RegisterSelectOverlayParentScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RegisterSelectOverlayParentScrollCallbackTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);
    MockPipelineContext::SetUp();
    int32_t parentId = 1;
    int32_t callbackId = 2;
    overlay.RegisterSelectOverlayParentScrollCallback(parentId, callbackId);
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto context = host->GetContext();
    EXPECT_NE(context, nullptr);
    auto manager = context->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    auto parentIt = manager->parentScrollCallbacks_.find(parentId);
    auto& callbackMap = parentIt->second;
    auto callbackIt = callbackMap.find(callbackId);
    auto& callback = callbackIt->second;
    Axis axis = Axis::VERTICAL;
    float offset = 0.0f;
    int32_t source = SCROLL_FROM_START;
    callback(axis, offset, source);
    source = -1;
    callback(axis, offset, source);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: RegisterSelectOverlayParentScrollCallbackTest002
 * @tc.desc: RegisterSelectOverlayParentScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RegisterSelectOverlayParentScrollCallbackTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);

    int32_t callbackId = 2;
    int32_t nonExistentParentId = 999;
    overlay.RegisterSelectOverlayParentScrollCallback(nonExistentParentId, callbackId);
#endif
}

/**
 * @tc.name: RegisterSelectOverlayParentScrollCallbackTest003
 * @tc.desc: RegisterSelectOverlayParentScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RegisterSelectOverlayParentScrollCallbackTest003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);

    int32_t anotherParentId = 3;
    int32_t anotherCallbackId = 4;
    overlay.RegisterSelectOverlayParentScrollCallback(anotherParentId, anotherCallbackId);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_000
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_000, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = true;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);

    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = false;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = false;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(overlay.selectTemporarilyHidden_, hide);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_001
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(overlay.selectTemporarilyHidden_, hide);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_002
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    bool hide = false;
    bool isScroll = false;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_EQ(overlay.selectTemporarilyHidden_, hide);
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_EQ(overlay.selectTemporarilyHidden_, hide);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_003
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_004
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_004, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    bool hide = true;
    bool isScroll = true;
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_005
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_005, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    bool hide = false;
    bool isScroll = true;
    overlay.dropParams_ = std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    ASSERT_NE(overlay.dropParams_, nullptr);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_006
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_006, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    bool hide = false;
    bool isScroll = true;
    overlay.dropParams_ = std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    ASSERT_NE(overlay.dropParams_, nullptr);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(overlay.dropParams_, nullptr);
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    auto info = overlay.webSelectInfo_;
    info.menuInfo.menuIsShow = true;
    overlay.webSelectInfo_ = info;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    MockPipelineContext::TearDown();
    EXPECT_NE(overlay.dropParams_, nullptr);
#endif
}

/**
 * @tc.name: HideHandleAndQuickMenuIfNecessary_007
 * @tc.desc: HideHandleAndQuickMenuIfNecessary.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HideHandleAndQuickMenuIfNecessary_007, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    bool hide = false;
    bool isScroll = true;
    overlay.dropParams_ = std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    ASSERT_NE(overlay.dropParams_, nullptr);
    auto insertHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    insertHandle->isEnable_ = false;
    overlay.insertHandle_ = insertHandle;
    EXPECT_NE(overlay.insertHandle_, nullptr);
    auto startSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    startSelectionHandle->isEnable_ = true;
    startSelectionHandle->alpha_ = 1;
    startSelectionHandle->y_ = 0;
    overlay.startSelectionHandle_ = startSelectionHandle;
    EXPECT_NE(overlay.startSelectionHandle_, nullptr);
    auto endSelectionHandle = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMockDummy>();
    endSelectionHandle->isEnable_ = true;
    endSelectionHandle->alpha_ = 1;
    endSelectionHandle->y_ = 0;
    overlay.endSelectionHandle_ = endSelectionHandle;
    EXPECT_NE(overlay.endSelectionHandle_, nullptr);
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_NE(overlay.dropParams_, nullptr);
    overlay.startSelectionHandle_ = startSelectionHandle;
    overlay.endSelectionHandle_ = endSelectionHandle;
    auto info = overlay.webSelectInfo_;
    info.menuInfo.menuIsShow = false;
    overlay.webSelectInfo_ = info;
    overlay.HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    EXPECT_FALSE(overlay.webSelectInfo_.isNewAvoid);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnParentScrollStartOrEndCallback_001
 * @tc.desc: OnParentScrollStartOrEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnParentScrollStartOrEndCallback_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    WebSelectOverlay overlay(g_webPattern);
    MockPipelineContext::SetUp();
    overlay.selectTemporarilyHidden_ = true;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    overlay.OnParentScrollStartOrEndCallback(false);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.selectTemporarilyHiddenByScroll_, true);
#endif
}

/**
 * @tc.name: OnParentScrollStartOrEndCallback_002
 * @tc.desc: OnParentScrollStartOrEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnParentScrollStartOrEndCallback_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    WebSelectOverlay overlay(g_webPattern);
    MockPipelineContext::SetUp();
    overlay.selectTemporarilyHidden_ = true;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    overlay.OnParentScrollStartOrEndCallback(true);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.selectTemporarilyHiddenByScroll_, false);
#endif
}

/**
 * @tc.name: OnParentScrollStartOrEndCallback_003
 * @tc.desc: OnParentScrollStartOrEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnParentScrollStartOrEndCallback_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    WebSelectOverlay overlay(g_webPattern);
    MockPipelineContext::SetUp();
    overlay.selectTemporarilyHidden_ = true;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    overlay.OnParentScrollStartOrEndCallback(true);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.selectTemporarilyHiddenByScroll_, false);
#endif
}

/**
 * @tc.name: OnParentScrollStartOrEndCallback_004
 * @tc.desc: OnParentScrollStartOrEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnParentScrollStartOrEndCallback_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(g_webPattern);
    overlay.selectTemporarilyHidden_ = false;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    overlay.OnParentScrollStartOrEndCallback(true);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.selectTemporarilyHiddenByScroll_, false);
#endif
}

/**
 * @tc.name: WebPatternOnParentScrollStartOrEndCallbackTest001
 * @tc.desc: OnParentScrollStartOrEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, WebPatternOnParentScrollStartOrEndCallbackTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(g_webPattern);
    overlay.selectTemporarilyHidden_ = true;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    overlay.OnParentScrollStartOrEndCallback(false);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.selectTemporarilyHiddenByScroll_, true);
#endif
}

/**
 * @tc.name: WebPatternOnParentScrollStartOrEndCallbackTest002
 * @tc.desc: OnParentScrollStartOrEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, WebPatternOnParentScrollStartOrEndCallbackTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(g_webPattern);
    overlay.selectTemporarilyHidden_ = true;
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSelectOverlayManager();
    EXPECT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    EXPECT_NE(current, nullptr);
    overlay.OnParentScrollStartOrEndCallback(false);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.selectTemporarilyHiddenByScroll_, true);
#endif
}

/**
 * @tc.name: StopListenSelectOverlayParentScroll
 * @tc.desc: StopListenSelectOverlayParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, StopListenSelectOverlayParentScroll, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    overlay.StopListenSelectOverlayParentScroll(frameNode);
#endif
}

/**
 * @tc.name: ComputeMouseClippedSelectionBounds
 * @tc.desc: ComputeMouseClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeMouseClippedSelectionBounds, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    int32_t startX = 10;
    int32_t startY = 20;
    int32_t width = 100;
    int32_t height = 50;
    auto ret1 = overlay.ComputeMouseClippedSelectionBounds(startX, startY, width, height);
    EXPECT_EQ(ret1.GetY(), 0);
    auto ret2 = overlay.ComputeMouseClippedSelectionBounds(0, -1, 0, 0);
    EXPECT_EQ(ret2.GetY(), 0);
    auto ret3 = overlay.ComputeMouseClippedSelectionBounds(0, -1, 0, 2);
    EXPECT_EQ(ret3.GetY(), -1);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_001
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateRunQuickMenuSelectInfo_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptionsV2;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClickV2;
    OnPrepareMenuCallback onPrepareMenuCallback = PrepareMenuOptionsV2;
    webPattern->UpdateEditMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
    overlay.UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    webPattern->onPrepareMenuCallback_ = nullptr;
    overlay.UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(overlay.isQuickMenuMouseTrigger_);
    int start = 0, end = 0;
    selectInfo.onCreateCallback.textRangeCallback(start, end);
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_002
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateRunQuickMenuSelectInfo_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptionsV2;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClickV2;
    webPattern->UpdateEditMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), nullptr);
    selectInfo.isSingleHandle = true;
    overlay.UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(overlay.isQuickMenuMouseTrigger_);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_003
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateRunQuickMenuSelectInfo_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptionsV2;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClickV2;
    OnPrepareMenuCallback onPrepareMenuCallback = PrepareMenuOptionsV2;
    webPattern->onCreateMenuCallback_ = nullptr;
    webPattern->onMenuItemClick_ = nullptr;
    webPattern->onPrepareMenuCallback_ = nullptr;
    overlay.UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(overlay.isQuickMenuMouseTrigger_);
#endif
}

/**
 * @tc.name: UpdateRunQuickMenuSelectInfo_004
 * @tc.desc: UpdateRunQuickMenuSelectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateRunQuickMenuSelectInfo_004, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptionsV2;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClickV2;
    OnPrepareMenuCallback onPrepareMenuCallback = PrepareMenuOptionsV2;
    webPattern->onCreateMenuCallback_ =
        [](const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        std::vector<MenuOptionsParam> menuOptions;
        return menuOptions;
    };
    webPattern->onPrepareMenuCallback_ =
        [](const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        std::vector<MenuOptionsParam> menuOptions;
        return menuOptions;
    };
    webPattern->onMenuItemClick_ = [](const NG::MenuItemParam& menuItem) -> bool { return false; };
    overlay.UpdateRunQuickMenuSelectInfo(selectInfo, params, insertTouchHandle, beginTouchHandle, endTouchHandle);
    EXPECT_FALSE(overlay.isQuickMenuMouseTrigger_);
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBound_001
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeClippedSelectionBound_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
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
    overlay.ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
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
    overlay.ComputeClippedSelectionBounds(paramsone, startHandleone, endHandleone, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBound_002
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeClippedSelectionBound_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);

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
    overlay.ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBound_003
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeClippedSelectionBound_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
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
    bool isNewAvoid = true;
    overlay.ComputeClippedSelectionBounds(paramsone, startHandleone, endHandleone, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();
#endif
}


/**
 * @tc.name: ComputeClippedSelectionBound_004
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeClippedSelectionBound_004, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
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
    bool isNewAvoid = true;
    overlay.ComputeClippedSelectionBounds(paramstwo, startHandletwo, endHandletwo, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBound_005
 * @tc.desc: Test ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeClippedSelectionBound_005, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);

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
    overlay.ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_EQ(isNewAvoid, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: ComputeClippedSelectionBounds006
 * @tc.desc: ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeClippedSelectionBounds006, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto params = std::make_shared<NWebQuickMenuParamsMockImpl>();
    auto startHandle = std::make_shared<NWebTouchHandleStateMockImpl>();
    auto endHandle = std::make_shared<NWebTouchHandleStateMockImpl>();
    bool isNewAvoid = true;
    auto ret = overlay.ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_TRUE(isNewAvoid);
    EXPECT_EQ(ret, RectF());
#endif
}

/**
 * @tc.name: SetEditMenuOptions_001
 * @tc.desc: SetEditMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, SetEditMenuOptions_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectOverlayInfo selectInfo;
    OnCreateMenuCallback onCreateMenuCallback = CreateMenuOptionsV2;
    OnMenuItemClickCallback onMenuItemClick = HandleMenuItemClickV2;
    OnPrepareMenuCallback onPrepareMenuCallback = PrepareMenuOptionsV2;
    overlay.SetEditMenuOptions(selectInfo);
    webPattern->onCreateMenuCallback_ =
        [](const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        std::vector<MenuOptionsParam> menuOptions;
        return menuOptions;
    };
    overlay.SetEditMenuOptions(selectInfo);
    webPattern->onMenuItemClick_ = [](const NG::MenuItemParam& menuItem) -> bool { return false; };
    overlay.SetEditMenuOptions(selectInfo);
    webPattern->onPrepareMenuCallback_ =
        [](const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        std::vector<MenuOptionsParam> menuOptions;
        return menuOptions;
    };
    overlay.SetEditMenuOptions(selectInfo);
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid_001
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, QuickMenuIsNeedNewAvoid_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    auto params = std::make_shared<NWebQuickMenuParamsNeMockFirst>();
    auto startHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    auto endHandle = std::make_shared<NWebTouchHandleStateNeMockFirst>();
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    overlay.QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    auto ret = overlay.isQuickMenuMouseTrigger_;
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid_002
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, QuickMenuIsNeedNewAvoid_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
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
    overlay.QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(selectInfo.isNewAvoid, true);
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid_003
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, QuickMenuIsNeedNewAvoid_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
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
    overlay.QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(selectInfo.isNewAvoid, true);
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid004
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, QuickMenuIsNeedNewAvoid004, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    auto params = std::make_shared<NWebQuickMenuParamsDummy>();
    auto startHandle = std::make_shared<NWebTouchHandleStateDummy>();
    auto endHandle = std::make_shared<NWebTouchHandleStateDummy>();
    overlay.QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(overlay.isQuickMenuMouseTrigger_, true);
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_TRUE(overlay.isQuickMenuMouseTrigger_);
    EXPECT_EQ(selectInfo.selectArea, RectF(100, 0, 150, 50));
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid005
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, QuickMenuIsNeedNewAvoid005, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    auto params = std::make_shared<NWebQuickMenuParamsMockImpl>();
    auto startHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    auto endHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    overlay.QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(overlay.isQuickMenuMouseTrigger_, false);
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_EQ(selectInfo.selectArea, RectF());
#endif
}

/**
 * @tc.name: UpdateTouchHandleForOverlay_001
 * @tc.desc: UpdateTouchHandleForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateTouchHandleForOverlay_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    EXPECT_NE(webPattern->delegate_, nullptr);
    bool ret = true;
    auto handle_ = std::make_shared<OHOS::NWeb::MockNWebTouchHandleStateImpl>();
    overlay.insertHandle_ = handle_;
    overlay.startSelectionHandle_ = nullptr;
    overlay.endSelectionHandle_ = nullptr;
    bool result = overlay.IsTouchHandleValid(handle_);
    overlay.UpdateTouchHandleForOverlay(ret);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: UpdateTouchHandleForOverlay_002
 * @tc.desc: UpdateTouchHandleForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateTouchHandleForOverlay_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    EXPECT_NE(webPattern->delegate_, nullptr);
    bool ret = true;
    overlay.insertHandle_ = nullptr;
    auto handle_ = std::make_shared<OHOS::NWeb::MockNWebTouchHandleStateImpl>();
    overlay.startSelectionHandle_ = handle_;
    overlay.endSelectionHandle_ = handle_;
    overlay.selectTemporarilyHidden_ = true;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    bool result = overlay.IsTouchHandleValid(handle_);
    overlay.UpdateTouchHandleForOverlay(ret);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: UpdateTouchHandleForOverlay_003
 * @tc.desc: UpdateTouchHandleForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateTouchHandleForOverlay_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    EXPECT_NE(webPattern->delegate_, nullptr);
    bool ret = true;
    overlay.insertHandle_ = nullptr;
    g_alpha = 1.0f;
    auto handle_ = std::make_shared<OHOS::NWeb::MockNWebTouchHandleStateImpl>();
    overlay.startSelectionHandle_ = handle_;
    overlay.endSelectionHandle_ = handle_;
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    bool result = overlay.IsTouchHandleValid(handle_);
    overlay.UpdateTouchHandleForOverlay(ret);
    g_alpha = 0;
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: UpdateTouchHandleForOverlay004
 * @tc.desc: UpdateTouchHandleForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateTouchHandleForOverlay004, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    EXPECT_NE(webPattern->delegate_, nullptr);
    bool ret = false;
    overlay.UpdateTouchHandleForOverlay(ret);
    EXPECT_FALSE(ret);
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.UpdateTouchHandleForOverlay(ret);
    EXPECT_TRUE(overlay.selectTemporarilyHiddenByScroll_);
    overlay.selectTemporarilyHidden_ = true;
    EXPECT_TRUE(overlay.selectTemporarilyHidden_);
#endif
}

/**
 * @tc.name: UpdateTouchHandleForOverlayTest005
 * @tc.desc: Test UpdateTouchHandleForOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateTouchHandleForOverlayTest005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebSelectOverlay overlay(g_webPattern);
    overlay.insertHandle_ = std::make_shared<NWebTouchHandleStateMock>();
    overlay.startSelectionHandle_.reset();
    overlay.endSelectionHandle_.reset();
    overlay.UpdateTouchHandleForOverlay();
    overlay.insertHandle_.reset();
    overlay.startSelectionHandle_ = std::make_shared<NWebTouchHandleStateMock>();
    overlay.endSelectionHandle_ = std::make_shared<NWebTouchHandleStateMock>();
    overlay.UpdateTouchHandleForOverlay();
    overlay.startSelectionHandle_.reset();
    overlay.endSelectionHandle_.reset();
    overlay.UpdateTouchHandleForOverlay();
#endif
}

/**
 * @tc.name: SelectCancel_001
 * @tc.desc: SelectCancel.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, SelectCancel_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    overlay.quickMenuCallback_ = callback;
    overlay.SelectCancel();
#endif
}

/**
 * @tc.name: SelectCancel_002
 * @tc.desc: SelectCancel.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, SelectCancel_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    overlay.SelectCancel();
#endif
}

/**
 * @tc.name: UpdateClippedSelectionBounds_001
 * @tc.desc: UpdateClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateClippedSelectionBounds_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    int32_t startX = 10;
    int32_t startY = 20;
    int32_t width = 100;
    int32_t height = 50;
    overlay.UpdateClippedSelectionBounds(startX, startY, width, height);
#endif
}

/**
 * @tc.name: UpdateClippedSelectionBounds_002
 * @tc.desc: UpdateClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateClippedSelectionBounds_002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    int32_t startX = 10;
    int32_t startY = 20;
    int32_t width = 100;
    int32_t height = 50;
    overlay.isQuickMenuMouseTrigger_ = true;
    overlay.UpdateClippedSelectionBounds(startX, startY, width, height);
#endif
}

/**
 * @tc.name: ChangeVisibilityOfQuickMenu
 * @tc.desc: ChangeVisibilityOfQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ChangeVisibilityOfQuickMenu, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    overlay.ChangeVisibilityOfQuickMenu();
#endif
}

/**
 * @tc.name: ChangeVisibilityOfQuickMenu002
 * @tc.desc: ChangeVisibilityOfQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ChangeVisibilityOfQuickMenu002, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    overlay.startSelectionHandle_ = startTouchHandle;
    overlay.endSelectionHandle_ = endTouchHandle;
    overlay.ChangeVisibilityOfQuickMenu();
    overlay.selectTemporarilyHiddenByScroll_ = true;
    overlay.ChangeVisibilityOfQuickMenu();
    overlay.selectTemporarilyHidden_ = true;
    overlay.ChangeVisibilityOfQuickMenu();
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.selectTemporarilyHidden_ = false;
    overlay.SetMenuIsShow(true);
    overlay.ChangeVisibilityOfQuickMenu();
    overlay.SetMenuIsShow(false);
    overlay.ChangeVisibilityOfQuickMenu();
#endif
}

/**
 * @tc.name: PreProcessOverlay_001
 * @tc.desc: Test function PreProcessOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, PreProcessOverlay_001, TestSize.Level0)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);
    OverlayRequest request;
    request.menuIsShow = false;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    bool result = overlay.PreProcessOverlay(request);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PreProcessOverlay_002
 * @tc.desc: Test function PreProcessOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, PreProcessOverlay_002, TestSize.Level0)
{
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::SetUp();

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    ;
    WebSelectOverlay overlay(textBase);

    OverlayRequest request;
    request.menuIsShow = false;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    bool result = overlay.PreProcessOverlay(request);
    EXPECT_TRUE(result);

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: PreProcessOverlay_003
 * @tc.desc: Test function PreProcessOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, PreProcessOverlay_003, TestSize.Level0)
{
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::SetUp();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);
    OverlayRequest request;
    request.menuIsShow = false;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    bool result = overlay.PreProcessOverlay(request);
    EXPECT_TRUE(result);
    EXPECT_TRUE(overlay.IsEnableContainerModal());
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: CheckHandleVisible_001
 * @tc.desc: Test function CheckHandleVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, CheckHandleVisible_001, TestSize.Level2)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    RectF paintRect(0, 0, 100.0f, 100.0f);
    bool result = overlay.CheckHandleVisible(paintRect);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: AfterCloseOverlay_001
 * @tc.desc: Test function AfterCloseOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, AfterCloseOverlay_001, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    WebSelectOverlay overlay(webPattern);
    overlay.AfterCloseOverlay();
    EXPECT_EQ(overlay.selectOverlayDragging_, false);
    EXPECT_EQ(overlay.isShowHandle_, false);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_001
 * @tc.desc: Test function OnUpdateSelectOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnUpdateSelectOverlayInfo_001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);
    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.SetIsSingleHandle(false);
    overlay.webSelectInfo_.isHandleLineShow = false;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_EQ(selectInfo.isHandleLineShow, true);
}

/**
 * @tc.name: GetFirstHandleInfo_001
 * @tc.desc: Test function GetFirstHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetFirstHandleInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);
    std::optional<SelectHandleInfo> result = overlay.GetFirstHandleInfo();
}

/**
 * @tc.name: GetFirstHandleInfo_002
 * @tc.desc: Test function GetFirstHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetFirstHandleInfo_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);
    auto touchHandle = std::make_shared<NWeb::CustomNWebTouchHandleState>();
    touchHandle->SetX(10.0);
    touchHandle->SetY(20.0);
    touchHandle->SetEdgeHeight(5.0);
    RectF paintRect = overlay.ComputeTouchHandleRect(touchHandle);
    overlay.webSelectInfo_.secondHandle.paintRect = paintRect;
    overlay.webSelectInfo_.secondHandle.isShow = false;
    std::optional<SelectHandleInfo> result = overlay.GetFirstHandleInfo();
    overlay.webSelectInfo_.secondHandle.isShow = true;
    result  = overlay.GetFirstHandleInfo();
}

/**
 * @tc.name: GetSecondHandleInfo_001
 * @tc.desc: Test function GetSecondHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetSecondHandleInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetSecondHandleInfo();
}

/**
 * @tc.name: GetSecondHandleInfo_002
 * @tc.desc: Test function GetSecondHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetSecondHandleInfo_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    ;
    WebSelectOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetSecondHandleInfo();
}

/**
 * @tc.name: OnUpdateMenuInfo_001
 * @tc.desc: Test function OnUpdateMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnUpdateMenuInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);
    SelectMenuInfo selectMenuInfo1;
    selectMenuInfo1.showCopyAll = false;
    selectMenuInfo1.showCopy = false;
    selectMenuInfo1.showCut = false;
    selectMenuInfo1.showPaste = false;
    selectMenuInfo1.menuIsShow = false;
    selectMenuInfo1.showCameraInput = false;
    overlay.webSelectInfo_.menuInfo = selectMenuInfo1;
    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_FALSE(selectMenuInfo.showCopyAll);
    EXPECT_FALSE(selectMenuInfo.showCopy);
    EXPECT_FALSE(selectMenuInfo.showCut);
    EXPECT_FALSE(selectMenuInfo.showPaste);
    EXPECT_FALSE(selectMenuInfo.menuIsShow);
    EXPECT_FALSE(selectMenuInfo.showCameraInput);
}

/**
 * @tc.name: GetSelectArea_001
 * @tc.desc: Test function GetSelectArea.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetSelectArea_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    RectF result = overlay.GetSelectArea();
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.Width(), 0);
    EXPECT_EQ(result.Height(), 0);
}

/**
 * @tc.name: GetSelectedText_001
 * @tc.desc: Test function GetSelectedText.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetSelectedText_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    std::string result = overlay.GetSelectedText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: OnHandleMoveStart
 * @tc.desc: OnHandleMoveStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnSelectHandleStart, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSelectOverlayManager();
    ASSERT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    ASSERT_NE(current, nullptr);
    manager->selectContentManager_ = AceType::MakeRefPtr<SelectContentOverlayManager>(frameNode);
    GestureEvent event;
    overlay.OnSelectHandleStart(event, true);
    webPattern->overlayCreating_ = true;
    webPattern->UpdateNativeEmbedModeEnabled(true);
    overlay.OnSelectHandleStart(event, false);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnHandleMove
 * @tc.desc: OnHandleMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleMove, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    manager->isDragged_ = true;
    RectF handleRect;
    webPattern->isDragging_ = true;
    webPattern->webOffset_ = OffsetT<float>(1.2f, 1.2f);
    manager->isDragged_ = true;
    overlay.OnHandleMove(handleRect, true);
    webPattern->isDragging_ = false;
    manager->isDragged_ = false;
    overlay.OnHandleMove(handleRect, true);
    webPattern->overlayCreating_ = true;
    overlay.OnHandleMove(handleRect, true);
    webPattern->isDragging_ = true;
    overlay.OnHandleMove(handleRect, true);
    manager->isDragged_ = true;
    overlay.OnHandleMove(handleRect, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnHandleMoveStart_001
 * @tc.desc: OnHandleMoveStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleMoveStart_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSelectOverlayManager();
    ASSERT_NE(manager, nullptr);
    SelectOverlayInfo info;
    info.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    manager->selectOverlayItem_ = selectOverlayNode;
    auto current = manager->selectOverlayItem_.Upgrade();
    ASSERT_NE(current, nullptr);
    manager->selectContentManager_ = AceType::MakeRefPtr<SelectContentOverlayManager>(frameNode);
    GestureEvent event;
    overlay.OnHandleMoveStart(event, true);
    webPattern->overlayCreating_ = true;
    webPattern->UpdateNativeEmbedModeEnabled(true);
    overlay.OnHandleMoveStart(event, false);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnHandleMoveDone_001
 * @tc.desc: Test function OnHandleMoveDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleMoveDone_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    RectF rect;
    bool isFirst = false;
    overlay.OnHandleMoveDone(rect, isFirst);
    EXPECT_EQ(overlay.GetPattern<WebPattern>(), nullptr);
}

/**
 * @tc.name: OnHandleMoveDone_002
 * @tc.desc: Test function OnHandleMoveDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleMoveDone_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);

    RectF rect;
    bool isFirst = false;
    overlay.OnHandleMoveDone(rect, isFirst);
}

/**
 * @tc.name: OnHandleMoveDone_003
 * @tc.desc: OnHandleMoveDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleMoveDone_003, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    RectF handleRect;
    overlay.OnHandleMoveDone(handleRect, true);
    webPattern->overlayCreating_ = true;
    webPattern->imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    overlay.OnHandleMoveDone(handleRect, true);
    overlay.endSelectionHandle_ = nullptr;
    overlay.startSelectionHandle_ = std::make_shared<NWebTouchHandleStateUN>();
    overlay.OnHandleMoveDone(handleRect, true);
    overlay.startSelectionHandle_ = nullptr;
    overlay.endSelectionHandle_ = std::make_shared<NWebTouchHandleStateUN>();
    overlay.OnHandleMoveDone(handleRect, true);
    overlay.startSelectionHandle_ = std::make_shared<NWebTouchHandleStateUN>();
    EXPECT_EQ(overlay.startSelectionHandle_->GetX(), 10);
    EXPECT_EQ(overlay.startSelectionHandle_->GetY(), 10);
    EXPECT_EQ(overlay.endSelectionHandle_->GetX(), 10);
    EXPECT_EQ(overlay.endSelectionHandle_->GetY(), 10);
#endif
}

/**
 * @tc.name: OnOverlayClick_001
 * @tc.desc: OnOverlayClick
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnOverlayClick_001, TestSize.Level1)
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
    WebSelectOverlay overlay(webPattern);
    EXPECT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    overlay.OnOverlayClick(event, true);
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startTouchHandle =
        std::make_shared<OHOS::NWeb::CustomNWebTouchHandleState>();
    overlay.insertHandle_  = startTouchHandle;
    overlay.OnOverlayClick(event, true);
#endif
}

/**
 * @tc.name: OnCloseOverlay_001
 * @tc.desc: Test function OnCloseOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnCloseOverlay_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    OptionMenuType menuType = OptionMenuType::NO_MENU;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    RefPtr<OverlayInfo> info;
    overlay.OnCloseOverlay(menuType, reason, info);
    EXPECT_EQ(overlay.GetPattern<WebPattern>(), nullptr);
}

/**
 * @tc.name: OnCloseOverlay_002
 * @tc.desc: Test function OnCloseOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnCloseOverlay_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);

    OptionMenuType menuType = OptionMenuType::NO_MENU;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    RefPtr<OverlayInfo> info;
    overlay.OnCloseOverlay(menuType, reason, info);
}

/**
 * @tc.name: OnHandleReverse_001
 * @tc.desc: Test function OnHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleReverse_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);
    overlay.OnHandleReverse(false);
    overlay.needResetHandleReverse_ = true;
    overlay.OnHandleReverse(true);
    overlay.OnAfterSelectOverlayShow(true);
    overlay.needResetHandleReverse_ = false;
    overlay.OnHandleReverse(true);
    overlay.OnAfterSelectOverlayShow(true);
}

/**
 * @tc.name: OnHandleGlobalTouchEvent_001
 * @tc.desc: Test function OnHandleGlobalTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleGlobalTouchEvent_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);

    SourceType sourceType = SourceType::MOUSE;
    TouchType touchType = TouchType::DOWN;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_TRUE(overlay.IsMouseClickDown(sourceType, touchType));

    sourceType = SourceType::TOUCH;
    touchType = TouchType::UP;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_TRUE(overlay.IsTouchUp(sourceType, touchType));

    sourceType = SourceType::NONE;
    touchType = TouchType::UNKNOWN;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
}

/**
 * @tc.name: UpdateSelectMenuOptions
 * @tc.desc: Test function UpdateSelectMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSelectMenuOptions, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);
    overlay.webSelectInfo_.menuInfo.showTranslate = true;
    overlay.webSelectInfo_.menuInfo.showSearch = true;
    overlay.UpdateSelectMenuOptions();
    EXPECT_FALSE(overlay.webSelectInfo_.menuInfo.showTranslate);
    EXPECT_FALSE(overlay.webSelectInfo_.menuInfo.showSearch);
}

/**
 * @tc.name: OnHandleMarkInfoChange001
 * @tc.desc: Test function OnHandleMarkInfoChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnHandleMarkInfoChange001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);

    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    SelectOverlayDirtyFlag flag = DIRTY_HANDLE_COLOR_FLAG;
    overlay.OnHandleMarkInfoChange(shareOverlayInfo, flag);

    flag = DIRTY_FIRST_HANDLE;
    overlay.OnHandleMarkInfoChange(shareOverlayInfo, flag);

    shareOverlayInfo->menuInfo.showShare = false;
    overlay.OnHandleMarkInfoChange(shareOverlayInfo, flag);

    shareOverlayInfo->menuInfo.showShare = true;
    overlay.OnHandleMarkInfoChange(shareOverlayInfo, flag);

    flag = DIRTY_SECOND_HANDLE;
    overlay.needResetHandleReverse_ = false;
    overlay.OnHandleMarkInfoChange(shareOverlayInfo, flag);
    overlay.needResetHandleReverse_ = true;
    overlay.OnHandleMarkInfoChange(shareOverlayInfo, flag);
}

/**
 * @tc.name: OnMenuItemActionTest006
 * @tc.desc: Test function OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnMenuItemActionTest006, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebSelectOverlay overlay(textBase);
    overlay.startSelectionHandle_ = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMock>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    overlay.quickMenuCallback_ = callback;
    overlay.OnMenuItemAction(OptionMenuActionId::TRANSLATE, OptionMenuType::TOUCH_MENU);
    EXPECT_FALSE(overlay.startSelectionHandle_);
    overlay.endSelectionHandle_ = std::make_shared<OHOS::NWeb::NWebTouchHandleStateMock>();
    overlay.quickMenuCallback_ = callback;
    overlay.OnMenuItemAction(OptionMenuActionId::SEARCH, OptionMenuType::TOUCH_MENU);
    EXPECT_FALSE(overlay.endSelectionHandle_);
}

/**
 * @tc.name: UpdateAIMenuTest001
 * @tc.desc: Test AIMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateAIMenuTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();

    WebSelectOverlay overlay(webPattern);
    overlay.DetectSelectedText("13323332333");
    overlay.canShowAIMenu_ = true;
    overlay.DetectSelectedText("13323332333");

    auto adapter = webPattern->GetDataDetectorAdapter();
    ASSERT_NE(adapter, nullptr);
    overlay.aiMenuType_ = TextDataDetectType::PHONE_NUMBER;
    overlay.DetectSelectedText("13323332333");
    EXPECT_EQ(overlay.aiMenuType_, TextDataDetectType::INVALID);
    overlay.UpdateAISelectMenu(TextDataDetectType::PHONE_NUMBER, "13323332333");
    EXPECT_EQ(overlay.aiMenuType_, TextDataDetectType::PHONE_NUMBER);
}

/**
 * @tc.name: HandleOnAskCelia001
 * @tc.desc: Test HandleOnAskCelia.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HandleOnAskCelia001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WebSelectOverlay g_overlay(webPattern);
    webPattern->GetCoordinatePoint();
    std::shared_ptr<NWebTouchHandleState> touchHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_overlay.ComputeTouchHandleRect(touchHandle);
    g_Y = -1;
    g_overlay.ComputeTouchHandleRect(touchHandle);
    std::shared_ptr<NWebQuickMenuParams> params = std::make_shared<NWebQuickMenuParamsMock>();
    std::shared_ptr<NWebQuickMenuCallback> callback = std::make_shared<NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    g_editStateFlags = OHOS::NWeb::NWebQuickMenuParams::QM_EF_CAN_COPY;
    g_overlay.HandleOnAskCelia();
    FuncVariant funcAskCelia = []() -> std::string { return "askCelia"; };
    FuncVariant funcCopy = []() -> std::string { return "copy"; };
    FuncVariant funcSelectText = []() -> std::string { return "selectText"; };
    FuncVariant funcLocation = [](int32_t id, std::string content) {};
    webPattern->textDetectResult_.menuOptionAndAction["askCelia"] = { { "funcAskCelia", funcAskCelia },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    g_overlay.HandleOnAskCelia();
    FuncVariant funcAskCelia2 = [](int32_t id, std::string content) {};
    webPattern->textDetectResult_.menuOptionAndAction["askCelia"] = { { "askCelia1", funcAskCelia2 },
        { "askCelia2", funcLocation } };
    g_overlay.HandleOnAskCelia();
}

/**
 * @tc.name: InitAIDetectResult_001
 * @tc.desc: Test InitAIDetectResult.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, InitAIDetectResult_001, TestSize.Level0)
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
    webPattern->InitAIDetectResult();
    ASSERT_EQ(webPattern->textDetectResult_.menuOptionAndAction.empty(), true);
    FuncVariant funcAskCelia = [](int32_t id, std::string content) {};
    webPattern->textDetectResult_.menuOptionAndAction["askCelia"] = { { "askCelia", funcAskCelia } };
    webPattern->InitAIDetectResult();
    ASSERT_EQ(webPattern->textDetectResult_.menuOptionAndAction.empty(), false);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnTouchSelectionChangedTest011
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnTouchSelectionChangedTest011, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WebSelectOverlay overlay(webPattern);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto insertHandle = nullptr;
    ASSERT_EQ(insertHandle, nullptr);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    ASSERT_NE(startSelectionHandle, nullptr);
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    ASSERT_NE(endSelectionHandle, nullptr);
    overlay.isShowHandle_ = true;
    overlay.selectOverlayDragging_ = true;
    overlay.isSelectAll_ = true;
    overlay.OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    EXPECT_EQ(overlay.isSelectAll_, true);
}

/**
 * @tc.name: OnMenuItemActionTestSelectAll
 * @tc.desc: Test OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnMenuItemActionTestSelectAll, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    SelectOverlayInfo selectInfo;
    auto flags = g_editStateFlags;
    g_editStateFlags = 0;
    overlay.SetMenuOptions(selectInfo, params, callback);
    overlay.isSelectAll_ = true;
    overlay.OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::TOUCH_MENU);
    ASSERT_EQ(overlay.isSelectAll_, false);
    overlay.isSelectAll_ = true;
    overlay.OnMenuItemAction(OptionMenuActionId::CUT, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(overlay.isSelectAll_, false);
    g_editStateFlags = flags;
}

/**
 * @tc.name: UpdateSelectMenuOptionsTest002
 * @tc.desc: Test function UpdateSelectMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSelectMenuOptionsTest002, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebSelectOverlay overlay(textBase);
    overlay.isSelectAll_ = true;
    overlay.UpdateSelectMenuOptions();
    EXPECT_FALSE(overlay.isSelectAll_);
}

/**
 * @tc.name: UpdateTouchHandleForOverlayTestSelectAll
 * @tc.desc: Test OnTouchSelectionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateTouchHandleForOverlayTestSelectAll, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    EXPECT_NE(manager, nullptr);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    auto contentManager = AceType::DynamicCast<SelectContentOverlayManager>(manager);
    auto g_webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(g_webPattern, nullptr);
    WebSelectOverlay overlay(g_webPattern);
    overlay.OnBind(WeakPtr<AceType>(contentManager));
    auto CManager = overlay.GetManager<SelectContentOverlayManager>();
    EXPECT_NE(CManager, nullptr);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    CManager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(CManager->shareOverlayInfo_);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->parent_ = AceType::WeakClaim(AceType::RawPtr(selectOverlayNode));
    CManager->handleNode_ = AceType::WeakClaim(AceType::RawPtr(selectOverlayNode));
    CManager->menuNode_ = AceType::WeakClaim(AceType::RawPtr(selectOverlayNode));
    overlay.insertHandle_ = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    overlay.startSelectionHandle_ = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.endSelectionHandle_ = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.selectTemporarilyHidden_ = false;
    overlay.selectTemporarilyHiddenByScroll_ = false;
    overlay.isShowHandle_ = true;
    overlay.selectOverlayDragging_ = true;
    overlay.isSelectAll_ = true;
    overlay.UpdateTouchHandleForOverlay(false);
    overlay.isSelectAll_ = false;
    overlay.UpdateTouchHandleForOverlay(false);
    MockPipelineContext::TearDown();
    EXPECT_EQ(overlay.isSelectAll_, false);
}

/**
 * @tc.name: UpdateSingleHandleVisible
 * @tc.desc: Test UpdateSingleHandleVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, UpdateSingleHandleVisible, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.insertHandle_ = insertHandle;
    overlay.OnHandleIsHidden();
    overlay.UpdateSingleHandleVisible(true);
    MockPipelineContext::TearDown();
    EXPECT_TRUE(overlay.insertHandle_->IsEnable());
}

/**
 * @tc.name: OnVisibleAreaChange
 * @tc.desc: OnVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, OnVisibleAreaChange, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);
    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    webPattern->OnShowMagnifier();
    webPattern->isDragEndMenuShow_ = true;
    WeakPtr<TextBase> textBase = nullptr;
    webPattern->OnVisibleAreaChange(false);
    webPattern->webSelectOverlay_ = AceType::MakeRefPtr<WebSelectOverlay>(textBase);
    webPattern->UpdateSingleHandleVisible(false);
    webPattern->OnVisibleAreaChange(false);
    webPattern->webSelectOverlay_->insertHandle_ = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    webPattern->isVisible_ = true;
    webPattern->OnHideMagnifier();
    webPattern->OnVisibleAreaChange(false);
    EXPECT_FALSE(webPattern->isDragEndMenuShow_);
}

/**
 * @tc.name: HandleBlurEvent
 * @tc.desc: HandleBlurEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, HandleBlurEvent, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);
    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    WeakPtr<TextBase> textBase = nullptr;
    webPattern->HandleBlurEvent(BlurReason::FOCUS_SWITCH);
    webPattern->webSelectOverlay_ = AceType::MakeRefPtr<WebSelectOverlay>(textBase);
    webPattern->HandleBlurEvent(BlurReason::FOCUS_SWITCH);
    webPattern->webSelectOverlay_->insertHandle_ = std::make_shared<NWebTouchHandleStateBeginTestImpl>();
    webPattern->HandleBlurEvent(BlurReason::FOCUS_SWITCH);
    ASSERT_NE(webPattern->delegate_, nullptr);
}

/**
 * @tc.name: RunQuickMenu_005
 * @tc.desc: RunQuickMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, RunQuickMenu_005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    WebSelectOverlay overlay(webPattern);
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params =
        std::make_shared<OHOS::NWeb::NWebQuickMenuParamsSelectImpl>();
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback =
        std::make_shared<OHOS::NWeb::NWebQuickMenuCallbackMock>();
    overlay.isQuickMenuMouseTrigger_ = true;
    g_insertHandle = nullptr;
    g_endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_startSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    g_isEnable = true;
    g_isLongPress = false;
    bool result = overlay.RunQuickMenu(params, callback);
    EXPECT_TRUE(result);
    g_isLongPress = true;
    result = overlay.RunQuickMenu(params, callback);
    g_isLongPress = false;
    g_isEnable = false;
    g_endSelectionHandle = nullptr;
    g_startSelectionHandle = nullptr;
    MockPipelineContext::TearDown();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetTouchHandleExistState
 * @tc.desc: Test SetTouchHandleExistState.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, SetTouchHandleExistState, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    webPattern->OnModifyDone();
    WebSelectOverlay overlay(webPattern);
    auto insertHandle = std::make_shared<NWebTouchHandleStateEndTestImpl>();
    overlay.insertHandle_ = insertHandle;
    overlay.OnHandleIsHidden();
    overlay.SetTouchHandleExistState(true);
    MockPipelineContext::TearDown();
    EXPECT_TRUE(overlay.insertHandle_->IsEnable());
}

/**
 * @tc.name: GetBottomWithKeyboard
 * @tc.desc: Test GetBottomWithKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, GetBottomWithKeyboardTest, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    if (!pipeline) {
        MockPipelineContext::TearDown();
        ASSERT_NE(pipeline, nullptr);
    }
    pipeline->safeAreaManager_ = safeAreaManager;
    WebSelectOverlay overlay(webPattern);
    auto ret = overlay.GetBottomWithKeyboard(EDGE_HEIGHT);
    MockPipelineContext::TearDown();
    ASSERT_EQ(ret, EDGE_HEIGHT);
}
 
/**
 * @tc.name: ComputeMenuOffset
 * @tc.desc: Test InitWebMenuAvoidStrategy and ComputeMenuOffset in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeMenuOffsetTest0, TestSize.Level1)
{
    auto *stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webFrameNode, nullptr);
    stack->Push(webFrameNode);
    auto webPattern = webFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    /**
    * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    if (!pipeline) {
        MockPipelineContext::TearDown();
        ASSERT_NE(pipeline, nullptr);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    /**
    * @tc.steps: step. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    InitLayoutWrapper(layoutWrapper, geometryNode, infoPtr);
    /**
    * @tc.steps: step3. set keyboardInset_.
    */
    InitSafeAreaManager(pipeline);
    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->firstHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->secondHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->isSingleHandle = true;
    infoPtr->isNewAvoid = false;
    OffsetF menuOffset = {0.0f, 0.0f};
    RectF menuRect = {0.0f, 0.0f, 0.0f, 100.0f};
    OffsetF windowOffset = {0.0f, 0.0f};
    auto layoutWrapperPtr = AccessibilityManager::RawPtr(layoutWrapper);
    WebSelectOverlay overlay(webPattern);
    auto ret = overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    infoPtr->isNewAvoid = true;
    ret |= overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    infoPtr->isSingleHandle = false;
    ret |= overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    MockPipelineContext::TearDown();
    infoPtr->isNewAvoid = false;
    ret |= overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    EXPECT_FALSE(ret);
}
 
/**
 * @tc.name: ComputeMenuOffset
 * @tc.desc: Test InitWebMenuAvoidStrategy and ComputeMenuOffset in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeMenuOffsetTest1, TestSize.Level1)
{
    auto *stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webFrameNode, nullptr);
    stack->Push(webFrameNode);
    auto webPattern = webFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    /**
    * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    if (!pipeline) {
        MockPipelineContext::TearDown();
        ASSERT_NE(pipeline, nullptr);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    /**
    * @tc.steps: step. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    InitLayoutWrapper(layoutWrapper, geometryNode, infoPtr);
    /**
    * @tc.steps: step3. set keyboardInset_.
    */
    InitSafeAreaManager(pipeline);
    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->firstHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->secondHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->isSingleHandle = false;
    infoPtr->isNewAvoid = false;
    OffsetF menuOffset = {0.0f, 0.0f};
    RectF menuRect = {0.0f, 0.0f, 0.0f, 100.0f};
    OffsetF windowOffset = {0.0f, 0.0f};
    auto layoutWrapperPtr = AccessibilityManager::RawPtr(layoutWrapper);
    WebSelectOverlay overlay(webPattern);
    auto ret = overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    MockPipelineContext::TearDown();
    EXPECT_TRUE(ret);
}
 
/**
  * @tc.name: ComputeMenuOffset
  * @tc.desc: Test InitWebMenuAvoidStrategy and ComputeMenuOffset in Select Overlay algorithm.
  * @tc.type: FUNC
  */
HWTEST_F(WebSelectOverlayTest, ComputeMenuOffsetTest2, TestSize.Level1)
{
    auto *stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webFrameNode, nullptr);
    stack->Push(webFrameNode);
    auto webPattern = webFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    /**
    * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    if (!pipeline) {
        MockPipelineContext::TearDown();
        ASSERT_NE(pipeline, nullptr);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    /**
    * @tc.steps: step. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    InitLayoutWrapper(layoutWrapper, geometryNode, infoPtr);
    /**
    * @tc.steps: step3. set keyboardInset_.
    */
    InitSafeAreaManager(pipeline);
    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->firstHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->secondHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->isSingleHandle = false;
    infoPtr->isNewAvoid = false;
    OffsetF menuOffset = {0.0f, -1.0f};
    RectF menuRect = {0.0f, -1.0f, 0.0f, 100.0f};
    OffsetF windowOffset = {0.0f, 0.0f};
    auto layoutWrapperPtr = AccessibilityManager::RawPtr(layoutWrapper);
    geometryNode->SetFrameSize(SizeF(0.0f, 1280.0f));
    WebSelectOverlay overlay(webPattern);
    auto ret = overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    MockPipelineContext::TearDown();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ComputeMenuOffset
 * @tc.desc: Test InitWebMenuAvoidStrategy and ComputeMenuOffset in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, ComputeMenuOffsetTest3, TestSize.Level1)
{
    auto *stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webFrameNode, nullptr);
    stack->Push(webFrameNode);
    auto webPattern = webFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    /**
    * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    if (!pipeline) {
        MockPipelineContext::TearDown();
        ASSERT_NE(pipeline, nullptr);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    /**
    * @tc.steps: step. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    InitLayoutWrapper(layoutWrapper, geometryNode, infoPtr);
    /**
    * @tc.steps: step3. set keyboardInset_.
    */
    InitSafeAreaManager(pipeline);
    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->firstHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->secondHandle.paintRect = {0.0f, 0.0f, 0.0f, 0.0f};
    infoPtr->isSingleHandle = false;
    infoPtr->isNewAvoid = false;
    OffsetF menuOffset = {0.0f, 1.0f};
    RectF menuRect = {0.0f, 1.0f, 0.0f, -100.0f};
    OffsetF windowOffset = {0.0f, 0.0f};
    auto layoutWrapperPtr = AccessibilityManager::RawPtr(layoutWrapper);
    geometryNode->SetFrameSize(SizeF(0.0f, 1280.0f));
    WebSelectOverlay overlay(webPattern);
    auto ret = overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    MockPipelineContext::TearDown();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: WebMenuAvoidStrategy
 * @tc.desc: Test WebMenuAvoidStrategy.
 * @tc.type: FUNC
 */
HWTEST_F(WebSelectOverlayTest, WebMenuAvoidStrategyTest, TestSize.Level1)
{
    auto *stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto webFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webFrameNode, nullptr);
    stack->Push(webFrameNode);
    auto webPattern = webFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    /**
    * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrentContext();
    if (!pipeline) {
        MockPipelineContext::TearDown();
        ASSERT_NE(pipeline, nullptr);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    /**
    * @tc.steps: step. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    InitLayoutWrapper(layoutWrapper, geometryNode, infoPtr);
    /**
    * @tc.steps: step3. set keyboardInset_.
    */
    InitSafeAreaManager(pipeline);
    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->firstHandle.paintRect = {0.0f, 0.0f, 0.0f, 1.0f};
    infoPtr->secondHandle.paintRect = {100.0f, 299.0f, 0.0f, 1.0f};
    infoPtr->isSingleHandle = false;
    infoPtr->isNewAvoid = false;
    infoPtr->selectArea = {0.0f, 0.0f, 100.0f, 300.0f};
    OffsetF menuOffset = {0.0f, 300.0f};
    RectF menuRect = {0.0f, 300.0f, 20.0f, 100.0f};
    OffsetF windowOffset = {0.0f, 0.0f};
    auto layoutWrapperPtr = AccessibilityManager::RawPtr(layoutWrapper);
    geometryNode->SetFrameSize(SizeF(0.0f, 300.0f));
    WebSelectOverlay overlay(webPattern);
    auto ret = overlay.ComputeMenuOffset(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    auto ret1 = NearEqual(menuOffset.GetX(), 40.0f, NEW_EPSILON);
    auto ret2 = NearEqual(menuOffset.GetY(), 100.0f, NEW_EPSILON);
    MockPipelineContext::TearDown();
    EXPECT_TRUE(ret && ret1 && ret2);
}
} // namespace OHOS::Ace::NG
