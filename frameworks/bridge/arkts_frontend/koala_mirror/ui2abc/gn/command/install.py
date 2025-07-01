#!/usr/bin/env python

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

import subprocess
import os
import argparse

NPM_REPO = "https://repo.huaweicloud.com/repository/npm/"
 
parser = argparse.ArgumentParser(description="npm command parser")
parser.add_argument("--project-path", help="project directory in koala repo")
parser.add_argument("--node-path", help="nodejs path")

args = parser.parse_args()

project_path = args.project_path
node_path = args.node_path

env = os.environ.copy()
env_orig = env["PATH"]
env["PATH"] = f"{node_path}:{env['PATH']}"

koala_log = os.path.join(project_path, "koala_build.log")

def execute(dir, args):
    os.chdir(dir)
    if env.get("KOALA_LOG_STDOUT") is not None:
        subprocess.run(args, env=env, text=True, check=True, stderr=subprocess.STDOUT)
        return
    try:
        ret = subprocess.run(args, capture_output=True, env=env, text=True, check=True)
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("install log:\n" + ret.stdout)
            f.close()
    except subprocess.CalledProcessError as e:
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("error message: "+ e.stderr + "\n")
            # In order to see errors in CI log
            print(f.read())
            f.close()

def install(dir):
    execute(dir, ["npm", "install", "--registry", NPM_REPO, "--verbose"])

def main():
    install(project_path)
    
if __name__ == '__main__':
    main()