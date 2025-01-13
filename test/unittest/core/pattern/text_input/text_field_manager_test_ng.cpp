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

#include <utility>

#include "foundation/graphic/graphic_utils_lite/interfaces/kits/gfx_utils/graphic_types.h"
#include "gtest/gtest.h"
#include "text_input_base.h"

#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TextFieldManagerTestNG : public TextInputBases {
public:
};

/**
 * @tc.name: TextFieldManagerNG_RemoveTextFieldInfo001
 * @tc.desc: test RemoveTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveTextFieldInfo001, TestSize.Level1)
{
    TextFieldInfo info;
    TextFieldManagerNG text_field_manager;
    int32_t key = 1;
    int32_t autoFillContainerNodeId = 0;
    int32_t nodeId = 0;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { key, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(key, unmap));
    text_field_manager.RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
    auto map = text_field_manager.textFieldInfoMap_;
    EXPECT_EQ(map.find(autoFillContainerNodeId), map.end());
}

/**
 * @tc.name: TextFieldManagerNG_RemoveTextFieldInfo002
 * @tc.desc: test RemoveTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveTextFieldInfo002, TestSize.Level1)
{
    TextFieldInfo info;
    TextFieldManagerNG text_field_manager;
    int32_t key = 1;
    int32_t autoFillContainerNodeId = 1;
    int32_t nodeId = 0;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { key, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(key, unmap));
    text_field_manager.RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
    auto map = text_field_manager.textFieldInfoMap_;
    auto innerMap = map.find(autoFillContainerNodeId)->second;
    EXPECT_NE(map.find(autoFillContainerNodeId), map.end());
    EXPECT_EQ(innerMap.find(nodeId), innerMap.end());
}

/**
 * @tc.name: TextFieldManagerNG_RemoveTextFieldInfo003
 * @tc.desc: test RemoveTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveTextFieldInfo003, TestSize.Level1)
{
    TextFieldInfo info;
    TextFieldManagerNG text_field_manager;
    int32_t key = 1;
    int32_t autoFillContainerNodeId = 1;
    int32_t nodeId = 1;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { key, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(key, unmap));
    auto beforeMap = text_field_manager.textFieldInfoMap_;
    auto beforeInnerMap = beforeMap.find(autoFillContainerNodeId)->second;
    EXPECT_NE(beforeInnerMap.find(nodeId), beforeInnerMap.end());
    text_field_manager.RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
    auto afterMap = text_field_manager.textFieldInfoMap_;
    auto afterInnerMap = afterMap.find(autoFillContainerNodeId)->second;
    EXPECT_EQ(afterInnerMap.find(nodeId), afterInnerMap.end());
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo001
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo001, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = -1;
    info.autoFillContainerNodeId = -1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldInfo info_insert;
    info_insert.nodeId = -1;
    info_insert.autoFillContainerNodeId = -1;
    info_insert.inputType = TextInputType::DATETIME;
    info_insert.contentType = TextContentType::BEGIN;
    info_insert.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    text_field_manager.UpdateTextFieldInfo(info_insert);
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto innerMap = map->second;
    auto inputType = innerMap.find(info_insert.nodeId)->second.inputType;
    EXPECT_NE(inputType, TextInputType::DATETIME);
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo002
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo002, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = -1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    text_field_manager.UpdateTextFieldInfo(info);
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto innerMap = map->second;
    EXPECT_NE(innerMap.end(), innerMap.find(info.nodeId));
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo003
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo003, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = 1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldInfo info_insert;
    info_insert.nodeId = 1;
    info_insert.autoFillContainerNodeId = 1;
    info_insert.inputType = TextInputType::DATETIME;
    info_insert.contentType = TextContentType::BEGIN;
    info_insert.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    text_field_manager.UpdateTextFieldInfo(info_insert);
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto innerMap = map->second;
    auto inputType = innerMap.find(info_insert.nodeId)->second.inputType;
    EXPECT_EQ(inputType, TextInputType::DATETIME);
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo004
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo004, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = 1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId + 1, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    EXPECT_EQ(text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId),
        text_field_manager.textFieldInfoMap_.end());
    text_field_manager.UpdateTextFieldInfo(info);
    EXPECT_NE(text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId),
        text_field_manager.textFieldInfoMap_.end());
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo005
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo005, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 2;
    info.autoFillContainerNodeId = 1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldInfo info_insert;
    info_insert.nodeId = 1;
    info_insert.autoFillContainerNodeId = 1;
    info_insert.inputType = TextInputType::DATETIME;
    info_insert.contentType = TextContentType::BEGIN;
    info_insert.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { info.nodeId, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(info.autoFillContainerNodeId, unmap));
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    EXPECT_NE(map, text_field_manager.textFieldInfoMap_.end());
    auto innerMap = map->second;
    EXPECT_NE(innerMap.find(info.nodeId), innerMap.end());
    text_field_manager.UpdateTextFieldInfo(info_insert);
    EXPECT_EQ(text_field_manager.textFieldInfoMap_.find(info.nodeId), text_field_manager.textFieldInfoMap_.end());
    auto afterMap = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto afterInnerMap = afterMap->second;
    auto inputType = afterInnerMap.find(info_insert.nodeId)->second.inputType;
    EXPECT_NE(afterInnerMap.find(info.nodeId), afterInnerMap.end());
    EXPECT_EQ(inputType, TextInputType::DATETIME);
}
} // namespace OHOS::Ace::NG