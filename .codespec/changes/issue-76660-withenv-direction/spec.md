# WithEnv 环境变量 direction 支持与框架适配

> ArkUI 测试设计 Spec 规范模板 | 版本: v0.2  
> 基于 `ArkUI_SpecV0.2.md` 填充，规格口径以当前 ace_engine 源码事实和 `.codespec/changes/issue-76660-withenv-direction/` 产物为准。

---

## 元信息

| 字段 | 内容 |
|------|------|
| 需求编号 | REQ-04-03-01-01 |
| 需求名称 | WithEnv 环境变量框架新增 direction 支持与内部框架适配 |
| 特性编号 | FEAT-04-03-01-01 |
| 需求来源 | OpenHarmony ArkUI issue 76660 |
| 提出人 | 需求 Owner 未在当前产物中明确 |
| 优先级 | P0 |
| 目标版本 | 未确认，沿用 `manifest.target_release` 当前未定状态 |
| SIG归属 | SIG_ArkUI |
| 状态 | Draft |
| 复杂度 | 标准 |
| 创建日期 | 2025-05-25 |
| 最后更新 | 2026-06-17 |

---

## 一、需求目标与规格

### 1.1 US-1：通过 WithEnv 设置子树默认 direction

**角色：** ArkTS 应用开发者  
**Want：** 通过 WithEnv 容器的 `.env(WritableEnvKey.DIRECTION, value)` 设置子树默认布局方向  
**以便：** 在 RTL/LTR 场景中统一控制局部 UI 子树的默认方向  
**优先级：** P0

#### AC验收标准

| AC编号 | 验收标准（Given/WHEN/THEN格式） | 类型 |
|--------|----------------------------------|------|
| AC-1.1 | Given 页面存在 WithEnv 容器且后代节点未显式设置 `.direction()`，WHEN WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)`，THEN 后代节点通过布局方向解析得到 `Direction.Rtl` | 正常 |
| AC-1.2 | Given 页面存在 WithEnv 容器且后代节点未显式设置 `.direction()`，WHEN WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Ltr)`，THEN 后代节点通过布局方向解析得到 `Direction.Ltr` | 正常 |
| AC-1.3 | Given 页面存在 WithEnv 容器且后代节点未显式设置 `.direction()`，WHEN WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Auto)`，THEN 后代节点的 direction 结果保持 `Direction.Auto`，非 Auto 解析继续按全局 RTL/LTR 规则处理 | 边界 |
| AC-1.4 | Given 后代节点没有 WithEnv 祖先或祖先 WithEnv 未设置 direction key，WHEN 节点解析 layout direction，THEN 节点不获得 env direction，继续使用原有 Auto/全局方向解析路径 | 边界 |

---

### 1.2 US-2：通过 @Env 获取当前 direction

**角色：** ArkTS 自定义组件开发者  
**Want：** 使用 `@Env(WritableEnvKey.DIRECTION)` 在组件变量中读取当前上下文 direction  
**以便：** 组件逻辑能够根据局部方向执行条件渲染或状态更新  
**优先级：** P0

#### AC验收标准

| AC编号 | 验收标准（Given/WHEN/THEN格式） | 类型 |
|--------|----------------------------------|------|
| AC-2.1 | Given 动态前端自定义组件位于设置了 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)` 的 WithEnv 子树内，WHEN 组件声明 `@Env(WritableEnvKey.DIRECTION) directionValue: string = 'Auto'` 并首次读取变量，THEN `directionValue` 的当前 native 可观测值为 `'Rtl'` | 正常 |
| AC-2.2 | Given 自定义组件已通过 `@Env(WritableEnvKey.DIRECTION)` 读取祖先 WithEnv 的 direction，且 Text 组件绑定展示该变量，WHEN 祖先 WithEnv 将 direction 从 `Direction.Ltr` 更新为 `Direction.Rtl`，THEN 绑定 Text 的可观测内容从 `'Ltr'` 更新为 `'Rtl'` | 正常 |
| AC-2.3 | Given 自定义组件声明 `@Env(WritableEnvKey.DIRECTION) directionValue: string = 'Auto'` 且没有定义 direction 的 WithEnv 祖先，WHEN 组件首次读取变量，THEN `directionValue` 保持组件声明时的默认值 `'Auto'` | 边界 |
| AC-2.4 | Given 组件内代码尝试给 `@Env(WritableEnvKey.DIRECTION)` 装饰变量赋值，WHEN 执行赋值操作，THEN 运行时抛出只读变量错误，组件不能通过该变量反向修改 env 值 | 异常 |

