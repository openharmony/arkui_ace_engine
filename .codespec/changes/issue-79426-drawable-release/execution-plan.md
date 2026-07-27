# 执行计划

> 将 Approved spec/design 拆成可执行、可验证、可审查的 Task。当前状态为 Approved，可进入代码实现。

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-drawable-descriptor-release-state |
| CodeSpec ID | drawable-descriptor-release-state |
| 关联 Feature | Func-04-01-03-Feat-01-delta |
| 关联文档 | proposal.md / spec.md / design.md |
| Profile | arkui |
| 子 Profile | sdk-api |
| 复杂度 | 标准 |
| 状态 | Approved |
| Owner | liyujie |

## 输入状态

| 输入 | 路径 | 要求状态 |
|------|------|----------|
| Requirement | `.codespec/changes/drawable-descriptor-release-state/proposal.md` | Approved / Baselined |
| Spec | `.codespec/changes/drawable-descriptor-release-state/spec.md` | Approved |
| Design | `.codespec/changes/drawable-descriptor-release-state/design.md` | Approved |

## 受影响文件全量清单

| 仓 | 层（来自 design.md） | 文件路径 | 修改类型 | 说明 |
|----|---------------------|----------|----------|------|
| ace_engine | Dynamic NAPI binding | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` | 修改 | 声明 `release/isReleased`。 |
| ace_engine | Dynamic NAPI binding | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` | 修改 | 注册五类 Dynamic descriptor 的生命周期方法；通过 JS object `_isReleased` 属性判断 release/isReleased 和 SDK 标记 `111002` 的访问型 API 状态，控制/刷新类 API 不额外读取 `_isReleased`，通过 native 空返回保持无操作；补齐 load async 引用保持；通过 `napi_remove_wrap` 解除 native 绑定。 |
| ace_engine | Previewer 可执行用例 | `examples/DrawableDescriptor/entry/src/main/ets/pages/DrawableDescriptorReleaseStateTest.ets` | 新增 | 覆盖 Dynamic `release/isReleased`、重复 release、release 后访问型 API、控制/刷新类 API、已发起 load 后 release。 |
| ace_engine | Previewer 可执行用例 | `examples/DrawableDescriptor/entry/src/main/ets/pages/Index.ets` | 修改 | 将 `DrawableDescriptorReleaseStateTest` 页面加入现有 DrawableDescriptor 示例入口。 |
| ace_engine | Previewer 可执行用例 | `examples/DrawableDescriptor/entry/src/main/resources/base/profile/main_pages.json` | 修改 | 将 `pages/DrawableDescriptorReleaseStateTest` 加入应用页面 profile，确保 router 可进入新页面。 |
| ace_engine | Static ArkTS | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets` | 只读核验 | Static 已实现 `_isReleased/release/isReleased`；本次不改语义。 |
| ace_engine | NAPI native bridge | `interfaces/native/node/native_node_napi.cpp` | 只读核验 | release 后移除 wrap，使 `OH_ArkUI_GetDrawableDescriptorFromNapiValue` 保持参数错误路径。 |
| ace_engine | ANI native bridge | `interfaces/native/node/native_node_ani.cpp` | 只读核验 | Static released 对象通过 `nativeObj=0` 保持参数错误路径；本次不修改。 |
| ace_engine | C API | `interfaces/native/node/drawable_descriptor.cpp` | 只读核验 | `OH_ArkUI_DrawableDescriptor_Dispose` 签名和生命周期语义不变。 |
| interface_sdk-js | ArkTS Dynamic SDK 声明 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts` | 只读核验 | `release/isReleased` 声明已存在；本次不修改 SDK 声明。 |
| interface_sdk-js | ArkTS Static SDK 声明 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets` | 只读核验 | Static 声明已存在；本次不修改。 |

**检查项：**
- [x] design.md 调用链每一层都有对应文件列出
- [x] 每个文件修改类型和职责说明明确
- [x] Static、C API、SDK 声明均明确为只读核验，不进入实现修改范围
- [x] 不手工修改 `frameworks/bridge/arkts_frontend/**/generated/` 产物
- [x] 不新增或修改 `interfaces/native/` Public C API 签名、结构布局、错误码或 ABI

## AC 到 Task 追溯

| AC | 来源 | Task | 验证方式 | 覆盖 |
|----|------|------|----------|------|
| AC-1.1 | spec.md | TASK-001, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-1.2 | spec.md | TASK-001, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-1.3 | spec.md | TASK-001, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-1.4 | spec.md | TASK-001, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-1.5 | spec.md | TASK-001, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-1.6 | spec.md | TASK-001, TASK-002, TASK-003 | ace_engine 构建 + 现有 DrawableDescriptor previewer 冒烟 | 是 |
| AC-2.1 | spec.md | TASK-002, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-2.2 | spec.md | TASK-001, TASK-003 | Previewer 可执行用例 + 代码审查 | 是 |
| AC-3.1 | spec.md | TASK-003 | Static 文件 diff 审查 + previewer static 页面冒烟 | 是 |
| AC-3.2 | spec.md | TASK-003 | Static 文件 diff 审查 + previewer static 页面冒烟 | 是 |
| AC-3.3 | spec.md | TASK-001, TASK-003 | bridge 只读审查 + released 后 unwrap 失败路径核验 | 是 |
| AC-3.4 | spec.md | TASK-001, TASK-003 | C 句柄引用计数路径审查 | 是 |
| AC-3.5 | spec.md | TASK-003 | C API 头文件和实现 diff 审查 | 是 |

## 首批实现边界

**首批必须实现：** Dynamic NAPI `release/isReleased` 方法注册、JS object `_isReleased` 状态、release 幂等释放、访问型 API `111002` 分流、控制/刷新类 API native 空返回无操作、已发起 `load()` 的 async 引用保持、previewer 可执行用例。

**可后置：** XTS 用例、NAPI 单测、SDK 声明调整、长期 `specs/` 回灌。

**不建议延后：** `load()` 入队后 release 的引用安全；缺失该项会使 AC-2.1 和可靠性底线不闭合。

## 阶段计划

| 阶段 | 目标 | 关键 Task | 结束门槛 | 最小验证 |
|------|------|-----------|----------|----------|
| Phase-1 | Dynamic 生命周期接线和访问分流 | TASK-001 | `release/isReleased` 五类方法表可见，released 后访问型 `111002` 和控制/刷新类 native 空返回分流正确 | ace_engine 构建 + previewer release 状态用例 |
| Phase-2 | 异步 load 生命周期闭环 | TASK-002 | queue 成功、queue 失败、complete 三条路径引用对称释放 | ace_engine 构建 + previewer load/release 用例 |
| Phase-3 | 示例验证和兼容性审查 | TASK-003 | previewer 页面覆盖 P0/P1 AC，Static/C API 文件无行为修改 | previewer 冒烟 + diff 审查 |

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证命令 |
|---------|------|----------|---------|----------|----------|----------|
| TASK-001 | Dynamic `release/isReleased` 与 release 后访问分流 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp/.h` | AC-1.1, AC-1.2, AC-1.3, AC-1.4, AC-1.5, AC-1.6, AC-2.2, AC-3.3, AC-3.4 | 无 | 五类 descriptor 方法表注册生命周期 API；release 幂等且移除当前 wrap；SDK 标记 `111002` 的访问型 API 读取 `_isReleased` 后抛出或 reject；未标错误码的控制/刷新类 API 不额外读取 `_isReleased`，native 为空即无操作；未 release 行为保持原路径 | `cd /srv/workspace/openharmony_master_default_20260713175555_huawei_b8da041e5/code && ./build.sh --product-name rk3568 --build-target ace_engine` |
| TASK-002 | `load()` 已入队后 release 的 async 引用安全 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp/.h` | AC-2.1, AC-1.6 | TASK-001 | 入队成功的 async context 持有独立 native 引用；queue 失败和 complete 路径释放引用；Promise 完成不重新绑定 released 前端对象 | `cd /srv/workspace/openharmony_master_default_20260713175555_huawei_b8da041e5/code && ./build.sh --product-name rk3568 --build-target ace_engine` |
| TASK-003 | Previewer 可执行用例与兼容性审查 | `examples/DrawableDescriptor/entry/src/main/ets/pages/DrawableDescriptorReleaseStateTest.ets`, `examples/DrawableDescriptor/entry/src/main/ets/pages/Index.ets`, 只读核验文件 | AC-1.1 到 AC-3.5 | TASK-001, TASK-002 | 示例入口可打开 release 状态页面；页面能执行首发 release、重复 release、isReleased、release 后访问型 API、控制/刷新类 API、load/release 交错；Static/C API/SDK 声明 diff 无修改 | Previewer 打开 `examples/DrawableDescriptor` 并执行 `DrawableDescriptorReleaseStateTest`、`drawableDescriptorStaticTest` 页面 |

## Task 详情

### TASK-001: Dynamic release/isReleased 与 release 后访问分流

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 Dynamic NAPI 对象侧补齐 `release()` 和 `isReleased()`，并让访问 native 的 Dynamic 方法在 released 状态下按 SDK 错误码口径分流：访问型 API 返回 `111002`，未标错误码的控制/刷新类 API native 为空即无操作。 |
| AC 映射 | AC-1.1, AC-1.2, AC-1.3, AC-1.4, AC-1.5, AC-1.6, AC-2.2, AC-3.3, AC-3.4 |
| 前置依赖 | proposal/spec/design 均 Approved。 |
| 非目标 | 不改 Static ArkTS 行为；不新增 C API；不改 `OH_ArkUI_DrawableDescriptor_Dispose`；不新增 NAPI 单测；不修改 SDK 声明；不手工编辑 generated 文件。 |
| 完成判据 | 五类 Dynamic descriptor 都有 `release/isReleased`；首次 release 设置 released 状态并解除 wrap；重复 release 返回且不崩溃；访问型 API released 后抛 `BusinessError 111002` 或 reject `111002`；控制/刷新类 API released 后不额外读取 `_isReleased`，native 为空即无操作；未 release 路径保持既有行为。 |
| 停止条件 | 发现现有 NAPI runtime 无法在 JS object 上保存 `_isReleased` 状态，或移除 wrap 会破坏 `isReleased()` 可调用性；停止并修订 design/plan。 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` | 增加 `Release`、`IsReleased` 声明。 |
| Modify | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` | 实现生命周期 API，注册到 Base、PixelMap、Layered、Animated、Picture 五类方法表；访问型 API 接入 `111002` guard，控制/刷新类 API 保持 native 空返回无操作。 |

**Spec Context**

| 规格项 | 必须满足 |
|--------|----------|
| AC-1.1 | 首次 `release()` 后对象进入 released 状态，`isReleased()` 返回 true。 |
| AC-1.2 | 重复 `release()` 直接返回、不崩溃，`isReleased()` 保持 true。 |
| AC-1.3 | 未释放对象 `isReleased()` 返回 false。 |
| AC-1.4 | released 后 `getPixelMap/getForeground/getBackground/getMask/loadSync/load` 抛出或 reject `BusinessError 111002`。 |
| AC-1.5 | released 后 `invalidate/setHdrComposition/getAnimationController/setBlendMode` 无操作返回。 |
| AC-1.6 | 未调用 release 的既有加载、分层、动画、Picture/HDR 能力不变。 |
| AC-2.2 | 已 released 后新调用 `load()` reject `BusinessError 111002`。 |
| AC-3.3 | released 对象 bridge 提取 native descriptor 返回参数错误。 |
| AC-3.4 | release 不主动使已提取的 C 侧 `ArkUI_DrawableDescriptor*` 句柄失效。 |

**Design Context**

| ADR | 执行要求 |
|-----|----------|
| ADR-1 | released 状态由 Dynamic JS object `_isReleased` 属性表达；创建时初始化为 `false`，`release()` 后置 `true`，`isReleased()` 直接读取属性，不访问后端业务对象。 |
| ADR-2 | `release()` 未释放时先设置 `_isReleased=true`，再调用 `napi_remove_wrap` 当前对象；NAPI 删除 `NativeReference` 并触发现有 `Destructor` / `NewDestructor` finalizer 对等释放，`Release` 本身不手动 delete/decreaseRef。 |
| ADR-4 | guard 分为访问型 API `111002`、控制/刷新型 API native 空返回无操作、`isReleased()` 可调用三类；未标错误码的控制/刷新类 API 不额外读取 `_isReleased`。 |
| ADR-5 | Static 和 C API 不修改。 |

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | Must: release 状态只在 Dynamic NAPI binding 补齐，不下沉到 core/C API。 |
| OH-ARCH-API-LEVEL | Must Not: 修改 Public C API 签名、结构布局、错误码或 ABI。 |
| arkui/sdk-api | Must: API 签名、错误语义、运行时实现和验证映射与 spec/design 一致。 |

**Steps**

- [x] 在 `js_drawable_descriptor.h/.cpp` 增加 `Release` 和 `IsReleased` NAPI 方法声明与实现。
- [x] 使用 JS object `_isReleased` 属性表达 released 状态；所有创建路径初始化为 `false`，`release()` 首次调用后置 `true` 并移除 wrap，后续调用直接读属性返回。
- [x] 核验 binding release 路径；`napi_remove_wrap` 删除 `NativeReference` 后触发原 finalizer，Layered 旧对象使用 `Destructor` delete，新 descriptor 使用 `NewDestructor` `decreaseRef`。
- [x] 在 Base、PixelMap、Layered、Animated、Picture 五类 descriptor 方法表注册 `release` 和 `isReleased`；`getMaskClipPath` 作为 static 方法不注册实例生命周期 API。
- [x] 将 `getPixelMap/getForeground/getBackground/getMask/loadSync/load` 接入访问型 guard；released 后抛或 reject `BusinessError 111002`。
- [x] 将 `invalidate/setHdrComposition/getAnimationController/setBlendMode` 保持为 native 空返回无操作；released 后因 wrap 已移除，`napi_unwrap` 取不到 native 后直接返回，不额外读取 `_isReleased`。
- [x] 核验 `OH_ArkUI_GetDrawableDescriptorFromNapiValue` 对已移除 wrap 的对象仍走参数错误路径，且未 release 前已提取的 C 侧句柄不被主动释放。
- [x] 从 OpenHarmony 根目录构建 `ace_engine`。

**Completion Evidence**

| 证据类型 | 命令/路径 | 期望结果 |
|----------|-----------|----------|
| 构建 | `bash /home/huawei/.codex/skills/ohos-dev-arkui-ace-engine-build/scripts/build_wrapper.sh --product rk3568 -- --export-para PYCACHE_ENABLE:true --build-target ace_engine --ccache --fast-rebuild` | PASS：`rk3568 build success`，`=====build  successful=====`，时间 `2026-07-23 22:19:58`，cost `0:07:29` |
| 代码审查 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp/.h` | PASS：`Release/IsReleased`、五类方法表、访问型 `111002` guard、控制/刷新类 native 空返回已覆盖；NAPI remove_wrap/finalizer 路径已核验 |

