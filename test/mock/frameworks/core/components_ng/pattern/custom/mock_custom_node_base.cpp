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

#include "core/components_ng/pattern/custom/custom_node_base.h"

namespace OHOS::Ace::NG {
CustomNodeBase::~CustomNodeBase() = default;

void CustomNodeBase::SetJSViewName(std::string&& name)
{
    jsViewName_ = std::move(name);
}

std::string& CustomNodeBase::GetJSViewName()
{
    return jsViewName_;
}

void CustomNodeBase::SetUpdateFunction(std::function<void()>&& updateFunc)
{
    updateFunc_ = std::move(updateFunc);
}

void CustomNodeBase::Reset()
{
    needRebuild_ = false;
}

void CustomNodeBase::Update()
{
    if (updateFunc_) {
        updateFunc_();
    }
    needRebuild_ = false;
}

void CustomNodeBase::MarkNeedUpdate()
{
    needRebuild_ = true;
}

void CustomNodeBase::FireOnDisappear()
{
    if (destroyFunc_) {
        destroyFunc_();
    }
}

void CustomNodeBase::FireOnAppear()
{
    if (appearFunc_) {
        appearFunc_();
    }
}

bool CustomNodeBase::CheckFireOnAppear()
{
    return false;
}

void CustomNodeBase::FireDidBuild()
{
    if (didBuildFunc_) {
        didBuildFunc_();
    }
}

void CustomNodeBase::FireRecycleRenderFunc()
{
}
} // namespace OHOS::Ace::NG
