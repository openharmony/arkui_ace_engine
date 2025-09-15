/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "interop_ani_modifier.h"

#include "core/components_ng/base/interop/view_stack_processor_interop.h"

#include <memory>

namespace OHOS::Ace::NG {
ani_long CreateViewStackProcessor()
{
    auto pointer = Referenced::MakeRefPtr<OHOS::Ace::NG::InteropViewStackProcessor>();
    auto raw = AceType::RawPtr(pointer);
    raw->IncRefCount();
    return reinterpret_cast<ani_long>(raw);
}

ani_long PopViewStackProcessor()
{
    auto node = OHOS::Ace::NG::ViewStackProcessor::GetInstance()->Finish();
    auto pointer = AceType::RawPtr(node);
    pointer->IncRefCount();
    return reinterpret_cast<ani_long>(pointer);
}

void DeleteViewStackProcessor(ani_long pointer)
{
    reinterpret_cast<OHOS::Ace::NG::InteropViewStackProcessor*>(pointer)->DecRefCount();
}

const ArkUIAniInteropModifier* GetInteropAniModifier()
{
    static const ArkUIAniInteropModifier impl = {
        .createViewStackProcessor = OHOS::Ace::NG::CreateViewStackProcessor,
        .popViewStackProcessor = OHOS::Ace::NG::PopViewStackProcessor,
        .deleteViewStackProcessor = OHOS::Ace::NG::DeleteViewStackProcessor,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
