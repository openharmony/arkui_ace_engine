/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "frameworks/core/common/sharedata/share_data.h"
#include "base/memory/ace_type.h"

#include <functional>
#include <set>
#include <string>
#include <map>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ShareDataTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToShareDataTest001
 * @tc.desc: Test cast to sharedata.
 * @tc.type: FUNC
 */
HWTEST_F(ShareDataTest, CastToShareDataTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the InsertBuffer and set bufferId is 0, set dataArray is {1, 2}.
     * @tc.steps: step2. call the GetShareBufferById.
     * @tc.expected: step2. return expect result.
     */
    int32_t bufferId = 0;
    int32_t errorBufferId = 1;

    std::shared_ptr<std::vector<uint8_t>> dataArray = std::make_shared<std::vector<uint8_t>>();
    dataArray->push_back(1);
    dataArray->push_back(2);

    ShareData::InsertBuffer(bufferId, dataArray);
    std::shared_ptr<std::vector<uint8_t>> retData = ShareData::GetShareBufferById(bufferId);
    EXPECT_EQ(retData->at(0), 1);

    /**
     * @tc.steps: step3. call the ReleaseShareBufferById.
     * @tc.steps: step4. call the GetShareBufferById.
     * @tc.expected: step4. the return value is null.
     */
    ShareData::ReleaseShareBufferById(bufferId);
    std::shared_ptr<std::vector<uint8_t>> retEraseData = ShareData::GetShareBufferById(bufferId);
    EXPECT_EQ(retEraseData, nullptr);

    /**
     * @tc.steps: step5. call the GetShareBufferById and set the wrong id.
     * @tc.expected: step5. the return value is null.
     */
    std::shared_ptr<std::vector<uint8_t>> retErrorData = ShareData::GetShareBufferById(errorBufferId);
    EXPECT_EQ(retErrorData, nullptr);

    /**
     * @tc.steps: step6. call the ReleaseShareBufferById and set the wrong id.
     * @tc.expected: step6. the id is not found.
     */
    ShareData::ReleaseShareBufferById(errorBufferId);
}
} // namespace OHOS::Ace