---

### 1.3 US-3：显式 direction 覆盖 env direction

**角色：** ArkTS 应用开发者  
**Want：** 在局部节点上继续使用 `.direction()` 显式覆盖 WithEnv 默认方向  
**以便：** 在统一设置子树方向时仍可精确控制特殊节点  
**优先级：** P0

#### AC验收标准

| AC编号 | 验收标准（Given/WHEN/THEN格式） | 类型 |
|--------|----------------------------------|------|
| AC-3.1 | Given WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)`，且后代节点显式设置 `.direction(Direction.Ltr)`，WHEN 后代节点解析布局方向，THEN 使用显式值 `Direction.Ltr` | 正常 |
| AC-3.2 | Given WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Ltr)`，且后代节点显式设置 `.direction(Direction.Rtl)`，WHEN 后代节点解析布局方向，THEN 使用显式值 `Direction.Rtl` | 正常 |
| AC-3.3 | Given WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)` 且子树中存在多个可获焦节点，WHEN 执行线性焦点遍历，THEN 焦点顺序按节点解析后的 RTL 方向参与计算 | 回归 |

---

### 1.4 US-4：WithEnv 嵌套和 CustomEnv 兼容

**角色：** ArkUI 框架开发者  
**Want：** 系统 env 与已有 custom env 在 WithEnv 嵌套、更新、移除场景下保持明确规则  
**以便：** direction 接入不破坏已有 WithEnv 使用方式，并为后续系统 env 扩展保留一致模型  
**优先级：** P1

#### AC验收标准

| AC编号 | 验收标准（Given/WHEN/THEN格式） | 类型 |
|--------|----------------------------------|------|
| AC-4.1 | Given 外层 WithEnv 设置 direction 为 `Direction.Ltr`，内层 WithEnv 设置 direction 为 `Direction.Rtl`，WHEN 内层后代节点查询 direction env，THEN 返回最近祖先内层 WithEnv 的 `Direction.Rtl` | 正常 |
| AC-4.2 | Given 外层 WithEnv 与内层 WithEnv 均设置 direction key，WHEN 外层 WithEnv 更新同一 key，THEN 内层 WithEnv 子树中依赖内层 key 的组件不接收外层同 key 更新 | 边界 |
| AC-4.3 | Given WithEnv 已设置 direction key 且后代节点未显式设置 `.direction()`，WHEN 该 key 被移除或设置值为 undefined，THEN 后代布局方向查询不到 env 值并回退到原有 Auto/全局方向解析路径 | 边界 |
| AC-4.4 | Given 自定义组件已通过 `@Env(WritableEnvKey.DIRECTION)` 读取并缓存祖先 direction，WHEN 祖先 WithEnv 移除 direction key 且系统 env 更新值为空，THEN 当前动态前端不覆盖已缓存变量值；后续重新创建组件时无祖先值场景按 AC-2.3 处理 | 边界 |
| AC-4.5 | Given custom env 使用 `CustomEnvKey<string>`，WithEnv 设置 `.customEnv(key, 'dark')` 且后代组件通过 `@CustomEnv(key)` 绑定 Text 展示该值，WHEN WithEnv 将该 key 更新为 `'light'`，THEN 绑定 Text 的可观测内容从 `'dark'` 更新为 `'light'` | 回归 |

---

## 二、规则定义

### 2.1 功能规则（FR）

| 规则ID | 描述 | 触发条件 | 作用对象 | 关联AC |
|--------|------|----------|----------|--------|
| FR-1.1 | WithEnv 支持通过 `.env(WritableEnvKey.DIRECTION, value)` 设置 direction 系统环境变量 | 开发者在 WithEnvAttribute 上调用 `.env()`，key 为 `WritableEnvKey.DIRECTION`，value 为 `Direction.Ltr`、`Direction.Rtl` 或 `Direction.Auto` | WithEnv 子树 | AC-1.1, AC-1.2, AC-1.3 |
| FR-1.2 | 未显式设置 `.direction()` 的后代节点可从最近祖先 WithEnv 读取 direction env 作为默认 direction | 节点解析 layout direction 且自身没有显式 direction 值 | 后代 FrameNode/LayoutProperty | AC-1.1, AC-1.2, AC-1.4, AC-4.1 |
| FR-2.1 | `@Env(WritableEnvKey.DIRECTION)` 支持读取当前上下文 direction env 值 | 自定义组件声明并读取 `@Env(WritableEnvKey.DIRECTION)` 变量 | 自定义组件状态变量 | AC-2.1, AC-2.3 |
| FR-2.2 | direction env 变化后通知已依赖该 key 的自定义组件刷新并重新读取 | WithEnv 中 direction key 的值发生设置或移除 | 已注册依赖的 CustomNode | AC-2.2, AC-4.3, AC-4.4 |
| FR-3.1 | 显式 `.direction()` 优先级高于 direction env | 节点自身存在显式 direction 值 | 显式设置 direction 的后代节点 | AC-3.1, AC-3.2 |
| FR-3.2 | 焦点线性遍历复用节点解析后的 layout direction | 可获焦节点所在子树通过 WithEnv direction 改变布局方向 | FocusHub 线性焦点遍历 | AC-3.3 |
| FR-4.1 | 嵌套 WithEnv 按最近祖先规则解析同名 key | 多层 WithEnv 都设置 direction key | 嵌套子树 | AC-4.1, AC-4.2 |
| FR-4.2 | CustomEnv 泛型 key 改造后保留设值、查值和更新语义 | 使用 `CustomEnvKey<T>`、`.customEnv<T>()` 或 `@CustomEnv()` | 自定义环境变量 | AC-4.5 |

---

### 2.2 业务规则（BR）

| 规则ID | 描述 | 约束条件 | 关联AC |
|--------|------|----------|--------|
| BR-1.1 | direction 解析优先级固定为显式 `.direction()` 高于 WithEnv direction env，高于原有全局 Auto 解析 | 仅当节点没有显式 direction 时才读取 env；env 缺失时不改变原有 Auto 语义 | AC-1.1, AC-1.4, AC-3.1, AC-3.2 |
| BR-1.2 | WithEnv direction env 是局部子树默认值，不是全局应用方向 | 仅影响 WithEnv 后代；不影响兄弟子树、祖先节点或其他页面上下文 | AC-1.1, AC-4.1 |
| BR-2.1 | `@Env(WritableEnvKey.DIRECTION)` 为只读消费方接口 | 组件只能读取和响应 env 值，不能通过赋值修改 WithEnv 中的 env 值 | AC-2.4 |
| BR-4.1 | 本期只固化 direction 系统 env 的可验收行为 | `WritableEnvKey.FONT_SCALE`、Readonly 系统 env 具体键和缓存优化不作为本期 direction 验收范围 | AC-1.1, AC-2.1, AC-4.5 |
| BR-4.2 | CustomEnv string key 旧写法迁移为 `CustomEnvKey<T>` | 新 API 通过泛型 key 约束类型；当前动态实现要求传入 `CustomEnvKey` 对象，旧 string 调用方需要迁移 | AC-4.5 |

---

### 2.3 异常/豁免规则（ER）

| 规则ID | 场景 | 处理方式 | 关联AC |
|--------|------|----------|--------|
| ER-1.1 | WithEnv `.env()` 入参 key 不是支持的可写系统 env key | 不写入系统 env 值，后代查询不到该 key | AC-1.4 |
| ER-1.2 | WithEnv `.env(WritableEnvKey.DIRECTION, value)` 的 value 不是 direction 可接受值 | 不写入 direction env 值，保持原有值或回退路径 | AC-1.4 |
| ER-2.1 | `@Env(WritableEnvKey.DIRECTION)` 没有找到祖先 env 值 | native 查询返回 undefined，前端装饰变量保持声明默认值 | AC-2.3 |
| ER-2.2 | 组件尝试给 `@Env` 装饰变量赋值 | 抛出只读变量错误，变量值不被调用方赋值覆盖 | AC-2.4 |
| ER-4.1 | 外层 WithEnv 更新同 key，但内层 WithEnv 已定义该 key | 更新通知不穿透内层同 key 作用域 | AC-4.2 |
| ER-4.2 | env 值变化时依赖节点已经失效或正在卸载 | 通过弱引用失效检查跳过该节点，不要求抛错 | AC-2.2, AC-4.3 |
| ER-4.3 | direction key 移除后系统 env 更新值为空 | 当前动态前端的 env update handler 不覆盖已缓存变量；布局侧重新查询时回退原有路径 | AC-4.3, AC-4.4 |

---

### 2.4 恢复契约（RC）

| 规则ID | 触发条件 | 恢复策略 | 恢复结果 | 约束 |
|--------|----------|----------|----------|------|
| RC-1.1 | 节点重新挂载到组件树后已有 env 依赖可能对应新的祖先链 | 触发已注册 env 依赖重新回调，组件重新查询当前祖先链的 env 值 | 组件变量和布局方向恢复到新位置对应的 env 结果 | 不承诺缓存 O(1)；本期以功能正确为准 |
| RC-1.2 | WithEnv direction key 被移除 | 布局侧重新查询 env；动态前端收到空值更新时不覆盖已缓存变量 | 布局方向回退到原有 Auto/全局路径；已缓存的 `@Env` 变量保持移除前值，重新创建组件时按默认值初始化 | 已有显式 `.direction()` 不受影响 |
| RC-1.3 | 依赖节点已经销毁但依赖表仍保留历史 id | 通过弱引用身份校验识别失效项并跳过或清理 | 不对失效节点触发错误回调 | 不把主动依赖清理作为本期功能验收项 |

---

## 三、2D能力特征分析

### 3.1 是否涉及新增开放API

**是否涉及：** 是

| 字段 | 内容 |
|------|------|
| API类型 | Public |
| API Reference | 当前 ace_engine 内可核对路径包括 `frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts`、`frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/system_env.ts`、`frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts`、`frameworks/bridge/declarative_frontend/jsview/js_view.cpp`、`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decorator.ts`、`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.WithEnv.ets`；正式 SDK API 参考需随 SDK 声明同步确认 |
| API Sample Code | 见本节下方 ArkTS 示例；公开资料链接需随 API 文档同步 |
| API方法定义 | 见下方新增 API 清单与变更 API 清单 |
| API调用使用方式 | 在 ArkTS 页面中使用 WithEnv 容器包裹子树，通过 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)` 设置 direction；在自定义组件中通过 `@Env(WritableEnvKey.DIRECTION)` 读取 |
| 运行触发方式 | 页面构建时创建 WithEnv 节点并设置 env；布局方向解析、`@Env` 首次读取或 env 值更新时触发查询/通知 |

