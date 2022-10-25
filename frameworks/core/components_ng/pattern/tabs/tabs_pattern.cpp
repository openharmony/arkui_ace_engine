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

#include "core/components_ng/pattern/tabs/tabs_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void TabsPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void TabsPattern::SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    auto tabsNode = GetHost();
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(tabBarNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().back());
    CHECK_NULL_VOID(swiperNode);

    ChangeEvent changeEvent([tabBarNode, jsEvent = std::move(event)](int32_t index) {
        /* Update tabBar indicator */
        auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
        layoutProperty->UpdateIndicator(index);
        RectF rect = layoutProperty->GetIndicatorRect(index);
        auto paintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
        paintProperty->UpdateIndicator(rect);
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

        /* js callback */
        if (jsEvent) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);
        }
    });

    if (onChangeEvent_) {
        (*onChangeEvent_).swap(changeEvent);
    } else {
        onChangeEvent_ = std::make_shared<ChangeEvent>(changeEvent);
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->AddOnChangeEvent(onChangeEvent_);
    }
}

void TabsPattern::OnModifyDone()
{
    if (onChangeEvent_) {
        return;
    }
    SetOnChangeEvent(nullptr);
}

} // namespace OHOS::Ace::NG
