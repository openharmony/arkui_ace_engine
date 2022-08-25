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

#include "core/components/text_overlay/text_overlay_component.h"

namespace OHOS::Ace {
TextOverlayComponent::TextOverlayComponent(
    const RefPtr<ThemeManager>& themeManager, const RefPtr<AccessibilityManager>& accessibilityManager)
{
    themeManager_ = themeManager;
    accessibilityManager_ = accessibilityManager;
    InitThemeStyle(themeManager);
}

RefPtr<Element> TextOverlayComponent::CreateElement()
{
    return nullptr;
}

RefPtr<RenderNode> TextOverlayComponent::CreateRenderNode()
{
    return nullptr;
}

void TextOverlayComponent::InitThemeStyle(const RefPtr<ThemeManager>& themeManager)
{
}

RefPtr<Component> TextOverlayComponent::BuildChild(
    bool isSingleHandle, bool hasToolBar, bool hasMenu, bool hasIcon, bool hasAnimation)
{
    return nullptr;
}

RefPtr<Component> TextOverlayComponent::BuildToolBar(
    bool isSingleHandle, bool hasToolBar, bool hasMenu, bool hasIcon, bool hasAnimation)
{
    return nullptr;
}

RefPtr<ButtonComponent> TextOverlayComponent::BuildButton(const std::string& data, const EventMarker& onClick)
{
    return nullptr;
}

RefPtr<ButtonComponent> TextOverlayComponent::BuildMoreIconButton(bool hasMenu)
{
    return nullptr;
}

RefPtr<Component> TextOverlayComponent::BuildAnimation(const RefPtr<Component>& child, bool hasAnimation)
{
    return nullptr;
}

void TextOverlayComponent::BuildMenuForDeclative(bool isSingleHandle)
{
}

RefPtr<Component> TextOverlayComponent::BuildMenu(bool isSingleHandle)
{
    return nullptr;
}

void TextOverlayComponent::AddOptionForMenu()
{
}

RefPtr<OptionComponent> TextOverlayComponent::BuildMenuOption(
    const std::string& imageSrc, InternalResource::ResourceId resourceId, const std::string& text, bool useResource)
{
    return nullptr;
}

void TextOverlayComponent::OnOptionClick(int32_t index)
{
}

void TextOverlayComponent::OnToolBarButtonClick(const EventMarker& marker, const std::string& eventName)
{
}

std::string TextOverlayComponent::GetSelectedText() const
{
    return "";
}

bool TextOverlayComponent::HasMoreButton() const
{
    return hasMoreButton_;
}

void TextOverlayComponent::SetIsPassword(bool isPassword)
{
    isPassword_ = isPassword;
}

bool TextOverlayComponent::GetIsPassword() const
{
    return isPassword_;
}

void TextOverlayComponent::SetIsSingleHandle(bool isSingleHandle)
{
    isSingleHandle_ = isSingleHandle;
}

bool TextOverlayComponent::GetIsSingleHandle() const
{
    return isSingleHandle_;
}

void TextOverlayComponent::SetLineHeight(double lineHeight)
{
    lineHeight_ = lineHeight;
}

double TextOverlayComponent::GetLineHeight() const
{
    return lineHeight_;
}

void TextOverlayComponent::SetStartHandleHeight(double startHandleHeight)
{
    startHandleHeight_ = startHandleHeight;
}

const std::optional<double>& TextOverlayComponent::GetStartHandleHeight() const
{
    return startHandleHeight_;
}

void TextOverlayComponent::SetEndHandleHeight(double endHandleHeight)
{
    endHandleHeight_ = endHandleHeight;
}

const std::optional<double>& TextOverlayComponent::GetEndHandleHeight() const
{
    return endHandleHeight_;
}

void TextOverlayComponent::SetClipRect(const Rect& clipRect)
{
    clipRect_ = clipRect;
}

const Rect& TextOverlayComponent::GetClipRect() const
{
    return clipRect_;
}

void TextOverlayComponent::SetHandleColor(const Color& handleColor)
{
    handleColor_ = handleColor;
}

const Color& TextOverlayComponent::GetHandleColor() const
{
    return handleColor_;
}

void TextOverlayComponent::SetHandleColorInner(const Color& handleColorInner)
{
    handleColorInner_ = handleColorInner;
}

const Color& TextOverlayComponent::GetHandleColorInner() const
{
    return handleColorInner_;
}

void TextOverlayComponent::SetHandleDiameter(const Dimension& handleDiameter)
{
    handleDiameter_ = handleDiameter;
}

const Dimension& TextOverlayComponent::GetHandleDiameter() const
{
    return handleDiameter_;
}

void TextOverlayComponent::SetHandleDiameterInner(const Dimension& handleDiameterInner)
{
    handleDiameterInner_ = handleDiameterInner;
}

const Dimension& TextOverlayComponent::GetHandleDiameterInner() const
{
    return handleDiameterInner_;
}

void TextOverlayComponent::SetMenuSpacingWithText(const Dimension& menuSpacingWithText)
{
    menuSpacingWithText_ = menuSpacingWithText;
}

const Dimension& TextOverlayComponent::GetMenuSpacingWithText() const
{
    return menuSpacingWithText_;
}

void TextOverlayComponent::SetOnFocusChange(const std::function<void(bool, bool)>& onFocusChange)
{
    onFocusChange_ = onFocusChange;
}

const std::function<void(bool, bool)>& TextOverlayComponent::GetOnFocusChange() const
{
    return onFocusChange_;
}

void TextOverlayComponent::SetOnCut(const CommonCallback& onCut)
{
    onCut_ = onCut;
}

const CommonCallback& TextOverlayComponent::GetOnCut() const
{
    return onCut_;
}

void TextOverlayComponent::SetOnCopy(const CommonCallback& onCopy)
{
    onCopy_ = onCopy;
}

const CommonCallback& TextOverlayComponent::GetOnCopy() const
{
    return onCopy_;
}

void TextOverlayComponent::SetOnPaste(const CommonCallback& onPaste)
{
    onPaste_ = onPaste;
}

const CommonCallback& TextOverlayComponent::GetOnPaste() const
{
    return onPaste_;
}

void TextOverlayComponent::SetOnCopyAll(const CopyAllCallback& onCopyAll)
{
    onCopyAll_ = onCopyAll;
}

const CopyAllCallback& TextOverlayComponent::GetOnCopyAll() const
{
    return onCopyAll_;
}

void TextOverlayComponent::SetCutButtonMarker(const EventMarker& cutButtonMarker)
{
    cutButtonMarker_ = cutButtonMarker;
}

const EventMarker& TextOverlayComponent::GetCutButtonMarker() const
{
    return cutButtonMarker_;
}

void TextOverlayComponent::SetCopyButtonMarker(const EventMarker& copyButtonMarker)
{
    copyButtonMarker_ = copyButtonMarker;
}

const EventMarker& TextOverlayComponent::GetCopyButtonMarker() const
{
    return copyButtonMarker_;
}

void TextOverlayComponent::SetPasteButtonMarker(const EventMarker& pasteButtonMarker)
{
    pasteButtonMarker_ = pasteButtonMarker;
}

const EventMarker& TextOverlayComponent::GetPasteButtonMarker() const
{
    return pasteButtonMarker_;
}

void TextOverlayComponent::SetCopyAllButtonMarker(const EventMarker& copyAllButtonMarker)
{
    copyAllButtonMarker_ = copyAllButtonMarker;
}

const EventMarker& TextOverlayComponent::GetCopyAllButtonMarker() const
{
    return copyAllButtonMarker_;
}

void TextOverlayComponent::SetMoreButtonMarker(const EventMarker& moreButtonMarker)
{
    moreButtonMarker_ = moreButtonMarker;
}

const EventMarker& TextOverlayComponent::GetMoreButtonMarker() const
{
    return moreButtonMarker_;
}

void TextOverlayComponent::SetStartHandleOffset(const Offset& offset)
{
    startHandleOffset_ = offset;
}

const Offset& TextOverlayComponent::GetStartHandleOffset() const
{
    return startHandleOffset_;
}

void TextOverlayComponent::SetEndHandleOffset(const Offset& offset)
{
    endHandleOffset_ = offset;
}

const Offset& TextOverlayComponent::GetEndHandleOffset() const
{
    return endHandleOffset_;
}

void TextOverlayComponent::SetOnStartHandleMove(const StartHandleMoveCallback& onStartHandleMove)
{
    onStartHandleMove_ = onStartHandleMove;
}

const StartHandleMoveCallback& TextOverlayComponent::GetOnStartHandleMove() const
{
    return onStartHandleMove_;
}

void TextOverlayComponent::SetOnEndHandleMove(const EndHandleMoveCallback& onEndHandleMove)
{
    onEndHandleMove_ = onEndHandleMove;
}

const EndHandleMoveCallback& TextOverlayComponent::GetOnEndHandleMove() const
{
    return onEndHandleMove_;
}

void TextOverlayComponent::SetWeakTextField(const WeakPtr<RenderTextField>& weakTextField)
{
    weakTextField_ = weakTextField;
}

const WeakPtr<RenderTextField>& TextOverlayComponent::GetWeakTextField() const
{
    return weakTextField_;
}

void TextOverlayComponent::SetWeakText(const WeakPtr<RenderText>& weakText)
{
    weakText_ = weakText;
}

const WeakPtr<RenderText>& TextOverlayComponent::GetWeakText() const
{
    return weakText_;
}

void TextOverlayComponent::SetWeakImage(const WeakPtr<RenderImage>& weakImage)
{
    weakImage_ = weakImage;
}

const WeakPtr<RenderImage>& TextOverlayComponent::GetWeakImage() const
{
    return weakImage_;
}

void TextOverlayComponent::SetRealTextDirection(TextDirection realTextDirection)
{
    realTextDirection_ = realTextDirection;
}

TextDirection TextOverlayComponent::GetRealTextDirection() const
{
    return realTextDirection_;
}

void TextOverlayComponent::SetOptions(const std::vector<InputOption>& options)
{
    options_ = options;
}

const std::vector<InputOption>& TextOverlayComponent::GetOptions() const
{
    return options_;
}

void TextOverlayComponent::SetImageFill(const std::optional<Color>& imageFill)
{
    imageFill_ = imageFill;
}

void TextOverlayComponent::SetOptionsClickMarker(const EventMarker& onOptionsClick)
{
    optionsClickMarker_ = onOptionsClick;
}

void TextOverlayComponent::SetTranslateButtonMarker(const EventMarker& onTranslate)
{
    translateButtonMarker_ = onTranslate;
}

void TextOverlayComponent::SetShareButtonMarker(const EventMarker& onShare)
{
    shareButtonMarker_ = onShare;
}

void TextOverlayComponent::SetSearchButtonMarker(const EventMarker& onSearch)
{
    searchButtonMarker_ = onSearch;
}

void TextOverlayComponent::SetPopOverlay(const CommonCallback& popOverlay)
{
    popOverlay_ = popOverlay;
}

void TextOverlayComponent::SetContext(const WeakPtr<PipelineContext>& context)
{
    context_ = context;
}

const RefPtr<SelectPopupComponent>& TextOverlayComponent::GetMenu() const
{
    return menu_;
}
} // namespace OHOS::Ace
