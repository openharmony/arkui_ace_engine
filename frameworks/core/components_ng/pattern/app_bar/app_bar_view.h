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

class ACE_FORCE_EXPORT AppBarView : public Referenced {
public:
    AppBarView() = default;
    RefPtr<FrameNode> Create(const RefPtr<FrameNode>& stage);
    void SetVisible(bool visible) {}
    void SetRowColor(const std::optional<Color>& color) {}
    void SetContent(const std::string& content) {}
    void SetFontStyle(Ace::FontStyle fontStyle) {}
    void SetIconColor(const std::optional<Color>& color) {}
    void SetStatusBarItemColor(bool isLight);
    std::optional<RectF> GetAppBarRect();
    void AddContentToJSContainer();
    void OnMenuClick();
    void OnCloseClick();
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
    static void InitUIExtensionNode(const RefPtr<FrameNode>& uiExtNode);
    int32_t sessionId_ = 0;

    WeakPtr<FrameNode> atomicService_;
    RefPtr<FrameNode> contentStage_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H
