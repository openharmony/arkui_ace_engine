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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H

#include <stdint.h>
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/dialog//dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/dialog/dialog_render_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class DialogPattern : public Pattern {
    DECLARE_ACE_TYPE(DialogPattern, Pattern);

public:
    DialogPattern(const RefPtr<DialogTheme>& dialogTheme, const RefPtr<UINode>& customNode)
        : dialogTheme_(dialogTheme), customNode_(customNode)
    {}
    ~DialogPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return AceType::MakeRefPtr<DialogLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<DialogRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<DialogEventHub>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    void BuildChild(const DialogProperties& dialogProperties);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

private:
    void OnModifyDone() override;
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchUp(const Offset& clickPosition);
    void PopDialog(int32_t buttonIdx);

    // set render context properties of content frame
    void UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode, const RefPtr<DialogTheme>& theme);

    RefPtr<FrameNode> BuildTitle(std::string& data, const DialogProperties& dialogProperties);
    RefPtr<FrameNode> BuildContent(std::string& data, const DialogProperties& dialogProperties);

    RefPtr<FrameNode> BuildButtons(const std::vector<ButtonInfo>& buttons);
    RefPtr<UINode> CreateButton(const ButtonInfo& params, int32_t index);
    // to close dialog when button is clicked
    void BindCloseCallBack(const RefPtr<GestureEventHub>& hub, int32_t buttonIdx);
    // build ActionSheet items
    RefPtr<FrameNode> BuildSheet(const std::vector<ActionSheetInfo>& sheets);
    RefPtr<FrameNode> BuildSheetItem(const ActionSheetInfo& item);
    // build actionMenu
    RefPtr<FrameNode> BuildMenu(const std::vector<ButtonInfo>& buttons);

    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<UINode> customNode_;

    // XTS inspector values
    std::string message_;
    std::string title_;

    ACE_DISALLOW_COPY_AND_MOVE(DialogPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H