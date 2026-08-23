# 执行计划 — WithEnv direction 与 tree-state 恢复

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-04-03-01-01 |
| 关联 Feature/Bug | FEAT-04-03-01-01 / issue 76660 |
| 关联文档 | `proposal.md`、`spec.md`、`design.md` |
| 复杂度 | 标准 |
| 状态 | ReadyForReview（实现已存在，验证未闭合） |
| Owner | 未指定（需求记录未提供） |

## 输入状态

| 输入 | 路径 | 当前状态 |
|------|------|----------|
| Requirement | `proposal.md` | Baselined；生命周期补充已记录 |
| Spec | `spec.md` | Review |
| Design | `design.md` | Reviewing |

在 Spec/Design 审批和 fresh verification 完成前，不把当前实现标记为可交付。

## 首批实现边界

**必须实现：** direction 局部默认值、显式覆盖、最近祖先规则、显式 reader 双向索引、已初始化 Env/CustomEnv 的 detach 默认值与 attach 重查、懒初始化兼容、旧 reader 注销。

**后置：** O(1) 解析缓存、全部 implicit 精准通知、dump、fontScale 用户可见默认值、TypeScript 单测框架扩建。

**不建议延后：** 同/跨 PipelineContext reparent native 测试与至少一个真实 ArkTS/HAP 同实例往返场景；缺少它们不能关闭 GC。

## 受影响文件全量清单

