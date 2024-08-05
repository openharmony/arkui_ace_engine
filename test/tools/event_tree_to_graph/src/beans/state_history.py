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
from src.beans.procedure_step import ProcedureStep
from src.utils.log_wrapper import log_info


class StateHistory(BaseBean):
    event_procedures = []
    original_str = ''

    def __init__(self, input_str):
        super().__init__()
        self.original_str = input_str
        self.event_procedures = []
        self.splice_event_procedure(input_str)
        self.check_parse_result()

    def splice_event_procedure(self, input_str):
        for line in input_str.split('\n'):
            if line.find('procedure: ') == -1:
                continue
            event_procedure = ProcedureStep(line)
            if event_procedure is not None:
                self.event_procedures.append(event_procedure)

    def check_parse_result(self):
        if self.event_procedures is None or len(self.event_procedures) == 0:
            self.parse_failed()
        else:
            self.parse_succeed()

    def get_detailed_summary_string(self):
        result_str = ''
        for procedure_step in self.event_procedures:
            result_str += procedure_step.get_detailed_summary_string() + '\n'
        result_str.rstrip('\n')
        return result_str

    def to_string(self):
        result_str = '  stateHistory:'
        for event_procedure in self.event_procedures:
            result_str += '\n' + event_procedure.to_string()
        return result_str

    def dump(self):
        log_info(self.to_string())
