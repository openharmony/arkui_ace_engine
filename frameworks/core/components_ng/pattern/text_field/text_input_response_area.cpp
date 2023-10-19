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
void TextInputResponseArea::LayoutChild(LayoutWrapper* layoutWrapper)
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
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto childFrameSize = childGeometryNode->GetFrameSize();
    auto childOffset = GetChildOffset(textInputFrameSize, contentRect, childFrameSize);
    childGeometryNode->SetFrameOffset(childOffset);
    childWrapper->GetGeometryNode()->SetFrameSize(childFrameSize);
    areaRect_.SetSize(childFrameSize);
    areaRect_.SetOffset(childOffset);
    childWrapper->Layout();
}

SizeF TextInputResponseArea::Measure(LayoutWrapper* layoutWrapper)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
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
void PasswordResponseArea::InitResponseArea(const WeakPtr<Pattern>& hostPattern)
{
    hostPattern_ = hostPattern;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        host->GetChildren();
        host->Clean();
    }
    if (!IsShowPasswordIcon()) {
        LOGD("show password icon is false");
        return;
    }
    auto passwordNode = CreateNode();
    CHECK_NULL_VOID(passwordNode);
    passwordNode->MountToParent(host);
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
    imageNode->MarkModifyDone();
    imageNode->MountToParent(stackNode);
    passwordNode_ = imageNode;

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
    gesture->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(clickCallback)));
}

void PasswordResponseArea::OnPasswordIconClicked()
{
    isObscured_ = !isObscured_;
    UpdateImageSource();
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnObscuredChanged(isObscured_);
}

SizeF PasswordResponseArea::Measure(LayoutWrapper* layoutWrapper)
{
    if (!IsShowPasswordIcon()) {
        LOGD("show password icon is false");
        return SizeF(0, 0);
    }
    return TextInputResponseArea::Measure(layoutWrapper);
}

void PasswordResponseArea::Layout(LayoutWrapper* layoutWrapper)
{
    if (!IsShowPasswordIcon()) {
        LOGD("show password icon is false");
        return;
    }
    LayoutChild(layoutWrapper);
}

OffsetF PasswordResponseArea::GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize)
{
    return OffsetF(parentSize.Width() - childSize.Width(), 0);
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
    ImageSourceInfo showSystemSourceInfo;
    showSystemSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
    showIcon_ = layoutProperty->GetShowPasswordSourceInfoValue(showSystemSourceInfo);

    ImageSourceInfo hideSystemSourceInfo;
    hideSystemSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
    hideIcon_ = layoutProperty->GetHidePasswordSourceInfoValue(hideSystemSourceInfo);
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

void PasswordResponseArea::DestoryArea()
{
    TextInputResponseArea::DestoryArea();
    isObscured_ = true;
    hostPattern_.Reset();
    passwordNode_.Reset();
    showIcon_ = std::nullopt;
    hideIcon_ = std::nullopt;
}

bool PasswordResponseArea::IsShowPasswordIcon()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, false);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowPasswordIconValue(true) &&
           layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;
} // PasswordResponseArea end

// UnitResponseArea begin
void UnitResponseArea::InitResponseArea(const WeakPtr<Pattern>& hostPattern)
{
    hostPattern_ = hostPattern;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        host->GetChildren();
        host->Clean();
    }
    if (!IsShowUnit()) {
        return;
    }
    auto unitNode = unitNode_.Upgrade();
    CHECK_NULL_VOID(unitNode);
    unitNode->MountToParent(host);
}

SizeF UnitResponseArea::Measure(LayoutWrapper* layoutWrapper)
{
    if (!IsShowUnit()) {
        LOGD("not show unit");
        return SizeF(0, 0);
    }
    return TextInputResponseArea::Measure(layoutWrapper);
}

void UnitResponseArea::Layout(LayoutWrapper* layoutWrapper)
{
    if (!IsShowUnit()) {
        LOGD("not show unit");
        return;
    }
    LayoutChild(layoutWrapper);
}

OffsetF UnitResponseArea::GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize)
{
    return OffsetF(contentRect.GetX() + contentRect.Width(), 0);
}

bool UnitResponseArea::IsShowUnit()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, false);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowUnderlineValue(false) &&
           layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED;
}

void UnitResponseArea::DestoryArea()
{
    TextInputResponseArea::DestoryArea();
    hostPattern_.Reset();
    unitNode_.Reset();
} // UnitResponseArea end

} // namespace OHOS::Ace::NG