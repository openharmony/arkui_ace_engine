# Image CAPI 示例

<!--
Copyright (c) 2026 Huawei Device Co., Ltd.
Licensed under the Apache License, Version 2.0.
-->

## 📁 目录说明

本目录包含 Image 组件的 CAPI（C API）测试用例，展示如何使用 Native C++ 代码创建和控制 Image 组件。

### 技术栈

- **ArkTS 层**: 使用 NodeContent 方式创建 Native UI（推荐）
- **C++ 层**: 使用 ArkUI Native Node API 创建 Image 组件
- **渲染方式**: NodeContent（XComponent 传统方式已废弃）

---

## 📋 测试用例列表

### ETS 层面

| 文件名 | 说明 | 状态 |
|--------|------|------|
| `Index.ets` | 主入口，NodeContent 方式 | ✅ 推荐 |

### C++ 层面测试用例 (NormalImageListExample.h)

| 用例 | 功能 | 涉及 API | 状态 |
|------|------|----------|------|
| **Test 1** | 基础图片加载 | SetSrc, SetWidth, SetHeight | ✅ |
| **Test 2** | 九宫格切片 | SetSlice | ✅ |
| **Test 3** | Lattice 基础渲染 | SetLattice, OH_Drawing_LatticeCreate | ✅ |
| **Test 4** | Lattice 自定义区域 | OH_Drawing_LatticeCreate (rectTypes) | ✅ |
| **Test 5** | Lattice 固定颜色 | OH_Drawing_LatticeCreate (colors) | ✅ |
| **Test 6** | 方向 + 抗锯齿 + 重复 | SetOrientation, SetAntialiased, SetObjectRepeat | ✅ |
| **Test 7** | 动态切片参数 | SetSlice (动态更新) | ✅ |
| **Test 8** | Matrix 变换 | ImageMatrix::Translate/Rotate/Scale | ✅ |
| **Test 9** | ObjectFit 测试 | SetObjectFit | ✅ |
| **Test 10** | Matrix + ObjectFit 组合 | SetImageMatrix + SetObjectFit | ✅ |
| **Test 11** | EXIF 方向自动识别 | SetOrientation(AUTO) | ✅ |

---

## 🔧 核心文件说明

### ArkTS 层

#### `entry/src/main/ets/pages/Index.ets`
- **功能**: 主入口页面
- **特点**:
  - 使用 NodeContent 方式（推荐）
  - 显示/隐藏 Native UI 控制
  - 简洁清晰，无废弃 API

### C++ 层

#### `entry/src/main/cpp/NormalImageListExample.h`
- **功能**: 包含 11 个 Image 测试用例
- **特点**:
  - 每个用例都有详细注释
  - 涵盖 Image 组件的主要 CAPI
  - 代码经过优化和去重

#### `entry/src/main/cpp/ArkUIImageNode.h`
- **功能**: Image 节点封装类
- **提供方法**:
  - `SetSrc()` - 设置图片源
  - `SetSlice()` - 设置九宫格切片
  - `SetLattice()` - 设置 Lattice
  - `SetImageMatrix()` - 设置变换矩阵
  - `SetObjectFit()` - 设置填充模式
  - `SetOrientation()` - 设置方向
  - `SetAntialiased()` - 设置抗锯齿
  - `SetObjectRepeat()` - 设置重复模式

#### `entry/src/main/cpp/image/image_matrix.cpp`
- **功能**: ImageMatrix 实现
- **提供方法**:
  - `Identity()` - 创建单位矩阵
  - `Translate()` - 平移变换
  - `Rotate()` - 旋转变换
  - `Scale()` - 缩放变换

#### `entry/src/main/cpp/NativeEntry.cpp`
- **功能**: NAPI 入口
- **导出函数**:
  - `createNativeRoot()` - 创建 Native 根节点
  - `destroyNativeRoot()` - 销毁 Native 根节点

---

## 🚀 如何运行

### 前提条件
- DevEco Studio 6.0+
- OpenHarmony API 12+
- NDK 环境已配置

### 编译步骤

1. **打开项目**
   ```bash
   cd arkui_ace_engine/examples/ImageCapiExample
   ```

2. **构建项目**
   ```bash
   hvigorw assembleHap
   ```

