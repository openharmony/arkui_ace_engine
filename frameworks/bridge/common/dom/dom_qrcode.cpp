/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_qrcode.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMQrcode::DOMQrcode(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    qrcodeChild_ = AceType::MakeRefPtr<QrcodeComponent>();
}

void DOMQrcode::ResetInitializedStyle()
{
    InitializeStyle();
}

bool DOMQrcode::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(DOMQrcode&, const std::string&)> qrcodeAttrOperators[] = {
        { DOM_QRCODE_TYPE,
            [](DOMQrcode& qrcode,
                const std::string& value) { qrcode.qrcodeChild_->SetQrcodeType(ConvertStrToQrcodeType(value)); } },
        { DOM_QRCODE_VALUE,
            [](DOMQrcode& qrcode, const std::string& value) { qrcode.qrcodeChild_->SetValue(value); } },
    };
    auto operatorIter = BinarySearchFindIndex(qrcodeAttrOperators, ArraySize(qrcodeAttrOperators), attr.first.c_str());
    if (operatorIter != -1) {
        qrcodeAttrOperators[operatorIter].value(*this, attr.second);
        return true;
    }
    return false;
}

bool DOMQrcode::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    const static LinearMapNode<void (*)(DOMQrcode&, const std::string&)> qrcodeOperators[] = {
        { DOM_QRCODE_BACKGROUND_COLOR,
            [](DOMQrcode& qrcode, const std::string& value) {
                qrcode.qrcodeChild_->SetBackgroundColor(qrcode.ParseColor(value));
            } },
        { DOM_QRCODE_COLOR,
            [](DOMQrcode& qrcode, const std::string& value) {
                qrcode.qrcodeChild_->SetQrcodeColor(qrcode.ParseColor(value));
            } },
        { DOM_QRCODE_HEIGHT,
            [](DOMQrcode& qrcode, const std::string& value) {
                qrcode.qrcodeChild_->SetQrcodeHeight(qrcode.ParseDimension(value));
                qrcode.qrcodeChild_->SetHeightDefined(true);
            } },
        { DOM_QRCODE_WIDTH,
            [](DOMQrcode& qrcode, const std::string& value) {
                qrcode.qrcodeChild_->SetQrcodeWidth(qrcode.ParseDimension(value));
                qrcode.qrcodeChild_->SetWidthDefined(true);
            } },
    };
    auto operatorIter = BinarySearchFindIndex(qrcodeOperators, ArraySize(qrcodeOperators), style.first.c_str());
    if (operatorIter != -1) {
        qrcodeOperators[operatorIter].value(*this, style.second);
        return true;
    }
    return false;
}

void DOMQrcode::InitializeStyle()
{
    qrcodeTheme_ = GetTheme<QrcodeTheme>();
    if (!qrcodeTheme_) {
        LOGE("qrcodeTheme is null");
        return;
    }
    qrcodeChild_->SetQrcodeColor(qrcodeTheme_->GetQrcodeColor());
    qrcodeChild_->SetBackgroundColor(qrcodeTheme_->GetBackgroundColor());
    qrcodeChild_->SetQrcodeType(qrcodeTheme_->GetQrcodeType());
    qrcodeChild_->SetQrcodeWidth(qrcodeTheme_->GetQrcodeWidth());
    qrcodeChild_->SetQrcodeHeight(qrcodeTheme_->GetQrcodeHeight());
}

} // namespace OHOS::Ace::Framework
