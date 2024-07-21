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


import os

from src.beans.dump_result import DumpResult
from src.keywords import keywords_dict, get_dict_value
from src.utils.log_wrapper import log_error


class ContentParser:
    file_path = ""
    parse_result = None

    def __init__(self, path):
        self.file_path = path

    def is_succeed(self):
        return self.parse_result is not None

    def do_parse(self):
        file_content = self.load_file()
        if file_content is None or file_content == '':
            log_error('file is not exist')
            return None
        event_tree_count = self.pre_check_event_tree_count(file_content)
        if event_tree_count == 0:
            log_error('NO event tree found')
            return None
        self.parse_result = DumpResult(file_content)
        return self.parse_result

    def load_file(self):
        if os.path.exists(self.file_path):
            with open(self.file_path, 'r') as f:
                return f.read()
        else:
            return None

    def pre_check_event_tree_count(self, file_content):
        event_tree_count = 0
        for line in file_content.split('\n'):
            index = line.find(get_dict_value(keywords_dict, 'event tree'))
            if index != -1:
                event_tree_count += 1
        return event_tree_count
