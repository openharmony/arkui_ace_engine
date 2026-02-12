# IDLize 项目指南

本文件为 Claude Code (claude.ai/code) 在此代码库中工作时提供指导。

## 项目概述

**IDLize** 是 OpenHarmony ArkUI 的代码生成工具链，可将 TypeScript/ArkTS 接口定义转换为多语言绑定代码。它通过基于 WebIDL 的中间表示，使 C++ 组件能够被 ArkTS、TypeScript、Java、仓颉等语言无缝调用。

**核心价值**：为 OpenHarmony 生态系统提供跨语言互操作性 —— 用 TypeScript/ArkTS 编写一次定义，即可生成 6+ 种目标语言的绑定代码。

**仓库地址**：https://gitcode.com/openharmony-sig/arkui_idlize

## 代码转换工作流

### 前置环境检查

操作系统环境：Ubuntu 22.04 LTS

meson版本 > 0.60

node.js版本 > 18.0

> meson 安装命令：`sudo apt-get install meson`

### 更新子模块并运行 npm install

拉取最新的分支变更：

```shell
cd idlize
git submodule update --init
git submodule update
npm i && npm i --prefix external && npm i --prefix external/ui2abc/libarkts
```

### 生成代码

**1. 下载并抽象 SDK**

```shell
npm run libarkts:reinstall:regenerate -C etsgen
npm run download:sdk
npm run absolute:sdk
npm run run:sdk -C etsgen
```

> 在 etsgen/out/idl/@ohos.base.idl 中做一些手动修改，从 AsyncCallback 中移除第二个类型参数：
> [TypeParameters="T,E"] -> [TypeParameters="T"]

**2. 生成代码**

```shell
npm run go -C scraper
cd scraper/out
./go-main.sh
```

### 升级代码

> 这一步是将转换好的代码复制到 arkui_ace_engine 仓库中。

**1. 更新 generated 文件夹**

复制 `scraper/out/generated/sig/arkoala-arkts/arkui/generated` 到 `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated`

**2. 更新 framework 文件夹**

复制 `scraper/out/generated/sig/arkoala-arkts/framework/native/src/generated` 到 `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/framework/native/src/generated`

**3. 更新原生头文件**

复制 `scraper/out/generated/libace/generated/interface/arkoala_api_generated.h` 到 `frameworks/core/interfaces/native/generated/interface/arkoala_api_generated.h`

复制 `scraper/out/generated/libace/utility/generated/converter_generated.h` 到 `frameworks/core/interfaces/native/utility/generated/converter_generated.h`

## 架构概览

### 高层转换流水线

```
┌─────────────────────────────────────────────────────────────────┐
│                      输入层                                      │
│  .d.ts 文件  │  .ets 文件  │  .idl 文件  │  配置文件           │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                      解析层                                      │
│  • TypeScript Compiler API (ts.createProgram)                   │
│  • 自定义 IDL 解析器 (递归下降)                                  │
│  • 配置加载器                                                    │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                   中间表示 (IDL AST - core/src/idl.ts)          │
│  • IDLFile, IDLInterface, IDLMethod, IDLProperty                │
│  • 50+ 种类型节点 (PrimitiveType, ReferenceType 等)             │
│  • 扩展属性系统 (30+ 种元数据标记)                               │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                      转换层                                      │
│  • IDLVisitor (TypeScript → IDL) - libohos/src/IDLVisitor.ts    │
│  • 泛型转换器 (单态化)                                           │
│  • 类型引用解析                                                  │
│  • 继承关系处理                                                  │
│  • 两阶段处理 (Phase 1: 解析, Phase 2: 解析引用)                 │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                    代码生成层                                    │
│  • PeerLibrary/PeerClass/PeerMethod                             │
│  • 参数转换器 (ArgConvertors.ts)                                │
│  • 语言 Writer (LanguageWriter.ts + writers/)                   │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                       输出层                                     │
│  .ets  │  .ts  │  .java  │  .kt  │  .cpp/.h  │  .idl            │
└─────────────────────────────────────────────────────────────────┘
```

### 核心转换流程

