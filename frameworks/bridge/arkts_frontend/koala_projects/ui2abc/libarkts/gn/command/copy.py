#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2025 Huawei Device Co., Ltd.
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

import argparse
import os
import shutil
import subprocess
import sys


def copy_files(source_path, dest_path, is_file=False):
    try:
        if is_file:
            os.makedirs(os.path.dirname(dest_path), exist_ok=True)
            shutil.copy(source_path, dest_path)
        else:
            shutil.copytree(source_path, dest_path, dirs_exist_ok=True,
                symlinks=True)
    except Exception as err:
        raise Exception("Copy files failed. Error: " + str(err)) from err


def run_cmd(cmd, execution_path=None):
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                           stdin=subprocess.PIPE,
                           stderr=subprocess.PIPE,
                           cwd=execution_path)
    stdout, stderr = proc.communicate(timeout=1000)
    if proc.returncode != 0:
        raise Exception(stdout.decode() + stderr.decode())



def copy_output(options):

    copy_files(os.path.join(options.from_path, 'clang_x64/libes2panda_lib.node'),
            os.path.join(options.to_path, 'build/native/build/es2panda.node'), True)


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--from-path', help='path to output')
    parser.add_argument('--to-path', help='path to root out')

    options = parser.parse_args()
    return options


def main():
    options = parse_args()
    copy_output(options)


if __name__ == '__main__':
    sys.exit(main())