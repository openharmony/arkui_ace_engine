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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_MODEL_NG_H

#include <memory>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ViewStackModelNG : public ViewStackModel {
public:
    void Push(const RefPtr<AceType>& node, bool isCustomView) override
    {
        auto uiNode = AceType::DynamicCast<UINode>(node);
        ViewStackProcessor::GetInstance()->Push(uiNode, isCustomView);
    }

#ifdef ACE_STATIC
    void PushPtr(int64_t pointer) override
    {
        ViewStackProcessor::GetInstance()->PushPtr(pointer);
    }
#endif

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
        return ViewStackProcessor::GetInstance()->GetNodeIdToAccountFor();
    }

    void SetElmtIdToAccountFor(int32_t elmtId) override
    {
        ViewStackProcessor::GetInstance()->SetNodeIdToAccountFor(elmtId);
    }

    void StopGetAccessRecording() override
    {
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }

    void ImplicitPopBeforeContinue() override
    {
        ViewStackProcessor::GetInstance()->ImplicitPopBeforeContinue();
    }

    void GetAndPushFrameNode(const std::string& tag, int32_t elmtId) override
    {
        ViewStackProcessor::GetInstance()->GetAndPushFrameNode(tag, elmtId);
    }

    bool CheckTopNodeFirstBuilding() const override
    {
        return ViewStackProcessor::GetInstance()->CheckTopNodeFirstBuilding();
    }

    bool IsEmptyStack() const override
    {
        return ViewStackProcessor::GetInstance()->IsEmpty();
    }

    void PushPrebuildCompCmd() override
    {
        ViewStackProcessor::GetInstance()->PushPrebuildCompCmd();
    }

    void PushPrebuildCompCmd(const char* commandName, PrebuildFunc prebuildFunc) override
    {
        ViewStackProcessor::GetInstance()->PushPrebuildCompCmd(commandName, prebuildFunc);
    }

    bool CheckIsPrebuildTimeout() override
    {
        return ViewStackProcessor::GetInstance()->CheckIsPrebuildTimeout();
    }

    bool IsPrebuilding() override
    {
        return ViewStackProcessor::GetInstance()->IsPrebuilding();
    }

private:
    static thread_local std::unique_ptr<ScopedViewStackProcessor> scopeStack_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_MODEL_NG_H
