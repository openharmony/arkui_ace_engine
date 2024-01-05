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

#include "core/components_ng/pattern/app_bar/app_bar_view.h"

#include <map>

#include "base/utils/utils.h"
#include "base/want/want_wrap.h"
#include "core/common/app_bar_helper.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {

const Dimension MARGIN_TEXT_LEFT = 24.0_vp;
const Dimension MARGIN_TEXT_RIGHT = 84.0_vp;
const Dimension MARGIN_BUTTON = 12.0_vp;
const Dimension MARGIN_BACK_BUTTON_RIGHT = -20.0_vp;
const float REVERSED_X = -1.0f;
const float UNCHANGED_X = 1.0f;
const float UNCHANGED_Y = 1.0f;
constexpr int32_t LABLE_ROWSIZE = 2;

bool HasNavigation(const RefPtr<UINode>& node)
{
    if (node->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
        return true;
    }
    const auto& children = node->GetChildren();
    return std::any_of(children.begin(), children.end(), [](const auto& node) { return HasNavigation(node); });
}
} // namespace

RefPtr<FrameNode> AppBarView::Create(RefPtr<FrameNode>& content)
{
    auto atom = FrameNode::CreateFrameNode(V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<AtomicServicePattern>());
    auto titleBar = BuildBarTitle();
    atom->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    atom->AddChild(titleBar);
    atom->AddChild(content);
#ifndef IS_EMULATOR
    auto faButton = BuildFaButton();
    atom->AddChild(faButton);
#endif
    content->GetLayoutProperty()->UpdateLayoutWeight(1.0f);
    content->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    return atom;
}

void AppBarView::iniBehavior()
{
    CHECK_NULL_VOID(atom_);
    auto titleBar = AceType::DynamicCast<FrameNode>(atom_->GetFirstChild());
    CHECK_NULL_VOID(titleBar);
    auto content = AceType::DynamicCast<FrameNode>(atom_->GetChildAtIndex(1));
    CHECK_NULL_VOID(content);
    auto stagePattern = content->GetPattern<StagePattern>();
    CHECK_NULL_VOID(stagePattern);
    stagePattern->SetOnRebuildFrameCallback([titleBar, content, this]() {
        auto backButton = AceType::DynamicCast<FrameNode>(titleBar->GetFirstChild());
        CHECK_NULL_VOID(backButton);
        if (content->GetChildren().size() > 1) {
            backButton->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
            if (!isVisibleSetted) {
                titleBar->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
            }
            return;
        }
        backButton->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
        if (HasNavigation(content)) {
            titleBar->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
        }
    });
    UpdateRowLayout();
}

RefPtr<FrameNode> AppBarView::BuildBarTitle()
{
    auto appBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutProperty = appBarRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(appBarTheme->GetAppBarHeight())));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    auto renderContext = appBarRow->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(appBarTheme->GetBgColor());

    auto titleLabel = BuildBarLabel();
    appBarRow->AddChild(BuildIconButton(
        InternalResource::ResourceId::APP_BAR_BACK_SVG,
        [pipeline](GestureEvent& info) {
            if (pipeline) {
                pipeline->CallRouterBackToPopPage();
            }
        },
        true));
    appBarRow->AddChild(titleLabel);
    return appBarRow;
}

RefPtr<FrameNode> AppBarView::BuildBarLabel()
{
    // create title label
    auto appBarLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = appBarLabel->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);
#ifdef PREVIEW
    auto label = themeConstants->GetString(pipeline->GetAppLabelId());
    if (label.empty()) {
        label = "label";
        LOGW("[Engine Log] Unable to get label for shared library in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
    }
    textLayoutProperty->UpdateContent(label);
#else
    textLayoutProperty->UpdateContent(themeConstants->GetString(pipeline->GetAppLabelId()));
#endif
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    textLayoutProperty->UpdateMaxLines(LABLE_ROWSIZE);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(appBarTheme->GetFontSize());
    textLayoutProperty->UpdateTextColor(appBarTheme->GetTextColor());
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    textLayoutProperty->UpdateLayoutWeight(1.0f);
    
    MarginProperty margin;
    margin.left = CalcLength(MARGIN_TEXT_LEFT);
    margin.right = CalcLength(MARGIN_TEXT_RIGHT);
    textLayoutProperty->UpdateMargin(margin);
	
    return appBarLabel;
}

