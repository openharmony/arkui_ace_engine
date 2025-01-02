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

#ifndef INTERFACES_NAPI_KITS_PROMPT_ACTION_PROMPT_CONTROLLER_H
#define INTERFACES_NAPI_KITS_PROMPT_ACTION_PROMPT_CONTROLLER_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::Napi {

class PromptController {
public:
    PromptController() = default;
    virtual ~PromptController() = default;

    void SetNode(const WeakPtr<NG::FrameNode> node)
    {
        node_ = node;
    }

    virtual void Close() {};
protected:
    WeakPtr<NG::FrameNode> node_;
};

class PromptDialogController : public PromptController {
public:
    PromptDialogController() = default;
    ~PromptDialogController() override = default;

    void Close() override;
};
} // namespace OHOS::Ace::Napi
#endif // #define INTERFACES_NAPI_KITS_PROMPT_ACTION_PROMPT_CONTROLLER_H