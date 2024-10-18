/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_MEDIA_PLAYER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_MEDIA_PLAYER_H

#include <stdint.h>

#include "gmock/gmock.h"

#include "core/components_ng/render/media_player.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_WIDTH = 100;
constexpr int32_t DEFAULT_HEIGHT = 100;
} // namespace

class MockMediaPlayer : public MediaPlayer {
    DECLARE_ACE_TYPE(MockMediaPlayer, MediaPlayer)
public:
    ~MockMediaPlayer() override = default;
    
    int32_t GetVideoWidth() override
    {
        return DEFAULT_WIDTH;
    }

    int32_t GetVideoHeight() override
    {
        return DEFAULT_HEIGHT;
    }

    MOCK_METHOD0(IsMediaPlayerValid, bool());
    MOCK_METHOD3(SetSource, bool(const std::string&, const std::string&, const std::string&));
    MOCK_METHOD0(SetSurface, int32_t());
    MOCK_METHOD0(PrepareAsync, int32_t());
    MOCK_METHOD0(Pause, int32_t());
    MOCK_METHOD1(GetDuration, int32_t(int32_t&));
    MOCK_METHOD0(Prepare, int32_t());
    MOCK_METHOD0(Stop, int32_t());
    MOCK_METHOD2(Seek, int32_t(int32_t, SeekMode));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_MEDIA_PLAYER_H
