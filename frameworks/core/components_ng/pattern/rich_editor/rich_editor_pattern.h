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

#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_configuration.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_proxy.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_content_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

namespace OHOS::MiscServices {
class OnTextChangedListener;
} // namespace OHOS::MiscServices
#endif
#endif

namespace OHOS::Ace::NG {
// TextPattern is the base class for text render node to perform paint text.
enum class MoveDirection { FORWARD, BACKWARD };

class RichEditorPattern : public TextPattern, public TextInputClient {
    DECLARE_ACE_TYPE(RichEditorPattern, TextPattern, TextInputClient);

public:
    RichEditorPattern();
    ~RichEditorPattern() override;
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

    void OnVisibleChange(bool isVisible) override;
    void OnModifyDone() override;
    void BeforeCreateLayoutWrapper() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) override;
    void PerformAction(TextInputAction action, bool forceCloseKeyboard = true) override;
    int32_t GetInstanceId() const;
    void InsertValue(const std::string& insertValue);
    void CreateTextSpanNode(
        RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info, const std::string& insertValue);
    void DeleteBackward(int32_t length);
    void DeleteForward(int32_t length);
    void SetInputMethodStatus(bool keyboardShown);
    bool CursorMoveLeft();
    bool CursorMoveRight();
    bool CursorMoveUp();
    bool CursorMoveDown();
    bool SetCaretPosition(int32_t pos);
    int32_t GetCaretPosition();
    int32_t GetTextContentLength();
    bool GetCaretVisible() const;
    OffsetF CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight);
    void CopyTextSpanStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target);
    int32_t TextSpanSplit(int32_t position);
    SpanPositionInfo GetSpanPositionInfo(int32_t position);
    std::function<ImageSourceInfo()> CreateImageSourceInfo(const ImageSpanOptions& options);
    void DeleteSpans(const RangeOptions& options);
    void DeleteSpanByRange(int32_t start, int32_t end, SpanPositionInfo info);
    void DeleteSpansByRange(int32_t start, int32_t end, SpanPositionInfo startInfo, SpanPositionInfo endInfo);
    void ClearContent(const RefPtr<UINode>& child);
    bool SetCaretOffset(int32_t caretPosition);
    void UpdateSpanStyle(int32_t start, int32_t end, TextStyle textStyle, ImageSpanAttribute imageStyle);
    void SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle);
    int32_t AddImageSpan(const ImageSpanOptions& options);
    int32_t AddTextSpan(const TextSpanOptions& options);
    RichEditorSelection GetSpansInfo(int32_t start, int32_t end, GetSpansMethod method);
    void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle) override;
    std::u16string GetLeftTextOfCursor(int32_t number);
    std::u16string GetRightTextOfCursor(int32_t number);
    int32_t GetTextIndexAtCursor();
    void ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle) override;
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle) override;
    void OnAreaChangedInner() override;
    void CreateHandles() override;
#ifdef ENABLE_DRAG_FRAMEWORK
    std::function<void(Offset)> GetThumbnailCallback() override;
#endif

private:
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleBlurEvent();
    void HandleFocusEvent();
    void HandleClickEvent(GestureEvent& info);
    void InitMouseEvent();
    void ScheduleCaretTwinkling();
    void OnCaretTwinkling();
    void StartTwinkling();
    void StopTwinkling();
    void UpdateTextStyle(RefPtr<SpanNode>& spanNode, TextStyle textStyle);
    void UpdateImageStyle(RefPtr<FrameNode>& imageNode, ImageSpanAttribute imageStyle);
    void InitTouchEvent();
    bool SelectOverlayIsOn();
    void HandleLongPress(GestureEvent& info);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleTouchEvent(const TouchEventInfo& info);
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
#ifdef ENABLE_DRAG_FRAMEWORK
    void InitDragDropEvent();
    void UpdateSpanItemDragStatus(const std::list<ResultObject>& resultObjects, bool IsDragging);
    NG::DragDropInfo OnDragStart(const RefPtr<OHOS::Ace::DragEvent>& event);
    void OnDragEnd();
    void OnDragMove(const RefPtr<OHOS::Ace::DragEvent>& event);

    void AddDragFrameNodeToManager(const RefPtr<FrameNode>& frameNode)
    {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto dragDropManager = context->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->AddDragFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    }
#endif // ENABLE_DRAG_FRAMEWORK

    RefPtr<UINode> GetChildByIndex(int32_t index) const;
    std::string GetSelectedSpanText(std::wstring value, int32_t start, int32_t end) const;
    TextStyleResult GetTextStyleObject(RefPtr<SpanNode> node);
    ResultObject GetTextResultObject(RefPtr<SpanItem> item, int32_t index, int32_t start, int32_t end);
    ResultObject GetImageResultObject(RefPtr<SpanItem> item, int32_t index, int32_t start, int32_t end);
    void OnHover(bool isHover);
    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard);
#if defined(ENABLE_STANDARD_INPUT)
    bool EnableStandardInput(bool needShowSoftKeyboard);
#else
    bool UnableStandardInput(bool isFocusViewChanged);
#endif
    bool HasConnection() const;
    bool CloseKeyboard(bool forceClose) override;
    void CalcInsertValueObj(TextInsertValueInfo& info);
    void CalcDeleteValueObj(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info);
    int32_t DeleteValueSetImageSpan(const RefPtr<SpanItem> spanItem, RichEditorAbstractSpanResult& spanResult);
    int32_t DeleteValueSetTextSpan(const RefPtr<SpanItem> spanItem, int32_t currentPosition, int32_t length,
        RichEditorAbstractSpanResult& spanResult);
    void DeleteByDeleteValueInfo(const RichEditorDeleteValue& info);
    bool OnKeyEvent(const KeyEvent& keyEvent);
    void MoveCaretAfterTextChange();
    bool BeforeIMEInsertValue(const std::string& insertValue);
    void AfterIMEInsertValue(const RefPtr<SpanNode>& spanNode, int32_t moveLength);
    void InsertValueToBeforeSpan(RefPtr<SpanNode>& spanNodeBefore, const std::string& insertValue);
#if defined(ENABLE_STANDARD_INPUT)
    sptr<OHOS::MiscServices::OnTextChangedListener> richEditTextChangeListener_;
#else
    RefPtr<TextInputConnection> connection_ = nullptr;
#endif
    bool isMousePressed_ = false;
    bool isFirstmouseSelect_ = false;
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    bool imeAttached_ = false;
    bool imeShown_ = false;
#endif
    int32_t moveLength_ = 0;
    int32_t instanceId_ = -1;
    int32_t caretPosition_ = 0;
    bool isTextChange_ = false;
    bool caretVisible_ = false;
    bool isRichEditorInit_ = false;
    bool clickEventInitialized_ = false;
    bool focusEventInitialized_ = false;
    OffsetF parentGlobalOffset_;
    RefPtr<TouchEventImpl> touchListener_;
    struct UpdateSpanStyle updateSpanStyle_;
    CancelableCallback<void()> caretTwinklingTask_;
    RefPtr<RichEditorController> richEditorController_;
    RefPtr<RichEditorContentModifier> richEditorContentModifier_;
    RefPtr<RichEditorOverlayModifier> richEditorOverlayModifier_;
    MoveDirection moveDirection_ = MoveDirection::FORWARD;
#ifdef ENABLE_DRAG_FRAMEWORK
    std::list<ResultObject> dragResultObjects_;
#endif // ENABLE_DRAG_FRAMEWORK
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_PATTERN_H
