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

#include "bridge/declarative_frontend/jsview/models/sliding_panel_model_impl.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/panel/sliding_panel_component_v2.h"

namespace OHOS::Ace::Framework {

void SlidingPanelModelImpl::Create(bool isShow)
{
    auto slidingPanel = AceType::MakeRefPtr<SlidingPanelComponentV2>();
    ViewStackProcessor::GetInstance()->ClaimElementId(slidingPanel);
    slidingPanel->SetHasDragBar(true);
    ViewStackProcessor::GetInstance()->Push(slidingPanel);
    slidingPanel->SetVisible(isShow);
    auto component = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(component);
    if (!display) {
        LOGE("display is null");
        return;
    }
    display->SetVisible(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
}

void SlidingPanelModelImpl::SetPanelMode(PanelMode mode)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetMode(mode);
    }
}

void SlidingPanelModelImpl::SetPanelType(PanelType type)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetType(type);
    }
}

void SlidingPanelModelImpl::SetHasDragBar(bool hasDragBar)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetHasDragBar(hasDragBar);
    }
}

void SlidingPanelModelImpl::SetMiniHeight(const Dimension& miniHeight)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetMiniHeight(std::pair(miniHeight, true));
    }
}

void SlidingPanelModelImpl::SetHalfHeight(const Dimension& halfHeight)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetHalfHeight(std::pair(halfHeight, true));
    }
}

void SlidingPanelModelImpl::SetFullHeight(const Dimension& fullHeight)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetFullHeight(std::pair(fullHeight, true));
    }
}

void SlidingPanelModelImpl::SetIsShow(bool isShow)
{
    auto component = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(component);
    if (!display) {
        LOGE("display is null");
        return;
    }
    display->SetVisible(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    auto panelComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(panelComponent);
    if (!panel) {
        LOGE("Panel is null");
        return;
    }
    panel->SetVisible(isShow);
}

void SlidingPanelModelImpl::SetBackgroundMask(const Color& backgroundMask)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (!panel) {
        LOGE("Panel is null");
        return;
    }

    auto displayComponent = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(displayComponent);
    if (!display) {
        LOGE("display is null");
        return;
    }
    display->SetBackgroundMask(backgroundMask);
}

void SlidingPanelModelImpl::SetBackgroundColor(const Color& backgroundColor)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto box = SlidingPanelModelImpl::GetPanelBox();
    if (!panel || !box) {
        LOGE("Not valid type for SlidingPanel");
        return;
    }
    box->SetColor(backgroundColor);
    panel->SetHasBgStyle(true);
    panel->SetHasDecorationStyle(true);
}

void SlidingPanelModelImpl::SetOnSizeChange(std::function<void(const BaseEventInfo*)>&& changeEvent)
{
    auto onSizeChange = EventMarker(changeEvent);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetOnSizeChanged(onSizeChange);
    }
}

void SlidingPanelModelImpl::SetOnHeightChange(std::function<void(const float)>&& onHeightChange)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetOnHeightChanged(onHeightChange);
    }
}

void SlidingPanelModelImpl::Pop()
{
    JSContainerBase::Pop();
}

void SlidingPanelModelImpl::SetBorderColor(const Color& borderColor)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto decoration = SlidingPanelModelImpl::GetPanelDecoration();
    if (!panel || !decoration) {
        return;
    }
    auto border = decoration->GetBorder();
    border.SetColor(borderColor);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
}

void SlidingPanelModelImpl::SetBorderWidth(const Dimension& borderWidth)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto decoration = SlidingPanelModelImpl::GetPanelDecoration();
    if (!panel || !decoration) {
        return;
    }
    auto border = decoration->GetBorder();
    border.SetWidth(borderWidth);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
}

void SlidingPanelModelImpl::SetBorderStyle(const BorderStyle& borderStyle)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto decoration = SlidingPanelModelImpl::GetPanelDecoration();
    if (!panel || !decoration) {
        return;
    }
    auto border = decoration->GetBorder();
    border.SetStyle(borderStyle);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
}

void SlidingPanelModelImpl::SetBorder(const BorderStyle& borderStyle, const Dimension& borderWidth)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    if (!panel) {
        LOGE("Panel is Null");
        return;
    }
    auto decoration = SlidingPanelModelImpl::GetPanelDecoration();
    auto border = decoration->GetBorder();
    border.SetStyle(borderStyle);
    border.SetWidth(borderWidth);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
}

RefPtr<BoxComponent> SlidingPanelModelImpl::GetPanelBox()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    if (!panel) {
        return nullptr;
    }
    if (panel->HasBoxStyle()) {
        return panel->GetBoxStyle();
    } else {
        panel->SetHasBoxStyle(true);
        auto box = AceType::MakeRefPtr<BoxComponent>();
        panel->SetBoxStyle(box);
        return box;
    }
}

RefPtr<Decoration> SlidingPanelModelImpl::GetPanelDecoration()
{
    auto box = SlidingPanelModelImpl::GetPanelBox();
    if (!box) {
        return nullptr;
    }
    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }
    return decoration;
}
} // namespace OHOS::Ace::Framework