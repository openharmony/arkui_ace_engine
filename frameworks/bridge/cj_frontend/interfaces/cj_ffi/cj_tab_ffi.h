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

#ifndef OHOS_ACE_FRAMEWORK_FFI_CJ_TAB_H
#define OHOS_ACE_FRAMEWORK_FFI_CJ_TAB_H

#include <cstdint>

#include "ffi_remote_data.h"

#include "base/memory/referenced.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_transitioneffect.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components/tab_bar/tab_controller.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
#include "core/components_ng/property/transition_property.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT TabsController : public OHOS::FFI::FFIData {
    DECL_TYPE(TabsController, OHOS::FFI::FFIData)
public:
    TabsController();
    virtual ~TabsController();
    void ChangeIndex(int32_t index);
    void PreloadItems(std::set<int32_t> indexSet);
    void SetTabBarTranslate(NG::TranslateOptions options);
    void SetTabBarOpacity(double opacity);
    const RefPtr<TabController>& GetController() const
    {
        return controller_;
    }

    void SetSwiperController(const RefPtr<NG::TabsControllerNG>& swiperController)
    {
        swiperController_ = swiperController;
    }

    const RefPtr<NG::TabsControllerNG>& GetSwiperController() const
    {
        return swiperController_;
    }

private:
    RefPtr<TabController> controller_;
    RefPtr<NG::TabsControllerNG> swiperController_; // used by ng structure
};

class ACE_EXPORT CJTabContentTransitionProxy : public OHOS::FFI::FFIData {
    DECL_TYPE(CJTabContentTransitionProxy, OHOS::FFI::FFIData)
public:
    explicit CJTabContentTransitionProxy(const RefPtr<TabContentTransitionProxy>& proxy)
    {
        proxy_ = proxy;
    }

    int32_t getFromIndex()
    {
        return proxy_->GetFromIndex();
    }

    int32_t getToIndex()
    {
        return proxy_->GetToIndex();
    }

    void finishTransition()
    {
        proxy_->FinishTransition();
    }

private:
    RefPtr<TabContentTransitionProxy> proxy_;
};
} // namespace OHOS::Ace::Framework

using VectorInt32Ptr = void*;
using VectorFloat32Ptr = void*;

extern "C" {
struct CJTabsScrollableBarModeOptions {
    double margin;
    int32_t marginUnit;
    int32_t nonScrollableLayoutStyle;
};

struct CJTabsDividerStyle {
    double strokeWidth;
    int32_t strokeWidthUnit;
    uint32_t color;
    double startMargin;
    int32_t startMarginUnit;
    double endMargin;
    int32_t endMarginUnit;
};

struct CJTabsBlurOptions {
    VectorFloat32Ptr grayscale;
};

struct CJTabsBarBackgroundBlurStyleOptions {
    int32_t colorMode;
    int32_t adaptiveColor;
    CJTabsBlurOptions blurOptions;
    float scale;
    int32_t policy;
    uint32_t inactiveColor;
};

struct CJTabsBarGridColumnOptions {
    double margin;
    int32_t marginUnit;
    double gutter;
    int32_t gutterUnit;
    int32_t sm;
    int32_t md;
    int32_t lg;
};

struct CJTabsBackgroundEffectOptions {
    double radius;
    double saturation;
    double brightness;
    uint32_t color;
    int32_t adaptiveColor;
    CJTabsBlurOptions blurOptions;
    int32_t policy;
    uint32_t inactiveColor;
};

struct CJTabsAnimationEvent {
    float currentOffset;
    float targetOffset;
    float velocity;
};

typedef void (*TransitionFunc)(int32_t from, int32_t to, int64_t id);
struct CJTabContentAnimatedTransition {
    int32_t timeout;
    TransitionFunc transition;
    bool isUndefined;
};

CJ_EXPORT void FfiOHOSAceFrameworkTabsCreate(int32_t barPosition, int64_t controllerId, int32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkTabsPop();
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarMode(int32_t barMode);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarModeWithOptions(int32_t barMode, CJTabsScrollableBarModeOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetIndex(int32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetVertical(bool isVertical);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetScrollable(bool isScrollable);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetAnimationDuration(float duration);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetAnimateMode(int32_t animateMode);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarPosition(int32_t barPosition);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetDivider(CJTabsDividerStyle dividerStyle);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetFadingEdge(bool fadingEdge);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarOverlap(bool barOverlap);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarBackgroundColor(uint32_t backgroundColor);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarBackgroundBlurStyle(int32_t blurStyle);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarBackgroundBlurStyleWithOptions(
    int32_t blurStyle, CJTabsBarBackgroundBlurStyleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarGridAlign(CJTabsBarGridColumnOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetEdgeEffect(int32_t edgeEffect);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarBackgroundEffect(CJTabsBackgroundEffectOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnChange(void (*callback)(int32_t index));
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnTabBarClick(void (*callback)(int32_t index));
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnAnimationStart(
    void (*callback)(int32_t index, int32_t targetIndex, CJTabsAnimationEvent event));
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnAnimationEnd(void (*callback)(int32_t index, CJTabsAnimationEvent event));
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnGestureSwipe(void (*callback)(int32_t index, CJTabsAnimationEvent event));
CJ_EXPORT void FfiOHOSAceFrameworkTabsCustomContentTransition(
    CJTabContentAnimatedTransition (*callback)(int32_t from, int32_t to));
CJ_EXPORT void FfiOHOSAceFrameworkTabsCustomAnimationFinishTransition(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnContentWillChange(bool (*callback)(int32_t currentIndex, int32_t comingIndex));
CJ_EXPORT int64_t FfiOHOSAceFrameworkTabsControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkTabsControllerChangeIndex(int64_t self, int32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkTabsControllerPreloadItems(int64_t selfId, VectorInt32Ptr indices);
CJ_EXPORT void FfiOHOSAceFrameworkTabsControllerSetTabBarTranslate(
    int64_t selfId, OHOS::Ace::Framework::CTranslateOptions translate);
CJ_EXPORT void FfiOHOSAceFrameworkTabsControllerSetTabBarOpacity(int64_t selfId, double opacity);
CJ_EXPORT void FfiOHOSAceFrameworkTabContentCreate();
CJ_EXPORT void FfiOHOSAceFrameworkTabContentPop();
CJ_EXPORT void FfiOHOSAceFrameworkTabContentSetTabBar(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkTabContentSetTabBarWithIcon(const char* icon, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkTabContentSetTabBarWithComponent(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkTabContentOnWillShow(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkTabContentOnWillHide(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkTabContentPUCreate(void (*callback)());
}

#endif
