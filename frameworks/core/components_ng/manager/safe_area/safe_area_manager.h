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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SAFE_AREA_SAFE_AREA_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SAFE_AREA_SAFE_AREA_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/property/transition_property.h"

namespace OHOS::Ace::NG {
// SafeAreaManager stores layout information to apply SafeArea correctly.

struct WindowTypeConfig {
    WindowTypeConfig() = default;
    WindowTypeConfig(bool isAppWindow, bool isSystemWindow, bool isSceneBoardWindow)
        : isAppWindow(isAppWindow), isSystemWindow(isSystemWindow), isSceneBoardWindow(isSceneBoardWindow)
    {}
    bool isAppWindow = true;
    bool isSystemWindow = false;
    bool isSceneBoardWindow = false;
};

class SafeAreaManager : public virtual AceType {
    DECLARE_ACE_TYPE(SafeAreaManager, AceType);

public:
    SafeAreaManager() = default;
    ~SafeAreaManager() override = default;

    /**
     * @brief Check if the incoming safe area is identical to the system safe area
     *
     * @param safeArea The new system safe area.
     * @return True if the incoming safe area is identical to the current one, false otherwise.
     */
    bool CheckSystemSafeArea(const SafeAreaInsets& safeArea);

    /**
     * @brief Updates the system safe area.
     *
     * @param safeArea The new system safe area.
     * @return True if the system safe area was modified, false otherwise.
     */
    bool UpdateSystemSafeArea(const SafeAreaInsets& safeArea);

    /**
     * @brief Check if the incoming safe area is identical to the navigation indictor safe area.
     *
     * @param safeArea The new navigation indictor safe area.
     * @return True if the incoming safe area is identical to the current one, false otherwise.
     */
    bool CheckNavArea(const SafeAreaInsets& safeArea);

    /**
     * @brief Updates the navigation indictor safe area.
     *
     * @param safeArea The new navigation indictor safe area.
     * @return True if the system safe area was modified, false otherwise.
     */
    bool UpdateNavArea(const SafeAreaInsets& safeArea);

    /**
     * @brief Retrieves the system safe area insets.
     *
     * This function returns the safe area insets of the system, which represents the portion of the screen that is
     * covered by system UI elements such as the status bar or navigation bar.
     *
     * @return The system safe area insets.
     */
    SafeAreaInsets GetSystemSafeArea() const;

    /**
     * @brief Cut the incoming area with root size, then check if the result is identical to the cutout safe area.
     *
     * @param safeArea The SafeAreaInsets representing the new cutout safe area, which would be modified.
     * @return True if the incoming safe area is identical to the current one, false otherwise.
     */
    bool CheckCutoutSafeArea(
        const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize = NG::OptionalSize<uint32_t>());

    /**
     * @brief Updates the cutout safe area.
     *
     * This function is responsible for updating the cutout safe area based on the provided SafeAreaInsets.
     *
     * @param safeArea The SafeAreaInsets representing the new cutout safe area.
     * @return true if the cutout safe area was successfully updated, false otherwise.
     */
    bool UpdateCutoutSafeArea(
        const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize = NG::OptionalSize<uint32_t>());

    /**
     * @brief Retrieves the safe area insets that account for any cutout areas on the screen.
     *
     * @return The safe area insets that account for any cutout areas on the screen.
     */
    SafeAreaInsets GetCutoutSafeArea() const;

    bool UpdateScbSystemSafeArea(const SafeAreaInsets& safeArea);

    bool UpdateScbCutoutSafeArea(
        const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize = NG::OptionalSize<uint32_t>());

    bool UpdateScbNavSafeArea(const SafeAreaInsets& safeArea);

    /**
     * @brief Retrieves the safe area insets combining System and Cutout.
     *
     * @return The System & Cutout safe area insets.
     */
    SafeAreaInsets GetSafeArea() const;

    /**
     * @brief Retrieves the safe area insets only System.
     *
     * @return The System safe area insets.
     */
    SafeAreaInsets GetSafeAreaWithoutCutout() const;

    /**
     * @brief Updates the safe area to accommodate the keyboard.
     *
     * This function is called to update the safe area when the keyboard is shown or hidden.
     *
     * @param keyboardHeight The height of the keyboard in pixels.
     * @return true if the safe area was modified, false otherwise.
     */
    bool UpdateKeyboardSafeArea(float keyboardHeight, std::optional<uint32_t> rootHeight = std::nullopt);