| 层 | 文件路径 | 修改类型 | 职责 |
|----|----------|----------|------|
| CodeSpec | `.codespec/changes/issue-76660-withenv-direction/manifest.md` | 修改 | profile、状态与归并说明 |
| CodeSpec | `.codespec/changes/issue-76660-withenv-direction/proposal.md` | 修改 | 固化生命周期和默认值补充基线 |
| CodeSpec | `.codespec/changes/issue-76660-withenv-direction/spec.md` | 重写 | 只保留可观察行为、统一规则和 AC |
| CodeSpec | `.codespec/changes/issue-76660-withenv-direction/design.md` | 重写 | 实现结构、精确时序、方案取舍和风险 |
| CodeSpec | `.codespec/changes/issue-76660-withenv-direction/execution-plan.md` | 重写 | Task、文件、AC 与验证矩阵 |
| CodeSpec | `.codespec/changes/issue-76660-withenv-direction/review.md` | 修改 | 规范符合性、代码质量与 GC 结论 |
| Evidence | `.codespec/changes/issue-76660-withenv-direction/evidence/reviews/spec-compliance.md` | 修改 | 逐 AC 机器事实与缺口 |
| 临时文档 | `.codespec/changes/issue-76660-withenv-direction/reparent-analysis-and-design.md` | 删除 | 有效内容归并到 design |
| 临时文档 | `.codespec/changes/issue-76660-withenv-direction/reparent-single-page-ets-cases.md` | 删除 | 场景矩阵归并到本计划，不保留 900+ 行未执行样例代码 |
| Dynamic bridge | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp` | 修改 | callback 准备/Ensure、native 查值桥接、引用链清理 |
| Dynamic bridge | `frameworks/bridge/declarative_frontend/jsview/js_view.h` | 修改 | tree-state handler 成员与 Ensure 声明 |
| State management | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_base.ts` | 修改 | 已初始化变量 attach 重查、detach 默认值复位、单次 dirty flush |
| State management | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_change_observation.ts` | 修改 | CustomEnv local-default backing 前缀 |
| State management | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts` | 修改 | 保留 Env 原初始化条件与查询分流；保存 CustomEnv 本地默认值 |
| State management | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_env.ts` | 修改 | tree-state lifecycle 的 direction fallback（detach 直接复位，attach 防御兜底） |
| NG lifecycle | `frameworks/core/components_ng/pattern/custom/custom_node.cpp` | 修改 | attach/detach 事件与 reader 注销顺序 |
| NG lifecycle | `frameworks/core/components_ng/pattern/custom/custom_node.h` | 修改 | tree-state callback Set/Has/Reset |
| Pipeline | `frameworks/core/pipeline_ng/environment_manager.cpp` | 修改 | 显式 reader 注销 |
| Pipeline | `frameworks/core/pipeline_ng/environment_manager.h` | 修改 | 生命周期注销入口 |
| Test mock | `test/mock/frameworks/core/components_ng/pattern/custom/mock_custom_node.cpp` | 修改 | 与产品生命周期时序保持一致 |
| Unit test | `test/unittest/core/pipeline/environment_manager_test_ng.cpp` | 修改 | reparent、跨 context、callback 激活和清理 |

产品代码不新增公共 C/C++ API/ABI、依赖或 generated 文件。

校验器使用以下列表作为同一范围的机器可读索引：

- `.codespec/changes/issue-76660-withenv-direction/manifest.md`
- `.codespec/changes/issue-76660-withenv-direction/proposal.md`
- `.codespec/changes/issue-76660-withenv-direction/spec.md`
- `.codespec/changes/issue-76660-withenv-direction/design.md`
- `.codespec/changes/issue-76660-withenv-direction/execution-plan.md`
- `.codespec/changes/issue-76660-withenv-direction/review.md`
- `.codespec/changes/issue-76660-withenv-direction/evidence/reviews/spec-compliance.md`
- `.codespec/changes/issue-76660-withenv-direction/reparent-analysis-and-design.md`（删除）
- `.codespec/changes/issue-76660-withenv-direction/reparent-single-page-ets-cases.md`（删除）
- `frameworks/bridge/declarative_frontend/jsview/js_view.cpp`
- `frameworks/bridge/declarative_frontend/jsview/js_view.h`
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_base.ts`
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_change_observation.ts`
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts`
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_env.ts`
- `frameworks/core/components_ng/pattern/custom/custom_node.cpp`
- `frameworks/core/components_ng/pattern/custom/custom_node.h`
- `frameworks/core/pipeline_ng/environment_manager.cpp`
- `frameworks/core/pipeline_ng/environment_manager.h`
- `test/mock/frameworks/core/components_ng/pattern/custom/mock_custom_node.cpp`
- `test/unittest/core/pipeline/environment_manager_test_ng.cpp`

## AC 到 Task 追溯

| AC | Task | 验证方式 | 当前覆盖 |
|----|------|----------|----------|
| AC-1.1～AC-1.4 | TASK-001 | direction/layout 组件 unittest + ArkTS 页面 | 实现存在；targeted 执行待补 |
| AC-2.1～AC-2.4 | TASK-001, TASK-002 | bridge/ArkTS/HAP | 实现审查完成；端到端待补 |
| AC-3.1～AC-3.4 | TASK-001 | direction 优先级、嵌套、焦点回归 | targeted 执行待补 |
| AC-4.1～AC-4.5 | TASK-002 | lifecycle unittest + 同实例 ArkTS/HAP reparent | C++ 用例已写，未运行；ArkTS/HAP 待执行 |
| AC-4.6 | TASK-002, TASK-003 | 多 key Watch/dirty 观察 | 代码审查可见单次 dirty flush；运行证据待补 |

## 阶段计划

| 阶段 | 目标 | Task | 结束门槛 | 最小验证 |
|------|------|------|----------|----------|
| Phase-1 | direction 与显式 reader 主链 | TASK-001 | 设置、查询、更新、嵌套和显式覆盖可验证 | component/pipeline unittest |
| Phase-2 | tree-state 与 reparent 恢复 | TASK-002 | native 时序、旧索引清理、默认值与懒初始化符合 spec | 4 个定向 gtest + ArkTS/HAP 主场景 |
| Phase-3 | 文档归并与交付门禁 | TASK-003 | 逐 AC 证据完整，无虚假 PASS | `git diff --check` + `ohos-sdd validate` + review |

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证 |
|---------|------|----------|---------|----------|----------|------|
| TASK-001 | WithEnv direction 与 reader 主链 | WithEnv/layout/EnvironmentManager/SDK/bridge 既有改动 | AC-1.*, AC-2.*, AC-3.* | 无 | direction 和最近祖先规则可验收 | component/pipeline unittest、SDK 编译 |
| TASK-002 | 生命周期恢复与默认值所有权 | JSView、state management、CustomNode、EnvironmentManager、pipeline test | AC-2.*, AC-4.* | TASK-001 | 未读无副作用；已读 detach default、attach 新值、旧 edge 清空 | 定向 gtest + ArkTS/HAP |
| TASK-003 | 规格归并与 GC 证据 | `.codespec/changes/issue-76660-withenv-direction/**` | 全部 | TASK-001, TASK-002 | 临时文档内容归位、逐 AC 结论真实、验证缺口明确 | diff/SDD validation/review |

## TASK-001：direction 与显式 reader 主链

**非目标：** 不把缓存 O(1)、全部通知精准化或 fontScale 默认值作为完成条件。

**完成判据：**

- `.env(WritableEnvKey.DIRECTION, value)` 可从 ArkTS 到 native 设置；
- 最终 direction 优先级为 explicit > nearest WithEnv > Auto/global；
- explicit `@Env`/`@CustomEnv` reader 可登记当前 owner，UPDATE/REMOVE/ADD 后保持最近作用域规则；
- API 声明与运行时签名一致，SDK 编译通过。

**验证命令（完整 OpenHarmony 根目录）：**

```bash
./build.sh --product-name ohos-sdk --build-target ace_engine
./build.sh --product-name rk3568 --build-target unittest
```

## TASK-002：tree-state 生命周期恢复

**Required rules：**

- metadata 不等于 initialized backing；
- callback 缺失表示尚无 relevant env 消费，不能补 first-attach 标志；
- find 入口先 Ensure callback，再尝试获取 node context/manager；
- Env getter 保留原 truthy 初始化条件；direct-query 只选择 native find 路径，不增加 TS fallback；
- 正常 direction 查询 miss 由 native bridge 返回 `Auto`；状态管理 helper 服务于 tree-state lifecycle fallback，detach 直接复位、attach 防御兜底；
- detach 顺序为清 context → old manager 注销 → 默认值复位 → 后续 ResetParent；
- attach 顺序为 SetParent → AttachContext/onMainTree → 重查已初始化 key；
- CustomEnv local default 独立保存；direction=`Auto`；fontScale 无新增默认值；
- system/custom 两个循环分别处理，所有变量完成后最多一次 dirty flush。

**停止条件：**

- 发现合法 on-main-tree direct SetParent 不经过 detach/attach；
- 需要新增公共 API/ABI、全局注册表、UINode 常驻字段或依赖；
- native 测试证明 detach callback 前 reader 未注销，或 attach callback 时新 parent/context 未就绪。

**native 定向测试：**

```bash
./out/rk3568/tests/ace_engine/unittest/core/pipeline/environment_manager_test_ng \
  --gtest_filter='PipelineContextTestNg.EnvironmentManagerExplicitReaderReparent001:PipelineContextTestNg.EnvironmentManagerExplicitReaderCrossContextReparent001:PipelineContextTestNg.CustomNodeEnvTreeStateCallbackActivationOffTree001:PipelineContextTestNg.CustomNodeEnvTreeStateCallbackActivationOnTree001'
```

若产物路径随构建目标变化，应从 `test/unittest/core/pipeline/BUILD.gn` 的目标和实际 out 目录确认，不得把“文件已写”当成“测试已通过”。

## ArkTS/HAP 验证矩阵

原 `reparent-single-page-ets-cases.md` 的 6 份长代码草稿只保留可复用的场景设计。正式验证应在当前 SDK 上重建最小页面并记录源码、设备、构建和运行结果；未经执行的示例代码不作为证据。

| Case ID | 场景 | 操作 | 核心断言 | 关联 AC | 优先级 |
|---------|------|------|----------|---------|--------|
| HAP-1 | 同一 BuilderNode/CustomNode 在 LTR WithEnv A 与 RTL WithEnv B 间移动 | remove A → detached → append B，往返 20 次 | instance 不变；A=Ltr；detach=Auto/local default；B=Rtl；旧 A 后续更新无效 | AC-4.1, AC-4.2 | 必须 |
| HAP-2 | 离屏 BuilderNode 首次读取 | detached 时首次读 direction/custom，再挂 A | 离屏返回 Auto/local default；首次 attach 校正为 A | AC-4.4 | 必须 |
| HAP-3 | 声明但未读 | 首次 attach、detach、reattach 均不读取变量 | 无 Watch、无绑定 UI 更新、无提前初始化 | AC-4.3 | 必须 |
| HAP-4 | 多 key + Watch | 同组件读取 direction 和两个 CustomEnv key 后 detach/attach | 每个实际变化 Watch 一次；无重复 tree-state 回调；UI dirty 集中提交一次 | AC-4.6 | 必须 |
| HAP-5 | If/Else + ContentSlot/NodeContent | 分支切换导致同一内容节点离开 A 并进入 B | 同一 instance 按 HAP-1 顺序变化 | AC-4.1, AC-4.2 | 建议 |
| HAP-6 | ForEach stable-key reorder | 重排后更新外层 WithEnv | 存活 reader 均接收新值，key→instance 符合预期 | AC-2.2 | 补充 |
| HAP-7 | Repeat virtual reuse/cache | 滚动、复用、重新激活后更新外层 WithEnv | 可见及重新激活 reader 不保留旧值 | AC-2.2, AC-4.2 | 补充 |
| HAP-8 | LazyForEach move/cache | move/cache/active 切换后更新外层 WithEnv | 当前与重新激活 reader 使用有效作用域值 | AC-2.2, AC-4.2 | 补充 |
| HAP-9 | Native C API 同一 Row reparent | 同一 handle 在 LTR/RTL scope 间移动 | START/END 的隐式 layout direction 随 scope 变化 | AC-1.*, AC-3.* | 补充；不替代 explicit decorator 测试 |

每个 HAP case 记录：SDK/设备版本、页面源码提交、操作次数、instance/key 对照、Watch 日志、崩溃与旧 owner 更新结果。HAP-1～HAP-4 未通过时 GC 必须保持 ChangesRequested。

## TASK-003：文档与证据归并

**Steps：**

- [x] 将提交 `46849cd852ab` 的生命周期可观察行为移入 spec；
- [x] 将 callback/reader 职责、精确时序、方案取舍与父链时差风险移入 design；
- [x] 将 6 类 ETS 草稿压缩为可执行验证矩阵，删除未执行的大段样例代码；
- [x] review 与 evidence 区分“实现审查 PASS”和“运行验证 BLOCKED”；
- [x] 运行 fresh 文档校验并记录结果；
- [ ] 在完整 OpenHarmony 环境补齐 native/HAP 证据。

## Plan 自审清单

- [x] 每个 spec AC 映射到至少一个 Task
- [x] 产品、测试、文档和删除文件范围完整列出
- [x] 每个 Task 有非目标、完成判据或停止条件
- [x] fontScale、缓存、dump 未混入本期完成条件
- [x] SpecTest N/A 有替代验证，不用 Inspector 覆盖不了的内部状态冒充 SpecTest
- [x] 未执行的 ETS 草稿不作为 PASS 证据
- [ ] fresh native 与 ArkTS/HAP 运行证据完成
