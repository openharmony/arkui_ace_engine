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
#include "arkoala_api_generated.h"
#include "canvas_path_accessor_peer_impl.h"

struct Path2DPeer : public CanvasPathPeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Path2DAccessor {
void DestroyPeerImpl(Path2DPeer* peer)
{
}
Ark_NativePointer CtorImpl()
{
    return new Path2DPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void AddPathImpl(Path2DPeer* peer,
                 const Ark_Path2D* path,
                 const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->path2d);
    CHECK_NULL_VOID(path);
    CHECK_NULL_VOID(transform);
    auto peer2 = reinterpret_cast<Path2DPeer*>(path->ptr);
    CHECK_NULL_VOID(peer2);

    auto opt = Converter::OptConvert<Ark_Matrix2D>(*transform);
    CHECK_NULL_VOID(opt);
    auto matrix = reinterpret_cast<Matrix2DPeer*>(opt->ptr);
    CHECK_NULL_VOID(matrix);
 }
} // Path2DAccessor
const GENERATED_ArkUIPath2DAccessor* GetPath2DAccessor()
{
    static const GENERATED_ArkUIPath2DAccessor Path2DAccessorImpl {
        Path2DAccessor::DestroyPeerImpl,
        Path2DAccessor::CtorImpl,
        Path2DAccessor::GetFinalizerImpl,
        Path2DAccessor::AddPathImpl,
    };
    return &Path2DAccessorImpl;
}

struct Path2DPeer {
    virtual ~Path2DPeer() = default;
};
}
