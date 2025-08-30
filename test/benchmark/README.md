# ACE Engine Performance Regression Detection (Ratio-Based)

This directory contains tools for detecting performance regressions in the ACE Engine using a ratio-based methodology that normalizes each benchmark against its corresponding baseline.

## Overview

The ratio-based regression detection system works by:

1. **Running baseline benchmarks** - Simple operations that provide performance baselines
2. **Running component benchmarks** - Real UI component operations (Creation, Layout, etc.)
3. **Normalizing against baselines** - Each benchmark is measured as a ratio to its baseline (component_time / baseline_time)
4. **Recording historical ratios** - Track ratio trends over time for better regression detection
5. **Detecting ratio changes** - Compare current ratios against thresholds and historical trends

## Key Advantages of Ratio-Based Approach

- **Normalized measurements** - Accounts for system performance variations
- **Historical trend analysis** - Detects gradual performance degradation
- **Better baseline matching** - Intelligent pairing of components with appropriate baselines
- **Consistent reporting** - Ratios are more stable across different environments
- **Improved sensitivity** - Can detect smaller performance changes over time

## Files

- `regression_detector.py` - Main Python script for regression detection
- `run_regression_check.sh` - Shell wrapper script for easy execution
- `regression_config.ini` - Configuration file for customizing detection parameters
- `baseline.cpp` - Baseline benchmark implementations

## Quick Start

### Prerequisites

1. **Build the benchmarks:**
   ```bash
   ./build.sh --product-name rk3568 --build-target ace_engine:benchmark
   ```

2. **Ensure Python 3 is available:**
   ```bash
   python3 --version
   ```

### Running Regression Detection

#### Using the Shell Script (Recommended)

```bash
# Basic usage with defaults
./run_regression_check.sh

# Custom threshold and verbose output
./run_regression_check.sh --threshold 1.3 --verbose

# Custom build directory
./run_regression_check.sh --build-dir /path/to/benchmarks

# Custom output directory
./run_regression_check.sh --output-dir /tmp/reports
```

#### Using the Python Script Directly

```bash
# Basic usage
python3 regression_detector.py

# With custom parameters and historical data
python3 regression_detector.py \
    --build-dir //out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/ \
    --threshold 1.2 \
    --output regression_report.txt \
    --json-output regression_report.json \
    --historical-data historical_ratios.json \
    --verbose
```

## Configuration

Edit `regression_config.ini` to customize:

- **Regression thresholds** - Per-component or global thresholds
- **Benchmark matching rules** - How baseline and component benchmarks are paired
- **Severity levels** - Classification of regression severity
- **Reporting options** - Output formats and content
- **CI integration** - Failure conditions for automated pipelines

## Output

The system generates two types of reports:

### Text Report
```
================================================================================
ACE ENGINE PERFORMANCE REGRESSION REPORT (RATIO-BASED)
================================================================================
Generated: 2025-08-30 14:30:25
Baseline benchmarks: 7
Component benchmarks: 2
Normalized components: 2
Regressions detected: 1

SUMMARY
----------------------------------------
HIGH: 1 regression(s)

BENCHMARK-TO-BASELINE RATIOS
----------------------------------------------------------------------
Component Benchmark                      Baseline                  Ratio      Status
--------------------------------------------------------------------------------
LayoutGrid/128                           BaselineLayoutCalculation/128 1.65       REGRESSION
CreateGrid/64                            BaselineNodeCreation/64   1.15       OK

HISTORICAL RATIO TRENDS
----------------------------------------
LayoutGrid/128: [1.2, 1.3, 1.4, 1.5, 1.65] ↗

REGRESSION DETAILS
----------------------------------------
1. LayoutGrid/128
   Baseline: BaselineLayoutCalculation/128
   Current Ratio: 1.65
   Expected Ratio: 1.20
   Degradation: 37.5%
   Severity: HIGH
   Regression Type: threshold
   Times: 13200000ns vs 8000000ns
   Recent History: [1.2, 1.3, 1.4, 1.5, 1.65]
```

### JSON Report
```json
{
  "baseline_results": [...],
  "component_results": [...],
  "normalized_baselines": [...],
  "normalized_components": [
    {
      "name": "LayoutGrid/128",
      "baseline_name": "BaselineLayoutCalculation/128",
      "raw_time_ns": 13200000,
      "baseline_time_ns": 8000000,
      "ratio_to_baseline": 1.65,
      "iterations": 50,
      "benchmark_type": "component"
    }
  ],
  "historical_ratios": {
    "LayoutGrid/128": [1.2, 1.3, 1.4, 1.5, 1.65]
  },
  "regressions": [
    {
      "component_benchmark": "LayoutGrid/128",
      "baseline_benchmark": "BaselineLayoutCalculation/128",
      "current_ratio": 1.65,
      "baseline_ratio": 1.20,
      "degradation_percent": 37.5,
      "regression_type": "threshold",
      "severity": "HIGH",
      "historical_ratios": [1.2, 1.3, 1.4, 1.5, 1.65]
    }
  ],
  "timestamp": "2025-08-30 14:30:25",
  "summary": {
    "total_regressions": 1,
    "critical_regressions": 0,
    "high_regressions": 1
  }
}
```

## Exit Codes

The regression detector uses the following exit codes:

- **0** - No regressions detected (SUCCESS)
- **1** - Critical/High severity regressions detected (FAILURE)
- **2** - Low/Medium severity regressions detected (WARNING)
- **3** - Error occurred during execution (ERROR)

## Integration with CI/CD

### GitLab CI Example

```yaml
performance_regression_check:
  stage: test
  script:
    - ./build.sh --product-name rk3568 --build-target ace_engine:benchmark
    - cd test/benchmark
    - ./run_regression_check.sh --threshold 1.2
  artifacts:
    when: always
    paths:
      - test/benchmark/reports/
    reports:
      junit: test/benchmark/reports/regression_report_*.json
  only:
    - merge_requests
    - main
```

### GitHub Actions Example

```yaml
name: Performance Regression Check
on: [push, pull_request]

jobs:
  regression-check:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Build Benchmarks
        run: ./build.sh --product-name rk3568 --build-target ace_engine:benchmark
        
      - name: Run Regression Detection
        run: |
          cd test/benchmark
          ./run_regression_check.sh --threshold 1.2 --verbose
          
      - name: Upload Reports
        uses: actions/upload-artifact@v3
        if: always()
        with:
          name: regression-reports
          path: test/benchmark/reports/
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

2. Update the matching patterns in `regression_detector.py` or `regression_config.ini`

### Adding a Component Benchmark

1. Create or update a component benchmark file (e.g., `components/new_component_benchmark.cpp`)
2. Add the benchmark to the component BUILD.gn file
3. Update the matching patterns to pair with appropriate baseline benchmarks

## Troubleshooting

### Common Issues

1. **Benchmark executables not found**
   - Ensure benchmarks are built: `./build.sh --product-name rk3568 --build-target ace_engine:benchmark`
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
./run_regression_check.sh --verbose
```

Or with the Python script:

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
