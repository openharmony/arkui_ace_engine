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

def get_sub_str(input_str, keyword, value_separator_count=0, is_last=False):
    if input_str is None or keyword is None:
        return None
    index = input_str.find(keyword)
    if index == -1:
        return None
    start_index = index + len(keyword)
    if is_last:
        end_index = input_str.find("\n", start_index)
        if end_index == -1:
            end_index = len(input_str)
    else:
        if value_separator_count == 0:
            end_index = input_str.find(",", start_index)
            if end_index == -1:
                # we are reaching the end
                end_index = len(input_str)
        else:
            # 查找 value_separator_count 数量的逗号
            temp_start_index = start_index
            for i in range(value_separator_count):
                temp_start_index = input_str.find(",", temp_start_index) + 1
            end_index = input_str.find(",", temp_start_index)
    if end_index == -1:
        print("no result for ", keyword, " in input string: ", input_str)
        return None
    sub_str = input_str[start_index:end_index]
    return sub_str


# 从给定的字符串中查找给定的关键字，并将该关键字后面直到逗号或行尾之前的内容转换为数字之后返回
# value_separator_count: the count of comma in value
def get_value_as_int(input_str, keyword, value_separator_count=0, is_last=False):
    sub_str = get_sub_str(input_str, keyword, value_separator_count, is_last)
    if sub_str is None:
        return None
    return int(sub_str)


def get_value_as_float(input_str, keyword, value_separator_count=0, is_last=False):
    sub_str = get_sub_str(input_str, keyword, value_separator_count, is_last)
    if sub_str is None:
        return None
    return float(sub_str)


def get_value_as_str(input_str, keyword, value_separator_count=0, is_last=False):
    sub_str = get_sub_str(input_str, keyword, value_separator_count, is_last)
    if sub_str is None:
        return None
    return sub_str


def pack_string_until_next_keyword(texts, start_index, start_keyword, end_keywords):
    if texts is None or start_keyword is None or end_keywords is None:
        return None
    if len(texts) == 0 or len(start_keyword) == 0 or len(end_keywords) == 0:
        return None
    if start_index < 0 or start_index >= len(texts):
        return None
    current_index = 0
    pack_result = ""
    is_start_found = False
    for line in texts:
        if current_index < start_index:
            current_index += 1
            continue
        reach_end = False
        line = line.rstrip("\n")
        if (is_start_found == False) and line.find(start_keyword) != -1:
            is_start_found = True
            pack_result = line
            current_index += 1
            continue
        for keyword in end_keywords:
            if line.find(keyword) != -1:
                reach_end = True
                break
        if reach_end:
            break
        pack_result = f'{pack_result}\n{line}'
        current_index += 1
    return [pack_result, current_index]
