---
target_release:
  id: API-26.0.0
  status: proposed
---

# 需求文档

> 一份文档，从原始需求到基线结论。当前 proposal 已 Baselined，可作为下游 spec 输入。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-drawable-descriptor-release-state |
| 需求名称 | DrawableDescriptor 增加 release/isReleased 绑定状态能力 |
| 来源 | 用户请求 |
| 提出人 | liyujie |
| 目标发行版本 | API 26.0.0 |
| 候选 Profile | arkui (子 profile: sdk-api) |
| 优先级 | P1 |
| 状态 | Baselined |

### 原始描述

**原始问题：** 我要在drawable descriptor中增加release方法和isReleased方法，release方法用于解除前端对象跟后端对象之间的绑定关系，isReleased则判断这个关系有没有解除。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| ArkTS/System API 调用者 | Dynamic DrawableDescriptor SDK 已声明 release/isReleased，但动态 NAPI 方法表未注册对应方法，无法通过动态前端显式解除对象与 native descriptor 的绑定 | 大对象/资源只能依赖 GC/finalizer；API 声明与运行时行为不一致 |
| Native/NDK bridge 调用者 | 从 ArkTS 对象提取 native descriptor 时依赖 `napi_unwrap`/`nativeObj`，已释放对象的错误边界需要与 release 语义对齐 | release 后继续桥接可能出现行为不一致或错误码覆盖不足 |

