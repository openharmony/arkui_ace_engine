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

#include "irregular_matrices.h"

namespace OHOS::Ace::NG {
GridLayoutOptions GetOptionDemo1()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,  // [2 x 1]
        1,  // [1 x 3]
        2,  // [2 x 1]
        5,  // [1 x 4]
        7,  // [1 x 2]
        9,  // [1 x 2]
        10, // [1 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        switch (index) {
            case 0:
                return { .columns = 2, .rows = 1 };
            case 1:
                return { .columns = 1, .rows = 3 };
            case 2:
                return { .columns = 2, .rows = 1 };
            case 5:
                return { .columns = 1, .rows = 4 };
            default:
                return { .columns = 1, .rows = 2 };
        }
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo2()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        1, // [1 x 3]
        4, // [3 x 1]
        5, // [1 x 2]
        7, // [1 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 3, .columns = 1 };
        }
        if (index == 0) {
            return { 2, 2 };
        }
        if (index == 4) {
            return { .rows = 1, .columns = 3 };
        }
        return { .rows = 2, .columns = 1 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo5()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        2, // [2 x 1]
        3, // [2 x 4]
        4, // [2 x 1]
        5, // [1 x 2]
        8, // [2 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 1, .columns = 2 };
        }
        if (index == 3) {
            return { .rows = 4, .columns = 2 };
        }
        if (index == 4) {
            return { .rows = 1, .columns = 2 };
        }
        if (index == 5) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 2, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo6()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        2,  // [2 x 1]
        5,  // [2 x 1]
        10, // [2 x 1]
    };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize { return { .rows = 1, .columns = 2 }; };
    return option;
}

GridLayoutOptions GetOptionDemo8()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        2, // [3 x 2]
        5, // [1 x 3]
        6, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 2, .columns = 3 };
        }
        if (index == 5) {
            return { .rows = 3, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo9()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 2]
        3, // [2 x 2]
        6, // [3 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 3) {
            return { 2, 2 };
        }
        return { .rows = 2, .columns = 3 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo10()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 1]
        1, // [2 x 1]
        2, // [1 x 1]
        3, // [2 x 2]
        4, // [1 x 1]
        5, // [1 x 1]
        6, // [1 x 2]
        7, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 6) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 0 || index == 2 || index == 5 || index == 4) {
            return { 1, 1 };
        }
        if (index == 3) {
            return { 2, 2 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo11()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        3, // [1 x 2]
        4, // [1 x 2]
        6, // [3 x 2]
    };

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { 2, 2 };
        }
        if (index == 6) {
            return { .rows = 2, .columns = 3 };
        }
        return { .rows = 2, .columns = 1 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo12()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        2, // [1 x 6]
    };

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { 2, 2 };
        }
        return { .rows = 6, .columns = 1 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo13()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [5 x 3]
        2, // [2 x 2]
        3, // [3 x 6]
    };

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 3, .columns = 5 };
        }
        if (index == 2) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 6, .columns = 3 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo14()
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,
        2,
        22,
    };

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0 || index == 2) {
            return { .rows = 2, .columns = 3 };
        }
        return { .rows = 6, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo15()
{
    GridLayoutOptions option;
    option.irregularIndexes = { 0, 1, 7, 12 };

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 3, .columns = 2 };
        }
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 7) {
            return { 2, 2 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo16()
{
    GridLayoutOptions option = GetOptionDemo15();
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0 || index == 12) {
            return { .rows = 3, .columns = 2 };
        }
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        return { 2, 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    return option;
}

GridLayoutOptions GetOptionDemo17()
{
    GridLayoutOptions option;
    option.irregularIndexes = { 0, 1, 2, 3, 4 };

    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index < 2) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 2 };
    };
    return option;
}
} // namespace OHOS::Ace::NG