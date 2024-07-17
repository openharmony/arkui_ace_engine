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

# Preprocess the input file, removing extraneous information, and generate an intermediate file
import os
import stat

from src.keywords import keywords_dict, get_dict_value
from src.utils.log_wrapper import log_info


def handle_file_preprocess(input_file, output_file):
    # Check if the file at the output file path exists, and if it does, delete it first.
    if os.path.exists(output_file):
        try:
            os.remove(output_file)
        except Exception as e:
            print(f"delete {output_file} failed：{e}")

    with open(input_file, 'r', encoding='utf-8') as infile:
        flags = os.O_WRONLY | os.O_CREAT
        mode = stat.S_IWUSR | stat.S_IRUSR
        with os.fdopen(os.open(output_file, flags, mode), 'w') as outfile:
            event_tree_dump_info_key = get_dict_value(keywords_dict, 'EventTreeDumpInfo')
            for line in infile:
                # find the EventTreeDumpInfo section position
                index = line.find(event_tree_dump_info_key)
                if index != -1:
                    new_index = index + len(event_tree_dump_info_key)
                    newline = line[new_index:]
                    outfile.write(newline)
                else:
                    outfile.write(line)
    log_info("preprocess done: " + input_file + "->" + output_file)
