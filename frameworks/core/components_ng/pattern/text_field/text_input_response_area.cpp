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
#include "core/common/container.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float MAX_FONT_SCALE = 2.0f;
constexpr Dimension ICON_MAX_SIZE = 40.0_vp;
constexpr Dimension DEFAULT_ICON_HOT_ZONE = 40.0_vp;
constexpr Dimension ICON_FOCUS_PADDING = 2.0_vp;
constexpr Dimension DEFAULT_HOVER_SIZE = 32.0_vp;
constexpr int HALF_SPACE = 2;
constexpr int DOUBLE_PADDING = 2;
} // namespace

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

OffsetF TextInputResponseArea::GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize, float nodeWidth)
{
    auto offset = Alignment::GetAlignPosition(parentSize, childSize, Alignment::CENTER);
    auto textFieldPattern = hostPattern_.Upgrade();
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRTL) {
        return OffsetF(nodeWidth, offset.GetY());
    } else {
        return OffsetF(parentSize.Width() - childSize.Width() - nodeWidth, offset.GetY());
    }
}

SizeF TextInputResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    SizeF size(0, 0);
    CHECK_NULL_RETURN(layoutWrapper, size);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto textfieldLayoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textfieldLayoutProperty, size);
    auto childLayoutConstraint = textfieldLayoutProperty->CreateChildConstraint();
    CHECK_NULL_RETURN(childWrapper, size);
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    childWrapper->Measure(childLayoutConstraint);
    auto geometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, size);
    return geometryNode->GetFrameSize();
}

SizeF TextInputResponseArea::GetFrameSize(bool withSafeArea)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, SizeF(0, 0));
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF(0, 0));
    return geometryNode->GetFrameSize(withSafeArea);
}

Alignment TextInputResponseArea::GetStackAlignment(const TextDirection& userDirection)
{
    bool isSysRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if ((isSysRtl && userDirection == TextDirection::LTR) ||
        (!isSysRtl && userDirection == TextDirection::RTL)) {
        return Alignment::CENTER_RIGHT;
    }
    return Alignment::CENTER_LEFT;
}

RefPtr<FrameNode> TextInputResponseArea::CreateResponseAreaImageNode(const ImageSourceInfo& imageSourceInfo,
    ImageFit imageFit, const CalcSize& userDefinedIdealSize)
{
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->SetDraggable(false);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr); // return nullptr as this is severe situation
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageLayoutProperty->UpdateImageFit(imageFit);
    imageLayoutProperty->UpdateUserDefinedIdealSize(userDefinedIdealSize);
    return imageNode;
}

void TextInputResponseArea::SetHoverRect(RefPtr<FrameNode>& stackNode, RectF& rect, float iconSize,
    float hoverRectHeight, bool isFocus)
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(textFieldPattern);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(stackNode);
    auto stackGeometryNode = stackNode->GetGeometryNode();
    CHECK_NULL_VOID(stackGeometryNode);
    auto stackRect = stackGeometryNode->GetFrameRect();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageGeometryNode = imageFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageRect = imageGeometryNode->GetFrameRect();
    if (isFocus) {
        hoverRectHeight = hoverRectHeight - ICON_FOCUS_PADDING.ConvertToPx();
    }

    auto iconHoverPadding = (hoverRectHeight - iconSize) / HALF_SPACE;
    auto stackHoverPadding = (hoverRectHeight - stackRect.Height()) / HALF_SPACE;
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRTL) {
        rect = RectF(stackRect.GetX() + stackRect.Width() - imageRect.Width() - iconHoverPadding,
            stackRect.GetY() - stackHoverPadding, hoverRectHeight, hoverRectHeight);
    } else {
        rect = RectF(stackRect.GetX() - iconHoverPadding, stackRect.GetY() - stackHoverPadding,
            hoverRectHeight, hoverRectHeight);
    }
}

