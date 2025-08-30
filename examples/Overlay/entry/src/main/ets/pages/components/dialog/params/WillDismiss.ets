export const dismissTestList: string[] = [
  // 1. 回调事件为空
  'NA',
  // 2. 回调事件undefined
  'undefined',
  // 3. 回调事件设置func
  'DismissDialog.dismiss()',

  // 4.reason设置undefined, 回调事件禁止
  'reason_undefined_0',
  // 5.reason设置undefined, 回调事件允许
  'reason_undefined_1',

  // 6.reason判断index, 回调事件禁止
  'reason_index_0',
  // 7.reason判断index, 回调事件允许
  'reason_index_1',

  // 8.reason判断枚举值, 回调事件禁止
  'reason_enum_0',
  // 9.reason判断枚举值, 回调事件允许
  'reason_enum_1',
]