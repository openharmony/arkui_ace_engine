/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_SELECT_OVERLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_SELECT_OVERLAY_H
#include <optional>

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_callback.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_holder.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/event/ace_events.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
struct OverlayRequest {
    bool menuIsShow = true;
    bool hideHandle = false;
    bool animation = false;
    bool hideHandleLine = false;
    int32_t requestCode = 0;
};

enum class DragHandleIndex { NONE, FIRST, SECOND };

class BaseTextSelectOverlay : public SelectOverlayHolder, public SelectOverlayCallback {
    DECLARE_ACE_TYPE(BaseTextSelectOverlay, SelectOverlayHolder, SelectOverlayCallback);

public:
    explicit BaseTextSelectOverlay(const WeakPtr<TextBase>& textBase) : hostTextBase_(textBase) {}
    ~BaseTextSelectOverlay() = default;

    static RectF GetVisibleRect(const RefPtr<FrameNode>& node, const RectF& visibleRect);

    template<class T>
    RefPtr<T> GetPattern() const
    {
        return DynamicCast<T>(hostTextBase_.Upgrade());
    }

    WeakPtr<TextBase> GetHostTextBase()
    {
        return hostTextBase_;
    }

    void ProcessOverlay(const OverlayRequest& request = OverlayRequest());
    void ProcessOverlayOnAreaChanged(const OverlayRequest& request = OverlayRequest());
    virtual bool PreProcessOverlay(const OverlayRequest& request)
    {
        return true;
    }
    virtual void AfterCloseOverlay() {}

