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
from src.keywords import touch_point_keyword, get_sample_key, get_sample_separator_count
from src.utils.log_wrapper import log_info
from src.utils.value_parser import get_value_as_int, get_value_as_str


#   id: 0, point: Offset (278.00, 551.00), screenPoint: Offset (278.00, 551.00), type: TouchUp, timestamp: 2017-08-25
#   15:00:22.295, isInjected: 0
class TouchPoint(BaseBean):
    id = 0
    point = ''
    screenPoint = ''
    type = ''
    timestamp = ''
    isInjected = 0
    original_str = ''
    downFingerIds = 0

    def __init__(self, input_str):
        super().__init__()
        self.original_str = input_str
        self.id = get_value_as_int(input_str, get_sample_key(touch_point_keyword, 'id'),
                                   get_sample_separator_count(touch_point_keyword, 'id'))
        self.point = get_value_as_str(input_str, get_sample_key(touch_point_keyword, 'point'),
                                      get_sample_separator_count(touch_point_keyword, 'point'))
        self.screenPoint = get_value_as_str(input_str, get_sample_key(touch_point_keyword, 'screenPoint'),
                                            get_sample_separator_count(touch_point_keyword, 'screenPoint'))
        self.type = get_value_as_str(input_str, get_sample_key(touch_point_keyword, 'type'),
                                     get_sample_separator_count(touch_point_keyword, 'type'))
        self.timestamp = get_value_as_str(input_str, get_sample_key(touch_point_keyword, 'timestamp'),
                                          get_sample_separator_count(touch_point_keyword, 'timestamp'))
        self.isInjected = get_value_as_int(input_str, get_sample_key(touch_point_keyword, 'isInjected'),
                                           get_sample_separator_count(touch_point_keyword, 'isInjected'))
        self.downFingerIds = get_value_as_str(input_str, get_sample_key(touch_point_keyword, 'downFingerIds'),
                                           get_sample_separator_count(touch_point_keyword, 'downFingerIds'), True)
        self.check_parse_result()

    def check_parse_result(self):
        if (self.id is None or self.type is None or self.timestamp
                is None or self.isInjected is None):
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        return ('id: {}, point: {}, screenPoint: {}, type: {}, timestamp: {}, isInjected: {}, downFingerIds: {}'
                .format(self.id, self.point, self.screenPoint, self.type, self.timestamp, self.isInjected, self.downFingerIds))

    def to_summary_string(self):
        return ('id: {}, {}, {}, {}, {}'
                .format(str(self.id), self.point, self.screenPoint, self.type, self.timestamp))

    def dump(self):
        log_info(self.to_string())