void TextInputResponseArea::SetHotZoneRect(DimensionRect& hotZoneRegion, float iconSize, float hotZoneHeight)
{
    auto hotZoneX = - (hotZoneHeight - iconSize) / HALF_SPACE;
    auto hotZoneY = - (hotZoneHeight - iconSize) / HALF_SPACE;

    OffsetF hotZoneOffset;
    hotZoneOffset.SetX(hotZoneX);
    hotZoneOffset.SetY(hotZoneY);
    SizeF hotZoneSize;
    hotZoneSize.SetWidth(hotZoneHeight);
    hotZoneSize.SetHeight(hotZoneHeight);
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize.Width()), Dimension(hotZoneSize.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset.GetX()), Dimension(hotZoneOffset.GetY())));
}
// TextInputResponseArea end

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
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    stackLayoutProperty->UpdateAlignment(GetStackAlignment(layoutProperty->GetLayoutDirection()));
    AddEvent(stackNode);
    stackNode->MarkModifyDone();

    if (IsShowSymbol() && SystemProperties::IsNeedSymbol()) {
        auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(symbolNode, nullptr);
        passwordNode_ = symbolNode;
        InitSymbolEffectOptions();
        UpdateSymbolSource();

        symbolNode->MountToParent(stackNode);
        stackNode_ = stackNode;
        return stackNode;
    }

    LoadImageSourceInfo();
    auto currentImageSourceInfo = GetCurrentSourceInfo();
    CHECK_NULL_RETURN(currentImageSourceInfo, nullptr);
    auto imageNode = CreateResponseAreaImageNode(currentImageSourceInfo.value(), ImageFit::FILL,
        CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    CHECK_NULL_RETURN(imageNode, nullptr);

    passwordNode_ = imageNode;
    AddImageEventOnError();
    imageNode->MarkModifyDone();
    imageNode->MountToParent(stackNode);
    stackNode_ = stackNode;
    return stackNode;
}

void PasswordResponseArea::AddIconHotZoneRect()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    if (host->LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    CHECK_NULL_VOID(stackNode_);
    auto stackGeometryNode = stackNode_->GetGeometryNode();
    CHECK_NULL_VOID(stackGeometryNode);
    auto stackRect = stackGeometryNode->GetFrameRect();

    auto iconSize = stackRect.Width() - GetIconRightOffset();
    auto hotZoneHeight = static_cast<float>(DEFAULT_ICON_HOT_ZONE.ConvertToPx());
    hotZoneHeight = passwordHoverSize_ > hotZoneHeight ? passwordHoverSize_ : hotZoneHeight;
    DimensionRect hotZoneRegion;
    SetHotZoneRect(hotZoneRegion, iconSize, hotZoneHeight);

    auto defaultHoverSize = static_cast<float>(DEFAULT_HOVER_SIZE.ConvertToPx());
    auto mouseHotZoneHeight = NearZero(passwordHoverSize_) ? defaultHoverSize : passwordHoverSize_;
    DimensionRect mouseHotZoneRegion;
    SetHotZoneRect(mouseHotZoneRegion, iconSize, mouseHotZoneHeight);

    std::vector<DimensionRect> mouseRegion;
    mouseRegion.emplace_back(mouseHotZoneRegion);

    auto stackGestureHub = stackNode_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(stackGestureHub);
    stackGestureHub->SetMouseResponseRegion(mouseRegion);

    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(hotZoneRegion);
    stackGestureHub->SetResponseRegion(responseRegion);
}

