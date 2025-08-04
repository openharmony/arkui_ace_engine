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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class ScrollPatternMock : public ScrollPattern {
public:
    bool isBegin = false;
    bool isEnd = false;

    bool IsAtTop() const override
    {
        return isBegin;
    }

    bool IsAtBottom() const override
    {
        return isEnd;
    }
};

class SwiperPatternMock : public SwiperPattern {
public:
    bool isBegin = false;
    bool isEnd = false;

    bool IsAtStart() const override
    {
        return isBegin;
    }

    bool IsAtEnd() const override
    {
        return isEnd;
    }
};

class ScrollableTargetInfoAccessorTest : public AccessorTestBase<GENERATED_ArkUIScrollableTargetInfoAccessor,
    &GENERATED_ArkUIAccessors::getScrollableTargetInfoAccessor, ScrollableTargetInfoPeer> {
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTargetInfoAccessorTest, ctorTest, TestSize.Level1)
{
    auto peer1 = reinterpret_cast<ScrollableTargetInfoPeer*>(this->accessor_->construct());
    auto peer2 = reinterpret_cast<ScrollableTargetInfoPeer*>(this->accessor_->construct());
    auto peer3 = reinterpret_cast<ScrollableTargetInfoPeer*>(this->accessor_->construct());
    ASSERT_NE(peer1, nullptr);
    ASSERT_NE(peer2, nullptr);
    ASSERT_NE(peer3, nullptr);
    EXPECT_EQ(peer1->GetPattern(), nullptr);
    EXPECT_EQ(peer2->GetPattern(), nullptr);
    EXPECT_EQ(peer3->GetPattern(), nullptr);
    finalyzer_(peer1);
    finalyzer_(peer2);
    finalyzer_(peer3);
}

/**
 * @tc.name: isBeginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTargetInfoAccessorTest, isBeginTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isBegin, nullptr);
    EXPECT_FALSE(accessor_->isBegin(peer_));
    auto scrollablePattern = AceType::MakeRefPtr<ScrollPatternMock>();
    peer_->SetPattern(scrollablePattern);
    EXPECT_FALSE(accessor_->isBegin(peer_));
    scrollablePattern->isBegin = true;
    EXPECT_TRUE(accessor_->isBegin(peer_));
    auto swiperPattern = AceType::MakeRefPtr<SwiperPatternMock>();
    peer_->SetPattern(swiperPattern);
    EXPECT_FALSE(accessor_->isBegin(peer_));
    swiperPattern->isBegin = true;
    EXPECT_TRUE(accessor_->isBegin(peer_));
}

/**
 * @tc.name: isEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTargetInfoAccessorTest, isEndTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isEnd, nullptr);
    EXPECT_FALSE(accessor_->isEnd(peer_));
    auto scrollablePattern = AceType::MakeRefPtr<ScrollPatternMock>();
    peer_->SetPattern(scrollablePattern);
    EXPECT_FALSE(accessor_->isEnd(peer_));
    scrollablePattern->isEnd = true;
    EXPECT_TRUE(accessor_->isEnd(peer_));
    auto swiperPattern = AceType::MakeRefPtr<SwiperPatternMock>();
    peer_->SetPattern(swiperPattern);
    EXPECT_FALSE(accessor_->isEnd(peer_));
    swiperPattern->isEnd = true;
    EXPECT_TRUE(accessor_->isEnd(peer_));
}
} // namespace OHOS::Ace::NG
