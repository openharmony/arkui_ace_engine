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

enum HandleIndex { FIRST, SECOND, CARET };

class TextFieldSelectOverlay : public BaseTextSelectOverlay {
    DECLARE_ACE_TYPE(TextFieldSelectOverlay, BaseTextSelectOverlay);

public:
    explicit TextFieldSelectOverlay(const WeakPtr<TextBase>& textBase) : BaseTextSelectOverlay(textBase) {}
    ~TextFieldSelectOverlay() = default;

    // override BaseTextSelectOverlay
    bool PreProcessOverlay(const OverlayRequest& request) override;
    bool CheckHandleVisible(const RectF& paintRect) override;
    void OnResetTextSelection() override;
    void AfterCloseOverlay() override;

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
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason) override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType) override;

    void HandleOnShowMenu();

    void SetLastSourceType(SourceType sourceType)
    {
        lastSourceType_ = sourceType;
    }

    bool IsUseTouchAtLast()
    {
        return lastSourceType_ == SourceType::TOUCH;
    }

private:
    std::optional<SelectHandleInfo> GetHandleInfo(HandleIndex handlIndex);
    void UpdatePattern();
    int32_t GetCaretPositionOnHandleMove(const OffsetF& localOffset);
    int32_t GetTextAreaCaretPosition(const OffsetF& localOffset);
    int32_t GetTextInputCaretPosition(const OffsetF& localOffset);
    void CloseMagnifier();
    SourceType lastSourceType_ = SourceType::NONE;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_SELECT_OVERLAY_H
