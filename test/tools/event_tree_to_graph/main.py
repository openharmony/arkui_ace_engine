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

# Defer imports to allow dependency checking first
ContentParser = None
generate_all_graphs = None
handle_file_preprocess = None
log_info = None
log_error = None
enable_debug = None
log_message = None


def import_modules():
    """Import all required modules after dependency check."""
    global ContentParser, generate_all_graphs, handle_file_preprocess
    global log_info, log_error, enable_debug, log_message

    from src.content_parser import ContentParser
    from src.graph.graph_converter import generate_all_graphs
    from src.pre_process import handle_file_preprocess
    from src.utils.log_wrapper import log_info, log_error, enable_debug, log_message


def safe_print(text):
    """Print text with encoding safety for Windows console."""
    try:
        print(text)
    except UnicodeEncodeError:
        # Fallback for Windows console with GBK encoding
        print(text.encode('ascii', 'ignore').decode('ascii'))


def check_and_install_graphviz():
    """Check if graphviz is installed, and try to install if not."""
    print('='*100)
    safe_print('[CHECK] Checking dependencies...')
    print('='*100)

    # Check Python package
    try:
        import graphviz
        safe_print('[OK] Python package "graphviz" is installed.')
    except ImportError:
        safe_print('[ERROR] Python package "graphviz" is NOT installed.')
        print('\nAttempting to install graphviz Python package...\n')

        try:
            # Try to install using pip
            subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'graphviz'],
                                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            print('[OK] Successfully installed graphviz Python package.')
            # Clear the import cache and re-import
            import importlib
            if 'graphviz' in sys.modules:
                del sys.modules['graphviz']
            import graphviz
        except subprocess.CalledProcessError:
            print('[ERROR] Failed to install graphviz Python package automatically.')
            print('\nPlease install it manually:')
            print('  pip install graphviz')
            print('\nOr:')
            print('  python3 -m pip install graphviz')
            return False
        except Exception as e:
            print(f'[ERROR] Error installing graphviz: {e}')
            return False

    # Check graphviz executable (dot)
    dot_found = False
    try:
        result = subprocess.run(['dot', '-V'],
                              capture_output=True, text=True, timeout=5)
        if result.returncode == 0:
            print(f'[OK] Graphviz executable "dot" is installed.')
            if 'version' in result.stderr.lower():
                version = result.stderr.strip().split('version')[-1].strip()
                print(f'   Version: {version}')
            dot_found = True
    except (FileNotFoundError, subprocess.TimeoutExpired):
        pass

    if not dot_found:
        print('[ERROR] Graphviz executable is NOT installed.')
        print('\n[WARNING]  The Python package is installed, but Graphviz executable is missing.')
        print('\nPlease install Graphviz executable:')
        if sys.platform == 'darwin':
            print('  macOS: brew install graphviz')
            print('         Or download from: https://graphviz.org/download/')
        elif sys.platform.startswith('linux'):
            print('  Linux: sudo apt-get install graphviz  (Ubuntu/Debian)')
            print('         sudo yum install graphviz      (CentOS/RHEL)')
            print('         Or download from: https://graphviz.org/download/')
        elif os.name == 'nt':
            print('  Windows: Download installer from: https://graphviz.org/download/')
            print('           After installation, add Graphviz bin directory to PATH')
        else:
            print('  Download from: https://graphviz.org/download/')

        print('\n[WARNING]  Note: You need BOTH the Python package AND the executable.')
        print('='*100)
        return False

    print('='*100)
    return True

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

def check_hdc_available():
    """Check if hdc command is available."""
    try:
        result = subprocess.run(['hdc', '--version'],
                              capture_output=True, text=True, timeout=5)
        return result.returncode == 0
    except (FileNotFoundError, subprocess.TimeoutExpired):
        return False