    // override SelectOverlayHolder
    RefPtr<FrameNode> GetOwner() override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside = true) override;
    bool CheckTouchInHostNode(const PointF& touchPoint) override;
    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode) override;
    bool CheckRestartHiddenHandleTask(int32_t requestCode) override;
    std::optional<RectF> GetAncestorNodeViewPort() override;
    RefPtr<SelectOverlayCallback> GetCallback() override
    {
        return AceType::Claim(this);
    }
    // override SelectOverlayHolder end

    // common method
    bool SelectOverlayIsOn();
    bool SelectOverlayIsCreating();
    void CloseOverlay(bool animation, CloseReason reason);
    void ToggleMenu();
    void ShowMenu();
    void HideMenu(bool noAnimation = false);
    void DisableMenu();
    void EnableMenu();
    virtual void UpdateAllHandlesOffset();
    virtual void UpdateFirstHandleOffset();
    virtual void UpdateSecondHandleOffset();
    void UpdateViewPort();
    bool IsShowMouseMenu();
    bool IsCurrentMenuVisibile();
    bool IsHandleReverse();
    void RemoveSelectionHoldCallback();
    void SetSelectionHoldCallback();

    bool IsSingleHandle()
    {
        return isSingleHandle_;
    }

    bool IsUsingMouse()
    {
        return isUsingMouse_;
    }

    void SetIsSingleHandle(bool isSingleHandle)
    {
        isSingleHandle_ = isSingleHandle;
    }

    void SetUsingMouse(bool isUsingMouse)
    {
        isUsingMouse_ = isUsingMouse;
    }

    void SetShowPaste(bool isShowPaste)
    {
        isShowPaste_ = isShowPaste;
    }

    bool IsShowPaste()
    {
        return isShowPaste_;
    }

    void SetMenuIsShow(bool isShowMenu)
    {
        isShowMenu_ = isShowMenu;
        originalMenuIsShow_ = isShowMenu;
    }

    bool IsShowMenu()
    {
        return isShowMenu_;
    }

    void SetIsShowHandleLine(bool isShowHandleLine)
    {
        isShowHandleLine_ = isShowHandleLine;
    }

    void SetMouseMenuOffset(const OffsetF& offset)
    {
        mouseMenuOffset_ = offset;
    }

    // common virtual methods.
    virtual RectF GetVisibleContentRect(bool isGlobal = false);
    virtual bool CheckHandleVisible(const RectF& paintRect) = 0;

    virtual std::vector<std::string> GetPasteMimeTypes()
    {
        return std::vector<std::string>();
    }

    virtual void OnResetTextSelection() {}

    virtual bool IsAcceptResetSelectionEvent(SourceType sourceType, TouchType touchType);

    bool HasRenderTransform()
    {
        UpdateTransformFlag();
        return hasTransform_;
    }
    // transformed global point to original local point.
    void RevertLocalPointWithTransform(OffsetF& point);
    // original local point to transformed global point.
    void GetGlobalPointsWithTransform(std::vector<OffsetF>& points);
    // original local rect to transformd global rect.
    void GetGlobalRectWithTransform(RectF& rect);
    std::vector<OffsetF> GetGlobalRectVertexWithTransform(const RectF& rect, float extendValue = 0.0f);
    // original local point to transformed local point.
    void GetLocalPointsWithTransform(std::vector<OffsetF>& localPoints);
    void GetLocalPointWithTransform(OffsetF& localPoint);
    // original local rect to transformed local rect.
    void GetLocalRectWithTransform(RectF& localRect);

    OffsetF GetPaintOffsetWithoutTransform();
    RectF GetPaintRectWithTransform();
    OffsetF GetPaintRectOffsetWithTransform();
    RectF GetVisibleContentRectWithTransform(float epsilon);
    bool CheckHandleIsVisibleWithTransform(const OffsetF& startPoint, const OffsetF& endPoint, float epsilon);
    bool IsPointInRect(const OffsetF& point, const OffsetF& leftBottom, const OffsetF& rightBottom,
        const OffsetF& rightTop, const OffsetF& leftTop);

    void OnSelectionMenuOptionsUpdate(
        const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick);

    void OnCreateMenuCallbackUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback)
    {
        onCreateMenuCallback_ = onCreateMenuCallback;
    }

    void OnMenuItemClickCallbackUpdate(const NG::OnMenuItemClickCallback&& onMenuItemClick)
    {
        onMenuItemClick_ = onMenuItemClick;
    }

    float GetHandleDiameter();
    VectorF GetHostScale();
    void SwitchToOverlayMode();
    void SwitchToEmbedMode();
    void SetHandleLevelMode(HandleLevelMode mode);
    bool IsOverlayMode()
    {
        return handleLevelMode_ == HandleLevelMode::OVERLAY;
    }

    void OnHandleLevelModeChanged(HandleLevelMode mode) override
    {
        SetHandleLevelMode(mode);
        UpdateAllHandlesOffset();
        UpdateViewPort();
    }
    virtual void OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag);
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info) override;
    void OnHandleMoveStart(const GestureEvent& event, bool isFirst) override
    {
        isHandleDragging_ = true;
        dragHandleIndex_ = isFirst ? DragHandleIndex::FIRST : DragHandleIndex::SECOND;
    }
    void OnHandleMoveDone(const RectF& rect, bool isFirst) override
    {
        isHandleDragging_ = false;
        dragHandleIndex_ = DragHandleIndex::NONE;
    }
    bool GetIsHandleDragging()
    {
        return isHandleDragging_;
    }
    bool IsTouchAtHandle(const TouchEventInfo& info);
    bool IsClickAtHandle(const GestureEvent& info);
    bool HasUnsupportedTransform(bool checkScale = false);
    bool CheckUnsupportedTransformMatrix(const RefPtr<RenderContext> context, bool checkScale);
    bool CheckSwitchToMode(HandleLevelMode mode) override;

    void OnUpdateOnCreateMenuCallback(SelectOverlayInfo& selectInfo)
    {
        selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback_;
        selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick_;
        auto textRange = [weak = GetHostTextBase()](int32_t& start, int32_t& end) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->GetSelectIndex(start, end);
        };
        selectInfo.onCreateCallback.textRangeCallback = textRange;
    }
    bool GetClipHandleViewPort(RectF& rect);
    bool CalculateClippedRect(RectF& rect);
    void MarkOverlayDirty();
    void OnHandleMarkInfoChange(const std::shared_ptr<SelectOverlayInfo> info, SelectOverlayDirtyFlag flag) override;
    void UpdateHandleColor();
    virtual std::optional<Color> GetHandleColor()
    {
        return std::nullopt;
    }
    void AddAvoidKeyboardCallback(bool isCustomKeyboard);
    void RemoveAvoidKeyboardCallback();

    bool IsEnableContainerModal() override
    {
        return enableContainerModal_;
    }
    bool IsHiddenHandle();

    bool IsHandleVisible(bool isFirst);
    void SetMenuTranslateIsSupport(bool menuTranslateIsSupport)
    {
        menuTranslateIsSupport_ = menuTranslateIsSupport;
    }
    void SetIsSupportMenuSearch(bool isSupportMenuSearch)
    {
        isSupportMenuSearch_ = isSupportMenuSearch;
    }

