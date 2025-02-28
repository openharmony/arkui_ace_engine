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

#pragma once

#include "arkoala_api_generated.h"
#include "base/memory/ace_type.h"
#include "core/interfaces/native/utility/converter.h"
#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/shape.h"
#include "core/components/common/properties/color.h"
#include "core/interfaces/native/implementation/basic_shape_peer.h"

using DimensionOffset = OHOS::Ace::DimensionOffset;
using Path = OHOS::Ace::Path;
using BasicShape = OHOS::Ace::BasicShape;
using Color = OHOS::Ace::Color;

namespace OHOS::Ace::NG {
struct PathShapeOptions {
    std::optional<std::string> commands;
};
}

struct PathShapePeer : public BasicShapePeer {
    public:
        explicit PathShapePeer(OHOS::Ace::NG::PathShapeOptions options)
        {
            shape = OHOS::Ace::AceType::MakeRefPtr<Path>();
            shape->SetValue(options.commands.value_or(""));
        };
        ~PathShapePeer() = default;

        OHOS::Ace::RefPtr<BasicShape> GetBasicShape() override
        {
            return shape;
        }
        const std::string& GetCommands() const
        {
            return shape->GetValue();
        }
        void SetCommands(const std::string& commands)
        {
            shape->SetValue(commands);
        }
        void ResetCommands()
        {
            shape->SetValue("");
        }
        const DimensionOffset& GetOffset() const
        {
            return shape->GetOffset();
        }
        void SetOffset(const DimensionOffset& offset)
        {
            shape->SetOffset(offset);
        }
        void ResetOffset()
        {
            shape->SetOffset({});
        }
        Color GetFill() const
        {
            return shape->GetColor();
        }
        void SetFill(const Color& color)
        {
            shape->SetColor(color);
        }
        void ResetFill()
        {
            shape->SetColor({});
        }
        const DimensionOffset& GetPosition() const
        {
            return shape->GetPosition();
        }
        void SetPosition(const DimensionOffset& position)
        {
            shape->SetPosition(position);
        }
        void ResetPosition()
        {
            shape->SetPosition({});
        }
        OHOS::Ace::RefPtr<Path> shape;
};

namespace OHOS::Ace::NG::GeneratedModifier {
    using PathShapePeerImpl = ::PathShapePeer;
} // namespace OHOS::Ace::NG::GeneratedModifier