RefPtr<FrameNode> AppBarView::BuildFaButton()
{
    auto buttonNode = BuildIconButton(InternalResource::ResourceId::APP_BAR_FA_SVG, nullptr, false);
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdatePosition(OffsetT<Dimension>());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    auto clickCallback = [pipeline, appBarTheme, buttonNode](GestureEvent& info) {
#ifdef PREVIEW
        LOGW("[Engine Log] Unable to show the SharePanel in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
#else
        if (!pipeline || !appBarTheme) {
            return;
        }
        if (SystemProperties::GetExtSurfaceEnabled()) {
            LOGI("start panel bundleName is %{public}s, abilityName is %{public}s",
                appBarTheme->GetBundleName().c_str(), appBarTheme->GetAbilityName().c_str());
            pipeline->FireSharePanelCallback(appBarTheme->GetBundleName(), appBarTheme->GetAbilityName());
        } else {
            BindContentCover(buttonNode);
        }
#endif
    };
    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    if (buttonEventHub) {
        buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
    return buttonNode;
}

RefPtr<FrameNode> AppBarView::BuildIconButton(
    InternalResource::ResourceId icon, GestureEventFunc&& clickCallback, bool isBackButton)
{
    // button image icon
    ImageSourceInfo imageSourceInfo;
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());

    imageSourceInfo.SetResourceId(icon);
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(appBarTheme->GetIconSize()), CalcLength(appBarTheme->GetIconSize())));
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageIcon->MarkModifyDone();

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());

    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    auto buttonPattern = AceType::DynamicCast<ButtonPattern>(buttonNode->GetPattern());
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->SetClickedColor(appBarTheme->GetClickEffectColor());

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    buttonEventHub->AddClickEvent(clickEvent);

    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
    auto butttonRadius = appBarTheme->GetIconCornerRadius();
    buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(butttonRadius));
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(appBarTheme->GetIconSize() * 2), CalcLength(appBarTheme->GetIconSize() * 2)));
    MarginProperty margin;
    margin.left = CalcLength(isBackButton ? MARGIN_BUTTON : -MARGIN_BUTTON);
    margin.right = CalcLength(isBackButton ? MARGIN_BACK_BUTTON_RIGHT : MARGIN_BUTTON);
    buttonLayoutProperty->UpdateMargin(margin);
    buttonNode->MarkModifyDone();
    buttonNode->AddChild(imageIcon);
    return buttonNode;
}

void AppBarView::BindContentCover(const RefPtr<FrameNode>& targetNode)
{
    if (OHOS::Ace::AppBarHelper::QueryAppGalleryBundleName().empty()) {
        LOGE("UIExtension BundleName is empty.");
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    std::string stageAbilityName = "";
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    if (appBarTheme) {
        stageAbilityName = appBarTheme->GetStageAbilityName();
    }
    NG::ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    auto buildNodeFunc = [targetNode, overlayManager, &modalStyle, &stageAbilityName]() -> RefPtr<UINode> {
        auto onRelease = [overlayManager, &modalStyle, targetNode](int32_t releaseCode) {
            overlayManager->BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, targetNode);
        };
        auto onError = [overlayManager, &modalStyle, targetNode](
                           int32_t code, const std::string& name, const std::string& message) {
            overlayManager->BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, targetNode);
        };

        // Create parameters of UIExtension.
        auto missionId = AceApplicationInfo::GetInstance().GetMissionId();
        std::map<std::string, std::string> params;
        params.try_emplace("bundleName", AceApplicationInfo::GetInstance().GetProcessName());
        params.try_emplace("abilityName", AceApplicationInfo::GetInstance().GetAbilityName());
        params.try_emplace("module", Container::Current()->GetModuleName());
        if (missionId != -1) {
            params.try_emplace("missionId", std::to_string(missionId));
        }
        params.try_emplace("ability.want.params.uiExtensionType", "sys/commonUI");
        LOGI("BundleName: %{public}s, AbilityName: %{public}s, Module: %{public}s",
            AceApplicationInfo::GetInstance().GetProcessName().c_str(),
            AceApplicationInfo::GetInstance().GetAbilityName().c_str(), Container::Current()->GetModuleName().c_str());

        // Create UIExtension node.
        auto appGalleryBundleName = OHOS::Ace::AppBarHelper::QueryAppGalleryBundleName();
        auto uiExtNode = OHOS::Ace::AppBarHelper::CreateUIExtensionNode(
            appGalleryBundleName, stageAbilityName, params, std::move(onRelease), std::move(onError));
        LOGI("UIExtension BundleName: %{public}s, AbilityName: %{public}s", appGalleryBundleName.c_str(),
            stageAbilityName.c_str());

        // Update ideal size of UIExtension.
        auto layoutProperty = uiExtNode->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, uiExtNode);
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(Dimension(1.0, DimensionUnit::PERCENT))));
        uiExtNode->MarkModifyDone();
        return uiExtNode;
    };
    overlayManager->BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, targetNode);
}

