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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_SELECT_OVERLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_SELECT_OVERLAY_H
#include <optional>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/event/ace_events.h"
namespace OHOS::Ace::NG {

class TextFieldSelectOverlay : public BaseTextSelectOverlay {
    DECLARE_ACE_TYPE(TextFieldSelectOverlay, BaseTextSelectOverlay);

public:
    explicit TextFieldSelectOverlay(const WeakPtr<TextBase>& textBase) : BaseTextSelectOverlay(textBase) {}
    ~TextFieldSelectOverlay() = default;

    // override BaseTextSelectOverlay
    bool PreProcessOverlay(const OverlayRequest& request) override;
    bool CheckHandleVisible(const RectF& paintRect) override;

    std::vector<std::string> GetPasteMimeTypes() override
    {
        return pasteMimeTypes_;
    }

    void OnResetTextSelection() override;
    void AfterCloseOverlay() override;
    RectF GetHandleLocalPaintRect(DragHandleIndex dragHandleIndex) override;
    void OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag) override;
    void UpdateAllHandlesOffset() override;
    void UpdateFirstHandleOffset() override;
    void UpdateSecondHandleOffset() override;

    // override SelectOverlayHolder
    std::optional<SelectHandleInfo> GetFirstHandleInfo() override;
    std::optional<SelectHandleInfo> GetSecondHandleInfo() override;
    void OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag) override;
    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode) override;
    RectF GetSelectArea() override;
    std::string GetSelectedText() override;

    // override SelectOverlayCallback
    void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type) override;
    void OnHandleMove(const RectF& rect, bool isFirst) override;
    void OnHandleMoveDone(const RectF& rect, bool isFirst) override;
    void OnAfterSelectOverlayShow(bool isCreate) override;
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info = nullptr) override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside = true) override;
    void OnHandleIsHidden() override;
    void OnHandleMoveStart(const GestureEvent& event, bool isFirst) override;

    void HandleOnShowMenu();

    void ProcessSelectAllOverlay(const OverlayRequest& request);

    void SetLastSourceType(SourceType sourceType)
    {
        lastSourceType_ = sourceType;
    }

    bool IsUseTouchAtLast()
    {
        return lastSourceType_ == SourceType::TOUCH;
    }

    void OnHandleLevelModeChanged(HandleLevelMode mode) override;
    void OnOverlayClick(const GestureEvent& event, bool isFirst) override;
    bool IsRegisterTouchCallback() override
    {
        return true;
    }

    int32_t GetCaretPositionOnHandleMove(const OffsetF& localOffset, bool isFirst);
    bool IsClipHandleWithViewPort() override
    {
        return !HasRenderTransform();
    }
    std::optional<Color> GetHandleColor() override;

protected:
    bool AllowSearch() override;

private:
    std::optional<SelectHandleInfo> GetHandleInfo(const RectF& handlePaintRect);
    void UpdatePattern(const OverlayRequest& request);
    int32_t GetTextAreaCaretPosition(const OffsetF& localOffset);
    int32_t GetTextInputCaretPosition(const OffsetF& localOffset, bool isFirst);
    void CloseMagnifier();
    void TriggerContentToScroll(const OffsetF& localOffset, bool isEnd);
    SourceType lastSourceType_ = SourceType::NONE;
    std::vector<std::string> pasteMimeTypes_ = { "text/plain", "text/html" };
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_SELECT_OVERLAY_H
