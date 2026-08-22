# DFX Trace Context

> 文档版本：v1.1
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `DFXTrace`

## 定位

DFX Trace 是 ArkUI 引擎的 Trace 打点基础设施，涵盖 ACE Trace 核心框架与 FrameTrace 适配、帧调度报告与 Jank 检测、性能检查与阈值监控。它不是对外公共 API，而是引擎内部 DFX 能力，与 PerfMonitor 交叉，为帧级性能诊断提供数据。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体打点语义、帧报告、Jank 检测、阈值监控应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ACE Trace 核心 | `frameworks/base/log/ace_trace.h` | ACE_SCOPED_TRACE、ACE_TRACE_BEGIN/END/Finish 打点宏定义，流程级 Trace |
| FrameTrace 适配 | `frameworks/base/log/ace_trace.cpp` | ACE Trace 实现 |
| PerfMonitor | `frameworks/base/perfmonitor/perf_monitor.h` | 性能监控、帧调度统计、场景 ID、报告，与 Trace 交叉 |
| Jank 检测 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | PipelineContext 中的 Jank 检测逻辑、帧调度延迟报告 |
| PerfCheck 阈值 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | PerfCheck、性能阈值检查、超限告警 |

### API 入口

DFX Trace 是引擎内部能力，没有独立 SDK API。PerfMonitor 通过 C API accessor 对外暴露部分帧级性能数据。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| HiTraceMeter | `adapter/ohos/osal/ace_trace.cpp` | `base/hiviewdfx/hitrace` | `hitrace_meter.h` | StartTrace/FinishTrace/StartAsyncTrace/CountTrace/StartTraceEx/FinishTraceEx，HITRACE_TAG_ACE |
| HiTraceChain | `adapter/ohos/osal/trace_id_impl.cpp` | `base/hiviewdfx/hitrace` | `hitrace/trace.h` | HiTraceChain::GetId/SetId/ClearId 跨线程 trace ID 传播 |
| FFRT 帧感知调度 | `adapter/ohos/osal/frame_trace_adapter_impl.cpp` | `foundation/resourceschedule/frame_aware_sched` | `frame_trace.h` | FRAME_TRACE::TraceAndExecute/FrameAwareTraceEnable/IsEnabled |
| HiCollie Watchdog | `adapter/ohos/osal/perf_interfaces.cpp` | `base/hiviewdfx/hicollie` | `xcollie/watchdog.h` | Watchdog::GetInstance().SetScrollState() 滚动状态监控 |
| Hiview PerfMonitorAdapter | `adapter/ohos/osal/perf_interfaces.cpp` | `base/hiviewdfx/hiview` | `perf_monitor_adapter.h` (隐含) | PerfMonitorAdapter::GetInstance() 全套性能监控 API |
| ResSched 资源调度 | `adapter/ohos/osal/ressched_report.cpp` | `foundation/resourceschedule/resource_schedule_service` | `libressched_client.z.so` (dlopen) | dlopen 动态加载 ReportData/ReportSyncEvent（条件编译 RESOURCE_SCHEDULE_SERVICE_ENABLE） |
| 系统参数 | `adapter/ohos/osal/frame_trace_adapter_impl.cpp` | `base/startup/init` | `parameters.h` | GetBoolParameter/SetParameter 帧 trace 限流控制 |
| c_utils securec | `frameworks/base/log/ace_trace.cpp` | `commonlibrary/c_utils` | `securec.h` | vsnprintf_s 安全字符串格式化 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| PerfMonitor 测试 | `test/unittest/frameworks/base/perfmonitor/perf_monitor_test.cpp` | PerfMonitor、SetSceneId/SetFrameDump、性能操作报告测试 |
| PerfMonitor C API accessor | `test/unittest/capi/accessors/global_scope_ohos_arkui_performance_monitor_accessor_test.cpp` | C API PerfMonitor accessor、ArkTS→Native 桥接测试 |

### 相关 Spec

Trace 功能域：`specs/03-engine-framework/08-dfx-foundation/03-trace/`（功能 ID `03-08-03`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| ACE Trace 核心框架与 FrameTrace 适配 | `specs/03-engine-framework/08-dfx-foundation/03-trace/Feat-01-ace-trace-core-frame-trace-spec.md` | ACE_SCOPED_TRACE、Hitrace、FrameTrace、打点框架 |
| 帧调度报告与 Jank 检测 | `specs/03-engine-framework/08-dfx-foundation/03-trace/Feat-02-frame-report-jank-spec.md` | 帧调度报告、Jank 检测、PerfMonitor |
| 性能检查与阈值监控 | `specs/03-engine-framework/08-dfx-foundation/03-trace/Feat-03-perf-check-threshold-spec.md` | PerfCheck、阈值、超限告警、监控 |
| 设计文档 | `specs/03-engine-framework/08-dfx-foundation/03-trace/design.md` | 整体架构设计、ADR |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Trace 打点不出现 | ACE_SCOPED_TRACE、FrameTrace 打点宏展开条件、HiLog 配置 |
| 帧调度 Jank 检不上报 | PerfMonitor、SetSceneId 场景注册、帧调度统计 |
| 性能阈值告警不触发 | PerfCheck 阈值配置、PipelineContext 阈值检查逻辑 |
| PerfMonitor 数据不完整 | PerfMonitor 性能数据采集点、场景 ID 注册时机 |

## 调试入口

- Trace 打点断点：ACE_SCOPED_TRACE、FrameTrace 宏展开位置
- PerfMonitor 断点：PerfMonitor::SetSceneId、PerfMonitor::SetFrameDump、PerfMonitor::PerfAction
- Jank 检测断点：PipelineContext Jank 检测逻辑、帧调度统计
- PerfCheck 断点：PipelineContext PerfCheck 阈值检查

## 相关主题

- 日志：[docs/kb/architecture/dfx/logging.md](logging.md)
- 内存管理：[docs/kb/architecture/dfx/memory-management.md](memory-management.md)
- Dump 机制：[docs/kb/architecture/dfx/dump-mechanism.md](dump-mechanism.md)