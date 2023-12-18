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
#include "bridge/declarative_frontend/jsview/js_base_node.h"

#include <unordered_set>

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
namespace {
const char* DIRTY_FLAG[] = { "UPDATE_PROPERTY", "UPDATE_CONTENT" };
const std::unordered_set<std::string> EXPORT_TEXTURE_SUPPORT_TYPES = { V2::JS_VIEW_ETS_TAG, V2::COMMON_VIEW_ETS_TAG };
} // namespace

void JSBaseNode::BuildNode(const JSCallbackInfo& info)
{
    if (info.Length() >= 1 && !info[0]->IsFunction()) {
        return;
    }
    auto builder = info[0];
    auto buildFunc = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(buildFunc);
    if ((info.Length() >= 2 && !(info[1]->IsObject() || info[1]->IsUndefined() || info[1]->IsNull()))) {
        return;
    }
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        NG::ViewStackProcessor::GetInstance()->SetIsBuilderNode(true);
        NG::ViewStackProcessor::GetInstance()->SetIsExportTexture(renderType_ == NodeRenderType::RENDER_TYPE_TEXTURE);
        if (info.Length() >= 2 && info[1]->IsObject()) {
            JSRef<JSVal> param = info[1];
            buildFunc->ExecuteJS(1, &param);
        } else {
            buildFunc->ExecuteJS();
        }
        viewNode_ = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    // only customNode support export texture
    if (viewNode_ && EXPORT_TEXTURE_SUPPORT_TYPES.count(viewNode_->GetTag()) > 0) {
        viewNode_->CreateExportTextureInfoIfNeeded();
        auto exportTextureInfo = viewNode_->GetExportTextureInfo();
        CHECK_NULL_VOID(exportTextureInfo);
        exportTextureInfo->SetSurfaceId(surfaceId_);
        exportTextureInfo->SetCurrentRenderType(renderType_);
    }
}

void JSBaseNode::ConstructorCallback(const JSCallbackInfo& info)
{
    std::string surfaceId;
    NodeRenderType renderType = NodeRenderType::RENDER_TYPE_DISPLAY;
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto renderOption = JSRef<JSObject>::Cast(info[0]);
        auto type = renderOption->GetProperty("type");
        if (type->IsNumber()) {
            renderType = static_cast<NodeRenderType>(type->ToNumber<uint32_t>());
        }
        auto id = renderOption->GetProperty("surfaceId");
        if (id->IsString()) {
            surfaceId = id->ToString();
        }
    }
    auto instance = AceType::MakeRefPtr<JSBaseNode>(renderType, surfaceId);
    instance->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(instance));
}

void JSBaseNode::DestructorCallback(JSBaseNode* node)
{
    if (node != nullptr) {
        node->DecRefCount();
    }
}

void JSBaseNode::MarkDirty(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        return;
    }
    auto flag = info[0]->ToNumber<uint32_t>();
    LOGI("markDirty DirtyFlag.%{public}s", DIRTY_FLAG[flag]);
}

void JSBaseNode::FinishUpdateFunc(const JSCallbackInfo& info)
{
    NG::ViewStackProcessor::GetInstance()->FlushRerenderTask();
}

void JSBaseNode::JSBind(BindingTarget globalObj)
{
    JSClass<JSBaseNode>::Declare("__JSBaseNode__");

    JSClass<JSBaseNode>::CustomMethod("build", &JSBaseNode::BuildNode);
    JSClass<JSBaseNode>::CustomMethod("markDirty", &JSBaseNode::MarkDirty);
    JSClass<JSBaseNode>::CustomMethod("finishUpdateFunc", &JSBaseNode::FinishUpdateFunc);

    JSClass<JSBaseNode>::Bind(globalObj, JSBaseNode::ConstructorCallback, JSBaseNode::DestructorCallback);
}
} // namespace OHOS::Ace::Framework
