# Sticker 样例使用指南

## 快速开始

### 1. 构建项目

```bash
cd examples/Sticker
./build.sh
```

或者使用 hvigor 直接构建：

```bash
hvigorw assembleHap
```

### 2. 安装到设备

```bash
# 查找生成的 HAP 文件
find entry/build -name "*.hap"

# 安装到设备
hdc install entry/build/default/outputs/default/entry-default-signed.hap
```

### 3. 启动应用

```bash
# hdc shell aa start -a EntryAbility -b com.example.sticker
```

## 功能演示

### 添加贴纸

有两种方式添加贴纸：

1. **从相册选择图片**
   - 点击 "Add Image" 按钮
   - 在弹出的相册界面中选择一张图片
   - 图片会自动添加到画布中心

2. **使用示例贴纸**
   - 点击底部的彩色按钮（1、2、3）
   - 每个按钮会添加不同颜色的示例贴纸

### 操作贴纸

#### 选择贴纸
- 点击任意贴纸，该贴纸会被选中
- 选中的贴纸会显示蓝色虚线边框
- 同时显示操作手柄：
  - 右下角：蓝色圆点（缩放手柄）
  - 顶部：绿色圆点（旋转手柄）
  - 右上角：红色删除图标

#### 移动贴纸
1. 点击并按住贴纸
2. 拖动到目标位置
3. 释放手指

#### 缩放贴纸
1. 选中贴纸
2. 按住右下角的蓝色圆点
3. 拖动来调整大小
4. 最小缩放为 0.5x

#### 旋转贴纸
1. 选中贴纸
2. 按住顶部的绿色圆点
3. 围绕中心旋转

#### 删除贴纸
有两种方式删除选中的贴纸：
- 点击贴纸右上角的红色删除图标
- 点击底部出现的 "Delete" 按钮

#### 清除所有
- 点击标题栏右侧的 "Clear All" 按钮
- 所有贴纸会被清除

## 代码结构说明

### 主要文件

```
Index.ets                    # 贴纸编辑器主页面
  ├─ StickerItem 接口        # 贴纸数据模型
  ├─ addSticker()            # 添加贴纸
  ├─ selectSticker()         # 选择贴纸
  ├─ deleteSelectedSticker() # 删除选中贴纸
  ├─ clearAllStickers()      # 清除所有贴纸
  ├─ selectImageFromGallery() # 从相册选择图片
  └─ StickerComponent()      # 贴纸组件（可拖拽、缩放、旋转）
```

### 关键实现

#### 1. 贴纸数据模型

```typescript
interface StickerItem {
  id: string;                           // 唯一标识
  imageSrc: string | PixelMap | Resource; // 图片源
  x: number;                            // X 坐标
  y: number;                            // Y 坐标
  width: number;                        // 宽度
  height: number;                       // 高度
  rotation: number;                     // 旋转角度（度）
  scale: number;                        // 缩放比例
  isSelected: boolean;                  // 是否选中
}
```

#### 2. 拖拽实现

使用 `PanGesture` 处理拖拽：

```typescript
.gesture(
  PanGesture({ direction: PanDirection.All })
    .onActionStart(() => {
      onSelect(sticker.id);
    })
    .onActionUpdate((event: GestureEvent) => {
      sticker.x += event.offsetX;
      sticker.y += event.offsetY;
      onUpdate(sticker.id, sticker.x, sticker.y, sticker.scale, sticker.rotation);
    })
)
```

#### 3. 缩放实现

```typescript
Circle({ width: 20, height: 20 })
  .fill($r('app.color.sticker_primary'))
  .position({
    x: sticker.width * sticker.scale / 2 - 10,
    y: sticker.height * sticker.scale / 2 - 10
  })
  .gesture(
    PanGesture({ direction: PanDirection.All })
      .onActionUpdate((event: GestureEvent) => {
        const delta = (event.offsetX + event.offsetY) / 2;
        const newScale = Math.max(0.5, sticker.scale + delta / 100);
        sticker.scale = newScale;
        onUpdate(sticker.id, sticker.x, sticker.y, sticker.scale, sticker.rotation);
      })
  )
```

#### 4. 旋转实现

```typescript
Circle({ width: 20, height: 20 })
  .fill(Color.Green)
  .position({
    x: sticker.width * sticker.scale / 2 - 10,
    y: -sticker.height * sticker.scale / 2 - 10
  })
  .gesture(
    PanGesture({ direction: PanDirection.All })
      .onActionUpdate((event: GestureEvent) => {
        const centerX = sticker.x;
        const centerY = sticker.y;
        const angle = Math.atan2(
          sticker.y + event.offsetY - centerY,
          sticker.x + event.offsetX - centerX
        );
        sticker.rotation = angle * 180 / Math.PI;
        onUpdate(sticker.id, sticker.x, sticker.y, sticker.scale, sticker.rotation);
      })
  )
```

## 自定义开发

### 修改画布大小

在 `Index.ets` 中修改状态变量：

```typescript
@State private canvasWidth: number = 360;
@State private canvasHeight: number = 600;
```

### 添加更多示例贴纸

修改 `sampleImages` 数组并添加相应的图片资源：

```typescript
private sampleImages: string[] = [
  'common/images/star.png',
  'common/images/heart.png',
  'common/images/smile.png',
  'common/images/crown.png',  // 新增
  'common/images/glasses.png' // 新增
];
```

### 修改贴纸默认大小

在 `addSticker` 方法中修改：

```typescript
const newSticker: StickerItem = {
  // ...
  width: 150,  // 默认 100，改为 150
  height: 150, // 默认 100，改为 150
  // ...
};
```

### 添加保存功能

可以使用 Canvas 组件将贴纸保存为图片：

```typescript
async saveCanvas() {
  // 创建离屏 Canvas
  const canvas = new OffscreenCanvas(this.canvasWidth, this.canvasHeight);
  const ctx = canvas.getContext('2d');

  // 绘制背景
  ctx.fillStyle = '#FFFFFF';
  ctx.fillRect(0, 0, this.canvasWidth, this.canvasHeight);

  // 绘制每个贴纸
  for (const sticker of this.stickerList) {
    ctx.save();
    ctx.translate(sticker.x + sticker.width / 2, sticker.y + sticker.height / 2);
    ctx.rotate(sticker.rotation * Math.PI / 180);
    ctx.scale(sticker.scale, sticker.scale);
    // 绘制图片
    ctx.drawImage(sticker.imageSrc, -sticker.width / 2, -sticker.height / 2);
    ctx.restore();
  }

  // 生成图片
  const imageData = canvas.toDataURL();
  // 保存到相册或文件系统
}
```

## 调试技巧

### 查看日志

```bash
# 查看应用日志
hdc shell hilog | grep Sticker

# 清除日志
hdc shell hilog -r
```

### 常见问题

1. **贴纸不显示**
   - 检查图片路径是否正确
   - 确认图片资源已添加到 `media` 目录

2. **手势不响应**
   - 确认手势没有与父组件冲突
   - 检查 `gesture` 修饰符的顺序

3. **性能问题**
   - 限制同时显示的贴纸数量
   - 优化图片大小
   - 使用 `PixelMap` 而非 URI

## 扩展功能建议

1. **文本贴纸** - 添加可编辑的文本贴纸
2. **滤镜效果** - 为贴纸添加滤镜（亮度、对比度等）
3. **图层管理** - 支持调整贴纸的显示顺序
4. **撤销/重做** - 记录操作历史
5. **保存功能** - 将画布保存为图片
6. **分享功能** - 分享到社交应用
7. **动画效果** - 添加贴纸的入场/出场动画

---

*最后更新: 2026-02-10*
