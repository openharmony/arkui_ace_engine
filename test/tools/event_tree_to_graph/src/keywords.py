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

# 定义所有关键词
# 结构: 每个event tree 按照如下结构解析
# 2: event tree =>
#  touch points:
#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchDown, timestamp:
#   2017-08-25 15:00:22.244, isInjected: 0
#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchUp, timestamp: 2017-08-25
#   15:00:22.295, isInjected: 0
#  hittest:
#   nodeId: 0, parentId: -1, tag: root, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: RectT (0.00,
#   0.00) - [720.00 x 1280.00]
#   nodeId: 1, parentId: 0, tag: stage, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: RectT (0.00,
#   0.00) - [720.00 x 1280.00]
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


from typing import Dict, Any


class KeyValueSample:
    key = ""
    value = ""
    value_separator_count = 0

    def __init__(self, key_and_value, force_no_space=False):
        if force_no_space:
            texts = key_and_value.split(":")
        else:
            texts = key_and_value.split(": ")
        if len(texts) != 2:
            if len(texts) == 1:
                self.key = texts[0]
                self.value = ""
            else:
                self.key = ""
                self.value = ""
        else:
            self.key = texts[0] + (": " if not force_no_space else ":")
            self.value = texts[1]
        self.value_separator_count = self.value.count(", ")


# level 1 keywords
keywords_dict = {
    "EventTreeDumpInfo": " EventTreeDumpInfo: ",
    "event tree": "event tree =>",
}

# touch point keywords
#  touch points:
#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchDown, timestamp:
#   2017-08-25 15:00:22.244, isInjected: 0
#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchUp, timestamp: 2017-08-25
#   15:00:22.295, isInjected: 0
touch_point_keyword = {
    "touch points": KeyValueSample("touch points:"),
    "id": KeyValueSample("id: 0"),
    "point": KeyValueSample("point: Offset (278.00, 551.00)"),
    "screenPoint": KeyValueSample("screenPoint: Offset (278.00, 551.00)"),
    "type": KeyValueSample("type: TouchDown,"),
    "timestamp": KeyValueSample("timestamp: 2017-08-25 15:00:22.244"),
    "isInjected": KeyValueSample("isInjected: 0"),
}

#   nodeId: 0, parentId: -1, tag: root, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: RectT (0.00,
#   0.00) - [720.00 x 1280.00]
hittest_node_keyword = {
    "hittest": KeyValueSample("hittest:"),
    "nodeId": KeyValueSample("nodeId: 0"),
    "parentId": KeyValueSample("parentId: -1"),
    "tag": KeyValueSample("tag: root"),
    "comId": KeyValueSample("comId: PageDesktopLayout"),
    "monopolizeEvents": KeyValueSample("monopolizeEvents: 0"),
    "isHit": KeyValueSample("isHit: 1"),
    "hitTestMode": KeyValueSample("hitTestMode: 0"),
    "responseRegion": KeyValueSample("responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]"),
}

# event procedure keywords
#  event procedures:
#   finger:0
#    frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0xf072b240
#     stateHistory:
#      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247
#      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295
#   finger:1
#    frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0xf072b240
#     stateHistory:
#      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247
#      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295
event_procedure_keyword = {
    "event procedures": KeyValueSample("event procedures:"),
    "finger": KeyValueSample("finger:0", True),
    "frameNodeId": KeyValueSample("frameNodeId: 84"),
    "type": KeyValueSample("type: TouchEventActuator"),
    "depth": KeyValueSample("depth: 0"),
    "id": KeyValueSample("id: 0xf072b240"),
    "parentId": KeyValueSample("parentId: 0xf072b240"),
    "stateHistory": KeyValueSample("stateHistory:"),
    "procedure": KeyValueSample("procedure: HandleTouchDown"),
    "state": KeyValueSample("state: READY"),
    "disposal": KeyValueSample("disposal: NONE"),
    "timestamp": KeyValueSample("timestamp: 2017-08-25 15:00:22.247"),
    "duration": KeyValueSample("duration: 500"),
    "isForDrag": KeyValueSample("isForDrag: 0"),
    "repeat": KeyValueSample("repeat: 0"),
    "customInfo": KeyValueSample("customInfo: "),
    "direction": KeyValueSample("direction: 3"),
    "distance": KeyValueSample("distance: 7.5"),
    "fingers": KeyValueSample("fingers: 1")
}


def get_dict_value(input_dict: Dict[str, Any], key: str) -> Any:
    if not isinstance(input_dict, dict):
        raise ValueError("input_dict must be a dictionary")
    return input_dict.get(key)


def get_sample_key(input_dict: Dict[str, KeyValueSample], name: str) -> str:
    sample: KeyValueSample = get_dict_value(input_dict, name)
    if sample is None:
        return ''
    return sample.key


def get_sample_value(input_dict: Dict[str, KeyValueSample], name: str) -> str:
    sample: KeyValueSample = get_dict_value(input_dict, name)
    if sample is None:
        return ''
    return sample.value


def get_sample_separator_count(input_dict: Dict[str, KeyValueSample], name: str) -> int:
    sample: KeyValueSample = get_dict_value(input_dict, name)
    if sample is None:
        return 0
    return sample.value_separator_count