    /**
     * @brief Retrieves the inset of the safe area caused by the keyboard.
     *
     * @return The inset of the safe area caused by the keyboard.
     */
    SafeAreaInsets::Inset GetKeyboardInset() const
    {
        if (keyboardAvoidMode_ == KeyBoardAvoidMode::NONE) {
            SafeAreaInsets::Inset inset;
            return inset;
        }
        return keyboardInset_;
    }

    void UpdateKeyboardOffset(float offset)
    {
        keyboardOffset_ = offset;
    }

    float GetKeyboardOffset(bool withoutProcess = false) const;

    float GetKeyboardOffsetDirectly() const
    {
        return keyboardOffset_;
    }

    float GetRawKeyboardHeight() const
    {
        return rawKeyboardHeight_;
    }

    void SetRawKeyboardHeight(float height)
    {
        rawKeyboardHeight_ = height;
    }

    bool KeyboardSafeAreaEnabled() const
    {
        return keyboardSafeAreaEnabled_;
    }

    SafeAreaInsets GetCombinedSafeArea(const SafeAreaExpandOpts& opts) const;

    const std::set<WeakPtr<FrameNode>>& GetGeoRestoreNodes() const
    {
        return geoRestoreNodes_;
    }

    void AddGeoRestoreNode(const WeakPtr<FrameNode>& node)
    {
        geoRestoreNodes_.insert(node);
    }

    void AddNeedExpandNode(const WeakPtr<FrameNode>& node)
    {
        needExpandNodes_.insert(node);
    }

    std::vector<WeakPtr<FrameNode>> GetExpandNodeSet();

    bool AddNodeToExpandListIfNeeded(const WeakPtr<FrameNode>& node);

    void ClearNeedExpandNode()
    {
        needExpandNodes_.clear();
    }

    void RemoveRestoreNode(const WeakPtr<FrameNode>& node)
    {
        geoRestoreNodes_.erase(node);
    }

    RefPtr<InterpolatingSpring> GetSafeAreaCurve() const
    {
        return safeAreaCurve_;
    }
    void ExpandSafeArea();

    OffsetF GetWindowWrapperOffset();

    SafeAreaInsets GetSafeAreaWithoutProcess() const;

    SafeAreaInsets GetScbSafeArea() const;

    bool SetIsFullScreen(bool value);
    bool SetIsNeedAvoidWindow(bool value);
    bool SetIgnoreSafeArea(bool value);
    bool SetKeyBoardAvoidMode(KeyBoardAvoidMode value);
    KeyBoardAvoidMode GetKeyBoardAvoidMode();
    bool IsIgnoreSafeArea()
    {
        return ignoreSafeArea_;
    }
    bool IsNeedAvoidWindow()
    {
        return isNeedAvoidWindow_;
    }
    bool IsFullScreen()
    {
        return isFullScreen_;
    }
    bool SetIsAtomicService(bool value);
    bool IsAtomicService() const;

    float GetSafeHeight() const
    {
        Dimension safeDistance = 16.0_vp;
        return safeDistance.ConvertToPx();
    }

    void SetLastKeyboardPoistion(float position)
    {
        lastKeyboardY_ = position;
    }

    float GetLastKeyboardPoistion() const
    {
        return lastKeyboardY_;
    }

    bool IsSafeAreaValid() const;

    // check if the page node needs to be avoid keyboard
    bool CheckPageNeedAvoidKeyboard(const RefPtr<FrameNode>& frameNode);

    PaddingPropertyF SafeAreaToPadding(bool withoutProcess = false);

    void SetWindowTypeConfig(bool isAppWindow, bool isSystemWindow, bool isSceneBoardWindow)
    {
        windowTypeConfig_ = WindowTypeConfig(isAppWindow, isSystemWindow, isSceneBoardWindow);
    }

    WindowTypeConfig GetWindowTypeConfig()
    {
        return windowTypeConfig_;
    }

