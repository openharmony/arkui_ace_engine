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

#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MenuItemPattern::OnModifyDone()
{
    RegisterOnClick();
    RegisterOnTouch();
    RegisterOnHover();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    RegisterOnKeyEvent(focusHub);

    auto eventHub = host->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->IsEnabled()) {
        CHECK_NULL_VOID(content_);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        auto contentProperty = content_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(contentProperty);
        contentProperty->UpdateTextColor(theme->GetDisabledMenuFontColor());
    }
    if (IsSelectIconShow()) {
        AddSelectIcon();
    }
}

void MenuItemPattern::OnMountToParentDone()
{
    ModifyFontSize();
}

RefPtr<FrameNode> MenuItemPattern::GetMenuWrapper()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

RefPtr<FrameNode> MenuItemPattern::GetMenu()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void MenuItemPattern::ShowSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("MenuItemPattern::ShowSubMenu menu item id is %{public}d", host->GetId());
    auto buildFunc = GetSubBuilder();
    if (buildFunc && !isSubMenuShowed_) {
        isSubMenuShowed_ = true;

        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        auto subMenu = MenuView::Create(customNode, host->GetId(), MenuType::SUB_MENU);
        auto menuPattern = subMenu->GetPattern<MenuPattern>();
        menuPattern->SetParentMenuItem(host);
        subMenuId_ = subMenu->GetId();
        AddSelfHoverRegion(host);
        auto menuWrapper = GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapper);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        menuWrapperPattern->AddSubMenuId(host->GetId());
        subMenu->MountToParent(menuWrapper);

        OffsetF offset = GetSubMenuPostion(host);

        auto menuProps = subMenu->GetLayoutProperty<MenuLayoutProperty>();
        CHECK_NULL_VOID(menuProps);
        menuProps->UpdateMenuOffset(offset);
        menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        RegisterWrapperMouseEvent();

        auto focusHub = subMenu->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->RequestFocus();
    }
}

void MenuItemPattern::CloseMenu()
{
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->HideMenu();
}

void MenuItemPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<MenuItemEventHub>();

    auto event = [onChange = hub->GetOnChange(), weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetChange();
        if (onChange) {
            LOGI("trigger onChange");
            onChange(pattern->IsSelected());
        }

        if (pattern->GetSubBuilder() != nullptr) {
            pattern->ShowSubMenu();
            return;
        }

        // hide menu when menu item is clicked
        pattern->CloseMenu();
    };
    auto clickEvent = MakeRefPtr<ClickEvent>(std::move(event));

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddClickEvent(clickEvent);
}

void MenuItemPattern::RegisterOnTouch()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnPress(info);
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent);
}

void MenuItemPattern::RegisterOnHover()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHover);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent);
    inputHub->SetHoverEffect(HoverEffectType::BOARD);
}

void MenuItemPattern::RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

void MenuItemPattern::OnPress(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        auto clickedColor = theme->GetClickedColor();
        UpdateBackgroundColor(clickedColor);
    } else if (touchType == TouchType::UP) {
        auto bgColor = theme->GetBackgroundColor();
        UpdateBackgroundColor(bgColor);
    }
}

void MenuItemPattern::OnHover(bool isHover)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (isHover || isSubMenuShowed_) {
        auto hoverColor = theme->GetHoverColor();
        UpdateBackgroundColor(hoverColor);

        ShowSubMenu();
    } else {
        auto bgColor = theme->GetBackgroundColor();
        UpdateBackgroundColor(bgColor);
    }
}

bool MenuItemPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((event.code == KeyCode::KEY_DPAD_RIGHT || event.code == KeyCode::KEY_ENTER ||
            event.code == KeyCode::KEY_SPACE) &&
        !isSubMenuShowed_) {
        ShowSubMenu();
        return true;
    }
    return false;
}

