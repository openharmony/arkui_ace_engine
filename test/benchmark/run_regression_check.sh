#!/bin/bash
# 
# ACE Engine Performance Regression Detection Script
# 
# This script runs performance benchmarks and detects regressions by comparing
# baseline performance with component benchmarks.
#

set -e  # Exit on any error

# Default configuration
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="../../../out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/" # assuming you run the script from ace_engine
OUTPUT_DIR="${SCRIPT_DIR}/reports"
HISTORICAL_DATA="${SCRIPT_DIR}/historical_ratios.json"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
VERBOSE=""

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show usage
show_usage() {
    cat << EOF
Usage: $0 [OPTIONS]

Detect performance regressions in ACE Engine benchmarks.

OPTIONS:
    -d, --build-dir DIR    OpenHarmony project root directory
                           Script will append: /out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/
    -o, --output-dir DIR    Output directory for reports (default: ./reports)
    -v, --verbose          Enable verbose output
    -h, --help             Show this help message

EXAMPLES:
    $0 -d /path/to/build                 # Minimum required usage
    $0 -d /path/to/build -o /tmp/reports  # Custom output directory

EXIT CODES:
    0 - No regressions detected
    1 - Critical/High severity regressions detected
    2 - Low/Medium severity regressions detected
    3 - Error occurred during execution

EOF
}

# Parse command line arguments
parse_args() {
    while [[ $# -gt 0 ]]; do
        case $1 in
            -d|--build-dir)
                BUILD_DIR="$2/out/rk3568/clang_x64/tests/benchmark/ace_engine/benchmark/"
                shift 2
                    ;;
                -o|--output-dir)
                    OUTPUT_DIR="$2"
                    shift 2
                    ;;
            -v|--verbose)
                VERBOSE="--verbose"
                shift
                ;;
            -h|--help)
                show_usage
                exit 0
                ;;
            *)
                print_error "Unknown option: $1"
                show_usage
                exit 1
                ;;
        esac
    done
    
    # Validate required parameters
    if [[ -z "$BUILD_DIR" ]]; then
        print_error "Build directory is required. Use -d or --build-dir to specify it."
        show_usage
        exit 1
    fi
}

# Function to check prerequisites
check_prerequisites() {
    print_info "Checking prerequisites..."
    
    # Check if Python 3 is available
    if ! command -v python3 &> /dev/null; then
        print_error "Python 3 is required but not installed."
        exit 3
    fi
    
    # Check if regression detector script exists
    if [[ ! -f "${SCRIPT_DIR}/regression_detector.py" ]]; then
        print_error "regression_detector.py not found in ${SCRIPT_DIR}"
        exit 3
    fi
    
    # Expand build directory path if it starts with //
    if [[ "${BUILD_DIR}" == //* ]]; then
        BUILD_DIR="${BUILD_DIR#//}"
        BUILD_DIR="/${BUILD_DIR}"
    fi
    
    # Check if benchmark executables exist
    if [[ ! -f "${BUILD_DIR}/ace_baseline" ]]; then
        print_error "Baseline benchmark executable not found: ${BUILD_DIR}/ace_baseline"
        print_info "Please build benchmarks first using: ./build.sh --product-name rk3568 --build-target ace_engine:benchmark"
        exit 3
    fi
    
    if [[ ! -f "${BUILD_DIR}/ace_components" ]]; then
        print_error "Components benchmark executable not found: ${BUILD_DIR}/ace_components"
        print_info "Please build benchmarks first using: ./build.sh --product-name rk3568 --build-target ace_engine:benchmark"
        exit 3
    fi
    
    print_success "Prerequisites check passed"
}

# Function to setup output directory
setup_output_dir() {
    if [[ ! -d "$OUTPUT_DIR" ]]; then
        print_info "Creating output directory: $OUTPUT_DIR"
        mkdir -p "$OUTPUT_DIR"
    fi
}

# Function to run regression detection
run_regression_detection() {
    print_info "Starting ratio-based performance regression detection..."
    print_info "Build directory: $BUILD_DIR"
    print_info "Output directory: $OUTPUT_DIR"
    print_info "Historical data: $HISTORICAL_DATA"
    
    # Setup output files
    TEXT_REPORT="${OUTPUT_DIR}/regression_report_${TIMESTAMP}.txt"
    JSON_REPORT="${OUTPUT_DIR}/regression_report_${TIMESTAMP}.json"
    
    # Run the Python regression detector
    python3 "${SCRIPT_DIR}/regression_detector.py" \
        --build-dir "$BUILD_DIR" \
        --output "$TEXT_REPORT" \
        --json-output "$JSON_REPORT" \
        --historical-data "$HISTORICAL_DATA" \
        $VERBOSE
    
    local exit_code=$?
    
    # Process results based on exit code
    case $exit_code in
        0)
            print_success "No performance regressions detected!"
            print_info "Reports saved:"
            print_info "  Text: $TEXT_REPORT"
            print_info "  JSON: $JSON_REPORT"
            if [[ -f "$HISTORICAL_DATA" ]]; then
                print_info "  Historical data updated: $HISTORICAL_DATA"
            fi
            ;;
        1)
            print_error "Critical/High severity performance regressions detected!"
            print_info "Check detailed report: $TEXT_REPORT"
            ;;
        2)
            print_warning "Low/Medium severity performance regressions detected."
            print_info "Check detailed report: $TEXT_REPORT"
            ;;
        3)
            print_error "Error occurred during regression detection."
            ;;
        *)
            print_error "Unexpected exit code: $exit_code"
            ;;
    esac
    
    return $exit_code
}

# Function to generate summary
generate_summary() {
    local exit_code=$1
    
    echo ""
    echo "=========================================="
    echo "REGRESSION DETECTION SUMMARY"
    echo "=========================================="
    echo "Timestamp: $(date)"
    echo "Build Directory: $BUILD_DIR"
    echo "Output Directory: $OUTPUT_DIR"
    echo ""
    
    case $exit_code in
        0)
            echo "Result: ✅ PASS - No regressions"
            ;;
        1)
            echo "Result: ❌ FAIL - Critical regressions"
            ;;
        2)
            echo "Result: ⚠️  WARN - Minor regressions"
            ;;
        *)
            echo "Result: 💥 ERROR - Execution failed"
            ;;
    esac
    
    echo "=========================================="
}

# Main execution
main() {
    local start_time=$(date +%s)
    
    print_info "ACE Engine Performance Regression Detector"
    print_info "============================================"
    
    parse_args "$@"
    check_prerequisites
    setup_output_dir
    
    local exit_code=0
    if run_regression_detection; then
        exit_code=$?
    else
        exit_code=$?
    fi
    
    local end_time=$(date +%s)
    local duration=$((end_time - start_time))
    
    generate_summary $exit_code
    print_info "Execution time: ${duration} seconds"
    
    exit $exit_code
}

# Run main function with all arguments
main "$@"
