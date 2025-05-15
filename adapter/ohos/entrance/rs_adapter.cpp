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

namespace OHOS::Ace {

void RsAdapter::RsUIDirectorInit(
    std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
    const OHOS::sptr<OHOS::Rosen::Window>& window, std::string cacheDir)
{
    if (!SystemProperties::GetMultiInstanceEnabled()) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        auto surfaceNode = window->GetSurfaceNode();
        rsUiDirector->SetRSSurfaceNode(surfaceNode);
        rsUiDirector->SetCacheDir(cacheDir);
        rsUiDirector->Init();
    } else {
        rsUiDirector = window->GetRSUIDirector();
        if (!rsUiDirector) {
            rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        }
        rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());
        rsUiDirector->SetCacheDir(cacheDir);
        rsUiDirector->Init(true, true);
    }
}

void RsAdapter::RsFlushImplicitTransaction(
    std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
    const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
    std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode)
{
    if (!SystemProperties::GetMultiInstanceEnabled()) {
        rsUiDirector = Rosen::RSUIDirector::Create();
        rsUiDirector->Init();
        auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
        if (transactionProxy != nullptr) {
            transactionProxy->FlushImplicitTransaction();
        }
    } else {
        rsUiDirector = dragWindow->GetRSUIDirector();
        if (!rsUiDirector) {
            rsUiDirector = Rosen::RSUIDirector::Create();
        }
        rsUiDirector->Init(true, true);
        auto surfaceNode = dragWindow->GetSurfaceNode();
        if (surfaceNode) {
            auto rsUiContext = surfaceNode->GetRSUIContext();
            if (rsUiContext) {
                rsUiContext->GetRSTransaction()->FlushImplicitTransaction();
            } else {
                FlushImplicitTransaction();
            }
        } else {
            FlushImplicitTransaction();
        }
    }
    rsUiDirector->SetRSSurfaceNode(surfaceNode);
}

void RsAdapter::RsFlushImplicitTransactionWithRoot(
    std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
    const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
    std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode,
    std::shared_ptr<Rosen::RSNode>& rootNode)
{
    if (!SystemProperties::GetMultiInstanceEnabled()) {
        rsUiDirector = Rosen::RSUIDirector::Create();
        rsUiDirector->Init();
        auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
        if (transactionProxy != nullptr) {
            transactionProxy->FlushImplicitTransaction();
        }
        rsUiDirector->SetRSSurfaceNode(surfaceNode);
        rootNode = Rosen::RSRootNode::Create();
    } else {
        rsUiDirector = dragWindow->GetRSUIDirector();
        if (!rsUiDirector) {
            rsUiDirector = Rosen::RSUIDirector::Create();
        }
        rsUiDirector->Init(true, true);
        auto surfaceNode = dragWindow->GetSurfaceNode();
        std::shared_ptr<Rosen::RSUIContext> rsUiContext;
        if (surfaceNode) {
            rsUiContext = surfaceNode->GetRSUIContext();
            if (rsUiContext) {
                rsUiContext->GetRSTransaction()->FlushImplicitTransaction();
            } else {
                FlushImplicitTransaction();
            }
        } else {
            FlushImplicitTransaction();
        }
        rsUiDirector->SetRSSurfaceNode(surfaceNode);
        rootNode = Rosen::RSRootNode::Create(false, false, rsUiContext);
    }
}

void RsAdapter::FlushImplicitTransaction()
{
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
}
}