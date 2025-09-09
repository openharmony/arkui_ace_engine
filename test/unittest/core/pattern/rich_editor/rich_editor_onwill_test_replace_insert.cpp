 /*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/rich_editor/rich_editor_onwill_test_common.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
std::pair<InputInfo, ReplacedSpanInfo> REPLACE_INSERT_CASES[] = {
    {{ .spans = "abc|abc|abc", .selector = { 0, 1 }}, /* 0 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc|abc|abc", .selector = { 0, 2 }}, /* 1 */
        {.rangeBefore = { 0, 2 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 2 }, .value = u"Ac"}},
    {{ .spans = "abc|abc|abc", .selector = { 0, 3 }}, /* 2 */
        {.rangeBefore = { 0, 3 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "abc|abc|abc", .selector = { 0, 4 }}, /* 3 */
        {.rangeBefore = { 0, 4 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc|abc|abc", .selector = { 0, 5 }}, /* 4 */
        {.rangeBefore = { 0, 5 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 2 }, .value = u"Ac"}},
    {{ .spans = "abc|abc|abc", .selector = { 0, 6 }}, /* 5 */
        {.rangeBefore = { 0, 6 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "abc|abc|abc", .selector = { 0, 7 }}, /* 6 */
        {.rangeBefore = { 0, 7 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc|abc|abc", .selector = { 1, 2 }}, /* 7 */
        {.rangeBefore = { 1, 2 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 3 }, .value = u"aAc"}},
    {{ .spans = "abc|abc|abc", .selector = { 1, 3 }}, /* 8 */
        {.rangeBefore = { 1, 3 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc|abc|abc", .selector = { 1, 4 }}, /* 9 */
        {.rangeBefore = { 1, 4 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc|abc|abc", .selector = { 1, 6 }}, /* 10 */
        {.rangeBefore = { 1, 6 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc|abc|abc", .selector = { 1, 7 }}, /* 11 */
        {.rangeBefore = { 1, 7 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},

    {{ .spans = "[IMAGE]abc|abc", .selector = { 0, 1 }}, /* 12 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 0, 2 }}, /* 13 */
        {.rangeBefore = { 0, 2 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 0, 4 }}, /* 14 */
        {.rangeBefore = { 0, 4 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 0, 5 }}, /* 15 */
        {.rangeBefore = { 0, 5 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 0, 7 }}, /* 16 */
        {.rangeBefore = { 0, 7 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 1, 2 }}, /* 17 */
        {.rangeBefore = { 1, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 4 }, .value = u"Abc"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 1, 4 }}, /* 18 */
        {.rangeBefore = { 1, 4 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 5 }, .value = u"Aabc"}},
    {{ .spans = "[IMAGE]abc|abc", .selector = { 1, 5 }}, /* 19 */
        {.rangeBefore = { 1, 5 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 4 }, .value = u"Abc"}},

    {{ .spans = "[SYMBOL]abc|abc", .selector = { 0, 2 }}, /* 20 */
        {.rangeBefore = { 0, 2 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 0, 3 }}, /* 21 */
        {.rangeBefore = { 0, 3 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 0, 5 }}, /* 22 */
        {.rangeBefore = { 0, 5 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 0, 6 }}, /* 23 */
        {.rangeBefore = { 0, 6 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 0, 8 }}, /* 24 */
        {.rangeBefore = { 0, 8 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 2, 3 }}, /* 25 */
        {.rangeBefore = { 2, 3 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 5 }, .value = u"Abc"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 2, 5 }}, /* 26 */
        {.rangeBefore = { 2, 5 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 6 }, .value = u"Aabc"}},
    {{ .spans = "[SYMBOL]abc|abc", .selector = { 2, 6 }}, /* 27 */
        {.rangeBefore = { 2, 6 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 5 }, .value = u"Abc"}},

    {{ .spans = "abc[IMAGE]abc", .selector = { 0, 1 }}, /* 28 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 0, 3 }}, /* 29 */
        {.rangeBefore = { 0, 3 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 0, 4 }}, /* 30 */
        {.rangeBefore = { 0, 4 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 0, 5 }}, /* 31 */
        {.rangeBefore = { 0, 5 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 1, 2 }}, /* 32 */
        {.rangeBefore = { 1, 2 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 3 }, .value = u"aAc"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 1, 3 }}, /* 33 */
        {.rangeBefore = { 1, 3 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 1, 4 }}, /* 34 */
        {.rangeBefore = { 1, 4 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 1, 5 }}, /* 35 */
        {.rangeBefore = { 1, 5 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 2, 3 }}, /* 36 */
        {.rangeBefore = { 2, 3 }, .spanIndex = 0, .rangeInSpan = { 2, 3 }, .spanRange = { 0, 3 }, .value = u"abA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 2, 4 }}, /* 37 */
        {.rangeBefore = { 2, 4 }, .spanIndex = 0, .rangeInSpan = { 2, 3 }, .spanRange = { 0, 3 }, .value = u"abA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 2, 5 }}, /* 38 */
        {.rangeBefore = { 2, 5 }, .spanIndex = 0, .rangeInSpan = { 2, 3 }, .spanRange = { 0, 3 }, .value = u"abA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 3, 4 }}, /* 39 */
        {.rangeBefore = { 3, 4 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 3, 5 }}, /* 40 */
        {.rangeBefore = { 3, 5 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 4, 5 }}, /* 41 */
        {.rangeBefore = { 4, 5 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 4, 7 }, .value = u"Abc"}},
    {{ .spans = "abc[IMAGE]abc", .selector = { 4, 7 }}, /* 42 */
        {.rangeBefore = { 4, 7 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 4, 5 }, .value = u"A"}},

    {{ .spans = "abc[SYMBOL]abc", .selector = { 0, 1 }}, /* 43 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 0, 3 }}, /* 44 */
        {.rangeBefore = { 0, 3 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 0, 5 }}, /* 45 */
        {.rangeBefore = { 0, 5 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 0, 6 }}, /* 46 */
        {.rangeBefore = { 0, 6 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 1, 2 }}, /* 47 */
        {.rangeBefore = { 1, 2 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 3 }, .value = u"aAc"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 1, 3 }}, /* 48 */
        {.rangeBefore = { 1, 3 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 1, 5 }}, /* 49 */
        {.rangeBefore = { 1, 5 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 1, 6 }}, /* 50 */
        {.rangeBefore = { 1, 6 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 2 }, .value = u"aA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 2, 3 }}, /* 51 */
        {.rangeBefore = { 2, 3 }, .spanIndex = 0, .rangeInSpan = { 2, 3 }, .spanRange = { 0, 3 }, .value = u"abA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 2, 5 }}, /* 52 */
        {.rangeBefore = { 2, 5 }, .spanIndex = 0, .rangeInSpan = { 2, 3 }, .spanRange = { 0, 3 }, .value = u"abA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 2, 6 }}, /* 53 */
        {.rangeBefore = { 2, 6 }, .spanIndex = 0, .rangeInSpan = { 2, 3 }, .spanRange = { 0, 3 }, .value = u"abA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 3, 5 }}, /* 54 */
        {.rangeBefore = { 3, 5 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 3, 6 }}, /* 55 */
        {.rangeBefore = { 3, 6 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 5, 6 }}, /* 56 */
        {.rangeBefore = { 5, 6 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 5, 8 }, .value = u"Abc"}},
    {{ .spans = "abc[SYMBOL]abc", .selector = { 5, 8 }}, /* 57 */
        {.rangeBefore = { 5, 8 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 5, 6 }, .value = u"A"}},

    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 0, 1 }}, /* 58 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 0, 2 }}, /* 59 */
        {.rangeBefore = { 0, 2 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 3 }, .value = u"Abc"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 0, 4 }}, /* 60 */
        {.rangeBefore = { 0, 4 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 0, 5 }}, /* 61 */
        {.rangeBefore = { 0, 5 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 1, 2 }}, /* 62 */
        {.rangeBefore = { 1, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 4 }, .value = u"Abc"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 1, 4 }}, /* 63 */
        {.rangeBefore = { 1, 4 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 1, 5 }}, /* 64 */
        {.rangeBefore = { 1, 5 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 2, 3 }}, /* 65 */
        {.rangeBefore = { 2, 3 }, .spanIndex = 1, .rangeInSpan = { 1, 2 }, .spanRange = { 1, 4 }, .value = u"aAc"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 2, 4 }}, /* 66 */
        {.rangeBefore = { 2, 4 }, .spanIndex = 1, .rangeInSpan = { 1, 2 }, .spanRange = { 1, 3 }, .value = u"aA"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 2, 5 }}, /* 67 */
        {.rangeBefore = { 2, 5 }, .spanIndex = 1, .rangeInSpan = { 1, 2 }, .spanRange = { 1, 3 }, .value = u"aA"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 3, 4 }}, /* 68 */
        {.rangeBefore = { 3, 4 }, .spanIndex = 1, .rangeInSpan = { 2, 3 }, .spanRange = { 1, 4 }, .value = u"abA"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 3, 5 }}, /* 69 */
        {.rangeBefore = { 3, 5 }, .spanIndex = 1, .rangeInSpan = { 2, 3 }, .spanRange = { 1, 4 }, .value = u"abA"}},
    {{ .spans = "[IMAGE]abc[IMAGE]", .selector = { 4, 5 }}, /* 70 */
        {.rangeBefore = { 4, 5 }, .spanIndex = 1, .rangeInSpan = { 3, 4 }, .spanRange = { 1, 5 }, .value = u"abcA"}},

    {{ .spans = "[IMAGE][IMAGE][IMAGE]", .selector = { 0, 1 }}, /* 71 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[IMAGE][IMAGE][IMAGE]", .selector = { 1, 2 }}, /* 72 */
        {.rangeBefore = { 1, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[IMAGE][IMAGE][IMAGE]", .selector = { 2, 3 }}, /* 73 */
        {.rangeBefore = { 2, 3 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 3 }, .value = u"A"}},

    {{ .spans = "[IMAGE][SYMBOL][IMAGE]", .selector = { 0, 1 }}, /* 74 */
        {.rangeBefore = { 0, 1 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[IMAGE][SYMBOL][IMAGE]", .selector = { 1, 3 }}, /* 75 */
        {.rangeBefore = { 1, 3 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[IMAGE][SYMBOL][IMAGE]", .selector = { 3, 4 }}, /* 76 */
        {.rangeBefore = { 3, 4 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 3, 4 }, .value = u"A"}},
};

} // namespace

class RichEditorOnWillTestReplaceInsert : public RichEditorOnWillTestCommon {};

#define CREATE_REPLACE_INSERT_CASE(number) \
    CREATE_INSERT_CASE(RichEditorOnWillTestReplaceInsert, REPLACE_INSERT_CASES, number)

GENERATE_CASES(77, CREATE_REPLACE_INSERT_CASE);
}