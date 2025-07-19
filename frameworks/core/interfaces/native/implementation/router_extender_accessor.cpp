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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include <cstring>

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RouterExtenderAccessor {
namespace {
void RegisterPageCallback(const RefPtr<FrameNode>& frameNode, const RefPtr<UINode>& jsViewNode)
{
    auto curPageNode = AceType::DynamicCast<PageNode>(frameNode);
    CHECK_NULL_VOID(curPageNode);
    auto pagePattern = curPageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto customNode = AceType::DynamicCast<CustomNode>(jsViewNode);
    CHECK_NULL_VOID(customNode);
    pagePattern->SetOnPageShow([weak = WeakPtr<CustomNode>(customNode)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnPageShow();
        }
    });
    pagePattern->SetOnPageHide([weak = WeakPtr<CustomNode>(customNode)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnPageHide();
        }
    });
    pagePattern->SetOnBackPressed([weak = WeakPtr<CustomNode>(customNode)]() {
        auto view = weak.Upgrade();
        if (view) {
            return view->FireOnBackPressed();
        }
        return false;
    });

    pagePattern->SetPageTransitionFunc(
        [weak = WeakPtr<CustomNode>(customNode), pageId = curPageNode->GetId(),
            weakPage = WeakPtr<FrameNode>(curPageNode)]() {
            auto custom = weak.Upgrade();
            auto page = weakPage.Upgrade();
            if (custom && page) {
                auto pattern = page->GetPattern<PagePattern>();
                CHECK_NULL_VOID(pattern);
                NG::ScopedViewStackProcessor scopedViewStackProcessor;
                NG::ViewStackProcessor::GetInstance()->SetPageNode(page);
                // clear pageTransition effects and execute js to get latest pageTransition effects.
                pattern->ClearPageTransitionEffect();
                custom->FirePageTransition();
                NG::ViewStackProcessor::GetInstance()->SetPageNode(nullptr);
            }
        });

    pagePattern->MarkRenderDone();
}
}
Ark_NativePointer PushImpl(const Ark_String* url, const Opt_Boolean* recover, Ark_NativePointer jsView,
    const Opt_Callback_Void* finishCallback)
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
        callback = [finish = CallbackHelper(finishCallback->value)]() {
            finish.Invoke();
        };
    }
    auto pageNode = delegate->PushExtender(pushUrl, "", recoverValue, std::move(callback));
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto jsViewNode = reinterpret_cast<UINode*>(jsView);
    CHECK_NULL_RETURN(jsViewNode, nullptr);
    auto frameNode = AceType::Claim(reinterpret_cast<FrameNode*>(pageNode));
    jsViewNode->MountToParent(frameNode);
    frameNode->MarkDirtyNode();

    RegisterPageCallback(frameNode, AceType::Claim(jsViewNode));
    return pageNode;
}

Ark_NativePointer ReplaceImpl(const Ark_String* url, const Opt_Boolean* recover, Ark_NativePointer jsView,
    const Opt_Callback_Void* enterFinishCallback, const Opt_Callback_Void* exitFinishCallback)
{
    CHECK_NULL_RETURN(url, nullptr);
    CHECK_NULL_RETURN(recover, nullptr);
    CHECK_NULL_RETURN(jsView, nullptr);
    CHECK_NULL_RETURN(enterFinishCallback, nullptr);
    CHECK_NULL_RETURN(exitFinishCallback, nullptr);
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
        callback = [finish = CallbackHelper(enterFinishCallback->value)]() {
            finish.Invoke();
        };
    }
    std::function<void()> replace;
    if (exitFinishCallback->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        replace = [replaceBack = CallbackHelper(exitFinishCallback->value)]() {
            replaceBack.Invoke();
        };
    }
    auto pageNode = delegate->ReplaceExtender(pushUrl, "", recoverValue, std::move(callback), std::move(replace));
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto jsViewNode = reinterpret_cast<UINode*>(jsView);
    CHECK_NULL_RETURN(jsViewNode, nullptr);
    auto frameNode = AceType::Claim(reinterpret_cast<FrameNode*>(pageNode));
    jsViewNode->MountToParent(frameNode);
    frameNode->MarkDirtyNode();

    RegisterPageCallback(frameNode, AceType::Claim(jsViewNode));
    return pageNode;
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

Ark_NativePointer RunPageImpl(const Ark_String* url, const Opt_Boolean* recover, Ark_NativePointer jsView,
    const Opt_Callback_Void* finishCallback)
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
        callback = [finish = CallbackHelper(finishCallback->value)]() {
            finish.Invoke();
        };
    }
    auto pageNode = delegate->RunPageExtender(pushUrl, "", recoverValue, std::move(callback));
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto jsViewNode = reinterpret_cast<UINode*>(jsView);
    CHECK_NULL_RETURN(jsViewNode, nullptr);
    auto frameNode = AceType::Claim(reinterpret_cast<FrameNode*>(pageNode));
    jsViewNode->MountToParent(frameNode);
    jsViewNode->MarkDirtyNode();

    RegisterPageCallback(frameNode, AceType::Claim(jsViewNode));
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