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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_EXECUTION_SCOPE_DEFINES_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_EXECUTION_SCOPE_DEFINES_H

#ifdef USE_ARK_ENGINE
#define JAVASCRIPT_EXECUTION_SCOPE(exec) \
    panda::LocalScope socpe(exec.vm_);
#define JAVASCRIPT_EXECUTION_SCOPE_STATIC                                                                \
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime()); \
    panda::LocalScope socpe(runtime->GetEcmaVm());
#define CHECK_JAVASCRIPT_SCOPE_AND_RETURN                             \
    if (JsiDeclarativeEngineInstance::GetCurrentRuntime() == nullptr) \
        return;
#define CHECK_JAVASCRIPT_SCOPE(exec, ...)                                               \
    if (JsiDeclarativeEngineInstance::GetCurrentRuntime() == nullptr || exec.vm_ == nullptr) \
        return __VA_ARGS__;
#define JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(exec, ...) \
    CHECK_JAVASCRIPT_SCOPE(exec, __VA_ARGS__)            \
    JAVASCRIPT_EXECUTION_SCOPE(exec)
#else
#define JAVASCRIPT_EXECUTION_SCOPE(exec)
#define JAVASCRIPT_EXECUTION_SCOPE_STATIC
#define CHECK_JAVASCRIPT_SCOPE_AND_RETURN
#define JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(exec, ...)
#endif

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JS_EXECUTION_SCOPE_DEFINES_H
