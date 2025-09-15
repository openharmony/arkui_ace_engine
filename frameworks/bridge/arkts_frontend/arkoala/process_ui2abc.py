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


import os
import sys
import json
import time
import shutil
import subprocess
from typing import Dict, List

from preprocess import merge_component
from build import scan_directory_for_paths

class Paths:
    def __init__(self):
        self.project_path = None
        self.ohos_ets_api_path = None
        self.ohos_ets_arkts_path = None


def parse_argv(argv) -> Paths:
    """
    parse command line arguments
    """
    if len(argv) < 2:
        print("Usage: python process.py <project_path>")
        sys.exit(1)

    path = Paths()
    path.project_path = os.path.abspath(argv[1])
    path.ohos_ets_api_path = os.path.abspath(argv[2])
    path.ohos_ets_arkts_path = os.path.abspath(argv[3])

    return path

def pre_processing(path: Paths):
    start_time = time.time()
    target_path = os.path.join(
        path.project_path, "arkui-ui2abc-processed")

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

def generate_new_arkts_config(path: Paths):
    """
    generate new ui2abc config json
    """
    paths = {}
    new_paths = {}
    if path.ohos_ets_api_path == "" or path.ohos_ets_arkts_path == "":
        print(f"ohos ets api or arkts path not exists")
        sys.exit(1)
    else:
        scan_paths = [path.ohos_ets_api_path, path.ohos_ets_arkts_path]
        for scan_path in scan_paths:
            scanned_paths = scan_directory_for_paths(scan_path)
            for key, value in scanned_paths.items():
                if key in paths:
                    paths[key].extend(value)
                else:
                    paths[key] = value
    old_arkts_config_path = os.path.join(path.project_path, "ui2abcconfig-m3.json")
    new_arkts_config_path = os.path.join(path.project_path, "ui2abcconfig-m3-merged.json")
    # need take old arkts config json paths splicing to new arkts config paths
    with open(old_arkts_config_path, 'r', encoding='utf-8') as f:
        old_data = json.load(f)
        old_paths = old_data['compilerOptions']['paths']
        for key, value in paths.items():
            if key not in old_paths:
                old_paths[key] = value
        with open(new_arkts_config_path, 'w', encoding="utf-8") as f:
            json.dump(old_data, f, indent=2, ensure_ascii=False)

def main(argv):
    path = parse_argv(argv)
    os.chdir(path.project_path)
    pre_processing(path)
    generate_new_arkts_config(path)


if __name__ == '__main__':
    start_time = time.time()
    main(sys.argv)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Arkoala: build time: {elapsed_time:.2f} seconds")
