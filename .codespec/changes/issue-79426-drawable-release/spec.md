# 特性规格

> 固化用户可见行为和验收标准。当前状态为 Approved，可作为 design 输入。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | DrawableDescriptor release/isReleased 绑定状态能力 |
| 特性编号 | Func-04-01-03-Feat-01-delta |
| 所属 Epic | 无，存量能力增量 |
| 优先级 | P1 |
| 目标版本 | API 26.0.0 |
| SIG 归属 | ArkUI |
| 状态 | Approved |
| 复杂度 | 标准 |

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | Dynamic `DrawableDescriptor.release()` 运行时行为 | SDK 声明已存在，本次补齐动态运行时绑定解除行为。 |
| ADDED | Dynamic `DrawableDescriptor.isReleased()` 运行时行为 | SDK 声明已存在，本次补齐动态运行时释放状态查询。 |
| MODIFIED | Dynamic release 后访问语义 | 指定 API release 后抛出或 reject `BusinessError 111002`；指定控制/刷新类 API release 后无操作返回。 |
| UNCHANGED | Static DrawableDescriptor release 行为 | Static 不动，保持既有 `undefined` / `imageWidth=-1,imageHeight=-1` 降级返回。 |
| UNCHANGED | C API 生命周期 | 不新增 C API，不修改 `OH_ArkUI_DrawableDescriptor_Dispose` ABI 或语义。 |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | `.codespec/changes/drawable-descriptor-release-state/proposal.md` | Approved / Baselined |

需求基线、不涉及项、受影响子系统与仓库详见 proposal.md。本文档只固化 API 行为和验收标准。

## 用户故事

### US-1: Dynamic DrawableDescriptor 显式释放

**作为** ArkTS Dynamic DrawableDescriptor 调用者，  
**我想要** 主动调用 `release()` 解除前端对象与后端对象的绑定，  
**以便** 提前释放 native 资源并避免继续访问已解绑对象。

**验收标准（AC, Acceptance Criteria）：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-1.1 | WHEN Dynamic `DrawableDescriptor` 或任一子类对象首次调用 `release()` THEN 对象进入 released 状态，后续 `isReleased()` 返回 `true`。 | 正常 |
| AC-1.2 | WHEN Dynamic 同一对象重复调用 `release()` THEN 调用直接返回且不崩溃，`isReleased()` 保持 `true`。 | 边界 |
| AC-1.3 | WHEN Dynamic 对象未调用 `release()` THEN `isReleased()` 返回 `false`。 | 正常 |
| AC-1.4 | WHEN Dynamic 已释放对象调用 `getPixelMap()`、`getForeground()`、`getBackground()`、`getMask()`、`loadSync()` 或新发起 `load()` THEN 抛出或 reject `BusinessError 111002`。 | 异常 |
| AC-1.5 | WHEN Dynamic 已释放对象调用 `invalidate()`、`setHdrComposition()`、`getAnimationController()` 或 `setBlendMode()` THEN 调用无操作返回且不崩溃。 | 边界 |
| AC-1.6 | WHEN Dynamic 对象在未释放状态下使用既有加载、分层、动画、Picture/HDR 能力 THEN 既有行为不变。 | 兼容 |

### US-2: 异步 load 与释放状态

**作为** ArkTS Dynamic DrawableDescriptor 调用者，  
**我想要** 在 `load()` 已发起后调用 `release()` 仍不会破坏异步结果，  
**以便** 避免异步加载与显式释放之间产生崩溃或未定义行为。

**验收标准（AC, Acceptance Criteria）：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-2.1 | WHEN Dynamic 对象在未释放状态下发起 `load()`，随后调用 `release()` THEN 已发起的 Promise 继续安全完成，完成过程不访问已释放内存，也不重新绑定已 release 的前端对象。 | 边界 |
| AC-2.2 | WHEN Dynamic 对象已经处于 released 状态后再调用 `load()` THEN Promise reject `BusinessError 111002`。 | 异常 |

### US-3: Static 与 C API 兼容边界

**作为** Static ArkTS 或 NDK 调用者，  
**我想要** 本次变更不改变 Static 既有 release 行为，也不改变 C API 生命周期接口，  
**以便** 保持现有调用方兼容。

