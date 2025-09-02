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
Performance Regression Detector for ArkUI ACE Engine

This script runs baseline and UI benchmarks to detect performance regressions
by comparing the ratio between baseline and actual benchmark performance.
"""

import argparse
import json
import os
import re
import subprocess
import sys
import time
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple

BUILD_DIR_FROM_SCRIPT = "../../../../../out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/"
DEFAULT_BENCHMARK_EXEC = "ace_components"
HISTORICAL_DATA_FILE = Path(__file__).parent / "historical_ratios.json"

@dataclass
class BenchmarkResult:
    """Represents a single benchmark result."""
    name: str
    time_ns: float
    iterations: int
    cpu_time_ns: float
    real_time_ns: float
    bytes_per_second: Optional[float] = None
    items_per_second: Optional[float] = None


@dataclass
class NormalizedBenchmarkResult:
    """Represents a benchmark result normalized against its baseline."""
    name: str
    baseline_name: str
    raw_time_ns: float
    baseline_time_ns: float
    ratio_to_baseline: float
    iterations: int
    benchmark_type: str  # 'baseline' or 'benchmark'


@dataclass
class RegressionReport:
    """Represents a regression analysis report."""
    baseline_results: List[BenchmarkResult]
    benchmark_results: List[BenchmarkResult]
    normalized_benchmark: List[NormalizedBenchmarkResult]
    historical_ratios: Dict[str, List[float]]  # For tracking ratio changes over time
    regressions: List[Dict[str, any]]
    timestamp: str
    summary: Dict[str, any]


class BenchmarkRunner:
    """Handles running benchmarks and parsing results."""
    
    def __init__(self, build_dir: str, benchmark_exe: str):
        self.build_dir = Path(build_dir)
        self.baseline_exe = self.build_dir / "ace_baseline"
        self.benchmark_exe = self.build_dir / benchmark_exe

    def run_benchmark(self, executable: Path, format_type: str = "json", benchmark_filter: str = None) -> Dict:
        """Run a benchmark executable and return parsed results."""
        if not executable.exists():
            raise FileNotFoundError(f"Benchmark executable not found: {executable}")
        
        cmd = [str(executable), f"--benchmark_format={format_type}"]
        
        # Add benchmark filter if specified
        if benchmark_filter:
            cmd.append(f"--benchmark_filter={benchmark_filter}")
        
        try:
            print(f"Running benchmark: {executable.name}")
            if benchmark_filter:
                print(f"🎯 Filter: {benchmark_filter}")
            result = subprocess.run(
                cmd, 
                capture_output=True, 
                text=True, 
                check=True,
                timeout=300  # 5 minute timeout
            )
            
            if format_type == "json":
                return json.loads(result.stdout)
            else:
                return {"raw_output": result.stdout}
                
        except subprocess.CalledProcessError as e:
            print(f"❌ Error running benchmark {executable}: {e}")
            print(f"🔍 Stderr: {e.stderr}")
            raise
        except subprocess.TimeoutExpired:
            print(f"⏰ Benchmark {executable} timed out")
            raise
        except json.JSONDecodeError as e:
            print(f"🔍 Error parsing JSON output from {executable}: {e}")
            print(f"📄 Raw output: {result.stdout}")
            raise
    
    def parse_benchmark_results(self, raw_results: Dict) -> List[BenchmarkResult]:
        """Parse benchmark results from JSON format."""
        results = []
        
        if "benchmarks" not in raw_results:
            print("⚠️ Warning: No 'benchmarks' key found in results")
            return results
        
        for bench in raw_results["benchmarks"]:
            result = BenchmarkResult(
                name=bench.get("name", "unknown"),
                time_ns=bench.get("time", 0),
                iterations=bench.get("iterations", 0),
                cpu_time_ns=bench.get("cpu_time", 0),
                real_time_ns=bench.get("real_time", 0),
                bytes_per_second=bench.get("bytes_per_second"),
                items_per_second=bench.get("items_per_second")
            )
            results.append(result)
        
        return results


class RegressionAnalyzer:
    """Analyzes benchmark results for performance regressions using ratio-based methodology."""
    
    def __init__(self, regression_threshold: float):
        """
        Initialize analyzer.
        
        Args:
            regression_threshold: Factor above which ratio change is considered a regression
        """
        self.regression_threshold = regression_threshold
        self.historical_data = self._load_historical_data()
    
    def _load_historical_data(self) -> Dict[str, List[float]]:
        """Load historical ratio data from file."""
        if not os.path.exists(HISTORICAL_DATA_FILE):
            print(f"⚠️ Warning: Historical data file not found: {HISTORICAL_DATA_FILE}")
            return {}
        
        try:
            with open(HISTORICAL_DATA_FILE, 'r') as f:
                return json.load(f)
        except (json.JSONDecodeError, IOError):
            return {}
    
    def _save_historical_data(self, data: Dict[str, List[float]]):
        """Save historical ratio data to file."""
        try:
            with open(HISTORICAL_DATA_FILE, 'w') as f:
                json.dump(data, f, indent=2)
        except IOError as e:
            print(f"⚠️ Warning: Could not save historical data: {e}")
    
    def find_baseline_reference(self, benchmark_name: str, baselines: List[BenchmarkResult]) -> Optional[BenchmarkResult]:
        """Find the most appropriate baseline for a given benchmark."""
        # Enhanced matching patterns with more specific rules
        patterns = [
            # Direct size-based matching (prefer same parameter size)
            (r"(\w+)/(\d+)", r"Baseline\w+/\2"),
            
            # Operation-based matching
            (r"Create(\w+)", r"BaselineNodeCreation"),
            (r"Layout(\w+)", r"BaselineLayoutCalculation"), 
            (r"Build(\w+)", r"BaselineTreeConstruction"),
            (r"Update(\w+)", r"BaselinePropertyUpdate"),
            (r"Traverse(\w+)", r"BaselineTreeTraversal"),
            (r"(\w+)Tree(\w+)", r"BaselineTreeConstruction"),
            (r"(\w+)Property(\w+)", r"BaselinePropertyUpdate"),
            
            # Generic fallbacks
            (r"Grid", r"BaselineLayoutCalculation"),
            (r"List", r"BaselineTreeConstruction"),
            (r"Node", r"BaselineNodeCreation"),
        ]
        
        # Try to extract size parameter from benchmark name
        size_match = re.search(r'/(\d+)', benchmark_name)
        target_size = int(size_match.group(1)) if size_match else None
        
        best_match = None
        best_score = 0
        
        for baseline in baselines:
            score = 0
            
            # Check each pattern
            for bench_pattern, baseline_pattern in patterns:
                if re.search(bench_pattern, benchmark_name, re.IGNORECASE):
                    # Special handling for size-based patterns
                    if "\\2" in baseline_pattern and target_size:
                        # Replace the back-reference with actual size
                        actual_baseline_pattern = baseline_pattern.replace("\\2", str(target_size))
                        if re.search(actual_baseline_pattern, baseline.name, re.IGNORECASE):
                            score += 15  # Higher score for exact size match
                    elif re.search(baseline_pattern, baseline.name, re.IGNORECASE):
                        score += 10
                        
                        # Bonus for size matching
                        if target_size:
                            baseline_size_match = re.search(r'/(\d+)', baseline.name)
                            if baseline_size_match:
                                baseline_size = int(baseline_size_match.group(1))
                                if baseline_size == target_size:
                                    score += 5
                                elif abs(baseline_size - target_size) <= target_size * 0.1:  # Within 10%
                                    score += 2
                        
                        break
            
            if score > best_score:
                best_score = score
                best_match = baseline
        
        return best_match
    
    def normalize_benchmarks(self, baseline_results: List[BenchmarkResult], 
                           benchmark_results: List[BenchmarkResult]) -> List[NormalizedBenchmarkResult]:
        """Normalize all benchmarks against their baselines to create ratios."""
        
        normalized_benchmark = []
        
        # Then, normalize benchmarks against their matched baselines
        for benchmark in benchmark_results:
            baseline_ref = self.find_baseline_reference(benchmark.name, baseline_results)
            
            if baseline_ref and baseline_ref.cpu_time_ns > 0:
                ratio = benchmark.cpu_time_ns / baseline_ref.cpu_time_ns
                
                normalized = NormalizedBenchmarkResult(
                    name=benchmark.name,
                    baseline_name=baseline_ref.name,
                    raw_time_ns=benchmark.cpu_time_ns,
                    baseline_time_ns=baseline_ref.cpu_time_ns,
                    ratio_to_baseline=ratio,
                    iterations=benchmark.iterations,
                    benchmark_type='benchmark'
                )
                normalized_benchmark.append(normalized)
            else:
                print(f"⚠️ Warning: No suitable baseline found for {benchmark.name}")
        
        return normalized_benchmark
    
    def detect_regressions(self, normalized_benchmark: List[NormalizedBenchmarkResult]) -> List[Dict[str, any]]:
        """Detect regressions by comparing current ratios with historical data only."""
        regressions = []
        
        for norm_result in normalized_benchmark:
            current_ratio = norm_result.ratio_to_baseline
            benchmark_name = norm_result.name
            
            # Get historical ratios for this benchmark
            historical_ratios = self.historical_data.get(benchmark_name, [])
            
            # Determine if this is a regression
            is_regression = False
            baseline_ratio = None
            degradation_percent = 0
            severity = "LOW"
            
            # ONLY detect regressions based on historical data
            if len(historical_ratios) >= 3:
                # Use historical data for comparison
                baseline_ratio = sum(historical_ratios[-3:]) / 3
                if current_ratio > baseline_ratio * self.regression_threshold:
                    is_regression = True
                    degradation_percent = (current_ratio / baseline_ratio - 1.0) * 100
            else:
                # No sufficient historical data - skip regression detection
                # This means the benchmark passes regardless of the ratio
                continue
            
            if is_regression:
                # Determine severity based on the ratio
                if current_ratio > 10.0:
                    severity = "CRITICAL"
                elif current_ratio > 3.0:
                    severity = "HIGH"
                elif current_ratio > self.regression_threshold * 1.5:
                    severity = "MEDIUM"
                else:
                    severity = "LOW"
                
                regression = {
                    "benchmark_benchmark": benchmark_name,
                    "baseline_benchmark": norm_result.baseline_name,
                    "current_ratio": current_ratio,
                    "baseline_ratio": baseline_ratio,
                    "degradation_percent": degradation_percent,
                    "raw_time_ns": norm_result.raw_time_ns,
                    "baseline_time_ns": norm_result.baseline_time_ns,
                    "historical_ratios": historical_ratios[-5:] if historical_ratios else [],  # Last 5 for context
                    "severity": severity,
                    "detection_method": "historical" if len(historical_ratios) >= 3 else "absolute_threshold"
                }
                regressions.append(regression)
        
        return regressions
    
    def update_historical_data(self, normalized_benchmark: List[NormalizedBenchmarkResult]):
        """Update historical ratio data with current measurements."""
        for norm_result in normalized_benchmark:
            benchmark_name = norm_result.name
            current_ratio = norm_result.ratio_to_baseline
            
            # Initialize list if not exists
            if benchmark_name not in self.historical_data:
                self.historical_data[benchmark_name] = []
            
            # Add current ratio
            self.historical_data[benchmark_name].append(current_ratio)
            
            # Keep only last 20 measurements to prevent unbounded growth
            if len(self.historical_data[benchmark_name]) > 20:
                self.historical_data[benchmark_name] = self.historical_data[benchmark_name][-20:]
        
        # Save updated data
        self._save_historical_data(self.historical_data)

class ReportGenerator:
    """Generates regression analysis reports."""
    
    def generate_report(self, report: RegressionReport, output_file: Optional[str] = None) -> str:
        """Generate a comprehensive regression report."""
        lines = []
        lines.append("ACE ENGINE PERFORMANCE REGRESSION REPORT (RATIO-BASED)")
        lines.append(f"🕒 Generated: {report.timestamp}")
        lines.append(f"Baseline: {len(report.baseline_results)}")
        lines.append(f"benchmarks: {len(report.benchmark_results)}")
        lines.append(f"Normalized benchmarks: {len(report.normalized_benchmark)}")
        lines.append(f"🚨 Regressions detected: {len(report.regressions)}")
        lines.append("")
        
        # Summary
        lines.append("SUMMARY")
        lines.append("─" * 40)
        if report.regressions:
            critical_count = len([r for r in report.regressions if r["severity"] == "CRITICAL"])
            high_count = len([r for r in report.regressions if r["severity"] == "HIGH"])
            medium_count = len([r for r in report.regressions if r["severity"] == "MEDIUM"])
            low_count = len([r for r in report.regressions if r["severity"] == "LOW"])
            
            lines.append(f"🚨 {len(report.regressions)} performance regression(s) detected:")
            if critical_count > 0:
                lines.append(f"  💥 Critical: {critical_count}")
            if high_count > 0:
                lines.append(f"  🔥 High: {high_count}")
            if medium_count > 0:
                lines.append(f"  ⚠️ Medium: {medium_count}")
            if low_count > 0:
                lines.append(f"  📊 Low: {low_count}")
        else:
            lines.append("✅ No performance regressions detected!")
        
        lines.append("")
        
        # Normalized benchmark ratios
        lines.append("📊 BENCHMARK-TO-BASELINE RATIOS")
        lines.append("─" * 90)
        lines.append(f"{'benchmark Benchmark':<40} {'Baseline':<25} {'Ratio':<10} {'Historical Avg':<15}")
        lines.append("─" * 90)

        for norm_comp in report.normalized_benchmark:
            # Get historical ratios for this benchmark
            historical = report.historical_ratios.get(norm_comp.name, [])
            # Show average of last 3 historical ratios for brevity
            if len(historical) >= 3:
                avg = sum(historical[-3:]) / 3
                historical_str = f"{avg:.2f}"
            elif historical:
                avg = sum(historical) / len(historical)
                historical_str = f"{avg:.2f}"
            else:
                historical_str = "[]"
            
            lines.append(f"{norm_comp.name:<40} {norm_comp.baseline_name:<25} {norm_comp.ratio_to_baseline:<10.2f} {historical_str:<15}")
        lines.append("")
        
        # Historical trends (if available)
        if report.historical_ratios:
            lines.append("📈 HISTORICAL RATIO TRENDS")
            lines.append("─" * 40)
            for comp_name, ratios in report.historical_ratios.items():
                if len(ratios) > 1:
                    trend = "📈" if ratios[-1] > ratios[0] else "📉" if ratios[-1] < ratios[0] else "➡️"
                    lines.append(f"{comp_name}: {ratios[-5:]} {trend}")
            lines.append("")
        
        # Detailed regressions
        if report.regressions:
            lines.append("🚨 REGRESSION DETAILS")
            lines.append("─" * 40)
            
            # Sort regressions by severity and ratio
            severity_order = {"CRITICAL": 0, "HIGH": 1, "MEDIUM": 2, "LOW": 3}
            sorted_regressions = sorted(report.regressions, 
                                      key=lambda x: (severity_order.get(x["severity"], 4), -x["current_ratio"]))
            
            for i, reg in enumerate(sorted_regressions, 1):
                severity_emoji = {
                    "CRITICAL": "💥",
                    "HIGH": "🔥", 
                    "MEDIUM": "⚠️",
                    "LOW": "📊"
                }.get(reg["severity"], "❓")
                
                lines.append(f"{i}. {reg['benchmark_benchmark']} {severity_emoji} {reg['severity']}")
                lines.append(f"   📊 Current Ratio: {reg['current_ratio']:.2f}")
                lines.append(f"   📈 Expected Ratio: {reg['baseline_ratio']:.2f}")
                lines.append(f"   📉 Degradation: {reg['degradation_percent']:.1f}%")
                lines.append(f"   ⏱️ Times: {reg['raw_time_ns']:.0f}ns vs {reg['baseline_time_ns']:.0f}ns")
                lines.append(f"   🔍 Detection: {reg.get('detection_method', 'unknown')}")
                
                if reg.get('historical_ratios'):
                    lines.append(f"   📜 Recent History: {reg['historical_ratios']}")
                
                lines.append("")
        
        report_text = "\n".join(lines)
        
        if output_file:
            with open(output_file, 'w') as f:
                f.write(report_text)
            print(f"📄 Report saved to: {output_file}")
        
        return report_text
    
    def generate_json_report(self, report: RegressionReport, output_file: str):
        """Generate a JSON format report for automated processing."""
        json_data = asdict(report)
        
        with open(output_file, 'w') as f:
            json.dump(json_data, f, indent=2)
        
        print(f"💾 JSON report saved to: {output_file}")


def main():
    """Main entry point for the regression detector."""
    parser = argparse.ArgumentParser(
        description="Detect performance regressions in ACE Engine benchmarks",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python regression_detector.py
  python regression_detector.py --build-dir /custom/path/to/benchmarks
  python regression_detector.py --threshold 1.3 --output regression_report.txt
  python regression_detector.py --json-output results.json
        """
    )
    
    parser.add_argument(
        "--build-dir",
        default=str(Path(__file__).parent / BUILD_DIR_FROM_SCRIPT),
        help="Path to benchmark executables directory"
    )
    
    parser.add_argument(
        "--exe",
        default = DEFAULT_BENCHMARK_EXEC,
        help="Path to benchmark executable"
    )
    parser.add_argument(
        "--filter",
        help="Benchmark filter pattern for benchmarks (regex)"
    )
    
    parser.add_argument(
        "--output",
        help="Output file for text report"
    )
    
    parser.add_argument(
        "--threshold",
        type=float,
        default=1.1,
        help="Regression threshold (ratio above which performance is considered degraded)"
    )
    
    parser.add_argument(
        "--json-output",
        help="Output file for JSON report"
    )
    
    args = parser.parse_args()
    
    try:
        # Initialize benchmarks
        runner = BenchmarkRunner(args.build_dir, args.exe)
        analyzer = RegressionAnalyzer(args.threshold)
        reporter = ReportGenerator()
        
        # Run benchmarks
        baseline_raw = runner.run_benchmark(runner.baseline_exe)
        baseline_results = runner.parse_benchmark_results(baseline_raw)
        print(f"✅ Baseline obtained: {len(baseline_results)} results")
        
        benchmarks_raw = runner.run_benchmark(runner.benchmark_exe, benchmark_filter=args.filter)
        benchmark_results = runner.parse_benchmark_results(benchmarks_raw)
        print(f"✅ Benchmarks obtained: {len(benchmark_results)} results")
        
        # Normalize benchmarks against baselines to create ratios
        print("NORMALIZING BENCHMARKS AGAINST BASELINES...")
        normalized_benchmark = analyzer.normalize_benchmarks(
            baseline_results, benchmark_results)
        print(f"Normalization completed: {len(normalized_benchmark)} normalized benchmarks")
        
        # Detect regressions based on ratios
        print("🚨 DETECTING PERFORMANCE REGRESSIONS...")
        regressions = analyzer.detect_regressions(normalized_benchmark)
        
        if regressions:
            print(f"⚠️ {len(regressions)} potential regressions detected!")
        else:
            print("🎉 No regressions detected!")
        
        print("\n💾 Updating historical data...")
        analyzer.update_historical_data(normalized_benchmark)
        print("✅ Historical data updated")
        
        # Generate report
        print("📊 GENERATING REGRESSION REPORT...")
        report = RegressionReport(
            baseline_results=baseline_results,
            benchmark_results=benchmark_results,
            normalized_benchmark=normalized_benchmark,
            historical_ratios=analyzer.historical_data,
            regressions=regressions,
            timestamp=time.strftime("%Y-%m-%d %H:%M:%S"),
            summary={
                "total_regressions": len(regressions),
                "regression_threshold": args.threshold,
                "critical_regressions": len([r for r in regressions if r["severity"] == "CRITICAL"]),
                "high_regressions": len([r for r in regressions if r["severity"] == "HIGH"])
            }
        )
        
        # Output reports
        report_text = reporter.generate_report(report, args.output)
        
        if args.json_output:
            print(f"💾 Saving JSON report to: {args.json_output}")
            reporter.generate_json_report(report, args.json_output)
        
        if not args.output:
            print("\n" + "="*80)
            print(report_text)
        else:
            print(f"📄 Report saved to: {args.output}")
        
        # Exit with appropriate code based on regression severity
        if regressions:
            critical_regressions = len([r for r in regressions if r["severity"] == "CRITICAL"])
            high_regressions = len([r for r in regressions if r["severity"] == "HIGH"])
            
            if critical_regressions > 0:
                print(f"\n💥 CRITICAL: {critical_regressions} critical regression(s) detected!")
                sys.exit(2)  # Critical regressions
            elif high_regressions > 0:
                print(f"\n⚠️ WARNING: {high_regressions} high-severity regression(s) detected!")
                sys.exit(1)  # High severity regressions
            else:
                print(f"\n📊 INFO: {len(regressions)} low/medium regression(s) detected.")
                sys.exit(1)  # Any regressions
        else:
            print("\n✅ SUCCESS: No performance regressions detected!")
            sys.exit(0)  # Success
            
    except Exception as e:
        print("\n💥 " + "="*60)
        print("❌ FATAL ERROR OCCURRED")
        print("="*60)
        print(f"🚨 Error: {e}")
        print("\nDetailed error trace:")
        import traceback
        traceback.print_exc()
        sys.exit(3)


if __name__ == "__main__":
    main()
