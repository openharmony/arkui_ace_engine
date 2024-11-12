/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorBaseControllerAccessor {
RichEditorBaseControllerPeer* CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
Ark_Int32 GetCaretOffsetImpl(RichEditorBaseControllerPeer* peer)
{
    return 0;
}
Ark_Boolean SetCaretOffsetImpl(RichEditorBaseControllerPeer* peer,
                               const Ark_Number* offset)
{
    return 0;
}
void CloseSelectionMenuImpl(RichEditorBaseControllerPeer* peer)
{
}
Ark_NativePointer GetTypingStyleImpl(RichEditorBaseControllerPeer* peer)
{
    return 0;
}
void SetTypingStyleImpl(RichEditorBaseControllerPeer* peer,
                        const Ark_RichEditorTextStyle* value)
{
}
void SetSelectionImpl(RichEditorBaseControllerPeer* peer,
                      const Ark_Number* selectionStart,
                      const Ark_Number* selectionEnd,
                      const Opt_SelectionOptions* options)
{
}
Ark_Boolean IsEditingImpl(RichEditorBaseControllerPeer* peer)
{
    return 0;
}
void StopEditingImpl(RichEditorBaseControllerPeer* peer)
{
}
Ark_NativePointer GetLayoutManagerImpl(RichEditorBaseControllerPeer* peer)
{
    return 0;
}
Ark_NativePointer GetPreviewTextImpl(RichEditorBaseControllerPeer* peer)
{
    return 0;
}
} // RichEditorBaseControllerAccessor
const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorBaseControllerAccessor RichEditorBaseControllerAccessorImpl {
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
    };
    return &RichEditorBaseControllerAccessorImpl;
}

}
