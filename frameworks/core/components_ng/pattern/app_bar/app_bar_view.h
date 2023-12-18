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
 *   |--AppBar(Row)
 *
 *   |--Stage
 *     |--Page
 */

/**
 * The structure of AppBar:+
 * |--AppBar
 *   |--row
 *     |--BackButton
 *     |--Title
 *   |FaButton
 */
class ACE_FORCE_EXPORT AppBarView : public Referenced {
public:
    AppBarView() = default;
    explicit AppBarView(const RefPtr<FrameNode>& atom)
    {
        atom_ = atom;
    }
    static RefPtr<FrameNode> Create(RefPtr<FrameNode>& content);
    void SetVisible(bool visible);
    void SetRowColor(const std::optional<Color>& color);
    void SetContent(const std::string& content);
    void SetFontStyle(Ace::FontStyle fontStyle);
    void SetIconColor(const std::optional<Color>& color);
    void iniBehavior();
    void SetRowWidth(const Dimension& positionX);
    void IniColor();

private:
    static RefPtr<FrameNode> BuildBarTitle();
    static RefPtr<FrameNode> BuildIconButton(
        InternalResource::ResourceId icon, GestureEventFunc&& clickCallback, bool isBackButton);
    static void BindContentCover(const RefPtr<FrameNode>& targetNode);
    static RefPtr<FrameNode> BuildFaButton();
    static void SetEachIconColor(
        RefPtr<FrameNode> icon, const std::optional<Color>& color, InternalResource::ResourceId image);
    RefPtr<FrameNode> atom_;
    RefPtr<FrameNode> GetFaButton();
    
    bool isVisibleSetted = false;
    bool isRowColorSetted = false;
    bool isIconColorSetted = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H
