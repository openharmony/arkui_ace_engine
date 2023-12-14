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

#include "core/components_ng/pattern/text_field/text_input_response_area.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
// TextInputResponseArea begin
void TextInputResponseArea::LayoutChild(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto children = frameNode->GetChildren();
    CHECK_NULL_VOID(!children.empty());
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textInputGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textInputGeometryNode);
    auto contentRect = textInputGeometryNode->GetContentRect();
    auto textInputFrameSize = textInputGeometryNode->GetFrameSize();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto childFrameSize = childGeometryNode->GetFrameSize();
    auto childOffset = GetChildOffset(textInputFrameSize, contentRect, childFrameSize, nodeWidth);
    childGeometryNode->SetFrameOffset(childOffset);
    childWrapper->GetGeometryNode()->SetFrameSize(childFrameSize);
    areaRect_.SetSize(childFrameSize);
    areaRect_.SetOffset(childOffset);
    childWrapper->Layout();
    nodeWidth += childFrameSize.Width();
}

SizeF TextInputResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto textfieldLayoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    SizeF size(0, 0);
    CHECK_NULL_RETURN(textfieldLayoutProperty, size);
    auto childLayoutConstraint = textfieldLayoutProperty->CreateChildConstraint();
    CHECK_NULL_RETURN(childWrapper, size);
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    auto&& layoutConstraint = childLayoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        layoutConstraint->selfIdealSize->SetHeight(
            CalcLength(layoutWrapper->GetGeometryNode()->GetFrameSize().Height()));
    }
    childWrapper->Measure(childLayoutConstraint);
    auto geometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, size);
    return geometryNode->GetFrameSize();
} // TextInputResponseArea end

// PasswordResponseArea begin
void PasswordResponseArea::InitResponseArea()
{
    ClearArea();
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    if (!IsShowPasswordIcon()) {
        return;
    }
    auto passwordNode = CreateNode();
    CHECK_NULL_VOID(passwordNode);
    passwordNode->MountToParent(host);
}

const RefPtr<FrameNode> PasswordResponseArea::GetFrameNode()
{
    auto frameNode = passwordNode_.Upgrade();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto stackNode = frameNode->GetParent();
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto ret = AceType::DynamicCast<FrameNode>(stackNode);
    CHECK_NULL_RETURN(ret, nullptr);
    return ret;
}

RefPtr<FrameNode> PasswordResponseArea::CreateNode()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, nullptr);
    auto iconSize = GetIconSize();
    auto rightOffset = GetIconRightOffset();
    auto hotZoneSize = iconSize + rightOffset;

    auto stackNode = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    auto stackLayoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(stackLayoutProperty, nullptr);
    stackLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(hotZoneSize), std::nullopt));
    stackLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    AddEvent(stackNode);
    stackNode->MarkModifyDone();

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    imageNode->SetDraggable(false);
    LoadImageSourceInfo();
    auto currentImageSourceInfo = GetCurrentSourceInfo();
    CHECK_NULL_RETURN(currentImageSourceInfo, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(currentImageSourceInfo.value());
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    auto eventHub = imageNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    eventHub->SetOnError([ weakNode = WeakClaim(AceType::RawPtr(imageNode)), weakArea = WeakClaim(this) ]
        (const LoadImageFailEvent& info) {
        auto host = weakNode.Upgrade();
        CHECK_NULL_VOID(host);
        auto area = weakArea.Upgrade();
        CHECK_NULL_VOID(area);
        auto imagePattern = host->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(imagePattern);
        auto layoutProperty = host->GetLayoutProperty<ImageLayoutProperty>();
        layoutProperty->UpdateImageSourceInfo(area->GetDefaultSourceInfo(area->isObscured_));
        imagePattern->LoadImageDataIfNeed();
    });
    imageNode->MarkModifyDone();
    imageNode->MountToParent(stackNode);
    passwordNode_ = imageNode;
    stackNode_ = stackNode;
    return stackNode;
}

void PasswordResponseArea::AddEvent(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto focusHub = node->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto gesture = node->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto button = weak.Upgrade();
        CHECK_NULL_VOID(button);
        button->OnPasswordIconClicked();
    };
    auto longPressCallback = [](GestureEvent& info) {
        LOGI("PasswordResponseArea long press");
    };
    gesture->SetLongPressEvent(MakeRefPtr<LongPressEvent>(std::move(longPressCallback)));
    gesture->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(clickCallback)));
}

