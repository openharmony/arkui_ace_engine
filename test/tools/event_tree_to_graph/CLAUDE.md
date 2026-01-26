# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **visualization tool for event tree debugging** in OpenHarmony's ACE (ArkUI Cross-platform Engine). It converts dumped event tree data from the system into interactive SVG graphs for debugging gesture recognition and event handling.

## Core Functionality

The tool processes event tree dumps from OpenHarmony devices and generates visual representations:
- **Event Tree Graphs**: Shows touch points, event procedures, and event node relationships
- **Hit Test Graphs**: Displays frame node hierarchy with hit test results
- **Multi-touch Support**: Visualizes different finger scopes with color-coded edges

## Development Commands

### Running the Tool

```bash
# Basic usage (generates simplified view)
python3 main.py

# Detailed mode (shows complete event information)
python3 main.py -m

# Debug mode (enables verbose logging)
python3 main.py -d

# Dump event tree directly from device (Windows only)
python3 main.py -r
```

### Testing

```bash
# Run tests from the project root
python3 -m pytest src/test/

# Run specific test module
python3 -m pytest src/test/beans_test.py
python3 -m pytest src/test/keyword_test.py
```

### Dependencies

```bash
# Install required Python packages
python -m pip install graphviz
```

**Note**: The `graphviz` Python package requires the [Graphviz](https://graphviz.org/download/) executable to be installed and available in PATH.

## Input Data Format

The tool expects event tree dump data in this format:

```
xxx)-(10000:10000:scope)] EventTreeDumpInfo: WindowName: EntryView
xxx)-(10000:10000:scope)] EventTreeDumpInfo: 0: event tree =>
xxx)-(10000:10000:scope)] EventTreeDumpInfo:  touch points:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:   id: 0, point: Offset (392.00, 312.00), type: TouchDown, timestamp: ...
xxx)-(10000:10000:scope)] EventTreeDumpInfo:  hittest:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:   nodeId: 0, parentId: -1, tag: root, ...
xxx)-(10000:10000:scope)] EventTreeDumpInfo:  event procedures:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:   finger:0
xxx)-(10000:10000:scope)] EventTreeDumpInfo:    frameNodeId: 84, type: TouchEventActuator, ...
```

Place input data in `./resources/dumpfile/input.txt`.

## Architecture

### Data Processing Pipeline

```
Input File (dump data)
    ↓
Pre-process (pre_process.py)
    ↓ Removes "EventTreeDumpInfo: " prefix
Content Parser (content_parser.py)
    ↓ Parses keywords and structure
DumpResult (beans/dump_result.py)
    ↓ Contains multiple EventTrees
    ↓
EventTree (beans/event_tree.py)
    ├── TouchPoint[] (beans/touch_point.py)
    ├── FrameNode[] (beans/frame_node.py) - Hit test results
    └── EventProcedures (beans/event_procedures.py)
        └── EventScope[] (beans/event_scope.py) - Per finger
            └── EventNode[] (beans/event_node.py)
                └── StateHistory (beans/state_history.py)
    ↓
Graph Converter (graph/graph_converter.py)
    ↓
SVG Output (./output/)
```

### Key Components

**Parsing Layer** (`src/beans/`):
- `DumpResult`: Top-level container for parsed event trees
- `EventTree`: Represents one complete event tree with touch points, hit tests, and procedures
- `EventProcedures`: Container for event scopes (one per finger)
- `EventNode`: Individual event recognizer with state history
- `FrameNode`: Hit test result node with hierarchy info

**Keyword System** (`src/keywords.py`):
- Defines all parsing keywords with sample values
- `keywords_dict`: Top-level keywords for event tree detection
- `touch_point_keyword`, `hittest_node_keyword`, `event_procedure_keyword`: Section-specific keywords
- `KeyValueSample` class: Stores keyword pattern and separator count for parsing

**Value Parser** (`src/utils/value_parser.py`):
- `get_value_as_int/float/str()`: Extract typed values from strings
- `pack_string_until_next_keyword()`: Groups text between keywords
- Handles comma-separated values with configurable separator counts

**Graph Generation** (`src/graph/graph_converter.py`):
- Recursively builds tree structures from flat node lists using `parentId` relationships
- `build_event_node_tree()`: Creates parent-child hierarchy for event nodes
- `build_hittest_result_tree()`: Creates hierarchy for frame nodes
- Generates color-coded edges for different finger scopes

## Important Design Patterns

### Parent-Child Tree Reconstruction

Both event nodes and frame nodes are stored as flat lists with `parentId` references. The tool reconstructs tree structures:

```python
# In graph_converter.py
node_map = {}  # address/id → EventParentChildrenPair
for item in flatten_nodes:
    node_map[item.address] = EventParentChildrenPair(item)

# Build hierarchy
for item in flatten_nodes:
    if item.parentId is not None and item.parentId != '0x0':
        parent = node_map[item.parentId]
        child = node_map[item.address]
        parent.append_child(child)
```

### Keyword-Driven Parsing

The parser uses keyword matching with sample values to handle variability in log format:

```python
# keywords.py
event_procedure_keyword = {
    "frameNodeId": KeyValueSample("frameNodeId: 84"),  # Sample: "84"
    "type": KeyValueSample("type: TouchEventActuator"),
}

# Usage in parsing
value = get_value_as_int(line, "frameNodeId: ", separator_count=0)
```

### Cross-Referencing

After parsing, `EventNode.tag` is updated by cross-referencing with `FrameNode` data:

```python
# In event_tree.py:134
event_procedures.update_event_nodes_with_frame_nodes(frame_nodes)
```

This allows event nodes to display their component tag (e.g., "Button", "Stack") in the visualization.

## Device Integration

### Windows Batch Script (`src/bats/dump_event.bat`)

The `-r` flag triggers device dump on Windows:
1. Enables ACE debug mode via `hdc shell param set`
2. Prompts for WindowId
3. Executes `hidumper -s WindowManagerService -a '-w <windowId> -event'`
4. Saves output to `dump_temp.txt`

### Preprocessing

Raw device logs contain the `EventTreeDumpInfo: ` prefix on every line. `pre_process.py` removes this prefix to create clean input for the parser.

## Output

Generated SVG files are saved in `./output/`:
- `event_tree_<id>.svg`: Event procedure tree with touch point info
- `hit_test_<id>.svg`: Frame node hierarchy with hit test highlights

Hit test results highlight nodes where `isHit=1` in red for easy identification.

## Common Modifications

- **Adding New Keywords**: Update `keywords.py` with new `KeyValueSample` entries
- **Custom Node Display**: Modify `get_summary_string()` methods in bean classes
- **Graph Styling**: Adjust colors, shapes in `graph_converter.py`
- **New Input Formats**: Extend parsing logic in `content_parser.py` and relevant bean classes
