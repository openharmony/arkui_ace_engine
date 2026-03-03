/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef ACCESSIBILITY_CAPI_SCENARIO2_AUDIO_PLAYER_H
#define ACCESSIBILITY_CAPI_SCENARIO2_AUDIO_PLAYER_H

#include "ScenarioBase.h"
#include "fakenode/fake_node.h"
#include "fakenode/FakeCustomWidget.h"

namespace NativeXComponentSample {

/**
 * @brief 场景2：音频播放器
 *
 * 演示范围信息、位置信息、事件上报
 * 覆盖接口：12个
 * 测试用例：7个
 */
class Scenario2AudioPlayer : public ScenarioBase {
public:
    Scenario2AudioPlayer();
    ~Scenario2AudioPlayer() override;

    // 实现ScenarioBase接口
    const char* GetId() const override
    {
        return "scenario2_audio";
    }

    const char* GetName() const override
    {
        return "音频播放器";
    }

    const char* GetDescription() const override
    {
        return "演示范围信息、位置信息、事件上报（12个接口）";
    }

    void Initialize() override;
    const std::vector<AccessibleObject*>& GetNodes() const override;
    AccessibleObject* GetRootNode() const override;
    AccessibleObject* GetNodeById(int64_t elementId) override;
    bool HandleAction(int64_t elementId, ArkUI_Accessibility_ActionType action) override;
    void Cleanup() override;

    int GetInterfaceCount() const override
    {
        return 12;
    }

    int GetTestCaseCount() const override
    {
        return 7;
    }

private:
    void CreateNodes();
    void ConfigureNodes();

    // 节点指针
    AccessibleObject* rootNode_ = nullptr;
    AccessibleObject* playButton_ = nullptr;
    AccessibleObject* pauseButton_ = nullptr;
    AccessibleObject* stopButton_ = nullptr;
    AccessibleObject* progressSlider_ = nullptr;
    AccessibleObject* volumeSlider_ = nullptr;
    AccessibleObject* currentTimeText_ = nullptr;
    AccessibleObject* totalTimeText_ = nullptr;

    // 节点列表
    std::vector<AccessibleObject*> nodes_;
    int32_t nextElementId_ = 1;

    // 状态管理
    bool isPlaying_ = false;
    int32_t currentProgress_ = 30;  // 当前进度（0-100）
    int32_t volume_ = 70;            // 音量（0-100）

    // 元素ID分配
    int32_t AllocateElementId()
    {
        return nextElementId_++;
    }

    // 更新播放状态
    void UpdatePlayState()
    {
        if (isPlaying_) {
            // 正在播放，显示暂停按钮
            playButton_->SetIsVisible(false);
            pauseButton_->SetIsVisible(true);
        } else {
            // 已暂停，显示播放按钮
            playButton_->SetIsVisible(true);
            pauseButton_->SetIsVisible(false);
        }
    }
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_SCENARIO2_AUDIO_PLAYER_H
