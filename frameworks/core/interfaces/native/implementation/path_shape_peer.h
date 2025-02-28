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

// #pragma once

#include "arkoala_api_generated.h"
#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/dimension_offset.h"
#include "frameworks/base/geometry/shape.h"
#include "core/components/common/properties/color.h"
// #include "core/interfaces/native/utility/converter.h"
#include "frameworks/core/interfaces/native/implementation/basic_shape_peer.h"

using DimensionOffset = OHOS::Ace::DimensionOffset;
using PathShapeOptions = OHOS::Ace::NG::PathShapeOptions;
using Path = OHOS::Ace::Path;
using BasicShape = OHOS::Ace::BasicShape;
using Color = OHOS::Ace::Color;

struct PathShapePeer : public BasicShapePeer {
    public:
        PathShapePeer(PathShapeOptions options) 
        {
            shape_ = OHOS::Ace::AceType::MakeRefPtr<Path>();
            shape_->SetValue(options.commands.value_or(""));
        };
        ~PathShapePeer() = default;
        
        OHOS::Ace::RefPtr<BasicShape> GetBasicShape() override
        {
            return shape_;
        }
        const std::string& GetCommands() const
        {
            return shape_->GetValue();
        }
        void SetCommands(const std::string& commands)
        {
            shape_->SetValue(commands);
        }
        void ResetCommands()
        {
            shape_->SetValue("");
        }
        const DimensionOffset& GetOffset() const
        {
            return shape_->GetOffset();
        }
        void SetOffset(const DimensionOffset& offset)
        {
            shape_->SetOffset(offset);
        }
        void ResetOffset()
        {
            shape_->SetOffset({});
        }
        Color GetFill() const
        {
            return shape_->GetColor();
        }
        void SetFill(const Color& color)
        {
            shape_->SetColor(color);
        }
        void ResetFill()
        {
            shape_->SetColor({});
        }
        const DimensionOffset& GetPosition() const
        {
            return shape_->GetPosition();
        }
        void SetPosition(const DimensionOffset& position)
        {
            shape_->SetPosition(position);
        }
        void ResetPosition()
        {
            shape_->SetPosition({});
        }
    private:
        OHOS::Ace::RefPtr<Path> shape_;
};

namespace OHOS::Ace::NG::GeneratedModifier {
    using PathShapePeerImpl = ::PathShapePeer;
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_SHAPE_PEER_H
