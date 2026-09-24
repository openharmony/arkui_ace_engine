/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <limits>
#include <vector>

#include "gtest/gtest.h"

#include "frameworks/bridge/codec/byte_buffer_operator.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {

std::vector<uint8_t> CreateLengthBuffer(int32_t length)
{
    std::vector<uint8_t> buffer;
    ByteBufferWriter writer(buffer);
    writer.WriteData(length);
    return buffer;
}

} // namespace

class ByteBufferOperatorTest : public testing::Test {};

/**
 * @tc.name: ByteBufferOperatorTest001
 * @tc.desc: Reject an int16 array length whose byte count would bypass a uint32 boundary check.
 * @tc.type: FUNC
 */
HWTEST_F(ByteBufferOperatorTest, ByteBufferOperatorTest001, TestSize.Level1)
{
    const auto buffer = CreateLengthBuffer(std::numeric_limits<int32_t>::max());
    ByteBufferReader reader(buffer);
    std::vector<int16_t> result;

    EXPECT_FALSE(reader.ReadData(result));
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ByteBufferOperatorTest002
 * @tc.desc: Reject an int32 array length whose byte count truncates to zero in uint32.
 * @tc.type: FUNC
 */
HWTEST_F(ByteBufferOperatorTest, ByteBufferOperatorTest002, TestSize.Level1)
{
    constexpr int32_t overflowLength = 0x40000000;
    const auto buffer = CreateLengthBuffer(overflowLength);
    ByteBufferReader reader(buffer);
    std::vector<int32_t> result;

    EXPECT_FALSE(reader.ReadData(result));
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ByteBufferOperatorTest003
 * @tc.desc: Reject an int32 array length that causes both truncation and addition wraparound in uint32.
 * @tc.type: FUNC
 */
HWTEST_F(ByteBufferOperatorTest, ByteBufferOperatorTest003, TestSize.Level1)
{
    const auto buffer = CreateLengthBuffer(std::numeric_limits<int32_t>::max());
    ByteBufferReader reader(buffer);
    std::vector<int32_t> result;

    EXPECT_FALSE(reader.ReadData(result));
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ByteBufferOperatorTest004
 * @tc.desc: Decode valid arrays after applying overflow-safe boundary checks.
 * @tc.type: FUNC
 */
HWTEST_F(ByteBufferOperatorTest, ByteBufferOperatorTest004, TestSize.Level1)
{
    const std::vector<int16_t> source = { 1, -2, 3 };
    std::vector<uint8_t> buffer;
    ByteBufferWriter writer(buffer);
    writer.WriteData(source);

    ByteBufferReader reader(buffer);
    std::vector<int16_t> result;

    EXPECT_TRUE(reader.ReadData(result));
    EXPECT_EQ(result, source);
}

} // namespace OHOS::Ace::Framework