**验收标准（AC, Acceptance Criteria）：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-3.1 | WHEN Static 已释放对象调用 `getPixelMap()` THEN 返回 `undefined`，不改为 `BusinessError 111002`。 | 兼容 |
| AC-3.2 | WHEN Static 已释放对象调用 `loadSync()` 或 `load()` THEN 返回或 resolve `imageWidth=-1,imageHeight=-1`，不改为 `BusinessError 111002`。 | 兼容 |
| AC-3.3 | WHEN 通过 NAPI/ANI bridge 从已释放 Dynamic 或 Static DrawableDescriptor 提取 native descriptor THEN 返回参数错误，不产生新的有效 native descriptor。 | 异常 |
| AC-3.4 | WHEN 已经提取出的 C 侧 `ArkUI_DrawableDescriptor*` 句柄存在 THEN 后续前端对象 `release()` 不主动使该 C 侧句柄失效；C 侧句柄仍按 `OH_ArkUI_DrawableDescriptor_Dispose` 管理生命周期。 | 兼容 |
| AC-3.5 | WHEN 调用现有 `OH_ArkUI_DrawableDescriptor_Dispose` THEN 函数签名、结构布局、错误码和生命周期语义保持不变。 | 兼容 |

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1.1 | R-1, R-2 | TASK-001, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-1.2 | R-3 | TASK-001, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-1.3 | R-2 | TASK-001, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-1.4 | R-4 | TASK-001, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-1.5 | R-5 | TASK-001, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-1.6 | R-9 | TASK-001, TASK-003 | 既有用例回归 / previewer 冒烟 | `evidence/checks/check-implementation.md` 构建和边界 diff PASS；Previewer GUI 待人工补验 |
| AC-2.1 | R-6 | TASK-002, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-2.2 | R-4 | TASK-001, TASK-003 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-3.1 | R-7 | TASK-003 | Static 行为回归 / 代码审查 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-3.2 | R-7 | TASK-003 | Static 行为回归 / 代码审查 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| AC-3.3 | R-8 | TASK-001, TASK-003 | bridge 行为验证 / 代码审查 | `evidence/reviews/spec-compliance.md` PASS |
| AC-3.4 | R-10 | TASK-001, TASK-003 | C API 兼容性审查 | `evidence/reviews/spec-compliance.md` PASS |
| AC-3.5 | R-11 | TASK-003 | C API ABI/头文件审查 | `evidence/reviews/spec-compliance.md` PASS |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | Dynamic DrawableDescriptor 或子类首次调用 `release()`。 | 对象进入 released 状态；释放后不再允许访问其后端绑定对象。 | 覆盖 DrawableDescriptor、PixelMapDrawableDescriptor、LayeredDrawableDescriptor、AnimatedDrawableDescriptor、PictureDrawableDescriptor。 | AC-1.1 |
| R-2 | 行为 | Dynamic 对象调用 `isReleased()`。 | release 前返回 `false`；release 后返回 `true`。 | `isReleased()` 本身可在 released 状态下调用。 | AC-1.1, AC-1.3 |
| R-3 | 边界 | Dynamic 已 released 对象重复调用 `release()`。 | 直接返回，不崩溃，不改变已释放状态。 | 重复次数不产生额外副作用。 | AC-1.2 |
| R-4 | 异常 | Dynamic 已 released 对象调用 `getPixelMap/getForeground/getBackground/getMask/loadSync/load`。 | 同步 API 抛 `BusinessError 111002`；Promise API reject `BusinessError 111002`。 | 已发起的 `load()` 按 R-6 处理；released 后新发起的 `load()` 按本规则处理。 | AC-1.4, AC-2.2 |
| R-5 | 边界 | Dynamic 已 released 对象调用 `invalidate/setHdrComposition/getAnimationController/setBlendMode`。 | 无操作返回且不崩溃。 | 不重新创建或重新绑定后端对象。 | AC-1.5 |
| R-6 | 边界 | Dynamic 对象未 release 时已发起 `load()`，随后调用 `release()`。 | 已发起 Promise 继续安全完成；完成结果不重新绑定 released 前端对象。 | 不允许访问已释放内存。 | AC-2.1 |
| R-7 | 兼容 | Static 已 released 对象调用 `getPixelMap/loadSync/load`。 | 保持现有行为：`getPixelMap()` 返回 `undefined`；`loadSync/load` 返回或 resolve `imageWidth=-1,imageHeight=-1`。 | 本次不改变 Static 错误码语义。 | AC-3.1, AC-3.2 |
| R-8 | 异常 | 从已 released 前端对象提取 native descriptor。 | 返回参数错误，不产生新的有效 native descriptor。 | 适用于 NAPI/ANI bridge。 | AC-3.3 |
| R-9 | 兼容 | Dynamic 对象未调用 `release()` 并使用既有功能。 | 加载、分层、动画、Picture/HDR 等既有行为保持不变。 | 本次不扩展非 release 行为。 | AC-1.6 |
| R-10 | 兼容 | 前端对象 release 前已提取 C 侧 descriptor 句柄。 | 后续前端 release 不主动使既有 C 侧句柄失效。 | C 侧句柄继续由 C API 生命周期管理。 | AC-3.4 |
| R-11 | 兼容 | 使用现有 C API Dispose。 | `OH_ArkUI_DrawableDescriptor_Dispose` 签名、结构布局、错误码和生命周期语义不变。 | 不新增 C API release/isReleased。 | AC-3.5 |

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | AC-1.1 到 AC-1.3 | previewer 可执行用例 / API 行为验证 | Dynamic release 首次调用、重复调用、isReleased 状态切换。 |
| VM-2 | AC-1.4、AC-2.2 | previewer 可执行用例 / API 行为验证 | released 后指定 API 抛出或 reject `BusinessError 111002`。 |
| VM-3 | AC-1.5 | previewer 可执行用例 / API 行为验证 | released 后 `invalidate/setHdrComposition/getAnimationController/setBlendMode` 无操作返回。 |
| VM-4 | AC-2.1 | previewer 可执行用例 / API 行为验证 | 已发起 `load()` 后 release 仍安全完成，不重新绑定 released 前端对象。 |
| VM-5 | AC-3.1 到 AC-3.2 | Static 行为回归 / 代码审查 | Static 不动，保持 `undefined/-1` 降级行为。 |
| VM-6 | AC-3.3 到 AC-3.5 | bridge/C API 兼容性审查 | released 对象不能再提取新 native descriptor；C API Dispose ABI 和语义不变。 |