void PasswordResponseArea::CreateIconRect(RoundRect& paintRect, bool isFocus)
{
    CHECK_NULL_VOID(stackNode_);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode_->GetFirstChild());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageGeometryNode = imageFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageRect = imageGeometryNode->GetFrameRect();
    auto textInputNode = stackNode_->GetParentFrameNode();
    CHECK_NULL_VOID(textInputNode);
    auto textInputRect = textInputNode->GetGeometryNode()->GetFrameRect();
    auto iconSize = imageRect.Height();
    auto defaultRectHeight = DEFAULT_HOVER_SIZE.ConvertToPx();
    auto rectHeight = iconSize > defaultRectHeight ? iconSize : defaultRectHeight;
    auto hoverRectHeight = rectHeight > textInputRect.Height() ? textInputRect.Height() : rectHeight;
    auto maxHoverRectHeight = iconSize + DOUBLE_PADDING * GetIconRightOffset();
    hoverRectHeight = hoverRectHeight > maxHoverRectHeight ? maxHoverRectHeight : hoverRectHeight;
    passwordHoverSize_ = hoverRectHeight;
    hoverIconPadding_ = (hoverRectHeight - iconSize) / HALF_SPACE;
    RectF rect;
    SetHoverRect(stackNode_, rect, iconSize, hoverRectHeight, isFocus);
    paintRect.SetRect(rect);
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
        auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        auto node = button->GetFrameNode();
        CHECK_NULL_VOID(node);
        auto message = !button->IsObscured() ? theme->GetHasShowedPassword() : theme->GetHasHiddenPassword();
        node->OnAccessibilityEvent(AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY, message);
    };
    auto mouseTask = [id = Container::CurrentId(), weak = hostPattern_](MouseInfo& info) {
        info.SetStopPropagation(true);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textfield = DynamicCast<TextFieldPattern>(pattern);
        CHECK_NULL_VOID(textfield);
        textfield->RestoreDefaultMouseState();
    };
    auto touchTask = [weak = WeakClaim(this)](TouchEventInfo& info) {
        info.SetStopPropagation(true);
    };

    auto inputHub = node->GetOrCreateInputEventHub();
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
    gesture->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    gesture->AddTouchEvent(MakeRefPtr<TouchEventImpl>(std::move(touchTask)));
}

void PasswordResponseArea::Refresh()
{
    auto iconNode = passwordNode_.Upgrade();
    if (!iconNode) {
        InitResponseArea();
        return;
    }

    auto textFieldPattern = hostPattern_.Upgrade();
    if (textFieldPattern && stackNode_) {
        auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
        auto stackLayoutProperty = stackNode_->GetLayoutProperty<LayoutProperty>();
        if (stackLayoutProperty && layoutProperty) {
            stackLayoutProperty->UpdateAlignment(GetStackAlignment(layoutProperty->GetLayoutDirection()));
        }
    }

    // update node symbol
    if (IsShowSymbol() && IsSymbolIcon() && SystemProperties::IsNeedSymbol()) {
        UpdateSymbolColor();
        return;
    }

    // update node image
    if (!IsShowSymbol() && !IsSymbolIcon()) {
        auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        CHECK_NULL_VOID(imageLayoutProperty->HasImageSourceInfo());
        auto currentSrc = imageLayoutProperty->GetImageSourceInfoValue().GetSrc();
        LoadImageSourceInfo();
        auto src = isObscured_ ? hideIcon_->GetSrc() : showIcon_->GetSrc();
        if (currentSrc != src) {
            UpdateImageSource();
        }
        return;
    }

    ReplaceNode();
}

void PasswordResponseArea::ClearArea()
{
    auto hostPattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(hostPattern);
    auto host = hostPattern->GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(stackNode_);
    host->RemoveChildAndReturnIndex(stackNode_);
    passwordNode_.Reset();
    areaRect_.Reset();
}

void PasswordResponseArea::ReplaceNode()
{
    auto oldFrameNode = passwordNode_.Upgrade();
    CHECK_NULL_VOID(oldFrameNode);

    if (IsShowSymbol() && SystemProperties::IsNeedSymbol()) {
        auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(symbolNode);
        stackNode_->ReplaceChild(oldFrameNode, symbolNode);
        passwordNode_ = symbolNode;
        InitSymbolEffectOptions();
        UpdateSymbolSource();
        return;
    }

    auto iconSize = GetIconSize();
    LoadImageSourceInfo();
    auto currentImageSourceInfo = GetCurrentSourceInfo();
    CHECK_NULL_VOID(currentImageSourceInfo);
    auto imageNode = CreateResponseAreaImageNode(currentImageSourceInfo.value(), ImageFit::FILL,
        CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    CHECK_NULL_VOID(imageNode);

    stackNode_->ReplaceChild(oldFrameNode, imageNode);
    passwordNode_ = imageNode;
    AddImageEventOnError();
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void PasswordResponseArea::OnPasswordIconClicked()
{
    isObscured_ = !isObscured_;
    ChangeObscuredState();
}

void PasswordResponseArea::UpdatePasswordIconColor(const Color& color)
{
    showIcon_->SetFillColor(color);
    hideIcon_->SetFillColor(color);

    if (IsSymbolIcon()) {
        UpdateSymbolColor();
    } else {
        UpdateImageSource();
    }
}

void PasswordResponseArea::ChangeObscuredState()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (IsSymbolIcon() && SystemProperties::IsNeedSymbol()) {
        UpdateSymbolSource();
    } else {
        UpdateImageSource();
    }
    textFieldPattern->OnObscuredChanged(isObscured_);
}

SizeF PasswordResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (!IsShowPasswordIcon()) {
        return SizeF(0, 0);
    }
    auto textInputMeasure = TextInputResponseArea::Measure(layoutWrapper, index);
    AddIconHotZoneRect();
    return textInputMeasure;
}

