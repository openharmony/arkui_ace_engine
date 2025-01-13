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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_FORM_FRONTEND_DECLARATIVE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_FORM_FRONTEND_DECLARATIVE_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/common/ace_page.h"
#include "core/common/frontend.h"
#include "frameworks/bridge/card_frontend/form_frontend_delegate_declarative.h"
#include "frameworks/bridge/card_frontend/js_card_parser.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/page_id_pool.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"

namespace OHOS::Ace {
class ACE_EXPORT FormFrontendDeclarative : public DeclarativeFrontend {
    DECLARE_ACE_TYPE(FormFrontendDeclarative, DeclarativeFrontend);
public:
    FormFrontendDeclarative() = default;

    // Card
    void UpdateData(const std::string& dataList);
    void HandleSurfaceChanged(int32_t width, int32_t height);
    void UpdatePageData(const std::string& dataList);
    void OnMediaFeatureUpdate();

    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
    UIContentErrorCode RunDynamicPage(
        const std::string& url, const std::string& params, const std::string& entryPoint) override;

    void SetErrorEventHandler(
        std::function<void(const std::string&, const std::string&)>&& errorCallback) override;

    void OnSurfaceChanged(int32_t width, int32_t height) override;
    void SetColorMode(ColorMode colorMode) override;

    void SetLoadCardCallBack(const WeakPtr<PipelineBase>& outSidePipelineContext)
    {
        const auto& loadCallback = [outSidePipelineContext](
                                       const std::string& url, int64_t cardId, const std::string& entryPoint) -> bool {
            auto context = outSidePipelineContext.Upgrade();
            if (!context) {
                return false;
            }

            auto outSidefrontend = AceType::DynamicCast<DeclarativeFrontend>(context->GetFrontend());
            if (!outSidefrontend) {
                return false;
            }

            // Use the same js engine with host pipeline
            auto jsEngine = outSidefrontend->GetJsEngine();
            if (!jsEngine) {
                return false;
            }
            return jsEngine->LoadCard(url, cardId, entryPoint);
        };

        auto delegate = AceType::DynamicCast<Framework::FormFrontendDelegateDeclarative>(delegate_);
        if (delegate) {
            delegate->SetLoadCardCallBack(loadCallback);
        }
    }

    RefPtr<Framework::FormFrontendDelegateDeclarative> GetDelegate()
    {
        return AceType::DynamicCast<Framework::FormFrontendDelegateDeclarative>(delegate_);
    }

    std::string GetFormSrcPath(const std::string& uri, const std::string& suffix) const;

    void SetFormSrc(std::string formSrc)
    {
        formSrc_ = formSrc;
    }

    std::string GetFormSrc() const
    {
        return formSrc_;
    }

    void SetRunningCardId(int64_t cardId)
    {
        cardId_ = cardId;
    }

    void SetIsFormRender(bool isCardfront)
    {
        isFormRender_ = isCardfront;
    }

    bool IsFormRender()
    {
        return isFormRender_;
    }

    void SetTaskExecutor(RefPtr<TaskExecutor> taskExecutor)
    {
        taskExecutor_ = taskExecutor;
    }

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }
    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }
    std::string GetModuleName() const
    {
        return moduleName_;
    }
    std::string GetBundleName() const
    {
        return bundleName_;
    }
    void SetIsBundle(bool isBundle)
    {
        isBundle_ = isBundle;
    }
    bool IsBundle() const
    {
        return isBundle_;
    }

    UIContentErrorCode InnerRunCardPage(
        const std::string& url, const std::string& params, const std::string& entryPoint);
    UIContentErrorCode InnerRunDynamicPage(
        const std::string& url, const std::string& params, const std::string& entryPoint);

    ColorMode colorMode_ = ColorMode::LIGHT;
    bool foregroundFrontend_ = false;
    double density_ = 1.0;
    std::string cardHapPath_;

    Framework::PipelineContextHolder holder_;
    RefPtr<AssetManager> assetManager_;

    mutable std::once_flag onceFlag_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AceEventHandler> eventHandler_;
    std::string formSrc_;
    WindowConfig cardWindowConfig_;
    uint64_t cardId_ = 0; // cardId != formId, cardId is the nodeId of component.

    std::string bundleName_;
    std::string moduleName_;
    bool isBundle_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_FORM_FRONTEND_DECLARATIVE_H
