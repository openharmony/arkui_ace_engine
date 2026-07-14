# ThemeManager 完整架构分析

> **文档版本**: v1.0
> **更新时间**: 2026-02-07
> **源码版本**: OpenHarmony ace_engine (master 分支)
> **作者**: Claude (ACE Engine 架构分析)

---

## 📚 目录

1. [主题系统概述](#1-主题系统概述)
2. [架构设计](#2-架构设计)
3. [核心流程](#3-核心流程)
4. [关键特性](#4-关键特性)
5. [代码组织](#5-代码组织)
6. [调用关系图](#6-调用关系图)
7. [性能优化策略](#7-性能优化策略)
8. [常见问题与调试](#8-常见问题与调试)
9. [扩展指南](#9-扩展指南)

---

## 1. 主题系统概述

### 1.1 ThemeManager 定位和职责

**ThemeManager** 是 ACE Engine 主题系统的核心管理器，负责：

1. **主题构建与缓存**
   - 构建各类组件的主题（ButtonTheme, TextTheme, CheckboxTheme 等）
   - 管理主题实例的生命周期
   - 提供主题缓存机制避免重复构建

2. **主题切换支持**
   - 支持浅色/深色模式切换
   - 支持自定义主题加载
   - 支持系统主题配置更新

3. **Token 主题系统集成**
   - 与 TokenThemeStorage 协同工作
   - 支持基于 Token 的主题包装器（ThemeWrapper）
   - 支持局部主题覆盖（WithThemeNode）

4. **资源适配桥接**
   - 通过 ThemeConstants 桥接 ResourceAdapter
   - 支持多平台资源适配（OHOS/Preview）
   - 支持资源动态更新

### 1.2 核心功能

#### 功能清单

| 功能 | 说明 | 关键方法 |
|------|------|----------|
| **主题获取** | 获取组件主题实例 | `GetTheme()`, `GetTheme(themeScopeId)` |
| **主题构建** | 构建主题或主题包装器 | `GetThemeOrigin()`, `GetThemeKit()` |
| **主题加载** | 从资源加载主题 | `LoadResourceThemes()`, `LoadSystemTheme()` |
| **配置更新** | 更新资源配置 | `UpdateConfig()` |
| **模式切换** | 切换深浅色模式 | `SetColorScheme()` |
| **背景色获取** | 获取应用背景色 | `GetBackgroundColor()` |

#### 设计目标

1. **高性能**
   - 双层缓存机制（themes_ + themeWrappersLight_/Dark_）
   - 延迟构建（按需构建主题）
   - 多线程安全访问

2. **可扩展**
   - 支持动态注册主题构建器
   - 支持自定义主题包装器
   - 支持 Kit 扩展机制

3. **灵活性**
   - 支持全局主题 + 局部主题覆盖
   - 支持多种颜色模式（LIGHT/DARK/UNDEFINED）
   - 支持资源动态更新

### 1.3 与其他模块的交互关系

```
┌─────────────────────────────────────────────────────────────┐
│                   Application Layer                         │
│  (ArkTS 应用使用 Theme 通过 ThemeManager 获取样式)           │
└───────────────────────────┬─────────────────────────────────┘
                            │
                            ↓
┌─────────────────────────────────────────────────────────────┐
│              Components NG / Components Layer                │
│  ┌──────────────┐  ┌───────────────┐  ┌─────────────────┐  │
│  │ ButtonPattern│  │  TextPattern  │  │ CheckboxPattern │  │
│  │  GetTheme()  │  │  GetTheme()   │  │   GetTheme()    │  │
│  └──────┬───────┘  └───────┬───────┘  └────────┬────────┘  │
│         │                   │                   │            │
│         └───────────────────┼───────────────────┘            │
│                             ↓                                │
│                    ┌──────────────────┐                      │
│                    │  ThemeManager    │                      │
│                    └────────┬─────────┘                      │
└─────────────────────────────┼────────────────────────────────┘
                              │
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                    Theme System Components                   │
│  ┌─────────────────┐  ┌──────────────────┐  ┌────────────┐ │
│  │ThemeConstants   │  │TokenThemeStorage │  │ Resource   │ │
│  │(资源常量管理)    │  │(Token主题存储)   │  │ Adapter    │ │
│  └────────┬────────┘  └────────┬─────────┘  └────────────┘ │
│           │                    │                             │
│           ↓                    ↓                             │
│  ┌─────────────────┐  ┌──────────────────┐                  │
│  │ThemeBuilder     │  │ThemeWrapper      │                  │
│  │(主题构建器)      │  │(主题包装器)       │                  │
│  └─────────────────┘  └──────────────────┘                  │
└───────────────────────────┬─────────────────────────────────┘
                            │
                            ↓
┌─────────────────────────────────────────────────────────────┐
│                  Platform Adapter Layer                     │
│              (ResourceAdapter OHOS 实现)                     │
└─────────────────────────────────────────────────────────────┘
```

**关键交互**：

1. **Component Pattern → ThemeManager**
   - Pattern 通过 `GetTheme<T>()` 获取主题
   - ThemeManager 返回对应的 Theme 实例

2. **ThemeManager ↔ ThemeConstants**
   - ThemeConstants 提供 `GetColor()`, `GetDimension()` 等资源获取接口
   - ThemeManager 持有 ThemeConstants 实例

3. **ThemeManager ↔ TokenThemeStorage**
   - TokenThemeStorage 管理 Token 主题缓存
   - ThemeManager 通过 TokenThemeStorage 获取自定义主题

4. **ThemeConstants ↔ ResourceAdapter**
   - ResourceAdapter 适配不同平台资源
   - ThemeConstants 通过 ResourceAdapter 获取资源值

---

## 2. 架构设计

### 2.1 类继承关系

```
AceType (基础类)
    ↓
Theme (主题基类 - interfaces/inner_api/ace_kit/include/ui/view/theme/theme.h)
    ↓
    ├── ThemeManager (抽象接口 - frameworks/core/components/theme/theme_manager.h)
    │   ↓
    │   └── ThemeManagerImpl (实现类 - frameworks/core/components/theme/theme_manager_impl.h)
    │       ├── themes_: 主题缓存
    │       ├── themeWrappersLight_: 浅色主题包装器缓存
    │       ├── themeWrappersDark_: 深色主题包装器缓存
    │       ├── themeConstants_: 资源常量管理器
    │       └── themeMultiThreadMutex_: 多线程互斥锁
    │
    └── 具体主题类 (如 ButtonTheme, TextTheme 等)
        ↓
        └── TokenThemeWrapper (主题包装器基类)
            ↓
            ├── TextThemeWrapper
            ├── CheckboxThemeWrapper
            └── ... (其他组件的主题包装器)
```

### 2.2 ThemeManager 接口设计

**Source**: `frameworks/core/components/theme/theme_manager.h`

#### 核心接口

```cpp
class ACE_EXPORT ThemeManager : public AceType {
public:
    // 资源初始化
    virtual void InitResource(const ResourceInfo& resourceInfo) {}

    // 配置更新
    virtual void UpdateConfig(const ResourceConfiguration& config) {}

    // 加载系统主题
    virtual void LoadSystemTheme(int32_t themeId) {}
    virtual void SetSystemThemeId(int32_t themeId) {}
    virtual int32_t GetSystemTheme() { return -1; }
    virtual void ParseSystemTheme() {}

    // 颜色模式设置
    virtual void SetColorScheme(ColorScheme colorScheme) {}

    // 获取背景色
    virtual Color GetBackgroundColor() const = 0;

    // 获取主题常量
    virtual RefPtr<ThemeConstants> GetThemeConstants(
        const std::string& bundleName, const std::string& moduleName) const = 0;
    virtual RefPtr<ThemeConstants> GetThemeConstants() const = 0;

    // 获取主题（核心接口）
    virtual RefPtr<Theme> GetTheme(ThemeType type) = 0;
    virtual RefPtr<Theme> GetTheme(ThemeType type, int32_t themeScopeId) = 0;

    // 加载资源主题
    virtual void LoadResourceThemes() {}

    // 模板方法：获取指定类型的主题
    template<typename T>
    RefPtr<T> GetTheme() {
        return AceType::DynamicCast<T>(GetTheme(T::TypeId()));
    }

    template<typename T>
    RefPtr<T> GetTheme(int32_t themeScopeId) {
        return AceType::DynamicCast<T>(GetTheme(T::TypeId(), themeScopeId));
    }

    // 注册 Kit 主题构建器
    virtual void RegisterThemeKit(ThemeType type, Ace::Kit::BuildFunc func) = 0;
    virtual void RegisterCustomThemeKit(ThemeType type, Ace::Kit::BuildThemeWrapperFunc func) = 0;
};
```

### 2.3 ThemeManagerImpl 架构

**Source**: `frameworks/core/components/theme/theme_manager_impl.h`

#### 成员变量

```cpp
class ThemeManagerImpl : public ThemeManager {
private:
    // 普通主题缓存：ThemeType → Theme
    std::unordered_map<ThemeType, RefPtr<Theme>> themes_;

    // 主题包装器缓存：支持浅色/深色双缓存
    using ThemeWrappers = std::unordered_map<ThemeType, RefPtr<TokenThemeWrapper>>;
    ThemeWrappers themeWrappersLight_;  // 浅色模式主题包装器
    ThemeWrappers themeWrappersDark_;   // 深色模式主题包装器

    // 主题常量管理器
    RefPtr<ThemeConstants> themeConstants_;

    // 当前系统主题 ID
    int32_t currentThemeId_ = -1;

    // 多线程互斥锁（递归锁）
    std::recursive_mutex themeMultiThreadMutex_;
};
```

**设计要点**：

1. **三层缓存结构**
   - `themes_`：缓存普通 Theme 对象
   - `themeWrappersLight_`：缓存浅色模式的 TokenThemeWrapper
   - `themeWrappersDark_`：缓存深色模式的 TokenThemeWrapper

2. **双模式支持**
   - Light/Dark 双缓存实现快速模式切换
   - 通过 `GetThemeWrappers(ColorMode)` 选择对应缓存

3. **线程安全**
   - 使用 `std::recursive_mutex` 支持同一线程多次加锁
   - `GetTheme()` 根据多线程标志选择不同实现路径

### 2.4 主题构建器（ThemeBuilder）架构

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:113-184`

#### 构建器映射表

```cpp
// 主题构建器映射：ThemeType → BuildFunc
const std::unordered_map<ThemeType, RefPtr<Theme>(*)(const RefPtr<ThemeConstants>&)>
    THEME_BUILDERS = {
    { AppTheme::TypeId(), &ThemeBuildFunc<AppTheme::Builder> },
    { ButtonTheme::TypeId(), &ThemeBuildFunc<ButtonTheme::Builder> },
    { PickerTheme::TypeId(), &ThemeBuildFunc<PickerTheme::Builder> },
    { CheckboxTheme::TypeId(), &ThemeBuildFunc<CheckboxTheme::Builder> },
    // ... 60+ 组件主题构建器
};

// 主题包装器构建器映射
const std::unordered_map<ThemeType, RefPtr<TokenThemeWrapper>(*)(const RefPtr<ThemeConstants>&)>
    TOKEN_THEME_WRAPPER_BUILDERS = {
    { CheckboxTheme::TypeId(), &ThemeWrapperBuildFunc<NG::CheckboxThemeWrapper::WrapperBuilder> },
    { SwitchTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SwitchThemeWrapper::WrapperBuilder> },
    // ... 13+ 主题包装器构建器
};
```

#### 构建器模式

```cpp
// 普通主题构建器模板
template<class T>
RefPtr<Theme> ThemeBuildFunc(const RefPtr<ThemeConstants>& themeConstants)
{
    return T().Build(themeConstants);
}

// 主题包装器构建器模板
template<class T>
RefPtr<TokenThemeWrapper> ThemeWrapperBuildFunc(const RefPtr<ThemeConstants>& themeConstants)
{
    return T().BuildWrapper(themeConstants);
}
```

**ButtonTheme 构建器示例**：

```cpp
class ButtonTheme : public virtual Theme {
public:
    class Builder {
    public:
        RefPtr<ButtonTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ButtonTheme> theme = AceType::MakeRefPtr<ButtonTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);  // 解析主题模式
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
                         const RefPtr<ButtonTheme>& theme) const
        {
            RefPtr<ThemeStyle> buttonPattern =
                themeConstants->GetPatternByName(THEME_PATTERN_BUTTON);
            if (!buttonPattern) {
                LOGW("find pattern of button fail");
                return;
            }
            // 从 ThemeStyle 中解析各个属性
            theme->bgColor_ = buttonPattern->GetAttr<Color>("button_bg_color", Color());
            theme->textStyle_.SetTextColor(
                buttonPattern->GetAttr<Color>("button_text_color", Color()));
            // ... 更多属性解析
        }
    };
};
```

### 2.5 Token 主题系统工作原理

#### TokenTheme 架构

**Source**: `frameworks/core/components_ng/token_theme/token_theme_storage.h`

```
TokenThemeStorage (单例)
    ├── themeScopeMap_: ThemeScopeId → ThemeId
    ├── themeCache_: ThemeId → TokenTheme
    ├── defaultLightTheme_: 默认浅色主题
    ├── defaultDarkTheme_: 默认深色主题
    └── darkThemeColorsAvailable_ / lightThemeColorsAvailable_: 颜色可用性标记
```

**核心数据结构**：

```cpp
class TokenThemeStorage final {
public:
    // 存储 ThemeScopeId 到 ThemeId 的映射
    void StoreThemeScope(TokenThemeScopeId themeScopeId, int32_t themeId);

    // 移除 ThemeScope
    void RemoveThemeScope(TokenThemeScopeId themeScopeId, bool removeToken = false);

    // 获取 Token 主题
    const RefPtr<TokenTheme>& GetTheme(TokenThemeScopeId themeScopeId);

    // 缓存管理
    void CacheSet(const RefPtr<TokenTheme>& theme);
    const RefPtr<TokenTheme>& CacheGet(int32_t themeId);
    void CacheRemove(int32_t themeId);
    void CacheClear();

private:
    // ThemeScopeId → ThemeId 映射
    std::unordered_map<TokenThemeScopeId, int32_t> themeScopeMap_;

    // ThemeId → TokenTheme 缓存（有序 map）
    std::map<int32_t, RefPtr<TokenTheme>> themeCache_;
    std::mutex themeCacheMutex_;

    // 默认主题（静态成员）
    inline static RefPtr<TokenTheme> defaultLightTheme_ = nullptr;
    inline static RefPtr<TokenTheme> defaultDarkTheme_ = nullptr;
};
```

#### TokenThemeWrapper 机制

**Source**: `interfaces/inner_api/ace_kit/include/ui/view/theme/token_theme_wrapper.h`

```cpp
class TokenThemeWrapper : virtual public Theme {
public:
    // 应用 Token 主题（纯虚函数，子类必须实现）
    virtual void ApplyTokenTheme(const TokenTheme& theme) = 0;
};
```

**TextThemeWrapper 示例**：

**Source**: `frameworks/core/components_ng/pattern/text/text_theme_wrapper.h`

```cpp
class TextThemeWrapper : public TextTheme, public TokenThemeWrapper {
public:
    class WrapperBuilder : public Builder {
    public:
        RefPtr<TokenThemeWrapper> BuildWrapper(
            const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<TextThemeWrapper>();
            auto theme = AceType::DynamicCast<TextTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            InitThemeDefaults(theme);           // 初始化默认值
            ParsePattern(themeConstants, theme); // 解析主题模式
            return wrapper;
        }
    };

    // 应用 Token 主题
    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            textStyle_.SetTextColor(colors->FontPrimary());  // 使用 Token 颜色
        }
    }
};
```

### 2.6 主题缓存机制

#### 缓存层次

```
Level 1: themes_ 缓存
    ├── Key: ThemeType (组件类型)
    ├── Value: RefPtr<Theme>
    └── Scope: 全局共享

Level 2: themeWrappersLight_ / themeWrappersDark_ 缓存
    ├── Key: ThemeType
    ├── Value: RefPtr<TokenThemeWrapper>
    └── Scope: 按颜色模式分离

Level 3: TokenThemeStorage::themeCache_
    ├── Key: int32_t (ThemeId)
    ├── Value: RefPtr<TokenTheme>
    └── Scope: Token 主题全局缓存
```

#### 缓存查找流程

```
GetTheme(type, themeScopeId)
    ↓
TokenThemeStorage::GetTheme(themeScopeId)
    ├── if (themeScopeId == 0) → return GetDefaultTheme()
    └── else → return CacheGet(themeScopeMap_[themeScopeId])
    ↓
检查 tokenTheme 是否存在
    ├── 不存在 → 退化为 GetTheme(type)
    └── 存在 → 继续
    ↓
根据 ColorMode 选择缓存（Light 或 Dark）
    ↓
检查 themeWrappers 中是否有缓存
    ├── 有缓存 → wrapper->ApplyTokenTheme(*tokenTheme)
    └── 无缓存 → builderIter->second(themeConstants_)
                    → wrapper->ApplyTokenTheme(*tokenTheme)
                    → 缓存到 themeWrappers
    ↓
return wrapper (dynamic_cast to Theme)
```

### 2.7 多线程主题构建支持

**Source**: `frameworks/core/components/theme/theme_manager_multi_thread.cpp`

#### 多线程模式判断

```cpp
RefPtr<Theme> ThemeManagerImpl::GetTheme(ThemeType type)
{
    // 判断是否在多线程安全节点作用域内
    if (MultiThreadBuildManager::IsThreadSafeNodeScope()) {
        return GetThemeMultiThread(type);  // 多线程路径
    }
    std::lock_guard<std::recursive_mutex> lock(themeMultiThreadMutex_);
    return GetThemeNormal(type);  // 单线程路径
}
```

#### 多线程安全实现

```cpp
RefPtr<Theme> ThemeManagerImpl::GetThemeMultiThread(ThemeType type)
{
    std::lock_guard<std::recursive_mutex> lock(themeMultiThreadMutex_);
    return GetThemeNormal(type);  // 加锁后执行正常逻辑
}

void ThemeManagerImpl::LoadResourceThemesMultiThread()
{
    std::lock_guard<std::recursive_mutex> lock(themeMultiThreadMutex_);
    LoadResourceThemesInner();  // 加锁后执行加载
}
```

**设计要点**：

1. **递归锁**：使用 `std::recursive_mutex` 允许同一线程多次加锁
2. **统一逻辑**：多线程和单线程共享 `GetThemeNormal()` 实现
3. **性能权衡**：只在必要时加锁（判断 `IsThreadSafeNodeScope()`）

---

## 3. 核心流程

### 3.1 主题加载流程（LoadResourceThemes）

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:448-464`

```cpp
void ThemeManagerImpl::LoadResourceThemes()
{
    if (MultiThreadBuildManager::IsThreadSafeNodeScope()) {
        LoadResourceThemesMultiThread();  // 多线程路径
        return;
    }
    std::lock_guard<std::recursive_mutex> lock(themeMultiThreadMutex_);
    LoadResourceThemesInner();  // 单线程路径
}

void ThemeManagerImpl::LoadResourceThemesInner()
{
    themes_.clear();            // 清空主题缓存
    themeWrappersLight_.clear(); // 清空浅色主题包装器缓存
    themeWrappersDark_.clear();  // 清空深色主题包装器缓存
    themeConstants_->LoadTheme(currentThemeId_);  // 重新加载主题常量
}
```

**流程图**：

```
LoadResourceThemes()
    ↓
检查是否多线程模式
    ├── 是 → LoadResourceThemesMultiThread()
    │        ├── 加锁
    │        └── LoadResourceThemesInner()
    └── 否 → 加锁
             └── LoadResourceThemesInner()
                      ↓
                  清空所有缓存
                      ├── themes_.clear()
                      ├── themeWrappersLight_.clear()
                      └── themeWrappersDark_.clear()
                      ↓
                  重新加载主题常量
                      └── themeConstants_->LoadTheme(currentThemeId_)
```

### 3.2 主题获取流程（GetTheme）

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:242-273`

#### 无 ThemeScopeId 版本

```cpp
RefPtr<Theme> ThemeManagerImpl::GetTheme(ThemeType type)
{
    if (MultiThreadBuildManager::IsThreadSafeNodeScope()) {
        return GetThemeMultiThread(type);  // 多线程路径
    }
    std::lock_guard<std::recursive_mutex> lock(themeMultiThreadMutex_);
    return GetThemeNormal(type);
}

RefPtr<Theme> ThemeManagerImpl::GetThemeNormal(ThemeType type)
{
    // 1. 检查缓存
    auto findIter = themes_.find(type);
    if (findIter != themes_.end()) {
        return findIter->second;  // 缓存命中
    }

    // 2. 尝试 Kit 构建器
    auto theme = GetThemeKit(type);
    CHECK_NULL_RETURN(theme, GetThemeOrigin(type));  // Kit 失败则用原始构建器
    return theme;
}

RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type)
{
    // 查找构建器
    auto builderIter = THEME_BUILDERS.find(type);
    if (builderIter == THEME_BUILDERS.end()) {
        return nullptr;  // 没有注册的构建器
    }

    // 构建主题
    auto theme = builderIter->second(themeConstants_);
    themes_.emplace(type, theme);  // 缓存主题
    return theme;
}

RefPtr<Theme> ThemeManagerImpl::GetThemeKit(ThemeType type)
{
    auto builderIterKit = THEME_BUILDERS_KIT.find(type);
    if (builderIterKit == THEME_BUILDERS_KIT.end()) {
        return nullptr;  // 没有 Kit 构建器
    }

    // 处理局部颜色模式
    if (auto pipeline = NG::PipelineContext::GetCurrentContext(); pipeline) {
        ColorMode localMode = pipeline->GetLocalColorMode();
        ColorMode systemMode = pipeline->GetColorMode();
        bool needRestore = false;
        if (localMode != ColorMode::COLOR_MODE_UNDEFINED && localMode != systemMode) {
            // 普通主题应工作在系统颜色模式
            ResourceManager::GetInstance().UpdateColorMode(
                pipeline->GetBundleName(), pipeline->GetModuleName(),
                pipeline->GetInstanceId(), systemMode);
            pipeline->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
            needRestore = true;
        }
        auto theme = builderIterKit->second();
        if (needRestore) {
            pipeline->SetLocalColorMode(localMode);
            ResourceManager::GetInstance().UpdateColorMode(
                pipeline->GetBundleName(), pipeline->GetModuleName(),
                pipeline->GetInstanceId(), localMode);
        }
        themes_.emplace(type, theme);
        return theme;
    }

    auto theme = builderIterKit->second();
    themes_.emplace(type, theme);
    return theme;
}
```

**流程图**：

```
GetTheme(type)
    ↓
检查多线程模式
    ├── 是 → GetThemeMultiThread() → 加锁 → GetThemeNormal()
    └── 否 → 加锁 → GetThemeNormal()
                      ↓
                  检查 themes_ 缓存
                      ├── 命中 → 返回缓存的主题
                      └── 未命中 → 继续
                                ↓
                            GetThemeKit(type)
                                ├── 检查 THEME_BUILDERS_KIT
                                ├── 处理局部颜色模式（如果需要）
                                ├── 调用 Kit 构建器
                                └── 缓存到 themes_
                                ↓
                            (如果 Kit 失败)
                                ↓
                            GetThemeOrigin(type)
                                ├── 检查 THEME_BUILDERS
                                ├── 调用构建函数
                                └── 缓存到 themes_
```

#### 带 ThemeScopeId 版本（Token 主题）

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:318-377`

```cpp
RefPtr<Theme> ThemeManagerImpl::GetTheme(ThemeType type, TokenThemeScopeId themeScopeId)
{
    if (MultiThreadBuildManager::IsThreadSafeNodeScope()) {
        return GetThemeMultiThread(type, themeScopeId);
    }
    std::lock_guard<std::recursive_mutex> lock(themeMultiThreadMutex_);
    return GetThemeNormal(type, themeScopeId);
}

RefPtr<Theme> ThemeManagerImpl::GetThemeNormal(ThemeType type, TokenThemeScopeId themeScopeId)
{
    auto theme = GetThemeKit(type, themeScopeId);
    CHECK_NULL_RETURN(theme, GetThemeOrigin(type, themeScopeId));
    return theme;
}

RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type, int32_t themeScopeId)
{
    // 1. 从 TokenThemeStorage 获取 Token 主题
    auto tokenTheme = NG::TokenThemeStorage::GetInstance()->GetTheme(themeScopeId);
    if (!tokenTheme) {
        return GetTheme(type);  // 退化为普通主题
    }

    // 2. 获取当前颜色模式
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, GetTheme(type));
    ColorMode currentMode = GetCurrentColorMode();
    ColorMode themeMode = tokenTheme->GetColorMode();

    // 3. 根据颜色模式选择缓存
    auto& themeWrappers = GetThemeWrappers(
        themeMode == ColorMode::COLOR_MODE_UNDEFINED ? currentMode : themeMode);

    // 4. 检查缓存
    auto findIter = themeWrappers.find(type);
    if (findIter != themeWrappers.end()) {
        auto wrapper = findIter->second;
        wrapper->ApplyTokenTheme(*tokenTheme);  // 应用 Token 主题
        return AceType::DynamicCast<Theme>(wrapper);
    }

    // 5. 查找构建器
    auto builderIter = TOKEN_THEME_WRAPPER_BUILDERS.find(type);
    if (builderIter == TOKEN_THEME_WRAPPER_BUILDERS.end()) {
        return GetTheme(type);  // 没有包装器构建器，退化为普通主题
    }

    // 6. 处理局部颜色模式不匹配
    bool needRestore = false;
    if (themeMode != ColorMode::COLOR_MODE_UNDEFINED && themeMode != currentMode) {
        // 当前主题的局部颜色模式与实际配色方案不匹配
        ResourceManager::GetInstance().UpdateColorMode(
            pipeline->GetBundleName(), pipeline->GetModuleName(),
            pipeline->GetInstanceId(), themeMode);
        pipeline->SetLocalColorMode(themeMode);
        needRestore = true;
    }

    // 7. 构建主题包装器
    auto wrapper = builderIter->second(themeConstants_);
    if (needRestore) {
        // 切换资源管理器回系统颜色模式
        pipeline->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
        ResourceManager::GetInstance().UpdateColorMode(
            pipeline->GetBundleName(), pipeline->GetModuleName(),
            pipeline->GetInstanceId(), currentMode);
    }

    // 8. 应用 Token 主题并缓存
    wrapper->ApplyTokenTheme(*tokenTheme);
    themeWrappers.emplace(type, wrapper);
    return AceType::DynamicCast<Theme>(wrapper);
}
```

**流程图**：

```
GetTheme(type, themeScopeId)
    ↓
检查多线程模式
    ├── 是 → GetThemeMultiThread(type, themeScopeId)
    └── 否 → GetThemeNormal(type, themeScopeId)
              ↓
          TokenThemeStorage::GetTheme(themeScopeId)
              ├── themeScopeId == 0 → GetDefaultTheme()
              └── else → CacheGet(themeScopeMap_[themeScopeId])
              ↓
          (Token 主题存在?)
              ├── 否 → GetTheme(type)  // 退化
              └── 是 → 继续
                        ↓
                    获取颜色模式
                        ├── currentMode = GetCurrentColorMode()
                        └── themeMode = tokenTheme->GetColorMode()
                        ↓
                    选择缓存（Light 或 Dark）
                        ↓
                    检查 themeWrappers 缓存
                        ├── 命中 → ApplyTokenTheme() → 返回
                        └── 未命中 → 继续
                                  ↓
                              查找 TOKEN_THEME_WRAPPER_BUILDERS
                                  ├── 未找到 → GetTheme(type)
                                  └── 找到 → 继续
                                            ↓
                                        处理颜色模式不匹配
                                            ↓
                                        构建主题包装器
                                            ↓
                                        ApplyTokenTheme()
                                            ↓
                                        缓存到 themeWrappers
                                            ↓
                                        返回 wrapper
```

### 3.3 配置更新流程（UpdateConfig）

**Source**: `frameworks/core/components/theme/theme_manager_impl.h:38-41`

```cpp
void UpdateConfig(const ResourceConfiguration& config) override
{
    themeConstants_->UpdateConfig(config);
}
```

**ThemeConstants::UpdateConfig** 链路：

```
ThemeManager::UpdateConfig(config)
    ↓
ThemeConstants::UpdateConfig(config)
    ↓
ResourceAdapter::UpdateConfig(config, themeFlag)
    ↓
ResourceManager::UpdateConfiguration(config)
    ↓
系统资源更新（颜色、方向、DPI 等）
```

### 3.4 主题切换和缓存失效机制

#### 主题切换触发点

1. **系统颜色模式切换（完整流程）**

   **Source**: 基于实际代码分析（`adapter/ohos/entrance/`）

   **架构说明**：
   - **FA 模型** (Feature Ability)：基于 AceAbility，调用方为元能力子系统
   - **Stage 模型**：基于 UIContent，调用方为窗口子系统
   - 两条独立的调用链最终汇聚到 AceContainer::UpdateConfiguration()

   ```
   ┌─────────────────────────────────────────────────────────────────────┐
   │                       应用模型层（双入口）                           │
   ├──────────────────────────────┬──────────────────────────────────────┤
   │ ① FA 模型                      │ ① Stage 模型                       │
   │    元能力子系统                │    窗口子系统                      │
   │         ↓                     │         ↓                         │
   │    OHOS::AppExecFwk::        │    OHOS::Rosen::Window*            │
   │    Configuration::Update()   │    (窗口配置变更通知)               │
   │         ↓                     │         ↓                         │
   │    Ability::                │    UIContentStubImpl::             │
   │    OnConfigurationUpdated()  │    NotifyConfigurationUpdate()     │
   │         ↓                     │         ↓                         │
   │ ┌────────────────────────┐   │ ┌────────────────────────────┐    │
   │ │ AceAbility::           │   │ │ UIContentImpl::            │    │
   │ │ OnConfigurationUpdated()│   │ │ UpdateConfiguration(config)│    │
   │ │ Location:              │   │ │ Location:                  │    │
   │ │ ace_ability.cpp:614    │   │ │ ui_content_impl.cpp:3275   │    │
   │ └────────────────────────┘   │ └────────────────────────────┘    │
   └──────────────────────────────┴──────────────────────────────────────┘
                                      ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ ② AceContainer 层（核心逻辑）                              │
   │    AceContainer::UpdateConfiguration()                     │
   │    Location: adapter/ohos/entrance/ace_container.cpp:3676 │
   │                                                             │
   │    ① BuildResConfig(resConfig, ...)                        │
   │    ② SetColorMode() → Container::colorMode_ = LIGHT/DARK   │
   │    ③ ThemeManager::UpdateConfig(resConfig)                 │
   │    ④ ThemeManager::LoadResourceThemes() ← 清空缓存         │
   │    ⑤ 判断配置变更类型                                       │
   └────────────────────────────┬────────────────────────────────┘
                                ↓
                ┌───────────────┴───────────────┐
                │ configurationChange.          │
                │ OnlyColorModeChange()?        │
                ↓                               ↓
        【快速路径】                    【完整路径】
        (仅颜色模式)                   (其他配置变更)
                │                               │
                ↓                               ↓
   ┌─────────────────────────┐    ┌──────────────────────────┐
   │ ⑤a. ReloadThemeCache()  │    │ ⑤b. OnFrontUpdated()     │
   │     TokenThemeStorage   │    │     SaveConfigurationConfig() │
   │     ::CacheResetColor() │    │     NotifyConfigurationChange() │
   │                         │    │     NotifyConfigToSubContainers() │
   │ ⑥a. UpdateColorMode()   │    │     ClearImageCache()     │
   │     ├─ PipelineContext  │    │                          │
   │     │  ::NotifyColorModeChange(0/1) │
   │     └─ NotifyConfigToSubContainers() │
   └─────────────────────────┘    └──────────────────────────┘
                │                               │
                └───────────────┬───────────────┘
                                ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 5. PipelineContext 层                                       │
   │    PipelineContext::NotifyColorModeChange(uint32_t colorMode)│
   │    Location: frameworks/core/pipeline_ng/pipeline_context.cpp:6850 │
   │                                                             │
   │    • 创建 400ms 动画 Lambda                                 │
   │      [colorMode, rootColorMode = GetColorMode()]           │
   │    • AnimationUtils::Animate(400ms, FRICTION 曲线)         │
   │    • Lambda 回调执行：                                       │
   │      - rootNode->SetDarkMode(rootColorMode == DARK)        │
   │      - rootNode->NotifyColorModeChange(colorMode)          │
   └────────────────────────────┬────────────────────────────────┘
                                ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 6. FrameNode 层（节点级更新）                               │
   │    FrameNode::NotifyColorModeChange(colorMode)             │
   │    Location: frameworks/core/components_ng/base/frame_node.cpp:1640 │
   │                                                             │
   │    ① 计算 GetRerenderable()                                │
   │    ② if (GetRerenderable()) {                              │
   │         SetDarkMode(GetContext()->GetColorMode() == DARK) │
   │       }                                                    │
   │    ③ Pattern::OnColorModeChange(colorMode)                 │
   │    ④ 递归通知子节点                                        │
   └────────────────────────────┬────────────────────────────────┘
                                ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 7. Pattern 层（组件级更新）                                 │
   │    Pattern::OnColorConfigurationUpdate()                   │
   │    Pattern::OnColorModeChange(colorMode)                   │
   │    Pattern::GetTheme<ColorProperty>()  ← 重新获取主题      │
   └─────────────────────────────────────────────────────────────┘
   ```

   **关键代码位置**：

   | 应用模型 | 入口方法 | 文件位置 | 行号 | 调用方 |
   |---------|---------|----------|------|--------|
   | **FA 模型** | AceAbility::OnConfigurationUpdated | `adapter/ohos/entrance/ace_ability.cpp` | 614-638 | 元能力子系统 |
   | **Stage 模型** | UIContentImpl::UpdateConfiguration | `adapter/ohos/entrance/ui_content_impl.cpp` | 3275-3296 | 窗口子系统 |
   | **共同路径** | AceContainer::UpdateConfiguration | `adapter/ohos/entrance/ace_container.cpp` | 3676-3728 | 汇聚点 |
   | | SetColorMode | `adapter/ohos/entrance/ace_container.cpp` | 3586/3590 | 更新 Container::colorMode_ |
   | | ThemeManager::UpdateConfig | `adapter/ohos/entrance/ace_container.cpp` | 3700 | 更新主题配置 |
   | | LoadResourceThemes | `adapter/ohos/entrance/ace_container.cpp` | 3706 | 清空主题缓存 |
   | | 快速路径判断 | `adapter/ohos/entrance/ace_container.cpp` | 3707 | OnlyColorModeChange() |
   | | ReloadThemeCache | `adapter/ohos/entrance/ace_container.cpp` | 3708 | Token 缓存重置 |
   | | UpdateColorMode | `adapter/ohos/entrance/ace_container.cpp` | 3596-3615 | 颜色模式更新 |
   | | NotifyColorModeChange | `frameworks/core/pipeline_ng/pipeline_context.cpp` | 6850 | 动画回调 |
   | | FrameNode 更新 | `frameworks/core/components_ng/base/frame_node.cpp` | 1640 | 节点级更新 |

   **应用模型对比**：

   | 特性 | FA 模型 | Stage 模型 |
   |------|---------|------------|
   | **入口类** | AceAbility | UIContentImpl |
   | **继承关系** | 继承自 OHOS::AppExecFwk::Ability | 实现 UIContent 接口 |
   | **调用方** | 元能力子系统 | 窗口子系统 |
   | **配置来源** | Ability::OnConfigurationUpdated() | Window 配置变更通知 |
   | **异步任务** | PostTask 到 UI 线程 | PostTask 到 UI 线程 |
   | **汇聚点** | AceContainer::UpdateConfiguration() | AceContainer::UpdateConfiguration() |
   | **适用场景** | 传统 FA 应用 | Stage 模型应用（推荐） |

   **流程特点**：

   - ✅ **三层缓存清空**：ThemeManager 缓存、TokenThemeStorage 缓存、图片缓存
   - ✅ **快速路径优化**：仅颜色模式变更时走快速路径（避免完整配置更新开销）
   - ✅ **异步动画过渡**：400ms 摩擦曲线动画，平滑过渡
   - ✅ **子容器同步**：NotifyConfigToSubContainers 确保子容器配置一致

2. **WithThemeNode 局部主题更新**
   ```
   WithThemeNode::NotifyThemeScopeUpdate()
       ↓
   子节点 Pattern::OnThemeScopeUpdate()
       ↓
   Pattern::GetTheme(themeScopeId)  // 获取新主题
   ```

3. **旧自定义主题覆盖链路**
   ```
   旧 resources/styles/*.json 自定义样式覆盖链路
   已随 theme.csv 预置主题系统下线移除。
   ```

#### 缓存失效策略

| 缓存类型 | 失效时机 | 失败方式 |
|---------|---------|----------|
| `themes_` | `LoadResourceThemes()` | `themes_.clear()` |
| `themeWrappersLight_` | `LoadResourceThemes()` | `themeWrappersLight_.clear()` |
| `themeWrappersDark_` | `LoadResourceThemes()` | `themeWrappersDark_.clear()` |
| `TokenThemeStorage::themeCache_` | `CacheRemove()`, `CacheClear()` | 手动移除或清空 |

**设计权衡**：

- ✅ **优点**：完全清空缓存确保配置更新后所有组件使用新主题
- ❌ **缺点**：配置切换后首次访问所有主题需要重新构建（性能开销）
- 🔧 **改进方向**：可考虑增量更新机制（只更新受影响的主题）

---

## 4. 关键特性

### 4.1 颜色模式支持（深浅色模式）

#### ColorMode 定义

```cpp
enum class ColorMode {
    LIGHT = 0,
    DARK = 1,
    COLOR_MODE_UNDEFINED = -1  // 跟随系统
};
```

#### 当前颜色模式获取

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:471-478`

```cpp
ColorMode ThemeManagerImpl::GetCurrentColorMode() const
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    ColorMode systemMode = Container::CurrentColorMode();
    CHECK_NULL_RETURN(pipelineContext, systemMode);
    ColorMode localMode = pipelineContext->GetLocalColorMode();
    // 优先使用局部模式，否则使用系统模式
    return localMode == ColorMode::COLOR_MODE_UNDEFINED ? systemMode : localMode;
}
```

#### 浅色/深色缓存选择

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:466-468`

```cpp
ThemeManagerImpl::ThemeWrappers& ThemeManagerImpl::GetThemeWrappers(ColorMode mode)
{
    return mode == ColorMode::DARK ? themeWrappersDark_ : themeWrappersLight_;
}
```

**工作原理**：

```
GetTheme(type, themeScopeId)
    ↓
GetCurrentColorMode()
    ├── localMode != COLOR_MODE_UNDEFINED → 使用 localMode
    └── localMode == COLOR_MODE_UNDEFINED → 使用 systemMode
    ↓
GetThemeWrappers(mode)
    ├── mode == DARK → 返回 themeWrappersDark_
    └── mode == LIGHT → 返回 themeWrappersLight_
    ↓
从对应缓存中查找/构建主题包装器
```

### 4.2 ThemeScopeId 机制

#### ThemeScopeId 用途

**ThemeScopeId** 用于支持**局部主题覆盖**：

1. **全局主题**（themeScopeId = 0）
   - 使用系统默认主题
   - 通过 `GetTheme(type)` 获取

2. **局部主题**（themeScopeId != 0）
   - 使用 WithThemeNode 定义的自定义主题
   - 通过 `GetTheme(type, themeScopeId)` 获取
   - 支持嵌套（内层主题覆盖外层）

#### WithThemeNode 实现

**Source**: `frameworks/core/components_ng/syntax/with_theme_node.h`

```cpp
class WithThemeNode : public UINode {
public:
    explicit WithThemeNode(int32_t nodeId) : UINode(V2::JS_WITH_THEME_ETS_TAG, nodeId) {
        SetThemeScopeId(nodeId);  // 设置主题作用域 ID
    }

    void SetThemeScopeId(int32_t themeScopeId) override
    {
        UINode::SetThemeScopeId(themeScopeId);
        NotifyThemeScopeUpdate();  // 通知子节点更新主题
    }

    void NotifyThemeScopeUpdate();
};
```

**ArkTS 使用示例**：

```typescript
// 外层使用深色主题
WithTheme() {
  Button('Dark Theme Button')
  // 内层覆盖为浅色主题
  WithTheme() {
    Button('Light Theme Button')  // 这个按钮使用浅色主题
  }
}
```

#### TokenThemeStorage::StoreThemeScope

**Source**: `frameworks/core/components_ng/token_theme/token_theme_storage.cpp:35-38`

```cpp
void TokenThemeStorage::StoreThemeScope(TokenThemeScopeId themeScopeId, int32_t themeId)
{
    themeScopeMap_[themeScopeId] = themeId;  // 建立映射关系
}
```

### 4.3 主题包装器缓存（Light/Dark 双缓存）

#### 双缓存设计

```cpp
class ThemeManagerImpl : public ThemeManager {
private:
    ThemeWrappers themeWrappersLight_;  // 浅色模式缓存
    ThemeWrappers themeWrappersDark_;   // 深色模式缓存
};
```

#### 缓存切换逻辑

```cpp
RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type, int32_t themeScopeId)
{
    // ...
    ColorMode currentMode = GetCurrentColorMode();
    ColorMode themeMode = tokenTheme->GetColorMode();

    // 根据主题的颜色模式选择对应缓存
    auto& themeWrappers = GetThemeWrappers(
        themeMode == ColorMode::COLOR_MODE_UNDEFINED ? currentMode : themeMode);

    auto findIter = themeWrappers.find(type);
    if (findIter != themeWrappers.end()) {
        auto wrapper = findIter->second;
        wrapper->ApplyTokenTheme(*tokenTheme);  // 更新 Token 主题
        return AceType::DynamicCast<Theme>(wrapper);
    }
    // ... 构建并缓存
}
```

**优势**：

1. **快速模式切换**：Light/Dark 模式切换时无需重新构建 ThemeWrapper
2. **按需应用**：调用 `ApplyTokenTheme()` 动态更新颜色
3. **内存效率**：同一类型只缓存一个 Light 和一个 Dark 包装器

### 4.4 性能优化策略

#### 4.4.1 延迟构建（Lazy Construction）

```cpp
RefPtr<Theme> ThemeManagerImpl::GetThemeNormal(ThemeType type)
{
    auto findIter = themes_.find(type);
    if (findIter != themes_.end()) {
        return findIter->second;  // 缓存命中，立即返回
    }

    // 缓存未命中，才构建主题
    auto theme = GetThemeKit(type);
    CHECK_NULL_RETURN(theme, GetThemeOrigin(type));
    return theme;
}
```

**优化效果**：

- ✅ 只构建实际使用的主题
- ✅ 避免启动时构建 60+ 主题的开销
- ✅ 减少内存占用

#### 4.4.2 双层缓存

```
Level 1: themes_ (普通主题)
    ├── 命中率: 高（大部分组件使用普通主题）
    └── 查找复杂度: O(1) unordered_map

Level 2: themeWrappersLight_/Dark_ (Token 主题包装器)
    ├── 命中率: 中（仅 Token 主题场景）
    └── 查找复杂度: O(1) unordered_map

Level 3: TokenThemeStorage::themeCache_ (Token 主题)
    ├── 命中率: 低（仅自定义主题）
    └── 查找复杂度: O(log n) map（有序）
```

#### 4.4.3 颜色模式临时切换优化

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:358-373`

```cpp
RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type, int32_t themeScopeId)
{
    // ...
    bool needRestore = false;
    if (themeMode != ColorMode::COLOR_MODE_UNDEFINED && themeMode != currentMode) {
        // 临时切换到局部颜色模式
        ResourceManager::GetInstance().UpdateColorMode(
            pipeline->GetBundleName(), pipeline->GetModuleName(),
            pipeline->GetInstanceId(), themeMode);
        pipeline->SetLocalColorMode(themeMode);
        needRestore = true;
    }
    auto wrapper = builderIter->second(themeConstants_);
    if (needRestore) {
        // 立即恢复系统颜色模式
        pipeline->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
        ResourceManager::GetInstance().UpdateColorMode(
            pipeline->GetBundleName(), pipeline->GetModuleName(),
            pipeline->GetInstanceId(), currentMode);
    }
    // ...
}
```

**优化要点**：

1. **最小化临时切换窗口**：只在构建期间切换模式
2. **立即恢复**：构建完成后立即恢复系统模式
3. **避免副作用**：不影响其他组件的颜色模式

---

## 5. 代码组织

### 5.1 目录结构和文件分布

```
ace_engine/
├── frameworks/
│   ├── core/
│   │   ├── components/                      # Legacy 组件主题
│   │   │   ├── theme/                       # 主题系统核心
│   │   │   │   ├── theme_manager.h          # ThemeManager 抽象接口
│   │   │   │   ├── theme_manager_impl.h     # ThemeManagerImpl 实现类
│   │   │   │   ├── theme_manager_impl.cpp   # 实现代码（479 行）
│   │   │   │   ├── theme_manager_multi_thread.cpp  # 多线程支持
│   │   │   │   ├── theme_constants.h        # 资源常量管理
│   │   │   │   ├── theme_constants.cpp      # 资源常量实现
│   │   │   │   ├── theme_attributes.h       # 主题属性
│   │   │   │   ├── theme_attributes.cpp     # 主题属性实现
│   │   │   │   ├── theme_style.h            # 主题样式
│   │   │   │   ├── resource_adapter.h       # 资源适配器接口
│   │   │   │   ├── app_theme.h              # 应用主题
│   │   │   │   ├── icon_theme.h             # 图标主题
│   │   │   │   ├── blur_style_theme.h       # 模糊样式主题
│   │   │   │   ├── shadow_theme.h           # 阴影主题
│   │   │   │   └── ...
│   │   │   ├── button/                      # Button 组件
│   │   │   │   ├── button_theme.h           # Button 主题定义
│   │   │   │   └── ...
│   │   │   ├── text/                        # Text 组件
│   │   │   │   ├── text_theme.h             # Text 主题定义
│   │   │   │   └── ...
│   │   │   └── [其他组件主题...]
│   │   └── components_ng/                   # NG 组件
│   │       ├── token_theme/                 # Token 主题系统
│   │       │   ├── token_theme_storage.h    # Token 主题存储
│   │       │   ├── token_theme_storage.cpp  # Token 主题存储实现
│   │       │   ├── token_theme.h            # Token 主题定义
│   │       │   └── token_theme_wrapper.h    # Token 主题包装器
│   │       ├── pattern/                     # Pattern 层
│   │       │   ├── text/
│   │       │   │   └── text_theme_wrapper.h # Text 主题包装器
│   │       │   ├── checkbox/
│   │       │   │   └── checkbox_theme_wrapper.h
│   │       │   └── [其他组件主题包装器...]
│   │       └── syntax/
│   │           └── with_theme_node.h        # WithTheme 语法节点
│   └── interfaces/
│       └── inner_api/
│           └── ace_kit/
│               └── include/ui/view/theme/
│                   ├── theme.h               # Theme 基类
│                   ├── token_theme.h         # TokenTheme 定义
│                   └── token_theme_wrapper.h # TokenThemeWrapper 接口
└── test/
    ├── unittest/core/manager/
    │   └── theme_manager_test_ng.cpp        # ThemeManager 单元测试
    └── unittest/interfaces/ace_kit/
        └── token_theme_test.cpp             # Token 主题测试
```

### 5.2 应用模型入口（FA vs Stage）

ACE Engine 支持两种应用模型，通过不同的入口类触发主题切换：

#### FA 模型入口

**位置**: `adapter/ohos/entrance/ace_ability.h` `ace_ability.cpp`

```cpp
class AceAbility final : public OHOS::AppExecFwk::Ability {
public:
    void OnConfigurationUpdated(const Configuration& configuration) override;
    // ...
};
```

**特点**：
- **继承关系**: 继承自 OHOS::AppExecFwk::Ability
- **调用方**: 元能力子系统
- **配置来源**: Ability 基类的 OnConfigurationUpdated 回调
- **适用场景**: 传统 FA (Feature Ability) 应用

**代码流程** (ace_ability.cpp:614-638):
```cpp
void AceAbility::OnConfigurationUpdated(const Configuration& configuration)
{
    Ability::OnConfigurationUpdated(configuration);  // 调用基类

    auto container = Platform::AceContainer::GetContainer(abilityId_);
    auto taskExecutor = container->GetTaskExecutor();
    taskExecutor->PostTask(
        [weakContainer, configuration]() {
            Platform::ParsedConfig parsedConfig;
            parsedConfig.colorMode = configuration.GetItem(
                OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
            // ... 解析其他配置项
            container->UpdateConfiguration(parsedConfig, configuration.GetName());
        },
        TaskExecutor::TaskType::UI, "ArkUIAbilityUpdateConfiguration");
}
```

#### Stage 模型入口

**位置**: `adapter/ohos/entrance/ui_content_impl.h` `ui_content_impl.cpp`

```cpp
class ACE_FORCE_EXPORT UIContentImpl : public UIContent {
public:
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);
    // ...
};
```

**特点**：
- **接口实现**: 实现 UIContent 接口
- **调用方**: 窗口子系统
- **配置来源**: Rosen::Window 配置变更通知
- **适用场景**: Stage 模型应用（推荐）

**代码流程** (ui_content_impl.cpp:3275-3296):
```cpp
void UIContentImpl::UpdateConfiguration(
    const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    CHECK_NULL_VOID(config);
    StoreConfiguration(config);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    taskExecutor->PostTask(
        [weakContainer, config, instanceId = instanceId_]() {
            auto container = weakContainer.Upgrade();
            Platform::ParsedConfig parsedConfig;
            BuildParsedConfig(parsedConfig, config, formFontUseDefault);
            container->UpdateConfiguration(parsedConfig, config->GetName());
        },
        TaskExecutor::TaskType::UI, "ArkUIUIContentUpdateConfiguration");
}
```

#### 双模型对比

| 特性 | FA 模型 | Stage 模型 |
|------|---------|------------|
| **入口类** | AceAbility | UIContentImpl |
| **基类/接口** | 继承 Ability | 实现 UIContent |
| **调用方** | 元能力子系统 | 窗口子系统 |
| **配置对象** | OHOS::AppExecFwk::Configuration | OHOS::AppExecFwk::Configuration |
| **配置来源** | Ability 回调 | Window 通知 |
| **解析方式** | 直接从 Configuration 提取 | BuildParsedConfig 辅助函数 |
| **异步任务** | PostTask 到 UI 线程 | PostTask 到 UI 线程 |
| **汇聚点** | AceContainer::UpdateConfiguration() | AceContainer::UpdateConfiguration() |
| **推荐使用** | 遗留系统 | 新应用（推荐） |

**架构图**：

```
┌─────────────────────────────────────────────────────────┐
│                    应用层                               │
├──────────────────────┬──────────────────────────────────┤
│   FA 模型应用         │   Stage 模型应用                  │
│                      │                                  │
│   AceAbility         │   UIContentImpl                  │
│   (继承 Ability)      │   (实现 UIContent)               │
└──────────┬───────────┴──────────────┬───────────────────┘
           ↓                          ↓
┌─────────────────────────────────────────────────────────┐
│              Ace Container 层（汇聚点）                   │
│                                                          │
│   AceContainer::UpdateConfiguration()                   │
│   • 统一的配置处理逻辑                                    │
│   • ThemeManager 更新                                    │
│   • 颜色模式切换                                          │
└──────────────────────────┬───────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────┐
│                 ThemeManager 层                         │
│                                                          │
│   ThemeManager::UpdateConfig()                          │
│   ThemeManager::LoadResourceThemes()                    │
└─────────────────────────────────────────────────────────┘
```

**设计优势**：
- ✅ **统一处理**: 两种模型最终汇聚到同一配置处理逻辑
- ✅ **向后兼容**: 支持 FA 和 Stage 模型共存
- ✅ **灵活切换**: 开发者可以选择适合的应用模型
- ✅ **代码复用**: ThemeManager 和资源适配层代码共享

### 5.3 核心类和接口

#### ThemeManager（抽象接口）

**文件**: `frameworks/core/components/theme/theme_manager.h`

**职责**：
- 定义主题管理的公共接口
- 提供模板方法 `GetTheme<T>()`
- 定义 Kit 扩展注册接口

**核心方法**：
```cpp
virtual RefPtr<Theme> GetTheme(ThemeType type) = 0;
virtual RefPtr<Theme> GetTheme(ThemeType type, int32_t themeScopeId) = 0;
virtual RefPtr<ThemeConstants> GetThemeConstants() const = 0;
virtual void LoadResourceThemes() = 0;
```

#### ThemeManagerImpl（实现类）

**文件**:
- `frameworks/core/components/theme/theme_manager_impl.h`
- `frameworks/core/components/theme/theme_manager_impl.cpp` (479 lines)
- `frameworks/core/components/theme/theme_manager_multi_thread.cpp`

**职责**：
- 实现 ThemeManager 接口
- 管理主题缓存（themes_、themeWrappersLight_/Dark_）
- 支持普通主题和 Token 主题获取
- 支持多线程安全访问

**核心数据成员**：
```cpp
std::unordered_map<ThemeType, RefPtr<Theme>> themes_;
ThemeWrappers themeWrappersLight_;
ThemeWrappers themeWrappersDark_;
RefPtr<ThemeConstants> themeConstants_;
std::recursive_mutex themeMultiThreadMutex_;
```

**核心方法**：
```cpp
RefPtr<Theme> GetThemeNormal(ThemeType type);
RefPtr<Theme> GetThemeOrigin(ThemeType type);
RefPtr<Theme> GetThemeKit(ThemeType type);
RefPtr<Theme> GetThemeNormal(ThemeType type, int32_t themeScopeId);
RefPtr<Theme> GetThemeOrigin(ThemeType type, int32_t themeScopeId);
RefPtr<Theme> GetThemeKit(ThemeType type, int32_t themeScopeId);
void LoadResourceThemesInner();
ColorMode GetCurrentColorMode() const;
ThemeWrappers& GetThemeWrappers(ColorMode mode);
```

#### ThemeConstants（资源常量管理器）

**文件**:
- `frameworks/core/components/theme/theme_constants.h`
- `frameworks/core/components/theme/theme_constants.cpp`

**职责**：
- 桥接 ResourceAdapter 和主题系统
- 提供资源获取接口（GetColor, GetDimension, GetString 等）
- 解析主题样式（ThemeStyle）

**核心方法**：
```cpp
Color GetColor(uint32_t key) const;
Dimension GetDimension(uint32_t key) const;
std::string GetString(uint32_t key) const;
int32_t GetInt(uint32_t key) const;
RefPtr<ThemeStyle> GetPatternByName(const std::string& patternName);
void LoadTheme(int32_t themeId);
void UpdateConfig(const ResourceConfiguration& config);
```

#### TokenThemeStorage（Token 主题存储）

**文件**:
- `frameworks/core/components_ng/token_theme/token_theme_storage.h`
- `frameworks/core/components_ng/token_theme/token_theme_storage.cpp`

**职责**：
- 管理 Token 主题的全局缓存
- 管理 ThemeScopeId 到 ThemeId 的映射
- 提供默认浅色/深色主题

**核心数据成员**：
```cpp
std::unordered_map<TokenThemeScopeId, int32_t> themeScopeMap_;
std::map<int32_t, RefPtr<TokenTheme>> themeCache_;
std::mutex themeCacheMutex_;
inline static RefPtr<TokenTheme> defaultLightTheme_ = nullptr;
inline static RefPtr<TokenTheme> defaultDarkTheme_ = nullptr;
```

**核心方法**：
```cpp
void StoreThemeScope(TokenThemeScopeId themeScopeId, int32_t themeId);
void RemoveThemeScope(TokenThemeScopeId themeScopeId, bool removeToken);
const RefPtr<TokenTheme>& GetTheme(TokenThemeScopeId themeScopeId);
void SetDefaultTheme(const RefPtr<TokenTheme>& theme, ColorMode colorMode);
const RefPtr<TokenTheme>& GetDefaultTheme();
RefPtr<TokenTheme> ObtainSystemTheme(ColorMode themeColorMode);
```

#### TokenThemeWrapper（主题包装器基类）

**文件**: `interfaces/inner_api/ace_kit/include/ui/view/theme/token_theme_wrapper.h`

**职责**：
- 定义 Theme 到 TokenTheme 的适配接口
- 子类实现具体的 `ApplyTokenTheme` 逻辑

**核心接口**：
```cpp
class TokenThemeWrapper : virtual public Theme {
public:
    virtual void ApplyTokenTheme(const TokenTheme& theme) = 0;
};
```

#### 具体主题类

**示例**：
- `ButtonTheme`: `frameworks/core/components/button/button_theme.h`
- `TextTheme`: `frameworks/core/components/text/text_theme.h`
- `CheckboxTheme`: `frameworks/core/components/checkable/checkable_theme.h`

**通用结构**：
```cpp
class [Component]Theme : public virtual Theme {
public:
    class Builder {
    public:
        RefPtr<[Component]Theme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
                         const RefPtr<[Component]Theme>& theme) const;
    };

    // 主题属性（颜色、尺寸、样式等）
    Color bgColor_;
    TextStyle textStyle_;
    Dimension radius_;
    // ...
};
```

#### 主题包装器实现

**示例**：
- `TextThemeWrapper`: `frameworks/core/components_ng/pattern/text/text_theme_wrapper.h`
- `CheckboxThemeWrapper`: `frameworks/core/components_ng/pattern/checkbox/checkbox_theme_wrapper.h`

**通用结构**：
```cpp
class [Component]ThemeWrapper : public [Component]Theme, public TokenThemeWrapper {
public:
    class WrapperBuilder : public Builder {
    public:
        RefPtr<TokenThemeWrapper> BuildWrapper(
            const RefPtr<ThemeConstants>& themeConstants) const;
    };

    void ApplyTokenTheme(const TokenTheme& theme) override;
};
```

### 5.3 关键数据结构

#### THEME_BUILDERS 映射表

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:113-184`

```cpp
const std::unordered_map<ThemeType, RefPtr<Theme>(*)(const RefPtr<ThemeConstants>&)>
    THEME_BUILDERS = {
    { AppTheme::TypeId(), &ThemeBuildFunc<AppTheme::Builder> },
    { ButtonTheme::TypeId(), &ThemeBuildFunc<ButtonTheme::Builder> },
    // ... 60+ 主题类型
};
```

**作用**：将 ThemeType 映射到对应的构建函数

#### TOKEN_THEME_WRAPPER_BUILDERS 映射表

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:192-212`

```cpp
const std::unordered_map<ThemeType, RefPtr<TokenThemeWrapper>(*)(const RefPtr<ThemeConstants>&)>
    TOKEN_THEME_WRAPPER_BUILDERS = {
    { CheckboxTheme::TypeId(), &ThemeWrapperBuildFunc<NG::CheckboxThemeWrapper::WrapperBuilder> },
    { SwitchTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SwitchThemeWrapper::WrapperBuilder> },
    // ... 13+ 主题包装器
};
```

**作用**：将 ThemeType 映射到对应的主题包装器构建函数

#### THEME_BUILDERS_KIT / TOKEN_THEME_WRAPPER_BUILDERS_KIT

**Source**: `frameworks/core/components/theme/theme_manager_impl.cpp:214-215`

```cpp
std::unordered_map<ThemeType, Ace::Kit::BuildFunc> THEME_BUILDERS_KIT;
std::unordered_map<ThemeType, Ace::Kit::BuildThemeWrapperFunc> TOKEN_THEME_WRAPPER_BUILDERS_KIT;
```

**作用**：运行时注册的 Kit 扩展构建器（支持动态插件）

---

## 6. 调用关系图

### 6.1 从系统配置到主题更新的完整调用链

#### 颜色模式切换场景（完整流程）

**Source**: 基于3.4节"系统颜色模式切换（完整流程）"

```
┌─────────────────────────────────────────────────────────────────┐
│ ① 应用模型层（双入口）                                           │
├──────────────────────────────┬──────────────────────────────────┤
│ FA 模型                        │ Stage 模型                        │
│   元能力子系统                │   窗口子系统                      │
│        ↓                     │        ↓                         │
│   AceAbility::               │   UIContentImpl::                │
│   OnConfigurationUpdated()   │   UpdateConfiguration(config)    │
│   ace_ability.cpp:614        │   ui_content_impl.cpp:3275       │
└──────────┬───────────────────┴──────────────┬───────────────────┘
           ↓                                  ↓
┌─────────────────────────────────────────────────────────────────┐
│ ② AceContainer 层（配置处理核心）                                 │
│   AceContainer::UpdateConfiguration()                            │
│   ace_container.cpp:3676                                         │
│                                                                   │
│   ① BuildResConfig(resConfig, ...)                               │
│   ② SetColorMode() → Container::colorMode_ = LIGHT/DARK          │
│   ③ ThemeManager::UpdateConfig(resConfig)                        │
│   ④ ThemeManager::LoadResourceThemes() ← 清空缓存                │
│   ⑤ 判断配置变更类型                                              │
└───────────────────────────────┬───────────────────────────────────┘
                                ↓
                ┌───────────────┴───────────────┐
                │ configurationChange.          │
                │ OnlyColorModeChange()?        │
                ↓                               ↓
        【快速路径】                    【完整路径】
        (仅颜色模式)                   (其他配置变更)
                │                               │
                ↓                               ↓
   ┌─────────────────────────┐    ┌──────────────────────────┐
   │ ⑤a. ReloadThemeCache()  │    │ ⑤b. OnFrontUpdated()     │
   │     TokenThemeStorage   │    │     SaveConfigurationConfig() │
   │     ::CacheResetColor() │    │     NotifyConfigurationChange() │
   │                         │    │     NotifyConfigToSubContainers() │
   │ ⑥a. UpdateColorMode()   │    │     ClearImageCache()     │
   │     ace_container.cpp:  │    │                          │
   │     3596-3615            │    │                          │
   │     ├─ PipelineContext  │    │                          │
   │     │  ::NotifyColorModeChange(0/1) │
   │     │  pipeline_context.cpp:6850 │
   │     └─ NotifyConfigToSubContainers() │
   └─────────────────────────┘    └──────────────────────────┘
                │                               │
                └───────────────┬───────────────┘
                                ↓
┌─────────────────────────────────────────────────────────────────┐
│ ③ PipelineContext 层（动画过渡）                                  │
│   PipelineContext::NotifyColorModeChange(uint32_t colorMode)    │
│   pipeline_context.cpp:6850                                       │
│                                                                   │
│   • 创建 400ms 动画 Lambda                                        │
│     [colorMode, rootColorMode = GetColorMode()]                  │
│   • AnimationUtils::Animate(400ms, FRICTION 曲线)                │
│   • Lambda 回调执行：                                              │
│     - rootNode->SetDarkMode(rootColorMode == DARK)               │
│     - rootNode->NotifyColorModeChange(colorMode)                 │
└───────────────────────────────┬───────────────────────────────────┘
                                ↓
┌─────────────────────────────────────────────────────────────────┐
│ ④ FrameNode 层（节点级更新）                                      │
│   FrameNode::NotifyColorModeChange(colorMode)                    │
│   frame_node.cpp:1640                                             │
│                                                                   │
│   ① 计算 GetRerenderable()                                       │
│   ② if (GetRerenderable()) {                                     │
│        SetDarkMode(GetContext()->GetColorMode() == DARK)         │
│      }                                                            │
│   ③ Pattern::OnColorModeChange(colorMode)                        │
│   ④ 递归通知子节点                                                │
└───────────────────────────────┬───────────────────────────────────┘
                                ↓
┌─────────────────────────────────────────────────────────────────┐
│ ⑤ Pattern 层（组件级更新）                                       │
│   Pattern::OnColorConfigurationUpdate()                          │
│   Pattern::OnColorModeChange(colorMode)                          │
│   Pattern::GetTheme<ColorProperty>()  ← 重新获取主题             │
│                                                                   │
│   此时主题缓存已清空，重新构建时使用新颜色模式                    │
└─────────────────────────────────────────────────────────────────┘
```

**关键节点说明**：

| 步骤 | 方法 | 作用 | 位置 |
|------|------|------|------|
| **① 应用层** | AceAbility/UIContentImpl::OnConfigurationUpdated | 配置变更入口 | ace_ability.cpp:614<br>ui_content_impl.cpp:3275 |
| **② 配置处理** | AceContainer::UpdateConfiguration | 统一配置处理 | ace_container.cpp:3676 |
| | SetColorMode | 更新 Container::colorMode_ | ace_container.cpp:3586/3590 |
| | ThemeManager::UpdateConfig | 更新主题配置 | ace_container.cpp:3700 |
| | ThemeManager::LoadResourceThemes | **清空主题缓存** | ace_container.cpp:3706 |
| **③ 快速路径** | UpdateColorMode | 颜色模式专用路径 | ace_container.cpp:3596 |
| | ReloadThemeCache | 清空 Token 缓存 | ace_container.cpp:3708 |
| **④ PipelineContext** | NotifyColorModeChange | 400ms 动画过渡 | pipeline_context.cpp:6850 |
| **⑤ FrameNode** | NotifyColorModeChange | 节点级更新 | frame_node.cpp:1640 |
| **⑥ Pattern** | GetTheme<ColorProperty>() | 重新获取主题 | 各组件 Pattern |

**缓存清空时机**：

```
AceContainer::UpdateConfiguration()
    ↓
ThemeManager::LoadResourceThemes()  // ace_container.cpp:3706
    ↓
ThemeManagerImpl::LoadResourceThemes()
    ├── themes_.clear()              // 清空普通主题缓存
    ├── themeWrappersLight_.clear()  // 清空浅色包装器缓存
    ├── themeWrappersDark_.clear()   // 清空深色包装器缓存
    └── themeConstants_->LoadTheme(currentThemeId_)  // 重新加载常量
            ↓
        ResourceAdapter::LoadTheme(themeId)
            ↓
        重新加载资源（浅色 → 深色）
```

**组件重新渲染流程**：

```
Pattern::OnColorModeChange(colorMode)
    ↓
GetTheme<ButtonTheme>()  // 缓存已清空
    ↓
ThemeManagerImpl::GetThemeNormal(ButtonTheme::TypeId())
    ├── 检查 themes_[ButtonTheme::TypeId()]  // 缓存未命中
    └── GetThemeOrigin(ButtonTheme::TypeId())
            ↓
        THEME_BUILDERS[ButtonTheme::TypeId()](themeConstants_)
            ↓
        ButtonTheme::Builder::Build(themeConstants_)
            ├── 此时 ResourceAdapter 已切换到深色模式
            ├── 从深色主题资源中解析颜色
            └── 创建新的 ButtonTheme（深色版本）
                ↓
            缓存到 themes_[ButtonTheme::TypeId()]
                ↓
            Pattern 应用新主题
                ↓
            组件重新渲染（深色主题）
```

#### WithThemeNode 主题更新场景

```
ArkTS 代码：WithTheme() { Button() }
    ↓
WithThemeNode 创建
    ├── SetThemeScopeId(nodeId)
    └── StoreThemeScope(nodeId, themeId)
          ↓
      子节点 Button 创建
          ↓
      ButtonPattern::OnModifyDone()
          ↓
      GetTheme<ButtonTheme>(themeScopeId)
          ↓
      TokenThemeStorage::GetTheme(themeScopeId)
          ├── themeScopeId == 0 → GetDefaultTheme()
          └── else → CacheGet(themeScopeMap_[themeScopeId])
                ↓
            ThemeManagerImpl::GetThemeOrigin(type, themeScopeId)
                ├── 获取 TokenTheme
                ├── 选择 Light/Dark 缓存
                ├── 检查 themeWrappers 缓存
                ├── 构建或复用 ThemeWrapper
                └── wrapper->ApplyTokenTheme(*tokenTheme)
                      ↓
                  ButtonThemeWrapper::ApplyTokenTheme(const TokenTheme& theme)
                      ├── 从 TokenTheme 获取颜色
                      └── 更新 ButtonTheme 颜色属性
                            ↓
                        ButtonPattern 应用新主题
                            ↓
                        Button 重新渲染
```

### 6.2 主题系统与资源系统的交互

```
组件 Pattern
    ↓
GetTheme<ButtonTheme>()
    ↓
ThemeManagerImpl::GetThemeNormal(type)
    ├── 检查 themes_ 缓存
    ├── 缓存未命中 → GetThemeOrigin(type)
    └── 调用 THEME_BUILDERS[type](themeConstants_)
          ↓
      ButtonTheme::Builder::Build(themeConstants)
          ↓
      ParsePattern(themeConstants, theme)
          ↓
      themeConstants->GetPatternByName(THEME_PATTERN_BUTTON)
          ↓
      ThemeStyle (由 ResourceAdapter 装载，包含按钮主题属性)
          ├── buttonPattern->GetAttr<Color>("button_bg_color")
          ├── buttonPattern->GetAttr<Dimension>("button_radius")
          └── buttonPattern->GetAttr<double>("button_font_weight")
                ↓
            ThemeStyle::GetAttr<T>()
                ↓
                返回主题属性值（Color, Dimension, int, double 等）
```

### 6.3 组件获取主题的典型调用路径

#### 普通 Theme（无 ThemeScopeId）

```
ButtonPattern::OnModifyDone()
    ↓
auto theme = GetTheme<ButtonTheme>()  // 模板方法
    ↓
ThemeManager::GetTheme(ButtonTheme::TypeId())
    ↓
ThemeManagerImpl::GetThemeNormal(ButtonTheme::TypeId())
    ├── 检查 themes_[ButtonTheme::TypeId()]
    ├── 缓存命中 → 返回缓存的主题
    └── 缓存未命中 → GetThemeOrigin(ButtonTheme::TypeId())
            ↓
        THEME_BUILDERS[ButtonTheme::TypeId()](themeConstants_)
            ↓
        ThemeBuildFunc<ButtonTheme::Builder>(themeConstants_)
            ↓
        ButtonTheme::Builder::Build(themeConstants_)
            ├── 创建 ButtonTheme 实例
            ├── ParsePattern(themeConstants, theme)
            └── 返回 ButtonTheme
                ↓
            缓存到 themes_[ButtonTheme::TypeId()]
                ↓
            返回 ButtonTheme
                ↓
        ButtonPattern 使用主题（如 theme->GetBgColor()）
```

#### Token Theme（带 ThemeScopeId）

```
WithThemeNode 作用域内的 Button
    ↓
ButtonPattern::OnModifyDone()
    ↓
auto theme = GetTheme<ButtonTheme>(themeScopeId)  // 带 ThemeScopeId
    ↓
ThemeManager::GetTheme(ButtonTheme::TypeId(), themeScopeId)
    ↓
ThemeManagerImpl::GetThemeNormal(ButtonTheme::TypeId(), themeScopeId)
    ↓
TokenThemeStorage::GetTheme(themeScopeId)
    ├── themeScopeId == 0 → GetDefaultTheme()
    └── else → CacheGet(themeScopeMap_[themeScopeId])
          ↓
      获取 TokenTheme 实例
          ↓
      检查 themeWrappersLight_/Dark_ 缓存
          ├── 缓存命中 → wrapper->ApplyTokenTheme(*tokenTheme)
          └── 缓存未命中 → TOKEN_THEME_WRAPPER_BUILDERS[type](themeConstants_)
                  ↓
              ThemeWrapperBuildFunc<TextThemeWrapper::WrapperBuilder>(themeConstants_)
                  ↓
              TextThemeWrapper::WrapperBuilder::BuildWrapper(themeConstants_)
                  ├── 创建 TextThemeWrapper 实例
                  ├── InitThemeDefaults(theme)
                  ├── ParsePattern(themeConstants, theme)
                  └── 返回 TextThemeWrapper
                      ↓
                  wrapper->ApplyTokenTheme(*tokenTheme)
                      ↓
                  TextThemeWrapper::ApplyTokenTheme(const TokenTheme& theme)
                      ├── theme.Colors()->FontPrimary()
                      └── textStyle_.SetTextColor(color)
                          ↓
                      缓存到 themeWrappersLight_/Dark_
                          ↓
                      返回 TextThemeWrapper
                          ↓
                  ButtonPattern 使用主题包装器
```

---

## 7. 性能优化策略

### 7.1 缓存命中率分析

#### 缓存命中率优化策略

| 缓存类型 | 预期命中率 | 优化策略 |
|---------|-----------|----------|
| `themes_` | 90%+ | • 启动时常用组件主题（Button, Text）快速构建<br>• 使用 unordered_map 实现 O(1) 查找 |
| `themeWrappersLight_/Dark_` | 80%+ | • Light/Dark 双缓存减少模式切换开销<br>• ApplyTokenTheme 只更新颜色，不重建对象 |
| `TokenThemeStorage::themeCache_` | 60%+ | • 使用 std::map 有序存储<br>• 静态 defaultLightTheme_/defaultDarkTheme_ 复用 |

#### 缓存失效优化

**当前实现**：
```cpp
void ThemeManagerImpl::LoadResourceThemesInner()
{
    themes_.clear();            // 全部清空
    themeWrappersLight_.clear(); // 全部清空
    themeWrappersDark_.clear();  // 全部清空
}
```

**潜在优化方向**（未实现）：
- 增量更新：只重新加载受影响的主题
- 版本号机制：为主题添加版本号，只在版本变化时重建
- 弱引用缓存：使用 WeakPtr 自动回收未使用的主题

### 7.2 主题构建性能分析

#### 主题构建开销

**ButtonTheme::Build 开销分解**：

```
ParsePattern(themeConstants, theme)
    ├── GetPatternByName(THEME_PATTERN_BUTTON)      ~10 μs
    ├── buttonPattern->GetAttr<Color>(...) × 30      ~150 μs
    └── buttonPattern->GetAttr<Dimension>(...) × 10  ~100 μs

总计：~260 μs / ButtonTheme
```

**60+ 组件主题构建总开销**：
```
60 组件 × 260 μs = 15.6 ms
```

**优化策略**：
1. **延迟构建**：只构建实际使用的主题（当前实现）
2. **并行构建**：多线程并行构建独立主题（未实现）
3. **预构建**：应用启动时后台预构建常用主题（未实现）

#### TokenTheme 构建

**TokenThemeStorage::CreateSystemTokenTheme 开销**：

```cpp
RefPtr<TokenTheme> TokenThemeStorage::CreateSystemTokenTheme(ColorMode colorMode)
{
    // 获取 ThemeConstants
    auto themeConstants = themeManager->GetThemeConstants();  // ~50 μs

    // 创建 TokenTheme
    auto tokenColors = AceType::MakeRefPtr<TokenColors>();
    auto tokenDarkColors = AceType::MakeRefPtr<TokenColors>();
    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(themeId);  // ~10 μs

    // 加载颜色（TOTAL_NUMBER = 200+）
    std::vector<Color> colors;
    colors.reserve(TokenColors::TOTAL_NUMBER);
    for (size_t resId = 0; resId < TokenColors::TOTAL_NUMBER; ++resId) {
        colors.push_back(themeConstants->GetColor(...));  // ~5 μs × 200 = 1000 μs
    }
    tokenColors->SetColors(std::move(colors));  // ~50 μs

    总计：~1.2 ms / TokenTheme
}
```

### 7.3 颜色模式切换性能

#### 模式切换开销分解

```
系统颜色模式切换
    ↓
LoadResourceThemes()
    ├── 清空缓存                           ~10 μs
    └── themeConstants_->LoadTheme(themeId)  ~50 ms (ResourceAdapter 重新加载资源)
          ↓
      下次 GetTheme<ButtonTheme>()
          └── 重新构建 ButtonTheme            ~260 μs
```

**总开销**：
- 首次模式切换：~50 ms（资源加载）
- 后续组件访问：~260 μs × N（N 为不同组件类型数量）

**优化方向**：
1. **资源预加载**：Light/Dark 资源同时加载（未实现）
2. **主题预构建**：模式切换前预构建新主题（未实现）
3. **动画过渡**：颜色过渡动画提升用户体验（已支持）

### 7.4 内存占用分析

#### 内存占用估算

| 数据结构 | 条目数 | 单条大小 | 总大小 |
|---------|-------|---------|--------|
| `themes_` | 60 | 8 bytes (RefPtr) + 8 bytes (Theme*) | ~960 bytes |
| `themeWrappersLight_` | 13 | 8 bytes (RefPtr) + 8 bytes (Wrapper*) | ~208 bytes |
| `themeWrappersDark_` | 13 | 8 bytes (RefPtr) + 8 bytes (Wrapper*) | ~208 bytes |
| `TokenThemeStorage::themeCache_` | 10 | 8 bytes (RefPtr) + 8 bytes (TokenTheme*) + 16 bytes (map node) | ~320 bytes |
| **实际主题对象** | 60 | ~500 bytes / Theme | ~30 KB |
| **TokenTheme 对象** | 10 | ~2 KB / TokenTheme (200+ Color) | ~20 KB |

**总计**：~50 KB / 应用实例

**优化策略**：
- ✅ 当前内存占用已较低（< 100 KB）
- 🔧 可考虑使用 WeakPtr 自动回收未使用的主题
- 🔧 可考虑 LRU 缓存限制缓存大小

---

## 8. 常见问题与调试

### 8.1 常见问题

#### 问题 1：主题颜色不更新

**现象**：
```
用户切换深浅色模式后，组件颜色仍保持旧颜色
```

**原因分析**：
1. Pattern 未正确调用 `GetTheme<T>()`
2. 主题缓存未清空
3. 组件未标记为 dirty（需要重新渲染）

**调试步骤**：

```cpp
// 1. 检查 LoadResourceThemes 是否调用
// 在 ThemeManagerImpl::LoadResourceThemesInner() 添加日志
void ThemeManagerImpl::LoadResourceThemesInner()
{
    LOGI("LoadResourceThemes: clearing caches");
    themes_.clear();
    themeWrappersLight_.clear();
    themeWrappersDark_.clear();
    themeConstants_->LoadTheme(currentThemeId_);
    LOGI("LoadResourceThemes: done, themes_.size()=%{public}zu", themes_.size());
}

// 2. 检查 Pattern 是否重新获取主题
// 在 Pattern::OnModifyDone() 添加日志
void ButtonPattern::OnModifyDone()
{
    auto theme = GetTheme<ButtonTheme>();
    LOGI("ButtonPattern::OnModifyDone: theme=%{public}p, bgColor=%{public}x",
         theme.Get(), theme ? theme->GetBgColor().GetValue() : 0);
}

// 3. 检查组件是否标记 dirty
// 在 Pattern 中检查是否调用了 MarkDirtyNode
```

**解决方案**：

```cpp
// 确保在 OnModifyDone 中重新获取主题
void ButtonPattern::OnModifyDone()
{
    // 重新获取主题（缓存已清空，会构建新主题）
    auto theme = GetTheme<ButtonTheme>();
    if (theme) {
        // 应用新主题
        UpdateButtonStyle(theme);

        // 标记需要重新渲染
        auto host = GetHost();
        if (host) {
            host->MarkDirtyNode(PROPERTY_PATTERN_RENDER_CONTEXT);
        }
    }
}
```

#### 问题 2：TokenTheme 获取失败

**现象**：
```
GetTheme(type, themeScopeId) 返回 nullptr
```

**原因分析**：
1. TokenThemeStorage 中未存储对应的 themeScopeId
2. TokenTheme 未缓存
3. TokenTheme 构建失败

**调试步骤**：

```cpp
// 1. 检查 themeScopeId 是否正确存储
auto tokenTheme = NG::TokenThemeStorage::GetInstance()->GetTheme(themeScopeId);
LOGI("GetTheme: themeScopeId=%{public}d, tokenTheme=%{public}p",
     themeScopeId, tokenTheme.Get());

// 2. 检查 TokenThemeStorage::themeScopeMap_
auto& storage = *NG::TokenThemeStorage::GetInstance();
auto it = storage.themeScopeMap_.find(themeScopeId);
if (it != storage.themeScopeMap_.end()) {
    LOGI("themeScopeMap_[%{public}d] = %{public}d", themeScopeId, it->second);
} else {
    LOGE("themeScopeId not found in themeScopeMap_");
}

// 3. 检查 TokenThemeStorage::themeCache_
auto themeId = storage.themeScopeMap_[themeScopeId];
auto& cache = storage.themeCache_;
auto cacheIt = cache.find(themeId);
if (cacheIt != cache.end()) {
    LOGI("themeCache_[%{public}d] = %{public}p", themeId, cacheIt->second.Get());
} else {
    LOGE("themeId not found in themeCache_");
}
```

**解决方案**：

```cpp
// 确保在 WithThemeNode 中正确存储主题作用域
void WithThemeNode::SetThemeScopeId(int32_t themeScopeId) override
{
    UINode::SetThemeScopeId(themeScopeId);

    // 存储 themeScopeId 到 TokenThemeStorage
    NG::TokenThemeStorage::GetInstance()->StoreThemeScope(themeScopeId, themeId);

    // 通知子节点更新
    NotifyThemeScopeUpdate();
}
```

#### 问题 3：主题包装器缓存未命中

**现象**：
```
GetTheme(type, themeScopeId) 每次都重新构建 ThemeWrapper
```

**原因分析**：
1. ColorMode 判断错误，选择了错误的缓存
2. themeWrappers 缓存被清空
3. ThemeType 不匹配

**调试步骤**：

```cpp
// 在 GetThemeOrigin 中添加调试日志
RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type, int32_t themeScopeId)
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, GetTheme(type));
    ColorMode currentMode = GetCurrentColorMode();
    ColorMode themeMode = tokenTheme->GetColorMode();

    LOGI("GetThemeOrigin: type=%{public}d, themeScopeId=%{public}d, "
         "currentMode=%{public}d, themeMode=%{public}d",
         type, themeScopeId, static_cast<int>(currentMode), static_cast<int>(themeMode));

    auto& themeWrappers = GetThemeWrappers(
        themeMode == ColorMode::COLOR_MODE_UNDEFINED ? currentMode : themeMode);

    LOGI("GetThemeOrigin: using %{public}s cache, size=%{public}zu",
         (themeMode == ColorMode::DARK) ? "Dark" : "Light", themeWrappers.size());

    auto findIter = themeWrappers.find(type);
    if (findIter != themeWrappers.end()) {
        LOGI("GetThemeOrigin: cache hit for type=%{public}d", type);
        // ...
    } else {
        LOGI("GetThemeOrigin: cache miss for type=%{public}d", type);
        // ...
    }
}
```

**解决方案**：

```cpp
// 确保 ColorMode 判断正确
ColorMode ThemeManagerImpl::GetCurrentColorMode() const
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    ColorMode systemMode = Container::CurrentColorMode();
    CHECK_NULL_RETURN(pipelineContext, systemMode);
    ColorMode localMode = pipelineContext->GetLocalColorMode();

    LOGD("GetCurrentColorMode: localMode=%{public}d, systemMode=%{public}d",
         static_cast<int>(localMode), static_cast<int>(systemMode));

    return localMode == ColorMode::COLOR_MODE_UNDEFINED ? systemMode : localMode;
}
```

### 8.2 调试方法

#### 使用 DumpInfo

在 ThemeManagerImpl 中添加 DumpInfo 方法：

```cpp
void ThemeManagerImpl::DumpInfo(std::ostream& os) const
{
    os << "ThemeManagerImpl dump:\n";
    os << "  themes_.size() = " << themes_.size() << "\n";
    os << "  themeWrappersLight_.size() = " << themeWrappersLight_.size() << "\n";
    os << "  themeWrappersDark_.size() = " << themeWrappersDark_.size() << "\n";
    os << "  currentThemeId_ = " << currentThemeId_ << "\n";

    os << "  Cached themes:\n";
    for (const auto& [type, theme] : themes_) {
        os << "    [" << type << "] = " << theme.Get() << "\n";
    }

    os << "  Cached theme wrappers (Light):\n";
    for (const auto& [type, wrapper] : themeWrappersLight_) {
        os << "    [" << type << "] = " << wrapper.Get() << "\n";
    }

    os << "  Cached theme wrappers (Dark):\n";
    for (const auto& [type, wrapper] : themeWrappersDark_) {
        os << "    [" << type << "] = " << wrapper.Get() << "\n";
    }
}
```

调用方式：

```cpp
// 在 Pattern 或测试代码中调用
themeManager->DumpInfo(std::cerr);
```

#### 使用日志标记

在关键路径添加日志：

```cpp
#define THEME_LOG_TAG "ThemeManager"

