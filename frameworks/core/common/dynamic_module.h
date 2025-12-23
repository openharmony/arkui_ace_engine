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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace panda {
template<typename T>
class Local;
class ObjectRef;
namespace ecmascript {
class EcmaVM;
}
} // namespace panda

namespace OHOS::Ace {

class DynamicModule {
public:
    DynamicModule() = default;
    virtual ~DynamicModule() = default;

    virtual void RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) = 0;
    virtual const void* GetDynamicModifier() = 0;
    virtual const void* GetStaticModifier() = 0;
    virtual const void* GetCjModifier() = 0;
    virtual void* GetModel()
    {
        return nullptr;
    }
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_H