**期望结果：** DrawableDescriptor 前端对象提供 `release()` 和 `isReleased()`；`release()` 首次调用解除前端对象与后端对象的绑定并释放对应 native 引用，重复调用不崩溃；`isReleased()` 返回绑定关系是否已解除；release 后继续访问内部 native 数据的 API 按规格返回或抛出明确结果。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| AGENTS 规则 | `AGENTS.md` | 要求 KB-first、源码核验、API/ABI 风险显式确认。 |
| KB 路由 | `docs/kb/components/media/image.md:129` | DrawableDescriptor 归属图片加载通用能力：`specs/04-common-capability/01-image-loading/03-drawable-descriptor/`。 |
| 长期规格 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md:65` | 已记录 Dynamic 重复 release 不崩溃且 `isReleased()` 返回 true。 |
| 长期规格 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md:66` | 已记录 Dynamic release 后 `getPixelMap`/Layered getter/`loadSync`/`load` 抛 `BusinessError 111002`。 |
| 长期规格 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md:67` | 已记录 Static release 后返回 `undefined` 或 `imageWidth=-1,imageHeight=-1`。 |
| 长期设计 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md:84` | 版本节点记录 API 26 包含 release + Picture + HDR。 |
| 长期设计 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md:96` | ADR-6 记录 TS 侧 release/isReleased 显式释放 + GC fallback，C 侧 dispose 显式释放。 |
| Dynamic SDK 声明 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts:143` | `release(): void` 已声明，since 26.0.0 dynamic。 |
| Dynamic SDK 声明 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts:160` | `isReleased(): boolean` 已声明，since 26.0.0 dynamic。 |
| Static SDK 声明 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets:115` | Static `release(): void` 已声明。 |
| Static SDK 声明 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets:126` | Static `isReleased(): boolean` 已声明。 |
| Static 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets:94` | Static `release()` 已实现，清理 finalizer、置 `nativeObj=0`、置 `_isReleased=true`。 |
| Static 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets:104` | Static `isReleased()` 返回 `_isReleased`。 |
| Dynamic release 状态实现 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:40`、`:129`、`:138` | 最新实现将 release 状态保存为 JS object 属性 `_isReleased`；创建路径初始化 `false`，`isReleased()` 直接读取该属性。 |
| Dynamic release 解绑实现 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1055`、`:1058`、`:1060` | `release()` 已实现幂等判断，首次调用设置 `_isReleased=true`，再通过 `napi_remove_wrap` 解除当前前端对象到 native 的 wrap 绑定。 |
| Dynamic 方法表覆盖 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1503`、`:1512`、`:1521`、`:1532`、`:1542` | Base、PixelMap、Layered、Animated、Picture 五类 descriptor 均注册 `release/isReleased`。 |
| Dynamic 访问型 API | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:477`、`:505`、`:533`、`:621`、`:736`、`:803` | SDK 已标 `111002` 的 `getForeground/getBackground/getMask/getPixelMap/load/loadSync` 读取 `_isReleased` 后抛出或 reject。 |
| Dynamic 控制/刷新类 API | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:586`、`:857`、`:1427`、`:1455` | SDK 未标错误码的 `setBlendMode/getAnimationController/setHdrComposition/invalidate` 不额外读取 `_isReleased`；release 后 unwrap 取不到 native 即无操作返回。 |
| Dynamic async load 引用 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:757`、`:717`、`:778` | 未 release 时已发起的 `load()` 使用 async context 独立持有并释放 native 引用，release 不取消已发起 Promise。 |
| Bridge 行为 | `interfaces/native/node/native_node_napi.cpp:360` | NAPI bridge 在 `napi_unwrap` 失败时返回 `ERROR_CODE_PARAM_INVALID` 并提示对象已释放。 |
| ANI bridge 行为 | `interfaces/native/node/native_node_ani.cpp:343` | ANI bridge 通过 `nativeObj` 判断 native 对象是否存在。 |
| C API 现状 | `interfaces/native/node/drawable_descriptor.cpp:66` | C API 已有 `OH_ArkUI_DrawableDescriptor_Dispose`，本需求不应改动其 ABI/语义。 |
| 测试缺口 | `rg release/isReleased/111002 test/unittest ...` | 未找到针对 release/isReleased 的既有单测命中；按用户确认不补 NAPI 单测，已新增 previewer 可执行用例并使用代码审查记录替代证据。 |

### 初始范围

**可能包含：**
- Dynamic `@ohos.arkui.drawableDescriptor` NAPI 运行时补齐 `release()` / `isReleased()` 方法注册和实现。
- 覆盖 `DrawableDescriptor`、`PixelMapDrawableDescriptor`、`LayeredDrawableDescriptor`、`AnimatedDrawableDescriptor`、`PictureDrawableDescriptor` 五类对象的 release 状态。
- release 首次调用释放或减少 native 引用，并解除前端对象到后端对象的访问路径。
- release 后 `getPixelMap()`、`getForeground()`、`getBackground()`、`getMask()`、`loadSync()`、`load()` 返回或抛出与 Dynamic SDK 声明一致的 `BusinessError 111002`。
- release 后 `invalidate()`、`setHdrComposition()`、`getAnimationController()`、`setBlendMode()` 无操作返回。
- 保持 Static 已实现行为，不修改 Static 运行时语义。
- 不补充 NAPI 单测，不强制新增 XTS；可新增 previewer 可执行用例覆盖首次 release、重复 release、isReleased、release 后访问、bridge 提取 released 对象等行为。

**明确不包含：**
- 不新增或修改 `interfaces/native/drawable_descriptor.h` 的 C API 签名、结构布局、错误码或 ABI。
- 不改变 `OH_ArkUI_DrawableDescriptor_Dispose` 语义；它仍是 C API 句柄释放接口。
- 不改变 DrawableDescriptor 的加载、合成、动画控制、Picture/HDR 等非 release 行为。
- 不手工修改 `frameworks/bridge/arkts_frontend/**/generated/` 产物。
- 不调整图片解码、ResourceManager、PixelMap 生命周期策略。
- 不新增权限、IPC、跨进程通信或数据迁移。

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| Dynamic SDK 声明已经包含 release/isReleased，当前需求重点是补齐运行时实现 | 技术/API | SDK 声明 + NAPI 方法表核验 | 已验证 |
| Static ArkTS 已实现 release/isReleased，且 release 后采用降级返回而非 BusinessError | 技术/兼容性 | Static 实现 + 长期规格核验 | 已验证 |
| Dynamic release 应解除 `napi_wrap` 对 native 指针的有效访问，并避免 GC finalizer 二次释放 | 技术/可靠性 | 源码核验当前 wrap/finalizer 两类释放路径 | 已设计并实现 |
| C API 不需要新增 release/isReleased，因为已有 Dispose 且本需求描述为前端对象与后端对象绑定解除 | API/兼容性 | C API 现状核验 + release 不影响已提取 C 侧句柄的确认 | 已验证 |
| 目标版本沿用 SDK 声明 API 26 | 发布 | SDK 注解核验 + liyujie 确认 | 已验证 |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 单仓变更，但涉及 System API 运行时语义、对象生命周期、错误码和测试补齐。 |
| 涉及仓数量 | 1 | 实现位于 ace_engine；SDK 声明位于 interface/sdk-js 且已存在，本次不强制修改 SDK 声明/文档/示例。 |
| 是否涉及 Public/System API | 是：System API 运行时语义；Public C API 不新增 | Dynamic/Static SDK 已声明 release/isReleased；C API Dispose 已存在。 |
| 是否涉及安全/性能关键路径 | 否 | 主要是生命周期释放；不在渲染热路径，但涉及资源提前释放和 async load 竞态，需要可靠性约束。 |
| 是否跨 SIG | 否 | 初步归属 ArkUI SIG。 |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [x] 需求来源和责任人已明确
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断或明确为待定

---

## 二、澄清记录

### 待澄清问题

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | 目标版本是否确认为 API 26 / OpenHarmony 版本号是什么？ | SDK 注解为 26.0.0，但 proposal 需明确 target_release。 | 已澄清：沿用 API 26.0.0；确认人 liyujie。 |
| Q-2 | Owner/确认人是谁？ | 标准级 ArkUI 需求基线必须有需求方/Owner/SIG 确认。 | 已澄清：Owner/确认人 liyujie。 |
| Q-3 | Dynamic release 后是否严格按 SDK 声明对 `getPixelMap/getForeground/getBackground/getMask/loadSync/load` 抛 `BusinessError 111002`？ | Static 当前是降级返回；Dynamic SDK 文档要求 111002，需要确认不做跨范式拉齐。 | 已澄清：是，按 SDK 抛出或 reject 111002；确认人 liyujie。 |
| Q-4 | `invalidate()`、`setHdrComposition()`、`getAnimationController()`、`setBlendMode()` release 后是否也应统一拦截？ | SDK 文档列举的 API 不完全覆盖所有访问 native 的方法，避免实现期语义漂移。 | 已澄清：release 后无操作返回；确认人 liyujie。 |
| Q-5 | release 是否应影响已经通过 bridge 提取出的 `ArkUI_DrawableDescriptor*` 句柄？ | 前端对象解绑不应破坏已增加引用计数的 C 侧句柄，除非需求方明确要求。 | 已澄清：release 只解除当前前端对象绑定，不主动影响已提取 C 侧句柄；确认人 liyujie。 |
| Q-6 | async `load()` 已入队后再调用 release，Promise 应按旧 native 完成、reject 111002，还是取消/安全返回？ | 涉及异步生命周期与 use-after-release 防护，是实现设计关键边界。 | 已澄清：已发起的 `load()` 继续安全完成；release 后新调用 `load()` 按 Q-3 reject 111002；确认人 liyujie。 |
| Q-7 | 是否只补 Dynamic NAPI，还是也要求 Static 行为与 Dynamic 111002 错误码完全一致？ | Static 现有实现和长期规格是 `undefined/-1` 降级返回，改变会有兼容风险。 | 已澄清：Static 不动；确认人 liyujie。 |
| Q-8 | 是否需要新增 XTS/SDK API 文档/示例？ | sdk-api 子 profile 要求声明、运行时、测试和文档同步确认。 | 已澄清：不补 NAPI 单测，不强制新增 XTS；可新增 previewer 可执行用例；确认人 liyujie。 |

### 确认口径

> Q-1 到 Q-8 已由 liyujie 确认；proposal 已满足基线输入条件。

| 编号 | 推荐结论 | 依据 |
|------|----------|------|
| Q-1 | 目标 API 版本沿用 `@since 26.0.0`。 | Dynamic/Static SDK 声明均标注 26.0.0；liyujie 已确认。 |
| Q-2 | Owner/确认人为 liyujie。 | liyujie 已确认。 |
| Q-3 | Dynamic 按 SDK 声明执行：release 后访问 `getPixelMap/getForeground/getBackground/getMask/loadSync/load` 抛出或 reject `BusinessError 111002`。 | Dynamic SDK 和长期规格已有明确错误码。 |
| Q-4 | `invalidate/setHdrComposition/getAnimationController/setBlendMode` release 后无操作返回。 | liyujie 已确认。 |
| Q-5 | release 只解除当前前端对象与后端对象的绑定，不主动使已通过 bridge 增加引用计数的 `ArkUI_DrawableDescriptor*` 失效；released 对象再次 bridge 提取应返回参数错误。 | liyujie 已确认；NAPI bridge 已通过 unwrap 空指针处理已释放路径；C API 句柄有独立 Dispose。 |
| Q-6 | `load()` 在 release 后调用应 reject 111002；`load()` 调用时对象未 release 且已入队时继续安全完成，完成结果不重新绑定已 release 的前端对象。 | liyujie 已确认；需要同时满足 API 语义和 use-after-release 防护。 |
| Q-7 | Static 保持现有 `undefined/-1` 降级行为，不在本次改成 Dynamic 的 111002。 | liyujie 已确认；长期规格 AC-1.6 和 Static 实现已如此定义，改动会引入兼容风险。 |
| Q-8 | 本次不补 NAPI 单测，不强制新增 XTS；允许新增 previewer 可执行用例。 | liyujie 已确认；既有单测未命中 release/isReleased/111002。 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-07-21 | AI Agent | SDD Define 初始分析 | 需求定位为 Dynamic DrawableDescriptor release/isReleased 运行时补齐；基线时 SDK/长期规格已有该 API，动态运行时存在方法接线和 release 后访问归类缺口。 | 需求方/Owner 回答 Q-1 到 Q-8 后才能基线。 |
| 2026-07-21 | AI Agent | Clarifying 推进 | 已形成 Q-1 到 Q-8 推荐确认口径。 | 等待需求方/Owner 确认或修正推荐口径。 |
| 2026-07-21 | liyujie | Clarifying 第一轮答复 | Q-1 目标版本沿用 API 26.0.0；Q-2 Owner/确认人为 liyujie；Q-3 Dynamic 指定 API release 后抛出或 reject 111002；Q-4 其他 native 访问方法 release 后无操作返回；Q-5 release 只解除当前前端对象绑定，不影响已提取 C 侧句柄；Q-6 已发起 load 继续安全完成。 | 继续确认 Q-7 Static 行为和 Q-8 文档/示例范围。 |
| 2026-07-21 | liyujie | Clarifying 第二轮答复 | Q-7 Static 不动；Q-8 不补 NAPI 单测，不强制新增 XTS，可以新增 previewer 可执行用例。 | 澄清关闭，进入 proposal 基线。 |
| 2026-07-23 | liyujie | 实现口径修正 | release 状态应存为 JS object `_isReleased` 属性；SDK 未标错误码的 API 不需要检查 `_isReleased`，未获取到 native 指针即无操作返回。 | 已同步调整 design/plan/review/evidence 文档。 |

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | Dynamic 前端对象解除 native 绑定、查询释放状态、release 后访问边界。 | liyujie | 已确认 |
| 明确不包含哪些？ | C API ABI 变更、Dispose 语义变更、非 release 行为变更、生成文件手工修改。 | liyujie | 已确认 |
| 是否有分期策略？ | 一期只补 Dynamic 运行时；Static 不动；不补 NAPI 单测，不强制 XTS，允许新增 previewer 可执行用例。 | liyujie | 已确认 |

### 方案探索

| 编号 | 方案概述 | 优势 | 风险/代价 | 选择结论 |
|------|----------|------|-----------|----------|
| A-1 | 在 Dynamic JS object 上保存 `_isReleased` 状态；release 设置属性后通过 `napi_remove_wrap` 解除 wrap；仅 SDK 标记 `111002` 的访问型 API 读取 `_isReleased`，未标错误码的控制/刷新类 API 通过 unwrap native 为空自然无操作。 | 贴合“前端对象与后端对象解绑”的需求；不改 core/C API ABI；`isReleased()` 可直接读取前端对象状态；可复用现有 finalizer/refcount 策略；未标错误码的 API 不增加开发者错误处理负担。 | 需要梳理 Layered 旧对象 delete 与新 descriptor refcount 两类释放，避免二次释放；需要处理 async load 竞态；需要覆盖所有对象创建路径初始化 `_isReleased=false`；需要逐项确认哪些 API 需要 `111002`，哪些只保留 native 空返回。 | 推荐 |
| A-2 | 在 `frameworks/core/drawable/DrawableDescriptor` 增加 released 状态。 | core 层状态集中。 | 不能覆盖 NAPI wrap 解绑语义；Layered 旧对象与新 descriptor 混用，仍需前端 wrapper 状态；C API/bridge 可能受影响。 | 备选 |
| A-3 | 仅在 JS/ArkTS 声明层增加方法，不释放 native。 | 改动小。 | 不满足解除绑定和提前释放资源目标；与 SDK 111002 语义不一致。 | 放弃 |

**取舍理由：** A-1 最小化 API/ABI 风险，并直接解决动态前端对象到 native 对象的绑定解除问题。实现以 JS object `_isReleased` 作为状态真相源；`release/isReleased` 和 SDK 已标 `111002` 的访问型 API 读取该属性，未标错误码的控制/刷新类 API 只依赖既有 native unwrap 空返回路径。

### 上下文与知识源检索日志

| 编号 | 来源 | 查询/读取内容 | 关键发现 | 可信度 | 用于 | 命中/原因 |
|------|------|---------------|----------|--------|------|-----------|
| K-1 | KB | `python3 docs/kb_search.py "drawable descriptor"` | 无直接条目。 | 高 | 路由 | 未命中 |
| K-2 | KB/docs | `rg DrawableDescriptor docs` | `docs/kb/components/media/image.md:129` 指向 DrawableDescriptor 规格目录。 | 高 | 路由 | 命中 |
| K-3 | 规格 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md` | 已有 AC-1.4/1.5/1.6 定义 release/isReleased 和 release 后行为。 | 高 | 范围/AC | 命中 |
| K-4 | 设计 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md` | ADR-6 定义 TS release/isReleased + GC fallback，C 侧 Dispose。 | 高 | 方案 | 命中 |
| K-5 | SDK | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts` | Dynamic `release/isReleased` 已声明为 API 26。 | 高 | API 评估 | 命中 |
| K-6 | SDK | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets` | Static `release/isReleased` 已声明。 | 高 | API 评估 | 命中 |
| K-7 | Static 实现 | `frameworks/bridge/arkts_frontend/.../@ohos.arkui.drawableDescriptor.ets` | Static `_isReleased`、`release()`、`isReleased()` 已实现。 | 高 | 范围 | 命中 |
| K-8 | Dynamic 实现 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp/.h` | 最新实现已补齐 Dynamic `release/isReleased` 注册；JS object `_isReleased` 为状态真相源，`111002` 访问型 API 读取该属性，未标错误码 API native 为空无操作。 | 高 | 范围/风险 | 命中 |
| K-9 | Bridge | `interfaces/native/node/native_node_napi.cpp` / `native_node_ani.cpp` | NAPI/ANI bridge 已通过 unwrap/nativeObj 空值识别已释放/无 native 对象路径。 | 高 | 边界 | 命中 |
| K-10 | 测试 | `rg release/isReleased/111002 test/unittest ...` | 未找到 release/isReleased 行为单测；按用户确认不补 NAPI 单测，使用 previewer 可执行用例和代码审查作为本轮验证资产。 | 高 | 测试计划 | 未命中，记录替代验证 |

