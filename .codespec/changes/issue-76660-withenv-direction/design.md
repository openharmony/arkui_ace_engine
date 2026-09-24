# 架构设计 — WithEnv direction 与 tree-state 恢复

## 设计元数据

| 字段 | 内容 |
|------|------|
| Design ID | DESIGN-04-03-01-01 |
| 关联需求 | `proposal.md`（REQ-04-03-01-01） |
| 目标 Feature | FEAT-04-03-01-01 |
| 复杂度 | 标准 |
| 目标版本 | 未规划版本 |
| Owner | 未指定（需求记录未提供） |
| 状态 | Reviewing |

## 需求基线

| 项 | 设计约束 |
|----|----------|
| direction | 显式 direction 优先于最近 WithEnv direction；无 WithEnv 时沿用 Auto/全局方向 |
| tree-state | detached/off-main-tree 不再拥有旧 WithEnv 祖先；已初始化变量恢复默认值，再挂树按新祖先链重查 |
| 初始化兼容 | decorator metadata 只表示声明，不能表示变量已经首次读取；普通首次挂树不得主动初始化 |
| 默认值 | direction 默认值为 `Auto`；CustomEnv 保存组件初始化时的本地默认值；fontScale 默认值不在本期定义 |
| 性能范围 | 不引入全局注册表、UINode 常驻计数或大规模缓存协议；O(1) 查值与全部精准通知后置 |

对应行为基线为 `spec.md` AC-1.1～AC-4.6。本文不新增用户可见行为。

## 上下文和现状

### 源码核验事实

| 事实 | 源码证据 |
|------|----------|
| system/custom 显式查值先登记 reader，再沿 parent 链解析最近 owner | `frameworks/core/pipeline_ng/environment_manager.cpp:218`、`:257`、`:280`、`:294` |
| reader→owner 与 owner→reader 使用两组 system/custom 双向索引 | `frameworks/core/pipeline_ng/environment_manager.h:99`、`:107`、`:161` |
| 注销只删除显式 reader record 与 owner reverse edge，不查值、不产生前端默认值 | `frameworks/core/pipeline_ng/environment_manager.cpp:391`、`:399` |
| CustomNode attach 直接发 attached 事件；detach 使用旧 context 先注销，再发 detached 事件 | `frameworks/core/components_ng/pattern/custom/custom_node.cpp:52`、`:66` |
| 挂树先设置 parent，再 AttachContext/onMainTree，最后进入 OnAttach；下树先清 context，OnDetach 后才由移除流程 ResetParent | `frameworks/core/components_ng/base/ui_node.cpp:793`、`:1020`、`:1077`、`:604` |
| JSView 只有存在 relevant decorator 时参与；已有 initialized backing 才在建节点时 Ensure callback | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp:1006`、`:1026` |
| 每次 native find 前调用 Ensure；Ensure 在 callback 已存在时立即返回 | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp:1544`、`:1581`、`:1611` |
| TS tree-state handler 只处理 own backing 已存在的变量；attach 查值，detach 直接用默认值 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_base.ts:569` |
| 合法 direction 查询在 EnvironmentManager 查值 miss 时由 native bridge 返回 `Auto`；CustomEnv 初始化默认值独立保存，不提前创建当前值 backing | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp:114`、`:1611`、`frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts:385`、`:445` |

### 调用链层级分析

| 层 | 模块 | 职责 | 修改类型 |
|----|------|------|----------|
| Public ArkTS | WithEnv/SystemEnvKey/CustomEnvKey | 类型安全的设置与读取入口 | 扩展/签名调整 |
| 状态管理 | Env/CustomEnv decorator、PUV2 view base | 懒初始化、默认值所有权、状态通知 | 修改 |
| Dynamic bridge | JSViewPartialUpdate | 将 native 查值和 tree-state 事件桥接到同一 JSView | 修改 |
| NG 生命周期 | CustomNode/UINode | 在确定的 attach/detach 时点触发恢复 | 修改 |
| Pipeline | EnvironmentManager | 最近祖先解析、显式 reader 双向索引、更新通知和注销 | 修改 |
| Layout | LayoutProperty/PipelineContext | 将 direction env 纳入最终布局方向 | 修改 |

分层方向保持 ArkTS → bridge → NG/pipeline；无跨子系统依赖、无 IPC、无新增 bundle 依赖。

### 适用架构规则

| Rule ID | 适用原因 | 设计结论 | 验证方式 |
|---------|----------|----------|----------|
| OH-ARCH-LAYERING | 跨状态管理、bridge、NG pipeline | 生命周期事实由 native 提供；查询缺省转换由 bridge 完成；detach 本地复位由状态管理完成 | 代码审查 |
| OH-ARCH-API-LEVEL | Public ArkTS API 扩展 | 不新增 C/System API；签名与 `spec.md` 一致 | SDK 编译 |
| ARKUI-LIFECYCLE | 组件上下树与 reparent | attach 只在新 parent/context 就绪后重查；detach 不沿尚未清除的 parent 查询 | 生命周期 unittest |

