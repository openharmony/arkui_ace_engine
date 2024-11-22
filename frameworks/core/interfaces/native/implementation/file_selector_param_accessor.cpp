/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"


namespace OHOS::Ace::NG::GeneratedModifier {
namespace FileSelectorParamAccessor {
FileSelectorParamPeer* CtorImpl()
{
    return new FileSelectorParamPeer();
}
static void DestroyPeer(FileSelectorParamPeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(&DestroyPeer);
}
void GetTitleImpl(FileSelectorParamPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetTitle();
    // title need to be returned
    LOGE("FileSelectorParamAccessor::GetTitleImpl - return value need to be supported");
}
Ark_NativePointer GetModeImpl(FileSelectorParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    peer->handler->GetMode();
    // mode need to be returned
    LOGE("FileSelectorParamAccessor::GetModeImpl - return value need to be supported");
    return 0;
}
void GetAcceptTypeImpl(FileSelectorParamPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetAcceptType();
    // accept type need to be returned
    LOGE("FileSelectorParamAccessor::GetAcceptTypeImpl - return value need to be supported");
}
Ark_Boolean IsCaptureImpl(FileSelectorParamPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->IsCapture());
}
} // FileSelectorParamAccessor
const GENERATED_ArkUIFileSelectorParamAccessor* GetFileSelectorParamAccessor()
{
    static const GENERATED_ArkUIFileSelectorParamAccessor FileSelectorParamAccessorImpl {
        FileSelectorParamAccessor::CtorImpl,
        FileSelectorParamAccessor::GetFinalizerImpl,
        FileSelectorParamAccessor::GetTitleImpl,
        FileSelectorParamAccessor::GetModeImpl,
        FileSelectorParamAccessor::GetAcceptTypeImpl,
        FileSelectorParamAccessor::IsCaptureImpl,
    };
    return &FileSelectorParamAccessorImpl;
}

}
