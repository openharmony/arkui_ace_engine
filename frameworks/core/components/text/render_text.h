/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_RENDER_TEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_RENDER_TEXT_H

#include "base/geometry/dimension.h"
#include "core/common/clipboard/clipboard.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_component.h"
#include "core/components/text_overlay/text_overlay_manager.h"
#include "core/components/text_span/render_text_span.h"
#include "core/components/text_span/text_span_component.h"
#include "core/gestures/click_recognizer.h"
#include "core/gestures/gesture_type.h"
#include "core/gestures/long_press_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class TextComponent;

class RenderText : public RenderNode, public TextOverlayBase, public DragDropEvent {
    DECLARE_ACE_TYPE(RenderText, RenderNode, TextOverlayBase, DragDropEvent);

public:
    ~RenderText() override;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void OnStatusChanged(RenderStatus renderStatus) override;

    void OnPaintFinish() override;

    Size GetContentSize() override;

    bool TouchTest(const Point& globalPoint, const Point& parentLocalPoint, const TouchRestrict& touchRestrict,
        TouchTestResult& result) override;

    std::string GetTextData() const;
    void SetTextData(const std::string& textData);

    void SetTextStyle(const TextStyle& textStyle)
    {
        textStyle_ = textStyle;
    }
    const TextStyle& GetTextStyle()
    {
        return textStyle_;
    }

    void MarkNeedMeasure()
    {
        needMeasure_ = true;
    }

    virtual double GetTextWidth() = 0;

    RefPtr<Component> GetComponent() override;

    void Dump() override;

    void SetParagraphWidth(double paragraphWidth)
    {
        paragraphWidth_ = paragraphWidth;
    }

    double GetParagraphWidth() const
    {
        return paragraphWidth_;
    }

    void SetParagraphHeight(double paragraphHeight)
    {
        paragraphHeight_ = paragraphHeight;
    }

    double GetParagraphHeight() const
    {
        return paragraphHeight_;
    }

    void OnLongPress(const LongPressInfo& longPressInfo);
    void ShowTextOverlay(const Offset& showOffset) override;
    void ShowTextOverlay(const Offset& showOffset, bool isUsingMouse);
    bool HandleMouseEvent(const MouseEvent& event) override;
    void RegisterCallbacksToOverlay() override;
    const TextSelection GetTextSelect() const
    {
        return textValue_.selection;
    }

    std::string GetSelectedContent() const override;
    const TextEditingValue GetTextValue() const
    {
        return textValue_;
    }

    const Offset& GetStartOffset() const
    {
        return startOffset_;
    }

    void SetStartOffset(const Offset& startOffset)
    {
        startOffset_ = startOffset;
    }

    const Offset& GetEndOffset() const
    {
        return endOffset_;
    }

    void SetEndOffset(const Offset& endOffset)
    {
        endOffset_ = endOffset;
    }

protected:
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    virtual Size Measure() = 0;
    virtual uint32_t GetTextLines() = 0;
    virtual int32_t GetTouchPosition(const Offset& offset) = 0;
    void UpdateAccessibilityText();

    template<class T>
    void UpdateIfChanged(T& update, const T& val)
    {
        if (update != val) {
            needMeasure_ = true;
            update = val;
        }
    }

    void CheckIfNeedMeasure();
    void ClearRenderObject() override;
    TextStyle textStyle_;
    Color focusColor_;
    Color lostFocusColor_;
    double fontScale_ = 1.0;
    double dipScale_ = 1.0;
    bool isFocus_ = false;
    bool needMeasure_ = true;
    bool isCallbackCalled_ = false;
    uint32_t maxLines_ = UINT32_MAX;
    RefPtr<TextComponent> text_;
    std::map<int32_t, std::map<GestureType, EventMarker>> touchRegions_; // key of map is end position of span.
    double paragraphWidth_ = 0.0;
    double paragraphHeight_ = 0.0;
    std::optional<TextAlign> alignment_;
    bool isCustomFont_ = false;

private:
    bool IsDeclarativePara();
    void HandleTouchEvent(GestureType type, const Offset& touchPosition);
    void HandleClick(const ClickInfo& info);
    void HandleRemoteMessage(const ClickInfo& info);
    void HandleLongPress(const Offset& longPressPosition);
    EventMarker GetEventMarker(int32_t position, GestureType type);
    void FireEvent(const EventMarker& marker);
    void UpdateOverlay();
    Offset GetPositionForExtend(int32_t extend);
    void HandleOnCopy();
    void HandleOnCopyAll(const std::function<void(const Offset&, const Offset&)>& callback);
    void HandleOnStartHandleMove(int32_t end, const Offset& startHandleOffset,
        const std::function<void(const Offset&)>& startCallback, bool isSingleHandle = false);
    void HandleOnEndHandleMove(
        int32_t start, const Offset& endHandleOffset, const std::function<void(const Offset&)>& endCallback);
    void HideTextOverlay();
    void UpdateTextOverlay();
    // Drag event
    void PanOnActionStart(const GestureEvent& info) override;
    void PanOnActionUpdate(const GestureEvent& info) override;
    void PanOnActionEnd(const GestureEvent& info) override;
    void PanOnActionCancel(const GestureEvent& info) override;
    DragItemInfo GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info) override;
    void CreateSelectRecognizer();

    bool needClickDetector_ = false;
    bool needLongPressDetector_ = false;
    bool needTouchDetector_ = false;
    int32_t touchStartPosition_ = 0;
    RefPtr<RawRecognizer> rawRecognizer_;
    RefPtr<ClickRecognizer> clickDetector_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<LongPressRecognizer> textOverlayRecognizer_;
    RefPtr<ClickRecognizer> hideTextOverlayRecognizer_;
    RefPtr<PanRecognizer> selectRecognizer_;
    RefPtr<Clipboard> clipboard_;
    CopyOptions copyOption_ = CopyOptions::None;
    Offset startOffset_;
    Offset endOffset_;
    Offset lastDragMoveOffset_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_RENDER_TEXT_H
