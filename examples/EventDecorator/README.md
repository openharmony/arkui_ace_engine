# @Event装饰器：规范组件输出

### 介绍

本工程主要实现了对以下指南文档中 [@Event装饰器：规范组件输出](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/ui/state-management/arkts-new-event.md) 示例代码片段的工程化，主要目标是帮助开发者快速了解在@ComponentV2装饰的自定义组件中使用@Event装饰器。

### 更改父组件中变量

#### 介绍

1. 使用@Event可以更改父组件中变量，当该变量作为子组件@Param变量的数据源时，该变化会同步回子组件的@Param变量。

#### 效果预览

<img src="screenshots/EventDecoratorTest1.gif" width="250">

#### 使用说明

1. 通过点击主页的EventDecoratorTest1Button按钮，跳转到EventDecoratorTest1页面，点击change to Title Two按钮change to Title One按钮，其title值会进行改变。

### 父组件将变化同步回子组件的过程是异步

#### 介绍

1. 使用@Event修改父组件的值是立刻生效的，但从父组件将变化同步回子组件的过程是异步的，即在调用完@Event的方法后，子组件内的值不会立刻变化。这是因为@Event将子组件值实际的变化能力交由父组件处理，在父组件实际决定如何处理后，将最终值在渲染之前同步回子组件。

#### 效果预览

<img src="screenshots/EventDecoratorTest2.gif" width="250">

#### 使用说明

1. 通过点击主页的EventDecoratorTest2Button按钮，跳转到EventDecoratorTest2页面，点击Text组件，其index也会进行改变。

### 工程目录

```
entry/src/main/
|---ets
|---|---entryability
|---|---|---EntryAbility.ets
|---|---pages
|---|---|---EventDecoratorTest1.ets
|---|---|---EventDecoratorTest2.ets
|---|---|---Index.ets						// 首页
|---resources								// 静态资源
|---ohosTest
|---|---ets
|---|---|---tests
|---|---|---|---Ability.test.ets            // 自动化测试用例
```

### 具体实现

1. 使用@Event可以更改父组件中变量，当该变量作为子组件@Param变量的数据源时，该变化会同步回子组件的@Param变量。
2. 使用@Event修改父组件的值是立刻生效的，但从父组件将变化同步回子组件的过程是异步的，即在调用完@Event的方法后，子组件内的值不会立刻变化。这是因为@Event将子组件值实际的变化能力交由父组件处理，在父组件实际决定如何处理后，将最终值在渲染之前同步回子组件。
3. 点击文字触发@Event函数事件改变子组件的值。
4. 在调用changeIndex之后，父组件中index的值已经变化，但子组件中的index值还没有同步变化。

### 相关权限

不涉及。

### 依赖

不涉及。

### 约束与限制

1. 本示例仅支持标准系统上运行，支持设备：华为手机。
2. 本示例支持API22版本SDK，SDK版本号(API Version 22 Release)。
3. 本示例需要使用DevEco Studio 版本号(6.0.0Release)才可编译运行。

### 下载

如需单独下载本工程，执行如下命令：

```
git init
git config core.sparsecheckout true
echo code/DocsSample/ArkUISample/EventDecorator > .git/info/sparse-checkout
git remote add origin https://gitcode.com/openharmony/applications_app_samples.git
git pull origin master
```