/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace/serializeable_object.h"

#include <dlfcn.h>

namespace OHOS::Ace {
namespace {
using CreateFunction = SerializeableObject* (*)();
constexpr char NODE_OBJECT_CREATE_FUNC[] = "OHOS_ACE_CreateNodeObject";

SerializeableObject* CreateNodeObjectInner()
{
    void* handle = dlopen("libace.z.so", RTLD_LAZY);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateFunction>(dlsym(handle, NODE_OBJECT_CREATE_FUNC));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }

    auto nodeObject = entry();
    if (nodeObject == nullptr) {
        dlclose(handle);
    }

    return nodeObject;
}
} // namespace

std::unique_ptr<SerializeableObject> SerializeableObject::CreateNodeObject()
{
    std::unique_ptr<SerializeableObject> obj;
    obj.reset(CreateNodeObjectInner());
    return obj;
}
} // namespace OHOS::Ace