void PasswordResponseArea::Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth)
{
    if (!IsShowPasswordIcon()) {
        return;
    }
    LayoutChild(layoutWrapper, index, nodeWidth);
}

float PasswordResponseArea::GetIconSize()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, 0.0f);
    auto tmpHost = textFieldPattern->GetHost();
    CHECK_NULL_RETURN(tmpHost, 0.0f);
    auto pipeline = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto iconSize = textFieldTheme->GetIconSize().ConvertToPx();
    if (tmpHost->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        iconSize = textFieldTheme->GetPasswordIconSize().ConvertToPx();
    }
    return static_cast<float>(iconSize);
}

float PasswordResponseArea::GetIconRightOffset()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, 0.0f);
    auto tmpHost = textFieldPattern->GetHost();
    auto pipeline = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = textFieldTheme->GetPadding();
    if (tmpHost->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        auto passwordIconPadding = textFieldTheme->GetPasswordIconPadding();
        return static_cast<float>(passwordIconPadding.ConvertToPx());
    }
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
    auto pipeline = tmpHost->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>(tmpHost->GetThemeScopeId());
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

void PasswordResponseArea::AddImageEventOnError()
{
    auto imageNode = passwordNode_.Upgrade();
    auto eventHub = imageNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError([ weakNode = WeakClaim(AceType::RawPtr(imageNode)), weakArea = WeakClaim(this) ]
        (const LoadImageFailEvent& info) {
        auto host = weakNode.Upgrade();
        CHECK_NULL_VOID(host);
        auto area = weakArea.Upgrade();
        CHECK_NULL_VOID(area);
        auto imagePattern = host->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(imagePattern);
        auto layoutProperty = host->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateImageSourceInfo(area->GetDefaultSourceInfo(area->isObscured_));
        imagePattern->LoadImageDataIfNeed();
    });
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

void PasswordResponseArea::UpdateSymbolSource()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto symbolNode = passwordNode_.Upgrade();
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    auto currentSymbolId = isObscured_ ? textFieldTheme->GetHideSymbolId() : textFieldTheme->GetShowSymbolId();
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(currentSymbolId));
    symbolProperty->UpdateFontSize(textFieldTheme->GetSymbolSize());
    symbolColor_ = textFieldTheme->GetSymbolColor();
    symbolProperty->UpdateSymbolColorList({ symbolColor_ });
    symbolProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        symbolProperty->UpdateFontSize(textFieldTheme->GetPasswordIconSize());
    }

    symbolNode->MarkModifyDone();
    symbolNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void PasswordResponseArea::UpdateSymbolColor()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto symbolNode = passwordNode_.Upgrade();
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    Color color = textFieldTheme->GetSymbolColor();
    if (layoutProperty->GetIsDisabledValue(false)) {
        color = textFieldTheme->GetTextColorDisable();
    }

    // frame bug, MarkDirtyNode will trigger symbol effect
    // add a temp variable for record color, prevent frequent MarkDirtyNode triggering
    if (symbolColor_ != color) {
        symbolColor_ = color;
        symbolProperty->UpdateSymbolColorList({ symbolColor_ });
        symbolNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void PasswordResponseArea::InitSymbolEffectOptions()
{
    auto symbolNode = passwordNode_.Upgrade();
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    auto symbolEffectOptions = symbolProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.SetEffectType(SymbolEffectType::REPLACE);
    symbolEffectOptions.SetScopeType(Ace::ScopeType::WHOLE);
    symbolEffectOptions.SetIsTxtActive(true);
    symbolEffectOptions.SetIsTxtActiveSource(0);
    symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
}

bool PasswordResponseArea::IsShowSymbol()
{
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsShowPasswordSymbol();
}

bool PasswordResponseArea::IsSymbolIcon()
{
    auto iconFrameNode = passwordNode_.Upgrade();
    CHECK_NULL_RETURN(iconFrameNode, false);
    return iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG;
}

bool PasswordResponseArea::IsShowPasswordIcon()
{
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsShowPasswordIcon();
}

void PasswordResponseArea::OnThemeScopeUpdate(const RefPtr<TextFieldTheme>& theme)
{
    // no interface to set password icon color, should update every time
    CHECK_NULL_VOID(theme);
    UpdatePasswordIconColor(theme->GetSymbolColor());
} // PasswordResponseArea end

// UnitResponseArea begin
void UnitResponseArea::InitResponseArea()
{
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

void UnitResponseArea::ClearArea()
{
    auto hostPattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(hostPattern);
    auto host = hostPattern->GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(unitNode_);
    host->RemoveChildAndReturnIndex(unitNode_);
    areaRect_.Reset();
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

bool UnitResponseArea::IsShowUnit()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsUnderlineMode();
} // UnitResponseArea end

void CleanNodeResponseArea::InitResponseArea()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    LoadingImageProperty();
    auto cleanNode = CreateNode();
    CHECK_NULL_VOID(cleanNode);
    cleanNode->MountToParent(host);
}

SizeF CleanNodeResponseArea::Measure(LayoutWrapper* layoutWrapper, int32_t index)
{
    auto textInputMeasure = TextInputResponseArea::Measure(layoutWrapper, index);
    AddIconHotZoneRect();
    return textInputMeasure;
}

void CleanNodeResponseArea::AddIconHotZoneRect()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    if (host->LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    CHECK_NULL_VOID(cleanNode_);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(cleanNode_->GetFirstChild());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageGeometryNode = imageFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageRect = imageGeometryNode->GetFrameRect();
    auto iconSize = imageRect.Height();
    auto hotZoneHeight = static_cast<float>(DEFAULT_ICON_HOT_ZONE.ConvertToPx());
    hotZoneHeight = cancelHoverSize_ > hotZoneHeight ? cancelHoverSize_ : hotZoneHeight;
    DimensionRect hotZoneRegion;
    SetHotZoneRect(hotZoneRegion, iconSize, hotZoneHeight);

    auto defaultHoverSize = static_cast<float>(DEFAULT_HOVER_SIZE.ConvertToPx());
    auto mouseHotZoneHeight = NearZero(cancelHoverSize_) ? defaultHoverSize : cancelHoverSize_;
    DimensionRect mouseHotZoneRegion;
    SetHotZoneRect(mouseHotZoneRegion, iconSize, mouseHotZoneHeight);

    std::vector<DimensionRect> mouseRegion;
    mouseRegion.emplace_back(mouseHotZoneRegion);

    auto stackGestureHub = cleanNode_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(stackGestureHub);
    stackGestureHub->SetMouseResponseRegion(mouseRegion);

    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(hotZoneRegion);
    stackGestureHub->SetResponseRegion(responseRegion);
}

float GetCancelButtonPadding(const RefPtr<TextFieldTheme>& textFieldTheme)
{
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = textFieldTheme->GetPadding();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        auto cancelButtonPadding = textFieldTheme->GetCancelIconPadding();
        return static_cast<float>(cancelButtonPadding.ConvertToPx());
    }
    return static_cast<float>(themePadding.Left().ConvertToPx());
}

