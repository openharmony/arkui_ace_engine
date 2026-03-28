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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H

#include <cstddef>
#include <optional>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/properties/text_enums.h"
#include "interfaces/inner_api/ace/modal_ui_extension_config.h"

namespace OHOS::Ace::NG {
/**
 * The structure of Atomic Service (install free):
 * |--AtomicService(Column)
 *   |--JsView
 *     |--Stage
 *     |--MenuBarRow
 *       |--MenuBar
 *          |--menuButton
 *          |--divider
 *          |--closeButton
 * |--ModalPage(UEC)
 */

using RectChangeFunc = std::function<void(const RectF& oldRect, const RectF& rect)>;
using RectCallbackDeleter = void(*)(void*);

class ACE_FORCE_EXPORT AppBarView : public Referenced {
public:
    AppBarView() = default;
    RefPtr<FrameNode> Create(const RefPtr<FrameNode>& stage);
    RefPtr<Pattern> GetAtomicServicePattern();
    void SetVisible(bool visible) {}
    void SetRowColor(const std::optional<Color>& color) {}
    void SetContent(const std::string& content) {}
    void SetFontStyle(Ace::FontStyle fontStyle) {}
    void SetIconColor(const std::optional<Color>& color) {}
    void SetStatusBarItemColor(bool isLight);
    std::optional<RectF> GetAppBarRect();
    void OnMenuClick();
    void OnCloseClick();
    void RequestAtomicServiceTerminate();
    void SetOnBackPressedConsumed();
    void CreateServicePanel(const std::string& appGalleryBundleName, const std::string& abilityName,
        std::map<std::string, std::string>& params);
#ifndef PREVIEW
    ModalUIExtensionCallbacks GetModalUIExtensionCallbacks(bool firstTry);
#endif
    static void BuildAppbar(RefPtr<PipelineBase> pipleline);
    static void RegistAppBarNodeBuilder(
        std::function<RefPtr<FrameNode>(NG::AppBarView* appBar, const RefPtr<FrameNode>& stage)> appBarNodeBuilder);
    static int32_t AddRectChangeListener(
        const RefPtr<PipelineContext>& pipelineContext, std::function<void(const RectF& rect)>&& listener);
    static void RemoveRectChangeListener(const RefPtr<PipelineContext>& pipelineContext, int32_t id);
    void SetMenuBarVisible(bool visible);
    void OnThirdCloseEvent();

    void SetLastRectChangeTime(int64_t time)
    {
        lastRectChangeTime_ = time;
    }
    int64_t GetLastRectChangeTime() const
    {
        return lastRectChangeTime_;
    }

    void SetRectChangeCallbackContext(void* ctx, RectCallbackDeleter deleter) {
        rectChangeCallbackRef_ = ctx;
        rectCallbackDeleter_ = deleter;
    }
    void* GetRectChangeCallbackContext() const
    {
        return rectChangeCallbackRef_;
    }

    void SetRectChangeCallback(RectChangeFunc&& callback);
protected:
    virtual ~AppBarView()
    {
        if (rectChangeCallbackRef_ && rectCallbackDeleter_) {
            rectCallbackDeleter_(rectChangeCallbackRef_);
            rectChangeCallbackRef_ = nullptr;
            rectCallbackDeleter_ = nullptr;
        }
    }
private:
    RefPtr<FrameNode> BuildMenuBarRow();
    RefPtr<FrameNode> BuildMenuBar();
    RefPtr<FrameNode> BuildButton(bool isMenuButton);
    RefPtr<FrameNode> BuildIcon(bool isMenuIcon);
    RefPtr<FrameNode> BuildDivider();
    void BindJSContainer();
    void BindMenuCallback(const RefPtr<FrameNode>& menuButton);
    void BindCloseCallback(const RefPtr<FrameNode>& closeButton);
    void CreateServicePanel(bool firstTry);
    void DestroyServicePanel();
    void FireExtensionHostParams();
    void UpdateVisibilityOfMenuBarRow(const RefPtr<FrameNode>& menubarRow, const RefPtr<Container>& container);
    void InitAbilityContextCallback();
    void FireAbilityCloseEvent();
    static void InitUIExtensionNode(const RefPtr<FrameNode>& uiExtNode);
    static void InitAccessibility(RefPtr<UINode> uiNode);
    void AddInnerOnSizeChangeCallback(RefPtr<FrameNode> frameNode);
    int32_t sessionId_ = 0;

    WeakPtr<FrameNode> atomicService_;
    RefPtr<FrameNode> contentStage_;
    static std::function<RefPtr<FrameNode>(NG::AppBarView* appBar, const RefPtr<FrameNode>& stage)> appBarNodeBuilder_;
    int64_t lastRectChangeTime_ = 0;
    void* rectChangeCallbackRef_ = nullptr;
    RectCallbackDeleter rectCallbackDeleter_ = nullptr;
    RectChangeFunc rectChangeCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H