#### 新增API清单

| API签名 | 类型 | 功能描述 | 参数说明 | 返回值 | 头文件 | 权限要求 |
|---------|------|----------|----------|--------|--------|----------|
| `class SystemEnvKey<T>` | Public ArkTS | 系统环境变量 key 基类 | `keyId: string` 标识系统 env key | key 对象 | 不涉及 C/C++ 头文件 | 无 |
| `class WritableSystemEnvKey<T> extends SystemEnvKey<T>` | Public ArkTS | 可写系统环境变量 key | 由系统提供静态实例，不建议应用自行构造未注册 key | key 对象 | 不涉及 C/C++ 头文件 | 无 |
| `class ReadonlySystemEnvKey<T> extends SystemEnvKey<T>` | Public ArkTS | 只读系统环境变量 key 类型 | 本期不交付具体只读 key 行为 | key 对象 | 不涉及 C/C++ 头文件 | 无 |
| `class WritableEnvKey` | Public ArkTS | 可写系统环境变量 key 集合 | 静态成员 `DIRECTION`、`FONT_SCALE` | 静态 key 集合 | 不涉及 C/C++ 头文件 | 无 |
| `WritableEnvKey.DIRECTION: WritableSystemEnvKey<Direction>` | Public ArkTS | direction 系统 env key | value 类型为 `Direction` | key 对象 | 不涉及 C/C++ 头文件 | 无 |
| `WithEnvAttribute.env<T>(key: WritableSystemEnvKey<T>, value: T): WithEnvAttribute` | Public ArkTS | 设置 WithEnv 子树系统 env 值 | `key` 为可写系统 env key；`value` 类型与 key 泛型匹配 | `WithEnvAttribute`，支持链式调用 | 不涉及 C/C++ 头文件 | 无 |
| `class CustomEnvKey<S>` | Public ArkTS | 自定义环境变量泛型 key | 由 `CustomEnvKey.create<T>()` 创建实例 | key 对象 | 不涉及 C/C++ 头文件 | 无 |
| `CustomEnvKey.create<T>(): CustomEnvKey<T>` | Public ArkTS | 创建自定义 env key | 泛型 `T` 约束该 key 对应 value 类型 | `CustomEnvKey<T>` | 不涉及 C/C++ 头文件 | 无 |

