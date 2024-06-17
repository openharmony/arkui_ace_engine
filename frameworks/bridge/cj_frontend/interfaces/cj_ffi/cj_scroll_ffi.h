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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SCROLL_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SCROLL_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeNGScroller : public OHOS::FFI::FFIData {
    DECL_TYPE(Scroller, OHOS::FFI::FFIData)
public:
    NativeNGScroller();

    void ScrollTo(
        const Dimension& xOffset, const Dimension& yOffset, double duration, const RefPtr<Curve>& curve);
    void ScrollEdge(ScrollEdgeType edge);
    void ScrollPage(bool next);
    void ScrollBy(const Dimension& xOffset, const Dimension& yOffset);
    void ScrollToIndex(int32_t index, bool smooth, int32_t align);
    Offset CurrentOffset();

    RefPtr<ScrollControllerBase>& GetController()
    {
        return controller_;
    }

    void SetController(const RefPtr<ScrollControllerBase>& controller)
    {
        controller_ = controller;
    }

    void SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy)
    {
        scrollBarProxy_ = proxy;
    }

    const RefPtr<ScrollProxy>& GetScrollBarProxy()
    {
        return scrollBarProxy_;
    }

private:
    RefPtr<ScrollControllerBase> controller_;
    RefPtr<ScrollProxy> scrollBarProxy_;
};

} // namespace OHOS::Ace::Framework

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkScrollCreate(int64_t scrollerID);
CJ_EXPORT void FfiOHOSAceFrameworkScrollScrollable(int32_t scrollDirection);
CJ_EXPORT void FfiOHOSAceFrameworkScrollScrollBar(int32_t barState);
CJ_EXPORT void FfiOHOSAceFrameworkScrollScrollBarColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkScrollScrollBarWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkScrollNestedScroll(int32_t scrollForward, int32_t scrollBackward);
CJ_EXPORT void FfiOHOSAceFrameworkScrollOnScroll(void (*callback)(CJOffset offset));
CJ_EXPORT void FfiOHOSAceFrameworkScrollOnScrollEdge(void (*callback)(int32_t edge));
CJ_EXPORT void FfiOHOSAceFrameworkScrollOnScrollEnd(void (*callback)());
CJ_EXPORT int64_t FfiOHOSAceFrameworkScrollerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkScrollerScrollTo(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkScrollerScrollToByCurve(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit, double duration, const char* curve);
CJ_EXPORT void FfiOHOSAceFrameworkScrollerScrollBy(
    int64_t selfID, double xOffset, int32_t xUnit, double yOffset, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkScrollerScrollEdge(int64_t selfID, int32_t edge);
CJ_EXPORT void FfiOHOSAceFrameworkScrollerScrollToIndex(int64_t selfID, int32_t index, bool smooth, int32_t align);
CJ_EXPORT void FfiOHOSAceFrameworkScrollerScrollPage(int64_t selfID, bool next);
CJ_EXPORT void FfiOHOSAceFrameworkScrollSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state));
CJ_EXPORT CJOffset FfiOHOSAceFrameworkScrollerCurrentOffset(int64_t selfID);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SCROLL_FFI_H
