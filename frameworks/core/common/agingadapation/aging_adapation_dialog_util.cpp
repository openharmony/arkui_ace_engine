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
#include "base/utils/utf_helper.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
namespace OHOS::Ace::NG {
RefPtr<FrameNode> AgingAdapationDialogUtil::ShowLongPressDialog(
    const std::string& message, ImageSourceInfo& imageSourceInfo)
{
    return ShowLongPressDialog(UtfUtils::Str8ToStr16(message), imageSourceInfo);
}

RefPtr<FrameNode> AgingAdapationDialogUtil::ShowLongPressDialog(
    const std::u16string& message, ImageSourceInfo& imageSourceInfo)
{
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));

    if (imageSourceInfo.IsValid()) {
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(context, nullptr);
        auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
        CHECK_NULL_RETURN(dialogTheme, nullptr);
        auto color = dialogTheme->GetDialogIconColor();
        imageSourceInfo.SetFillColor(Color(color.GetValue()));
        auto imageNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
        imageLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(dialogTheme->GetIdealSize()), CalcLength(dialogTheme->GetIdealSize())));
        imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        MarginProperty imageMargin;
        Dimension dialogHeight;
        if (message.empty()) {
            float scale = context->GetFontScale();
            if (NearEqual(scale, dialogTheme->GetBigFontSizeScale()) ||
                NearEqual(scale, dialogTheme->GetLargeFontSizeScale())) {
                dialogHeight = Dimension(dialogTheme->GetBigDialogWidth(), DimensionUnit::VP);
            } else if (NearEqual(scale, dialogTheme->GetMaxFontSizeScale())) {
                dialogHeight = Dimension(dialogTheme->GetMaxDialogWidth(), DimensionUnit::VP);
            }
            auto marginSize = (dialogHeight - dialogTheme->GetIdealSize()).ConvertToPx() / 2;
            imageMargin.top = CalcLength(Dimension(marginSize, DimensionUnit::PX));
            imageMargin.bottom = CalcLength(Dimension(marginSize, DimensionUnit::PX));
            imageLayoutProperty->UpdateMargin(imageMargin);
            imageNode->MountToParent(columnNode);
            imageNode->MarkModifyDone();
            return CreateCustomDialog(columnNode);
        }
        imageMargin.top = CalcLength(dialogTheme->GetDialogPropertyTop());
        imageMargin.bottom = CalcLength(dialogTheme->GetDialogPropertyBottom());
        imageLayoutProperty->UpdateMargin(imageMargin);
        imageNode->MountToParent(columnNode);
        imageNode->MarkModifyDone();
    }
    CreateDialogTextNode(columnNode, message);
    return CreateCustomDialog(columnNode);
}

RefPtr<FrameNode> AgingAdapationDialogUtil::ShowLongPressDialog(
    const std::string& message, const RefPtr<FrameNode>& iconNode)
{
    return ShowLongPressDialog(UtfUtils::Str8ToStr16(message), iconNode);
}

RefPtr<FrameNode> AgingAdapationDialogUtil::ShowLongPressDialog(
    const std::u16string& message, const RefPtr<FrameNode>& iconNode)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);
    auto srcLayoutProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(srcLayoutProperty, nullptr);
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(symbolProperty, nullptr);
    symbolProperty->UpdateFontSize(dialogTheme->GetIdealSize());
    symbolProperty->UpdateSymbolSourceInfo(srcLayoutProperty->GetSymbolSourceInfoValue());
    auto symbolColorList = srcLayoutProperty->GetSymbolColorListValue({});
    symbolColorList.empty() ? symbolProperty->UpdateSymbolColorList({ dialogTheme->GetDialogIconColor() })
                            : symbolProperty->UpdateSymbolColorList(symbolColorList);
    auto fontWeight = srcLayoutProperty->GetFontWeightValue(FontWeight::NORMAL);
    symbolProperty->UpdateFontWeight(fontWeight);
    auto renderStrategy = srcLayoutProperty->GetSymbolRenderingStrategyValue(0);
    symbolProperty->UpdateSymbolRenderingStrategy(renderStrategy);
    MarginProperty symbolMargin;
    Dimension dialogHeight;
    if (message.empty()) {
        float scale = context->GetFontScale();
        if (NearEqual(scale, dialogTheme->GetBigFontSizeScale()) ||
            NearEqual(scale, dialogTheme->GetLargeFontSizeScale())) {
            dialogHeight = Dimension(dialogTheme->GetBigDialogWidth(), DimensionUnit::VP);
        } else if (NearEqual(scale, dialogTheme->GetMaxFontSizeScale())) {
            dialogHeight = Dimension(dialogTheme->GetMaxDialogWidth(), DimensionUnit::VP);
        }
        auto marginSize = (dialogHeight - dialogTheme->GetIdealSize()).ConvertToPx() / 2;
        symbolMargin.top = CalcLength(Dimension(marginSize, DimensionUnit::PX));
        symbolMargin.bottom = CalcLength(Dimension(marginSize, DimensionUnit::PX));
        symbolProperty->UpdateMargin(symbolMargin);
        symbolNode->MountToParent(columnNode);
        symbolNode->MarkModifyDone();
        return CreateCustomDialog(columnNode);
    }
    symbolMargin.top = CalcLength(dialogTheme->GetDialogPropertyTop());
    symbolMargin.bottom = CalcLength(dialogTheme->GetDialogPropertyBottom());
    symbolProperty->UpdateMargin(symbolMargin);
    symbolNode->MountToParent(columnNode);
    symbolNode->MarkModifyDone();
    CreateDialogTextNode(columnNode, message);
    return CreateCustomDialog(columnNode);
}