def check_device_connected(verify_responsive=False):
    """Check if device is connected using hdc command.

    Args:
        verify_responsive: If True, execute a test command to verify device is responsive.
                          If False, only check if devices are listed (faster).
    """
    try:
        # First, list all targets
        result = subprocess.run(['hdc', 'list', 'targets'],
                              capture_output=True, text=True, timeout=5)
        if result.returncode != 0:
            return False

        # Check if any device is listed
        devices = result.stdout.strip()
        if not devices or 'Fail' in result.stdout:
            return False

        # Parse device list (each line is a device serial number)
        device_list = [line.strip() for line in devices.split('\n') if line.strip()]

        if not device_list:
            return False

        # If verify_responsive is True, test if device actually responds
        if verify_responsive:
            for device_serial in device_list:
                try:
                    test_result = subprocess.run(
                        ['hdc', 'shell', 'echo', 'test'],
                        capture_output=True,
                        text=True,
                        timeout=3
                    )
                    if test_result.returncode == 0 and 'test' in test_result.stdout:
                        return True  # Device is responsive
                except (subprocess.TimeoutExpired, FileNotFoundError):
                    continue  # Device not responsive, try next one
            return False  # No device responded
        else:
            return True  # Devices are listed, considered connected

    except (FileNotFoundError, subprocess.TimeoutExpired):
        return False

def wait_for_device_connection(timeout_seconds=120):
    """Wait for device to be connected, with timeout."""
    import time

    # First check if hdc is available
    if not check_hdc_available():
        print('\n' + '='*100)
        log_error('hdc command not found!')
        print('='*100)
        print('\n[WARNING]  The hdc (HarmonyOS Device Connector) tool is required for device communication.')
        print('\nPlease install hdc first:')
        print('  1. Install HarmonyOS SDK from: https://developer.harmonyos.com/cn/develop/deveco-studio')
        print('  2. Add hdc to your PATH, or use full path to hdc executable')
        print('\nAfter installation, you can verify with: hdc --version')
        print('='*100)
        return False

    print('\n' + '='*100)
    print('[WAIT] Waiting for device connection...')
    print('='*100)
    print('\n[TIP] Please connect your device using USB or configure network connection.')
    print('   The script will automatically continue when a device is detected.')
    print('   Press Ctrl+C to cancel.\n')

    start_time = time.time()
    check_interval = 2  # Check every 2 seconds

    try:
        while True:
            # Check timeout
            elapsed = time.time() - start_time
            if elapsed >= timeout_seconds:
                print('\n' + '='*100)
                log_error(f'Wait timeout ({timeout_seconds}s). No device connected.')
                print('\n[TIP] Tips:')
                print('  1. Check USB connection')
                print('  2. Enable USB debugging on device')
                print('  3. Check with: hdc list targets')
                print('='*100)
                return False

            # Check device connection (use fast check first, then verify)
            if check_device_connected(verify_responsive=False):
                # Device listed, now verify it's actually responsive
                if check_device_connected(verify_responsive=True):
                    print('\n' + '='*100)
                    print('[OK] Device connected!')
                    print('='*100)
                    return True

            # Show waiting progress with spinner
            remaining = int(timeout_seconds - elapsed)
            dots = '.' * (int(elapsed) % 4 + 1)
            print(f'\r   Waiting{dots} ({remaining}s remaining)', end='', flush=True)

            time.sleep(check_interval)

    except KeyboardInterrupt:
        print('\n\n' + '='*100)
        print('[WARNING]  Cancelled by user.')
        print('='*100)
        return False

