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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"

#include "cj_lambda.h"

#include "bridge/common/utils/utils.h"
#include "core/components/scroll/scroll_component.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
constexpr int32_t SNAP_START_INDEX = 0;
constexpr double DEFAULT_DIMENSION_VALUE = 0.0;
constexpr double DEFAULT_DURATION = 1000.0;

const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::FREE, Axis::NONE };
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<ScrollEdgeType> SCROLL_EDGE_TYPES = { ScrollEdgeType::SCROLL_TOP, ScrollEdgeType::SCROLL_NONE,
    ScrollEdgeType::SCROLL_BOTTOM, ScrollEdgeType::SCROLL_NONE, ScrollEdgeType::SCROLL_TOP, ScrollEdgeType::SCROLL_NONE,
    ScrollEdgeType::SCROLL_BOTTOM };
const std::vector<ScrollAlign> SCROLL_ALIGN_LIST = { ScrollAlign::START, ScrollAlign::CENTER, ScrollAlign::END,
    ScrollAlign::AUTO, ScrollAlign::NONE };

bool CheckSnapPagination(const std::vector<Dimension>& snapPagination)
{
    CHECK_NULL_RETURN(!snapPagination.empty(), false);
    float preValue = (*snapPagination.begin()).Value();
    CHECK_NULL_RETURN(!Negative(preValue), false);
    auto unit = (*snapPagination.begin()).Unit();
    for (auto iter = snapPagination.begin() + 1; iter < snapPagination.end(); ++iter) {
        if (Negative((*iter).Value()) || (*iter).Unit() != unit || LessOrEqual((*iter).Value(), preValue)) {
            return false;
        }
        preValue = (*iter).Value();
    }
    return true;
}
} // namespace

namespace OHOS::Ace::Framework {

NativeNGScroller::NativeNGScroller() : FFIData()
{
    LOGI("Scroller constructed: %{public}" PRId64, GetID());
}

void NativeNGScroller::ScrollTo(const Dimension& xOffset, const Dimension& yOffset, double duration,
    const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    auto direction = controller_->GetScrollDirection();
    auto position = direction == Axis::VERTICAL ? yOffset : xOffset;
    controller_->AnimateTo(position, static_cast<float>(duration), curve, smooth, canOverScroll);
}

void NativeNGScroller::ScrollBy(const Dimension& xOffset, const Dimension& yOffset)
{
    if (!controller_) {
        LOGE("Scroll controller is null: invalid scrollerID");
        return;
    }

    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            if (xOffset.Unit() == DimensionUnit::PERCENT) {
                deltaX = 0.0;
            } else {
                deltaX = context->NormalizeToPx(xOffset);
            }
            if (yOffset.Unit() == DimensionUnit::PERCENT) {
                deltaY = 0.0;
            } else {
                deltaY = context->NormalizeToPx(yOffset);
            }
        }
    }
    controller_->ScrollBy(deltaX, deltaY, false);
}

void NativeNGScroller::ScrollEdge(ScrollEdgeType edge, float velocity)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    if (velocity > 0) {
        velocity = Dimension(velocity, DimensionUnit::VP).ConvertToPx();
        controller_->ScrollToEdge(edge, velocity);
        return;
    }
    controller_->ScrollToEdge(edge, true);
}

void NativeNGScroller::ScrollFling(double velocity)
{
    if (NearZero(velocity)) {
        return;
    }
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    velocity = Dimension(velocity, DimensionUnit::VP).ConvertToPx();
    controller_->Fling(velocity);
}

void NativeNGScroller::ScrollPage(bool next, bool animation)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    controller_->ScrollPage(!next, animation);
}

void NativeNGScroller::ScrollToIndex(int32_t index, bool smooth, int32_t align, double offset, int32_t unit)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    auto extraOffset = Dimension(offset, static_cast<DimensionUnit>(unit)).ConvertToPx();
    controller_->ScrollToIndex(index, smooth, SCROLL_ALIGN_LIST[align], extraOffset);
}

Offset NativeNGScroller::CurrentOffset()
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return Offset(0.0, 0.0);
    }
    return controller_->GetCurrentOffset();
}

