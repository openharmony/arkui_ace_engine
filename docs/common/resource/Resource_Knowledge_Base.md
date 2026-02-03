# ArkUI 资源系统完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-03
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [系统架构](#系统架构)
3. [核心组件详解](#核心组件详解)
4. [资源类型与分类](#资源类型与分类)
5. [资源解析流程](#资源解析流程)
6. [三大解析入口](#三大解析入口)
7. [缓存机制](#缓存机制)
8. [配置变化响应](#配置变化响应)
9. [完整 API 清单](#完整-api-清单)
10. [关键实现细节](#关键实现细节)
11. [使用示例](#使用示例)
12. [调试指南](#调试指南)
13. [常见问题](#常见问题)
14. [附录](#附录)

---

## 概述

### 资源系统定位

**资源系统**（Resource System）是 OpenHarmony ArkUI 框架中的**应用资源管理核心**，提供统一的资源访问接口，支持应用资源（字符串、颜色、图片、布局等）的加载、解析、缓存和动态更新。

**核心价值**：
- 📦 **统一接口** - 提供统一的资源访问 API
- 🔄 **动态更新** - 支持配置变化（深色模式、语言、分辨率）时的资源重载
- 💾 **高效缓存** - LRU 缓存机制提升资源访问性能
- 🌍 **多语言支持** - 完整的国际化（i18n）和本地化（l10n）支持
- 🎨 **主题适配** - 深色/浅色模式自动切换
- 🏗️ **模块化解耦** - 支持多 bundle/module 资源隔离

### 技术架构特点

| 特性 | 说明 |
|------|------|
| **设计模式** | 单例模式 + 适配器模式 + 包装器模式 |
| **缓存策略** | LRU（Least Recently Used）缓存 |
| **线程安全** | `std::shared_mutex` 读写锁 |
| **资源隔离** | 按 bundleName.moduleName.instanceId 三元组隔离 |
| **配置响应** | 配置变化监听器模式 |

### 代码规模

```
frameworks/core/common/resource/    # 核心资源管理
├── resource_manager.h/cpp         # 资源管理器（单例）
├── resource_wrapper.h/cpp         # 资源包装器
├── resource_parse_utils.h/cpp     # 资源解析工具
├── pattern_resource_manager.h/cpp # Pattern 层资源管理
└── resource_object.h              # 资源对象定义

adapter/ohos/osal/                 # 平台适配层
├── resource_adapter_impl.h/cpp    # 资源适配器实现
└── resource_adapter_impl_v2.h/cpp # V2 版本适配器

frameworks/bridge/declarative_frontend/  # 前端桥接层
├── jsview/js_view_abstract.cpp    # JS 资源解析
└── engine/jsi/nativeModule/arkts_utils.cpp  # Modifier 资源解析

interfaces/napi/kits/utils/        # NAPI 接口
└── napi_utils.cpp                 # NAPI 资源解析
```

---

## 系统架构

### 整体架构图

```
┌─────────────────────────────────────────────────────────────────┐
│                        应用层 (ArkTS)                            │
│                                                                  │
│  $r('app.string.hello')  $r('sys.color.primary')  $r('app.media.icon')  │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ↓
┌─────────────────────────────────────────────────────────────────┐
│                      前端桥接层 (Bridge Layer)                    │
│                                                                  │
│  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────┐ │
│  │ JS 解析入口       │  │ Modifier 解析入口 │  │ NAPI 解析入口 │ │
│  │ js_view_abstract │  │ arkts_utils      │  │ napi_utils   │ │
│  └────────┬─────────┘  └────────┬─────────┘  └──────┬───────┘ │
│           │                     │                     │          │
│           └─────────────────────┴─────────────────────┘          │
│                                 ↓                                │
│                 CompleteResourceObject()                         │
│                   解析资源对象 (id, type, params)                │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ↓
┌─────────────────────────────────────────────────────────────────┐
│                    核心资源层 (Core Resource)                     │
│                                                                  │
│  ┌────────────────────────────────────────────────────────┐    │
│  │            ResourceManager (单例)                        │    │
│  │  ┌──────────────────────────────────────────────────┐  │    │
│  │  │  ResourceAdapter 缓存 (LRU, 默认容量 3)            │  │    │
│  │  │  - bundleName.moduleName.instanceId → ResourceAdapter │  │    │
│  │  └──────────────────────────────────────────────────┘  │    │
│  └────────────────────────────────────────────────────────┘    │
│                                 ↓                                │
│  ┌────────────────────────────────────────────────────────┐    │
│  │              ResourceWrapper (统一访问接口)              │    │
│  │  - GetColor/GetString/GetMedia/GetRawfile...           │    │
│  └────────────────────────────────────────────────────────┘    │
│                                 ↓                                │
│  ┌────────────────────────────────────────────────────────┐    │
│  │          ResourceParseUtils (解析工具)                   │    │
│  │  - ParseResColor/ParseResString/ParseResDimension...    │    │
│  └────────────────────────────────────────────────────────┘    │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ↓
┌─────────────────────────────────────────────────────────────────┐
│                  平台适配层 (Adapter Layer)                       │
│                                                                  │
│  ┌──────────────────────┐  ┌──────────────────────────────┐    │
│  │  ResourceAdapter     │  │  ThemeConstants              │    │
│  │  (资源解耦模式)       │  │  (传统主题模式)               │    │
│  │                      │  │                              │    │
│  │  - GetColorById      │  │  - GetColor                  │    │
│  │  - GetStringByName   │  │  - GetDimension              │    │
│  │  - GetMediaPath      │  │  - GetString                 │    │
│  └──────────┬───────────┘  └────────────┬─────────────────┘    │
│             │                            │                       │
│             ↓                            ↓                       │
│  ┌────────────────────────────────────────────────────┐        │
│  │     ResourceAdapterImpl / ResourceAdapterImplV2    │        │
│  │     (OHOS 平台实现 - GlobalResourceManager)        │        │
│  └────────────────────────────────────────────────────┘        │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ↓
┌─────────────────────────────────────────────────────────────────┐
│                   OpenHarmony 资源管理子系统                       │
│                                                                  │
│  Global::ResourceManager (全局资源管理器)                         │
│  - 加载 resources.index                                          │
│  - 解析资源限定词（语言、地区、设备类型等）                        │
│  - 最佳匹配资源选择                                              │
└─────────────────────────────────────────────────────────────────┘
```

### 核心类继承关系

```
AceType (基础类型)
    │
    ├── ResourceAdapter (虚接口)
    │     ├── ResourceAdapterImpl (OHOS 实现)
    │     └── ResourceAdapterImplV2 (OHOS V2 实现)
    │
    ├── ResourceWrapper (统一资源访问)
    │
    ├── ResourceObject (资源对象)
    │
    ├── PatternResourceManager (Pattern 层资源管理)
    │
    └── PropertyValueBase (属性值基类)

ThemeStyle (主题样式)
    └── ResourceThemeStyle (资源主题样式)
```

---

## 核心组件详解

### 1. ResourceManager（资源管理器）

**源码位置**：`frameworks/core/common/resource/resource_manager.h:50`

#### 核心职责

- 管理多个 ResourceAdapter 实例（按 bundleName.moduleName.instanceId 隔离）
- 提供 LRU 缓存机制（默认容量 3）
- 线程安全的资源访问（`std::shared_mutex`）
- 配置变化通知（深色模式、语言等）
- 资源加载错误记录（最多 100 条）

#### 关键方法

```cpp
class ResourceManager final : public AceType {
public:
    // 获取单例
    static ResourceManager& GetInstance();

    // 获取或创建 ResourceAdapter
    RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(
        const RefPtr<ResourceObject>& resourceObject);

    // 添加 ResourceAdapter 到缓存
    void AddResourceAdapter(const std::string& bundleName,
                           const std::string& moduleName,
                           int32_t instanceId,
                           RefPtr<ResourceAdapter>& resourceAdapter,
                           bool replace = false);

    // 获取 ResourceAdapter
    RefPtr<ResourceAdapter> GetResourceAdapter(
        const std::string& bundleName,
        const std::string& moduleName,
        int32_t instanceId);

    // 移除 ResourceAdapter
    void RemoveResourceAdapter(const std::string& bundleName,
                              const std::string& moduleName,
                              int32_t instanceId);

    // 更新资源配置
    void UpdateResourceConfig(const std::string& bundleName,
                             const std::string& moduleName,
                             int32_t instanceId,
                             const ResourceConfiguration& config,
                             bool themeFlag = false);

    // 更新颜色模式
    void UpdateColorMode(const std::string& bundleName,
                        const std::string& moduleName,
                        int32_t instanceId,
                        ColorMode colorMode);

    // 设置缓存大小
    void SetResourceCacheSize(size_t cacheSize);

    // 转储资源加载错误
    void DumpResLoadError();
};
```

#### 缓存键生成

```cpp
// resource_manager.h:60-66
std::string MakeCacheKey(const std::string& bundleName,
                        const std::string& moduleName,
                        int32_t instanceId)
{
    if (bundleName.empty() && moduleName.empty()) {
        return std::to_string(instanceId);
    }
    return bundleName + "." + moduleName + "." + std::to_string(instanceId);
}
```

**示例**：
- `"com.example.app.entry.12345"` - 完整键
- `"12345"` - 默认键（bundleName 和 moduleName 为空）

#### LRU 缓存机制

```cpp
// resource_manager.h:202-204
std::atomic<size_t> capacity_ = 3;  // 默认容量
std::list<CacheNode<RefPtr<ResourceAdapter>>> cacheList_;  // LRU 链表
std::unordered_map<std::string,
    std::list<CacheNode<RefPtr<ResourceAdapter>>>::iterator> cache_;  // 缓存映射
```

**LRU 策略**：
- 访问时移动到链表头部
- 超过容量时删除链表尾部
- 使用 `CountLimitLRU` 工具类管理

---

### 2. ResourceAdapter（资源适配器）

**源码位置**：`frameworks/core/components/theme/resource_adapter.h:34`

#### 核心职责

- 虚接口，定义资源访问的标准 API
- 平台无关的资源访问抽象
- 支持按 ID 和按名称两种访问方式

#### 核心接口分类

##### 颜色资源

```cpp
// 按资源 ID 获取
virtual Color GetColor(uint32_t resId) = 0;

// 按资源名称获取
virtual Color GetColorByName(const std::string& resName);

// 检查是否存在深色模式资源
virtual bool ExistDarkResById(const std::string& resourceId);
virtual bool ExistDarkResByName(const std::string& resourceName,
                                const std::string& resourceType);
```

##### 尺寸资源

```cpp
virtual Dimension GetDimension(uint32_t resId) = 0;
virtual Dimension GetDimensionByName(const std::string& resName);
```

##### 字符串资源

```cpp
virtual std::string GetString(uint32_t resId) = 0;
virtual std::string GetStringByName(const std::string& resName);

// 复数字符串（带数量参数）
virtual std::string GetPluralString(uint32_t resId, int quantity);
virtual std::string GetPluralStringByName(const std::string& resName, int quantity);

// 字符串数组
virtual std::vector<std::string> GetStringArray(uint32_t resId) const;
virtual std::vector<std::string> GetStringArrayByName(const std::string& resName) const;
```

##### 数值资源

```cpp
virtual int32_t GetInt(uint32_t resId) = 0;
virtual int32_t GetIntByName(const std::string& resName);

virtual double GetDouble(uint32_t resId) = 0;
virtual double GetDoubleByName(const std::string& resName);

virtual bool GetBoolean(uint32_t resId) const;
virtual bool GetBooleanByName(const std::string& resName) const;

virtual std::vector<uint32_t> GetIntArray(uint32_t resId) const;
virtual std::vector<uint32_t> GetIntArrayByName(const std::string& resName) const;
```

##### 媒体资源

```cpp
virtual std::shared_ptr<Media::PixelMap> GetPixelMap(uint32_t resId);
virtual std::string GetMediaPath(uint32_t resId);
virtual std::string GetMediaPathByName(const std::string& resName);

// 获取媒体数据
virtual bool GetMediaData(uint32_t resId, size_t& len,
                         std::unique_ptr<uint8_t[]>& dest);
virtual bool GetMediaData(const std::string& resName, size_t& len,
                         std::unique_ptr<uint8_t[]>& dest);
```

##### Rawfile 资源

```cpp
virtual std::string GetRawfile(const std::string& fileName);

// 获取 Rawfile 描述符（文件描述符方式）
virtual bool GetRawFD(const std::string& rawfileName,
                     RawfileDescription& rawfileDescription) const;

// 获取 Rawfile 数据
virtual bool GetRawFileData(const std::string& rawFile, size_t& len,
                           std::unique_ptr<uint8_t[]>& dest);
```

##### Symbol 资源

```cpp
virtual uint32_t GetSymbolByName(const char *name) const;
virtual uint32_t GetSymbolById(uint32_t resId) const;
```

##### 主题样式

```cpp
virtual RefPtr<ThemeStyle> GetTheme(int32_t themeId);
virtual RefPtr<ThemeStyle> GetPatternByName(const std::string& patternName);
```

#### 工厂方法

```cpp
// 创建 ResourceAdapter（根据配置决定使用 V1 或 V2）
static RefPtr<ResourceAdapter> Create();
static RefPtr<ResourceAdapter> CreateV2();

// 创建新的 ResourceAdapter（指定 bundle/module）
static RefPtr<ResourceAdapter> CreateNewResourceAdapter(
    const std::string& bundleName,
    const std::string& moduleName);
```

---

### 3. ResourceWrapper（资源包装器）

**源码位置**：`frameworks/core/common/resource/resource_wrapper.h:34`

#### 核心职责

- 统一 ResourceAdapter 和 ThemeConstants 的访问接口
- 支持资源解耦模式（`SystemProperties::GetResourceDecoupling()`）
- 运行时选择使用 ResourceAdapter 或 ThemeConstants

#### 设计模式

```cpp
class ResourceWrapper : public AceType {
public:
    ResourceWrapper(RefPtr<ThemeConstants>& themeConstants,
                   RefPtr<ResourceAdapter>& resourceAdapter);

    // 所有资源访问方法都遵循以下模式：
    Color GetColor(uint32_t key) const {
        if (SystemProperties::GetResourceDecoupling()) {
            CHECK_NULL_RETURN(resourceAdapter_, Color());
            return resourceAdapter_->GetColor(key);
        }
        CHECK_NULL_RETURN(themeConstants_, Color());
        return themeConstants_->GetColor(key);
    }

    // ... 其他方法类似
};
```

#### 模式切换机制

| 模式 | 使用的底层接口 | 配置开关 |
|------|---------------|---------|
| **资源解耦模式** | ResourceAdapter | `SystemProperties::GetResourceDecoupling() == true` |
| **传统主题模式** | ThemeConstants | `SystemProperties::GetResourceDecoupling() == false` |

---

### 4. ResourceObject（资源对象）

**源码位置**：`interfaces/inner_api/ace_kit/include/ui/resource/resource_object.h:35`

#### 数据结构

```cpp
class ResourceObject : public AceType {
private:
    int32_t id_;              // 资源 ID（-1 表示使用名称访问）
    int32_t type_;            // 资源类型（对应 ResourceType 枚举）
    int32_t instanceId_;      // 实例 ID（UIContent 实例）
    Color color_;             // 缓存的颜色值
    std::vector<ResourceObjectParams> params_;  // 资源参数
    std::string bundleName_;  // Bundle 名称
    std::string moduleName_;  // Module 名称
    std::string nodeTag_;     // 节点标签（用于调试）
    ColorMode colorMode_;     // 颜色模式
    bool isResource_;         // 是否为资源对象
    bool hasDarkRes_;         // 是否有深色模式资源
};
```

#### 资源参数类型

```cpp
enum class ResourceObjectParamType {
    NONE,    // 无类型
    INT,     // 整数
    STRING,  // 字符串
    FLOAT    // 浮点数
};

struct ResourceObjectParams {
    std::optional<std::string> value;
    ResourceObjectParamType type = ResourceObjectParamType::NONE;
};
```

#### 典型使用场景

```cpp
// 场景 1: 按 ID 访问资源
ResourceObject obj(resId, resType, params, bundleName, moduleName, instanceId);
Color color = ResourceWrapper->GetColor(obj.GetId());

// 场景 2: 按名称访问资源（id = -1）
ResourceObject obj(bundleName, moduleName, instanceId);
obj.GetParams()[0].value = "app.color.primary";
Color color = ResourceWrapper->GetColorByName(obj.GetParams()[0].value.value());
```

---

### 5. ResourceParseUtils（资源解析工具）

**源码位置**：`frameworks/core/common/resource/resource_parse_utils.h:45`

#### 核心职责

- 将 ResourceObject 解析为具体类型（Color、String、Dimension 等）
- 处理深色模式颜色反转
- 提供静态工具方法，无状态

#### 解析方法清单

##### 颜色解析

```cpp
// 解析为 Color
static bool ParseResColor(const RefPtr<ResourceObject>& resObj, Color& result);

// 解析为 Color（支持颜色模式）
static bool ParseResColorWithColorMode(const RefPtr<ResourceObject>& resObj,
                                      Color& result,
                                      const ColorMode& colorMode);

// 从 Color 完成 ResourceObject
static void CompleteResourceObjectFromColor(RefPtr<ResourceObject>& resObj,
                                           Color& color,
                                           const std::string& nodeTag);
```

##### 字符串解析

```cpp
static bool ParseResString(const RefPtr<ResourceObject>& resObj, std::string& result);
static bool ParseResString(const RefPtr<ResourceObject>& resObj, std::u16string& result);
```

##### 数值解析

```cpp
static bool ParseResInteger(const RefPtr<ResourceObject>& resObj, int32_t& result);
static bool ParseResInteger(const RefPtr<ResourceObject>& resObj, uint32_t& result);

static bool ParseResDouble(const RefPtr<ResourceObject>& resObj, double& result);
static bool ParseResBool(const RefPtr<ResourceObject>& resObj, bool& result);
```

##### 尺寸解析

```cpp
// 解析为 CalcDimension（通用）
static bool ParseResResource(const RefPtr<ResourceObject>& resObj, CalcDimension& result);

// 解析为 Dimension（支持不同单位）
static bool ParseResDimensionNG(const RefPtr<ResourceObject>& resObj,
                               CalcDimension& result,
                               DimensionUnit defaultUnit,
                               bool isSupportPercent = true);

// 特定单位解析
static bool ParseResDimensionVp(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
static bool ParseResDimensionFp(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
static bool ParseResDimensionPx(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
```

##### 数组解析

```cpp
static bool ParseResIntegerArray(const RefPtr<ResourceObject>& resObj,
                                std::vector<uint32_t>& result);
static bool ParseResStrArray(const RefPtr<ResourceObject>& resObj,
                            std::vector<std::string>& result);
```

##### 媒体解析

```cpp
static bool ParseResMedia(const RefPtr<ResourceObject>& resObj, std::string& result);
```

##### 模板解析方法

```cpp
template<class T>
static bool ConvertFromResObjNG(const RefPtr<ResourceObject>& resObj, T& result);

template<class T>
static bool ConvertFromResObj(const RefPtr<ResourceObject>& resObj, T& result);
```

---

### 6. PatternResourceManager（Pattern 层资源管理器）

**源码位置**：`frameworks/core/common/resource/pattern_resource_manager.h:72`

#### 核心职责

- 管理 Pattern 层的资源绑定
- 支持配置变化时的资源重载
- 提供属性值更新回调机制

#### 数据结构

```cpp
// 属性值类型
enum class ValueType {
    UNKNOWN = 0,
    CALDIMENSION,   // 计算尺寸
    COLOR,          // 颜色
    DOUBLE,         // 双精度浮点
    DIMENSION,      // 尺寸
    FLOAT,          // 浮点
    FONT_WEIGHT,    // 字重
    MEDIA,          // 媒体
    STRING,         // 字符串
    U16STRING,      // UTF-16 字符串
    VECTOR_STRING   // 字符串向量
};

// 变体值类型
using VariantValue = std::variant<std::string, std::u16string, float, double,
                                 Color, CalcDimension, std::vector<std::string>,
                                 FontWeight>;

// 属性值基类
class PropertyValueBase : public virtual AceType {
    VariantValue value_;
    ValueType valueType_;
};
```

#### 核心方法

```cpp
class PatternResourceManager final : public AceType {
public:
    // 添加资源（带更新回调）
    void AddResource(const std::string& key,
                    const RefPtr<ResourceObject>& resObj,
                    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc);

    // 移除资源
    void RemoveResource(const std::string& key);

    // 重载所有资源（配置变化时调用）
    void ReloadResources();

    // 检查是否为空
    bool Empty();

    // 解析属性值
    void ParsePropertyValue(const RefPtr<ResourceObject>& resObj,
                           RefPtr<PropertyValueBase> value);

    // 注册资源（类型安全）
    template<typename T>
    void RegisterResource(std::function<void(const std::string&, const RefPtr<PropertyValueBase>&)>&& propUpdateFunc,
                         const std::string& key,
                         const RefPtr<ResourceObject>& resObj,
                         T value);
};
```

---

## 资源类型与分类

### ResourceType 枚举

**源码位置**：`frameworks/core/common/resource/resource_parse_utils.h:30`

```cpp
enum class ResourceType : uint32_t {
    COLOR = 10001,      // 颜色资源
    FLOAT,              // 浮点数资源
    STRING,             // 字符串资源
    PLURAL,             // 复数字符串资源
    BOOLEAN,            // 布尔值资源
    INTARRAY,           // 整数数组资源
    INTEGER,            // 整数资源
    PATTERN,            // 模式资源
    STRARRAY,           // 字符串数组资源

    MEDIA = 20000,      // 媒体资源
    RAWFILE = 30000,    // Rawfile 资源
    SYMBOL = 40000      // Symbol 图标资源
};
```

### 资源分类与用途

| 分类 | 资源类型 | 用途 | 示例 |
|------|---------|------|------|
| **颜色** | COLOR | 文字颜色、背景色、边框色 | `app.color.primary`, `sys.color.background` |
| **字符串** | STRING | 按钮文本、提示信息、标题 | `app.string.ok`, `app.string.cancel` |
| **复数** | PLURAL | 带数量的字符串 | `app.plural.items` (1 item, 2 items) |
| **字符串数组** | STRARRAY | 选项列表、标签页 | `app.strarray.weekdays` |
| **数值** | INTEGER, FLOAT, DOUBLE | 尺寸值、最大值、最小值 | `app.integer.max_length` |
| **整数数组** | INTARRAY | 边距、间距组合 | `app.intarray.padding` |
| **布尔值** | BOOLEAN | 开关状态、特性标志 | `app.boolean.enable_feature` |
| **尺寸** | (通过 STRING 解析) | 宽度、高度、字体大小 | `app.string.font_size` |
| **媒体** | MEDIA | 图片、图标、动画 | `app.media.icon`, `app.media.background` |
| **Rawfile** | RAWFILE | 原始文件（JSON、音频等） | `rawfile/config.json` |
| **Symbol** | SYMBOL | Symbol 图标 | `app.symbol.home` |
| **模式** | PATTERN | 主题模式 | `app.pattern.card_style` |

### 资源限定词

OpenHarmony 支持的资源限定词（影响资源匹配）：

| 限定词类别 | 示例 | 影响的资源类型 |
|----------|------|--------------|
| 语言 | `zh_CN`, `en_US` | STRING, PLURAL, STRARRAY |
| 地区 | `CN`, `US` | 所有资源 |
| 设备类型 | `phone`, `tablet`, `2in1` | DIMENSION, MEDIA |
| 方向 | `vertical`, `horizontal` | DIMENSION, MEDIA |
| 深色模式 | `dark`, `light` | COLOR |
| 屏幕密度 | `ldpi`, `xhdpi`, `xxhdpi` | DIMENSION, MEDIA |
| 设备特性 | `foldable`, `watch` | 所有资源 |

---

## 资源解析流程

### 完整解析流程图

```
┌─────────────────────────────────────────────────────────────┐
│  前端 ArkTS 代码                                             │
│                                                             │
│  Text().fontColor($r('app.color.primary'))                  │
│  Image().src($r('app.media.icon'))                          │
└──────────────────────────┬──────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  步骤 1: JavaScript 资源对象识别                             │
│                                                             │
│  $r('app.color.primary')                                    │
│    ↓                                                        │
│  JSRef<JSObject> jsRes = {                                  │
│    id: "app.color.primary",                                 │
│    type: -1,  // UNKNOWN                                    │
│    params: ["app.color.primary"]                            │
│  }                                                          │
└──────────────────────────┬──────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  步骤 2: CompleteResourceObject (资源对象补全)               │
│  源码：js_view_abstract.cpp:6179                            │
│                                                             │
│  JSViewAbstract::CompleteResourceObject(jsRes)              │
│    ↓                                                        │
│  解析资源路径 → 提取 bundleName, moduleName, resName, resType│
│    ↓                                                        │
│  创建 ResourceObject:                                       │
│    - id_: -1 (使用名称访问)                                 │
│    - type_: ResourceType::COLOR                             │
│    - bundleName_: "com.example.app"                         │
│    - moduleName_: "entry"                                   │
│    - params_: [{"app.color.primary", STRING}]              │
└──────────────────────────┬──────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  步骤 3: 获取 ResourceAdapter                               │
│  源码：resource_manager.cpp:33                              │
│                                                             │
│  ResourceManager::GetInstance().GetOrCreateResourceAdapter( │
│      resourceObject)                                        │
│    ↓                                                        │
│  1. 尝试从缓存获取（LRU 查找）                               │
│  2. 若未命中，创建新的 ResourceAdapter                      │
│  3. 添加到 LRU 缓存                                         │
└──────────────────────────┬──────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  步骤 4: 创建 ResourceWrapper                               │
│  源码：resource_parse_utils.cpp                             │
│                                                             │
│  auto resourceWrapper =                                     │
│      AceType::MakeRefPtr<ResourceWrapper>(                  │
│          themeConstants, resourceAdapter);                  │
└──────────────────────────┬──────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  步骤 5: 解析资源值                                          │
│  源码：resource_parse_utils.cpp                             │
│                                                             │
│  ResourceParseUtils::ParseResColor(resourceObject, color)   │
│    ↓                                                        │
│  resourceWrapper->GetColorByName("app.color.primary")       │
│    ↓                                                        │
│  ResourceAdapter::GetColorByName(resName)                   │
│    ↓                                                        │
│  Global::ResourceManager::GetStringByName(resName)          │
└──────────────────────────┬──────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────┐
│  步骤 6: 返回解析后的值                                      │
│                                                             │
│  Color color = Color(0xFF0000FF);  // 蓝色                  │
│    ↓                                                        │
│  应用到组件属性                                              │
│  Text().fontColor(color)                                    │
└─────────────────────────────────────────────────────────────┘
```

### 资源键解析详解

#### $r() 格式解析

**支持的格式**：

```
$r('app.color.primary')
$r('sys.color.ohos_id_color_primary')
$r('[com.example.hsp].color.custom')
```

**解析逻辑** (`js_view_abstract.cpp:6137`):

```cpp
bool JSViewAbstract::ParseDollarResource(
    const JSRef<JSVal>& jsValue,
    std::string& targetModule,
    ResourceType& resType,
    std::string& resName,
    bool isParseType)
{
    // 1. 检查是否为字符串
    if (!jsValue->IsString()) {
        return false;
    }

    // 2. 获取资源路径
    std::string resPath = jsValue->ToString();

    // 3. 按 '.' 分割
    std::vector<std::string> tokens;
    StringUtils::StringSplitter(resPath, '.', tokens);

    // 4. 验证格式：必须是 3 段
    if (tokens.size() != 3) {
        return false;
    }

    // 5. 解析第一段：模块名
    std::string maybeModuleName = tokens[0];
    if (maybeModuleName[0] == '[' && maybeModuleName.back() == ']') {
        // HSP 模块：[com.example.hsp]
        targetModule = maybeModuleName.substr(1, maybeModuleName.size() - 2);
    } else if (tokens[0] == "app" || tokens[0] == "sys") {
        // app 或 sys：使用 moduleName 传入值
        targetModule = tokens[0];
    } else {
        return false;
    }

    // 6. 解析第二段：资源类型
    if (!ConvertResourceType(tokens[1], resType)) {
        return false;
    }

    // 7. 第三段：资源名称
    resName = resPath;

    return true;
}
```

**ConvertResourceType 映射**:

```cpp
// 资源类型字符串 → ResourceType 枚举
{
    {"color", ResourceType::COLOR},
    {"float", ResourceType::FLOAT},
    {"string", ResourceType::STRING},
    {"plural", ResourceType::PLURAL},
    {"pattern", ResourceType::PATTERN},
    {"boolean", ResourceType::BOOLEAN},
    {"integer", ResourceType::INTEGER},
    {"strarray", ResourceType::STRARRAY},
    {"intarray", ResourceType::INTARRAY},
    {"media", ResourceType::MEDIA},
}
```

---

## 三大解析入口

### 1. JS 解析入口（js_view_abstract.cpp）

**源码位置**：`frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp`

#### 核心函数

##### CompleteResourceObject

```cpp
// js_view_abstract.cpp:6179
void JSViewAbstract::CompleteResourceObject(JSRef<JSObject>& jsObj)
{
    std::string bundleName;
    std::string moduleName;
    int32_t resId = -1;
    int32_t resType = UNKNOWN_RESOURCE_TYPE;

    CompleteResourceObjectInner(jsObj, bundleName, moduleName, resId, resType, resIdJsValue);
}
```

**输入格式**：
```javascript
{
  "id": "app.color.primary",
  "type": -1,  // UNKNOWN
  "params": ["app.color.primary"],
  "bundleName": "com.example.app",
  "moduleName": "entry"
}
```

**输出**：
- 补全 `resId`, `resType`
- 解析 `bundleName`, `moduleName`
- 识别资源类型

##### ParseDollarResource

```cpp
// js_view_abstract.cpp:6137
bool JSViewAbstract::ParseDollarResource(
    const JSRef<JSVal>& jsValue,
    std::string& targetModule,
    ResourceType& resType,
    std::string& resName,
    bool isParseType)
{
    // 解析 $r('app.color.primary') 格式
}
```

**调用链**：
```
JSViewAbstract::ParseJsColor()
    → JSViewAbstract::ParseColor()
        → JSViewAbstract::CompleteResourceObject()
            → JSViewAbstract::ParseDollarResource()
```

---

### 2. Modifier 解析入口（arkts_utils.cpp）

**源码位置**：`frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.cpp`

#### 核心函数

##### CheckDarkResource

```cpp
// arkts_utils.cpp:229
bool ArkTSUtils::CheckDarkResource(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::GetResourceDecoupling() || !resObj) {
        return false;
    }

    auto resourceAdapter = ResourceManager::GetInstance()
        .GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resourceAdapter, false);

    int32_t resId = resObj->GetId();
    bool hasDarkRes = false;

    auto params = resObj->GetParams();
    if (resId == -1 && !params.empty() && params.back().value.has_value()) {
        // 按名称检查
        std::vector<std::string> splitter;
        StringUtils::StringSplitter(params.back().value.value(), '.', splitter);
        hasDarkRes = resourceAdapter->ExistDarkResByName(
            splitter.back(),
            std::to_string(resObj->GetType()));
    } else {
        // 按 ID 检查
        hasDarkRes = resourceAdapter->ExistDarkResById(std::to_string(resId));
    }

    return hasDarkRes;
}
```

##### CompleteResourceObjectFromColor

```cpp
// arkts_utils.cpp:251
void ArkTSUtils::CompleteResourceObjectFromColor(
    RefPtr<ResourceObject>& resObj,
    Color& color,
    bool state,
    const NodeInfo& nodeInfo)
{
    if (!state || !SystemProperties::ConfigChangePerform()) {
        return;
    }

    // 检查深色模式
    bool hasDarkRes = CheckDarkResource(resObj);

    // 处理颜色反转
    if (nodeInfo.localColorMode == ColorMode::DARK) {
        if (!hasDarkRes) {
            color = Color(invertFunc(color.GetValue()));
        }
    } else if (nodeInfo.localColorMode == ColorMode::LIGHT) {
        if (hasDarkRes) {
            color = Color(invertFunc(color.GetValue()));
        }
    }

    // 缓存到 ResourceObject
    if (!resObj) {
        resObj = AceType::MakeRefPtr<ResourceObject>(
            bundleName, moduleName, instanceId);
    }
    resObj->SetColor(color);
    resObj->SetColorMode(nodeInfo.localColorMode);
    resObj->SetHasDarkRes(hasDarkRes);
}
```

**用途**：
- Modifier 链式调用时的资源解析
- 支持深色模式自动切换
- 颜色反转处理

---

### 3. NAPI 解析入口（napi_utils.cpp）

**源码位置**：`interfaces/napi/kits/utils/napi_utils.cpp`

#### 核心函数

##### ParseDollarResource

```cpp
// napi_utils.cpp:253
bool ParseDollarResource(
    napi_env env,
    napi_value value,
    ResourceType& resType,
    std::string& resName,
    std::string& moduleName)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);

    if (valueType != napi_string) {
        return false;
    }

    std::string resPath;
    if (!GetNapiString(env, value, resPath, valueType)) {
        return false;
    }

    std::vector<std::string> tokens;
    StringUtils::StringSplitter(resPath, '.', tokens);

    // 验证格式：app.xxx.xxx 或 sys.xxx.xxx
    if (tokens.size() != 3) {
        return false;
    }

    std::string maybeModuleName = tokens[0];
    if (maybeModuleName.size() < 3) {
        return false;
    }

    char begin = *maybeModuleName.begin();
    char end = maybeModuleName.at(maybeModuleName.size() - 1);
    bool headCheckPass = false;

    if (begin == '[' && end == ']') {
        moduleName = maybeModuleName.substr(1, maybeModuleName.size() - 2);
        headCheckPass = true;
    }

    if (std::find(RESOURCE_HEADS.begin(), RESOURCE_HEADS.end(), tokens[0]) ==
            RESOURCE_HEADS.end() && !headCheckPass) {
        return false;
    }

    if (!ConvertResourceType(tokens[1], resType)) {
        return false;
    }

    resName = resPath;
    return true;
}
```

**常量定义**：
```cpp
std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
```

##### CreateResourceWrapper

```cpp
// napi_utils.cpp:196
RefPtr<ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info)
{
    auto bundleName = info.bundleName;
    auto moduleName = info.moduleName;

    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;

    if (SystemProperties::GetResourceDecoupling()) {
        if (bundleName.has_value() && moduleName.has_value()) {
            auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
                bundleName.value_or(""),
                moduleName.value_or(""),
                Container::CurrentIdSafely());
            resourceAdapter = ResourceManager::GetInstance()
                .GetOrCreateResourceAdapter(resourceObject);
        } else {
            resourceAdapter = ResourceManager::GetInstance()
                .GetResourceAdapter(Container::CurrentIdSafely());
        }

        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = GetThemeConstants(info.bundleName, info.moduleName);
        if (!themeConstants) {
            return nullptr;
        }
    }

    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(
        themeConstants, resourceAdapter);
    return resourceWrapper;
}
```

**用途**：
- NAPI 接口中的资源解析
- C++ native 模块访问资源
- 跨语言边界的资源传递

---

## 缓存机制

### LRU 缓存详解

#### 缓存数据结构

```cpp
// resource_manager.h:202-204
std::atomic<size_t> capacity_ = 3;  // 默认缓存 3 个 ResourceAdapter

// LRU 双向链表
std::list<CacheNode<RefPtr<ResourceAdapter>>> cacheList_;

// 哈希映射：cacheKey → 链表迭代器
std::unordered_map<std::string,
    std::list<CacheNode<RefPtr<ResourceAdapter>>>::iterator> cache_;
```

#### 缓存操作流程

##### 添加到缓存（AddResourceAdapter）

```cpp
// resource_manager.h:68-82
void AddResourceAdapter(const std::string& bundleName,
                       const std::string& moduleName,
                       int32_t instanceId,
                       RefPtr<ResourceAdapter>& resourceAdapter,
                       bool replace = false)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);

    if (bundleName.empty() && moduleName.empty()) {
        // 默认 adapter：直接存入 map
        resourceAdapters_[std::to_string(instanceId)] = resourceAdapter;
    } else {
        auto key = MakeCacheKey(bundleName, moduleName, instanceId);

        if (replace) {
            // 替换模式：先移除旧缓存
            CountLimitLRU::RemoveCacheObjFromCountLimitLRU<
                RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
        }

        // 添加到 LRU 缓存
        CountLimitLRU::CacheWithCountLimitLRU<
            RefPtr<ResourceAdapter>>(key, resourceAdapter, cacheList_, cache_, capacity_);
    }
}
```

##### 从缓存获取（GetResourceAdapter）

```cpp
// resource_manager.h:111-135
RefPtr<ResourceAdapter> GetResourceAdapter(
    const std::string& bundleName,
    const std::string& moduleName,
    int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);

    auto key = MakeCacheKey(bundleName, moduleName, instanceId);

    // 1. 先查找持久化 map（默认 adapter）
    auto mapIter = resourceAdapters_.find(key);
    if (mapIter != resourceAdapters_.end()) {
        return mapIter->second;
    }

    // 2. 查找 LRU 缓存
    auto resAdapter = CountLimitLRU::GetCacheObjWithCountLimitLRU<
        RefPtr<ResourceAdapter>>(key, cacheList_, cache_);

    if (resAdapter != nullptr) {
        // LRU 命中：自动移动到链表头部
        return resAdapter;
    }

    return nullptr;
}
```

#### LRU 淘汰策略

```
初始状态（容量 = 3）：

cacheList_: [ ] (空)
cache_: { }

添加 A、B、C：

cacheList_: [C] → [B] → [A]
cache_: { "A": iter_A, "B": iter_B, "C": iter_C }

访问 A（LRU 移动到头部）：

cacheList_: [A] → [C] → [B]
cache_: { "A": iter_A, "B": iter_B, "C": iter_C }

添加 D（超过容量，淘汰尾部 B）：

cacheList_: [D] → [A] → [C]
cache_: { "A": iter_A, "C": iter_C, "D": iter_D }  // B 被移除
```

### 缓存容量管理

#### 设置缓存大小

```cpp
// resource_manager.h:187-193
void SetResourceCacheSize(size_t cacheSize) {
    capacity_.store(cacheSize);

    // 立即淘汰超出部分
    while (cache_.size() > capacity_) {
        cache_.erase(cacheList_.back().cacheKey);
        cacheList_.pop_back();
    }
}
```

**使用示例**：
```cpp
// 增加缓存容量到 10
ResourceManager::GetInstance().SetResourceCacheSize(10);

// 减少缓存容量到 1（立即淘汰）
ResourceManager::GetInstance().SetResourceCacheSize(1);
```

### 缓存键生成策略

#### 完整键（带 bundle 和 module）

```cpp
// resource_manager.h:65
return bundleName + "." + moduleName + "." + std::to_string(instanceId);

// 示例：
// "com.example.app.entry.12345"
// "com.example.hsp.settings.12345"
```

#### 默认键（仅 instanceId）

```cpp
// resource_manager.h:63-64
if (bundleName.empty() && moduleName.empty()) {
    return std::to_string(instanceId);
}

// 示例：
// "12345"
```

#### 特殊键（CROSS_PLATFORM 模式）

```cpp
// resource_manager.cpp:42-45
#ifdef CROSS_PLATFORM
if (resourceAdapter == nullptr) {
    std::string fullModuleName = bundleName + "." + moduleName;
    resourceAdapter = GetResourceAdapter(bundleName, fullModuleName, instanceId);
}
#endif
```

---

## 配置变化响应

### 支持的配置类型

| 配置类型 | 枚举/类型 | 触发场景 |
|---------|---------|---------|
| **颜色模式** | ColorMode | 深色/浅色模式切换 |
| **语言** | std::string | 系统语言改变 |
| **方向** | Orientation | 屏幕旋转 |
| **分辨率** | Dimension | 窗口大小变化 |
| **字体缩放** | float | 字体大小调整 |

### UpdateResourceConfig 流程

```cpp
// resource_manager.cpp:65-80
void ResourceManager::UpdateResourceConfig(
    const std::string& bundleName,
    const std::string& moduleName,
    int32_t instanceId,
    const ResourceConfiguration& config,
    bool themeFlag)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);

    std::string compareId = std::to_string(instanceId);

    // 1. 更新持久化 map 中的 ResourceAdapter
    for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->first) == compareId) {
            iter->second->UpdateConfig(config, themeFlag);
        }
    }

    // 2. 更新 LRU 缓存中的 ResourceAdapter
    for (auto iter = cacheList_.begin(); iter != cacheList_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->cacheKey) == compareId) {
            iter->cacheObj->UpdateConfig(config, themeFlag);
        }
    }
}
```

### UpdateColorMode 流程

```cpp
// resource_manager.cpp:82-97
void ResourceManager::UpdateColorMode(
    const std::string& bundleName,
    const std::string& moduleName,
    int32_t instanceId,
    ColorMode colorMode)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);

    std::string compareId = std::to_string(instanceId);

    // 1. 更新持久化 map
    for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->first) == compareId) {
            iter->second->UpdateColorMode(colorMode);
        }
    }

    // 2. 更新 LRU 缓存
    for (auto iter = cacheList_.begin(); iter != cacheList_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->cacheKey) == compareId) {
            iter->cacheObj->UpdateColorMode(colorMode);
        }
    }
}
```

### PatternResourceManager 的 ReloadResources

```cpp
// pattern_resource_manager.cpp
void PatternResourceManager::ReloadResources()
{
    for (auto& [key, updater] : resMap_) {
        if (updater.updateFunc) {
            // 调用注册的更新回调
            updater.updateFunc(updater.obj);
        }
    }
}
```

**调用时机**：
- 系统配置变化监听器触发
- `OnConfigurationChanged` 回调
- 深色模式切换
- 多语言切换

---

## 完整 API 清单

### ResourceManager API

| 方法签名 | 说明 | 线程安全 |
|---------|------|---------|
| `static ResourceManager& GetInstance()` | 获取单例 | 是 |
| `RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(const RefPtr<ResourceObject>&)` | 获取或创建 ResourceAdapter | 是 |
| `void AddResourceAdapter(..., RefPtr<ResourceAdapter>&, bool replace)` | 添加到缓存 | 是 |
| `RefPtr<ResourceAdapter> GetResourceAdapter(bundleName, moduleName, instanceId)` | 获取 ResourceAdapter | 是 |
| `RefPtr<ResourceAdapter> GetResourceAdapter(instanceId)` | 获取默认 ResourceAdapter | 是 |
| `void RemoveResourceAdapter(bundleName, moduleName, instanceId)` | 移除 ResourceAdapter | 是 |
| `void UpdateResourceConfig(..., ResourceConfiguration&, bool)` | 更新配置 | 是 |
| `void UpdateColorMode(..., ColorMode)` | 更新颜色模式 | 是 |
| `void SetResourceCacheSize(size_t)` | 设置缓存大小 | 是 |
| `void DumpResLoadError()` | 转储错误日志 | 是 |
| `void AddResourceLoadError(ResourceErrorInfo)` | 添加错误记录 | 是 |
| `void Reset()` | 清空缓存 | 是 |

### ResourceAdapter API

#### 颜色相关

| 方法签名 | 说明 |
|---------|------|
| `virtual Color GetColor(uint32_t resId) = 0` | 按 ID 获取颜色 |
| `virtual Color GetColorByName(const std::string& resName)` | 按名称获取颜色 |
| `virtual bool ExistDarkResById(const std::string&)` | 检查是否有深色资源（按 ID） |
| `virtual bool ExistDarkResByName(const std::string&, const std::string&)` | 检查是否有深色资源（按名称） |

#### 尺寸相关

| 方法签名 | 说明 |
|---------|------|
| `virtual Dimension GetDimension(uint32_t resId) = 0` | 按 ID 获取尺寸 |
| `virtual Dimension GetDimensionByName(const std::string& resName)` | 按名称获取尺寸 |

#### 字符串相关

| 方法签名 | 说明 |
|---------|------|
| `virtual std::string GetString(uint32_t resId) = 0` | 按 ID 获取字符串 |
| `virtual std::string GetStringByName(const std::string& resName)` | 按名称获取字符串 |
| `virtual std::string GetPluralString(uint32_t, int)` | 获取复数字符串（按 ID） |
| `virtual std::string GetPluralStringByName(const std::string&, int)` | 获取复数字符串（按名称） |
| `virtual std::vector<std::string> GetStringArray(uint32_t) const` | 获取字符串数组（按 ID） |
| `virtual std::vector<std::string> GetStringArrayByName(const std::string&) const` | 获取字符串数组（按名称） |

#### 数值相关

| 方法签名 | 说明 |
|---------|------|
| `virtual int32_t GetInt(uint32_t resId) = 0` | 按 ID 获取整数 |
| `virtual int32_t GetIntByName(const std::string& resName)` | 按名称获取整数 |
| `virtual double GetDouble(uint32_t resId) = 0` | 按 ID 获取双精度浮点 |
| `virtual double GetDoubleByName(const std::string& resName)` | 按名称获取双精度浮点 |
| `virtual bool GetBoolean(uint32_t) const` | 获取布尔值（按 ID） |
| `virtual bool GetBooleanByName(const std::string&) const` | 获取布尔值（按名称） |
| `virtual std::vector<uint32_t> GetIntArray(uint32_t) const` | 获取整数数组（按 ID） |
| `virtual std::vector<uint32_t> GetIntArrayByName(const std::string&) const` | 获取整数数组（按名称） |

#### 媒体相关

| 方法签名 | 说明 |
|---------|------|
| `virtual std::shared_ptr<PixelMap> GetPixelMap(uint32_t)` | 获取 PixelMap（按 ID） |
| `virtual std::string GetMediaPath(uint32_t)` | 获取媒体路径（按 ID） |
| `virtual std::string GetMediaPathByName(const std::string&)` | 获取媒体路径（按名称） |
| `virtual bool GetMediaData(uint32_t, size_t&, std::unique_ptr<uint8_t[]>&)` | 获取媒体数据（按 ID） |
| `virtual bool GetMediaData(const std::string&, size_t&, std::unique_ptr<uint8_t[]>&)` | 获取媒体数据（按名称） |

#### Rawfile 相关

| 方法签名 | 说明 |
|---------|------|
| `virtual std::string GetRawfile(const std::string&)` | 获取 Rawfile 路径 |
| `virtual bool GetRawFD(const std::string&, RawfileDescription&) const` | 获取 Rawfile 文件描述符 |
| `virtual bool GetRawFileData(const std::string&, size_t&, std::unique_ptr<uint8_t[]>&)` | 获取 Rawfile 数据 |

#### Symbol 相关

| 方法签名 | 说明 |
|---------|------|
| `virtual uint32_t GetSymbolByName(const char*) const` | 按名称获取 Symbol ID |
| `virtual uint32_t GetSymbolById(uint32_t) const` | 按 ID 获取 Symbol ID |

#### 主题相关

| 方法签名 | 说明 |
|---------|------|
| `virtual RefPtr<ThemeStyle> GetTheme(int32_t)` | 获取主题样式 |
| `virtual RefPtr<ThemeStyle> GetPatternByName(const std::string&)` | 按名称获取模式样式 |

#### 配置相关

| 方法签名 | 说明 |
|---------|------|
| `virtual void UpdateConfig(const ResourceConfiguration&, bool)` | 更新配置 |
| `virtual void UpdateColorMode(ColorMode)` | 更新颜色模式 |
| `virtual ColorMode GetResourceColorMode() const` | 获取当前颜色模式 |
| `virtual void UpdateResourceManager(const std::string&, const std::string&)` | 更新资源管理器 |

### ResourceWrapper API

| 方法签名 | 说明 |
|---------|------|
| `Color GetColor(uint32_t) const` | 获取颜色 |
| `Color GetColorByName(const std::string&) const` | 获取颜色（按名称） |
| `Dimension GetDimension(uint32_t) const` | 获取尺寸 |
| `Dimension GetDimensionByName(const std::string&) const` | 获取尺寸（按名称） |
| `int32_t GetInt(uint32_t) const` | 获取整数 |
| `int32_t GetIntByName(const std::string&) const` | 获取整数（按名称） |
| `double GetDouble(uint32_t) const` | 获取双精度浮点 |
| `double GetDoubleByName(const std::string&) const` | 获取双精度浮点（按名称） |
| `std::string GetString(uint32_t) const` | 获取字符串 |
| `std::string GetStringByName(const std::string&) const` | 获取字符串（按名称） |
| `std::string GetPluralString(uint32_t, int) const` | 获取复数字符串 |
| `std::string GetPluralStringByName(const std::string&, int) const` | 获取复数字符串（按名称） |
| `bool GetBoolean(uint32_t) const` | 获取布尔值 |
| `bool GetBooleanByName(const std::string&) const` | 获取布尔值（按名称） |
| `std::vector<uint32_t> GetIntArray(uint32_t) const` | 获取整数数组 |
| `std::vector<uint32_t> GetIntArrayByName(const std::string&) const` | 获取整数数组（按名称） |
| `std::shared_ptr<PixelMap> GetPixelMap(uint32_t) const` | 获取 PixelMap |
| `std::vector<std::string> GetStringArray(uint32_t) const` | 获取字符串数组 |
| `std::vector<std::string> GetStringArrayByName(const std::string&) const` | 获取字符串数组（按名称） |
| `std::string GetMediaPath(uint32_t) const` | 获取媒体路径 |
| `std::string GetMediaPathByName(const std::string&) const` | 获取媒体路径（按名称） |
| `std::string GetRawfile(const std::string&) const` | 获取 Rawfile 路径 |
| `bool GetRawFileData(const std::string&, size_t&, std::unique_ptr<uint8_t[]>&)` | 获取 Rawfile 数据 |
| `bool GetRawFD(const std::string&, RawfileDescription&) const` | 获取 Rawfile 文件描述符 |
| `uint32_t GetSymbolByName(const char*) const` | 获取 Symbol（按名称） |
| `uint32_t GetSymbolById(uint32_t) const` | 获取 Symbol（按 ID） |
| `void UpdateColorMode(ColorMode)` | 更新颜色模式 |

### ResourceParseUtils API

| 方法签名 | 说明 |
|---------|------|
| `static bool ParseResColor(const RefPtr<ResourceObject>&, Color&)` | 解析颜色 |
| `static bool ParseResColorWithColorMode(..., Color&, const ColorMode&)` | 解析颜色（支持颜色模式） |
| `static bool ParseResString(const RefPtr<ResourceObject>&, std::string&)` | 解析字符串 |
| `static bool ParseResString(const RefPtr<ResourceObject>&, std::u16string&)` | 解析 UTF-16 字符串 |
| `static bool ParseResInteger(const RefPtr<ResourceObject>&, int32_t&)` | 解析整数 |
| `static bool ParseResInteger(const RefPtr<ResourceObject>&, uint32_t&)` | 解析无符号整数 |
| `static bool ParseResDouble(const RefPtr<ResourceObject>&, double&)` | 解析双精度浮点 |
| `static bool ParseResBool(const RefPtr<ResourceObject>&, bool&)` | 解析布尔值 |
| `static bool ParseResResource(const RefPtr<ResourceObject>&, CalcDimension&)` | 解析为计算尺寸 |
| `static bool ParseResDimensionNG(..., CalcDimension&, DimensionUnit, bool)` | 解析为尺寸（NG） |
| `static bool ParseResDimensionVp(const RefPtr<ResourceObject>&, CalcDimension&)` | 解析为 vp 尺寸 |
| `static bool ParseResDimensionFp(const RefPtr<ResourceObject>&, CalcDimension&)` | 解析为 fp 尺寸 |
| `static bool ParseResDimensionPx(const RefPtr<ResourceObject>&, CalcDimension&)` | 解析为 px 尺寸 |
| `static bool ParseResIntegerArray(const RefPtr<ResourceObject>&, std::vector<uint32_t>&)` | 解析整数数组 |
| `static bool ParseResStrArray(const RefPtr<ResourceObject>&, std::vector<std::string>&)` | 解析字符串数组 |
| `static bool ParseResMedia(const RefPtr<ResourceObject>&, std::string&)` | 解析媒体路径 |
| `static void CompleteResourceObjectFromColor(..., Color&, const std::string&)` | 从颜色完成资源对象 |

### PatternResourceManager API

| 方法签名 | 说明 |
|---------|------|
| `void AddResource(const std::string&, const RefPtr<ResourceObject>&, std::function<void(...)>&&)` | 添加资源（带更新回调） |
| `void RemoveResource(const std::string&)` | 移除资源 |
| `void ReloadResources()` | 重载所有资源 |
| `bool Empty()` | 检查是否为空 |
| `void ParsePropertyValue(const RefPtr<ResourceObject>&, RefPtr<PropertyValueBase>)` | 解析属性值 |
| `template<typename T> void RegisterResource(...)` | 注册资源（类型安全） |

---

## 关键实现细节

### 1. 资源解耦模式（Resource Decoupling）

**源码位置**：`resource_wrapper.h:52`

#### 模式切换逻辑

```cpp
Color GetColor(uint32_t key) const {
    if (SystemProperties::GetResourceDecoupling()) {
        // 新模式：使用 ResourceAdapter
        CHECK_NULL_RETURN(resourceAdapter_, Color());
        return resourceAdapter_->GetColor(key);
    }
    // 旧模式：使用 ThemeConstants
    CHECK_NULL_RETURN(themeConstants_, Color());
    return themeConstants_->GetColor(key);
}
```

#### 两种模式对比

| 特性 | 资源解耦模式（ResourceAdapter） | 传统主题模式（ThemeConstants） |
|------|------------------------------|------------------------------|
| **底层接口** | Global::ResourceManager | ThemeManager |
| **资源隔离** | 支持（按 bundle/module） | 不支持 |
| **配置变化响应** | 实时更新 | 需要重新构建主题 |
| **HSP 支持** | 完整支持 | 有限支持 |
| **深色模式** | 自动切换 | 需要手动切换 |
| **推荐使用** | ✅ 是（API 10+） | ❌ 否（兼容性保留） |

---

### 2. 深色模式支持

#### 检查深色资源

```cpp
// arkts_utils.cpp:229
bool ArkTSUtils::CheckDarkResource(const RefPtr<ResourceObject>& resObj)
{
    auto resourceAdapter = ResourceManager::GetInstance()
        .GetOrCreateResourceAdapter(resObj);

    int32_t resId = resObj->GetId();
    bool hasDarkRes = false;

    if (resId == -1) {
        // 按名称检查
        hasDarkRes = resourceAdapter->ExistDarkResByName(
            resourceName, resourceType);
    } else {
        // 按 ID 检查
        hasDarkRes = resourceAdapter->ExistDarkResById(
            std::to_string(resId));
    }

    return hasDarkRes;
}
```

#### 颜色反转处理

```cpp
// arkts_utils.cpp:251
void ArkTSUtils::CompleteResourceObjectFromColor(
    RefPtr<ResourceObject>& resObj,
    Color& color,
    bool state,
    const NodeInfo& nodeInfo)
{
    bool hasDarkRes = CheckDarkResource(resObj);

    if (nodeInfo.localColorMode == ColorMode::DARK) {
        if (!hasDarkRes) {
            // 深色模式但没有深色资源：反转颜色
            color = Color(invertFunc(color.GetValue()));
        }
    } else if (nodeInfo.localColorMode == ColorMode::LIGHT) {
        if (hasDarkRes) {
            // 浅色模式但有深色资源：反转颜色
            color = Color(invertFunc(color.GetValue()));
        }
    }

    resObj->SetColor(color);
    resObj->SetHasDarkRes(hasDarkRes);
}
```

#### invertFunc 函数

```cpp
// 颜色反转：RGB 分量取反
auto invertFunc = [](uint32_t color) -> uint32_t {
    uint32_t r = (color >> 16) & 0xFF;
    uint32_t g = (color >> 8) & 0xFF;
    uint32_t b = color & 0xFF;
    uint32_t a = color & 0xFF000000;

    return a | ((0xFF - r) << 16) | ((0xFF - g) << 8) | (0xFF - b);
};
```

---

### 3. 线程安全机制

#### 读写锁（std::shared_mutex）

```cpp
// resource_manager.h:199-200
std::shared_mutex mutex_;  // 读写锁
std::shared_mutex errorMutex_;  // 错误日志专用锁
```

**读操作**（共享锁，多个读操作可并行）：
```cpp
RefPtr<ResourceAdapter> GetResourceAdapter(...) {
    std::shared_lock<std::shared_mutex> lock(mutex_);  // 共享锁
    // ... 查找操作
}
```

**写操作**（独占锁，阻塞所有读写）：
```cpp
void AddResourceAdapter(...) {
    std::unique_lock<std::shared_mutex> lock(mutex_);  // 独占锁
    // ... 修改操作
}
```

---

### 4. 资源加载错误处理

#### 错误信息结构

```cpp
// resource_manager.h:37-48
struct ResourceErrorInfo {
    int32_t nodeId;        // 节点 ID
    std::string sourceKey; // 资源键
    std::string sourceTag; // 资源标签
    std::string nodeTag;   // 节点标签
    int64_t errorTime;     // 错误时间
    int32_t state;         // 错误状态
};
```

#### 错误记录添加

```cpp
// resource_manager.h:178-185
void AddResourceLoadError(ResourceErrorInfo errorInfo) {
    std::unique_lock<std::shared_mutex> lock(errorMutex_);

    resourceErrorList_.emplace_front(errorInfo);

    // 最多保存 100 条错误
    if (resourceErrorList_.size() > MAX_DUMP_LIST_SIZE) {
        resourceErrorList_.pop_back();
    }
}
```

#### 错误转储

```cpp
// resource_manager.cpp:99-117
void ResourceManager::DumpResLoadError() {
    std::unique_lock<std::shared_mutex> lock(errorMutex_);

    DumpLog::GetInstance().Print("----------ResourceLoadErrorInfo----------");

    if (resourceErrorList_.empty()) {
        DumpLog::GetInstance().Print("No resource load error have occurred.");
        return;
    }

    DumpLog::GetInstance().Print("ResourceLoadErrorTimes: " +
        std::to_string(resourceErrorList_.size()));

    for (const auto& error : resourceErrorList_) {
        DumpLog::GetInstance().Print(1,
            "Node: " + std::to_string(error.nodeId) +
            ", nodeTag: " + error.nodeTag +
            ", sourceKey: " + error.sourceKey +
            ", sourceTag: " + error.sourceTag +
            ", errorCode: " + std::to_string(error.state) +
            ", errorTime: " + ConvertTimestampToStr(error.errorTime));
    }
}
```

---

### 5. 复数字符串格式化

#### 占位符模式

```cpp
// napi_utils.cpp:26
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(
    R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
```

**支持格式**：
- `%d` - 整数（短格式，位置隐式）
- `%s` - 字符串
- `%f` - 浮点数
- `%1$s` - 显式位置（第 1 个参数，字符串）
- `%2$d` - 显式位置（第 2 个参数，整数）

#### 占位符替换

```cpp
// napi_utils.cpp:79-126
void ReplaceHolder(std::string& originStr,
                  const std::vector<std::string>& params,
                  uint32_t containCount)
{
    auto size = static_cast<uint32_t>(params.size());

    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matches;

    bool shortHolderType = false;
    bool firstMatch = true;
    uint32_t searchTime = 0;

    while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matches[2];
        std::string type = matches[4];

        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            // 检查占位符类型一致性
            if (static_cast<uint32_t>(shortHolderType) ^
                ((uint32_t)(pos.length() == 0))) {
                LOGE("wrong place holder, stop parse string");
                return;
            }
        }

        std::string::size_type index = 0;
        if (shortHolderType) {
            // 短格式：%d, %s
            index = static_cast<std::string::size_type>(searchTime + containCount);
        } else {
            // 长格式：%1$d, %2$s
            int32_t indexTmp = StringUtils::StringToInt(pos) +
                static_cast<int32_t>(containCount) - 1;
            if (indexTmp >= 0) {
                index = static_cast<std::string::size_type>(indexTmp);
            }
        }

        if (index < size) {
            std::string replaceContentStr = GetLocalizedParamStr(params[index], type);
            originStr.replace(matches[0].first - originStr.begin(),
                            matches[0].length(),
                            replaceContentStr);
        }

        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}
```

**使用示例**：

```
资源文件：
<string name="welcome_message">Hello %1$s, you have %2$d messages</string>

调用：
GetStringFormat("welcome_message", ["Alice", "5"])

结果：
"Hello Alice, you have 5 messages"
```

---

## 使用示例

### 示例 1: 基础资源访问（颜色）

#### ArkTS 代码

```typescript
// 使用 $r() 访问颜色资源
@Entry
@Component
struct MyComponent {
  @State textColor: ResourceColor = $r('app.color.text_primary');

  build() {
    Text('Hello')
      .fontColor(this.textColor)
  }
}
```

#### 底层调用流程

```cpp
// 1. JS 层解析
JSRef<JSObject> jsRes = { id: "app.color.text_primary", type: -1, ... };

// 2. 补全资源对象
JSViewAbstract::CompleteResourceObject(jsRes);
// → 解析出：resType = COLOR, resName = "app.color.text_primary"

// 3. 获取 ResourceAdapter
auto resourceAdapter = ResourceManager::GetInstance()
    .GetOrCreateResourceAdapter(resourceObject);

// 4. 解析颜色
Color color;
ResourceParseUtils::ParseResColor(resourceObject, color);
// → resourceAdapter->GetColorByName("app.color.text_primary")

// 5. 应用到组件
textPattern->textColor_ = color;
```

---

### 示例 2: 字符串资源（复数）

#### 资源文件

```json
// resources/base/element/strings.json
{
  "plural": {
    "items": {
      "one": "%d item",
      "other": "%d items"
    }
  }
}
```

#### ArkTS 代码

```typescript
@Entry
@Component
struct ItemList {
  @State itemCount: number = 5;

  build() {
    Text($r('app.plural.items', this.itemCount))
  }
}
```

#### 底层解析

```cpp
// 1. 获取复数字符串
std::string result = resourceWrapper->GetPluralStringByName(
    "app.plural.items", 5);
// → 返回："5 items"

// 2. 如果有占位符，进行替换
// （对于 "%d items"，数字已被 Global::ResourceManager 处理）
```

---

### 示例 3: 媒体资源（图片）

#### ArkTS 代码

```typescript
@Entry
@Component
struct ImageComponent {
  build() {
    Image($r('app.media.icon'))
      .width(100)
      .height(100)
  }
}
```

#### 底层解析

```cpp
// 1. 解析媒体资源
std::string mediaPath;
ResourceParseUtils::ParseResMedia(resourceObject, mediaPath);
// → resourceAdapter->GetMediaPathByName("app.media.icon")
// → 返回："/data/storage/el2/base/haps/entry/files/icon.png"

// 2. 加载图片
ImagePattern::SetImageSrc(mediaPath);
```

---

### 示例 4: Rawfile 资源

#### 资源结构

```
resources/rawfile/
├── config.json
└── data/
    └── items.json
```

#### ArkTS 代码

```typescript
// 读取 Rawfile 文件
import { rawfile } from '@kit.ArkTS';

let data = rawfile.readRawFile('config.json');
let config = JSON.parse(data);
```

#### 底层解析（C++）

```cpp
// 1. 获取 Rawfile 数据
std::string rawFile = "config.json";
size_t len;
std::unique_ptr<uint8_t[]> data;

bool success = resourceWrapper->GetRawFileData(rawFile, len, data);
// → resourceAdapter->GetRawFileData("config.json", len, data)

// 2. 使用数据
if (success) {
    // data.get() 指向文件内容
    // len 是文件大小
}
```

---

### 示例 5: 深色模式适配

#### 资源文件

```
resources/
├── base/element/colors.json
│   └── { "color": { "background": "#FFFFFF" } }
└── dark/element/colors.json
│   └── { "color": { "background": "#000000" } }
```

#### ArkTS 代码

```typescript
@Entry
@Component
struct ThemeComponent {
  @State bgColor: ResourceColor = $r('app.color.background');

  build() {
    Column() {
      Text('Content')
    }
    .backgroundColor(this.bgColor)
  }
}
```

#### 底层处理

```cpp
// 1. 检查深色模式
bool hasDarkRes = CheckDarkResource(resourceObject);

// 2. 获取当前颜色模式
ColorMode colorMode = resourceAdapter->GetResourceColorMode();

// 3. 解析颜色
Color color;
ResourceParseUtils::ParseResColorWithColorMode(
    resourceObject, color, colorMode);

// 4. 如果没有深色资源且当前是深色模式，自动反转
if (colorMode == ColorMode::DARK && !hasDarkRes) {
    color = Color(invertFunc(color.GetValue()));
}
```

---

### 示例 6: NAPI 接口使用

#### C++ Native 代码

```cpp
#include "napi_utils.h"

using namespace OHOS::Ace::Napi;

static napi_value GetResourceString(napi_env env, napi_callback_info info) {
    // 1. 获取参数
    size_t argc = 1;
    napi_value jsValue;
    napi_get_cb_info(env, info, &argc, &jsValue, nullptr, nullptr);

    // 2. 解析资源
    ResourceType resType;
    std::string resName;
    std::string moduleName;

    if (!ParseDollarResource(env, jsValue, resType, resName, moduleName)) {
        // 不是资源，按普通字符串处理
        return jsValue;
    }

    // 3. 创建 ResourceWrapper
    ResourceInfo info;
    info.moduleName = moduleName;

    auto resourceWrapper = CreateResourceWrapper(info);
    if (!resourceWrapper) {
        return nullptr;
    }

    // 4. 获取字符串值
    std::string result;
    if (resType == ResourceType::STRING) {
        result = resourceWrapper->GetStringByName(resName);
    }

    // 5. 返回 JS 字符串
    return CreateNapiString(env, result);
}
```

---

## 调试指南

### 1. 启用资源日志

#### 设置日志标签

```cpp
// 资源系统使用以下日志标签
#define TAG "AceResource"  // 或 AceLogTag::ACE_RESOURCE

// 启用日志
LOGD("%{public}s", "Resource message");  // Debug
LOGI("%{public}s", "Resource message");  // Info
LOGW("%{public}s", "Resource message");  // Warning
LOGE("%{public}s", "Resource message");  // Error
```

#### 使用 HIDUMPER 转储

```bash
# 转储资源加载错误
hdc shell hidumper -s AceService -a "-d ResourceLoadError"

# 转储 ResourceAdapter 状态
hdc shell hidumper -s AceService -a "-d ResourceManager"
```

---

### 2. 检查资源缓存

#### 查看缓存容量

```cpp
// 添加日志
auto& manager = ResourceManager::GetInstance();

size_t cacheSize = manager.cache_.size();
LOGI("Resource cache size: %{public}zu", cacheSize);

// 转储缓存键
for (const auto& [key, iter] : manager.cache_) {
    LOGI("Cache key: %{public}s", key.c_str());
}
```

---

### 3. 验证资源解析

#### 断点位置

| 功能 | 文件 | 行号（约） |
|------|------|-----------|
| JS 资源对象补全 | js_view_abstract.cpp | 6179 |
| $r() 解析 | js_view_abstract.cpp | 6137 |
| 获取 ResourceAdapter | resource_manager.cpp | 33 |
| 颜色解析 | resource_parse_utils.cpp | ~200 |
| 深色模式检查 | arkts_utils.cpp | 229 |

#### 日志输出

```cpp
// 在关键点添加日志
auto resourceAdapter = ResourceManager::GetInstance()
    .GetOrCreateResourceAdapter(resourceObject);

if (!resourceAdapter) {
    LOGE("Failed to get ResourceAdapter: bundle=%{public}s, module=%{public}s, id=%{public}d",
        resourceObject->GetBundleName().c_str(),
        resourceObject->GetModuleName().c_str(),
        resourceObject->GetInstanceId());
    return Color();
}

LOGI("ResourceAdapter created: key=%{public}s",
    MakeCacheKey(bundleName, moduleName, instanceId).c_str());
```

---

### 4. 常见问题排查

#### 问题 1: 资源未找到

**症状**：
- 返回默认值（空字符串、黑色等）
- 日志显示资源加载失败

**排查步骤**：

```cpp
// 1. 检查 ResourceObject 是否正确创建
LOGI("ResourceObject: id=%{public}d, type=%{public}d, bundle=%{public}s, module=%{public}s",
    resObj->GetId(), resObj->GetType(),
    resObj->GetBundleName().c_str(),
    resObj->GetModuleName().c_str());

// 2. 检查 ResourceAdapter 是否存在
auto resourceAdapter = ResourceManager::GetInstance()
    .GetOrCreateResourceAdapter(resObj);
if (!resourceAdapter) {
    LOGE("ResourceAdapter is null!");
}

// 3. 检查资源名称
auto params = resObj->GetParams();
if (!params.empty() && params[0].value.has_value()) {
    LOGI("Resource name: %{public}s", params[0].value.value().c_str());
}

// 4. 转储错误日志
ResourceManager::GetInstance().DumpResLoadError();
```

#### 问题 2: 深色模式不生效

**症状**：
- 深色模式下颜色未变化
- 有深色资源但未生效

**排查步骤**：

```cpp
// 1. 检查当前颜色模式
ColorMode colorMode = resourceAdapter->GetResourceColorMode();
LOGI("Current color mode: %{public}d", static_cast<int>(colorMode));

// 2. 检查是否有深色资源
bool hasDarkRes = CheckDarkResource(resObj);
LOGI("Has dark resource: %{public}s", hasDarkRes ? "true" : "false");

// 3. 检查资源对象的状态
LOGI("ResourceObject color mode: %{public}d, hasDarkRes: %{public}s",
    static_cast<int>(resObj->GetColorMode()),
    resObj->HasDarkResource() ? "true" : "false");

// 4. 检查配置变化监听
// 确保调用了 UpdateColorMode
```

#### 问题 3: 配置变化后资源未更新

**症状**：
- 切换语言后字符串未变化
- 切换深色模式后颜色未更新

**排查步骤**：

```cpp
// 1. 确认配置变化通知已触发
LOGI("Config changed: bundle=%{public}s, module=%{public}s",
    bundleName.c_str(), moduleName.c_str());

// 2. 检查 ResourceAdapter 是否收到更新
ResourceManager::GetInstance().UpdateResourceConfig(
    bundleName, moduleName, instanceId, config, false);

// 3. 检查 PatternResourceManager 是否重载
patternResourceManager->ReloadResources();

// 4. 检查注册的更新回调是否被调用
// 在回调函数中添加日志
```

---

## 常见问题

### Q1: $r() 和 $sys.r() 有什么区别？

| 特性 | $r() | $sys.r() |
|------|------|----------|
| **资源来源** | 应用资源（app） | 系统资源（sys） |
| **路径前缀** | `app.` | `sys.` |
| **资源位置** | `resources/base/element/` | 系统资源文件 |
| **用途** | 应用自定义资源 | 系统预定义资源（如系统颜色） |
| **示例** | `$r('app.color.primary')` | `$sys.r('sys.color.ohos_id_color_primary')` |

**解析差异**：
```cpp
// js_view_abstract.cpp
std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };

if (tokens[0] == "app") {
    // 应用资源：使用 bundleName/moduleName
    targetModule = GetCurrentModuleName();
} else if (tokens[0] == "sys") {
    // 系统资源：使用系统 ResourceAdapter
    targetModule = "system";
}
```

---

### Q2: 何时使用 ResourceAdapter vs ThemeConstants？

**使用 ResourceAdapter**（推荐）：
- API 10+ 新项目
- 需要跨模块资源访问（HSP）
- 需要动态资源更新
- 需要完整的深色模式支持

**使用 ThemeConstants**（兼容性）：
- API 9 旧项目维护
- 不需要动态更新
- 简单单模块应用

**切换控制**：
```cpp
// 系统属性控制
if (SystemProperties::GetResourceDecoupling()) {
    return resourceAdapter;  // 新模式
} else {
    return themeConstants;   // 旧模式
}
```

---

### Q3: 如何提高资源缓存命中率？

**策略**：

1. **增加缓存容量**
```cpp
ResourceManager::GetInstance().SetResourceCacheSize(10);
```

2. **复用 ResourceObject**
```cpp
// ❌ 差：每次创建新对象
for (int i = 0; i < 100; i++) {
    auto obj = AceType::MakeRefPtr<ResourceObject>(...);
    ParseResColor(obj, color);
}

// ✅ 好：复用对象
auto obj = AceType::MakeRefPtr<ResourceObject>(...);
for (int i = 0; i < 100; i++) {
    ParseResColor(obj, color);
}
```

3. **避免频繁切换 bundle/module**
```cpp
// ❌ 差：频繁切换
ParseResource("com.app1.module1", "color1");
ParseResource("com.app2.module2", "color2");
ParseResource("com.app1.module1", "color3");  // 缓存已淘汰

// ✅ 好：批量处理
ParseResource("com.app1.module1", "color1");
ParseResource("com.app1.module1", "color3");  // 缓存命中
ParseResource("com.app2.module2", "color2");
```

---

### Q4: 资源名称解析失败怎么办？

**常见原因**：

1. **格式错误**
```cpp
// ❌ 错误格式
$r('color.primary')           // 缺少 app/sys
$r('app.color')                // 缺少资源名
$r('app.color.primary.extra') // 多余段落

// ✅ 正确格式
$r('app.color.primary')
$r('[com.example.hsp].color.custom')
```

2. **资源不存在**
```cpp
// 检查资源文件
resources/base/element/colors.json
{
  "color": {
    "primary": "#FF0000"  // 确保资源定义存在
  }
}
```

3. **模块名错误**
```cpp
// 检查 moduleName 是否正确
auto container = Container::Current();
LOGI("Current module: %{public}s", container->GetModuleName().c_str());
```

---

### Q5: 如何支持 HSP 动态共享包的资源？

**HSP 资源格式**：
```typescript
// HSP 中的资源
$r('[com.example.hsp].color.custom')
```

**解析逻辑**：
```cpp
// js_view_abstract.cpp
if (tokens[0][0] == '[' && tokens[0].back() == ']') {
    // HSP 模块：[com.example.hsp]
    targetModule = tokens[0].substr(1, tokens[0].size() - 2);
}
```

**创建 ResourceAdapter**：
```cpp
// resource_manager.cpp
auto resourceAdapter = ResourceAdapter::CreateNewResourceAdapter(
    bundleName,  // "com.example.hsp"
    moduleName   // "" 或具体模块名
);
```

---

## 附录

### A. 资源目录结构

```
resources/
├── base/                    # 默认资源（无限定词）
│   ├── element/             # 基本元素资源
│   │   ├── colors.json      # 颜色资源
│   │   ├── strings.json     # 字符串资源
│   │   ├── floats.json      # 浮点资源
│   │   ├── booleans.json    # 布尔资源
│   │   └── integers.json    # 整数资源
│   ├── media/               # 媒体资源
│   │   ├── icon.png
│   │   └── background.jpg
│   ├── profile/             # 配置文件
│   │   └── main_pages.json
│   └── rawfile/             # 原始文件
│       ├── config.json
│       └── data.json
├── en_US/                   # 英语（美国）
│   └── element/
│       └── strings.json
├── zh_CN/                   # 中文（中国）
│   └── element/
│       └── strings.json
└── dark/                    # 深色模式
    └── element/
        └── colors.json
```

---

### B. 资源文件示例

#### colors.json

```json
{
  "color": [
    {
      "name": "primary",
      "value": "#FF0000"
    },
    {
      "name": "background",
      "value": "#FFFFFF"
    }
  ]
}
```

#### strings.json

```json
{
  "string": [
    {
      "name": "app_name",
      "value": "My Application"
    },
    {
      "name": "welcome_message",
      "value": "Hello %s!"
    }
  ]
}
```

#### plurals.json

```json
{
  "plural": [
    {
      "name": "item",
      "value": {
        "one": "%d item",
        "other": "%d items"
      }
    }
  ]
}
```

---

### C. 关键源码文件索引

| 模块 | 文件路径 | 说明 |
|------|---------|------|
| **核心管理** | frameworks/core/common/resource/resource_manager.h/cpp | ResourceManager 单例 |
| **资源包装** | frameworks/core/common/resource/resource_wrapper.h/cpp | ResourceWrapper 统一接口 |
| **资源解析** | frameworks/core/common/resource/resource_parse_utils.h/cpp | ResourceParseUtils 工具类 |
| **Pattern 管理** | frameworks/core/common/resource/pattern_resource_manager.h/cpp | PatternResourceManager |
| **资源对象** | interfaces/inner_api/ace_kit/include/ui/resource/resource_object.h | ResourceObject 定义 |
| **适配器接口** | frameworks/core/components/theme/resource_adapter.h | ResourceAdapter 虚接口 |
| **OHOS 适配器** | adapter/ohos/osal/resource_adapter_impl.h/cpp | ResourceAdapterImpl 实现 |
| **JS 解析入口** | frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp | JS 层资源解析 |
| **Modifier 解析** | frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.cpp | Modifier 资源解析 |
| **NAPI 解析** | interfaces/napi/kits/utils/napi_utils.cpp | NAPI 资源解析 |

---

### D. 相关文档

- **[OpenHarmony 资源访问指南](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides/resource-categories-and-access)** - 官方资源文档
- **[CLAUDE.md](../../CLAUDE.md)** - 项目级指导文档
- **[Inner API 知识库](../../docs/interfaces/inner_api/inner_api_Knowledge_Base.md)** - Inner API 深度参考

---

### E. 版本历史

| 版本 | 日期 | 变更说明 |
|------|------|---------|
| v1.0 | 2026-02-03 | 初始版本，完整资源系统知识库 |

---

### F. 反馈与贡献

如发现文档错误或有改进建议，请：
1. 提交 Issue 到项目仓库
2. 参考项目 CLAUDE.md 规范提交 PR
3. 联系文档维护者

---

**文档结束**
