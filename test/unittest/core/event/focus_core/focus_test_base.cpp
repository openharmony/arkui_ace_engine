/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"
#include "test/unittest/core/event/focus_core/focus_test_base.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

RefPtr<FrameNode> FocusTestBaseNg::CreateRootNode()
{
    auto rootNode = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    return rootNode;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNode(const std::string& tag)
{
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<FocusTestPattern>());
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNodeWithFocusPattern(const std::string& tag,
    FocusType focusType, bool focusable)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable});
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNodeWithFocusPatternAndAlgorithm(const std::string& tag,
    FocusType focusType, bool focusable, ScopeFocusAlgorithm algorithm)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable});
    focusTestPattern->SetScopeFocusAlgorithm(algorithm);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNodeWithFocusPattern(const std::string& tag,
    FocusType focusType, bool focusable, FocusStyleType styleType)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNodeWithFocusPatternAndAlgorithm(const std::string& tag,
    FocusType focusType, bool focusable, FocusStyleType styleType, ScopeFocusAlgorithm algorithm)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    focusTestPattern->SetScopeFocusAlgorithm(algorithm);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNodeWithFocusPattern(const std::string& tag,
    FocusType focusType, bool focusable, FocusStyleType styleType, const FocusPaintParam& paintParams)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateNodeWithFocusPatternAndAlgorithm(const std::string& tag,
    FocusType focusType, bool focusable, FocusStyleType styleType,
    const FocusPaintParam& paintParams, ScopeFocusAlgorithm algorithm)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    focusTestPattern->SetScopeFocusAlgorithm(algorithm);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateFocusViewWithFocusPattern(const std::string& tag,
    std::list<int32_t>& list, FocusType focusType, bool focusable)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusViewTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable});
    focusTestPattern->SetRouteOfFirstScope(list);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateFocusViewWithFocusPatternAndAlgorithm(const std::string& tag,
    std::list<int32_t>& list, FocusType focusType, bool focusable, ScopeFocusAlgorithm algorithm)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusViewTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable});
    focusTestPattern->SetScopeFocusAlgorithm(algorithm);
    focusTestPattern->SetRouteOfFirstScope(list);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateFocusViewWithFocusPattern(const std::string& tag,
    std::list<int32_t>& list, FocusType focusType, bool focusable, FocusStyleType styleType)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusViewTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    focusTestPattern->SetRouteOfFirstScope(list);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateFocusViewWithFocusPatternAndAlgorithm(const std::string& tag,
    std::list<int32_t>& list, FocusType focusType, bool focusable,
    FocusStyleType styleType, ScopeFocusAlgorithm algorithm)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusViewTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    focusTestPattern->SetScopeFocusAlgorithm(algorithm);
    focusTestPattern->SetRouteOfFirstScope(list);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateFocusViewWithFocusPattern(const std::string& tag,
    std::list<int32_t>& list, FocusType focusType, bool focusable,
    FocusStyleType styleType, const FocusPaintParam& paintParams)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusViewTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    focusTestPattern->SetRouteOfFirstScope(list);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

RefPtr<FrameNode> FocusTestBaseNg::CreateFocusViewWithFocusPatternAndAlgorithm(const std::string& tag,
    std::list<int32_t>& list, FocusType focusType, bool focusable, FocusStyleType styleType,
    const FocusPaintParam& paintParams, ScopeFocusAlgorithm algorithm)
{
    auto focusTestPattern = AceType::MakeRefPtr<FocusViewTestPattern>();
    focusTestPattern->SetFocusPattern({focusType, focusable, styleType});
    focusTestPattern->SetScopeFocusAlgorithm(algorithm);
    focusTestPattern->SetRouteOfFirstScope(list);
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), focusTestPattern);
    return node;
}

bool FocusTestBaseNg::InitFocusTestBaseNG()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    focusManager_ = context->GetOrCreateFocusManager();
    CHECK_NULL_RETURN(focusManager_, false);
    return true;
}
} // namespace OHOS::Ace::NG