bool NativeNGScroller::IsAtEnd()
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return false;
    }
    return controller_->IsAtEnd();
}

Rect NativeNGScroller::GetItemRect(int32_t index)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return Rect();
    }
    return controller_->GetItemRect(index);
}

int32_t NativeNGScroller::GetItemIndex(const Dimension& xOffset, const Dimension& yOffset)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return -1;
    }

    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            deltaX = context->NormalizeToPx(xOffset);
            deltaY = context->NormalizeToPx(yOffset);
        }
    }
    return controller_->GetItemIndex(deltaX, deltaY);
}

} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkScrollCreate(int64_t scrollerID)
{
    if (scrollerID == -1) {
        ScrollModel::GetInstance()->Create();
        std::pair<bool, Color> barColor;
        barColor.first = false;
        std::pair<bool, Dimension> barWidth;
        barWidth.first = false;
        auto pipelineContext = PipelineContext::GetCurrentContext();
        auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
        ScrollModel::GetInstance()->InitScrollBar(theme, barColor, barWidth, EdgeEffect::NONE);
        return;
    }

    auto scroller = FFIData::GetData<NativeNGScroller>(scrollerID);
    if (scroller == nullptr) {
        LOGE("invalid scrollerID");
        return;
    }
    ScrollModel::GetInstance()->Create();
    auto positionController = ScrollModel::GetInstance()->GetOrCreateController();
    scroller->SetController(positionController);
    auto proxy = scroller->GetScrollBarProxy();
    if (!proxy) {
        proxy = ScrollModel::GetInstance()->CreateScrollBarProxy();
        scroller->SetScrollBarProxy(proxy);
    }
    ScrollModel::GetInstance()->SetScrollBarProxy(proxy);
    std::pair<bool, Color> barColor;
    barColor.first = false;
    std::pair<bool, Dimension> barWidth;
    barWidth.first = false;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    ScrollModel::GetInstance()->InitScrollBar(theme, barColor, barWidth, EdgeEffect::NONE);
}

void FfiOHOSAceFrameworkScrollScrollable(int32_t scrollDirection)
{
    if (!Utils::CheckParamsValid(scrollDirection, AXIS.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }

    ScrollModel::GetInstance()->SetAxis(AXIS[scrollDirection]);
}

void FfiOHOSAceFrameworkScrollScrollBar(int32_t barState)
{
    if (!Utils::CheckParamsValid(barState, DISPLAY_MODE.size())) {
        LOGE("invalid value for DisplayMode");
        return;
    }
    ScrollModel::GetInstance()->SetDisplayMode(barState);
}

void FfiOHOSAceFrameworkScrollScrollBarColor(uint32_t color)
{
    ScrollModel::GetInstance()->SetScrollBarColor(Color(color));
}

void FfiOHOSAceFrameworkScrollSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state))
{
    auto lambda = [callback = CJLambda::Create(callback)](
                      const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        auto res = callback(offset.Value(), static_cast<int32_t>(state));
        ScrollFrameResult scrollRes { .offset = Dimension { res, DimensionUnit::VP } };
        return scrollRes;
    };
    ScrollModel::GetInstance()->SetOnScrollFrameBegin(lambda);
}

void FfiOHOSAceFrameworkScrollScrollBarWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    ScrollModel::GetInstance()->SetScrollBarWidth(value);
}

void FfiOHOSAceFrameworkScrollNestedScroll(int32_t scrollForward, int32_t scrollBackward)
{
    NestedScrollOptions localNestedScrollOptions = { .forward = NestedScrollMode(scrollForward),
        .backward = NestedScrollMode(scrollBackward) };
    ScrollModel::GetInstance()->SetNestedScroll(localNestedScrollOptions);
}

void FfiOHOSAceFrameworkScrollEnablePaging(bool enablePaging)
{
    ScrollModel::GetInstance()->SetEnablePaging(enablePaging);
}

void FfiOHOSAceFrameworkScrollInteraction(bool interaction)
{
    ScrollModel::GetInstance()->SetScrollEnabled(interaction);
}

void FfiOHOSAceFrameworkScrollFriction(double friction)
{
    ScrollModel::GetInstance()->SetFriction(friction);
}

