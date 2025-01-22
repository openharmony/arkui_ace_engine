/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/app_bar/app_bar_utils.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

namespace OHOS::Ace::NG {
bool ExecuteCustomAppBarAbc()
{
    auto custom = CustomAppBarNode::CreateCustomNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    return true;
}
} // namespace OHOS::Ace::NG
