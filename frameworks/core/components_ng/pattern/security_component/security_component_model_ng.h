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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_SECURITY_COMPONENT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_SECURITY_COMPONENT_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/security_component_common.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {
struct SecurityComponentElementStyle {
    int32_t text;
    int32_t icon;
    int32_t backgroundType;
    uint32_t symbolIcon;
};

class ACE_FORCE_EXPORT SecurityComponentModelNG {
public:
    typedef bool (*GetIconResourceFuncType) (int32_t iconStyle, InternalResource::ResourceId& id);
    typedef bool (*GetTextResourceFuncType) (int32_t textStyle, std::string& text);
    virtual ~SecurityComponentModelNG() = default;
    virtual void Create(int32_t text, int32_t icon,
        int32_t backgroundType, bool isArkuiComponent) = 0;
    void CreateCommon(const std::string& tag, int32_t text, int32_t icon,
        int32_t backgroundType,
        const std::function<RefPtr<Pattern>(void)>& patternCreator, bool isArkuiComponent);
    RefPtr<FrameNode> CreateNode(const std::string& tag, int32_t nodeId,
        SecurityComponentElementStyle& style,
        const std::function<RefPtr<Pattern>(void)>& patternCreator, bool isArkuiComponent);
    static void SetIconSize(const Dimension& value);
    static void SetIconSize(const NG::CalcSize& value);
    static void SetSymbolIconSize(const Dimension& value);
    static void SetIconColor(const Color& value);
    static void SetIconBorderRadius(const Dimension& value);
    static void SetIconBorderRadius(const std::optional<Dimension>& topLeft,
        const std::optional<Dimension>& topRight, const std::optional<Dimension>& bottomLeft,
        const std::optional<Dimension>& bottomRight);
    static void SetIcon(const ImageSourceInfo& value);
    static void SetText(const std::string& value);
    static void SetIconSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetIconColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetSymbolIconColor(const std::vector<Color>& value);
    static void SetFontSize(const Dimension& value);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetFontStyle(const Ace::FontStyle& value);
    static void SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetFontWeight(const FontWeight& value);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetFontFamily(const std::vector<std::string>& fontFamilies);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& fontFamilies);
    static void SetStateEffect(const bool& value);
    static void SetTipPosition(const TipPosition& value);
    static void SetFontColor(const Color& value);
    static void SetFontColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetBackgroundColor(const Color& value);
    static void SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& valueOpt);
    static void SetBackgroundBorderWidth(const Dimension& value);
    static void SetBackgroundBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBackgroundBorderColor(const Color& value);
    static void SetBackgroundBorderColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetBackgroundBorderStyle(const BorderStyle& value);
    static void SetBackgroundBorderStyle(FrameNode* frameNode, const std::optional<BorderStyle>& value);
    static void SetBackgroundBorderRadius(const Dimension& value);
    static void SetBackgroundBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBackgroundBorderRadius(const std::optional<Dimension>& topLeft,
        const std::optional<Dimension>& topRight, const std::optional<Dimension>& bottomLeft,
        const std::optional<Dimension>& bottomRight);
    static void SetBackgroundPadding(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom);
    static void SetBackgroundPadding(FrameNode* frameNode,
        const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom);
    static void SetBackgroundPadding(const std::optional<Dimension>& padding);
    static void SetTextIconSpace(const Dimension& value);
    static void SetTextIconSpace(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetTextIconLayoutDirection(const SecurityComponentLayoutDirection& value);
    static void SetTextIconLayoutDirection(FrameNode* frameNode,
        const std::optional<SecurityComponentLayoutDirection>& value);
    static void SetAlign(const Alignment alignment);
    static void SetMaxFontScale(const float value);
    static void SetMinFontScale(const float value);
    static void SetMaxLines(const int32_t value);
    static void SetAdaptMaxFontSize(const Dimension& value);
    static void SetAdaptMinFontSize(const Dimension& value);
    static void SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value);

    virtual bool GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id)
    {
        return false;
    }

    virtual bool GetTextResource(int32_t textStyle,  std::string& text)
    {
        return false;
    }

    virtual bool IsClickResultSuccess(GestureEvent& info)
    {
#ifdef SECURITY_COMPONENT_ENABLE
        auto secEventValue = info.GetSecCompHandleEvent();
        if (secEventValue != nullptr) {
            if (secEventValue->GetInt("handleRes",
                static_cast<int32_t>(SecurityComponentHandleResult::CLICK_SUCCESS)) ==
                static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK)) {
                return false;
            }
        }
#endif
        return true;
    }

protected:
    static RefPtr<SecurityComponentTheme> GetTheme();
    static void InitChildNode(FrameNode* frameNode, const SecurityComponentElementStyle& style,
    GetIconResourceFuncType getIconResource, GetTextResourceFuncType getTextResource);
    static bool InitSecurityComponent(FrameNode* frameNode,
        const SecurityComponentElementStyle& style, bool isArkuiComponent,
        GetIconResourceFuncType getIconResource, GetTextResourceFuncType getTextResource);

private:
    static void SetDefaultIconStyle(const RefPtr<FrameNode>& imageNode, InternalResource::ResourceId id,
        bool isButtonVisible);
    static void SetDefaultSymbolIconStyle(const RefPtr<FrameNode>& symbolNode, uint32_t symbolId,
        bool isButtonVisible);
    static void SetInvisibleBackgroundButton(const RefPtr<FrameNode>& buttonNode);
    static bool IsBackgroundVisible();
    static bool IsBackgroundVisible(FrameNode* frameNode);
    static bool IsArkuiComponent();
    static bool IsArkuiComponent(FrameNode* frameNode);
    static void NotifyFontColorSet();
    static bool IsBelowThreshold(const Color& value);
    static bool IsInReleaseList(uint32_t value);
    static void SetDefaultBackgroundButton(const RefPtr<FrameNode>& buttonNode,
        int32_t type);
    static void SetDefaultTextStyle(const RefPtr<FrameNode>& textNode, const std::string& text, bool isButtonVisible);
    static void InitLayoutProperty(RefPtr<FrameNode>& node, int32_t text, int32_t icon, uint32_t symbolIcon,
        int32_t backgroundType);
    RefPtr<FrameNode> InitChild(const std::string& tag, int32_t nodeId,
        SecurityComponentElementStyle& style, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_SECURITY_COMPONENT_MODEL_NG_H
