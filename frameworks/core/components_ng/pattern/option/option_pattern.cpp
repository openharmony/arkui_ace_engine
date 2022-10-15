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

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
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

    auto action = hub->GetOnClick();
    RegisterOnClick(gestureHub, action);
    RegisterOnHover(gestureHub);
}

void OptionPattern::RegisterOnClick(const RefPtr<GestureEventHub>& hub, const std::function<void()>& action)
{
    auto host = GetHost();
    auto event = [host, action, targetId = targetId_](GestureEvent& /*info*/) {
        if (action) {
            LOGI("Option's JS callback executing");
            action();
        }
        // hide menu when option is clicked
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->HideMenu(targetId);
    };
    auto clickEvent = MakeRefPtr<ClickEvent>(std::move(event));
    hub->AddClickEvent(clickEvent);
}

void OptionPattern::RegisterOnHover(const RefPtr<GestureEventHub>& hub)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto touchCallback = [host, weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        // update hover status, repaint background color
        if (touchType == TouchType::DOWN) {
            LOGD("triggers option hover");
            auto paintProps = pattern->GetPaintProperty<OptionPaintProperty>();
            paintProps->UpdateHover(true);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

            // disable next option node's divider
            pattern->UpdateNextNodeDivider(false);
        }
        if (touchType == TouchType::UP) {
            auto paintProps = pattern->GetPaintProperty<OptionPaintProperty>();
            paintProps->UpdateHover(false);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

            pattern->UpdateNextNodeDivider(true);
        }
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    hub->AddTouchEvent(touchEvent);
}

void OptionPattern::UpdateNextNodeDivider(bool needDivider)
{
    auto host = GetHost();
    // find next option node from parent menuNode
    auto nextNode = host->GetParent()->GetChildAtIndex(index_ + 1);
    if (nextNode) {
        if (!InstanceOf<FrameNode>(nextNode)) {
            LOGW("next optionNode is not a frameNode! type = %{public}s", nextNode->GetTag().c_str());
            return;
        }
        auto props = DynamicCast<FrameNode>(nextNode)->GetPaintProperty<OptionPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateNeedDivider(needDivider);
        nextNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void OptionPattern::SetFontSize(const Dimension& value) {
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateFontSize(value);
}

void OptionPattern::SetItalicFontStyle(const Ace::FontStyle& value) {
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateItalicFontStyle(value);
}

void OptionPattern::SetFontWeight(const FontWeight& value) {
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateFontWeight(value);
}

void OptionPattern::SetFontFamily(const std::vector<std::string>& value) {
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateFontFamily(value);
}

void OptionPattern::SetFontColor(const Color& color) {
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateTextColor(color);
}

} // namespace OHOS::Ace::NG