void CleanNodeResponseArea::CreateIconRect(RoundRect& paintRect, bool isFocus)
{
    CHECK_NULL_VOID(cleanNode_);
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(cleanNode_->GetFirstChild());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageGeometryNode = imageFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageRect = imageGeometryNode->GetFrameRect();
    auto textInputNode = cleanNode_->GetParentFrameNode();
    CHECK_NULL_VOID(textInputNode);
    auto textInputRect = textInputNode->GetGeometryNode()->GetFrameRect();
    auto iconSize = imageRect.Height();
    auto defaultRectHeight = DEFAULT_HOVER_SIZE.ConvertToPx();
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto rectHeight = iconSize > defaultRectHeight ? iconSize : defaultRectHeight;
    auto hoverRectHeight = rectHeight > textInputRect.Height() ? textInputRect.Height() : rectHeight;
    auto maxHoverRectHeight = iconSize + DOUBLE_PADDING * GetCancelButtonPadding(theme);
    hoverRectHeight = hoverRectHeight > maxHoverRectHeight ? maxHoverRectHeight : hoverRectHeight;
    cancelHoverSize_ = hoverRectHeight;
    hoverIconPadding_ = (hoverRectHeight - iconSize) / HALF_SPACE;
    RectF rect;
    SetHoverRect(cleanNode_, rect, iconSize, hoverRectHeight, isFocus);
    paintRect.SetRect(rect);
}

