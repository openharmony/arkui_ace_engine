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

#include "prompt_controller.h"

#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Napi {

void PromptDialogController::Close()
{
    if (node_.Invalid()) {
        return;
    }
    auto dialogNode = node_.Upgrade();
    CHECK_NULL_VOID(dialogNode);
    auto pipeline = dialogNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode);
}

} // namespace OHOS::Ace::Napi
