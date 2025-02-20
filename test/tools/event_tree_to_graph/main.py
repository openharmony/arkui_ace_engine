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
import os
import subprocess
import sys

from src.content_parser import ContentParser
from src.graph.graph_converter import generate_all_graphs
from src.pre_process import handle_file_preprocess
from src.utils.log_wrapper import log_info, log_error, enable_debug
from src.utils.log_wrapper import log_message

def usage():
    print('python main.py -i input.txt')
    print('\n Usage: main.py <cmd> <input>')
    print('         <cmd>: TODO')
    print('         <input>: input dump file')
    return


def parse_args():
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('-d', action='store_true', default=False, help='enable debug info')
    parser.add_argument('-r', action='store_true', default=False, help='dump event tree with device')
    parser.add_argument('-m', action='store_true', default=False, help='add details info')
    argument = parser.parse_args()
    argument.detailed = argument.m
    argument.dump_from_device = argument.r
    argument.debug = argument.d
    return argument

def delete_file(file_path):
    try:
        os.remove(file_path)
        log_message("delete file successful")
    except OSError as e:
        log_error("delete file error")

def dump_from_device():
    bat_file_path = r'src\bats\dump_event.bat'
    try:
        subprocess.call([bat_file_path])
        print('capture event tree done.')
    except FileNotFoundError:
        print(f'file not found: {bat_file_path}')
    except Exception as e:
        print(f'exception: {e}')


# python main.py -i input.txt
if __name__ == '__main__':
    # parse the args
    args = parse_args()
    generated_file_path = ''
    # config log model
    if args.debug:
        enable_debug(True)
    # dump trace from device if needed
    if os.name == 'nt':
        dump_from_device()
        with open('generated_file_path.txt', 'r') as f:
            generated_file_path = f.read().strip()
    else:
        log_error('only support dump from device on windows')
        sys.exit(1)
    # pre process
    handle_file_preprocess(generated_file_path, 'dump_temp.txt')
    # read the dump file and parse
    dump_result = ContentParser('dump_temp.txt').do_parse()
    if dump_result.is_succeed():
        log_info('parse done')
        dump_result.dump()
    else:
        log_error('parse failed')
    delete_file('generated_file_path.txt')
    generate_all_graphs(dump_result, args.detailed)
