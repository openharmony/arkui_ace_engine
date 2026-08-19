# UIContext 实例 ID 泄漏 Issue Context

> 文档版本：v1.2
> 更新时间：2026-08-04
> 来源：`docs/context_registry.json` 主题 `UIContextInstanceIdLeak`
> 关联功能域：04-12-01

## 问题概述

UIContext 动态前端（jsUIContext.js）曾使用手动 `syncInstanceId`/`restoreInstanceId` 配对。修复前，提前返回、异常抛出或未配对的 restore 会使线程当前实例 ID 切换到错误值，导致后续操作作用在错误的 UI 实例上。JS 前端问题已由变更 `c13dbf04e84aa04b7803fa043b323df5aaacb0d7` 通过 `withInstanceId` 的 `try/finally` 包装修复；ANI 和 C API 路径仍需分别核对调用方的配对保护。

修复前的典型表现：
- 多实例场景下调用 UIContext 方法后，后续操作作用在错误的实例上
- 参数校验失败后，后续 UIContext 方法调用全部指向错误实例
- UIContext 方法抛出异常后，实例 ID 栈永久错位，整个线程实例管理失效


## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| capability | fix_location | common_ani_modifier | frameworks/core/interfaces/native/ani/common_ani_modifier.cpp | verified |
| capability | fix_location | system_ops_accessor | frameworks/core/interfaces/native/implementation/system_ops_accessor.cpp | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 提前返回路径漏调 restoreInstanceId | 方法中有条件分支提前 return | `getFrameNodeById` 节点不存在时 `return null`，跳过 restore；`openBindSheet` 参数校验失败时 `return Promise.reject`，跳过 restore |
| 异常路径漏调 restoreInstanceId | 业务逻辑抛出 JS 异常 | `createDragAction` 旧代码用手动 try/catch 补救，但其他方法（如 `animateTo`、`showAlertDialog`）无异常保护 |
| 未 sync 就 restore（栈错位） | 参数校验失败时在 sync 之前调 restore | `ComponentSnapshot.createFromComponent` 校验 content 为 null 时直接调用 `restoreInstanceId()`，但此时尚未调用 `syncInstanceId`，导致实例 ID 栈弹出了上一个保存的值 |

## 排查路径

### 快速判断

1. 确认是否为多实例场景（多窗口、子窗口、半模态弹窗等）
2. 检查是否在 UIContext 方法调用后出现"操作错实例"的表现（如弹窗出现在错误窗口）
3. 检查是否在 UIContext 方法参数校验失败后出现后续操作异常
4. 在 `jsUIContext.js` 中搜索 `__JSScopeUtil__.syncInstanceId` 和 `__JSScopeUtil__.restoreInstanceId` 是否严格配对

### 详细排查

#### 提前返回路径漏调 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `jsUIContext.js` 中搜索所有 `syncInstanceId` 调用 | 每个调用都应有对应的 `restoreInstanceId` | 检查方法内所有 return 路径是否都经过 restore |
| 2 | 检查方法内是否有条件分支提前 return | 提前 return 前必须有 `restoreInstanceId` | 确认该 return 路径是否漏调 |
| 3 | 检查是否已使用 `withInstanceId` 包装 | 所有 UIContext 方法应使用 `withInstanceId` | 如果仍使用手动 sync/restore，需替换 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/engine/jsUIContext.js`：`withInstanceId` 工具函数定义（`try/finally` 保证 restore）
- `frameworks/bridge/declarative_frontend/jsview/js_scope_util.cpp`：`SyncInstanceId`/`RestoreInstanceId` 的 C++ 实现
- `frameworks/bridge/declarative_frontend/jsview/js_scope_util.cpp`：`restoreInstanceIds_` 为 `static thread_local std::vector<int32_t>`，非类成员，全线程共享同一栈
- `frameworks/bridge/declarative_frontend/jsview/js_scope_util.cpp`：`SyncInstanceId` 将当前实例 ID 压入 `restoreInstanceIds_` 栈
- `frameworks/bridge/declarative_frontend/jsview/js_scope_util.cpp`：`RestoreInstanceId` 空栈时将实例 ID 设为 `INSTANCE_ID_UNDEFINED`（非宏路径）或调用 `CURRENT_ID_POP(0, INSTANCE_ID_UNDEFINED)`（宏路径）
- `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp,179-209`：ANI 接口有独立的 `restoreInstanceIds_` 和 `SyncInstanceId`/`RestoreInstanceId`，模式相同
- `frameworks/core/interfaces/native/implementation/system_ops_accessor.cpp,49-78`：C API 接口有独立的 `restoreInstanceIds_` 和 `SyncInstanceIdImpl`/`RestoreInstanceIdImpl`，模式相同

#### 栈错位 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 搜索 `restoreInstanceId` 调用前是否有对应的 `syncInstanceId` | restore 必须在 sync 之后 | 找到未 sync 就 restore 的位置 |
| 2 | 检查 `restoreInstanceIds_` 栈是否可能为空 | 空栈时 `RestoreInstanceId` 会将实例 ID 设为 `INSTANCE_ID_UNDEFINED` | 确认是否会导致实例 ID 失效 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/jsview/js_scope_util.cpp`：`restoreInstanceIds_` 为 `static thread_local` 变量，非类成员
- `frameworks/bridge/declarative_frontend/jsview/js_scope_util.cpp`：`RestoreInstanceId` 实现中，空栈时行为取决于 `ENABLE_CONTAINER_SCOPE_TRACKING` 宏：
  - 非宏路径：`ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED)`，实例 ID 被设为无效值
  - 宏路径：`CURRENT_ID_POP(0, INSTANCE_ID_UNDEFINED, CurrentIdSourceType::JS_FRONTEND)`，同样设为无效值但记录追踪信息