## API 变更分析

### 新增 API

| API 名称 | 开放范围 | 入参概要 | 返回值 | 错误码范围 | 功能描述 | 关联 AC |
|----------|----------|----------|--------|------------|----------|---------|
| `DrawableDescriptor.release()` | System | 无 | `void` | N/A | 解除 Dynamic 前端对象与后端对象的绑定；重复调用无崩溃。SDK 声明已存在，本次补齐运行时行为。 | AC-1.1, AC-1.2 |
| `DrawableDescriptor.isReleased()` | System | 无 | `boolean` | N/A | 查询 Dynamic 前端对象是否已解除后端绑定。SDK 声明已存在，本次补齐运行时行为。 | AC-1.1, AC-1.3 |

### 变更/废弃 API

| API 名称 | 变更类型 | 影响场景 | 迁移指引 | 关联 AC |
|----------|----------|----------|----------|---------|
| `DrawableDescriptor.getPixelMap()` | 行为补齐 | Dynamic release 后调用。 | 调用方可先用 `isReleased()` 判断；release 后调用将抛 `111002`。 | AC-1.4 |
| `LayeredDrawableDescriptor.getForeground/getBackground/getMask()` | 行为补齐 | Dynamic release 后调用。 | 调用方可先用 `isReleased()` 判断；release 后调用将抛 `111002`。 | AC-1.4 |
| `DrawableDescriptor.loadSync/load()` | 行为补齐 | Dynamic release 后新调用；已发起 load 后 release。 | release 后新调用失败；已发起 load 继续安全完成。 | AC-1.4, AC-2.1, AC-2.2 |
| `invalidate/setHdrComposition/getAnimationController/setBlendMode` | 行为补齐 | Dynamic release 后调用。 | release 后调用无操作返回。 | AC-1.5 |
| Static `DrawableDescriptor.release/isReleased` 相关行为 | 不变 | Static release 后访问。 | 无迁移；保持既有 `undefined/-1` 行为。 | AC-3.1, AC-3.2 |
| C API `OH_ArkUI_DrawableDescriptor_Dispose` | 不变 | C 侧 descriptor 生命周期。 | 无迁移；继续由调用方显式 Dispose。 | AC-3.5 |

## 接口规格

### 接口定义

**DrawableDescriptor.release**

| 属性 | 值 |
|------|-----|
| 函数签名 | `release(): void` |
| 返回值 | `void` — 无返回值 |
| 开放范围 | System |
| 错误码 | N/A |
| 关联 AC | AC-1.1, AC-1.2 |

**参数约束**

| 参数 | 类型 | 必填 | 默认值 | 约束条件 |
|------|------|------|--------|---------|
| N/A | N/A | N/A | N/A | 无入参。 |

**行为场景**

| # | 触发条件 | 预期行为 | 关联 AC |
|---|----------|----------|---------|
| 1 | 对未释放 Dynamic 对象调用 `release()`。 | 对象进入 released 状态。 | AC-1.1 |
| 2 | 对已释放 Dynamic 对象重复调用 `release()`。 | 直接返回，不崩溃。 | AC-1.2 |

