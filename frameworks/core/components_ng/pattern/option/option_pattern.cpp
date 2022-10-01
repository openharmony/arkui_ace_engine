/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/option/option_pattern.h"

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void OptionPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<OptionEventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    
    // register touch event
    auto action = hub->GetOnClick();
    auto touchCallback = [host, weak = WeakClaim(this), action](const TouchEventInfo& info) {
        auto optionPattern = weak.Upgrade();
        CHECK_NULL_VOID(optionPattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        // change option background color on touch
        if (touchType == TouchType::DOWN) {
            LOGI("triggers hover");
            auto paintProps = optionPattern->GetPaintProperty<OptionPaintProperty>();
            paintProps->UpdateHover(true);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        if (touchType == TouchType::UP) {
            // action();

            auto paintProps = optionPattern->GetPaintProperty<OptionPaintProperty>();
            paintProps->UpdateHover(false);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent);
    LOGD("touch event registered");
}

} // namespace OHOS::Ace::NG