说明：设置侧 API 声明中 `WritableEnvKey.DIRECTION` 的 value 类型为 `Direction`；当前动态前端 `@Env(WritableEnvKey.DIRECTION)` native 查询和更新回调的可观测值为字符串 `'Ltr'`、`'Rtl'`、`'Auto'`，测试用例需按当前 bridge 行为断言。

#### 变更/废弃API

| 原有API | 变更类型 | 新API | 迁移说明 |
|---------|----------|--------|----------|
| `Env(value: SystemProperties): PropertyDecorator` | 变更 | `<T>(key: SystemEnvKey<T> \| SystemProperties): PropertyDecorator` | `@Env(SystemProperties)` 旧用法保留；新增 `@Env(WritableEnvKey.DIRECTION)` 系统 env key 用法 |
| `CustomEnv(value: string): PropertyDecorator` | 变更 | `<T>(key: CustomEnvKey<T>): PropertyDecorator` | 调用方需用 `CustomEnvKey.create<T>()` 创建 key 后传入 |
| `WithEnvAttribute.customEnv(key: string, value: any): WithEnvAttribute` | 变更 | `customEnv<T>(key: CustomEnvKey<T>, value: T): WithEnvAttribute` | string key 调用方迁移为 `CustomEnvKey<T>`，value 类型与 key 泛型匹配 |

