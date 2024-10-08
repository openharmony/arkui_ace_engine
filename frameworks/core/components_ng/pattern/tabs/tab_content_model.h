/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_MODEL_H

#include <mutex>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/property/measure_property.h"
#include "core/event/ace_events.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
enum class SelectedMode {
    INDICATOR,
    BOARD,
};

enum class LayoutMode {
    AUTO,
    VERTICAL,
    HORIZONTAL,
};

struct BottomTabBarStyle {
    bool symmetricExtensible = false;
    LayoutMode layoutMode = LayoutMode::VERTICAL;
    FlexAlign verticalAlign = FlexAlign::CENTER;
};

struct IndicatorStyle final {
    Color color = Color::WHITE;
    Dimension height = 0.0_vp;
    Dimension width = 0.0_vp;
    Dimension borderRadius = 0.0_vp;
    Dimension marginTop = 0.0_vp;
    IndicatorStyle()
    {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        if (!pipelineContext) {
            return;
        }
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        if (!tabTheme) {
            return;
        }
        color = tabTheme->GetActiveIndicatorColor();
        height = tabTheme->GetSubTabIndicatorHeight();
        marginTop = tabTheme->GetSubTabIndicatorGap();
    }
    bool operator==(const IndicatorStyle& indicator) const
    {
        return (color == indicator.color) && (height == indicator.height) &&
               (width == indicator.width) && (borderRadius == indicator.borderRadius)
               && (marginTop == indicator.marginTop);
    }
};

struct BoardStyle final {
    Dimension borderRadius = 0.0_vp;
    BoardStyle()
    {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        if (!pipelineContext) {
            return;
        }
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        if (!tabTheme) {
            return;
        }
        borderRadius = tabTheme->GetFocusIndicatorRadius();
    }
    bool operator==(const BoardStyle& board) const
    {
        return borderRadius == board.borderRadius;
    }
};

struct LabelStyle {
    std::optional<Ace::TextOverflow> textOverflow;
    std::optional<uint32_t> maxLines;
    std::optional<Dimension> minFontSize;
    std::optional<Dimension> maxFontSize;
    std::optional<Ace::TextHeightAdaptivePolicy> heightAdaptivePolicy;
    std::optional<Dimension> fontSize;
    std::optional<Ace::FontWeight> fontWeight;
    std::optional<std::vector<std::string>> fontFamily;
    std::optional<Ace::FontStyle> fontStyle;
    std::optional<Color> unselectedColor;
    std::optional<Color> selectedColor;
};

struct IconStyle {
    std::optional<Color> unselectedColor;
    std::optional<Color> selectedColor;
};

struct TabBarSymbol {
    std::function<void(WeakPtr<NG::FrameNode>, std::string)> onApply = nullptr;
    bool selectedFlag = false;
};

class ACE_FORCE_EXPORT TabContentModel {
public:
    static TabContentModel* GetInstance();
    virtual ~TabContentModel() = default;

    virtual void Create() = 0;
    virtual void Create(std::function<void()>&& deepRenderFunc) = 0;
    virtual void Pop() = 0;
    virtual void SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
        const std::optional<TabBarSymbol>& tabBarSymbol, std::function<void()>&& builder, bool useContentOnly) = 0;
    virtual void SetTabBarStyle(TabBarStyle tabBarStyle) = 0;
    virtual void SetIndicator(const IndicatorStyle& indicator) = 0;
    virtual void SetBoard(const BoardStyle& board) = 0;
    virtual void SetSelectedMode(SelectedMode selectedMode) = 0;
    virtual void SetLabelStyle(const LabelStyle& labelStyle) = 0;
    virtual void SetIconStyle(const IconStyle& iconStyle)  {}
    virtual void SetPadding(const NG::PaddingProperty& padding) = 0;
    virtual void SetUseLocalizedPadding(bool useLocalizedPadding) = 0;
    virtual void SetLayoutMode(LayoutMode layoutMode) = 0;
    virtual void SetVerticalAlign(FlexAlign verticalAlign) = 0;
    virtual void SetSymmetricExtensible(bool isExtensible) = 0;
    virtual void SetId(const std::string& id) = 0;
    virtual void SetOnWillShow(std::function<void()>&& onWillShow) {}
    virtual void SetOnWillHide(std::function<void()>&& onWillHide) {}
    virtual void SetCustomStyleNode(const RefPtr<NG::FrameNode>& customStyleNode) {}

private:
    static std::unique_ptr<TabContentModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_MODEL_H
