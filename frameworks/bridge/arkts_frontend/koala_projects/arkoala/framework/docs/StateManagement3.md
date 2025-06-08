Thoughts on [variable decorators v3](https://gitee.com/arkui-finland/public-reports/blob/master/stateMgmt3/variable_decorators_design.md)

## Component decorators

It seems that support for new component decorators does not look difficult.
It can be easily developed after improving current implementation of our ETS-plugin.
There may be problems with the difference in $ processing, but they seem solvable.

1. Introduce an ability to create a property translator from two decorators, i.e. @Param @Once
2. Develop new property translators, because most of them cannot reuse current implementation
3. Have to parse and process $-prefix contextually
   - Parse and process !!-postfix
   - Generate $-handlers automatically

## Model View decorators

It is much more worse with object decorators.
We may need to introduce an outdated concept of listeners, which has a strong impact on performance.
In addition, the ability to track changes in object fields depends on the capabilities of TS Reflection.
It can cause problems with the migration to ArkTS programming language.

1. Have to support @Track in current implementation
2. Have to implement @Trace for new API
3. Have to implement @Monitor for new API
   - It requires to improve our observable proxy
   - It may require to add state listeners to our state manager (bad idea)
4. Support @Computed functions, which look like @memo-functions
   - Investigate an ability to use our StateManager.computableState to implement them
5. ArkUI.mkObserved - public API to add mentioned functionality to any object without @Observed
6. Revisit our deepCopy and add an ability to specify its depth
7. Support serialization/deserialization
