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
#include "core/interfaces/native/utility/converter.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/screen/screen_model.h"
#endif // WINDOW_SCENE_SUPPORTED

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScreenModifier {
Ark_NativePointer ConstructImpl()
{
    return nullptr;
}
} // ScreenModifier
namespace ScreenInterfaceModifier {
void SetScreenOptionsImpl(Ark_NativePointer node,
                          const Ark_Number* screenId)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(screenId);

#ifdef WINDOW_SCENE_SUPPORTED
    auto convValue = Converter::Convert<uint32_t>(*screenId);
    ScreenModel::SetOptions(frameNode, convValue);
#endif //WINDOW_SCENE_SUPPORTED
}
} // ScreenInterfaceModifier
const GENERATED_ArkUIScreenModifier* GetScreenModifier()
{
    static const GENERATED_ArkUIScreenModifier ArkUIScreenModifierImpl {
        ScreenModifier::ConstructImpl,
        ScreenInterfaceModifier::SetScreenOptionsImpl,
    };
    return &ArkUIScreenModifierImpl;
}

}
