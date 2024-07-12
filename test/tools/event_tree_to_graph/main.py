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


import argparse

from src.content_parser import ContentParser
from src.graph.graph_converter import generate_event_trees_graph
from src.pre_process import handle_file_preprocess
from src.utils.log_wrapper import log_info, log_error


def usage():
    print("python main.py -i input.txt")
    print('\n Usage: main.py <cmd> <input> <output>')
    print('         <cmd>: TODO')
    print('         <input>: input dump file')
    print('         <output>: ouput image file\n')
    return


def parse_args():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("-i", type=str, default="input.txt", help="input the dump source file")
    parser.add_argument("-o", type=str, default="dump_temp.txt", help="output the generated image")
    parser.add_argument("-m", action='store_true', default=False, help="是否生成详细信息")
    argument = parser.parse_args()
    argument.input_file = argument.i
    argument.output_file = argument.o
    argument.detailed = argument.m
    return argument


# python main.py -i input.txt
if __name__ == '__main__':
    # 解析参数
    args = parse_args()
    # 预处理
    handle_file_preprocess(args.input_file, args.output_file)
    # 读取文件，并解析
    dump_result = ContentParser(args.output_file).do_parse()
    if dump_result.is_succeed():
        log_info("解析成功")
        dump_result.dump()
    else:
        log_error("解析失败")
    generate_event_trees_graph(dump_result, args.detailed)
