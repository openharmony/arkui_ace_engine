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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scrollbar_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL };
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkScrollBarCreate(int64_t scrollerID, int32_t direction, int32_t state)
{
    if (!Utils::CheckParamsValid(direction, AXIS.size())) {
        LOGE("invalid value for DisplayMode");
        return;
    }
    if (!Utils::CheckParamsValid(state, DISPLAY_MODE.size())) {
        LOGE("invalid value for DisplayMode");
        return;
    }
    auto scroller = FFIData::GetData<NativeNGScroller>(scrollerID);
    if (scroller == nullptr) {
        LOGE("invalid id to create Scroller");
        return;
    }
    auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(scroller->GetScrollBarProxy());

    bool infoflag = true;
    bool proxyFlag = true;
    auto proxy = ScrollBarModel::GetInstance()->GetScrollBarProxy(scrollBarProxy);

    ScrollBarModel::GetInstance()->Create(proxy, infoflag, proxyFlag, direction, state);
}

void FfiOHOSAceFrameworkSetEnableNestedScroll(bool value)
{
    ScrollBarModel::GetInstance()->SetEnableNestedScroll(value);
}
}