**上下文结论：**
- 高可信结论：SDK 与长期规格已经定义 release/isReleased；Static 已实现；Dynamic NAPI 最新实现已补齐方法注册、JS object `_isReleased` 状态、`111002` 访问型 API 检查和无错误码 API native 空返回。
- 待补充结论：无。
- 未使用来源及原因：未查外部 DeepWiki/多仓知识库；当前证据已能在本仓和 interface/sdk-js 中定位 API 与实现缺口，且网络受限。

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | ArkUI / ace_engine；可能只读或同步 interface/sdk-js SDK 声明。 | liyujie | 已确认 |
| 是否需要新增子系统或部件？ | 否。 | liyujie | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 不新增 Public C API；现有 C API Dispose 不变。 | liyujie | 已确认 |
| 是否需要新增 System API？ | SDK 已声明 Dynamic/Static `release/isReleased`；本次补齐 System API 运行时实现。 | liyujie | 已确认 |
| 是否会废弃已有 API？ | 否。 | liyujie | 已确认 |
| 是否需要新增权限声明？ | 否。 | liyujie | 已确认 |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | release 后行为是否改变既有应用？ | 新增/补齐 API 26 行为；未调用 release 的既有流程不应变化。release 后访问错误语义需与 SDK 保持一致；其他 native 访问方法 release 后无操作返回。 | liyujie | 已确认 |
| 性能 | 是否影响热路径？ | 正常访问增加一次轻量状态检查；release 可提前释放 native 引用。 | liyujie | 已确认 |
| 安全 | 是否涉及权限/隐私？ | 不涉及新增权限或隐私数据；需避免 release/load 竞态导致 use-after-release。 | liyujie | 已确认 |
| 可靠性 | 重复 release、GC finalizer、bridge 引用计数如何保证？ | 必须防二次释放；已发起 load 继续安全完成；释放策略要区分旧 Layered 对象和新 descriptor refcount。 | liyujie | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| ArkUI drawable modifier | 运行 | Dynamic 非 Layered descriptor 通过 modifier 管理 native descriptor 引用计数。 | 已核验 |
| NAPI wrap/finalizer | 运行 | release 需要与 `napi_wrap`/finalizer 行为一致，避免 GC 再次释放。 | 已设计并实现 |
| interface/sdk-js | API | 声明已存在；本次不强制修改 SDK 文档或示例。 | 已确认 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| 二次释放 | 可靠性 | release 后 GC finalizer 再释放 native，可能崩溃。 | release 设置 `_isReleased` 后通过 `napi_remove_wrap` 删除 NativeReference，并复用既有 finalizer 释放当前绑定引用。 | 已实现 |
| 异步加载竞态 | 可靠性 | `load()` 入队后 release，async context 持有已释放 native。 | 已发起 load 继续安全完成；设计中需要保持必要 native 引用，不允许 use-after-release。 | 已确认 |
| 范式行为不一致 | 兼容性 | Dynamic 抛 111002，Static 返回 undefined/-1。 | Static 不动，差异由 proposal/spec 明确记录。 | 已确认 |
| 方法表覆盖不全 | 实现 | 子类实例可能没有 release/isReleased。 | 五类 NAPI 方法表统一注册公共生命周期方法。 | 已实现 |