- `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp`：ANI 接口的 `RestoreInstanceId`，空栈时行为类似（非宏路径用 `-1`，与 JS 前端的 `INSTANCE_ID_UNDEFINED` 值相同）
- `frameworks/core/interfaces/native/implementation/system_ops_accessor.cpp`：C API 接口的 `RestoreInstanceIdImpl`，模式相同

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 提前返回路径漏调 | 引入 `withInstanceId` 工具函数，用 `try/finally` 保证 `restoreInstanceId` 必定执行 | `jsUIContext.js` 所有 UIContext 方法替换为 `withInstanceId` 包装 | c13dbf04e84aa04b7803fa043b323df5aaacb0d7 (fixed) | commit diff: 所有手动 sync/restore 替换为 withInstanceId 闭包 |
| 异常路径漏调 | 同上，`try/finally` 天然覆盖异常路径 | 同上 | c13dbf04e84aa04b7803fa043b323df5aaacb0d7 (fixed) | commit diff: `createDragAction` 的手动 try/catch 被移除，由 withInstanceId 统一处理 |
| 栈错位 | 删除未经 sync 就执行的 restore；需要切换实例的业务调用统一放入 `withInstanceId` | `createFromComponent` 的参数校验仍在闭包外，但校验失败分支不再调用 `restoreInstanceId` | c13dbf04e84aa04b7803fa043b323df5aaacb0d7 (fixed) | commit diff: 删除参数校验失败分支中未配对的 `restoreInstanceId()`，并用 `withInstanceId` 包装后续业务调用 |

**注意：同类问题也存在于 ANI 接口和 C API 接口**，但当前修复仅覆盖了 JS 前端（`jsUIContext.js`）：
- `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp`：ANI 接口的 `SyncInstanceId`/`RestoreInstanceId` 仍为手动调用模式，若调用方存在提前返回或异常路径，同样可能泄漏
- `frameworks/core/interfaces/native/implementation/system_ops_accessor.cpp`：C API 接口的 `SyncInstanceIdImpl`/`RestoreInstanceIdImpl` 同理

### ANI 路径 DragController 特例

ANI 路径中 DragController 的 `createDragAction` 有两个特有风险点：

1. **UIContextImpl.ets 手动 Sync/Restore 无 try/finally 保护**：`DragControllerImpl.createDragAction()`（`UIContextImpl.ets`）使用 `_Common_Sync_InstanceId`/`_Common_Restore_InstanceId`，中间代码抛异常时 `Restore_InstanceId` 不会执行，导致实例 ID 栈永久错位。与 JS 前端修复前的问题完全一致。

2. **ANI 路径 instanceId 重捕获不一致**：`ANIHandleDragAction()` 在 createDragAction 时设置 `dragAsyncContext->instanceId = Container::CurrentIdSafely()`，但 `ANIHandleDragActionStartDrag()` 在 startDrag 时又用 `Container::CurrentIdSafely()` 重写 instanceId。两个函数均实现于 `frameworks/core/interfaces/native/ani/drag_controller_ani_modifier.cpp`。如果 startDrag 在不同上下文被调用，新值可能覆盖原始值，导致拖拽操作执行在错误的 UI 实例上。NAPI 路径不存在此重捕获行为。

关键代码定位：
- `frameworks/core/interfaces/native/ani/drag_controller_ani_modifier.cpp`：`ANIHandleDragAction`/`ANIHandleDragActionStartDrag` 中的 instanceId 捕获与重捕获
- `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/dragController/drag_controller_module.cpp`：ANI 参数解析与 DragController Modifier 调用入口
- `frameworks/core/components_ng/manager/drag_drop/drag_drop_func_wrapper.cpp`：三条路径拖拽核心功能汇聚层

核心修复代码（`withInstanceId` 函数定义）：
```javascript
function withInstanceId(instanceId, callback) {
    __JSScopeUtil__.syncInstanceId(instanceId);
    try {
        return callback();
    } finally {
        __JSScopeUtil__.restoreInstanceId();
    }
}
```

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 引入 withInstanceId 工具函数，替换所有手动 sync/restore | 提前返回路径漏调 + 异常路径漏调 + 栈错位 | fixed | commit c13dbf04 diff: 全文替换 syncInstanceId/restoreInstanceId 为 withInstanceId 闭包 | verified |

## 预防措施

- 新增 UIContext 方法必须使用 `withInstanceId` 包装，禁止手动调用 `syncInstanceId`/`restoreInstanceId`
- 代码审查时重点检查 `jsUIContext.js` 中是否残留手动 sync/restore 模式
- ANI 接口（`common_ani_modifier.cpp`）和 C API 接口（`system_ops_accessor.cpp`）中的 `SyncInstanceId`/`RestoreInstanceId` 调用同样需要配对保护，建议引入类似 `withInstanceId` 的 RAII 包装
- 多实例场景下建议增加实例 ID 栈一致性校验的 DFX 打点
- `restoreInstanceIds_` 为 `static thread_local` 变量，同一线程内所有 UIContext 实例共享同一栈，任何未配对的 sync/restore 都会影响后续所有操作

## 相关主题

- `docs/kb/capabilities/ui-context.md`：UIContext 代码型 KB
- `docs/kb/architecture/multi-instance-management.md`：多实例管理架构 KB