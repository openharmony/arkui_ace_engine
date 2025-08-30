#!/usr/bin/env python3
"""
Performance Regression Detector for ArkUI ACE Engine

This script runs baseline and UI component benchmarks to detect performance regressions
by comparing the ratio between baseline and actual component performance.
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
    benchmark_type: str  # 'baseline' or 'component'


@dataclass
class RegressionReport:
    """Represents a regression analysis report."""
    baseline_results: List[BenchmarkResult]
    component_results: List[BenchmarkResult]
    normalized_baselines: List[NormalizedBenchmarkResult]
    normalized_components: List[NormalizedBenchmarkResult]
    historical_ratios: Dict[str, List[float]]  # For tracking ratio changes over time
    regressions: List[Dict[str, any]]
    timestamp: str
    summary: Dict[str, any]


class BenchmarkRunner:
    """Handles running benchmarks and parsing results."""
    
    def __init__(self, build_dir: str):
        self.build_dir = Path(build_dir)
        self.baseline_exe = self.build_dir / "ace_baseline"
        self.components_exe = self.build_dir / "ace_components"
    
    def run_benchmark(self, executable: Path, format_type: str = "json") -> Dict:
        """Run a benchmark executable and return parsed results."""
        if not executable.exists():
            raise FileNotFoundError(f"Benchmark executable not found: {executable}")
        
        cmd = [str(executable), f"--benchmark_format={format_type}"]
        
        try:
            print(f"Running benchmark: {executable.name}")
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
            print(f"Error running benchmark {executable}: {e}")
            print(f"Stderr: {e.stderr}")
            raise
        except subprocess.TimeoutExpired:
            print(f"Benchmark {executable} timed out")
            raise
        except json.JSONDecodeError as e:
            print(f"Error parsing JSON output from {executable}: {e}")
            print(f"Raw output: {result.stdout}")
            raise
    
    def parse_benchmark_results(self, raw_results: Dict) -> List[BenchmarkResult]:
        """Parse benchmark results from JSON format."""
        results = []
        
        if "benchmarks" not in raw_results:
            print("Warning: No 'benchmarks' key found in results")
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
    
    def __init__(self, regression_threshold: float, historical_data_file: str):
        """
        Initialize analyzer.
        
        Args:
            regression_threshold: Factor above which ratio change is considered a regression
            historical_data_file: Path to file storing historical ratio data
        """
        self.regression_threshold = regression_threshold
        self.historical_data_file = historical_data_file
        self.historical_data = self._load_historical_data()
    
    def _load_historical_data(self) -> Dict[str, List[float]]:
        """Load historical ratio data from file."""
        if not self.historical_data_file or not os.path.exists(self.historical_data_file):
            return {}
        
        try:
            with open(self.historical_data_file, 'r') as f:
                return json.load(f)
        except (json.JSONDecodeError, IOError):
            return {}
    
    def _save_historical_data(self, data: Dict[str, List[float]]):
        """Save historical ratio data to file."""
        if not self.historical_data_file:
            return
        
        try:
            with open(self.historical_data_file, 'w') as f:
                json.dump(data, f, indent=2)
        except IOError as e:
            print(f"Warning: Could not save historical data: {e}")
    
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
                           component_results: List[BenchmarkResult]) -> Tuple[List[NormalizedBenchmarkResult], List[NormalizedBenchmarkResult]]:
        """Normalize all benchmarks against their baselines to create ratios."""
        
        normalized_baselines = []
        normalized_components = []
        
        # First, normalize baseline benchmarks against themselves (ratio = 1.0)
        for baseline in baseline_results:
            normalized = NormalizedBenchmarkResult(
                name=baseline.name,
                baseline_name=baseline.name,
                raw_time_ns=baseline.cpu_time_ns,
                baseline_time_ns=baseline.cpu_time_ns,
                ratio_to_baseline=1.0,
                iterations=baseline.iterations,
                benchmark_type='baseline'
            )
            normalized_baselines.append(normalized)
        
        # Then, normalize component benchmarks against their matched baselines
        for component in component_results:
            baseline_ref = self.find_baseline_reference(component.name, baseline_results)
            
            if baseline_ref and baseline_ref.cpu_time_ns > 0:
                ratio = component.cpu_time_ns / baseline_ref.cpu_time_ns
                
                normalized = NormalizedBenchmarkResult(
                    name=component.name,
                    baseline_name=baseline_ref.name,
                    raw_time_ns=component.cpu_time_ns,
                    baseline_time_ns=baseline_ref.cpu_time_ns,
                    ratio_to_baseline=ratio,
                    iterations=component.iterations,
                    benchmark_type='component'
                )
                normalized_components.append(normalized)
            else:
                print(f"Warning: No suitable baseline found for {component.name}")
        
        return normalized_baselines, normalized_components
    
    def detect_regressions(self, normalized_components: List[NormalizedBenchmarkResult]) -> List[Dict[str, any]]:
        """Detect regressions by comparing current ratios with thresholds and historical data."""
        regressions = []
        
        for norm_result in normalized_components:
            current_ratio = norm_result.ratio_to_baseline
            benchmark_name = norm_result.name
            
            # Get historical ratios for this benchmark
            historical_ratios = self.historical_data.get(benchmark_name, [])
            
            if len(historical_ratios) < 3:
                continue
            baseline_ratio = sum(historical_ratios[-3:]) / 3
            if current_ratio > baseline_ratio * self.regression_threshold:
                # Calculate degradation percentage
                degradation_percent = (current_ratio / baseline_ratio - 1.0) * 100
                
                regression = {
                    "component_benchmark": benchmark_name,
                    "baseline_benchmark": norm_result.baseline_name,
                    "current_ratio": current_ratio,
                    "baseline_ratio": baseline_ratio,
                    "degradation_percent": degradation_percent,
                    "severity": self._categorize_severity(current_ratio / baseline_ratio),
                    "raw_time_ns": norm_result.raw_time_ns,
                    "baseline_time_ns": norm_result.baseline_time_ns,
                    "historical_ratios": historical_ratios[-5:] if historical_ratios else []  # Last 5 for context
                }
                regressions.append(regression)
        
        return regressions
    
    def update_historical_data(self, normalized_components: List[NormalizedBenchmarkResult]):
        """Update historical ratio data with current measurements."""
        for norm_result in normalized_components:
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
    
    def _categorize_severity(self, ratio: float) -> str:
        """Categorize regression severity based on performance ratio."""
        if ratio >= 2.0:
            return "CRITICAL"
        elif ratio >= 1.5:
            return "HIGH"
        elif ratio >= 1.3:
            return "MEDIUM"
        elif ratio >= 1.2:
            return "LOW"
        else:
            return "NONE"


class ReportGenerator:
    """Generates regression analysis reports."""
    
    def generate_report(self, report: RegressionReport, output_file: Optional[str] = None) -> str:
        """Generate a comprehensive regression report."""
        lines = []
        lines.append("=" * 80)
        lines.append("ACE ENGINE PERFORMANCE REGRESSION REPORT (RATIO-BASED)")
        lines.append("=" * 80)
        lines.append(f"Generated: {report.timestamp}")
        lines.append(f"Baseline benchmarks: {len(report.baseline_results)}")
        lines.append(f"Component benchmarks: {len(report.component_results)}")
        lines.append(f"Normalized components: {len(report.normalized_components)}")
        lines.append(f"Regressions detected: {len(report.regressions)}")
        lines.append("")
        
        # Summary
        lines.append("SUMMARY")
        lines.append("-" * 40)
        if report.regressions:
            severity_counts = {}
            for reg in report.regressions:
                severity = reg["severity"]
                severity_counts[severity] = severity_counts.get(severity, 0) + 1
            
            for severity, count in sorted(severity_counts.items()):
                lines.append(f"{severity}: {count} regression(s)")
        else:
            lines.append("✓ No performance regressions detected!")
        
        lines.append("")
        
        # Normalized benchmark ratios
        lines.append("BENCHMARK-TO-BASELINE RATIOS")
        lines.append("-" * 70)
        lines.append(f"{'Component Benchmark':<40} {'Baseline':<25} {'Ratio':<10} {'Status'}")
        lines.append("-" * 80)
        
        for norm_comp in sorted(report.normalized_components, key=lambda x: x.ratio_to_baseline, reverse=True):
            status = "REGRESSION" if norm_comp.ratio_to_baseline > 1.2 else "OK"
            if norm_comp.ratio_to_baseline < 0.9:
                status = "IMPROVED"
            
            lines.append(f"{norm_comp.name:<40} {norm_comp.baseline_name:<25} {norm_comp.ratio_to_baseline:<10.2f} {status}")
        
        lines.append("")
        
        # Historical trends (if available)
        if report.historical_ratios:
            lines.append("HISTORICAL RATIO TRENDS")
            lines.append("-" * 40)
            for comp_name, ratios in report.historical_ratios.items():
                if len(ratios) > 1:
                    trend = "↗" if ratios[-1] > ratios[0] else "↘" if ratios[-1] < ratios[0] else "→"
                    lines.append(f"{comp_name}: {ratios[-5:]} {trend}")
            lines.append("")
        
        # Detailed regressions
        if report.regressions:
            lines.append("REGRESSION DETAILS")
            lines.append("-" * 40)
            
            for i, reg in enumerate(report.regressions, 1):
                lines.append(f"{i}. {reg['component_benchmark']}")
                lines.append(f"   Baseline: {reg['baseline_benchmark']}")
                lines.append(f"   Current Ratio: {reg['current_ratio']:.2f}")
                lines.append(f"   Expected Ratio: {reg['baseline_ratio']:.2f}")
                lines.append(f"   Degradation: {reg['degradation_percent']:.1f}%")
                lines.append(f"   Severity: {reg['severity']}")
                lines.append(f"   Regression Type: {reg['regression_type']}")
                lines.append(f"   Times: {reg['raw_time_ns']:.0f}ns vs {reg['baseline_time_ns']:.0f}ns")
                
                if reg.get('historical_ratios'):
                    lines.append(f"   Recent History: {reg['historical_ratios']}")
                
                lines.append("")
        
        report_text = "\n".join(lines)
        
        if output_file:
            with open(output_file, 'w') as f:
                f.write(report_text)
            print(f"Report saved to: {output_file}")
        
        return report_text
    
    def generate_json_report(self, report: RegressionReport, output_file: str):
        """Generate a JSON format report for automated processing."""
        json_data = asdict(report)
        
        with open(output_file, 'w') as f:
            json.dump(json_data, f, indent=2)
        
        print(f"JSON report saved to: {output_file}")


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
        default="//out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/",
        help="Path to benchmark executables directory"
    )
    
    parser.add_argument(
        "--threshold",
        type=float,
        default=1.2,
        help="Regression threshold (ratio above which performance is considered degraded)"
    )
    
    parser.add_argument(
        "--output",
        help="Output file for text report"
    )
    
    parser.add_argument(
        "--json-output",
        help="Output file for JSON report"
    )
    
    parser.add_argument(
        "--historical-data",
        help="Path to file for storing historical ratio data"
    )
    
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Enable verbose output"
    )
    
    args = parser.parse_args()
    
    try:
        # Initialize components
        runner = BenchmarkRunner(args.build_dir)
        analyzer = RegressionAnalyzer(args.threshold, args.historical_data)
        reporter = ReportGenerator()
        
        # Run benchmarks
        print("Running baseline benchmarks...")
        baseline_raw = runner.run_benchmark(runner.baseline_exe)
        baseline_results = runner.parse_benchmark_results(baseline_raw)
        
        print("Running component benchmarks...")
        components_raw = runner.run_benchmark(runner.components_exe)
        component_results = runner.parse_benchmark_results(components_raw)
        
        if args.verbose:
            print(f"Baseline results: {len(baseline_results)}")
            print(f"Component results: {len(component_results)}")
        
        # Normalize benchmarks against baselines to create ratios
        print("Normalizing benchmarks against baselines...")
        normalized_baselines, normalized_components = analyzer.normalize_benchmarks(
            baseline_results, component_results)
        
        if args.verbose:
            print(f"Normalized components: {len(normalized_components)}")
            for norm_comp in normalized_components:
                print(f"  {norm_comp.name}: {norm_comp.ratio_to_baseline:.2f} vs {norm_comp.baseline_name}")
        
        # Detect regressions based on ratios
        print("Detecting regressions...")
        regressions = analyzer.detect_regressions(normalized_components)
        
        # Update historical data
        if args.historical_data:
            analyzer.update_historical_data(normalized_components)
        
        # Generate report
        report = RegressionReport(
            baseline_results=baseline_results,
            component_results=component_results,
            normalized_baselines=normalized_baselines,
            normalized_components=normalized_components,
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
            reporter.generate_json_report(report, args.json_output)
        
        if not args.output:
            print(report_text)
        
        # Exit with appropriate code
        if regressions:
            critical_or_high = [r for r in regressions if r["severity"] in ["CRITICAL", "HIGH"]]
            if critical_or_high:
                print(f"\nERROR: {len(critical_or_high)} critical/high severity regressions detected!")
                sys.exit(1)
            else:
                print(f"\nWARNING: {len(regressions)} low/medium severity regressions detected.")
                sys.exit(2)
        else:
            print("\nSUCCESS: No performance regressions detected.")
            sys.exit(0)
            
    except Exception as e:
        print(f"Error: {e}")
        if args.verbose:
            import traceback
            traceback.print_exc()
        sys.exit(3)


if __name__ == "__main__":
    main()
