/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_FONT_COLLECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_FONT_COLLECTION_H

#include <memory>
#include <string>

#include "testing_text_style.h"
#include "testing_typography.h"

namespace OHOS::Ace::Testing {
class TestingFontCollection {
public:
    TestingFontCollection() = default;
    virtual ~TestingFontCollection() = default;

    static std::shared_ptr<TestingFontCollection> GetInstance(bool createWithICU = true)
    {
        return std::make_shared<TestingFontCollection>();
    }

#ifdef USE_GRAPHIC_TEXT_GINE
    static std::shared_ptr<TestingFontCollection> Create()
    {
        return std::make_shared<TestingFontCollection>();
    }

private:
    static std::shared_ptr<TestingFontCollection> instance;
#endif
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_FONT_COLLECTION_H
