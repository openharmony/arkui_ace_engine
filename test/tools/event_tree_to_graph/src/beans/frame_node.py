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
from src.keywords import hittest_node_keyword, get_sample_key, get_sample_separator_count
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
        self.nodeId = get_value_as_int(node_dump_str, get_sample_key(hittest_node_keyword, 'nodeId'),
                                       get_sample_separator_count(hittest_node_keyword, 'nodeId'))
        self.parentId = get_value_as_int(node_dump_str, get_sample_key(hittest_node_keyword, 'parentId'),
                                         get_sample_separator_count(hittest_node_keyword, 'parentId'))
        self.tag = get_value_as_str(node_dump_str, get_sample_key(hittest_node_keyword, 'tag'),
                                    get_sample_separator_count(hittest_node_keyword, 'tag'))
        self.com_id = get_value_as_str(node_dump_str, get_sample_key(hittest_node_keyword, 'comId'),
                                       get_sample_separator_count(hittest_node_keyword, 'comId'))
        self.monopolizeEvents = get_value_as_int(node_dump_str,
                                                 get_sample_key(hittest_node_keyword, 'monopolizeEvents'),
                                                 get_sample_separator_count(hittest_node_keyword, 'monopolizeEvents'))
        self.isHit = get_value_as_int(node_dump_str, get_sample_key(hittest_node_keyword, 'isHit'),
                                      get_sample_separator_count(hittest_node_keyword, 'isHit'))
        self.hitTestMode = get_value_as_int(node_dump_str, get_sample_key(hittest_node_keyword, 'hitTestMode'),
                                            get_sample_separator_count(hittest_node_keyword, 'hitTestMode'))
        self.responseRegion = get_value_as_str(node_dump_str, get_sample_key(hittest_node_keyword, 'responseRegion'),
                                               get_sample_separator_count(hittest_node_keyword, 'responseRegion'), True)
        self.check_parse_result()

    def check_parse_result(self):
        if (self.nodeId is None or self.parentId is None or self.tag is None or self.monopolizeEvents is None or
                self.isHit is None or self.hitTestMode is None):
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        result_str = 'nodeId: {}, parentId: {}, tag: {}'.format(self.nodeId, self.parentId, self.tag)
        if self.com_id is not None:
            result_str += ', comId: {}'.format(self.com_id)
        result_str += ', monopolizeEvents: {}, isHit: {}, hitTestMode: {}, responseRegion: {}'.format(
            self.monopolizeEvents, self.isHit, self.hitTestMode, self.responseRegion)
        return result_str

    def get_summary_string(self):
        result_str = '{}({}) , isHit: {}'.format(self.tag, self.nodeId, self.isHit)
        return result_str

    def get_showup_string(self):
        result_str = ("{}({})\n\nisHit: {}\nhitTestMode: {}"
                      .format(self.tag, self.nodeId, self.isHit, self.hitTestMode))
        return result_str

    def dump(self):
        log_info(self.to_string())
