/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PREVIEW_MENU_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PREVIEW_MENU_CONTROLLER_H

#include "ui/base/referenced.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/menu_property.h"

namespace OHOS::Ace::NG {
using AIPreviewMenuErrorCallback =
    std::function<void(int32_t code, const std::string& name, const std::string& message)>;
class PreviewMenuController : public virtual AceType {
    DECLARE_ACE_TYPE(PreviewMenuController, AceType);

public:
    PreviewMenuController(const WeakPtr<TextPattern>& pattern);
    virtual ~PreviewMenuController() = default;
    void BindContextMenu(const RefPtr<FrameNode>& targetNode, bool isShow = true);
    void ClosePreviewMenu()
    {
        isShow_ = false;
    }

    bool IsPreviewMenuShow()
    {
        return isShow_;
    }

    static void CreatePreviewMenu(
        TextDataDetectType type, const std::string& content, std::function<void()> disappearCallback);

private:
    void CreateAIEntityMenu();
    static void CreateContactErrorNode(
        const RefPtr<FrameNode>& previewNode, const std::string& content, std::function<void()>&& disappearCallback);
    static void CreateLinkingErrorNode(
        const RefPtr<FrameNode>& previewNode, TextDataDetectType type, std::function<void()>&& disappearCallback);
    static RefPtr<FrameNode> CreateLinkingPreviewNode();
    static RefPtr<FrameNode> CreateContactPreviewNode();
    static void UpdateNonLinkNodeProperty(const RefPtr<ImageLayoutProperty>& imageLayoutProperty,
        const RefPtr<TextLayoutProperty>& textLayoutProperty, const std::string& content);
    static void UpdateLinkNodeProperty(const RefPtr<TextLayoutProperty>& textLayoutProperty, TextDataDetectType type);
    static RefPtr<FrameNode> CreatePreview(TextDataDetectType type);
    static void MountErrorNode(const RefPtr<FrameNode>& previewNode, TextDataDetectType type,
        const std::string& content, std::function<void()> disappearCallback);
    static AIPreviewMenuErrorCallback GetErrorCallback(const RefPtr<FrameNode>& previewNode, TextDataDetectType type,
        const std::string& content, std::function<void()>&& disappearCallback);
    std::function<void()> GetDisappearCallback();
    static std::function<void()> GetLinkingCallback(const std::string& appName);

    MenuParam menuParam_;
    std::function<void()> menuBuilder_ = nullptr;
    std::function<void()> previewBuilder_ = nullptr;

    WeakPtr<TextPattern> pattern_;
    bool isShow_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(PreviewMenuController);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PREVIEW_MENU_CONTROLLER_H