## 关键设计决策

### ADR-1：当前实现保留父链解析，显式通知使用双向索引

| 方案 | 结论 | 理由 |
|------|------|------|
| 全部查值缓存 O(1) + revision/dirty 协议 | 后置 | 节点移动、key ADD/REMOVE、跨 context 的失效状态空间大，不是本次生命周期修正的必要条件 |
| system/custom 显式 reader 双向索引 + 当前父链解析 | 选定 | 与现有实现一致；UPDATE/REMOVE 可从 owner 精确找到 reader，查值自然重绑最近 owner |
| 全子树 DFS 作为所有显式通知机制 | 不选 | 显式 reader 已有索引；仅 key ADD 等需要发现潜在 reader 的场景保留范围遍历 |

实际结构：

```text
systemExplicitReaders_ / customExplicitReaders_
  readerId -> weak reader + { key -> weak owner WithEnv }

systemExplicitScopes_ / customExplicitScopes_
  ownerId -> weak owner + { key -> readerId set }
```

`UnregisterExplicitReader` 对 system/custom 各执行一次：验证 reader id 仍属于同一个 live node，按 record 中每个 key 从 scope reverse edge 删除 readerId，最后删除 reader record。它不读取值、不调用状态管理，也不构造默认值。

system implicit direction/layout 消费者仍采用 FULL 子树通知并由内层同 key WithEnv 截断；这是与 explicit reader 不同的通路。PRECISE implicit index 仍为预留能力，不在本期交付。

### ADR-2：direction 按“显式 > env > Auto/全局”解析

`LayoutProperty` 保持显式 direction 为第一优先级；仅在显式值缺失时，通过当前 PipelineContext 查询最近 WithEnv direction；查不到则进入既有 Auto/全局解析。这样不修改 `TextDirection` 枚举，也不要求每个节点常驻 env 字段。

动态 bridge 将 native direction 表示转换为 `Ltr/Rtl/Auto` 可观察值；Public API 的类型契约仍由 `WritableSystemEnvKey<Direction>` 定义。

### ADR-3：生命周期用“backing 是否存在”识别已消费变量

metadata 与 value-initialized 是两个事实：

- metadata：该组件声明过 relevant Env/CustomEnv；
- own backing：该变量已经走过 getter 赋值；即使当前值是 `false`、`0`、空字符串或 `undefined`，生命周期回调也应视为已经消费过该变量。

因此 tree-state handler 对 direct-query Env 和 CustomEnv 使用实例 own-property 判断是否需要更新。`@Env` getter 本身仍统一保留原有 `if (!this[storeProp])` 初始化条件，direct-query 只决定调用 native `findEnvValueByKey()` 还是原有 `EnvV2.registerEnv()`，不额外引入 TS 默认值兜底或初始化分支。CustomEnv 字段初始化只写独立的 local-default backing，不创建 current-value backing；首次 getter 才查 WithEnv 并写 current backing。

这避免额外的 `firstAttach`/`initialized` 聚合标志，并保证生命周期处理不会因 falsey backing 漏掉已经消费过的变量；它不改变 `@Env` getter 对 falsey 值可能再次查值的既有行为。

### ADR-4：callback 的有无表示聚合消费关系

比较方案：

| 方案 | 结论 | 原因 |
|------|------|------|
| attach/detach 总是遍历声明 metadata | 否决 | 首次 attach 早于首次 Render，会把未读变量从懒初始化改成主动初始化 |
| 单独保存 firstAttach/hasInitialized 标志 | 否决 | callback 与标志形成两份需同步的状态，reuse/Destroy 更易出错 |
| 按需 Ensure tree-state callback | 选定 | callback 缺失直接表示当前 JSView 尚未消费 relevant env；已有消费统一走同一 attach/detach 路径 |

callback 安装入口只有两类：

1. 创建 CustomNode 时，若实例已存在 initialized backing，则立即 Ensure；
2. 创建后首次或后续 `findEnvValueByKey` / `findCustomValueByKey` 在尝试取得 EnvironmentManager 前 Ensure。

Ensure 每次 find 都调用是为了覆盖“建节点后才首次读取”和“离屏首次读取”两个时机。重复调用只做 CustomNode cast 与 `HasOnEnvTreeStateChangeFunc()` 检查，callback 已存在时立即返回；它不触发 tree-state handler，也不产生第二次状态刷新。同一组件的 key A 首次安装 callback 后，紧接着 key B 的 Ensure 不会调用前端刷新。

