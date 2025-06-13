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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/qrcode/qrcode_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT QRCodeModelNG : public OHOS::Ace::QRCodeModel {
public:
    void Create(const std::string& value) override;
    void SetQRCodeColor(const Color& color) override;
    void SetQRBackgroundColor(const Color& color) override;
    void SetContentOpacity(const double opacity) override;
    void CreateWithResourceObj(QRCodeResourceType jsResourceType, const RefPtr<ResourceObject>& resObj) override;
    
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetQRCodeValue(FrameNode* frameNode, const std::string& value);
    static void SetQRCodeColor(FrameNode* frameNode, const Color& color);
    static void SetQRBackgroundColor(FrameNode* frameNode, const Color& color);
    static void SetContentOpacity(FrameNode* frameNode, const double opacity);
    static void CreateWithResourceObj(
        FrameNode* frameNode, QRCodeResourceType jsResourceType, const RefPtr<ResourceObject>& resObj);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODEL_NG_H
