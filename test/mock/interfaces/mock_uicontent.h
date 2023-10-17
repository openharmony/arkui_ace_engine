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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_UICONTENT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_UICONTENT_H

#include "gmock/gmock.h"
#include "native_engine/native_engine.h"
#include "native_engine/native_value.h"
#include "ui_content.h"

namespace OHOS {
namespace Ace {
class MockUIContent : public UIContent {
public:
    MockUIContent() = default;
    ~MockUIContent() override = default;

    MOCK_METHOD3(Initialize, void(OHOS::Rosen::Window* window, const std::string& url, napi_value storage));
    MOCK_METHOD3(InitializeByName, void(OHOS::Rosen::Window* window, const std::string& name, napi_value storage));
    MOCK_METHOD4(Initialize,
        void(OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowID));
    MOCK_METHOD0(Foreground, void());
    MOCK_METHOD0(Background, void());
    MOCK_METHOD0(Focus, void());
    MOCK_METHOD0(UnFocus, void());
    MOCK_METHOD0(Destroy, void());
    MOCK_METHOD1(OnNewWant, void(const OHOS::AAFwk::Want& want));
    MOCK_METHOD3(Restore, void(OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage));
    MOCK_CONST_METHOD0(GetContentInfo, std::string());
    MOCK_METHOD0(DestroyUIDirector, void());
    MOCK_METHOD0(ProcessBackPressed, bool());
    MOCK_METHOD1(ProcessPointerEvent, bool(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent));
    MOCK_METHOD1(ProcessKeyEvent, bool(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent));
    MOCK_METHOD1(ProcessAxisEvent, bool(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent));
    MOCK_METHOD1(ProcessVsyncEvent, bool(uint64_t timeStampNanos));
    MOCK_METHOD1(UpdateConfiguration, void(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config));
    MOCK_METHOD3(UpdateViewportConfig, void(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
                                           const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction));
    MOCK_METHOD2(UpdateWindowMode, void(OHOS::Rosen::WindowMode mode, bool hasDeco));
    MOCK_METHOD3(HideWindowTitleButton, void(bool hideSplit, bool hideMaximize, bool hideMinimize));
    MOCK_METHOD1(SetIgnoreViewSafeArea, void(bool ignoreViewSafeArea));
    MOCK_METHOD0(GetBackgroundColor, uint32_t());
    MOCK_METHOD1(SetBackgroundColor, void(uint32_t color));
    MOCK_METHOD2(DumpInfo, void(const std::vector<std::string>& params, std::vector<std::string>& info));
    MOCK_METHOD1(SetNextFrameLayoutCallback, void(std::function<void()>&& callback));
    MOCK_METHOD1(NotifyMemoryLevel, void(int32_t level));
    MOCK_METHOD1(SetAppWindowTitle, void(const std::string& title));
    MOCK_METHOD1(SetAppWindowIcon, void(const std::shared_ptr<Media::PixelMap>& pixelMap));
    MOCK_METHOD0(GetFormRootNode, std::shared_ptr<Rosen::RSSurfaceNode>());
    MOCK_METHOD1(UpdateFormData, void(const std::string& data));
    MOCK_METHOD1(
        UpdateFormSharedImage, void(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap));
    MOCK_METHOD1(SetFormWidth, void(const float width));
    MOCK_METHOD1(SetFormHeight, void(const float height));
    MOCK_METHOD0(GetFormWidth, float());
    MOCK_METHOD0(GetFormHeight, float());
    MOCK_METHOD2(OnFormSurfaceChange, void(float width, float height));
    MOCK_METHOD1(SetActionEventHandler, void(std::function<void(const std::string& action)>&& actionCallback));
    MOCK_METHOD1(SetFormLinkInfoUpdateHandler, void(std::function<void(const std::vector<std::string>&)>&& callback));
    MOCK_METHOD1(SetErrorEventHandler,
        void(std::function<void(const std::string& code, const std::string& msg)>&& actionCallback));
    MOCK_METHOD1(ReloadForm, void(const std::string& url));
    MOCK_METHOD1(SetIsFocusActive, void(bool isFocusActive));

    MOCK_METHOD3(CreateModalUIExtension, int32_t(const AAFwk::Want& want,
        const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config));
    MOCK_METHOD1(CloseModalUIExtension, void(int32_t sessionId));
};
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_UICONTENT_H
