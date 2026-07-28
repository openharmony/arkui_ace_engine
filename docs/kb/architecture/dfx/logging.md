# DFX Logging Context

> 文档版本：v1.1
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `DFXLogging`

## 定位

DFX Logging 是 ArkUI 引擎的日志基础设施，涵盖 LogWrapper 核心日志框架、HiLog 平台适配、日志控制开关、前端日志桥接（JS console → HiLog）和 HiSysEvent 事件上报。它不是对外公共 API，而是引擎内部 DFX 能力。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体日志级别、格式输出、控制开关行为应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| LogWrapper 核心 | `frameworks/base/log/log_wrapper.h` | LogWrapper：JudgeLevel、GetBriefFileName、SetLogLevel；统一日志级别判断和文件名提取 |
| HiLog 适配 | `adapter/ohos/osal/log_wrapper.cpp` | OHOS 平台 LogWrapper 实现；Ace 日志级别 → HiLog 优先级映射 |
| EventReport 事件上报 | `frameworks/base/log/event_report.h` | EventReport 事件上报接口定义 |
| EventReport OHOS 实现 | `adapter/ohos/osal/event_report.cpp` | HiSysEventWrite 事件上报 OHOS 实现 |
| AceTracker | `frameworks/base/log/ace_tracker.h` | AceTracker 跟踪日志 |
| AceScoringLog | `frameworks/base/log/ace_scoring_log.h` | AceScoringLog 评分日志 |
| AcePerformanceCheck | `frameworks/base/log/ace_performance_check.h` | AcePerformanceCheck 性能检查 |
| AcePerformanceMonitor | `frameworks/base/log/ace_performance_monitor.h` | AcePerformanceMonitor 性能监控 |
| PerfMonitor 日志 | `frameworks/base/perfmonitor/perf_monitor.cpp` | 性能监控日志输出，与 Trace 交叉 |

### API 入口

DFX Logging 是引擎内部能力，没有独立 SDK API。应用侧通过 `console.log` 间接使用前端日志桥接。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| HiLog | `adapter/ohos/osal/log_wrapper.cpp` | `base/hiviewdfx/hilog` | `hilog/log.h` | Ace 日志级别 → HiLog 优先级映射，`HILOG_IMPL()` 宏 |
| HiSysEvent | `adapter/ohos/osal/event_report.cpp` | `base/hiviewdfx/hisysevent` | `hisysevent.h` | `HiSysEventWrite` 事件上报，Domain=ACE |
| HiCollie (XCollie) | `adapter/ohos/osal/event_report.cpp` | `base/hiviewdfx/hicollie` | `xcollie/xcollie.h`, `xcollie/xcollie_define.h` | Form 修改超时定时器 SetTimer/CancelTimer |
| DFX Crash SDK | `adapter/ohos/osal/log_wrapper.cpp` (dlsym) | `base/hiviewdfx` (DFX 核心) | 动态加载符号 `DFX_SetCrashObj`/`DFX_ResetCrashObj`/`GetTrace` | Crash 回调上下文捕获，通过 `dlsym(RTLD_DEFAULT)` 动态加载 |
| ResSched 资源调度 | `adapter/ohos/osal/event_report.cpp` | `foundation/resourceschedule/resource_schedule_service` | `res_sched_client.h`, `res_type.h` | 资源调度事件上报（条件编译 `RESOURCE_SCHEDULE_SERVICE_ENABLE`） |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| LogWrapper Mock | `test/mock/frameworks/base/log/mock_log_wrapper.cpp` | 测试替身，JudgeLevel/GetBriefFileName/SetLogLevel/CheckThread |
| FrameNode 日志级别 | `test/unittest/core/base/frame_node_test_ng.cpp` | 间接测试 LogWrapper::GetLogLevel/SetLogLevel |
| DelayedLogTask | `test/unittest/base/delay_task_test.cpp` | ArkUIDelayLogTaskTest：延时日志任务调度 |
| PerfMonitor accessor | `test/unittest/capi/accessors/global_scope_ohos_arkui_performance_monitor_accessor_test.cpp` | C API PerfMonitor accessor（间接覆盖 jank 日志） |

### 相关 Spec

日志功能域：`specs/03-engine-framework/08-dfx-foundation/01-logging/`（功能 ID `03-08-01`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| LogWrapper 核心与 HiLog 适配 | `specs/03-engine-framework/08-dfx-foundation/01-logging/Feat-01-log-wrapper-core-spec.md` | LogWrapper 接口合约、HiLog 适配、MockLogWrapper |
| 日志控制开关与前端日志桥接 | `specs/03-engine-framework/08-dfx-foundation/01-logging/Feat-02-log-control-frontend-bridge-spec.md` | 日志开关、JS console、LOG_TAG、日志域 |
| HiSysEvent 事件上报与异常诊断 | `specs/03-engine-framework/08-dfx-foundation/01-logging/Feat-03-hisysevent-report-spec.md` | HiSysEvent、故障诊断事件上报 |
| 设计文档 | `specs/03-engine-framework/08-dfx-foundation/01-logging/design.md` | 整体架构设计、ADR |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 日志级别不输出 | LogWrapper::JudgeLevel 判断逻辑、HiLog 优先级映射 |
| 日志格式/文件名不对 | LogWrapper::GetBriefFileName 文件名截取、LogWrapper format 函数 |
| JS console.log 不输出到 HiLog | 前端日志桥接链路 |
| 日志开关不生效 | 日志域 LOG_TAG、开关宏 |
| HiSysEvent 事件不上报 | event_report.cpp 事件定义和注册时机 |

## 调试入口

- LogWrapper 断点：`LogWrapper::JudgeLevel`、`LogWrapper::SetLogLevel`、`LogWrapper::GetBriefFileName`
- HiLog 适配断点：`adapter/ohos/osal/log_wrapper.cpp` 日志级别映射
- EventReport 断点：`adapter/ohos/osal/event_report.cpp` 事件注册与上报

## 相关主题

- Trace 打点：`docs/kb/architecture/dfx/trace.md`
- Dump 机制：`docs/kb/architecture/dfx/dump-mechanism.md`
- 内存管理：`docs/kb/architecture/dfx/memory-management.md`