// 主题获取日志
TAG_LOGI(THEME_LOG_TAG, "GetTheme: type=%{public}d, themeScopeId=%{public}d", type, themeScopeId);

// 缓存命中/未命中日志
TAG_LOGD(THEME_LOG_TAG, "Theme cache %{public}s for type=%{public}d",
         findIter != themes_.end() ? "hit" : "miss", type);

// 颜色模式切换日志
TAG_LOGI(THEME_LOG_TAG, "Color mode changed: %{public}d → %{public}d",
         static_cast<int>(oldMode), static_cast<int>(newMode));
```

#### 使用单元测试

参考 `test/unittest/core/manager/theme_manager_test_ng.cpp`：

```cpp
TEST_F(ThemeManagerTest, GetTheme_CacheHit)
{
    // 第一次获取
    auto theme1 = themeManager_->GetTheme<ButtonTheme>();
    ASSERT_NE(theme1, nullptr);

    // 第二次获取（应该命中缓存）
    auto theme2 = themeManager_->GetTheme<ButtonTheme>();
    ASSERT_EQ(theme1, theme2);  // 相同指针
}

TEST_F(ThemeManagerTest, GetThemeWithThemeScopeId_TokenTheme)
{
    // 存储 Token 主题
    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(123);
    TokenThemeStorage::GetInstance()->StoreThemeScope(456, 123);
    TokenThemeStorage::GetInstance()->CacheSet(tokenTheme);

    // 获取带 ThemeScopeId 的主题
    auto theme = themeManager_->GetTheme<ButtonTheme>(456);
    ASSERT_NE(theme, nullptr);
}
```

### 8.3 性能分析

#### 缓存命中率统计

```cpp
class ThemeManagerImpl : public ThemeManager {
private:
    struct CacheStats {
        uint64_t hits = 0;
        uint64_t misses = 0;
    };
    CacheStats themesStats_;
    CacheStats wrappersStats_;

public:
    void DumpCacheStats() const
    {
        double themeHitRate = 100.0 * themesStats_.hits /
            (themesStats_.hits + themesStats_.misses);
        double wrapperHitRate = 100.0 * wrappersStats_.hits /
            (wrappersStats_.hits + wrappersStats_.misses);

        LOGI("Theme cache hit rate: %{public}.2f%% (%{public}llu / %{public}llu)",
             themeHitRate, themesStats_.hits, themesStats_.hits + themesStats_.misses);
        LOGI("Wrapper cache hit rate: %{public}.2f%% (%{public}llu / %{public}llu)",
             wrapperHitRate, wrappersStats_.hits, wrappersStats_.hits + wrappersStats_.misses);
    }
};
```

#### 主题构建时间统计

```cpp
RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    auto builderIter = THEME_BUILDERS.find(type);
    if (builderIter == THEME_BUILDERS.end()) {
        return nullptr;
    }

    auto theme = builderIter->second(themeConstants_);
    themes_.emplace(type, theme);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    LOGD("Theme built: type=%{public}d, duration=%{public}lld μs", type, duration.count());

    return theme;
}
```

---

## 9. 扩展指南

### 9.1 添加新组件主题

#### 步骤 1：定义主题类

```cpp
// frameworks/core/components/mycomponent/mycomponent_theme.h
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MYCOMPONENT_MYCOMPONENT_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MYCOMPONENT_MYCOMPONENT_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

