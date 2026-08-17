/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PASSWORD_ICON_HOST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PASSWORD_ICON_HOST_H

#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/event/mouse_event.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {
class ImageSourceInfo;
namespace NG {
class FrameNode;
class RoundRect;
} // namespace NG
enum class TextDirection;

/**
 * @brief Interface for password icon hosting, decoupling PasswordResponseArea
 *        from concrete Pattern types (TextFieldPattern, RichEditorPattern).
 *
 * Both TextFieldPattern and RichEditorPattern implement this interface to
 * enable shared use of PasswordResponseArea.
 */
class IPasswordIconHost : public virtual AceType {
    DECLARE_ACE_TYPE(IPasswordIconHost, AceType);
public:
    ~IPasswordIconHost() override = default;

    virtual bool IsInPasswordMode() const = 0;
    virtual bool IsShowPasswordIcon() const = 0;
    virtual bool IsShowPasswordSymbol() const = 0;
    virtual void OnObscuredChanged(bool isObscured) = 0;
    virtual RefPtr<NG::FrameNode> GetHost() const = 0;
    virtual TextDirection GetLayoutDirection() = 0;
    virtual bool CheckLayoutProperty() = 0;
    virtual ImageSourceInfo GetShowPasswordSourceInfo(const ImageSourceInfo& defaultInfo) = 0;
    virtual ImageSourceInfo GetHidePasswordSourceInfo(const ImageSourceInfo& defaultInfo) = 0;
    virtual bool IsDisabled() = 0;
    virtual bool IsTV() const = 0;
    virtual void RestoreDefaultMouseState() = 0;
    virtual bool SetPasswordIconHoverColor(const std::vector<NG::RoundRect>& rects, uint32_t color) = 0;
    virtual bool ClearPasswordIconHoverColor() = 0;
    virtual bool GetPasswordIconHoverColor(uint32_t& color) = 0;
    virtual bool GetPasswordIconPressColor(uint32_t& color) = 0;
    virtual void SetResponseButtonTouched(bool isTouched) {}
    virtual void OnHover(bool isHover, const HoverInfo& info) {}
};

// Template helpers for IPasswordIconHost implementations — reduces structural duplication
// between TextFieldPattern and RichEditorPattern where only LayoutProperty/OverlayModifier
// types differ. Forward declarations suffice; full types are resolved at instantiation
// (in the .cpp files that already include them).

template <typename LayoutPropT>
inline bool IsShowPasswordIconImpl(const RefPtr<LayoutPropT>& prop, bool defaultShowIcon)
{
    CHECK_NULL_RETURN(prop, false);
    return prop->GetShowPasswordIconValue(defaultShowIcon);
}

template <typename LayoutPropT>
inline ImageSourceInfo GetShowPasswordSourceInfoImpl(const RefPtr<LayoutPropT>& prop,
    const ImageSourceInfo& defaultInfo)
{
    CHECK_NULL_RETURN(prop, defaultInfo);
    return prop->GetShowPasswordSourceInfoValue(defaultInfo);
}

template <typename LayoutPropT>
inline ImageSourceInfo GetHidePasswordSourceInfoImpl(const RefPtr<LayoutPropT>& prop,
    const ImageSourceInfo& defaultInfo)
{
    CHECK_NULL_RETURN(prop, defaultInfo);
    return prop->GetHidePasswordSourceInfoValue(defaultInfo);
}

template <typename LayoutPropT>
inline bool IsDisabledImpl(const RefPtr<LayoutPropT>& prop)
{
    CHECK_NULL_RETURN(prop, false);
    return prop->GetIsDisabledValue(false);
}

template <typename OverlayModT, typename StrategyT>
inline bool SetPasswordIconHoverColorImpl(
    const RefPtr<OverlayModT>& mod, const std::vector<NG::RoundRect>& rects,
    uint32_t color, const RefPtr<NG::FrameNode>& host, StrategyT strategy)
{
    CHECK_NULL_RETURN(mod, false);
    mod->SetHoverColorAndRects(rects, color);
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(strategy);
    return true;
}

template <typename OverlayModT, typename StrategyT>
inline bool ClearPasswordIconHoverColorImpl(
    const RefPtr<OverlayModT>& mod, const RefPtr<NG::FrameNode>& host, StrategyT strategy)
{
    CHECK_NULL_RETURN(mod, false);
    mod->ClearHoverColorAndRects();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(strategy);
    return true;
}

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PASSWORD_ICON_HOST_H
