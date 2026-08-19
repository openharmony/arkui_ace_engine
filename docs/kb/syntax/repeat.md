# Repeat Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `Repeat`

## 定位

`Repeat`（FuncID `07-05-03`）是 ArkUI 渲染控制循环语法，覆盖核心（非虚拟）渲染 + 虚拟滚动（`.virtualScroll`）+ 模板化渲染（`.template`）+ 内存优化（`@since26`）。本页同时覆盖原旧 KB 的「RepeatVirtualScroll」主题，统一为一个功能域。

与 `LazyForEach` 的差异：Repeat 用数组 + TS lambda（无 `IDataSource` / `DataChangeListener`）；**key 完全在 TS 侧生成**（`pu_repeat.ts`），C++ 仅消费解析后的 id 串；diff 决策（含 v2 虚拟滚动复用匹配）在 TS 侧，C++ 节点无 diff 智能。虚拟滚动 **v2 为 master 动态路径**（`RepeatVirtualScroll2Node`，RID 缓存），**v1（`RepeatVirtualScrollNode`，key+ttype）已废弃**、源码保留不演进。具体行为、默认值、错误码以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 非虚拟节点 | `frameworks/core/components_ng/syntax/repeat_node.cpp`、`.h` | `RepeatNode`：`CreateTempItems` / `FinishRepeatRender` / `MoveChild` / `MoveData` / `SetOnMove` / `InitDragManager` / 动画门控 |
| Model 工厂 | `frameworks/core/components_ng/syntax/repeat_model_ng.cpp`、`repeat_model.h` | `StartRender` / `FinishRender` / `MoveChild` / `CreateNewChildStart/Finish` / `OnMove` / `IsAllowAnimation` |
| 虚拟滚动 v2（master） | `frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_node.cpp`、`.h`、`repeat_virtual_scroll_2_caches.cpp`、`.h` | v2 RID 缓存（`cacheItem4Rid_` / `l1Rid4Index_`）、active range / recycle / sync-load / FreezeSpareNode（API≥18）/ 内存优化 |
| 虚拟滚动 v2 Model | `frameworks/core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.cpp` | `SetCreateByTemplate` / 模板门控 |
| 虚拟滚动 v1（已废弃） | `frameworks/core/components_ng/syntax/repeat_virtual_scroll_node.*`、`repeat_virtual_scroll_caches.*` | v1（原 API≤15 兼容）**已废弃**，代码保留不演进 |
| 共享基类 | `frameworks/core/components_ng/syntax/for_each_base_node.h` | `ForEachBaseNode`：`FireOnMove`（from!=to）/ drag / `MoveData` 纯虚（详见 07-05-01） |
| JS 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_repeat.cpp`（`JSRepeat`）、`js_repeat_virtual_scroll_2.cpp` | 绑定 startRender / finishRender / moveChild / createNewChild / onMove / item-drag / isAllowAnimation |
| TS API / diff 驱动 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_repeat.ts`、`pu_repeat_impl.ts`、`pu_repeat_virtual_scroll_2_impl.ts` | TS 侧 key 生成（默认 `funcWithIndex`）、reRender 三 case diff、`RepeatNative` 调度、v2 复用匹配（`canUpdateTryMatch`） |
| 全局工具 / metadata | `frameworks/core/components_ng/syntax/lazy_for_each_utils.cpp`、`.h`、`adapter/ohos/entrance/ui_content_impl.cpp` | `enableRepeatAnimation` 全局标志（默认 false） |
| 父容器 | List / Grid Pattern | drag 驱动 onMove、animation gating 判定 parent==List |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/repeat.d.ts` | `Repeat<T>(arr)` + `.each` / `.key`（`@since12`）、`.virtualScroll`（`@since12`）、`.template` / `.templateId`（`@since12`）、内存优化（`@since26`） |
| Static SDK | `<OH_ROOT>/interface/sdk-js/api/arkui/component/repeat.static.d.ets` | `@since23` 整套 |
| 数据类型 | 同上 d.ts / `.d.ets` | `RepeatItem<T>`、`RepeatAttribute<T>`、`VirtualScrollOptions`、`TemplateOptions`、`RepeatMemOptStrategy`（`@since26`，仅 v2） |

API 检索建议：在 SDK 中搜索 `Repeat`、`RepeatAttribute`、`virtualScroll`、`template`、`VirtualScrollOptions`、`memoryOptimizationStrategy`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/syntax/repeat_test_ng.cpp`、`repeat_model_test_ng.cpp` | RepeatNode diff / onMove / 动画门控、Model 门面 |
| UT（v2） | `test/unittest/core/syntax/repeat_virtual_2_test_ng.cpp`、`repeat_virtual_2_syntax_test_ng_advanced.cpp`、`repeat_virtual_2_model_test_ng.cpp`、`repeat_virtual_2_caches_test_ng.cpp` | v2 RID 缓存 / active range / recycle |
| UT（v1） | `test/unittest/core/syntax/repeat_virtual_test_ng.cpp`、`repeat_virtual_test_ng_2.cpp`、`repeat_virtual_model_test_ng.cpp`、`repeat_virtual_scroll_syntax_test_ng_advanced.cpp` | v1（已废弃）兼容回归 |
| TS 单测 | state-mgmt 单测（`pu_repeat_impl.ts`） | key 生成 / diff 三 case / 复用抑制 |
| XTS | `test/xts` | dynamic/static 双范式端到端 |
| Spec 功能域 | `specs/07-frontend/05-render-control/03-repeat/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `07-05-03` 功能域注册入口 |

### 相关 Spec

Repeat 功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | Repeat 核心语法与非虚拟渲染（基线） | `Feat-01-repeat-core-syntax-and-non-virtual-rendering-spec.md` |
| Feat-02 | Repeat 虚拟滚动（v2；v1 已废弃） | `Feat-02-repeat-virtual-scroll-v1-v2-spec.md` |
| Feat-03 | Repeat 模板化渲染与复用 | `Feat-03-repeat-template-rendering-and-reuse-spec.md` |
| Feat-04 | Repeat 内存优化策略 | `Feat-04-repeat-memory-optimization-strategy-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 重复用户 key 全量重渲染 | `pu_repeat_impl.ts`（`key2Item.size<arr.length` → 回退默认 + 全量重渲染，静默） |
| `.each()` 缺省报错时机 | 运行时抛 `BusinessError(103802)`（非编译期） |
| 虚拟滚动路径假设 | master 动态路径**始终 v2**（`pu_repeat.ts`）；v1 已废弃，勿按运行时 API 版本选 v1/v2 |
| 模板内 `@ReusableV2` 不生效 | 模板子节点（ttype≠''）`SetAllowReusableV2Descendant(false)`；each 子节点（ttype=''）仍允许 |
| 动画复用抑制不生效 | `repeat_node.cpp` `IsAllowAnimation`（默认 false metadata + 仅 List 父，Grid 不启用） |
| onMove 拖拽排序不可用 | `repeat_node.cpp` `InitDragManager`（仅 List/Grid 直接父） |
| 内存回收行为与 LazyForEach 不同 | Repeat v2 无 `maxCacheCount` 硬下限（仅 LazyForEach 有），回收量由用户 `TemplateOptions.cachedCount` 预算约束 |

