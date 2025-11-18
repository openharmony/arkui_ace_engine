/*
 * Copyright (c) 2024-2024 Huawei Device Co., Ltd.
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

#include <iostream>

#include <libunwind.h>

#include "modifier_test_base.h"

#define MIN_FRAME 4
#define MAX_FRAME 64
#define BUF_SZ 512

namespace OHOS::Ace::NG {

static std::set<std::string> reportedThemes;

static const std::string GET_THEME_PREFIX("_ZN4OHOS3Ace12ThemeManager8GetThemeINS0_");

std::string ProcessBacktrace(void)
{
    unw_context_t context;
    unw_getcontext(&context);

    unw_cursor_t cursor;
    unw_init_local(&cursor, &context);

    unw_word_t pc;
    unw_word_t prevPc;
    bool shouldContinue = true;
    for (int index = 0; index < MAX_FRAME; index++) {
        if (unw_get_reg(&cursor, UNW_REG_IP, (unw_word_t*)(&pc))) {
            break;
        }

        if (index > MIN_FRAME && prevPc == pc) {
            break;
        }
        prevPc = pc;

        char sym[BUF_SZ];
        unw_word_t offset;
        if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
            //std::cout << sym << std::endl;
            auto str = std::string(sym);
            if (str.substr(0, GET_THEME_PREFIX.size()) == GET_THEME_PREFIX) {
                std::size_t pos;
                auto len = std::stoi(str.substr(GET_THEME_PREFIX.size()), &pos);
                auto themeName = str.substr(GET_THEME_PREFIX.size() + pos, len);
                return themeName;
            }
        }

        if (!shouldContinue) {
            break;
        }

        int ret = unw_step(&cursor);
        if (ret == 0) {
            shouldContinue = false;
        } else if (ret < 0) {
            break;
        }
    }
    return "";
}

void ReportTheme(ThemeType type)
{
    auto theme = ProcessBacktrace();
    if (theme == "") {
        theme = std::to_string(type);
        if (reportedThemes.count(theme)) {
            return;
        }
        reportedThemes.insert(theme);
        std::cout << "GetTheme<>() function was called, but information in stack is not found!\n";
        std::cout << "TypeId() of requested theme is: " << type << "\n";
    } else {
        if (reportedThemes.count(theme)) {
            return;
        }
        reportedThemes.insert(theme);
        std::cout << "GetTheme<" << theme << ">() function was called.";
        std::cout << " And since this theme was not setup nullptr will be returned!\n";
        std::cout << "If you see crash, that is probably because of this theme!\n";
    }
}

void ResetThemes()
{
    reportedThemes.clear();
}
} //namespace OHOS::Ace::NG
