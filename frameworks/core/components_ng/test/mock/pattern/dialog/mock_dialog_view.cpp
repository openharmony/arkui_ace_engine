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

#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> DialogView::CreateDialogNode(
    const DialogProperties& param, const RefPtr<UINode>& customNode = nullptr)
{
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode("",
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, customNode));
    if (customNode) {
        customNode->MountToParent(dialog);
    }
    return dialog;
}
} // namespace OHOS::Ace::NG
