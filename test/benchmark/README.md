# ACE Engine Performance Regression Detection (Ratio-Based)

This directory contains tools for detecting performance regressions in the ACE Engine using a ratio-based methodology that normalizes each benchmark against its corresponding baseline.

## Overview

The ratio-based regression detection system works by:

1. **Running baselines** - Simple operations that provide performance baselines
2. **Running UI benchmarks** - Real UI operations (Creation, Layout, etc.)
3. **Normalizing against baselines** - Each benchmark is measured as a ratio to its baseline (benchmark_time / baseline_time)
4. **Recording historical ratios** - Track ratio trends over time for better regression detection
5. **Detecting ratio changes** - Compare current ratios against thresholds and historical trends

## Key Advantages of Ratio-Based Approach

- **Normalized measurements** - Accounts for system performance variations
- **Historical trend analysis** - Detects gradual performance degradation
- **Better baseline matching** - Intelligent pairing of benchmarks with appropriate baselines
- **Consistent reporting** - Ratios are more stable across different environments
- **Improved sensitivity** - Can detect smaller performance changes over time

## Structure

The benchmark suite is organized into several key components:

### Core Files
- `regression_detector.py` - Main Python script for regression detection on host environment
- `baseline.cpp` - Baseline benchmark implementations

### Components Directory
- Same build structure as unit tests
- Pipeline, rendering, and animations are mocked
- Benchmarks performance of UI component code: creation and layout

### Render Directory
- Benchmarks RosenRenderContext performance
- Core paths including:
  - RenderContext creation
  - SyncGeometryNode operations
  - Render property updates

## Quick Start

### Prerequisites

1. **Build the benchmarks:**
   ```bash
   ./build.sh --product-name rk3568 --build-target benchmark_linux
   ```

2. **Ensure Python 3 is available:**
   ```bash
   python3 --version
   ```

### Running Regression Detection

```bash
# Basic usage
./regression_detector.py

# With custom parameters and historical data
./regression_detector.py \
    --build-dir //out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/ \
    --threshold 1.2 \
    --output regression_report.txt \
    --json-output regression_report.json \
    --historical-data historical_ratios.json \
    --verbose
```

## Benchmark Matching Logic

The system automatically matches baseline benchmarks to component benchmarks using patterns:

| Baseline Benchmark | Component Benchmark Pattern | Purpose |
|-------------------|---------------------------|---------|
| `BaselineNodeCreation` | `CreateGrid`, `Create.*` | Node/component creation performance |
| `BaselineLayoutCalculation` | `LayoutGrid`, `Layout.*` | Layout algorithm performance |
| `BaselineTreeConstruction` | `.*Tree.*Construction.*` | UI tree building performance |
| `BaselinePropertyUpdate` | `.*Property.*Update.*` | Property/style update performance |
| `BaselineTreeTraversal` | `.*Tree.*Traversal.*` | Tree walking performance |

## Adding New Benchmarks

### Adding a Baseline Benchmark

1. Add the benchmark function to `baseline.cpp`:
   ```cpp
   static void BaselineNewOperation(benchmark::State& state) {
       // Implementation
   }
   BENCHMARK(BaselineNewOperation)->Range(8, 8 << 8);
   ```

2. Update the matching patterns in `regression_detector.py`

### Adding a Component Benchmark

1. Create or update a component benchmark file (e.g., `components/new_component_benchmark.cpp`)
2. Add the benchmark to the component BUILD.gn file
3. (Optional) Update the matching patterns to pair with appropriate baseline benchmarks

## Troubleshooting

### Common Issues

1. **Benchmark executables not found**
   - Ensure benchmarks are built: `./build.sh --product-name rk3568 --build-target benchmark_linux`
   - Check the build directory path

2. **No benchmark matches found**
   - Verify benchmark naming follows expected patterns
   - Check the matching rules in configuration

3. **Inconsistent results**
   - Run benchmarks multiple times to account for system variance
   - Ensure system load is consistent during testing
   - Consider using performance isolation techniques

### Debug Mode

Run with verbose output to see detailed information:

```bash
python3 regression_detector.py --verbose
```

## Performance Tips

1. **Run on dedicated hardware** - Avoid running on shared systems
2. **Disable CPU frequency scaling** - Use performance governor
3. **Close unnecessary applications** - Minimize system noise
4. **Run multiple iterations** - Average results over several runs
5. **Use consistent test data** - Ensure benchmark inputs are identical

## Contributing

When adding new benchmarks or modifying the regression detection logic:

1. Follow the existing naming conventions
2. Add appropriate documentation
3. Test with various threshold values
4. Ensure new benchmarks are properly paired with baselines
5. Update this README with any new features
