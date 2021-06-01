/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/display/render_display.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"

namespace OHOS::Ace {

void RenderDisplay::Update(const RefPtr<Component>& component)
{
    const RefPtr<DisplayComponent> display = AceType::DynamicCast<DisplayComponent>(component);
    if (!display) {
        LOGE("RenderDisplay update with nullptr");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    visible_ = display->GetVisible();
    double opacity = std::min(std::max(display->GetOpacity(), 0.0), 1.0);
    if (disableLayer_ != display->IsDisableLayer()) {
        // recover opacity in child
        UpdateOpacity(UINT8_MAX);
        disableLayer_ = display->IsDisableLayer();
    }
    if (!IsDeclarativeAnimationActive()) {
        opacity_ = static_cast<uint8_t>(round(opacity * UINT8_MAX));
    }
    SetShadow(display->GetShadow());
    MarkNeedLayout();
}

void RenderDisplay::PerformLayout()
{
    LayoutParam layoutParam = GetLayoutParam();
    if (visible_ == VisibleType::GONE) {
        layoutParam.SetMinSize(Size());
        layoutParam.SetMaxSize(Size());
    }
    Size childSize;
    if (!GetChildren().empty()) {
        GetChildren().front()->Layout(layoutParam);
        childSize = GetChildren().front()->GetLayoutSize();
    }
    SetLayoutSize(childSize);
}

void RenderDisplay::GetOpacityCallbacks()
{
    opacityCallbacks_.clear();
    if (!disableLayer_) {
        return;
    }
    GetDomOpacityCallbacks(GetNodeId(), opacityCallbacks_);
}

void RenderDisplay::Dump()
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc(std::string("Display: ").append(visible_ == VisibleType::VISIBLE ? "visible" :
            visible_ == VisibleType::INVISIBLE ? "invisible" : "gone"));
    }
}

bool RenderDisplay::GetVisible() const
{
    return RenderNode::GetVisible() && visible_ == VisibleType::VISIBLE;
}

} // namespace OHOS::Ace