void PasswordResponseArea::Refresh()
{
    auto imageNode = passwordNode_.Upgrade();
    if (!imageNode) {
        InitResponseArea();
        return;
    }
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto currentSrc = imageLayoutProperty->GetImageSourceInfoValue().GetSrc();
    LoadImageSourceInfo();
    auto src = isObscured_ ? hideIcon_->GetSrc() : showIcon_->GetSrc();
    if (currentSrc != src) {
        UpdateImageSource();
    }
}

void PasswordResponseArea::OnPasswordIconClicked()
{
    isObscured_ = !isObscured_;
    UpdateImageSource();
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnObscuredChanged(isObscured_);
}

SizeF PasswordResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (!IsShowPasswordIcon()) {
        return SizeF(0, 0);
    }
    return TextInputResponseArea::Measure(layoutWrapper, index);
}

void PasswordResponseArea::Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth)
{
    if (!IsShowPasswordIcon()) {
        return;
    }
    LayoutChild(layoutWrapper, index, nodeWidth);
}

OffsetF PasswordResponseArea::GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize, float nodeWidth)
{
    return OffsetF(parentSize.Width() - childSize.Width() - nodeWidth, 0);
}

float PasswordResponseArea::GetIconSize()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, 0.0f);
    auto tmpHost = textFieldPattern->GetHost();
    CHECK_NULL_RETURN(tmpHost, 0.0f);
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    return static_cast<float>(textFieldTheme->GetIconSize().ConvertToPx());
}

float PasswordResponseArea::GetIconRightOffset()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, 0.0f);
    auto tmpHost = textFieldPattern->GetHost();
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = textFieldTheme->GetPadding();
    return static_cast<float>(themePadding.Left().ConvertToPx());
}

void PasswordResponseArea::LoadImageSourceInfo()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(textFieldPattern);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    showIcon_ = layoutProperty->GetShowPasswordSourceInfoValue(GetDefaultSourceInfo(false));
    hideIcon_ = layoutProperty->GetHidePasswordSourceInfoValue(GetDefaultSourceInfo(true));
    auto tmpHost = textFieldPattern->GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    if (showIcon_->GetResourceId() == InternalResource::ResourceId::SHOW_PASSWORD_SVG) {
        showIcon_->SetFillColor(textFieldTheme->GetTextColor());
    }
    if (hideIcon_->GetResourceId() == InternalResource::ResourceId::HIDE_PASSWORD_SVG) {
        hideIcon_->SetFillColor(textFieldTheme->GetTextColor());
    }
    if (layoutProperty->GetIsDisabledValue(false)) {
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_VOID(iconTheme);
        auto textDisableColor = textFieldTheme->GetTextColorDisable();
        auto hideIconPath = iconTheme->GetIconPath(hideIcon_->GetResourceId());
        hideIcon_->SetSrc(hideIconPath, textDisableColor);
        auto showIconPath = iconTheme->GetIconPath(showIcon_->GetResourceId());
        showIcon_->SetSrc(showIconPath, textDisableColor);
        UpdateImageSource();
    }
}

ImageSourceInfo PasswordResponseArea::GetDefaultSourceInfo(bool isObscured)
{
    if (isObscured) {
        ImageSourceInfo hideSystemSourceInfo;
        hideSystemSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
        return hideSystemSourceInfo;
    }
    ImageSourceInfo showSystemSourceInfo;
    showSystemSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
    return showSystemSourceInfo;
}

void PasswordResponseArea::UpdateImageSource()
{
    auto frameNode = passwordNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto currentImageSourceInfo = GetCurrentSourceInfo();
    CHECK_NULL_VOID(currentImageSourceInfo);
    layoutProperty->UpdateImageSourceInfo(currentImageSourceInfo.value());
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->LoadImageDataIfNeed();
}

bool PasswordResponseArea::IsShowPasswordIcon()
{
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsShowPasswordIcon();
} // PasswordResponseArea end

// UnitResponseArea begin
void UnitResponseArea::InitResponseArea()
{
    ClearArea();
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    if (!IsShowUnit()) {
        return;
    }
    CHECK_NULL_VOID(unitNode_);
    unitNode_->MountToParent(host);
}

const RefPtr<FrameNode> UnitResponseArea::GetFrameNode()
{
    auto frameNode = AceType::DynamicCast<FrameNode>(unitNode_);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

SizeF UnitResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (!IsShowUnit()) {
        return SizeF(0, 0);
    }
    return TextInputResponseArea::Measure(layoutWrapper, index);
}

void UnitResponseArea::Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth)
{
    if (!IsShowUnit()) {
        return;
    }
    LayoutChild(layoutWrapper, index, nodeWidth);
}