def dump_from_device():
    """Dump event tree from connected device."""
    # First check if hdc is available
    if not check_hdc_available():
        print('\n' + '='*100)
        log_error('hdc command not found!')
        print('='*100)
        print('\n[WARNING]  The hdc (HarmonyOS Device Connector) tool is required for device communication.')
        print('\nPlease install hdc first:')
        print('  1. Install HarmonyOS SDK from: https://developer.harmonyos.com/cn/develop/deveco-studio')
        print('  2. Add hdc to your PATH, or use full path to hdc executable')
        print('\nAfter installation, you can verify with: hdc --version')
        print('='*100)
        return False

    # Check if device is connected and responsive, if not, wait for connection
    if not check_device_connected(verify_responsive=True):
        if not wait_for_device_connection():
            return False

    # [WARNING] IMPORTANT: Prompt user to interact with device before dumping
    print('\n' + '='*100)
    print('[DEVICE] Event Tree Dump Requirements')
    print('='*100)
    print('\n[WARNING]  IMPORTANT: Event trees are only recorded when you interact with the device!')
    print('\nBefore dumping, please make sure you have done ONE of the following:')
    print('  [OK] Touched the screen (tap, click, press)')
    print('  [OK] Slid or scrolled on the screen')
    print('  [OK] Performed any gesture on the target window')
    print('\nWhy? Event trees are created ONLY on:')
    print('  • TouchType::DOWN events (when you touch the screen)')
    print('  • AxisAction::BEGIN events (when you start scrolling)')
    print('\nIf you just opened the app without touching, the event tree will be EMPTY.')
    print('='*100)

    # Ask user to confirm
    try:
        choice = input('\nHave you interacted with the screen? (Y/N, default=Y): ').strip().upper()
        if choice == 'N' or choice == 'NO':
            print('\n[PAUSE]  Please interact with the device first, then run the dump again.')
            print('[TIP] Tip: Touch or slide on the target window, then immediately run this tool.')
            return False
    except (EOFError, KeyboardInterrupt):
        print('\n\nCancelled.')
        return False

    delete_file("dump_temp.txt")
    delete_file("log.txt")

    # Enable debug mode
    try:
        result = subprocess.run(['hdc', 'shell', 'param', 'set', 'persist.ace.debug.enabled', '1'],
                              capture_output=True, text=True, timeout=5)
        if result.returncode != 0:
            log_error(f'Failed to enable debug mode: {result.stderr}')
            return False
        log_info('Debug mode enabled on device.')
    except (FileNotFoundError, subprocess.TimeoutExpired) as e:
        log_error(f'Failed to enable debug mode: {e}')
        return False

    # Display window list to help user choose
    log_message('Fetching window list from device...')
    print('\n' + '='*100)
    print('Available Windows:')
    print('='*100)

    focus_win_id = None

    try:
        # Run command and show output
        result = subprocess.run(
            ['hdc', 'shell', 'hidumper', '-s', 'WindowManagerService', '-a', '-a'],
            capture_output=True, text=True, timeout=10
        )
        if result.returncode == 0 and 'Fail' not in result.stdout:
            # Parse and display window info in a formatted way
            lines = result.stdout.split('\n')
            for line in lines:
                # Skip empty lines and irrelevant lines
                if not line.strip() or '[ability]' in line or 'ScreenGroup' in line:
                    continue

                if 'Focus window:' in line:
                    # Extract focus window ID (first number after colon)
                    parts = line.split(':')
                    if len(parts) > 1:
                        id_parts = parts[1].strip().split()
                        if id_parts:
                            focus_win_id = id_parts[0]
                    print(line)

                # Show separator lines
                elif line.startswith('---'):
                    print(line)

                # Show header line
                elif 'WindowName' in line and 'DisplayId' in line:
                    print(line)

                # Show data lines - must contain WindowName but not be header
                # and not contain metadata like "All Focus window"
                elif ('WindowName' not in line and
                      'Focus window:' not in line and
                      'All Focus window' not in line and
                      not line.startswith('---') and
                      len(line.split()) >= 6):  # Window data lines have at least 6 fields
                    print(line)

            print('='*100)
            if focus_win_id:
                print(f'\n[TIP] Tip: Current focus window is WinId: {focus_win_id}')
                print(f'   You can directly input: {focus_win_id}\n')
        else:
            print('Failed to fetch window list.')
            print('='*100 + '\n')
    except (subprocess.TimeoutExpired, FileNotFoundError) as e:
        print(f'Warning: Failed to fetch window list: {e}')
        print('='*100 + '\n')

    # Get window ID from user
    try:
        prompt = 'Please input WindowId'
        if focus_win_id:
            prompt += f' (press Enter to use focus window {focus_win_id})'
        prompt += ': '

        window_id = input(prompt)
        window_id = window_id.strip()

        # Use focus window if user pressed Enter without input
        if not window_id and focus_win_id:
            window_id = focus_win_id
            log_message(f'Using focus window: {window_id}')

        if not window_id:
            log_error('WindowId cannot be empty.')
            return False
    except (EOFError, KeyboardInterrupt):
        log_error('Input cancelled.')
        return False

    # Clean up old dump files on device
    log_message('Cleaning up old dump files on device...')
    try:
        # Find dump files
        find_result = subprocess.run(['hdc', 'shell', 'find', 'data/', '-name', 'arkui.dump'],
                                   capture_output=True, text=True, timeout=5)
        if find_result.returncode == 0 and find_result.stdout.strip():
            # Remove each found file
            for dump_file in find_result.stdout.strip().split('\n'):
                if dump_file.strip():
                    subprocess.run(['hdc', 'shell', 'rm', dump_file.strip()],
                                 capture_output=True, timeout=5)
                    log_message(f'Removed: {dump_file.strip()}')
    except (subprocess.TimeoutExpired, FileNotFoundError):
        # Ignore cleanup errors
        pass

    # Dump event tree
    log_message('Dumping event tree from device...')
    try:
        # Use shell=True to properly handle quotes in the command
        cmd = f'hdc shell "hidumper -s WindowManagerService -a \'-w {window_id} -event\'"'
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=30)

        # Check return code first
        if result.returncode != 0:
            log_error('Failed to dump event tree.')
            if result.stderr:
                log_error(f'hidumper error: {result.stderr}')
            return False

        # Check if output is empty
        if not result.stdout.strip():
            log_error('Dump output is empty!')
            log_error('Possible causes:')
            log_error('  1. Window ID is invalid or window does not exist')
            log_error('  2. persist.ace.debug.enabled is not set to 1')
            log_error('  3. No event tree data available for this window')
            if result.stderr:
                log_error(f'hidumper stderr: {result.stderr}')
            return False

        # Validate output contains event tree data
        if 'event tree =>' not in result.stdout:
            log_error('Dump output does not contain event tree data!')
            log_error('Output preview:')
            preview = result.stdout[:500] if len(result.stdout) > 500 else result.stdout
            log_error(preview)
            log_error('')
            log_error('[TIP] Tips:')
            log_error('  - Make sure persist.ace.debug.enabled is set to 1')
            log_error('  - Try touching the screen before dumping')
            log_error('  - Check window ID with: hdc shell hidumper -s WindowManagerService -a -a')
            return False

        # Write to file only if validation passed
        with open('dump_temp.txt', 'w', encoding='utf-8') as f:
            f.write(result.stdout)

        log_info('Capture event tree done.')
        return True
    except FileNotFoundError:
        log_error('hdc command not found. Please ensure HarmonyOS SDK is installed and in PATH.')
        return False
    except subprocess.TimeoutExpired:
        log_error('Dump operation timed out.')
        return False


