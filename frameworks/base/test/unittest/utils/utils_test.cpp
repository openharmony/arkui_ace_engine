/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <memory>
#include <atomic>
#include <chrono>
#include <ctime>
#include <regex>
#include <sys/time.h>

#include "gtest/gtest.h"

#include "base/utils/base_id.h"
#include "base/utils/date_util.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "base/utils/resource_configuration.h"
#include "base/utils/string_expression.h"
#include "base/utils/string_utils.h"
#include "base/utils/time_util.h"

#ifndef WINDOWS_PLATFORM
#include "securec.h"
#endif

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const uint32_t SET_YESR = 2022;
const uint32_t SET_MONTH = 10;
const uint32_t SET_DAY = 28;
const uint32_t DEFAULT_YEAR = 1900;
const uint32_t DEFAULT_MONTH = 0;
const uint32_t DEFAULT_DAY = 1;
const uint32_t DEFAULT_WEEK = 0;
const uint32_t DAY_OF_MONTH = 31;
const uint32_t DAY_OF_WEEK = 4;
const uint32_t ADD_ONE = 1;
const uint64_t NUM_OF_ID = 1;
const double NORMAL_CALC_RESULT = 6.2;
const double ERROR_CALC_RESULT = 0.0;
const std::string FORMULA_ONE = "2 * 3 - (2 + 3) / 5 + 6 / 2";
const std::string FORMULA_TWO = "8 / 2 + 1 )";
const std::string FORMULA_THREE = "931 - 3 * + 102 / +";
} // namespace

class UtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void UtilsTest::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "UtilsTest SetUpTestCase";
}

void UtilsTest::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "UtilsTest TearDownTestCase";
}

void UtilsTest::SetUp()
{
    GTEST_LOG_(INFO) << "UtilsTest SetUp";
}

void UtilsTest::TearDown()
{
    GTEST_LOG_(INFO) << "UtilsTest TearDown";
}

/**
 * @tc.name: UtilsTest001
 * @tc.desc: Call BaseId() constructor twice
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest001, TestSize.Level1)
{
    BaseId baseId_1;
    ASSERT_TRUE(baseId_1.GetId() == NUM_OF_ID);
}

/**
 * @tc.name: UtilsTest002
 * @tc.desc: set year:2022,month:10,day:28
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest002, TestSize.Level1)
{
    Date oneDay;
    ASSERT_EQ(oneDay.year, DEFAULT_YEAR);
    ASSERT_EQ(oneDay.month, DEFAULT_MONTH);
    ASSERT_EQ(oneDay.day, DEFAULT_DAY);
    ASSERT_EQ(oneDay.week, DEFAULT_WEEK);
    auto locaDay = oneDay.Current();
    time_t nowTime;
    struct tm* localTime;
    time(&nowTime);
    localTime = localtime(&nowTime);
    ASSERT_EQ(locaDay.year, localTime->tm_year + DEFAULT_YEAR);
    ASSERT_EQ(locaDay.month, localTime->tm_mon + ADD_ONE);
    ASSERT_EQ(locaDay.day, localTime->tm_mday);
    ASSERT_EQ(locaDay.week, localTime->tm_wday);
    ASSERT_EQ(locaDay.IsLeapYear(SET_YESR), false);
    ASSERT_EQ(locaDay.DayOfMonth(SET_YESR, SET_MONTH), DAY_OF_MONTH);
    ASSERT_EQ(locaDay.CalculateWeekDay(SET_YESR, SET_MONTH, SET_DAY), DAY_OF_WEEK);
}

/**
 * @tc.name: UtilsTest003
 * @tc.desc: give a normal formula to ConvertDal2Rpn
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest003, TestSize.Level1)
{
    double CalculateExp(const std::string& expression, const std::function<double(const Dimension&)>& calcFunc);
    auto calcResult =
        StringExpression::CalculateExp(FORMULA_ONE, [](const Dimension& dim) -> double { return dim.Value(); });
    ASSERT_EQ(calcResult, NORMAL_CALC_RESULT);
}

/**
 * @tc.name: UtilsTest004
 * @tc.desc: give a error formula to ConvertDal2Rpn
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest004, TestSize.Level1)
{
    double CalculateExp(const std::string& expression, const std::function<double(const Dimension&)>& calcFunc);
    auto errResultTwo =
        StringExpression::CalculateExp(FORMULA_TWO, [](const Dimension& dim) -> double { return dim.Value(); });
    auto errResultThree =
        StringExpression::CalculateExp(FORMULA_THREE, [](const Dimension& dim) -> double { return dim.Value(); });
    ASSERT_EQ(errResultTwo, ERROR_CALC_RESULT);
    ASSERT_EQ(errResultThree, ERROR_CALC_RESULT);
}

} // namespace OHOS::Ace