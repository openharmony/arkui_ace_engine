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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SWIPER_CONTROLLER_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SWIPER_CONTROLLER_H

#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components/swiper/swiper_component.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeSwiperController : public OHOS::FFI::FFIData {
DECL_TYPE(NativeSwiperController, OHOS::FFI::FFIData)
public:
    NativeSwiperController();
    ~NativeSwiperController() override;
    void ShowNext();
    void ShowPrevious();
    void FinishAnimation();
    void FinishAnimationWithCallback(const std::function<void()>& callback);
    void SetController(const RefPtr<SwiperController>& controller);
    void ChangeIndex(int32_t index, bool useAnimation);
private:
    RefPtr<SwiperController> controller_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SWIPER_CONTROLLER_H
