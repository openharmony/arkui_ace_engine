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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RENDER_WEB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RENDER_WEB_H

#include "core/components/common/layout/constants.h"
#include "core/components/option/option_component.h"
#include "core/components/select_popup/select_popup_component.h"
#include "core/components/text/text_component.h"
#include "core/components/text_overlay/text_overlay_component.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_component.h"
#include "core/gestures/pan_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

#include <chrono>
#include<queue>

namespace OHOS::Ace {
namespace {

struct MouseClickInfo {
    double x = -1;
    double y = -1;
    TimeStamp start;
};

#ifdef OHOS_STANDARD_SYSTEM
struct TouchInfo {
    double x = -1;
    double y = -1;
    int32_t id = -1;
};

struct TouchHandleState {
    int32_t id = -1;
    int32_t x = -1;
    int32_t y = -1;
    int32_t edge_height = 0;
};

enum WebOverlayType {
    INSERT_OVERLAY,
    SELECTION_OVERLAY,
    INVALID_OVERLAY
};
#endif
}

class RenderWeb : public RenderNode, public DragDropEvent {
    DECLARE_ACE_TYPE(RenderWeb, RenderNode, DragDropEvent);

public:
    static RefPtr<RenderNode> Create();

    RenderWeb();
    ~RenderWeb() override = default;

    enum class VkState {
        VK_NONE,
        VK_SHOW,
        VK_HIDE
    };

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnAttachContext() override;
    void OnMouseEvent(const MouseEvent& event);
    bool HandleMouseEvent(const MouseEvent& event) override;
    void SendDoubleClickEvent(const MouseClickInfo& info);
    bool HandleDoubleClickEvent(const MouseEvent& event);
    bool HandleKeyEvent(const KeyEvent& keyEvent);

#ifdef OHOS_STANDARD_SYSTEM
    void OnAppShow() override;
    void OnAppHide() override;
    void OnGlobalPositionChanged() override;
    void OnPositionChanged() override;
    void OnSizeChanged() override;
    void HandleTouchDown(const TouchEventInfo& info, bool fromOverlay);
    void HandleTouchUp(const TouchEventInfo& info, bool fromOverlay);
    void HandleTouchMove(const TouchEventInfo& info, bool fromOverlay);
    void HandleTouchCancel(const TouchEventInfo& info);

    // Related to text overlay
    void SetUpdateHandlePosition(
        const std::function<void(const OverlayShowOption&, float, float)>& updateHandlePosition);
    bool RunQuickMenu(
        std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
        std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback);
    void OnQuickMenuDismissed();
    void OnTouchSelectionChanged(
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle);
    bool TextOverlayMenuShouldShow() const;
    bool GetShowStartTouchHandle() const;
    bool GetShowEndTouchHandle() const;
    bool OnCursorChange(const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info);
    void OnSelectPopupMenu(
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback);
#endif

    void SetDelegate(const RefPtr<WebDelegate>& delegate)
    {
        delegate_ = delegate;
    }

    RefPtr<WebDelegate> GetDelegate() const
    {
        return delegate_;
    }

    bool IsAxisScrollable(AxisDirection direction) override;
    WeakPtr<RenderNode> CheckAxisNode() override;

    void SetWebIsFocus(bool isFocus)
    {
        isFocus_ = isFocus;
    }

    bool GetWebIsFocus() const
    {
        return isFocus_;
    }

    void SetNeedOnFocus(bool needOnFocus)
    {
        needOnFocus_ = needOnFocus;
    }

    bool GetNeedOnFocus() const
    {
        return needOnFocus_;
    }
    void PanOnActionStart(const GestureEvent& info) override;
    void PanOnActionUpdate(const GestureEvent& info) override;
    void PanOnActionEnd(const GestureEvent& info) override;
    void PanOnActionCancel(const GestureEvent& info) override;
    DragItemInfo GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info) override;
    void InitEnhanceSurfaceFlag();

protected:
    RefPtr<WebDelegate> delegate_;
    RefPtr<WebComponent> web_;
    Size drawSize_;
    Size drawSizeCache_;
    bool isUrlLoaded_ = false;
    Size preDrawSize_;
    Offset position_;
    Offset prePosition_;
    bool isEnhanceSurface_ = false;
    bool isCreateWebView_ = false;

private:
#ifdef OHOS_STANDARD_SYSTEM
    void Initialize();
    void InitPanEvent();
    void HandleDragMove(const GestureEvent& event);
    bool ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos, const TouchType& touchType);
    void OnTouchTestHit(const Offset& coordinateOffset, const TouchRestrict& touchRestrict,
        TouchTestResult& result) override;
    bool IsTouchHandleValid(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle);
    bool IsTouchHandleShow(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> handle);
    WebOverlayType GetTouchHandleOverlayType(
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle);
    RefPtr<TextOverlayComponent> CreateTextOverlay(
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle);
    void PushTextOverlayToStack();
    void PopTextOverlay();
    Offset NormalizeTouchHandleOffset(float x, float y);
    void RegisterTextOverlayCallback(
        int32_t flags, std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback);
    void OnDragWindowStartEvent(RefPtr<PipelineContext> pipelineContext, const GestureEvent& info,
        const DragItemInfo& dragItemInfo);
    void OnDragWindowMoveEvent(RefPtr<PipelineContext> pipelineContext, const GestureEvent& info);
    void OnDragWindowDropEvent(RefPtr<PipelineContext> pipelineContext, const GestureEvent& info);
    void UpdateGlobalPos();
    RefPtr<OptionComponent> BuildSelectMenu(const std::string& value);

    RefPtr<RawRecognizer> touchRecognizer_ = nullptr;
    RefPtr<PanRecognizer> panRecognizer_ = nullptr;
    OnMouseCallback onMouse_;
    OnKeyEventCallback onKeyEvent_;
    std::function<bool(KeyEventInfo& keyEventInfo)> onPreKeyEvent_;
    RefPtr<TextOverlayComponent> textOverlay_;
    WeakPtr<StackElement> stackElement_;
    std::function<void(const OverlayShowOption&, float, float)> updateHandlePosition_ = nullptr;

    bool showTextOveralyMenu_ = false;
    bool showStartTouchHandle_ = false;
    bool showEndTouchHandle_ = false;
    bool isDragging_ = false;
    bool isW3cDragEvent_ = false;

    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle_ = nullptr;
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle_ = nullptr;
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle_ = nullptr;
#endif
    void RegistVirtualKeyBoardListener();
    bool ProcessVirtualKeyBoard(int32_t width, int32_t height, double keyboard);
    void SetRootView(int32_t width, int32_t height, int32_t offset);
    void UpdateDelegate();
    bool needUpdateWeb_ = true;
    bool isFocus_ = false;
    bool needOnFocus_ = false;
    double offsetFix_ = 0.0;
    VkState isVirtualKeyBoardShow_ { VkState::VK_NONE };
    std::queue<MouseClickInfo> doubleClickQueue_;
    RefPtr<SelectPopupComponent> popup_ = nullptr;
    RefPtr<ThemeManager> themeManager_ = nullptr;
    RefPtr<AccessibilityManager> accessibilityManager_ = nullptr;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RENDER_WEB_H
