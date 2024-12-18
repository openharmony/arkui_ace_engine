export const useEnabled = <T>(enabled: boolean, value: T, defaultValue: T | undefined = undefined) => {
  return enabled ? value : defaultValue;
}
export const useEnabledBase = <T>(enabled: boolean, value: T, defaultValue: Length) => {
  return enabled ? value : defaultValue;
}
export const useEnabledNumber = <T>(enabled: boolean, value: T, defaultValue: number) => {
  return enabled ? value : defaultValue;
}
export const useEnabledArray = <T>(enabled: boolean, value: T, defaultValue: T | number[]) => {
  return enabled ? value : defaultValue;
}
export function tagDesRule(title: string, radioName: string): string {
  return `开启了[${title}]调整为[${radioName}]`
}