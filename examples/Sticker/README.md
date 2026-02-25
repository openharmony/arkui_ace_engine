# Sticker Example Application

> **版本**: v1.0
> **更新时间**: 2026-02-10
> **语言**: ArkTS (TypeScript)

---

## 概述

这是一个演示贴纸（Sticker）功能的样例应用，展示了如何在 OpenHarmony 上实现图片贴纸编辑器，包括添加图片、拖拽、缩放、旋转等功能。

## 功能特性

### 核心功能

1. **添加图片**
   - 从相册选择图片作为贴纸
   - 使用预设的示例贴纸（彩色方块）

2. **贴纸操作**
   - **拖拽移动**: 点击并拖动贴纸可以移动位置
   - **缩放大小**: 使用蓝色圆角手柄可以缩放贴纸
   - **旋转**: 使用绿色圆角手柄可以旋转贴纸
   - **选择**: 点击贴纸进行选择，显示操作手柄
   - **删除**: 选中后点击删除按钮或红色删除图标

3. **画布管理**
   - 清除所有贴纸
   - 多个贴纸叠加显示
   - 支持触控手势交互

## 目录结构

```
Sticker/
├── AppScope/                           # 应用级配置和资源
├── entry/                              # 主模块
│   ├── src/main/
│   │   ├── ets/                        # ArkTS 源代码
│   │   │   ├── entryability/           # 应用入口
│   │   │   │   └── EntryAbility.ets
│   │   │   └── pages/                  # 页面
│   │   │       └── Index.ets           # 贴纸编辑器主页面
│   │   ├── resources/                  # 资源文件
│   │   │   ├── base/
│   │   │   │   ├── element/            # 字符串、颜色等资源
│   │   │   │   ├── media/              # 图片、图标资源
│   │   │   │   └── profile/            # 配置文件
│   │   │   ├── en_US/                  # 英文资源
│   │   │   └── zh_CN/                  # 中文资源
│   │   └── module.json5                # 模块配置
│   └── build-profile.json5             # 构建配置
├── build-profile.json5                 # 应用构建配置
├── hvigorfile.ts                       # Hvigor 构建脚本
├── oh-package.json5                    # 包依赖配置
└── README.md                           # 本文件
```


*最后更新: 2026-02-10*