后端 value-update callback 可以在建节点时注册，因为真正投递仍由 EnvironmentManager 的 reader edge 决定；tree-state callback 不同，生命周期会直接调用它，所以必须等到至少一个变量实际初始化后才安装。

### ADR-5：显式 attached 事件，attach 重查、detach 复位

tree-state callback 携带 `isAttached`，不靠 context 是否为空猜测生命周期：

- attach：只遍历已初始化变量，查询当前祖先链；miss 使用该变量默认值；
- detach：只遍历已初始化变量，直接写默认值，不执行 native 查询；
- system 与 custom 分两个 forEach，保持各自 key/filter/default 规则；
- 每个实际变化执行 `fireChange` 与 decorated Watch，两个循环完成后最多调用一次 dirty flush。

正常 direction 查询的默认值由 native bridge 的 `MakeSystemEnvValue()` 统一产生：manager 查不到 owner/value 时返回 `Auto`，TS getter 直接保存 native 结果。tree-state handler 使用状态管理 helper 表达 lifecycle default：detach 不查询并直接得到 direction=`Auto`；attach 查询仅在 native 异常返回 `undefined` 时防御性兜底。没有已批准默认值的其他 direct-query system key 仍返回 `undefined`，本文不为 fontScale 定义新默认值。CustomEnv 从独立 local-default backing 恢复，WithEnv 覆盖不得修改该 backing。

### ADR-6：JS handler 所有权跟随 JSView，CustomNode 只持弱转发

JSView 成员保存 JS function wrapper，并在 Destroy/析构时清空，以遵循既有 C++→JS 引用链清理约定。CustomNode 仅持捕获 JSView WeakPtr 的 native callback；reuse 创建新 view 时先 Reset 旧 callback，再按新实例 backing 状态决定是否 Ensure。

该决策吸收 PR #87514 关于引用链的审查意见，不引入 CustomNode 对 JS function 的强持有。

## 生命周期时序

### 普通首次创建且变量未读

```text
组件字段初始化
  └─ CustomEnv 仅保存 local default
CreateViewNode
  ├─ 注册 value-update bridge（仅有对应 metadata 时）
  ├─ Reset recycle node 的旧 tree-state callback
  └─ initialized backing 不存在：不 Ensure
MountToParent
  ├─ SetParent(newParent)
  ├─ AttachContext(newContext)
  ├─ onMainTree = true
  └─ OnAttachToMainTree：callback 为空，无前端处理
首次 Render/getter
  ├─ Ensure callback
  └─ 查询当前 parent 链并创建 backing/reader edge
```

结果：初始化阶段相对旧行为不新增 env 查值、Watch 或 dirty 更新，对应 AC-4.3。

### 离屏首次读取后首次挂树

```text
getter -> native find
  ├─ Ensure callback（先于 manager 获取）
  ├─ attached context 为空时，GetContext 回退到 ContainerScope 对应的当前 PipelineContext
  ├─ 无可解析的 owner/value，native MakeSystemEnvValue(direction, nullopt) 返回 Auto
  └─ backing 直接写 native 返回值
后续 AddChild
  ├─ SetParent -> AttachContext -> onMainTree=true
  └─ callback(true) -> 只重查已存在 backing -> 写最近 WithEnv 值并建 reader edge
```

结果：即使离屏首次查询时没有 attached context/WithEnv owner，也不会错过第一次 attach 校正，对应 AC-4.4。

### 从 A 下树并挂入 B

```text
Remove from A
  UINode::DetachFromMainTree
    1. onMainTree=false
    2. save oldContext
    3. DetachContext(false)          // node context 已清空
    4. CustomNode::OnDetachFromMainTree(oldContext)
       a. oldManager.UnregisterExplicitReader(node)
       b. callback(false)
          - system/custom 已初始化 backing 恢复默认值
          - 逐变量 fireChange/Watch，最后一次 dirty flush
    5. 递归 detach 子节点
  UINode::OnRemoveFromParent 后半段
    6. ResetParent()                 // 旧 parent 此时才清除

Add to B
  1. B.children.insert(node)
  2. SetParent(B)
  3. AttachContext(newContext)
  4. onMainTree=true
  5. callback(true)
     - 查询已初始化 key
     - 写 B 最近祖先值
     - 在新 manager 建 reader/owner edge
```

顺序保证 detach 的正常 handler 不沿旧 parent 查值，attach 查询时新 parent/context 已就绪。同 manager 与跨 PipelineContext reparent 共用该协议。

## 更新通知与多 key 行为

value 更新和 tree-state 更新是两条独立通路：

- WithEnv key UPDATE/REMOVE：EnvironmentManager 通过 owner reverse index 定位已登记 reader并派发携带 key/value 的通知；
- key ADD：为发现原先 miss 但已登记该 key 的 reader，需要在该作用域下重绑候选 reader；
- tree-state：不携带某一个 key 的 value，因为 detach 需要对本组件全部已初始化 relevant key 复位，attach 需要按新 parent 链逐 key 重建 owner。