void AppBarView::SetVisible(bool visible)
{
    CHECK_NULL_VOID(atom_);
    auto uiRow = atom_->GetFirstChild();
    CHECK_NULL_VOID(uiRow);
    auto row = AceType::DynamicCast<FrameNode>(uiRow);
    row->GetLayoutProperty()->UpdateVisibility(visible ? VisibleType::VISIBLE : VisibleType::GONE);
    row->MarkModifyDone();
    row->MarkDirtyNode();
    isVisibleSetted = true;
}

void AppBarView::SetRowColor(const std::optional<Color>& color)
{
    CHECK_NULL_VOID(atom_);
    auto uiRow = atom_->GetFirstChild();
    CHECK_NULL_VOID(uiRow);
    auto row = AceType::DynamicCast<FrameNode>(uiRow);
    if (color) {
        row->GetRenderContext()->UpdateBackgroundColor(color.value());
    } else {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
        row->GetRenderContext()->UpdateBackgroundColor(appBarTheme->GetBgColor());
    }
    row->MarkModifyDone();
    row->MarkDirtyNode();
    isRowColorSetted = color.has_value();
}

void AppBarView::SetContent(const std::string& content)
{
    CHECK_NULL_VOID(atom_);
    auto uiRow = atom_->GetFirstChild();
    CHECK_NULL_VOID(uiRow);
    auto uiLabel = uiRow->GetLastChild();
    CHECK_NULL_VOID(uiLabel);
    auto label = AceType::DynamicCast<FrameNode>(uiLabel);
    label->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(content);
    label->MarkModifyDone();
    label->MarkDirtyNode();
}

void AppBarView::SetFontStyle(Ace::FontStyle fontStyle)
{
    CHECK_NULL_VOID(atom_);
    auto uiRow = atom_->GetFirstChild();
    CHECK_NULL_VOID(uiRow);
    auto uiLabel = uiRow->GetLastChild();
    CHECK_NULL_VOID(uiLabel);
    auto label = AceType::DynamicCast<FrameNode>(uiLabel);
    label->GetLayoutProperty<TextLayoutProperty>()->UpdateItalicFontStyle(fontStyle);
    label->MarkModifyDone();
    label->MarkDirtyNode();
}

void AppBarView::SetIconColor(const std::optional<Color>& color)
{
    CHECK_NULL_VOID(atom_);
    auto row = atom_->GetFirstChild();
    CHECK_NULL_VOID(row);
    auto backButton = row->GetFirstChild();
    CHECK_NULL_VOID(backButton);
    auto backIcon = AceType::DynamicCast<FrameNode>(backButton->GetFirstChild());
    SetEachIconColor(backIcon, color, InternalResource::ResourceId::APP_BAR_BACK_SVG);
    isIconColorSetted = color.has_value();
    auto faButton = GetFaButton();
    CHECK_NULL_VOID(faButton);
    auto faIcon = AceType::DynamicCast<FrameNode>(faButton->GetFirstChild());
    SetEachIconColor(faIcon, color, InternalResource::ResourceId::APP_BAR_FA_SVG);
}

void AppBarView::SetRowWidth(const Dimension& width)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    auto butttonRadius = appBarTheme->GetIconCornerRadius();
    Dimension offset = appBarTheme->GetIconSize() * 3;
    Dimension positionX = width - offset;
    Dimension positionLeftX = appBarTheme->GetIconSize() - butttonRadius;
    Dimension positionY = (appBarTheme->GetAppBarHeight() / 2.0f) - appBarTheme->GetIconSize();
    auto faButton = GetFaButton();
    CHECK_NULL_VOID(faButton);
    auto renderContext = faButton->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (!isRtl) {
        renderContext->UpdatePosition(OffsetT(positionX, positionY));
    } else {
        renderContext->UpdatePosition(OffsetT(positionLeftX, positionY));
    }
}