### AC 完整性

- [x] 每个用户故事有验收标准草案
- [x] AC 使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 已由需求方/Owner 确认，可进入基线

### 澄清结论

- [x] 功能范围已完全明确
- [x] 子系统影响已识别
- [x] API 变更已评估
- [x] 兼容性和非功能需求已确认
- [x] 依赖和风险已识别且有缓解方案草案
- [x] AC 草案可测试
- [x] 标准复杂度已完成方案探索

**结论:** 通过；liyujie 已确认范围、兼容性和验证边界，可进入 spec。

---

## 三、需求基线

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-07-21 |
| Owner | liyujie |
| 确认人 | liyujie |
| 复杂度 | 标准 |
| Profile | arkui / arkui-sdk-api |
| 目标发行版本 | API 26.0.0 |
| 版本状态 | proposed |

### 问题陈述

Dynamic DrawableDescriptor SDK 已声明 `release()` 和 `isReleased()`，长期规格也定义了 release 后行为；本需求补齐前端对象与后端 native descriptor 的显式解绑能力，并把 release 后访问行为固化为可测试契约。最新实现中，Dynamic NAPI 已注册生命周期方法，`_isReleased` 保存在 JS object 上；SDK 标记 `111002` 的访问型 API 按错误码返回，未标错误码的控制/刷新类 API 在 native unwrap 为空时无操作返回。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 提供显式解绑能力 | Dynamic 五类 DrawableDescriptor 对象均可调用 `release()`，重复调用不崩溃。 | previewer 可执行用例 / API 行为验证 |
| 提供释放状态查询 | release 前 `isReleased()` 为 false，release 后为 true。 | previewer 可执行用例 / API 行为验证 |
| release 后访问行为明确 | 指定 API release 后按 SDK 语义抛 `BusinessError 111002`；其他指定方法无操作；Static 既有规格不变。 | previewer 可执行用例 / API 行为验证 |
| 不破坏 C API ABI | `interfaces/native/drawable_descriptor.h` 无签名、结构布局、错误码变更。 | 代码审查 + C API 编译/测试 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为 ArkTS 调用者，我想要主动 release DrawableDescriptor，以便提前解除前端对象与 native descriptor 的绑定。 | P0 |
| US-2 | 作为 ArkTS 调用者，我想要查询 DrawableDescriptor 是否已 release，以便避免对已解绑对象继续访问。 | P0 |
| US-3 | 作为 Native bridge 调用者，我想要 released ArkTS 对象被识别为无效 native 对象，以便避免复用已解绑对象。 | P1 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN Dynamic DrawableDescriptor 或任一子类首次调用 `release()` THEN native 绑定被解除，后续 GC/finalizer 不发生二次释放。 | 正常 | US-1 |
| AC-2 | WHEN Dynamic 同一对象重复调用 `release()` THEN 调用直接返回且不崩溃，`isReleased()` 保持 true。 | 边界 | US-1/US-2 |
| AC-3 | WHEN Dynamic 未释放对象调用 `isReleased()` THEN 返回 false；WHEN 已释放对象调用 `isReleased()` THEN 返回 true。 | 正常 | US-2 |
| AC-4 | WHEN Dynamic 已释放对象调用 `getPixelMap()`、`getForeground()`、`getBackground()`、`getMask()`、`loadSync()` 或 `load()` THEN 抛出或 reject `BusinessError 111002`。 | 异常 | US-1 |
| AC-5 | WHEN Static 已释放对象调用 `getPixelMap()`、`loadSync()` 或 `load()` THEN 保持现有规格：返回 `undefined` 或 `imageWidth=-1,imageHeight=-1`，除非 Owner 明确要求改为错误码。 | 兼容 | US-1 |
| AC-6 | WHEN 通过 NAPI/ANI bridge 从 released DrawableDescriptor 提取 native descriptor THEN 返回参数错误，不产生新的有效 native 引用。 | 异常 | US-3 |
| AC-7 | WHEN 不调用 `release()` 使用 DrawableDescriptor 现有加载、合成、动画、Picture/HDR 能力 THEN 既有行为不变。 | 兼容 | US-1 |
| AC-8 | WHEN `load()` 已入队后对象调用 `release()` THEN 已发起的 Promise 继续安全完成，完成过程不访问已释放内存，也不重新绑定已 release 的前端对象。 | 边界 | US-1 |
| AC-9 | WHEN Dynamic 已释放对象调用 `invalidate()`、`setHdrComposition()`、`getAnimationController()` 或 `setBlendMode()` THEN 调用无操作返回且不崩溃。 | 边界 | US-1 |

