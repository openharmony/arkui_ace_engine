# DFX Memory Management Context

> 文档版本：v1.1
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `DFXMemoryManagement`

## 定位

DFX Memory Management 是 ArkUI 引擎的内存管理基础设施，涵盖引用计数智能指针（RefPtr/WeakPtr/AceType/Referenced）、内存分配监控（MemoryMonitor）、NG 内存回收管线（MemoryManager recycle）和系统内存压力监听与全局 GC 触发。它不是对外公共 API，而是引擎内部 DFX 能力，是所有组件和模块的内存安全基础。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体引用计数语义、回收策略和 GC 触发条件应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AceType 基类 | `frameworks/base/memory/ace_type.h` | 引用计数基类；MakeRefPtr/DynamicCast/WeakClaim、DECLARE_ACE_TYPE、typeId 系统 |
| RefPtr 智能指针 | `frameworks/base/memory/referenced.h` | RefPtr/WeakPtr 定义；引用计数增减、线程安全、生命周期管理 |
| Referenced 基类 | `frameworks/base/memory/referenced.h` | Referenced 基类；RefPtr/WeakPtr 指向的目标类型必须继承 Referenced |
| DynamicCast | `frameworks/base/memory/ace_type.h` | DynamicCast<T>(RefPtr<AceType>) 安全向下转型；类型检查、线程安全的引用转换 |
| MemoryMonitor | `frameworks/base/memory/memory_monitor.h` | 内存分配监控接口定义；MemoryMonitor、AllocInfo、DumpAllocInfo |
| MemoryManager (NG) | `frameworks/core/components_ng/manager/memory/memory_manager.h` | NG 内存回收管线；节点回收、PipelineContext 内存管理 |
| 内存压力监听 | `frameworks/core/components_ng/manager/memory/memory_manager.cpp` | 系统内存压力回调、全局 GC 触发逻辑 |
| 全局 GC | `frameworks/core/pipeline_ng/pipeline_context.cpp` | PipelineContext::OnMemoryPressure；系统内存压力事件 → 全局 GC |

### API 入口

DFX Memory Management 是引擎内部能力，没有独立 SDK API。AceType/RefPtr/WeakPtr 是所有组件 Pattern/Model 的基类，但被应用侧间接使用。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| ui_lite 基础类型 | `frameworks/base/memory/ace_type.h`, `referenced.h`, `memory_monitor.h` | `foundation/arkui/ui_lite` (推测) | `ui/base/ace_type.h`, `ui/base/referenced.h`, `ui/base/memory_monitor.h` | thin wrapper 重定向到 ui_lite 头文件 |
| Bionic mallopt | `frameworks/base/memory/memory_monitor.cpp` | OHOS Bionic libc | `<malloc.h>` → `mallopt(M_PURGE, 0)` | malloc cache purge（仅 `__BIONIC__` 平台） |
| 系统内存压力回调 | `adapter/ohos/entrance/ui_content_impl.cpp` | 系统内核/资源调度 | `UIContentImpl::NotifyMemoryLevel(level)` | 系统回调入口，OS 调入 ace_engine 通知内存压力级别 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| AceType/RefPtr/WeakPtr 综合 | `test/unittest/core/base/observer_test_ng.cpp` | AceType/RefPtr/WeakPtr/DynamicCast/MakeRefPtr 综合验证 |
| UObject 测试 | `test/unittest/base/uobject_test.cpp` | UObject、AceType/Referenced 基础对象验证 |
| Container 测试 | `test/unittest/base/container_test.cpp` | SafeList/SafeMap 并发 AceType-managed 对象并发访问测试 |
| UiNodeGc 测试 | `test/unittest/core/base/ui_node_gc_test_ng.cpp` | UiNodeGc、节点垃圾回收生命周期测试 |
| NodeRenderStatusMonitor | `test/unittest/core/base/node_render_status_monitor_test_ng.cpp` | NodeRenderStatusMonitor、节点渲染状态监控测试 |

### 相关 Spec

内存管理功能域：`specs/03-engine-framework/08-dfx-foundation/02-memory-management/`（功能 ID `03-08-02`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| RefPtr/WeakPtr/AceType 引用计数智能指针 | `specs/03-engine-framework/08-dfx-foundation/02-memory-management/Feat-01-refptr-weakptr-ace-type-spec.md` | RefPtr/WeakPtr/AceType/Referenced/DynamicCast 引用计数模型 |
| MemoryMonitor 调试分配监控 | `specs/03-engine-framework/08-dfx-foundation/02-memory-management/Feat-02-memory-monitor-spec.md` | MemoryMonitor、分配统计和请求级 dump |
| NG MemoryManager 内存回收管线 | `specs/03-engine-framework/08-dfx-foundation/02-memory-management/Feat-03-ng-memory-manager-recycle-spec.md` | NG MemoryManager、节点回收、管线、内存压力触发 |
| 系统内存压力监听与全局 GC | `specs/03-engine-framework/08-dfx-foundation/02-memory-management/Feat-04-memory-pressure-global-gc-spec.md` | 内存压力监听、全局 GC 触发、应用生命周期 |
| 设计文档 | `specs/03-engine-framework/08-dfx-foundation/02-memory-management/design.md` | 整体架构设计、ADR |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| RefPtr 循环引用对象不释放 | 检查 AceType 基类的 DeclareReferenced 调用链、父子持有子 RefPtr、子节点 RefPtr 的增减 |
| WeakPtr 悬空引用对象已释放 | Referenced::WeakClaim、WeakPtr::Reset、弱引用生命周期 |
| DynamicCast 转型失败 | DynamicCast 类型检查、线程安全、转型失败时的 nullptr |
| 内存泄漏 | MemoryMonitor DumpAllocInfo、节点 DumpInfo、检查未回收的 RefPtr |
| 内存压力 GC 不触发 | MemoryManager::OnMemoryPressure、PipelineContext 全局 GC 调用链 |
| UiNodeGc 节点回收不及时 | UiNodeGc、isTooLate、ReleaseInner、GC 回收时机 |

## 调试入口

- RefPtr/WeakPtr 断点：AceType::MakeRefPtr、RefPtr 构造/析构、Referenced::RefCount/StrongRefCount
- DynamicCast 断点：DynamicCast<T>(RefPtr<AceType>) 类型检查、转型逻辑
- 内存回收断点：MemoryManager::OnMemoryPressure、UiNodeGc::ReleaseInner、PipelineContext::OnMemoryPressure
- 内存监控断点：MemoryMonitor::DumpAllocInfo
- 全局 GC 断点：PipelineContext 内存压力回调 → 全局 GC 调用链

## 相关主题

- 日志：`docs/kb/architecture/dfx/logging.md`
- Trace 打点：`docs/kb/architecture/dfx/trace.md`
- Dump 机制：`docs/kb/architecture/dfx/dump-mechanism.md`