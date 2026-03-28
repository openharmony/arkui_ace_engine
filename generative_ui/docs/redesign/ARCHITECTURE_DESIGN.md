# A2UIRender 架构重构设计文档

## 1. 设计背景

### 1.1 当前问题
1. **调用顺序依赖问题**：当前实现假设 `bindToRender` 先于 `onReceive` 调用，但开发者可能先 `new SurfaceController` 并通过 `onReceive` 传输 DSL，然后再与 `A2UIRenderComponent` 绑定
2. **强耦合设计**：`SurfaceController.onReceive()` 直接依赖 `currentRootSlot`，但这个值在 `onReceive` 时可能为 `undefined`
3. **单一 Surface 限制**：当前架构无法支持一个 RenderContext 内部管理多个 Surface 的场景

### 1.2 设计目标
1. **解耦 DSL 解析与 UI 绑定**：`onReceive` 和 `bindToRender` 应该可以任意顺序调用
2. **支持多 Surface 管理**：通过 RenderSlot 管理内部多个 Surface，使用栈结构
3. **统一管理**：通过 RenderManager 统一管理所有 RenderSlot

## 2. 架构设计

### 2.1 核心概念

#### 2.1.1 RenderId（渲染 ID）
- **作用**：唯一标识一个 SurfaceController 实例
- **生成方式**：通过 ETS 侧的 ID 生成器自增生成
- **生命周期**：随 SurfaceController 创建而创建，随 SurfaceController 销毁而失效

#### 2.1.2 RenderSlot（渲染槽）
- **作用**：管理一个 SurfaceController 内部的多个 Surface(Surface即SurfaceSlot)
- **结构**：使用surefaceManager 管理多个 Surface
- **成员**：
  - `renderId`: 所属的渲染 ID
  - `surfaceManager`: Surface 管理器，用于创建和查询 Surface

#### 2.1.3 RenderManager（渲染管理器）
- **作用**：管理进程内所有的 RenderSlot
- **实现**：C++ 单例类
- **职责**：
  - 创建和销毁 RenderSlot
  - 通过 renderId 查找 RenderSlot
  - 维护 renderId 到 RenderSlot 的映射

### 2.2 类设计

#### 2.2.1 ETS 侧

```
┌─────────────────────────────────────────┐
│         RenderIdGenerator               │
├─────────────────────────────────────────┤
│ - nextId: number                        │
│ + generateId(): number                  │
└─────────────────────────────────────────┘
                    │
                    │ uses
                    ▼
┌──────────────────────────────────────────────────────────┐
│              SurfaceController                            │
├──────────────────────────────────────────────────────────┤
│ - renderId: number                                        │
│ - catalog: Catalog                                        │
│ - surfaceBelongsTo?: string                               │
│ - onAction?: ActionReceiver                               │
│ - onError?: ErrorCallback                                 │
│ - onSurfaceEvent: SurfaceEventCallback                    │
│ - currentRootSlot?: NodeContent                           │
│ + constructor(catalog, eventCallback, checkSchema)        │
│ + onReceive(dsl: string): void                            │
│ + bindToRender(rootSlot: NodeContent): void               │
└──────────────────────────────────────────────────────────┘
```

#### 2.2.2 C++ 侧

```
┌─────────────────────────────────────────┐
│            RenderManager                │
├─────────────────────────────────────────┤
│ - renderSlots_: Map<renderId, RenderSlot>│
│ + GetInstance(): RenderManager&         │
│ + CreateRenderSlot(renderId): RenderSlot&│
│ + FindRenderSlot(renderId): RenderSlot* │
│ + RemoveRenderSlot(renderId): void      │
└─────────────────────────────────────────┘
                    │
                    │ manages
                    ▼
┌──────────────────────────────────────────────────────────┐
│                  RenderSlot                               │
├──────────────────────────────────────────────────────────┤
│ - renderId_: number                                       │
│ - surfaceManager_: SurfaceManager                        │
│ + RenderSlot(renderId: number)                           │
│ + GetRenderId(): number                                  │
│ + PushSurface(surfaceId: string): SurfaceSlot&           │
│ + PopSurface(): void                                     │
│ + GetTopSurface(): SurfaceSlot*                          │
│ + FindSurface(surfaceId: string): SurfaceSlot*           │
│ + BindTopSurfaceToRoot(contentHandle): void              │
└──────────────────────────────────────────────────────────┘
                    │
                    │ manages
                    ▼
┌─────────────────────────────────────────┐
│          SurfaceSlot (existing)         │
├─────────────────────────────────────────┤
│ - surfaceId_: string                    │
│ - contentHandle_: ArkUI_NodeContentHandle│
│ - rootComponent_: Component             │
│ - bindingEngine_: BindingEngine         │
│ + SetSurfaceId(surfaceId)               │
│ + GetSurfaceId(): string                │
│ + SetContentHandle(handle)              │
│ + UpdateComponents(messageBody)         │
│ + UpdateDataModel(messageBody)          │
└─────────────────────────────────────────┘
```

### 2.3 时序图

#### 2.3.1 SurfaceController 构造和初始化

```
SurfaceController          RenderIdGenerator          C++ Layer
     │                            │                        │
     │  constructor()              │                        │
     │───────────────────────────>│                        │
     │                            │                        │
     │  generateId()              │                        │
     │<───────────────────────────│                        │
     │                            │                        │
     │  initRenderSlot(renderId)  │                        │
     │───────────────────────────────────────────────────>│
     │                            │                        │
     │                            │                        │  CreateRenderSlot(renderId)
     │                            │                        │──────────────>
     │                            │                        │
     │                            │                        │  new RenderSlot(renderId)
     │                            │                        │──────>
     │                            │                        │
     │                            │                        │  new SurfaceManager()
     │                            │                        │──────>
```