    uint32_t GetkeyboardHeightConsideringUIExtension()
    {
        return keyboardHeightConsideringUIExtension_;
    }
    void SetkeyboardHeightConsideringUIExtension(uint32_t height)
    {
        if (keyboardHeightConsideringUIExtension_ != height) {
            for (const auto& [nodeId, callback] : keyboardChangeCbsConsideringUIExt_) {
                if (callback) {
                    callback();
                }
            }
            keyboardHeightConsideringUIExtension_ = height;
        }
    }
    void AddKeyboardChangeCallbackConsideringUIExt(int32_t nodeId, const std::function<void()>& callback)
    {
        keyboardChangeCbsConsideringUIExt_[nodeId] = callback;
    }
    void RemoveKeyboardChangeCallbackConsideringUIExt(int32_t nodeId)
    {
        keyboardChangeCbsConsideringUIExt_.erase(nodeId);
    }

private:
    bool isAtomicService_ = false;

    // app window is full screen
    // todo: remove and only use isNeedAvoidWindow_
    bool isFullScreen_ = false;

    /**
     * @brief Indicates whether the UI within the current window type needs to avoid SafeAreaInsets.
     */
    bool isNeedAvoidWindow_ = false;

    /**
     * @brief Indicates whether to ignore the SafeAreaInsets, specified by the developer from frontend.
     */
    bool ignoreSafeArea_ = false;

    /**
     * @brief Indicates whether the keyboard safe area is enabled. When enabled, UI avoids the keyboard inset and the
     * Page is compressed when the keyboard is up. When disabled, the size of Page doesn't change, but Page would
     * offset vertically according to [keyboardOffset_] when [keyboardAvoidMode_] is OFFSET or stay still when
     * [keyboardAvoidMode_] is NONE.
     */
    bool keyboardSafeAreaEnabled_ = false;

    KeyBoardAvoidMode keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;

    SafeAreaInsets systemSafeArea_;
    SafeAreaInsets cutoutSafeArea_;
    SafeAreaInsets navSafeArea_;
    // keyboard is bottom direction only
    SafeAreaInsets::Inset keyboardInset_;

    std::optional<SafeAreaInsets> scbSystemSafeArea_;
    std::optional<SafeAreaInsets> scbCutoutSafeArea_;
    std::optional<SafeAreaInsets> scbNavSafeArea_;
    
    WindowTypeConfig windowTypeConfig_;

    /**
     * @brief A set of weak pointers to FrameNode objects whose geometry info are saved before their SafeArea
     * expansion. The geometry info of these nodes need to be restored when their next Layout task begins.
     */
    std::set<WeakPtr<FrameNode>> geoRestoreNodes_;

    struct DepthCompare {
        bool operator()(const WeakPtr<FrameNode>& a, const WeakPtr<FrameNode>& b) const
        {
            auto ptrA = a.Upgrade();
            auto ptrB = b.Upgrade();
            if (!ptrA || !ptrB) {
                return false;
            }
            if (ptrA->GetDepth() < ptrB->GetDepth()) {
                return true;
            }
            if (ptrA->GetDepth() == ptrB->GetDepth()) {
                return ptrA < ptrB;
            }
            return false;
        }
    };
    std::set<WeakPtr<FrameNode>, DepthCompare> needExpandNodes_;
    // amount of offset to apply to Page when keyboard is up
    float keyboardOffset_ = 0.0f;

    float lastKeyboardY_ = 0.0f;
    float rawKeyboardHeight_ = 0.0f;

    static constexpr float SAFE_AREA_VELOCITY = 0.0f;
    static constexpr float SAFE_AREA_MASS = 1.0f;
    static constexpr float SAFE_AREA_STIFFNESS = 228.0f;
    static constexpr float SAFE_AREA_DAMPING = 30.0f;
    RefPtr<InterpolatingSpring> safeAreaCurve_ = AceType::MakeRefPtr<InterpolatingSpring>(
        SAFE_AREA_VELOCITY, SAFE_AREA_MASS, SAFE_AREA_STIFFNESS, SAFE_AREA_DAMPING);

    uint32_t keyboardHeightConsideringUIExtension_ = 0;
    std::unordered_map<int32_t, std::function<void()>> keyboardChangeCbsConsideringUIExt_;

    ACE_DISALLOW_COPY_AND_MOVE(SafeAreaManager);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SAFE_AREA_SAFE_AREA_MANAGER_H
