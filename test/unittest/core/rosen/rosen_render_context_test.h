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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H

#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/render/adapter/background_modifier.h"
#include "core/components_ng/render/adapter/focus_state_modifier.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/transition_modifier.h"
#include "core/components_ng/pattern/particle/particle_pattern.h"
#include "frameworks/core/components_ng/render/image_painter.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
namespace {} // namespace
using namespace testing;
using namespace testing::ext;
class RosenRenderContextTest : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RosenRenderContext> InitRosenRenderContext(const RefPtr<FrameNode>& frameNode);
    RefPtr<RosenRenderContext> InitRosenRenderContext(const RefPtr<FrameNode>& frameNode,
        const RenderContext::ContextType& type);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H
