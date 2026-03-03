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

#include <hilog/log.h>

#include "Scenario2AudioPlayer.h"


namespace {

const int64_t ROOT_ELEMENT_ID = 0;      // Element ID for root node
const int32_t RANGE_MIN = 0;            // Minimum range value
const int32_t RANGE_MAX = 100;          // Maximum range value
const int32_t PROGRESS_INCREMENT = 10;  // Progress increment value
const int32_t MODULO_VALUE = 101;       // Modulo value for calculation

} // namespace


namespace NativeXComponentSample {

/**
 * @brief Constructor for Scenario2AudioPlayer
 */
Scenario2AudioPlayer::Scenario2AudioPlayer()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Scenario2AudioPlayer constructor called");
}

/**
 * @brief Destructor for Scenario2AudioPlayer
 */
Scenario2AudioPlayer::~Scenario2AudioPlayer()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Scenario2AudioPlayer destructor called");
    Cleanup();
}

/**
 * @brief Initializes the audio player scenario
 */
void Scenario2AudioPlayer::Initialize()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Initializing Scenario2AudioPlayer");
    CreateNodes();
    ConfigureNodes();
}

/**
 * @brief Creates all nodes for the audio player scenario
 */
void Scenario2AudioPlayer::CreateNodes()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Creating nodes for audio player");

    // 1. Create root node (container)
    auto* container = new FakeCustomWidget("audioPlayer");
    container->SetElementId(ROOT_ELEMENT_ID);
    container->SetAccessibilityGroup(true);
    container->SetAccessibilityLevel("page");
    rootNode_ = container;
    nodes_.push_back(rootNode_);

    // 2. Create play button
    playButton_ = new FakeButton("play");
    playButton_->SetElementId(AllocateElementId());
    playButton_->SetName("播放");
    playButton_->SetAccessibilityText("播放音频");
    playButton_->SetClickable(true);
    playButton_->SetFocusable(true);
    playButton_->SetParent(rootNode_);
    nodes_.push_back(playButton_);

    // 3. Create pause button
    pauseButton_ = new FakeButton("pause");
    pauseButton_->SetElementId(AllocateElementId());
    pauseButton_->SetName("暂停");
    pauseButton_->SetAccessibilityText("暂停音频");
    pauseButton_->SetClickable(true);
    pauseButton_->SetFocusable(true);
    pauseButton_->SetIsVisible(false);  // Initially hidden
    pauseButton_->SetParent(rootNode_);
    nodes_.push_back(pauseButton_);

    // 4. Create stop button
    stopButton_ = new FakeButton("stop");
    stopButton_->SetElementId(AllocateElementId());
    stopButton_->SetName("停止");
    stopButton_->SetAccessibilityText("停止音频");
    stopButton_->SetClickable(true);
    stopButton_->SetFocusable(true);
    stopButton_->SetParent(rootNode_);
    nodes_.push_back(stopButton_);

    // 5. Create progress slider
    progressSlider_ = new AccessibleObject("progressSlider");
    progressSlider_->SetElementId(AllocateElementId());
    progressSlider_->SetName("进度");
    progressSlider_->SetComponentType("slider");
    progressSlider_->SetAccessibilityText("播放进度");
    progressSlider_->SetClickable(true);
    progressSlider_->SetFocusable(true);
    // Set range info (0-100)
    ArkUI_AccessibleRangeInfo rangeInfo;
    rangeInfo.current = currentProgress_;
    rangeInfo.min = RANGE_MIN;
    rangeInfo.max = RANGE_MAX;
    progressSlider_->SetRangeInfo(rangeInfo);
    progressSlider_->SetParent(rootNode_);
    nodes_.push_back(progressSlider_);

    // 6. Create volume slider
    volumeSlider_ = new AccessibleObject("volumeSlider");
    volumeSlider_->SetElementId(AllocateElementId());
    volumeSlider_->SetName("音量");
    volumeSlider_->SetComponentType("slider");
    volumeSlider_->SetAccessibilityText("音量控制");
    volumeSlider_->SetClickable(true);
    volumeSlider_->SetFocusable(true);
    // Set range info (0-100)
    ArkUI_AccessibleRangeInfo volumeRangeInfo;
    volumeRangeInfo.current = volume_;
    volumeRangeInfo.min = RANGE_MIN;
    volumeRangeInfo.max = RANGE_MAX;
    volumeSlider_->SetRangeInfo(volumeRangeInfo);
    volumeSlider_->SetParent(rootNode_);
    nodes_.push_back(volumeSlider_);

    // 7. Create current time text
    currentTimeText_ = new AccessibleObject("currentTime");
    currentTimeText_->SetElementId(AllocateElementId());
    currentTimeText_->SetName("00:30");
    currentTimeText_->SetComponentType("text");
    currentTimeText_->SetAccessibilityText("当前时间 30秒");
    currentTimeText_->SetParent(rootNode_);
    nodes_.push_back(currentTimeText_);

    // 8. Create total time text
    totalTimeText_ = new AccessibleObject("totalTime");
    totalTimeText_->SetElementId(AllocateElementId());
    totalTimeText_->SetName("03:45");
    totalTimeText_->SetComponentType("text");
    totalTimeText_->SetAccessibilityText("总时间 3分45秒");
    totalTimeText_->SetParent(rootNode_);
    nodes_.push_back(totalTimeText_);

    // Add child nodes to container
    if (auto* customWidget = dynamic_cast<FakeCustomWidget*>(rootNode_)) {
        customWidget->AddChild(playButton_);
        customWidget->AddChild(pauseButton_);
        customWidget->AddChild(stopButton_);
        customWidget->AddChild(progressSlider_);
        customWidget->AddChild(volumeSlider_);
        customWidget->AddChild(currentTimeText_);
        customWidget->AddChild(totalTimeText_);
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Created %{public}zu nodes for audio player", nodes_.size());
}

