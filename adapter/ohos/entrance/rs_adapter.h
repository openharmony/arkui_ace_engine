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

#include "base/memory/referenced.h"
#include "transaction/rs_transaction_proxy.h"

namespace OHOS::Rosen {
class RSUIContext;
class RSUIDirector;
class RSSurfaceNode;
class RSNode;
class Window;
}

namespace OHOS::Ace {
class PipelineBase;
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
    static std::shared_ptr<Rosen::RSUIContext> GetRSUIContext(const RefPtr<PipelineBase>& pipeline);
private:
    static void FlushImplicitTransaction();
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_RS_ADAPTER_H