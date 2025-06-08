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

import argparse
import os
import shutil
import sys

def copy(src_base, dist_base):
    """Copy arkoala.abc."""
    shutil.copy2(src_base, dist_base)

def main(argv):
    parser = argparse.ArgumentParser(description="Copy arkoala.abc")
    parser.add_argument("--project-path", required=True, help="project path.")
    parser.add_argument("--src", required=True, help="source path.")
    parser.add_argument("--dst", required=True, help="destination path.")
    args = parser.parse_args()

    copy(args.src, args.dst)
    copy(args.src, os.path.join(args.project_path, "dist", "arkoala.abc"))

if __name__ == '__main__':
    main(sys.argv)