/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "frameworks/core/interfaces/native/implementation/bind_sheet_utils.h"

using namespace OHOS::Ace::NG::Converter;
namespace OHOS::Ace::NG::GeneratedModifier {
namespace BindSheetOpsAccessor {

Ark_NativePointer RegisterBindSheetShowCallbackImpl(Ark_NativePointer node, Ark_Boolean value,
    const ShowCallback* callback, const Opt_CustomNodeBuilder* builder, const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, node);
    CHECK_NULL_RETURN(builder, node);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto changeEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& param) {
        PipelineContext::SetCallBackNode(weakNode);
        bool isShow = false;
        if (param == "true") {
            isShow = true;
        }
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isShow));
    };
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showCloseIcon = true;
    sheetStyle.showInPage = false;
    BindSheetUtil::SheetCallbacks cbs;
    auto sheetOptions = options ? Converter::OptConvert<Ark_SheetOptions>(*options) : std::nullopt;
    if (sheetOptions) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, sheetOptions.value());
        BindSheetUtil::ParseFuntionalCallbacks(cbs, sheetOptions.value());
        Converter::VisitUnion(sheetOptions->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.isTitleBuilder = false;
                sheetStyle.sheetTitle = OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = OptConvert<std::string>(value.subtitle.value);
            },
            [frameNode, node, &cbs, &sheetStyle](const CustomNodeBuilder& value) {
                cbs.titleBuilder = [callback = CallbackHelper(value), node]() {
                    auto uiNode = callback.BuildSync(node);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
                sheetStyle.isTitleBuilder = true;
            }, []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, sheetOptions.value());
    }
    auto optBuilder = Converter::GetOptPtr(builder);
    if (!optBuilder) {
        return node;
    }
    CallbackHelper(*optBuilder).BuildAsync([frameNode, value, sheetStyle, changeEvent,
        titleBuilder = std::move(cbs.titleBuilder), onAppear = std::move(cbs.onAppear),
        onDisappear = std::move(cbs.onDisappear), shouldDismiss = std::move(cbs.shouldDismiss),
        onWillDismiss = std::move(cbs.onWillDismiss), onWillAppear = std::move(cbs.onWillAppear),
        onWillDisappear = std::move(cbs.onWillDisappear), onHeightDidChange = std::move(cbs.onHeightDidChange),
        onDetentsDidChange = std::move(cbs.onDetentsDidChange), onWidthDidChange = std::move(cbs.onWidthDidChange),
        onTypeDidChange = std::move(cbs.onTypeDidChange), sheetSpringBack = std::move(cbs.sheetSpringBack)](
        const RefPtr<UINode>& uiNode) mutable {
        auto buildFunc = [frameNode, uiNode]() {
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        ViewAbstractModelStatic::BindSheet(frameNode, value, std::move(changeEvent), std::move(buildFunc),
            std::move(titleBuilder), sheetStyle, std::move(onAppear), std::move(onDisappear),
            std::move(shouldDismiss), std::move(onWillDismiss), std::move(onWillAppear), std::move(onWillDisappear),
            std::move(onHeightDidChange), std::move(onDetentsDidChange), std::move(onWidthDidChange),
            std::move(onTypeDidChange), std::move(sheetSpringBack));
        }, node);

        return node;
}

Ark_NativePointer RegisterContentCoverShowCallbackImpl(Ark_NativePointer node, Ark_Boolean isShowValue,
    const ShowCallback* callback, const Opt_CustomNodeBuilder* builder, const Opt_ContentCoverOptions* options)
{
    CHECK_NULL_RETURN(builder, node);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, node);

    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto changeEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& param) {
        PipelineContext::SetCallBackNode(weakNode);
        bool isShow = false;
        if (param == "true") {
            isShow = true;
        }
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isShow));
    };
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::DEFAULT;
    std::function<void()> onShowCallback;
    std::function<void()> onDismissCallback;
    std::function<void()> onWillShowCallback;
    std::function<void()> onWillDismissCallback;
    std::function<void(const int32_t&)> onWillDismissFunc;
    ContentCoverParam contentCoverParam;
    auto coverOption = options ? Converter::OptConvert<Ark_ContentCoverOptions>(*options) : std::nullopt;
    if (coverOption) {
        BindSheetUtil::ParseContentCoverCallbacks(weakNode, coverOption.value(), onShowCallback,
            onDismissCallback, onWillShowCallback, onWillDismissCallback, onWillDismissFunc);
        modalStyle.modalTransition = Converter::OptConvert<ModalTransition>(coverOption->modalTransition)
            .value_or(ModalTransition::DEFAULT);
        modalStyle.backgroundColor = Converter::OptConvert<Color>(coverOption->backgroundColor);
        contentCoverParam.transitionEffect = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(coverOption->transition)
            .value_or(contentCoverParam.transitionEffect);
    }
    contentCoverParam.onWillDismiss = std::move(onWillDismissFunc);

    auto optBuilder = Converter::GetOptPtr(builder);
    if (isShowValue && optBuilder) {
        CallbackHelper(*optBuilder).BuildAsync([weakNode, frameNode, modalStyle, contentCoverParam,
            onShowCallback = std::move(onShowCallback),
            onDismissCallback = std::move(onDismissCallback),
            onWillShowCallback = std::move(onWillShowCallback),
            onWillDismissCallback = std::move(onWillDismissCallback), changeEvent
        ](const RefPtr<UINode>& uiNode) mutable {
            PipelineContext::SetCallBackNode(weakNode);
            auto buildFunc = [uiNode]() -> RefPtr<UINode> {
                return uiNode;
            };
            ViewAbstractModelStatic::BindContentCover(frameNode, true, std::move(changeEvent), std::move(buildFunc),
                modalStyle, std::move(onShowCallback), std::move(onDismissCallback), std::move(onWillShowCallback),
                std::move(onWillDismissCallback), contentCoverParam);
            }, node);
    } else {
        ViewAbstractModelStatic::BindContentCover(frameNode, false, std::move(changeEvent), nullptr,
            modalStyle, std::move(onShowCallback), std::move(onDismissCallback),
            std::move(onWillShowCallback), std::move(onWillDismissCallback), contentCoverParam);
    }
    return node;
}
} // BindSheetOpsAccessor
const GENERATED_ArkUIBindSheetOpsAccessor* GetBindSheetOpsAccessor()
{
    static const GENERATED_ArkUIBindSheetOpsAccessor BindSheetOpsAccessorImpl {
        BindSheetOpsAccessor::RegisterBindSheetShowCallbackImpl,
        BindSheetOpsAccessor::RegisterContentCoverShowCallbackImpl,
    };
    return &BindSheetOpsAccessorImpl;
}

}