protected:
    RectF MergeSelectedBoxes(
        const std::vector<RectF>& boxes, const RectF& contentRect, const RectF& textRect, const OffsetF& paintOffset);
    bool IsMouseClickDown(SourceType sourceType, TouchType touchType)
    {
        return sourceType == SourceType::MOUSE && touchType == TouchType::DOWN;
    }

    bool IsTouchUp(SourceType sourceType, TouchType touchType)
    {
        return (sourceType == SourceType::TOUCH || sourceType == SourceType::TOUCH_PAD) && touchType == TouchType::UP;
    }

    RectF ConvertPaintInfoToRect(const SelectHandlePaintInfo& paintInfo);
    void SetTransformPaintInfo(SelectHandleInfo& handleInfo, const RectF& localHandleRect);
    bool CheckHandleCanPaintInHost(const RectF& firstRect, const RectF& secondRect);
    virtual RectF GetHandleLocalPaintRect(DragHandleIndex dragHandleIndex);
    virtual void CalcHandleLevelMode(const RectF& firstLocalPaintRect, const RectF& secondLocalPaintRect);
    bool IsAncestorNodeStartAnimation(FrameNodeChangeInfoFlag flag);
    bool IsAncestorNodeGeometryChange(FrameNodeChangeInfoFlag flag);
    bool IsAncestorNodeStartScroll(FrameNodeChangeInfoFlag flag);
    bool IsAncestorNodeEndScroll(FrameNodeChangeInfoFlag flag);
    bool IsAncestorNodeTransformChange(FrameNodeChangeInfoFlag flag);
    bool IsAncestorNodeHasTransition(FrameNodeChangeInfoFlag flag);
    void SetEnableHandleLevel(bool enableHandleLevel)
    {
        enableHandleLevel_ = enableHandleLevel;
    }
    void RegisterScrollingListener(const RefPtr<FrameNode> scrollableNode);
    void OnHandleScrolling(const WeakPtr<FrameNode>& scrollingNode);
    virtual void UpdateTransformFlag();
    bool CheckHasTransformAttr();
    void UpdateOriginalMenuIsShow()
    {
        originalMenuIsShow_ = IsCurrentMenuVisibile();
    }
    virtual void UpdateMenuWhileAncestorNodeChanged(
        bool shouldHideMenu, bool shouldShowMenu, FrameNodeChangeInfoFlag extraFlag);
    virtual void UpdateClipHandleViewPort(RectF& rect) {};
    static bool GetFrameNodeContentRect(const RefPtr<FrameNode>& node, RectF& rect);
    static bool GetScrollableClipContentRect(const RefPtr<FrameNode>& node, RectF& rect);
    static std::pair<ContentClipMode, std::optional<ContentClip>> GetScrollableClipInfo(const RefPtr<FrameNode>& node);
    virtual bool IsClipHandleWithViewPort()
    {
        return false;
    }
    void ApplySelectAreaWithKeyboard(RectF& selectArea);
    bool IsHandleInParentSafeAreaPadding();
    bool IsHandleInParentSafeAreaPadding(const RectF& firstRect, const RectF& secondRect);
    bool CheckHandleIsInSafeAreaPadding(const RefPtr<FrameNode>& node, const RectF& handle);
    void CheckEnableContainerModal()
    {
        enableContainerModal_ = true;
    }
    bool IsNeedMenuTranslate();
    void HandleOnTranslate();
    bool IsNeedMenuSearch();
    void HandleOnSearch();
    virtual bool AllowTranslate()
    {
        return false;
    }
    virtual bool AllowSearch()
    {
        return false;
    }
    bool IsSupportMenuShare();
    bool IsNeedMenuShare();
    void HandleOnShare();
    virtual bool AllowShare()
    {
        return false;
    }
    std::optional<OverlayRequest> latestReqeust_;
    bool hasTransform_ = false;
    HandleLevelMode handleLevelMode_ = HandleLevelMode::OVERLAY;
    OnCreateMenuCallback onCreateMenuCallback_;
    OnMenuItemClickCallback onMenuItemClick_;
    bool isHandleMoving_ = false;
    DragHandleIndex dragHandleIndex_ = DragHandleIndex::NONE;
    RectF ConvertWindowToScreenDomain(RectF rect);
    EdgeF ConvertWindowToScreenDomain(EdgeF edge);
    std::string GetTranslateParamRectStr(RectF rect, EdgeF rectLeftTop, EdgeF rectRightBottom);

private:
    void FindScrollableParentAndSetCallback(const RefPtr<FrameNode>& host);
    void RegisterParentScrollCallback(const RefPtr<FrameNode>& host, int32_t parentId);
    void ShowSelectOverlay(const OverlayRequest& request, bool hasClipboardData);
    void GetHandlePoints(const RectF& handleRect, std::vector<PointF>& points, bool handleOnTop);
    bool IsPointsInRegion(const std::vector<PointF>& points, const RectF& regionRect);
    bool CheckAndUpdateHostGlobalPaintRect();
    bool CheckHasTransformMatrix(const RefPtr<RenderContext>& context);
    bool isHandleDragging_ = false;
    bool isSingleHandle_ = false;
    bool isShowPaste_ = false;
    bool isShowMenu_ = true;
    bool isShowHandleLine_ = true;
    bool isUsingMouse_ = false;
    OffsetF mouseMenuOffset_;
    WeakPtr<TextBase> hostTextBase_;
    bool enableHandleLevel_ = false;
    bool touchAtHandle_ = false;
    bool isChangeToOverlayModeAtEdge_ = true;
    bool hasRegisterListener_ = false;
    RectF globalPaintRect_;
    bool originalMenuIsShow_ = true;
    bool enableContainerModal_ = false;
    bool menuTranslateIsSupport_ = false;
    bool isSupportMenuSearch_ = false;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_SELECT_OVERLAY_H
