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
#ifndef OHOS_GLOBAL_I18N_DATE_TIME_SEQUENCE_H
#define OHOS_GLOBAL_I18N_DATE_TIME_SEQUENCE_H

#include <string>
#include <unordered_map>

namespace OHOS::Ace {

struct OrderResult {
    /**
     * the year,month and day sequence,
     * empty value represent call interface failed
     */
    std::string dateOrder;

    /**
     * 0 represent time position, 1 represent date position
     * -1 represent call interface failed
     */
    std::string dateTimeOrder;

    /**
     * 0 represent am/pm position, 1 represent time position
     * -1 represent call interface failed
     */
    std::string amPmTimeOrder;

    // whether datetime format string starts with zero
    bool startsWithZero;
};

class DateTimeSequence {
public:
   static OrderResult GetDateOrder(const std::string& locale);
   static OrderResult GetDateTimeOrder(const std::string& locale);
   static OrderResult GetAmPmTimeOrder(const std::string& locale);

private:
   static std::string ModifyOrder(std::string& pattern);
   static void ProcessNormal(char ch, int* order, size_t orderSize, int* lengths, size_t lengsSize);
};
} // namespace OHOS::Ace
#endif