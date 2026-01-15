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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SCOPED_RS_TRANSACTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SCOPED_RS_TRANSACTION_H

#include <stdint.h>
#include "transaction/rs_sync_transaction_handler.h"
#include "transaction/rs_transaction.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace::NG {
class FormScopedRSTransaction final {
public:
    FormScopedRSTransaction(int32_t scopeId);
    ~FormScopedRSTransaction();

    ACE_DISALLOW_COPY_AND_MOVE(FormScopedRSTransaction);

private:
    std::shared_ptr<Rosen::RSTransaction> OpenSyncTransaction(int32_t scopeId);
    void CloseSyncTransaction();

    std::shared_ptr<Rosen::RSSyncTransactionHandler> transactionHandler_;
    std::shared_ptr<Rosen::RSTransaction> rsTransaction_;
    bool needCloseSync_ = false;
    bool isMultiInstanceEnabled_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SCOPED_RS_TRANSACTION_H
