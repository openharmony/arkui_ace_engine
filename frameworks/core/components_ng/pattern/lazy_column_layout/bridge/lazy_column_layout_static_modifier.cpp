/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model_static.h"
#include "core/components_ng/pattern/list/list_properties.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "arkoala_api_generated.h"
#endif

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<HorizontalAlign>& dst, const Ark_HorizontalAlign& src)
{
    switch (src) {
        case ARK_HORIZONTAL_ALIGN_START: dst = HorizontalAlign::START; break;
        case ARK_HORIZONTAL_ALIGN_END: dst = HorizontalAlign::END; break;
        case ARK_HORIZONTAL_ALIGN_CENTER: dst = HorizontalAlign::CENTER; break;
        default: break;
    }
}
template<>
void AssignCast(std::optional<V2::StickyStyle>& dst, const Ark_StickyStyle& src)
{
    switch (src) {
        case ARK_STICKY_STYLE_NONE: dst = V2::StickyStyle::NONE; break;
        case ARK_STICKY_STYLE_HEADER: dst = V2::StickyStyle::HEADER; break;
        case ARK_STICKY_STYLE_FOOTER: dst = V2::StickyStyle::FOOTER; break;
        case ARK_STICKY_STYLE_BOTH: dst = V2::StickyStyle::BOTH; break;
        default: break;
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LazyColumnLayoutExtenderAccessor {
Ark_NativePointer LazyColumnLayoutConstructorImpl(Ark_Int32 id)
{
    auto frameNode = LazyColumnLayoutModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetLazyColumnLayoutOptionsImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SpaceImpl(Ark_NativePointer node,
               const Opt_LengthMetrics* space)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*space);
    if (convValue && convValue->Value() < 0.0f) {
        convValue = Dimension(0.0f, convValue->Unit());
    }
    LazyColumnLayoutModelStatic::SetSpace(frameNode, convValue);
}
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_HorizontalAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<HorizontalAlign>(value);
    LazyColumnLayoutModelStatic::SetAlignItems(frameNode, convValue);
}
void HeaderImpl(Ark_NativePointer node,
                const Opt_CustomNodeBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optBuilder = Converter::GetOptPtr(builder);
    if (!optBuilder) {
        LazyColumnLayoutModelStatic::RemoveHeader(frameNode);
        return;
    }
    CallbackHelper(*optBuilder)
        .BuildAsync([weakNode = AceType::WeakClaim(frameNode)](const RefPtr<UINode>& uiNode) {
            CHECK_NULL_VOID(uiNode);
            auto host = weakNode.Upgrade();
            CHECK_NULL_VOID(host);
            LazyColumnLayoutModelStatic::SetHeader(AceType::RawPtr(host), uiNode);
        }, node);
}
void FooterImpl(Ark_NativePointer node,
                const Opt_CustomNodeBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optBuilder = Converter::GetOptPtr(builder);
    if (!optBuilder) {
        LazyColumnLayoutModelStatic::RemoveFooter(frameNode);
        return;
    }
    CallbackHelper(*optBuilder)
        .BuildAsync([weakNode = AceType::WeakClaim(frameNode)](const RefPtr<UINode>& uiNode) {
            CHECK_NULL_VOID(uiNode);
            auto host = weakNode.Upgrade();
            CHECK_NULL_VOID(host);
            LazyColumnLayoutModelStatic::SetFooter(AceType::RawPtr(host), uiNode);
        }, node);
}
void StickyImpl(Ark_NativePointer node,
                const Opt_StickyStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<V2::StickyStyle>(value);
    LazyColumnLayoutModelStatic::SetSticky(frameNode, EnumToInt(style));
}
void OnVisibleIndexesChangeImpl(Ark_NativePointer node,
                                const Opt_OnVisibleIndexesChangeCallback* callback_)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(callback_);
    if (!optValue) {
        LazyColumnLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, nullptr);
        return;
    }
    auto onVisibleIndexesChange = [arkCallback = CallbackHelper(*optValue)](const int32_t start, const int32_t end) {
        auto arkStart = Converter::ArkValue<Ark_Int32>(start);
        auto arkEnd = Converter::ArkValue<Ark_Int32>(end);
        arkCallback.Invoke(arkStart, arkEnd);
    };
    LazyColumnLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, std::move(onVisibleIndexesChange));
}
} // LazyColumnLayoutExtenderAccessor

#ifdef INCLUDE_GENERATED_SOURCES
const GENERATED_ArkUILazyColumnLayoutExtenderAccessor* GetLazyColumnLayoutStaticAccessor()
{
    static const GENERATED_ArkUILazyColumnLayoutExtenderAccessor LazyColumnLayoutExtenderAccessorImpl {
        LazyColumnLayoutExtenderAccessor::LazyColumnLayoutConstructorImpl,
        LazyColumnLayoutExtenderAccessor::SetLazyColumnLayoutOptionsImpl,
        LazyColumnLayoutExtenderAccessor::SpaceImpl,
        LazyColumnLayoutExtenderAccessor::AlignItemsImpl,
        LazyColumnLayoutExtenderAccessor::HeaderImpl,
        LazyColumnLayoutExtenderAccessor::FooterImpl,
        LazyColumnLayoutExtenderAccessor::StickyImpl,
        LazyColumnLayoutExtenderAccessor::OnVisibleIndexesChangeImpl,
    };
    return &LazyColumnLayoutExtenderAccessorImpl;
}
#endif

} // namespace OHOS::Ace::NG::GeneratedModifier
