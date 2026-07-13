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

#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_node.h"

#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#ifdef XCOMPONENT_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_model_impl.h"
#endif
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"

namespace OHOS::Ace::Framework {
XComponentModel* GetModel()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifdef XCOMPONENT_SUPPORTED
        static Framework::XComponentModelImpl model;
        return &model;
#endif
    }
    static NG::XComponentModelNG model;
    return &model;
}

void* XComponentNode::Create(const XComponentParams& params)
{
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    if (params.controller) {
        xcomponentController = params.controller->GetController();
    }
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(GetModel()->Create(params.elmtId,
        static_cast<float>(params.width), static_cast<float>(params.height), params.xcomponentId,
        static_cast<XComponentType>(params.xcomponentType), params.libraryName, xcomponentController));
    CHECK_NULL_RETURN(frameNode, nullptr);
    ACE_UINODE_TRACE(frameNode);
    frameNode->SetIsArkTsFrameNode(true);
    auto pattern = frameNode->GetPattern<NG::XComponentPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetRenderType(static_cast<NodeRenderType>(params.renderType));
    pattern->SetExportTextureSurfaceId(params.surfaceId);

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, nullptr);
    auto* jsXComponent = new XComponentNode();
    jsXComponent->SetFrameNode(frameNode);
    taskExecutor->PostTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(frameNode))]() {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            ACE_UINODE_TRACE(frameNode);
            auto xcPattern = frameNode->GetPattern<NG::XComponentPattern>();
            CHECK_NULL_VOID(xcPattern);
            xcPattern->XComponentSizeInit();
            xcPattern->SetXcomponentInit(true);
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentCreate");

    return jsXComponent;
}

bool XComponentNode::ChangeRenderType(int32_t renderType)
{
    auto xcFrameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_RETURN(xcFrameNode, false);
    ACE_UINODE_TRACE(xcFrameNode);
    auto pattern = xcFrameNode->GetPattern<NG::XComponentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->ChangeRenderType(static_cast<NodeRenderType>(renderType));
}

void XComponentNode::RegisterOnCreate(NG::ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& funcArg)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_VOID(frameNode);
    ACE_UINODE_TRACE(frameNode);
    if (!funcArg->IsFunction(vm)) {
        return;
    }

    panda::Local<panda::FunctionRef> func = funcArg->ToObject(vm);
    auto onLoad = [func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(AceType::RawPtr(frameNode))](
                      const std::string& xcomponentId) {
        auto vm = func.GetEcmaVM();
        CHECK_NULL_VOID(NG::ArkTSUtils::CheckJavaScriptScope(vm));
        ACE_UINODE_TRACE(node);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("XComponentNode.onCreate");
        PipelineContext::SetCallBackNode(node);
#ifdef XCOMPONENT_SUPPORTED
        std::vector<Local<JSValueRef>> argv;
        Local<JSValueRef> jsVal;
        if (Framework::XComponentClient::GetInstance().GetJSVal(const_cast<EcmaVM*>(vm), xcomponentId, jsVal)) {
            argv.emplace_back(jsVal);
        }
#endif
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        NG::ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetModel()->RegisterOnCreate(frameNode, std::move(onLoad));
}

void XComponentNode::RegisterOnDestroy(NG::ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& funcArg)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_VOID(frameNode);
    ACE_UINODE_TRACE(frameNode);

    if (!funcArg->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> func = funcArg->ToObject(vm);
    auto onDestroy = [func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(AceType::RawPtr(frameNode))](
                         const std::string& xcomponentId) {
        auto vm = func.GetEcmaVM();
        CHECK_NULL_VOID(NG::ArkTSUtils::CheckJavaScriptScope(vm));
        ACE_UINODE_TRACE(node);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("XComponentNode.onDestroy");
        PipelineContext::SetCallBackNode(node);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        NG::ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetModel()->RegisterOnDestroy(frameNode, std::move(onDestroy));
}
} // namespace OHOS::Ace::Framework