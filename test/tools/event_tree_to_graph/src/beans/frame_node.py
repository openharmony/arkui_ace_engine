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
from src.keywords import hittest_node_keyword
from src.utils.log_wrapper import log_info
from src.utils.value_parser import get_value_as_int, get_value_as_str


# nodeId: 0, parentId: -1, tag: root, monopolizeEvents: 0, isHit: 1, hitTestMode: 0, responseRegion: RectT (0.00,
# 0.00) - [720.00 x 1280.00]
class FrameNode(BaseBean):
    nodeId = 0
    parentId = -1
    tag = ''
    com_id = ''
    monopolizeEvents = 0
    isHit = 1
    hitTestMode = 0
    responseRegion = ''

    original_str = ''

    def __init__(self, node_dump_str):
        super().__init__()
        self.original_str = node_dump_str
        self.nodeId = get_value_as_int(node_dump_str, hittest_node_keyword['nodeId'].key,
                                       hittest_node_keyword['nodeId'].value_separator_count)
        self.parentId = get_value_as_int(node_dump_str, hittest_node_keyword['parentId'].key,
                                         hittest_node_keyword['parentId'].value_separator_count)
        self.tag = get_value_as_str(node_dump_str, hittest_node_keyword['tag'].key,
                                    hittest_node_keyword['tag'].value_separator_count)
        self.com_id = get_value_as_str(node_dump_str, hittest_node_keyword['comId'].key,
                                       hittest_node_keyword['comId'].value_separator_count)
        self.monopolizeEvents = get_value_as_int(node_dump_str, hittest_node_keyword['monopolizeEvents'].key,
                                                 hittest_node_keyword['monopolizeEvents'].value_separator_count)
        self.isHit = get_value_as_int(node_dump_str, hittest_node_keyword['isHit'].key,
                                      hittest_node_keyword['isHit'].value_separator_count)
        self.hitTestMode = get_value_as_int(node_dump_str, hittest_node_keyword['hitTestMode'].key,
                                            hittest_node_keyword['hitTestMode'].value_separator_count)
        self.responseRegion = get_value_as_str(node_dump_str, hittest_node_keyword['responseRegion'].key,
                                               hittest_node_keyword['responseRegion'].value_separator_count, True)
        self.check_parse_result()

    def check_parse_result(self):
        if (self.nodeId is None or self.parentId is None or self.tag is None or self.monopolizeEvents is None or
                self.isHit is None or self.hitTestMode is None or self.responseRegion is None):
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        result_str = '  nodeId: ' + str(self.nodeId) + ', parentId: ' + str(self.parentId) + ', tag: ' + self.tag
        if self.com_id is not None:
            result_str += ', comId: ' + self.com_id
        result_str += ', monopolizeEvents: ' + str(self.monopolizeEvents) + ', isHit: ' + str(
            self.isHit) + ', hitTestMode: ' + str(self.hitTestMode) + ', responseRegion: ' + self.responseRegion
        return result_str

    def dump(self):
        log_info(self.to_string())
