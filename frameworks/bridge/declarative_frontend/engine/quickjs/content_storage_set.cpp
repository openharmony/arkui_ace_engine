/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/content_storage_set.h"

#include "base/log/log.h"

namespace OHOS::Ace::Framework {

std::map<int32_t, QJSRef<QJSValue>> ContentStorageSet::contentStorageSet_;
std::map<int32_t, QJSRef<QJSValue>> ContentStorageSet::contextSet_;
std::map<int32_t, NativeReference*> ContentStorageSet::lazyContentStorageSet_;
std::map<int32_t, NativeReference*> ContentStorageSet::lazyContextSet_;

QJSRef<QJSValue> ContentStorageSet::GetCurrentStorage()
{
    return QJSRef<QJSValue>::Make();
}

QJSRef<QJSValue> ContentStorageSet::GetCurrentContext()
{
    return QJSRef<QJSValue>::Make();
}

void ContentStorageSet::SetCurrentStorage(int32_t instanceId, NativeReference* storage) {}

void ContentStorageSet::SetCurrentContext(int32_t instanceId, NativeReference* context) {}

void ContentStorageSet::ConvertLazyNativeValueSet() {}

} // namespace OHOS::Ace::Framework