#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2026 Huawei Device Co., Ltd.
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
import sys
import os
import time
import shutil
import argparse
import tarfile


def parse_args():
    parser = argparse.ArgumentParser(
        description="Generate ArkUI code using idlizer runner",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="Example:\n"
        "  python generation.py \\\n"
        "    --arkts_sdk_path /path/to/ets_api \\\n"
        "    --base_dir /path/to/arkoala_generator \\\n"
        "    --arkgen_interop_types /path/to/interop-types.h \\\n"
        "    --panda_sdk_path /path/to/panda-sdk \\\n"
        "    --node_bin_path /path/to/node/bin \\\n"
        "    --libarkts_path /path/to/libarkts\n")
    parser.add_argument("--arkts_sdk_path", required=True, help="Path to ArkTS SDK (e.g. ohos_ets_api_path)")
    parser.add_argument("--base_dir", required=True, help="Base directory for output and config files")
    parser.add_argument("--arkgen_interop_types", required=True, help="Path to interop-types.h file")
    parser.add_argument("--panda_sdk_path", required=True, help="Path to panda_sdk.tgz file")
    parser.add_argument("--node_bin_path", required=True, help="Path to Node.js bin directory")
    parser.add_argument("--libarkts_path", required=True, help="Path to libarkts.tgz file")

    return parser.parse_args()


def main():
    args = parse_args()

    arkts_sdk_path = args.arkts_sdk_path
    base_dir = args.base_dir
    arkgen_interop_types = args.arkgen_interop_types
    panda_sdk_path = args.panda_sdk_path
    node_bin_path = args.node_bin_path
    libarkts_path = args.libarkts_path

    output_dir = os.path.join(base_dir, "out")
    arkgen_options_file = os.path.join(base_dir, "generation_config/arkgen-config.json")
    scraper_options_file = os.path.join(base_dir, "generation_config/scraper-config.json")
    etsgen_options_file = os.path.join(base_dir, "generation_config/etsgen-config.json")
    idl_pattern = os.path.join(base_dir, "arkui_extra_idl")

    arkts_sdk_path = os.path.dirname(arkts_sdk_path)

    node = os.path.join(node_bin_path, "node")
    npm = os.path.join(node_bin_path, "npm")
    npx = os.path.join(node_bin_path, "npx")

    script_dir = os.path.dirname(os.path.abspath(__file__))

    start_time = time.time()

    libarkts_dest = os.path.join(base_dir, "libarkts")
    panda_sdk_dest = os.path.join(base_dir, "libarkts", "sdk")
    env = os.environ.copy()
    env["PATH"] = node_bin_path + os.pathsep + env.get("PATH", "")
    env["PANDA_SDK_PATH"] = panda_sdk_dest

    # step0 clean previous build artifacts
    print(f"Step0: Running npm run clean in {script_dir}...")
    try:
        subprocess.run([npm, "run", "clean"], env=env, cwd=script_dir, check=True, capture_output=True, text=True)
        print("npm run clean completed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error: npm run clean failed with exit code {e.returncode}")
        print("STDOUT:", e.stdout)
        print("STDERR:", e.stderr)
        sys.exit(1)
    except FileNotFoundError:
        print("Error: 'npm' command not found. Please ensure Node.js and npm are installed and in PATH.")
        sys.exit(1)

    # step1 copy libarkts.tgz to libarkts and extract panda_sdk.tgz
    print(f"Step1: Copying {libarkts_path} to {libarkts_dest}...")
    try:
        if os.path.isfile(libarkts_path):
            os.makedirs(libarkts_dest, exist_ok=True)
            shutil.copy2(libarkts_path, libarkts_dest)
            print("libarkts.tgz copied successfully.")
        else:
            print(f"Error: libarkts.tgz not found at {libarkts_path}")
            sys.exit(1)
    except Exception as e:
        print(f"Error: Failed to copy libarkts.tgz: {e}")
        sys.exit(1)

    if panda_sdk_path:
        print(f"Step1: Extracting {panda_sdk_path} to {libarkts_dest}...")
        try:
            if os.path.isfile(panda_sdk_path):
                os.makedirs(libarkts_dest, exist_ok=True)
                with tarfile.open(panda_sdk_path, "r:gz") as tar:
                    tar.extractall(path=libarkts_dest)
                print("panda_sdk.tgz extracted successfully.")
            else:
                print(f"Error: panda_sdk.tgz not found at {panda_sdk_path}")
                sys.exit(1)
        except Exception as e:
            print(f"Error: Failed to extract panda_sdk.tgz: {e}")
            sys.exit(1)
    else:
        print("Step1: Skipped panda_sdk extraction (panda_sdk_path is empty).")

    # step2 install arkui_idlize and libarkts
    print(f"Step2: Running npm install in {script_dir}...")
    try:
        subprocess.run([npm, "install"], env=env, cwd=script_dir, check=True, capture_output=True, text=True)
        print("npm install completed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error: npm install failed with exit code {e.returncode}")
        print("STDOUT:", e.stdout)
        print("STDERR:", e.stderr)
        sys.exit(1)
    except FileNotFoundError:
        print("Error: 'npm' command not found. Please ensure Node.js and npm are installed and in PATH.")
        sys.exit(1)

    # step3 generate code
    cmd = [
        npx, "@idlizer/runner", "m3", arkts_sdk_path,
        idl_pattern,
        "--sdk-stage", "prepared",
        "--arkgen-options-file", arkgen_options_file,
        "--etsgen-options-file", etsgen_options_file,
        "--arkgen-interop-types", arkgen_interop_types,
        "--scraper-options-file", scraper_options_file,
        "--arkgen", f"{npx} @idlizer/arkgen",
        "--etsgen", f"{npx} @idlizer/etsgen",
        "--target", "all",
        "--no-arkgen-dummy-impl",
        "--output", output_dir
    ]

    print(f"Step3: Generation. Running command: {' '.join(cmd)}")

    try:
        result = subprocess.run(cmd, env=env, check=True, cwd=script_dir, capture_output=True, text=True)
        elapsed_time = time.time() - start_time
        seconds = int(elapsed_time)
        milliseconds = int((elapsed_time - seconds) * 1000)
        print(f"Generation completed successfully. Output: {output_dir}")
        print(f"Total time: {seconds} s {milliseconds} ms")
    except subprocess.CalledProcessError as e:
        print(f"Error: Generation failed with exit code {e.returncode}")
        print("STDOUT:", e.stdout)
        print("STDERR:", e.stderr)
        sys.exit(1)
    except FileNotFoundError:
        print("Error: 'npx' command not found. Please ensure Node.js and npm are installed and in PATH.")
        sys.exit(1)

if __name__ == "__main__":
    main()
