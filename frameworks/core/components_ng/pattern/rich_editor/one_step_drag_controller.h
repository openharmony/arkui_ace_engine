/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_ONE_STEP_DRAG_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_ONE_STEP_DRAG_CONTROLLER_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
namespace {
using TagFilter = std::function<bool(const std::string&)>;
using Builder = std::function<void()>;
const TagFilter DEFAULT_FILTER = [](const std::string&) { return false; };
const TagFilter IMAGE_TAG_FILTER = [](const std::string& tag) { return tag == V2::IMAGE_ETS_TAG; };
const TagFilter PLACEHOLDER_TAG_FILTER = [](const std::string& tag) { return tag == V2::PLACEHOLDER_SPAN_ETS_TAG; };
}

class OneStepDragParam {
public:
    OneStepDragParam(const Builder& builder, const SelectMenuParam& selectMenuParam,
        TextSpanType spanType, TagFilter tagFilter);
    virtual ~OneStepDragParam() = default;
    virtual MenuParam GetMenuParam(const RefPtr<FrameNode>& frameNode) const = 0;
    virtual void EnableOneStepDrag(const RefPtr<FrameNode>& frameNode) = 0;
    virtual void EnableDrag(const RefPtr<FrameNode>& frameNode) const;
    void BindContextMenu(const RefPtr<FrameNode>& frameNode);
    void FillJsonValue(const std::unique_ptr<JsonValue>& jsonValue) const;
    void HandleDirtyNodes();
    inline void MarkDirtyNode(const WeakPtr<FrameNode>& dirtyFrameNode);

    const TextSpanType spanType_;
    const std::function<bool(const std::string&)> tagFilter_;

protected:
    Builder menuBuilder = nullptr;
    Builder previewBuilder = nullptr;
    std::function<void(int32_t, int32_t)> onAppear = nullptr;
    MenuParam menuParam;
    std::queue<WeakPtr<FrameNode>> dirtyFrameNodes;
};

class ImageOneStepDragParam : public OneStepDragParam {
public:
    ImageOneStepDragParam(const Builder& builder, const SelectMenuParam& selectMenuParam)
        : OneStepDragParam(builder, selectMenuParam, TextSpanType::IMAGE, IMAGE_TAG_FILTER) {}
    MenuParam GetMenuParam(const RefPtr<FrameNode>& frameNode) const override;
    void EnableOneStepDrag(const RefPtr<FrameNode>& frameNode) override;

private:
    float CalcImageScale(const RefPtr<ImageSpanNode>& imageNode) const;
};

class PlaceholderOneStepDragParam : public OneStepDragParam {
public:
    PlaceholderOneStepDragParam(const Builder& builder, const SelectMenuParam& selectMenuParam)
        : OneStepDragParam(builder, selectMenuParam, TextSpanType::BUILDER, PLACEHOLDER_TAG_FILTER) {}
    MenuParam GetMenuParam(const RefPtr<FrameNode>& frameNode) const override;
    void EnableDrag(const RefPtr<FrameNode>& frameNode) const override;
    void EnableOneStepDrag(const RefPtr<FrameNode>& frameNode) override;
};

class OneStepDragController {
public:
    OneStepDragController(const WeakPtr<RichEditorPattern>& pattern) : pattern_(pattern) {}
    static std::string GetJsonRange(TextSpanType spanType, const RefPtr<FrameNode>& frameNode);
    bool SetMenuParam(TextSpanType spanType, const Builder& builder, const SelectMenuParam& menuParam);
    void EnableOneStepDrag(TextSpanType spanType, const RefPtr<FrameNode>& frameNode);
    void CopyDragCallback(TextSpanType spanType, const RefPtr<FrameNode>& frameNode);
    void SetEnableEventResponse(bool isEnable);
    void FillJsonValue(const std::unique_ptr<JsonValue>& jsonValue);
    void MarkDirtyNode(const WeakPtr<ImageSpanNode>& dirtyFrameNode);
    void HandleDirtyNodes();

private:
    const std::unique_ptr<OneStepDragParam>& GetDragParam(TextSpanType spanType) const;
    const std::unique_ptr<OneStepDragParam>& CreateDragParam(TextSpanType spanType, const Builder& builder,
        const SelectMenuParam& menuParam);

private:
    const std::unique_ptr<OneStepDragParam> invalidParam = nullptr;
    WeakPtr<RichEditorPattern> pattern_;
    std::unique_ptr<OneStepDragParam> imageDragParam_ = nullptr;
    std::unique_ptr<OneStepDragParam> placeholderDragParam_ = nullptr;
    bool isEnableEventResponse_ = true;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_ONE_STEP_DRAG_CONTROLLER_H