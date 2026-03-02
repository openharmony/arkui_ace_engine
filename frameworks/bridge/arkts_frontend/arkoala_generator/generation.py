#!/usr/bin/env python3
import subprocess
import sys
import glob
import os

def main():
    if len(sys.argv) != 9:
        print("Usage: python generation.py <path-to-arkts12-sdk> <directory-to-install-generated-files> <arkgen-options-file> <scraper-options-file> <etsgen-options-file> <arkgen-interop-types> <panda-sdk-path> <node-bin-path>")
        print("Example: python generation.py /path/to/sdk /path/to/output /path/to/arkgen.json /path/to/scraper.json /path/to/etsgen.json /path/to/interop-types /path/to/panda-sdk /path/to/node/bin")
        sys.exit(1)
    
    arkts_sdk_path = sys.argv[1]
    output_dir = sys.argv[2]
    arkgen_options_file = sys.argv[3]
    scraper_options_file = sys.argv[4]
    etsgen_options_file = sys.argv[5]
    arkgen_interop_types = sys.argv[6]
    panda_sdk_path = sys.argv[7]
    node_bin_path = sys.argv[8]

    arkts_sdk_path = os.path.dirname(arkts_sdk_path)


    env = os.environ.copy()
    env["PATH"] = node_bin_path + os.pathsep + env.get("PATH", "")
    env["PANDA_SDK_PATH"] = panda_sdk_path
    
    node = os.path.join(node_bin_path, "node")
    npm = os.path.join(node_bin_path, "npm")
    npx = os.path.join(node_bin_path, "npx")

    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    print(f"Running npm install in {script_dir}...")
    try:
        node_version = subprocess.run([node, "--version"], env=env, cwd=script_dir, check=True, capture_output=True, text=True)
        print(f"Node version: {node_version.stdout.strip()}")
        npm_version = subprocess.run([npm, "--version"], env=env, cwd=script_dir, check=True, capture_output=True, text=True)
        print(f"NPM version: {npm_version.stdout.strip()}")
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
    
    idl_pattern = "node_modules/@idlizer/interfaces/interfaces/arkui-extra/"
    
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
        "--output", output_dir
    ]
    
    print(f"Running command: {' '.join(cmd)}")

    try:
        result = subprocess.run(cmd, env=env, check=True, cwd=script_dir, capture_output=True, text=True)
        print(f"Generation completed successfully. Output: {output_dir}")
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
