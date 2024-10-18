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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MANAGER_H

#include <bitset>
#include <memory>
#include <mutex>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/want/want_wrap.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "interfaces/inner_api/ace/viewport_config.h"

namespace OHOS {
template<typename T>
class sptr;
namespace Rosen {
class AvoidArea;
enum class WSError;
class OccupiedAreaChangeInfo;
} // namespace Rosen
} // namespace OHOS

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t UI_EXTENSION_UNKNOW_ID = 0;
constexpr int32_t UI_EXTENSION_ID_FIRST_MAX = 10;
constexpr int32_t UI_EXTENSION_ID_OTHER_MAX = 9;
constexpr int64_t UI_EXTENSION_OFFSET_MAX = 100000000000;
constexpr int64_t UI_EXTENSION_OFFSET_MIN = 10000000000;
constexpr int32_t UI_EXTENSION_ID_FACTOR = 10;
constexpr int32_t UI_EXTENSION_LEVEL_MAX = 3;
constexpr int32_t UI_EXTENSION_ROOT_ID = -1;
}; // namespace

class UIExtensionPattern;
class SecurityUIExtensionPattern;
class UIExtensionManager : public AceType {
    DECLARE_ACE_TYPE(UIExtensionManager, AceType);

public:
    UIExtensionManager() = default;
    ~UIExtensionManager() override = default;

    void RegisterUIExtensionInFocus(
        const WeakPtr<UIExtensionPattern>& uiExtensionFocused, const WeakPtr<SessionWrapper>& sessionWrapper);
    bool OnBackPressed();
    const RefPtr<FrameNode> GetFocusUiExtensionNode();
    bool IsWrapExtensionAbilityId(int64_t elementId);
    bool SendAccessibilityEventInfo(const Accessibility::AccessibilityEventInfo& eventInfo, int64_t uiExtensionOffset,
        const RefPtr<PipelineBase>& pipeline);
    std::pair<int64_t, int64_t> UnWrapExtensionAbilityId(int64_t extensionOffset, int64_t elementId);
    int32_t ApplyExtensionId();
    void RecycleExtensionId(int32_t id);
    void RegisterSecurityUIExtensionInFocus(
        const WeakPtr<SecurityUIExtensionPattern>& uiExtensionFocused,
        const WeakPtr<SessionWrapper>& sessionWrapper);

    /**
     * @brief Create a UIExtensionComponent object on the page and save it in the UIExtension management object
     *
     * @param uiExtension The UIExtensionComponent pattern object
     */
    void AddAliveUIExtension(int32_t nodeId, const WeakPtr<UIExtensionPattern>& uiExtension);

    /**
     * @brief Clear the UIExtensionComponent to be destroyed
     *
     * @param nodeId The UIExtensionComponent Id
     */
    void RemoveDestroyedUIExtension(int32_t nodeId);

    /**
     * @brief Check whether UIExtensionComponent Node is showing placeholder
     *
     * @param nodeId The UIExtensionComponent Id
     */
    bool IsShowPlaceholder(int32_t nodeId);

    /**
     * @brief Transfer the original avoid area and avoid area type to the UIExtensionAbility
     *
     * @param avoidArea The original avoid area
     * @param type The original aovid areatype
     */
    void TransferOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type);

    bool NotifyOccupiedAreaChangeInfo(const sptr<Rosen::OccupiedAreaChangeInfo>& info);

    bool HandleUnfocusedModalUecBackPressed();

    bool IsLastModalUec(const RefPtr<FrameNode>& frameNode);

    void NotifySizeChangeReason(
        WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction);

    void AddAliveUIExtension(int32_t nodeId, const WeakPtr<SecurityUIExtensionPattern>& uiExtension);

    void UpdateSessionViewportConfig(const ViewportConfig& config);

    void DumpUIExt();

private:
    class UIExtensionIdUtility {
    public:
        UIExtensionIdUtility() = default;
        ~UIExtensionIdUtility() = default;
        UIExtensionIdUtility(const UIExtensionIdUtility&) = delete;
        UIExtensionIdUtility& operator=(const UIExtensionIdUtility&) = delete;

        int32_t ApplyExtensionId();
        void RecycleExtensionId(int32_t id);

    private:
        static std::bitset<UI_EXTENSION_ID_FIRST_MAX> idPool_;
        static std::mutex poolMutex_;
    };

    WeakPtr<UIExtensionPattern> uiExtensionFocused_;
    WeakPtr<SecurityUIExtensionPattern> securityUiExtensionFocused_;
    WeakPtr<SessionWrapper> sessionWrapper_;
    std::mutex aliveUIExtensionMutex_;
    std::map<int32_t, OHOS::Ace::WeakPtr<UIExtensionPattern>> aliveUIExtensions_;
    std::map<int32_t, OHOS::Ace::WeakPtr<SecurityUIExtensionPattern>> aliveSecurityUIExtensions_;
    std::unique_ptr<UIExtensionIdUtility> extensionIdUtility_ = std::make_unique<UIExtensionIdUtility>();
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MANAGER_H
