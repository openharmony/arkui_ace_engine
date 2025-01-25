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
#include <cstdint>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
struct VisibleRange {
    VisibleRange(FrameNode* parent, int32_t indexUp, int32_t indexDown)
        : parent_(parent), indexUp_(indexUp), indexDown_(indexDown)
    {}

    bool NeedFillUp();

    bool NeedFillDown();

    FrameNode* parent_ {};
    FrameNode* markUp_ {};
    FrameNode* markDown_ {};
    int32_t indexUp_;
    int32_t indexDown_;
};

class MockKoalaLazyForEach {
public:
    MockKoalaLazyForEach(FrameNode* parent, int32_t totalCnt, std::function<RefPtr<FrameNode>(int32_t)>&& itemCreator)
        : itemCreator_(itemCreator), parent_(parent), totalCnt_(totalCnt)
    {}
    void Update(int32_t s, int32_t e, void* pointer);

    void RangeModeUpdate(int32_t s, int32_t e);

    void NormalModeUpdate(int32_t s, int32_t e, void* pointer);

    RefPtr<FrameNode> CreateItem(int32_t idx);

    /**
     * @brief mock trigger frontend update
     *
     */
    void Increment();

private:
    std::function<RefPtr<FrameNode>(int32_t)> itemCreator_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> itemCache_;
    FrameNode* parent_;
    int32_t totalCnt_;
    std::queue<std::function<void()>> taskQ_;
};
} // namespace OHOS::Ace::NG
