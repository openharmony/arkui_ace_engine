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

#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
thread_local std::unique_ptr<ViewStackProcessor> ViewStackProcessor::instance = nullptr;

ViewStackProcessor* ViewStackProcessor::GetInstance()
{
    if (!instance) {
        instance.reset(new ViewStackProcessor);
    }
    return instance.get();
}

ViewStackProcessor::ViewStackProcessor() = default;

RefPtr<FrameNode> ViewStackProcessor::GetMainFrameNode() const
{
    return AceType::DynamicCast<FrameNode>(GetMainElementNode());
}

RefPtr<UINode> ViewStackProcessor::GetMainElementNode() const
{
    if (elementsStack_.empty()) {
        return nullptr;
    }
    return elementsStack_.top();
}

void ViewStackProcessor::Push(const RefPtr<UINode>& element, bool /*isCustomView*/)
{
    elementsStack_.push(element);
}

RefPtr<UINode> ViewStackProcessor::Finish()
{
    auto element = elementsStack_.top();
    elementsStack_.pop();
    return element;
}

bool ViewStackProcessor::IsCurrentVisualStateProcess()
{
    return true;
}

} // namespace OHOS::Ace::NG