OffsetF UnitResponseArea::GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize, float nodeWidth)
{
    return OffsetF(parentSize.Width() - childSize.Width() - nodeWidth, 0);
}

bool UnitResponseArea::IsShowUnit()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsShowUnit();
} // UnitResponseArea end

void CleanNodeResponseArea::InitResponseArea()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldLayoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (textFieldLayoutProperty->HasIconSize()) {
        iconSize_ = textFieldLayoutProperty->GetIconSizeValue();
    }

    if (textFieldLayoutProperty->HasIconSrc()) {
        iconSrc_ = textFieldLayoutProperty->GetIconSrcValue();
    }

    if (textFieldLayoutProperty->HasIconColor()) {
        iconColor_ = textFieldLayoutProperty->GetIconColorValue();
    }
    auto cleanNode = CreateNode();
    CHECK_NULL_VOID(cleanNode);
    cleanNode->MountToParent(host);
}

SizeF CleanNodeResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    return TextInputResponseArea::Measure(layoutWrapper, index);
}

void CleanNodeResponseArea::Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth)
{
    LayoutChild(layoutWrapper, index, nodeWidth);
}

OffsetF CleanNodeResponseArea::GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize, float nodeWidth)
{
    return OffsetF(parentSize.Width() - childSize.Width() - nodeWidth, 0);
}

const RefPtr<FrameNode> CleanNodeResponseArea::GetFrameNode()
{
    return cleanNode_;
}

RefPtr<FrameNode> CleanNodeResponseArea::CreateNode()
{
    auto stackNode = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    auto stackLayoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(stackLayoutProperty, nullptr);
    stackLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), std::nullopt));
    stackLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    stackNode->MarkModifyDone();
    auto cleanNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(cleanNode, nullptr);
    cleanNode->SetDraggable(false);
    ImageSourceInfo info;
    if (iconSrc_.empty()) {
        info.SetResourceId(InternalResource::ResourceId::CLOSE_SVG);
    } else {
        info.SetSrc(iconSrc_);
    }
    if (info.IsSvg()) {
        info.SetFillColor(iconColor_);
        auto imageRenderProperty = cleanNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_RETURN(imageRenderProperty, nullptr);
        imageRenderProperty->UpdateSvgFillColor(iconColor_);
    }
    auto imageLayoutProperty = cleanNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(info);
    imageLayoutProperty->UpdateImageFit(ImageFit::COVER);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    cleanNode->MarkModifyDone();
    cleanNode->MountToParent(stackNode);
    InitClickEvent(stackNode);
    cleanNode_ = stackNode;
    return stackNode;
}

void CleanNodeResponseArea::InitClickEvent(const RefPtr<FrameNode>& frameNode)
{
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto cleanNode = weak.Upgrade();
        CHECK_NULL_VOID(cleanNode);
        cleanNode->OnCleanNodeClicked();
    };
    auto longPressCallback = [](GestureEvent& info) { LOGI("CleanNodeResponseArea long press"); };
    gesture->SetLongPressEvent(MakeRefPtr<LongPressEvent>(std::move(longPressCallback)));
    gesture->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(clickCallback)));
}

void CleanNodeResponseArea::OnCleanNodeClicked()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->ClearEditingValue();
}

void CleanNodeResponseArea::UpdateCleanNode(bool isShow)
{
    isShow_ = isShow;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    CHECK_NULL_VOID(cleanNode_);
    auto stackLayoutProperty = cleanNode_->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(stackLayoutProperty);
    auto imageNode = cleanNode_->GetFirstChild();
    CHECK_NULL_VOID(imageNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    if (isShow) {
        auto host = textFieldPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto themePadding = textFieldTheme->GetPadding();
        auto rightOffset = static_cast<float>(themePadding.Left().ConvertToPx());
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto frameSize = geometryNode->GetFrameSize();
        auto iconSize = std::min(iconSize_.ConvertToPx(), static_cast<double>(frameSize.Height()));
        if (NearZero(iconSize)) {
            isShow_ = false;
        }
        auto hotZoneSize = iconSize + rightOffset;
        stackLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(hotZoneSize), std::nullopt));
        imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    } else {
        stackLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), std::nullopt));
        imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    }
    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void CleanNodeResponseArea::ClearArea()
{
    auto hostPattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(hostPattern);
    auto host = hostPattern->GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(cleanNode_);
    host->RemoveChildAndReturnIndex(cleanNode_);
    cleanNode_.Reset();
}
} // namespace OHOS::Ace::NG