#### API Sample Code

```ts
@Component
struct DirectionAwareChild {
  @Env(WritableEnvKey.DIRECTION) directionValue: string = 'Auto';

  build() {
    Row() {
      Text(this.directionValue === 'Rtl' ? 'RTL' : 'LTR')
    }
  }
}

@Entry
@Component
struct WithEnvDirectionPage {
  build() {
    WithEnv() {
      Column() {
        DirectionAwareChild()
        Text('explicit direction').direction(Direction.Ltr)
      }
    }
    .env(WritableEnvKey.DIRECTION, Direction.Rtl)
  }
}
```

---

### 3.2 是否涉及应用兼容性

**是否涉及：** 是

| 字段 | 内容 |
|------|------|
| 修改前规格 | WithEnv 已有 custom env 能力；`@Env` 主要面向既有 SystemProperties；direction 是组件自身属性，不具备 WithEnv 子树默认值能力 |
| 修改后规格 | WithEnv 新增 direction 系统 env；`@Env` 支持 `SystemEnvKey<T>`；显式 `.direction()` 优先于 env；CustomEnv 使用 `CustomEnvKey<T>` 泛型 key |
| 是否进行版本隔离 | 否。当前产物未提供版本隔离实现或隔离版本号；公开 API since 信息需随 SDK 声明确认 |
| changelog | 建议记录：新增 WithEnv `.env()` 系统 env 设置能力，新增 `WritableEnvKey.DIRECTION`，`@Env` 支持系统 env key，CustomEnv/customEnv 迁移为 `CustomEnvKey<T>` |

---

### 3.3 是否涉及支持跨平台

**是否涉及：** 否

本期规格仅覆盖 OpenHarmony ArkUI/ACE Engine 当前运行链路，未定义 Android、iOS 或其他跨平台行为。

---

### 3.4 是否涉及IDE预览

**是否涉及：** 否

当前源码和 `.codespec` 产物未定义 IDE 预览专属规格。若测试需要可视化验证，优先使用 ArkUI SpecTest Host Preview 或组件 unittest，而不是将 IDE 预览列为本期能力。

---

### 3.5 是否涉及编译工具链

**是否涉及：** 否