/**
 * @brief Configures the initial state of nodes
 */
void Scenario2AudioPlayer::ConfigureNodes()
{
    // Configure initial state
    UpdatePlayState();

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Configured audio player nodes");
}

/**
 * @brief Gets all nodes in this scenario
 * @return Vector of pointers to all nodes
 */
const std::vector<AccessibleObject*>& Scenario2AudioPlayer::GetNodes() const
{
    return nodes_;
}

/**
 * @brief Gets the root node of this scenario
 * @return Pointer to the root node
 */
AccessibleObject* Scenario2AudioPlayer::GetRootNode() const
{
    return rootNode_;
}

/**
 * @brief Finds a node by its element ID
 * @param elementId The element ID to search for
 * @return Pointer to the node if found, nullptr otherwise
 */
AccessibleObject* Scenario2AudioPlayer::GetNodeById(int64_t elementId)
{
    if (elementId <= RANGE_MIN || elementId > static_cast<int64_t>(nodes_.size())) {
        return nullptr;
    }
    return nodes_[elementId - 1];
}

/**
 * @brief Handles an accessibility action on a node
 * @param elementId The element ID to perform the action on
 * @param action The type of action to perform
 * @return true if the action was handled, false otherwise
 */
bool Scenario2AudioPlayer::HandleAction(int64_t elementId,
    ArkUI_Accessibility_ActionType action)
{
    auto* node = GetNodeById(elementId);
    if (!node) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Scenario2",
            "Node not found: elementId=%{public}lld", elementId);
        return false;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "HandleAction: elementId=%{public}lld, action=%{public}d",
        elementId, action);

    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            // Handle play button click
            if (node == playButton_) {
                isPlaying_ = true;
                UpdatePlayState();
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
                    "Play button clicked, start playing");
                return true;
            }
            // Handle pause button click
            else if (node == pauseButton_) {
                isPlaying_ = false;
                UpdatePlayState();
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
                    "Pause button clicked, pause playing");
                return true;
            }
            // Handle stop button click
            else if (node == stopButton_) {
                isPlaying_ = false;
                currentProgress_ = RANGE_MIN;
                UpdatePlayState();
                // Update progress range info
                ArkUI_AccessibleRangeInfo rangeInfo;
                rangeInfo.current = RANGE_MIN;
                rangeInfo.min = RANGE_MIN;
                rangeInfo.max = RANGE_MAX;
                progressSlider_->SetRangeInfo(rangeInfo);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
                    "Stop button clicked, reset progress");
                return true;
            }
            // Handle slider click (simulate progress adjustment)
            else if (node == progressSlider_) {
                currentProgress_ = (currentProgress_ + PROGRESS_INCREMENT) % MODULO_VALUE;
                ArkUI_AccessibleRangeInfo rangeInfo;
                rangeInfo.current = currentProgress_;
                rangeInfo.min = RANGE_MIN;
                rangeInfo.max = RANGE_MAX;
                progressSlider_->SetRangeInfo(rangeInfo);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
                    "Progress slider clicked, new value: %{public}d",
                    currentProgress_);
                return true;
            }
            // Handle volume slider click
            else if (node == volumeSlider_) {
                volume_ = (volume_ + PROGRESS_INCREMENT) % MODULO_VALUE;
                ArkUI_AccessibleRangeInfo volumeRangeInfo;
                volumeRangeInfo.current = volume_;
                volumeRangeInfo.min = RANGE_MIN;
                volumeRangeInfo.max = RANGE_MAX;
                volumeSlider_->SetRangeInfo(volumeRangeInfo);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
                    "Volume slider clicked, new value: %{public}d",
                    volume_);
                return true;
            }
            break;

        default:
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
                "Unhandled action: %{public}d", action);
            break;
    }

    return false;
}

/**
 * @brief Cleans up all resources used by this scenario
 */
void Scenario2AudioPlayer::Cleanup()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario2",
        "Cleaning up %{public}zu nodes", nodes_.size());

    // Note: rootNode will clean up its child nodes, so only clean rootNode here
    if (auto* customWidget = dynamic_cast<FakeCustomWidget*>(rootNode_)) {
        customWidget->Cleanup();
    }

    nodes_.clear();
    rootNode_ = nullptr;
    playButton_ = nullptr;
    pauseButton_ = nullptr;
    stopButton_ = nullptr;
    progressSlider_ = nullptr;
    volumeSlider_ = nullptr;
    currentTimeText_ = nullptr;
    totalTimeText_ = nullptr;
}

} // namespace NativeXComponentSample