## 调试入口

- 非虚拟 diff 链路：TS `reRender` 三 case（retained / reused-slot / new）→ `RepeatNative.moveChild` / `createNewChild` → `RepeatNode` swap / attach。
- key 链路：`pu_repeat.ts` `__RepeatDefaultKeyGen.funcWithIndex` → `RepeatNative.createNewChildStart(key)` → `js_repeat.cpp` → `repeat_model_ng.cpp`。
- 虚拟滚动链路：`.virtualScroll` → master 始终 v2 → `RepeatVirtualScroll2Node` + TS `onGetRid4Index` / `onRecycleItems` / `canUpdateTryMatch`。
- 内存优化链路（v2，`@since26`）：窗口 / 内存回调 + 1s `PostMemOptTask` poll + 2s 防抖（hide 同步清 / show 延迟恢复 / LOW·CRITICAL 异步清）。

## 相关主题

- [LazyForEach：`docs/kb/syntax/lazy-for-each.md`](lazy-for-each.md)
- [渲染控制语法（ForEach / if-else / 共享基类）：`docs/kb/syntax/render-control.md`](render-control.md)
- [组件复用框架（`SetAllowReusableV2Descendant` / `DisableRecycle`）：`docs/kb/architecture/component-reuse-framework.md`](../architecture/component-reuse-framework.md)