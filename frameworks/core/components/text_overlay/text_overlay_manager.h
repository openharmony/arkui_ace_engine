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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_OVERLAY_TEXT_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_OVERLAY_TEXT_OVERLAY_MANAGER_H

#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing_forward.h"
#endif
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "frameworks/base/geometry/offset.h"
#include "frameworks/base/geometry/rect.h"
#include "frameworks/base/memory/ace_type.h"
#include "frameworks/core/common/ime/text_editing_value.h"
#include "frameworks/core/pipeline/base/overlay_show_option.h"

namespace OHOS::Rosen {
class Typography;
}

#ifndef USE_ROSEN_DRAWING
class SkCanvas;
#endif

namespace OHOS::Ace {

class RenderNode;
class Animator;
class StackElement;
class PipelineContext;
class TextOverlayComponent;
class TextOverlayManager;

enum class CursorPositionType {
    NONE = 0,
    END,      // end of paragraph
    BOUNDARY, // boundary of LTR and RTL
    NORMAL,
};

enum class DirectionStatus : uint8_t {
    LEFT_LEFT = 0, // System direction is LTR, text direction is LTR.
    LEFT_RIGHT,
    RIGHT_LEFT,
    RIGHT_RIGHT,
};

// Describe where caret is and how tall visually.
struct CaretMetrics {
    void Reset()
    {
        offset.Reset();
        height = 0.0;
    }

    Offset offset;
    // When caret is close to different glyphs, the height will be different.
    double height = 0.0;
    std::string ToString() const
    {
        std::string result = "Offset: ";
        result += offset.ToString();
        result += ", height: ";
        result += std::to_string(height);
        return result;
    }
};

class TextOverlayBase : public virtual AceType {
    DECLARE_ACE_TYPE(TextOverlayBase, AceType);

public:
    TextOverlayBase() = default;
    ~TextOverlayBase() override;

    void SetUpdateHandlePosition(const std::function<void(const OverlayShowOption&)>& updateHandlePosition)
    {
        updateHandlePosition_ = updateHandlePosition;
    }

    void SetUpdateHandleDiameter(const std::function<void(const double&)>& updateHandleDiameter)
    {
        updateHandleDiameter_ = updateHandleDiameter;
    }

    void SetUpdateHandleDiameterInner(const std::function<void(const double&)>& updateHandleDiameterInner)
    {
        updateHandleDiameterInner_ = updateHandleDiameterInner;
    }

    void SetOnClipRectChanged(const std::function<void(const Rect&)>& onClipRectChanged)
    {
        onClipRectChanged_ = onClipRectChanged;
    }

    static bool IsSelectiveDevice()
    {
        return (SystemProperties::GetDeviceType() != DeviceType::TV &&
                SystemProperties::GetDeviceType() != DeviceType::WATCH);
    }

    void MarkIsOverlayShowed(bool isOverlayShowed)
    {
        isOverlayShowed_ = isOverlayShowed;
    }

    bool IsOverlayShowed() const
    {
        return isOverlayShowed_;
    }

    const std::vector<Rect>& GetSelectedRect() const
    {
        return selectedRect_;
    }

    double GetSelectHeight() const
    {
        return selectHeight_;
    }

