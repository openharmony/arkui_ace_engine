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
from src.beans.event_scope import EventScope
from src.beans.frame_node import FrameNode
from src.utils.log_wrapper import log_info
from src.utils.value_parser import pack_string_until_next_keyword


class EventProcedures(BaseBean):
    event_scopes = []

    def __init__(self, input_str):
        super().__init__()
        self.event_scopes = []
        self.parse_event_scopes(input_str)
        self.check_parse_result()

    def parse_event_scopes(self, input_str):
        spliced_lines = input_str.split('\n')
        start_keyword = 'finger:'
        end_keywords = ['finger:', 'event tree =>']
        current_index = 0
        while current_index < len(spliced_lines):
            current_line = spliced_lines[current_index]
            if current_line.find('finger:') != -1:
                packed_result = pack_string_until_next_keyword(spliced_lines, current_index, start_keyword,
                                                               end_keywords)
                packed_str = packed_result[0]
                if packed_str is None or len(packed_str) == 0:
                    current_index += 1
                    continue
                current_index = packed_result[1]
                event_scope = EventScope(packed_str)
                if event_scope.is_succeed():
                    self.event_scopes.append(event_scope)
            else:
                current_index += 1

    def update_event_nodes_with_frame_nodes(self, frame_nodes: List[FrameNode]):
        for scope in self.event_scopes:
            scope.update_event_nodes_with_frame_nodes(frame_nodes)

    def check_parse_result(self):
        if self.event_scopes is None or len(self.event_scopes) == 0:
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        result_str = 'event procedures: '
        for scope in self.event_scopes:
            result_str += '\n' + scope.to_string()
        return result_str

    def dump(self):
        log_info(self.to_string())
