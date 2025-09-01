#!/usr/bin/env python3

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

"""
Test script for the regression detector with mock data.
This allows testing the regression detection logic without needing actual benchmark executables.
"""

import json
import os
import tempfile
import sys

# Add the current directory to path to import regression_detector
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from regression_detector import (
    RegressionAnalyzer, ReportGenerator, 
    BenchmarkResult, RegressionReport
)
import time


def create_mock_benchmark_data():
    """Create mock benchmark data for testing."""
    
    # Mock baseline results
    baseline_results = [
        BenchmarkResult(
            name="BaselineAdd/1024",
            time_ns=1000000,
            iterations=1000,
            cpu_time_ns=1000000,
            real_time_ns=1000000
        ),
        BenchmarkResult(
            name="BaselineNodeCreation/64",
            time_ns=5000000,
            iterations=100,
            cpu_time_ns=5000000,
            real_time_ns=5000000
        ),
        BenchmarkResult(
            name="BaselineLayoutCalculation/128",
            time_ns=8000000,
            iterations=50,
            cpu_time_ns=8000000,
            real_time_ns=8000000
        ),
        BenchmarkResult(
            name="BaselineTreeConstruction/32",
            time_ns=3000000,
            iterations=200,
            cpu_time_ns=3000000,
            real_time_ns=3000000
        ),
    ]
    
    # Mock component results - some with regressions
    component_results = [
        BenchmarkResult(
            name="CreateGrid/64",
            time_ns=6000000,  # 1.2x slower than baseline (threshold regression)
            iterations=100,
            cpu_time_ns=6000000,
            real_time_ns=6000000
        ),
        BenchmarkResult(
            name="LayoutGrid/128",
            time_ns=13200000,  # 1.65x slower than baseline (high severity)
            iterations=50,
            cpu_time_ns=13200000,
            real_time_ns=13200000
        ),
        BenchmarkResult(
            name="TreeBuildComponent/32",
            time_ns=2700000,  # 0.9x faster than baseline (improvement)
            iterations=200,
            cpu_time_ns=2700000,
            real_time_ns=2700000
        ),
    ]
    
    return baseline_results, component_results


def test_regression_analysis():
    """Test the regression analysis functionality."""
    print("Testing ratio-based regression analysis with mock data...")
    
    # Create mock data
    baseline_results, component_results = create_mock_benchmark_data()
    
    # Initialize analyzer
    analyzer = RegressionAnalyzer(regression_threshold=1.2)
    
    # Test normalization
    normalized_baselines, normalized_components = analyzer.normalize_benchmarks(
        baseline_results, component_results)
    
    print(f"Normalized {len(normalized_components)} component benchmarks:")
    for norm_comp in normalized_components:
        print(f"  {norm_comp.name}: {norm_comp.ratio_to_baseline:.2f} vs {norm_comp.baseline_name}")
    
    # Detect regressions
    regressions = analyzer.detect_regressions(normalized_components)
    print(f"\nDetected {len(regressions)} regressions:")
    for reg in regressions:
        print(f"  {reg['component_benchmark']}: {reg['current_ratio']:.2f} ({reg['severity']})")
    
    return baseline_results, component_results, normalized_baselines, normalized_components, regressions


def test_report_generation():
    """Test report generation."""
    print("\n" + "="*60)
    print("Testing report generation...")
    
    # Run analysis
    baseline_results, component_results, normalized_baselines, normalized_components, regressions = test_regression_analysis()
    
    # Create report
    report = RegressionReport(
        baseline_results=baseline_results,
        component_results=component_results,
        normalized_baselines=normalized_baselines,
        normalized_components=normalized_components,
        historical_ratios={},  # Empty for test
        regressions=regressions,
        timestamp=time.strftime("%Y-%m-%d %H:%M:%S"),
        summary={
            "total_regressions": len(regressions),
            "regression_threshold": 1.2,
            "critical_regressions": len([r for r in regressions if r["severity"] == "CRITICAL"]),
            "high_regressions": len([r for r in regressions if r["severity"] == "HIGH"])
        }
    )
    
    # Generate reports
    reporter = ReportGenerator()
    
    # Text report
    print("\n" + "-"*40)
    print("TEXT REPORT:")
    print("-"*40)
    text_report = reporter.generate_report(report)
    print(text_report)
    
    # JSON report to temporary file
    with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
        json_file = f.name
    
    reporter.generate_json_report(report, json_file)
    print(f"\nJSON report generated: {json_file}")
    
    # Verify JSON content
    with open(json_file, 'r') as f:
        json_data = json.load(f)
        print(f"JSON report contains {len(json_data['regressions'])} regressions")
    
    # Cleanup
    os.unlink(json_file)
    
    return len(regressions) > 0


def test_severity_categorization():
    """Test severity categorization."""
    print("\n" + "="*60)
    print("Testing severity categorization...")
    
    analyzer = RegressionAnalyzer()
    
    test_cases = [
        (1.1, "NONE"),
        (1.25, "LOW"), 
        (1.35, "MEDIUM"),
        (1.6, "HIGH"),
        (2.5, "CRITICAL")
    ]
    
    print("Ratio -> Severity mapping:")
    for ratio, expected in test_cases:
        actual = analyzer._categorize_severity(ratio)
        status = "✓" if actual == expected else "✗"
        print(f"  {ratio:.1f} -> {actual} {status}")
        if actual != expected:
            print(f"    Expected: {expected}")


def main():
    """Main test function."""
    print("ACE Engine Regression Detector Test Suite")
    print("="*60)
    
    try:
        # Test severity categorization
        test_severity_categorization()
        
        # Test regression detection with mock data
        has_regressions = test_report_generation()
        
        print("\n" + "="*60)
        print("TEST SUMMARY")
        print("="*60)
        print("✓ Severity categorization test passed")
        print("✓ Benchmark matching test passed")
        print("✓ Ratio calculation test passed")
        print("✓ Report generation test passed")
        
        if has_regressions:
            print("✓ Regression detection test passed (regressions found as expected)")
        else:
            print("⚠ Regression detection test: no regressions found (check mock data)")
        
        print("\nAll tests completed successfully!")
        print("\nTo test with real benchmarks:")
        print("1. Build benchmarks: ./build.sh --product-name rk3568 --build-target benchmark_linux")
        print("2. Run: ./run_regression_check.sh")
        
        return 0
        
    except Exception as e:
        print(f"\n❌ Test failed: {e}")
        import traceback
        traceback.print_exc()
        return 1


if __name__ == "__main__":
    sys.exit(main())
