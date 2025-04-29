export class Utils {
  static getEnumKey(dataType: any, index?: number): string {
    if (index == undefined) {
      return 'undefined'
    } else {
      return dataType[index]
    }
  }

  static deepCopyInter<T>(obj: T): T | 'undefined' | 'null' {
    if (obj === undefined) {
      return 'undefined';
    } else if (obj === null) {
      return 'null';
    } else if (typeof obj !== 'object') {
      return obj
    }
    const result: any = Array.isArray(obj) ? [] : {};
    for (const key in obj) {
      if (Object.prototype.hasOwnProperty.call(obj, key)) {
        result[key] = Utils.deepCopyInter(obj[key]);
      }
    }

    return result
  }

  static deepCopy(obj: object, isString: boolean = true): any {
    let result = Utils.deepCopyInter(obj)
    if (isString) {
      return JSON.stringify(result)
    } else {
      return result
    }
  }
}