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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorBaseControllerAccessor {
void DestroyPeerImpl(Ark_RichEditorBaseController peer)
{
}
Ark_RichEditorBaseController CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetCaretOffsetImpl(Ark_RichEditorBaseController peer)
{
    return {};
}
Ark_Boolean SetCaretOffsetImpl(Ark_RichEditorBaseController peer,
                               const Ark_Number* offset)
{
    return {};
}
void CloseSelectionMenuImpl(Ark_RichEditorBaseController peer)
{
}
Ark_RichEditorTextStyle GetTypingStyleImpl(Ark_RichEditorBaseController peer)
{
    return {};
}
void SetTypingStyleImpl(Ark_RichEditorBaseController peer,
                        const Ark_RichEditorTextStyle* value)
{
}
void SetSelectionImpl(Ark_RichEditorBaseController peer,
                      const Ark_Number* selectionStart,
                      const Ark_Number* selectionEnd,
                      const Opt_SelectionOptions* options)
{
}
Ark_Boolean IsEditingImpl(Ark_RichEditorBaseController peer)
{
    return {};
}
void StopEditingImpl(Ark_RichEditorBaseController peer)
{
}
Ark_LayoutManager GetLayoutManagerImpl(Ark_RichEditorBaseController peer)
{
    return {};
}
Ark_PreviewText GetPreviewTextImpl(Ark_RichEditorBaseController peer)
{
    return {};
}
Opt_RectResult GetCaretRectImpl(Ark_RichEditorBaseController peer)
{
    return {};
}
} // RichEditorBaseControllerAccessor
const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorBaseControllerAccessor RichEditorBaseControllerAccessorImpl {
        RichEditorBaseControllerAccessor::DestroyPeerImpl,
        RichEditorBaseControllerAccessor::CtorImpl,
        RichEditorBaseControllerAccessor::GetFinalizerImpl,
        RichEditorBaseControllerAccessor::GetCaretOffsetImpl,
        RichEditorBaseControllerAccessor::SetCaretOffsetImpl,
        RichEditorBaseControllerAccessor::CloseSelectionMenuImpl,
        RichEditorBaseControllerAccessor::GetTypingStyleImpl,
        RichEditorBaseControllerAccessor::SetTypingStyleImpl,
        RichEditorBaseControllerAccessor::SetSelectionImpl,
        RichEditorBaseControllerAccessor::IsEditingImpl,
        RichEditorBaseControllerAccessor::StopEditingImpl,
        RichEditorBaseControllerAccessor::GetLayoutManagerImpl,
        RichEditorBaseControllerAccessor::GetPreviewTextImpl,
        RichEditorBaseControllerAccessor::GetCaretRectImpl,
    };
    return &RichEditorBaseControllerAccessorImpl;
}

}
