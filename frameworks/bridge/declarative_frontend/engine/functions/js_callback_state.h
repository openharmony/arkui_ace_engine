/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CALLBACK_STATE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CALLBACK_STATE_H

#include <utility>

#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {

template<typename FuncT>
struct JsCallbackState {
    JSExecutionContext execCtx;
    RefPtr<FuncT> func;
    WeakPtr<NG::FrameNode> node;
};

template<typename FuncT, typename Signature>
class JsCallbackWithNode;

template<typename FuncT, typename R, typename... Args>
class JsCallbackWithNode<FuncT, R(Args...)> {
public:
    using Trampoline = R (*)(const RefPtr<FuncT>&, Args...);

    JsCallbackWithNode(const JSExecutionContext& execCtx, RefPtr<FuncT> func, WeakPtr<NG::FrameNode> node,
        Trampoline trampoline, R defaultResult = R())
        : state_{execCtx, std::move(func), std::move(node)}, trampoline_(trampoline),
            defaultResult_(std::move(defaultResult))
    {}

    R operator()(Args... args) const
    {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(state_.execCtx, defaultResult_);
        NG::PipelineContext::SetCallBackNode(state_.node);
        return trampoline_(state_.func, std::forward<Args>(args)...);
    }

private:
    JsCallbackState<FuncT> state_;
    Trampoline trampoline_ = nullptr;
    R defaultResult_;
};

template<typename FuncT, typename... Args>
class JsCallbackWithNode<FuncT, void(Args...)> {
public:
    using Trampoline = void (*)(const RefPtr<FuncT>&, Args...);

    JsCallbackWithNode(const JSExecutionContext& execCtx, RefPtr<FuncT> func, WeakPtr<NG::FrameNode> node,
        Trampoline trampoline)
        : state_{execCtx, std::move(func), std::move(node)}, trampoline_(trampoline)
    {}

    void operator()(Args... args) const
    {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(state_.execCtx);
        NG::PipelineContext::SetCallBackNode(state_.node);
        trampoline_(state_.func, std::forward<Args>(args)...);
    }

private:
    JsCallbackState<FuncT> state_;
    Trampoline trampoline_ = nullptr;
};

template<typename Signature>
class JsCallbackWithoutNode;

template<typename... Args>
class JsCallbackWithoutNode<void(Args...)> {
public:
    using Trampoline = void (*)(const JSRef<JSFunc>&, Args...);

    JsCallbackWithoutNode(const JSExecutionContext& execCtx, JSRef<JSFunc> func, Trampoline trampoline)
        : execCtx_(execCtx), func_(std::move(func)), trampoline_(trampoline)
    {}

    void operator()(Args... args) const
    {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx_);
        trampoline_(func_, std::forward<Args>(args)...);
    }

private:
    JSExecutionContext execCtx_;
    JSRef<JSFunc> func_;
    Trampoline trampoline_ = nullptr;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CALLBACK_STATE_H
