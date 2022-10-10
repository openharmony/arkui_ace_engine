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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DialogView {
public:
    static RefPtr<FrameNode> CreateDialogNode(const DialogProperties& param, const RefPtr<UINode>& customNode);

    static RefPtr<FrameNode> CreateDialogWithType(DialogType type);

    static void BuildChild(const RefPtr<FrameNode>& dialogNode, const DialogProperties& prop, std::string& data,
        const RefPtr<DialogTheme>& theme, const RefPtr<UINode>& customNode);

    static RefPtr<FrameNode> BuildButtons(const std::vector<ButtonInfo>& buttons,
        const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode>& dialog);
    // build ActionSheet items
    static RefPtr<FrameNode> BuildSheet(
        const std::vector<ActionSheetInfo>& sheets, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode> dialog);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_VIEW_H
