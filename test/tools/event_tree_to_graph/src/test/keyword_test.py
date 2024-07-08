#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

from src.keywords import KeyValueSample


# 2: event tree =>
#  touch points:
#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchDown, timestamp: 2017-08-25 15:00:22.244, isInjected: 0
#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchUp, timestamp: 2017-08-25 15:00:22.295, isInjected: 0
#  hittest:
#   nodeId: 0, parentId: -1, tag: root, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]
#   nodeId: 1, parentId: 0, tag: stage, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]
#  event procedures:
#   finger:0
#    frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0x0
#     stateHistory:
#      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247
#      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295
#   finger:1
#    frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0x0
#     stateHistory:
#      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247
#      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295
if __name__ == '__main__':
    KeyValueSample("touch points:")
    KeyValueSample("id: 0")
    KeyValueSample("screenPoint: Offset (278.00, 551.00)")
    KeyValueSample("responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]")