3. **安装到设备**
   ```bash
   hdc install entry/build/default/outputs/default/entry-default-signed.hap
   ```

4. **运行测试**
   - 在设备上打开应用
   - 点击 "Show Native UI" 按钮
   - 滚动查看 11 个测试用例

---

## 📖 使用指南

### NodeContent 方式（推荐）

```typescript
import nativeNode from 'libentry.so';
import { NodeContent } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  private rootSlot: NodeContent = new NodeContent();
  
  build() {
    Column() {
      Button('Show Native')
        .onClick(() => {
          nativeNode.createNativeRoot(this.rootSlot);
        })
      
      ContentSlot(this.rootSlot)
    }
  }
}
```

### C++ 创建 Image 组件

```cpp
#include "ArkUIImageNode.h"

auto image = std::make_shared<ArkUIImageNode>();
image->SetSrc("resources/rawfile/startIcon.png");
image->SetWidth(100);
image->SetHeight(100);
list->AddChild(image);
```

---

## 🔍 测试验证

### 验证清单

- [ ] Test 1: 图片正常显示
- [ ] Test 2: 九宫格切片效果正确
- [ ] Test 3-5: Lattice 渲染正常
- [ ] Test 6: 方向旋转正确
- [ ] Test 7: 动态切片响应正常
- [ ] Test 8: Matrix 变换正确
- [ ] Test 9-10: ObjectFit 模式正确
- [ ] Test 11: EXIF 方向识别正确

### 常见问题

**Q: Native 组件不显示？**
- 检查 `libentry.so` 是否正确编译
- 确认 `nativeNode.createNativeRoot()` 已调用
- 查看日志输出

**Q: 图片加载失败？**
- 检查图片路径 `resources/rawfile/startIcon.png`
- 确认资源文件已正确打包
- 查看 onError 回调

**Q: 编译报错？**
- 确保 NDK 环境已配置
- 检查 `CMakeLists.txt` 配置
- 确认头文件路径正确

---

## 📝 代码规范

### 注释要求

所有测试用例必须包含以下注释块：

```cpp
// ========================================
// Test X: 功能名称
// ========================================
// 测试目的：...
// 涉及 API: ...
// 参数说明：...
// 预期结果：...
```

### 命名规范

- ETS 文件：大驼峰，如 `Index.ets`
- C++ 头文件：大驼峰 + `.h`，如 `ArkUIImageNode.h`
- C++ 实现：小写 + `.cpp`，如 `image_matrix.cpp`
- 函数名：大驼峰，如 `CreateImageListExample`
- 变量名：小驼峰，如 `imageNode`

---

## ⚠️ 重要说明

### 已废弃的 API

**XComponent 传统方式已废弃，不再使用：**
- ❌ `XComponent` + `createNativeNode` 方式
- ❌ `OH_NativeXComponent` 相关 API
- ❌ 手动管理 Surface 的方式

**推荐使用 NodeContent 方式：**
- ✅ `NodeContent` + `ContentSlot`
- ✅ `createNativeRoot` / `destroyNativeRoot`
- ✅ 自动管理生命周期

### 迁移指南

如果旧代码使用 XComponent 方式，请参考以下方式迁移：

**旧代码（已废弃）：**
```typescript
XComponent({
  id: 'xcomponent',
  type: 'node',
  libraryname: 'nativeNode'
})
.onLoad(() => {
  nativeNode.createNativeNode('xcomponent');
})
```

**新代码（推荐）：**
```typescript
NodeContent rootSlot = new NodeContent();

Button('Show Native')
  .onClick(() => {
    nativeNode.createNativeRoot(rootSlot);
  })

ContentSlot(rootSlot)
```

---

## 🔗 相关文档

- [Image 组件 API 文档](../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-basic-components-image.md)
- [CAPI 开发指南](../../../docs/zh-cn/application-dev/ui/arkui-native-develop.md)
- [Native Drawing API](../../../docs/zh-cn/application-dev/reference/apis-native-drawing.md)
- [NodeContent 使用指南](../../../docs/zh-cn/application-dev/ui/arkui-nodecontent.md)

---

## 📄 许可证

```
Copyright (c) 2026 Huawei Device Co., Ltd.
Licensed under the Apache License, Version 2.0.
```
