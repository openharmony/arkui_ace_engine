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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace HttpAuthHandlerAccessor {
HttpAuthHandlerPeer* CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
Ark_Boolean ConfirmImpl(HttpAuthHandlerPeer* peer,
                        const Ark_String* userName,
                        const Ark_String* password)
{
    return 0;
}
void CancelImpl(HttpAuthHandlerPeer* peer)
{
}
Ark_Boolean IsHttpAuthInfoSavedImpl(HttpAuthHandlerPeer* peer)
{
    return 0;
}
} // HttpAuthHandlerAccessor
const GENERATED_ArkUIHttpAuthHandlerAccessor* GetHttpAuthHandlerAccessor()
{
    static const GENERATED_ArkUIHttpAuthHandlerAccessor HttpAuthHandlerAccessorImpl {
        HttpAuthHandlerAccessor::CtorImpl,
        HttpAuthHandlerAccessor::GetFinalizerImpl,
        HttpAuthHandlerAccessor::ConfirmImpl,
        HttpAuthHandlerAccessor::CancelImpl,
        HttpAuthHandlerAccessor::IsHttpAuthInfoSavedImpl,
    };
    return &HttpAuthHandlerAccessorImpl;
}

}
