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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_HYPERLINK_BRIDGE_HYPERLINK_DYNAMIC_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_HYPERLINK_BRIDGE_HYPERLINK_DYNAMIC_MODULE_H

#include "core/common/dynamic_module.h"

namespace OHOS::Ace {

class HyperlinkDynamicModule : public DynamicModule {
public:
    HyperlinkDynamicModule() = default;
    ~HyperlinkDynamicModule() = default;

    void RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) override;
    const void* GetDynamicModifier() override;
    const void* GetStaticModifier() override;
    const void* GetCjModifier() override;
    void* GetModel() override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_HYPERLINK_BRIDGE_HYPERLINK_DYNAMIC_MODULE_H