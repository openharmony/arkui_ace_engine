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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TEXT_BLOB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TEXT_BLOB_H

namespace OHOS::Ace::Testing {

enum class TestingTextEncoding {
    UTF8,
    UTF16,
    UTF32,
    GLYPH_ID,
};

class TestingTextBlob {
public:
    TestingTextBlob() = default;
    ~TestingTextBlob() = default;
    static std::shared_ptr<TestingTextBlob> MakeFromText(const void* text, size_t byteLength,
        const TestingFont& font,TestingTextEncoding encoding = TestingTextEncoding::UTF8)
    {
        return std::make_shared<TestingTextBlob>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TEXT_BLOB_H