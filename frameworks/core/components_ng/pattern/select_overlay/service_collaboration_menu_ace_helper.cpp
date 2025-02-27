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

#include <cstdint>
#include "base/utils/utils.h"
#ifndef PREVIEW

#include "core/components_ng/pattern/select_overlay/service_collaboration_menu_ace_helper.h"

#include "base/geometry/calc_dimension.h"
#include "base/image/pixel_map.h"
#include "base/json/json_util.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/placement.h"
#include "core/components/divider/divider_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "frameworks/core/pipeline/base/element_register.h"
#include "frameworks/base/thread/cancelable_callback.h"
#include "core/components/common/properties/popup_param.h"
#include "image_source.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t TOAST_DURATION = 2000;
const std::string END_ICON_PATH = "resource:///ohos_ic_public_cancel.svg";
} // namespace

void ServiceCollaborationMenuAceHelper::CreateText(
    const std::string& value, const RefPtr<FrameNode>& parent, const Color& color, bool needMargin, bool hasEndIcon)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "text is %{public}s", value.c_str());
    auto textPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(textPipeline);
    auto textTheme = textPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(textTheme);
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(textNode);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProperty);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProperty->UpdateFontSize(textTheme->GetMenuFontSize());
    textProperty->UpdateFontWeight(FontWeight::REGULAR);
    textProperty->UpdateTextColor(color);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateForegroundColor(color);
    textProperty->UpdateContent(value);
    if (needMargin) {
        MarginProperty margin;
        margin.right = CalcLength(
            static_cast<float>(hasEndIcon ? TEXT_RIGHT_MARGIN : TEXT_RIGHT_MARGIN_NO_ENDICON), DimensionUnit::VP);
        margin.left = CalcLength(static_cast<float>(TEXT_LEFT_MARGIN));
        textProperty->UpdateMargin(margin);
    }
    textNode->MountToParent(parent);
    textNode->MarkModifyDone();
}
void ServiceCollaborationMenuAceHelper::CreateHeaderText(
    const std::string& value, const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& menuItemGroupNode)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter, text is %{public}s", value.c_str());
    auto textPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(textPipeline);
    auto textTheme = textPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(textTheme);
    auto richTheme = textPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richTheme);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(textNode);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProperty);
    textProperty->UpdateFontSize(Dimension(static_cast<float>(HEADER_TEXT_FONT_SIZE), DimensionUnit::FP));
    textProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textProperty->UpdateTextColor(textTheme->GetSecondaryFontColor());
    textProperty->UpdateMaxLines(HEADER_TEXT_MAX_LINE);
    textProperty->UpdateEllipsisMode(EllipsisMode::TAIL);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProperty->UpdateWordBreak(WordBreak::BREAK_ALL);
    textProperty->UpdateCalcMinSize(
        CalcSize(CalcLength(static_cast<float>(HEADER_MIN_WIDTH)), CalcLength(static_cast<float>(HEADER_MIN_HEIGHT))));
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateForegroundColor(richTheme->GetMenuTitleColor());
    textProperty->UpdateContent(value);
    MarginProperty margin;
    margin.right = CalcLength(static_cast<float>(HEADER_MARGIN_LEFT));
    margin.left = CalcLength(static_cast<float>(HEADER_MARGIN_RIGHT));
    margin.top = CalcLength(static_cast<float>(HEADER_MARGIN_TOP));
    margin.bottom = CalcLength(static_cast<float>(HEADER_MARGIN_BOTTOM));
    textProperty->UpdateMargin(margin);
    textNode->MountToParent(row);
    auto menuItemGroupPattern = menuItemGroupNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(menuItemGroupPattern);
    menuItemGroupPattern->AddHeaderContent(textNode);
    menuItemGroupPattern->AddHeader(row);
    textNode->MarkModifyDone();
}
void ServiceCollaborationMenuAceHelper::CreateEndIcon(uint32_t iconId, const RefPtr<FrameNode>& parent)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter, icon is %{public}d", iconId);
    auto iconPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(iconPipeline);
    auto iconTheme = iconPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto richTheme = iconPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richTheme);
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(iconNode);
    auto iconProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(iconProperty);
    iconProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(iconId));
    iconProperty->UpdateSymbolColorList({ richTheme->GetMenuIconColor() });
    iconProperty->UpdateFontSize(iconTheme->GetIconSideLength());
    iconProperty->UpdateAlignment(Alignment::CENTER);
    iconNode->MountToParent(parent);
    iconNode->MarkModifyDone();
}
void ServiceCollaborationMenuAceHelper::CreateStartIcon(uint32_t iconId, const RefPtr<FrameNode>& parent)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter, icon is %{public}d", iconId);
    auto iconPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(iconPipeline);
    auto iconTheme = iconPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto richTheme = iconPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richTheme);
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(iconNode);
    auto iconProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(iconProperty);
    iconProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(iconId));
    iconProperty->UpdateSymbolColorList({ richTheme->GetMenuIconColor() });
    iconProperty->UpdateFontSize(iconTheme->GetIconSideLength());
    iconProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.right = CalcLength(iconTheme->GetIconContentPadding());
    margin.left = CalcLength(-2.0f);
    iconProperty->UpdateMargin(margin);
    iconNode->MountToParent(parent, 0);
    iconNode->MarkModifyDone();
}
RefPtr<FrameNode> ServiceCollaborationMenuAceHelper::CreateMainMenuItem(
    const std::string& value, const std::string& iconType, const Color& color, bool needEndIcon)
{
    auto textPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(textPipeline, nullptr);
    auto selectTheme = textPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, nullptr);
    auto richTheme = textPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richTheme, nullptr);
    auto mainMenuItem = CreateMainMenuItem(
        value, GetSymbolId(iconType), richTheme->GetMenuTextColor(), needEndIcon);
    CHECK_NULL_RETURN(mainMenuItem, nullptr);
    if (!needEndIcon) {
        auto leftRow = DynamicCast<FrameNode>(mainMenuItem->GetChildAtIndex(0));
        CHECK_NULL_RETURN(leftRow, nullptr);
        auto textNode = DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->GetRenderContext()->UpdateOpacity(selectTheme->GetDisabledFontColorAlpha());
        textNode->MarkModifyDone();
    }
    return mainMenuItem;
}
RefPtr<FrameNode> ServiceCollaborationMenuAceHelper::CreateMainMenuItem(
    const std::string& value, uint32_t iconId, const Color& color, bool needEndIcon)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter");
    auto menuPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(menuPipeline, nullptr);
    auto menuTheme = menuPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(menuTheme, nullptr);
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    menuItemPattern->onClickEventSet_ = true;
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), menuItemPattern);
    CHECK_NULL_RETURN(menuItemNode, nullptr);
    auto menuItemProperty = menuItemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_RETURN(menuItemProperty, nullptr);
    menuItemProperty->UpdatePadding({ .right = CalcLength(2.0f) });
    auto renderContext = menuItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(menuTheme->GetMenuDefaultInnerRadius()));
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);
    auto rowProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProperty, nullptr);
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(rightRow, nullptr);
    auto rightRowProperty = rightRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rightRowProperty, nullptr);
    rightRowProperty->UpdatePadding({ .right = CalcLength(22.0f) });
    auto paintProperty = menuItemNode->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    paintProperty->UpdateStrokeWidth(Dimension(static_cast<float>(BORDER_WIDTH), DimensionUnit::PX));
    paintProperty->UpdateStartMargin(Dimension(12.0f, DimensionUnit::VP));
    paintProperty->UpdateEndMargin(Dimension(12.0f, DimensionUnit::VP));
    paintProperty->UpdateDividerColor(menuTheme->GetLineColor());
    rowProperty->UpdateCalcMinSize(
        CalcSize(CalcLength(static_cast<float>(MENUITEM_WIDTH), DimensionUnit::VP),
        CalcLength(static_cast<float>(MENUITEM_HEIGHT), DimensionUnit::VP)));
    CreateText(value, row, color, true, needEndIcon);
    row->MountToParent(menuItemNode);
    row->MarkModifyDone();
    if (needEndIcon) {
        CreateEndIcon(iconId, rightRow);
        rightRow->MountToParent(menuItemNode);
        rightRow->MarkModifyDone();
    }
    menuItemNode->MarkModifyDone();
    menuItemNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return menuItemNode;
}
uint32_t ServiceCollaborationMenuAceHelper::GetSymbolId(const std::string& abilityType)
{
    auto iconPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(iconPipeline, 0);
    auto richTheme = iconPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richTheme, 0);
    if (abilityType == "CAMERA") {
        return richTheme->GetCameraSymbolId();
    }
    if (abilityType == "SCAN") {
        return richTheme->GetScanSymbolId();
    }
    if (abilityType == "IMAGE_PICKER") {
        return richTheme->GetImageSymbolId();
    }
    if (abilityType == "CHEVRON_RIGHT") {
        return richTheme->GetChevronRightSymbolId();
    }
    return 0;
}
RefPtr<FrameNode> ServiceCollaborationMenuAceHelper::CreateDeviceMenuItem(
    const std::string& value, uint32_t iconId)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter iconId is %{public}d, value is %{public}s", iconId, value.c_str());
    auto menuPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(menuPipeline, nullptr);
    auto menuTheme = menuPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(menuTheme, nullptr);
    auto richTheme = menuPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richTheme, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuItemPattern>());
    CHECK_NULL_RETURN(menuItemNode, nullptr);
    auto renderContext = menuItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(menuTheme->GetMenuDefaultInnerRadius()));
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);
    auto rowProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProperty, nullptr);
    MarginProperty margin;
    margin.top = CalcLength(static_cast<float>(MENUITEM_MARGIN));
    margin.bottom = CalcLength(static_cast<float>(MENUITEM_MARGIN));
    rowProperty->UpdateMargin(margin);
    auto menuHeight = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
        ? menuTheme->GetMenuChildMinHeight().ConvertToPx()
        : menuTheme->GetOptionMinHeight().ConvertToPx();
    rowProperty->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(menuHeight)));
    CreateStartIcon(iconId, row);
    CreateText(value, row, richTheme->GetMenuTextColor(), false, false);
    row->MountToParent(menuItemNode);
    row->MarkModifyDone();
    return menuItemNode;
}
void ServiceCollaborationMenuAceHelper::RemoveSubmenu(const RefPtr<FrameNode>& menuWrapper)
{
    CHECK_NULL_VOID(!mainMenuIsHover_);
    CHECK_NULL_VOID(menuWrapper);
    auto childrenList = menuWrapper->GetChildren();
    for (const auto& children : childrenList) {
        if (children == nullptr) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(children);
        auto pattern = frameNode->GetPattern<MenuPattern>();
        if (!pattern) {
            continue;
        }
        if (pattern && pattern->GetTargetTag() == SUN_MENU_TAG) {
            menuWrapper->RemoveChild(children);
            subMenuIsShow_ = false;
        }
    }
}
    void ServiceCollaborationMenuAceHelper::SubMenuDown(const RefPtr<FrameNode>& menuWrapper)
{
    CHECK_NULL_VOID(menuWrapper);
    auto childrenList = menuWrapper->GetChildren();
    for (const auto& children : childrenList) {
        if (!children) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(children);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<MenuPattern>();
        if (!pattern) {
            continue;
        }
        if (pattern && pattern->GetTargetTag() == SUN_MENU_TAG) {
            menuWrapper->RemoveChild(children);
            subMenuIsShow_ = false;
        }
    }
}
RefPtr<FrameNode> ServiceCollaborationMenuAceHelper::CreateMenuNode()
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter");
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<InnerMenuPattern>(INNER_MENU_ID, V2::MENU_ETS_TAG, MenuType::MULTI_MENU));
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, nullptr);
    menuLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    menuNode->MarkModifyDone();
    return menuNode;
}
RefPtr<FrameNode> ServiceCollaborationMenuAceHelper::CreateMenuItemGroupNode(
    uint32_t index, const std::string& deviceName)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter");
    auto menuItemGroupNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemGroupPattern>();});
    CHECK_NULL_RETURN(menuItemGroupNode, nullptr);
    auto menuItemGroupPaintPros = menuItemGroupNode->GetPaintProperty<MenuItemGroupPaintProperty>();
    CHECK_NULL_RETURN(menuItemGroupPaintPros, nullptr);
    menuItemGroupPaintPros->UpdateStrokeWidth(Dimension(static_cast<float>(0), DimensionUnit::VP));

    TAG_LOGI(AceLogTag::ACE_MENU, "DEVICE NAME IS %{public}s", deviceName.c_str());
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);
    auto rowProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProperty, nullptr);
    MarginProperty margin;
    margin.right = CalcLength(static_cast<float>(GROUP_MARGIN), DimensionUnit::VP);
    margin.left = CalcLength(static_cast<float>(GROUP_MARGIN), DimensionUnit::VP);
    rowProperty->UpdateCalcMinSize(
        CalcSize(CalcLength(static_cast<float>(GROUP_MIN_WIDTH), DimensionUnit::VP), std::nullopt));
    
    if (index > 0) {
        BorderWidthProperty borderWidth;
        borderWidth.topDimen = Dimension(static_cast<float>(BORDER_WIDTH), DimensionUnit::VP);
        BorderWidthProperty borderWidth1;
        borderWidth1.UpdateWithCheck(borderWidth);
        rowProperty->UpdateBorderWidth(borderWidth1);
        auto context = row->GetRenderContext();
        CHECK_NULL_RETURN(context, nullptr);
        context->UpdateBorderWidth(borderWidth1);
        auto menuPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(menuPipeline, nullptr);
        auto menuTheme = menuPipeline->GetTheme<SelectTheme>();
        CHECK_NULL_RETURN(menuTheme, nullptr);
        BorderColorProperty borderColorProperty;
        borderColorProperty.SetColor(menuTheme->GetLineColor());
        context->UpdateBorderColor(borderColorProperty);
    }
    rowProperty->UpdateMargin(margin);
    CreateHeaderText(deviceName, row, menuItemGroupNode);

    auto focusHub = row->GetFocusHub();
    focusHub->SetEnabled(false);
    menuItemGroupNode->MarkModifyDone();
    menuItemGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return menuItemGroupNode;
}


