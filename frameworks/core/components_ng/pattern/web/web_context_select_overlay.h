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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_CONTEXT_SELECT_OVERLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_CONTEXT_SELECT_OVERLAY_H

#include <optional>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"
#include "core/components_ng/pattern/text/text_base.h"

namespace OHOS::Ace::NG {

class WebContextSelectOverlay : public BaseTextSelectOverlay {
    DECLARE_ACE_TYPE(WebContextSelectOverlay, BaseTextSelectOverlay);

public:
    explicit WebContextSelectOverlay(const WeakPtr<TextBase>& textBase) : BaseTextSelectOverlay(textBase) {}
    ~WebContextSelectOverlay() = default;

    // override BaseTextSelectOverlay
    bool PreProcessOverlay(const OverlayRequest& request) override;
    bool CheckHandleVisible(const RectF& paintRect) override;
    void OnResetTextSelection() override {}
    void AfterCloseOverlay() override {}
    // override BaseTextSelectOverlay end

    // override SelectOverlayHolder
    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& selectInfo, int32_t requestCode) override;
    std::optional<SelectHandleInfo> GetFirstHandleInfo() override;
    std::optional<SelectHandleInfo> GetSecondHandleInfo() override;
    void OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag) override;
    RectF GetSelectArea() override;
    std::string GetSelectedText() override;
    // override SelectOverlayHolder end

    // override SelectOverlayCallback
    void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type) override;
    void OnHandleMove(const RectF& rect, bool isFirst) override {}
    void OnHandleMoveDone(const RectF& rect, bool isFirst) override;
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info = nullptr) override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside = true) override;
    // override SelectOverlayCallback end

private:
    bool hasText_ = false;
    bool hasImage_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(WebContextSelectOverlay);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_CONTEXT_SELECT_OVERLAY_H
