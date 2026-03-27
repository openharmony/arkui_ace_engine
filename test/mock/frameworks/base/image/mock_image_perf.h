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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_IMAGE_PERF_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_IMAGE_PERF_H
#include "gmock/gmock.h"

#include "base/image/image_perf.h"

namespace OHOS::Ace {
class MockImagePerf : public ImagePerf {
public:
    MOCK_METHOD(void, StartRecordImageLoadStat, (int64_t), (override));
    MOCK_METHOD(void, EndRecordImageLoadStat, (int64_t, const std::string&, (std::pair<int, int>), int), (override));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_IMAGE_PERF_H