本期不新增编译器诊断、告警或错误信息规格。SDK API 声明同步应通过 SDK 编译验证，但不改变编译工具链行为。

---

### 3.6 是否涉及全球化语言

**是否涉及：** 是

- 支持语言列表：不按具体自然语言枚举。本特性服务 RTL/LTR 方向场景，典型覆盖阿拉伯语、希伯来语等 RTL 语言环境，以及中文、英文等 LTR 语言环境。
- 规格边界：WithEnv direction 只控制局部 UI 子树默认方向，不负责语言资源选择、翻译、排版断词或区域格式化。

---

### 3.7 是否涉及深浅色模式

**是否涉及：** 否

本特性不改变颜色、主题、深浅色切换或主题资源选择。

---

### 3.8 是否涉及新材质

**是否涉及：** 否

本特性不新增材质、背景、阴影、模糊或渲染风格。

---

### 3.9 是否涉及无障碍

**是否涉及：** 否

当前需求和源码证据未定义无障碍语义树、朗读顺序、焦点遍历或辅助功能属性变化。direction 可能影响布局呈现，但本期无独立无障碍规格。

---

### 3.10 是否涉及多设备差异

**是否涉及：** 否

| 设备类型 | 差异化描述 | 测试验证 |
|----------|------------|----------|
| 手机 | 无差异规格 | 否 |
| Pad | 无差异规格 | 否 |
| PC | 无差异规格 | 否 |
| 穿戴 | 无差异规格 | 否 |
| 智慧屏 | 无差异规格 | 否 |
| 座舱 | 无差异规格 | 否 |
| 其他 | 无差异规格 | 否 |

---

### 3.11 是否涉及适老化

**是否涉及：** 否

本期不改变字体大小策略、触控热区、对比度或适老化专项体验。

---

### 3.12 是否涉及资料新增或变更

**是否涉及：** 是

资料新增/变更：建议同步 ArkTS API Reference 与示例，内容包括 `WithEnvAttribute.env<T>()`、`WritableEnvKey.DIRECTION`、`@Env(SystemEnvKey<T>)` 和 CustomEnvKey 迁移说明。当前 ace_engine 工作树未提供外部资料 gitcode 链接。

---

## 四、非功能性需求（NFR）

### 4.1 是否涉及性能指标

**是否涉及：** 否

本期不设可量化性能指标。旧产物中的“不使用 env 零开销”“查值优于 O(n)”属于后续框架优化目标；当前源码仍存在向上查找与子树通知过滤路径，不能作为本期已实现性能 AC。

---

### 4.2 是否涉及功耗指标

**是否涉及：** 否

本期不定义功耗指标。

---

### 4.3 是否涉及稳定性&可靠性

**是否涉及：** 是

**可靠性指标要求：**

| 指标项 | 目标值 | 测试场景 | 验证方法 |
|--------|--------|----------|----------|
| env 查询稳定性 | 无 WithEnv、无 key、非法 key 场景不崩溃 | 无祖先、未设置 key、非法 key/value | 组件 unittest |
| env 更新稳定性 | 更新 direction 后依赖组件收到正确值；移除 direction 后布局侧回退，动态前端已缓存 `@Env` 值不被空值覆盖 | direction Ltr/Rtl/Auto 更新、移除 key | 组件 unittest + ArkTS 工程验证 |
| 嵌套作用域稳定性 | 外层更新不穿透内层同 key WithEnv | 外层与内层均定义 direction key | 组件 unittest |
| 失效节点处理 | 已销毁或失效节点不触发崩溃 | env 更新时依赖节点失效 | 代码审查 + targeted unittest |

---

### 4.4 是否涉及安全隐私合规

**是否涉及：** 否

本特性不采集、存储或传输用户隐私数据，不新增权限校验、加密、审计或安全策略。

---

### 4.5 是否涉及DFX

**是否涉及：** 否

当前源码未提供 WithEnv env 专项 dump、日志、事件上报或维测接口规格。旧产物中提到的 dump 支持不作为当前实现验收项。

---

## 五、2C功能体验分析

### 5.1 是否涉及UX-静态UI效果

**是否涉及：** 是

