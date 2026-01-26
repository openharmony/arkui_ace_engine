# Standalone Distribution Guide

## Overview

This tool can generate a single-file standalone version of the event tree visualizer for easy distribution.

## Building Standalone Version

### Prerequisites

- Python 3.7+
- All project dependencies (graphviz, etc.)

### Build Command

```bash
python3 build_standalone.py
```

This will generate `event_tree_visualizer.py` - a single executable Python file containing all modules.

## Using the Standalone Version

### Basic Usage

```bash
python3 event_tree_visualizer.py
```

### Dump from Device

```bash
python3 event_tree_visualizer.py -r
```

### Debug Mode

```bash
python3 event_tree_visualizer.py -d
```

### Make Executable (Linux/macOS)

```bash
chmod +x event_tree_visualizer.py
./event_tree_visualizer.py
```

## Distribution

The standalone script is ready for distribution:

1. **Copy the file** to target system
2. **Install dependencies**:
   ```bash
   pip install graphviz
   ```
3. **Install Graphviz executable**:
   - macOS: `brew install graphviz`
   - Linux: `sudo apt-get install graphviz`
   - Windows: Download from https://graphviz.org/download/
4. **Run the script**

## Benefits

✅ **Single File**: No need to copy the entire directory structure
✅ **Easy Distribution**: Just one file to share
✅ **No Directory Requirements**: Works from any location
✅ **All Features**: Includes all functionality (device dump, graph generation, etc.)

## Limitations

⚠️ **Generated Files**: Still requires `output/` directory for generated graphs
⚠️ **Dependencies**: External Python packages (graphviz) still required
⚠️ **Updates**: To update, rebuild from source

## File Size

The standalone script is approximately **78 KB** containing all 19 modules.

## Technical Details

The standalone script:
- Combines all Python modules into a single file
- Uses `from __future__ import annotations` for type hints
- Removes inter-module imports (inlines all code)
- Preserves all functionality
- Adds clear module separators for readability

## Troubleshooting

### Build Fails

Ensure all source files are present:
```bash
ls -la src/
```

### Runtime Error: Module Not Found

This shouldn't happen with the standalone version. If it does, rebuild:
```bash
rm event_tree_visualizer.py
python3 build_standalone.py
```

### Permission Denied

Make the script executable:
```bash
chmod +x event_tree_visualizer.py
```

## Example Workflow

1. **Build standalone version**:
   ```bash
   python3 build_standalone.py
   ```

2. **Test it locally**:
   ```bash
   python3 event_tree_visualizer.py
   ```

3. **Distribute**:
   - Email the file
   - Upload to shared drive
   - Package with documentation

4. **User receives file**:
   - Installs dependencies
   - Runs script directly

## Support

For issues with:
- **Building**: Check all source files are present
- **Running**: Verify dependencies installed
- **Device dump**: Ensure hdc tool available
