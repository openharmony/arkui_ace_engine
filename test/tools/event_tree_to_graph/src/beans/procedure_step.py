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
from src.keywords import event_procedure_keyword, get_sample_key, get_sample_separator_count
from src.utils.log_wrapper import log_info
from src.utils.value_parser import get_value_as_str


# procedure: HandleTouchDown, state: READY, disposal: NONE, timestamp: 2017-08-25 15:00:20.177
class ProcedureStep(BaseBean):
    procedure = ''
    state = ''
    disposal = ''
    timestamp = ''

    original_str = ''

    def __init__(self, input_str):
        super().__init__()
        self.original_str = input_str
        self.procedure = get_value_as_str(input_str, get_sample_key(event_procedure_keyword, 'procedure'),
                                          get_sample_separator_count(event_procedure_keyword, 'procedure'))
        self.state = get_value_as_str(input_str, get_sample_key(event_procedure_keyword, 'state'),
                                      get_sample_separator_count(event_procedure_keyword, 'state'))
        self.disposal = get_value_as_str(input_str, get_sample_key(event_procedure_keyword, 'disposal'),
                                         get_sample_separator_count(event_procedure_keyword, 'disposal'))
        self.timestamp = get_value_as_str(input_str, get_sample_key(event_procedure_keyword, 'timestamp'),
                                          get_sample_separator_count(event_procedure_keyword, 'timestamp'), True)
        self.check_parse_result()

    def check_parse_result(self):
        if self.procedure is None or self.timestamp is None:
            self.parse_failed()
        else:
            self.parse_succeed()

    def get_detailed_summary_string(self):
        result_str = self.procedure
        if self.state is not None:
            result_str += ', state(' + self.state + ')'
        if self.disposal is not None:
            result_str += ', disposal(' + self.disposal + ')'
        return result_str

    def to_string(self):
        result_str = '  procedure: ' + self.procedure
        if self.state is not None:
            result_str += ', state: ' + self.state
        if self.disposal is not None:
            result_str += ', disposal: ' + self.disposal
        result_str += ', timestamp: ' + self.timestamp
        return result_str

    def dump(self):
        log_info(self.to_string())