| 效果编号 | 前置条件(Given) | 触发条件(WHEN) | 预期结果(THEN) | UX效果图 |
|----------|-----------------|----------------|----------------|----------|
| 效果1 | 页面中 WithEnv 设置 direction 为 `Direction.Rtl`，后代节点使用 start/end 或依赖 direction 的布局逻辑，且未显式设置 `.direction()` | WHEN 页面完成布局 | THEN 后代节点按 RTL 默认方向计算布局属性 | 无，建议由 SpecTest Inspector 断言节点 direction 或布局结果 |
| 效果2 | 页面中 WithEnv 设置 direction 为 `Direction.Rtl`，某个后代节点显式 `.direction(Direction.Ltr)` | WHEN 页面完成布局 | THEN 显式节点按 LTR 方向计算布局，其他未显式节点仍按 env 方向 | 无，建议由 SpecTest Inspector 或组件 unittest 断言 |

---

### 5.2 是否涉及UX-动态UI效果（动效）

**是否涉及：** 否

本期不定义动画、过渡或动效效果。

---

### 5.3 是否涉及UX-手势/事件/交互/焦点

**是否涉及：** 是

本期不改变手势识别或通用事件分发；但源码中线性焦点遍历会读取组件 layout direction，WithEnv direction 作为默认 layout direction 时可能影响焦点顺序。

| 交互编号 | 前置条件(Given) | 触发条件(WHEN) | 预期结果(THEN) | 关联AC |
|----------|-----------------|----------------|----------------|--------|
| 交互1 | WithEnv 设置 direction 为 `Direction.Rtl`，子树中存在多个可获焦节点且节点未显式覆盖 direction | WHEN 用户通过键盘或遥控器执行线性焦点遍历 | THEN 焦点顺序按 RTL 方向参与计算 | AC-3.3 |

---

### 5.4 是否涉及用户数据

**是否涉及：** 否

本期 env 值为组件树运行时状态，不定义持久化、重启恢复、克隆、升级保留或用户数据存储。

---

