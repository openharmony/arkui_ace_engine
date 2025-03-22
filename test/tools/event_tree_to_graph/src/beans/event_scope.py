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

from typing import List

from src.beans.base_bean import BaseBean
from src.beans.event_node import EventNode
from src.beans.frame_node import FrameNode
from src.keywords import event_procedure_keyword, keywords_dict, get_sample_key, get_dict_value, \
    get_sample_separator_count
from src.utils.log_wrapper import log_info
from src.utils.value_parser import get_value_as_int, pack_string_until_next_keyword


class EventScope(BaseBean):
    finger = 0
    event_nodes = []
    isNeedParentId = False

    def __init__(self, input_str):
        super().__init__()
        self.event_nodes = []
        texts = input_str.split('\n')
        if texts is None or len(texts) == 0:
            self.parse_failed()
            return
        finger_str = texts[0]
        self.finger = get_value_as_int(finger_str, get_sample_key(event_procedure_keyword, 'finger'),
                                       get_sample_separator_count(event_procedure_keyword, 'finger'), True)
        self.parse_event_nodes(texts, 1)
        self.check_parse_result()

    #   finger:0
    #    frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0x0
    #     stateHistory:
    #      procedure: HandleTouchDown, timestamp: 2017-08-25 15:00:22.247
    #      procedure: HandleTouchUp, timestamp: 2017-08-25 15:00:22.295
    #    frameNodeId: 84, type: ExclusiveRecognizer, depth: 0, id: 0xf063eed0, parentId: 0x0
    #     stateHistory:
    #      procedure: HandleTouchDown, state: READY, disposal: NONE, timestamp: 2017-08-25 15:00:22.247
    #      procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 15:00:22.295
    #     frameNodeId: 88, type: LongPressRecognizer, depth: 1, id: 0xef748aa0, parentId: 0xf063eed0, customInfo:
    #     duration: 500, isForDrag: 0, repeat: 0, fingers: 1
    #      stateHistory:
    #       procedure: HandleTouchDown, state: DETECTING, disposal: NONE, timestamp: 2017-08-25 15:00:22.247
    #       procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 15:00:22.295
    #     frameNodeId: 84, type: PanRecognizer, depth: 1, id: 0xf3d6bfc0, parentId: 0xf063eed0, customInfo:
    #     direction: 3, isForDrag: 0, distance: 7.5, fingers: 1
    #      stateHistory:
    #       procedure: HandleTouchDown, state: DETECTING, disposal: NONE, timestamp: 2017-08-25 15:00:22.247
    #       procedure: HandleTouchUp, state: FAIL, disposal: REJECT, timestamp: 2017-08-25 15:00:22.295
    def parse_event_nodes(self, spliced_lines, start_index):
        start_keyword = get_sample_key(event_procedure_keyword, 'frameNodeId')
        end_keywords = [start_keyword, get_dict_value(keywords_dict, 'event tree')]
        current_index = 0
        while current_index < len(spliced_lines):
            if current_index < start_index:
                current_index += 1
                self.isNeedParentId = True
                continue
            current_line = spliced_lines[current_index]
            if current_line.find('frameNodeId') != -1:
                packed_result = pack_string_until_next_keyword(spliced_lines, current_index, start_keyword,
                                                               end_keywords)
                packed_str = packed_result[0]
                if packed_str is None or len(packed_str) == 0:
                    current_index += 1
                    continue
                current_index = packed_result[1]
                event_node = EventNode(packed_str, self.isNeedParentId)
                self.isNeedParentId = False
                if event_node is not None:
                    self.event_nodes.append(event_node)
            else:
                current_index += 1

    def check_parse_result(self):
        if self.finger is None or self.event_nodes is None or len(self.event_nodes) == 0:
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        result_str = '  finger: ' + str(self.finger)
        for event_node in self.event_nodes:
            result_str += '\n' + event_node.to_string()
        return result_str

    def dump(self):
        log_info(self.to_string())

    def update_event_nodes_with_frame_nodes(self, frame_nodes: List[FrameNode]):
        for event_node in self.event_nodes:
            event_node.update_tag_from_frame_nodes_info(frame_nodes)
