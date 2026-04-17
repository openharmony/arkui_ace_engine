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

#include "adapter/ohos/entrance/rs_adapter.h"

#include "base/utils/system_properties.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/pipeline/pipeline_base.h"
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "wm/window.h"

namespace OHOS::Ace {

void RsAdapter::RsUIDirectorInit(
    std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
    const OHOS::sptr<OHOS::Rosen::Window>& window, std::string cacheDir)
{
    rsUiDirector = window->GetRSUIDirector();
    rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());
    rsUiDirector->SetCacheDir(cacheDir);
}

void RsAdapter::RsFlushImplicitTransaction(std::shared_ptr<OHOS::Rosen::RSUIDirector> &rsUiDirector,
    const OHOS::sptr<OHOS::Rosen::Window> &dragWindow, std::shared_ptr<OHOS::Rosen::RSSurfaceNode> &surfaceNode)
{
    rsUiDirector = dragWindow->GetRSUIDirector();

    auto surfaceNodeFromWindow = dragWindow->GetSurfaceNode();
    if (surfaceNodeFromWindow) {
        auto rsUiContext = surfaceNodeFromWindow->GetRSUIContext();
        if (rsUiContext) {
            rsUiContext->GetRSTransaction()->FlushImplicitTransaction();
        } else {
            FlushImplicitTransaction();
        }
    } else {
        FlushImplicitTransaction();
    }
    rsUiDirector->SetRSSurfaceNode(surfaceNodeFromWindow);
}

void RsAdapter::RsFlushImplicitTransactionWithRoot(
    std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
    const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
    std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode,
    std::shared_ptr<Rosen::RSNode>& rootNode)
{
    rsUiDirector = dragWindow->GetRSUIDirector();
    auto surfaceNode1 = dragWindow->GetSurfaceNode();
    std::shared_ptr<Rosen::RSUIContext> rsUiContext;
    if (surfaceNode1) {
        rsUiContext = surfaceNode->GetRSUIContext();
        if (rsUiContext) {
            rsUiContext->GetRSTransaction()->FlushImplicitTransaction();
        } else {
            FlushImplicitTransaction();
        }
    } else {
        FlushImplicitTransaction();
    }
    rsUiDirector->SetRSSurfaceNode(surfaceNode1);
    rootNode = Rosen::RSRootNode::Create(false, false, rsUiContext);
}

void RsAdapter::FlushImplicitTransaction()
{
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
}

std::shared_ptr<Rosen::RSUIContext> RsAdapter::GetRSUIContext(const RefPtr<PipelineBase>& pipeline)
{
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto window = pipeline->GetWindow();
    CHECK_NULL_RETURN(window, nullptr);
    auto rsUIDirector = window->GetRSUIDirector();
    CHECK_NULL_RETURN(rsUIDirector, nullptr);
    auto rsUIContext = rsUIDirector->GetRSUIContext();
    return rsUIContext;
}
}