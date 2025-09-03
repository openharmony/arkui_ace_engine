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

#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

#include "matrix2d_peer_impl.h"
#include "path2d_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Path2DAccessor {
namespace {
const std::string EMPTY_STRING = "";
RefPtr<Path2DPeerImpl> CreatePeerImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<Path2DPeerImpl>();
    peerImpl->IncRefCount();
    peerImpl->SetOptions();
    return peerImpl;
}
} // namespace

void DestroyPeerImpl(Ark_Path2D peer)
{
    auto peerImpl = reinterpret_cast<Path2DPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_Path2D Construct0Impl()
{
    auto peerImpl = CreatePeerImpl();
    return reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_Path2D Construct1Impl(Ark_LengthMetricsUnit unit)
{
    auto peerImpl = CreatePeerImpl();
    auto optUnit = Converter::OptConvert<Ace::CanvasUnit>(unit).value_or(Ace::CanvasUnit::DEFAULT);
    peerImpl->SetUnit(optUnit);
    return reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_Path2D Construct2Impl(Ark_Path2D path)
{
    auto peerImpl = CreatePeerImpl();
    if (path) {
        auto canvasPath = path->GetCanvasPath2d();
        peerImpl->SetCanvasPath2d(canvasPath);
    }
    return reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_Path2D Construct3Impl(Ark_Path2D path,
                          Ark_LengthMetricsUnit unit)
{
    auto peerImpl = CreatePeerImpl();
    auto optUnit = Converter::OptConvert<Ace::CanvasUnit>(unit).value_or(Ace::CanvasUnit::DEFAULT);
    peerImpl->SetUnit(optUnit);
    if (path) {
        auto canvasPath = path->GetCanvasPath2d();
        peerImpl->SetCanvasPath2d(canvasPath);
    }
    return reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_Path2D Construct4Impl(const Ark_String* d)
{
    auto peerImpl = CreatePeerImpl();
    auto path = Converter::OptConvertPtr<std::string>(d).value_or(EMPTY_STRING);
    if (!path.empty()) {
        auto canvasPath = Referenced::MakeRefPtr<CanvasPath2D>(path);
        peerImpl->SetCanvasPath2d(canvasPath);
    }
    return reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_Path2D Construct5Impl(const Ark_String* description,
                          Ark_LengthMetricsUnit unit)
{
    auto peerImpl = CreatePeerImpl();
    auto optUnit = Converter::OptConvert<Ace::CanvasUnit>(unit).value_or(Ace::CanvasUnit::DEFAULT);
    peerImpl->SetUnit(optUnit);
    auto path = Converter::OptConvertPtr<std::string>(description).value_or(EMPTY_STRING);
    if (!path.empty()) {
        auto canvasPath = Referenced::MakeRefPtr<CanvasPath2D>(path);
        peerImpl->SetCanvasPath2d(canvasPath);
    }
    return reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void AddPathImpl(Ark_Path2D peer,
                 Ark_Path2D path,
                 const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(transform);
    auto peerImpl = reinterpret_cast<Path2DPeerImpl*>(peer);
    auto matrix = Converter::OptConvert<Ark_Matrix2D>(*transform);
    peerImpl->Path2DAddPath(path, matrix);
}
} // Path2DAccessor
const GENERATED_ArkUIPath2DAccessor* GetPath2DAccessor()
{
    static const GENERATED_ArkUIPath2DAccessor Path2DAccessorImpl {
        Path2DAccessor::DestroyPeerImpl,
        Path2DAccessor::Construct0Impl,
        Path2DAccessor::Construct1Impl,
        Path2DAccessor::Construct2Impl,
        Path2DAccessor::Construct3Impl,
        Path2DAccessor::Construct4Impl,
        Path2DAccessor::Construct5Impl,
        Path2DAccessor::GetFinalizerImpl,
        Path2DAccessor::AddPathImpl,
    };
    return &Path2DAccessorImpl;
}
}