### 范围边界

**包含：** Dynamic NAPI release/isReleased 方法注册和实现、JS object `_isReleased` 状态、访问型 `111002` 检查、控制/刷新类 native 空返回、bridge released 对象边界、previewer 可执行用例。

**不包含：** C API ABI 变更、C API Dispose 行为变更、PixelMap/ResourceManager/图片解码策略变更、非 release 能力重构、生成文件手工修改。

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 当前职责 | 影响类型 | Owner |
|--------|------|-----------|----------|----------|-------|
| ArkUI | ace_engine | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp/.h` | Dynamic NAPI DrawableDescriptor 类和方法绑定 | 修改/运行时实现 | liyujie |
| ArkUI | ace_engine | `frameworks/bridge/arkts_frontend/.../@ohos.arkui.drawableDescriptor.ets` | Static DrawableDescriptor ArkTS 实现 | 可能测试/对齐，不建议改语义 | liyujie |
| ArkUI | ace_engine | `interfaces/native/node/native_node_napi.cpp` | 从 ArkTS NAPI 对象提取 C API descriptor | 边界测试/可能小修 | liyujie |
| ArkUI | ace_engine | `interfaces/native/node/native_node_ani.cpp` | 从 ArkTS static/ANI 对象提取 C API descriptor | 边界测试/可能小修 | liyujie |
| ArkUI | interface_sdk-js | `api/@ohos.arkui.drawableDescriptor*.d.ts/.d.ets` | SDK API 声明 | 已存在；仅需确认是否同步注释 | liyujie |
| ArkUI | ace_engine | `examples/` 或 `examples/SpecTest/` previewer 可执行用例路径 | DrawableDescriptor release/isReleased 行为验证 | 可新增用例 | liyujie |

### API 变更项清单

| API 名称 | 变更类型 | 开放范围 | 概要说明 |
|----------|----------|----------|----------|
| `DrawableDescriptor.release()` | 运行时补齐 | System API | SDK 已声明；Dynamic NAPI 运行时补齐解绑行为。 |
| `DrawableDescriptor.isReleased()` | 运行时补齐 | System API | SDK 已声明；Dynamic NAPI 运行时补齐状态查询。 |
| `OH_ArkUI_DrawableDescriptor_Dispose` | N/A | Public C API | 不新增、不修改；仅作为现有 C API 生命周期对照。 |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 是（轻量） | release 可提前释放资源；仅 `release/isReleased` 和 SDK 标记 `111002` 的访问型 API 增加轻量状态读取，未标错误码的控制/刷新类 API 不新增 release 状态检查。 | spec.md / design.md |
| 安全与权限 | 否 | 不新增权限、不处理隐私数据；可靠性风险在设计中处理。 | N/A |
| 兼容性 | 是 | Dynamic/Static release 后行为差异和 C API ABI 不变需要固化。 | spec.md |
| API/SDK | 是 | System API 运行时补齐，SDK 声明已存在。 | spec.md / design.md |
| IPC/跨进程 | 否 | DrawableDescriptor 对象绑定在本进程运行时。 | N/A |
| 构建与部件 | 是 | 修改 inner_api/测试目标后需构建验证。 | design.md / execution-plan.md |
| 国际化/无障碍 | 否 | 数据对象生命周期，不影响文本或无障碍树。 | N/A |
| 数据迁移 | 否 | 不持久化数据。 | N/A |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 要求新增 C API 或改变 Dispose ABI/语义 | 回到 proposal 重新评估 API/ABI 风险，需用户/Owner 确认。 |
| AC 变更 | release 后错误码、Static 行为或 async load 语义变化 | 回到 proposal/spec 重新审批。 |
| API 变更 | SDK 签名、错误码、since 标注变更 | 触发 design/API 审批。 |
| 目标版本变更 | 确认 OpenHarmony 目标版本 | 更新 proposal frontmatter 和 manifest。 |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC 并经需求方/Owner 确认
- [ ] 每条 AC 可测试、可度量
- [ ] 范围内/外已确认
- [x] `proposal.target_release` 已确认
- [x] `manifest.profile` 已确认或明确 none
- [x] 涉及仓、模块、SIG 已识别
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认
- [x] 标准复杂度的澄清问题已逐项关闭，且讨论记录包含需求方/Owner/SIG 明确确认
- [x] 上下文与知识源检索日志已填写；未查询关键来源的原因已记录
- [x] 目标仓 Agent 指南已检查并记录关键约束

**基线结论:** 通过。Q-1 到 Q-8 已关闭，proposal 可作为 spec 输入。
