/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/pipeline/base/rs_render_node.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_ui_director.h"

#include "core/components/remote_window/rosen_render_remote_window.h"
#endif

namespace OHOS::Ace {

const std::shared_ptr<RSNode>& RSRenderNode::GetRSNode()
{
    return rsNode_;
}
} // namespace OHOS::Ace