bool CleanNodeResponseArea::IsShowClean() const
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFieldPattern, false);
    return textFieldPattern->IsShowCancelButtonMode();
}

bool CleanNodeResponseArea::IsShowSymbol() const
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    return textFieldLayoutProperty->GetIsShowSymbolValue(true);
}

bool CleanNodeResponseArea::IsSymbolIcon() const
{
    CHECK_NULL_RETURN(cleanNode_, false);
    CHECK_NULL_RETURN(cleanNode_->GetFirstChild(), false);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(cleanNode_->GetFirstChild());
    CHECK_NULL_RETURN(iconFrameNode, false);
    return iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG;
}

void CleanNodeResponseArea::Layout(LayoutWrapper *layoutWrapper, int32_t index, float &nodeWidth)
{
    if (!IsShowClean()) {
        return;
    }
    LayoutChild(layoutWrapper, index, nodeWidth);
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
    stackLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    auto textFieldPattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(textFieldPattern, nullptr);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    stackLayoutProperty->UpdateAlignment(GetStackAlignment(layoutProperty->GetLayoutDirection()));
    stackNode->MarkModifyDone();

    if (IsShowSymbol() && SystemProperties::IsNeedSymbol()) {
        auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(symbolNode, nullptr);
        cleanNode_ = stackNode;
        symbolNode->MountToParent(stackNode);
        InitClickEvent(stackNode);
        SetCancelSymbolIconSize();
        UpdateSymbolSource();
        return stackNode;
    }

    auto info = CreateImageSourceInfo();
    auto imageNode = CreateResponseAreaImageNode(info, ImageFit::COVER, CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);

    cleanNode_ = stackNode;
    imageNode->MarkModifyDone();
    imageNode->MountToParent(stackNode);
    InitClickEvent(stackNode);
    return stackNode;
}

void CleanNodeResponseArea::SetCancelSymbolIconSize()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto symbolNode = cleanNode_->GetFirstChild();
    CHECK_NULL_VOID(symbolNode);
    auto symbolFrameNode = AceType::DynamicCast<FrameNode>(symbolNode);
    CHECK_NULL_VOID(symbolFrameNode);
    auto symbolProperty = symbolFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    symbolProperty->UpdateFontSize(textFieldTheme->GetSymbolSize());
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        symbolProperty->UpdateFontSize(textFieldTheme->GetCancelIconSize());
    }
}

CalcDimension CleanNodeResponseArea::GetSymbolDefaultSize()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, CalcDimension());
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_RETURN(host, CalcDimension());
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, CalcDimension());
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, CalcDimension());
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, CalcDimension());
    return textTheme->GetTextStyle().GetFontSize();
}