RefPtr<FrameNode> AgingAdapationDialogUtil::CreateCustomDialog(const RefPtr<FrameNode>& columnNode)
{
    CHECK_NULL_RETURN(columnNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);
    DialogProperties dialogProperties;
    dialogProperties.alignment = DialogAlignment::CENTER;
    dialogProperties.gridCount = dialogTheme->GetGridCount();
    dialogProperties.isModal = false;
    dialogProperties.backgroundColor = Color::TRANSPARENT;
    dialogProperties.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultLG);
    dialogProperties.borderRadius = BorderRadiusProperty(dialogTheme->GetDialogCornerRadius());
    CalcSize columnMinSize;
    float scale = context->GetFontScale();
    if (NearEqual(scale, dialogTheme->GetBigFontSizeScale()) ||
        NearEqual(scale, dialogTheme->GetLargeFontSizeScale())) {
        dialogProperties.width = CalcDimension(dialogTheme->GetBigDialogWidth(), DimensionUnit::VP);
        columnMinSize.SetHeight(CalcLength(dialogTheme->GetBigDialogWidth(), DimensionUnit::VP));
    } else if (NearEqual(scale, dialogTheme->GetMaxFontSizeScale())) {
        dialogProperties.width = CalcDimension(dialogTheme->GetMaxDialogWidth(), DimensionUnit::VP);
        columnMinSize.SetHeight(CalcLength(dialogTheme->GetMaxDialogWidth(), DimensionUnit::VP));
    }
    auto layoutProperty = columnNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateCalcMinSize(columnMinSize);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, nullptr);
    return overlayManager->ShowDialogWithNode(dialogProperties, columnNode, isRightToLeft);
}

void AgingAdapationDialogUtil::CreateDialogTextNode(const RefPtr<FrameNode>& columnNode, const std::u16string& message)
{
    CHECK_NULL_VOID(columnNode);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(message);
    textLayoutProperty->UpdateFontSize(dialogTheme->GetDialogFontSize());
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateMaxLines(dialogTheme->GetMaxLines());
    MarginProperty margin;
    margin.left = CalcLength(dialogTheme->GetTextPropertyLeft());
    margin.right = CalcLength(dialogTheme->GetTextPropertyRight());
    margin.bottom = CalcLength(dialogTheme->GetTextPropertyBottom());
    if (columnNode->GetFirstChild() == nullptr) {
        margin.top = CalcLength(dialogTheme->GetTextPropertyBottom());
        CalcSize textMinSize;
        Dimension textMinHeight;
        float scale = context->GetFontScale();
        if (NearEqual(scale, dialogTheme->GetBigFontSizeScale()) ||
            NearEqual(scale, dialogTheme->GetLargeFontSizeScale())) {
            textMinHeight = Dimension(dialogTheme->GetBigDialogWidth(), DimensionUnit::VP) -
                            dialogTheme->GetTextPropertyBottom() - dialogTheme->GetTextPropertyBottom();
        } else if (NearEqual(scale, dialogTheme->GetMaxFontSizeScale())) {
            textMinHeight = Dimension(dialogTheme->GetMaxDialogWidth(), DimensionUnit::VP) -
                            dialogTheme->GetTextPropertyBottom() - dialogTheme->GetTextPropertyBottom();
        }
        textMinSize.SetHeight(CalcLength(textMinHeight));
        textLayoutProperty->UpdateCalcMinSize(textMinSize);
    }
    textLayoutProperty->UpdateMargin(margin);
    auto color = dialogTheme->GetDialogFontColor();
    textLayoutProperty->UpdateTextColor(Color(color.GetValue()));
    textNode->MountToParent(columnNode);
}

float AgingAdapationDialogUtil::GetDialogBigFontSizeScale()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0.0);
    auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, 0.0);
    return dialogTheme->GetBigFontSizeScale();
}

float AgingAdapationDialogUtil::GetDialogLargeFontSizeScale()
{
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, 0.0);
    auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, 0.0);
    return dialogTheme->GetLargeFontSizeScale();
}

float AgingAdapationDialogUtil::GetDialogMaxFontSizeScale()
{
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, 0.0);
    auto dialogTheme = context->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, 0.0);
    return dialogTheme->GetMaxFontSizeScale();
}
} // namespace OHOS::Ace::NG