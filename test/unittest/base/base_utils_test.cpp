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

#include <atomic>
#include <chrono>
#include <ctime>
#include <memory>
#include <regex>
#include <string>
#include <sys/time.h>

#include "gtest/gtest.h"

#include "base/log/log.h"
#include "base/utils/base_id.h"
#include "base/utils/date_util.h"
#include "base/utils/resource_configuration.h"
#include "base/utils/string_expression.h"
#include "base/utils/string_utils.h"
#include "base/utils/time_util.h"
#include "base/utils/utf.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"

#ifndef WINDOWS_PLATFORM
#include "securec.h"
#endif

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr uint32_t DEFAULT_YEAR = 1900;
constexpr uint32_t DEFAULT_MONTH = 0;
constexpr uint32_t DEFAULT_DAY = 1;
constexpr uint32_t DEFAULT_WEEK = 0;
constexpr uint32_t DAY_OF_MONTH_TWENTY_NINE = 29;
constexpr uint32_t DAY_OF_MONTH_THIRTY = 30;
constexpr uint32_t DAY_OF_MONTH_THIRTY_ONE = 31;
constexpr uint32_t DAY_OF_MONTH_DEFAULT = 0;
constexpr uint32_t DAY_OF_WEEK = 4;
constexpr uint32_t ADD_ONE = 1;
constexpr uint32_t TEST_INPUT_UINT32 = 123456;
constexpr uint64_t NUM_OF_ID = 1;
constexpr int32_t TEST_INPUT_INT32 = 123456;
constexpr int32_t TWELVE_HOUR_BASE = 12;
constexpr int32_t TWENTY_FOUR_HOUR_BASE = 24;
constexpr int32_t DAY_TIME_LOWER_LIMIT = 6;
constexpr int32_t DAY_TIME_UPPER_LIMIT = 18;
constexpr int32_t SET_HOURS_FOR_THE_FIRST_TIME = -13;
constexpr int32_t SET_HOURS_FOR_THE_SECOND_TIME = 8;
constexpr int32_t SET_HOURS_FOR_THE_THIRD_TIME = 24;
constexpr int32_t GET_HOURSWEST_FOR_THE_FIRST_TIME = 11;
constexpr int32_t GET_HOURSWEST_FOR_THE_SECOND_TIME = 8;
constexpr int32_t TEST_INPUT_ARGS_TWO = 2022;
constexpr int64_t TEST_INPUT_INT64 = 123456;
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int64_t NANOSEC_TO_MILLISEC = 1000000;
constexpr int64_t CONTENT_OF_RESOURCEHANDLERS = 255;
constexpr size_t MAX_STRING_SIZE = 256;
constexpr double NORMAL_CALC_RESULT = 0.0;
constexpr double ERROR_CALC_RESULT = 0.0;
constexpr double CONFIGURATION_OF_DENSITY = 1.0;
constexpr double CONFIGURATION_OF_FONT_RATIO = 1.0;
constexpr double TEST_INPUT_DOUBLE = 123456;
constexpr double STRING_TO_DIMENSION_RESULT = 100.0;
constexpr double STRING_TO_DEGREE_RESULT = 360.0;
constexpr float TEST_INPUT_FLOAT = 123456;
const std::string CONFIGURATION_PATH = "/data/app/el2/100/base";
const std::string FORMULA_ONE = "2 * 3 - (2 + 3) / 5 + 6 / 2";
const std::string FORMULA_TWO = "8 / 2 + 1 )";
const std::string FORMULA_THREE = "931 - 3 * + 102 / +";
const std::string TEST_INPUT_FMT_STR = "%s-%d";
const std::string FMT_OUT_STR = "TODAY-2022";
const std::string TEST_INPUT_U8_STRING = "THIS IS A STRING";
const std::string DEFAULT_STRING = "error";
const std::string TEST_INPUT_U8_STRING_NULL = "";
const std::string TEST_INPUT_U8_STRING_NUMBER = "123456";
const std::string STRING_TO_CALC_DIMENSION_RESULT = "100.0calc";
const std::u16string TEST_INPUT_U16_STRING = u"THIS IS A STRING";
const std::u16string TEST_INPUT_U16_EMOJI = u"😁👻🔕🈯👩‍👩‍👧‍👦👨‍👩‍👧‍👧🙄😬🤥😌😔👩‍👦👨‍👩‍👦";
const std::u16string DEFAULT_USTRING = u"error";
const std::u32string TEST_INPUT_U32_STRING = U"THIS IS A STRING";
const std::u32string TEST_INPUT_U32_EMOJI = U"😁👻🔕🈯👩‍👩‍👧‍👦👨‍👩‍👧‍👧🙄😬🤥😌😔👩‍👦👨‍👩‍👦";
const std::u32string DEFAULT_U32STRING = U"error";
const std::wstring TEST_INPUT_W_STRING = L"THIS IS A STRING";
const std::wstring DEFAULT_WSTRING = L"error";
const char TEST_INPUT_ARGS_ONE[MAX_STRING_SIZE] = "TODAY";
const std::vector<int64_t> RESOURCEHANDLERS = { 255 };
} // namespace

class BaseUtilsTest : public testing::Test {};

