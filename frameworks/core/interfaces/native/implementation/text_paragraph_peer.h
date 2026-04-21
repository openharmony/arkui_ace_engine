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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_PARAGRAPH_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_PARAGRAPH_PEER_H

#include <cstdint>

#include "typography.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct text_ParagraphPeer final {
    using Paragraph = OHOS::Rosen::Typography;
    std::unique_ptr<Paragraph> paragraph = nullptr;
    void* paragraphAni = nullptr;

protected:
    explicit text_ParagraphPeer(std::unique_ptr<Paragraph> paragraph) : paragraph(std::move(paragraph)) {};
    ~text_ParagraphPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_PARAGRAPH_PEER_H