**Handoff Summary**

| 项 | 内容 |
|----|------|
| 允许修改 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp`, `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` |
| 允许新建 | 无 |
| 只读参考 | `interfaces/native/node/native_node_napi.cpp`, `interfaces/native/node/native_node_ani.cpp`, `interfaces/native/node/drawable_descriptor.cpp`, `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts` |
| Spec 摘要 | Dynamic 首次 release 后 `isReleased()` true，重复 release 幂等，未 release 为 false；released 后访问型 API `111002`，控制/刷新类 API native 空返回无操作；bridge 从 released 对象提取 native descriptor 返回参数错误。 |
| Design 摘要 | released 状态由 JS object `_isReleased` 属性表达；release 置 true 后移除当前 wrap，由 NAPI finalizer 触发旧 Layered delete 或新 descriptor decreaseRef；Static/C API 不改。 |
| 验证命令 | `bash /home/huawei/.codex/skills/ohos-dev-arkui-ace-engine-build/scripts/build_wrapper.sh --product rk3568 -- --export-para PYCACHE_ENABLE:true --build-target ace_engine --ccache --fast-rebuild` / 实际 PASS |
| 完成规则 | 不得修改允许范围外的文件；如需扩大范围，先修订 execution-plan；没有 fresh verification evidence 不得声明完成。 |

### TASK-002: load() 已入队后 release 的 async 引用安全

| 字段 | 内容 |
|------|------|
| 任务目标 | 让未 released 状态下已发起的 `load()` 在随后 `release()` 后仍安全完成，并保证 native 引用在 queue 成功、queue 失败、complete 三条路径对称释放。 |
| AC 映射 | AC-2.1, AC-1.6 |
| 前置依赖 | TASK-001 的 released 状态和访问型 guard 已完成。 |
| 非目标 | 不取消已发起 Promise；不改变 `loadSync()` 同步加载语义；不改变 Layered 旧对象 `load()` 既有 undefined 返回路径以外的行为。 |
| 完成判据 | `load()` 入队成功后 async context 持有独立 native 引用；前端对象 release 只释放前端绑定引用；Promise complete 后释放 async 引用；queue 失败时立即释放 async 引用；未 release 的 load/loadSync 回归保持现有结果。 |
| 停止条件 | `GetArkUIDrawableModifier()` 没有可复用的引用计数 API 来为 async context 持有新 descriptor；停止并修订 design/plan。 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` | 必要时补充 async 引用 helper 声明。 |
| Modify | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` | 扩展 `LoadAsyncContext`，在 `Load`、`LoadComplete` 和 queue 失败路径释放 async 引用。 |

**Spec Context**

| 规格项 | 必须满足 |
|--------|----------|
| AC-2.1 | 未释放状态下发起 `load()`，随后 release，已发起 Promise 继续安全完成，不访问已释放内存，不重新绑定 released 前端对象。 |
| AC-1.6 | 未 release 状态下既有加载能力不变。 |

**Design Context**

| ADR | 执行要求 |
|-----|----------|
| ADR-3 | `load()` 入队前对新 descriptor 增加一次 async 持有引用，Promise 完成后释放；release 只释放前端绑定引用。 |
| 资源所有权矩阵 | queue 成功由 async context 持有并在 complete 释放；queue 失败立即释放；前端 release 不影响 async 持有引用。 |

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | Must: 复用 drawable modifier 现有引用计数，不新增跨模块依赖。 |
| arkui/sdk-api | Must: Promise API released 后新调用 reject `111002`，已发起调用不被 release 取消。 |

**Steps**

- [x] 在 `Load()` 中先使用 TASK-001 的访问型 guard；released 状态下创建 Promise 并 reject `BusinessError 111002`。
- [x] 未 release 且非 Layered 的 `load()` 在 async work 入队前增加 async native 引用。
- [x] queue 成功后由 async context 接管引用；queue 失败时释放 async 引用并返回已创建 Promise。
- [x] `LoadComplete()` 在 resolve/reject 后释放 async 引用，再删除 async work 和 context。
- [x] 确认 `LoadExecute()` 只使用 async context 持有的 native，不依赖前端对象 wrap。
- [x] 从 OpenHarmony 根目录构建 `ace_engine`。

**Completion Evidence**

| 证据类型 | 命令/路径 | 期望结果 |
|----------|-----------|----------|
| 构建 | `bash /home/huawei/.codex/skills/ohos-dev-arkui-ace-engine-build/scripts/build_wrapper.sh --product rk3568 -- --export-para PYCACHE_ENABLE:true --build-target ace_engine --ccache --fast-rebuild` | PASS：`rk3568 build success`，`=====build  successful=====`，时间 `2026-07-23 22:19:58`，cost `0:07:29` |
| 代码审查 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` | PASS：queue 成功、queue 失败、complete 三条路径引用释放对称 |

