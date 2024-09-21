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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components/tab_bar/tab_controller.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT TabsController : public OHOS::FFI::FFIData {
DECL_TYPE(TabsController, OHOS::FFI::FFIData)
public:
    TabsController();
    virtual ~TabsController();
    void ChangeIndex(int32_t index);
    const RefPtr<TabController>& GetController() const
    {
        return controller_;
    }

    void SetSwiperController(const RefPtr<SwiperController>& swiperController)
    {
        swiperController_ = swiperController;
    }

    const RefPtr<SwiperController>& GetSwiperController() const
    {
        return swiperController_;
    }

private:
    RefPtr<TabController> controller_;
    RefPtr<SwiperController> swiperController_; // used by ng structure
};
}

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkTabsCreate(int32_t barPosition, int64_t controllerId, int32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkTabsPop();
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetBarMode(int32_t barMode);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetIndex(int32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetVertical(bool isVertical);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetScrollable(bool isScrollable);
CJ_EXPORT void FfiOHOSAceFrameworkTabsSetAnimationDuration(float duration);
CJ_EXPORT void FfiOHOSAceFrameworkTabsOnChange(void (*callback)(int32_t index));
CJ_EXPORT int64_t FfiOHOSAceFrameworkTabsControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkTabsControllerChangeIndex(int64_t self, int32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkTabContentCreate();
CJ_EXPORT void FfiOHOSAceFrameworkTabContentPop();
CJ_EXPORT void FfiOHOSAceFrameworkTabContentSetTabBar(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkTabContentSetTabBarWithIcon(const char* icon, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkTabContentSetTabBarWithComponent(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkTabContentPUCreate(void (*callback)());
}

#endif
