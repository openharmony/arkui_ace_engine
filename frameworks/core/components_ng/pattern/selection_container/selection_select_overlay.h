/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_SELECTION_SELECT_OVERLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_SELECTION_SELECT_OVERLAY_H

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"

namespace OHOS::Ace::NG {
class SelectionContainerChild;
class SelectionContainerPattern;

class SelectionSelectOverlay : public BaseTextSelectOverlay {
    DECLARE_ACE_TYPE(SelectionSelectOverlay, BaseTextSelectOverlay);

public:
    SelectionSelectOverlay(const WeakPtr<TextBase>& textBase, const WeakPtr<SelectionContainerPattern>& pattern)
        : BaseTextSelectOverlay(textBase), pattern_(pattern)
    {
    }
    ~SelectionSelectOverlay() override = default;

    bool CheckHandleVisible(const RectF& paintRect) override;
    RefPtr<FrameNode> GetOwner() override;
    bool CheckTouchInHostNode(const PointF& touchPoint) override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside = true) override;
    bool PreProcessOverlay(const OverlayRequest& request) override;
    std::optional<SelectHandleInfo> GetFirstHandleInfo() override;
    std::optional<SelectHandleInfo> GetSecondHandleInfo() override;
    std::optional<RectF> GetAncestorNodeViewPort() override;
    void OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag) override;
    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode) override;
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info = nullptr) override;
    std::string GetSelectedText() override;
    void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type) override;
    void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type, const std::string& labelInfo) override;
    void OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag) override;
    void OnHandleMoveStart(const GestureEvent& event, bool isFirst) override;
    void OnHandleMove(const RectF& rect, bool isFirst) override;
    void OnHandleMoveDone(const RectF& rect, bool isFirst) override;
    void OnResetTextSelection() override;
    std::optional<Color> GetHandleColor() override;
    std::optional<CopyOptions> ResolveCopyOptionForSelectedText() const;
    void UpdateAISelectMenu();

protected:
    RectF GetSelectAreaFromRects(SelectRectsType pos) override;
    void CalcHandleLevelMode(const RectF& firstLocalPaintRect, const RectF& secondLocalPaintRect) override;
    bool AllowTranslate() override;
    bool AllowSearch() override;
    bool AllowShare() override;

private:
    class FlushHandleNodeGuard final {
    public:
        explicit FlushHandleNodeGuard(const RefPtr<SelectionSelectOverlay>& overlay);
        ~FlushHandleNodeGuard();

    private:
        RefPtr<SelectionSelectOverlay> overlay_;
    };

    bool IsShowTranslate() const;
    bool IsShowSearch() const;
    bool HasValidSelectedText() const;
    void OnHandleLevelModeChanged(HandleLevelMode mode) override;
    void UpdateTransformFlag() override;
    bool IsClipHandleWithViewPort() override;
    bool CheckAndAdjustHandle(const RefPtr<SelectionContainerChild>& child, RectF& paintRect);
    bool CheckAndAdjustHandleWithContent(const RectF& visibleContentRect, RectF& paintRect);
    RectF GetSelectAreaFromHandleFallback();
    void HandleOnAskCelia();
    bool IsAskCeliaSupported() const;
    OffsetF GetHotPaintOffset();
    void FlushHandleNodeIfNeeded();

    WeakPtr<SelectionContainerPattern> pattern_;
    OffsetF hostPaintOffset_;
    bool isDraggingFirstHandle_ = true;
    bool isFlushingHandleNode_ = false;
    bool needUpdateViewPortOnMoveDone_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(SelectionSelectOverlay);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_SELECTION_SELECT_OVERLAY_H
