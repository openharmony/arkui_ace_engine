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
#include "core/components_ng/pattern/security_component/security_component_common.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SecurityComponentModelNG {
public:
    virtual ~SecurityComponentModelNG() = default;
    virtual void Create(int32_t text, int32_t icon,
        SecurityComponentBackgroundType backgroundType) = 0;
    void CreateCommon(const std::string& tag, int32_t text, int32_t icon,
        SecurityComponentBackgroundType backgroundType,
        const std::function<RefPtr<Pattern>(void)>& patternCreator);
    virtual void SetIconSize(const Dimension& value);
    virtual void SetIconColor(const Color& value);
    virtual void SetFontSize(const Dimension& value);
    virtual void SetFontStyle(const Ace::FontStyle& value);
    virtual void SetFontWeight(const FontWeight& value);
    virtual void SetFontFamily(const std::vector<std::string>& fontFamilies);
    virtual void SetFontColor(const Color& value);
    virtual void SetBackgroundColor(const Color& value);
    virtual void SetBackgroundBorderWidth(const Dimension& value);
    virtual void SetBackgroundBorderColor(const Color& value);
    virtual void SetBackgroundBorderStyle(const BorderStyle& value);
    virtual void SetBackgroundBorderRadius(const Dimension& value);
    virtual void SetBackgroundPadding(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom);
    virtual void SetBackgroundPadding(const std::optional<Dimension>& padding);
    virtual void SetTextIconPadding(const Dimension& value);
    virtual void SetTextIconLayoutDirection(const SecurityComponentLayoutDirection& value);
    virtual void SetlayoutOrder(const SecSecurityComponentLayoutOrder& value);

    virtual bool GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id)
    {
        return false;
    }

    virtual bool GetTextResource(int32_t textStyle,  std::string& text)
    {
        return false;
    }

protected:
    RefPtr<SecurityComponentTheme> GetTheme();

private:
    void SetDefaultIconStyle(const RefPtr<FrameNode>& imageNode, InternalResource::ResourceId id);
    void SetDefaultBackgroundButton(const RefPtr<FrameNode>& buttonNode,
        SecurityComponentBackgroundType type);
    void SetDefaultTextStyle(const RefPtr<FrameNode>& textNode, const std::string& text);
    void InitLayoutProperty(RefPtr<FrameNode>& node, int32_t text, int32_t icon,
        SecurityComponentBackgroundType backgroundType);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_SECURITY_COMPONENT_MODEL_NG_H