**1. dts2peer (TypeScript → 对等代码)** - 最常用
```
.d.ts 文件
  → TypeScript Compiler API
  → IDLVisitor (libohos/src/IDLVisitor.ts, 95KB)
  → IDL AST (core/src/idl.ts, 68KB)
  → GenericTransformer (泛型单态化)
  → PeerLibrary 创建
  → LanguageWriter (ETSLanguageWriter, TsLanguageWriter 等)
  → 生成的代码 (.ets, .ts, .java, .kt, .cpp)
```

**2. idl2peer (IDL → 对等代码)**
```
.idl 文件
  → IDL Parser (core/src/from-idl/parser.ts)
  → IDL AST
  → PeerLibrary 创建
  → LanguageWriter
  → 生成的代码
```

**3. ets2ts (ArkTS → TypeScript)**
```
.ets 文件
  → TypeScript Compiler API
  → AST 转换
  → TypeScript 输出
```

## 核心概念

### 两阶段处理

代码库使用两阶段处理模式来处理跨文件引用：

**Phase 1** (`visitPhase1()`)：独立解析所有文件，构建 AST，创建未解析的类型引用
**Phase 2** (`visitPhase2(siblings)`)：使用完整的符号表解析跨文件类型引用

这使得 Phase 1 可以并行处理，同时在 Phase 2 维护正确的类型链接。

### 泛型单态化

**问题**：TypeScript 泛型是类型层面的抽象，在大多数目标语言的运行时中不存在。

**解决方案**：在代码生成时通过创建特化版本将泛型转换为具体类型。

```typescript
// 原始定义
interface Container<T, U> { value: T; process(u: U): void }

// 当使用 Container<string, number> 时
// 创建单态化版本:
interface Container_string_number {
    [OriginalGenericName="Container"]
    value: string;
    process(u: number): void;
}
```

**例外**：UI 组件、Builder 类和 Materialized 类不进行单态化（它们保留泛型结构）。

### 扩展属性系统

IDL 使用与 WebIDL 兼容的扩展属性来表示元数据:

```typescript
[Component="Button"]        // 标记 UI 组件
[TypeArguments="T,U"]       // 泛型参数
[DtsName="_Button_"]        // 原始 TypeScript 名称
[Synthetic]                 // 自动生成的节点标记
[OriginalGenericName="Container"]  // 单态化前的名称
```

### 类型品牌标记

代码库使用 TypeScript 品牌标记来实现编译时类型安全:

```typescript
export interface IDLNode {
    _idlNodeBrand: never  // 节点类型的品牌标记
}
export interface IDLType {
    _idlTypeBrand: never  // 类型系统的品牌标记
}
```

这可以防止节点类型和类型节点的意外混合。

### 配置系统

**单例模式** (core/src/config.ts):
```typescript
let currentConfig: CoreConfiguration = defaultCoreConfiguration
export function setDefaultConfiguration<T>(config: T): void
export function patchDefaultConfiguration<T>(config: Partial<T>): void
export function generatorConfiguration<T>(): T
```

**生成器配置** (arkgen/generation-config/config.json):
- `rootComponents`: UI 组件名称列表
- `ignoreGenerics`: 跳过单态化的类型
- `forceCallback`: 视为回调的方法
- `modules`: 包和命名空间映射

## 模块结构

### 核心库 (`core/src/`)

**idl.ts** (68KB) - 完整的 IDL 类型系统，包含 50+ 种节点类型
- 所有 IDL 节点类型：IDLInterface、IDLMethod、IDLProperty、IDLEnum 等
- 类型层次：IDLNode → IDLEntry | IDLType
- 扩展属性：30+ 种元数据属性
- 用于单态化的节点克隆函数

**idlize.ts** - 主生成协调器
- `generate()` 函数：代码生成的主要入口点
- 两阶段处理协调
- 访问者模式执行

**config.ts** - 配置管理（单例）
- 全局配置访问
- JSON 模式验证

