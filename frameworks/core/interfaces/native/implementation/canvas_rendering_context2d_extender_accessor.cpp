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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "canvas_rendering_context2d_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasRenderingContext2DExtenderAccessor {
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_CanvasRenderingContext2D peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(peer);
    peer->StartImageAnalyzer(vmContext, asyncWorker, config, outputArgumentForReturningPromise);
}
} // CanvasRenderingContext2DExtenderAccessor
const GENERATED_ArkUICanvasRenderingContext2DExtenderAccessor* GetCanvasRenderingContext2DExtenderAccessor()
{
    static const GENERATED_ArkUICanvasRenderingContext2DExtenderAccessor CanvasRenderingContext2DExtenderAccessorImpl {
        CanvasRenderingContext2DExtenderAccessor::StartImageAnalyzerImpl,
    };
    return &CanvasRenderingContext2DExtenderAccessorImpl;
}

}
