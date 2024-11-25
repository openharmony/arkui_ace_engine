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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AbstractPropertyAccessor {
AbstractPropertyPeer* CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void GetImpl(AbstractPropertyPeer* peer)
{
}
void SetImpl(AbstractPropertyPeer* peer,
             const Ark_CustomObject* newValue)
{
}
void InfoImpl(AbstractPropertyPeer* peer)
{
}
} // AbstractPropertyAccessor
const GENERATED_ArkUIAbstractPropertyAccessor* GetAbstractPropertyAccessor()
{
    static const GENERATED_ArkUIAbstractPropertyAccessor AbstractPropertyAccessorImpl {
        AbstractPropertyAccessor::CtorImpl,
        AbstractPropertyAccessor::GetFinalizerImpl,
        AbstractPropertyAccessor::GetImpl,
        AbstractPropertyAccessor::SetImpl,
        AbstractPropertyAccessor::InfoImpl,
    };
    return &AbstractPropertyAccessorImpl;
}

}