**peer-generation/** - 对等代码数据结构
- `PeerLibrary.ts`：管理所有生成代码的中心库
- `PeerClass.ts`：表示一个生成的类
- `PeerMethod.ts`：表示带有签名的生成方法
- `BuilderClass.ts`：Builder 模式的类
- `Materialized.ts`：需要原生集成的特殊类型
- `ReferenceResolver.ts`：带缓存的类型引用解析

**LanguageWriters/** - 多语言代码生成
- `LanguageWriter.ts`：抽象基类
- `ArgConvertors.ts` (75KB)：参数转换系统，包含 20+ 种转换器
  - BooleanConvertor、EnumConvertor、AggregateConvertor、ArrayConvertor 等
  - 处理语言之间的序列化/反序列化
- `writers/`：语言特定实现
  - `ETSLanguageWriter.ts`：ArkTS（单引号，TypeChecker 集成）
  - `TsLanguageWriter.ts`：标准 TypeScript
  - `JavaLanguageWriter.ts`：Java with JNI
  - `JavaLanguageWriter.ts`：Java with JNI
  - `CppLanguageWriter.ts`：C++ 原生绑定
  - `CJLanguageWriter.ts`：仓颉语言支持

**from-idl/** - IDL 解析
- `parser.ts`：手写递归下降解析器（不使用解析器生成器）
- `deserialize.ts`：IDL AST 反序列化

**transformers/** - AST 转换
- `GenericTransformer.ts`：泛型单态化逻辑

### OHOS 库 (`libohos/src/`)

**IDLVisitor.ts** (95KB) - 核心转换引擎
- `visitPhase1()`：解析节点，创建 IDL 结构
- `visitPhase2()`：解析跨文件引用
- `serializeClass()`：将 TypeScript 类转换为 IDL 接口
- `serializeInterface()`：将 TypeScript 接口转换为 IDL
- `serializeMethod()`：转换方法并处理参数
- 名称建议机制和配置驱动的替换

**peer-generation/** - OHOS 特定的对等生成
- `IdlPeerProcessor.ts`：处理 IDL 以生成对等代码
- `LayoutManager.ts`：文件组织和依赖管理
- `DefaultConfiguration.ts`：OHOS 特定默认值

### Arkgen (`arkgen/src/`)

**main.ts** - 入口点
```typescript
import { arkgen } from "./app";
arkgen(process.argv.slice(2));
```

**app.ts** - 使用 commander 的 CLI 应用
- `--dts2peer`：TypeScript 定义转对等代码
- `--idl2peer`：IDL 转对等代码
- `--ets2ts`：ArkTS 转 TypeScript
- `--show-config-schema`：打印 JSON 模式

**arkoala.ts** - Arkoala 特定的生成协调

**printers/** - 文件输出管理
- 布局管理器、文件打印器、导入组织

**generation-config/** - 配置文件
- `config.json`：默认配置
- `schema.json`：验证用的 JSON 模式

## 语言特定细节

### ArkTS (Language.ARKTS)
- 文件扩展名：`.ets`
- 单引号字符串（不是双引号）
- 特殊 lambda 语法（lambda 体内没有尾随分号）
- TypeChecker 集成用于运行时类型检查
- ArkTS 编译器 bug 的变通方法（例如 `toByte()`、`toInt()` 类型转换）

### TypeScript (Language.TS)
- 文件扩展名：`.ts`
- 标准 TS 语法
- 双引号字符串

### Java
- JNI 集成用于原生调用
- 显式可空性模型

### C++
- 原生绑定
- 指针类型和内存管理

### 仓颉
- 中国国产语言支持
- `.cj` 文件扩展名

## 关键文件位置

| 用途 | 文件路径 |
|------|----------|
| **主入口** | `arkgen/src/main.ts` |
| **CLI 应用** | `arkgen/src/app.ts` |
| **IDL 类型** | `core/src/idl.ts` (68KB) |
| **生成协调器** | `core/src/idlize.ts` |
| **TypeScript→IDL Visitor** | `libohos/src/IDLVisitor.ts` (95KB) |
| **泛型转换器** | `core/src/transformers/GenericTransformer.ts` |
| **Language Writers 基类** | `core/src/LanguageWriters/LanguageWriter.ts` |
| **Arg Convertors** | `core/src/LanguageWriters/ArgConvertors.ts` (75KB) |
| **配置** | `core/src/config.ts` |
| **IDL Parser** | `core/src/from-idl/parser.ts` |
| **Peer Library** | `core/src/peer-generation/PeerLibrary.ts` |
| **配置文件** | `arkgen/generation-config/config.json` |

## 错误处理

**诊断系统** (`core/src/diagnosticmessages.ts`)：
- `DiagnosticMessageGroup`：收集和报告错误
- `reportDiagnosticMessage()`：带位置上下文的报告
- `allGroupsEntries`：所有诊断的静态集合

**错误恢复**：
- 非致命错误：跳过当前声明，继续解析
- 致命错误：终止解析并报告