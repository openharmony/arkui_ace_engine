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
from src.beans.frame_node import FrameNode
from src.beans.state_history import StateHistory
from src.keywords import event_procedure_keyword, get_sample_key, get_sample_separator_count
from src.utils.log_wrapper import log_info, log_error
from src.utils.value_parser import get_value_as_int, get_value_as_str, get_value_as_float


# frameNodeId: 84, type: PanRecognizer, depth: 1, id: 0xf3d6bfc0, parentId: 0xf063eed0, customInfo: direction: 3,
# isForDrag: 0, distance: 7.5, fingers: 1
class EventNode(BaseBean):
    frameNodeId = 0
    type = ''
    depth = ''
    address = ''  # id
    parentId = '0x0'

    # optional info
    custom_info = None
    direction = None
    duration = None
    isForDrag = None
    distance = None
    repeat = None
    fingers = None

    state_history = None

    original_str = ''

    # updated after parsing done
    tag = ''

    def __init__(self, input_str, isNeedParentId):
        super().__init__()
        texts = input_str.split('\n')
        if len(texts) < 2:
            log_error('EventNode: input_str is invalid')
            return
        self.original_str = input_str
        # parse frame node info
        # frameNodeId: 84, type: TouchEventActuator, depth: 0, id: 0xf072b240, parentId: 0x0
        frame_node_str = texts[0]
        self.frameNodeId = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'frameNodeId'),
                                            get_sample_separator_count(event_procedure_keyword, 'frameNodeId'))
        self.type = get_value_as_str(frame_node_str, get_sample_key(event_procedure_keyword, 'type'),
                                     get_sample_separator_count(event_procedure_keyword, 'type'))
        self.depth = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'depth'),
                                      get_sample_separator_count(event_procedure_keyword, 'depth'))
        self.address = get_value_as_str(frame_node_str, get_sample_key(event_procedure_keyword, 'id'),
                                        get_sample_separator_count(event_procedure_keyword, 'id'))
        if isNeedParentId:
            self.parentId = '0x0'
        else:
            self.parentId = get_value_as_str(frame_node_str, get_sample_key(event_procedure_keyword, 'parentId'),
                                         get_sample_separator_count(event_procedure_keyword, 'parentId'))
        self.duration = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'duration'),
                                         get_sample_separator_count(event_procedure_keyword, 'duration'))
        self.custom_info = get_value_as_str(frame_node_str, get_sample_key(event_procedure_keyword, 'customInfo'),
                                            get_sample_separator_count(event_procedure_keyword, 'customInfo'))
        self.direction = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'direction'),
                                          get_sample_separator_count(event_procedure_keyword, 'direction'))
        self.distance = get_value_as_float(frame_node_str, get_sample_key(event_procedure_keyword, 'distance'),
                                           get_sample_separator_count(event_procedure_keyword, 'distance'))
        self.isForDrag = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'isForDrag'),
                                          get_sample_separator_count(event_procedure_keyword, 'isForDrag'))
        self.repeat = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'repeat'),
                                       get_sample_separator_count(event_procedure_keyword, 'repeat'))
        self.fingers = get_value_as_int(frame_node_str, get_sample_key(event_procedure_keyword, 'fingers'),
                                        get_sample_separator_count(event_procedure_keyword, 'fingers'))
        # parse state history
        self.parse_state_history(texts, 1)
        self.check_parse_result()

    def check_parse_result(self):
        # check the necessary field.s
        if (self.frameNodeId is None or self.type is None or self.depth is None or self.address is None or
                self.parentId is None):
            self.parse_failed()
            return
        if self.state_history is None:
            self.parse_failed()
            return
        self.parse_succeed()

    def parse_state_history(self, text_array, start_index):
        if len(text_array) <= start_index:
            return
        # skip stateHistory itself
        procedures_str = ''
        for i in range(start_index + 1, len(text_array)):
            procedures_str += (text_array[i] + '\n')
        self.state_history = StateHistory(procedures_str)

    def update_tag_from_frame_nodes_info(self, frame_nodes: List[FrameNode]):
        if frame_nodes is None or len(frame_nodes) == 0:
            return
        for frame_node in frame_nodes:
            if frame_node.nodeId == self.frameNodeId:
                self.tag = frame_node.tag
                break

    def get_summary_string(self):
        return self.tag + '(' + str(self.frameNodeId) + ')\n' + self.type + '\n' + self.address

    def get_detailed_summary_string(self):
        return (self.tag + '(' + str(
            self.frameNodeId) + ') ' + self.type + ' ' + self.address + '\n'
                + self.state_history.get_detailed_summary_string())

    def to_string(self):
        result_str = '  frameNodeId: ' + str(self.frameNodeId) + ', type: ' + self.type + ', depth: ' + str(
            self.depth) + ', id: ' + self.address + ', parentId: ' + self.parentId
        if self.custom_info is not None:
            result_str += ',' + ' customInfo: ' + self.custom_info
        if self.direction is not None:
            result_str += ',' + ' direction: ' + str(self.direction)
        if self.distance is not None:
            result_str += ',' + ' distance: ' + str(self.distance)
        if self.duration is not None:
            result_str += ',' + ' duration: ' + str(self.duration)
        if self.repeat is not None:
            result_str += ',' + ' repeat: ' + str(self.repeat)
        if self.isForDrag is not None:
            result_str += ',' + ' isForDrag: ' + str(self.isForDrag)
        if self.fingers is not None:
            result_str += ',' + ' fingers: ' + str(self.fingers)
        result_str += '\n' + self.state_history.to_string()
        return result_str

    def dump(self):
        log_info(self.to_string())