RefPtr<FrameNode> ServiceCollaborationMenuAceHelper::CreateSubDeviceOutMenu(
    const RefPtr<FrameNode>& innerMenu, const RefPtr<FrameNode>& menuWrapper)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "CreateSubDeviceMenuOnCol");
    MenuParam param;
    param.type = MenuType::SUB_MENU;
    param.isShowInSubWindow = false;
    auto subMenu = MenuView::Create(innerMenu, SUB_MENU_ID, SUN_MENU_TAG, param);
    auto inputHub = subMenu->GetOrCreateInputEventHub();
    CHECK_NULL_RETURN(inputHub, nullptr);
    auto mouseTask = [weakHelper = WeakClaim(this), weakMenuWrapper = WeakClaim(RawPtr(menuWrapper))](bool isHover) {
        auto helper = weakHelper.Upgrade();
        CHECK_NULL_VOID(helper);
        TAG_LOGI(AceLogTag::ACE_MENU, "mouseTask, isHover=%{public}d", isHover);
        if (isHover) {
            helper->subMenuIsHover_ = true;
            return;
        }
        helper->subMenuIsHover_ = false;
        ContainerScope scope(Container::CurrentIdSafely());
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto cancelableCallback = [weakHelper, weakMenuWrapper, instanceId = Container::CurrentIdSafely()] {
            auto helper = weakHelper.Upgrade();
            auto menuWrapper = weakMenuWrapper.Upgrade();
            CHECK_NULL_VOID(helper && menuWrapper);
            ContainerScope scope(instanceId);
            helper->RemoveSubmenu(menuWrapper);
        };
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            cancelableCallback, TaskExecutor::TaskType::UI, 100, "ArkUIRichEditorRemoveMenuNode");
    };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(hoverEvent);
    return subMenu;
}

