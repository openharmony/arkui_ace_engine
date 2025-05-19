/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_richtext.h"

#include <optional>
#include <string>

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/richtext_model_impl.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/richtext_model_ng.h"

namespace OHOS::Ace {
const std::string RAWFILE_PREFIX = "resource://RAWFILE/";
const std::string BUNDLE_NAME_PREFIX = "bundleName:";
const std::string MODULE_NAME_PREFIX = "moduleName:";
std::unique_ptr<RichTextModel> RichTextModel::instance_ = nullptr;
std::mutex RichTextModel::mutex_;
RichTextModel* RichTextModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RichTextModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RichTextModelNG());
            } else {
                instance_.reset(new Framework::RichTextModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSRichText::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    std::string data;
    std::string webSrc;
    std::optional<std::string> dstSrc;
    if (ParseJsString(info[0], data)) {
        RichTextModel::GetInstance()->Create(data);
    } else if (ParseJsMedia(info[0], webSrc)) {
        ParseRawfileWebSrc(info[0], webSrc);
        int np = static_cast<int>(webSrc.find_first_of("/"));
        dstSrc = np < 0 ? webSrc : webSrc.erase(np, 1);
        RichTextModel::GetInstance()->Create(dstSrc.value());
    } else {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "richtext component failed to parse data");
    }
}

void JSRichText::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichText>::Declare("RichText");
    JSClass<JSRichText>::StaticMethod("create", &JSRichText::Create);
    JSClass<JSRichText>::StaticMethod("onStart", &JSRichText::OnStart);
    JSClass<JSRichText>::StaticMethod("onComplete", &JSRichText::OnComplete);
    JSClass<JSRichText>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRichText>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRichText>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRichText>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRichText>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRichText>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSRichText::OnStart(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onStartEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };

        RichTextModel::GetInstance()->SetOnPageStart(onStartEvent);
    }
}

void JSRichText::OnComplete(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onCompleteEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                   const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };

        RichTextModel::GetInstance()->SetOnPageFinish(onCompleteEvent);
    }
}

void JSRichText::ParseRawfileWebSrc(const JSRef<JSVal>& srcValue, std::string& webSrc)
{
    if (!srcValue->IsObject() || webSrc.substr(0, RAWFILE_PREFIX.size()) != RAWFILE_PREFIX) {
        return;
    }
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(srcValue, bundleName, moduleName);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if ((!bundleName.empty() && !moduleName.empty()) &&
        (bundleName != AceApplicationInfo::GetInstance().GetPackageName() ||
        moduleName != container->GetModuleName())) {
        webSrc = RAWFILE_PREFIX + BUNDLE_NAME_PREFIX + bundleName + "/" + MODULE_NAME_PREFIX + moduleName + "/" +
            webSrc.substr(RAWFILE_PREFIX.size());
    }
}
} // namespace OHOS::Ace::Framework
