/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/hyperlink_modifier.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_static.h"

#include "core/components_ng/pattern/hyperlink/bridge/hyperlink_model_impl.h"

namespace OHOS::Ace {
std::unique_ptr<HyperlinkModel> HyperlinkModel::instance_ = nullptr;
std::mutex HyperlinkModel::mutex_;
HyperlinkModel* HyperlinkModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::HyperlinkModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::HyperlinkModelNG());
            } else {
                instance_.reset(new Framework::HyperlinkModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
} // namespace

void Create(const std::string& address, const std::string& content)
{
    HyperlinkModel::GetInstance()->Create(address, content);
}

void SetHyperlinkColor(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetColor(frameNode, Color(color));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        pattern->RegisterResource<Color>("Color", resObj, Color(color));
    } else {
        pattern->UnRegisterResource("Color");
    }
}

void ResetHyperlinkColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto hyperlinkTheme = themeManager->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(hyperlinkTheme);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("Color");
    HyperlinkModelNG::SetColor(frameNode, Color(hyperlinkTheme->GetTextColor()));
}

void SetHyperlinkDraggable(ArkUINodeHandle node, ArkUI_Bool draggable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetDraggable(frameNode, draggable);
}

void ResetHyperlinkDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetDraggable(frameNode, false);
}

void SetHyperlinkResponseRegion(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (int32_t i = 0; i < length / NUM_4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * NUM_4 + NUM_0], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_0]));
        CalcDimension yDimen =
            CalcDimension(values[i * NUM_4 + NUM_1], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_1]));
        CalcDimension widthDimen =
            CalcDimension(values[i * NUM_4 + NUM_2], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i * NUM_4 + NUM_3], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    HyperlinkModelNG::SetResponseRegion(frameNode, region, true);
}

void ResetHyperlinkResponseRegion(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    HyperlinkModelNG::SetResponseRegion(frameNode, region, false);
}

ArkUINodeHandle CreateHyperlinkFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = HyperlinkModelStatic::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void Pop()
{
    HyperlinkModel::GetInstance()->Pop();
}

const ArkUIHyperlinkModifier* GetHyperlinkDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIHyperlinkModifier modifier = {
        .create = Create,
        .setHyperlinkColor = SetHyperlinkColor,
        .resetHyperlinkColor = ResetHyperlinkColor,
        .setHyperlinkDraggable = SetHyperlinkDraggable,
        .resetHyperlinkDraggable = ResetHyperlinkDraggable,
        .setHyperlinkResponseRegion = SetHyperlinkResponseRegion,
        .resetHyperlinkResponseRegion = ResetHyperlinkResponseRegion,
        .createHyperlinkFrameNode = CreateHyperlinkFrameNode,
        .pop = Pop
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIHyperlinkModifier* GetCJUIHyperlinkModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIHyperlinkModifier modifier = {
        .setHyperlinkColor = SetHyperlinkColor,
        .resetHyperlinkColor = ResetHyperlinkColor,
        .setHyperlinkDraggable = SetHyperlinkDraggable,
        .resetHyperlinkDraggable = ResetHyperlinkDraggable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace OHOS::Ace::NG
