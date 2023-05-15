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

#include "core/components_ng/base/distribute_ui.h"

namespace OHOS::Ace::NG {
SerializeableObjectArray DistributeUI::DumpUITree()
{
    return SerializeableObjectArray();
}

void DistributeUI::SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate) 
{
}

void DistributeUI::UnSubscribeUpdate() 
{
}

void DistributeUI::ProcessSerializeableInputEvent(const SerializeableObjectArray& array) 
{
}

void DistributeUI::RestoreUITree(const SerializeableObjectArray& array) 
{
}

void DistributeUI::UpdateUITree(const SerializeableObjectArray& array) 
{
}

void DistributeUI::SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent) 
{
}

void DistributeUI::UnSubscribeInputEventProcess() 
{
}

void DistributeUI::AddDeletedNode(int32_t nodeId) 
{
}

void DistributeUI::AddNewNode(int32_t nodeId) 
{
}

void DistributeUI::AddDirtyCustomNode(int32_t nodeId) 
{
}

void DistributeUI::AddDirtyRenderNode(int32_t nodeId) 
{
}

void DistributeUI::AddDirtyLayoutNode(int32_t nodeId) 
{
}

void DistributeUI::OnTreeUpdate() 
{
}

void DistributeUI::OnPageChanged(int32_t pageId) 
{
}

int32_t DistributeUI::GetCurrentPageId()
{
    return 0;
}

void DistributeUI::BypassEvent(const TouchEvent& point, bool isSubPipe) 
{
}

bool DistributeUI::IsSinkMode()
{
    return false;
}

void DistributeUI::ApplyOneUpdate() 
{
}
} // namespace OHOS::Ace::NG