/**
 * @tc.name: BaseUtilsTest001
 * @tc.desc: Call BaseId() constructor twice
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest001, TestSize.Level1)
{
    BaseId baseId_1;
    ASSERT_TRUE(baseId_1.GetId() == NUM_OF_ID);
}

/**
 * @tc.name: BaseUtilsTest002
 * @tc.desc: Set year:2022,month:10,day:28
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest002, TestSize.Level1)
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
    ASSERT_EQ(locaDay.DayOfMonth(2000, 1), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 2), DAY_OF_MONTH_TWENTY_NINE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 3), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 4), DAY_OF_MONTH_THIRTY);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 5), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 6), DAY_OF_MONTH_THIRTY);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 7), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 8), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 9), DAY_OF_MONTH_THIRTY);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 10), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 11), DAY_OF_MONTH_THIRTY);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 12), DAY_OF_MONTH_THIRTY_ONE);
    ASSERT_EQ(locaDay.DayOfMonth(2000, 13), DAY_OF_MONTH_DEFAULT);
    ASSERT_EQ(locaDay.CalculateWeekDay(2000, 1, 28), DAY_OF_WEEK);
}

/**
 * @tc.name: BaseUtilsTest003
 * @tc.desc: Give a normal formula to ConvertDal2Rpn
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest003, TestSize.Level1)
{
    double CalculateExp(const std::string& expression, const std::function<double(const Dimension&)>& calcFunc);
    auto calcResult =
        StringExpression::CalculateExp(FORMULA_ONE, [](const Dimension& dim) -> double { return dim.Value(); });
    ASSERT_EQ(calcResult, NORMAL_CALC_RESULT);
}

/**
 * @tc.name: BaseUtilsTest004
 * @tc.desc: Give a error formula to ConvertDal2Rpn
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest004, TestSize.Level1)
{
    double CalculateExp(const std::string& expression, const std::function<double(const Dimension&)>& calcFunc);
    auto errResultTwo =
        StringExpression::CalculateExp(FORMULA_TWO, [](const Dimension& dim) -> double { return dim.Value(); });
    auto errResultThree =
        StringExpression::CalculateExp(FORMULA_THREE, [](const Dimension& dim) -> double { return dim.Value(); });
    ASSERT_EQ(errResultTwo, ERROR_CALC_RESULT);
    ASSERT_EQ(errResultThree, ERROR_CALC_RESULT);
}

/**
 * @tc.name: BaseUtilsTest005
 * @tc.desc: Check FormatString
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest005, TestSize.Level1)
{
    auto firstTestText = StringUtils::FormatString("");
    auto secondTestText =
        StringUtils::FormatString(TEST_INPUT_FMT_STR.c_str(), TEST_INPUT_ARGS_ONE, TEST_INPUT_ARGS_TWO);
    ASSERT_TRUE(firstTestText == "");
    ASSERT_EQ(secondTestText, FMT_OUT_STR);
}

/**
 * @tc.name: BaseUtilsTest006
 * @tc.desc: Set the time zone within [-14, -12]
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest006, TestSize.Level1)
{
    time_t nowTime;
    struct tm* localTime;
    time(&nowTime);
    localTime = gmtime(&nowTime);
    int32_t localTimeHour12, localTimeHour24;
    auto theTimeOfNow = GetTimeOfNow(SET_HOURS_FOR_THE_FIRST_TIME);
    auto theTimeOfZone = GetTimeOfZone(SET_HOURS_FOR_THE_FIRST_TIME);
    localTimeHour24 = localTime->tm_hour - SET_HOURS_FOR_THE_FIRST_TIME;
    if (localTimeHour24 >= TWENTY_FOUR_HOUR_BASE) {
        localTimeHour24 -= TWENTY_FOUR_HOUR_BASE;
    } else if (localTimeHour24 < 0) {
        localTimeHour24 += TWENTY_FOUR_HOUR_BASE;
    }
    if (localTimeHour24 >= TWELVE_HOUR_BASE) {
        localTimeHour12 = localTimeHour24 - TWELVE_HOUR_BASE;
    } else {
        localTimeHour12 = localTimeHour24;
    }
    ASSERT_EQ(theTimeOfNow.hoursWest_, GET_HOURSWEST_FOR_THE_FIRST_TIME);
    ASSERT_EQ(theTimeOfNow.second_, localTime->tm_sec);
    ASSERT_EQ(theTimeOfNow.minute_, localTime->tm_min);
    ASSERT_EQ(theTimeOfNow.hour12_, localTimeHour12);
    ASSERT_EQ(theTimeOfNow.hour24_, localTimeHour24);
    ASSERT_EQ(theTimeOfZone.hoursWest_, GET_HOURSWEST_FOR_THE_FIRST_TIME);
    ASSERT_EQ(theTimeOfZone.second_, localTime->tm_sec);
    ASSERT_EQ(theTimeOfZone.minute_, localTime->tm_min);
    ASSERT_EQ(theTimeOfZone.hour12_, localTimeHour12);
    ASSERT_EQ(theTimeOfZone.hour24_, localTimeHour24);
}

/**
 * @tc.name: BaseUtilsTest007
 * @tc.desc: Set the time zone within [-12, 12]
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest007, TestSize.Level1)
{
    time_t nowTime;
    struct tm* localTime;
    time(&nowTime);
    localTime = gmtime(&nowTime);
    int32_t localTimeHour12, localTimeHour24;
    auto theTimeOfNow = GetTimeOfNow(SET_HOURS_FOR_THE_SECOND_TIME);
    auto theTimeOfZone = GetTimeOfZone(SET_HOURS_FOR_THE_SECOND_TIME);
    localTimeHour24 = localTime->tm_hour - SET_HOURS_FOR_THE_SECOND_TIME;
    if (localTimeHour24 >= TWENTY_FOUR_HOUR_BASE) {
        localTimeHour24 -= TWENTY_FOUR_HOUR_BASE;
    } else if (localTimeHour24 < 0) {
        localTimeHour24 += TWENTY_FOUR_HOUR_BASE;
    }
    if (localTimeHour24 >= TWELVE_HOUR_BASE) {
        localTimeHour12 = localTimeHour24 - TWELVE_HOUR_BASE;
    } else {
        localTimeHour12 = localTimeHour24;
    }
    bool isDayTimeOfNow = IsDayTime(theTimeOfNow);
    bool isDayTimeOfZone = IsDayTime(theTimeOfZone);
    ASSERT_EQ(theTimeOfNow.hoursWest_, GET_HOURSWEST_FOR_THE_SECOND_TIME);
    ASSERT_EQ(theTimeOfNow.second_, localTime->tm_sec);
    ASSERT_EQ(theTimeOfNow.minute_, localTime->tm_min);
    ASSERT_EQ(theTimeOfNow.hour12_, localTimeHour12);
    ASSERT_EQ(theTimeOfNow.hour24_, localTimeHour24);
    ASSERT_EQ(theTimeOfZone.hoursWest_, GET_HOURSWEST_FOR_THE_SECOND_TIME);
    ASSERT_EQ(theTimeOfZone.second_, localTime->tm_sec);
    ASSERT_EQ(theTimeOfZone.minute_, localTime->tm_min);
    ASSERT_EQ(theTimeOfZone.hour12_, localTimeHour12);
    ASSERT_EQ(theTimeOfZone.hour24_, localTimeHour24);
    if (localTimeHour24 >= DAY_TIME_LOWER_LIMIT && localTimeHour24 < DAY_TIME_UPPER_LIMIT) {
        ASSERT_EQ(isDayTimeOfNow, true);
        ASSERT_EQ(isDayTimeOfZone, true);
    } else {
        ASSERT_EQ(isDayTimeOfNow, false);
        ASSERT_EQ(isDayTimeOfZone, false);
    }
}

/**
 * @tc.name: BaseUtilsTest008
 * @tc.desc: Set the time zone beyond the range of [-14, 12]
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest008, TestSize.Level1)
{
    time_t nowTime;
    struct tm* localTime;
    time(&nowTime);
    localTime = gmtime(&nowTime);
    auto theTimeOfNow = GetTimeOfNow(SET_HOURS_FOR_THE_THIRD_TIME);
    auto theTimeOfZone = GetTimeOfZone(SET_HOURS_FOR_THE_THIRD_TIME);
    struct timeval currentTime;
    struct timezone timeZone;
    gettimeofday(&currentTime, &timeZone);
    auto getHoursWest = timeZone.tz_minuteswest / 60;
    ASSERT_EQ(theTimeOfNow.hoursWest_, getHoursWest);
    ASSERT_EQ(theTimeOfNow.second_, localTime->tm_sec);
    ASSERT_EQ(theTimeOfNow.minute_, localTime->tm_min);
    ASSERT_EQ(theTimeOfZone.hoursWest_, getHoursWest);
    ASSERT_EQ(theTimeOfZone.second_, localTime->tm_sec);
    ASSERT_EQ(theTimeOfZone.minute_, localTime->tm_min);
}

/**
 * @tc.name: BaseUtilsTest009
 * @tc.desc: Check the time since the device was started
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest009, TestSize.Level1)
{
    auto microTickCount = GetMicroTickCount();
    auto sysTimestamp = GetSysTimestamp();
    int64_t microTickCountMsec, sysTimestampMsec;
    microTickCountMsec = microTickCount / MICROSEC_TO_MILLISEC;
    sysTimestampMsec = sysTimestamp / NANOSEC_TO_MILLISEC;
    ASSERT_EQ(microTickCountMsec, sysTimestampMsec);
}

/**
 * @tc.name: BaseUtilsTest010
 * @tc.desc: Set ResourceConfiguration
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest010, TestSize.Level1)
{
    ResourceConfiguration resConfiguration;
    ASSERT_EQ(resConfiguration.TestFlag(
                  ResourceConfiguration::COLOR_MODE_UPDATED_FLAG, ResourceConfiguration::FONT_RATIO_UPDATED_FLAG),
        false);
    resConfiguration.SetDeviceType(DeviceType::UNKNOWN);
    resConfiguration.SetOrientation(DeviceOrientation::ORIENTATION_UNDEFINED);
    resConfiguration.SetDensity(CONFIGURATION_OF_DENSITY);
    resConfiguration.SetFontRatio(CONFIGURATION_OF_FONT_RATIO);
    resConfiguration.SetColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    resConfiguration.SetDeviceAccess(true);
    ASSERT_EQ(resConfiguration.GetDeviceType(), DeviceType::UNKNOWN);
    ASSERT_EQ(resConfiguration.GetOrientation(), DeviceOrientation::ORIENTATION_UNDEFINED);
    ASSERT_EQ(resConfiguration.GetDensity(), CONFIGURATION_OF_DENSITY);
    ASSERT_EQ(resConfiguration.GetFontRatio(), CONFIGURATION_OF_FONT_RATIO);
    ASSERT_EQ(resConfiguration.GetColorMode(), ColorMode::COLOR_MODE_UNDEFINED);
    ASSERT_EQ(resConfiguration.GetDeviceAccess(), true);
}

/**
 * @tc.name: BaseUtilsTest011
 * @tc.desc: Set ResourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest011, TestSize.Level1)
{
    ResourceInfo resourceInfo;
    ResourceConfiguration resConfiguration;
    resourceInfo.SetResourceConfiguration(resConfiguration);
    resourceInfo.SetResourceHandlers(RESOURCEHANDLERS);
    resourceInfo.SetHapPath(CONFIGURATION_PATH);
    resourceInfo.SetPackagePath(CONFIGURATION_PATH);
    resourceInfo.SetThemeId(NUM_OF_ID);
    ASSERT_EQ(resourceInfo.GetResourceConfiguration().GetDeviceType(), DeviceType::PHONE);
    ASSERT_EQ(resourceInfo.GetResourceHandlers()[0], CONTENT_OF_RESOURCEHANDLERS);
    ASSERT_EQ(resourceInfo.GetHapPath(), CONFIGURATION_PATH);
    ASSERT_EQ(resourceInfo.GetPackagePath(), CONFIGURATION_PATH);
    ASSERT_EQ(resourceInfo.GetThemeId(), NUM_OF_ID);
}

/**
 * @tc.name: BaseUtilsTest012
 * @tc.desc: Json does not contain "colorMode"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest012, TestSize.Level1)
{
    const std::string inputTestJsonStr = "{"
                                         "  \"deviceType\": \"PHONE\",          "
                                         "  \"fontScale\": 1.0                  "
                                         "}";
    ResourceConfiguration resConfiguration;
    uint32_t updateFlags = ResourceConfiguration::COLOR_MODE_UPDATED_FLAG;
    bool isUpdateFromJsonString = resConfiguration.UpdateFromJsonString(inputTestJsonStr, updateFlags);
    ASSERT_EQ(isUpdateFromJsonString, true);
}

/**
 * @tc.name: BaseUtilsTest013
 * @tc.desc: Json does not contain "fontScale"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest013, TestSize.Level1)
{
    const std::string inputTestJsonStr = "{"
                                         "  \"deviceType\": \"PHONE\",          "
                                         "  \"colorMode\": 1.0                  "
                                         "}";
    ResourceConfiguration resConfiguration;
    uint32_t updateFlags = ResourceConfiguration::COLOR_MODE_UPDATED_FLAG;
    bool isUpdateFromJsonString = resConfiguration.UpdateFromJsonString(inputTestJsonStr, updateFlags);
    ASSERT_EQ(isUpdateFromJsonString, true);
}

/**
 * @tc.name: BaseUtilsTest014
 * @tc.desc: ColorMode is not "light" or "dark"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest014, TestSize.Level1)
{
    const std::string inputTestJsonStr = "{"
                                         "  \"deviceType\": \"PHONE\",          "
                                         "  \"fontScale\": \"1.0\",             "
                                         "  \"colorMode\": \"undefined\"            "
                                         "}";
    ResourceConfiguration resConfiguration;
    uint32_t updateFlags = ResourceConfiguration::COLOR_MODE_UPDATED_FLAG;
    bool isUpdateFromJsonString = resConfiguration.UpdateFromJsonString(inputTestJsonStr, updateFlags);
    ASSERT_EQ(isUpdateFromJsonString, true);
}

/**
 * @tc.name: BaseUtilsTest015
 * @tc.desc: FontScale is not 1.0
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest015, TestSize.Level1)
{
    const std::string inputTestJsonStr = "{"
                                         "  \"deviceType\": \"PHONE\",          "
                                         "  \"fontScale\": 2.0,                 "
                                         "  \"colorMode\": \"light\"            "
                                         "}";
    ResourceConfiguration resConfiguration;
    uint32_t updateFlags = ResourceConfiguration::COLOR_MODE_UPDATED_FLAG;
    bool isUpdateFromJsonString = resConfiguration.UpdateFromJsonString(inputTestJsonStr, updateFlags);
    ASSERT_EQ(isUpdateFromJsonString, true);
    ASSERT_EQ(updateFlags, ResourceConfiguration::FONT_RATIO_UPDATED_FLAG);
}

/**
 * @tc.name: BaseUtilsTest016
 * @tc.desc: Set colorMode "dark"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest016, TestSize.Level1)
{
    const std::string inputTestJsonStr = "{"
                                         "  \"deviceType\": \"PHONE\",          "
                                         "  \"fontScale\": 1.0,                 "
                                         "  \"colorMode\": \"dark\"             "
                                         "}";
    ResourceConfiguration resConfiguration;
    uint32_t updateFlags = ResourceConfiguration::COLOR_MODE_UPDATED_FLAG;
    bool isUpdateFromJsonString = resConfiguration.UpdateFromJsonString(inputTestJsonStr, updateFlags);
    ASSERT_EQ(isUpdateFromJsonString, true);
    ASSERT_EQ(updateFlags, ResourceConfiguration::COLOR_MODE_UPDATED_FLAG);
}

/**
 * @tc.name: BaseUtilsTest017
 * @tc.desc: Check char in bmp and whether the content of string is a number
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest017, TestSize.Level1)
{
    const char16_t testChar16 = 0xD800;
    const wchar_t testWchar = 0xD800;
    ASSERT_EQ(StringUtils::NotInUtf16Bmp(testChar16), true);
    ASSERT_EQ(StringUtils::NotInBmp(testWchar), true);
    ASSERT_EQ(StringUtils::IsNumber(TEST_INPUT_U8_STRING_NULL), false);
    ASSERT_EQ(StringUtils::IsNumber(TEST_INPUT_U8_STRING_NUMBER), true);
}

/**
 * @tc.name: BaseUtilsTest018
 * @tc.desc: U16string-string-wstring, string-uint32, string-int64 convert
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest018, TestSize.Level1)
{
    ASSERT_EQ(StringUtils::Str8ToStr16(TEST_INPUT_U8_STRING), TEST_INPUT_U16_STRING);
    ASSERT_EQ(StringUtils::Str16ToStr8(TEST_INPUT_U16_STRING), TEST_INPUT_U8_STRING);
    ASSERT_EQ(StringUtils::ToWstring(TEST_INPUT_U8_STRING), TEST_INPUT_W_STRING);
    ASSERT_EQ(StringUtils::ToString(TEST_INPUT_W_STRING), TEST_INPUT_U8_STRING);
    ASSERT_EQ(StringUtils::Str8ToStr16(StringUtils::DEFAULT_STRING), StringUtils::DEFAULT_USTRING);
    ASSERT_EQ(StringUtils::Str16ToStr8(StringUtils::DEFAULT_USTRING), StringUtils::DEFAULT_STRING);
    ASSERT_EQ(StringUtils::ToWstring(StringUtils::DEFAULT_STRING), StringUtils::DEFAULT_WSTRING);
    ASSERT_EQ(StringUtils::ToString(StringUtils::DEFAULT_WSTRING), StringUtils::DEFAULT_STRING);
    ASSERT_EQ(StringUtils::DoubleToString(TEST_INPUT_DOUBLE, 0), TEST_INPUT_U8_STRING_NUMBER);
    ASSERT_EQ(StringUtils::StringToLongInt(TEST_INPUT_U8_STRING_NUMBER), TEST_INPUT_INT64);
    ASSERT_EQ(StringUtils::StringToUint(TEST_INPUT_U8_STRING_NUMBER), TEST_INPUT_UINT32);
}

/**
 * @tc.name: BaseUtilsTest019
 * @tc.desc: Delete all mark : "."
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest019, TestSize.Level1)
{
    std::string markString = "THIS. IS. A. STRING";
    const char mark = '.';
    StringUtils::DeleteAllMark(markString, mark);
    ASSERT_EQ(markString, TEST_INPUT_U8_STRING);
}

/**
 * @tc.name: BaseUtilsTest020
 * @tc.desc: Replace tab and newline with space
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest020, TestSize.Level1)
{
    std::string inputTabAndNewLine = "THIS\rIS\nA\tSTRING";
    StringUtils::ReplaceTabAndNewLine(inputTabAndNewLine);
    ASSERT_EQ(inputTabAndNewLine, TEST_INPUT_U8_STRING);
}

/**
 * @tc.name: BaseUtilsTest021
 * @tc.desc: Input a string contain "auto"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest021, TestSize.Level1)
{
    const std::string stringToDimensionValue = "auto";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    auto calcDim = StringUtils::StringToCalcDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), 0);
    ASSERT_EQ(dim.Unit(), DimensionUnit::AUTO);
    ASSERT_EQ(calcDim.Value(), 0);
    ASSERT_EQ(calcDim.Unit(), DimensionUnit::AUTO);
}

/**
 * @tc.name: BaseUtilsTest022
 * @tc.desc: Input a string contain "calc"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest022, TestSize.Level1)
{
    const std::string stringToDimensionValue = "100.0calc";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    auto calcDim = StringUtils::StringToCalcDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Unit(), DimensionUnit::VP);
    ASSERT_EQ(calcDim.CalcValue(), STRING_TO_CALC_DIMENSION_RESULT);
    ASSERT_EQ(calcDim.Unit(), DimensionUnit::CALC);
}

/**
 * @tc.name: BaseUtilsTest023
 * @tc.desc: Input a string contain "%"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest023, TestSize.Level1)
{
    const std::string stringToDimensionValue = "100.0%";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), 1.0);
    ASSERT_EQ(dim.Unit(), DimensionUnit::PERCENT);
}

/**
 * @tc.name: BaseUtilsTest024
 * @tc.desc: Input a string contain "px"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest024, TestSize.Level1)
{
    const std::string stringToDimensionValue = "100.0px";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), STRING_TO_DIMENSION_RESULT);
    ASSERT_EQ(dim.Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: BaseUtilsTest025
 * @tc.desc: Input a string contain "vp"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest025, TestSize.Level1)
{
    const std::string stringToDimensionValue = "100.0vp";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), STRING_TO_DIMENSION_RESULT);
    ASSERT_EQ(dim.Unit(), DimensionUnit::VP);
}

/**
 * @tc.name: BaseUtilsTest026
 * @tc.desc: Input a string contain "fp"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest026, TestSize.Level1)
{
    const std::string stringToDimensionValue = "100.0fp";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), STRING_TO_DIMENSION_RESULT);
    ASSERT_EQ(dim.Unit(), DimensionUnit::FP);
}

/**
 * @tc.name: BaseUtilsTest027
 * @tc.desc: Input a string contain "lpx"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest027, TestSize.Level1)
{
    const std::string stringToDimensionValue = "100.0lpx";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), STRING_TO_DIMENSION_RESULT);
    ASSERT_EQ(dim.Unit(), DimensionUnit::LPX);
}

/**
 * @tc.name: BaseUtilsTest028
 * @tc.desc: Set an empty string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest028, TestSize.Level1)
{
    const std::string stringToDimensionValue = "";
    auto dim = StringUtils::StringToDimension(stringToDimensionValue, true);
    ASSERT_EQ(dim.Value(), 0.0);
    ASSERT_EQ(dim.Unit(), DimensionUnit::VP);
}

/**
 * @tc.name: BaseUtilsTest029
 * @tc.desc: Set an empty string, check StringToDegree
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest029, TestSize.Level1)
{
    const std::string stringToDegreeValue = "";
    auto degreeValue = StringUtils::StringToDegree(stringToDegreeValue);
    ASSERT_EQ(degreeValue, 0.0);
}

/**
 * @tc.name: BaseUtilsTest030
 * @tc.desc: Input a string contain "deg"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest030, TestSize.Level1)
{
    const std::string stringToDegreeValue = "360.0deg";
    auto degreeValue = StringUtils::StringToDegree(stringToDegreeValue);
    ASSERT_EQ(degreeValue, STRING_TO_DEGREE_RESULT);
}

/**
 * @tc.name: BaseUtilsTest031
 * @tc.desc: Input a string contain "gard"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest031, TestSize.Level1)
{
    const std::string stringToDegreeValue = "400.0grad";
    auto degreeValue = StringUtils::StringToDegree(stringToDegreeValue);
    ASSERT_EQ(degreeValue, STRING_TO_DEGREE_RESULT);
}

/**
 * @tc.name: BaseUtilsTest032
 * @tc.desc: Input a string contain "rad"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest032, TestSize.Level1)
{
    const std::string stringToDegreeValue = "6.28318530717958647692rad";
    auto degreeValue = StringUtils::StringToDegree(stringToDegreeValue);
    ASSERT_EQ(degreeValue, STRING_TO_DEGREE_RESULT);
}

/**
 * @tc.name: BaseUtilsTest033
 * @tc.desc: Input a string contain "turn"
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest033, TestSize.Level1)
{
    const std::string stringToDegreeValue = "1turn";
    auto degreeValue = StringUtils::StringToDegree(stringToDegreeValue);
    ASSERT_EQ(degreeValue, STRING_TO_DEGREE_RESULT);
}

/**
 * @tc.name: BaseUtilsTest034
 * @tc.desc: Input a string contain "-", split string to string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest034, TestSize.Level1)
{
    const std::string stringSplitterValue = "123456-123456";
    const char delimiter = '-';
    std::vector<std::string> out;
    StringUtils::StringSplitter(stringSplitterValue, delimiter, out);
    ASSERT_EQ(out[0], TEST_INPUT_U8_STRING_NUMBER);
}

/**
 * @tc.name: BaseUtilsTest035
 * @tc.desc: Input a string contain "-", split string to int32_t
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest035, TestSize.Level1)
{
    const std::string stringSplitterValue = "123456-123456";
    const char delimiter = '-';
    std::vector<int32_t> out;
    StringUtils::StringSplitter(stringSplitterValue, delimiter, out);
    ASSERT_EQ(out[0], TEST_INPUT_INT32);
}

/**
 * @tc.name: BaseUtilsTest036
 * @tc.desc: Input a string contain "-", split string to double
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest036, TestSize.Level1)
{
    const std::string stringSplitterValue = "123456-123456";
    const char delimiter = '-';
    std::vector<double> out;
    StringUtils::StringSplitter(stringSplitterValue, delimiter, out);
    ASSERT_EQ(out[0], TEST_INPUT_DOUBLE);
}

/**
 * @tc.name: BaseUtilsTest037
 * @tc.desc: Input a string contain "-", split string to float
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest037, TestSize.Level1)
{
    const std::string stringSplitterValue = "123456-123456";
    const char delimiter = '-';
    std::vector<float> out;
    StringUtils::StringSplitter(stringSplitterValue, delimiter, out);
    ASSERT_EQ(out[0], TEST_INPUT_FLOAT);
}

/**
 * @tc.name: BaseUtilsTest038
 * @tc.desc: Input a string contain "-", split string to Dimension
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest038, TestSize.Level1)
{
    const std::string stringSplitterValue = "123456-123456";
    const char delimiter = '-';
    std::vector<Dimension> out;
    StringUtils::StringSplitter(stringSplitterValue, delimiter, out);
    ASSERT_EQ(out[0].Value(), TEST_INPUT_DOUBLE);
    ASSERT_EQ(out[0].Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: BaseUtilsTest039
 * @tc.desc: No characters found for splitSepValue in splitStrValue
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest039, TestSize.Level1)
{
    const std::string splitStrValue = "THIS IS A STRING";
    const std::string splitSepValue = "!?";
    std::vector<std::string> stringOut;
    std::vector<Dimension> dimOut;
    StringUtils::SplitStr(splitStrValue, splitSepValue, stringOut, true);
    StringUtils::SplitStr(splitStrValue, splitSepValue, dimOut, true);
    ASSERT_EQ(stringOut[0], TEST_INPUT_U8_STRING);
    ASSERT_EQ(dimOut[0].Value(), 0);
    ASSERT_EQ(dimOut[0].Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: BaseUtilsTest040
 * @tc.desc: There is some characters found for splitSepValue in splitStrValue
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest040, TestSize.Level1)
{
    const std::string splitStrValue = "##THIS IS A STRING***##";
    const std::string splitSepValue = "#*";
    std::vector<std::string> stringOut;
    std::vector<Dimension> dimOut;
    StringUtils::SplitStr(splitStrValue, splitSepValue, stringOut, true);
    StringUtils::SplitStr(splitStrValue, splitSepValue, dimOut, true);
    ASSERT_EQ(stringOut[0], TEST_INPUT_U8_STRING);
    ASSERT_EQ(dimOut[0].Value(), 0);
    ASSERT_EQ(dimOut[0].Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: BaseUtilsTest041
 * @tc.desc: splitString is empty
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest041, TestSize.Level1)
{
    const std::string splitStrValue = "";
    const std::string splitSepValue = "";
    std::vector<std::string> stringOut;
    std::vector<Dimension> dimOut;
    StringUtils::SplitStr(splitStrValue, splitSepValue, stringOut, true);
    StringUtils::SplitStr(splitStrValue, splitSepValue, dimOut, true);
    ASSERT_TRUE(stringOut.empty());
    ASSERT_TRUE(dimOut.empty());
}

/**
 * @tc.name: BaseUtilsTest042
 * @tc.desc: StartWith, EndWith the same string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest042, TestSize.Level1)
{
    const std::string startWithValue = "THIS IS A STRING";
    const std::string prefixString = "THIS IS A STRING";
    const char* prefixChar = "THIS IS A STRING";
    size_t prefixLen = startWithValue.size();
    ASSERT_EQ(StringUtils::StartWith(startWithValue, prefixString), true);
    ASSERT_EQ(StringUtils::StartWith(startWithValue, prefixChar, prefixLen), true);
    ASSERT_EQ(StringUtils::EndWith(startWithValue, prefixString), true);
    ASSERT_EQ(StringUtils::EndWith(startWithValue, prefixString), true);
}

/**
 * @tc.name: BaseUtilsTest043
 * @tc.desc: utf8 string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest043, TestSize.Level1)
{
    std::string utf8String = "THIS IS A UTF-8 STRING é (e-acute).";
    ASSERT_EQ(IsUTF8(utf8String), true);
}

/**
 * @tc.name: BaseUtilsTest044
 * @tc.desc: empty string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest044, TestSize.Level1)
{
    std::string emptyUtf8 = "";
    ASSERT_EQ(IsUTF8(emptyUtf8), false);
}

/**
 * @tc.name: BaseUtilsTest045
 * @tc.desc: singleByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest045, TestSize.Level1)
{
    std::string singleByte = "\x80";
    ASSERT_EQ(IsUTF8(singleByte), false);
}

/**
 * @tc.name: BaseUtilsTest046
 * @tc.desc: singleByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest046, TestSize.Level1)
{
    uint8_t data = 0x41;
    auto result = ConvertMUtf8ToUtf16Pair(&data, 1);
    EXPECT_EQ(result.first, 0x0041);
    EXPECT_EQ(result.second, 1);
}

/**
 * @tc.name: BaseUtilsTest047
 * @tc.desc: twoByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest047, TestSize.Level1)
{
    uint8_t data[2] = { 0xC3, 0x81 };
    auto result = ConvertMUtf8ToUtf16Pair(data, 2);
    EXPECT_EQ(result.first, 0xc1);
    EXPECT_EQ(result.second, 2);
}

/**
 * @tc.name: BaseUtilsTest048
 * @tc.desc: threeByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest048, TestSize.Level1)
{
    uint8_t data[3] = { 0xE1, 0x82, 0x81 };
    auto result = ConvertMUtf8ToUtf16Pair(data, 3);
    EXPECT_EQ(result.first, 0x1081);
    EXPECT_EQ(result.second, 3);
}

/**
 * @tc.name: BaseUtilsTest049
 * @tc.desc:fourByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest049, TestSize.Level1)
{
    uint8_t data[4] = { 0xF1, 0x80, 0x80, 0x81 };
    auto result = ConvertMUtf8ToUtf16Pair(data, 4);
    EXPECT_EQ(result.first, 0xD8C0DC01);
    EXPECT_EQ(result.second, 4);
}

/**
 * @tc.name: BaseUtilsTest050
 * @tc.desc: empty string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest050, TestSize.Level1)
{
    const uint8_t* emptyStr = reinterpret_cast<const uint8_t*>("");
    size_t size = MUtf8ToUtf16Size(emptyStr, 0);
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: BaseUtilsTest051
 * @tc.desc: singleByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest051, TestSize.Level1)
{
    const uint8_t* singleByteStr = reinterpret_cast<const uint8_t*>("a");
    size_t size = MUtf8ToUtf16Size(singleByteStr, 1);
    EXPECT_EQ(size, 1);
}

/**
 * @tc.name: BaseUtilsTest052
 * @tc.desc: mixed string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest052, TestSize.Level1)
{
    const uint8_t* mixedStr = reinterpret_cast<const uint8_t*>(u8"Hello, 世界!");
    size_t size = MUtf8ToUtf16Size(mixedStr, strlen(reinterpret_cast<const char*>(mixedStr)));
    EXPECT_EQ(size, 10);
}

/**
 * @tc.name: BaseUtilsTest053
 * @tc.desc: empty string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest053, TestSize.Level1)
{
    const uint8_t* emptyInput = nullptr;
    uint16_t output[10] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(emptyInput, output, 0, 10, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: BaseUtilsTest054
 * @tc.desc: singleByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest054, TestSize.Level1)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(u8"a");
    uint16_t output[10] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(input, output, 1, 10, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(output[0], 'a');
}

/**
 * @tc.name: BaseUtilsTest055
 * @tc.desc: mixed string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest055, TestSize.Level1)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(u8"Hello, 世界!");
    uint16_t output[50] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(input, output, strlen(reinterpret_cast<const char*>(input)), 50, 0);
    EXPECT_EQ(result, 10);
}

/**
 * @tc.name: BaseUtilsTest056
 * @tc.desc: invalid string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest056, TestSize.Level1)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(u8"XXXX");
    uint16_t output[10] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(input, output, 4, 10, 0);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: BaseUtilsTest057
 * @tc.desc: null string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest057, TestSize.Level1)
{
    const uint16_t* emptyInput = nullptr;
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(emptyInput, output, 0, 10, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: BaseUtilsTest058
 * @tc.desc: singlebyte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest058, TestSize.Level1)
{
    const uint16_t input[] = { 0x0061 };
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(input, output, 1, 10, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(output[0], 0x61);
}

/**
 * @tc.name: BaseUtilsTest059
 * @tc.desc: twobyte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest059, TestSize.Level1)
{
    const uint16_t input[] = { 0xD800, 0xDC00 };
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(input, output, 2, 10, 0);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: BaseUtilsTest060
 * @tc.desc: twobyte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest060, TestSize.Level1)
{
    const uint16_t input[] = { 0xD800, 0xD800 };
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(input, output, 2, 10, 0);
    EXPECT_EQ(result, 6);
}

/**
 * @tc.name: BaseUtilsTest061
 * @tc.desc: standard string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest061, TestSize.Level1)
{
    std::string legalStr = "THIS IS A UTF-8 STRING é (e-acute).";
    ConvertIllegalStr(legalStr);
    EXPECT_TRUE(IsUTF8(legalStr));
    EXPECT_EQ(legalStr, "THIS IS A UTF-8 STRING é (e-acute).");
}

/**
 * @tc.name: BaseUtilsTest062
 * @tc.desc: valid string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest062, TestSize.Level1)
{
    std::string illegalStr = "Hello, \xFF\xFE World!";
    ConvertIllegalStr(illegalStr);
    EXPECT_TRUE(IsUTF8(illegalStr));
    EXPECT_EQ(illegalStr, "Hello,  World!");
}

/**
 * @tc.name: BaseUtilsTest063
 * @tc.desc: emptyStr string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest063, TestSize.Level1)
{
    std::string emptyStr = "";
    ConvertIllegalStr(emptyStr);
    EXPECT_FALSE(IsUTF8(emptyStr));
    EXPECT_EQ(emptyStr, "");
}

/**
 * @tc.name: BaseUtilsTest064
 * @tc.desc: allByte string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest064, TestSize.Level1)
{
    std::string allByteValues(256, 0);
    for (int i = 0; i < 256; ++i) {
        allByteValues[i] = static_cast<char>(i);
    }
    ConvertIllegalStr(allByteValues);
    EXPECT_TRUE(IsUTF8(allByteValues));
}

/**
 * @tc.name: BaseUtilsTest065
 * @tc.desc: test utf_helper.cpp: Convert u16string and string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest065, TestSize.Level1)
{
    ASSERT_EQ(UtfUtils::Str16ToStr8(TEST_INPUT_U16_STRING), TEST_INPUT_U8_STRING);
    ASSERT_EQ(UtfUtils::Str8ToStr16(TEST_INPUT_U8_STRING), TEST_INPUT_U16_STRING);
    ASSERT_EQ(UtfUtils::Str16ToStr8(UtfUtils::DEFAULT_U16STR), UtfUtils::DEFAULT_STR);
    ASSERT_EQ(UtfUtils::Str8ToStr16(UtfUtils::DEFAULT_STR), UtfUtils::DEFAULT_U16STR);
}

/**
 * @tc.name: BaseUtilsTest066
 * @tc.desc: test utf_helper.cpp: Convert u16string and string with debug for nornal string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest066, TestSize.Level1)
{
    ASSERT_EQ(UtfUtils::Str16DebugToStr8(TEST_INPUT_U16_STRING), TEST_INPUT_U8_STRING);
    ASSERT_EQ(UtfUtils::Str8DebugToStr16(TEST_INPUT_U8_STRING), TEST_INPUT_U16_STRING);
    ASSERT_EQ(UtfUtils::Str16DebugToStr8(UtfUtils::DEFAULT_U16STR), UtfUtils::DEFAULT_STR);
    ASSERT_EQ(UtfUtils::Str8DebugToStr16(UtfUtils::DEFAULT_STR), UtfUtils::DEFAULT_U16STR);
}

/**
 * @tc.name: BaseUtilsTest067
 * @tc.desc: test utf_helper.cpp: Convert u16string to string with debug for truncated emoji string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest067, TestSize.Level1)
{
    std::u16string emojiStr = u"哈哈😁";
    std::u16string subEmojiStr = emojiStr.substr(0, 3);
    std::string excpectSubEmojiStr = "哈哈\uFFFD"; /* \uFFFD is emoji ? */
    ASSERT_EQ(UtfUtils::Str16DebugToStr8(subEmojiStr), excpectSubEmojiStr);
}

