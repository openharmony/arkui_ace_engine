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

#include "adapter/ohos/entrance/ace_container.h"

namespace OHOS::Ace::Platform {
namespace {
constexpr uint32_t DEFAULT_WINDOW_TYPE = 1;
}

using AcePlatformFinish = std::function<void()>;
using AcePlatformStartAbility = std::function<void(const std::string& address)>;
class MockPlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit MockPlatformEventCallback(AcePlatformFinish onFinish) : onFinish_(onFinish) {}
    MockPlatformEventCallback(AcePlatformFinish onFinish, AcePlatformStartAbility onStartAbility)
        : onFinish_(onFinish), onStartAbility_(onStartAbility) {}

    ~MockPlatformEventCallback() override = default;

    void OnFinish() const override {}

    void OnStartAbility(const std::string& address) override {}

    void OnStatusBarBgColorChanged(uint32_t color) override {}

private:
    AcePlatformFinish onFinish_;
    AcePlatformStartAbility onStartAbility_;
};

AceContainer::AceContainer(int32_t instanceId, FrontendType type, std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility,
    std::unique_ptr<PlatformEventCallback> callback, bool useCurrentEventRunner, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), aceAbility_(aceAbility), useCurrentEventRunner_(useCurrentEventRunner) {}

AceContainer::AceContainer(int32_t instanceId, FrontendType type,
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool isSubAceContainer, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), runtimeContext_(std::move(runtimeContext)),
      abilityInfo_(std::move(abilityInfo)), useCurrentEventRunner_(useCurrentEventRunner),
      isSubContainer_(isSubAceContainer) {}

// for DynamicComponent
AceContainer::AceContainer(int32_t instanceId, FrontendType type,
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
    std::shared_ptr<TaskWrapper> taskWrapper,
    bool useCurrentEventRunner, bool isSubAceContainer, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), runtimeContext_(std::move(runtimeContext)),
      abilityInfo_(std::move(abilityInfo)), useCurrentEventRunner_(useCurrentEventRunner),
      isSubContainer_(isSubAceContainer) {}

AceContainer::~AceContainer() {}

RefPtr<AceContainer> container_;

void AceContainer::SetAppRunningUniqueId(const std::string& uniqueId)
{
    return;
}

const std::string& AceContainer::GetAppRunningUniqueId() const
{
    static const std::string res;
    return res;
}

RefPtr<AceContainer> AceContainer::GetContainer(int32_t instanceId)
{
    if (container_) {
        return container_;
    }
    std::weak_ptr<OHOS::AbilityRuntime::Context> context =
        std::weak_ptr<OHOS::AbilityRuntime::ContextImpl>();
    auto abilityInfo = std::weak_ptr<OHOS::AppExecFwk::AbilityInfo>();
    AcePlatformFinish onFinish;
    AcePlatformStartAbility onStartAbility;
    std::unique_ptr<PlatformEventCallback> callback =
        std::make_unique<MockPlatformEventCallback>(onFinish, onStartAbility);
    container_ = AceType::MakeRefPtr<AceContainer>(instanceId, FrontendType::DECLARATIVE_JS, context,
        abilityInfo, std::move(callback));
    return container_;
}

bool AceContainer::UpdatePopupUIExtension(const RefPtr<NG::FrameNode>& node,
    uint32_t autoFillSessionId, bool isNative)
{
    return true;
}

bool AceContainer::ClosePopupUIExtension(uint32_t autoFillSessionId)
{
    return true;
}

void AceContainer::Initialize() {}

void AceContainer::Destroy() {}

bool AceContainer::IsKeyboard()
{
    return true;
}

void AceContainer::DestroyView() {}

void AceContainer::Dispatch(const std::string& group, std::vector<uint8_t>&& data,
    int32_t id, bool replyToComponent) const {}

void AceContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode,
    std::string&& errorMessage) const {}

bool AceContainer::Dump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    return true;
}

void AceContainer::TriggerGarbageCollection() {}

void AceContainer::DumpHeapSnapshot(bool isPrivate) {}

void AceContainer::DestroyHeapProfiler() {}

