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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/stack/stack_model.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace
class PanelPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: SlidingPanelLayoutPropertyTest001
 * @tc.desc: Set show value into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest001, TestSize.Level1)
{
    DialogProperties props = {
        .type = DialogType::COMMON,
        .alignment = DialogAlignment::CENTER,
        .useCustom = true,
    };
    DialogView::CreateDialogNode(props, nullptr);
}


} // namespace OHOS::Ace::NG