void AppBarView::SetEachIconColor(
    RefPtr<FrameNode> icon, const std::optional<Color>& color, InternalResource::ResourceId image)
{
    CHECK_NULL_VOID(icon);
    ImageSourceInfo info;
    if (color.has_value()) {
        info.SetResourceId(image, color);
    } else {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
        info.SetResourceId(image, appBarTheme->GetTextColor());
    }
    icon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(info);
    icon->MarkModifyDone();
    icon->MarkDirtyNode();
}

void AppBarView::IniColor()
{
    CHECK_NULL_VOID(atom_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();

    auto row = atom_->GetFirstChild();
    auto label = AceType::DynamicCast<FrameNode>(row->GetLastChild());
    CHECK_NULL_VOID(label);
    auto textLayoutProperty = label->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(appBarTheme->GetTextColor());

    if (!isRowColorSetted) {
        SetRowColor(std::nullopt);
    }

    if (!isIconColorSetted) {
        SetIconColor(std::nullopt);
    }
}

RefPtr<FrameNode> AppBarView::GetFaButton()
{
#ifndef IS_EMULATOR
    CHECK_NULL_RETURN(atom_, nullptr);
    return AceType::DynamicCast<FrameNode>(atom_->GetLastChild());
#endif
    return nullptr;
}

RefPtr<FrameNode> AppBarView::GetBackButton()
{
    CHECK_NULL_RETURN(atom_, nullptr);
    auto row = atom_->GetFirstChild();
    CHECK_NULL_RETURN(row, nullptr);
    return AceType::DynamicCast<FrameNode>(row->GetFirstChild());
}

void AppBarView::ReverseBackButton()
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto backButton = GetBackButton();
    CHECK_NULL_VOID(backButton);
    auto renderContext = backButton->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto buttonLayoutProperty = backButton->GetLayoutProperty();
    CHECK_NULL_VOID(buttonLayoutProperty);

    MarginProperty buttonmargin;
    bool isBackButton = true;
    if (!isRtl) {
        buttonmargin.left = CalcLength(isBackButton ? MARGIN_BUTTON : -MARGIN_BUTTON);
        buttonmargin.right = CalcLength(isBackButton ? MARGIN_BACK_BUTTON_RIGHT : MARGIN_BUTTON);
        renderContext->UpdateTransformScale(VectorF(UNCHANGED_X, UNCHANGED_Y));
    } else {
        buttonmargin.right = CalcLength(isBackButton ? MARGIN_BUTTON : -MARGIN_BUTTON);
        buttonmargin.left = CalcLength(isBackButton ? MARGIN_BACK_BUTTON_RIGHT : MARGIN_BUTTON);
        renderContext->UpdateTransformScale(VectorF(REVERSED_X, UNCHANGED_Y));
    }
    buttonLayoutProperty->UpdateMargin(buttonmargin);

    backButton->MarkModifyDone();
    backButton->MarkDirtyNode();
}

void AppBarView::UpdateRowLayout()
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRtlSetted == isRtl) {
        return;
    }
    CHECK_NULL_VOID(atom_);
    auto row = atom_->GetFirstChild();
    auto label = AceType::DynamicCast<FrameNode>(row->GetChildAtIndex(1));
    CHECK_NULL_VOID(label);
    auto textLayoutProperty = label->GetLayoutProperty<TextLayoutProperty>();
    MarginProperty textmargin;
    if (!isRtl) {
        textLayoutProperty->UpdateTextAlign(TextAlign::LEFT);
        textmargin.left = CalcLength(MARGIN_TEXT_LEFT);
        textmargin.right = CalcLength(MARGIN_TEXT_RIGHT);
        isRtlSetted = false;
    } else {
        textLayoutProperty->UpdateTextAlign(TextAlign::RIGHT);
        textmargin.right = CalcLength(MARGIN_TEXT_LEFT);
        textmargin.left = CalcLength(MARGIN_TEXT_RIGHT);
        isRtlSetted = true;
    }
    textLayoutProperty->UpdateMargin(textmargin);
    label->MarkModifyDone();
    label->MarkDirtyNode();

    ReverseBackButton();
}
} // namespace OHOS::Ace::NG
