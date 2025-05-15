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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_RS_ADAPTER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_RS_ADAPTER_H

#include <string>
#include "window.h"

#include "transaction/rs_transaction_proxy.h"
#include "ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"

namespace OHOS::Ace {
class RsAdapter {
public:
    RsAdapter() = default;
    ~RsAdapter() = default;
    static void RsUIDirectorInit(
        std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
        const OHOS::sptr<OHOS::Rosen::Window>& window, std::string cacheDir);
    static void RsFlushImplicitTransaction(
          std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
          const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
          std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode);
    static void RsFlushImplicitTransactionWithRoot(
          std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
          const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
          std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode,
          std::shared_ptr<Rosen::RSNode>& rootNode);
private:
    static void FlushImplicitTransaction();
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_RS_ADAPTER_H