**DrawableDescriptor.isReleased**

| 属性 | 值 |
|------|-----|
| 函数签名 | `isReleased(): boolean` |
| 返回值 | `boolean` — 是否已释放 |
| 开放范围 | System |
| 错误码 | N/A |
| 关联 AC | AC-1.1, AC-1.3 |

**参数约束**

| 参数 | 类型 | 必填 | 默认值 | 约束条件 |
|------|------|------|--------|---------|
| N/A | N/A | N/A | N/A | 无入参。 |

**行为场景**

| # | 触发条件 | 预期行为 | 关联 AC |
|---|----------|----------|---------|
| 1 | Dynamic 对象未调用 `release()`。 | 返回 `false`。 | AC-1.3 |
| 2 | Dynamic 对象已调用 `release()`。 | 返回 `true`。 | AC-1.1 |

## 兼容性声明

- **已有 API 行为变更:** 是。仅补齐 Dynamic release 后访问语义；未调用 `release()` 的既有路径保持不变。
- **配置文件格式变更:** 否。
- **数据存储格式变更:** 否。
- **最低支持版本:** API 26.0.0。
- **API 版本号策略:** 沿用 SDK 现有 `@since 26.0.0` 标注；本次不新增 C API。

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| Dynamic 与 Static 行为分离 | Dynamic release 后指定 API 使用 `111002`；Static 不动，保持既有降级返回。 | AC-1.4, AC-3.1, AC-3.2 |
| C API ABI 不变 | 不新增 C API release/isReleased，不修改 Dispose 签名、结构布局和错误码。 | AC-3.4, AC-3.5 |
| 异步安全 | 已发起 `load()` 后 release 必须安全完成，不访问已释放内存。 | AC-2.1 |
| 验证方式边界 | 本次不补 NAPI 单测，不强制 XTS；允许新增 previewer 可执行用例。 | AC-1.1 到 AC-3.5 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | 未调用 `release()` 的既有调用路径无用户可感知行为变化。 | 既有回归 / previewer 冒烟 | `evidence/checks/check-implementation.md` 构建 PASS；Previewer GUI 待人工补验 |
| 安全 | 不新增权限，不处理隐私数据。 | 代码审查 | `evidence/reviews/spec-compliance.md` PASS |
| 可靠性 | 重复 release、release 后访问、异步 load 与 release 交错不崩溃。 | previewer 可执行用例 / API 行为验证 | `evidence/reviews/spec-compliance.md` PASS；Previewer GUI 待人工补验 |
| 可测试性 | P0/P1 AC 可通过 previewer 可执行用例或明确替代审查验证。 | previewer / 代码审查 | `evidence/checks/check-implementation.md` 记录可执行页面和未执行缺口 |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | DrawableDescriptor release 行为与设备形态无关。 | previewer / API 行为验证 | 代码审查确认无设备分支；Previewer GUI 待人工补验 |
| 平板 | 无差异 | DrawableDescriptor release 行为与设备形态无关。 | previewer / API 行为验证 | 代码审查确认无设备分支；Previewer GUI 待人工补验 |
| 折叠屏 | 无差异 | DrawableDescriptor release 行为与设备形态无关。 | previewer / API 行为验证 | 代码审查确认无设备分支；Previewer GUI 待人工补验 |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | N/A | 数据对象生命周期，不直接参与无障碍树。 | N/A |
| 大字体 | N/A | 不涉及文本显示。 | N/A |
| 深色模式 | N/A | 不改变资源选择或主题适配。 | N/A |
| 多窗口/分屏 | N/A | DrawableDescriptor release 行为与窗口状态无关。 | N/A |
| 多用户 | N/A | 不涉及用户数据隔离。 | N/A |
| 版本升级 | 是 | API 26.0.0 起补齐 runtime 行为；未调用 release 的旧行为保持不变。 | AC-1.6 |
| 生态兼容 | 是 | Static 和 C API 生命周期保持不变。 | AC-3.1 到 AC-3.5 |

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（做什么/不做什么清晰）
- [x] 无语义模糊表述（"快速""稳定""尽可能"等）
- [x] AC 与规则表交叉一致（每个 AC 至少关联一条规则，每条规则至少关联一个 AC）
- [x] 规则表每条通过 5 项质量检查（可复现/可观测/边界值/关联AC/无冲突）

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "DrawableDescriptor release isReleased Dynamic Static C API behavior"
```

**关键文档：** `.codespec/changes/drawable-descriptor-release-state/proposal.md`、`specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md`、`specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md`
