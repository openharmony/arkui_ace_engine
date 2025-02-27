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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_SHAPE_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_SHAPE_PEER_H

#include "core/components/common/properties/color.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

// namespace Converter {
//     template<>
//     PathShapeOptions Convert(const Ark_PathShapeOptions& value)
//     {
//         return {.commands = Converter::OptConvert<std::string>(value.commands)};
//     };
//     template<>
//     PathShapePosition Convert(const Ark_Position& value)
//     {
//         return {.x = Converter::OptConvert<InteropLength>(value.x),
//             .y = Converter::OptConvert<InteropLength>(value.y)};
//     };
// }
}

struct PathShapePeer {
    public:
        PathShapePeer(OHOS::Ace::NG::PathShapeOptions options): commands_(options.commands.value_or("")) {};
        ~PathShapePeer(){};
        std::string GetCommands() const
        {
            return commands_;
        }
        OHOS::Ace::NG::PathShapePosition GetOffset() const
        {
            return offset_;
        }
        OHOS::Ace::Color GetFill() const
        {
            return fill_;
        }
        OHOS::Ace::NG::PathShapePosition GetPosition() const
        {
            return position_;
        }
        void SetCommands(std::string commands)
        {
            commands_ = commands;
        }
        void ResetCommands()
        {
            commands_ = "";
        }
        void SetOffset(OHOS::Ace::NG::PathShapePosition offset)
        {
            offset_ = offset;
        }
        void ResetOffset()
        {
            offset_ = {};
        }
        void SetFill(OHOS::Ace::Color color)
        {
            fill_ = color;
        }
        void ResetFill()
        {
            fill_ = {};
        }
        void SetPosition(OHOS::Ace::NG::PathShapePosition position)
        {
            position_ = position;
        }
        void ResetPosition()
        {
            position_ = {};
        }
    private:
        std::string commands_ = "";
        OHOS::Ace::NG::PathShapePosition offset_ = {};
        OHOS::Ace::Color fill_;
        OHOS::Ace::NG::PathShapePosition position_ = {};
};

namespace OHOS::Ace::NG::GeneratedModifier {
    using PathShapePeerImpl = ::PathShapePeer;
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_SHAPE_PEER_H
