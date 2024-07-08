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

# 预处理输入文件，去除多余信息，生成一个中间文件
import os
from src.keywords import keywords_dict
from src.utils.log_wrapper import log_info


def handle_file_preprocess(input_file, output_file):
    # 检查输出文件路径的文件是否存在，存在则先删除
    if os.path.exists(output_file):
        try:
            os.remove(output_file)
        except Exception as e:
            # 删除文件时发生错误
            print(f"删除文件 {output_file} 时发生错误：{e}")

    # 打开原始文件和目标文件
    with open(input_file, 'r', encoding='utf-8') as infile, open(output_file, 'w', encoding='utf-8') as outfile:
        # 遍历输入文件的每一行
        for line in infile:
            # 查找'EventTreeDumpInfo'的位置
            index = line.find(keywords_dict['EventTreeDumpInfo'])
            # 如果找到了'EventTreeDumpInfo: '
            if index != -1:
                new_index = index + len(keywords_dict['EventTreeDumpInfo'])
                # 从'EventTreeDumpInfo'开始截取直到行末
                newline = line[new_index:]
                # 将处理后的行写入临时文件
                outfile.write(newline)
            else:
                # 否则直接写入临时文件
                outfile.write(line)
    log_info("输入文件预处理完成：" + input_file + "->" + output_file)