void ServiceCollaborationMenuAceHelper::SubMeunMountToMainMenu(
    const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& menuWrapper,
    std::function<RefPtr<FrameNode>(void)> subDeviceMenuCreator)
{
    AddHoverEventToMainMenu(menuNode, menuWrapper, subDeviceMenuCreator);
    AddClickEventToMainMenu(menuNode, menuWrapper, subDeviceMenuCreator);
}

void ServiceCollaborationMenuAceHelper::AddHoverEventToMainMenu(
    const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& menuWrapper,
    std::function<RefPtr<FrameNode>(void)> subDeviceMenuCreator)
{
    auto inputHub = menuNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weakHelper = WeakClaim(this), weakMenuWrapper = WeakClaim(RawPtr(menuWrapper)),
                      weakMenuNode = WeakClaim(RawPtr(menuNode)), subDeviceMenuCreator](bool isHover) {
        auto menuItemNode = weakMenuNode.Upgrade();
        auto menuWrapper = weakMenuWrapper.Upgrade();
        auto helper = weakHelper.Upgrade();
        CHECK_NULL_VOID(menuItemNode && menuWrapper && helper);
        if (isHover) {
            helper->mainMenuIsHover_ = true;
            if (!helper->subMenuIsShow_) {
                TAG_LOGI(AceLogTag::ACE_MENU, "create SubMenu enter.1");
                auto subMenu = subDeviceMenuCreator();
                CHECK_NULL_VOID(subMenu);
                TAG_LOGI(AceLogTag::ACE_MENU, "create SubMenu enter.2");
                auto submenuPattern = subMenu->GetPattern<MenuPattern>();
                CHECK_NULL_VOID(submenuPattern);
                submenuPattern->SetParentMenuItem(menuItemNode);
                subMenu->MountToParent(menuWrapper);
                auto menuProps = subMenu->GetLayoutProperty<MenuLayoutProperty>();
                auto frameSize = menuItemNode->GetGeometryNode()->GetMarginFrameSize();
                OffsetF position = menuItemNode->GetPaintRectOffset(false, true) + OffsetF(frameSize.Width(), 0.0);
                menuProps->UpdateMenuOffset(position);
                subMenu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
                helper->subMenuIsShow_ = true;
            }
            return;
        }
        TAG_LOGI(AceLogTag::ACE_MENU, "remove SubMenu enter.");
        helper->mainMenuIsHover_ = false;
        // timeout 100ms to RemoveChild
        ContainerScope scope(Container::CurrentIdSafely());
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto cancelableCallback = [weakHelper, weakMenuWrapper, instanceId = Container::CurrentIdSafely()] {
            auto menuWrapper = weakMenuWrapper.Upgrade();
            auto helper = weakHelper.Upgrade();
            ContainerScope scope(instanceId);
            if (!helper->subMenuIsHover_) {
                helper->SubMenuDown(menuWrapper);
            }
        };
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            cancelableCallback, TaskExecutor::TaskType::UI, 100, "ArkUIRichEditorRemoveMenuNode");
    };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(hoverEvent);
}

