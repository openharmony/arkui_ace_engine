#!/usr/bin/env python3
import subprocess
import sys
import glob
import os

def main():
    if len(sys.argv) != 8:
        print("Usage: python generation.py <path-to-arkts12-sdk> <directory-to-install-generated-files> <arkgen-options-file> <scraper-options-file> <etsgen-options-file> <arkgen-interop-types> <panda-sdk-path>")
        print("Example: python generation.py /path/to/sdk /path/to/output /path/to/arkgen.json /path/to/scraper.json /path/to/etsgen.json /path/to/interop-types /path/to/panda-sdk")
        sys.exit(1)
    
    arkts_sdk_path = sys.argv[1]
    output_dir = sys.argv[2]
    arkgen_options_file = sys.argv[3]
    scraper_options_file = sys.argv[4]
    etsgen_options_file = sys.argv[5]
    arkgen_interop_types = sys.argv[6]
    panda_sdk_path = sys.argv[7]

    arkts_sdk_path = os.path.dirname(arkts_sdk_path)

    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    print(f"Running npm install in {script_dir}...")
    try:
        subprocess.run(["npm", "install"], cwd=script_dir, check=True, capture_output=True, text=True)
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
        "npx", "@idlizer/runner", "m3", arkts_sdk_path,
        idl_pattern,
        "--sdk-stage", "prepared",
        "--arkgen-options-file", arkgen_options_file,
        "--etsgen-options-file", etsgen_options_file,
        "--arkgen-interop-types", arkgen_interop_types,
        "--scraper-options-file", scraper_options_file,
        "--arkgen", "npx @idlizer/arkgen",
        "--etsgen", "npx @idlizer/etsgen",
        "--output", output_dir
    ]
    
    print(f"Running command: {' '.join(cmd)}")
    
    env = os.environ.copy()
    env["PANDA_SDK_PATH"] = panda_sdk_path
    
    try:
        result = subprocess.run(cmd, check=True, env=env, capture_output=True, text=True)
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
