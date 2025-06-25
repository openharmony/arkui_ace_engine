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
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/core/interfaces/native/utility/callback_helper.h"

#include <string.h>

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RouterExtenderAccessor {
Ark_NativePointer PushImpl(const Ark_String* url)
{
    CHECK_NULL_RETURN(url, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = pushUrl;
    routerPageInfo.params = "";
    routerPageInfo.recoverable = true;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = AceType::DynamicCast<ArktsFrontend>(container->GetFrontend());
    CHECK_NULL_RETURN(delegate, nullptr);
    auto pageRouterManager = delegate->GetPageRouterManager();
    if (!pageRouterManager) {
        return nullptr;
    }
    auto pageNode = pageRouterManager->PushExtender(routerPageInfo);
    return pageNode.GetRawPtr();
}

Ark_NativePointer ReplaceImpl(const Ark_String* url, const Opt_Callback_Void* finishCallback)
{
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(finishCallback, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = pushUrl;
    routerPageInfo.params = "";
    routerPageInfo.recoverable = true;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = AceType::DynamicCast<ArktsFrontend>(container->GetFrontend());
    CHECK_NULL_RETURN(delegate, nullptr);
    auto pageRouterManager = delegate->GetPageRouterManager();
    if (!pageRouterManager) {
        return nullptr;
    }
    std::function<void()> callback;
    if (finishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        callback = [finish = CallbackHelper(finishCallback->value)]() {
            finish.Invoke();
        };
    }
    auto pageNode = pageRouterManager->ReplaceExtender(routerPageInfo, std::move(callback));
    return pageNode.GetRawPtr();
}

void MoveCommonUnderPageNode(Ark_NativePointer commonNode, Ark_NativePointer pageNode)
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
    common->MarkModifyDone();
    common->MarkDirtyNode();
}

void BackImpl()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = AceType::DynamicCast<ArktsFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(delegate);
    auto pageRouterManager = delegate->GetPageRouterManager();
    if (!pageRouterManager) {
        return;
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = "";
    routerPageInfo.params = "";
    pageRouterManager->BackWithTarget(routerPageInfo);
}

Ark_NativePointer RunPageImpl(const Ark_String* url)
{
    CHECK_NULL_RETURN(url, nullptr);
    std::string pushUrl = Converter::Convert<std::string>(*url);
    if (pushUrl.empty()) {
        return nullptr;
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = pushUrl;
    routerPageInfo.params = "";
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto delegate = AceType::DynamicCast<ArktsFrontend>(container->GetFrontend());
    CHECK_NULL_RETURN(delegate, nullptr);
    auto pageRouterManager = delegate->GetPageRouterManager();
    if (!pageRouterManager) {
        return nullptr;
    }
    auto pageNode = pageRouterManager->RunPageExtender(routerPageInfo);
    return pageNode.GetRawPtr();
}

void ClearImpl()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto delegate = AceType::DynamicCast<ArktsFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(delegate);
    auto pageRouterManager = delegate->GetPageRouterManager();
    if (!pageRouterManager) {
        return;
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = "";
    routerPageInfo.params = "";
    pageRouterManager->Clear();
}
}

const GENERATED_ArkUIRouterExtenderAccessor* GetRouterExtenderAccessor()
{
    static const GENERATED_ArkUIRouterExtenderAccessor RouterExtenderAccessorImpl {
        RouterExtenderAccessor::PushImpl,
        RouterExtenderAccessor::ReplaceImpl,
        RouterExtenderAccessor::MoveCommonUnderPageNode,
        RouterExtenderAccessor::BackImpl,
        RouterExtenderAccessor::RunPageImpl,
        RouterExtenderAccessor::ClearImpl
    };
    return &RouterExtenderAccessorImpl;
}
}