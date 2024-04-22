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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_SELECT_OVERLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_SELECT_OVERLAY_H
#include <optional>

#include "core/components_ng/pattern/text/text_select_overlay.h"

namespace OHOS::Ace::NG {
class RichEditorSelectOverlay : public TextSelectOverlay {
    DECLARE_ACE_TYPE(RichEditorSelectOverlay, TextSelectOverlay);

public:
    explicit RichEditorSelectOverlay(const WeakPtr<TextBase>& textBase) : TextSelectOverlay(textBase) {}
    ~RichEditorSelectOverlay() = default;

    // override TextBaseSelectOverlay
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
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason) override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType) override {};
    std::optional<SelectOverlayInfo> GetSelectOverlayInfo();
    bool IsSingleHandleShow();
    void UpdateMenuOffset();
    bool IsHandlesShow();

private:
    void RemoveAreaChangeInner();
    void UpdateSelectorOnHandleMove(const OffsetF& handleOffset, bool isFirstHandle) override;
    void CheckEditorTypeChange(SelectOverlayInfo& selectInfo, TextSpanType selectType);

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorSelectOverlay);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_SELECT_OVERLAY_H