void CleanNodeResponseArea::UpdateSymbolSource()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto symbolNode = cleanNode_->GetFirstChild();
    CHECK_NULL_VOID(symbolNode);
    auto symbolFrameNode = AceType::DynamicCast<FrameNode>(symbolNode);
    CHECK_NULL_VOID(symbolFrameNode);
    auto symbolProperty = symbolFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto lastFontSize = symbolProperty->GetFontSize().value_or(GetSymbolDefaultSize());
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(textFieldTheme->GetCancelSymbolId()));
    symbolProperty->UpdateSymbolColorList({ textFieldTheme->GetSymbolColor() });
    auto maxFontScale = layoutProperty->GetMaxFontScale().value_or(MAX_FONT_SCALE);
    symbolProperty->UpdateMaxFontScale(std::min(MAX_FONT_SCALE, maxFontScale));
    symbolProperty->UpdateMinFontScale(layoutProperty->GetMinFontScale().value_or(0.0f));

    auto iconSymbol = layoutProperty->GetCancelIconSymbol();
    if (iconSymbol && host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        iconSymbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(symbolFrameNode)));
        // reset symbol effect
        auto symbolEffectOptions = symbolProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
        symbolEffectOptions.SetIsTxtActive(false);
        symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    }

    Dimension fontSize;
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        fontSize = symbolProperty->GetFontSize().value_or(textFieldTheme->GetCancelIconSize());
    } else {
        fontSize = symbolProperty->GetFontSize().value_or(textFieldTheme->GetSymbolSize());
    }
    if (GreatOrEqualCustomPrecision(fontSize.ConvertToPx(), ICON_MAX_SIZE.ConvertToPx())) {
        fontSize = ICON_MAX_SIZE;
    }
    iconSize_ = fontSize;
    symbolProperty->UpdateFontSize(lastFontSize);

    symbolFrameNode->MarkModifyDone();
    symbolFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
    gesture->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(clickCallback)));
}

void CleanNodeResponseArea::OnCleanNodeClicked()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    CHECK_NULL_VOID(!textFieldPattern->IsDragging());
    textFieldPattern->CleanNodeResponseKeyEvent();
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
}

void CleanNodeResponseArea::UpdateCleanNode(bool isShow)
{
    isShow_ = isShow;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    CHECK_NULL_VOID(cleanNode_);
    auto stackLayoutProperty = cleanNode_->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(stackLayoutProperty);
    auto iconNode = cleanNode_->GetFirstChild();
    CHECK_NULL_VOID(iconNode);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(iconNode);
    CHECK_NULL_VOID(iconFrameNode);
    auto iconLayoutProperty = iconFrameNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(iconLayoutProperty);
    if (isShow) {
        auto host = textFieldPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto rightOffset = GetCancelButtonPadding(textFieldTheme);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto frameSize = geometryNode->GetFrameSize();
        auto iconSize = GetIconSize();
        if (!NearZero(frameSize.Height())) {
            iconSize = std::min(iconSize, frameSize.Height());
        }
        auto hotZoneSize = NearZero(iconSize) ? 0.0f : iconSize + rightOffset;
        stackLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(hotZoneSize), CalcLength(iconSize)));
        iconLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
        if (IsSymbolIcon()) {
            auto symbolProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(symbolProperty);
            symbolProperty->UpdateFontSize(CalcDimension(iconSize));
        }
        stackLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        iconLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        stackLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), std::nullopt));
        iconLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
        stackLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        iconLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    }
    iconFrameNode->MarkModifyDone();
    iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool CleanNodeResponseArea::CheckUpdateCleanNode()
{
    CHECK_NULL_RETURN(cleanNode_, false);
    auto cleanNodeGeometryNode = cleanNode_->GetGeometryNode();
    CHECK_NULL_RETURN(cleanNodeGeometryNode, false);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(hostPattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, false);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto textFieldFrameSize = geometryNode->GetFrameSize();
    auto cleanNodeFrameSize = cleanNodeGeometryNode->GetFrameSize();
    return GreatNotEqual(cleanNodeFrameSize.Height(), textFieldFrameSize.Height());
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
    areaRect_.Reset();
}

void CleanNodeResponseArea::Refresh()
{
    auto textFieldPattern = hostPattern_.Upgrade();
    if (textFieldPattern && cleanNode_) {
        auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
        auto stackLayoutProperty = cleanNode_->GetLayoutProperty<LayoutProperty>();
        if (layoutProperty && stackLayoutProperty) {
            stackLayoutProperty->UpdateAlignment(GetStackAlignment(layoutProperty->GetLayoutDirection()));
        }
    }

    // update node symbol
    if (IsShowSymbol() && IsSymbolIcon() && SystemProperties::IsNeedSymbol()) {
        UpdateSymbolSource();
        return;
    }

    // update node image
    if (!IsShowSymbol() && !IsSymbolIcon()) {
        LoadingImageProperty();
        auto info = CreateImageSourceInfo();
        CHECK_NULL_VOID(cleanNode_);
        auto imageNode = cleanNode_->GetFirstChild();
        CHECK_NULL_VOID(imageNode);
        auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
        CHECK_NULL_VOID(imageFrameNode);
        auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(info);
        imageFrameNode->MarkModifyDone();
        imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }

    ReplaceNode();
}