void AceContainer::ForceFullGC() {}
void AceContainer::CheckAndSetFontFamily() {}
void AceContainer::HotReload() {}
NG::SafeAreaInsets AceContainer::GetKeyboardSafeArea()
{
    return {};
}
bool AceContainer::IsLauncherContainer()
{
    return true;
}
bool AceContainer::IsScenceBoardWindow()
{
    return false;
}
bool AceContainer::IsUIExtensionWindow()
{
    return false;
}
bool AceContainer::IsSceneBoardEnabled()
{
    return true;
}
bool AceContainer::IsMainWindow() const
{
    return true;
}
bool AceContainer::IsSubWindow() const
{
    return true;
}
bool AceContainer::IsDialogWindow() const
{
    return true;
}
bool AceContainer::IsSystemWindow() const
{
    return true;
}
bool AceContainer::IsHostMainWindow() const
{
    return true;
}
bool AceContainer::IsHostSubWindow() const
{
    return true;
}
bool AceContainer::IsHostDialogWindow() const
{
    return true;
}
bool AceContainer::IsHostSystemWindow() const
{
    return true;
}
bool AceContainer::IsHostSceneBoardWindow() const
{
    return true;
}
uint32_t AceContainer::GetParentMainWindowId(uint32_t currentWindowId) const
{
    return 0;
}
bool AceContainer::GetCurPointerEventInfo(DragPointerEvent& dragPointerEvent, StopDragCallback&& stopDragCallback)
{
    return true;
}

bool AceContainer::GetCurPointerEventSourceType(int32_t& sourceType)
{
    return true;
}

int32_t AceContainer::RequestAutoFill(const RefPtr<NG::FrameNode>& node, AceAutoFillType autoFillType,
    bool isNewPassWord, bool& isPopup, uint32_t& autoFillSessionId, bool isNative,
    const std::function<void()>& onFinish, const std::function<void()>& onUIExtNodeBindingCompleted)
{
    return AceAutoFillError::ACE_AUTO_FILL_SUCCESS;
}

bool AceContainer::IsNeedToCreatePopupWindow(const AceAutoFillType& autoFillType)
{
    return true;
}
bool AceContainer::RequestAutoSave(const RefPtr<NG::FrameNode>& node, const std::function<void()>& onFinish,
    const std::function<void()>& onUIExtNodeBindingCompleted, bool isNative,
    int32_t instanceId)
{
    return true;
}
std::shared_ptr<NavigationController> AceContainer::GetNavigationController(const std::string& navigationId)
{
    return nullptr;
}
void AceContainer::OverwritePageNodeInfo(const RefPtr<NG::FrameNode>& frameNode,
    AbilityBase::ViewData& viewData) {}
HintToTypeWrap AceContainer::PlaceHolderToType(const std::string& onePlaceHolder)
{
    HintToTypeWrap hintToTypeWrap;
    return hintToTypeWrap;
}
void AceContainer::TerminateUIExtension() {}
bool AceContainer::UIExtensionIsHalfScreen()
{
    return false;
}
bool AceContainer::MaybeRelease()
{
    return true;
}
uint32_t AceContainer::GetParentWindowType() const
{
    return 0;
}
uint32_t AceContainer::GetWindowType() const
{
    return 0;
}

sptr<IRemoteObject> AceContainer::GetParentToken()
{
    return parentToken_;
}
Rosen::AvoidArea AceContainer::GetAvoidAreaByType(Rosen::AvoidAreaType type)
{
    return {};
}
uint32_t AceContainer::GetStatusBarHeight()
{
    return 0;
}

void AceContainer::NotifyConfigurationChange(
    bool needReloadTransition, const ConfigurationChange& configurationChange) {}

sptr<IRemoteObject> AceContainer::GetToken()
{
    return token_;
}

std::shared_ptr<AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(
    const std::string& bundle, const std::string& module)
{
    return nullptr;
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindow(int32_t instanceId)
{
    return nullptr;
}

void AceContainer::SetCurPointerEvent(const std::shared_ptr<MMI::PointerEvent>& currentEvent) {}

void AceContainer::UpdateConfiguration(const ParsedConfig& parsedConfig, const std::string& configuration) {}
bool AceContainer::GetLastMovingPointerPosition(DragPointerEvent& dragPointerEvent)
{
    return true;
}
} // namespace OHOS::Ace::Platform