## 六、参考资料

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | `.codespec/changes/issue-76660-withenv-direction/proposal.md` | 已存在 |
| Design | `.codespec/changes/issue-76660-withenv-direction/design.md` | 已存在，部分架构优化标记为后续 |
| Manifest | `.codespec/changes/issue-76660-withenv-direction/manifest.md` | 已存在 |
| 当前 spec-for-ai 模板 | `/home/qingshan/Documents/repo/spec-for-ai/openharmony/templates/spec.md` | 已核对 |
| ArkUI 测试模板 | `ArkUI_SpecV0.2.md` | 已作为本次结构依据 |
| WithEnv JS bridge | `frameworks/bridge/declarative_frontend/jsview/js_with_env.cpp`、`frameworks/bridge/declarative_frontend/jsview/js_view.cpp` | 已核对 |
| System env TS key | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/system_env.ts` | 已核对 |
| @Env 装饰器 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts` | 已核对 |
| Static ArkTS state management | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decorator.ts`、`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.WithEnv.ets` | 已核对 |
| EnvironmentManager | `frameworks/core/pipeline_ng/environment_manager.cpp` | 已核对 |
| Layout direction env | `frameworks/core/components_ng/layout/layout_property.cpp`、`frameworks/core/pipeline_ng/pipeline_context.cpp` | 已核对 |
| FocusHub direction | `frameworks/core/components_ng/event/focus_hub.cpp` | 已核对 |
| 单元测试 | `test/unittest/core/syntax/with_env_syntax_test_ng.cpp`、`test/unittest/core/pipeline/environment_manager_test_ng.cpp` | 已核对 |

---

## 附录：术语表

| 术语 | 定义 |
|------|------|
| WithEnv | ArkUI 容器语法节点，用于为子树提供环境变量 |
| SystemEnvKey | 系统环境变量 key 类型，用于标识框架定义的环境变量 |
| WritableEnvKey.DIRECTION | 本期新增的可写系统 env key，value 类型为 `Direction` |
| CustomEnvKey | 自定义环境变量 key 类型，用于替代旧 string custom env key |
| Direction.Auto | 自动方向值，非 Auto 解析仍按全局 RTL/LTR 规则处理 |
| 最近祖先 | 从消费节点向父链查找时遇到的第一个定义同名 env key 的 WithEnv |

---

## 验证映射

| AC | 验证方式 | 当前证据 | 需新增验证 |
|----|----------|----------|--------|
| AC-1.1 | 组件 unittest + SpecTest | `LayoutProperty::GetLayoutDirection()` 已接入 env 查询；EnvironmentManager 可查 direction key | 补充 direction env 对布局结果的 targeted unittest 或 SpecTest |
| AC-1.2 | 组件 unittest + SpecTest | 同 AC-1.1 | 补充 LTR 场景 |
| AC-1.3 | 组件 unittest | WithEnvNode 接受 `TextDirection::AUTO` | 补充 Auto env 解析用例 |
| AC-1.4 | 组件 unittest | `ResolveDirectionFromEnv()` 查不到时返回空，LayoutProperty 回退 Auto | 补充无 WithEnv/无 key 用例 |
| AC-2.1 | ArkTS 工程验证或 JS bridge unittest | `@Env` 可识别 `SystemEnvKey`，native `findEnvValueByKey` 可查询系统 env；动态 bridge 返回 `'Rtl'/'Ltr'/'Auto'` 字符串 | 补充真实 ArkTS 或 bridge 层用例 |
| AC-2.2 | 组件 unittest + ArkTS 工程验证 | EnvironmentManager 更新系统 env 后可触发 CustomNode system env update；动态 bridge 更新值为字符串 | 补充 `@Env(WritableEnvKey.DIRECTION)` 端到端响应式用例 |
| AC-2.3 | ArkTS 工程验证 | native 查询无值返回 undefined | 补充前端默认值保持用例 |
| AC-2.4 | ArkTS 工程验证 | `@Env` setter 抛只读错误 | 补充赋值异常用例 |
| AC-3.1 | 组件 unittest + SpecTest | `layoutDirection_.has_value()` 优先于 env 查询 | 补充显式 LTR 覆盖 env RTL 用例 |
| AC-3.2 | 组件 unittest + SpecTest | 同 AC-3.1 | 补充显式 RTL 覆盖 env LTR 用例 |
| AC-3.3 | 组件 unittest + 焦点交互测试 | `FocusHub::GoToNextFocusLinear()` 使用 `IsComponentDirectionRtl()`，后者读取 `LayoutProperty::GetLayoutDirection()` | 补充 WithEnv RTL 子树焦点遍历用例 |
| AC-4.1 | 组件 unittest | `EnvironmentManagerSystemEnvInnerScope001` 覆盖最近祖先查询 | 可补充 layout direction 级联用例 |
| AC-4.2 | 组件 unittest | `EnvironmentManagerSystemEnvInnerScope001` 覆盖外层更新不穿透内层同 key | 无 |
| AC-4.3 | 组件 unittest | `EnvironmentManagerSystemEnvRemovedValue001` 覆盖移除通知空值 | 补充 layout fallback 和 @Env 默认值用例 |
| AC-4.4 | ArkTS 工程验证 | 动态前端 `__onEnvValueUpdate__Internal()` 对 undefined 更新直接返回，不覆盖已缓存变量 | 补充移除 key 后当前组件值保持、重新创建组件默认值恢复用例 |
| AC-4.5 | 回归 unittest + ArkTS 编译验证 | `CustomEnvKey.create<T>()`、`WithEnvAttribute.customEnv<T>()`、`@CustomEnv(key)` 路径已存在；custom env 更新测试已有基础覆盖 | 补充 CustomEnvKey ArkTS 迁移编译验证 |

## 后续演进项

以下内容来自旧 design/spec 的理想目标，但当前源码未完整实现，不作为本期验收 AC：

| 演进项 | 当前状态 | 建议处理 |
|--------|----------|----------|
| env 查值缓存 | 当前仍通过父链向上查找最近 WithEnv | 后续单独立项，补充缓存失效和节点移动测试 |
| 精准通知替代 DFS | 当前通知仍对子树 DFS，并结合依赖表和作用域屏蔽过滤 | 后续单独立项，定义依赖注册表驱动通知 AC |
| 不使用 env 零额外开销 | 当前通过 `GetUseEnvManager()` 降低未启用路径影响，但无量化指标 | 后续以 benchmark 或代码审查指标重新定义 |
| WithEnv dump 支持 | 当前未看到专项 dump 输出实现 | 后续作为 DFX 需求单独定义 |
