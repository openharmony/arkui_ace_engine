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

#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/ng/point_t.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class UIExtensionPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};
} // namespace OHOS::Ace::NG
