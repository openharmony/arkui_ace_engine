/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MOCK_MATRIX2D_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MOCK_MATRIX2D_H

#include "frameworks/core/components/common/properties/paint_state.h"

namespace OHOS::Ace::NG {
class Matrix2DHolder {
public:
    Matrix2DHolder() = default;
    ~Matrix2DHolder() = default;

    static Matrix2DHolder* GetInstance()
    {
        static Matrix2DHolder instance;
        return &instance;
    }
    void SetUp()
    {
        isCalled = false;
        counter = 0;
        request = true;
    }
    void TearDown()
    {
        isCalled = false;
        counter = 0;
        request = false;
    }
public:
    bool request = false;
    bool isCalled = false;    
    int counter = 0;
    TransformParam param;

};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MOCK_MATRIX2D_H

