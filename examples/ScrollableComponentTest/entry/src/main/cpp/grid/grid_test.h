/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GRID_TEST_H
#define GRID_TEST_H

#include "common.h"
#include "components/grid/Grid1.h"

namespace ArkUICApiDemo {

class GridTest {
public:
    ~GridTest();
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);

private:
    static std::shared_ptr<GridComponent> CreatGrid(int32_t type);
    static std::shared_ptr<GridComponent> CreatGrid1(int32_t type);
    static std::shared_ptr<GridComponent> CreatGrid2(int32_t type);
    static std::shared_ptr<GridComponent> CreatGrid3(int32_t type);
    static std::shared_ptr<GridComponent> CreatGrid4(int32_t type);
    static int32_t edgeEffectIndex_;
    static int32_t modeIndex_;
    static int32_t widthIndex_;
    static int32_t colorIndex_;
    static int32_t rowGapIndex_;
    static int32_t enableScrollIndex_;
    static int32_t alignItemsIndex_;
    static int32_t flingSpeedLimitIndex_;
    static int32_t frictionIndex_;
    static int32_t clipModeIndex_;
    static int32_t fadingEdgeIndex_;
    static int32_t nestedModeIndex_;
    static int32_t itemStyleIndex_;
    static int32_t backToTopIndex_;
};
} // namespace ArkUICApiDemo

#endif // CAPIDEMO_GRID_TEST_H