#### 2.3.2 onReceive 调用（先于 bindToRender）

```
SurfaceController          A2UIMessage            RenderManager         RenderSlot
     │                           │                        │                   │
     │  onReceive(dsl)           │                        │                   │
     │─────────────────────────>│                        │                   │
     │                           │                        │                   │
     │  fromDSL(dsl)             │                        │                   │
     │<──────────────────────────│                        │                   │
     │                           │                        │                   │
     │  processMessage(renderId, a2uiMessage, catalog)    │                   │
     │──────────────────────────────────────────────────────────────────────>│
     │                           │                        │                   │
     │                           │                        │  FindRenderSlot(renderId)
     │                           │                        │<──────────────────│
     │                           │                        │                   │
     │                           │                        │  GetSurface(surfaceId)
     │                           │                        │<──────────────────│
     │                           │                        │                   │
     │                           │                        │  UpdateComponents() / UpdateDataModel()
     │                           │                        │───────────────────>│
```

#### 2.3.3 bindToRender 调用

```
SurfaceController          RenderManager         RenderSlot          SurfaceSlot
     │                           │                   │                    │
     │  bindToRender(rootSlot)   │                   │                    │
     │─────────────────────────────────────────────────────────────────────────>│
     │                           │                   │                    │
     │  bindSurfaceToRender(renderId, contentHandle)│                    │
     │─────────────────────────────────────────────>│                    │
     │                           │                   │                    │
     │                           │  FindRenderSlot(renderId)               │
     │                           │<──────────────────│                    │
     │                           │                   │                    │
     │                           │  GetTopSurface()  │                    │
     │                           │<──────────────────│                    │
     │                           │                   │                    │
     │                           │                   │  SetContentHandle()│
     │                           │                   │───────────────────>│
```

#### 2.3.4 onReceive 后调用 bindToRender

```
SurfaceController          RenderManager         RenderSlot          SurfaceSlot
     │                           │                   │                    │
     │  onReceive(dsl)           │                   │                    │
     │─────────────────────────────────────────────>│                    │
     │                           │                   │                    │
     │                           │  CREATE_SURFACE   │                    │
     │                           │  PushSurface()    │                    │
     │                           │                   │───────────────────>│
     │                           │                   │                    │
     │  bindToRender(rootSlot)   │                   │                    │
     │─────────────────────────────────────────────>│                    │
     │                           │                   │                    │
     │                           │  GetTopSurface()  │                    │
     │                           │                   │───────────────────>│
     │                           │                   │  SetContentHandle()│
```

## 3. 实现计划

### 3.1 ETS 侧实现

1. **创建 RenderIdGenerator 类**
   - 实现单例模式
   - 提供自增 ID 生成方法

2. **修改 SurfaceController 类**
   - 添加 `renderId` 成员变量
   - 构造函数中调用 ID 生成器
   - 添加 `initRenderSlot()` 方法调用 NAPI 接口
   - 修改 `onReceive()` 方法，传递 renderId 而不是 currentRootSlot
   - 修改 `bindToRender()` 方法，通过 renderId 绑定

3. **更新 NAPI 接口**
   - 添加 `initRenderSlot(renderId)` 接口
   - 修改 `processMessage(renderId, message, catalog)` 接口
   - 添加 `bindSurfaceToRender(renderId, contentHandle)` 接口

### 3.2 C++ 侧实现

1. **创建 RenderManager 类**
   - 实现单例模式
   - 管理 renderId 到 RenderSlot 的映射
   - 提供创建、查找、删除 RenderSlot 的方法

2. **创建 RenderSlot 类**
   - 保存 renderId
   - 包含 Surface 栈（std::stack）
   - 包含 SurfaceManager 实例
   - 提供 PushSurface、PopSurface、GetTopSurface 等方法
   - 提供 BindTopSurfaceToRoot 方法

3. **修改 SurfaceManager（可选）**
   - 保留现有的 SurfaceManager
   - 或者将其功能整合到 RenderSlot 内部

4. **更新 NAPI 绑定**
   - 添加 `InitRenderSlot` 方法
   - 修改 `HandleIncomingMessage` 为 `ProcessMessage`
   - 添加 `BindSurfaceToRender` 方法

### 3.3 测试策略

1. **单元测试**
   - 测试 RenderIdGenerator 的自增功能
   - 测试 SurfaceController 的初始化
   - 测试 RenderSlot 的栈操作

2. **集成测试**
   - 测试先 onReceive 后 bindToRender 的流程
   - 测试先 bindToRender 后 onReceive 的流程
   - 测试多个 Surface 的创建和管理

3. **回归测试**
   - 确保现有的测试用例仍然通过
   - 确保现有的功能不受影响

## 4. 风险与注意事项

1. **向后兼容性**：需要确保现有的代码仍然能够正常工作
2. **性能影响**：RenderSlot 的查找操作不应该影响性能
3. **内存管理**：确保 RenderSlot 和 SurfaceSlot 的正确销毁
4. **线程安全**：RenderManager 需要考虑线程安全问题（如果有多线程场景）

## 5. 实施步骤

1. **第一阶段**：实现 RenderIdGenerator 和修改 SurfaceController（ETS）
2. **第二阶段**：实现 RenderManager 和 RenderSlot（C++）
3. **第三阶段**：更新 NAPI 绑定
4. **第四阶段**：测试和验证
