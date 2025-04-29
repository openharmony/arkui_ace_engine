/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_COMPONENT_IMPL_H
#define OHOS_ACE_COMPONENT_TEST_COMPONENT_IMPL_H

#include <vector>

#include "component_test/core/action.h"

#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::ComponentTest {

class ACE_FORCE_EXPORT ComponentTestComponentImpl final {
public:
    ComponentTestComponentImpl() = default;
    ~ComponentTestComponentImpl() = default;

    void TapImpl(ErrInfo& errInfo) const;
    void DoubleTapImpl(ErrInfo& errInfo) const;
    void PressImpl(ErrInfo& errInfo, uint32_t duration = PRESS_HOLD_MS) const;
    void PinchOutImpl(float scale, ErrInfo& errInfo) const;
    void PinchInImpl(float scale, ErrInfo& errInfo) const;
    void InputTextImpl(std::string text, ErrInfo& errInfo) const;
    void ClearTextImpl(ErrInfo& errInfo) const;
    void ScrollToTopImplAsync(uint32_t speed, std::function<void(ErrInfo errInfo)>&& callback) const;
    void ScrollToBottomImplAsync(uint32_t speed, std::function<void(ErrInfo errInfo)>&& callback) const;
    std::string GetIdImpl(ErrInfo& errInfo) const;
    std::string GetTextImpl(ErrInfo& errInfo) const;
    std::string GetTypeImpl(ErrInfo& errInfo) const;
    bool IsClickableImpl(ErrInfo& errInfo) const;
    bool IsLongPressableImpl(ErrInfo& errInfo) const;
    bool IsScrollableImpl(ErrInfo& errInfo) const;
    bool IsEnabledImpl(ErrInfo& errInfo) const;
    bool IsFocusedImpl(ErrInfo& errInfo) const;
    bool IsSelectedImpl(ErrInfo& errInfo) const;
    bool IsCheckedImpl(ErrInfo& errInfo) const;
    bool IsCheckableImpl(ErrInfo& errInfo) const;
    std::string GetInspectorInfoImpl(ErrInfo& errInfo) const;
    std::string GetInspectorTreeImpl(ErrInfo& errInfo) const;
    int32_t GetChildCountImpl(ErrInfo& errInfo) const;
    NG::RectF GetBoundsImpl(ErrInfo& errInfo) const;
    void SetUiNode(const RefPtr<NG::UINode> uiNode);
    void SetEffective();

private:
    RefPtr<NG::UINode> uiNode_ = nullptr;
    NG::RectF effective_ = {};
    void GetContextInfo(const RefPtr<NG::PipelineContext>& context, std::unique_ptr<JsonValue>& jsonRoot) const;
    void ScrollToBorderAsync(uint32_t speed, bool toTop, std::function<void(ErrInfo errInfo)>&& callback) const;
    void GetFrameNodeChildren(
        const RefPtr<NG::UINode>& uiNode, std::vector<RefPtr<NG::UINode>>& children, int32_t pageId) const;
    std::string GetChildrenInspectorInfo(
        std::vector<RefPtr<NG::UINode>> children, int32_t pageId, std::unique_ptr<JsonValue> jsonNode) const;
    void GetInspectorChildren(
        const RefPtr<NG::UINode>& parent, std::unique_ptr<JsonValue>& jsonNodeArray, int pageId) const;
    void GetSpanInspector(
        const RefPtr<NG::UINode>& parent, std::unique_ptr<JsonValue>& jsonNodeArray, int pageId) const;
    bool GenericClick(const TouchType touchType, uint32_t duration = PRESS_HOLD_MS) const;
    RefPtr<NG::FrameNode> GetFrameNode() const;
};

} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_COMPONENT_IMPL_H