void ServiceCollaborationMenuAceHelper::AddClickEventToMainMenu(
    const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& menuWrapper,
    std::function<RefPtr<FrameNode>(void)> subDeviceMenuCreator)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "Service Collaborationfwk mainMenu clickTask enter");
    auto gestureHub = menuNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto clickTask = [weakHelper = WeakClaim(this), weakMenuWrapper = WeakClaim(RawPtr(menuWrapper)),
                      weakMenuNode = WeakClaim(RawPtr(menuNode)), subDeviceMenuCreator](GestureEvent& event) {
        TAG_LOGI(AceLogTag::ACE_MENU, "menuitem clickTask enter");
        auto menuItemNode = weakMenuNode.Upgrade();
        auto menuWrapper = weakMenuWrapper.Upgrade();
        auto helper = weakHelper.Upgrade();
        CHECK_NULL_VOID(menuItemNode && menuWrapper && helper);
        helper->subMenuIsShow_ = false;
        if (!helper->subMenuIsShow_) {
            TAG_LOGI(AceLogTag::ACE_MENU, "clickTask create SubMenu enter.1");
            auto subMenu = subDeviceMenuCreator();
            CHECK_NULL_VOID(subMenu);
            TAG_LOGI(AceLogTag::ACE_MENU, "clickTask create SubMenu enter.2");
            auto submenuPattern = subMenu->GetPattern<MenuPattern>();
            CHECK_NULL_VOID(submenuPattern);
            submenuPattern->SetParentMenuItem(menuItemNode);
            subMenu->MountToParent(menuWrapper);
            auto menuProps = subMenu->GetLayoutProperty<MenuLayoutProperty>();
            auto frameSize = menuItemNode->GetGeometryNode()->GetMarginFrameSize();
            OffsetF position = menuItemNode->GetPaintRectOffset(false, true) + OffsetF(frameSize.Width(), 0.0);
            menuProps->UpdateMenuOffset(position);
            subMenu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
            helper->subMenuIsShow_ = true;
        }
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(clickEvent);
}

