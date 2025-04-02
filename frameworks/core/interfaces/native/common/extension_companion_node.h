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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H

#include "core/components_ng/base/extension_handler.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedApiImpl {

class ExtensionCompanionNode : public ExtensionHandler {
    DECLARE_ACE_TYPE(ExtensionCompanionNode, ExtensionHandler);

public:
    ExtensionCompanionNode(int peerId, int flags, void* peer)
        : flags_(flags)
    {}

    ~ExtensionCompanionNode() = default;

    void SetAlignmentValue(Ark_Int32 value)
    {
        alignment_ = value;
    }
    Ark_Int32 GetAlignmentValue() const
    {
        return alignment_;
    }

    void SetFlags(Ark_UInt32 flags)
    {
        flags_ = flags;
    }

    Ark_UInt32 GetFlags() const
    {
        return flags_;
    }

    void SetVMContext(Ark_VMContext context)
    {
        context_ = context;
    }

    Ark_VMContext GetVMContext() const
    {
        return context_;
    }

private:
    Ark_UInt32 flags_ = 0;
    Ark_Int32 alignment_ = 0;
    Ark_VMContext context_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H