class MyComponentTheme : public virtual Theme {
    DECLARE_ACE_TYPE(MyComponentTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MyComponentTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MyComponentTheme> theme = AceType::MakeRefPtr<MyComponentTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
                         const RefPtr<MyComponentTheme>& theme) const
        {
            RefPtr<ThemeStyle> myComponentPattern =
                themeConstants->GetPatternByName(THEME_PATTERN_MYCOMPONENT);
            if (!myComponentPattern) {
                LOGW("find pattern of MyComponent fail");
                return;
            }
            // 解析主题属性
            theme->bgColor_ = myComponentPattern->GetAttr<Color>("mycomponent_bg_color", Color());
            theme->textSize_ = myComponentPattern->GetAttr<Dimension>("mycomponent_text_size", 0.0_fp);
        }
    };

    ~MyComponentTheme() override = default;

    // Getter 方法
    Color GetBgColor() const { return bgColor_; }
    Dimension GetTextSize() const { return textSize_; }

private:
    MyComponentTheme() = default;

    Color bgColor_;
    Dimension textSize_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MYCOMPONENT_MYCOMPONENT_THEME_H
```

#### 步骤 2：注册主题构建器

```cpp
// frameworks/core/components/theme/theme_manager_impl.cpp

// 在文件顶部添加头文件
#include "core/components/mycomponent/mycomponent_theme.h"

