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
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::FREE, Axis::NONE };
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<ScrollEdgeType> SCROLL_EDGE_TYPES = { ScrollEdgeType::SCROLL_TOP, ScrollEdgeType::SCROLL_NONE,
    ScrollEdgeType::SCROLL_BOTTOM, ScrollEdgeType::SCROLL_NONE, ScrollEdgeType::SCROLL_TOP, ScrollEdgeType::SCROLL_NONE,
    ScrollEdgeType::SCROLL_BOTTOM };
const std::vector<ScrollAlign> SCROLL_ALIGN_LIST = { ScrollAlign::START, ScrollAlign::CENTER, ScrollAlign::END,
    ScrollAlign::AUTO, ScrollAlign::NONE };
} // namespace

namespace OHOS::Ace::Framework {

NativeNGScroller::NativeNGScroller() : FFIData()
{
    LOGI("Scroller constructed: %{public}" PRId64, GetID());
}

void NativeNGScroller::ScrollTo(
    const Dimension& xOffset, const Dimension& yOffset, double duration, const RefPtr<Curve>& curve)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    auto direction = controller_->GetScrollDirection();
    auto position = direction == Axis::VERTICAL ? yOffset : xOffset;
    bool smooth = false;
    controller_->AnimateTo(position, duration, curve, smooth);
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

void NativeNGScroller::ScrollEdge(ScrollEdgeType edge)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    controller_->ScrollToEdge(edge, true);
}

void NativeNGScroller::ScrollPage(bool next)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    controller_->ScrollPage(!next, true);
}

void NativeNGScroller::ScrollToIndex(int32_t index, bool smooth, int32_t align)
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return;
    }
    controller_->ScrollToIndex(index, smooth, SCROLL_ALIGN_LIST[align]);
}

Offset NativeNGScroller::CurrentOffset()
{
    if (!controller_) {
        LOGE("controller_ is nullptr");
        return Offset(0.0, 0.0);
    }
    return controller_->GetCurrentOffset();
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
    auto lambda = [callback = CJLambda::Create(callback)](const Dimension& offset, const ScrollState& state)
     -> ScrollFrameResult {
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
    NestedScrollOptions localNestedScrollOptions = {.forward = NestedScrollMode(scrollForward),
        .backward = NestedScrollMode(scrollBackward)};
    ScrollModel::GetInstance()->SetNestedScroll(localNestedScrollOptions);
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
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollTo(xValue, yValue, 0.0, Curves::EASE);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollToByCurve(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit, double duration, const char* curve)
{
    Dimension xValue(xOffset, static_cast<DimensionUnit>(xUnit));
    Dimension yValue(yOffset, static_cast<DimensionUnit>(yUnit));
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollTo(xValue, yValue, duration, CreateCurve(curve, false));
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollBy(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit)
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
void FfiOHOSAceFrameworkScrollerScrollToIndex(int64_t selfID, int32_t index, bool smooth, int32_t align)
{
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollToIndex(index, smooth, align);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollEdge(int64_t selfID, int32_t edge)
{
    if (!Utils::CheckParamsValid(edge, SCROLL_EDGE_TYPES.size())) {
        LOGE("invalid value for DisplayMode");
        return;
    }
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollEdge(SCROLL_EDGE_TYPES[edge]);
    } else {
        LOGE("invalid scrollerID");
    }
}

void FfiOHOSAceFrameworkScrollerScrollPage(int64_t selfID, bool next)
{
    auto self_ = FFIData::GetData<NativeNGScroller>(selfID);
    if (self_ != nullptr) {
        self_->ScrollPage(next);
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
}