void FfiOHOSAceFrameworkScrollEdgeEffect(int32_t edgeEffect, bool alwaysEnabled)
{
    ScrollModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
}

void FfiOHOSAceFrameworkScrollScrollsnap(ScrollSnapOptionsParams params)
{
    const auto& snapValue = *reinterpret_cast<std::vector<float>*>(params.vHandle);
    const auto& snapUnit = *reinterpret_cast<std::vector<int32_t>*>(params.pHandle);
    std::pair<bool, bool> enableSnapToSide = { params.enableSnapToStart, params.enableSnapToSEnd };

    std::vector<Dimension> snapPagination;
    CalcDimension intervalSize;
    if (params.isArry) {
        for (auto i = 0; i < params.size; i++) {
            auto pValue = snapValue[i];
            auto pUnit = static_cast<DimensionUnit>(snapUnit[i]);
            CalcDimension dms = Dimension(pValue, pUnit);
            snapPagination.push_back(dms);
        }
        intervalSize = CalcDimension(DEFAULT_DIMENSION_VALUE);
    } else {
        auto pValue = snapValue[SNAP_START_INDEX];
        auto pUnit = static_cast<DimensionUnit>(snapUnit[SNAP_START_INDEX]);
        intervalSize = Dimension(pValue, pUnit);
    }

    if (!CheckSnapPagination(snapPagination)) {
        std::vector<Dimension>().swap(snapPagination);
    }

    ScrollModel::GetInstance()->SetScrollSnap(
        static_cast<ScrollSnapAlign>(params.snapAlign), intervalSize, snapPagination, enableSnapToSide);
}

void FfiOHOSAceFrameworkScrollInitialOffset(float xOffsetValue, int32_t xUnit, float yOffsetValue, int32_t yUnit)
{
    CalcDimension xOffset = CalcDimension(xOffsetValue, static_cast<OHOS::Ace::DimensionUnit>(xUnit));
    CalcDimension yOffset = CalcDimension(yOffsetValue, static_cast<OHOS::Ace::DimensionUnit>(yUnit));
    ScrollModel::GetInstance()->SetInitialOffset(NG::OffsetT(xOffset, yOffset));
}

void FfiOHOSAceFrameworkScrollOnScroll(void (*callback)(CJOffset scrollInfo))
{
    ScrollModel::GetInstance()->SetOnScroll(
        [ffiOnScroll = CJLambda::Create(callback)](const Dimension& xOffset, const Dimension& yOffset) {
            CJOffset ffiScrollInfo;
            ffiScrollInfo.xOffset = xOffset.Value();
            ffiScrollInfo.yOffset = yOffset.Value();
            ffiOnScroll(ffiScrollInfo);
        });
}

void FfiOHOSAceFrameworkScrollOnWillScroll(
    CJOffset (*callback)(double xOffset, double yOffset, int32_t state, int32_t source))
{
    auto lambda = [callback = CJLambda::Create(callback)](const Dimension& xOffset, const Dimension& yOffset,
                      const ScrollState& state, const ScrollSource& source) -> NG::TwoDimensionScrollResult {
        NG::TwoDimensionScrollResult scrollRes { .xOffset = xOffset, .yOffset = yOffset };
        CJOffset res =
            callback(xOffset.Value(), yOffset.Value(), static_cast<int32_t>(state), static_cast<int32_t>(source));
        scrollRes.xOffset = Dimension { res.xOffset, DimensionUnit::VP };
        scrollRes.yOffset = Dimension { res.yOffset, DimensionUnit::VP };
        return scrollRes;
    };
    ScrollModel::GetInstance()->SetOnWillScroll(lambda);
}

void FfiOHOSAceFrameworkScrollOnDidScroll(void (*callback)(double xOffset, double yOffset, int32_t state))
{
    auto lambda = [callback = CJLambda::Create(callback)](
                      const Dimension& xOffset, const Dimension& yOffset, const ScrollState& state) {
        callback(xOffset.Value(), yOffset.Value(), static_cast<int32_t>(state));
    };
    ScrollModel::GetInstance()->SetOnDidScroll(lambda);
}