    void ChangeSelection(int32_t start, int32_t end);
    void InitAnimation(const WeakPtr<PipelineContext>& pipelineContext);
    bool GetCaretRect(int32_t extent, Rect& caretRect, double caretHeightOffset = 0.0) const;
#ifndef USE_ROSEN_DRAWING
    void PaintSelection(SkCanvas* canvas, const Offset& globalOffset);
#else
    void PaintSelection(RSCanvas* canvas, const Offset& globalOffset);
#endif
    virtual void InitSelection(const Offset& pos, const Offset& globalOffset);
    virtual void UpdateStartSelection(int32_t end, const Offset& pos, const Offset& globalOffset);
    virtual void UpdateEndSelection(int32_t start, const Offset& pos, const Offset& globalOffset);
    virtual void ShowTextOverlay(const Offset& showOffset) = 0;
    virtual void RegisterCallbacksToOverlay() = 0;
    virtual Offset GetHandleOffset(int32_t extend) = 0;
    virtual std::string GetSelectedContent() const = 0;
    RefPtr<TextOverlayManager> GetTextOverlayManager(const WeakPtr<PipelineContext>& pipelineContext);
    bool IsSelectedText(const Offset& pos, const Offset& globalOffset);

protected:
    std::shared_ptr<Rosen::Typography> paragraph_;
    CursorPositionType cursorPositionType_ = CursorPositionType::NORMAL;
    DirectionStatus directionStatus_ = DirectionStatus::LEFT_LEFT;
    Offset clickOffset_;
    // For ensuring caret is visible on screen, we take a strategy that move the whole text painting area.
    // It maybe seems rough, and doesn't support scrolling smoothly.
    Offset textOffsetForShowCaret_;
    // An outline for caret. It is used by default when the actual size cannot be retrieved.
    Rect caretProto_;
    Rect textOverlayPaintRect_;
    Color selectedColor_ = Color(0x330a59f7);
    double selectHeight_ = 0.0;
    // Default to the start of text (according to RTL/LTR).
    TextAlign textAlign_ = TextAlign::START;
    // RTL/LTR is inherit from parent.
    TextDirection defaultTextDirection_ = TextDirection::INHERIT;
    TextDirection realTextDirection_ = TextDirection::INHERIT;
    TextAffinity textAffinity_ = TextAffinity::DOWNSTREAM;
    TextEditingValue textValue_;
    std::string textForDisplay_;
    int32_t cursorPositionForShow_ = 0;
    double cursorWidth_ = 0.0;     // The unit is px.
    bool isOverlayShowed_ = false; // Whether overlay has showed.
    RefPtr<Animator> animator_;
    std::function<void(const OverlayShowOption&)> updateHandlePosition_;
    std::function<void(const double&)> updateHandleDiameter_;
    std::function<void(const double&)> updateHandleDiameterInner_;
    std::function<void(const Rect&)> onClipRectChanged_;
    RefPtr<TextOverlayComponent> textOverlay_;
    std::vector<Rect> selectedRect_;

private:
    Offset MakeEmptyOffset() const;
    double GetBoundaryOfParagraph(bool isLeftBoundary) const;
    bool ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result) const;
    bool ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result) const;
    bool ComputeOffsetForCaretCloserToClick(int32_t extent, CaretMetrics& result) const;
    DirectionStatus GetDirectionStatusOfPosition(int32_t position) const;
    int32_t GetCursorPositionForClick(const Offset& offset, const Offset& globalOffset);
    int32_t GetGraphemeClusterLength(int32_t extend, bool isPrefix) const;
};

class PipelineContext;
class TextOverlayManager : public virtual AceType {
    DECLARE_ACE_TYPE(TextOverlayManager, AceType);

public:
    explicit TextOverlayManager(const WeakPtr<PipelineContext>& context);
    ~TextOverlayManager() override;

    void SetTextOverlayBase(const WeakPtr<TextOverlayBase>& textOverlayBase)
    {
        textOverlayBase_ = textOverlayBase;
    }

    const RefPtr<TextOverlayBase> GetTextOverlayBase() const
    {
        auto textOverlayBase = textOverlayBase_.Upgrade();
        if (!textOverlayBase) {
            return nullptr;
        }
        return textOverlayBase;
    }

    const std::vector<Rect>& GetTextOverlayRect() const
    {
        return textOverlayRect_;
    }

    void AddTextOverlayRect(const Rect& textOverlayRect)
    {
        textOverlayRect_.emplace_back(textOverlayRect);
    }

    void ClearTextOverlayRect()
    {
        textOverlayRect_.clear();
    }

    // Coordinate offset is used to calculate the local location of the touch point in the event manager.
    void SetCoordinateOffset(const Offset& coordinateOffset)
    {
        coordinateOffset_ = coordinateOffset;
    }

    // Gets the coordinate offset to calculate the local location of the touch point by manually.
    const Offset& GetCoordinateOffset() const
    {
        return coordinateOffset_;
    }

    const RefPtr<RenderNode> GetTargetNode() const;
    void PopTextOverlay();
    void PushTextOverlayToStack(
        const RefPtr<TextOverlayComponent>& textOverlay, const WeakPtr<PipelineContext>& context);

    void HandleCtrlC() const;

private:
    WeakPtr<TextOverlayBase> textOverlayBase_;
    WeakPtr<StackElement> stackElement_;
    WeakPtr<PipelineContext> context_;
    std::vector<Rect> textOverlayRect_;
    Offset coordinateOffset_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_OVERLAY_TEXT_OVERLAY_MANAGER_H
