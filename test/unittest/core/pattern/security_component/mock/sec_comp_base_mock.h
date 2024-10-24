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
#ifndef ACE_MOCK_SECURITY_COMPONENT_BASE_H
#define ACE_MOCK_SECURITY_COMPONENT_BASE_H

#include <cstdint>
#include <string>

namespace OHOS {
namespace Security {
namespace SecurityComponent {
struct PaddingSize {
    double top;
    double right;
    double bottom;
    double left;
};

enum SecCompType {
    UNKNOWN_SC_TYPE = 0,
    LOCATION_COMPONENT,
    PASTE_COMPONENT,
    SAVE_COMPONENT,
    MAX_SC_TYPE
};

union SecCompColor {
    struct {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
    } argb;
    uint32_t value;
};

struct SecCompRect {
    double x_;
    double y_;
    double width_;
    double height_;
};

enum class SecCompBackground {
    UNKNOWN_BG = -2,
    NO_BG_TYPE = -1,
    CAPSULE = 0,
    CIRCLE = 1,
    NORMAL = 2,
    MAX_BG_TYPE
};

class SecCompBase {
public:
    SecCompBase() = default;
    virtual ~SecCompBase() = default;
    std::string ToJsonStr(void) const
    {
        return "";
    };

    // size
    double fontSize_;
    double iconSize_;
    PaddingSize padding_;
    double textIconSpace_;

    // color
    SecCompColor fontColor_;
    SecCompColor iconColor_;
    SecCompColor bgColor_;

    // border
    double borderWidth_;

    // parent effect
    bool parentEffect_ = false;
    bool isParentCheckFailed_ = false;
    bool isClipped_ = false;
    double topClip_;
    double bottomClip_;
    double leftClip_;
    double rightClip_;
    std::string parentTag_;

    SecCompType type_ = UNKNOWN_SC_TYPE;
    SecCompRect rect_;
    SecCompRect windowRect_;
    bool isValid_ = false;

    int32_t text_;
    int32_t icon_;
    SecCompBackground bg_;

    int32_t windowId_;
    int32_t nodeId_;
};
}  // namespace SecurityComponent
}  // namespace Security
}  // namespace OHOS
#endif  // ACE_MOCK_SECURITY_COMPONENT_BASE_H
