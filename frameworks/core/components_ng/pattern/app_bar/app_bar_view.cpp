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

const Dimension MARGIN_TEXT = 24.0_vp;
const Dimension MARGIN_BUTTON = 12.0_vp;
const Dimension MARGIN_BACK_BUTTON_RIGHT = -20.0_vp;

static WeakPtr<FrameNode> row_;
static WeakPtr<FrameNode> label_;
static ImageSourceInfo backImage_;
static ImageSourceInfo faImage_;
static WeakPtr<FrameNode> backIcon_;
static WeakPtr<FrameNode> faIcon_;

} // namespace

RefPtr<FrameNode> AppBarView::Create(RefPtr<FrameNode>& content)
{
    auto atom = FrameNode::CreateFrameNode(V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<AtomicServicePattern>());
    auto titleBar = BuildBarTitle();
    atom->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    atom->AddChild(titleBar);
    atom->AddChild(content);
    auto faButton = titleBar->GetLastChild();
    if (faButton) {
        LOGI("lqc: success add faButton");
        titleBar->RemoveChildAtIndex(2);
        atom->AddChild(faButton);
        // faButton->GetRenderContext()->UpdatePosition(OffsetT(0.9_pct, 4.0_Vp));
    }
    content->GetLayoutProperty()->UpdateLayoutWeight(1.0f);
    content->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto stagePattern = content->GetPattern<StagePattern>();
    if (stagePattern) {
        stagePattern->SetOnRebuildFrameCallback([titleBar, content]() {
            CHECK_NULL_VOID(titleBar);
            CHECK_NULL_VOID(content);
            auto backButton = AceType::DynamicCast<FrameNode>(titleBar->GetFirstChild());
            CHECK_NULL_VOID(backButton);
            if (content->GetChildren().size() > 1) {
                backButton->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
                return;
            }
            backButton->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
        });
    }
    return atom;
}

RefPtr<FrameNode> AppBarView::BuildBarTitle()
{
    auto appBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    row_ = appBarRow;
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

    // create title label
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
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
    textLayoutProperty->UpdateMaxLines(2);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(appBarTheme->GetFontSize());
    textLayoutProperty->UpdateTextColor(appBarTheme->GetTextColor());
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    textLayoutProperty->UpdateLayoutWeight(1.0f);

    MarginProperty margin;
    margin.left = CalcLength(MARGIN_TEXT);
    margin.right = CalcLength(MARGIN_TEXT);
    textLayoutProperty->UpdateMargin(margin);

    appBarRow->AddChild(BuildIconButton(
        InternalResource::ResourceId::APP_BAR_BACK_SVG,
        [pipeline](GestureEvent& info) {
            if (pipeline) {
                pipeline->CallRouterBackToPopPage();
            }
        }, true));
    appBarRow->AddChild(titleLabel);
    label_ = titleLabel;
#ifdef IS_EMULATOR
    return appBarRow;
#endif

    auto buttonNode = BuildIconButton(InternalResource::ResourceId::APP_BAR_FA_SVG, nullptr, false);
    auto buttonId = buttonNode->GetId();
    auto clickCallback = [pipeline, appBarTheme, buttonId](GestureEvent& info) {
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
            BindContentCover(buttonId);
        }
#endif
    };
    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    if (buttonEventHub) {
        buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
    appBarRow->AddChild(buttonNode);
    
    return appBarRow;
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
        LOGI("lqc: %{public}f",appBarTheme->GetIconSize().Value());
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageIcon->MarkModifyDone();

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());

    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    if (!isBackButton) {
        renderContext->UpdatePosition(OffsetT(0.9_pct, 4.0_vp));
    }

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

    if (isBackButton) {
        backImage_ = imageSourceInfo;
        backIcon_ = imageIcon;
    } else {
        faImage_ = imageSourceInfo;
        faIcon_ = imageIcon;
    }

    buttonNode->MarkModifyDone();

    buttonNode->AddChild(imageIcon);
    return buttonNode;
}