/**
 * @tc.name: BaseUtilsTest068
 * @tc.desc: test utf_helper.cpp: Convert string to u6string with debug for truncated emoji string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest068, TestSize.Level1)
{
    std::string emojiStr = "环境😁";
    std::string subEmojiStr = emojiStr.substr(0, 9);
    std::u16string excpectSubEmojiStr = u"环境\uFFFD"; /* \uFFFD is emoji ? */
    ASSERT_EQ(UtfUtils::Str8DebugToStr16(subEmojiStr), excpectSubEmojiStr);
}

/**
 * @tc.name: BaseUtilsTest069
 * @tc.desc: test utf_helper.cpp: Unpaired surrogates are replace with U+FFFD
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest069, TestSize.Level1)
{
    std::u16string emojiStr = u"哈哈😁";
    std::u16string subEmojiStr = emojiStr.substr(0, 3);
    std::u16string excpectSubEmojiStr = u"哈哈\uFFFD"; /* \uFFFD is emoji ? */
    UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(subEmojiStr.data()), subEmojiStr.length(), 0);
    ASSERT_EQ(subEmojiStr, excpectSubEmojiStr);
}

/**
 * @tc.name: BaseUtilsTest070
 * @tc.desc: test utf_helper.cpp: Nothing will be changed for normal string without truncation
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest070, TestSize.Level1)
{
    std::u16string emojiStr = u"哈哈😁";
    std::u16string excpectEmojiStr = emojiStr;
    UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(emojiStr.data()), emojiStr.length(), 0);
    ASSERT_EQ(emojiStr, excpectEmojiStr);
}

/**
 * @tc.name: BaseUtilsTest071
 * @tc.desc: test utf_helper.cpp: Convert u16string and u32string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest071, TestSize.Level1)
{
    ASSERT_EQ(UtfUtils::Str16ToStr32(TEST_INPUT_U16_STRING), TEST_INPUT_U32_STRING);
    ASSERT_EQ(UtfUtils::Str32ToStr16(TEST_INPUT_U32_STRING), TEST_INPUT_U16_STRING);
    ASSERT_EQ(UtfUtils::Str16ToStr32(TEST_INPUT_U16_EMOJI), TEST_INPUT_U32_EMOJI);
    ASSERT_EQ(UtfUtils::Str32ToStr16(TEST_INPUT_U32_EMOJI), TEST_INPUT_U16_EMOJI);
    ASSERT_EQ(UtfUtils::Str16ToStr32(u""), U"");
    ASSERT_EQ(UtfUtils::Str32ToStr16(U""), u"");
    ASSERT_EQ(UtfUtils::Str16ToStr32(UtfUtils::DEFAULT_U16STR), UtfUtils::DEFAULT_U32STR);
    ASSERT_EQ(UtfUtils::Str32ToStr16(UtfUtils::DEFAULT_U32STR), UtfUtils::DEFAULT_U16STR);
}

/**
 * @tc.name: BaseUtilsTest072
 * @tc.desc: test utf_helper.cpp: Convert u16string to u32string reserving truncated emoji string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest072, TestSize.Level1)
{
    std::u16string emojiStr = u"😁";
    std::u16string subEmojiStr = emojiStr.substr(0, 1);
    std::u32string excpectSubEmojiStr = U"哈";
    excpectSubEmojiStr[0] = 0xD83D; /* D83D DC01 is utf-16 encoding for emoji 😁 */
    ASSERT_EQ(UtfUtils::Str16ToStr32(subEmojiStr), excpectSubEmojiStr);
    ASSERT_EQ(UtfUtils::Str32ToStr16(UtfUtils::Str16ToStr32(subEmojiStr)), subEmojiStr);
}

