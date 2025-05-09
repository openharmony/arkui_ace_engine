/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_FRONTEND_H

#include <memory>

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"

#include "base/memory/ace_type.h"
#include "core/common/ace_page.h"
#include "core/common/frontend.h"

namespace OHOS::Ace {
class ACE_EXPORT MockFrontend : public Frontend {
    DECLARE_ACE_TYPE(MockFrontend, Frontend);

public:
    MOCK_METHOD(bool, Initialize, (FrontendType type, const RefPtr<TaskExecutor>& taskExecutor), (override));
    MOCK_METHOD(void, Destroy, (), (override));
    MOCK_METHOD(void, AttachPipelineContext, (const RefPtr<PipelineBase>& context), (override));
    MOCK_METHOD(void, SetAssetManager, (const RefPtr<AssetManager>& assetManager), (override));
    MOCK_METHOD(UIContentErrorCode, RunPage, (const std::string& url, const std::string& params), (override));
    MOCK_METHOD(void, ReplacePage, (const std::string& url, const std::string& params), (override));
    MOCK_METHOD(void, PushPage, (const std::string& url, const std::string& params), (override));
    MOCK_METHOD(void, AddPage, (const RefPtr<AcePage>& page), (override));
    MOCK_METHOD(void, TriggerGarbageCollection, (), (override));
    MOCK_METHOD(void, UpdateState, (Frontend::State state), (override));
    MOCK_METHOD(RefPtr<AccessibilityManager>, GetAccessibilityManager, (), (const override));
    MOCK_METHOD(bool, IsForeground, (), (override));
    MOCK_METHOD(RefPtr<AceEventHandler>, GetEventHandler, (), (override));
    MOCK_METHOD(void, RebuildAllPages, (), (override));
    MOCK_METHOD(void, SetColorMode, (ColorMode colorMode), (override));
    MOCK_METHOD(void, CallRouterBack, (), (override));
    MOCK_METHOD(void, OnNewWant, (const std::string& data), (override));
    MOCK_METHOD(void, OnNewRequest, (const std::string& data), (override));
    MOCK_METHOD(void, OnRemoteTerminated, (), (override));
    MOCK_METHOD(bool, OnRestoreData, (const std::string& data), (override));
    MOCK_METHOD(void, OnSaveData, (std::string & data), (override));
    MOCK_METHOD(void, OnMemoryLevel, (const int32_t level), (override));
    MOCK_METHOD(void, OnCompleteContinuation, (int32_t code), (override));
    MOCK_METHOD(bool, OnStartContinuation, (), (override));
    MOCK_METHOD(void, OnInactive, (), (override));
    MOCK_METHOD(void, OnActive, (), (override));
    MOCK_METHOD(void, OnHide, (), (override));
    MOCK_METHOD(void, OnShow, (), (override));
    MOCK_METHOD(void, OnRestoreAbilityState, (const std::string& data), (override));
    MOCK_METHOD(void, OnSaveAbilityState, (std::string & data), (override));
    MOCK_METHOD(bool, OnBackPressed, (), (override));
    MOCK_METHOD(void, DumpFrontend, (), (const override));
    MOCK_METHOD(std::string, GetPagePath, (), (const override));
    MOCK_METHOD(RefPtr<AcePage>, GetPage, (int32_t pageId), (const override));
    MOCK_METHOD(void, LoadPluginJsCode, (std::string && jsCode), (const override));
    MOCK_METHOD(void, SetJsMessageDispatcher, (const RefPtr<JsMessageDispatcher>& dispatcher), (const override));
    MOCK_METHOD(void, SendCallbackMessage, (const std::string& callbackId, const std::string& data), (const override));
    MOCK_METHOD(void, TransferComponentResponseData, (int32_t callbackId, int32_t code, std::vector<uint8_t>&& data),
        (const override));
    MOCK_METHOD(void, TransferJsResponseData, (int32_t callbackId, int32_t code, std::vector<uint8_t>&& data),
        (const override));
    MOCK_METHOD(
        void, TransferJsEventData, (int32_t callbackId, int32_t code, std::vector<uint8_t>&& data), (const override));
    MOCK_METHOD(void, TransferJsPluginGetError, (int32_t callbackId, int32_t errorCode, std::string&& errorMessage),
        (const override));
    MOCK_METHOD(void, LoadPluginJsByteCode, (std::vector<uint8_t> && jsCode, std::vector<int32_t>&& jsCodeLen),
        (const override));

    void OnSurfaceChanged(int32_t width, int32_t height) override
    {
        width_ = width;
        height_ = height;
    }

    void OnLayoutCompleted(const std::string& componentId) override
    {
        componentId_ = componentId;
    }
    void OnDrawCompleted(const std::string& componentId) override
    {
        componentId_ = componentId;
    }

    void OnDrawChildrenCompleted(const std::string& componentId) override
    {
        componentId_ = componentId;
    }

    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) override
    {
        return false;
    }

    int32_t GetWidth() const
    {
        return width_;
    }

    int32_t GetHeight() const
    {
        return height_;
    }

    const std::string& GetComponentId() const
    {
        return componentId_;
    }

    WindowConfig& GetWindowConfig() override
    {
        return windowConfig_;
    }

private:
    int32_t width_ = 0;
    int32_t height_ = 0;
    std::string componentId_ = "init_id";
    WindowConfig windowConfig_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_FRONTEND_H
