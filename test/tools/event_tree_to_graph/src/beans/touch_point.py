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
from src.keywords import touch_point_keyword
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

    def __init__(self, input_str):
        super().__init__()
        self.original_str = input_str
        self.id = get_value_as_int(input_str, touch_point_keyword['id'].key,
                                   touch_point_keyword['id'].value_separator_count)
        self.point = get_value_as_str(input_str, touch_point_keyword['point'].key,
                                      touch_point_keyword['point'].value_separator_count)
        self.screenPoint = get_value_as_str(input_str, touch_point_keyword['screenPoint'].key,
                                            touch_point_keyword['screenPoint'].value_separator_count)
        self.type = get_value_as_str(input_str, touch_point_keyword['type'].key,
                                     touch_point_keyword['type'].value_separator_count)
        self.timestamp = get_value_as_str(input_str, touch_point_keyword['timestamp'].key,
                                          touch_point_keyword['timestamp'].value_separator_count)
        self.isInjected = get_value_as_int(input_str, touch_point_keyword['isInjected'].key,
                                           touch_point_keyword['isInjected'].value_separator_count, True)
        self.check_parse_result()

    def check_parse_result(self):
        if (self.id is None or self.point is None or self.screenPoint is None or self.type is None or self.timestamp
                is None or self.isInjected is None):
            self.parse_failed()
        else:
            self.parse_succeed()

    def to_string(self):
        return '  id: ' + str(
            self.id) + ', point: ' + self.point + ', screenPoint: ' + self.screenPoint + ', type: ' + self.type + (
            ', timestamp: ') + self.timestamp + ', isInjected: ' + str(
            self.isInjected)

    def to_summary_string(self):
        return 'id: ' + str(self.id) + ', ' + self.point + ', ' + self.screenPoint + ', ' + self.type + (
            ', ') + self.timestamp

    def dump(self):
        log_info(self.to_string())
