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
#include "arkoala_api_generated.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/promise_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include <cstring>

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RouterExtenderAccessor {
Ark_NativePointer PushImpl(Ark_NativePointer jsView,
                           const Ark_String* url,
                           const Opt_Boolean* recover,
                           const Opt_RouterFinishCallback* finishCallback)
{
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    CHECK_NULL_RETURN(jsView, nullptr);
    CHECK_NULL_RETURN(finishCallback, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    bool recoverValue = true;
    if (recover->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        recoverValue = Converter::Convert<bool>(recover->value);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = container->GetFrontend();
    CHECK_NULL_RETURN(delegate, nullptr);
    std::function<void()> callback;
    if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        callback = [finish = CallbackHelper(finishCallback->value), jsNode = jsView]() {
            finish.Invoke(jsNode);
        };
    }
    auto pageNode = delegate->PushExtender(pushUrl, "", recoverValue, std::move(callback), jsView);
    return pageNode;
}

Ark_NativePointer CreateDynamicImpl(const Ark_String* url,
                                    const Opt_Boolean* recover)
{
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    bool recoverValue = true;
    if (recover->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        recoverValue = Converter::Convert<bool>(recover->value);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = container->GetFrontend();
    CHECK_NULL_RETURN(delegate, nullptr);
    auto pageNode = delegate->CreateDynamicExtender(pushUrl, recoverValue);
    return pageNode;
}

Ark_NativePointer PushDynamicImpl(Ark_NativePointer pageNode,
                                  const Ark_String* url,
                                  const Opt_Boolean* recover,
                                  const Opt_RouterFinishCallback* finishCallback)
{
    CHECK_NULL_RETURN(pageNode, nullptr);
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    CHECK_NULL_RETURN(finishCallback, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    bool recoverValue = true;
    if (recover->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        recoverValue = Converter::Convert<bool>(recover->value);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = container->GetFrontend();
    CHECK_NULL_RETURN(delegate, nullptr);
    std::function<void()> callback;
    if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        callback = [finish = CallbackHelper(finishCallback->value), pageNode]() {
            finish.Invoke(pageNode);
        };
    }
    auto node = delegate->PushDynamicExtender(pushUrl, "", recoverValue, std::move(callback), pageNode);
    return node;
}

Ark_NativePointer ReplaceDynamicImpl(Ark_NativePointer pageNode,
                                     const Ark_String* url,
                                     const Opt_Boolean* recover,
                                     const Opt_RouterFinishCallback* finishCallback)
{
    CHECK_NULL_RETURN(pageNode, nullptr);
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    CHECK_NULL_RETURN(finishCallback, nullptr);
    std::string replaceUrl = Converter::Convert<std::string>(*url);
    if (replaceUrl.empty()) {
        return nullptr;
    }
    bool recoverValue = true;
    if (recover->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        recoverValue = Converter::Convert<bool>(recover->value);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = container->GetFrontend();
    CHECK_NULL_RETURN(delegate, nullptr);
    std::function<void()> callback;
    if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        callback = [finish = CallbackHelper(finishCallback->value), pageNode]() {
            finish.Invoke(pageNode);
        };
    }
    auto node = delegate->ReplaceDynamicExtender(replaceUrl, "", recoverValue, std::move(callback), pageNode);
    return node;
}

Ark_NativePointer ReplaceImpl(Ark_NativePointer jsView,
                              const Ark_String* url,
                              const Opt_Boolean* recover,
                              const Opt_RouterFinishCallback* enterFinishCallback)
{
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    CHECK_NULL_RETURN(jsView, nullptr);
    CHECK_NULL_RETURN(enterFinishCallback, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    bool recoverValue = true;
    if (recover->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        recoverValue = Converter::Convert<bool>(recover->value);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = container->GetFrontend();
    CHECK_NULL_RETURN(delegate, nullptr);
    std::function<void()> callback;
    if (enterFinishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        callback = [finish = CallbackHelper(enterFinishCallback->value), jsNode = jsView]() {
            finish.Invoke(jsNode);
        };
    }
    auto pageNode = delegate->ReplaceExtender(pushUrl, "", recoverValue, std::move(callback), jsView);
    return pageNode;
}

void MoveCommonUnderPageNodeImpl(Ark_NativePointer commonNode,
                                 Ark_NativePointer pageNode)
{
    auto common = reinterpret_cast<FrameNode*>(commonNode);
    CHECK_NULL_VOID(common);
    auto stageNode = common->GetParent();
    CHECK_NULL_VOID(stageNode);
    if (stageNode->GetTag() != V2::STAGE_ETS_TAG) {
        return;
    }
    stageNode->RemoveChildSilently(AceType::Claim(common));

    auto page = reinterpret_cast<FrameNode*>(pageNode);
    CHECK_NULL_VOID(page);
    auto pageFrameNode = AceType::Claim(page);
    common->MountToParent(pageFrameNode);

    pageFrameNode->MarkModifyDone();
    pageFrameNode->MarkDirtyNode();
    common->MarkDirtyNode();
}

void BackImpl()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = container->GetFrontend();
    CHECK_NULL_VOID(delegate);
    delegate->BackExtender("", "");
}

void BackWithOptionsImpl(const Ark_String* url,
                         const Opt_Object* params)
{
    CHECK_NULL_VOID(url);
    CHECK_NULL_VOID(params);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    std::string param;
    if (params->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = container->GetFrontend();
    CHECK_NULL_VOID(delegate);
    delegate->BackExtender(pushUrl, param);
}

Ark_NativePointer RunPageImpl(Ark_NativePointer jsView,
                              const Ark_String* url,
                              const Opt_Boolean* recover,
                              const Opt_RouterFinishCallback* finishCallback)
{
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    CHECK_NULL_RETURN(jsView, nullptr);
    CHECK_NULL_RETURN(finishCallback, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    bool recoverValue = true;
    if (recover->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        recoverValue = Converter::Convert<bool>(recover->value);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = container->GetFrontend();
    CHECK_NULL_RETURN(delegate, nullptr);
    std::function<void()> callback;
    if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        callback = [finish = CallbackHelper(finishCallback->value), jsNode = jsView]() {
            finish.Invoke(jsNode);
        };
    }
    auto pageNode = delegate->RunPageExtender(pushUrl, "", recoverValue, std::move(callback), jsView);
    return pageNode;
}

void ClearImpl()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = container->GetFrontend();
    CHECK_NULL_VOID(delegate);
    delegate->ClearExtender();
}

void ShowAlertBeforeBackPageImpl(const Ark_String* url)
{
    CHECK_NULL_VOID(url);
    std::string message = Converter::Convert<std::string>(*url);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = container->GetFrontend();
    CHECK_NULL_VOID(delegate);
    delegate->ShowAlertBeforeBackPageExtender(message);
}

void HideAlertBeforeBackPageImpl()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = container->GetFrontend();
    CHECK_NULL_VOID(delegate);
    delegate->HideAlertBeforeBackPageExtender();
}

void PushNamedRoute0Impl(Ark_VMContext vmContext,
                         Ark_AsyncWorkerPtr asyncWorker,
                         Ark_NativePointer jsView,
                         const Ark_PageRouterOptions* options,
                         const Opt_RouterFinishCallback* finishCallback,
                         const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(vmContext);
    CHECK_NULL_VOID(asyncWorker);
    CHECK_NULL_VOID(jsView);
    CHECK_NULL_VOID(options);
    CHECK_NULL_VOID(finishCallback);
    CHECK_NULL_VOID(outputArgumentForReturningPromise);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](const std::string& errStr, int32_t errCode) {
        if (errCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({std::to_string(errCode), errStr});
        }
    };
    PageRouterOptions routerOptions;
    routerOptions.errorCallback = finishFunc;
    routerOptions.url = Converter::Convert<std::string>(options->options.url);
    routerOptions.isNamedRouterMode = true;
    if (options->options.recoverable.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        routerOptions.recoverable = Converter::Convert<bool>(options->options.recoverable.value);
    }
    if (options->mode.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        routerOptions.routerMode = static_cast<uint32_t>(options->mode.value);
    }
    auto execFunc = [routerOptions, finishCallback, jsView]() {
        std::function<void()> callback;
        if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
            callback = [finish = CallbackHelper(finishCallback->value), jsNode = jsView]() {
                finish.InvokeSync(jsNode);
            };
        }
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto delegate = container->GetFrontend();
        CHECK_NULL_VOID(delegate);
        delegate->PushNamedRouteExtender(routerOptions, std::move(callback), jsView);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
}
void PushNamedRoute1Impl(Ark_NativePointer jsView,
                         const Ark_PageRouterOptions* options,
                         const Opt_RouterFinishCallback* finishCallback,
                         const Opt_AsyncCallback_Void* callback_)
{
}
void ReplaceNamedRoute0Impl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_NativePointer jsView,
                            const Ark_PageRouterOptions* options,
                            const Opt_RouterFinishCallback* finishCallback,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(vmContext);
    CHECK_NULL_VOID(asyncWorker);
    CHECK_NULL_VOID(jsView);
    CHECK_NULL_VOID(options);
    CHECK_NULL_VOID(finishCallback);
    CHECK_NULL_VOID(outputArgumentForReturningPromise);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](const std::string& errStr, int32_t errCode) {
        if (errCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({std::to_string(errCode), errStr});
        }
    };
    PageRouterOptions routerOptions;
    routerOptions.errorCallback = finishFunc;
    routerOptions.url = Converter::Convert<std::string>(options->options.url);
    routerOptions.isNamedRouterMode = true;
    if (options->options.recoverable.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        routerOptions.recoverable = Converter::Convert<bool>(options->options.recoverable.value);
    }
    if (options->mode.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        routerOptions.routerMode = static_cast<uint32_t>(options->mode.value);
    }
    auto execFunc = [routerOptions, finishCallback, jsView]() {
        std::function<void()> callback;
        if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
            callback = [finish = CallbackHelper(finishCallback->value), jsNode = jsView]() {
                finish.InvokeSync(jsNode);
            };
        }
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto delegate = container->GetFrontend();
        CHECK_NULL_VOID(delegate);
        delegate->ReplaceNamedRouteExtender(routerOptions, std::move(callback), jsView);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
}
void ReplaceNamedRoute1Impl(Ark_NativePointer jsView,
                            const Ark_PageRouterOptions* options,
                            const Opt_RouterFinishCallback* finishCallback,
                            const Opt_AsyncCallback_Void* callback_)
{
}
}

const GENERATED_ArkUIRouterExtenderAccessor* GetRouterExtenderAccessor()
{
    static const GENERATED_ArkUIRouterExtenderAccessor RouterExtenderAccessorImpl {
        RouterExtenderAccessor::PushImpl,
        RouterExtenderAccessor::ReplaceImpl,
        RouterExtenderAccessor::MoveCommonUnderPageNodeImpl,
        RouterExtenderAccessor::BackImpl,
        RouterExtenderAccessor::BackWithOptionsImpl,
        RouterExtenderAccessor::RunPageImpl,
        RouterExtenderAccessor::ClearImpl,
        RouterExtenderAccessor::ShowAlertBeforeBackPageImpl,
        RouterExtenderAccessor::HideAlertBeforeBackPageImpl,
        RouterExtenderAccessor::PushNamedRoute0Impl,
        RouterExtenderAccessor::PushNamedRoute1Impl,
        RouterExtenderAccessor::ReplaceNamedRoute0Impl,
        RouterExtenderAccessor::ReplaceNamedRoute1Impl,
        RouterExtenderAccessor::CreateDynamicImpl,
        RouterExtenderAccessor::PushDynamicImpl,
        RouterExtenderAccessor::ReplaceDynamicImpl,
    };
    return &RouterExtenderAccessorImpl;
}
} // RouterExtenderAccessor