// 在 THEME_BUILDERS 映射表中添加条目
const std::unordered_map<ThemeType, RefPtr<Theme>(*)(const RefPtr<ThemeConstants>&)>
    THEME_BUILDERS = {
    // ... 现有条目 ...
    { MyComponentTheme::TypeId(), &ThemeBuildFunc<MyComponentTheme::Builder> },
};
```

#### 步骤 3：在 Pattern 中使用主题

```cpp
// frameworks/core/components_ng/pattern/mycomponent/mycomponent_pattern.cpp

void MyComponentPattern::OnModifyDone()
{
    // 获取主题
    auto theme = GetTheme<MyComponentTheme>();
    if (!theme) {
        LOGE("MyComponentTheme is null");
        return;
    }

    // 应用主题
    auto layoutProperty = GetLayoutProperty<MyComponentLayoutProperty>();
    layoutProperty->UpdateBackgroundColor(theme->GetBgColor());

    auto paintProperty = GetPaintProperty<MyComponentPaintProperty>();
    paintProperty->UpdateTextSize(theme->GetTextSize());

    // 标记需要重新渲染
    auto host = GetHost();
    if (host) {
        host->MarkDirtyNode(PROPERTY_PATTERN_RENDER_CONTEXT);
    }
}
```

### 9.2 添加 Token 主题包装器

#### 步骤 1：定义主题包装器类

```cpp
// frameworks/core/components_ng/pattern/mycomponent/mycomponent_theme_wrapper.h
#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MYCOMPONENT_MYCOMPONENT_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MYCOMPONENT_MYCOMPONENT_THEME_WRAPPER_H