void MenuItemPattern::RegisterWrapperMouseEvent()
{
    auto menuWrapper = GetMenuWrapper();
    if (menuWrapper && !wrapperMouseEvent_) {
        auto inputHub = menuWrapper->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);

        auto mouseTask = [weak = WeakClaim(this), menuWrapperPattern](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (menuWrapperPattern) {
                menuWrapperPattern->HandleMouseEvent(info, pattern);
            }
        };
        wrapperMouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
        inputHub->AddOnMouseEvent(wrapperMouseEvent_);
    }
}

void MenuItemPattern::AddSelfHoverRegion(const RefPtr<FrameNode>& targetNode)
{
    OffsetF topLeftPoint;
    OffsetF bottomRightPoint;
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    topLeftPoint = targetNode->GetPaintRectOffset();
    bottomRightPoint = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), frameSize.Height());
    AddHoverRegions(topLeftPoint, bottomRightPoint);
}

OffsetF MenuItemPattern::GetSubMenuPostion(const RefPtr<FrameNode>& targetNode)
{
    // show menu at left top point of targetNode
    OffsetF position;
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    position = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), 0.0);
    return position;
}

void MenuItemPattern::AddHoverRegions(const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint)
{
    TouchRegion hoverRegion = TouchRegion(
        Offset(topLeftPoint.GetX(), topLeftPoint.GetY()), Offset(bottomRightPoint.GetX(), bottomRightPoint.GetY()));
    hoverRegions_.emplace_back(hoverRegion);
    LOGI("MenuItemPattern::AddHoverRegions hoverRegion is %{private}s to %{private}s", topLeftPoint.ToString().c_str(),
        bottomRightPoint.ToString().c_str());
}

bool MenuItemPattern::IsInHoverRegions(double x, double y)
{
    for (auto hoverRegion : hoverRegions_) {
        if (hoverRegion.ContainsInRegion(x, y)) {
            return true;
        }
    }
    return false;
}

void MenuItemPattern::UpdateBackgroundColor(const Color& color)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(color);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuItemPattern::AddSelectIcon()
{
    auto host = GetHost();
    auto row = host->GetChildAtIndex(0);
    CHECK_NULL_VOID(row);
    if (IsSelected() && !selectIcon_) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_VOID(iconTheme);
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::MENU_OK_SVG);
        ImageSourceInfo imageSourceInfo;
        imageSourceInfo.SetSrc(iconPath);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        imageSourceInfo.SetFillColor(Color::BLACK);

        auto selectIcon = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(selectIcon);
        auto props = selectIcon->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateImageSourceInfo(imageSourceInfo);
        props->UpdateAlignment(Alignment::CENTER);
        CalcSize idealSize = { CalcLength(selectTheme->GetIconSideLength()),
            CalcLength(selectTheme->GetIconSideLength()) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        props->UpdateCalcLayoutProperty(layoutConstraint);

        auto iconRenderProperty = selectIcon->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(iconRenderProperty);
        iconRenderProperty->UpdateSvgFillColor(Color::BLACK);

        selectIcon->MountToParent(row, 0);
        selectIcon->MarkModifyDone();

        selectIcon_ = selectIcon;
    }
    if (!IsSelected() && selectIcon_) {
        row->RemoveChildAtIndex(0);
        selectIcon_ = nullptr;
    }
}

void MenuItemPattern::ModifyFontSize()
{
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuFontSize = menuPattern->FontSize();

    ModifyFontSize(menuFontSize);
}

void MenuItemPattern::ModifyFontSize(const Dimension& fontSize)
{
    CHECK_NULL_VOID(content_);
    auto contentProperty = content_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(contentProperty);
    contentProperty->UpdateFontSize(fontSize);
    content_->MarkModifyDone();

    CHECK_NULL_VOID(label_);
    auto labelProperty = label_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(labelProperty);
    labelProperty->UpdateFontSize(fontSize);
    label_->MarkModifyDone();
}
} // namespace OHOS::Ace::NG
