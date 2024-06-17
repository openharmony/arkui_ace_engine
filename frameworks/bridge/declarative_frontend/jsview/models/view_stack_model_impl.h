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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_STACK_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_STACK_MODEL_IMPL_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/pipeline/base/component.h"

namespace OHOS::Ace::Framework {

class ViewStackModelImpl : public ViewStackModel {
public:
    void Push(const RefPtr<AceType>& node, bool isCustomView) override
    {
        auto uiNode = AceType::DynamicCast<Component>(node);
        ViewStackProcessor::GetInstance()->Push(uiNode, isCustomView);
    }

    void Pop() override
    {
        ViewStackProcessor::GetInstance()->Pop();
    }

    void PopContainer() override
    {
        ViewStackProcessor::GetInstance()->PopContainer();
    }

    void PushKey(const std::string& key) override
    {
        ViewStackProcessor::GetInstance()->PushKey(key);
    }

    void PopKey() override
    {
        ViewStackProcessor::GetInstance()->PopKey();
    }

    void NewScope() override
    {
        scopeStack_ = std::make_unique<ScopedViewStackProcessor>();
    }

    RefPtr<AceType> Finish() override
    {
        auto node = ViewStackProcessor::GetInstance()->Finish();
        scopeStack_.reset();
        return node;
    }

    std::string ProcessViewId(const std::string& viewId) override
    {
        return ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    }

    AnimationOption GetImplicitAnimationOption() override
    {
        return ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    }

    void ClearVisualState() override
    {
        ViewStackProcessor::GetInstance()->ClearVisualState();
    }

    void SetVisualState(VisualState state) override
    {
        ViewStackProcessor::GetInstance()->SetVisualState(state);
    }

    void StartGetAccessRecordingFor(int32_t elmtId) override
    {
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    }

    int32_t GetElmtIdToAccountFor() override
    {
        return ViewStackProcessor::GetInstance()->GetElmtIdToAccountFor();
    }

    void SetElmtIdToAccountFor(int32_t elmtId) override
    {
        ViewStackProcessor::GetInstance()->SetElmtIdToAccountFor(elmtId);
    }

    void StopGetAccessRecording() override
    {
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }

    void ImplicitPopBeforeContinue() override
    {
        if ((ViewStackProcessor::GetInstance()->Size() > 1) &&
            ViewStackProcessor::GetInstance()->ShouldPopImmediately()) {
            ViewStackProcessor::GetInstance()->Pop();
        }
    }

    void GetAndPushFrameNode(const std::string& tag, int32_t elmtId) override
    {
        ViewStackProcessor::GetInstance()->GetAndPushFrameNode(tag, elmtId);
    }

    bool CheckTopNodeFirstBuilding() const override
    {
        return false;
    }

    bool IsEmptyStack() const override
    {
        // not check for old pipeline yet
        return true;
    }

private:
    std::unique_ptr<ScopedViewStackProcessor> scopeStack_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_STACK_MODEL_IMPL_H
