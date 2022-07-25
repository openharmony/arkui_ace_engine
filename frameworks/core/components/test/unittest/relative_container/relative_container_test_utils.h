/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_RELATIVE_CONTAINER_RELATIVE_CONTAINER_TEST_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_RELATIVE_CONTAINER_RELATIVE_CONTAINER_TEST_UTILS_H

#include "core/components/box/render_box.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/flex/render_flex_item.h"
#include "core/components/relative_container/render_relative_container.h"
#include "core/components/root/render_root.h"
#include "core/components/text/render_text.h"

namespace OHOS::Ace {
class MockRenderRoot final : public RenderRoot {
    DECLARE_ACE_TYPE(MockRenderRoot, RenderRoot);
};

class MockRenderRelativeContainer final : public RenderRelativeContainer {
    DECLARE_ACE_TYPE(MockRenderRelativeContainer, RenderRelativeContainer);
};

class MockRenderBox final : public RenderBox {
    DECLARE_ACE_TYPE(MockRenderBox, RenderBox);
};

class RelativeContainerTestUtils {
public:
    static RefPtr<RenderRoot> CreateRenderRoot();
    static RefPtr<RenderRelativeContainer> CreateRenderRelativeContainer(const RefPtr<PipelineContext>& context);
    static RefPtr<RenderBox> CreateRenderBox(
        const double width, const double height, const RefPtr<PipelineContext>& context);
    static void AddAlignRule(const std::string id, const AlignDirection& direction,
        const HorizontalAlign& horizontalRule, std::map<AlignDirection, AlignRule>& alignRules);
    static void AddAlignRule(const std::string id, const AlignDirection& direction, const VerticalAlign& verticalRule,
        std::map<AlignDirection, AlignRule>& alignRules);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_RELATIVE_CONTAINER_RELATIVE_CONTAINER_TEST_UTILS_H