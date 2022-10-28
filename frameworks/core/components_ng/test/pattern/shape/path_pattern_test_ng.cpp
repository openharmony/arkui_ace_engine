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

#include <string>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"
#include "core/components_ng/pattern/shape/path_paint_property.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {

const std::string PATH_CMD = "M150 0 L300 300 L0 300 Z";

} // namespace

class PathPatternTestNg : public BaseShapePatternTestNg {};

/**
 * @tc.name: Creator001
 * @tc.desc: create path with width and height
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, Creator001, TestSize.Level1)
{
    PathModelNG().Create();
    CheckSize();
}

/**
 * @tc.name: Creator002
 * @tc.desc: create path with no width or height
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, Creator002, TestSize.Level1)
{
    PathModelNG().Create();
    CheckNoSize();
}

/**
 * @tc.name: PathPaintProperty001
 * @tc.desc: create path with cmd
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, PathPaintProperty001, TestSize.Level1)
{
    PathModelNG().Create();
    PathModelNG().SetCommands(PATH_CMD);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto pathPaintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    EXPECT_EQ(pathPaintProperty->HasCommands(), true);
    EXPECT_STREQ(pathPaintProperty->GetCommandsValue().c_str(), PATH_CMD.c_str());
}

} // namespace OHOS::Ace::NG