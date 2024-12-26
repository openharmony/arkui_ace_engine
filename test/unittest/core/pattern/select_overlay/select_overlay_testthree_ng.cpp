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

#include "gtest/gtest.h"

#define protected public
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class SelectOverlayPatternTestNg : public testing::Test {
public:
};

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse001
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse001, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(40.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_TRUE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse002
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse002, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(40.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.info_->handleReverse = true;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_TRUE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse003
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse003, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(40.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.info_->handleReverse = true;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_FALSE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse004
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse004, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(40.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_FALSE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternUpdateAncestorViewPort001
 * @tc.desc: test UpdateAncestorViewPort
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternUpdateAncestorViewPort001, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(40.0f, 30.0f, 120.0f, 180.0f);
    std::optional<RectF> ancestorViewPort = rectF1;
    selectOverlayPattern.info_->ancestorViewPort = rectF2;
    selectOverlayPattern.UpdateAncestorViewPort(ancestorViewPort);
    EXPECT_EQ(selectOverlayPattern.info_->ancestorViewPort, ancestorViewPort);
}

/**
 * @tc.name: SelectOverlayPatternUpdateAncestorViewPort002
 * @tc.desc: test UpdateAncestorViewPort
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternUpdateAncestorViewPort002, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    std::optional<RectF> ancestorViewPort = rectF;
    selectOverlayPattern.info_->ancestorViewPort = rectF;
    selectOverlayPattern.UpdateAncestorViewPort(ancestorViewPort);
    EXPECT_EQ(selectOverlayPattern.info_->ancestorViewPort, ancestorViewPort);
}
} // namespace OHOS::Ace::NG