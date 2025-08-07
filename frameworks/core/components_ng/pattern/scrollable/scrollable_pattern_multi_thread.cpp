/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/point.h"
#include "base/log/dump_log.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/multi_thread.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/recorder/event_definition.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/manager/select_overlay/select_overlay_scroll_notifier.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/pipeline_ng/pipeline_context.h"

#ifdef ARKUI_CIRCLE_FEATURE
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#endif // ARKUI_CIRCLE_FEATURE

namespace OHOS::Ace::NG {
namespace {

} // namespace

void ScrollablePattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // do nothing unsafe thread
}
void ScrollablePattern::OnAttachToFrameNodeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

void ScrollablePattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UnRegister2DragDropManager(AceType::RawPtr(host));
    auto context = host->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    context->RemoveWindowStateChangedCallback(host->GetId());
}

void ScrollablePattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // moving from OnAttachToFrame to here
    host->GetRenderContext()->UpdateClipEdge(true);
    auto scrollBarProxy = scrollBarProxy_;
    CHECK_NULL_VOID(scrollBarProxy);
    auto enableNestScroll = scrollBarProxy->IsNestScroller();
    if (enableNestScroll) {
        SearchAndSetParentNestedScroll(host);
    }
}

void ScrollablePattern::ScrollPageMultiThread(bool reverse, bool smooth, AccessibilityScrollType scrollType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), reverse, smooth, scrollType]() {
        auto pattern = weak.Upgrade();
        float distance = reverse ? pattern->GetMainContentSize() : -(pattern->GetMainContentSize());
        if (scrollType == AccessibilityScrollType::SCROLL_HALF) {
            distance = distance / 2.f;
        }
        if (smooth) {
            float position = -(pattern->GetTotalOffset()) + distance;
            pattern->AnimateTo(-position, -1, nullptr, true, false, false);
        } else {
            pattern->StopAnimate();
            pattern->UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
        }
    });
}
} // namespace OHOS::Ace::NG
