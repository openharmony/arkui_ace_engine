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

# Description
#
# This script is invoked by the build system and does not need to be executed directly by the developer.
# First, it checks if --release is provided as an argument. This is the only allowed type for stateMgmt
# that is included in the build image. It then verifies if the node_modules folder exists. If not, npm
# install is executed. Afterward, npm run build_release is performed, which also generates generateGni.js
# The files_to_watch.gni file contains a list of input files from tsconfig.base.json. When any of these
# files are modified, the build system triggers this script to regenerate stateMgmt.js.

import os
import sys
import json
import time
import shutil
import subprocess
from typing import Dict, List

from preprocess import merge_component

class Paths:
    def __init__(self):
        self.project_path = None


def parse_argv(argv) -> Paths:
    """
    parse command line arguments
    """
    if len(argv) < 2:
        print("Usage: python process.py <project_path>")
        sys.exit(1)

    path = Paths()
    path.project_path = os.path.abspath(argv[1])

    return path

def pre_processing(path: Paths):
    start_time = time.time()
    target_path = os.path.join(
        path.project_path, "arkui-preprocessed")

    handwritten_path = os.path.join(target_path, "src", "handwritten", "component")
    generated_path = os.path.join(target_path, "src", "component")
    merge_component(handwritten_path, generated_path)

    if os.path.exists(handwritten_path):
        shutil.rmtree(handwritten_path)
    src_path = os.path.join(target_path, "src")
    dist_path = os.path.join(target_path, "arkui")
    # rename "src" to "arkui"
    if os.path.exists(src_path) and (not os.path.exists(dist_path)):
        shutil.move(src_path, dist_path)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Arkoala: preprocess time: {elapsed_time:.2f} seconds")
    return

def main(argv):
    path = parse_argv(argv)
    os.chdir(path.project_path)
    pre_processing(path)


if __name__ == '__main__':
    start_time = time.time()
    main(sys.argv)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Arkoala: build time: {elapsed_time:.2f} seconds")