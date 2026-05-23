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

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_content_pattern.h"

#include "core/common/container.h"
#include "core/common/stylus/stylus_detector_mgr.h"

namespace OHOS::Ace::NG {

void RichEditorPattern::OnAttachToFrameNodeMultiThread()
{
    // Intentionally empty: unsafe UI-thread operations deferred to OnAttachToMainTreeMultiThreadExtension
}

void RichEditorPattern::OnDetachFromFrameNodeMultiThread(FrameNode* node)
{
    // Intentionally empty: cleanup deferred to OnDetachFromMainTreeMultiThread
}

void RichEditorPattern::OnDetachFromMainTreeMultiThread()
{
    if (selectOverlay_) {
        CloseSelectOverlay();
    }
    TextPattern::OnDetachFromMainTreeMultiThread();
    ScrollablePattern::OnDetachFromMainTreeMultiThread();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ClearOnFocusTextField(AceType::RawPtr(host));
    auto context = pipeline_.Upgrade();
    IF_PRESENT(context, RemoveWindowSizeChangeCallback(frameId_));
    CHECK_NULL_VOID(keyboardOverlay_);
    keyboardOverlay_->CloseKeyboard(host->GetId());
}
} // namespace OHOS::Ace::NG
