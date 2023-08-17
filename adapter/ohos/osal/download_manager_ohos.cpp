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

#include "http_proxy.h"
#include "net_conn_client.h"

#include "base/network/download_manager.h"
namespace OHOS::Ace {
bool DownloadManager::GetProxy(ProxyInfo& proxy)
{
    NetManagerStandard::HttpProxy httpProxy;
    NetManagerStandard::NetConnClient::GetInstance().GetDefaultHttpProxy(httpProxy);
    proxy.host = httpProxy.GetHost();
    proxy.port = httpProxy.GetPort();

    auto exclusionList = httpProxy.GetExclusionList();
    for (auto&& ex: exclusionList) {
        proxy.exclusions.append(ex);
        if (ex != exclusionList.back()) {
            proxy.exclusions.append(",");
        }
    }
    return true;
}
} // namespace OHOS::Ace
