/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#if defined(PLAYER_FRAMEWORK_EXISTS)
#if defined(ENABLE_ROSEN_BACKEND) && defined(OHOS_PLATFORM)
#include "core/components_ng/render/adapter/rosen_media_player.h"
#endif
#include "core/components_ng/render/adapter/media_player_impl.h"
#endif
#include "core/components_ng/render/media_player.h"

namespace OHOS::Ace::NG {
RefPtr<MediaPlayer> MediaPlayer::Create()
{
#if defined(PLAYER_FRAMEWORK_EXISTS)
    if (SystemProperties::GetRosenBackendEnabled()) {
#ifdef ENABLE_ROSEN_BACKEND
#if defined(OHOS_PLATFORM)
        return MakeRefPtr<RosenMediaPlayer>();
#else
        return MakeRefPtr<MediaPlayerImpl>();
#endif
#endif
    }
#endif
    return MakeRefPtr<MediaPlayer>();
}
} // namespace OHOS::Ace::NG