同一组件存在 key A、key B 时，A 的首次 find 安装 callback；B 的 find 只命中 Ensure 快路径，不会触发 callback。真正 attach/detach 只触发一次 callback，内部逐 key 处理，变量 Watch 仍分别触发，但 dirty flush 收拢一次。

## API 签名、Kit 与权限

| API 签名 | 类型 | Kit | 声明/实现位置 | 权限/SysCap |
|----------|------|-----|---------------|-------------|
| `WritableEnvKey.DIRECTION: WritableSystemEnvKey<Direction>` | Public ArkTS | ArkUI | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/system_env.ts` | 无 |
| `WithEnvAttribute.env<T>(key, value)` | Public ArkTS | ArkUI | `frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts` | 无 |
| `CustomEnvKey.create<T>()` / `customEnv<T>()` | Public ArkTS | ArkUI | 同上及 `env_base/customEnv_key.ts` | 无 |
| `Env(SystemEnvKey<T> | SystemProperties)` / `CustomEnv(CustomEnvKey<T>)` | Public ArkTS | ArkUI state management | `state_mgmt/src/lib/v2/v2_decorators.ts` | 无 |

无 C API、InnerAPI、错误码、权限或 SysCap 变更。

## 构建系统影响

- 本轮 lifecycle 修改不新增源文件、不新增依赖、不修改 `bundle.json`。
- SDK/API 的既有构建接线属于此前 direction/SystemEnvKey 交付范围。
- 不手工修改 generated 目录。

## 测试性设计

| 测试层级 | 目标 | 验证方式 |
|----------|------|----------|
| C++ pipeline unittest | 双向索引、注销顺序、同/跨 context reparent、callback 安装前后生命周期 | `environment_manager_test_ng.cpp` 定向 gtest |
| ArkTS/HAP | direction/CustomEnv 默认值、Watch、多个 key、离屏首次读取 | execution-plan 的端到端场景矩阵 |
| 组件 unittest | direction 优先级、嵌套覆盖、key ADD/UPDATE/REMOVE | 现有 with_env/environment_manager 测试扩展 |
| SpecTest | N/A | 当前没有稳定 Inspector 断言覆盖 decorator backing 与 Watch；由 C++ + ArkTS/HAP 替代 |

## 正确性边界和开放风险

| 项 | 影响 | 当前保护 | 后续处理 |
|----|------|----------|----------|
| detach callback 与 ResetParent 存在时差 | detach 期间 old parent 仍可见；`UINode::GetContext()` 又会在 attached context 为空时回退当前 PipelineContext，因此 native 重查可能得到旧 owner 并重新注册 | 当前 TS handler detach 不查 native，direction 先写入 truthy 的 `Auto`，正常 getter/Watch 不会因本次复位再次查询 | EnvironmentManager 的 public find/register 尚未统一拒绝 off-main-tree reader。直接调用 native find、返回 `undefined` 的 key 或其他重入入口仍需遵守“off-main-tree 不得解析/注册 WithEnv”；后续应将其建立为底层统一不变量并补测试 |
| on-main-tree 直接 SetParent | 不经过真实 detach/attach 时 implicit dirty 与 explicit 重绑均可能缺失 | 支持路径要求 remove/add 触发生命周期 | 审计并禁止此入口，或为合法入口补齐完整生命周期；不能仅依赖 explicit reader count |
| key-remove 的动态前端缓存语义 | 当前 value-update 对 undefined 的既有处理与 detach 默认值不同 | 生命周期修正只处理明确 detached 事件 | 若要改 key-remove 可观察语义，单独修订 proposal/spec，不夹带在本次 detach 修正中 |
| fontScale | native miss 仍返回 `undefined`，且原有 truthy getter 条件可能使其再次查询；本期没有其默认值规格 | tree-state helper 仅为 direction 返回 `Auto`，getter 不增加 TS fallback | 不新增 fontScale 默认值或初始化次数承诺；另立需求后定义 |
| 完整验证未执行 | 不能宣称可合入 | 代码和测试已准备 | 在完整 OpenHarmony 构建树运行定向 native 测试与 ArkTS/HAP 场景 |

## 设计审批

- [x] 设计行为均可追溯到 spec AC
- [x] 生命周期入口、parent/context 先后顺序和默认值所有权已明确
- [x] 方案对比包含首次标志、统一重查和全局索引等备选
- [x] 无新增公共 API/ABI、依赖或 generated 文件
- [x] fontScale 默认值明确排除
- [ ] native 定向测试与 ArkTS/HAP 验证完成

**结论：** Reviewing；实现路径可审查，验证门禁未闭合。