**Handoff Summary**

| 项 | 内容 |
|----|------|
| 允许修改 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp`, `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` |
| 允许新建 | 无 |
| 只读参考 | `spec.md` AC-2.1/AC-2.2，`design.md` ADR-3 和资源所有权矩阵 |
| Spec 摘要 | 已发起 `load()` 后 release 继续安全完成；released 后新调用 `load()` reject `111002`。 |
| Design 摘要 | async context 独立持有 native 引用，front-end binding release 与 async lifetime 分离。 |
| 验证命令 | `bash /home/huawei/.codex/skills/ohos-dev-arkui-ace-engine-build/scripts/build_wrapper.sh --product rk3568 -- --export-para PYCACHE_ENABLE:true --build-target ace_engine --ccache` / 实际 PASS |
| 完成规则 | 不得修改允许范围外的文件；如需扩大范围，先修订 execution-plan；没有 fresh verification evidence 不得声明完成。 |

### TASK-003: Previewer 可执行用例与兼容性审查

| 字段 | 内容 |
|------|------|
| 任务目标 | 在现有 DrawableDescriptor 示例工程中新增可由 previewer 执行的 release 状态页面，并用文件 diff 审查 Static/C API/SDK 声明兼容边界。 |
| AC 映射 | AC-1.1, AC-1.2, AC-1.3, AC-1.4, AC-1.5, AC-1.6, AC-2.1, AC-2.2, AC-3.1, AC-3.2, AC-3.3, AC-3.4, AC-3.5 |
| 前置依赖 | TASK-001 和 TASK-002 已完成。 |
| 非目标 | 不新增 NAPI 单测；不强制新增 XTS；不修改 Static runtime；不修改 C API；不修改 SDK 声明。 |
| 完成判据 | `Index.ets` 可以进入 `DrawableDescriptorReleaseStateTest`；页面展示每个 release 场景的 PASS/FAIL 结果；页面能用公开 ArkTS API 触发 Dynamic 行为；Static/C API/SDK 声明只读文件在 diff 中无修改。 |
| 停止条件 | Previewer 无法创建或加载任一 Dynamic DrawableDescriptor 实例以覆盖核心 AC；停止并回传，改用 Owner 批准的替代验证资产。 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Create | `examples/DrawableDescriptor/entry/src/main/ets/pages/DrawableDescriptorReleaseStateTest.ets` | 新增 release 状态可执行页面。 |
| Modify | `examples/DrawableDescriptor/entry/src/main/ets/pages/Index.ets` | 在 `pages` 数组中加入 release 状态页面入口。 |
| Modify | `examples/DrawableDescriptor/entry/src/main/resources/base/profile/main_pages.json` | 在页面 profile 中加入 release 状态页面路径。 |
| Read | `examples/DrawableDescriptor/entry/src/main/ets/pages/drawableDescriptorStaticTest.ets` | 用于 Static 不变的 previewer 冒烟参考。 |
| Read | `interfaces/native/node/native_node_napi.cpp` | 核验 released Dynamic 对象 unwrap 失败返回参数错误。 |
| Read | `interfaces/native/node/native_node_ani.cpp` | 核验 Static released 对象 nativeObj=0 路径。 |
| Read | `interfaces/native/node/drawable_descriptor.cpp` | 核验 C API Dispose 未修改。 |
| Read | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts` | 核验 Dynamic SDK 声明未修改。 |
| Read | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets` | 核验 Static SDK 声明未修改。 |

**Spec Context**

| 场景 | 页面验证要求 |
|------|--------------|
| release/isReleased | 构造 Base/PixelMap、Layered、Animated、Picture 中可由 previewer 触达的对象，检查 release 前 false、首次 release 后 true、重复 release 后 true 且不崩溃。 |
| 访问型 API | released 后触发 `getPixelMap/getForeground/getBackground/getMask/loadSync/load`，记录同步 throw 或 Promise reject 的 `code === 111002`。 |
| 控制/刷新类 API | released 后触发 `invalidate/setHdrComposition/getAnimationController/setBlendMode`，记录 native 为空无操作返回且不崩溃。 |
| async load | 未 release 状态下发起 `load()`，立即调用 `release()`，记录 Promise 安全完成且对象 `isReleased()` 保持 true。 |
| Static/C API | Static 行为通过既有 static 页面冒烟和文件 diff 审查确认；C API 通过 diff 审查确认。 |

**Design Context**

| 设计项 | 执行要求 |
|--------|----------|
| 验证边界 | 用户确认不补 NAPI 单测、不强制 XTS；previewer 可执行用例作为主要运行验证。 |
| Static 不动 | `frameworks/bridge/arkts_frontend/.../@ohos.arkui.drawableDescriptor.ets` 不进入修改范围。 |
| C API 不动 | `interfaces/native/` 下 C API 只读核验，不修改签名、结构布局、错误码。 |

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| arkui/sdk-api | Must: API AC 映射到真实 ArkTS 工程验证或明确替代审查。 |
| OH-ARCH-API-LEVEL | Must Not: 修改 C API ABI；必须通过 diff 审查确认。 |
| OH-ARCH-COMPONENT-BUILD | Must: 示例文件遵循现有 `examples/DrawableDescriptor` 页面组织方式，不新增系统模块依赖。 |

**Steps**

- [x] 新增 `DrawableDescriptorReleaseStateTest.ets`，使用公开 ArkTS API 和现有 media 资源创建 descriptor。
- [x] 页面内实现可点击执行的场景结果列表，覆盖 `release/isReleased`、重复 release、访问型 API `111002`、控制/刷新类 API 无操作、已发起 load 后 release。
- [x] 修改 `Index.ets` 的 `pages` 数组，加入 `DrawableDescriptorReleaseStateTest`。
- [x] 修改 `main_pages.json` 的 `src` 数组，加入 `pages/DrawableDescriptorReleaseStateTest`。
- [ ] 使用 previewer 打开 `examples/DrawableDescriptor`，执行 `DrawableDescriptorReleaseStateTest` 页面并记录每项 PASS/FAIL。
- [ ] 使用 previewer 打开 `drawableDescriptorStaticTest` 页面做 Static 行为冒烟。
- [x] 审查 diff，确认 Static runtime、C API、SDK 声明文件无本需求修改。

**Completion Evidence**

| 证据类型 | 命令/路径 | 期望结果 |
|----------|-----------|----------|
| Previewer | `examples/DrawableDescriptor` → `DrawableDescriptorReleaseStateTest` | 页面内 AC 场景 PASS |
| Previewer | `examples/DrawableDescriptor` → `drawableDescriptorStaticTest` | Static 既有页面可打开并保持既有结果 |
| 静态检查 | `python3 -m json.tool examples/DrawableDescriptor/entry/src/main/resources/base/profile/main_pages.json` | PASS |
| 格式检查 | `/srv/workspace/openharmony_master_default_20260713175555_huawei_b8da041e5/code/prebuilts/clang/ohos/linux-x86_64/llvm/bin/clang-format --dry-run --Werror interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` | PASS |
| Diff 审查 | `git diff -- interfaces/native/node/drawable_descriptor.cpp interfaces/native/node/native_node_napi.cpp frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets` | PASS：只读边界文件无实现修改 |
| Diff 审查 | `git diff -- api/@ohos.arkui.drawableDescriptor.d.ts zh-cn/api/@ohos.arkui.drawableDescriptor.d.ts kits/@kit.ArkUI.d.ts kits/@kit.ArkUI.static.d.ets`（`code/interface/sdk-js`） | PASS：SDK 声明文件无修改 |
| Previewer | 当前环境 | 未执行：无 GUI/Previewer 运行环境，保留为人工补验项 |

**Handoff Summary**

| 项 | 内容 |
|----|------|
| 允许修改 | `examples/DrawableDescriptor/entry/src/main/ets/pages/DrawableDescriptorReleaseStateTest.ets`, `examples/DrawableDescriptor/entry/src/main/ets/pages/Index.ets`, `examples/DrawableDescriptor/entry/src/main/resources/base/profile/main_pages.json` |
| 允许新建 | `examples/DrawableDescriptor/entry/src/main/ets/pages/DrawableDescriptorReleaseStateTest.ets` |
| 只读参考 | `examples/DrawableDescriptor/entry/src/main/ets/pages/drawableDescriptorStaticTest.ets`, `interfaces/native/node/native_node_napi.cpp`, `interfaces/native/node/native_node_ani.cpp`, `interfaces/native/node/drawable_descriptor.cpp`, `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts`, `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets` |
| Spec 摘要 | Previewer 覆盖 AC-1.1 到 AC-2.2 的 Dynamic 行为；Static/C API AC-3.1 到 AC-3.5 使用 Static 页面冒烟和 diff 审查。 |
| Design 摘要 | 验证资产不替代 NAPI 单测；它是用户批准的 previewer 可执行用例。Static/C API 不修改。 |
| 验证命令 | Previewer 执行 `examples/DrawableDescriptor` 的 release 状态页面和 static 页面；diff 审查确认只读边界不被修改。 |
| 完成规则 | 不得新增 NAPI 单测或 XTS 作为本 Task 必选项；不得修改只读边界文件；没有 fresh verification evidence 不得声明完成。 |

## 生成文件与依赖声明

| 类别 | 结论 |
|------|------|
| generated 文件 | 本计划不手工修改 generated 文件。若实现期发现必须改 static generated 产物，停止并修订 design/plan，先修改生成源。 |
| C API ABI | 本计划不修改 `interfaces/native/drawable_descriptor.h`、`interfaces/native/node/drawable_descriptor.cpp` 的签名、结构布局、错误码或生命周期语义。 |
| BUILD.gn / bundle.json | 预计不修改。新增 previewer 页面复用现有 `examples/DrawableDescriptor` 工程入口，不新增外部系统模块依赖。 |
| SDK 声明 | Dynamic/Static SDK 声明已存在，本计划只读核验，不修改 `interface/sdk-js/api/@ohos.arkui.drawableDescriptor*.d.ts/.d.ets`。 |
| 测试策略 | 不新增 NAPI 单测；不强制新增 XTS；新增 previewer 可执行用例并保留代码审查替代证据。 |

## Plan 自审清单

- [x] 每个 P0/P1 AC 至少映射到一个 Task
- [x] 每个 Task 文件范围明确
- [x] 每个 Task 明确前置依赖、非目标、完成判据和停止条件
- [x] 每个 Task 有验证命令或明确的 previewer/审查验证路径
- [x] Task 粒度形成能力闭环
- [x] 没有 TBD/TODO/占位符
- [x] 没有要求 Agent 自行寻找未列出的上下文
- [x] 交接信息自包含（Handoff Summary 完整）
- [x] 每个 Task 验证在完成时立即执行并记录证据，不在阶段末尾批量补验
- [x] Task 未超过 3000 行上下文阈值，不需要继续拆分
- [x] ArkUI sdk-api 子 profile 的 API 签名、错误语义、运行时实现和验证映射已覆盖
- [x] Host Preview / previewer 适用范围和 N/A 替代审查已映射到 AC 和 Task
- [x] 长期 `specs/` 回灌列为实现完成后的后置项，不阻塞本计划审批
