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
std::pair<InputInfo, ReplacedSpanInfo> NORMAL_INSERT_CASES[] = {
    {{ .spans = "abc|abc", .caret = 0}, /* 0 */
        {.rangeBefore = { 0, 0 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 4 }, .value = u"Aabc"}},
    {{ .spans = "abc|abc", .caret = 1}, /* 1 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 0, .rangeInSpan = { 1, 2 }, .spanRange = { 0, 4 }, .value = u"aAbc"}},
    {{ .spans = "abc|abc", .caret = 3}, /* 2 */
        {.rangeBefore = { 3, 3 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc|abc", .caret = 4}, /* 3 */
        {.rangeBefore = { 4, 4 }, .spanIndex = 1, .rangeInSpan = { 1, 2 }, .spanRange = { 3, 7 }, .value = u"aAbc"}},
    {{ .spans = "abc|abc", .caret = 6}, /* 4 */
        {.rangeBefore = { 6, 6 }, .spanIndex = 1, .rangeInSpan = { 3, 4 }, .spanRange = { 3, 7 }, .value = u"abcA"}},
    {{ .spans = "[IMAGE][IMAGE]", .caret = 0}, /* 5 */
        {.rangeBefore = { 0, 0 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[IMAGE][IMAGE]", .caret = 1}, /* 6 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[IMAGE][IMAGE]", .caret = 2}, /* 7 */
        {.rangeBefore = { 2, 2 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 3 }, .value = u"A"}},
    {{ .spans = "[BUILDER][BUILDER]", .caret = 0}, /* 8 */
        {.rangeBefore = { 0, 0 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[BUILDER][BUILDER]", .caret = 1}, /* 9 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[BUILDER][BUILDER]", .caret = 2}, /* 10 */
        {.rangeBefore = { 2, 2 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 3 }, .value = u"A"}},
    {{ .spans = "[SYMBOL][SYMBOL]", .caret = 0}, /* 11 */
        {.rangeBefore = { 0, 0 }, .spanIndex = 0, .rangeInSpan = { 0, 1 }, .spanRange = { 0, 1 }, .value = u"A"}},
    {{ .spans = "[SYMBOL][SYMBOL]", .caret = 2}, /* 12 */
        {.rangeBefore = { 2, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 3 }, .value = u"A"}},
    {{ .spans = "[SYMBOL][SYMBOL]", .caret = 4}, /* 13 */
        {.rangeBefore = { 4, 4 }, .spanIndex = 2, .rangeInSpan = { 0, 1 }, .spanRange = { 4, 5 }, .value = u"A"}},
    {{ .spans = "abc[IMAGE]", .caret = 3}, /* 14 */
        {.rangeBefore = { 3, 3 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc[BUILDER]", .caret = 3}, /* 15 */
        {.rangeBefore = { 3, 3 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "abc[SYMBOL]", .caret = 3}, /* 16 */
        {.rangeBefore = { 3, 3 }, .spanIndex = 0, .rangeInSpan = { 3, 4 }, .spanRange = { 0, 4 }, .value = u"abcA"}},
    {{ .spans = "[IMAGE]abc", .caret = 1}, /* 17 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 5 }, .value = u"Aabc"}},
    {{ .spans = "[IMAGE][BUILDER]", .caret = 1}, /* 18 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[IMAGE][SYMBOL]", .caret = 1}, /* 19 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[BUILDER]abc", .caret = 1}, /* 20 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 5 }, .value = u"Aabc"}},
    {{ .spans = "[BUILDER][IMAGE]", .caret = 1}, /* 21 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[BUILDER][SYMBOL]", .caret = 1}, /* 22 */
        {.rangeBefore = { 1, 1 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 1, 2 }, .value = u"A"}},
    {{ .spans = "[SYMBOL]abc", .caret = 2}, /* 23 */
        {.rangeBefore = { 2, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 6 }, .value = u"Aabc"}},
    {{ .spans = "[SYMBOL][IMAGE]", .caret = 2}, /* 24 */
        {.rangeBefore = { 2, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 3 }, .value = u"A"}},
    {{ .spans = "[SYMBOL][BUILDER]", .caret = 2}, /* 25 */
        {.rangeBefore = { 2, 2 }, .spanIndex = 1, .rangeInSpan = { 0, 1 }, .spanRange = { 2, 3 }, .value = u"A"}},
};
} // namespace

class RichEditorOnWillTestNormalInsert : public RichEditorOnWillTestCommon {};

#define CREATE_NORMAL_INSERT_CASE(number) \
    CREATE_INSERT_CASE(RichEditorOnWillTestNormalInsert, NORMAL_INSERT_CASES, number)

GENERATE_CASES(26, CREATE_NORMAL_INSERT_CASE);
}