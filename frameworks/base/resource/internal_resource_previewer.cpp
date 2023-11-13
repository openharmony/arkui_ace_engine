/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <map>

#include "base/log/log.h"
#include "base/resource/internal_resource.h"

// binary/errorcode.json
// Use objcopy transform to compiled object file.
// The following parameters represent the beginning and end of the file.
extern uint8_t _binary_errorcode_json_start[];
extern uint8_t* _binary_errorcode_json_end;

// binary/indexletter_bar.json
// Use objcopy transform to compiled object file.
// The following parameters represent the beginning and end of the file.
extern uint8_t _binary_indexletter_bar_json_start[];
extern uint8_t* _binary_indexletter_bar_json_end;

// binary/entry.json
// Use objcopy transform to compiled object file.
// The following parameters represent the beginning and end of the file.
extern uint8_t _binary_entry_json_start[];
extern uint8_t* _binary_entry_json_end;

namespace OHOS::Ace {
namespace {

struct ResourceData final {
    ResourceData(const uint8_t* buf, size_t size) : buf(buf), size(size) {}
    ~ResourceData() = default;

    const uint8_t* buf;
    size_t size;
};

} // namespace

InternalResource::InternalResource() = default;

InternalResource::~InternalResource() = default;

const uint8_t* InternalResource::GetResource(const ResourceId id, size_t& size) const
{
    static const std::map<InternalResource::ResourceId, ResourceData> RESOURCE_MAP = {
        { InternalResource::ResourceId::ERRORINFO_JSON,
            ResourceData(_binary_errorcode_json_start,
                static_cast<size_t>(_binary_errorcode_json_end - _binary_errorcode_json_start)) },
        { InternalResource::ResourceId::INDEXLETTER_BAR_JSON,
            ResourceData(_binary_indexletter_bar_json_start,
                static_cast<size_t>(_binary_indexletter_bar_json_end - _binary_indexletter_bar_json_start)) },
        { InternalResource::ResourceId::ENTRY_JSON,
            ResourceData(
                _binary_entry_json_start, static_cast<size_t>(_binary_entry_json_end - _binary_entry_json_start)) },
    };
    auto iter = RESOURCE_MAP.find(id);
    if (iter != RESOURCE_MAP.end()) {
        size = iter->second.size;
        return iter->second.buf;
    }
    return nullptr;
}

} // namespace OHOS::Ace