# python main.py -i input.txt
if __name__ == '__main__':
    # Check dependencies first BEFORE importing any modules
    if not check_and_install_graphviz():
        print('\n[ERROR] Cannot proceed without Graphviz.')
        print('Please install the required dependencies and try again.\n')
        sys.exit(1)

    # Import all modules after dependency check passes
    import_modules()

    # parse the args
    args = parse_args()
    # config log model
    if args.debug:
        enable_debug(True)

    # Determine which file to parse
    dump_file = "dump_temp.txt"
    default_input = "./resources/dumpfile/input.txt"

    # Check if device is connected (use fast check for UI decision)
    device_connected = check_device_connected(verify_responsive=False)

    # Track if we dumped from device
    dumped_from_device = False
    dump_file_path = None

    if args.dump_from_device:
        # User explicitly requested dump from device with -r flag
        # dump_from_device() will wait for device if not connected
        if not dump_from_device():
            log_error('Failed to dump event tree from device.')
            sys.exit(1)
        dumped_from_device = True
        dump_file_path = os.path.abspath("dump_temp.txt")
    elif device_connected:
        # Device is connected but user didn't specify -r flag
        # Ask if they want to dump from device
        print('\n' + '='*100)
        print('[DEVICE] Detected connected device.')
        print('='*100)
        print('\nWould you like to dump event tree from the connected device?')
        print('  [Y] Yes - Dump from device')
        print('  [N] No  - Use local input file')
        print('  [Q] Quit')

        try:
            choice = input('\nYour choice (Y/N/Q, default=N): ').strip().upper()

            if choice == 'Y' or choice == 'YES':
                print('\nDumping from device...')
                if not dump_from_device():
                    log_error('Failed to dump event tree from device.')
                    sys.exit(1)
                dumped_from_device = True
                dump_file_path = os.path.abspath("dump_temp.txt")
            elif choice == 'Q' or choice == 'QUIT' or choice == 'E' or choice == 'EXIT':
                print('\nExiting...')
                sys.exit(0)
            else:
                # Default: use local input file
                print('\nUsing local input file...')
        except (EOFError, KeyboardInterrupt):
            print('\n\nCancelled.')
            sys.exit(0)
    else:
        # No device connected, ask if user wants to wait for device or use local file
        print('\n' + '='*100)
        print('[DEVICE] No device detected.')
        print('='*100)

        # Check if hdc is available before offering wait option
        hdc_available = check_hdc_available()

        print('\nWhat would you like to do?')
        if hdc_available:
            print('  [W] Wait for device connection')
        print('  [L] Use local input file')
        print('  [Q] Quit')

        try:
            prompt = '\nYour choice ('
            if hdc_available:
                prompt += 'W/L/Q, default=L): '
            else:
                prompt += 'L/Q, default=L): '

            choice = input(prompt).strip().upper()

            if hdc_available and (choice == 'W' or choice == 'WAIT'):
                print('\nWaiting for device connection...')
                if wait_for_device_connection():
                    print('\nDumping from device...')
                    if not dump_from_device():
                        log_error('Failed to dump event tree from device.')
                        sys.exit(1)
                    dumped_from_device = True
                    dump_file_path = os.path.abspath("dump_temp.txt")
                else:
                    log_error('Failed to connect to device.')
                    log_error('You can use local input file instead.')
                    sys.exit(1)
            elif choice == 'Q' or choice == 'QUIT' or choice == 'E' or choice == 'EXIT':
                print('\nExiting...')
                sys.exit(0)
            else:
                # Default: use local input file
                print('\nUsing local input file...')
        except (EOFError, KeyboardInterrupt):
            print('\n\nCancelled.')
            sys.exit(0)

    # Determine input source
    input_source = None  # Track where the input came from
    if os.path.exists(dump_file):
        log_info(f'Using existing dump file: {dump_file}')
        input_source = dump_file
    elif os.path.exists(default_input):
        log_info(f'Using default input file: {default_input}')
        input_source = default_input
        # Preprocess the input file to generate dump_temp.txt
        handle_file_preprocess(default_input, dump_file)
    else:
        # No input file found - provide helpful guidance
        print('\n' + '='*100)
        log_error('[ERROR] No input file found!')
        print('='*100)
        print('\n[INFO] The tool needs event tree dump data to visualize.')
        print('\n[OPTION 1] Dump from device (Recommended)')
        print('  If you have an OpenHarmony device:')
        print('    1. Connect your device via USB or network')
        print('    2. Run this tool with -r flag:')
        print(f'       python3 {os.path.basename(__file__)} -r')
        print('    3. Interact with the device screen when prompted')
        print('')
        print('\n[OPTION 2] Use existing dump file')
        print(f'  If you have event tree dump data from another source:')
        print(f'    1. Create the directory: {os.path.dirname(default_input)}')
        print(f'    2. Save your dump file to: {default_input}')
        print(f'    3. Or place preprocessed file at: {dump_file}')
        print('')
        print('[TIP] The dump file should contain "event tree =>" markers.')
        print('[TIP] You can get dump data using: hdc shell hidumper -s <WindowManagerService> -a -a')
        print('='*100 + '\n')
        sys.exit(1)

    try:
        # read the dump file and parse
        dump_result = ContentParser(dump_file).do_parse()

        # Check if parsing succeeded
        if dump_result is None:
            log_error('Failed to parse dump file!')
            log_error(f'Please check {dump_file} content:')
            if os.path.exists(dump_file):
                with open(dump_file, 'r') as f:
                    content = f.read()
                    if len(content) == 0:
                        log_error('  File is empty!')
                    elif len(content) < 100:
                        log_error(f'  Content: {content}')
                    else:
                        log_error(f'  File size: {len(content)} bytes')
                        log_error(f'  First 200 chars: {content[:200]}')
            log_error('')
            log_error('[TIP] Tips:')
            log_error('  - Make sure the file contains valid event tree dump data')
            log_error('  - Check that "event tree =>" appears in the file')
            log_error('  - Try dumping from device again')
            sys.exit(1)

        if dump_result.is_succeed():
            log_info('parse done')
            dump_result.dump()
        else:
            log_error('parse failed')
            sys.exit(1)

        # Generate all graphs
        generate_all_graphs(dump_result, args.detailed)

        # Display success message
        print('\n' + '='*100)
        print('[OK] Event tree visualization completed successfully!')
        print('='*100)

        # Show source file info if dumped from device
        if dumped_from_device and dump_file_path:
            print(f'\n[DEVICE] Dumped event tree from device.')
            print(f'[FILE] Source file: {dump_file_path}')
            if os.path.exists(dump_file_path):
                file_size = os.path.getsize(dump_file_path)
                print(f'   File size: {file_size:,} bytes')
                print(f'   [TIP] You can reuse this file for faster processing next time.')

        print(f'\n[GRAPH] Generated {dump_result.get_tree_count()} event tree(s):')

        # List generated files
        import glob
        svg_files = glob.glob(os.path.join('output', '*.svg'))
        if svg_files:
            print(f'\n[DIR] Output directory: {os.path.abspath("output")}/')
            print('\nGenerated files:')
            for svg_file in sorted(svg_files):
                file_size = os.path.getsize(svg_file)
                print(f'  - {os.path.basename(svg_file)} ({file_size:,} bytes)')

        # Ask user if they want to open SVG files
        print('\n' + '='*100)
        try:
            choice = input('Would you like to open the latest event tree SVG now? (Y/N, default=Y): ').strip().upper()
            if choice == '' or choice == 'Y' or choice == 'YES':
                # Filter only event tree files (not hit_test)
                event_tree_files = [f for f in svg_files if 'event_tree' in os.path.basename(f)]

                if event_tree_files:
                    # Sort to get the last one (most recent)
                    event_tree_files.sort()
                    latest_file = event_tree_files[-1]

                    print(f'\n📖 Opening latest event tree: {os.path.basename(latest_file)}')

                    # Open the file using system default method
                    success = False
                    try:
                        if os.name == 'nt':  # Windows
                            os.startfile(latest_file)
                            success = True
                        elif sys.platform == 'darwin':  # macOS
                            subprocess.run(['open', latest_file], check=True, capture_output=True)
                            success = True
                        else:  # Linux
                            subprocess.run(['xdg-open', latest_file], check=True, capture_output=True)
                            success = True

                        if success:
                            print(f'[OK] Successfully opened: {os.path.basename(latest_file)}')
                            print(f'   Location: {os.path.abspath(latest_file)}')

                    except Exception as e:
                        log_error(f'Failed to open {os.path.basename(latest_file)}: {e}')
                        print('\n[TIP] You can manually open the file from:')
                        print(f'   {os.path.abspath("output")}/')
                else:
                    print('\n[WARNING]  No event tree files found to open.')
                    print('[TIP] Make sure the dump contains event tree data.')
            else:
                print('\n[TIP] You can open the SVG files manually later.')
                print(f'   Location: {os.path.abspath("output")}/')

        except (EOFError, KeyboardInterrupt):
            print('\n\nSkipped opening files.')

        print('\n' + '='*100)
        print('\n[TIP] Next steps:')
        print('  1. View the event tree graph in your browser')
        print('  2. Event tree graph shows event node relationships and procedures')
        print('  3. Hit test graphs show frame node hierarchy with hit test results')
        print('  4. Accepted gestures are highlighted in green')
        print('\n[TIP] All generated files are in the output directory if you need them.')
        print('\n' + '='*100 + '\n')

    except Exception as e:
        log_error(f"Error parsing dump file: {e}")
        if args.debug:
            import traceback
            traceback.print_exc()
        sys.exit(1)