void FfiOHOSAceFrameworkScrollOnScrollEdge(void (*callback)(int32_t edge))
{
    ScrollModel::GetInstance()->SetOnScrollEdge(
        [ffiOnScrollEdge = CJLambda::Create(callback)](
            const NG::ScrollEdge& side) { ffiOnScrollEdge(static_cast<int32_t>(side)); });
}

void FfiOHOSAceFrameworkScrollOnScrollEnd(void (*callback)())
{
    ScrollModel::GetInstance()->SetOnScrollEnd(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkScrollOnScrollStart(void (*callback)())
{
    ScrollModel::GetInstance()->SetOnScrollStart(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkScrollOnScrollStop(void (*callback)())
{
    ScrollModel::GetInstance()->SetOnScrollStop(CJLambda::Create(callback));
}

int64_t FfiOHOSAceFrameworkScrollerCtor()
{
    auto nativeScroller = FFIData::Create<NativeNGScroller>();
    if (nativeScroller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return nativeScroller->GetID();
}

void FfiOHOSAceFrameworkScrollerScrollTo(int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit)
{
    double duration = 0.0;
    bool smooth = false;
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollTo(xValue, yValue, duration, curve, smooth, canOverScroll);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollToAnimation(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit, bool smooth)
{
    double duration = 0.0;
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollTo(xValue, yValue, duration, curve, smooth, canOverScroll);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollToAnimationOptions(int64_t selfID, double xOffset, int32_t xUnit, double yOffset,
    int32_t yUnit, double duration, const char* curve, bool canOverScroll)
{
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        bool hasDuration = true;
        if (Negative(duration)) {
            duration = DEFAULT_DURATION;
            hasDuration = false;
        }
        self_->ScrollTo(xValue, yValue, duration, CreateCurve(curve, false), !hasDuration, canOverScroll);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollBy(int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit)
{
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollBy(xValue, yValue);
    } else {
        LOGE("Scroll controller is null: invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollToIndex(
    int64_t selfID, int32_t index, bool smooth, int32_t align, double offset, int32_t unit)
{
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollToIndex(index, smooth, align, offset, unit);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollEdge(int64_t selfID, int32_t edge, float velocity)
{
    if (!Utils::CheckParamsValid(edge, SCROLL_EDGE_TYPES.size())) {
        LOGE("invalid value for DisplayMode");
        return;
    }
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollEdge(SCROLL_EDGE_TYPES[edge], velocity);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollFling(int64_t selfID, double velocity)
{
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollFling(velocity);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollPage(int64_t selfID, bool next, bool animation)
{
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollPage(next, animation);
    } else {
        LOGE("invalid scrollerID");
    }
}

CJOffset FfiOHOSAceFrameworkScrollerCurrentOffset(int64_t selfID)
{
    CJOffset cjOffset = { 0.0, 0.0 };
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        auto offset = self_->CurrentOffset();
        cjOffset.xOffset = offset.GetX();
        cjOffset.yOffset = offset.GetY();
    } else {
        LOGE("invalid scrollerID");
    }
    return cjOffset;
}

bool FfiOHOSAceFrameworkScrollerIsAtEnd(int64_t selfID)
{
    bool isAtEnd = false;
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        isAtEnd = self_->IsAtEnd();
    } else {
        LOGE("invalid scrollerID");
    }
    return isAtEnd;
}

CJRectResult FfiOHOSAceFrameworkScrollerGetItemRect(int64_t selfID, int32_t index)
{
    CJRectResult cjRectResult = { 0.0, 0.0, 0.0, 0.0 };
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        auto rectResult = self_->GetItemRect(index);
        cjRectResult.x = rectResult.Left();
        cjRectResult.y = rectResult.Top();
        cjRectResult.width = rectResult.Width();
        cjRectResult.height = rectResult.Height();
    } else {
        LOGE("invalid scrollerID");
    }
    return cjRectResult;
}

int32_t FfiOHOSAceFrameworkScrollerGetItemIndex(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit)
{
    int32_t res = -1;
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        res = self_->GetItemIndex(xValue, yValue);
    } else {
        LOGE("invalid scrollerID");
    }
    return res;
}
}