void AppBarView::BindContentCover(int32_t targetId)
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
    auto buildNodeFunc = [targetId, overlayManager, &modalStyle, &stageAbilityName]() -> RefPtr<UINode> {
        auto onRelease = [overlayManager, &modalStyle, targetId](int32_t releaseCode) {
            overlayManager->BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, targetId);
        };
        auto onError = [overlayManager, &modalStyle, targetId](
                           int32_t code, const std::string& name, const std::string& message) {
            overlayManager->BindContentCover(false, nullptr, nullptr, modalStyle, nullptr, nullptr, targetId);
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
    overlayManager->BindContentCover(true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, targetId);
}

void AppBarView::SetVisible(const bool visible)
{
    LOGI("lqc: into SetVisible");
    auto row = row_.Upgrade();
    CHECK_NULL_VOID(row);

    if (visible) {
        // auto pipeline = PipelineContext::GetCurrentContext();
        // CHECK_NULL_VOID(pipeline);
        // auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
        row->GetLayoutProperty()->ResetCalcMaxSize();
    } else {
        row->GetLayoutProperty()->UpdateCalcMaxSize(CalcSize(CalcLength(1.0_pct), CalcLength(0.0)));
    }
    // row->MarkModifyDone();

        // row->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        // row->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    LOGI("lqc: success SetVisible");
}


void AppBarView::SetRowColor(const Color& color)
{
    auto row = row_.Upgrade();
    if (!row) {
        return;
    }
    row->GetRenderContext()->UpdateBackgroundColor(color);
    LOGI("lqc: success SetBackGroundColor");
}

void AppBarView::SetRowColor(const std::string& color)
{
    auto row = row_.Upgrade();
    if (!row) {
        return;
    }
    row->GetRenderContext()->UpdateBackgroundColor(Color::FromString(color));
    LOGI("lqc: success SetBackGroundColor");
}

void AppBarView::SetRowColor()
{
    auto row = row_.Upgrade();
    CHECK_NULL_VOID(row);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    auto renderContext = row->GetRenderContext();
    renderContext->UpdateBackgroundColor(appBarTheme->GetBgColor());

    LOGI("lqc: success SetBackGroundColor");
}

void AppBarView::SetTitleContent(const std::string& content)
{
    auto label = label_.Upgrade();
    CHECK_NULL_VOID(label);
    label->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(content);
    label->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    
    LOGI("lqc: success SetTitleContent");
}

void AppBarView::SetTitleFontStyle(const Ace::FontStyle fontStyle)
{
    auto label = label_.Upgrade();
    if (!label) {
        return;
    }
    label->GetLayoutProperty<TextLayoutProperty>()->UpdateItalicFontStyle(fontStyle);
    LOGI("lqc: success SetTitleFontStyle");
}

void AppBarView::SetIconColor(const Color& color)
{
    auto backImage = backImage_;
    auto backIcon = backIcon_.Upgrade();
    auto faImage = faImage_;
    auto faIcon = faIcon_.Upgrade();

    if (!backIcon || !faIcon) {
        return;
    }

    backImage.SetResourceId(InternalResource::ResourceId::APP_BAR_BACK_SVG, color);
    backIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(backImage);

    faImage.SetResourceId(InternalResource::ResourceId::APP_BAR_FA_SVG, color);
    faIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(faImage);

    backIcon->MarkModifyDone();
    faIcon->MarkModifyDone();

    LOGI("lqc: success SetIconColor");
}

void AppBarView::SetIconColor(const std::string& color)
{
    auto backImage = backImage_;
    auto backIcon = backIcon_.Upgrade();
    auto faImage = faImage_;
    auto faIcon = faIcon_.Upgrade();
    if (!backIcon || !faIcon) {
        return;
    }

    backImage.SetResourceId(InternalResource::ResourceId::APP_BAR_BACK_SVG, Color::FromString(color));
    backIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(backImage);

    faImage.SetResourceId(InternalResource::ResourceId::APP_BAR_FA_SVG, Color::FromString(color));
    faIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(faImage);

    backIcon->MarkModifyDone();
    faIcon->MarkModifyDone();

    LOGI("lqc: success SetIconColor");
}
} // namespace OHOS::Ace::NG
