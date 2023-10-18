/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/flutter_node.h"

#include "ace_shell/shell/common/window_manager.h"
#include "flutter/flow/layers/picture_layer.h"
#include "flutter/flow/layers/transform_layer.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPictureRecorder.h"

#include "base/thread/task_executor.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"

namespace OHOS::Ace::NG {

void FlutterNode::AddPicture(sk_sp<SkPicture> picture)
{
    lastPicture_ = picture;
}

std::shared_ptr<flutter::Layer> FlutterNode::BuildLayer(int32_t instanceId)
{
    // create a background picture layer if have background
    GenBackgroundLayer();
    auto backgroundLayer = CreatePictureLayer(backgroundPicture_, instanceId);

    // create a picture layer if have picture content
    auto contentLayer = CreatePictureLayer(lastPicture_, instanceId);

    bool onlyOneLayer = !backgroundPicture_ ^ !lastPicture_;

    std::shared_ptr<flutter::Layer> layer;
    // if have child or transform properities, use container layer.
    // if have more than one picture layer, use container layer.
    // otherwise just use picture layer.
    if (!children_.empty() || !frameRect_.GetOffset().NonOffset() || !onlyOneLayer) {
        auto transform = SkMatrix::Translate(frameRect_.GetX(), frameRect_.GetY());
        auto containerLayer = std::make_shared<flutter::TransformLayer>(transform);
        if (backgroundLayer) {
            containerLayer->Add(std::move(backgroundLayer));
        }
        if (contentLayer) {
            containerLayer->Add(std::move(contentLayer));
        }
        for (auto& child : children_) {
            auto layer = child->BuildLayer(instanceId);
            if (layer) {
                containerLayer->Add(std::move(layer));
            }
        }
        layer = std::move(containerLayer);
    } else {
        if (contentLayer) {
            layer = std::move(contentLayer);
        } else if (backgroundLayer) {
            layer = std::move(backgroundLayer);
        }
    }

    return layer;
}

void FlutterNode::AddChild(const std::shared_ptr<FlutterNode>& node)
{
    children_.emplace_back(node);
}

void FlutterNode::ClearChildren()
{
    children_.clear();
}

void FlutterNode::Dump(int32_t depth)
{
    std::string space;
    for (int32_t i = 0; i < depth; i++) {
        space.append("  ");
    }
    LOGD("%sFrameRect: %s", space.c_str(), frameRect_.ToString().c_str());
    LOGD("%sColor: %s", space.c_str(), bgColor_.ColorToString().c_str());
    for (auto& node : children_) {
        node->Dump(depth + 1);
    }
}

void FlutterNode::GenBackgroundLayer()
{
    CHECK_NULL_VOID(needUpdateBackgroud_);
    if (bgColor_ == Color::TRANSPARENT || frameRect_.IsEmpty()) {
        return;
    }
    auto recorder = std::make_unique<SkPictureRecorder>();
    SkRect rect = SkRect::MakeXYWH(0, 0, frameRect_.Width(), frameRect_.Height());
    auto canvas = recorder->beginRecording(rect);
    if (isRootNode_) {
        canvas->drawColor(bgColor_.GetValue());
    } else {
        SkPaint paint;
        paint.setColor(bgColor_.GetValue());
        canvas->drawRect(rect, paint);
    }
    backgroundPicture_ = recorder->finishRecordingAsPicture();
}

std::shared_ptr<flutter::PictureLayer> FlutterNode::CreatePictureLayer(sk_sp<SkPicture> picture, int32_t instanceId)
{
    CHECK_NULL_RETURN(picture, nullptr);
    auto window = flutter::ace::WindowManager::GetWindow(instanceId);
    CHECK_NULL_RETURN(window, nullptr);
    return std::make_shared<flutter::PictureLayer>(SkPoint::Make(0, 0), window->CreateGPUObject(picture), false, false);
}

} // namespace OHOS::Ace::NG