// Callback

void ServiceCollaborationAceCallback::CreateText(const std::string& value, const RefPtr<FrameNode>& parent)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter, text is %{public}s", value.c_str());
    auto textPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(textPipeline);
    auto textTheme = textPipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(textTheme);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(textNode);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProperty);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProperty->UpdateFontSize(Dimension(static_cast<double>(TEXT_FONT_SIZE), DimensionUnit::VP));
    textProperty->UpdateFontWeight(FontWeight::REGULAR);
    textProperty->UpdateTextColor(textTheme->GetMenuFontColor());
    textProperty->UpdateCalcMaxSize(
        CalcSize(CalcLength(static_cast<float>(TEXT_MAX_WIDTH)), CalcLength(static_cast<float>(TEXT_MAX_HIGHT))));
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateForegroundColor(textTheme->GetMenuFontColor());
    textProperty->UpdateContent(value);
    MarginProperty margin;
    margin.top = CalcLength(static_cast<float>(TEXT_MARGIN_TOP), DimensionUnit::VP);
    margin.bottom = CalcLength(static_cast<float>(TEXT_MARGIN_BOTTOM), DimensionUnit::VP);
    textProperty->UpdateMargin(margin);
    textNode->MountToParent(parent);
    textNode->MarkModifyDone();
}

void ServiceCollaborationAceCallback::AddMouseEventToEndIcon(const RefPtr<FrameNode>& iconNode)
{
    auto inputHub = iconNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto gestureHub = iconNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto mouseTask = [weakHelper = WeakClaim(this), node = WeakClaim(RawPtr(iconNode))](bool isHover) {
        auto helper = weakHelper.Upgrade();
        auto iconNode = node.Upgrade();
        CHECK_NULL_VOID(helper && iconNode);
        auto iconContext = iconNode->GetRenderContext();
        CHECK_NULL_VOID(iconContext);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        if (isHover) {
            TAG_LOGI(AceLogTag::ACE_MENU, "hover");
            helper->endIconIsHover_ = isHover;
            iconContext->UpdateBackgroundColor(theme->GetHoverColor());
        } else {
            TAG_LOGI(AceLogTag::ACE_MENU, "leave");
            helper->endIconIsHover_ = isHover;
            iconContext->UpdateBackgroundColor(Color::TRANSPARENT);
        }
    };
    auto touchCallback = [weakHelper = WeakClaim(this), node = WeakClaim(RawPtr(iconNode))]
        (const TouchEventInfo& info) {
        auto helper = weakHelper.Upgrade();
        auto iconNode = node.Upgrade();
        CHECK_NULL_VOID(helper && iconNode);
        auto iconContext = iconNode->GetRenderContext();
        CHECK_NULL_VOID(iconContext);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN) {
            iconContext->UpdateBackgroundColor(theme->GetClickedColor());
        }
        if (touchType == TouchType::UP) {
            iconContext->UpdateBackgroundColor(helper->endIconIsHover_ ? theme->GetHoverColor() : Color::TRANSPARENT);
        }
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    inputHub->AddOnHoverEvent(hoverEvent);
    gestureHub->AddTouchEvent(touchEvent);
}