#include "core/components/mycomponent/mycomponent_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class MyComponentThemeWrapper : public MyComponentTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(MyComponentThemeWrapper, MyComponentTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(
            const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<MyComponentThemeWrapper>();
            auto theme = AceType::DynamicCast<MyComponentTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            InitThemeDefaults(theme);
            ParsePattern(themeConstants, theme);
            return wrapper;
        }
    };

    ~MyComponentThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            bgColor_ = colors->BackgroundPrimary();  // 使用 Token 颜色
        }
    }

protected:
    MyComponentThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MYCOMPONENT_MYCOMPONENT_THEME_WRAPPER_H
```

#### 步骤 2：注册主题包装器构建器

```cpp
// frameworks/core/components/theme/theme_manager_impl.cpp

// 在文件顶部添加头文件
#include "core/components_ng/pattern/mycomponent/mycomponent_theme_wrapper.h"

// 在 TOKEN_THEME_WRAPPER_BUILDERS 映射表中添加条目
const std::unordered_map<ThemeType, RefPtr<TokenThemeWrapper>(*)(const RefPtr<ThemeConstants>&)>
    TOKEN_THEME_WRAPPER_BUILDERS = {
    // ... 现有条目 ...
    { MyComponentTheme::TypeId(),
        &ThemeWrapperBuildFunc<NG::MyComponentThemeWrapper::WrapperBuilder> },
};
```

### 9.3 注册 Kit 扩展构建器

#### 运行时注册

```cpp
// 在应用启动时注册 Kit 构建器
auto RegisterMyComponentTheme = []() {
    ThemeManager::GetInstance()->RegisterThemeKit(
        MyComponentTheme::TypeId(),
        []() -> RefPtr<Theme> {
            // Kit 构建器实现
            auto theme = AceType::MakeRefPtr<MyComponentTheme>();
            // ... 构建逻辑 ...
            return theme;
        }
    );
};

