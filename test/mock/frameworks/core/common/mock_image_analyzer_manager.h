/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_MOCK_IMAGE_ANALYZER_MANAGER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_MOCK_IMAGE_ANALYZER_MANAGER_H

#include "core/common/ai/image_analyzer_manager.h"
#include "gmock/gmock.h"

namespace OHOS::Ace {
class MockImageAnalyzerManager : public ImageAnalyzerManager {
    DECLARE_ACE_TYPE(MockImageAnalyzerManager, ImageAnalyzerManager);

public:
    explicit MockImageAnalyzerManager(const RefPtr<NG::FrameNode>& frameNode, ImageAnalyzerHolder holder)
        : ImageAnalyzerManager(frameNode, holder)
    {}
    ~MockImageAnalyzerManager()
    {}
    void SetSupportImageAnalyzerFeature(bool isSupportImageAnalyzerFeature);
    void SetOverlayCreated(bool isOverlayCreated);
    MOCK_METHOD(void, UpdateKeyEvent, (KeyEvent), (override));
    static void SetUp();
    static void TearDown() {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_MOCK_IMAGE_ANALYZER_MANAGER_H