void ServiceCollaborationAceCallback::CreateEndIcon(const std::string& icon, const RefPtr<FrameNode>& parent)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter, icon is %{public}s", icon.c_str());
    auto iconPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(iconPipeline);
    auto iconTheme = iconPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_VOID(iconNode);
    auto iconProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(iconProperty);
    ImageSourceInfo info(icon);
    info.SetFillColor(iconTheme->GetPopIconColor());
    iconProperty->UpdateImageSourceInfo(info);
    iconProperty->UpdateUserDefinedIdealSize(
        CalcSize(
            CalcLength(static_cast<float>(ENDICON_SIZE), DimensionUnit::VP),
            CalcLength(static_cast<float>(ENDICON_SIZE), DimensionUnit::VP)
        )
    );
    iconProperty->UpdatePadding({ .left = CalcLength(static_cast<float>(ICON_PADDING), DimensionUnit::VP),
        .right = CalcLength(static_cast<float>(ICON_PADDING), DimensionUnit::VP),
        .top = CalcLength(static_cast<float>(ICON_PADDING), DimensionUnit::VP),
        .bottom = CalcLength(static_cast<float>(ICON_PADDING), DimensionUnit::VP) });
    iconProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.right = CalcLength(static_cast<float>(ENDICON_MARGIN_FIVE), DimensionUnit::VP);
    margin.left = CalcLength(static_cast<float>(ENDICON_MARGIN_THREE), DimensionUnit::VP);
    margin.top = CalcLength(static_cast<float>(ENDICON_MARGIN_TOP), DimensionUnit::VP);
    margin.bottom = CalcLength(static_cast<float>(ENDICON_MARGIN), DimensionUnit::VP);
    iconProperty->UpdateMargin(margin);
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>([weakCallback = WeakClaim(this)](GestureEvent& event) {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        ContainerScope scope(Container::CurrentIdSafely());
        callback->RemovePopupNode();
    });
    auto gestureHub = iconNode->GetOrCreateGestureEventHub();
    gestureHub->AddClickEvent(clickEvent);
    iconNode->MountToParent(parent);
    iconNode->MarkModifyDone();
    auto iconContext = iconNode->GetRenderContext();
    CHECK_NULL_VOID(iconContext);
    BorderRadiusProperty border(Dimension(static_cast<float>(ICON_BORDER_RADIUS), DimensionUnit::VP));
    iconContext->UpdateBorderRadius(border);
    AddMouseEventToEndIcon(iconNode);
}

void ServiceCollaborationAceCallback::CreateStartIcon(uint32_t iconId, const RefPtr<FrameNode>& parent)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "enter, iconId is %{public}d", iconId);
    auto iconPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(iconPipeline);
    auto iconTheme = iconPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(iconNode);
    auto iconProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(iconProperty);
    iconProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(iconId));
    iconProperty->UpdateSymbolColorList({ iconTheme->GetPopIconColor() });
    iconProperty->UpdateFontSize(Dimension(static_cast<float>(STARTICON_SIZE), DimensionUnit::VP));
    iconProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.right = CalcLength(static_cast<float>(STARTICON_MARGIN), DimensionUnit::VP);
    margin.left = CalcLength(static_cast<float>(STARTICON_MARGIN), DimensionUnit::VP);
    margin.top = CalcLength(static_cast<float>(STARTICON_MARGIN), DimensionUnit::VP);
    margin.bottom = CalcLength(static_cast<float>(STARTICON_MARGIN), DimensionUnit::VP);
    iconProperty->UpdateMargin(margin);
    iconNode->MountToParent(parent, 0);
    iconNode->MarkModifyDone();
}

