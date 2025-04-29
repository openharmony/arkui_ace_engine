/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/models/scroll_bar_model_impl.h"

#include "base/geometry/axis.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::NONE };
}

RefPtr<ScrollProxy> ScrollBarModelImpl::GetScrollBarProxy(const RefPtr<ScrollProxy>& scrollProxy)
{
    auto proxy = AceType::DynamicCast<ScrollBarProxy>(scrollProxy);
    if (!proxy) {
        proxy = AceType::MakeRefPtr<ScrollBarProxy>();
    }

    return proxy;
}

void ScrollBarModelImpl::Create(const RefPtr<ScrollProxy>& proxy, bool infoflag, bool proxyFlag,
    int directionValue, int stateValue, bool isCreateArc)
{
    RefPtr<Component> child;
    auto scrollBarComponent = AceType::MakeRefPtr<OHOS::Ace::ScrollBarComponent>(child);

    if (infoflag) {
        if (proxyFlag) {
            auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(proxy);
            scrollBarComponent->SetScrollBarProxy(scrollBarProxy);
        }

        if (directionValue > -1 && directionValue < static_cast<int>(AXIS.size())) {
            scrollBarComponent->SetAxis(AXIS[directionValue]);
        }

        if (stateValue > -1 && stateValue < static_cast<int>(DISPLAY_MODE.size())) {
            scrollBarComponent->SetDisplayMode(DISPLAY_MODE[stateValue]);
        }
    }

    ViewStackProcessor::GetInstance()->ClaimElementId(scrollBarComponent);
    ViewStackProcessor::GetInstance()->Push(scrollBarComponent);
    ViewStackProcessor::GetInstance()->GetDisplayComponent();
}
} // namespace OHOS::Ace::Framework
