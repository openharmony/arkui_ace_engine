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
from src.beans.event_tree import EventTree
from src.keywords import keywords_dict, get_dict_value
from src.utils.log_wrapper import log_info
from src.utils.value_parser import pack_string_until_next_keyword


class DumpResult(BaseBean):
    event_trees = []

    def __init__(self, input_str):
        super().__init__()
        self.event_trees = []
        self.parse_event_trees(input_str)
        self.check_parse_result()
        if self.is_succeed():
            self.update_tree_info()
        log_info('parse result: ' + self.to_string())

    def parse_event_trees(self, input_str):
        if input_str is None or len(input_str) == 0:
            return
        spliced_lines = input_str.split('\n')
        current_index = 0
        start_keyword = get_dict_value(keywords_dict, 'event tree')
        end_keywords = [start_keyword]
        while current_index < len(spliced_lines):
            line = spliced_lines[current_index]
            if line.find(start_keyword) == -1:
                # not found, try next line
                current_index += 1
                continue
            # found, pack one event tree str
            packed_result = pack_string_until_next_keyword(spliced_lines, current_index, start_keyword, end_keywords)
            if packed_result is None:
                # parse end
                return
            packed_str = packed_result[0]
            current_index = packed_result[1]
            if packed_result is None or packed_str is None or len(packed_str) == 0:
                self.parse_failed()
                return
            event_tree = EventTree(packed_str)
            if event_tree.is_succeed():
                self.event_trees.append(event_tree)

    def update_tree_info(self):
        for event_tree in self.event_trees:
            event_tree.update_event_nodes()

    def get_tree_count(self):
        return len(self.event_trees)

    def check_parse_result(self):
        if self.event_trees is None or len(self.event_trees) == 0:
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        result_str = 'DumpResult:'
        index = 0
        for event_tree in self.event_trees:
            result_str += '\nevent tree ' + str(event_tree.tree_id) + '\n' + event_tree.to_string()
            index += 1
        return result_str

    def dump(self):
        log_info(self.to_string())
