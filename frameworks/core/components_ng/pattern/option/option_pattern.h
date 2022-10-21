/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_PATTERN_H

#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/option/option_event_hub.h"
#include "core/components_ng/pattern/option/option_layout_algorithm.h"
#include "core/components_ng/pattern/option/option_paint_method.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
class OptionPattern : public Pattern {
    DECLARE_ACE_TYPE(OptionPattern, Pattern);

public:
    OptionPattern(int32_t targetId, int index) : targetId_(targetId), index_(index) {}
    ~OptionPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<OptionPaintMethod>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<OptionPaintProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<OptionEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<OptionLayoutAlgorithm>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetTextNode(const RefPtr<FrameNode>& text)
    {
        text_ = text;
    }

    void SetBgColor(const Color& color);
    // set font props
    void SetFontSize(const Dimension& value);
    void SetItalicFontStyle(const Ace::FontStyle& value);
    void SetFontWeight(const FontWeight& value);
    void SetFontFamily(const std::vector<std::string>& value);
    void SetFontColor(const Color& color);

    const Color& GetBgColor()
    {
        return bgColor_;
    }

    // get font props
    Dimension GetFontSize();
    Ace::FontStyle GetItalicFontStyle();
    FontWeight GetFontWeight();
    std::vector<std::string> GetFontFamily();
    Color GetFontColor();

    const std::string& GetText();

    // XTS inspector functions
    std::string InspectorGetFont();

    void SetIcon(const std::string& src)
    {
        iconSrc_ = src;
    }

    const std::string& GetIcon()
    {
        return iconSrc_;
    }

private:
    void OnModifyDone() override;

    void UpdateNextNodeDivider(bool needDivider);

    // register option's callback
    void RegisterOnClick();

    void RegisterOnTouch();
    // change option paint props on hover
    void OnHover(const TouchEventInfo& info);

    Color bgColor_ = Color(OPTION_DEFAULT_BACKGROUND_COLOR);

    // src of icon image, used in XTS inspector
    std::string iconSrc_;
    RefPtr<FrameNode> text_ = nullptr;
    RefPtr<TextTheme> textTheme_ = nullptr;
    // to hide menu through OverlayManager when option is clicked
    int32_t targetId_ = -1;
    // this option node's index in the menu
    int index_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(OptionPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_PATTERN_H