uint32_t ServiceCollaborationAceCallback::GetSymbolId(const std::string& abilityType)
{
    auto iconPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(iconPipeline, 0);
    auto richTheme = iconPipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richTheme, 0);
    if (abilityType == "CAMERA") {
        return richTheme->GetCameraSymbolId();
    }
    if (abilityType == "SCAN") {
        return richTheme->GetScanSymbolId();
    }
    if (abilityType == "IMAGE_PICKER") {
        return richTheme->GetImageSymbolId();
    }
    return 0;
}

RefPtr<FrameNode> ServiceCollaborationAceCallback::CreateCustomPopUpNode(
    const std::string& value, const std::string& icon)
{
    if (!row_) {
        auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(row, nullptr);
        auto rowProperty = row->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(rowProperty, nullptr);
        CreateStartIcon(GetSymbolId(ability_), row);
        CreateText(value, row);
        CreateEndIcon(END_ICON_PATH, row);
        row_ = row;
        row_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        return row_;
    }
    auto childrenList = row_->GetChildren();
    for (const auto& children : childrenList) {
        auto frameNode = AceType::DynamicCast<FrameNode>(children);
        if (frameNode && frameNode->GetTag() == V2::TEXT_ETS_TAG) {
            auto textProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
            textProperty->UpdateContent(value);
        }
    }
    row_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    return row_;
}

void ServiceCollaborationAceCallback::RemovePopupNode()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto overlay = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlay);
    CHECK_NULL_VOID(info_);
    CHECK_NULL_VOID(info_->pattern.Upgrade());
    CHECK_NULL_VOID(info_->pattern.Upgrade()->GetHost());
    auto pattern = AceType::DynamicCast<RichEditorPattern>(info_->pattern.Upgrade());
    CHECK_NULL_VOID(pattern);
    pattern->RegisterCaretChangeListener(nullptr);
    auto targetId = info_->pattern.Upgrade()->GetHost()->GetId();
    auto popupInfo = overlay->GetPopupInfo(targetId);
    popupInfo.markNeedUpdate = true;
    overlay->HidePopup(targetId, popupInfo);
    CHECK_NULL_VOID(menuHelper_);
    menuHelper_->photoCount_ = 0;
}

RefPtr<PopupParam> ServiceCollaborationAceCallback::GetPopupParam(bool isShow, StateChangeFunc& onStateChange)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ViewStackModel::GetInstance()->NewScope();
    popupParam->SetIsShow(isShow);
    Offset offset = { position_.GetX(), position_.GetY() };
    popupParam->SetTargetOffset(offset);
    popupParam->SetPlacement(Placement::TOP);
    popupParam->SetEnableArrow(true);
    popupParam->SetUseCustomComponent(true);
    popupParam->SetBackgroundColor(Color::WHITE);
    popupParam->SetTargetSpace(Dimension(static_cast<float>(TARGET_SPACE), DimensionUnit::VP));
    popupParam->SetOnStateChange(
        [weakHelper = WeakClaim(this), onStateChange](const std::string& isShow) {
        auto helper = weakHelper.Upgrade();
        CHECK_NULL_VOID(helper);
        bool show = JsonUtil::ParseJsonString(isShow)->GetBool("isVisible");
        if (!show && !helper->isMultiImage_) {
            onStateChange(isShow);
        }
    });
    Shadow shadow;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, popupParam);
    auto colorMode = container->GetColorMode();
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, popupParam);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, popupParam);
    shadow =  shadowTheme->GetShadow(ShadowStyle::OuterDefaultSM, colorMode);
    popupParam->SetShadow(shadow);
    return popupParam;
}

int32_t ServiceCollaborationAceCallback::OnEvent(uint32_t code, uint32_t eventId, std::string &category,
    StateChangeFunc& onStateChange_)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "code is %{public}d, msg is %{public}s.", code, category.c_str());
    ContainerScope scope(Container::CurrentIdSafely());
    CHECK_NULL_RETURN(info_, -1);
    if (code == PROCES_PREPARE) {
        position_ = AceType::DynamicCast<RichEditorPattern>(info_->pattern.Upgrade())->GetCaretRect().GetOffset();
        auto popupParam = GetPopupParam(true, onStateChange_);
        auto pattern = AceType::DynamicCast<RichEditorPattern>(info_->pattern.Upgrade());
        std::function<void(int32_t)> func = [weak = WeakClaim(this)](int32_t num) {
            auto callback = weak.Upgrade();
            CHECK_NULL_VOID(callback);
            if (!callback->isTransmit_) {
                callback->RemovePopupNode();
                callback->info_ = nullptr;
            }
        };
        pattern->RegisterCaretChangeListener(std::move(func));
        auto row = CreateCustomPopUpNode(category, "");
        CHECK_NULL_RETURN(row, -1);
        ViewAbstract::BindPopup(popupParam, info_->pattern.Upgrade()->GetHost(), row);
        return 0;
    }
    if (code == PHOTO_SENDING) {
        auto popupParam = GetPopupParam(true, onStateChange_);
        auto row = CreateCustomPopUpNode(category, "");
        ViewAbstract::BindPopup(popupParam, info_->pattern.Upgrade()->GetHost(), row);
        return 0;
    }
    if (code == MULTI_PHOTO_SENDING_BACK) {
        if (!isMultiImage_) {
            isMultiImage_ = true;
            RemovePopupNode();
        }
        return 0;
    }
    if (code == REMOTE_CANCEL) {
        RemovePopupNode();
        info_ = nullptr;
        return 0;
    }
    isMultiImage_ = false;
    RemovePopupNode();
    auto toastPipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(toastPipeline, -1);
    auto overlay = toastPipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlay, -1);
    overlay->ShowToast({ .message = category, .duration = TOAST_DURATION, .alignment = -1 }, nullptr);
    info_ = nullptr;
    return 0;
}

