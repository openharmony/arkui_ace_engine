# 执行计划

> FuncID: 04-01-03 | FeatID: Feat-02 | 变更 ID: issue-78716-pixelmap-drawable-resourcestr

## Task 拆分

| Task ID | 目标 | 受影响文件 | 依赖 |
|---------|------|------------|------|
| TASK-1 | 核心层: drawable_api 扩展 + modifier 实现 | `drawable_api.h`, `drawable_modifier.cpp` | 无 |
| TASK-2 | 动态 NAPI: PixelMapConstructor 扩展 | `js_drawable_descriptor.cpp` | TASK-1 |
| TASK-3 | 静态 ANI: 新方法 + 注册 | `drawable_module.cpp`, `drawable_module.h`, `module.cpp` | TASK-1 |
| TASK-4 | 静态 ArkTS: constructor 重载 | `drawableDescriptor.ets` | TASK-3 |
| TASK-5 | C API 桥接层验证（NAPI/ANI bridge + drawable_descriptor） | `native_node_napi.cpp`, `native_node_ani.cpp`, `drawable_descriptor.cpp`, `native_drawable_descriptor.cpp` | TASK-2, TASK-3 |
| TASK-6 | 编译验证 + 测试 | 编译 + unittest | TASK-1~5 |

## 实施顺序

```
TASK-1 (Core + API)
  ├── TASK-2 (Dynamic NAPI)
  │     └── TASK-5 (C API Bridge verify)
  └── TASK-3 (Static ANI)
        ├── TASK-4 (Static ArkTS)
        └── TASK-5 (C API Bridge verify)
              └── TASK-6 (Build + Test)
```

## 预计变更量

| 层 | 新增行数 | 说明 |
|----|----------|------|
| drawable_api.h | +2 | 2 个新函数指针 |
| drawable_modifier.cpp | +40 | 2 个新函数 + 函数表注册 |
| js_drawable_descriptor.cpp | +25 | string/Resource 分支 |
| drawable_module.cpp | +50 | 2 个 ANI 方法实现 |
| drawable_module.h | +2 | 2 个函数声明 |
| module.cpp | +8 | 2 个 ANI 注册条目 |
| drawableDescriptor.ets | +15 | constructor(ResourceStr) |
| **合计** | **~142** | |