// 调用注册
RegisterMyComponentTheme();
```

#### Kit 构建器优势

1. **动态加载**：支持插件式扩展
2. **跨模块**：可以从其他模块注册主题
3. **灵活性**：支持更复杂的构建逻辑

---

## 总结

### 核心要点

1. **三层架构**：
   - **ThemeManager**：主题管理接口
   - **ThemeManagerImpl**：具体实现（缓存、构建、多线程）
   - **ThemeConstants + ResourceAdapter**：资源适配层

2. **双层缓存机制**：
   - **普通主题缓存**（themes_）：缓存普通 Theme 对象
   - **Token 主题包装器缓存**（themeWrappersLight_/Dark_）：缓存浅色/深色模式的 ThemeWrapper

3. **Token 主题系统集成**：
   - **TokenThemeStorage**：全局 Token 主题缓存
   - **ThemeScopeId**：局部主题覆盖机制
   - **ApplyTokenTheme**：动态更新 Token 颜色

4. **颜色模式支持**：
   - **Light/Dark 双缓存**：快速模式切换
   - **局部颜色模式**：支持 WithThemeNode 局部覆盖
   - **系统颜色模式**：跟随系统配置

5. **性能优化策略**：
   - **延迟构建**：按需构建主题
   - **缓存复用**：避免重复构建
   - **多线程安全**：支持多线程访问

### 相关文件路径汇总

| 文件 | 路径 | 说明 |
|------|------|------|
| **ThemeManager 接口** | `frameworks/core/components/theme/theme_manager.h` | 主题管理器抽象接口 |
| **ThemeManagerImpl 头文件** | `frameworks/core/components/theme/theme_manager_impl.h` | 主题管理器实现类 |
| **ThemeManagerImpl 实现** | `frameworks/core/components/theme/theme_manager_impl.cpp` | 主题管理器实现代码 |
| **多线程支持** | `frameworks/core/components/theme/theme_manager_multi_thread.cpp` | 多线程主题构建 |
| **ThemeConstants** | `frameworks/core/components/theme/theme_constants.h` | 资源常量管理器 |
| **ResourceAdapter** | `frameworks/core/components/theme/resource_adapter.h` | 资源适配器接口 |
| **TokenThemeStorage** | `frameworks/core/components_ng/token_theme/token_theme_storage.h` | Token 主题存储 |
| **TokenThemeWrapper** | `interfaces/inner_api/ace_kit/include/ui/view/theme/token_theme_wrapper.h` | Token 主题包装器接口 |
| **WithThemeNode** | `frameworks/core/components_ng/syntax/with_theme_node.h` | WithTheme 语法节点 |
| **ButtonTheme 示例** | `frameworks/core/components/button/button_theme.h` | Button 主题定义 |
| **TextThemeWrapper 示例** | `frameworks/core/components_ng/pattern/text/text_theme_wrapper.h` | Text 主题包装器 |

### 参考资料

- **CLAUDE.md**: `frameworks/core/components/pattern/CLAUDE.md` - Pattern 层开发指南
- **Inner API 规范**: `interfaces/inner_api/CLAUDE.md` - Inner API 模块规范
- **单元测试**: `test/unittest/core/manager/theme_manager_test_ng.cpp` - ThemeManager 单元测试
- **Token 主题测试**: `test/unittest/interfaces/ace_kit/token_theme_test.cpp` - Token 主题测试

---

**文档维护**：
- **创建日期**: 2026-02-07
- **最后更新**: 2026-02-07
- **维护者**: Claude (ACE Engine 架构分析)
- **版本**: v1.0
