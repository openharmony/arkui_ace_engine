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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H

#include "core/components_ng/pattern/rich_editor/rich_editor_content_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
// TextPattern is the base class for text render node to perform paint text.
class RichEditorPattern : public TextPattern {
    DECLARE_ACE_TYPE(RichEditorPattern, TextPattern);

public:
    RichEditorPattern() = default;
    ~RichEditorPattern() override = default;
    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<RichEditorEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RichEditorLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RichEditorLayoutAlgorithm>(spanItemChildren_, paragraph_);
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!richEditorContentModifier_) {
            richEditorContentModifier_ = MakeRefPtr<RichEditorContentModifier>(textStyle_);
        }
        if (!richEditorOverlayModifier_) {
            richEditorOverlayModifier_ = MakeRefPtr<RichEditorOverlayModifier>();
        }
        return MakeRefPtr<RichEditorPaintMethod>(
            WeakClaim(this), paragraph_, baselineOffset_, richEditorContentModifier_, richEditorOverlayModifier_);
    }

    const RefPtr<RichEditorController>& GetRichEditorController()
    {
        return richEditorController_;
    }

    void SetRichEditorController(const RefPtr<RichEditorController>& controller)
    {
        richEditorController_ = controller;
    }

    int32_t GetTextContentLength();
    void OnModifyDone() override;
    void BeforeCreateLayoutWrapper() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    int32_t GetInstanceId() const;
    int32_t GetCaretPosition();
    void SetCaretPosition(int32_t pos);
    bool GetCaretVisible() const;
    OffsetF CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight);

private:
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleBlurEvent();
    void HandleFocusEvent();
    void HandleClickEvent(GestureEvent& info);
    void ScheduleCaretTwinkling();
    void OnCaretTwinkling();
    void StartTwinkling();
    void StopTwinkling();

    bool clickEventInitialized_ = false;
    bool focusEventInitialized_ = false;
    RefPtr<RichEditorContentModifier> richEditorContentModifier_;
    RefPtr<RichEditorOverlayModifier> richEditorOverlayModifier_;
    bool isRichEditorInit_ = false;
    RefPtr<RichEditorController> richEditorController_;
    int32_t caretPosition_ = 0;
    int32_t instanceId_ = -1;
    bool caretVisible_ = false;
    CancelableCallback<void()> caretTwinklingTask_;

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H