void CleanNodeResponseArea::ReplaceNode()
{
    CHECK_NULL_VOID(cleanNode_);
    CHECK_NULL_VOID(cleanNode_->GetFirstChild());
    auto oldFrameNode = AceType::DynamicCast<FrameNode>(cleanNode_->GetFirstChild());
    CHECK_NULL_VOID(oldFrameNode);

    if (IsShowSymbol() && SystemProperties::IsNeedSymbol()) {
        auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(symbolNode);
        cleanNode_->ReplaceChild(oldFrameNode, symbolNode);
        UpdateSymbolSource();
        return;
    }

    LoadingImageProperty();
    auto info = CreateImageSourceInfo();
    auto imageNode = CreateResponseAreaImageNode(info, ImageFit::COVER, CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    CHECK_NULL_VOID(imageNode);

    cleanNode_->ReplaceChild(oldFrameNode, imageNode);
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void CleanNodeResponseArea::LoadingImageProperty()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (textFieldLayoutProperty->HasIconSize()) {
        auto iconSizeValue = textFieldLayoutProperty->GetIconSizeValue();
        if (iconSizeValue.Unit() == DimensionUnit::PERCENT) {
            iconSize_ = iconSizeValue;
        } else {
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto pipeline = host->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto maxFontScale = pipeline->GetFontScale();
            auto minFontScale = 0.0f;
            if (textFieldLayoutProperty->HasMaxFontScale()) {
                maxFontScale = std::min(textFieldLayoutProperty->GetMaxFontScale().value(), maxFontScale);
            }
            if (textFieldLayoutProperty->HasMinFontScale()) {
                minFontScale = textFieldLayoutProperty->GetMinFontScale().value();
            }
            iconSize_ = Dimension(iconSizeValue).ConvertToPxDistribute(minFontScale, maxFontScale);
        }
    }
    if (textFieldLayoutProperty->HasIconSrc()) {
        iconSrc_ = textFieldLayoutProperty->GetIconSrcValue();
    }
    LoadingCancelButtonColor();
    if (textFieldLayoutProperty->HasBundleName()) {
        bundleName_ = textFieldLayoutProperty->GetBundleNameValue();
    }
    if (textFieldLayoutProperty->HasModuleName()) {
        moduleName_ = textFieldLayoutProperty->GetModuleNameValue();
    }
}

void CleanNodeResponseArea::LoadingCancelButtonColor()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (textFieldLayoutProperty->GetIsDisabledValue(false)) {
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        iconColor_ = theme->GetTextColorDisable();
    } else if (textFieldLayoutProperty->HasIconColor()) {
        iconColor_ = textFieldLayoutProperty->GetIconColorValue();
    }
}

ImageSourceInfo CleanNodeResponseArea::CreateImageSourceInfo()
{
    ImageSourceInfo info;
    info.SetBundleName(bundleName_);
    info.SetModuleName(moduleName_);
    if (iconSrc_.empty()) {
        info.SetResourceId(InternalResource::ResourceId::CLOSE_SVG);
    } else {
        info.SetSrc(iconSrc_);
    }
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, info);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, info);
    if (info.IsSvg() && textFieldLayoutProperty->HasIconColor()) {
        info.SetFillColor(iconColor_);
        CHECK_NULL_RETURN(cleanNode_, info);
        auto imageNode = cleanNode_->GetFirstChild();
        CHECK_NULL_RETURN(imageNode, info);
        auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
        CHECK_NULL_RETURN(imageFrameNode, info);
        auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_RETURN(imageRenderProperty, info);
        imageRenderProperty->UpdateSvgFillColor(iconColor_);
    }
    return info;
}

void CleanNodeResponseArea::OnThemeScopeUpdate(const RefPtr<TextFieldTheme>& theme)
{
    if (IsShowSymbol() && SystemProperties::IsNeedSymbol()) {
        UpdateSymbolSource();
    }
}
} // namespace OHOS::Ace::NG