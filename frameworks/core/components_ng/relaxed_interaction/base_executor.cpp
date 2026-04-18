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

#include "core/components_ng/relaxed_interaction/base_executor.h"

#include "core/components_ng/relaxed_interaction/frame_node_finder.h"
#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"

namespace OHOS::Ace::NG {

FrameNodeMatch BaseExecutor::FindFrameNode(
    double x, double y, GestureRecognizerPred pred)
{
    FrameNodeFinder finder(context_, pred);
    auto result = finder.FindAt(static_cast<float>(x), static_cast<float>(y));
    if (result.GetNode()) {
        WorkflowDumper::GetInstance().AddLog(
            "Found frame node " + result.GetNode()->ToString() + " for executor " + GetType());
    } else {
        WorkflowDumper::GetInstance().AddLog("No frame node found for executor " + GetType());
    }

    return result;
}

} // namespace OHOS::Ace::NG