RefPtr<PixelMap> ServiceCollaborationAceCallback::CreatePixelMap(void *buffer, uint32_t code, uint32_t dataLength)
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    auto imageSource = OHOS::Media::ImageSource::CreateImageSource((uint8_t *)buffer, dataLength, opts, errorCode);
    if (errorCode != 0) {
        TAG_LOGE(AceLogTag::ACE_MENU, "CreateImageSource from buffer failed.");
        return nullptr;
    }
    CHECK_NULL_RETURN(imageSource, nullptr);
    Media::DecodeOptions decodeOpts;
    std::shared_ptr<Media::PixelMap> pixelMap = imageSource->CreatePixelMap(decodeOpts, errorCode);
    if (errorCode != 0) {
        TAG_LOGE(AceLogTag::ACE_MENU, "CreatePixelMap failed.");
        return nullptr;
    }
    CHECK_NULL_RETURN(pixelMap, nullptr);
    auto imagePix = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
    return imagePix;
}

int32_t ServiceCollaborationAceCallback::OnDataCallback(uint32_t code, uint32_t collaborationId,
    uint32_t dataLength, std::unique_ptr<char[]>& data)
{
    CHECK_NULL_RETURN(menuHelper_, -1);
    ContainerScope scope(Container::CurrentIdSafely());
    CHECK_NULL_RETURN(info_, -1);
    isTransmit_ = true;
    TAG_LOGI(AceLogTag::ACE_MENU, "code is %{public}d, dataLength is %{public}d.", code, dataLength);
    auto imagePix = CreatePixelMap((void *)data.get(), code, dataLength);
    CHECK_NULL_RETURN(imagePix, -1);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, -1);
    CancelableCallback<void()> caretTwinklingTask;
    caretTwinklingTask.Reset([weakCallback = WeakClaim(this), code, imagePix,
        instanceId = Container::CurrentIdSafely(), weakHelper = WeakClaim(RawPtr(menuHelper_))] {
        auto callback = weakCallback.Upgrade();
        auto helper = weakHelper.Upgrade();
        CHECK_NULL_VOID(callback && imagePix && callback->info_);
        auto richEditorPattern = DynamicCast<RichEditorPattern>(callback->info_->pattern.Upgrade());
        CHECK_NULL_VOID(richEditorPattern);
        ContainerScope scope(instanceId);
        ImageSpanOptions options;
        options.imagePixelMap = imagePix;
        options.offset = richEditorPattern->GetCaretPosition() + helper->photoCount_;
        auto width = imagePix->GetWidth();
        auto height = imagePix->GetHeight();
        helper->photoCount_++;
        ImageSpanAttribute attr = {
            .size = ImageSpanSize{ .width = CalcDimension(width), .height = CalcDimension(height) } };
        options.imageAttribute = attr;
        if (!callback->info_->pattern.Upgrade()) {
            TAG_LOGE(AceLogTag::ACE_MENU, "info_->pattern.Upgrade() is nullptr.");
            return;
        }
        if (!richEditorPattern->GetTextSelector().SelectNothing()) {
            richEditorPattern->DeleteBackward(1);
        }
        richEditorPattern->AddImageSpan(options, false, 0, false);
        if (code == SEND_PHOTO_SUCCESS) {
            richEditorPattern->SetCaretPosition(richEditorPattern->GetCaretPosition() + helper->photoCount_);
            callback->RemovePopupNode();
            callback->isTransmit_ = false;
            callback->info_ = nullptr;
            callback->isMultiImage_ = false;
        }
    });
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, -1);
    taskExecutor->PostTask(caretTwinklingTask, TaskExecutor::TaskType::UI, "ArkUIRichEditorAddImageSpan",
                           PriorityType::VIP);
    return 0;
}
} // namespace OHOS::Ace::NG
#endif