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

#include "form_scoped_rs_transaction.h"

#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/container_scope.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "transaction/rs_sync_transaction_controller.h"

namespace OHOS::Ace::NG {
FormScopedRSTransaction::FormScopedRSTransaction(int32_t scopeId)
{
    ACE_SCOPED_TRACE("%s scopeId:%d", __func__, scopeId);
    std::shared_ptr<Rosen::RSTransaction> rsTransaction = OpenSyncTransaction(scopeId);

    rsTransaction_ = rsTransaction;
    if (rsTransaction) {
        rsTransaction->Begin();
    } else {
        TAG_LOGW(AceLogTag::ACE_FORM, "FormScopedRSTransaction: rsTransaction is nullptr");
    }
}

FormScopedRSTransaction::~FormScopedRSTransaction()
{
    ACE_SCOPED_TRACE("%s", __func__);
    if (rsTransaction_) {
        rsTransaction_->Commit();
    }
    CloseSyncTransaction();
}

std::shared_ptr<Rosen::RSTransaction> FormScopedRSTransaction::OpenSyncTransaction(int32_t scopeId)
{
    isMultiInstanceEnabled_ = SystemProperties::GetMultiInstanceEnabled();
    ACE_SCOPED_TRACE("%s isMultiInstanceEnabled:%d", __func__, isMultiInstanceEnabled_);
    if (isMultiInstanceEnabled_) {
        ContainerScope scope(scopeId);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (!pipeline) {
            TAG_LOGE(AceLogTag::ACE_FORM, "FormScopedRSTransaction: pipeline is nullptr");
            return nullptr;
        }
        std::shared_ptr<Rosen::RSUIDirector> rsUIDirector = pipeline->GetRSUIDirector();
        CHECK_NULL_RETURN(rsUIDirector, nullptr);
        auto rsUIContext = rsUIDirector->GetRSUIContext();
        CHECK_NULL_RETURN(rsUIContext, nullptr);
        auto transactionHandler = rsUIContext->GetSyncTransactionHandler();
        CHECK_NULL_RETURN(transactionHandler, nullptr);

        if (!transactionHandler->GetRSTransaction()) {
            transactionHandler->OpenSyncTransaction();
            needCloseSync_ = true;
            transactionHandler_ = transactionHandler;
        }
        return transactionHandler->GetRSTransaction();
    } else {
        auto transactionController = Rosen::RSSyncTransactionController::GetInstance();
        if (!transactionController->GetRSTransaction()) {
            transactionController->OpenSyncTransaction();
            needCloseSync_ = true;
        }
        return transactionController->GetRSTransaction();
    }
}

void FormScopedRSTransaction::CloseSyncTransaction()
{
    if (!needCloseSync_) {
        return;
    }

    if (isMultiInstanceEnabled_) {
        transactionHandler_->CloseSyncTransaction();
        return;
    }

    auto transactionController = Rosen::RSSyncTransactionController::GetInstance();
    if (transactionController) {
        transactionController->CloseSyncTransaction();
    }
}
} // namespace OHOS::Ace::NG
