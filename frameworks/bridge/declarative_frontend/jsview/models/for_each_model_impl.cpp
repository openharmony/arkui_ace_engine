/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <string>

#include "bridge/declarative_frontend/jsview/models/for_each_model_impl.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {


void ForEachModelImpl::Create(const std::string& compilerGenId, const OHOS::Ace::ForEachFunc& ForEachFunc)
{
    if (compilerGenId == "") {
        LOGE("Missing ForEach id");
        return;
    }
    if (!ForEachFunc.idGenFunc_ || !ForEachFunc.itemGenFunc_) {
        LOGE("for each func is nullptr");
        return;
    }

    auto* viewStack = ViewStackProcessor::GetInstance();
    std::string viewId = viewStack->ProcessViewId(compilerGenId);
    viewStack->Push(AceType::MakeRefPtr<ForEachComponent>(viewId, "ForEach"));

    std::vector<std::string> keys = ForEachFunc.idGenFunc_();
    for (size_t i = 0; i < keys.size(); i++) {
        keys[i].insert(0, "-");
        keys[i].insert(0, compilerGenId);
        viewStack->PushKey(keys[i]);

        viewStack->Push(AceType::MakeRefPtr<MultiComposedComponent>(viewStack->GetKey(), "ForEachItem"));
        ForEachFunc.itemGenFunc_(i);
        viewStack->PopContainer();
        viewStack->PopKey();
    }
}

void ForEachModelImpl::Create()
{
    LOGE("Create (no params) unsupported by ForEachModelImpl");
}

void ForEachModelImpl::Pop()
{
    ViewStackProcessor::GetInstance()->PopContainer();
}

std::list<std::string> ForEachModelImpl::GetCurrentIdList(int32_t nodeId)
{
    LOGE("GetCurrentIdList unsupported by ForEachModelImpl");
    return {};
}

void ForEachModelImpl::SetNewIds(std::list<std::string>&& newIds)
{
    LOGE("SetNewIds unsupported by ForEachModelImpl");
}

void ForEachModelImpl::CreateNewChildStart(const std::string& id)
{
    LOGE("CreateNewChildStart unsupported by ForEachModelImpl");
}

void ForEachModelImpl::CreateNewChildFinish(const std::string& id)
{
    LOGE("CreateNewChildFinish unsupported by ForEachModelImpl");
}

} // namespace OHOS::Ace::Framework
