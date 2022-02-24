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

#include "core/common/container.h"
#include "frameworks/bridge/declarative_frontend/engine/js_converter.h"

namespace OHOS::Ace::Framework {

std::map<int32_t, JsiRef<JsiValue>> ContentStorageSet::contentStorageSet_;
std::map<int32_t, JsiRef<JsiValue>> ContentStorageSet::contextSet_;
std::map<int32_t, NativeReference*> ContentStorageSet::lazyContentStorageSet_;
std::map<int32_t, NativeReference*> ContentStorageSet::lazyContextSet_;


JsiRef<JsiValue> ContentStorageSet::GetCurrentStorage()
{
    if (lazyContentStorageSet_.size() != 0) {
        ConvertLazyNativeValueSet();
    }
    auto instanceId = Container::CurrentId();
    auto storage = contentStorageSet_.find(instanceId);
    if (storage != contentStorageSet_.end()) {
        return storage->second;
    } else {
        LOGE("failed to find current storage");
        return JsiRef<JsiValue>::Make();
    }
}

JsiRef<JsiValue> ContentStorageSet::GetCurrentContext()
{
    if (lazyContextSet_.size() != 0) {
        ConvertLazyNativeValueSet();
    }
    auto instanceId = Container::CurrentId();
    auto context = contextSet_.find(instanceId);
    if (context != contextSet_.end()) {
        return context->second;
    } else {
        LOGE("failed to find current context");
        return JsiRef<JsiValue>::Make();
    }
}

void ContentStorageSet::SetCurrentStorage(int32_t instanceId, NativeReference* storage)
{
    if (lazyContentStorageSet_.size() != 0) {
        ConvertLazyNativeValueSet();
    }

    if (JsiDeclarativeEngineInstance::GetCurrentRuntime()) {
        contentStorageSet_.insert_or_assign(instanceId, JsConverter::ConvertNativeValueToJsVal(*storage));
    } else {
        lazyContentStorageSet_.insert_or_assign(instanceId, storage);
    }
}

void ContentStorageSet::SetCurrentContext(int32_t instanceId, NativeReference* context)
{
    if (lazyContextSet_.size() != 0) {
        ConvertLazyNativeValueSet();
    }

    if (JsiDeclarativeEngineInstance::GetCurrentRuntime()) {
        contextSet_.insert_or_assign(instanceId, JsConverter::ConvertNativeValueToJsVal(*context));
    } else {
        lazyContextSet_.insert_or_assign(instanceId, context);
    }
}

void ContentStorageSet::ConvertLazyNativeValueSet()
{
    if (JsiDeclarativeEngineInstance::GetCurrentRuntime()) {
        if (lazyContentStorageSet_.size() != 0) {
            for (auto storage : lazyContentStorageSet_) {
                contentStorageSet_.insert_or_assign(storage.first,
                    JsConverter::ConvertNativeValueToJsVal(*storage.second));
            }
            lazyContentStorageSet_.clear();
        }

        if (lazyContextSet_.size() != 0) {
            for (auto context : lazyContextSet_) {
                contextSet_.insert_or_assign(context.first,
                    JsConverter::ConvertNativeValueToJsVal(*context.second));
            }
            lazyContextSet_.clear();
        }
    }
}

} // namespace OHOS::Ace::Framework