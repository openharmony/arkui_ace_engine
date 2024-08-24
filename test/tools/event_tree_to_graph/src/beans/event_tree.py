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

from src.beans.base_bean import BaseBean
from src.beans.event_procedures import EventProcedures
from src.beans.frame_node import FrameNode
from src.beans.touch_point import TouchPoint
from src.utils.log_wrapper import log_info, log_error
from src.utils.value_parser import pack_string_until_next_keyword


# includes touch points and frame nodes(hittest) and event procedures
class EventTree(BaseBean):
    tree_id = -1  # the index in dump
    touch_points = []
    frame_nodes = []
    event_procedures = None

    def __init__(self, input_str):
        super().__init__()
        self.tree_id = -1
        self.touch_points = []
        self.frame_nodes = []
        self.event_procedures = None
        self.parse_event_tree(input_str)
        self.check_parse_result()

    def parse_event_tree(self, input_str):
        spliced_lines = input_str.split('\n')
        self.parse_tree_index(spliced_lines)
        current_index = self.parse_touch_points(spliced_lines, 0)
        current_index = self.parse_hit_tests(spliced_lines, current_index)
        current_index = self.parse_event_procedures(spliced_lines, current_index)
        return current_index

    def parse_tree_index(self, lines):
        if lines is None or len(lines) == 0:
            return
        tree_index_str = lines[0]
        spliced_tree_lines = tree_index_str.split(': ')
        if len(spliced_tree_lines) != 2:
            log_error('parse tree index failed, input str: ' + tree_index_str)
            return
        self.tree_id = int(spliced_tree_lines[0])

    def parse_touch_points(self, texts, start_index):
        start_keyword = 'touch points:'
        end_keywords = ['hittest:']
        packed_result = pack_string_until_next_keyword(texts, start_index, start_keyword, end_keywords)
        packed_str = packed_result[0]
        if packed_str is None or len(packed_str) == 0:
            return packed_result[1]
        spliced_touch_points = packed_str.split('\n')
        for touch_point_str in spliced_touch_points:
            if touch_point_str.find('id: ') == -1:
                continue
            touch_point = TouchPoint(touch_point_str)
            if touch_point is not None and touch_point.is_succeed():
                self.touch_points.append(touch_point)
        return packed_result[1]

    def parse_hit_tests(self, texts, start_index):
        start_keyword = 'hittest:'
        end_keywords = ['event procedures:']
        packed_result = pack_string_until_next_keyword(texts, start_index, start_keyword, end_keywords)
        packed_str = packed_result[0]
        if packed_str is None or len(packed_str) == 0:
            return packed_result[1]
        spliced_frame_nodes = packed_str.split('\n')
        for frame_node_str in spliced_frame_nodes:
            if frame_node_str.find('nodeId: ') == -1:
                continue
            frame_node = FrameNode(frame_node_str)
            if frame_node is not None and frame_node.is_succeed():
                self.frame_nodes.append(frame_node)
        return packed_result[1]

    def parse_event_procedures(self, texts, start_index):
        start_keyword = 'event procedures:'
        end_keywords = ['event tree =>']
        packed_result = pack_string_until_next_keyword(texts, start_index, start_keyword, end_keywords)
        packed_str = packed_result[0]
        if packed_str is None or len(packed_str) == 0:
            return packed_result[1]
        self.event_procedures = EventProcedures(packed_str)
        return packed_result[1]

    def is_parse_failed(self):
        if self.tree_id == -1 or self.touch_points is None or len(self.touch_points) == 0:
            return True
        if self.frame_nodes is None or len(self.frame_nodes) == 0 or self.event_procedures is None:
            return True
        return False

    # check the parse result
    def check_parse_result(self):
        if self.is_parse_failed():
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        result_str = 'touch points: '
        for touch_point in self.touch_points:
            result_str += '\n' + touch_point.to_string()
        result_str += '\n' + 'hittest: '
        for frame_node in self.frame_nodes:
            result_str += '\n' + frame_node.to_string()
        result_str += '\n' + self.event_procedures.to_string()
        return result_str

    def dump(self):
        log_info(self.to_string())

    def update_event_nodes(self):
        if self.event_procedures is None or self.frame_nodes is None or len(self.frame_nodes) == 0:
            return
        self.event_procedures.update_event_nodes_with_frame_nodes(self.frame_nodes)
