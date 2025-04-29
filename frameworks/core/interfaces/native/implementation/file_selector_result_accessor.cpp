/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/file_selector_result_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FileSelectorResultAccessor {
void DestroyPeerImpl(Ark_FileSelectorResult peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_FileSelectorResult CtorImpl()
{
    return new FileSelectorResultPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void HandleFileListImpl(Ark_FileSelectorResult peer,
                        const Array_String* fileList)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(fileList);
    auto vector = Converter::Convert<std::vector<std::string>>(*fileList);
    peer->handler->HandleFileList(vector);
}
} // FileSelectorResultAccessor
const GENERATED_ArkUIFileSelectorResultAccessor* GetFileSelectorResultAccessor()
{
    static const GENERATED_ArkUIFileSelectorResultAccessor FileSelectorResultAccessorImpl {
        FileSelectorResultAccessor::DestroyPeerImpl,
        FileSelectorResultAccessor::CtorImpl,
        FileSelectorResultAccessor::GetFinalizerImpl,
        FileSelectorResultAccessor::HandleFileListImpl,
    };
    return &FileSelectorResultAccessorImpl;
}

struct FileSelectorResultPeer {
    virtual ~FileSelectorResultPeer() = default;
};
}