/**
 * @tc.name: BaseUtilsTest073
 * @tc.desc: test utf_helper.cpp: Convert u16string to u32string reserving truncated emoji string
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, BaseUtilsTest073, TestSize.Level1)
{
    std::u16string emojiStr = u"哈哈😁";
    std::u16string subEmojiStr = emojiStr.substr(0, 3);
    std::u32string excpectSubEmojiStr = U"哈哈哈";
    excpectSubEmojiStr[2] = 0xD83D; /* D83D DC01 is utf-16 encoding for emoji 😁 */
    ASSERT_EQ(UtfUtils::Str16ToStr32(subEmojiStr), excpectSubEmojiStr);
    ASSERT_EQ(UtfUtils::Str32ToStr16(UtfUtils::Str16ToStr32(subEmojiStr)), subEmojiStr);
}

/**
 * @tc.name: StringExpressionTest001
 * @tc.desc: InitMapping()
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest001, TestSize.Level1)
{
    std::map<std::string, int> mapping;
    StringExpression::InitMapping(mapping);

    EXPECT_EQ(mapping.find("+")->second, 0);
    EXPECT_EQ(mapping.find("-")->second, 0);
    EXPECT_EQ(mapping.find("*")->second, 1);
    EXPECT_EQ(mapping.find("/")->second, 1);
    EXPECT_EQ(mapping.find("(")->second, 2);
    EXPECT_EQ(mapping.find(")")->second, 2);
}

/**
 * @tc.name: StringExpressionTest002
 * @tc.desc: CheckCalcIsValid()
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest002, TestSize.Level1)
{
    std::string formula;
    EXPECT_TRUE(StringExpression::CheckCalcIsValid(formula));
    formula = "+calc(1,1)-calc(1,1)";
    EXPECT_FALSE(StringExpression::CheckCalcIsValid(formula));
    formula = "(calc{1,1}+calc{1,1}-calc{1,1})";
    EXPECT_TRUE(StringExpression::CheckCalcIsValid(formula));
}

/**
 * @tc.name: StringExpressionTest003
 * @tc.desc: CheckCalcIsValid()
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest003, TestSize.Level1)
{
    std::string formula;
    StringExpression::ReplaceSignNumber(formula);
    EXPECT_EQ(formula, "");
    formula = "+10-10+1.0+2.0+5-1.0";
    StringExpression::ReplaceSignNumber(formula);
    EXPECT_EQ(formula, " (0 + 10) (0 - 10) (0 + 1.0) (0 + 2.0) (0 + 5) (0 - 1.0)");
}

/**
 * @tc.name: StringExpressionTest004
 * @tc.desc: PushOpStack()
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest004, TestSize.Level1)
{
    std::vector<std::string> result;
    std::vector<std::string> opStack;
    std::string curNum;
    std::string formula = "2 * 3 - (2 + 3) / 5 + 6 / 2";
    EXPECT_TRUE(StringExpression::PushOpStack(formula, curNum, result, opStack));
    EXPECT_TRUE(!result.empty());
    EXPECT_TRUE(!opStack.empty());
    EXPECT_TRUE(!curNum.empty());
}

/**
 * @tc.name: StringExpressionTest005
 * @tc.desc: CalculateFourOperationsExp()
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest005, TestSize.Level1)
{
    double opRes = 0.0;
    Dimension num1 = 10.0_px;
    Dimension num2 = 5.0_px;
    std::string formula = "+";
    EXPECT_TRUE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    EXPECT_EQ(opRes, 15.0);
    num1.SetUnit(DimensionUnit::NONE);
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num1.SetUnit(DimensionUnit::PX);
    num2.SetUnit(DimensionUnit::NONE);
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));

    formula = "-";
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num2.SetUnit(DimensionUnit::PX);
    num1.SetUnit(DimensionUnit::NONE);
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num1.SetUnit(DimensionUnit::PX);
    EXPECT_TRUE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    EXPECT_EQ(opRes, -5.0);

    formula = "*";
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num1.SetUnit(DimensionUnit::NONE);
    num2.SetUnit(DimensionUnit::PX);
    EXPECT_TRUE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num1.SetUnit(DimensionUnit::PX);
    num2.SetUnit(DimensionUnit::NONE);
    EXPECT_TRUE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    EXPECT_EQ(opRes, 50.0);

    formula = "/";
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num1.SetUnit(DimensionUnit::NONE);
    EXPECT_TRUE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    num1.SetValue(0.0);
    EXPECT_FALSE(StringExpression::CalculateFourOperationsExp(
        formula, num1, num2, [](const Dimension& dim) -> double { return dim.Value(); }, opRes));
    EXPECT_EQ(opRes, 0.5);
}

/**
 * @tc.name: StringExpressionTest006
 * @tc.desc: CalculateExpImpl()
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest006, TestSize.Level1)
{
    std::vector<std::string> rpnexp = { "2", "3", "*", "2", "3", "+", "5", "6", "/" };
    std::vector<Dimension> result;
    double opRes = 0.0;
    EXPECT_TRUE(StringExpression::CalculateExpImpl(
        rpnexp, [](const Dimension& dim) -> double { return dim.Value(); }, result, opRes));
    rpnexp = { "2_invalid", "*", "3" };
    EXPECT_FALSE(StringExpression::CalculateExpImpl(
        rpnexp, [](const Dimension& dim) -> double { return dim.Value(); }, result, opRes));
    result.clear();
    rpnexp = { "2", "*", "3", "-", "(", "2", "3", "+", "5", "6", "/" };
    EXPECT_FALSE(StringExpression::CalculateExpImpl(
        rpnexp, [](const Dimension& dim) -> double { return dim.Value(); }, result, opRes));
}

/**
 * @tc.name: StringExpressionTest007
 * @tc.desc: ConvertDal2Rpn: ReplaceSignNumberWithUnit()/FilterCalcSpecialString
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringExpressionTest007, TestSize.Level1)
{
    // replace sign number with unit with formula == ""
    std::string formula = "";
    std::vector<std::string> ret = StringExpression::ConvertDal2Rpn(formula);
    EXPECT_EQ(formula, "");
    EXPECT_EQ(ret.size(), 0);

    // replace sign number with unit normal case
    formula = "+1.1px";
    std::vector<std::string> ret2 = StringExpression::ConvertDal2Rpn(formula);
    EXPECT_EQ(ret2.size(), 0);

    formula = "calc(2 * 3 - (2 + 3) / 5 + 6 / 2 + (1 + 2))";
    std::vector<std::string> ret3 = StringExpression::ConvertDal2Rpn(formula);
    EXPECT_EQ(ret3.size(), 17);
}

/**
 * @tc.name: DateUtilsTest001
 * @tc.desc: GetMilliSecondsByDateTime
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, DateUtilsTest001, TestSize.Level1)
{
    std::tm dateTime;
    Date::GetMilliSecondsByDateTime(dateTime);
    EXPECT_EQ(dateTime.tm_year != 0, true);
    EXPECT_EQ(dateTime.tm_mday != 0, true);
    dateTime.tm_mday = 5;
    Date::GetMilliSecondsByDateTime(dateTime);
    EXPECT_EQ(dateTime.tm_year != 0, true);
    EXPECT_EQ(dateTime.tm_mday == 5, true);
    dateTime.tm_year = 8;
    Date::GetMilliSecondsByDateTime(dateTime);
    EXPECT_EQ(dateTime.tm_year == 8, true);
    EXPECT_EQ(dateTime.tm_mday == 5, true);
}

/**
 * @tc.name: StringUtilsTest001
 * @tc.desc: IsAscii
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, StringUtilsTest001, TestSize.Level1)
{
    std::string str = "abcde";
    bool ret = StringUtils::IsAscii(str);
    EXPECT_EQ(ret, true);
    str = "中文";
    bool ret2 = StringUtils::IsAscii(str);
    EXPECT_EQ(ret2, false);
}

/**
 * @tc.name: TimeUtilsTest001
 * @tc.desc: ConvertTimestampToStr
 * @tc.type: FUNC
 */
HWTEST_F(BaseUtilsTest, TimeUtilsTest001, TestSize.Level1)
{
    int64_t timestamp = 1626211200;
    std::string ret = ConvertTimestampToStr(timestamp);
    EXPECT_EQ(ret, "1970-01-20 03:43:31.200");
}
} // namespace OHOS::Ace
